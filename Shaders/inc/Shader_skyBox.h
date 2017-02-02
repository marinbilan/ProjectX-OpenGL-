#ifndef SHADER_SKYBOX__
#define SHADER_SKYBOX__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h" // Nuzno je zbog [ public ShadersIf::ShadersIf ]
#include "glm\glm.hpp"
#include "glm/gtc\matrix_transform.hpp"

namespace Shaders
{
class Shader_skyBox : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Shader_skyBox(const char* vertexShader, const char* fragmentShader);

	~Shader_skyBox();
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
	virtual GLuint const getmVID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Shader_skyBox& info)
	{
		output << "================ " << std::endl;
		output << "shaderProgramId: " << info.shaderProgramID << std::endl;
		output << "" << std::endl;
		output << "s_vPositionID:   " << info.s_vPositionID << std::endl;
		output << "" << std::endl;
		output << "mPID:            " << info.mPID << std::endl;
		output << "mVID:            " << info.mVID << std::endl;
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
	GLuint mPID;
	GLuint mVID;
};
}

#endif
