#version 330 core
// Model vertex data
layout (location = 0) in vec3 Position;	
// Model texture data
layout (location = 1) in vec2 texCoord;
// Model normal data
layout (location = 2) in vec3 Normal;

//Model projection
uniform mat4 projMat;
//Model view
uniform mat4 viewMat;
//Model
uniform mat4 modelMat;
//Transfer mapping coordinates to fragment shader
out vec2 TextCoord;
//Transfer vertex coordinates to fragment shader
out vec3 fragPos;
//Transfer normal coordinates to fragment shader
out vec3 aNormal;

void main()
{
	//The position of the model in 3D space
	fragPos=(modelMat * vec4(Position.xyz, 1.0)).xyz;
	//texture 
	TextCoord = texCoord;
	//normal
	aNormal=mat3(transpose(inverse(modelMat))) * Normal;
	//Three-dimensional space
	gl_Position = projMat * viewMat * modelMat * vec4(Position.xyz, 1.0);
}