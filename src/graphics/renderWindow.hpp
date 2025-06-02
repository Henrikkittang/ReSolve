#pragma once

#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>

#include <cstdint>

#include"decapricated/vertexArray.hpp"
#include"decapricated/indexBuffer.hpp"
#include"graphics/shader.hpp"
#include"graphics/renderable.hpp"


class RenderWindow
{
public:

	RenderWindow();
	RenderWindow(GLFWwindow* window);
	~RenderWindow();
	RenderWindow(const RenderWindow&) = delete;
	RenderWindow& operator=(const RenderWindow&) = delete;
	RenderWindow(RenderWindow&& other);
	RenderWindow& operator=(RenderWindow&& other);

    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void draw(const Renderable& renderable, const Shader& shader) const;

	bool windowShouldClose() const;
	void update();

	glm::ivec2 getSize() const;
	bool isKeyPressed(int key) const;
	
	// This function should not exists but it does for now during development
	GLFWwindow* getWindow() { return m_window; }	
	
private:

	GLFWwindow* m_window;
};
