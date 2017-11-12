#pragma once

#include "../if/ShaderIf.h"

namespace Shaders
{
class ShaderLearningOpenGL0 : public ShadersIf::ShadersIf
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
	// AMBIENT + DIFFUSE
	const char* vertexShader1 =
		"	#version 330 \r\n"
		""
		"	in vec3 aPos;"
		"	in vec3 aNormal;"
		""
		"	uniform mat4 projection;"
		"	uniform mat4 view;"
		"	uniform mat4 model;"
		"	uniform mat4 modelInv;"
		""
		"	out vec3 FragPos;"
		"	out vec3 Normal;"
		""
		"	void main()"
		"	{"
		"		FragPos = vec3(model * vec4(aPos, 1.0));"
		//"		Normal = aNormal;"
		"           Normal = mat3(transpose(modelInv)) * aNormal;"
		""
		"		gl_Position = projection * view * vec4(FragPos, 1.0);"
		"}";

	const char* fragmentShader1 =
		"#version 330 \r\n"
		""
		"	out vec4 FragColor;"
		""
		"	in vec3 Normal;"
		"	in vec3 FragPos;"
		""
		"	uniform vec3 lightPos;"
		"	uniform vec3 lightColor;"
		"	uniform vec3 objectColor;"
		""
		"	void main()"
		"	{"
		// AMBIENT
		"		float ambientStrength = 0.1;"
		"		vec3 ambient = ambientStrength * lightColor;"
		// DIFFUSE
		"		vec3 norm = normalize(Normal);"
		"		vec3 lightDir = normalize(lightPos - FragPos);"
		"		float diff = max(dot(norm, lightDir), 0.0);"
		"		vec3 diffuse = diff * lightColor;"
		""
		"		vec3 result = (ambient + diffuse) * objectColor;"
		"		FragColor = vec4(result, 1.0);"
		"	}";
	// AMBIENT + DIFFUSE + SPECULAR
	const char* vertexShader2 =
		"	#version 330 \r\n"
		""
		"	in vec3 aPos;"
		"	in vec3 aNormal;"
		""
		"	uniform mat4 projection;"
		"	uniform mat4 view;"
		"	uniform mat4 model;"
		"	uniform mat4 modelInv;"
		""
		"	out vec3 FragPos;"
		"	out vec3 Normal;"
		""
		"	void main()"
		"	{"
		"		FragPos = vec3(model * vec4(aPos, 1.0));"
		//"		Normal = aNormal;"
		"       Normal = mat3(transpose(modelInv)) * aNormal;"
		""
		"		gl_Position = projection * view * vec4(FragPos, 1.0);"
		"}";

	const char* fragmentShader2 =
		"#version 330 \r\n"
		""
		"	out vec4 FragColor;"
		""
		"	in vec3 Normal;"
		"	in vec3 FragPos;"
		""
		"	uniform vec3 lightPos;"
		"	uniform vec3 viewPos;"
		"	uniform vec3 lightColor;"
		"	uniform vec3 objectColor;"
		""
		"	void main()"
		"	{"
		// AMBIENT
		"		float ambientStrength = 0.1;"
		"		vec3 ambient = ambientStrength * lightColor;"
		// DIFFUSE
		"		vec3 norm = normalize(Normal);"
		"		vec3 lightDir = normalize(lightPos - FragPos);"
		"		float diff = max(dot(norm, lightDir), 0.0);"
		"		vec3 diffuse = diff * lightColor;"
		""
		// SPECULAR
		"       float specularStrength = 0.5;"
	    "       vec3 viewDir = normalize(viewPos - FragPos);"
	    "       vec3 reflectDir = reflect(-lightDir, norm);"
	    "       float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"
	    "       vec3 specular = specularStrength * spec * lightColor;"
		""
		"		vec3 result = (ambient + diffuse + specular) * objectColor;"
		"		FragColor = vec4(result, 1.0);"
		"	}";

	// AMBIENT + DIFFUSE + SPECULAR + MATERIALs
	const char* vertexShader3 =
		"	#version 330 \r\n"
		""
		"	in vec3 aPos;"
		"	in vec3 aNormal;"
		""
		"	uniform mat4 projection;"
		"	uniform mat4 view;"
		"	uniform mat4 model;"
		"	uniform mat4 modelInv;"
		""
		"	out vec3 FragPos;"
		"	out vec3 Normal;"
		""
		"	void main()"
		"	{"
		"		FragPos = vec3(model * vec4(aPos, 1.0));"
		"       Normal = mat3(transpose(modelInv)) * aNormal;"
		""
		"		gl_Position = projection * view * vec4(FragPos, 1.0);"
		"   }";

