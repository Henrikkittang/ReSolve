#pragma once

#include <glad/glad.h>

#include<cstdint>

class Renderable 
{
public:

    Renderable();
    Renderable(const void* data, uint32_t size, uint32_t floats, int mode=GL_STATIC_DRAW);
    ~Renderable();
    Renderable(Renderable&& other);
    Renderable& operator=(Renderable&& other);

    uint32_t size() const;
    void bind() const;
    void unbind() const;
    void update(const void* data, uint32_t size);

private:
    uint32_t m_size;
    int      m_mode;
    GLuint   m_vertexBufferID;
    GLuint   m_vertexArrayID;
};


