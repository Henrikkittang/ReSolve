#pragma once
#include<GL/glew.h>

#include<GLFW/glfw3.h>

class Scene
{
public:

    Scene() {};
    virtual ~Scene() {};
    virtual void onUpdate( GLFWwindow* wn ) = 0;
    virtual void onRender( GLFWwindow* wn ) = 0;
    virtual void onImGuiRender() {};
};
