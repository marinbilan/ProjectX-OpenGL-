#ifndef SHADERIF__
#define SHADERIF__

#include <iostream>
#include <string>
//
// GLEW
//
#include "../../__libs/glew-1.13.0/include/GL/glew.h"
//
// GLM
//
#include "../../__libs/glm/glm/glm.hpp"
#include "../../__libs/glm/glm/gtc/matrix_transform.hpp"

namespace Shaders
{
namespace ShadersIf
{
class ShadersIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] ShadersIf() {}
	//
	//	
	virtual ~ShadersIf()
	{
		std::cout << "ShadersIf destructor called!" << std::endl;
	}
	//
	//
	// FUNCTIONs
	//
	//
	virtual GLuint createShader(const char* vertexShader, const char* fragmentShader)
	{
		//
		// Make VertexShader
		//
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, (const GLchar**)&vertexShader, NULL);
		glCompileShader(vertexShaderID);
		//
		// Make FragmentShader
		//
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, (const GLchar**)&fragmentShader, NULL);
		glCompileShader(fragmentShaderID);
		//
		// Make Shader Program
		//
		GLuint shaderID = glCreateProgram();
		glAttachShader(shaderID, vertexShaderID);
		glAttachShader(shaderID, fragmentShaderID);
		glLinkProgram(shaderID);

		return shaderID;
	}

	virtual GLuint const getShaderProgramID() const { return 0; }
	// =============
	// VERTEX SHADER
	// =============
	//
	// [ ATTRIBs ]
	//
	virtual GLuint const getPositionsID()          const { return 0; }
	virtual GLuint const getNormalsID()            const { return 0; }	
	virtual GLuint const getTextureCoordsID()      const { return 0; }
	virtual GLuint const getTangentsID()           const { return 0; }
	// 
	// [ UNIFORMs ]
	//
	virtual GLuint const getProjectionMatrixID()   const { return 0; }
	virtual GLuint const getViewMatrixID()         const { return 0; }	
	virtual GLuint const getViewMatrixInvID()      const { return 0; }
	virtual GLuint const getModelMatrixID()        const { return 0; }

	virtual GLuint const getLightID()              const { return 0; }	
	virtual GLuint const getNormalsRotationsID()   const { return 0; } 
	//
	
	virtual GLuint const getgWorldID()             const { return 0; }    	
	virtual GLuint const getuseFakeLightingID()    const { return 0; }
	// ===============
	// FRAGMENT SHADER
	// ===============
	// 
	// [ UNIFORMs ]
	//
	virtual GLuint const gettextureSamplerID()     const { return 0; }

	virtual GLuint const getmodelTextureID()      const { return 0; }
	virtual GLuint const getnormalMapID()          const { return 0; }

	virtual GLuint const getlightColorID()         const { return 0; }
	virtual GLuint const getshineDamperID()        const { return 0; }
	virtual GLuint const getreflectivityID()       const { return 0; }
	virtual GLuint const getskyColorID()           const { return 0; }
	//
	//
	// OPERATORs
	//
	//				
private:

};
}
}

#endif