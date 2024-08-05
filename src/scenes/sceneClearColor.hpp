#pragma once

#include "scene.hpp"



class SceneClearColor : public Scene 
{
public:
    SceneClearColor(/* args */);
    ~SceneClearColor();
    void onUpdate( GLFWwindow* wn) override;
    void onRender( GLFWwindow* wn ) override;
    void onImGuiRender() override;
private:
    float m_clearColor[4];
};

