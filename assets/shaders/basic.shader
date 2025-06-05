#shader vertex
#version 460 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 uMVP;

out vec2 vTexCoord;

void main()
{
  gl_Position = uMVP * position;
  vTexCoord   = texCoord;
}

#shader fragment
#version 460 core

in vec2 vTexCoord;
layout(location = 0) out vec4 color;

uniform sampler2D uTexture;

void main()
{
  vec4 texColor = texture(uTexture, vTexCoord);
  color = texColor;
}