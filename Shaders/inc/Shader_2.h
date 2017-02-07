#ifndef SHADER_GUI__
#define SHADER_GUI__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h" // Nuzno je zbog [ public ShadersIf::ShadersIf ]
#include "glm\glm.hpp"
#include "glm/gtc\matrix_transform.hpp"

namespace Shaders
{
class Shader_GUI : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Shader_GUI(const char* vertexShader, const char* fragmentShader);

	~Shader_GUI();
	//
	//
	// FUNCTIONs
	// 
	//
	virtual GLuint const getShaderProgramID() const;
	//
	// ATTRIBs
	//
	virtual GLuint const getPositionID() const;
	// 
	// UNIFORMs
	//
	virtual GLuint const getmMID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Shader_GUI& info)
	{
		output << "================ " << std::endl;
		output << "shaderProgramId: " << info.shaderProgramID << std::endl;
		output << "" << std::endl;
		output << "s_vPositionID:   " << info.s_vPositionID << std::endl;
		output << "" << std::endl;
		output << "mMID:            " << info.mMID << std::endl;
		output << "================ " << std::endl;

		return output;
	}

private:

	GLuint shaderProgramID;
	//
	// ATTRIBs
	//
	GLuint s_vPositionID;
	//
	// UNIFORMs
	//
	GLuint mMID;
};
}

#endif
