#include"sceneMaze.hpp"

#include<iostream>

#include"util/random.hpp"
#include"util/util.hpp"


void SceneMaze::onCreate() 
{
    m_camera = Camera{960.0, 540.0};

    m_scl = 8;

    m_width  = 960 / m_scl;
    m_height = 540 / m_scl;

    m_renderable = Renderable{nullptr, (uint32_t)(m_width * m_height * 8 * sizeof(float)), 2, GL_DYNAMIC_DRAW};
    // m_renderable = Renderable{nullptr, 2 * 8 * sizeof(float), 2, GL_DYNAMIC_DRAW};

    m_mazeData = std::vector<int>( m_width*m_height, 1 );

    glm::ivec2 position = { Random::getInt(0, m_width), Random::getInt(0, m_height) };
    while( position.x % 2 == 0 || position.y % 2 == 0 )
        position = { Random::getInt(0, m_width), Random::getInt(0, m_height) };
    m_open.push( position );
    
    m_shader = Shader{"./resources/shaders/red.shader"};
    auto mvp = m_camera.getMVP();

    m_shader.bind();
    m_shader.setUniformMat4f("uMVP", mvp);
}

void SceneMaze::onUpdate() 
{
    if( m_open.empty() )
        return;

    glm::ivec2 currentposition = m_open.top();
    m_mazeData[ currentposition.y*m_width + currentposition.x ] = 0;

    auto frontiers = find_frontiers(currentposition, 1);
   
    if(!frontiers.empty())
    {
        size_t idx = Random::getInt(0, frontiers.size());
        glm::ivec2 newFrontier = frontiers[ idx ];

        connect_nodes(currentposition, newFrontier);
        
        m_mazeData[ newFrontier.y*m_width + newFrontier.x ] = 0;
        m_open.push(newFrontier);
    }else{
        m_open.pop();
    }
}


void SceneMaze::onRender() 
{
    // std::vector<Quad> quads;
    // quads.reserve( m_mazeData.size() );
    // for(size_t i = 0; i < m_mazeData.size(); i++)
    // {
    //     glm::vec2 position = { i % m_width, i / m_width };
// 
    //     if( m_mazeData[position.y*m_width + position.x] == 1 )
    //         continue;
// 
    //     quads.emplace_back( position.x*m_scl, position.y*m_scl, m_scl, m_scl );
    // }
    

    float* data = (float*)m_quads.data();
    m_renderable.update(data, (uint32_t)m_quads.size()*8*sizeof(float));

    GLCall( glDrawArrays(GL_QUADS, 0, m_renderable.size()*8*sizeof(float)) );    

}


void SceneMaze::onImGuiRender() {}


void SceneMaze::connect_nodes(glm::ivec2 curPos, glm::ivec2 nodePos)
{

    m_quads.emplace_back( nodePos.x*m_scl, nodePos.y*m_scl, m_scl, m_scl );    

    if(curPos.x > nodePos.x)
    {
        m_mazeData[ curPos.y*m_width + (curPos.x-1) ] = 0;
        m_quads.emplace_back( (nodePos.x-1)*m_scl, nodePos.y*m_scl, m_scl, m_scl );    
    }

    else if(curPos.x < nodePos.x)
    {
        m_mazeData[ curPos.y*m_width + (curPos.x+1) ] = 0;
        m_quads.emplace_back( (nodePos.x+1)*m_scl, nodePos.y*m_scl, m_scl, m_scl );    
    }
    
    else if(curPos.y > nodePos.y)
    {
        m_mazeData[ (curPos.y-1)*m_width + curPos.x ] = 0;
        m_quads.emplace_back( nodePos.x*m_scl, (nodePos.y-1)*m_scl, m_scl, m_scl );    
    }

    else if(curPos.y < nodePos.y)
    {
        m_mazeData[ (curPos.y+1)*m_width + curPos.x ] = 0;
        m_quads.emplace_back( nodePos.x*m_scl, (nodePos.y+1)*m_scl, m_scl, m_scl );    
    }
}

std::vector<glm::ivec2> SceneMaze::find_frontiers(glm::ivec2 pos, int state)
{
    std::vector<glm::ivec2> frontiers;
    frontiers.reserve(4);

    if( pos.x - 2 >= 0 && m_mazeData[ pos.y*m_width + (pos.x - 2) ] )
        frontiers.emplace_back(pos.x-2, pos.y);

    if( pos.x + 2 < m_width && m_mazeData[ pos.y*m_width + (pos.x + 2) ] )
        frontiers.emplace_back(pos.x+2, pos.y);

    if( pos.y - 2 >= 0 && m_mazeData[ (pos.y-2)*m_width + pos.x ] )
        frontiers.emplace_back(pos.x, pos.y-2);

    if( pos.y + 2 < m_height && m_mazeData[ (pos.y+2)*m_width + pos.x ] )
        frontiers.emplace_back(pos.x, pos.y+2);


    return frontiers;
}



void SceneMaze::onActivate()
{
    m_renderable.bind();
    m_shader.bind();
}


void SceneMaze::onDeactivate()
{
    m_renderable.unbind();
    m_shader.unbind();
}  
