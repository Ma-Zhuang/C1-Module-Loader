#pragma once
#include<glm.hpp>
#include<gtx/rotate_vector.hpp>
class LightDirectional
{
public:
	LightDirectional(glm::vec3 _lightPositon, glm::vec3 _lightAngles, glm::vec3 _lightColor = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightDirectional();
	//light position
	glm::vec3 lightPosition;
	// Lighting angle
	glm::vec3 lightAngles;
	//light color
	glm::vec3 lightColor;
	//Light emission direction
	glm::vec3 directional;
	//Updata light data
	void UpdataDirectional();
};

