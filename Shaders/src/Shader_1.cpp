#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_1.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_1::Shader_1(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "Shader_1 constructor called! " << std::endl;

	shaderProgramID = createShader(vertexShader, fragmentShader);
	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	positionsID = glGetAttribLocation(shaderProgramID, "s_vPosition");
	normalsID = glGetAttribLocation(shaderProgramID, "s_vNormal");
	// 
	// [ UNIFORMs ]
	//
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "mP");       	
	viewMatrixID = glGetUniformLocation(shaderProgramID, "mV");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "mM");

	lightID = glGetUniformLocation(shaderProgramID, "vLight");
	normalsRotationsMatrixID = glGetUniformLocation(shaderProgramID, "mRotations");
	//
	// Set Projection Matrix
	//
	projectionMatrix = glm::perspective(glm::radians(60.0f), 1024.0f / 768.0f, 0.1f, 1000.f);

	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);
}

Shaders::Shader_1::~Shader_1()
{
	std::cout << "Shader_1 destructor called!" << std::endl;
}
//
//
// FUNCTIONs
//
//
GLuint const Shaders::Shader_1::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// [ ATTRIBs ]
//
GLuint const Shaders::Shader_1::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::Shader_1::getNormalsID() const
{
	return normalsID;
}
//
// [ UNIFORMs ]
//
GLuint const Shaders::Shader_1::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::Shader_1::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::Shader_1::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::Shader_1::getLightID() const
{
	return lightID;
}

GLuint const Shaders::Shader_1::getNormalsRotationsID() const
{
	return normalsRotationsMatrixID;
}

