# How to run and build project
This project uses cmake as its configuration system. The project should support GCC, Clang and MSVC on both windows and linux, with emphasis on should. 

Commands for building project with GCC/Clang
```
mkdir build/release
cmake -B build/release -DCMAKE_BUILD_TYPE=Release
cmake --build build/release --config Release -j8
```
The binary will be located in `build/release/bin/` 

Commands for building project with MSVC
```
mkdir build/
cmake -B build/ 
cmake --build build/ --config Release -j8
```

This project contains a .vscode folder, which means that the easiest way to build and modify the project is from the vscode editor. Here you can bring up your task prompt to initilize, build and run for different modes (debug and release). The build system used for devolopment is make and the tasks need minor refactoring to work with other systems. 

# To do list

## General
- Add glfw events to the event system via callback functions
- Be able to send data to scenes, send data through events?
- Remove need for appContext.hpp to be included in cpp whenever its used
- Make a quick and simple file interface for standardized paths
- The asset manager is kinda overkill, as my projects rearly uses that many assets or has any need for dynamic loading, unloading or caching. 
- There realy is not camera system in place, only a util for calculating the mvp matrix, so move this over to a util class

## Build system
- Use cmake fetch content in favor of git modules
- Make better cross platform vscode tasks
- Making sure paths for assets are correct
- ? Add a production build mode (with copying of assets, bundling libraries, etc)
- ? Have som sort of system where its easy to switch compilers (vscode specific)

## Logger
- Switch to spdlogger
- Swap out fmt in favor of C++23 functionality
- Integrate OpenGL errors better with the logger

## Renderwindow
- Resizing/viewport management
- ? I maybe want the applicaton class to own the raw window pointer and have a renderwindow wrapped around it and sent to the scenes without ever modifying it

## Renderable
- Fix vertex atrribute array issue, something like the old vertexbuffer solution
