#pragma once

#include<cstdint>
#include<vector>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include"graphics/shader.hpp"
#include"graphics/renderable.hpp"





// Suggested Features:
// - Resizing/viewport management

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
	void update();

	void resize(int width, int height);
	void setVSync(bool enabled);
	void toggleFullscreen();
 
	glm::ivec2 getMousePosition() const;
	glm::ivec2 getSize() const;
	GLFWwindow* getNativeHandle();
	bool isKeyPressed(int key) const;
	bool windowShouldClose() const;
	bool isFullscreen() const;
	
private:

	GLFWwindow* m_window;
	Shader      m_basicShader;

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
};
