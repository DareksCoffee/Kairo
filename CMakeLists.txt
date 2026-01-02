cmake_minimum_required(VERSION 3.10)
project(Kairo VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Automatically find all .cc files in src/
file(GLOB_RECURSE SOURCES "src/*.cc")

# Create the executable
add_executable(kairo ${SOURCES})

# Compiler flags
if(MSVC)
    target_compile_options(kairo PRIVATE /W4)
else()
    target_compile_options(kairo PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Output directory
set_target_properties(kairo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Print build info
message(STATUS "Kairo Engine Build Configuration")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Source files found: ${SOURCES}")
