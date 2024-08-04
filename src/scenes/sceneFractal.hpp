#pragma once

#include "test.hpp"

#include"vertexArray.hpp"
#include"vertexBuffer.hpp"
#include"indexBuffer.hpp"
#include"shader.hpp"

#include"scene.hpp"

class SceneFractal : public Scene 
{
public:
    SceneFractal();
    ~SceneFractal();
    void onUpdate( GLFWwindow* wn ) override;
    void onRender( GLFWwindow* wn ) override;
    void onImGuiRender() override;


private:
    float        uZoom;                   
    glm::vec2    uPan;               
    int          maxIterations;
    
    Shader       m_shader;
    VertexArray  m_va;
    IndexBuffer  m_ib;

    
};

