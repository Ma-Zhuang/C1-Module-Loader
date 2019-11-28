#ifndef SHADER
#include "Shader.h"
#include<iostream>
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	std::stringstream vertexSStream;
	std::ostringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open()) {
			throw std::exception::exception("Open file error");
		}
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		ProgramID = glCreateProgram();
		glAttachShader(ProgramID, vertex);
		glAttachShader(ProgramID, fragment);
		glLinkProgram(ProgramID);
		checkCompileErrors(ProgramID, "PROGRAM");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}

 
}

void Shader::use()
{
	glUseProgram(ProgramID);
}

void Shader::setUniform3f(const char* paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ProgramID, paramNameString), param.x, param.y, param.z);
}

void Shader::setUniform1f(const char* paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ProgramID, paramNameString), param);
}

void Shader::setUniform1i(const char* paramNameString, int slot)
{
	glUniform1i(glGetUniformLocation(ProgramID, paramNameString), slot);
}

void Shader::checkCompileErrors(unsigned int ProgramID, std::string type) {
	int success;
	char infoLog[512];
	if (type != "PROGRAM") {
		glGetShaderiv(ProgramID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ProgramID, 512, NULL, infoLog);
			std::cout << "Shader Compile ERROR: " << infoLog << std::endl;
		}
	}
	else
	{
		glGetShaderiv(ProgramID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ProgramID, 512, NULL, infoLog);
			std::cout << "Program Linking ERROR: " << infoLog << std::endl;
		}
	}
}

#endif