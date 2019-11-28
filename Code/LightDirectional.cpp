#include "LightDirectional.h"

LightDirectional::LightDirectional(glm::vec3 _lightPositon, glm::vec3 _lightAngles, glm::vec3 _lightColor)
{
	lightPosition = _lightPositon;
	lightAngles = _lightAngles;
	lightColor = _lightColor;
	UpdataDirectional();
}

LightDirectional::~LightDirectional()
{
}

void LightDirectional::UpdataDirectional()
{
	//Change light position
	directional = lightPosition;
	directional = glm::rotateZ(directional, lightAngles.z);
	directional = glm::rotateX(directional, lightAngles.x);
	directional = glm::rotateY(directional, lightAngles.y);
	directional = -1.0f * directional;
}
