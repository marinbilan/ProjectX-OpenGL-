#include "../../Shaders/inc/ShaderLearningOpenGL0.h"

// CONSTRUCTORs / DESTRUCTORs
Shaders::ShaderLearningOpenGL0::ShaderLearningOpenGL0(GLfloat projMatrixWidth, GLfloat projMatrixHeight)
{
	shaderName = "ShaderLearningOpenGL0";

    shaderProgramID = createShader(vertexShader3, fragmentShader3);
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
	viewPositionID = glGetUniformLocation(shaderProgramID, "viewPos");
	lightColorID = glGetUniformLocation(shaderProgramID, "lightColor");
	objectColorID = glGetUniformLocation(shaderProgramID, "objectColor");

	materialAmbientID = glGetUniformLocation(shaderProgramID, "material.ambient");
	materialDiffuseID = glGetUniformLocation(shaderProgramID, "material.diffuse");
	materialSpecularID = glGetUniformLocation(shaderProgramID, "material.specular");
	matrialShininessID = glGetUniformLocation(shaderProgramID, "material.shininess");

	lightPositionID = glGetUniformLocation(shaderProgramID, "light.position");
	lightAmbientID = glGetUniformLocation(shaderProgramID, "light.ambient");
	lightDiffuseID = glGetUniformLocation(shaderProgramID, "light.diffuse");
	lightSpecularID = glGetUniformLocation(shaderProgramID, "light.specular");

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
GLuint const Shaders::ShaderLearningOpenGL0::getCameraPositionID() const
{
	return viewPositionID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getLightColorID() const
{
	return lightColorID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getObjectColorID() const
{
	return objectColorID;
}

// MATERIALs
GLuint const Shaders::ShaderLearningOpenGL0::getMaterialAmbientID() const
{
	return materialAmbientID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getMaterialDiffuseID() const
{
	return materialDiffuseID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getMaterialSpecularID() const
{
	return materialSpecularID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getMaterialShininessID() const
{
	return matrialShininessID;
}
// LIGHTs
GLuint const Shaders::ShaderLearningOpenGL0::getLightPositionID() const
{
	return lightPositionID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getLightAmbientID() const
{
	return lightAmbientID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getLightDiffuseID() const
{
	return lightDiffuseID;
}

GLuint const Shaders::ShaderLearningOpenGL0::getLightSpecularID() const
{
	return lightSpecularID;
}
// OPERATORs
void Shaders::ShaderLearningOpenGL0::printINFO()
{
	std::cout << *this;
}