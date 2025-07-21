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
	void draw(const Renderable& renderable) const;
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

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 uMVP;

out vec4 vColor;
out vec2 vTexCoord;

void main()
{
    gl_Position = uMVP * vec4(aPos, 1.0);
    vColor = aColor;
    vTexCoord = aTexCoord;
}


#shader fragment
#version 460 core

in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2D uTexture;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(uTexture, vTexCoord);
    FragColor = vColor;
}


)glsl";

	Shader m_basicShader;
};
