#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Shader.h"

class PointLight
{
public:

	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	PointLight();
	~PointLight();
	
	void Prepare(Shader* shader, int index);
	PointLight* PointLight::operator=(PointLight* p);
};
#endif