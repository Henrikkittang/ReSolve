#include"vertexLayout.hpp"

#include<glad/glad.h>
#include"util/log.hpp"


VertexElement::VertexElement(uint32_t type, uint32_t count, bool normalized)
    :type(type), count(count), normalized(normalized)
{}
    
uint32_t VertexElement::getSizeOfType(uint32_t type)
{
    switch (type)
    {
        case GL_FLOAT:         return 4;
        case GL_UNSIGNED_INT:  return 4;
        case GL_UNSIGNED_BYTE: return 1;
        default:
            LOG_WARN("Not a VertexElement");
    }
    // ASSERT(false);
    return 0;
}


VertexLayout::VertexLayout()
    :m_stride(0)
{}

VertexLayout::~VertexLayout()
{}

template<typename T>
void VertexLayout::push(uint32_t count)
{
    LOG_FATAL("VertexLayout::push is not implemented for this type");
}
 

template<>
void VertexLayout::push<float>(uint32_t count)
{  
    m_elements.emplace_back(GL_FLOAT, count, GL_FALSE);
    m_stride += VertexElement::getSizeOfType(GL_FLOAT) * count;
}


template<>
void VertexLayout::push<uint32_t>(uint32_t count)
{  
    m_elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE);
    m_stride += VertexElement::getSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
void VertexLayout::push<uint8_t>(uint32_t count)
{
    m_elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_TRUE);
    m_stride += VertexElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
}

const std::vector<VertexElement>& VertexLayout::getElements() const
{
    return m_elements;
}

uint32_t VertexLayout::getStride() const
{
    return m_stride;
}
