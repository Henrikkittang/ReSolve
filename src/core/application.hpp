#pragma once    
#include<string>
#include<vector>
#include<stack>

#include<GL/glew.h>

#include"scene.hpp"
#include"renderWindow.hpp"
#include"sceneManager.hpp"

class Application
{
public:
    Application(uint32_t screenWidth, uint32_t screenHeight, const std::string& title);
    ~Application();

    void ImGuiInit();
    void run();
    
public:
    inline static SceneManager sceneManager;

private:

private:

    RenderWindow m_window;
    bool         m_isImguiActive;

};
