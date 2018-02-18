#pragma once
#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderMarker0 : public ShadersIf::ShadersIf
{
	// BASIC COLOR
	const char* vertexShader =
		"	#version 330 \r\n"
		""
		"	in vec3 position;"
		""
		"	uniform mat4 projection;"
		"	uniform mat4 view;"
		"	uniform mat4 model;"
		""
		"	void main()"
		"	{"
		"		gl_Position = projection * view * model * vec4(position, 1.0f);"
		"}";

	const char* fragmentShader =
		"#version 330 \r\n"
		""
		"	out vec4 color;"
		""
		"	uniform vec3 objectColor;"
		"	uniform vec3 lightColor;"
		""
		"	void main()"
		"	{"
		"		color = vec4(lightColor * objectColor, 1.0f);"
		"	}";
public:
	// CONSTRUCTORs / DESTRUCTORs
	ShaderMarker0(GLfloat projMatrixWidth, GLfloat projMatrixHeight);

	~ShaderMarker0();
	// FUNCTIONs
	virtual std::string getShaderName();
	virtual GLuint const getShaderProgramID() const;
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	virtual GLuint const getPositionsID() const;
	//   UNIFORMs
	virtual GLuint const getProjectionMatrixID() const;
	virtual GLuint const getViewMatrixID() const;
	virtual GLuint const getModelMatrixID() const;
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	virtual GLuint const getObjectColorID() const;
	virtual GLuint const getLightColorID() const;

	// OPERATORs
	void printINFO();
	friend std::ostream& operator<<(std::ostream& output, ShaderMarker0& info)
	{
		output << "" << std::endl;
		output << "[ SHADER ]" << std::endl;
		output << " Shader Name:              " << info.shaderName << std::endl;
		output << " ShaderProgramID:          " << info.shaderProgramID << std::endl;
		output << "  [ VERTEX SHADER ]" << std::endl;
		output << "     positionsID         = " << info.positionsID << std::endl;
		output << "     normalsID           = " << info.normalsID << std::endl;
		output << "      projectionMatrixID = " << info.projectionMatrixID << std::endl;
		output << "      viewMatrixID       = " << info.viewMatrixID << std::endl;
		output << "      modelMatrixID      = " << info.modelMatrixID << std::endl;
		output << "  [ FRAGMENT SHADER ]" << std::endl;
		output << "      objectColorID      = " << info.objectColorID << std::endl;
		output << "      lightColorID       = " << info.lightColorID << std::endl;
		output << "" << std::endl;
		return output;
	}
private:
	std::string shaderName;
	GLuint shaderProgramID;

	glm::mat4 projectionMatrix;
	// VERTEX SHADER
	GLuint positionsID;
	GLuint normalsID;

	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;

	// FRAGMENT SHADER
	GLuint lightColorID;
	GLuint objectColorID;
};
}
