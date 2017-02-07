#ifndef SHADER_5__
#define SHADER_5__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

#include "glm\glm.hpp"
#include "glm/gtc\matrix_transform.hpp"

namespace Shaders
{
class Shader_5 : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Shader_5(const char* vertexShader, const char* fragmentShader);

	~Shader_5();
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
	virtual GLuint const getTextureCoordsID() const;
	// 
	// UNIFORMs
	//	
	virtual GLuint const getProjectionMatrixID() const;
	virtual GLuint const getViewMatrixID() const;
	virtual GLuint const getModelMatrixID() const;

	virtual GLuint const getLightID() const;
	virtual GLuint const getNormalsRotationsID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Shader_5& info)
	{
		//output << "================ " << std::endl;
		//output << "shaderProgramId: " << info.shaderProgramID << std::endl;
		//output << "" << std::endl;
		//output << "s_vPositionID:   " << info.s_vPositionID << std::endl;
		//output << "s_vNormalID:     " << info.s_vNormalID << std::endl;
		//output << "s_vTexCoordID:   " << info.s_vTexCoordID << std::endl;
		//output << "" << std::endl;
		//
		//output << "mPID:            " << info.mPID << std::endl;
		//output << "mVID:            " << info.mVID << std::endl;
		//output << "mMID:            " << info.mMID << std::endl;
		//output << "mRotationsID:    " << info.mRotationsID << std::endl;
		//output << "vLightID:        " << info.vLightID << std::endl;
		//output << "textureID:       " << info.textureID << std::endl;
		//output << "================ " << std::endl;

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
	GLuint textureCoordsID;
	//
	// UNIFORMs
	//
	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;

	GLuint lightID;
	GLuint normalsRotationsMatrixID;
	//		
	// SAMPLERs in FRAGMENT SHADER
	//
	GLuint textureSamplerID;
};
}

#endif
