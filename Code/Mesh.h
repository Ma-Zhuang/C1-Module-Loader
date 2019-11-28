#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<GL/glew.h>
#include<glm.hpp>
#include"Shader.h"
#include"Material.h"

//model data
struct Vertex
{
	//Model vertex coordinates
	glm::vec3 position;
	//Model texture coordinates
	glm::vec2 texCoords;
	//Model normal coordinates
	glm::vec3 normal;
};

//Represents the position, texture coordinates and normal vector index of a vertex in the obj file
struct VertexCombineIndex
{
	// Vertex Index
	GLuint posIndex;
	// Texture Index
	GLuint textCoordIndex;
	// Normal vector
	GLuint normIndex;
};

class Mesh
{
public:
	Mesh() {}
	//Data after model analysis
	std::vector<Vertex> vertData;
	//If the model surface information contains quadrilateral, it will be stored here
	std::vector<Vertex> QtoT_vertData;
	//To convert a quadrilateral in a model to a triangle
	void QuadsToTrangle();
	//One mesh and one material
	Material *material;
	int textureId=0;
	int TriorQuad = 3;
	~Mesh();
	void drawMesh(Shader* shader);
	//Binding model data
	void setUpMesh();
	//This is the name of the material for comparison
	std::string name;
private:
	unsigned int VAO, VBO, EBO;

};
