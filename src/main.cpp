#include<iostream>

#include"application.hpp"
#include"sceneFractal.hpp"
#include"sceneClearColor.hpp"
#include"sceneMaze.hpp"

int main()
{    
    Application app{960, 540, "Hello world"};
    app.ImGuiInit();

    app.addScene(new Maze);
    app.run();    
}