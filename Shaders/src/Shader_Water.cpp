#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_Water.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_Water::Shader_Water(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "Shader_Water constructor called! " << std::endl;

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
	modelMatrixID = glGetUniformLocation(shaderProgramID, "modelMatrix");
	cameraPositionID = glGetUniformLocation(shaderProgramID, "cameraPosition");
	// ===============
	// FRAGMENT SHADER
	// ===============
	//
	// [ UNIFORMs ]
	//		
	reflectionTextureID = glGetUniformLocation(shaderProgramID, "reflectionTexture");
	refractionTextureID = glGetUniformLocation(shaderProgramID, "refractionTexture");
	dudvMapID = glGetUniformLocation(shaderProgramID, "dudvMap");

	moveFactorID = glGetUniformLocation(shaderProgramID, "moveFactor");
	//
	// Set Projection Matrix TO DO: HEIGHT WIDTH
    // 
	projectionMatrix = glm::perspective(glm::radians(60.0f), 1366.0f / 768.0f, 0.1f, 1000.f);

	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);
}

Shaders::Shader_Water::~Shader_Water()
{
	std::cout << "Shader_Water destructor called!" << std::endl;
}
//
//
// FUNCTIONs
//
//
GLuint const Shaders::Shader_Water::getShaderProgramID() const
{
	return shaderProgramID;
}

// =============
// VERTEX SHADER
// =============

GLuint const Shaders::Shader_Water::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::Shader_Water::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::Shader_Water::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::Shader_Water::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::Shader_Water::getCameraPositionID() const
{
	return cameraPositionID;
}

// ===============
// FRAGMENT SHADER
// ===============

GLuint const Shaders::Shader_Water::getreflectionTextureID() const
{
	return reflectionTextureID;
}

GLuint const Shaders::Shader_Water::getrefractionTextureID() const
{
	return refractionTextureID;
}

GLuint const Shaders::Shader_Water::getdudvMapID() const
{
	return dudvMapID;
}

GLuint const Shaders::Shader_Water::getmoveFactorID() const
{
	return moveFactorID;
}


