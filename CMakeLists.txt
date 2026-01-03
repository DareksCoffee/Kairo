cmake_minimum_required(VERSION 3.10)
project(Kairo VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set policies for newer CMake versions
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find pkg-config for better package detection on Linux
find_package(PkgConfig QUIET)

# Find required packages
find_package(Vulkan REQUIRED)

if(PkgConfig_FOUND)
    pkg_check_modules(GLFW REQUIRED glfw3)
else()
    find_package(GLFW3 REQUIRED)
endif()

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# DirectX support (Windows only)
if(WIN32)
    find_package(DirectX QUIET)
    if(NOT DirectX_FOUND)
        # Try using d3d11 directly
        set(DirectX_FOUND TRUE)
        set(DirectX_INCLUDE_DIRS "")  # System includes
    endif()
endif()

# Automatically find all .cc files in src/
file(GLOB_RECURSE SOURCES "src/*.cc")

# Create the executable
add_executable(kairo ${SOURCES})

# Link libraries
target_link_libraries(kairo PRIVATE
    Vulkan::Vulkan
    ${GLFW_LIBRARIES}
    GLEW::GLEW
    OpenGL::OpenGL
)

# Windows-specific DirectX linking
if(WIN32 AND DirectX_FOUND)
    target_link_libraries(kairo PRIVATE
        d3d11
        d3d12
        dxgi
        d3dcompiler
    )
endif()

# Include directories for pkg-config results
if(GLFW_INCLUDE_DIRS)
    target_include_directories(kairo PRIVATE ${GLFW_INCLUDE_DIRS})
endif()


# Compiler flags
if(MSVC)
    target_compile_options(kairo PRIVATE /W4 /permissive-)
else()
    target_compile_options(kairo PRIVATE -Wall -Wextra -Wpedantic -fPIC)
endif()

# Platform-specific settings
if(APPLE)
    # macOS specific configurations
    set_target_properties(kairo PROPERTIES
        MACOSX_RPATH ON
    )
elseif(LINUX)
    # Linux specific configurations
    # Usually no additional setup needed
elseif(WIN32)
    # Windows specific configurations
    target_compile_options(kairo PRIVATE /D_CRT_SECURE_NO_WARNINGS)
    if(DirectX_FOUND)
        target_compile_definitions(kairo PRIVATE KAIRO_DIRECTX_ENABLED)
    endif()
endif()

# Output directory
set_target_properties(kairo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Print build info
message(STATUS "")
message(STATUS "=== Kairo Engine Build Configuration ===")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Source files found: ${SOURCES}")
message(STATUS "")
message(STATUS "=== Dependencies ===")
message(STATUS "  Vulkan: ${Vulkan_FOUND} (${Vulkan_VERSION})")
message(STATUS "  GLFW3: ${GLFW_FOUND}")
message(STATUS "  GLEW: ${GLEW_FOUND}")
message(STATUS "  OpenGL: ${OPENGL_FOUND}")
if(WIN32)
    message(STATUS "  DirectX: ${DirectX_FOUND}")
endif()
message(STATUS "")
message(STATUS "=== Build Directories ===")
message(STATUS "  Executable output: ${CMAKE_BINARY_DIR}/bin")
message(STATUS "")
