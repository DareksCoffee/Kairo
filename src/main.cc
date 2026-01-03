/*
    * @file src/main.cc
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * The main entry point for Kairo Engine
    *
*/

#include <stdio.h>
#include <util/logger.hh>
#include <core/window.hh>
#include <rhi/factory.hh>
#include <rhi/gpu.hh>
#include <rhi/context.hh>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    Logger::getInstance()->logInfo("=== Kairo Engine Starting ===");

    // Create window
    kairo::core::WindowProperties windowProps;
    windowProps.title = "Kairo Engine - OpenGL";
    windowProps.width = 1280;
    windowProps.height = 720;
    
    kairo::core::Window window(windowProps);
    if (!window.initialize()) {
        Logger::getInstance()->logError("Failed to initialize window");
        return 1;
    }

    // Initialize RHI factory and create GPU
    kairo::rhi::RhiFactory::setPreferredBackend(kairo::rhi::BackendType::OpenGL);
    auto gpu = kairo::rhi::RhiFactory::createGpu();
    
    if (!gpu || gpu->initialize() != kairo::rhi::Result::Success) {
        Logger::getInstance()->logError("Failed to initialize GPU");
        window.shutdown();
        return 1;
    }

    Logger::getInstance()->logInfo("GPU: " + gpu->getName());

    // Create graphics context
    auto context = gpu->createContext();
    if (!context) {
        Logger::getInstance()->logError("Failed to create graphics context");
        gpu->shutdown();
        window.shutdown();
        return 1;
    }

    // Main loop
    Logger::getInstance()->logInfo("Entering main loop");
    while (window.isOpen() && !window.shouldClose()) {
        window.pollEvents();

        // Rendering
        context->setViewport(0, 0, window.getWidth(), window.getHeight());
        context->clear(0.1f, 0.1f, 0.1f, 1.0f);

        window.update();
    }

    Logger::getInstance()->logInfo("Exiting main loop");

    // Cleanup
    context->shutdown();
    gpu->shutdown();
    window.shutdown();

    Logger::getInstance()->logInfo("=== Kairo Engine Shutdown ===");
    return 0;
}