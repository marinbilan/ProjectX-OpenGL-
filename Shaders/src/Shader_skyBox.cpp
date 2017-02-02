#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_skyBox.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_skyBox::Shader_skyBox(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "Shader_skyBox constructor called! " << std::endl;

	shaderProgramID = createShader(vertexShader, fragmentShader);
	//
	// Get Shader Variables [Attribs and Uniforms] IDs
	//
	s_vPositionID = glGetAttribLocation(shaderProgramID, "position");

	mPID = glGetUniformLocation(shaderProgramID, "projectionMatrix");
	mVID = glGetUniformLocation(shaderProgramID, "viewMatrix");
	//
	// Set Projection Matrix
	//
	glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(60.0f), 1024.0f / 768.0f, 0.1f, 1000.f);

	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(mPID, 1, GL_FALSE, &ProjectionMatrix[0][0]);
	glUseProgram(0);
}

Shaders::Shader_skyBox::~Shader_skyBox()
{
	std::cout << "Shader_GUI destructor called!" << std::endl;
}
//
//
// FUNCTIONs
// 
//
GLuint const Shaders::Shader_skyBox::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// ATTRIBs
//
GLuint const Shaders::Shader_skyBox::getPositionID() const
{
	return s_vPositionID;
}
//
// UNIFORMs
//
GLuint const Shaders::Shader_skyBox::getmVID() const
{
	return mVID;
}
