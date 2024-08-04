#include"indexBuffer.hpp"
#include"util.hpp"

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
    : m_count(count)
{
    GLCall( glGenBuffers(1, &m_renderID) );
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID) );
    GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW) );
}
IndexBuffer::~IndexBuffer()
{
    GLCall( glDeleteBuffers(1, &m_renderID) );
}

IndexBuffer::IndexBuffer(IndexBuffer&& other)
    : m_renderID(other.m_renderID) 
{
    other.m_renderID = 0; 
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other)
{
    if (this != &other) 
    {
        GLCall( glDeleteBuffers(1, &m_renderID) );
        
        m_renderID = other.m_renderID;
        other.m_renderID = 0;
    }
    return *this;
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
}


void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}