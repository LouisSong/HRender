#include "stdafx.h"
#include "Camera.h"
#include<gtc\matrix_transform.hpp>

Camera::Camera(glm::vec3 pos,glm::vec3 target, glm::vec3 up)
{
	this->pos = pos;
	this->target = target;
	this->front = target;
	this->up = up;

	this->Update();
}

void Camera::Update()
{
	view = glm::lookAt(this->pos, this->pos + this->front, this->up);
}

Camera::~Camera()
{
}
