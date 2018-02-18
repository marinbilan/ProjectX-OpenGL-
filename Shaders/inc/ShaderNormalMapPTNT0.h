#pragma once
#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderNormalMapPTNT0 : public ShadersIf::ShadersIf
{
	const char* VertexShaderNormalMapPTNT =
		"#version 330 \r\n"
		""
		"    in vec3 position;"
		"    in vec2 textureCoordinates;"
		"    in vec3 normal;"
		"    in vec3 tangent;"
		""
		"    uniform mat4 projectionMatrix;"
		"    uniform mat4 viewMatrix;"
		"    uniform mat4 transformationMatrix;"
		""
		"    uniform vec3 lightPositionEyeSpace;" // MULTIPLE
		""
		"    const float density = 0;"
		"    const float gradient = 5.001;"
		""
		"    out vec2 pass_textureCoordinates;"
		"    out vec3 toLightVector;" // MULTIPLE
		"    out vec3 toCameraVector;"
		"    out float visibility;"
		""
		"   void main(void) {"
		""
		"	   vec4 worldPosition = transformationMatrix * vec4(position, 1.0);"
		"	   mat4 modelViewMatrix = viewMatrix * transformationMatrix;"
		"	   vec4 positionRelativeToCam = modelViewMatrix * vec4(position, 1.0);"
		"	   gl_Position = projectionMatrix * positionRelativeToCam;"
		""
		"	   pass_textureCoordinates = textureCoordinates;"
		""
		"	   vec3 surfaceNormal = (modelViewMatrix * vec4(normal, 0.0)).xyz;"
		""
		"	vec3 norm = normalize(surfaceNormal);"
		"	vec3 tang = normalize((modelViewMatrix * vec4(tangent, 0.0)).xyz);"
		"	vec3 bitang = normalize(cross(norm, tang));"
		""
		"	mat3 toTangentSpace = mat3("
		"		tang.x, bitang.x, norm.x,"
		"		tang.y, bitang.y, norm.y,"
		"		tang.z, bitang.z, norm.z"
		"		);"
		""
		"	toLightVector = toTangentSpace * ( (viewMatrix * vec4(lightPositionEyeSpace, 1.0)).xyz - positionRelativeToCam.xyz);"
		"	toCameraVector = toTangentSpace * (-positionRelativeToCam.xyz);"
		""
		"	float distance = length(positionRelativeToCam.xyz);"
		"	visibility = exp(-pow((distance*density), gradient));"
		"	visibility = clamp(visibility, 0.0, 1.0);"
		""
		"}";
	const char* FragmentShaderNormalMapPTNT =
		"#version 330 \r\n"
		""
		"   in vec2 pass_textureCoordinates;"
		"   in vec3 toLightVector;" // MULTIPLE
		"   in vec3 toCameraVector;"
		"   in float visibility;"
		""
		"   uniform vec3 lightColour;" // MULTIPLE
		"   uniform float shineDamper;"
		"   uniform float reflectivity;"
		""
		"   uniform sampler2D modelTexture;"
		"   uniform sampler2D normalMap;"
		""
		"   out vec4 out_Color;"
		""
		"   void main(void) {"
		""
		"	   vec4 normalMapValue = 2.0 * texture(normalMap, pass_textureCoordinates, -1.0) - 1.0;"
		""
		"	   vec3 unitNormal = normalize(normalMapValue.rgb);"
		"	   vec3 unitVectorToCamera = normalize(toCameraVector);"
		""
		"	   vec3 totalDiffuse = vec3(0.0);"
		"	   vec3 totalSpecular = vec3(0.0);"
		""
		"		float distance = length(toLightVector);"
		"		vec3 attenuation = vec3(0.001);"
		"		float attFactor = attenuation.x + (attenuation.y * distance) + (attenuation.z * distance * distance);"
		"		vec3 unitLightVector = normalize(toLightVector);"
		"		float nDotl = dot(unitNormal, unitLightVector);"
		"		float brightness = max(nDotl, 0.0);"
		"		vec3 lightDirection = -unitLightVector;"
		"		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);"
		"		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);"
		"		specularFactor = max(specularFactor, 0.0);"
		"		float dampedFactor = pow(specularFactor, shineDamper);"
		"		totalDiffuse = totalDiffuse + (brightness * lightColour) / attFactor;"
		"		totalSpecular = totalSpecular + (dampedFactor * reflectivity * lightColour) / attFactor;"
		""
		"   totalDiffuse = max(totalDiffuse, 0.1);"
		""
		"   vec4 textureColour = texture(modelTexture, pass_textureCoordinates, -1.0);"
		"   if (textureColour.a<0.5) {"
		"		discard;"
		"	}"
		""
		"   out_Color = vec4(totalDiffuse, 1.0) * textureColour + vec4(totalSpecular, 1.0);"
		//"	out_Color = mix(vec4(skyColour, 1.0), out_Color, visibility);"
		""
		"}";
public:
	// CONSTRUCTORs / DESTRUCTORs
	ShaderNormalMapPTNT0(GLfloat projMatrixWidth, GLfloat projMatrixHeight);

	~ShaderNormalMapPTNT0();
	// FUNCTIONs
	virtual std::string getShaderName();
	virtual GLuint const getShaderProgramID() const;
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	virtual GLuint const getPositionsID() const;
	virtual GLuint const getTextureCoordsID() const;
	virtual GLuint const getNormalsID() const;
	virtual GLuint const getTangentsID() const;
	//   UNIFORMs
	virtual GLuint const getProjectionMatrixID() const;
	virtual GLuint const getViewMatrixID() const;
	virtual GLuint const getModelMatrixID() const;
	virtual GLuint const getLightPositionEyeSpaceID() const;

	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	virtual GLuint const getLightColorID() const;	
	virtual GLuint const getShineDamperID() const;
	virtual GLuint const getReflectivityID() const;
	virtual GLuint const getModelTextureID() const;
	virtual GLuint const getNormalMapID() const;

	// OPERATORs
	void printINFO();
	friend std::ostream& operator<<(std::ostream& output, ShaderNormalMapPTNT0& info)
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
		output << "  [ FRAGMENT SHADER ]" << std::endl;
		output << "      lightColourID      = " << info.lightColourID << std::endl;
		output << "      shineDamperID      = " << info.shineDamperID << std::endl;
		output << "      reflectivityID     = " << info.reflectivityID << std::endl;
		output << "      modelTextureID     = " << info.modelTextureID << std::endl;
		output << "      modelNormalMapID   = " << info.modelNormalMapID << std::endl;
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
	GLuint tangentsID;

	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;
	GLuint lightPositionEyeSpaceID;

	// FRAGMENT SHADER
	GLuint lightColourID;
	GLuint shineDamperID;
	GLuint reflectivityID;

	GLuint modelTextureID;
	GLuint modelNormalMapID;
};
}