	const char* fragmentShader3 =
		"#version 330 \r\n"
		""
		"	out vec4 FragColor;"
		""
	    "   struct Material" 
	    "   {"
		"      vec3 ambient;"
		"      vec3 diffuse;"
		"      vec3 specular;"
		"      float shininess;"
	    "   };"
		""
	    "   struct Light" 
	    "   {"
		"      vec3 position;"
		""
		"      vec3 ambient;"
		"      vec3 diffuse;"
		"      vec3 specular;"
	    "   };"
		""
		"	in vec3 Normal;"
		"	in vec3 FragPos;"
		""
		"	uniform vec3 viewPos;"
		"   uniform Material material;"
		"   uniform Light light;"
		""
		"	void main()"
		"	{"
		// AMBIENT
		"		vec3 ambient = light.ambient * material.ambient;"
		// DIFFUSE
		"		vec3 norm = normalize(Normal);"
		"		vec3 lightDir = normalize(light.position - FragPos);"
		"		float diff = max(dot(norm, lightDir), 0.0);"
		"		vec3 diffuse = light.diffuse * (diff * material.diffuse);"
		""
		// SPECULAR
		"       vec3 viewDir = normalize(viewPos - FragPos);"
		"       vec3 reflectDir = reflect(-lightDir, norm);"
		"       float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);"
		"       vec3 specular = light.specular * (spec * material.specular);"
		""
		"		vec3 result = ambient + diffuse + specular;"
		"		FragColor = vec4(result, 1.0);"
		"	}";
public:
	// CONSTRUCTORs / DESTRUCTORs
	ShaderLearningOpenGL0(GLfloat projMatrixWidth, GLfloat projMatrixHeight);

	~ShaderLearningOpenGL0();
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
	virtual GLuint const getModelMatrixInvID() const;
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	GLuint const getLightPositionID() const;
	GLuint const getCameraPositionID() const;
	virtual GLuint const getLightColorID() const;
	virtual GLuint const getObjectColorID() const;
	
	// MATERIALs and LIGHTs
	GLuint const getMaterialAmbientID() const;
	GLuint const getMaterialDiffuseID() const;
	GLuint const getMaterialSpecularID() const;
	GLuint const getMaterialShininessID() const;

	GLuint const NEWgetLightPositionID() const;
	GLuint const getLightAmbientID() const;
	GLuint const getLightDiffuseID() const;
	GLuint const getLightSpecularID() const;

	// OPERATORs
	void printINFO();
	friend std::ostream& operator<<(std::ostream& output, ShaderLearningOpenGL0& info)
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
		output << "      lightPositionID    = " << info.lightPositionID << std::endl;
		output << "      viewPositionID     = " << info.viewPositionID << std::endl;
		output << "      lightColorID       = " << info.lightColorID << std::endl;
		output << "      objectColorID      = " << info.objectColorID << std::endl;
		output << "" << std::endl;
		output << "      materialAmbientID  = " << info.materialAmbientID << std::endl;
		output << "      materialDiffuseID  = " << info.materialDiffuseID << std::endl;
		output << "      materialSpecularID = " << info.materialSpecularID << std::endl;
		output << "      matrialShininessID = " << info.matrialShininessID << std::endl;
		output << "      NEWlightPositionID = " << info.NEWlightPositionID << std::endl;
		output << "      lightAmbientID     = " << info.lightAmbientID << std::endl;
		output << "      lightDiffuseID     = " << info.lightDiffuseID << std::endl;
		output << "      lightSpecularID    = " << info.lightSpecularID << std::endl;
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
	GLuint modelMatrixInvID;

	// FRAGMENT SHADER
	GLuint lightPositionID;
	GLuint viewPositionID;
	GLuint lightColorID;
	GLuint objectColorID;

	// MATERIALs and LIGHTs
	GLuint materialAmbientID;
	GLuint materialDiffuseID;
	GLuint materialSpecularID;
	GLuint matrialShininessID;

	GLuint NEWlightPositionID;
	GLuint lightAmbientID;
	GLuint lightDiffuseID;
	GLuint lightSpecularID;
};
}

