#ifndef SHADER_PNT__
#define SHADER_PNT__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderPTN : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	ShaderPTN(std::string _shaderName, const char* vertexShader, const char* fragmentShader);

	~ShaderPTN();
	//
	//
	// FUNCTIONs
	// 
	//
	virtual std::string getShaderName();
	virtual GLuint const getShaderProgramID() const;
	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	virtual GLuint const getPositionsID() const;
	virtual GLuint const getTextureCoordsID() const;
	virtual GLuint const getNormalsID() const;
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
	virtual GLuint const getlightColorID() const;	
	virtual GLuint const getshineDamperID() const;
	virtual GLuint const getreflectivityID() const;
	virtual GLuint const getmodelTextureID() const;
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, ShaderPTN& info)
	{
		output << "" << std::endl;
		output << ">>>> SHADER <<<<" << std::endl;
		output << "shaderProgramID:          " << info.shaderProgramID << std::endl;
		output << " VERTEX SHADER" << std::endl;		
		output << "positionsID:              " << info.positionsID << std::endl;
		output << "textureCoordsID:          " << info.textureCoordsID << std::endl;
		output << "normalsID:                " << info.normalsID << std::endl;
		output << "projectionMatrixID:       " << info.projectionMatrixID << std::endl;
		output << "viewMatrixID:             " << info.viewMatrixID << std::endl;
		output << "viewMatrixInvID:          " << info.viewMatrixInvID << std::endl;
		output << "modelMatrixID:            " << info.modelMatrixID << std::endl;
		output << "lightPositionID:          " << info.lightPositionID << std::endl;
		output << "planeID:                  " << info.planeID << std::endl;
		output << " FRAGMENT SHADER " << std::endl;
		output << "lightColourID:            " << info.lightColourID << std::endl;
		output << "shineDamperID:            " << info.shineDamperID << std::endl;
		output << "reflectivityID:           " << info.reflectivityID << std::endl;
		output << "modelTextureID:           " << info.modelTextureID << std::endl;
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
	GLuint textureCoordsID;
	GLuint normalsID;
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
