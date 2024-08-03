#include"vertexArray.hpp"

#include "renderWindow.hpp"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_renderId));
}

VertexArray::~VertexArray()
{
    GLCall( glDeleteVertexArrays(1, &m_renderId) );
}

void VertexArray::bind() const
{
    GLCall( glBindVertexArray(m_renderId) );
}

void VertexArray::unbind() const
{
    GLCall( glBindVertexArray(0) );
}
 
void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    uint32_t offset = 0;
    for(int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall( glEnableVertexAttribArray(i) );
        GLCall( glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset) );
        offset += element.count * VertexBufferElement::getSizeOfType( element.type );
    }
}
