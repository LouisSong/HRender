#include "Camera.h"
#include<glm\gtc\matrix_transform.hpp>
#include <iostream>

Camera::Camera(glm::vec3 pos,glm::vec3 target, glm::vec3 up)
{
	this->pos = pos;
	this->target = target;
	this->worldUp = up;
	this->fov = 60;
}

void Camera::UpdateViewMatrix()
{
	view = glm::lookAt(pos, target, worldUp);
}

void Camera::Move(Camera_Movement direction,float deltaTime)
{
//	float velocity = speed * deltaTime;
//	switch (direction)
//	{
//		case FORWARD:
//			//pos += front * velocity;
//			target.z += velocity;
//			break;
//		case BACKWARD:
//			target.z -= velocity;
//			break;
//		case LEFT:
//			target.x += velocity;
//			break;
//		case RIGHT:
//			target.x -= velocity;
//			break;
//		default:
//			break;
//	}
}

void Camera::MouseMove(double xoffset, double yoffset,bool constrainPitch)
{
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	pitch += (float)yoffset;
	
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		else if (pitch < -89.0f)
			pitch = -89.0f;
	}

	float angleChange = (float)xoffset * sensitivity;
	angleAroundPlayer -= angleChange;

	yaw = 180 - angleAroundPlayer;
}

void Camera::Zoom(float yoffset)
{
	this->distanceFromPlayer -= yoffset;
	if (distanceFromPlayer < MIN_DISTANCE_FROM_PLAYER)
		distanceFromPlayer = MIN_DISTANCE_FROM_PLAYER;
	else if (distanceFromPlayer > MAX_DISTANCE_FROM_PLAYER)
		distanceFromPlayer = MAX_DISTANCE_FROM_PLAYER;
}

void Camera::UpdatePosition()
{
	float horizontalDistance = GetHorizontalDistance();
	float verticalDistance = GetVerticalDistance();

	float angle = angleAroundPlayer;
	float offsetX = horizontalDistance * glm::sin(glm::radians(angle));
	float offsetZ = horizontalDistance * glm::cos(glm::radians(angle));

	pos.x = target.x - offsetX;
	pos.y = verticalDistance;
	pos.z = target.z - offsetZ;
}

float Camera::GetHorizontalDistance()
{
	return distanceFromPlayer * glm::cos(glm::radians(pitch));
}

float Camera::GetVerticalDistance()
{
	return distanceFromPlayer * glm::sin(glm::radians(pitch));
}

Camera::~Camera()
{
}