#include"sceneMaze.hpp"

#include<iostream>

#include <glm/gtc/matrix_transform.hpp>

#include"random.hpp"

Maze::~Maze()
{}

void Maze::init() 
{

	srand((int)time(0));

    m_scl = 5;

    m_width  = 960 / m_scl;
    m_height = 540 / m_scl;


    m_mazeData = std::vector<int>( m_width*m_height, 1 );

    glm::ivec2 position = { Random::getInt(0, m_width), Random::getInt(0, m_height) };
    while( position.x % 2 == 0 || position.y % 2 == 0 )
        position = { Random::getInt(0, m_width), Random::getInt(0, m_height) };
    m_open.push( position );
    
    m_shader = Shader{"./resources/shaders/red.shader"};

}

void Maze::onUpdate( const RenderWindow& wn ) 
{
    if( m_open.empty() )
        return;

    glm::ivec2 currentPositon = m_open.top();
    m_mazeData[ currentPositon.y*m_width + currentPositon.x ] = 0;

    auto frontiers = find_frontiers(currentPositon, 1);

   
    if(!frontiers.empty())
    {
        size_t idx = rand_range(0, frontiers.size());
        glm::ivec2 newFrontier = frontiers[ idx ];

        connect_nodes(currentPositon, newFrontier);
        
        m_mazeData[ newFrontier.y*m_width + newFrontier.x ] = 0;
        m_open.push(newFrontier);
    }else{
        m_open.pop();
    }
}

void Maze::onRender( const RenderWindow& wn) 
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    glm::mat4 ident = glm::mat4(1.0f);
    glm::vec3 trvec = glm::vec3(0, 0, 0);
    glm::mat4 view = glm::translate(ident, trvec);
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 mvp = proj * view * model;

    m_shader.bind();
    m_shader.setUniformMat4f("uMVP", mvp);

    std::vector<float> vertecies;
    for(size_t i = 0; i < m_mazeData.size(); i++)
    {
        glm::ivec2 positon = { i % m_width, i / m_width };

        if( m_mazeData[positon.y*m_width + positon.x] == 0 )
            continue;

        vertecies.push_back( positon.x*m_scl );
        vertecies.push_back( positon.y*m_scl );

        vertecies.push_back( positon.x*m_scl + m_scl);
        vertecies.push_back( positon.y*m_scl );

        vertecies.push_back( positon.x*m_scl + m_scl );
        vertecies.push_back( positon.y*m_scl + m_scl );

        vertecies.push_back( positon.x*m_scl );
        vertecies.push_back( positon.y*m_scl  + m_scl);
    }
    
    size_t vertex_count = vertecies.size() / 2; // 2 coordinates per vertex
    size_t quad_count = vertex_count / 4; // 4 vertices per quad
    size_t count = quad_count * 6; // 6 indices per quad

    std::vector<uint32_t> indices(count);

    for(size_t i = 0, vertex_index = 0; i < count; i += 6, vertex_index += 4)
    {
        indices[i + 0] = vertex_index + 0;
        indices[i + 1] = vertex_index + 1;
        indices[i + 2] = vertex_index + 2;
        indices[i + 3] = vertex_index + 2;
        indices[i + 4] = vertex_index + 3;
        indices[i + 5] = vertex_index + 0;
    }
    IndexBuffer ib = { indices.data(), static_cast<uint32_t>(count) };

    VertexBuffer vb = {vertecies.data(), static_cast<uint32_t>(vertecies.size() * sizeof(float))};
    VertexBufferLayout layout; 
    layout.push<float>(2);
    
    VertexArray va;
    va.addBuffer(vb, layout);

    wn.draw(va, ib, m_shader);
}


void Maze::onImGuiRender() {}


void Maze::connect_nodes(glm::ivec2 curPos, glm::ivec2 nodePos)
{
    if(curPos.x > nodePos.x)
        m_mazeData[ curPos.y*m_width + (curPos.x-1) ] = 0;

    else if(curPos.x < nodePos.x)
        m_mazeData[ curPos.y*m_width + (curPos.x+1) ] = 0;

    else if(curPos.y > nodePos.y)
        m_mazeData[ (curPos.y-1)*m_width + curPos.x ] = 0;

    else if(curPos.y < nodePos.y)
        m_mazeData[ (curPos.y+1)*m_width + curPos.x ] = 0;
}

std::vector<glm::ivec2> Maze::find_frontiers(glm::ivec2 pos, int state)
{
    std::vector<glm::ivec2> frontiers;
    frontiers.reserve(4);

    if( pos.x - 2 >= 0 && m_mazeData[ pos.y*m_width + (pos.x - 2) ] )
        frontiers.emplace_back(pos.x-2, pos.y);

    if( pos.x + 2 >= 0 && m_mazeData[ pos.y*m_width + (pos.x + 2) ] )
        frontiers.emplace_back(pos.x+2, pos.y);

    if( pos.y - 2 >= 0 && m_mazeData[ (pos.y-2)*m_width + pos.x ] )
        frontiers.emplace_back(pos.x, pos.y-2);

    if( pos.y + 2 >= 0 && m_mazeData[ (pos.y+2)*m_width + pos.x ] )
        frontiers.emplace_back(pos.x, pos.y+2);


    return frontiers;
}

