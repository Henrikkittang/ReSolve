#pragma once
#include"vertexBuffer.hpp"
#include"vertexBufferLayout.hpp"

#include<glad/glad.h>

class VertexArray 
{
public:
    VertexArray();
    ~VertexArray();
    VertexArray(VertexArray&& other);
    VertexArray& operator=(VertexArray&& other);

    VertexArray(const VertexArray& other) = delete;
    VertexArray& operator=(const VertexArray& other) = delete;

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void bind() const;
    void unbind() const;
private:
    GLuint m_renderID;
};


