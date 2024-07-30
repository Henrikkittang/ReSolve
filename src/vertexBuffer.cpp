#include "vertexBuffer.hpp"
#include "renderWindow.hpp"

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
    glGenBuffers(1, &m_rendrerId);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendrerId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() 
{
    GLCall(glDeleteBuffers(1, &m_rendrerId));
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendrerId);
}


void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}