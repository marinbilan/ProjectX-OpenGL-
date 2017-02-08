#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_2.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_2::Shader_2(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "Shader_2 constructor called! " << std::endl;

	shaderProgramID = createShader(vertexShader, fragmentShader);
	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	// 
	// [ UNIFORMs ]
	//
	modelMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");
}

Shaders::Shader_2::~Shader_2()
{
	std::cout << "Shader_2 destructor called!" << std::endl;
}
//
//
// FUNCTIONs
// 
//
GLuint const Shaders::Shader_2::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// [ ATTRIBs ]
//
GLuint const Shaders::Shader_2::getPositionsID() const
{
	return positionsID;
}
//
// [ UNIFORMs ]
//
GLuint const Shaders::Shader_2::getModelMatrixID() const
{
	return modelMatrixID;
}
