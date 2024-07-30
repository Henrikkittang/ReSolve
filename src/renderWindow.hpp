#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>

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



class RenderWindow
{
public:

	RenderWindow(uint32_t width, uint32_t height);
	~RenderWindow();


    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	bool windowShouldClose() const;
	void update();

	glm::ivec2 getSize() const;
	GLFWwindow* getWindow() { return m_window; }	

private:

	GLFWwindow* m_window;
};
