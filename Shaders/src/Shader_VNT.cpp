#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_VNT.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_VNT::Shader_VNT(const char* vertexShader, const char* fragmentShader)
{
        std::cout << "ShaderVNT constructor called! " << std::endl;

        shaderProgramID = createShader(vertexShader, fragmentShader);
        //
        // Get Shader Variables [Attribs and Uniforms] IDs
        //
		// =============
		// VERTEX SHADER
		// =============
		positionID = glGetAttribLocation(shaderProgramID, "position");
		normalID = glGetAttribLocation(shaderProgramID, "normal");
		textureCoordsID = glGetAttribLocation(shaderProgramID, "textureCoords");
       
		projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");
		viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");
		viewMatrixInvID = glGetUniformLocation(shaderProgramID, "viewMatrixInv");
		transformationMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");

		lightPositionID = glGetUniformLocation(shaderProgramID, "lightPosition");
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

Shaders::Shader_VNT::~Shader_VNT()
{
        std::cout << "Shader_VNT destructor called!" << std::endl;
}
//
//
// FUNCTIONs
//
//
GLuint const Shaders::Shader_VNT::getShaderProgramID() const
{
        return shaderProgramID;
}
//
// ATTRIBs
//
GLuint const Shaders::Shader_VNT::getPositionID() const
{
        return positionID;
}

GLuint const Shaders::Shader_VNT::getNormalID() const
{
        return normalID;
}

GLuint const Shaders::Shader_VNT::gettextureCoordsID() const
{
	return textureCoordsID;
}
//
// UNIFORMs VERTEX SHADER
//
GLuint const Shaders::Shader_VNT::getmPID() const
{
        return projectionMatrixID;
}

GLuint const Shaders::Shader_VNT::getmVID() const
{
        return viewMatrixID;
}

GLuint const Shaders::Shader_VNT::getmVInvID() const
{
	return viewMatrixInvID;
}

GLuint const Shaders::Shader_VNT::getmMID() const
{
        return transformationMatrixID;
}

GLuint const Shaders::Shader_VNT::getLightID() const
{
        return lightPositionID;
}

GLuint const Shaders::Shader_VNT::getuseFakeLightingID() const
{
	return useFakeLightingID;
}
//
// UNIFORMs FRAGMENT SHADER
//
GLuint const Shaders::Shader_VNT::gettextureSamplerID() const
{
	return textureSamplerID;
}

GLuint const Shaders::Shader_VNT::getlightColorID() const
{
	return lightColorID;
}

GLuint const Shaders::Shader_VNT::getshineDamperID() const
{
	return shineDamperID;
}

GLuint const Shaders::Shader_VNT::getreflectivityID() const
{
	return reflectivityID;
}

GLuint const Shaders::Shader_VNT::getskyColorID() const
{
	return skyColorID;
}