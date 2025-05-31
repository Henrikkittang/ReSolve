cmake_minimum_required(VERSION 3.14)
project(OpenGLProject)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory
if(NOT MSVC)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
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
)

# Source files
file(GLOB_RECURSE PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Executable target
add_executable(OpenGLProject 
    ${PROJECT_SOURCES}
    ${CMAKE_SOURCE_DIR}/vendor/stb_image/stb_image.cpp
)

target_include_directories(OpenGLProject PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/vendor
    ${CMAKE_SOURCE_DIR}/vendor/GLFW/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Link libraries
target_link_libraries(OpenGLProject PRIVATE
    glad
    glfw
    OpenGL::GL
    imgui
)

# Compiler definitions
target_compile_definitions(OpenGLProject PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
)

# Compiler options
target_compile_options(OpenGLProject PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
)

# Optional: Windows-specific linkage
if (WIN32)
    target_link_libraries(OpenGLProject PRIVATE gdi32)
endif()
