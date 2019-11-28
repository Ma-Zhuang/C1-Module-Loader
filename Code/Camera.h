#pragma once
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
class Camera
{
public:
	Camera(glm::vec3 cameraposition, float pitch, float yaw, glm::vec3 worldup);

	//The world of camera in 3D space
	glm::vec3 cameraPosition;
	//Forward vector
	glm::vec3 Forward;
	//Camera right vector
	glm::vec3 Right;
	//Camera up vector
	glm::vec3 Up;
	//Save the current world up
	glm::vec3 WorldUp;

	float Pitch;
	float Yaw;
	//Mouse movement speed in X direction
	float SenseX = 0.001f;
	//Mouse movement speed in Y direction
	float SenseY = 0.001f;
	//Offset of camera movement in X direction
	float speedX = 0;
	//Offset of camera movement in Y direction
	float speedY = 0;
	//Offset of camera movement in Z direction
	float speedZ = 0;
	//Update view matrix
	glm::mat4 GetViewMatrix();
	//Updata mouse position
	void ProcessMouseMovement(float deltaX, float deltaY);
	//updata camera position
	void UpdataCameraPos();

private:
	//Updata camera vector value
	void UpdataCameraVectors();

};

