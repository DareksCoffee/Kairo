/*
    * @file include/rhi/context.hh
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * Graphics context abstraction interface for rendering operations
    *
*/

#pragma once

#include <rhi/types.hh>

namespace kairo::rhi {

/**
 * @brief Graphics context abstraction interface
 * 
 * Handles rendering operations and state management.
 */
class IGraphicsContext {
public:
    virtual ~IGraphicsContext() = default;

    /**
     * @brief Initialize the graphics context
     * @return Result code
     */
    virtual Result initialize() = 0;

    /**
     * @brief Shutdown the graphics context
     */
    virtual void shutdown() = 0;

    /**
     * @brief Begin a frame
     */
    virtual void beginFrame() = 0;

    /**
     * @brief End a frame and present
     */
    virtual void endFrame() = 0;

    /**
     * @brief Clear the framebuffer
     * @param r Red channel
     * @param g Green channel
     * @param b Blue channel
     * @param a Alpha channel
     */
    virtual void clear(float r, float g, float b, float a) = 0;

    /**
     * @brief Set viewport dimensions
     */
    virtual void setViewport(int x, int y, int width, int height) = 0;

    /**
     * @brief Check if context is initialized
     */
    virtual bool isInitialized() const = 0;
};

}  // namespace kairo::rhi
