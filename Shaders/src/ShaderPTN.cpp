#include <iostream>
#include <string>

#include "../../Shaders/inc/ShaderPTN.h"
//
// CONSTRUCTORs / DESTRUCTORs
//
Shaders::ShaderPTN::ShaderPTN(std::string _shaderName, const char* vertexShader, const char* fragmentShader)
{
	std::cout << "ShaderPTN constructor called! " << std::endl;
	shaderName = "shaderPTN1"; // Hardcoded shader name
    shaderProgramID = createShader(vertexShader, fragmentShader);
	// =============
	// VERTEX SHADER
	// =============
	// [ ATTRIBs ]
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	textureCoordsID = glGetAttribLocation(shaderProgramID, "textureCoordinates");
	normalsID = glGetAttribLocation(shaderProgramID, "normal");
	// [ UNIFORMs ]
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");      
	viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");
	viewMatrixInvID = glGetUniformLocation(shaderProgramID, "viewMatrixInv");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");
	lightPositionID = glGetUniformLocation(shaderProgramID, "lightPosition");
	planeID = glGetUniformLocation(shaderProgramID, "plane");
	// ===============
	// FRAGMENT SHADER
	// ===============
	// [ UNIFORMs ]	
	lightColourID = glGetUniformLocation(shaderProgramID, "lightColour");
	shineDamperID = glGetUniformLocation(shaderProgramID, "shineDamper");
	reflectivityID = glGetUniformLocation(shaderProgramID, "reflectivity");
	modelTextureID = glGetUniformLocation(shaderProgramID, "modelTexture");
	//
	// Set Projection Matrix TO DO: HEIGHT WIDTH
    // 
	projectionMatrix = glm::perspective(glm::radians(60.0f), 1366.0f / 768.0f, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);
}

Shaders::ShaderPTN::~ShaderPTN()
{
	std::cout << "ShaderPTN destructor called!" << std::endl;
}
//
//
// FUNCTIONs
//
//
std::string Shaders::ShaderPTN::getShaderName()
{
	return shaderName;
}

GLuint const Shaders::ShaderPTN::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// VERTEX SHADER
//
//
// ATTRIBs
//
GLuint const Shaders::ShaderPTN::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::ShaderPTN::getTextureCoordsID() const
{
	return textureCoordsID;
}

GLuint const Shaders::ShaderPTN::getNormalsID() const
{
	return normalsID;
}
//
// UNIFORMs
//
GLuint const Shaders::ShaderPTN::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::ShaderPTN::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::ShaderPTN::getViewMatrixInvID() const
{
	return viewMatrixInvID;
}

GLuint const Shaders::ShaderPTN::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::ShaderPTN::getLightID() const
{
	return lightPositionID;
}

GLuint const Shaders::ShaderPTN::getplaneID() const
{
	return planeID;
}
//
// FRAGMENT SHADER
//
GLuint const Shaders::ShaderPTN::getlightColorID() const
{
	return lightColourID;
}

GLuint const Shaders::ShaderPTN::getshineDamperID() const
{
	return shineDamperID;
}

GLuint const Shaders::ShaderPTN::getreflectivityID() const
{
	return reflectivityID;
}

GLuint const Shaders::ShaderPTN::getmodelTextureID() const
{
	return modelTextureID;
}