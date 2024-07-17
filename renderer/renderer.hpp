#pragma once

#include<GL/glew.h>

#include"vertexArray.hpp"
#include"indexBuffer.hpp"
#include"shader.hpp"

#include <cstdint>

#ifdef _MSC_VER
  #define __builtin_trap() __debugbreak()
#endif

// #define ASSERT(x) if (!(x)) __debugbreak()
#define ASSERT(x) if (!(x)) __builtin_trap()
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);



class Renderer
{
public:
    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
