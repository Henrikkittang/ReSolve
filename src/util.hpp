#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>


// Do I need this???
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


