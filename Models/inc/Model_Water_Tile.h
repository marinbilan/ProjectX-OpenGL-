#ifndef MODEL_WATER_TILE__
#define MODEL_WATER_TILE__

#include <iostream>
#include <string>
//
// ModelIf
//
#include "../if/ModelIf.h"

namespace Models
{
class Model_Water_Tile : public ModelsIf::ModelsIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Model_Water_Tile(char* _fileName,
		             Shaders::ShadersIf::ShadersIf* _shader,
		             Camera::CameraIf::CameraIf* _camera,
		             GLuint _textureID,
		             glm::vec3 _position, 
		             glm::vec3 _scale);

	~Model_Water_Tile();
	//
	//
	// FUNCTIONs
	// 
	//
	virtual void VertexAttribPointers();

	virtual void renderModel();
	//
	// OPERATORs
	//
	//	
	friend std::ostream& operator<<(std::ostream& output, Model_Water_Tile& info)
	{
		return output;
	}
	
private:
	//
	// MODEL VARIABLE(s)
	//
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint texID = 0;
	GLuint normalMapID = 0;

	GLuint num_ver;

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	glm::vec3 position;
	glm::vec3 scale;
	//
	// SHADER(s)
	//
	Shaders::ShadersIf::ShadersIf* shader;
	char* fileName;
	Camera::CameraIf::CameraIf* camera;
	GLuint textureID;
};
}

#endif
