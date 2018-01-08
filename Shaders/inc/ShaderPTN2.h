#pragma once

#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderPTN2 : public ShadersIf::ShadersIf
{
	const char* VertexShaderPTN =
		"#version 330 \r\n"
		""
		"	in vec3 position;"
		"	in vec2 textureCoordinates;"
		"	in vec3 normal;"
		""
		"	uniform mat4 projectionMatrix;"
		"	uniform mat4 viewMatrix;"
		"	uniform mat4 transformationMatrix;"
		"	uniform vec3 cameraPosition;"
		""
		"	out vec3 pass_normal;"
		"	out vec2 pass_textureCoordinates;"
		"	out vec3 reflectedVector;"
		"	out vec3 refractedVector;"
		""
		"	void main(void) {"
		""
		"		vec4 worldPosition = transformationMatrix * vec4(position, 1.0);"
		"		gl_Position = projectionMatrix * viewMatrix * worldPosition;"
		""
		"		pass_textureCoordinates = textureCoordinates;"
		"		pass_normal = normal;"
		"		vec3 unitNormal = normalize(normal);"
		""
		"		vec3 viewVector = normalize(worldPosition.xyz - cameraPosition);"
		"		reflectedVector = reflect(viewVector, unitNormal);"
		"		refractedVector = refract(viewVector, unitNormal, 1.0/1.33);"
		"}";
	const char* FragmentShaderPTN =
		"#version 330 \r\n"
		""
		"	in vec2 pass_textureCoordinates;"
		"	in vec3 pass_normal;"
		"	in vec3 reflectedVector;"
		"	in vec3 refractedVector;"
		""
		"	uniform sampler2D modelTexture;"
		"	uniform samplerCube enviroMap;"
		""
		"	const vec3 lightDirection = normalize(vec3(0.2, -1.0, 0.3));"
		"	const float ambient = 0.3;"
		""
		"	out vec4 out_Colour;"
		""
		"	void main(void) {"
		""
		"		float brightness = max(dot(-lightDirection, normalize(pass_normal)), 0.0) + ambient;"
		"		out_Colour = texture(modelTexture, pass_textureCoordinates) + brightness;"
		""
		"		vec4 reflectedColour = texture(enviroMap, reflectedVector);"
		"		vec4 refractedColour = texture(enviroMap, refractedVector);"
		"		vec4 enviroColour = mix(reflectedColour, refractedColour, 0.5);"
		""
		"		out_Colour = mix(out_Colour, enviroColour, 1.0);"
		"}";
public:
	// CONSTRUCTORs / DESTRUCTORs
	ShaderPTN2(GLfloat projMatrixWidth, GLfloat projMatrixHeight);

	~ShaderPTN2();
	// FUNCTIONs
	virtual std::string getShaderName();
	virtual GLuint const getShaderProgramID() const;
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	virtual GLuint const getPositionsID() const;
	virtual GLuint const getTextureCoordsID() const;
	virtual GLuint const getNormalsID() const;
	//   UNIFORMs
	virtual GLuint const getProjectionMatrixID() const;
	virtual GLuint const getViewMatrixID() const;
	virtual GLuint const getModelMatrixID() const;
	virtual GLuint const getCameraPositionID() const;
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	virtual GLuint const getModelTextureID() const;
	virtual GLuint const getEnviroMapID() const;

	// OPERATORs
	void printINFO();
	friend std::ostream& operator<<(std::ostream& output, ShaderPTN2& info)
	{
		output << "" << std::endl;
		output << "[ SHADER ]"<< std::endl;
		output << " Shader Name:              " << info.shaderName << std::endl;
		output << " ShaderProgramID:          " << info.shaderProgramID << std::endl;
		output << "  [ VERTEX SHADER ]" << std::endl;		
		output << "     positionsID         = " << info.positionsID << std::endl;
		output << "     textureCoordsID     = " << info.textureCoordsID << std::endl;
		output << "     normalsID           = " << info.normalsID << std::endl;
		output << "      projectionMatrixID = " << info.projectionMatrixID << std::endl;
		output << "      viewMatrixID       = " << info.viewMatrixID << std::endl;
		output << "      modelMatrixID      = " << info.modelMatrixID << std::endl;
		output << "      cameraPositionID   = " << info.cameraPositionID << std::endl;
		output << "  [ FRAGMENT SHADER ]" << std::endl;
		output << "      modelTextureID     = " << info.modelTextureID << std::endl;
		output << "      enviroMapID        = " << info.enviroMapID << std::endl;
		output << "" << std::endl;
		return output;
	}
private:
	std::string shaderName;
	GLuint shaderProgramID;

	glm::mat4 projectionMatrix;
	// VERTEX SHADER
	GLuint positionsID;
	GLuint textureCoordsID;
	GLuint normalsID;

	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;
	GLuint cameraPositionID;	

	// FRAGMENT SHADER
	GLuint modelTextureID;
	GLuint enviroMapID;
};
}
