#pragma once

#include"core/scene.hpp"
#include"core/camera.hpp"
#include"core/asset.hpp"
#include"graphics/texture.hpp"
#include"graphics/shader.hpp"
#include"util/random.hpp"


struct NoiseSettnings
{
    int    depth = 7;
    float amp   = 0.5;
    float freq  = 10.0;
    bool   redraw = false;
};

class SceneNoise : public Scene
{
public:
    using Scene::Scene;


    void onCreate() override;
    void onUpdate() override;
    void onRender() override;
    void onImGuiRender() override;

    void onActivate() override;
    void onDeactivate() override;

private:
    Texture m_texture;
    // Shader  m_shader;
    Camera  m_camera;
    AssetHandle m_shaderHandle;

    NoiseSettnings m_noiseSettnigns;
};