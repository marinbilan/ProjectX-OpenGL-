#include "../../Shaders/inc/ShaderPTN0.h"
//
// CONSTRUCTORs / DESTRUCTORs
//
Shaders::ShaderPTN0::ShaderPTN0(GLfloat projMatrixWidth, GLfloat projMatrixHeight)
{
	shaderName = "ShaderPTN0"; // Hardcoded shader name
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
	//
	// Set Projection Matrix
    // 
	projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);

	std::cout << "ShaderPTN0 object created! " << std::endl;
}

Shaders::ShaderPTN0::~ShaderPTN0()
{
	std::cout << "ShaderPTN0 destructor called!" << std::endl;
}
// FUNCTIONs
std::string Shaders::ShaderPTN0::getShaderName()
{
	return shaderName;
}

GLuint const Shaders::ShaderPTN0::getShaderProgramID() const
{
	return shaderProgramID;
}

GLuint const Shaders::ShaderPTN0::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::ShaderPTN0::getTextureCoordsID() const
{
	return textureCoordsID;
}

GLuint const Shaders::ShaderPTN0::getNormalsID() const
{
	return normalsID;
}

GLuint const Shaders::ShaderPTN0::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::ShaderPTN0::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::ShaderPTN0::getViewMatrixInvID() const
{
	return viewMatrixInvID;
}

GLuint const Shaders::ShaderPTN0::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::ShaderPTN0::getLightID() const
{
	return lightPositionID;
}

GLuint const Shaders::ShaderPTN0::getplaneID() const
{
	return planeID;
}
// FRAGMENT SHADER
GLuint const Shaders::ShaderPTN0::getlightColorID() const
{
	return lightColourID;
}

GLuint const Shaders::ShaderPTN0::getshineDamperID() const
{
	return shineDamperID;
}

GLuint const Shaders::ShaderPTN0::getreflectivityID() const
{
	return reflectivityID;
}

GLuint const Shaders::ShaderPTN0::getmodelTextureID() const
{
	return modelTextureID;
}
// OPERATORs
void Shaders::ShaderPTN0::printINFO()
{
	std::cout << *this;
}