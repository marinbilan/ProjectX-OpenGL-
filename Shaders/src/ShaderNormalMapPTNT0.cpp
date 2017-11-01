#include "../../Shaders/inc/ShaderNormalMapPTNT0.h"
//
// CONSTRUCTORs / DESTRUCTORs
//
Shaders::ShaderNormalMapPTNT0::ShaderNormalMapPTNT0(GLfloat projMatrixWidth, GLfloat projMatrixHeight)
{
	shaderName = "ShaderNormalMapPTNT0"; // Hardcoded shader name
    shaderProgramID = createShader(VertexShaderNormalMapPTNT, FragmentShaderNormalMapPTNT);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	textureCoordsID = glGetAttribLocation(shaderProgramID, "textureCoordinates");
	normalsID = glGetAttribLocation(shaderProgramID, "normal");
	tangentsID = glGetAttribLocation(shaderProgramID, "tangent");
	// [ UNIFORMs ]
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");      
	viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");

	lightPositionEyeSpaceID = glGetUniformLocation(shaderProgramID, "lightPositionEyeSpace");
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	lightColourID = glGetUniformLocation(shaderProgramID, "lightColour");
	shineDamperID = glGetUniformLocation(shaderProgramID, "shineDamper");
	reflectivityID = glGetUniformLocation(shaderProgramID, "reflectivity");

	modelTextureID = glGetUniformLocation(shaderProgramID, "modelTexture");
	modelNormalMapID = glGetUniformLocation(shaderProgramID, "normalMap");
	//
	// Set Projection Matrix
    // 
	projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);

	std::cout << "ShaderNormalMapPTNT0 created!" << std::endl;
}

Shaders::ShaderNormalMapPTNT0::~ShaderNormalMapPTNT0()
{
	std::cout << "ShaderNormalMapPTNT0 destructor called!" << std::endl;
}
// FUNCTIONs
std::string Shaders::ShaderNormalMapPTNT0::getShaderName()
{
	return shaderName;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getShaderProgramID() const
{
	return shaderProgramID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getTextureCoordsID() const
{
	return textureCoordsID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getNormalsID() const
{
	return normalsID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getTangentsID() const
{
	return tangentsID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getLightPositionEyeSpaceID() const
{
	return lightPositionEyeSpaceID;
}

// FRAGMENT SHADER
GLuint const Shaders::ShaderNormalMapPTNT0::getlightColorID() const
{
	return lightColourID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getshineDamperID() const
{
	return shineDamperID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getreflectivityID() const
{
	return reflectivityID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getmodelTextureID() const
{
	return modelTextureID;
}

GLuint const Shaders::ShaderNormalMapPTNT0::getNormalMapID() const
{
	return modelNormalMapID;
}
// OPERATORs
void Shaders::ShaderNormalMapPTNT0::printINFO()
{
	std::cout << *this;
}