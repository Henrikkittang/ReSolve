#include"sceneClearColor.hpp"

#include<imgui/imgui.h>

#include"util.hpp"
#include"application.hpp"
#include"event.hpp"
#include"sceneFractal.hpp"



SceneClearColor::~SceneClearColor() 
{}

void SceneClearColor::init()
{
    m_clearColor[0] = 0.2f;
    m_clearColor[1] = 0.3f;
    m_clearColor[2] = 0.8f;
    m_clearColor[3] = 1.0f;
}

void SceneClearColor::onUpdate( const RenderWindow& ) 
{
    GLCall( glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]) );
    GLCall( glClear(GL_COLOR_BUFFER_BIT) );

}
void SceneClearColor::onRender( const RenderWindow& ) 
{}

void SceneClearColor::onImGuiRender() 
{
    

    ImGui::ColorEdit4("Clear color", m_clearColor);
}


