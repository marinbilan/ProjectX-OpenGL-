#ifndef SHADER_CUBE__
#define SHADER_CUBE__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

#include "glm\glm.hpp"
#include "glm/gtc\matrix_transform.hpp"

namespace Shaders
{
class Shader_cube : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Shader_cube(const char* vertexShader, const char* fragmentShader);

	~Shader_cube();
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
	virtual GLuint const gettexCoordID() const;
	// 
	// UNIFORMs
	//
	virtual GLuint const getLightID() const;
	virtual GLuint const getmPID() const;
	virtual GLuint const getmVID() const;
	virtual GLuint const getmMID() const;
	virtual GLuint const getRotationsID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Shader_cube& info)
	{
		output << "================ " << std::endl;
		output << "shaderProgramId: " << info.shaderProgramID << std::endl;
		output << "" << std::endl;
		output << "s_vPositionID:   " << info.s_vPositionID << std::endl;
		output << "s_vNormalID:     " << info.s_vNormalID << std::endl;
		output << "s_vTexCoordID:   " << info.s_vTexCoordID << std::endl;
		output << "" << std::endl;
		
		output << "mPID:            " << info.mPID << std::endl;
		output << "mVID:            " << info.mVID << std::endl;
		output << "mMID:            " << info.mMID << std::endl;
		output << "mRotationsID:    " << info.mRotationsID << std::endl;
		output << "vLightID:        " << info.vLightID << std::endl;
		output << "textureID:       " << info.textureID << std::endl;
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
	GLuint s_vTexCoordID;
	//
	// UNIFORMs
	//
	GLuint mPID;
	GLuint mVID;
	GLuint mMID;
	GLuint mRotationsID;
	GLuint vLightID;
	// SAMPLERs in FRAGMENT SHADER
	GLuint textureID;
};
}

#endif
