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

// * Try to keep following convention
// * Size: number of bytes
// * Length: number of elements

class Renderable 
{
public:

    Renderable();
    Renderable(const void* data, uint32_t size, uint32_t vertexCapacity, uint32_t floatPerVertex, PrimitiveType type, int mode=GL_STATIC_DRAW);   
    ~Renderable();
    Renderable(Renderable&& other);
    Renderable& operator=(Renderable&& other);

    uint32_t vertexSize() const;
    uint32_t indexSize() const;
    uint32_t floatPerVertex() const;
    uint32_t size() const;
    void bind() const;
    void unbind() const;

    void update(const void* data, uint32_t size, uint32_t offset=0);
    void updateAppend(const void* data, uint32_t vertexSize);

private:
    std::vector<uint32_t> generateIndices(PrimitiveType type, uint32_t primitiveCount) const;
    uint32_t vertexCountToIndexCount(PrimitiveType type, uint32_t vertexCount) const;

private:

    uint32_t m_vertexCapacity; // * Buffer size
    uint32_t m_indexCapacity;  // ? Make it purley a functio of m_vertexCapacity

    uint32_t m_vertexSize;  // * Size of acutally used in buffer 
    uint32_t m_indexSize;   // ? Make it purley a functio of m_vertexSize 

    uint32_t m_floatPerVertex;
    PrimitiveType m_type;
    int      m_mode;
    GLuint   m_vertexBufferID;
    GLuint   m_vertexArrayID;
    GLuint   m_indexBufferID;    
};


