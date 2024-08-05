#include<iostream>

#include"application.hpp"
#include"sceneFractal.hpp"
#include"sceneClearColor.hpp"

int main()
{    
    Application app;
    app.ImGuiInit();

    app.emplaceScene( new SceneClearColor );
    app.run();    
}