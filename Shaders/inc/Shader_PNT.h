#ifndef SHADER_PNT__
#define SHADER_PNT__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

namespace Shaders
{
class Shader_PNT : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Shader_PNT(const char* vertexShader, const char* fragmentShader);

	~Shader_PNT();
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
	virtual GLuint const getViewMatrixInvID() const;
	virtual GLuint const getModelMatrixID() const;

	virtual GLuint const getLightID() const;
	virtual GLuint const getplaneID() const;
	// ===============
	// FRAGMENT SHADER
	// ===============
	// 
	// [ UNIFORMs ]
	//
	virtual GLuint const getmodelTextureID() const;
	virtual GLuint const getlightColorID() const;
	virtual GLuint const getshineDamperID() const;
	virtual GLuint const getreflectivityID() const;
	//
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Shader_PNT& info)
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
		output << "viewMatrixInvID:          " << info.viewMatrixInvID << std::endl;
		output << "modelMatrixID:            " << info.modelMatrixID << std::endl;
		output << "" << std::endl;
		output << "lightPositionID:          " << info.lightPositionID << std::endl;
		output << "planeID:                  " << info.planeID << std::endl;
		output << "" << std::endl;
		output << "modelTextureID:           " << info.modelTextureID << std::endl;
		output << "lightColourID:            " << info.lightColourID << std::endl;
		output << "shineDamperID:            " << info.shineDamperID << std::endl;
		output << "reflectivityID:           " << info.reflectivityID << std::endl;
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
	GLuint normalsID;
	GLuint textureCoordsID;
	// 
	// [ UNIFORMs ]
	//
	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint viewMatrixInvID;
	GLuint modelMatrixID;

	GLuint lightPositionID;	
	GLuint planeID;
	// ===============
	// FRAGMENT SHADER
	// ===============
	//
	// [ UNIFORMs ]
	//
	GLuint modelTextureID;
	GLuint lightColourID;
	GLuint shineDamperID;
	GLuint reflectivityID;
};
}

#endif
