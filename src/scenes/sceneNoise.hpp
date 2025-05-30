#pragma once

#include"scene.hpp"
#include"texture.hpp"
#include"random.hpp"
#include"camera.hpp"
#include"shader.hpp"


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
    Shader  m_shader;
    Camera  m_camera;

    NoiseSettnings m_noiseSettnigns;
};