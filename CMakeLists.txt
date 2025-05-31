cmake_minimum_required(VERSION 3.14)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory (for non-MSVC)
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

# Add GLAD
add_subdirectory(vendor/glad)

# Add other includes and sources
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE VENDOR  "vendor/*.cpp")

add_executable(output ${SOURCES} ${VENDOR})

# GLFW libs manually defined
target_link_libraries(output
    glad
    glfw3
    OpenGL::GL
    gdi32
)

target_include_directories(output PRIVATE
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/vendor/
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

# Link options (can be omitted unless needed)
target_link_options(output PRIVATE
    $<$<CONFIG:Debug>:>
    $<$<CONFIG:Release>:>
)

# Copy DLLs after build
file(GLOB DLL_FILES ${LIBS}/*.dll)
foreach(DLL ${DLL_FILES})
    get_filename_component(DLL_NAME ${DLL} NAME)
    add_custom_command(TARGET output POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${DLL}" "$<TARGET_FILE_DIR:output>/${DLL_NAME}"
        COMMENT "Copying ${DLL_NAME} to the target directory"
    )
endforeach()
