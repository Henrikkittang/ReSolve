#pragma once
#include<iostream>
#include<cassert>

#include"renderWindow.hpp"
#include"camera.hpp"

class Scene
{
public:
    virtual ~Scene() {};
    virtual void init() { assert("Init not implemented"); };
    virtual void onUpdate( const RenderWindow& wn ) { assert("OnUpdate not implemented"); exit(0);  };
    virtual void onRender( const RenderWindow& wn ) { assert("OnRender not implemented"); exit(0);  };
    virtual void onImGuiRender() {};
protected:
    Camera m_camera;
};
