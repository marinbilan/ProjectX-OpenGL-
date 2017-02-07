#ifndef SHADER_2__
#define SHADER_2__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h" // Nuzno je zbog [ public ShadersIf::ShadersIf ]
#include "glm\glm.hpp"
#include "glm/gtc\matrix_transform.hpp"

namespace Shaders
{
class Shader_2 : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Shader_2(const char* vertexShader, const char* fragmentShader);

	~Shader_2();
	//
	//
	// FUNCTIONs
	// 
	//
	virtual GLuint const getShaderProgramID() const;
	//
	// ATTRIBs
	//
	virtual GLuint const getPositionsID() const;
	// 
	// UNIFORMs
	//
	virtual GLuint const getModelMatrixID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Shader_2& info)
	{
		output << "" << std::endl;
		output << "shaderProgramID:..............." << info.shaderProgramID << std::endl;
		output << "" << std::endl;
		output << "positionsID:..................." << info.positionsID << std::endl;
		output << "modelMatrixID:................." << info.modelMatrixID << std::endl;
		output << "" << std::endl;

		return output;
	}

private:

	GLuint shaderProgramID;
	// =============
	// VERTEX SHADER
	// =============
	//
	// ATTRIBs
	//
	GLuint positionsID;
	//
	// UNIFORMs
	//
	GLuint modelMatrixID;
};
}

#endif
