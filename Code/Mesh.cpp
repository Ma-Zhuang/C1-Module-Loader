#include "Mesh.h"
#include "Textures.h"
void Mesh::QuadsToTrangle()
{
	//Convert quadrilateral to triangle
	for (int i = 0; i < vertData.size()/4; i++)
	{
		//Split the quadrilateral into two triangles by using the counter clockwise method
		//Draw triangles in the order of 0, 1, 2 and 2, 3, 0, respectively
		QtoT_vertData.push_back(vertData[i * 4 + 0]);
		QtoT_vertData.push_back(vertData[i * 4 + 1]);
		QtoT_vertData.push_back(vertData[i * 4 + 2]);

		QtoT_vertData.push_back(vertData[i * 4 + 2]);
		QtoT_vertData.push_back(vertData[i * 4 + 3]);
		QtoT_vertData.push_back(vertData[i * 4 + 0]);

	}
	//Clear the model data with quadrilateral before
	vertData.clear();
	//Combine the quadrilateral divided into two triangles and add the model data
	vertData = QtoT_vertData;
	//Clear QtoT_vertData variable
	QtoT_vertData.clear();
}

//Untying
Mesh::~Mesh()
{
	glBindVertexArray(0);
	glUseProgram(0);   
}

void Mesh::drawMesh(Shader* shader)
{
	  {
		//Passing material data into frame shader through uniform
		shader->use();
		if (material != nullptr)
		{
			shader->setUniform3f("material.ambient", material->ambient);
			shader->setUniform3f("material.diffuse", material->diffues);
			shader->setUniform3f("material.specular", material->specular);
			shader->setUniform1f("material.shininess", material->shininess);
		}
		else //If there is no material, you need to set a default material.

		{
			shader->setUniform3f("material.ambient", material->ambient);
			shader->setUniform3f("material.diffuse", material->diffues);
			shader->setUniform3f("material.specular", material->specular);
			shader->setUniform1f("material.shininess", material->shininess);
			
		}
		//Bind VAO data
		glBindVertexArray(VAO);
		//Bind Texture
		glBindTexture(GL_TEXTURE_2D, textureId);
		//Pass in picture to fragment
		shader->setUniform1i("tex", 0);
		//Draw the model as a triangle through drawarray
	  	glDrawArrays(GL_TRIANGLES, 0, vertData.size());

		//Untying vertexdata
		glBindVertexArray(0);
		//Untying texture
		glActiveTexture(GL_TEXTURE0);
	}
}

 

void Mesh::setUpMesh()
{
	if (TriorQuad == 4)
	{
		//Change 4 side lines to 3 corner lines
		QuadsToTrangle();
	}
	
	//Create VAO
	glGenVertexArrays(1, &VAO);

	//Bind VAO
	glBindVertexArray(VAO);

	//Create VBO
	glGenBuffers(1, &VBO);

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Fill VBO with data type, size, data method: whether to change frequently, if not select static
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertData.size(), vertData.data(), GL_STATIC_DRAW);
	//Value model vertex position
	glEnableVertexAttribArray(0);
	//Take model vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//Value model texture position
	glEnableVertexAttribArray(1);
	//Take model texture data
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GL_FLOAT)));
	//Value model normal position
	glEnableVertexAttribArray(2);
	//Take model normal data
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(GL_FLOAT)));
	//Clear
	glBindVertexArray(0);

	//To read the texture binding texture
	if (material != NULL && material->texturepathname != "")
	{
		textureId = Textures::load2DTexture(material->texturepathname.c_str(), GL_RGB, GL_RGB,0);
	}






}
