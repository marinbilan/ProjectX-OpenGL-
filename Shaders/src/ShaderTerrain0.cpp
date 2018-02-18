#include "../../Shaders/inc/ShaderTerrain0.h"

// CONSTRUCTORs / DESTRUCTORs
Shaders::ShaderTerrain0::ShaderTerrain0(GLfloat projMatrixWidth, GLfloat projMatrixHeight)
{
	shaderName = "ShaderTerrain0";

    shaderProgramID = createShader(vertexShader, fragmentShader);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	textureCoordsID = glGetAttribLocation(shaderProgramID, "textureCoords");
	normalsID = glGetAttribLocation(shaderProgramID, "normal");
	//   UNIFORMs
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");      
	viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");
	viewMatrixInvID = glGetUniformLocation(shaderProgramID, "viewMatrixInv");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");

	lightPositionID = glGetUniformLocation(shaderProgramID, "lightPosition");
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	backgroundTextureID = glGetUniformLocation(shaderProgramID, "backgroundTexture");
	rTextureID = glGetUniformLocation(shaderProgramID, "rTexture");
	gTextureID = glGetUniformLocation(shaderProgramID, "gTexture");
	bTextureID = glGetUniformLocation(shaderProgramID, "bTexture");
	blendMapID = glGetUniformLocation(shaderProgramID, "blendMap");

	lightColorID = glGetUniformLocation(shaderProgramID, "lightColor");
	shineDamperID = glGetUniformLocation(shaderProgramID, "shineDamper");
	reflectivityID = glGetUniformLocation(shaderProgramID, "reflectivity");

	// Set Projection Matrix
	projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);

	std::cout << "ShaderTerrain0 created!" << std::endl;
}

Shaders::ShaderTerrain0::~ShaderTerrain0()
{
	std::cout << "ShaderTerrain0 destructor called!" << std::endl;
}
// FUNCTIONs
std::string Shaders::ShaderTerrain0::getShaderName()
{
	return shaderName;
}

GLuint const Shaders::ShaderTerrain0::getShaderProgramID() const
{
	return shaderProgramID;
}

GLuint const Shaders::ShaderTerrain0::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::ShaderTerrain0::getTextureCoordsID() const
{
	return textureCoordsID;
}

GLuint const Shaders::ShaderTerrain0::getNormalsID() const
{
	return normalsID;
}

GLuint const Shaders::ShaderTerrain0::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::ShaderTerrain0::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::ShaderTerrain0::getViewMatrixInvID() const
{
	return viewMatrixInvID;
}

GLuint const Shaders::ShaderTerrain0::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::ShaderTerrain0::getLightPositionID() const
{
	return lightPositionID;
}
// FRAGMENT SHADER
GLuint const Shaders::ShaderTerrain0::getBackgroundTextureID() const
{
	return backgroundTextureID;
}

GLuint const Shaders::ShaderTerrain0::getRTextureID() const
{
	return rTextureID;
}

GLuint const Shaders::ShaderTerrain0::getGTextureID() const
{
	return gTextureID;
}

GLuint const Shaders::ShaderTerrain0::getBTextureID() const
{
	return bTextureID;
}

GLuint const Shaders::ShaderTerrain0::getBlendMapID() const
{
	return blendMapID;
}

GLuint const Shaders::ShaderTerrain0::getLightColorID() const
{
	return lightColorID;
}

GLuint const Shaders::ShaderTerrain0::getShineDamperID() const
{
	return shineDamperID;
}

GLuint const Shaders::ShaderTerrain0::getReflectivityID() const
{
	return reflectivityID;
}
// OPERATORs
void Shaders::ShaderTerrain0::printINFO()
{
	std::cout << *this;
}