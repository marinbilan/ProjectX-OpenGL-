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
	//
	// Get Shader Variables [Attribs and Uniforms] IDs
	//
	positionsID = glGetAttribLocation(shaderProgramID, "position");

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
// ATTRIBs
//
GLuint const Shaders::Shader_2::getPositionsID() const
{
	return positionsID;
}
//
// UNIFORMs
//
GLuint const Shaders::Shader_2::getModelMatrixID() const
{
	return modelMatrixID;
}
