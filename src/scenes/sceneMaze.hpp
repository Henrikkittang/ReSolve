#pragma once
#include<vector>
#include<stack>

#include<glm/glm.hpp>


#include"scene.hpp"


class Maze : public Scene
{
public:
    ~Maze();
    void init() override;
    void onUpdate( const RenderWindow& wn) override;
    void onRender( const RenderWindow& wn) override;
    void onImGuiRender() override;

private:
    int rand_range(int start, int end);
    void connect_nodes(glm::ivec2 cur_pos, glm::ivec2 node_pos);
    std::vector<glm::ivec2> find_frontiers(glm::ivec2 pos, int state);

private:
    uint32_t               m_width, m_height;
    std::vector<int>       m_mazeData;
    std::stack<glm::ivec2> m_open;
    Shader                 m_shader;

};
