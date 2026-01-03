/*
    * @file include/rhi/gpu.hh
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * GPU abstraction interface for graphics backends
    *
*/

#pragma once

#include <rhi/types.hh>
#include <string>

namespace kairo::rhi {

/**
 * @brief GPU abstraction interface
 * 
 * Defines the common interface for graphics hardware abstraction.
 */
class IGpu {
public:
    virtual ~IGpu() = default;

    /**
     * @brief Initialize the GPU
     * @return Result code
     */
    virtual Result initialize() = 0;

    /**
     * @brief Shutdown the GPU
     */
    virtual void shutdown() = 0;

    /**
     * @brief Get GPU name/description
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Get backend type
     */
    virtual BackendType getBackendType() const = 0;

    /**
     * @brief Create a graphics context
     * @return Shared pointer to the created context
     */
    virtual ContextHandle createContext() = 0;

    /**
     * @brief Check if GPU is initialized
     */
    virtual bool isInitialized() const = 0;
};

}  // namespace kairo::rhi
