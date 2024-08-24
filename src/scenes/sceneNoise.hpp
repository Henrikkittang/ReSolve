#pragma once

#include"scene.hpp"
#include"texture.hpp"
#include"random.hpp"


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
    void init() override;

    void onUpdate( const RenderWindow& wn ) override;
    void onRender( const RenderWindow& wn ) override;
    void onImGuiRender() override;

    void onActive() override;
    void onDeactivate() override;

private:
    Texture m_texture;
    Shader  m_shader;
    Camera  m_camera;

    NoiseSettnings m_noiseSettnigns;
};