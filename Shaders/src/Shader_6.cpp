#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_6.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_6::Shader_6(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "Shader_6 constructor called! " << std::endl;

    shaderProgramID = createShader(vertexShader, fragmentShader);
	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	normalsID = glGetAttribLocation(shaderProgramID, "normal");
	textureCoordsID = glGetAttribLocation(shaderProgramID, "textureCoordinates");
	// 
	// [ UNIFORMs ]
	//
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");      
	modelMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");
	viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");
	viewMatrixInvID = glGetUniformLocation(shaderProgramID, "viewMatrixInv");

	lightPositionID = glGetUniformLocation(shaderProgramID, "lightPosition");
	// ===============
	// FRAGMENT SHADER
	// ===============
	//
	// [ UNIFORMs ]
	//		
	modelTextureID = glGetUniformLocation(shaderProgramID, "modelTexture");
	lightColourID = glGetUniformLocation(shaderProgramID, "lightColour");
	shineDamperID = glGetUniformLocation(shaderProgramID, "shineDamper");
	reflectivityID = glGetUniformLocation(shaderProgramID, "reflectivity");
	//
	// Set Projection Matrix TO DO: HEIGHT WIDTH
    // 
	projectionMatrix = glm::perspective(glm::radians(60.0f), 1366.0f / 768.0f, 0.1f, 1000.f);

	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);
}

Shaders::Shader_6::~Shader_6()
{
	std::cout << "Shader_6 destructor called!" << std::endl;
}
//
//
// FUNCTIONs
//
//
GLuint const Shaders::Shader_6::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// ATTRIBs
//
GLuint const Shaders::Shader_6::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::Shader_6::getNormalsID() const
{
	return normalsID;
}

GLuint const Shaders::Shader_6::getTextureCoordsID() const
{
	return textureCoordsID;
}
//
// UNIFORMs
//
GLuint const Shaders::Shader_6::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::Shader_6::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::Shader_6::getViewMatrixInvID() const
{
	return viewMatrixInvID;
}

GLuint const Shaders::Shader_6::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::Shader_6::getmodelTextureID() const
{
	return modelTextureID;
}

GLuint const Shaders::Shader_6::getLightID() const
{
	return lightPositionID;
}

GLuint const Shaders::Shader_6::getlightColorID() const
{
	return lightColourID;
}

GLuint const Shaders::Shader_6::getshineDamperID() const
{
	return shineDamperID;
}

GLuint const Shaders::Shader_6::getreflectivityID() const
{
	return reflectivityID;
}

