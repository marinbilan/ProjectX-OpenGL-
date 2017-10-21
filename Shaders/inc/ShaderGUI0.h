#ifndef SHADERGUI0__
#define SHADERGUI0__

//#include <iostream>
//#include <string>

#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderGUI0 : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	ShaderGUI0(const char* vertexShader, const char* fragmentShader);

	~ShaderGUI0();
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
	virtual GLuint const getModelMatrixID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, ShaderGUI0& info)
	{
		output << "" << std::endl;
		output << "shaderProgramID: " << info.shaderProgramID << std::endl;
		output << "" << std::endl;
		output << "positionsID:     " << info.positionsID << std::endl;
		output << "modelMatrixID:   " << info.modelMatrixID << std::endl;
		output << "" << std::endl;

		return output;
	}

private:

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
	GLuint modelMatrixID;
};
}

#endif
