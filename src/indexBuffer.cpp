#include "indexBuffer.hpp"
#include "renderWindow.hpp"

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
    : m_count(count)
{
    glGenBuffers(1, &m_renderId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_renderId));
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderId);
}


void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}