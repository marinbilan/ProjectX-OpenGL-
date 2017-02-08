#ifndef SHADER_1__
#define SHADER_1__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

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
	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	virtual GLuint const getPositionsID() const;
	virtual GLuint const getNormalsID() const;
	// 
	// [ UNIFORMs ]
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
	friend std::ostream& operator<<(std::ostream& output, Shader_1& info)
	{
		output << "" << std::endl;
		output << "shaderProgramID:          " << info.shaderProgramID << std::endl;
		output << "" << std::endl;
		output << "positionsID:              " << info.positionsID << std::endl;
		output << "normalsID:                " << info.normalsID << std::endl;
		output << "" << std::endl;
		output << "projectionMatrixID:       " << info.projectionMatrixID << std::endl;
		output << "viewMatrixID:             " << info.viewMatrixID << std::endl;
		output << "modelMatrixID:            " << info.modelMatrixID << std::endl;
		
		output << "normalsRotationsMatrixID: " << info.normalsRotationsMatrixID << std::endl;
		output << "lightID:                  " << info.lightID << std::endl;
		output << "" << std::endl;

		return output;
	}

private:

	glm::mat4 projectionMatrix;

	GLuint shaderProgramID;
	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	GLuint positionsID;
	GLuint normalsID;
	// 
	// [ UNIFORMs ]
	//
	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;

	GLuint lightID;
	GLuint normalsRotationsMatrixID;
};
}

#endif
