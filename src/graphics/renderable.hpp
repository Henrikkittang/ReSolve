#pragma once

#include<vector>
#include<cstdint>

#include<glad/glad.h>


enum class PrimitiveType
{
    TRIANGLE=0,
    QUAD,
    POINT,
    LINE,
    TRIANGLE_STRIP,
    TRIANGLE_FAN
};

// Try to keep following convetion
// Size: number of bytes
// Length: number of elements

class Renderable 
{
public:

    Renderable();
    Renderable(const void* data, uint32_t vertexCount, uint32_t floatPerVertex, PrimitiveType type, int mode=GL_STATIC_DRAW);   
    ~Renderable();
    Renderable(Renderable&& other);
    Renderable& operator=(Renderable&& other);

    uint32_t vertexCount() const;
    uint32_t indexCount() const;
    uint32_t floatPerVertex() const;
    uint32_t size() const;
    void bind() const;
    void unbind() const;
    void update(const void* data, uint32_t size);

private:
    std::vector<uint32_t> generateIndices(PrimitiveType type, uint32_t primitiveCount) const;
private:

    uint32_t m_vertexCount;
    uint32_t m_indexCount;
    uint32_t m_floatPerVertex;
    PrimitiveType m_type;
    int      m_mode;
    GLuint   m_vertexBufferID;
    GLuint   m_vertexArrayID;
    GLuint   m_indexBufferID;    
};


