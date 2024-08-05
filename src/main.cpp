#include<iostream>

#include"application.hpp"
#include"sceneFractal.hpp"

int main()
{    
    Application app;
    app.ImGuiInit();

    // app.emplaceScene( new SceneFractal );
    auto ptr = std::make_unique<SceneFractal>();
    app.pushScene( std::move(ptr) );
    app.run();    
}