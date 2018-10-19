#ifndef CAMERA_H
#define CAMERA_H

#include<glm.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 target;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	glm::mat4 view;

	float speed = 10.0f;
	float sensitivity = 0.1f;
	float fov_sensitivity = 3.0f;

	float pitch = 0.0f;
	float yaw = 0.0f;

	float fov = 45.0f;

	Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	
	void Camera::UpdateViewMatrix();
	void Camera::Zoom(float yoffset);
	void Camera::Move(Camera_Movement direction, float deltaTime);
	void Camera::MouseMove(double xoffset, double yoffset, bool constrainPitch = true);
	void Camera::UpdateVectors();
	
	~Camera();

private:
	
};

#endif

