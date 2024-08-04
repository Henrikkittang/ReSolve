#pragma once
#include"vertexBuffer.hpp"
#include"vertexBufferLayout.hpp"

#include<GL/glew.h>

class VertexArray 
{
public:
    VertexArray();
    ~VertexArray();
    VertexArray(VertexArray&& other);
    VertexArray& operator=(VertexArray&& other);

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void bind() const;
    void unbind() const;
private:
    GLuint m_renderID;
};


