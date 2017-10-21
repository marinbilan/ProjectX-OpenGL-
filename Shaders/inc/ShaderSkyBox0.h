#ifndef SHADERSKYBOX0__
#define SHADERSKYBOX0__

//#include <iostream>
//#include <string>

#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderSkyBox0 : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	ShaderSkyBox0(const char* vertexShader, const char* fragmentShader);

	~ShaderSkyBox0();
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
	virtual GLuint const getViewMatrixID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, ShaderSkyBox0& info)
	{
		output << "" << std::endl;
		output << "shaderProgramID:          " << info.shaderProgramID << std::endl;
		output << "" << std::endl;
		output << "positionsID:              " << info.positionsID << std::endl;
		output << "" << std::endl;
		output << "projectionMatrixID:       " << info.projectionMatrixID << std::endl;
		output << "viewMatrixID:             " << info.viewMatrixID << std::endl;
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
	// 
	// [ UNIFORMs ]
	//
	GLuint projectionMatrixID;
	GLuint viewMatrixID;
};
}

#endif
