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
	virtual GLuint const getPositionsID() const;
	virtual GLuint const getNormalsID() const;
	// 
	// UNIFORMs
	//
	virtual GLuint const getProjectionMatrixID() const;
	virtual GLuint const getViewMatrixID() const;
	virtual GLuint const getModelMatrixID() const;

	virtual GLuint const getNormalsRotationsID() const;
	virtual GLuint const getLightID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Shader_1& info)
	{
		output << "" << std::endl;
		output << "shaderProgramID:..............." << info.shaderProgramID << std::endl;
		output << "" << std::endl;
		output << "positionsID:..................." << info.s_vPositionID << std::endl;
		output << "normalsID:....................." << info.s_vNormalID << std::endl;
		output << "" << std::endl;
		output << "projectionMatrixID:............" << info.mPID << std::endl;
		output << "viewMatrixID:.................." << info.mVID << std::endl;
		output << "modelMatrixID:................." << info.mMID << std::endl;
		output << "normalsRotationsMatrixID:......" << info.mRotationsID << std::endl;
		output << "lightID:......................." << info.vLightID << std::endl;
		output << "" << std::endl;

		return output;
	}

private:

	glm::mat4 projectionMatrix;

	GLuint shaderProgramID;
	//
	// ATTRIBs
	//
	GLuint positionsID;
	GLuint normalsID;
	//
	// UNIFORMs
	//
	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;

	GLuint normalsRotationsMatrixID;
	GLuint lightID;
};
}

#endif
