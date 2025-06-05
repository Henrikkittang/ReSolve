#pragma once
#include"graphics/renderWindow.hpp"
#include"core/sceneManager.hpp"
#include"core/assetManager.hpp"

struct AppContext
{
    RenderWindow&    window;
    SceneManager&    sceneManager;
    AssetManager&    assetManager;
};