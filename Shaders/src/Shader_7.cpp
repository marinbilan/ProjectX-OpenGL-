#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_7.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_7::Shader_7(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "Shader_7 constructor called! " << std::endl;

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
	tangentID = glGetAttribLocation(shaderProgramID, "tangent");
	// 
	// [ UNIFORMs ]
	//      
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");
	viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");
	viewMatrixInvID = glGetUniformLocation(shaderProgramID, "viewMatrixInv");

	lightPositionID = glGetUniformLocation(shaderProgramID, "lightPositionEyeSpace");	
	// ===============
	// FRAGMENT SHADER
	// ===============
	//
	// [ UNIFORMs ]
	//		
	modelTextureID = glGetUniformLocation(shaderProgramID, "modelTexture");
	normalMapID = glGetUniformLocation(shaderProgramID, "normalMap"); // TO DO: Bind to texture UNIT 1! Rendering Unit glBindTexture(TEXTURE2D, getnormalMapID())

	lightColourID = glGetUniformLocation(shaderProgramID, "lightColour");	
	shineDamperID = glGetUniformLocation(shaderProgramID, "shineDamper");
	reflectivityID = glGetUniformLocation(shaderProgramID, "reflectivity");
	//
	// Set Projection Matrix
    //
	projectionMatrix = glm::perspective(glm::radians(60.0f), 1366.0f / 768.0f, 0.1f, 1000.f);

	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);
}

Shaders::Shader_7::~Shader_7()
{
	std::cout << "Shader_7 destructor called!" << std::endl;
}
//
//
// FUNCTIONs
//
//
GLuint const Shaders::Shader_7::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// ATTRIBs
//
GLuint const Shaders::Shader_7::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::Shader_7::getNormalsID() const
{
	return normalsID;
}

GLuint const Shaders::Shader_7::getTextureCoordsID() const
{
	return textureCoordsID;
}

GLuint const Shaders::Shader_7::getTangentsID() const
{
	return tangentID;
}
//
// UNIFORMs
//
GLuint const Shaders::Shader_7::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::Shader_7::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::Shader_7::getViewMatrixInvID() const
{
	return viewMatrixInvID;
}

GLuint const Shaders::Shader_7::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::Shader_7::getmodelTextureID() const
{
	return modelTextureID;
}

GLuint const Shaders::Shader_7::getnormalMapID() const
{
	return normalMapID;
}

GLuint const Shaders::Shader_7::getLightID() const
{
	return lightPositionID;
}

GLuint const Shaders::Shader_7::getViewPosID() const
{
	return viewPosID;
}

GLuint const Shaders::Shader_7::getlightColorID() const
{
	return lightColourID;
}

GLuint const Shaders::Shader_7::getshineDamperID() const
{
	return shineDamperID;
}

GLuint const Shaders::Shader_7::getreflectivityID() const
{
	return reflectivityID;
}

