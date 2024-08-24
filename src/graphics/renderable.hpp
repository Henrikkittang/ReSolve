#pragma once

#include"scene.hpp"

class Renderable : public Scene
{
public:
    Renderable(const void* data, uint32_t size, uint32_t floats);
    ~Renderable();

    void bind();
    void unbind();

private:
    GLuint m_vertexBufferID;
    GLuint m_vertexArrayID;

};


