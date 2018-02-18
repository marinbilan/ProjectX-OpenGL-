#pragma once
#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderSkyBox0 : public ShadersIf::ShadersIf
{
	const char* vertexShader =
		"#version 330 \r\n"
		""
		"	in vec3 position;"
		""
		"	uniform mat4 projectionMatrix;"
		"	uniform mat4 viewMatrix;"
		""
		"	out vec3 textureCoords;"
		""
		"	void main()"
		"	{"
		"		gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);"
		""
		"		textureCoords = position;"
		"	}";

	const char* fragmentShader =
		"#version 330 \r\n"
		""
		"	in vec3 textureCoords;"
		"	out vec4 out_Color;"
		""
		"	uniform samplerCube cubeMap;"
		""
		"	void main()	"
		"	{"
		"		out_Color = texture(cubeMap, textureCoords);"
		"	}";
public:
	// CONSTRUCTORs / DESTRUCTORs
	ShaderSkyBox0(GLfloat projMatrixWidth, GLfloat projMatrixHeight);

	~ShaderSkyBox0();
	// FUNCTIONs
	virtual std::string getShaderName();
	virtual GLuint const getShaderProgramID() const;
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	virtual GLuint const getPositionsID() const;
	//   UNIFORMs
	virtual GLuint const getViewMatrixID() const;

	// OPERATORs
	void printINFO();
	friend std::ostream& operator<<(std::ostream& output, ShaderSkyBox0& info)
	{
		output << "" << std::endl;
		output << "[ SHADER ]" << std::endl;
		output << " Shader Name:              " << info.shaderName << std::endl;
		output << " ShaderProgramID:          " << info.shaderProgramID << std::endl;
		output << "  [ VERTEX SHADER ]" << std::endl;
		output << "     positionsID         = " << info.positionsID << std::endl;
		output << "      projectionMatrixID = " << info.projectionMatrixID << std::endl;
		output << "      viewMatrixID       = " << info.viewMatrixID << std::endl;
		return output;
	}

private:
	std::string shaderName;
	GLuint shaderProgramID;

	glm::mat4 projectionMatrix;

	// VERTEX SHADER
	GLuint positionsID;

	GLuint projectionMatrixID;
	GLuint viewMatrixID;
};
}
