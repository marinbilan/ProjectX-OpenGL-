#ifndef SHADER_5__
#define SHADER_5__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

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
	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	virtual GLuint const getPositionsID() const;
	virtual GLuint const getNormalsID() const;
	virtual GLuint const getTextureCoordsID() const;
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
	friend std::ostream& operator<<(std::ostream& output, Shader_5& info)
	{
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
	GLuint textureCoordsID;
	// 
	// [ UNIFORMs ]
	//
	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;

	GLuint lightID;
	GLuint normalsRotationsMatrixID;
	// ===============
	// FRAGMENT SHADER
	// ===============
	//
	// [ UNIFORMs ]
	//
	GLuint textureSamplerID;
};
}

#endif
