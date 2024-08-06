#pragma once    
#include<string>
#include<vector>
#include<stack>

#include<GL/glew.h>

#include"scene.hpp"
#include"renderWindow.hpp"


class Application
{
public:
    Application(uint32_t screenWidth, uint32_t screenHeight, const std::string& title);
    ~Application();

    void ImGuiInit();
    void run();
    static void addScene(Scene* scene);

private:
    void runScene(Scene* scene);

private:

    RenderWindow m_window;
    bool         m_isImguiActive;

    inline static std::stack<Scene*> s_scenes;
};
