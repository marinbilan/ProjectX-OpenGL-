#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_3.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_3::Shader_3(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "Shader_3 constructor called! " << std::endl;

	shaderProgramID = createShader(vertexShader, fragmentShader);
	//
	// Get Shader Variables [Attribs and Uniforms] IDs
	//
	positionsID = glGetAttribLocation(shaderProgramID, "position");

	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");
	viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");
	//
	// Set Projection Matrix
	//
	projectionMatrix = glm::perspective(glm::radians(60.0f), 1024.0f / 768.0f, 0.1f, 1000.f);

	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);
}

Shaders::Shader_3::~Shader_3()
{
	std::cout << "Shader_3 destructor called!" << std::endl;
}
//
//
// FUNCTIONs
// 
//
GLuint const Shaders::Shader_3::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// ATTRIBs
//
GLuint const Shaders::Shader_3::getPositionsID() const
{
	return positionsID;
}
//
// UNIFORMs
//
GLuint const Shaders::Shader_3::getViewMatrixID() const
{
	return viewMatrixID;
}
