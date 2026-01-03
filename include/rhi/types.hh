/*
    * @file include/rhi/types.hh
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * Core types and enumerations for the Rendering Hardware Interface (RHI)
    *
*/

#pragma once

#include <cstdint>
#include <memory>

namespace kairo::rhi {

// Forward declarations
class IGpu;
class IGraphicsContext;

using GpuHandle = std::shared_ptr<IGpu>;
using ContextHandle = std::shared_ptr<IGraphicsContext>;

// Backend types
enum class BackendType {
    OpenGL,
    Vulkan,
    DirectX12,
    Metal
};

// Result type for operations
enum class Result {
    Success,
    Failed,
    Unsupported,
    OutOfMemory
};

}  // namespace kairo::rhi
