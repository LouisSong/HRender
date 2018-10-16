#ifndef CAMERA_H
#define CAMERA_H

#include<glm.hpp>

class Camera
{
public:

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 view;

	float speed = 10.0f;

	Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	
	void Camera::Update();
	
	~Camera();

private:
	
};

#endif

