#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 color;
out vec2 uv;

void main()
{
	color = vec4(aColor,1.0);
	uv = aTexCoord;
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}