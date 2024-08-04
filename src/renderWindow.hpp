#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>

#include"vertexArray.hpp"
#include"indexBuffer.hpp"
#include"shader.hpp"

#include <cstdint>



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
	bool isKeyPressed(int key) const;
	
	// This function should not exists but it does for now during development
	GLFWwindow* getWindow() { return m_window; }	
	


private:

	GLFWwindow* m_window;
};
