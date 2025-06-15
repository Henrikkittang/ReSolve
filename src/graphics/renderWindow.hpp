#pragma once

#include<cstdint>
#include<vector>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include"core/assetManager.hpp"  // Needed for Ref, this needs to be changed
#include"graphics/shader.hpp"
#include"graphics/renderable.hpp"





// Suggested Features:
// - Resizing/viewport management
// - VSync toggle
// - Input abstraction (mouse/scroll)
// - Optional: expose getNativeHandle() cleanly

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
	void draw(const glm::vec2* vertecies, uint32_t size, PrimitiveType type) const;

	bool windowShouldClose() const;
	void update();

	glm::ivec2 getSize() const;
	bool isKeyPressed(int key) const;
	
	// This function should not exists but it does for now during development
	GLFWwindow* getWindow() { return m_window; }	
	
private:

	GLFWwindow* m_window;

	
	static inline const char* s_basicShaderSource = R"glsl(
#shader vertex
#version 460 core

layout(location = 0) in vec4 position;

uniform mat4 uMVP;

void main()
{
    gl_Position = uMVP * position;
}

#shader fragment
#version 460 core

uniform vec4 uColor;             

layout(location = 0) out vec4 color;

void main()
{
    color = uColor;
}

)glsl";

	Shader m_basicShader;
};
