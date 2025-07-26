#include"graphics/renderable.hpp"

#include<vector>

#include<fmt/core.h>
#include"util/log.hpp"

Renderable::Renderable()
    : m_vertexSize(0), m_floatPerVertex(0), m_type(PrimitiveType::TRIANGLE), 
      m_mode(GL_STATIC_DRAW), m_vertexBufferID(0), m_vertexArrayID(0), m_indexBufferID(0)
{}

Renderable::Renderable(const void* data, uint32_t size, uint32_t vertexCapacity, uint32_t floatPerVertex, PrimitiveType type, int mode)  
    : m_vertexCapacity(vertexCapacity), m_vertexSize(size), m_floatPerVertex(floatPerVertex), m_type(type),  
      m_mode(mode), m_vertexBufferID(0), m_vertexArrayID(0), m_indexBufferID(0)
{
    CHECK_WARN(m_vertexSize > m_vertexCapacity, "Vertex Size is larger than Vertex Capacity");

    std::vector<uint32_t> indices = generateIndices(m_type, m_vertexCapacity);
    uint32_t indexCapacity = static_cast<uint32_t>(indices.size());

    // Generate and bind Vertex Array
    GLCall(glGenVertexArrays(1, &m_vertexArrayID));
    GLCall(glBindVertexArray(m_vertexArrayID));

    // Generate and bind Vertex Buffer
    GLCall(glGenBuffers(1, &m_vertexBufferID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, m_vertexCapacity * floatPerVertex * sizeof(float), data, m_mode));

    // Generate and bind Index Buffer
    GLCall(glGenBuffers(1, &m_indexBufferID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCapacity * sizeof(uint32_t), indices.data(), m_mode));

    // Enable and set vertex attribute pointers
    GLCall(glEnableVertexAttribArray(0)); // position
    GLCall(glEnableVertexAttribArray(1)); // color
    GLCall(glEnableVertexAttribArray(2)); // texCoord

    GLsizei stride = floatPerVertex * sizeof(float);

    // Attribute 0: position (vec3)
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(0)));

    // Attribute 1: color (vec4)
    GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float))));

    // Attribute 2: texCoord (vec2)
    GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(7 * sizeof(float))));

    // Unbind Vertex Array (VAO)
    GLCall(glBindVertexArray(0));

    // Optional: unbind buffer (not strictly necessary as VAO stores state)
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

Renderable::Renderable(Renderable&& other)
    : m_vertexCapacity(other.m_vertexCapacity),  m_vertexSize(other.m_vertexSize), 
    m_floatPerVertex(other.m_floatPerVertex), m_type(other.m_type), m_mode(other.m_mode),  
    m_vertexBufferID(other.m_vertexBufferID), m_vertexArrayID(other.m_vertexArrayID),
    m_indexBufferID(other.m_indexBufferID)
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

        m_vertexCapacity = other.m_vertexCapacity;
        m_vertexSize     = other.m_vertexSize;
        m_type           = other.m_type;
        m_mode           = other.m_mode;
        m_floatPerVertex = other.m_floatPerVertex;
        m_vertexBufferID = other.m_vertexBufferID;
        m_vertexArrayID  = other.m_vertexArrayID;
        m_indexBufferID  = other.m_indexBufferID;

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
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID) );  
}


void Renderable::unbind() const
{
    GLCall( glBindVertexArray(0) );
}

uint32_t Renderable::vertexSize() const
{
    return m_vertexSize;
}

uint32_t Renderable::indexSize() const 
{ 
    return vertexCountToIndexCount(m_type, m_vertexSize);
}

uint32_t Renderable::floatPerVertex() const 
{ 
    return m_floatPerVertex; 
}

uint32_t Renderable::size() const 
{ 
    return m_vertexSize * m_floatPerVertex * sizeof(float); 
}


