#include<iostream>

#include"core/application.hpp"
#include"scenes/sceneFractal.hpp"
#include"scenes/sceneClearColor.hpp"
#include"scenes/sceneMaze.hpp"
#include"scenes/sceneNoise.hpp"

#include"util/log.hpp"

int main()
{    
    
    #ifdef _MSC_VER
        std::cout << "Compiled with MSVC\n";
    #elif __clang__
        std::cout << "Compiled with Clang\n";
    #elif __GNUC__
        std::cout << "Compiled with GCC\n";
    #else
        std::cout << "Compiler not detected\n";
    #endif


    #if RS_DEBUG
        std::cout << "Debug mode is active." << std::endl;
    #elif RS_RELEASE
        std::cout << "Release mode is active." << std::endl;
    #else
        std::cout << "No mode is active." << std::endl;
    #endif

    Application app{960, 540, "Hello world"};
    app.ImGuiInit();

    // app.registerScene<SceneClearColor>("Color");
    app.registerScene<SceneNoise>("Noise");
    app.registerScene<SceneMaze>("Maze");
    app.registerScene<SceneFractal>("Fractal");

    app.run();    
}