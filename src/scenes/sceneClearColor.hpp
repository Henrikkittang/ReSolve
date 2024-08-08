#pragma once

#include<iostream>
#include "..\core\scene.hpp"



class SceneClearColor : public Scene 
{
public:
    
    inline SceneClearColor() { init(); }
    ~SceneClearColor();
    void init() override;
    void onUpdate( const RenderWindow& wn) override;
    void onRender( const RenderWindow& wn ) override;
    void onImGuiRender() override;
private:
    float m_clearColor[4];
};

