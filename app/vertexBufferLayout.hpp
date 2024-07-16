#pragma once
#include<vector>
#include<stdint.h>

struct VertexBufferElement
{
    uint32_t type;
    uint32_t count;
    unsigned char normalized;

    VertexBufferElement(uint32_t type, uint32_t count, bool normalized);
    static uint32_t getSizeOfType(uint32_t type);
};

class VertexBufferLayout
{
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    template<typename T>
    void push(uint32_t count);

    const std::vector<VertexBufferElement>& getElements() const;
    uint32_t getStride() const; 
private:
    std::vector<VertexBufferElement> m_elements;
    uint32_t m_stride;
};

template<>
void VertexBufferLayout::push<float>(uint32_t count);

template<>
void VertexBufferLayout::push<uint32_t>(uint32_t count);

template<>
void VertexBufferLayout::push<unsigned char>(uint32_t count);
