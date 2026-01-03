/*
    * @file src/core/window.cc
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * Implementation of window management using GLFW
    *
*/

#include <core/window.hh>
#include <util/logger.hh>
#include <GLFW/glfw3.h>

namespace kairo::core {

Window::Window(const WindowProperties& props)
    : m_properties(props) {
    Logger::getInstance()->logDebug("Creating window: " + std::to_string(props.width) + "x" + std::to_string(props.height) + " - " + props.title);
}

Window::~Window() {
    if (m_initialized) {
        shutdown();
    }
}

bool Window::initialize() {
    Logger::getInstance()->logInfo("Initializing window: " + std::to_string(m_properties.width) + "x" + std::to_string(m_properties.height) + " - " + m_properties.title);

    if (m_initialized) {
        Logger::getInstance()->logWarning("Window already initialized");
        return true;
    }

    // Initialize GLFW if not already done
    if (!glfwInit()) {
        Logger::getInstance()->logError("Failed to initialize GLFW");
        return false;
    }

    // Set OpenGL context hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, m_properties.resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, m_properties.decorated ? GLFW_TRUE : GLFW_FALSE);

    // Create the window
    GLFWwindow* window = glfwCreateWindow(
        static_cast<int>(m_properties.width),
        static_cast<int>(m_properties.height),
        m_properties.title.c_str(),
        nullptr,
        nullptr
    );

    if (!window) {
        Logger::getInstance()->logError("Failed to create GLFW window");
        glfwTerminate();
        return false;
    }

    m_nativeHandle = window;

    // Set window position
    glfwSetWindowPos(window, m_properties.x, m_properties.y);

    // Make the window the current OpenGL context
    glfwMakeContextCurrent(window);

    // Set vsync
    glfwSwapInterval(m_properties.vsync ? 1 : 0);

    // Store this pointer in the user pointer for callback access
    glfwSetWindowUserPointer(window, this);

    // Set window close callback
    glfwSetWindowCloseCallback(window, [](GLFWwindow* w) {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (self) {
            self->m_shouldClose = true;
        }
    });

    // Set window resize callback
    glfwSetWindowSizeCallback(window, [](GLFWwindow* w, int width, int height) {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (self) {
            self->m_properties.width = static_cast<uint32_t>(width);
            self->m_properties.height = static_cast<uint32_t>(height);
            Logger::getInstance()->logInfo("Window resized to " + std::to_string(width) + "x" + std::to_string(height));
        }
    });

    m_initialized = true;
    Logger::getInstance()->logInfo("Window initialized successfully");
    return true;
}

void Window::shutdown() {
    if (!m_initialized) {
        return;
    }

    Logger::getInstance()->logInfo("Shutting down window");

    if (m_nativeHandle) {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_nativeHandle);
        glfwDestroyWindow(window);
        m_nativeHandle = nullptr;
    }

    glfwTerminate();
    m_initialized = false;
}

bool Window::isOpen() const {
    return m_initialized && !m_shouldClose;
}

bool Window::shouldClose() const {
    if (!m_nativeHandle) {
        return true;
    }

    GLFWwindow* window = static_cast<GLFWwindow*>(m_nativeHandle);
    return glfwWindowShouldClose(window) || m_shouldClose;
}

void Window::pollEvents() {
    if (!m_initialized) {
        Logger::getInstance()->logWarning("Window not initialized");
        return;
    }

    glfwPollEvents();
}

void Window::update() {
    if (!m_initialized) {
        return;
    }

    GLFWwindow* window = static_cast<GLFWwindow*>(m_nativeHandle);
    if (window) {
        glfwSwapBuffers(window);
    }
}

void Window::setWidth(uint32_t width) {
    m_properties.width = width;
    if (m_initialized && m_nativeHandle) {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_nativeHandle);
        glfwSetWindowSize(window, static_cast<int>(width), static_cast<int>(m_properties.height));
    }
}

void Window::setHeight(uint32_t height) {
    m_properties.height = height;
    if (m_initialized && m_nativeHandle) {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_nativeHandle);
        glfwSetWindowSize(window, static_cast<int>(m_properties.width), static_cast<int>(height));
    }
}

void Window::setPosition(int32_t x, int32_t y) {
    m_properties.x = x;
    m_properties.y = y;
    if (m_initialized && m_nativeHandle) {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_nativeHandle);
        glfwSetWindowPos(window, x, y);
    }
}

void Window::setTitle(const std::string& title) {
    m_properties.title = title;
    if (m_initialized && m_nativeHandle) {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_nativeHandle);
        glfwSetWindowTitle(window, title.c_str());
    }
}

void Window::setVsync(bool enabled) {
    m_properties.vsync = enabled;
    if (m_initialized) {
        glfwSwapInterval(enabled ? 1 : 0);
    }
}

}  // namespace kairo::core
