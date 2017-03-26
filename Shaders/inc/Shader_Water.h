#ifndef SHADER_Water__
#define SHADER_Water__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

namespace Shaders
{
class Shader_Water : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Shader_Water(const char* vertexShader, const char* fragmentShader);

	~Shader_Water();
	//
	//
	// FUNCTIONs
	// 
	//
	virtual GLuint const getShaderProgramID() const;
	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	virtual GLuint const getPositionsID() const;
	// 
	// [ UNIFORMs ]
	//
	virtual GLuint const getProjectionMatrixID() const;
	virtual GLuint const getViewMatrixID() const;
	virtual GLuint const getModelMatrixID() const;
	virtual GLuint const getCameraPositionID() const;
	// ===============
	// FRAGMENT SHADER
	// ===============
	// 
	// [ UNIFORMs ]
	//
	virtual GLuint const getreflectionTextureID() const;
	virtual GLuint const getrefractionTextureID() const;
	virtual GLuint const getdudvMapID() const;
	virtual GLuint const getmoveFactorID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Shader_Water& info)
	{
		output << "" << std::endl;
		output << "shaderProgramID:          " << info.shaderProgramID << std::endl;
		output << "" << std::endl;		
		output << "positionsID:              " << info.positionsID << std::endl;
		output << "" << std::endl;
		output << "projectionMatrixID:       " << info.projectionMatrixID << std::endl;
		output << "viewMatrixID:             " << info.viewMatrixID << std::endl;
		output << "modelMatrixID:            " << info.modelMatrixID << std::endl;
		output << "cameraPositionID:         " << info.cameraPositionID << std::endl;
		output << "" << std::endl;
		output << "" << std::endl;
		output << "reflectionTextureID:      " << info.reflectionTextureID << std::endl;
		output << "refractionTextureID:      " << info.refractionTextureID << std::endl;
		output << "dudvMapID:                " << info.dudvMapID << std::endl;
		output << "moveFactorID:             " << info.moveFactorID << std::endl;
		return output;
	}

private:

	GLuint shaderProgramID;

	glm::mat4 projectionMatrix;

	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	GLuint positionsID;
	// 
	// [ UNIFORMs ]
	//
	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;
	GLuint cameraPositionID;	
	// ===============
	// FRAGMENT SHADER
	// ===============
	//
	// [ UNIFORMs ]
	//
	GLuint reflectionTextureID;
	GLuint refractionTextureID;
	GLuint dudvMapID;

	GLuint moveFactorID;
};
}

#endif
