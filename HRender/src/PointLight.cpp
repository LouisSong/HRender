#include "stdafx.h"
#include<glm.hpp>
#include "PointLight.h"


PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}

void PointLight::Prepare(Shader* shader,int index)
{
	std::string indexStr = std::to_string(index);

	shader->SetVector3("pointLights[" + indexStr + "].position", position);
	
	shader->setFloat("pointLights["+ indexStr +"].constant", constant);
	shader->setFloat("pointLights[" + indexStr + "].linear", linear);
	shader->setFloat("pointLights[" + indexStr + "].quadratic", quadratic);

	shader->SetVector3("pointLights[" + indexStr + "].ambient", ambient);
	shader->SetVector3("pointLights[" + indexStr + "].diffuse", diffuse);
	shader->SetVector3("pointLights[" + indexStr + "].specular", specular);

}

PointLight* PointLight::operator=(PointLight* p)
{
	return p;
}