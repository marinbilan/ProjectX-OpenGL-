#pragma once
#include "../../CommonFunctions/CommonFunctions.h"

namespace Shaders
{
namespace ShadersIf
{
class ShadersIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] ShadersIf() {}
	virtual ~ShadersIf()
	{
		std::cout << "ShadersIf destructor called!" << std::endl;
	}
	// FUNCTIONs
	virtual GLuint createShader(const char* vertexShader, const char* fragmentShader)
	{
		// Make VertexShader
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, (const GLchar**)&vertexShader, NULL);
		glCompileShader(vertexShaderID);
		// Make FragmentShader
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, (const GLchar**)&fragmentShader, NULL);
		glCompileShader(fragmentShaderID);
		// Make Shader Program
		GLuint shaderID = glCreateProgram();
		glAttachShader(shaderID, vertexShaderID);
		glAttachShader(shaderID, fragmentShaderID);
		glLinkProgram(shaderID);

		return shaderID;
	}
	virtual std::string  getShaderName()                 { return dummyString; }
	virtual GLuint const getShaderProgramID()      const { return 0; }
	// [ VERTEX SHADER ]
	//   ATTRIBs
	// ------------------- [ ShaderPTN0 ] --------------------------
	virtual GLuint const getPositionsID()        const { return 0; }
	virtual GLuint const getTextureCoordsID()    const { return 0; }
	virtual GLuint const getNormalsID()          const { return 0; }
	//   UNIFORMs
	virtual GLuint const getProjectionMatrixID() const { return 0; }
	virtual GLuint const getViewMatrixID()       const { return 0; }	
	virtual GLuint const getViewMatrixInvID()    const { return 0; }
	virtual GLuint const getModelMatrixID()      const { return 0; }

	virtual GLuint const getLightPositionID()    const { return 0; }
	virtual GLuint const getPlaneID()            const { return 0; }
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	virtual GLuint const getLightColorID()       const { return 0; }	
	virtual GLuint const getShineDamperID()      const { return 0; }
	virtual GLuint const getReflectivityID()     const { return 0; }
	virtual GLuint const getModelTextureID()     const { return 0; }
	// -------------------------------------------------------------

	// ------------------- [ ShaderPTN1 ] --------------------------
	virtual GLuint const getSpecularMapID()      const { return 0; }
	// -------------------------------------------------------------

	// ------------------- [ ShaderPTN2 ] --------------------------
	virtual GLuint const getCameraPositionID()   const { return 0; }
	virtual GLuint const getEnviroMapID()        const { return 0; }
	// -------------------------------------------------------------

	// ------------------- [ ShaderSkyBox0 ] ------------------------
	// No new vars
	// --------------------------------------------------------------

	// ------------------- [ ShaderTerrain0 ] ------------------------	
	virtual GLuint const getBackgroundTextureID()  const { return 0; }
	virtual GLuint const getRTextureID()           const { return 0; }
	virtual GLuint const getGTextureID()           const { return 0; }
	virtual GLuint const getBTextureID()           const { return 0; }
	virtual GLuint const getBlendMapID()           const { return 0; }
	// ---------------------------------------------------------------

	// ------------------- [ ShaderWaterTile0 ] ----------------------
	virtual GLuint const getReflectionTextureID()  const { return 0; }
	virtual GLuint const getRefractionTextureID()  const { return 0; }
	virtual GLuint const getDudvMapID()            const { return 0; }
	virtual GLuint const getMoveFactorID()         const { return 0; }
	// ---------------------------------------------------------------

	// ------------------- [ ShaderGUI0 ] ----------------------------
	// No new vars
	// ---------------------------------------------------------------

	// ------------------- [ ShaderLearningOpenGL0 ] -----------------
	virtual GLuint const getModelMatrixInvID()     const { return 0; }
	virtual GLuint const getObjectColorID()        const { return 0; }
	virtual GLuint const getMaterialAmbientID()    const { return 0; }
	virtual GLuint const getMaterialDiffuseID()    const { return 0; }
	virtual GLuint const getMaterialSpecularID()   const { return 0; }
	virtual GLuint const getMaterialShininessID()  const { return 0; }
	virtual GLuint const getLightAmbientID()       const { return 0; }
	virtual GLuint const getLightDiffuseID()       const { return 0; }
	virtual GLuint const getLightSpecularID()      const { return 0; }
	// ---------------------------------------------------------------

	// ------------------- [ ShaderMarker0 ] ------------------
	// No new vars
	// --------------------------------------------------------

	// ------------------- [ ShaderNormalMapPTNT0 ] ---------------------
	virtual GLuint const getTangentsID()              const { return 0; }
	virtual GLuint const getLightPositionEyeSpaceID() const { return 0; }
	virtual GLuint const getNormalMapID()             const { return 0; }
	// ------------------------------------------------------------------


	// OPERATORs
	virtual void printINFO() {};
private:
	std::string dummyString;
};
}
}