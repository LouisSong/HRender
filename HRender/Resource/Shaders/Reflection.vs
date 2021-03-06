#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec3 Normal;
out vec3 Position;
out vec2 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat3 normalModel;

void main()
{
	Normal = normalModel * normal;
	Position = vec3(model * vec4(pos,1.0));
	FragPos = uv;
	gl_Position = projection * view * model * vec4(pos,1.0);
}