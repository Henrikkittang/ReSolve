#include"vertexArray.hpp"

#include "renderer.hpp"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
    GLCall( glDeleteVertexArrays(1, &m_rendererID) );
}

void VertexArray::bind() const
{
    GLCall( glBindVertexArray(m_rendererID) );
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
