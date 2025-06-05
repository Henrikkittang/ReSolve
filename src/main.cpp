#include<iostream>

#include"core/application.hpp"
#include"scenes/sceneFractal.hpp"
#include"scenes/sceneClearColor.hpp"
#include"scenes/sceneMaze.hpp"
#include"scenes/sceneNoise.hpp"

#include"core/assetManager.hpp"

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

    AssetManager rm{};

    AssetHandle texHandle1;
    AssetHandle texHandle2;

    

    if(!rm.load("./assets/textures/paint.png", texHandle1))
        std::cout << "Texture not loaded \n";
    
    if(!rm.load("./assets/textures/paint.png", texHandle2))
        std::cout << "Texture not loaded \n";

    auto tex1 = rm.get<Texture>(texHandle1);
    auto tex2 = rm.get<Texture>(texHandle2);

    std::cout << (rm.isValid(texHandle2) ? "valid" : "not valid") << "\n";

    std::cout << texHandle1.filepath << ", " << texHandle1.id << ", " << (int)texHandle1.type << "\n";
    std::cout << texHandle2.filepath << ", " << texHandle2.id << ", " << (int)texHandle2.type << "\n";

    // app.registerScene<SceneClearColor>("Color");
    app.registerScene<SceneNoise>("Noise");
    app.registerScene<SceneMaze>("Maze");
    app.registerScene<SceneFractal>("Fractal");

    app.run();    
}