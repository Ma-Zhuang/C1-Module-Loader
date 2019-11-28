//Defining a static library for glew
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"Shader.h"
#include<glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include"Camera.h"
//#include"Textures.h"
#include<vector>
#include "Mesh.h"
#include"Module.h"
#include"Material.h"
#include"LightDirectional.h"
Module Creeper = Module();
Module pouf = Module();
Module nanosuit = Module();
Module low_poly_boat = Module();
int model;
//Record the position information of the last time in the x-axis direction of the mouse
float lastX;
//Record the position information of the last time in the Y direction of the mouse
float lastY;
//Determine whether the mouse position is the first load
bool firstMouse = true;
//Input camera world space position, angle
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//Enter the position, color, rotation of the parallel light
LightDirectional lightdirectional = LightDirectional(glm::vec3(-2.0f, 1.0f, 1.0f), glm::vec3(glm::radians(189.0f), 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));

//Mouse movement
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	//Determine whether the mouse is loaded for the first time
	if (firstMouse == true) {
		//Mouse coordinates are camera coordinates
		lastX = xPos;
		lastY = yPos;
		//Loading the mouse is not the first time
		firstMouse = false;
	}
	//Offset of mouse movement
	float deltaX, deltaY;
	//X-axis movement
	deltaX = xPos - lastX;
	//Move in Y direction
	deltaY = yPos - lastY;
	//The coordinates of the point on the mouse are the coordinates after the move
	lastX = xPos;
	lastY = yPos;
	//Change camera position by mouse movement
	camera.ProcessMouseMovement(deltaX, deltaY);
}
//Keyboard input
void processInput(GLFWwindow* window) {
	//Push out procedure when ESC is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		//Close program
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		model = 1;
	}
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		model = 2;
	}
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		model = 3;
	}
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		model = 4;
	}
	else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		model = 5;
	}
	else if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
		model = 9;
	}
	//Camera advances when q is pressed
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		//Camera moves in the positive direction of Z axis
		camera.speedZ = 0.1f;
	}
	//Camera advances when e is pressed
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		//Camera moves in the negative Z direction
		camera.speedZ = -0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.speedX = -0.1f;
	}
	//Camera advances when D is pressed
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//Camera moves in the positive X-axis direction
		camera.speedX = 0.1f;
	}
	//Camera advances when w is pressed
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//Camera moves in the negative Y direction
		camera.speedY = 0.1f;
	}
	//Camera advances when s is pressed
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		//Camera moves in the positive direction of Y axis
		camera.speedY = -0.1f;
	}
	//When not moving
	else {
		//Camera x, y, Z moving distance is 0
		camera.speedZ = 0;
		camera.speedX = 0;
		camera.speedY = 0;
	}
}
int main() {
	//Initialize glfw
	glfwInit();
	//Confirm OpenGL version number Version:4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//Set OpenGL operation mode to core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Create a form with the size of 1024 * 768 and the name of "Module Loader(Zhuang Ma 10664074)"
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Module Loader(Zhuang Ma 10664074)", NULL, NULL);
	//Determine whether the form is loaded successfully
	if (window==NULL)
	{
		std::cout << "Window Load Failed!!" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Confirm context
	glfwMakeContextCurrent(window);
	//Hide Mouse Icon
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Call mouse move function
	glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//Allow loading of extension entry points
	glewExperimental = true;
	//Judge whether the glue initialization is successful
	if (glewInit() != GLEW_OK) {
		printf("Init GLEW ERROR");
		glfwTerminate();
		return -1;
	}
	
	//Set view size
	glViewport(0, 0, 1024, 768);
	//Read VertexShader and FragmentShader
	Shader* myShader = new Shader("VertexShader.vert", "FragmentShader.frag");

	nanosuit.Moduleload(".\\Test Model\\nanosuit.obj");
	//Load the read obj model data into mesh
	nanosuit.setUpMesh();

	//Read obj modle
	pouf.Moduleload(".\\Test Model\\pouf.obj");
	//Load the read obj model data into mesh
	pouf.setUpMesh();

	//Read obj modle
	low_poly_boat.Moduleload(".\\Test Model\\low_poly_boat.obj");
	//Load the read obj model data into mesh
	low_poly_boat.setUpMesh();

	//Read obj modle
	Creeper.Moduleload(".\\Test Model\\Creeper.obj");
	//Load the read obj model data into mesh
	Creeper.setUpMesh();

	//Opening depth test
	glEnable(GL_DEPTH_TEST);
	//Enable back culling
 	glEnable(GL_CULL_FACE);
	//Don't render model Bei
 	glCullFace(GL_BACK);

	//Define a unit matrix
	glm::mat4 modelMat = glm::mat4(1.0f);
	
	glm::mat4 viewMat = glm::mat4(1.0f);

	glm::mat4 projMat = glm::mat4(1.0f);
	//Set the far and near surface, 0.1f in and out, 1000.0f in the distance
	projMat = glm::perspective(glm::radians(40.0f), 1024.0f / 768.0f, 0.1f, 1000.0f);
	/*Render Loop
	Function to check whether glfw is required to exit before the start of each cycle.*/
	while (!glfwWindowShouldClose(window))
	{
		//Keyboard entry
		processInput(window);
		//Form background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//Clean screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Check whether there are any events triggered (such as keyboard input, mouse movement, etc.)
		viewMat = camera.GetViewMatrix();
		//Applying vertex shader and fragment shader
		myShader->use();
		//Passing angle to fragment shader through uniform
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		//Pass the model color to fragment shader and default to white
		glUniform3f(glGetUniformLocation(myShader->ProgramID, "objColor"), 1.0f, 1.0f, 1.0f);
		//Pass enverinment color to fragment shader and default to white
		glUniform3f(glGetUniformLocation(myShader->ProgramID, "ambientColor"), 0.5f, 0.5f, 0.5f);
		
		
		//Pass the position, color and direction of the flat light source to the fragment shader
		glUniform3f(glGetUniformLocation(myShader->ProgramID, "lightD.pos"), lightdirectional.lightPosition.x, lightdirectional.lightPosition.y, lightdirectional.lightPosition.z);
		glUniform3f(glGetUniformLocation(myShader->ProgramID, "lightD.color"), lightdirectional.lightColor.x, lightdirectional.lightColor.y, lightdirectional.lightColor.z);
		glUniform3f(glGetUniformLocation(myShader->ProgramID, "lightD.dirToLigth"), lightdirectional.directional.x, lightdirectional.directional.y, lightdirectional.directional.z);
		//Passing camera position to fragment shader
	 	glUniform3f(glGetUniformLocation(myShader->ProgramID, "cameraPos"), camera.cameraPosition.x, camera.cameraPosition.y, camera.cameraPosition.z);
		switch (model)
		{
		case 1:
			Creeper.draw(myShader);
			break;
		case 2:
			pouf.draw(myShader);
			break;
		case 3:
			nanosuit.draw(myShader);
			break;
		case 4:
			low_poly_boat.draw(myShader);
			break;
		case 5:
			Creeper.draw(myShader);
			pouf.draw(myShader);
			nanosuit.draw(myShader);
			low_poly_boat.draw(myShader);
			break;
		case 9:
			break;
		default:
			pouf.draw(myShader);
		}
		//Swap color buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
		camera.UpdataCameraPos();
	}
	//clear second obj model
	Creeper.~Module();
	pouf.~Module();
	nanosuit.~Module();
	low_poly_boat.~Module();
	glfwTerminate();
	return 0;
}