#pragma once    
#include<string>
#include<vector>
#include<stack>
#include<memory>

#include<GL/glew.h>

#include"scene.hpp"

// struct ApplicationSettings
// {
//     uint32_t screenWidth;
//     uint32_t screenHeight;
//     std::string screenTitle;
// };

class Application
{
public:
    Application();
    ~Application();

    void ImGuiInit();

    void run();

    static void emplaceScene(Scene* scene);
    static void pushScene(std::unique_ptr<Scene>&& scene);


private:

    GLFWwindow* m_window;
    bool        m_isImguiActive;

    inline static std::stack<std::unique_ptr<Scene>> s_scenes;
};
