#pragma once
#include"Shader.h"
#include<glm.hpp>
class Material
{
public:

	//Material diffuse
	glm::vec3 diffues ;
	//Material specular
	glm::vec3 specular;
	//Material ambient
	glm::vec3 ambient ;
	//Name of texture, default path
	std::string texturepathname;
	//Material specular size
	float shininess = 0;
	//Material name
	std::string name;
	//Material quantity
	int illum = 0;
	Material() {}
	~Material() {};
};

