#include"renderable.hpp"

#include"util.hpp"


Renderable::Renderable()
    : m_size(0), m_vertexBufferID(0), m_vertexArrayID(0)
{}

Renderable::Renderable(const void* data, uint32_t size, uint32_t floats)
    : m_size(size), m_vertexBufferID(0), m_vertexArrayID(0)
{

    GLCall( glGenVertexArrays(1, &m_vertexArrayID) );
    GLCall( glBindVertexArray(m_vertexArrayID) );

    GLCall( glGenBuffers(1, &m_vertexBufferID) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID) );
    GLCall( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );

    GLCall( glEnableVertexAttribArray(0) );
    GLCall( glVertexAttribPointer(0, floats, GL_FLOAT, GL_FALSE, floats * sizeof(float), (void*)0) );
    
   
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
    GLCall( glBindVertexArray(0) );
}

Renderable::Renderable(Renderable&& other)
    : m_size(other.m_size), m_vertexBufferID(other.m_vertexBufferID), m_vertexArrayID(other.m_vertexArrayID)
{
    other.m_vertexBufferID = 0;
    other.m_vertexArrayID  = 0;
}


Renderable::~Renderable()
{
    GLCall( glDeleteBuffers(1, &m_vertexBufferID) );
    GLCall( glDeleteVertexArrays(1, &m_vertexArrayID) );
}


Renderable& Renderable::operator=(Renderable&& other)
{
    if (this != &other) 
    {
        GLCall( glDeleteBuffers(1, &m_vertexBufferID) );
        GLCall( glDeleteVertexArrays(1, &m_vertexArrayID) );

        m_size = other.m_size;
        m_vertexBufferID = other.m_vertexBufferID;
        m_vertexArrayID  = other.m_vertexArrayID;

        other.m_vertexBufferID = 0;
        other.m_vertexArrayID  = 0;
    }
    return *this;
}

void Renderable::bind() const
{
    GLCall( glBindVertexArray(m_vertexArrayID) );
}


void Renderable::unbind() const
{
    GLCall( glBindVertexArray(0) );
}

uint32_t Renderable::size() const
{
    return m_size;
}


void Renderable::update(const void* data, uint32_t size)
{
    m_size = size;
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID) );    
    GLCall( glBufferData(GL_ARRAY_BUFFER, m_size, data, GL_STATIC_DRAW) );
}