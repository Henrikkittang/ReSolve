#pragma once

#include<GL/glew.h>


class VertexBuffer
{
public:

    VertexBuffer();
    VertexBuffer(const void* data, uint32_t size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
private:
    GLuint m_renderID;
};