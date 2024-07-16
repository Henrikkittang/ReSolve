#pragma once
#include <cstdint>

class IndexBuffer
{
public:

    IndexBuffer(const uint32_t* data, uint32_t count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    uint32_t getCount() const { return m_count; }

private:
    uint32_t m_rendrerID;
    uint32_t m_count;
};