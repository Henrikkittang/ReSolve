#pragma once
#include <cstdint>


class VertexBuffer
{
public:

    VertexBuffer() = default;
    VertexBuffer(const void* data, uint32_t size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
private:
    GLuint m_renderID;
};