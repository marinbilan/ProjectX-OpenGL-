#ifndef SHADERLEARNINGOPENGL1__
#define SHADERLEARNINGOPENGL1__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderLearningOpenGL1 : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	ShaderLearningOpenGL1(const char* vertexShader, const char* fragmentShader);

	~ShaderLearningOpenGL1();
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
	// ===============
	// FRAGMENT SHADER
	// ===============
	// 
	// [ UNIFORMs ]
	//
	virtual GLuint const getObjectColorID() const;
	virtual GLuint const getLightColorID() const;
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, ShaderLearningOpenGL1& info)
	{
		output << "" << std::endl;
		output << ">>>> SHADER <<<<" << std::endl;
		output << "shaderProgramID:          " << info.shaderProgramID << std::endl;
		output << " VERTEX SHADER" << std::endl;		
		output << "positionsID:              " << info.positionsID << std::endl;
		output << "projectionMatrixID:       " << info.projectionMatrixID << std::endl;
		output << "viewMatrixID:             " << info.viewMatrixID << std::endl;
		output << "modelMatrixID:            " << info.modelMatrixID << std::endl;
		output << " FRAGMENT SHADER " << std::endl;
		output << "objectColorID:            " << info.objectColorID << std::endl;
		output << "lightColorID:             " << info.lightColorID << std::endl;
		output << "" << std::endl;
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
	// ===============
	// FRAGMENT SHADER
	// ===============
	//
	// [ UNIFORMs ]
	//
	GLuint objectColorID;
	GLuint lightColorID;
};
}

#endif
