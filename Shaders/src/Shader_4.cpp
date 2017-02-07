#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_4.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_4::Shader_4(const char* vertexShader, const char* fragmentShader)
{
        std::cout << "ShaderVNT constructor called! " << std::endl;

        shaderProgramID = createShader(vertexShader, fragmentShader);
        //
        // Get Shader Variables [Attribs and Uniforms] IDs
        //
		// =============
		// VERTEX SHADER
		// =============
		positionsID = glGetAttribLocation(shaderProgramID, "position");
		normalsID = glGetAttribLocation(shaderProgramID, "normal");
		textureCoordsID = glGetAttribLocation(shaderProgramID, "textureCoords");
       
		projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");
		viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");
		modelMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");

		lightID = glGetUniformLocation(shaderProgramID, "lightPosition");
		viewMatrixInvertedID = glGetUniformLocation(shaderProgramID, "viewMatrixInv");
		
		useFakeLightingID = glGetUniformLocation(shaderProgramID, "useFakeLighting");
		// =============
		// FRAGMENT SHADER
		// =============
		textureSamplerID = glGetUniformLocation(shaderProgramID, "textureSampler");
		lightColorID = glGetUniformLocation(shaderProgramID, "lightColor");
		shineDamperID = glGetUniformLocation(shaderProgramID, "shineDamper");
		reflectivityID = glGetUniformLocation(shaderProgramID, "reflectivity");
		skyColorID = glGetUniformLocation(shaderProgramID, "skyColor");
        //
        // Set Projection Matrix
        //
        glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(60.0f), 1024.0f / 768.0f, 0.1f, 1000.f);

        glUseProgram(shaderProgramID);
        glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &ProjectionMatrix[0][0]);
        glUseProgram(0);
}

Shaders::Shader_4::~Shader_4()
{
        std::cout << "Shader_4 destructor called!" << std::endl;
}
//
//
// FUNCTIONs
//
//
GLuint const Shaders::Shader_4::getShaderProgramID() const
{
        return shaderProgramID;
}
//
// ATTRIBs
//
GLuint const Shaders::Shader_4::getPositionsID() const
{
        return positionsID;
}

GLuint const Shaders::Shader_4::getNormalsID() const
{
        return normalsID;
}

GLuint const Shaders::Shader_4::getTextureCoordsID() const
{
	return textureCoordsID;
}
//
// UNIFORMs VERTEX SHADER
//
GLuint const Shaders::Shader_4::getProjectionMatrixID() const
{
        return projectionMatrixID;
}

GLuint const Shaders::Shader_4::getViewMatrixID() const
{
        return viewMatrixID;
}

GLuint const Shaders::Shader_4::getModelMatrixID() const
{
        return modelMatrixID;
}

GLuint const Shaders::Shader_4::getLightID() const
{
        return lightID;
}

GLuint const Shaders::Shader_4::getViewMatrixInvertedID() const
{
	return viewMatrixInvertedID;
}

GLuint const Shaders::Shader_4::getuseFakeLightingID() const
{
	return useFakeLightingID;
}
//
// UNIFORMs FRAGMENT SHADER
//
GLuint const Shaders::Shader_4::gettextureSamplerID() const
{
	return textureSamplerID;
}

GLuint const Shaders::Shader_4::getlightColorID() const
{
	return lightColorID;
}

GLuint const Shaders::Shader_4::getshineDamperID() const
{
	return shineDamperID;
}

GLuint const Shaders::Shader_4::getreflectivityID() const
{
	return reflectivityID;
}

GLuint const Shaders::Shader_4::getskyColorID() const
{
	return skyColorID;
}