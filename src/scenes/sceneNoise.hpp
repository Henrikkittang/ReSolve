#pragma once

#include"scene.hpp"
#include"texture.hpp"
#include"random.hpp"
#include"camera.hpp"

#pragma once

#include"scene.hpp"


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
    void onCreate() override;

    void onUpdate( const RenderWindow& wn ) override;
    void onRender( const RenderWindow& wn ) override;
    void onImGuiRender() override;

    void onActivate() override;
    void onDeactivate() override;

private:
    Texture m_texture;
    Shader  m_shader;
    Camera  m_camera;

    NoiseSettnings m_noiseSettnigns;
};