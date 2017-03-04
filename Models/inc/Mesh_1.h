#ifndef MESH_1__
#define MESH_1__

#include <iostream>
#include <string>
//
// ModelIf
//
#include "../if/ModelIf.h"

namespace Models
{
class Mesh_1 : public ModelsIf::ModelsIf
{
public:
	//
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	//	
	Mesh_1(
		GLuint   _num_verts,
		GLfloat* _vertices,
		GLfloat* _normals,
		GLfloat* _textureCoords,
		Shaders::ShadersIf::ShadersIf* _shader, 
		Camera::CameraIf::CameraIf* _camera, 
		GLfloat* _light);

	~Mesh_1();
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
	friend std::ostream& operator<<(std::ostream& output, Mesh_1& info)
	{
		return output;
	}
	
private:

	GLuint   num_verts;
	GLfloat* vertices;
	GLfloat* normals;
	GLfloat* textureCoords;
	//
	// VAO
	//
	GLuint VAO;
	GLuint VBO;
	GLuint textureID;
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
	
	glm::mat4 modelMatrix;
};
}

#endif
