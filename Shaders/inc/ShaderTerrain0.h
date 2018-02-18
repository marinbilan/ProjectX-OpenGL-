#pragma once
#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderTerrain0 : public ShadersIf::ShadersIf
{
	// BASIC COLOR
	const char* vertexShader =
		"	#version 330 \r\n"
		""
		"	in vec3 position;"
		"	in vec2 textureCoords;"
		"	in vec3 normal;"
		""
		"	uniform mat4 projectionMatrix;"
		"	uniform mat4 viewMatrix;"
		"	uniform mat4 viewMatrixInv;"
		"	uniform mat4 transformationMatrix;"
		""
		"	uniform vec3 lightPosition;"
		""
		"	out vec2 pass_textureCoords;"
		"	out vec3 surfaceNormal;"
		"	out vec3 toLightVector;"
		"	out vec3 toCameraVector;"
		""
		"	void main()"
		"	{"
		"		gl_Position =  projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);"
		"		pass_textureCoords = textureCoords;"
		"		vec4 worldPosition = transformationMatrix * vec4(position, 1.0);"
		"		surfaceNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;"
		"		toLightVector = lightPosition - worldPosition.xyz;"
		"		toCameraVector =  (viewMatrixInv * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;"
		"}";

	const char* fragmentShader =
		"#version 330 \r\n"
		""
		"	in vec2 pass_textureCoords;"
		"	in vec3 surfaceNormal;"
		"	in vec3 toLightVector;"
		"	in vec3 toCameraVector;"
		""
		"	uniform sampler2D backgroundTexture;"
		"	uniform sampler2D rTexture;"
		"	uniform sampler2D gTexture;"
		"	uniform sampler2D bTexture;"
		"	uniform sampler2D blendMap;"
		""
		"	uniform vec3 lightColor;"
		"	uniform float shineDamper;"
		"	uniform float reflectivity;"
		""
		"	out vec4 out_Color;"
		""
		"	void main()"
		"	{"
		"		vec4 blendMapColor = texture(blendMap, pass_textureCoords);"
		"		float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);"
		"		vec2 tiledCoords = pass_textureCoords * 40.0;"
		"		vec4 backgroundTextureColor = texture(backgroundTexture, tiledCoords) * backTextureAmount;"
		"		vec4 rTextureColor = texture(rTexture, tiledCoords) * blendMapColor.r;"
		"		vec4 gTextureColor = texture(gTexture, tiledCoords) * blendMapColor.g;"
		"		vec4 bTextureColor = texture(bTexture, tiledCoords) * blendMapColor.b;"
		"		vec4 totalColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;"
		""
		"		vec3 unitNormal = normalize(surfaceNormal);"
		"		vec3 unitLightVector = normalize(toLightVector);"
		"		float nDot1 = dot(unitNormal, unitLightVector);"
		"		float brightness = max(nDot1, 0.1);"
		"		vec3 diffuse = brightness * lightColor;"
		"		vec3 unitVectorToCamera = normalize(toCameraVector);"
		"		vec3 lightDirection = - unitLightVector;"
		"		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);"
		"		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);"
		"		specularFactor = max(specularFactor, 0.0);"
		"		float dampedFactor = pow(specularFactor, shineDamper);"
		"		vec3 finalSpecular = dampedFactor * reflectivity * lightColor;"
		// out_Color = vec4(diffuse, 1.0) * texture(textureSampler, pass_textureCoords) + vec4(finalSpecular, 1.0);
		"		out_Color = vec4(diffuse, 1.0) * totalColor + vec4(finalSpecular, 1.0);"
		"	}";
public:
	// CONSTRUCTORs / DESTRUCTORs
	ShaderTerrain0(GLfloat projMatrixWidth, GLfloat projMatrixHeight);

	~ShaderTerrain0();
	// FUNCTIONs
	virtual std::string  getShaderName();
	virtual GLuint const getShaderProgramID() const;
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	virtual GLuint const getPositionsID() const;
	virtual GLuint const getTextureCoordsID() const;
	virtual GLuint const getNormalsID() const;
	//   UNIFORMs
	virtual GLuint const getProjectionMatrixID() const;
	virtual GLuint const getViewMatrixID() const;
	virtual GLuint const getViewMatrixInvID() const;
	virtual GLuint const getModelMatrixID() const;

	virtual GLuint const getLightPositionID() const;
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	virtual GLuint const getBackgroundTextureID() const;
	virtual GLuint const getRTextureID() const;
	virtual GLuint const getGTextureID() const;
	virtual GLuint const getBTextureID() const;
	virtual GLuint const getBlendMapID() const;

	virtual GLuint const getLightColorID() const;
	virtual GLuint const getShineDamperID() const;
	virtual GLuint const getReflectivityID() const;

	// OPERATORs
	void printINFO();
	friend std::ostream& operator<<(std::ostream& output, ShaderTerrain0& info)
	{
		output << "" << std::endl;
		output << "[ SHADER ]" << std::endl;
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
		output << "  [ FRAGMENT SHADER ]" << std::endl;
		output << "      backgroundTextureID= " << info.backgroundTextureID << std::endl;
		output << "      rTextureID         = " << info.rTextureID << std::endl;
		output << "      gTextureID         = " << info.gTextureID << std::endl;
		output << "      bTextureID         = " << info.bTextureID << std::endl;
		output << "      blendMapID         = " << info.blendMapID << std::endl;
		output << "      lightColorID       = " << info.lightColorID << std::endl;
		output << "      shineDamperID      = " << info.shineDamperID << std::endl;
		output << "      reflectivityID     = " << info.reflectivityID << std::endl;
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
	GLuint viewMatrixInvID;
	GLuint modelMatrixID;

	GLuint lightPositionID;
	// FRAGMENT SHADER
	GLuint backgroundTextureID;
	GLuint rTextureID;
	GLuint gTextureID;
	GLuint bTextureID;
	GLuint blendMapID;

	GLuint lightColorID;
	GLuint shineDamperID;
	GLuint reflectivityID;
};
}