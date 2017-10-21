//#include <iostream>
//#include <string>

#include "../../Shaders/inc/ShaderSkyBox0.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::ShaderSkyBox0::ShaderSkyBox0(const char* vertexShader, const char* fragmentShader)
{
	//std::cout << "Shader_3 constructor called! " << std::endl;

	shaderProgramID = createShader(vertexShader, fragmentShader);
	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	// 
	// [ UNIFORMs ]
	//
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

Shaders::ShaderSkyBox0::~ShaderSkyBox0()
{
	std::cout << "ShaderSkyBox0 destructor called!" << std::endl;
}
//
//
// FUNCTIONs
// 
//
GLuint const Shaders::ShaderSkyBox0::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// [ ATTRIBs ] 
//
GLuint const Shaders::ShaderSkyBox0::getPositionsID() const
{
	return positionsID;
}
//
// [ UNIFORMs ]
//
GLuint const Shaders::ShaderSkyBox0::getViewMatrixID() const
{
	return viewMatrixID;
}
