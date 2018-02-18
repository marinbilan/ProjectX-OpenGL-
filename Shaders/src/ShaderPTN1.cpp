#include "../../Shaders/inc/ShaderPTN1.h"
//
// CONSTRUCTORs / DESTRUCTORs
//
Shaders::ShaderPTN1::ShaderPTN1(GLfloat projMatrixWidth, GLfloat projMatrixHeight)
{
	shaderName = "ShaderPTN1"; // Hardcoded shader name
    shaderProgramID = createShader(VertexShaderPTN, FragmentShaderPTN);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
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
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	lightColourID = glGetUniformLocation(shaderProgramID, "lightColour");
	shineDamperID = glGetUniformLocation(shaderProgramID, "shineDamper");
	reflectivityID = glGetUniformLocation(shaderProgramID, "reflectivity");
	modelTextureID = glGetUniformLocation(shaderProgramID, "modelTexture");
	specularMapID = glGetUniformLocation(shaderProgramID, "specularMap");
	//
	// Set Projection Matrix
    // 
	projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);

	std::cout << "ShaderPTN1 created!" << std::endl;
}

Shaders::ShaderPTN1::~ShaderPTN1()
{
	std::cout << "ShaderPTN1 destructor called!" << std::endl;
}
// FUNCTIONs
std::string Shaders::ShaderPTN1::getShaderName()
{
	return shaderName;
}

GLuint const Shaders::ShaderPTN1::getShaderProgramID() const
{
	return shaderProgramID;
}

GLuint const Shaders::ShaderPTN1::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::ShaderPTN1::getTextureCoordsID() const
{
	return textureCoordsID;
}

GLuint const Shaders::ShaderPTN1::getNormalsID() const
{
	return normalsID;
}

GLuint const Shaders::ShaderPTN1::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::ShaderPTN1::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::ShaderPTN1::getViewMatrixInvID() const
{
	return viewMatrixInvID;
}

GLuint const Shaders::ShaderPTN1::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::ShaderPTN1::getLightPositionID() const
{
	return lightPositionID;
}

GLuint const Shaders::ShaderPTN1::getPlaneID() const
{
	return planeID;
}
// FRAGMENT SHADER
GLuint const Shaders::ShaderPTN1::getLightColorID() const
{
	return lightColourID;
}

GLuint const Shaders::ShaderPTN1::getShineDamperID() const
{
	return shineDamperID;
}

GLuint const Shaders::ShaderPTN1::getReflectivityID() const
{
	return reflectivityID;
}

GLuint const Shaders::ShaderPTN1::getModelTextureID() const
{
	return modelTextureID;
}

GLuint const Shaders::ShaderPTN1::getSpecularMapID() const
{
	return specularMapID;
}
// OPERATORs
void Shaders::ShaderPTN1::printINFO()
{
	std::cout << *this;
}