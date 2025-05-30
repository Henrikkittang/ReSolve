#pragma once
#include<vector>
#include<stack>

#include<glm/glm.hpp>

#include"renderable.hpp"
#include"scene.hpp"
#include"camera.hpp"

struct Quad
{
	float p[8];

	Quad(float x, float y, float width, float height)
		: p(x, y, x+width, y, x+width, y+height, x, y+height)
	{}
};


class SceneMaze : public Scene
{
public:

using Scene::Scene; // Inherit constructors


    void onCreate() override;
    void onUpdate( const RenderWindow& wn) override;
    void onRender( const RenderWindow& wn) override;
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
    Shader                 m_shader;
    Renderable             m_renderable;
    std::vector<Quad>      m_quads;

    Camera m_camera;
};
