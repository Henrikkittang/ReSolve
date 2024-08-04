#include<iostream>

#include"application.hpp"
#include"sceneFractal.hpp"

int main()
{    
    Application app;
    app.ImGuiInit();

    app.emplaceScene( new SceneFractal );
    app.run();
    
    app.ImGuiShutdown();

    return 0;
}