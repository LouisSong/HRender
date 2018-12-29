#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec2 FragPos;

uniform vec3 cameraPos;
uniform sampler2D texture1;
uniform samplerCube cubmapTexture;

void main()
{
	float ratio = 1.00 / 1.52;	//air 1.00;water 1.33;ice 1.309;glass 1.52;diamond 2.42;
	vec3 I = normalize(Position - cameraPos);
	vec3 R = refract(I,normalize(Normal),ratio);//refraction
	//vec3 R = reflect(I,normalize(Normal));//reflection
	vec4 diffuse = texture(texture1,FragPos);
	//vec4 reflectColor = vec4(texture(cubmapTexture,R).rgb,1.0);
	vec4 refractColor = vec4(texture(cubmapTexture,R).rgb,1.0);
	FragColor = refractColor;
	//FragColor = mix(diffuse,reflectColor,0.5);
}