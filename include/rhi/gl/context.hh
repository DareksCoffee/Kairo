/*
    * @file include/rhi/gl/context.hh
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * OpenGL graphics context implementation
    *
*/

#pragma once

#include <rhi/context.hh>

namespace kairo::rhi::gl {

/**
 * @brief OpenGL graphics context implementation
 */
class GlGraphicsContext : public IGraphicsContext {
public:
    GlGraphicsContext();
    ~GlGraphicsContext() override;

    Result initialize() override;
    void shutdown() override;
    void beginFrame() override;
    void endFrame() override;
    void clear(float r, float g, float b, float a) override;
    void setViewport(int x, int y, int width, int height) override;
    bool isInitialized() const override;

private:
    bool m_initialized{false};
};

}  // namespace kairo::rhi::gl
