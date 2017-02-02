#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_GUI.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_GUI::Shader_GUI(const char* vertexShader, const char* fragmentShader)
{
	std::cout << "Shader_GUI constructor called! " << std::endl;

	shaderProgramID = createShader(vertexShader, fragmentShader);
	//
	// Get Shader Variables [Attribs and Uniforms] IDs
	//
	s_vPositionID = glGetAttribLocation(shaderProgramID, "position");

	mMID = glGetUniformLocation(shaderProgramID, "transformationMatrix");
}

Shaders::Shader_GUI::~Shader_GUI()
{
	std::cout << "Shader_GUI destructor called!" << std::endl;
}
//
//
// FUNCTIONs
// 
//
GLuint const Shaders::Shader_GUI::getShaderProgramID() const
{
	return shaderProgramID;
}
//
// ATTRIBs
//
GLuint const Shaders::Shader_GUI::getPositionID() const
{
	return s_vPositionID;
}
//
// UNIFORMs
//
GLuint const Shaders::Shader_GUI::getmMID() const
{
	return mMID;
}
