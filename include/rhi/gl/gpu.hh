/*
    * @file include/rhi/gl/gpu.hh
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * OpenGL GPU implementation using GLEW
    *
*/

#pragma once

#include <rhi/gpu.hh>
#include <memory>

namespace kairo::rhi::gl {

/**
 * @brief OpenGL GPU implementation using GLEW
 */
class GlGpu : public IGpu {
public:
    GlGpu();
    ~GlGpu() override;

    Result initialize() override;
    void shutdown() override;
    std::string getName() const override;
    BackendType getBackendType() const override;
    ContextHandle createContext() override;
    bool isInitialized() const override;

private:
    bool m_initialized{false};
    std::string m_gpuName{};

    /**
     * @brief Initialize GLEW
     */
    Result initializeGlew();
};

}  // namespace kairo::rhi::gl
