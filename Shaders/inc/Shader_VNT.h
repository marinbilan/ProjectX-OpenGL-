#ifndef SHADER_VNT__
#define SHADER_VNT__

#include <iostream>
#include <string>

#include "../if/ShaderIf.h"

#include "glm\glm.hpp"
#include "glm/gtc\matrix_transform.hpp"

namespace Shaders
{
class Shader_VNT : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Shader_VNT(const char* vertexShader, const char* fragmentShader);

	~Shader_VNT();
	//
	//
	// FUNCTIONs
	// 
	//
	virtual GLuint const getShaderProgramID() const;
	//
	// ATTRIBs
	//
	virtual GLuint const getPositionID() const;
	virtual GLuint const getNormalID() const;
	virtual GLuint const gettextureCoordsID() const;
	// 
	// UNIFORMs
	//	
	virtual GLuint const getmPID() const;
	virtual GLuint const getmVID() const;
	virtual GLuint const getmVInvID() const;
	virtual GLuint const getmMID() const;
	virtual GLuint const getLightID() const;
	virtual GLuint const getuseFakeLightingID() const;
	
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
	friend std::ostream& operator<<(std::ostream& output, Shader_VNT& info)
	{
		output << "================ " << std::endl;
		output << "shaderProgramId: " << info.shaderProgramID << std::endl;
		//
		// VERTEX SHADER
		//
		output << "" << std::endl;
		output << "positionID:             " << info.positionID << std::endl;
		output << "normalID:               " << info.normalID << std::endl;
		output << "textureCoordsID:        " << info.textureCoordsID << std::endl;
		output << "" << std::endl;		
		output << "projectionMatrixID:     " << info.projectionMatrixID << std::endl;
		output << "viewMatrixID:           " << info.viewMatrixID << std::endl;
		output << "viewMatrixInvID:        " << info.viewMatrixInvID << std::endl;
		output << "transformationMatrixID: " << info.transformationMatrixID << std::endl;
		output << "lightPositionID:        " << info.lightPositionID << std::endl;
		output << "useFakeLightingID:      " << info.useFakeLightingID << std::endl;
		output << "" << std::endl;
		//
		// FRAGMENT SHADER
		//
		output << "textureSamplerID:       " << info.textureSamplerID << std::endl;
		output << "lightColorID:           " << info.lightColorID << std::endl;
		output << "shineDamperID:          " << info.shineDamperID << std::endl;
		output << "reflectivityID:         " << info.reflectivityID << std::endl;
		output << "skyColorID:             " << info.skyColorID << std::endl;
		output << "" << std::endl;
		output << "================ " << std::endl;

		return output;
	}

private:

	glm::mat4 ProjectionMatrix;

	GLuint shaderProgramID;
	// =============
	// VERTEX SHADER
	// =============
	//
	// ATTRIBs
	//
	GLuint positionID; // OK
	GLuint normalID; // OK
	GLuint textureCoordsID;
	//
	// UNIFORMs
	//
	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint viewMatrixInvID;
	GLuint transformationMatrixID;
	GLuint lightPositionID;
	GLuint useFakeLightingID;
	// =============
	// FRAGMENT SHADER
	// =============
	//
	// UNIFORMs
	//
	GLuint textureSamplerID;
	GLuint lightColorID;
	GLuint shineDamperID;
	GLuint reflectivityID;
	GLuint skyColorID;
};
}

#endif
