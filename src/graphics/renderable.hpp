#pragma once

#include<GL/glew.h>

#include<cstdint>

class Renderable 
{
public:

    Renderable();
    Renderable(const void* data, uint32_t size, uint32_t floats);
    ~Renderable();
    Renderable(Renderable&& other);
    Renderable& operator=(Renderable&& other);

    uint32_t size() const;
    void bind() const;
    void unbind() const;
    void update(const void* data, uint32_t size);

private:
    uint32_t m_size;
    GLuint m_vertexBufferID;
    GLuint m_vertexArrayID;
};


