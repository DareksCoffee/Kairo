/*
    * @file include/rhi/factory.hh
    * @author Coffee Games Studio
    * @date 1/3/2026
    * @brief
    * Factory for creating and switching between graphics backends
    *
*/

#pragma once

#include <rhi/types.hh>
#include <memory>

namespace kairo::rhi {

/**
 * @brief Factory for creating graphics backends
 * 
 * Provides a way to create and switch between different rendering backends.
 */
class RhiFactory {
public:
    /**
     * @brief Set the preferred backend
     * @param backend The backend type to use
     */
    static void setPreferredBackend(BackendType backend);

    /**
     * @brief Get the current preferred backend
     */
    static BackendType getPreferredBackend();

    /**
     * @brief Create a GPU instance for the preferred backend
     * @return Shared pointer to the created GPU
     */
    static GpuHandle createGpu();

    /**
     * @brief Create a GPU instance for a specific backend
     * @param backend The backend to use
     * @return Shared pointer to the created GPU
     */
    static GpuHandle createGpu(BackendType backend);

    /**
     * @brief Check if a backend is supported
     * @param backend The backend to check
     * @return True if supported, false otherwise
     */
    static bool isBackendSupported(BackendType backend);

private:
    static BackendType s_preferredBackend;
};

}  // namespace kairo::rhi
