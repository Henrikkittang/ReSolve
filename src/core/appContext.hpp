#pragma once
#include"graphics/renderWindow.hpp"
#include"core/sceneManager.hpp"
#include"core/resourceManager.hpp"

struct AppContext
{
    RenderWindow&    window;
    SceneManager&    sceneManager;
    ResourceManager& resourceManager;
};