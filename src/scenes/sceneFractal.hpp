#pragma once


#include"core/scene.hpp"
#include"core/camera.hpp"
#include"core/asset.hpp"

#include"graphics/renderable.hpp"
#include"graphics/shader.hpp"

#include"decapricated/vertexArray.hpp"
#include"decapricated/vertexBuffer.hpp"
#include"decapricated/indexBuffer.hpp"


class SceneFractal : public Scene 
{
public:

    using Scene::Scene;

    void onCreate() override;
    void onUpdate(  ) override;
    void onRender(  ) override;
    void onImGuiRender() override;

    void onActivate()   override;
    void onDeactivate() override;

private:
    float        uZoom;                   
    glm::vec2    uPan;               
    int          maxIterations;
    
    AssetHandle m_shaderHandle;
    Renderable  m_renderTarget;

    VertexArray    m_va;
    IndexBuffer    m_ib;
};

