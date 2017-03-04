#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_5.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_5::Shader_5(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "Shader_cube constructor called! " << std::endl;

    shaderProgramID = createShader(vertexShader, fragmentShader);
	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	positionsID = glGetAttribLocation(shaderProgramID, "s_vPosition");
	normalsID = glGetAttribLocation(shaderProgramID, "s_vNormal");
	textureCoordsID = glGetAttribLocation(shaderProgramID, "s_vTexCoord");
	// 
	// [ UNIFORMs ]
	//        
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "mP");
	viewMatrixID = glGetUniformLocation(shaderProgramID, "mV");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "mM");

	lightID = glGetUniformLocation(shaderProgramID, "vLight");
	normalsRotationsMatrixID = glGetUniformLocation(shaderProgramID, "mRotations");
	// ===============
	// FRAGMENT SHADER
	// ===============
	//
	// [ UNIFORMs ]
	//		
	textureSamplerID = glGetUniformLocation(shaderProgramID, "texture");
	//
	// Set Projection Matrix
    //
	glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(60.0f), 1024.0f / 768.0f, 0.1f, 1000.f);

	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &ProjectionMatrix[0][0]);
	glUseProgram(0);
}

Shaders::Shader_5::~Shader_5()
{
	std::cout << "Shader_2 destructor called!" << std::endl;
}
//
//
// FUNCTIONs
//
//
GLuint const Shaders::Shader_5::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// ATTRIBs
//
GLuint const Shaders::Shader_5::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::Shader_5::getNormalsID() const
{
	return normalsID;
}

GLuint const Shaders::Shader_5::getTextureCoordsID() const
{
	return textureCoordsID;
}
//
// UNIFORMs
//
GLuint const Shaders::Shader_5::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::Shader_5::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::Shader_5::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::Shader_5::getLightID() const
{
	return lightID;
}

GLuint const Shaders::Shader_5::getNormalsRotationsID() const
{
	return normalsRotationsMatrixID;
}

GLuint const Shaders::Shader_5::gettextureSamplerID() const
{
	return textureSamplerID;
}
