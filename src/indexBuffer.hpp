#pragma once
#include <cstdint>

class IndexBuffer
{
public:

    IndexBuffer() = default;
    IndexBuffer(const uint32_t* data, uint32_t count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    uint32_t getCount() const { return m_count; }

private:
    GLuint m_renderId;
    uint32_t m_count;
};