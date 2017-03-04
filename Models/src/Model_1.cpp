#include <iostream>
#include <string>

#include "../../Models/inc/Model_1.h"
//
// DATABASE [DB]
//
#include "../../Db/_dragon.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
//
Models::Model_1::Model_1(Shaders::ShadersIf::ShadersIf* _shader, Camera::CameraIf::CameraIf* _camera, GLfloat* _light)
{
	//
	// ADD SHADER(s)
	//
	shader = _shader;
	camera = _camera;
	light = _light;
	//
	// CREATE MODEL
	//
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 6 * num_ver*sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * num_ver*sizeof(GLfloat), vert);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * num_ver*sizeof(GLfloat), 3 * num_ver*sizeof(GLfloat), norm);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_ind*sizeof(GLuint), inds, GL_STATIC_DRAW);
	//
	// VERTEX ATTRIBUTE POINTER(s)
	//
	VertexAttribPointers();
}

Models::Model_1::~Model_1()
{
	std::cout << "Model_1 destructor called!" << std::endl;
}
//
//
// FUNCTION(s)
// 
//
void Models::Model_1::VertexAttribPointers()
{
	//
	// VERTEX ATTRIBUTE POINTER(s)
	//
	glUseProgram(shader->getShaderProgramID());
	glVertexAttribPointer(shader->getPositionsID(), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(shader->getNormalsID(), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vert)));
	glUseProgram(0);
}

void Models::Model_1::renderModel()
{
	//
	// ... UPDATE MODEL STATE
	//	
	modelMatrix = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	allRotsMatrix = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//
	// Bind VAO and Activate SHADER(s)
	//
	glBindVertexArray(VAO);
	glUseProgram(shader->getShaderProgramID());	
	//
	// Enable attributes in shaderProgramID
	//
	glEnableVertexAttribArray(shader->getPositionsID());
	glEnableVertexAttribArray(shader->getNormalsID());
	//
	// ... Update Uniforms ... 
	//     mP		  - shader [ Only once in shader ]
	//     mV		  - camera
	//     mM		  - modelMatrix
	//     mRotations - allRotsMatrix 
	//     vLight     - light
	//
	camera->updateCameraUniform(shader);
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);            
	glUniformMatrix4fv(shader->getNormalsRotationsID(), 1, GL_FALSE, &allRotsMatrix[0][0]);   
	glUniform4fv(shader->getLightID(), 1, light);
	//
	// ... DRAW MODEL (MESH) ...
	//
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, num_ind, GL_UNSIGNED_INT, NULL);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//
	// DISABLE EVERYTHING
	//
	glDisableVertexAttribArray(shader->getPositionsID());
	glDisableVertexAttribArray(shader->getNormalsID());

	glUseProgram(0);
	glBindVertexArray(0);
}


