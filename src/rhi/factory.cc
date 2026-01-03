/*
    * @file src/rhi/factory.cc
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * Implementation of the RHI factory for graphics backend creation
    *
*/

#include <rhi/factory.hh>
#include <rhi/gl/gpu.hh>
#include <stdexcept>
#include <util/logger.hh>

namespace kairo::rhi {

BackendType RhiFactory::s_preferredBackend = BackendType::OpenGL;

void RhiFactory::setPreferredBackend(BackendType backend) {
    s_preferredBackend = backend;
    std::string backend_name;
    switch (backend) {
        case BackendType::OpenGL: backend_name = "OpenGL"; break;
        case BackendType::Vulkan: backend_name = "Vulkan"; break;
        case BackendType::DirectX12: backend_name = "DirectX 12"; break;
        case BackendType::Metal: backend_name = "Metal"; break;
        default: backend_name = "Unknown"; break;
    }
    Logger::getInstance()->logInfo("RHI backend set to: " + backend_name);
}

BackendType RhiFactory::getPreferredBackend() {
    return s_preferredBackend;
}

GpuHandle RhiFactory::createGpu() {
    return createGpu(s_preferredBackend);
}

GpuHandle RhiFactory::createGpu(BackendType backend) {
    switch (backend) {
        case BackendType::OpenGL:
            return std::make_shared<gl::GlGpu>();
        case BackendType::Vulkan:
            Logger::getInstance()->logWarning("Vulkan backend not yet implemented");
            return nullptr;
        case BackendType::DirectX12:
            Logger::getInstance()->logWarning("DirectX 12 backend not yet implemented");
            return nullptr;
        case BackendType::Metal:
            Logger::getInstance()->logWarning("Metal backend not yet implemented");
            return nullptr;
        default:
            Logger::getInstance()->logError("Unknown backend type");
            return nullptr;
    }
}

bool RhiFactory::isBackendSupported(BackendType backend) {
    // For now, only OpenGL is fully implemented
    return backend == BackendType::OpenGL;
}

}  // namespace kairo::rhi
