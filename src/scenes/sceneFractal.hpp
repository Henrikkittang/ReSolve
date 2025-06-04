#pragma once

#include"decapricated/vertexArray.hpp"
#include"decapricated/vertexBuffer.hpp"

#include"decapricated/indexBuffer.hpp"
#include"graphics/shader.hpp"

#include"core/scene.hpp"
#include"core/camera.hpp"
#include"core/resource.hpp"


class SceneFractal : public Scene 
{
public:

    using Scene::Scene;

    void onCreate() override;
    void onUpdate(  ) override;
    void onRender(  ) override;
    void onImGuiRender() override;


private:
    float        uZoom;                   
    glm::vec2    uPan;               
    int          maxIterations;
    
    ResourceHandle m_shaderHandle;
    VertexArray    m_va;
    IndexBuffer    m_ib;

    Camera m_camera;
};

