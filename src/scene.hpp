#pragma once
#include<GL/glew.h>

#include<GLFW/glfw3.h>

class Scene
{
public:
    virtual void onUpdate( GLFWwindow* wn ) = 0;
    virtual void onRender( GLFWwindow* wn ) = 0;
    virtual void onImGuiRender();

    void run(GLFWwindow* wn);
};
