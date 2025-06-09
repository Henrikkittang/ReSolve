#pragma once

#include<cstdint>


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include"core/assetManager.hpp"  // Needed for Ref, this needs to be changed
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
	void draw(const Renderable& renderable, Ref<Shader> shader) const;
	void draw(const glm::vec2* vertecies, uint32_t size) const;

	bool windowShouldClose() const;
	void update();

	glm::ivec2 getSize() const;
	bool isKeyPressed(int key) const;
	
	// This function should not exists but it does for now during development
	GLFWwindow* getWindow() { return m_window; }	
	
private:

	GLFWwindow* m_window;
};
