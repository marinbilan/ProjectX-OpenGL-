#include <iostream>
#include <string>

#include "../../Shaders/inc/ShaderLearningOpenGL1.h"
//
// CONSTRUCTORs / DESTRUCTORs
//
Shaders::ShaderLearningOpenGL1::ShaderLearningOpenGL1(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "ShaderPTN constructor called! " << std::endl;

    shaderProgramID = createShader(vertexShader, fragmentShader);
	// =============
	// VERTEX SHADER
	// =============
	// [ ATTRIBs ]
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	// [ UNIFORMs ]
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projection");      
	viewMatrixID = glGetUniformLocation(shaderProgramID, "view");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "model");
	// ===============
	// FRAGMENT SHADER
	// ===============
	// [ UNIFORMs ]	
	objectColorID = glGetUniformLocation(shaderProgramID, "objectColor");
	lightColorID = glGetUniformLocation(shaderProgramID, "lightColor");
	//
	// Set Projection Matrix TO DO: HEIGHT WIDTH
    // 
	projectionMatrix = glm::perspective(glm::radians(60.0f), 1366.0f / 768.0f, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);
}

Shaders::ShaderLearningOpenGL1::~ShaderLearningOpenGL1()
{
	std::cout << "ShaderPTN destructor called!" << std::endl;
}
//
//
// FUNCTIONs
//
//
GLuint const Shaders::ShaderLearningOpenGL1::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// VERTEX SHADER
//
//
// ATTRIBs
//
GLuint const Shaders::ShaderLearningOpenGL1::getPositionsID() const
{
	return positionsID;
}
//
// UNIFORMs
//
GLuint const Shaders::ShaderLearningOpenGL1::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::ShaderLearningOpenGL1::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::ShaderLearningOpenGL1::getModelMatrixID() const
{
	return modelMatrixID;
}
//
// FRAGMENT SHADER
//
GLuint const Shaders::ShaderLearningOpenGL1::getObjectColorID() const
{
	return objectColorID;
}

GLuint const Shaders::ShaderLearningOpenGL1::getLightColorID() const
{
	return lightColorID;
}