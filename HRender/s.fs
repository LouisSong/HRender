#version 330 core

in vec4 color;
in vec2 uv;

out vec4 FragColor;

uniform vec4 uColor;
uniform sampler2D ourTexture;

void main()
{
	FragColor = texture(ourTexture,uv) * uColor;
};