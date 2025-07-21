#include"vertexArray.hpp"

#include"util/util.hpp"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_renderID));
}

VertexArray::~VertexArray()
{
    GLCall( glDeleteVertexArrays(1, &m_renderID) );
}

VertexArray::VertexArray(VertexArray&& other)
    : m_renderID(other.m_renderID) 
{
    other.m_renderID = 0; 
}

VertexArray& VertexArray::operator=(VertexArray&& other)
{
    if (this != &other) 
    {
        GLCall( glDeleteVertexArrays(1, &m_renderID) );
        
        m_renderID = other.m_renderID;
        
        other.m_renderID = 0;
    }
    return *this;
}


void VertexArray::bind() const
{
    GLCall( glBindVertexArray(m_renderID) );
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
    for(size_t i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall( glEnableVertexAttribArray(i) );
        GLCall( glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset) );
        offset += element.count * VertexBufferElement::getSizeOfType( element.type );
    }

    unbind();
    vb.unbind();
}
