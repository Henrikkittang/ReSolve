#pragma once

#include<cstdint>
#include<vector>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include"core/base.hpp"
#include"graphics/shader.hpp"
#include"graphics/renderable.hpp"





// Suggested Features:
// - Resizing/viewport management
//   This needs some kind of resize event that scenes can react to


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
	void update();

	void resize(int width, int height);
	void setVSync(bool enabled);
 
	glm::ivec2 getMousePosition() const;
	glm::ivec2 getSize() const;
	GLFWwindow* getNativeHandle();
	bool isKeyPressed(int key) const;
	bool windowShouldClose() const;

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:

	GLFWwindow* m_window;
	
};
