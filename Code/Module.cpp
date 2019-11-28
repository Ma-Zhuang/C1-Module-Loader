#include "Module.h"
#include<fstream>
#include<sstream>
#include<algorithm>
#include <glm.hpp>
#include <vector>
void Module::Moduleload(std::string path)
{
	//Determine whether the file is loaded
	std::ifstream file(path);
	if (!file)
	{
		std::cerr << "Error::ObjLoader, could not open obj file:"
			<< path << " for reading." << std::endl;
	}
	std::string line;
	Mesh * tempmesh=NULL;
	//This is to determine whether it is the first load
	bool first = false;
	while (getline(file, line))
	{
		//Use materials at this time,
		if (line.substr(0, 7) == "usemtl ")
		{
			std::istringstream s(line.substr(7));
			std::string name;
			s >> name;
			if (first == false)
			{
				//For the first time, there is no material at this time.

				//Read the data into mesh
				tempmesh = new Mesh();
				tempmesh->name = name;
			
		 
			
				tempmesh->material = getMaterial(name);
				//Use this name to load the corresponding material. Because the MTL file needs to be read first, there is data in it.

				first = true;
			}
			else if(first == true && tempmesh!=NULL)
			{
				//Put this data in the linked list
				meshs.push_back(*tempmesh);
				//Create a new continue reading
				tempmesh = new Mesh();
				tempmesh->name = name;
				//get mesh
				tempmesh->material = getMaterial(name);
			}
			 
		}
		//Vertex texture coordinate data
		if (line.substr(0, 2) == "vt") 
		{
			std::istringstream s(line.substr(3));
			glm::vec2 vt;
			s >> vt.x;
			s >> vt.y;
			//Note that the DDS texture loaded here needs to reverse y
			vt.y = -vt.y;  
			temp_textCoords.push_back(vt);


		}
		//Vertex normal vector data
		else if (line.substr(0, 2) == "vn") 
		{
			std::istringstream s(line.substr(3));
			glm::vec3 vn;
			s >> vn.x; s >> vn.y; s >> vn.z;
			temp_normals.push_back(vn);

		}
		//Vertex position data
		else if (line.substr(0, 1) == "v") 
		{
			std::istringstream s(line.substr(2));
			glm::vec3 v;
			s >> v.x; s >> v.y; s >> v.z;
			temp_vertices.push_back(v);
		}
		//When reading the face data, you need to determine whether there is a new material. If the new material on the right means that mesh should be installed again
		else if (line.substr(0, 1) == "f") {
			if (first == false)
			{
				//For the first time, there is no material at this time.
				//Read the data into mesh
				tempmesh = new Mesh();
				first = true;
			}
			
			std::istringstream vtns(line.substr(2));
			std::string vtn;
			int i = 0;
			//Handle multiple vertex attributes in a row
			while (vtns >> vtn) { 
				std::replace(vtn.begin(), vtn.end(), '/', ' ');
				std::istringstream ivtn(vtn);
				ivtn >> vertComIndex.posIndex
					>> vertComIndex.textCoordIndex
					>> vertComIndex.normIndex;

				vertComIndex.posIndex--;
				vertComIndex.textCoordIndex--;
				vertComIndex.normIndex--;
				v->position = temp_vertices[vertComIndex.posIndex];
				v->texCoords = temp_textCoords[vertComIndex.textCoordIndex];
				v->normal = temp_normals[vertComIndex.normIndex];
				//Put the data in
				tempmesh->vertData.push_back(*v);
				i++;
			//	vertComIndices.push_back(vertComIndex);
			}
			//Judge triangle or quadrilateral
			tempmesh->TriorQuad = i--;
		}
		else if (line.substr(0, 6) == "mtllib") {
			std::istringstream s(line.substr(6));
			std::string mtl;
			s >> mtl;
			readMTL(mtl);
		}

	}
	//After loading, load temp
	meshs.push_back(*tempmesh);
}
Module::~Module() {

	for (unsigned int i = 0; i < meshs.size(); i++)
	{
		meshs[i].~Mesh();
	}
}

void Module::readMTL(std::string mtlpath)
{
	Material *m = NULL;
	//std::cout << mtlpath << std::endl;
	std::ifstream file(".\\Test Model\\"+mtlpath);
	bool first = false;
	if (!file.fail()) {
		std::string line;
		while (std::getline(file, line)) {
			if (line.substr(0, 7) == "newmtl ") {
				//First load
				if (first == false) 
				{
					m = new Material();
					first = true;
				}
				else
				{
					//Put the materials in and add them up
					materials.push_back(*m);
					m = new Material();
				}
				
				m->name = line.substr(7);
			}
			else if (line.substr(0, 6) == "illum ") {
				m->illum = atoi(line.substr(6).c_str());
			}
			else if (line.substr(0, 3) == "Ks ") {
				std::istringstream stream(line.substr(3));
				glm::vec3 ks;
				stream >> ks.x >> ks.y >> ks.z;
				m->specular = ks;
			}
			else if (line.substr(0, 3) == "Ka ") {
				std::istringstream stream(line.substr(3));
				glm::vec3 ka;
				stream >> ka.x >> ka.y >> ka.z;
				m->ambient = ka;
			}
			else if (line.substr(0, 3) == "Ns ") {
				std::istringstream stream(line.substr(3));
				float s;
				stream >>s;
				m->shininess = s;
			}
			else if (line.substr(0, 3) == "Kd ") {
				std::istringstream stream(line.substr(3));
				glm::vec3 kd;
				stream >> kd.x >> kd.y >> kd.z;
				m->diffues = kd;
			}
			 else if (line.substr(0, 7) == "map_Kd ") {
				 std::istringstream stream(line.substr(7));
				 std::string s;
				 stream >> s;
				 
				 m->texturepathname = ".\\Test Model\\" + s;
			} 
		}
		//Put the materials in and add them up
		materials.push_back(*m);
		delete m;
	}
}

void Module::setUpMesh()
{
	for (int i = 0; i < meshs.size(); i++)
	{
		meshs[i].setUpMesh();
	}
}

void Module::draw(Shader* shader)
{
	for (int i = 0; i < meshs.size(); i++)
	{
		meshs[i].drawMesh(shader);
	}
}

Material *Module::getMaterial(std::string name)
{
	//Determine whether to apply to this group of materials
	for (int i = 0; i < materials.size(); i++)
	{
		if (materials[i].name == name)
		{
			return &materials[i];
		}
	}
	return NULL;
}

