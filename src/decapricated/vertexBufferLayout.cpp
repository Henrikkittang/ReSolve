#include"vertexBufferLayout.hpp"
#include"util/util.hpp"

#include <glad/glad.h>


VertexBufferElement::VertexBufferElement(uint32_t type, uint32_t count, bool normalized)
    :type(type), count(count), normalized(normalized)
{}
    
uint32_t VertexBufferElement::getSizeOfType(uint32_t type)
{
    switch (type)
    {
        case GL_FLOAT:         return 4;
        case GL_UNSIGNED_INT:  return 4;
        case GL_UNSIGNED_BYTE: return 1;
    }
    // ASSERT(false);
    return 0;
}


VertexBufferLayout::VertexBufferLayout()
    :m_stride(0)
{}

VertexBufferLayout::~VertexBufferLayout()
{}

template<typename T>
void VertexBufferLayout::push(uint32_t count)
{
    // static_assert(false);
}
 

template<>
void VertexBufferLayout::push<float>(uint32_t count)
{  
    m_elements.emplace_back(GL_FLOAT, count, GL_FALSE);
    m_stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
}


template<>
void VertexBufferLayout::push<uint32_t>(uint32_t count)
{  
    m_elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE);
    m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;

}

template<>
void VertexBufferLayout::push<uint8_t>(uint32_t count)
{
    m_elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_TRUE);
    m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
}

const std::vector<VertexBufferElement>& VertexBufferLayout::getElements() const
{
    return m_elements;
}

uint32_t VertexBufferLayout::getStride() const
{
    return m_stride;
}