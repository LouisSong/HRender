#include "stdafx.h"
#include "Camera.h"
#include<gtc\matrix_transform.hpp>

Camera::Camera(glm::vec3 pos,glm::vec3 target, glm::vec3 up)
{
	this->pos = pos;
	this->target = target;
	this->front = target;
	this->worldUp = up;
	this->fov = 45.0f;
	this->UpdateVectors();
}

void Camera::UpdateViewMatrix()
{
	view = glm::lookAt(pos, pos + front, up);
}

void Camera::Move(Camera_Movement direction,float deltaTime)
{
	float velocity = speed * deltaTime;
	switch (direction)
	{
		case FORWARD:
			pos += front * velocity;
			break;
		case BACKWARD:
			pos -= front * velocity;
			break;
		case LEFT:
			pos -= right * velocity;
			break;
		case RIGHT:
			pos += right * velocity;
			break;
		default:
			break;
	}

	UpdateVectors();
}

void Camera::MouseMove(double xoffset, double yoffset,bool constrainPitch)
{
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	pitch += (float)yoffset;
	yaw += (float)xoffset;

	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		else if (pitch < -89.0f)
			pitch = -89.0f;
	}
}

void Camera::Zoom(float yoffset)
{
	this->fov += yoffset * fov_sensitivity;
	if (this->fov > 45.0f)
		this->fov = 45.0f;
	else if (this->fov < 1.0f)
		this->fov = 1.0f;
}

void Camera::UpdateVectors()
{
	glm::vec3 _front;
	_front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	_front.y = sin(glm::radians(pitch));
	_front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	front = glm::normalize(_front);
	right = glm::cross(front,worldUp);
	up = glm::cross(right, front);
}

Camera::~Camera()
{
}
