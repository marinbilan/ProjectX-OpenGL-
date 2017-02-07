#ifndef SHADER_1__
#define SHADER_1__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

#include "glm\glm.hpp"
#include "glm/gtc\matrix_transform.hpp"

namespace Shaders
{
class Shader_1 : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Shader_1(const char* vertexShader, const char* fragmentShader);

	~Shader_1();
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
	virtual GLuint const getNormalID() const;
	// 
	// UNIFORMs
	//
	virtual GLuint const getProjectionMatrixID() const;
	virtual GLuint const getViewMatrixID() const;
	virtual GLuint const getModelMatrixID() const;

	virtual GLuint const getRotationsID() const;
	virtual GLuint const getLightID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Shader_1& info)
	{
		output << "================ " << std::endl;
		output << "shaderProgramId: " << info.shaderProgramID << std::endl;
		output << "" << std::endl;
		output << "s_vPositionID:   " << info.s_vPositionID << std::endl;
		output << "s_vNormalID:     " << info.s_vNormalID << std::endl;
		output << "" << std::endl;
		output << "vLightID:        " << info.vLightID << std::endl;
		output << "mPID:            " << info.mPID << std::endl;
		output << "mVID:            " << info.mVID << std::endl;
		output << "mMID:            " << info.mMID << std::endl;
		output << "mRotationsID:    " << info.mRotationsID << std::endl;
		output << "================ " << std::endl;

		return output;
	}

private:

	glm::mat4 ProjectionMatrix;

	GLuint shaderProgramID;
	//
	// ATTRIBs
	//
	GLuint s_vPositionID;
	GLuint s_vNormalID;
	//
	// UNIFORMs
	//
	GLuint vLightID;
	GLuint mPID;
	GLuint mVID;
	GLuint mMID;
	GLuint mRotationsID;
};
}

#endif
