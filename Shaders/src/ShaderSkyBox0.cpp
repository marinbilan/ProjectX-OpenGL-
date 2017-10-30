#include "../../Shaders/inc/ShaderSkyBox0.h"

// CONSTRUCTORs / DESTRUCTORs
Shaders::ShaderSkyBox0::ShaderSkyBox0(GLfloat projMatrixWidth, GLfloat projMatrixHeight)
{
	shaderName = "ShaderSkyBox0";

	shaderProgramID = createShader(vertexShader, fragmentShader);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	//   UNIFORMs
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");
	viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");

	// Set Projection Matrix
	projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);

	std::cout << "ShaderSkyBox0 created!" << std::endl;
}

Shaders::ShaderSkyBox0::~ShaderSkyBox0()
{
	std::cout << "ShaderSkyBox0 destructor called!" << std::endl;
}
// FUNCTIONs
std::string Shaders::ShaderSkyBox0::getShaderName()
{
	return shaderName;
}

GLuint const Shaders::ShaderSkyBox0::getShaderProgramID() const
{
	return shaderProgramID;
}

GLuint const Shaders::ShaderSkyBox0::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::ShaderSkyBox0::getViewMatrixID() const
{
	return viewMatrixID;
}
// OPERATORs
void Shaders::ShaderSkyBox0::printINFO()
{
	std::cout << *this;
}