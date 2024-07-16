#pragma once
#include"vertexBuffer.hpp"
#include"VertexBufferLayout.hpp"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void bind() const;
    void unbind() const;
private:
    uint32_t m_rendererID;
};


