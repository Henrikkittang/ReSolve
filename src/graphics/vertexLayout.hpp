#pragma once
#include<vector>
#include<cstdint>

struct VertexElement
{
    uint32_t type;
    uint32_t count;
    unsigned char normalized;

    VertexElement(uint32_t type, uint32_t count, bool normalized);
    static uint32_t getSizeOfType(uint32_t type);
};

class VertexLayout
{
public:
    VertexLayout();
    ~VertexLayout();

    template<typename T>
    void push(uint32_t count);

    const std::vector<VertexElement>& getElements() const;
    uint32_t getStride() const; 
private:
    std::vector<VertexElement> m_elements;
    uint32_t m_stride;
};

template<>
void VertexLayout::push<float>(uint32_t count);

template<>
void VertexLayout::push<uint32_t>(uint32_t count);

template<>
void VertexLayout::push<uint8_t>(uint32_t count);
