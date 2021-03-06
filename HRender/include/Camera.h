#ifndef CAMERA_H
#define CAMERA_H

#include<glm\glm.hpp>

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

	const float MIN_DISTANCE_FROM_PLAYER = 1.0f;
	const float MAX_DISTANCE_FROM_PLAYER = 150.0f;
	float distanceFromPlayer = 100.0f;
	
	float angleAroundPlayer = 0.0f;

	float speed = 10.0f;
	float sensitivity = 0.6f;
	float fov_sensitivity = 3.0f;

	float pitch = 0.0f;
	float yaw = 0.0f;

	float fov = 45.0f;

	Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	
	void UpdateViewMatrix();
	void Zoom(float yoffset);
	void Move(Camera_Movement direction, float deltaTime);
	void MouseMove(double xoffset, double yoffset, bool constrainPitch = true);

	float GetHorizontalDistance();
	float GetVerticalDistance();
	void UpdatePosition();
	
	~Camera();

private:
	
};

#endif

