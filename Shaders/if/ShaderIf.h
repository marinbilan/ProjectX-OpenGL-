#ifndef SHADERIF__
#define SHADERIF__

#include <iostream>
#include <string>

#include "../../__libs/glew-1.13.0/include/GL/glew.h"

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
	//
	// ATTRIBs
	//
	virtual GLuint const getPositionID() const { return 0; }
	virtual GLuint const getNormalID()   const { return 0; }
	// 
	// UNIFORMs
	//
	// Shader_1
	virtual GLuint const getgWorldID() const { return 0; }
	
	// Shader_2
	virtual GLuint const getLightID() const { return 0; }

	virtual GLuint const getmPID() const { return 0; }
	virtual GLuint const getmVID() const { return 0; }
	virtual GLuint const getmMID() const { return 0; }

	virtual GLuint const getRotationsID() const { return 0; } // Normals rotation
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