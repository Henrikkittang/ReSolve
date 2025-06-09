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

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
} 