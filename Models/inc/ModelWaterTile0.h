#ifndef MODELWATERTILE0__
#define MODELWATERTILE0__

//#include <iostream>
//#include <string>
//
// ModelIf
//
#include "../if/ModelIf.h"

namespace Models
{
class ModelWaterTile0 : public ModelsIf::ModelsIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	ModelWaterTile0(char* _fileName,
		             Shaders::ShadersIf::ShadersIf* _shader,
		             Camera::CameraIf::CameraIf* _camera,
		             GLuint _textureID,
		             glm::vec3 _position, 
		             glm::vec3 _scale);

	~ModelWaterTile0();
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
	friend std::ostream& operator<<(std::ostream& output, ModelWaterTile0& info)
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
