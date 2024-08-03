#include "vertexBuffer.hpp"
#include "renderWindow.hpp"

#include<iostream>

VertexBuffer::VertexBuffer()
{
    std::cout << "Vertex buffer created: default constructor \n";
}

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
    GLCall( glGenBuffers(1, &m_renderID) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_renderID) );
    GLCall( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) ) ;   
}

VertexBuffer::~VertexBuffer() 
{
    GLCall(glDeleteBuffers(1, &m_renderID));
}

void VertexBuffer::bind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_renderID) );
}


void VertexBuffer::unbind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}