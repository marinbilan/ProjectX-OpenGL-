#pragma once
#include "../if/ShaderIf.h"

namespace Shaders
{
	class ShaderWaterTile0 : public ShadersIf::ShadersIf
	{
	public:
		// CONSTRUCTORs / DESTRUCTORs
		ShaderWaterTile0(const char* vertexShader, const char* fragmentShader);
		~ShaderWaterTile0();

		virtual GLuint const getShaderProgramID() const;
		// VERTEX SHADER
		// [ ATTRIBs ]
		virtual GLuint const getPositionsID() const;
		// [ UNIFORMs ]
		virtual GLuint const getViewMatrixID() const;
		virtual GLuint const getModelMatrixID() const;
		virtual GLuint const getCameraPositionID() const;
		virtual GLuint const getLightPositionID() const;

		// FRAGMENT SHADER
		// [ UNIFORMs ]
		virtual GLuint const getReflectionTextureID() const;
		virtual GLuint const getRefractionTextureID() const;
		virtual GLuint const getDudvMapID() const;
		virtual GLuint const getNormalMapID() const;
		virtual GLuint const getLightColorID() const;
		virtual GLuint const getMoveFactorID() const;

		// OPERATORs
		friend std::ostream& operator<<(std::ostream& output, ShaderWaterTile0& info)
		{
			output << "" << std::endl;
			output << "shaderProgramID:    " << info.shaderProgramID << std::endl;
			output << "" << std::endl;
			output << "positionsID:        " << info.positionsID << std::endl;
			output << "projectionMatrixID: " << info.projectionMatrixID << std::endl;
			output << "viewMatrixID:       " << info.viewMatrixID << std::endl;
			output << "modelMatrixID:      " << info.modelMatrixID << std::endl;
			output << "" << std::endl;
			output << "cameraPositionID:   " << info.cameraPositionID << std::endl;
			output << "lightPositionID:    " << info.lightPositionID << std::endl;
			output << "" << std::endl;
			output << "reflectionTextureID:" << info.reflectionTextureID << std::endl;
			output << "refractionTextureID:" << info.refractionTextureID << std::endl;
			output << "dudvMapID:          " << info.dudvMapID << std::endl;
			output << "normalMapID:        " << info.normalMapID << std::endl;
			output << "" << std::endl;
			output << "lightColourID:      " << info.lightColourID << std::endl;
			output << "moveFactorID:       " << info.moveFactorID << std::endl;

			return output;
		}

	private:
		glm::mat4 projectionMatrix;
		GLuint shaderProgramID;

		// VERTEX SHADER
		// [ ATTRIBs ]
		GLuint positionsID;
		// [ UNIFORMs ]
		GLuint projectionMatrixID;
		GLuint viewMatrixID;
		GLuint modelMatrixID;
		GLuint cameraPositionID;
		GLuint lightPositionID;

		// VERTEX SHADER
		// [ UNIFORMs ]
		GLuint reflectionTextureID;
		GLuint refractionTextureID;
		GLuint dudvMapID;
		GLuint normalMapID;

		GLuint lightColourID;
		GLuint moveFactorID;
	};
}
