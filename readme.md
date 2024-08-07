# How to run and build project
This project uses cmake as its configuration system. This means that you need both cmake and a build system installed on your computer. Some common build systems include `make`, `ninja`  and `msvc`. The project should support MinGW, Clang and MSVC, with emphasis on should. 

Two commands are required to build the project
```
cmake -B build/release -DCMAKE_BUILD_TYPE=Release
cmake --build build/release --config Release -j9
```

This project contains a .vscode folder, which means that the easiest way to build and modify the project is from the vscode editor. Here you can bring up your task prompt to initilize, build and run for different modes (debug and release). The build system used for devolopment is make and the tasks need minor refactoring to work with other systems. 

# To do list

## Build system
- Add initlizer tasks in vscode for different build systems (vscode specific)
- Maybe have som sort of system where its easy to switch compilers (vscode specific)
- The cmake should idealy not contain compiler paths
- Have cmake specify parallel building, like the -j<n> flag

## Project
- Access to resources should happen via a resources manager with proper path access
- Build in functionality for batch rendering
- Add a system for mvp matrecies, define stuff by default in pixel space
- Add glfw events to the event system via callback functions
- I maybe want the applicaton class to own the raw window pointer and have a renderwindow wrapped around it and sent to the scenes without ever modifying it
- Have a diffrent scene system based on caching and maps rather than a stack
- Be able to send data to scenes
- Send data through events?