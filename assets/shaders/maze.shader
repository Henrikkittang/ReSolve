#shader vertex
#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

uniform mat4 uMVP;

out vec4 vColor;

void main()
{
    gl_Position = uMVP * vec4(aPos, 1.0);
    vColor = aColor;
}


#shader fragment
#version 460 core

in vec4 vColor;


out vec4 FragColor;

void main()
{
    FragColor = vColor;
}


