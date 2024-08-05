#include"sceneClearColor.hpp"

#include<imgui/imgui.h>

#include"util.hpp"
#include"application.hpp"
#include"sceneFractal.hpp"

SceneClearColor::SceneClearColor() 
    :m_clearColor{0.2f, 0.3f, 0.8f, 1.0f}
{}

SceneClearColor::~SceneClearColor() 
{}

void SceneClearColor::onUpdate( GLFWwindow* wn ) 
{
    GLCall( glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]) );
    GLCall( glClear(GL_COLOR_BUFFER_BIT) );

}
void SceneClearColor::onRender( GLFWwindow* wn ) 
{}

void SceneClearColor::onImGuiRender() 
{
    if( ImGui::Button("Change scene") )
    {
        Application::emplaceScene( new SceneFractal );
    }

    ImGui::ColorEdit4("Clear color", m_clearColor);
}


