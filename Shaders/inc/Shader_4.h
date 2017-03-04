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
		output << "" << std::endl;
		output << "shaderProgramID:          " << info.shaderProgramID << std::endl;
		output << "" << std::endl;
		output << "positionsID:              " << info.positionsID << std::endl;
		output << "normalsID:                " << info.normalsID << std::endl;
		output << "textureCoordsID:          " << info.textureCoordsID << std::endl;
		output << "" << std::endl;
		output << "projectionMatrixID:       " << info.projectionMatrixID << std::endl;
		output << "viewMatrixID:             " << info.viewMatrixID << std::endl;
		output << "modelMatrixID:            " << info.modelMatrixID << std::endl;
		output << "" << std::endl;		
		output << "lightID:                  " << info.lightID << std::endl;
		output << "viewMatrixInvertedID:     " << info.viewMatrixInvertedID << std::endl;
		output << "useFakeLightingID:        " << info.useFakeLightingID << std::endl;
		output << "" << std::endl;
		output << "textureSamplerID:         " << info.textureSamplerID << std::endl;
		output << "lightColorID:             " << info.lightColorID << std::endl;
		output << "shineDamperID:            " << info.shineDamperID << std::endl;
		output << "reflectivityID:           " << info.reflectivityID << std::endl;
		output << "skyColorID:               " << info.skyColorID << std::endl;

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
