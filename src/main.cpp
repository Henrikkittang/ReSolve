#include<iostream>

#include"core/application.hpp"
#include"scenes/sceneFractal.hpp"
#include"scenes/sceneClearColor.hpp"
#include"scenes/sceneMaze.hpp"
#include"scenes/sceneNoise.hpp"

#include"core/resourceManager.hpp"

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

    ResourceManager rm{};

    ResourceHandle shaderHandle;
    ResourceHandle textureHandle;

    

    if(!rm.load("./resources/shaders/basic.shader", shaderHandle));
        std::cout << "Shader not loaded \n";
    
    if(!rm.load("./resources/textures/paint.png", textureHandle));
        std::cout << "Texture not loaded \n";

    Texture* texture = (Texture*)rm.get(textureHandle);

    rm.unload(shaderHandle);

    app.registerScene<SceneClearColor>("Color");
    app.registerScene<SceneNoise>("Noise");
    app.registerScene<SceneMaze>("Maze");
    app.registerScene<SceneFractal>("Fractal");

    app.run();    
}