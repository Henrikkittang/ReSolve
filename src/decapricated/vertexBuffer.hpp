#pragma once

#include<cstdint>
#include<glad/glad.h>


class VertexBuffer
{
public:

    VertexBuffer();
    VertexBuffer(const void* data, uint32_t size);
    ~VertexBuffer();
    VertexBuffer(VertexBuffer&& other);
    VertexBuffer& operator=(VertexBuffer&&  other);

    VertexBuffer(const VertexBuffer& other) = delete;
    VertexBuffer& operator=(const VertexBuffer& other) = delete;

    void bind() const;
    void unbind() const;
private:
    GLuint m_renderID;
};