#include"sceneMaze.hpp"


#include<imgui/imgui.h>
#include<fmt/core.h>


#include"core/appContext.hpp"
#include"core/camera.hpp"
#include"util/random.hpp"
#include"util/log.hpp"



void SceneMaze::onCreate() 
{
    m_scl = 2;

    m_width  = ctx.window.getSize().x / m_scl;
    m_height = ctx.window.getSize().y / m_scl;

    Camera camera{(float)ctx.window.getSize().x, (float)ctx.window.getSize().y};

    ctx.assets.load("./assets/shaders/maze.shader", m_shaderHandle);
    Ref<Shader> shader = ctx.assets.get<Shader>(m_shaderHandle);
    shader->bind();
    shader->setUniformMat4f("uMVP", camera.getMVP());

    VertexLayout layout;
    layout.push<float>(2); // Position vec2
    layout.push<float>(4); // Color vec4

    m_renderable = Renderable{nullptr, 0, (uint32_t)m_width * m_height * layout.getStride(), layout.getStride(), PrimitiveType::QUAD, GL_DYNAMIC_DRAW};
    m_renderable.setVertexLayout(layout);

    m_mazeData = std::vector<int>( m_width*m_height, 1 );

    glm::ivec2 position = { Random::getInt(0, m_width), Random::getInt(0, m_height) };
    while( position.x % 2 == 0 || position.y % 2 == 0 )
        position = { Random::getInt(0, m_width), Random::getInt(0, m_height) };
    m_open.push( position );
    
    m_lastQuadSize = m_quads.size();
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

    // std::vector<Vertex> vertecies;
    // vertecies.reserve(m_quads.size()*4);
    // for(auto quad : m_quads)
    // {
    //     for(int i = 0; i < 8; i += 2)
    //     {
    //         vertecies.emplace_back( glm::vec3{quad.p[i], quad.p[i+1], 0}, glm::vec4{1.0, 0.0, 0.0, 1.0}, glm::vec2{0.0, 0.0} );
    //     }
    // }
    // m_renderable.update(vertecies.data(), vertecies.size()); // 4 vertices per quad
    // return;

    std::vector<MazeVertex> newVertecies;
    while( m_lastQuadSize < m_quads.size() )
    {
        Quad quad = m_quads[ m_lastQuadSize ];
        for(int i = 0; i < 8; i += 2)
        {
            newVertecies.emplace_back( glm::vec2{quad.p[i], quad.p[i+1]}, glm::vec4{1.0, (m_lastQuadSize % 255) / 255.0, 0.0, 1.0} );
        }
        m_lastQuadSize++;
    }    
    m_renderable.updateAppend(newVertecies.data(), (uint32_t)newVertecies.size()); 

}


void SceneMaze::onRender() 
{
   
    Ref<Shader> shader = ctx.assets.get<Shader>(m_shaderHandle);
    ctx.window.draw(m_renderable, shader);

    
}


void SceneMaze::onImGuiRender() 
{
    ImGui::Text("Quads: %zu",  m_quads.size());
}



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
    ctx.window.clear();
    m_renderable.bind();
}


void SceneMaze::onDeactivate()
{
    m_renderable.unbind();
}  
