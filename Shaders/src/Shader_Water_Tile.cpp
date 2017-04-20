#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_Water_Tile.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_Water_Tile::Shader_Water_Tile(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "Shader_Water_Tile constructor called! " << std::endl;

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
	lightPositionID = glGetUniformLocation(shaderProgramID, "lightPosition");
	// =============
	// FRAGMENT SHADER
	// =============
	// 
	// [ UNIFORMs ]
	//
	reflectionTextureID = glGetUniformLocation(shaderProgramID, "reflectionTexture");
	refractionTextureID = glGetUniformLocation(shaderProgramID, "refractionTexture");
	dudvMapID = glGetUniformLocation(shaderProgramID, "dudvMap");
	normalMapID = glGetUniformLocation(shaderProgramID, "normalMap");

	lightColourID = glGetUniformLocation(shaderProgramID, "lightColour");
	moveFactorID = glGetUniformLocation(shaderProgramID, "moveFactor");
	//
	// [ ATTRIBs ]
	//
	//
	// Set Projection Matrix
	//
	projectionMatrix = glm::perspective(glm::radians(60.0f), 1366.0f / 768.0f, 0.1f, 1000.f);

	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);
}

Shaders::Shader_Water_Tile::~Shader_Water_Tile()
{
	std::cout << "Shader_Water_Tile destructor called!" << std::endl;
}
//
//
// FUNCTIONs
// 
//
GLuint const Shaders::Shader_Water_Tile::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// [ ATTRIBs ]
//
GLuint const Shaders::Shader_Water_Tile::getPositionsID() const
{
	return positionsID;
}
//
// [ UNIFORMs ]
//
GLuint const Shaders::Shader_Water_Tile::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::Shader_Water_Tile::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::Shader_Water_Tile::getCameraPositionID() const
{
	return cameraPositionID;
}

GLuint const Shaders::Shader_Water_Tile::getlightPositionID() const
{
	return lightPositionID;
}

GLuint const Shaders::Shader_Water_Tile::getreflectionTextureID() const
{
	return reflectionTextureID;
}

GLuint const Shaders::Shader_Water_Tile::getrefractionTextureID() const
{
	return refractionTextureID;
}

GLuint const Shaders::Shader_Water_Tile::getdudvMapID() const
{
	return dudvMapID;
}

GLuint const Shaders::Shader_Water_Tile::getnormalMapID() const
{
	return normalMapID;
}

GLuint const Shaders::Shader_Water_Tile::getlightColorID() const
{
	return lightColourID;
}

GLuint const Shaders::Shader_Water_Tile::getmoveFactorID() const
{
	return moveFactorID;
}
