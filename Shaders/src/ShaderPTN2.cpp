#include "../../Shaders/inc/ShaderPTN2.h"
//
// CONSTRUCTORs / DESTRUCTORs
//
Shaders::ShaderPTN2::ShaderPTN2(GLfloat projMatrixWidth, GLfloat projMatrixHeight)
{
	shaderName = "ShaderPTN2"; // Hardcoded shader name
    shaderProgramID = createShader(VertexShaderPTN, FragmentShaderPTN);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	textureCoordsID = glGetAttribLocation(shaderProgramID, "textureCoordinates");
	normalsID = glGetAttribLocation(shaderProgramID, "normal");
	// [ UNIFORMs ]
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");      
	viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");
	cameraPositionID = glGetUniformLocation(shaderProgramID, "cameraPosition");
	// cam position add
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	modelTextureID = glGetUniformLocation(shaderProgramID, "modelTexture");
	enviroMapID = glGetUniformLocation(shaderProgramID, "enviroMap");
	//
	// Set Projection Matrix
    // 
	projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);

	std::cout << "ShaderPTN2 created!" << std::endl;
}

Shaders::ShaderPTN2::~ShaderPTN2()
{
	std::cout << "ShaderPTN2 destructor called!" << std::endl;
}
// FUNCTIONs
std::string Shaders::ShaderPTN2::getShaderName()
{
	return shaderName;
}

GLuint const Shaders::ShaderPTN2::getShaderProgramID() const
{
	return shaderProgramID;
}

// VERTEX SHADER
GLuint const Shaders::ShaderPTN2::getPositionsID() const
{
	return positionsID;
}

GLuint const Shaders::ShaderPTN2::getTextureCoordsID() const
{
	return textureCoordsID;
}

GLuint const Shaders::ShaderPTN2::getNormalsID() const
{
	return normalsID;
}

GLuint const Shaders::ShaderPTN2::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shaders::ShaderPTN2::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shaders::ShaderPTN2::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shaders::ShaderPTN2::getCameraPositionID() const
{
	return cameraPositionID;
}

// FRAGMENT SHADER

GLuint const Shaders::ShaderPTN2::getModelTextureID() const
{
	return modelTextureID;
}

GLuint const Shaders::ShaderPTN2::getEnviroMapID() const
{
	return enviroMapID;
}
// OPERATORs
void Shaders::ShaderPTN2::printINFO()
{
	std::cout << *this;
}