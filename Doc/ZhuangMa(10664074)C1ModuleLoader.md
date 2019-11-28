# Obj Module Loader

## Tools

### Integrated Development Environment 

1. Microsoft Visual Studio Community 2019
2. Microsoft Visual C++ 2019

### OpenGL- 4.5

### Lib

1. GLEW-2.1.0
2. GLFW-3.3
3. GLM
4.  stb_image 

## Set Up Operation Environment

### GLEW

1. Right click the project solution and click the Properties button

2. Click C/C++ --->> General --->> Additional Include Directories

   ![1](https://github.com/SOFT356-Genshushu/Pic/blob/master/1.png?raw=true)
   
3. Click Add to import the path of GLEW Include 

   ![2](https://github.com/SOFT356-Genshushu/Pic/blob/master/2.png?raw=true)

   ![3](https://github.com/SOFT356-Genshushu/Pic/blob/master/3.png?raw=true)

4. Linker --->> General --->> Additional Library Directories

   ![4](https://github.com/SOFT356-Genshushu/Pic/blob/master/4.png?raw=true)

5. Click Add to import the path of GLEW Iib 

   ![5](https://github.com/SOFT356-Genshushu/Pic/blob/master/5.png?raw=true)

6. Linker --->> Input --->> Additional Dependencies

   ![6](https://github.com/SOFT356-Genshushu/Pic/blob/master/6.png?raw=true)

7. Input glew32s.lib

8. Input opengl32.lib

### GLFW
1. Right click the project solution and click the Properties button

2. Click C/C++ --->> General --->> Additional Include Directories

   ![1](https://github.com/SOFT356-Genshushu/Pic/blob/master/1.png?raw=true)
   
3. Click Add to import the path of GLFW Include 

   ![2](https://github.com/SOFT356-Genshushu/Pic/blob/master/2.png?raw=true)

   ![8](https://github.com/SOFT356-Genshushu/Pic/blob/master/8.png?raw=true)
   
4. Linker --->> General --->> Additional Library Directories

   ![4](https://github.com/SOFT356-Genshushu/Pic/blob/master/4.png?raw=true)
   
5.  Click Add to import the path of GLFW Iib 

   ![7](https://github.com/SOFT356-Genshushu/Pic/blob/master/7.png?raw=true)
   
6. Linker --->> Input --->> Additional Dependencies

   ![6](https://github.com/SOFT356-Genshushu/Pic/blob/master/6.png?raw=true)
7. Input glfw32.lib

### GLM
1. Right click the project solution and click the Properties button

2. Click C/C++ --->> General --->> Additional Include Directories

   ![1](https://github.com/SOFT356-Genshushu/Pic/blob/master/1.png?raw=true)
   
3. Click Add to import the path of GLM 

   ![2](https://github.com/SOFT356-Genshushu/Pic/blob/master/2.png?raw=true)

   ![9](https://github.com/SOFT356-Genshushu/Pic/blob/master/9.png?raw=true)

### stb_image
1.  Download the stb_image. h file through GitHub and download it to the project directory (https://github.com/nothings/stb/blob/master/stb_image.h）

2. Right click the project solution and select an existing item. --->>Locate the location of the stb_image. h file and click ADD --->> Click the stb_image. h file.

   ![10](https://github.com/SOFT356-Genshushu/Pic/blob/master/10.png?raw=true)
   ![11](https://github.com/SOFT356-Genshushu/Pic/blob/master/11.png?raw=true)

## Method of Application

Click Run to enter the program after the user completes the above steps and successfully builds the running environment. 

In theory, this program can load any model, but for the convenience of demonstration, only four models are loaded temporarily. The names of the models are creaper, pouf, Nanosuit and low poly boat, respectively.

This program can achieve any obj type model loading and rendering.It includes the rendering of materials and textures, as well as the correct rendering of models without textures in the material file(The texture map format is PNG or jpg).In addition, the rendered model can be observed at any angle by moving the camera. Users can also change the rendering model through keyboard keys. It is worth noting that the program contains the content of directional light, which is embodied in specular reflection and diffuse reflection

**After program running:**

### **Keyboard key **

1. Press the key "W" to move the camera up
2. Press the key "S" to move the camera downward
3. Press the key "A" to move the camera to the left
4. Press the key "D" to move the camera to the right
5. Press the key "e" to move the camera backward in the current direction
6. Press the key "Q" to move the camera in the current direction
7. Press the digital key "1" to change the model to Creeper
8. Press the digital key "2" to change the model to pouf
9. Press the digital key "3" to change the model to nanosuit
10. Press the digital key "4" to change the model to low_poly_boat
11. Press the number key "5" to render all models in the same scene
12. Press the number key "9" to clear all models in the same scene
13. Press the number key "ESC" to Exit

### **Mouse Movement**

By moving the mouse to control the change of camera angle, the angle of view can be moved

## Procedure Workflow

### There are seven CPP files and two Shaders in this procedure. The workflow of these files is as follows:

The loader.cpp file is loaded first when the program runs. When the program is running, the loader.cpp file will be loaded first. In the loader.cpp file, the position, color and angle of the directional light will be set first, followed by the position and rotation angle of the camera. In addition, read the external two shaders (vertex shader and fragment shader) and all the data of the model into memory for parsing. Finally, the model data is parsed and then rendered.

When reading the shader data, the shader.cpp file will be called to parse the file. After that, shader.cpp will create a project from the read data for later model rendering. In addition, if the syntax of the shader is wrong, the user will get the corresponding prompt.

When reading the model data, loader.cpp will call the module.cpp file. In module.cpp, the data in the obj file will be parsed, and the vertex coordinates, texture coordinates, normal vectors and surface information can be removed respectively. After sorting the data categories, Mesh.cpp will be called and stored in the Mesh.cpp. Each mesh is the smallest entity that can be rendered, and multiple entities are finally combined into a complete model. During the analysis of obj model data, the MTL material file corresponding to obj model will be read, and information such as diffuse reflection, specular reflection, ambient light and texture map will be read from the material file. After that, material.cpp and mesh.cpp will be called to integrate these data for the final rendering.

In addition, the functions in camera.cpp will be called when the user presses the keyboard or moves the mouse to move the camera while the program is running. The main purpose of these functions is to change the position and rotation angle of the camera in the world position through calculation, so as to get the function of the mobile camera to observe the model. meanwhile, due to the change of camera position, the vector from the model to the camera also changes. Therefore, it is necessary to recalculate the specular reflection. At this time, lightdirectional.cpp and fragment shader will be called to calculate the specular reflection. 

### **The above details will be explained in more detail below with the aid of the figures.**



#### Function Call Diagram

##### The function called by loader.cpp

```c++
//Input camera world space position, angle
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//Enter the position, color, rotation of the parallel light
LightDirectional lightdirectional = LightDirectional(glm::vec3(-2.0f, 1.0f, 1.0f), glm::vec3(glm::radians(189.0f), 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));

//Load four models
Module Creeper = Module();
Module pouf = Module();
Module nanosuit = Module();
Module low_poly_boat = Module();
//Load the read obj model data into mesh
	nanosuit.setUpMesh();
//Load the read obj model data into mesh
	pouf.setUpMesh();
//Load the read obj model data into mesh
	low_poly_boat.setUpMesh();
//Load the read obj model data into mesh
	Creeper.setUpMesh();

//Read VertexShader and FragmentShader
Shader* myShader = new Shader("VertexShader.vert", "FragmentShader.frag");
```

![DependsOn-Loader-cpp.png](https://github.com/SOFT356-Genshushu/Pic/blob/master/Loader-cpp.png?raw=true)
##### Camera module

Call camera function to achieve camera movement

```c++
//Enter the camera's position, rotation angle, etc. so that the user can move the camera to recalculate the position
Camera::Camera(glm::vec3 cameraposition, float pitch, float yaw, glm::vec3 worldup);
//Get current camera perspective
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(cameraPosition, cameraPosition + Forward, WorldUp);
}
//Get the value of the user changing the camera position
void Camera::ProcessMouseMovement(float deltaX, float deltaY);
//Recalculate camera position by user variable
void Camera::UpdataCameraPos()
{
    //0.1f is used to control the speed. If you do not control the camera movement speed, the user experience will be very bad.
	cameraPosition += Forward * speedZ * 0.1f + Right * speedX * 0.1f + Up * speedY * 0.1f;
}
//Update camera position to calculate specular and diffuse reflections
void Camera::UpdataCameraVectors()
{
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
```

![Camera-h.png](https://github.com/SOFT356-Genshushu/Pic/blob/master/Camera-h.png?raw=true)
##### Model loading module

```c++
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
				//Use this name to load the corresponding material. Because the MTL file needs to be read first, there is data in it.

				first = true;
			}
			else if(first == true && tempmesh!=NULL)
			{
				
			}
			 
		}
		//Vertex texture coordinate data
		if (line.substr(0, 2) == "vt") 
		{

		}
		//Vertex normal vector data
		else if (line.substr(0, 2) == "vn") 
		{

		}
		//Vertex position data
		else if (line.substr(0, 1) == "v") 
		{
			
		}
		//When reading the face data, you need to determine whether there is a new material. If the new material on the right means that mesh should be installed again
		else if (line.substr(0, 1) == "f") {
		}
		else if (line.substr(0, 6) == "mtllib") {
			readMTL(mtl);
		}

	}


while (std::getline(file, line)) {
    //read mtl
			if (line.substr(0, 7) == "newmtl ") {
				if (first == false) //first load
				{

				}
				else
				{

				}
				
			}
    //read mtl number
			else if (line.substr(0, 6) == "illum ") {

			}
    //read specular
			else if (line.substr(0, 3) == "Ks ") {

			}
    //read ambient
			else if (line.substr(0, 3) == "Ka ") {

			}
    //read shininess
			else if (line.substr(0, 3) == "Ns ") {

			}
    //read diffuse
			else if (line.substr(0, 3) == "Kd ") {

			}
    //read diffuse texture name
			 else if (line.substr(0, 7) == "map_Kd ") {
				
			} 
		}
Material *Module::getMaterial(std::string name)
{
	 
	for (int i = 0; i < materials.size(); i++)
	{
        //When the group name in the obj file is equal to the group name of the mtl file, the obtained material data is stored in the material.
		if (materials[i].name == name)
		{
			return &materials[i];
		}
	}
	return NULL;
}

//The acquired data is combined by material and stored in the mesh.
void Module::setUpMesh()
{
	for (int i = 0; i < meshs.size(); i++)
	{
		meshs[i].setUpMesh();
	}
}
```

![Module-h.png](https://github.com/SOFT356-Genshushu/Pic/blob/master/Module-h.png?raw=true)
##### Light module

```c++
//Enter raw lighting data including color, position and rotation angle
LightDirectional::LightDirectional(glm::vec3 _lightPositon, glm::vec3 _lightAngles, glm::vec3 _lightColor);
//User changes the light raw data
void LightDirectional::UpdataDirectional()
{
	directional = lightPosition;
	directional = glm::rotateZ(directional, lightAngles.z);
	directional = glm::rotateX(directional, lightAngles.x);
	directional = glm::rotateY(directional, lightAngles.y);
	directional = -1.0f * directional;
}
```

![LightDirectional-h.png](https://github.com/SOFT356-Genshushu/Pic/blob/master/LightDirectional-h.png?raw=true)

##### Analytic model module

```c++
//The acquired data is combined by material and stored in the mesh.
void Module::setUpMesh()
{
	for (int i = 0; i < meshs.size(); i++)
	{
		meshs[i].setUpMesh();
	}
}
void Mesh::setUpMesh()
{
	if (TriorQuad == 4)
	{
		QuadsToTrangle();//Change 4 lines to 3 lines
	}
	//create VAO
	glGenVertexArrays(1, &VAO);
	//bind VAO
	glBindVertexArray(VAO);
	//create VBO
	glGenBuffers(1, &VBO);
	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Fill data with VBO Type      Size Data Method:               Whether to change frequently, if not static
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertData.size(), &vertData[0], GL_STATIC_DRAW);
	//Value point
	glEnableVertexAttribArray(0);
	//Take data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//Value point
	glEnableVertexAttribArray(1);
	//Take data
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GL_FLOAT)));
//Value point
	glEnableVertexAttribArray(2);
//Take data
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(GL_FLOAT)));
	glBindVertexArray(0);
	//Here to read the texture binding texture
	if (material != NULL && material->texturepathname != "")
	{
		textureId = Textures::load2DTexture(material->texturepathname.c_str(), GL_RGB, GL_RGB,0);
	}
}
//Use current project
void Shader::use()
{
	glUseProgram(ProgramID);
}
//Pass variables to the fragment shader
void Shader::setUniform3f(const char* paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ProgramID, paramNameString), param.x, param.y, param.z);
}
//Pass variables to the fragment shader
void Shader::setUniform1f(const char* paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ProgramID, paramNameString), param);
}
//Pass picture to the fragment shader
void Shader::setUniform1i(const char* paramNameString, int slot)
{
	glUniform1i(glGetUniformLocation(ProgramID, paramNameString), slot);
}
//Get texture address, texture format, etc. such as rgb, png
static unsigned int load2DTexture(const char* TexturePath, GLint internalFormat, GLenum format, int textureSlot)
```

![Mesh-h.png](https://github.com/SOFT356-Genshushu/Pic/blob/master/Mesh-h.png?raw=true)

##### Rendering module

```c++
//Draw the data in the mesh group by enumeration
void Module::draw(Shader* shader)
{
	for (int i = 0; i < meshs.size(); i++)
	{
		meshs[i].drawMesh(shader);
	}
}
void Mesh::drawMesh(Shader* shader)
{
	  {
		shader->use();
		if (material != nullptr)
		{
            //Get ambient light, diffuse reflections, specular reflections, and shininess
			shader->setUniform3f("material.ambient", material->ambient);
			shader->setUniform3f("material.diffuse", material->diffues);
			shader->setUniform3f("material.specular", material->specular);
			shader->setUniform1f("material.shininess", material->shininess);
		}
		else // If there is no material, this is a default material

		{
			shader->setUniform3f("material.ambient", material->ambient);
			shader->setUniform3f("material.diffuse", material->diffues);
			shader->setUniform3f("material.specular", material->specular);
			shader->setUniform1f("material.shininess", material->shininess);
			
		}
          //Binding data for rendering
		glBindVertexArray(VAO);
          //Bind diffuse map
		glBindTexture(GL_TEXTURE_2D, textureId);
          //Pass the texture to the fragment shader via uniform
		shader->setUniform1i("tex", 0);
	  	glDrawArrays(GL_TRIANGLES, 0, vertData.size());
	 	Untied
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}
}
			//Draw a model in the render maneuver
            Creeper.draw(myShader);
			pouf.draw(myShader);
			nanosuit.draw(myShader);
			low_poly_boat.draw(myShader);
```

![Shader-h.png](https://github.com/SOFT356-Genshushu/Pic/blob/master/Shader-h.png?raw=true)



##### Parsing texture module

```c++
if (line.substr(0, 7) == "map_Kd ") {
				 std::istringstream stream(line.substr(7));
				 std::string s;
				 stream >> s;
				 //Get the diffuse map in the current material block
				 m->texturepathname = ".\\Test Model\\" + s;
			} 
//Here to get and read the texture binding texture
	if (material != NULL && material->texturepathname != "")
	{
		textureId = Textures::load2DTexture(material->texturepathname.c_str(), GL_RGB, GL_RGB,0);
	}
```

![Textures-h.png](https://github.com/SOFT356-Genshushu/Pic/blob/master/Textures-h.png?raw=true)
#### Overall Dependency Diagram

  ![DependsOn-Loader-cpp.png](https://github.com/SOFT356-Genshushu/Pic/blob/master/DependsOn-Loader-cpp.png?raw=true)