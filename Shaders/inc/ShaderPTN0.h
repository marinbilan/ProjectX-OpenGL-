#ifndef SHADERPNT0__
#define SHADERPNT0__

#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderPTN0 : public ShadersIf::ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	ShaderPTN0(const char* vertexShader, const char* fragmentShader);

	~ShaderPTN0();
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
	friend std::ostream& operator<<(std::ostream& output, ShaderPTN0& info)
	{
		output << "" << std::endl;
		output << "----==== SHADER ====----"<< std::endl;
		output << "Shader Name: " << info.shaderName << std::endl;
		output << "ShaderProgramID: " << info.shaderProgramID << std::endl;
		output << " --== VERTEX SHADER ==--" << std::endl;		
		output << "  positionsID = " << info.positionsID;
		output << " textureCoordsID = " << info.textureCoordsID;
		output << " normalsID = " << info.normalsID;
		output << " projectionMatrixID = " << info.projectionMatrixID;
		output << " viewMatrixID = " << info.viewMatrixID;
		output << " viewMatrixInvID = " << info.viewMatrixInvID;
		output << " modelMatrixID = " << info.modelMatrixID;
		output << " lightPositionID = " << info.lightPositionID;
		output << " planeID = " << info.planeID << std::endl;
		output << " --== FRAGMENT SHADER ==--" << std::endl;
		output << "  lightColourID = " << info.lightColourID;
		output << " shineDamperID = " << info.shineDamperID;
		output << " reflectivityID = " << info.reflectivityID;
		output << " modelTextureID = " << info.modelTextureID;
		output << "" << std::endl;
		return output;
	}

	void printINFO();

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
