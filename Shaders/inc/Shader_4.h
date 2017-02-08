#ifndef SHADER_4__
#define SHADER_4__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

namespace Shaders
{
class Shader_4 : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Shader_4(const char* vertexShader, const char* fragmentShader);

	~Shader_4();
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
	virtual GLuint const getViewMatrixInvertedID() const;

	virtual GLuint const getuseFakeLightingID() const;
	// ===============
	// FRAGMENT SHADER
	// ===============
	// 
	// [ UNIFORMs ]
	//
	virtual GLuint const gettextureSamplerID() const;			
	virtual GLuint const getlightColorID() const;
	virtual GLuint const getshineDamperID() const;
	virtual GLuint const getreflectivityID() const;
	virtual GLuint const getskyColorID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Shader_4& info)
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
	GLuint viewMatrixInvertedID;
		
	GLuint useFakeLightingID;
	// ===============
	// FRAGMENT SHADER
	// ===============
	// 
	// [ UNIFORMs ]
	//
	GLuint textureSamplerID;
	GLuint lightColorID;
	GLuint shineDamperID;
	GLuint reflectivityID;
	GLuint skyColorID;
};
}

#endif
