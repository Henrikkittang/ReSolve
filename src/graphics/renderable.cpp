#include"renderable.hpp"

#include"util.hpp"

Renderable::Renderable(const void* data, uint32_t size, uint32_t floats)
{
    GLCall( glGenBuffers(1, &m_vertexBufferID) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID) );
    GLCall( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID) );

 
    GLCall( glGenVertexArrays(1, &m_vertexArrayID) );
    GLCall( glBindVertexArray(m_vertexArrayID) );

    GLCall( glEnableVertexAttribArray(0) );
    GLCall( glVertexAttribPointer(0, floats, GL_FLOAT, GL_FALSE, floats * sizeof(float), (void*)0) );
    
   
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Renderable::~Renderable()
{
    GLCall(glDeleteBuffers(1, &m_vertexBufferID));
    GLCall( glDeleteVertexArrays(1, &m_vertexArrayID) );
}

void Renderable::bind()
{
    GLCall( glBindVertexArray(m_vertexArrayID) );
}


void Renderable::unbind()
{
    GLCall( glBindVertexArray(0) );
}
