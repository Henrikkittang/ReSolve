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

## Build system
- Maybe have som sort of system where its easy to switch compilers (vscode specific)
- Have cmake specify parallel building, like the -j<n> flag

## Project
- Add glfw events to the event system via callback functions
- I maybe want the applicaton class to own the raw window pointer and have a renderwindow wrapped around it and sent to the scenes without ever modifying it
- Be able to send data to scenes, send data through events?
- Remove need for appContext.hpp to be included in cpp whenever its used
- Drawing stuff is generally awfull. Its a perfect mix of abstract but not quite and having to be very careful with the ordering of things 
- Make a quick and simple file interface for standardized paths
- Fix bug where everything crashes brutally. Occuers when many quads are rendered in the maze scene.
- Switch to spdlogger
- Swap out fmt in favor of C++23 functionality
- Use cmake fetch content in favor of git modules