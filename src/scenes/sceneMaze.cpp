#include"sceneMaze.hpp"

#include<iostream>

#include"random.hpp"

struct Quad
{
	float p[8];

	Quad(float x, float y, float width, float height)
		: p(x, y, x+width, y, x+width, y+height, x, y+height)
	{}
};

SceneMaze::~SceneMaze()
{}


void SceneMaze::init() 
{
    m_camera = Camera{960.0, 540.0};
    m_renderable = Renderable{nullptr, 960 * 540 * 4, 2};

    m_scl = 2;

    m_width  = 960 / m_scl;
    m_height = 540 / m_scl;


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

void SceneMaze::onUpdate( const RenderWindow& wn ) 
{
    if( m_open.empty() )
        return;

    glm::ivec2 currentPositon = m_open.top();
    m_mazeData[ currentPositon.y*m_width + currentPositon.x ] = 0;

    auto frontiers = find_frontiers(currentPositon, 1);
   
    if(!frontiers.empty())
    {
        size_t idx = Random::getInt(0, frontiers.size());
        glm::ivec2 newFrontier = frontiers[ idx ];

        connect_nodes(currentPositon, newFrontier);
        
        m_mazeData[ newFrontier.y*m_width + newFrontier.x ] = 0;
        m_open.push(newFrontier);
    }else{
        m_open.pop();
    }
}

void SceneMaze::onRender( const RenderWindow& wn) 
{
    
   
    std::vector<Quad> quads;
    quads.reserve( m_mazeData.size() );
    for(size_t i = 0; i < m_mazeData.size(); i++)
    {
        glm::vec2 positon = { i % m_width, i / m_width };

        if( m_mazeData[positon.y*m_width + positon.x] == 1 )
            continue;

        quads.emplace_back( positon.x*m_scl, positon.y*m_scl, m_scl, m_scl );
    }
    float* data = (float*)quads.data();
    
    m_renderable.update(data, (uint32_t)quads.size()*8*sizeof(float));
    wn.draw(m_renderable, m_shader);
    
  
}


void SceneMaze::onImGuiRender() {}


void SceneMaze::connect_nodes(glm::ivec2 curPos, glm::ivec2 nodePos)
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

