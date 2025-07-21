#pragma once

#include<iostream>

#include<glad/glad.h>
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


inline void DEBUG_LOG(const std::string& msg)
{
#ifdef DEBUG
    std::cout << msg << "\n";
#endif
}

inline void DEBUG_CHECK(bool cond, const std::string& msg)
{
#ifdef DEBUG
    if(cond)
        std::cout << msg << "\n";
#endif
}