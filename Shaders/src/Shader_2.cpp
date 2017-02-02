#include <iostream>
#include <string>

#include "../../Shaders/inc/Shader_2.h"
//
//
// CONSTRUCTORs / DESTRUCTORs
//
//
Shaders::Shader_2::Shader_2(const char* vertexShader, const char* fragmentShader)
{
        std::cout << "Shader_2 constructor called! " << std::endl;

        shaderProgramID = createShader(vertexShader, fragmentShader);
        //
        // Get Shader Variables [Attribs and Uniforms] IDs
        //
        s_vPositionID = glGetAttribLocation(shaderProgramID, "s_vPosition");
        s_vNormalID = glGetAttribLocation(shaderProgramID, "s_vNormal");

        vLightID = glGetUniformLocation(shaderProgramID, "vLight");
        mPID = glGetUniformLocation(shaderProgramID, "mP");
        mVID = glGetUniformLocation(shaderProgramID, "mV");
        mMID = glGetUniformLocation(shaderProgramID, "mM");
        mRotationsID = glGetUniformLocation(shaderProgramID, "mRotations");
        //
        // Set Projection Matrix
        //
        glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(60.0f), 1024.0f / 768.0f, 0.1f, 1000.f);

        glUseProgram(shaderProgramID);
        glUniformMatrix4fv(mPID, 1, GL_FALSE, &ProjectionMatrix[0][0]);
        glUseProgram(0);
}

Shaders::Shader_2::~Shader_2()
{
        std::cout << "Shader_2 destructor called!" << std::endl;
}
//
//
// FUNCTIONs
//
//
GLuint const Shaders::Shader_2::getShaderProgramID() const
{
        return shaderProgramID;
}
//
// ATTRIBs
//
GLuint const Shaders::Shader_2::getPositionID() const
{
        return s_vPositionID;
}

GLuint const Shaders::Shader_2::getNormalID() const
{
        return s_vNormalID;
}
//
// UNIFORMs
//
GLuint const Shaders::Shader_2::getLightID() const
{
        return vLightID;
}

GLuint const Shaders::Shader_2::getmPID() const
{
        return mPID;
}

GLuint const Shaders::Shader_2::getmVID() const
{
        return mVID;
}

GLuint const Shaders::Shader_2::getmMID() const
{
        return mMID;
}

GLuint const Shaders::Shader_2::getRotationsID() const
{
        return mRotationsID;
}
