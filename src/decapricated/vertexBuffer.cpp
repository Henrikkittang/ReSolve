#include"vertexBuffer.hpp"
#include"util/util.hpp"

#include<iostream>

VertexBuffer::VertexBuffer()
    : m_renderID(0)
{}

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
    GLCall( glGenBuffers(1, &m_renderID) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_renderID) );
    GLCall( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );   
}

VertexBuffer::~VertexBuffer() 
{
    GLCall(glDeleteBuffers(1, &m_renderID));
}

VertexBuffer::VertexBuffer(VertexBuffer&& other)
    : m_renderID(other.m_renderID) 
{
    other.m_renderID = 0; 
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&&  other)
{
    if (this != &other) 
    {
        GLCall(glDeleteBuffers(1, &m_renderID));
        
        m_renderID = other.m_renderID;
        other.m_renderID = 0;
    }
    return *this;
}


void VertexBuffer::bind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_renderID) );
}


void VertexBuffer::unbind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}