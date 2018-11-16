#version 330 core

in vec4 color;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec4 uColor;
uniform sampler2D texture1;

void main()
{
	vec4 color1 = texture(texture1,TexCoords);
	//FragColor =  color1;
	FragColor = vec4(vec3(gl_FragCoord.z),1.0);
}