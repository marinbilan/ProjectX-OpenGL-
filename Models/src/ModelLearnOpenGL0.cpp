#include "../../Models/inc/ModelLearnOpenGL0.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
// CONSTRUCTORs / DESTRUCTOR(s)
//
Models::ModelLearnOpenGL0::ModelLearnOpenGL0(Loader::ModelLoader*           _modelPTNLoader,
	                                       Loader::TextureLoader*         _textureLoader,
	                                       char*                          _textureShaderParams,
						                   Shaders::ShadersIf::ShadersIf* _shader)
{
	// CONSTURCOTR params
	modelPTNLoader      = _modelPTNLoader;
	textureLoader       = _textureLoader;
	textureShaderParams = _textureShaderParams;
	shader              = _shader;
	// MODEL params
	modelMatrix = glm::mat4(1.0f);
	// Position
	modelPosition = glm::vec3(0.0f, 5.0f, 0.0f);
	// Rotate around axe
	angle = -1.55f;
	modelRotateAround = glm::vec3(1.0f, 0.0f, 0.0f);
	// Scale
	modelScale = glm::vec3(0.1f, 0.1f, 0.1f);

	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
	modelMatrix = glm::scale(modelMatrix, modelScale);
	//
	// GET Textures
	//
	//texturesVectorId = textureLoader->getVectorOfTextures2DID();
}

Models::ModelLearnOpenGL0::~ModelLearnOpenGL0()
{
	std::cout << "ModelLearnOpenGL destructor called!" << std::endl;
}
//
// FUNCTION(s) - Add Clean function
// 
// SET
void Models::ModelLearnOpenGL0::setModelScale(glm::vec3 _modelScale)
{
	modelMatrix = glm::mat4(1.0f);
	modelScale = _modelScale;
	modelMatrix = glm::scale(modelMatrix, modelScale);

	glUseProgram(shader->getShaderProgramID());
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUseProgram(0);
}

void Models::ModelLearnOpenGL0::setModelRotation(GLfloat _angle, glm::vec3 _modelRotateAround)
{
	modelMatrix = glm::mat4(1.0f);
	angle = _angle;
	modelRotateAround = _modelRotateAround;
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);

	glUseProgram(shader->getShaderProgramID());
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUseProgram(0);
}

void Models::ModelLearnOpenGL0::setModelPosition(glm::vec3 _modelPosition)
{
	modelMatrix = glm::mat4(1.0f);
	modelPosition = _modelPosition;
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);

	glUseProgram(shader->getShaderProgramID());
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUseProgram(0);
}
// GET
glm::vec3& Models::ModelLearnOpenGL0::getModelScale()
{
	return modelScale;
}

glm::vec3& Models::ModelLearnOpenGL0::getModelRotation()
{
	return modelRotateAround;
}

glm::vec3& Models::ModelLearnOpenGL0::getModelPosition()
{
	return modelPosition;
}
//
// RENDER MODEL
//
void Models::ModelLearnOpenGL0::render()
{
	glBindVertexArray(modelPTNLoader->VAO);

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs

	for (unsigned int i = 0; i < modelPTNLoader->meshesVector.size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, modelPTNLoader->meshesVector[i].VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelPTNLoader->meshesVector[i].IBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), 0);                 // 
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

		glUseProgram(shader->getShaderProgramID()); // One shader for all meshes for now
		//
		// UPDATE UNIFORMs [ Update only uniforms related to model ]
		//
		// VERTEX SHADER
		glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
		// FRAGMENT SHADER
		glUniform1f(shader->getShineDamperID(), 15.0f);
		glUniform1f(shader->getReflectivityID(), 0.6f);
		//
		// uniform sampler2D modelTexture
		//
		glUniform1i(shader->getModelTextureID(), i); // shader textureID from each mesh connect with GL_TEXTURE0, GL_TEXTURE1...
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texturesVectorId[i]);
		//
		// DRAW MESHEs
		//
		glDrawElements(GL_TRIANGLES, modelPTNLoader->meshesVector[i].numIndices, GL_UNSIGNED_INT, 0);

		glUseProgram(0);
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);
}






