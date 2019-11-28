#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL\glew.h>
#include<glm.hpp>


class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource = 0;
	const char* fragmentSource = 0;
	unsigned int ProgramID = 0;//shader program ID
	void use();
	void setUniform3f(const char* paramNameString,glm::vec3 param);
	void setUniform1f(const char* paramNameString, float param);
	void setUniform1i(const char* paramNameString, int slot);

	enum Slot
	{
		DIFFUSE,
		SPECULAR
	};

private:
	void checkCompileErrors(unsigned int ProgramID, std::string type);
};

#endif