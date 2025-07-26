#pragma once
#include<vector>
#include<stack>

#include<glm/glm.hpp>


#include"core/scene.hpp"
#include"core/camera.hpp"
#include"core/asset.hpp"
#include"graphics/renderable.hpp"
#include"graphics/shader.hpp"

struct Quad
{
    float p[8];

    Quad(float x, float y, float width, float height)
    {
        p[0] = x;          p[1] = y;
        p[2] = x + width;  p[3] = y;
        p[4] = x + width;  p[5] = y + height;
        p[6] = x;          p[7] = y + height;
    }
};

class SceneMaze : public Scene
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
    void connect_nodes(glm::ivec2 cur_pos, glm::ivec2 node_pos);
    std::vector<glm::ivec2> find_frontiers(glm::ivec2 pos, int state);

private:
    uint32_t               m_width, m_height, m_scl;
    std::vector<int>       m_mazeData;
    std::stack<glm::ivec2> m_open;
    AssetHandle         m_shaderHandle;
    Renderable             m_renderable;
    std::vector<Quad>      m_quads;
    uint32_t               m_lastQuadSize;

    Camera m_camera;
};
