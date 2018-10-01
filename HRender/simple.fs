#version 330 core

in vec4 color;
in vec2 uv;

out vec4 FragColor;

uniform vec4 uColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec4 color1 = texture(texture1,uv);
	vec4 color2 = texture(texture2,uv);
	FragColor =  mix(color1,color2,0.2);
};