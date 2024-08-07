#pragma once
#include"renderWindow.hpp"
#include"camera.hpp"

class Scene
{
public:

    Scene() {};
    virtual ~Scene() {};
    virtual void init() = 0;
    virtual void onUpdate( const RenderWindow& wn ) = 0;
    virtual void onRender( const RenderWindow& wn ) = 0;
    virtual void onImGuiRender() {};
protected:
    Camera m_camera;
};
