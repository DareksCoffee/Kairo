/*
    * @file src/rhi/gl/context.cc
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * Implementation of OpenGL graphics context and rendering operations
    *
*/

#include <rhi/gl/context.hh>
#include <util/logger.hh>
#include <GL/glew.h>

namespace kairo::rhi::gl {

GlGraphicsContext::GlGraphicsContext() {
    Logger::getInstance()->logDebug("Creating OpenGL Graphics Context");
}

GlGraphicsContext::~GlGraphicsContext() {
    if (m_initialized) {
        shutdown();
    }
}

Result GlGraphicsContext::initialize() {
    Logger::getInstance()->logInfo("Initializing OpenGL Graphics Context");

    if (m_initialized) {
        Logger::getInstance()->logWarning("Graphics context already initialized");
        return Result::Success;
    }

    // Enable vsync
    // Note: This would typically be set via GLFW
    // glfwSwapInterval(1);

    m_initialized = true;
    return Result::Success;
}

void GlGraphicsContext::shutdown() {
    if (!m_initialized) {
        return;
    }

    Logger::getInstance()->logInfo("Shutting down OpenGL Graphics Context");
    m_initialized = false;
}

void GlGraphicsContext::beginFrame() {
    if (!m_initialized) {
        Logger::getInstance()->logError("Graphics context not initialized");
        return;
    }
}

void GlGraphicsContext::endFrame() {
    if (!m_initialized) {
        Logger::getInstance()->logError("Graphics context not initialized");
        return;
    }

    // Swap buffers would be called here (typically via GLFW)
    // glfwSwapBuffers(window);
}

void GlGraphicsContext::clear(float r, float g, float b, float a) {
    if (!m_initialized) {
        Logger::getInstance()->logWarning("Graphics context not initialized");
        return;
    }

    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GlGraphicsContext::setViewport(int x, int y, int width, int height) {
    if (!m_initialized) {
        Logger::getInstance()->logWarning("Graphics context not initialized");
        return;
    }

    glViewport(x, y, width, height);
}

bool GlGraphicsContext::isInitialized() const {
    return m_initialized;
}

}  // namespace kairo::rhi::gl
