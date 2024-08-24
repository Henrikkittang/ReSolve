#pragma once

#include"vertexArray.hpp"
#include"vertexBuffer.hpp"
#include"indexBuffer.hpp"
#include"shader.hpp"

#include"..\core\scene.hpp"

class SceneFractal : public Scene 
{
public:

    ~SceneFractal() override;
    void init() override;
    void onUpdate( const RenderWindow& wn ) override;
    void onRender( const RenderWindow& wn ) override;
    void onImGuiRender() override;


private:
    float        uZoom;                   
    glm::vec2    uPan;               
    int          maxIterations;
    
    Shader       m_shader;
    VertexArray  m_va;
    IndexBuffer  m_ib;

    
};

