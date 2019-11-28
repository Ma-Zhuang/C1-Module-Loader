#pragma once
#include<string>
#include"Shader.h"
#include"Mesh.h"
#include"Material.h"
class Module
{
public:
	//Read model file
	void Moduleload(std::string path);
	Module() {}
	~Module();
	//Read material file
	void readMTL(std::string mtlpath);
	//Store all the model data in mesh
	 void setUpMesh();
	Vertex* v = new Vertex();
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_textCoords;
	std::vector<glm::vec3> temp_normals;
	VertexCombineIndex vertComIndex;
	void draw(Shader* shader);
	Material material;
	//Determine whether to apply to this group of materials
	Material *getMaterial(std::string name);
	//Directly store all material information in materials, which is used for comparison in mesh
  	std::vector<Material> materials;
	//There are many mesh in an obj. Mesh is based on the sequence of read materials
	std::vector<Mesh> meshs;
	//Mesh used for reading
	Mesh mesh;
};