// ! Not tested
void Renderable::update(const void* data, uint32_t vertexSize, uint32_t vertexOffset)
{
    if( vertexOffset > m_vertexSize )
        m_vertexSize += ( m_vertexSize - vertexOffset );

    CHECK_WARN(m_vertexSize > m_vertexCapacity, "New size exceeds capacity"); 

    const uint32_t offset = m_vertexSize * m_floatPerVertex * sizeof(float);
    const uint32_t size   = vertexSize  * m_floatPerVertex * sizeof(float);

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}



void Renderable::updateAppend(const void* data, uint32_t vertexSize) 
{
    if (vertexSize == 0) return;

    CHECK_WARN(m_vertexSize + vertexSize > m_vertexCapacity, "New size exceeds capacity"); 

    const uint32_t offset = m_vertexSize * m_floatPerVertex * sizeof(float);
    const uint32_t size   = vertexSize  * m_floatPerVertex * sizeof(float);

    // Upload only new vertex data
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    
    m_vertexSize += vertexSize;
  
}



/////////////
// Private // 
/////////////

std::vector<uint32_t> Renderable::generateIndices(PrimitiveType type, uint32_t vertexCount) const 
{
    std::vector<uint32_t> indices;

    switch (type) 
    {
        case PrimitiveType::POINT: {
            indices.reserve(vertexCount);
            for (uint32_t i = 0; i < vertexCount; ++i)
                indices.push_back(i);
            break;
        }

        case PrimitiveType::LINE: {
            // Each line is 2 vertices → 2 indices per line
            uint32_t lineCount = vertexCount / 2;
            indices.reserve(lineCount * 2);
            for (uint32_t i = 0; i < lineCount * 2; ++i)
                indices.push_back(i);
            break;
        }

        case PrimitiveType::TRIANGLE: {
            // Each triangle is 3 vertices → 3 indices per triangle
            uint32_t triCount = vertexCount / 3;
            indices.reserve(triCount * 3);
            for (uint32_t i = 0; i < triCount * 3; ++i)
                indices.push_back(i);
            break;
        }

        case PrimitiveType::QUAD: {
            // Each quad is 4 vertices → 6 indices (2 triangles: 0-1-2, 2-3-0)
            uint32_t quadCount = vertexCount / 4;
            indices.reserve(quadCount * 6);
            for (uint32_t i = 0; i < quadCount; ++i) 
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

        case PrimitiveType::TRIANGLE_STRIP: {
            // triangleCount = vertexCount - 2
            if (vertexCount < 3) break;
            indices.reserve(vertexCount);
            for (uint32_t i = 0; i < vertexCount; ++i)
                indices.push_back(i);
            break;
        }

        case PrimitiveType::TRIANGLE_FAN: {
            // triangleCount = vertexCount - 2
            if (vertexCount < 3) break;
            uint32_t triCount = vertexCount - 2;
            indices.reserve(triCount * 3);
            for (uint32_t i = 0; i < triCount; ++i) 
            {
                indices.push_back(0);
                indices.push_back(i + 1);
                indices.push_back(i + 2);
            }
            break;
        }

        default:
            break;
    }

    return indices;
}

uint32_t Renderable::vertexCountToIndexCount(PrimitiveType type, uint32_t vertexCount) const
{
    switch (type) 
    {
        case PrimitiveType::POINT:
            return vertexCount;

        case PrimitiveType::LINE:
            // Each line uses 2 vertices → 2 indices per line
            return (vertexCount / 2) * 2;

        case PrimitiveType::TRIANGLE:
            // Each triangle uses 3 vertices → 3 indices per triangle
            return (vertexCount / 3) * 3;

        case PrimitiveType::QUAD:
            // Each quad uses 4 vertices → 6 indices (two triangles)
            return (vertexCount / 4) * 6;

        case PrimitiveType::TRIANGLE_STRIP:
            LOG_WARN("Not implemented for TRIANGLE_STRIP");
            return 0;
        case PrimitiveType::TRIANGLE_FAN:
            // Strip/Fan directly reference vertices in order
            return vertexCount;

        default:
            return 0;
    }
}
