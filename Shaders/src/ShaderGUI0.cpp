#include "../../Shaders/inc/ShaderGUI0.h"

// CONSTRUCTORs / DESTRUCTORs
Shaders::ShaderGUI0::ShaderGUI0(const char* vertexShader, const char* fragmentShader)
{
	shaderProgramID = createShader(vertexShader, fragmentShader);

	// VERTEX SHADER
	// [ ATTRIBs ]
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	// [ UNIFORMs ]
	modelMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");

	std::cout << "ShaderGUI0 created!" << std::endl;
}

Shaders::ShaderGUI0::~ShaderGUI0()
{
	std::cout << "ShaderGUI0 destructor called!" << std::endl;
}

// FUNCTIONs
GLuint const Shaders::ShaderGUI0::getShaderProgramID() const
{
	return shaderProgramID;
}
// [ ATTRIBs ]
GLuint const Shaders::ShaderGUI0::getPositionsID() const
{
	return positionsID;
}
// [ UNIFORMs ]
GLuint const Shaders::ShaderGUI0::getModelMatrixID() const
{
	return modelMatrixID;
}
