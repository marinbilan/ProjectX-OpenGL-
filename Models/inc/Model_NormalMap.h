#ifndef MODEL_NORMALMAP__
#define MODEL_NORMALMAP__

#include <iostream>
#include <string>
//
// ModelIf
//
#include "../if/ModelIf.h"

namespace Models
{
class Model_NormalMap : public ModelsIf::ModelsIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Model_NormalMap(Shaders::ShadersIf::ShadersIf* _shader, Camera::CameraIf::CameraIf* _camera, GLfloat* _light);

	~Model_NormalMap();
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
	friend std::ostream& operator<<(std::ostream& output, Model_NormalMap& info)
	{
		return output;
	}
	
private:
	//
	// VAO
	//
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint texBufferID = 0;
	//
	// SHADER
	//
	Shaders::ShadersIf::ShadersIf* shader;
	//
	// CAMERA
	//
	Camera::CameraIf::CameraIf* camera;
	//
	// MODEL VARIABLE
	//
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 allRotsMatrix = glm::mat4(1.0f);
	//
	// LIGHT
	//
	GLfloat* light;
};
}

#endif
