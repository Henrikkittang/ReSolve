#pragma once

#include "scene.hpp"



class SceneClearColor : public Scene 
{
public:
    ~SceneClearColor();
    void init() override;
    void onUpdate( const RenderWindow& wn) override;
    void onRender( const RenderWindow& wn ) override;
    void onImGuiRender() override;
private:
    float m_clearColor[4];
};

