/*
    * @file src/rhi/gl/gpu.cc
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * Implementation of OpenGL GPU initialization and management
    *
*/

#include <rhi/gl/gpu.hh>
#include <rhi/gl/context.hh>
#include <util/logger.hh>
#include <GL/glew.h>

namespace kairo::rhi::gl {

GlGpu::GlGpu() {
    Logger::getInstance()->logDebug("Creating OpenGL GPU");
}

GlGpu::~GlGpu() {
    if (m_initialized) {
        shutdown();
    }
}

Result GlGpu::initialize() {
    Logger::getInstance()->logInfo("Initializing OpenGL GPU");

    if (m_initialized) {
        Logger::getInstance()->logWarning("GPU already initialized");
        return Result::Success;
    }

    Result result = initializeGlew();
    if (result != Result::Success) {
        Logger::getInstance()->logError("Failed to initialize GLEW");
        return result;
    }

    // Get GPU name from OpenGL
    const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    if (renderer) {
        m_gpuName = std::string(renderer);
    } else {
        m_gpuName = "Unknown OpenGL Device";
    }

    Logger::getInstance()->logInfo("OpenGL Device: " + m_gpuName);
    Logger::getInstance()->logInfo("OpenGL Vendor: " + std::string(vendor ? vendor : "Unknown"));
    Logger::getInstance()->logInfo("OpenGL Version: " + std::string(version ? version : "Unknown"));

    m_initialized = true;
    return Result::Success;
}

void GlGpu::shutdown() {
    if (!m_initialized) {
        return;
    }

    Logger::getInstance()->logInfo("Shutting down OpenGL GPU");
    m_initialized = false;
}

std::string GlGpu::getName() const {
    return m_gpuName;
}

BackendType GlGpu::getBackendType() const {
    return BackendType::OpenGL;
}

ContextHandle GlGpu::createContext() {
    auto context = std::make_shared<GlGraphicsContext>();
    if (context->initialize() != Result::Success) {
        Logger::getInstance()->logError("Failed to initialize graphics context");
        return nullptr;
    }
    return context;
}

bool GlGpu::isInitialized() const {
    return m_initialized;
}

Result GlGpu::initializeGlew() {
    // Assume GLFW has already set up the OpenGL context
    glewExperimental = GL_TRUE;
    
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        Logger::getInstance()->logError("GLEW initialization failed: " + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        return Result::Failed;
    }

    Logger::getInstance()->logDebug("GLEW initialized successfully");
    return Result::Success;
}

}  // namespace kairo::rhi::gl
