#include<iostream>

#include"core/application.hpp"
#include"scenes/sceneFractal.hpp"
#include"scenes/sceneClearColor.hpp"
#include"scenes/sceneMaze.hpp"
#include"scenes/sceneNoise.hpp"



int main()
{    
    #if DEBUG
        std::cout << "Debug mode is active." << std::endl;
    #elif RELEASE
        std::cout << "Release mode is active." << std::endl;
    #else
        std::cout << "No mode is active." << std::endl;
    #endif

    Application app{960, 540, "Hello world"};
    app.ImGuiInit();

    // app.sceneManager.addScene<SceneClearColor>("Color");
    // app.sceneManager.addScene<SceneNoise>("Noise");
    app.registerScene<SceneMaze>("Maze");
    // app.sceneManager.addScene<SceneFractal>("Fractal");

    app.run();    
}