#include "vertexBuffer.hpp"
#include "renderWindow.hpp"

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
    GLCall( glGenBuffers(1, &m_renderId) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_renderId) );
    GLCall( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) ) ;
}

VertexBuffer::~VertexBuffer() 
{
    GLCall(glDeleteBuffers(1, &m_renderId));
}

void VertexBuffer::bind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_renderId) );
}


void VertexBuffer::unbind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}