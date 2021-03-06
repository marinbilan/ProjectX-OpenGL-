#pragma once
#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderPTN0 : public ShadersIf::ShadersIf
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
		"	uniform mat4 viewMatrixInv;"
		"	uniform mat4 transformationMatrix;"
		""
		"	uniform vec3 lightPosition;"
		"	uniform vec4 plane;"
		""
		"	out vec2 pass_textureCoordinates;"
		"	out vec3 surfaceNormal;"
		"	out vec3 toLightVector;"
		"	out vec3 toCameraVector;"
		""
		"	void main(void) {"
		""
		"		vec4 worldPosition = transformationMatrix * vec4(position, 1.0);"
		"		gl_ClipDistance[0] = dot(worldPosition, plane);"
		"		gl_Position = projectionMatrix * viewMatrix * worldPosition;"
		"		pass_textureCoordinates = textureCoordinates;"
		""
		"		surfaceNormal = ( transformationMatrix * vec4(normal, 0.0) ).xyz;"
		"		toLightVector = lightPosition - worldPosition.xyz;"
		"		toCameraVector = (viewMatrixInv * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;"
		"}";
	const char* FragmentShaderPTN =
		"#version 330 \r\n"
		""
		"	in vec2 pass_textureCoordinates;"
		"	in vec3 surfaceNormal;"
		"	in vec3 toLightVector;"
		"	in vec3 toCameraVector;"
		""
		"	uniform vec3 lightColour;"
		"	uniform float shineDamper;"
		"	uniform float reflectivity;"
		"	uniform sampler2D modelTexture;"
		""
		"	out vec4 out_Color;"
		""
		"	void main(void) {"
		""
		"		vec3 unitNormal = normalize(surfaceNormal);"
		"		vec3 unitLightVector = normalize(toLightVector);"
		""
		"		float nDot1 = dot(unitNormal, unitLightVector);"
		"		float brightness = max(nDot1, 0.2);"
		"		vec3 diffuse = brightness * lightColour;"
		""
		"		vec3 unitVectorToCamera = normalize(toCameraVector);"
		"		vec3 lightDirection = -unitLightVector;"
		"		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal); "
		""
		"		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera); "
		"		specularFactor = max(specularFactor, 0.0); "
		""
		"		float dampedFactor = pow(specularFactor, shineDamper); "
		""
		"		vec3 finalSpecular = dampedFactor * reflectivity * lightColour;"
		""
		"		out_Color = vec4(diffuse, 1.0) * texture(modelTexture, pass_textureCoordinates) + vec4(finalSpecular, 1.0);"
		"}";
public:
	// CONSTRUCTORs / DESTRUCTORs
	ShaderPTN0(GLfloat projMatrixWidth, GLfloat projMatrixHeight);

	~ShaderPTN0();
	// FUNCTIONs
	virtual std::string  getShaderName();
	virtual GLuint const getShaderProgramID()    const;
	// ---------------- [ ShaderPTN0 ] ----------------
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	virtual GLuint const getPositionsID()        const;
	virtual GLuint const getTextureCoordsID()    const;
	virtual GLuint const getNormalsID()          const;
	//   UNIFORMs
	virtual GLuint const getProjectionMatrixID() const;
	virtual GLuint const getViewMatrixID()       const;
	virtual GLuint const getViewMatrixInvID()    const;
	virtual GLuint const getModelMatrixID()      const;
	virtual GLuint const getLightPositionID()    const;
	virtual GLuint const getPlaneID()            const;

	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	virtual GLuint const getLightColorID()       const;	
	virtual GLuint const getShineDamperID()      const;
	virtual GLuint const getReflectivityID()     const;
	virtual GLuint const getModelTextureID()     const;
	// ------------------------------------------------

	// OPERATORs
	void printINFO();
	friend std::ostream& operator<<(std::ostream& output, ShaderPTN0& info)
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
		output << "      viewMatrixInvID    = " << info.viewMatrixInvID << std::endl;
		output << "      modelMatrixID      = " << info.modelMatrixID << std::endl;
		output << "      lightPositionID    = " << info.lightPositionID << std::endl;
		output << "      planeID            = " << info.planeID << std::endl;
		output << "  [ FRAGMENT SHADER ]" << std::endl;
		output << "      lightColourID      = " << info.lightColourID << std::endl;
		output << "      shineDamperID      = " << info.shineDamperID << std::endl;
		output << "      reflectivityID     = " << info.reflectivityID << std::endl;
		output << "      modelTextureID     = " << info.modelTextureID << std::endl;
		output << "" << std::endl;
		return output;
	}
private:
	std::string shaderName;
	glm::mat4   projectionMatrix;

	GLuint shaderProgramID;

	// VERTEX SHADER
	GLuint positionsID;
	GLuint textureCoordsID;
	GLuint normalsID;

	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint viewMatrixInvID;
	GLuint modelMatrixID;

	GLuint lightPositionID;	
	GLuint planeID;

	// FRAGMENT SHADER
	GLuint lightColourID;
	GLuint shineDamperID;
	GLuint reflectivityID;
	GLuint modelTextureID;
};
}
