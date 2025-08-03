
#include"core/application.hpp"
#include"scenes/sceneFractal.hpp"
#include"scenes/sceneClearColor.hpp"
#include"scenes/sceneMaze.hpp"
#include"scenes/sceneNoise.hpp"

#include <spdlog/spdlog.h>


int main()
{    
    Application app{960, 540, "Hello world"};
    app.ImGuiInit();

    // app.registerScene<SceneClearColor>("Color");
    app.registerScene<SceneNoise>("Noise");
    app.registerScene<SceneMaze>("Maze");
    app.registerScene<SceneFractal>("Fractal");

    app.run();    
}