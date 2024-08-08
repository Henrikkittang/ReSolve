#include<iostream>

#include"application.hpp"
#include"sceneFractal.hpp"
#include"sceneClearColor.hpp"
#include"sceneMaze.hpp"


int main()
{    
    Application app{960, 540, "Hello world"};
    app.ImGuiInit();

    app.s_sceneManager.addScene<SceneClearColor>("Color");
    app.s_sceneManager.addScene<SceneMaze>("Maze");
    app.s_sceneManager.addScene<SceneFractal>("Fractal");

    app.run();    
}