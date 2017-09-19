#include <iostream>
#include <string>

#include "../../Shaders/inc/ShaderDepthMapFBO.h"
// CONSTRUCTORs / DESTRUCTORs
Shaders::ShaderDepthMapFBO::ShaderDepthMapFBO(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "ShaderPTN constructor called! " << std::endl;

    shaderProgramID = createShader(vertexShader, fragmentShader);
	// VERTEX SHADER
	// [ ATTRIBs ]
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	// [ UNIFORMs ]
	lightSpaceMatrixID = glGetUniformLocation(shaderProgramID, "lightSpaceMatrix");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");
}

Shaders::ShaderDepthMapFBO::~ShaderDepthMapFBO()
{
	std::cout << "ShaderPTN destructor called!" << std::endl;
}
// FUNCTIONs
GLuint const Shaders::ShaderDepthMapFBO::getShaderProgramID() const
{
	return shaderProgramID;
}

// VERTEX SHADER
// ATTRIBs
GLuint const Shaders::ShaderDepthMapFBO::getPositionsID() const
{
	return positionsID;
}
// UNIFORMs
GLuint const Shaders::ShaderDepthMapFBO::getLightSpaceMatrixID() const
{
	return lightSpaceMatrixID;
}

GLuint const Shaders::ShaderDepthMapFBO::getModelMatrixID() const
{
	return modelMatrixID;
}
// FRAGMENT SHADER