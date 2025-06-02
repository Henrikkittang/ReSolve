cmake_minimum_required(VERSION 3.14)
project(ReSolve)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Detect platform
if(WIN32)
    set(PLATFORM_WINDOWS TRUE)
elseif(UNIX)
    set(PLATFORM_LINUX TRUE)
endif()

# Detect compiler
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(COMPILER_CLANG TRUE)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_GCC TRUE)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER_MSVC TRUE)
endif()

# Find OpenGL
find_package(OpenGL REQUIRED)

# Dependencies
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)

# ImGui setup
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui)

file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${CMAKE_SOURCE_DIR}/vendor/GLFW/include
    ${CMAKE_SOURCE_DIR}/vendor/glm/
)

# Source files
file(GLOB_RECURSE PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Executable target
add_executable(output 
    ${PROJECT_SOURCES}
    ${CMAKE_SOURCE_DIR}/vendor/stb_image/stb_image.cpp
)

target_include_directories(output PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/vendor
    ${CMAKE_SOURCE_DIR}/vendor/GLFW/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Link libraries
target_link_libraries(output PRIVATE
    glad
    glfw
    OpenGL::GL
    imgui
)

# Compiler definitions
target_compile_definitions(output PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
)

# Compiler options
if (COMPILER_GCC OR COMPILER_CLANG)
    target_compile_options(output PRIVATE
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Release>:-O3>
    )
elseif(COMPILER_MSVC)
    target_compile_options(output PRIVATE
        $<$<CONFIG:Debug>:/Zi /Od>
        $<$<CONFIG:Release>:/O2>
    )
endif()

# Platform-specific settings
if (PLATFORM_WINDOWS)
    target_link_libraries(output PRIVATE gdi32)
endif()
