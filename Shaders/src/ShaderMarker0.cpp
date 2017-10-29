#include "../../Shaders/inc/ShaderMarker0.h"

// CONSTRUCTORs / DESTRUCTORs
Shaders::ShaderMarker0::ShaderMarker0(GLfloat projMatrixWidth, GLfloat projMatrixHeight)
{
	shaderName = "ShaderMarker0";

    shaderProgramID = createShader(vertexShader, fragmentShader);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	//   UNIFORMs
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projection");      
	viewMatrixID = glGetUniformLocation(shaderProgramID, "view");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "model");
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	objectColorID = glGetUniformLocation(shaderProgramID, "objectColor");
	lightColorID = glGetUniformLocation(shaderProgramID, "lightColor");

	// Set Projection Matrix
	projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);

	std::cout << "ShaderMarker0 object created!" << std::endl;
}

Shaders::ShaderMarker0::~ShaderMarker0()
{
	std::cout << "ShaderMarker0 destructor called!" << std::endl;
}
// FUNCTIONs
std::string Shaders::ShaderMarker0::getShaderName()
{
	return shaderName;
}

GLuint const Shaders::ShaderMarker0::getShaderProgramID() const
{
	return shaderProgramID;
}

GLuint const Shaders::ShaderMarker0::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::ShaderMarker0::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::ShaderMarker0::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::ShaderMarker0::getModelMatrixID() const
{
	return modelMatrixID;
}
// FRAGMENT SHADER
GLuint const Shaders::ShaderMarker0::getObjectColorID() const
{
	return objectColorID;
}

GLuint const Shaders::ShaderMarker0::getLightColorID() const
{
	return lightColorID;
}

// OPERATORs
void Shaders::ShaderMarker0::printINFO()
{
	std::cout << *this;
}