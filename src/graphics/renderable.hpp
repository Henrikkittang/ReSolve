#pragma once

#include<vector>
#include<cstdint>

#include<glad/glad.h>


// Try to keep following convetion
// Size: number of bytes
// Length: number of elements

class Renderable 
{
public:

    Renderable();
    Renderable(const void* data, uint32_t size, uint32_t length, int mode=GL_STATIC_DRAW);
    ~Renderable();
    Renderable(Renderable&& other);
    Renderable& operator=(Renderable&& other);

    uint32_t vertexCount() const;
    uint32_t indexCount() const;
    void bind() const;
    void unbind() const;
    void update(const void* data, uint32_t size);

private:
    std::vector<uint32_t> generateQuadIndices(uint32_t quadCount) const; 
private:

    uint32_t m_vertexCount;
    uint32_t m_indexCount;
    uint32_t m_floatPerVertex;
    int      m_mode;
    GLuint   m_vertexBufferID;
    GLuint   m_vertexArrayID;
    GLuint   m_indexBufferID;    
};


