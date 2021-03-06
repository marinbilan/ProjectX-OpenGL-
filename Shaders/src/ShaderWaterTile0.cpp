#include "../../Shaders/inc/ShaderWaterTile0.h"

// CONSTRUCTORs / DESTRUCTORs
Shaders::ShaderWaterTile0::ShaderWaterTile0(const char* vertexShader, const char* fragmentShader)
{
	shaderProgramID = createShader(vertexShader, fragmentShader);

	// VERTEX SHADER
	// [ ATTRIBs ]
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	// [ UNIFORMs ]
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");
	viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "modelMatrix");
	cameraPositionID = glGetUniformLocation(shaderProgramID, "cameraPosition");
	lightPositionID = glGetUniformLocation(shaderProgramID, "lightPosition");

	// FRAGMENT SHADER
	// [ UNIFORMs ]
	reflectionTextureID = glGetUniformLocation(shaderProgramID, "reflectionTexture");
	refractionTextureID = glGetUniformLocation(shaderProgramID, "refractionTexture");
	dudvMapID = glGetUniformLocation(shaderProgramID, "dudvMap");
	normalMapID = glGetUniformLocation(shaderProgramID, "normalMap");
	lightColourID = glGetUniformLocation(shaderProgramID, "lightColour");
	moveFactorID = glGetUniformLocation(shaderProgramID, "moveFactor");

	// Set Projection Matrix
	projectionMatrix = glm::perspective(glm::radians(60.0f), 1366.0f / 768.0f, 0.1f, 1000.f);

	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);

	std::cout << "ShaderWaterTile created!" << std::endl;
}

Shaders::ShaderWaterTile0::~ShaderWaterTile0()
{
	std::cout << "ShaderWaterTile0 destructor called!" << std::endl;
}

// FUNCTIONs
GLuint const Shaders::ShaderWaterTile0::getShaderProgramID() const
{
	return shaderProgramID;
}
// [ ATTRIBs ]
GLuint const Shaders::ShaderWaterTile0::getPositionsID() const
{
	return positionsID;
}
// [ UNIFORMs ]
GLuint const Shaders::ShaderWaterTile0::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::ShaderWaterTile0::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::ShaderWaterTile0::getCameraPositionID() const
{
	return cameraPositionID;
}

GLuint const Shaders::ShaderWaterTile0::getLightPositionID() const
{
	return lightPositionID;
}

GLuint const Shaders::ShaderWaterTile0::getReflectionTextureID() const
{
	return reflectionTextureID;
}

GLuint const Shaders::ShaderWaterTile0::getRefractionTextureID() const
{
	return refractionTextureID;
}

GLuint const Shaders::ShaderWaterTile0::getDudvMapID() const
{
	return dudvMapID;
}

GLuint const Shaders::ShaderWaterTile0::getNormalMapID() const
{
	return normalMapID;
}

GLuint const Shaders::ShaderWaterTile0::getLightColorID() const
{
	return lightColourID;
}

GLuint const Shaders::ShaderWaterTile0::getMoveFactorID() const
{
	return moveFactorID;
}
