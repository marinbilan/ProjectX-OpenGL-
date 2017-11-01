#include "../../Shaders/inc/ShaderLearningOpenGL0.h"

// CONSTRUCTORs / DESTRUCTORs
Shaders::ShaderLearningOpenGL0::ShaderLearningOpenGL0(GLfloat projMatrixWidth, GLfloat projMatrixHeight)
{
	shaderName = "ShaderLearningOpenGL0";

    shaderProgramID = createShader(vertexShader1, fragmentShader1);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	positionsID = glGetAttribLocation(shaderProgramID, "aPos");
	normalsID = glGetAttribLocation(shaderProgramID, "aNormal");
	//   UNIFORMs
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projection");      
	viewMatrixID = glGetUniformLocation(shaderProgramID, "view");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "model");
	modelMatrixInvID = glGetUniformLocation(shaderProgramID, "modelInv");
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	lightPositionID = glGetUniformLocation(shaderProgramID, "lightPos");
	lightColorID = glGetUniformLocation(shaderProgramID, "lightColor");
	objectColorID = glGetUniformLocation(shaderProgramID, "objectColor");

	// Set Projection Matrix
	projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);

	std::cout << "ShaderLearningOpenGL0 created!" << std::endl;
}

Shaders::ShaderLearningOpenGL0::~ShaderLearningOpenGL0()
{
	std::cout << "ShaderPTN destructor called!" << std::endl;
}
// FUNCTIONs
std::string Shaders::ShaderLearningOpenGL0::getShaderName()
{
	return shaderName;
}

GLuint const Shaders::ShaderLearningOpenGL0::getShaderProgramID() const
{
	return shaderProgramID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getModelMatrixInvID() const
{
	return modelMatrixInvID;
}
// FRAGMENT SHADER
GLuint const Shaders::ShaderLearningOpenGL0::getLightPositionID() const
{
	return lightPositionID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getLightColorID() const
{
	return lightColorID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getObjectColorID() const
{
	return objectColorID;
}

// OPERATORs
void Shaders::ShaderLearningOpenGL0::printINFO()
{
	std::cout << *this;
}