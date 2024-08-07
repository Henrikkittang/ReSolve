cmake_minimum_required(VERSION 3.10)

# Project name
project(OpenGLProject)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Kinda cursed code for setting the compiler path. Not realy portable
if (NOT MSVC)
    set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/clang)
    set(CMAKE_CXX_COMPILER C:/msys64/mingw64/bin/clang++)
endif()

if(NOT MSVC)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()


find_package(OpenGL REQUIRED)

# Link directories for libraries
if(MSVC)
    set(LIBS ${CMAKE_SOURCE_DIR}/lib/lib-vc2022)
else()
    set(LIBS ${CMAKE_SOURCE_DIR}/lib/lib-mingw-w64)
endif()

link_directories(${LIBS})


# Libraries
set(GLFW_LIBS glfw3 opengl32 gdi32)
set(GLEW_LIBS glew32)
# set(OTHER_LIBS m)

# Get all .cpp files in the source directory
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE TESTS   "src/tests/*.cpp")
file(GLOB_RECURSE SCENES  "src/scenes/*.cpp")
file(GLOB_RECURSE VENDOR  "vendor/*.cpp")

include_directories(
	${CMAKE_SOURCE_DIR}/src/ 
	${CMAKE_SOURCE_DIR}/src/tests/ 
	${CMAKE_SOURCE_DIR}/src/scenes/ 
    ${CMAKE_SOURCE_DIR}/vendor/ 
)

add_executable(output
    ${SOURCES}
    ${TESTS}
    ${VENDOR}
)

target_link_libraries(output
    ${GLFW_LIBS} ${GLEW_LIBS} ${OTHER_LIBS}
)

target_compile_options(output PRIVATE
    $<$<CONFIG:Debug>:  -std=c++17 -Wall -g> 
    $<$<CONFIG:Release>:-std=c++17 -O3>
)


target_link_options(output PRIVATE
    $<$<CONFIG:Debug>: -v> 
    $<$<CONFIG:Release>:>
)


file(GLOB DLL_FILES ${LIBS}/*.dll)
foreach(DLL ${DLL_FILES})
    get_filename_component(DLL_NAME ${DLL} NAME)
    add_custom_command(
        TARGET output POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy 
        "${DLL}" 
        "$<TARGET_FILE_DIR:output>/${DLL_NAME}"
    COMMENT "Copying ${DLL_NAME} to the target directory"
    )
endforeach()


