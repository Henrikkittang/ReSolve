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
    // virtual void destroy() {}

    virtual void onUpdate( const RenderWindow& wn ) { assert("OnUpdate not implemented");  };
    virtual void onRender( const RenderWindow& wn ) { assert("OnRender not implemented");  };
    virtual void onImGuiRender() {};

    virtual void onActive() {}
    virtual void onDeactivate() {}

protected:
    Camera m_camera;
};
