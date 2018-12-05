#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

const float offset = 1.0 / 300.0;

void main()
{
	vec2 offsets[9] = vec2[](
		vec2(-offset,offset),
		vec2(0,offset),
		vec2(offset,offset),
		vec2(-offset,0),
		vec2(0,0),
		vec2(offset),
		vec2(-offset,-offset),
		vec2(0,-offset),
		vec2(offset,-offset)
	);

	float kernal[9] = float[](
		1,1,1,
		1,-8,1,
		1,1,1
	);

	//ģ��Ч��
	float kernal2[9] = float[](
		1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16  
	);

	 

	vec3 sampleTex[9];
	for(int i = 0;i < 9;i++)
	{
		sampleTex[i] = vec3(texture(screenTexture,TexCoords + offsets[i]));
	}

	vec3 col = vec3(0.0);
	for(int i = 0;i < 9;i++)
	{
		col += sampleTex[i] * kernal[i];
	}

	FragColor = vec4(col,1);

	//FragColor = texture(screenTexture,TexCoords);
	//float average = (FragColor.r + FragColor.g + FragColor.b) * 0.333;
	//FragColor = vec4(average,average,average,1.0);
}