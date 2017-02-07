#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_cube.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_cube::Shader_cube(const char* vertexShader, const char* fragmentShader)
{
        std::cout << "Shader_cube constructor called! " << std::endl;

        shaderProgramID = createShader(vertexShader, fragmentShader);
        //
        // Get Shader Variables [Attribs and Uniforms] IDs
        //
        s_vPositionID = glGetAttribLocation(shaderProgramID, "s_vPosition");
        s_vNormalID = glGetAttribLocation(shaderProgramID, "s_vNormal");
		s_vTexCoordID = glGetAttribLocation(shaderProgramID, "s_vTexCoord");
        
        mPID = glGetUniformLocation(shaderProgramID, "mP");
        mVID = glGetUniformLocation(shaderProgramID, "mV");
        mMID = glGetUniformLocation(shaderProgramID, "mM");
        mRotationsID = glGetUniformLocation(shaderProgramID, "mRotations");
		vLightID = glGetUniformLocation(shaderProgramID, "vLight");

		textureID = glGetUniformLocation(shaderProgramID, "texture");
        //
        // Set Projection Matrix
        //
        glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(60.0f), 1024.0f / 768.0f, 0.1f, 1000.f);

        glUseProgram(shaderProgramID);
        glUniformMatrix4fv(mPID, 1, GL_FALSE, &ProjectionMatrix[0][0]);
        glUseProgram(0);
}

Shaders::Shader_cube::~Shader_cube()
{
        std::cout << "Shader_2 destructor called!" << std::endl;
}
//
//
// FUNCTIONs
//
//
GLuint const Shaders::Shader_cube::getShaderProgramID() const
{
        return shaderProgramID;
}
//
// ATTRIBs
//
GLuint const Shaders::Shader_cube::getPositionID() const
{
        return s_vPositionID;
}

GLuint const Shaders::Shader_cube::getNormalID() const
{
        return s_vNormalID;
}

GLuint const Shaders::Shader_cube::gettexCoordID() const
{
	return s_vTexCoordID;
}
//
// UNIFORMs
//
GLuint const Shaders::Shader_cube::getLightID() const
{
        return vLightID;
}

GLuint const Shaders::Shader_cube::getmPID() const
{
        return mPID;
}

GLuint const Shaders::Shader_cube::getmVID() const
{
        return mVID;
}

GLuint const Shaders::Shader_cube::getmMID() const
{
        return mMID;
}

GLuint const Shaders::Shader_cube::getRotationsID() const
{
        return mRotationsID;
}
