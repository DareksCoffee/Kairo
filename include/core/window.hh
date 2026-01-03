/*
    * @file include/core/window.hh
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * Window management abstraction for the Kairo engine
    *
*/

#pragma once

#include <string>
#include <cstdint>
#include <functional>

namespace kairo::core {

/**
 * @brief Window configuration and properties
 */
struct WindowProperties {
    int32_t x = 0;
    int32_t y = 0;
    uint32_t width = 1280;
    uint32_t height = 720;
    std::string title = "Kairo Engine";
    bool vsync = true;
    bool resizable = true;
    bool decorated = true;
};

/**
 * @brief Window abstraction for the engine
 * 
 * Manages window creation, positioning, sizing and event handling.
 */
class Window {
public:
    /**
     * @brief Create a window instance
     * @param props Window properties
     */
    explicit Window(const WindowProperties& props = WindowProperties());
    
    ~Window();

    /**
     * @brief Initialize the window
     * @return True if successful, false otherwise
     */
    bool initialize();

    /**
     * @brief Shutdown the window
     */
    void shutdown();

    /**
     * @brief Check if the window is open
     */
    bool isOpen() const;

    /**
     * @brief Check if the window should close
     */
    bool shouldClose() const;

    /**
     * @brief Poll window events
     */
    void pollEvents();

    /**
     * @brief Update window state
     */
    void update();

    // Getters
    uint32_t getWidth() const { return m_properties.width; }
    uint32_t getHeight() const { return m_properties.height; }
    int32_t getPositionX() const { return m_properties.x; }
    int32_t getPositionY() const { return m_properties.y; }
    const std::string& getTitle() const { return m_properties.title; }
    bool getVsync() const { return m_properties.vsync; }

    // Setters
    void setWidth(uint32_t width);
    void setHeight(uint32_t height);
    void setPosition(int32_t x, int32_t y);
    void setTitle(const std::string& title);
    void setVsync(bool enabled);

    /**
     * @brief Get the native window handle
     * @return Opaque pointer to the native window (GLFWwindow*, etc.)
     */
    void* getNativeHandle() const { return m_nativeHandle; }

private:
    WindowProperties m_properties;
    void* m_nativeHandle{nullptr};
    bool m_initialized{false};
    bool m_shouldClose{false};

    /**
     * @brief Platform-specific window initialization
     */
    bool initializeNativeWindow();

    /**
     * @brief Platform-specific window shutdown
     */
    void shutdownNativeWindow();
};

}  // namespace kairo::core
