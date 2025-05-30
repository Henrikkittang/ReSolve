#pragma once

#include<GL/glew.h>

#include<cstdint>

class IndexBuffer
{
public:

    IndexBuffer() = default;
    IndexBuffer(const uint32_t* data, uint32_t count);
    ~IndexBuffer();
    IndexBuffer(IndexBuffer&& other);
    IndexBuffer& operator=(IndexBuffer&& other);

    IndexBuffer(const IndexBuffer& other) = delete;
    IndexBuffer& operator=(const IndexBuffer& other) = delete;

    void bind() const;
    void unbind() const;

    uint32_t getCount() const { return m_count; }

private:
    GLuint   m_renderID;
    uint32_t m_count;
};