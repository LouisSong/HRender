#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 color;
out vec2 uv;

void main()
{
	uv = aTexCoord;
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	//gl_PointSize = gl_Position.z;
}