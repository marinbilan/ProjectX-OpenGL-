#ifndef MODELIF__
#define MODELIF__

// Loader
#include "../../Loader/inc/ModelLoader.h"
#include "../../Loader/inc/ModelLoaderLearningOpenGL.h"
#include "../../Loader/inc/TextureLoader.h"
// ShaderIf
#include "../../Shaders/if/ShaderIf.h" // Remove this
// CameraIf
#include "../../Camera/if/CameraIf.h" // Remove this

namespace Models
{
struct Mesh
{
	std::string meshName;
	std::string meshShaderName;
	Shaders::ShadersIf::ShadersIf* meshShaderPtr;

	GLuint VBO;
	GLuint IBO;
	GLuint numIndices;
	GLfloat sizeInMB;

	GLuint texture0ID;

	// OPERATORs
	friend std::ostream& operator<<(std::ostream& output, Mesh& info)
	{
		output << "  Mesh VBO: " << info.VBO;
		output << "  IBO: " << info.IBO;
		output << "  Num Vertices = " << info.numIndices;
		output << "  Shader: ";
		output << "  TextureID = " << info.texture0ID;
		return output;
	}
};

namespace ModelsIf
{
class ModelsIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] ModelsIf() {}
	virtual ~ModelsIf()
	{
		std::cout << "ModelsIf destructor called!" << std::endl;
	}
	// FUNCTIONs
	// GET
	virtual GLuint getModelVAO() { return 0; };
	virtual std::vector<Models::Mesh> getVectorOfMeshes() { return std::vector<Models::Mesh>(); };

	virtual glm::mat4 getModelMatrix()   { return glm::mat4(1.0f); }
	virtual glm::vec3 getModelPosition() { return glm::vec3(0.0, 0.0, 0.0); }
	virtual glm::vec3 getModelScale()    { return glm::vec3(0.0, 0.0, 0.0); }
	virtual glm::vec3 getModelRotation() { return glm::vec3(0.0, 0.0, 0.0); }
	virtual GLfloat   getModelAngle()    { return 0; };
	// SET
	virtual void setModelPosition(glm::vec3 _modelPosition)                     {}
	virtual void setModelScale(glm::vec3 _modelScale)                           {}
	virtual void setModelRotation(glm::vec3 _modelRotateAround, GLfloat _angle) {}

	// RENDER // REMOVE THIS FROM MODELIF
	virtual void render() {};
	virtual void renderDepth(Shaders::ShadersIf::ShadersIf* _shader) {};
	// OPERATORs		
private:
};
}
}
#endif