#pragma once

#include<iostream>
#include "core/scene.hpp"



class SceneClearColor : public Scene 
{
public:
    
    using Scene::Scene;


    void onCreate() override;
    void onUpdate() override;
    void onRender() override;
    void onImGuiRender() override;
private:
    float m_clearColor[4];
};

