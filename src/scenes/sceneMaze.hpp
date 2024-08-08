#pragma once
#include<vector>
#include<stack>

#include<glm/glm.hpp>

#include"..\core\scene.hpp"

class SceneMaze : public Scene
{
public:
    SceneMaze() { init(); }

    ~SceneMaze();
    void init() override;
    void onUpdate( const RenderWindow& wn) override;
    void onRender( const RenderWindow& wn) override;
    void onImGuiRender() override;

private:
    void connect_nodes(glm::ivec2 cur_pos, glm::ivec2 node_pos);
    std::vector<glm::ivec2> find_frontiers(glm::ivec2 pos, int state);

private:
    uint32_t               m_width, m_height, m_scl;
    std::vector<int>       m_mazeData;
    std::stack<glm::ivec2> m_open;
    Shader                 m_shader;

};
