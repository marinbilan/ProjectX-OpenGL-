#ifndef SHADER_DEPTHMAPFBO__
#define SHADER_DEPTHMAPFBO__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderDepthMapFBO : public ShadersIf::ShadersIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	ShaderDepthMapFBO(const char* vertexShader, const char* fragmentShader);

	~ShaderDepthMapFBO();
	// FUNCTIONs
	virtual GLuint const getShaderProgramID() const;
	// VERTEX SHADER
	// [ ATTRIBs ]
	virtual GLuint const getPositionsID() const;
	// [ UNIFORMs ]
	virtual GLuint const getLightSpaceMatrixID() const;
	virtual GLuint const getModelMatrixID() const;
	// FRAGMENT SHADER

	// OPERATORs
	friend std::ostream& operator<<(std::ostream& output, ShaderDepthMapFBO& info)
	{
		output << "" << std::endl;
		output << ">>>> SHADER <<<<" << std::endl;
		output << "shaderProgramID:          " << info.shaderProgramID << std::endl;
		output << " VERTEX SHADER" << std::endl;		
		output << "positionsID:              " << info.positionsID << std::endl;
		output << "lightSpaceMatrixID:       " << info.lightSpaceMatrixID << std::endl;
		output << "modelMatrixID:            " << info.modelMatrixID << std::endl;
		output << "" << std::endl;
		return output;
	}

private:
	GLuint shaderProgramID;
	// VERTEX SHADER
	// [ ATTRIBs ]
	GLuint positionsID;
	// [ UNIFORMs ]
	GLuint lightSpaceMatrixID;
	GLuint modelMatrixID;
	// FRAGMENT SHADER
};
}

#endif
