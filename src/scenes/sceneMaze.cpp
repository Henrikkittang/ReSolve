#include"sceneMaze.hpp"

#include <glm/gtc/matrix_transform.hpp>


Maze::~Maze()
{}

void Maze::init() 
{
    m_width  = 960;
    m_height = 540;

    m_mazeData = std::vector<int>( m_width*m_height, 0 );

    m_open.emplace( rand_range(0, m_width), rand_range(0, m_height) );

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
    // Model matrix: Identity matrix (no transformation)
    glm::mat4 model = glm::mat4(1.0f);

    // View matrix: Camera at (0, 0, 3), looking at the origin, up is positive Y axis
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f), // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // Look at point
        glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector
    );

    // Projection matrix: Perspective projection
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), // Field of view in radians
        800.0f / 600.0f,     // Aspect ratio
        0.1f,                // Near clipping plane
        100.0f               // Far clipping plane
    );

    // Combine the matrices to create the MVP matrix
    glm::mat4 mvp = projection * view * model;


    std::vector<int> vertecies;
    for(size_t i = 0; i < m_mazeData.size(); i++)
    {
        glm::ivec2 positon = { i % m_width, i / m_width };

        if( m_mazeData[positon.y*m_width + positon.x] )
            continue;

        vertecies.push_back( positon.x );
        vertecies.push_back( positon.y );

        vertecies.push_back( positon.x + 1);
        vertecies.push_back( positon.y );

        vertecies.push_back( positon.x + 1 );
        vertecies.push_back( positon.y + 1 );

        vertecies.push_back( positon.x );
        vertecies.push_back( positon.y  + 1);
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

int Maze::rand_range(int start, int end)
{
    return (std::rand() % (int)(end - start)) + start;
}

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

