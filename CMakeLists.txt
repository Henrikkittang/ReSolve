cmake_minimum_required(VERSION 3.14)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory (non-MSVC)
if(NOT MSVC)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

# Dependencies
find_package(OpenGL REQUIRED)

# Set library path manually
if(MSVC)
    set(LIBS ${CMAKE_SOURCE_DIR}/lib/lib-vc2022)
else()
    set(LIBS ${CMAKE_SOURCE_DIR}/lib/lib-mingw-w64)
endif()
link_directories(${LIBS})

# Add sub project
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)



# Add source files from your own code
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE VENDOR  "vendor/*.cpp")


# Define the executable
add_executable(output ${SOURCES})

# ImGui static library
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui)

add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${CMAKE_SOURCE_DIR}/vendor/GLFW/include  # <- Add this
)

target_include_directories(output PRIVATE
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/vendor/GLFW/include/  # for <GLFW/glfw3.h>
    ${CMAKE_SOURCE_DIR}/vendor/  # for <GLFW/glfw3.h>
    ${IMGUI_DIR}/backends
)



# Link libraries
target_link_libraries(output
    glad
    glfw
    OpenGL::GL
    gdi32
    imgui
)

# Compiler definitions
target_compile_definitions(output PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
)

# Compile options
target_compile_options(output PRIVATE
    $<$<CONFIG:Debug>:-Wall -g>
    $<$<CONFIG:Release>:-O3>
)

# Link options
target_link_options(output PRIVATE
    $<$<CONFIG:Debug>:>
    $<$<CONFIG:Release>:>
)

