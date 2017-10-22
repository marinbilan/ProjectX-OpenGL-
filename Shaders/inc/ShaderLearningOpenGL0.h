#ifndef SHADERLEARNINGOPENGL0__
#define SHADERLEARNINGOPENGL0__

//#include <iostream>
//#include <string>

#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderLearningOpenGL0 : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	ShaderLearningOpenGL0(const char* vertexShader, const char* fragmentShader);

	~ShaderLearningOpenGL0();
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
	virtual std::string getShaderName();
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
	friend std::ostream& operator<<(std::ostream& output, ShaderLearningOpenGL0& info)
	{
		output << "" << std::endl;
		output << "----==== SHADER ====----" << std::endl;
		output << "Shader Name: " << info.shaderName << std::endl;
		output << "ShaderProgramID: " << info.shaderProgramID << std::endl;
		output << " --== VERTEX SHADER ==--" << std::endl;
		output << "  positionsID = " << info.positionsID;
		output << " projectionMatrixID = " << info.projectionMatrixID;
		output << " viewMatrixID = " << info.viewMatrixID;
		output << " modelMatrixID = " << info.modelMatrixID << std::endl;
		output << " --== FRAGMENT SHADER ==--" << std::endl;
		output << "  objectColorID = " << info.objectColorID;
		output << " lightColorID = " << info.lightColorID;
		output << "" << std::endl;
		return output;
	}

private:
	std::string shaderName;
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
