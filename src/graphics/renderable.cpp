#include"graphics/renderable.hpp"

#include<vector>

#include"util/util.hpp"

// add defualt values here to index stuff
Renderable::Renderable()
    : m_vertexCount(0), m_indexCount(0), m_floatPerVertex(0), m_type(PrimitiveType::TRIANGLE), m_mode(GL_STATIC_DRAW), m_vertexBufferID(0), m_vertexArrayID(0), m_indexBufferID(0)
{}

Renderable::Renderable(const void* data, uint32_t vertexCount, uint32_t floatPerVertex, PrimitiveType type,  int mode)      
    : m_vertexCount(vertexCount), m_indexCount(0), m_floatPerVertex(floatPerVertex), m_type(type),  m_mode(mode), m_vertexBufferID(0), m_vertexArrayID(0), m_indexBufferID(0)
{
    // Create indices for QUAD
    std::vector<uint32_t> indices = generateIndices(m_type, m_vertexCount / 4);
    m_indexCount = static_cast<uint32_t>(indices.size());

    // Generate and bind VertexArray
    GLCall( glGenVertexArrays(1, &m_vertexArrayID) );   
    GLCall( glBindVertexArray(m_vertexArrayID) );

    // Generate and bind VertexBuffer
    GLCall( glGenBuffers(1, &m_vertexBufferID) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID) );
    GLCall(glBufferData(GL_ARRAY_BUFFER, vertexCount*floatPerVertex*sizeof(float), data, m_mode));

    // Generate and bind IndexBuffer
    GLCall(glGenBuffers(1, &m_indexBufferID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount*sizeof(uint32_t), indices.data(), m_mode));

    // Unbind VertexArray
    GLCall( glEnableVertexAttribArray(0) );
    GLCall( glVertexAttribPointer(0, floatPerVertex, GL_FLOAT, GL_FALSE, floatPerVertex*sizeof(float), (void*)0) );

    // Unbind VertexBuffer
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
    GLCall( glBindVertexArray(0) );
}

Renderable::Renderable(Renderable&& other)
    : m_vertexCount(other.m_vertexCount),  m_indexCount(other.m_indexCount), m_floatPerVertex(other.m_floatPerVertex), m_type(other.m_type), m_mode(other.m_mode),  m_vertexBufferID(other.m_vertexBufferID), m_vertexArrayID(other.m_vertexArrayID)
{
    other.m_vertexBufferID = 0;
    other.m_vertexArrayID  = 0;
    other.m_indexBufferID  = 0;
}


Renderable& Renderable::operator=(Renderable&& other)
{
    if (this != &other) 
    {
        GLCall( glDeleteBuffers(1, &m_vertexBufferID) );
        GLCall( glDeleteVertexArrays(1, &m_vertexArrayID) );

        m_vertexCount    = other.m_vertexCount;
        m_indexCount     = other.m_indexCount;
        m_type           = other.m_type;
        m_mode           = other.m_mode;
        m_floatPerVertex = other.m_floatPerVertex;
        m_vertexBufferID = other.m_vertexBufferID;
        m_vertexArrayID  = other.m_vertexArrayID;

        other.m_vertexBufferID = 0;
        other.m_vertexArrayID  = 0;
        other.m_indexBufferID  = 0;
    }
    return *this;
}



Renderable::~Renderable()
{
    GLCall( glDeleteBuffers(1, &m_vertexBufferID) );
    GLCall( glDeleteVertexArrays(1, &m_vertexArrayID) );
}


void Renderable::bind() const
{
    GLCall( glBindVertexArray(m_vertexArrayID) );
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));  
}


void Renderable::unbind() const
{
    GLCall( glBindVertexArray(0) );
}

uint32_t Renderable::vertexCount() const
{
    return m_vertexCount;
}

uint32_t Renderable::indexCount() const 
{ 
    return m_indexCount; 
}

uint32_t Renderable::floatPerVertex() const 
{ 
    return m_floatPerVertex; 
}

uint32_t Renderable::size() const 
{ 
    return m_vertexCount * m_floatPerVertex * sizeof(float); 
}

void Renderable::update(const void* data, uint32_t vertexCount)
{
    m_vertexCount = vertexCount;

    auto indices = generateIndices(m_type, m_vertexCount / 4);
    uint32_t indexCount = static_cast<uint32_t>(indices.size());
    m_indexCount = indexCount;

    if (m_indexBufferID == 0)
        GLCall(glGenBuffers(1, &m_indexBufferID));

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t), indices.data(), m_mode));

    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID) );    
    
    GLCall( glBufferData(GL_ARRAY_BUFFER, m_vertexCount * m_floatPerVertex * sizeof(float), data, m_mode); );
    // GLCall( glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertexCount * m_floatPerVertex * sizeof(float), data) );
}

/////////////
// Private // 
/////////////


std::vector<uint32_t> Renderable::generateIndices(PrimitiveType type, uint32_t primitiveCount) const
{
    std::vector<uint32_t> indices;
    indices.reserve(primitiveCount * 6); // 2 triangles per quad

    switch (type) 
    {
        case PrimitiveType::POINT: 
        {
            for (uint32_t i = 0; i < primitiveCount; ++i)
                indices.push_back(i); // Each point is a vertex
            break;
        }

        case PrimitiveType::LINE: 
        {
            for (uint32_t i = 0; i < primitiveCount * 2; ++i)
                indices.push_back(i); // 2 indices per line
            break;
        }

        case PrimitiveType::TRIANGLE: 
        {
            for (uint32_t i = 0; i < primitiveCount * 3; ++i)
                indices.push_back(i); // 3 indices per triangle
            break;
        }

        case PrimitiveType::QUAD: 
        {
            for (uint32_t i = 0; i < primitiveCount; ++i) 
            {
                uint32_t base = i * 4;
                indices.push_back(base + 0);
                indices.push_back(base + 1);
                indices.push_back(base + 2);
                indices.push_back(base + 2);
                indices.push_back(base + 3);
                indices.push_back(base + 0);
            }
            break;
        }

        case PrimitiveType::TRIANGLE_STRIP: 
        {
            // Primitive count = number of triangles
            // Vertex count = primitiveCount + 2
            for (uint32_t i = 0; i < primitiveCount + 2; ++i)
                indices.push_back(i);
            break;
        }

        case PrimitiveType::TRIANGLE_FAN: 
        {
            // Fan starts from vertex 0, then connects in a fan
            for (uint32_t i = 1; i <= primitiveCount; ++i) {
                indices.push_back(0);
                indices.push_back(i);
                indices.push_back(i + 1);
            }
            break;
        }

        default:
            break;
    }

    return indices;


}