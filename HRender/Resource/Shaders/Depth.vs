#version 330 core
layout (location = 0) in vec3 pos;
//layout (location = 1) in vec3 normal;
layout (location = 1) in vec2 uv;

uniform mat3 normalModel;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main()
{
	gl_Position = projection * view * model * vec4(pos,1.0);;
	FragPos = vec3(model * vec4(pos,1.0));
	//Normal = normalModel * normal;
	TexCoords = uv;
}