#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube cubmapTexture;

void main()
{
	FragColor = texture(cubmapTexture,TexCoords);
}