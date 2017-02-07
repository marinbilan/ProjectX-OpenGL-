#ifndef SHADER_3__
#define SHADER_3__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h" // Nuzno je zbog [ public ShadersIf::ShadersIf ]
#include "glm\glm.hpp"
#include "glm/gtc\matrix_transform.hpp"

namespace Shaders
{
class Shader_3 : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Shader_3(const char* vertexShader, const char* fragmentShader);

	~Shader_3();
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
	virtual GLuint const getViewMatrixID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Shader_3& info)
	{
		output << "" << std::endl;
		output << "shaderProgramID:..............." << info.shaderProgramID << std::endl;
		output << "" << std::endl;
		output << "positionsID:..................." << info.s_vPositionID << std::endl;
		output << "" << std::endl;
		output << "projectionMatrixID:............" << info.mPID << std::endl;
		output << "modelMatrixID:................." << info.mMID << std::endl;
		output << "" << std::endl;

		return output;
	}

private:

	GLuint shaderProgramID;
	//
	// ATTRIBs
	//
	GLuint positionsID;
	//
	// UNIFORMs
	//
	GLuint projectionMatrixID;
	GLuint viewMatrixID;
};
}

#endif
