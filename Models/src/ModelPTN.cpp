#include "../../Models/inc/ModelPTN.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
// CONSTRUCTOR / DESTRUCTOR
Models::ModelPTN::ModelPTN(std::string                    _modelPath,
	                       std::string                    _modelName,
	                       Loader::ModelLoader*           _modelPTNLoader,
	                       Loader::TextureLoader*         _textureLoader,
						   Shaders::ShadersIf::ShadersIf* _shader,
	                       glm::vec3                      _modelPosition,
	                       glm::vec3                      _modelScale,
	                       glm::vec3                      _modelRotateAround,
	                       GLfloat                        _angle):
	                       modelPath(_modelPath),
	                       modelName(_modelName),
	                       modelPosition(_modelPosition),
	                       modelScale(_modelScale),
	                       modelRotateAround(_modelRotateAround),
	                       angle(_angle)
{
	// MODEL and TEXTUREs
	modelPTNLoader = new Loader::ModelLoader(const_cast<char *>(modelPath.c_str()), "_src/_models/_dagger/modelParams.txt"); // Remove params
	textureLoader = new Loader::TextureLoader(const_cast<char *>(modelPath.c_str()), modelPTNLoader->getNumberOfMeshes());
	// GET VAO
	VAO = modelPTNLoader->VAO;
	numOfMeshes = modelPTNLoader->meshesVector.size();
	// TODO clean up this:
	for (unsigned int i = 0; i < numOfMeshes; i++)
	{
		vectorOfVBOs.push_back(modelPTNLoader->meshesVector[i].VBO);
		vectorOfIBOs.push_back(modelPTNLoader->meshesVector[i].IBO);
		numberOfIndicesForEachMesh.push_back(modelPTNLoader->meshesVector[i].numIndices);
	}
	// GET Textures IDs
	texturesVectorId = textureLoader->getVectorOfTextures2DID();

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);
	modelMatrix = glm::scale(modelMatrix, modelScale);
	shader         = _shader; // Remove this
}

Models::ModelPTN::~ModelPTN()
{
	std::cout << "ModelPTN destructor called!" << std::endl;
}
// FUNCTIONs
// SET
void Models::ModelPTN::setModelPosition(glm::vec3 _modelPosition)
{
	modelMatrix = glm::mat4(1.0f);
	modelPosition = _modelPosition;
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);

	glUseProgram(shader->getShaderProgramID());
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUseProgram(0);
}

void Models::ModelPTN::setModelScale(glm::vec3 _modelScale)
{
	modelMatrix = glm::mat4(1.0f);
	modelScale = _modelScale;
	modelMatrix = glm::scale(modelMatrix, modelScale);

	glUseProgram(shader->getShaderProgramID());
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUseProgram(0);
}

void Models::ModelPTN::setModelRotation(glm::vec3 _modelRotateAround, GLfloat _angle)
{
	modelMatrix = glm::mat4(1.0f);
	angle = _angle;
	modelRotateAround = _modelRotateAround;
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);

	glUseProgram(shader->getShaderProgramID());
	glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	glUseProgram(0);
}
// GET
GLuint Models::ModelPTN::getModelVAO()
{
	return VAO;
}

std::vector<GLuint> Models::ModelPTN::getVectorOfVBOs()
{
	return vectorOfVBOs;
}

std::vector<GLuint> Models::ModelPTN::getVectorOfIBOs()
{
	return vectorOfIBOs;
}

std::vector<GLuint> Models::ModelPTN::getTexturesVectorId()
{
	return texturesVectorId;
}

std::vector<GLuint> Models::ModelPTN::getNumberOfIndicesVector()
{
	return numberOfIndicesForEachMesh;
}

GLuint Models::ModelPTN::getNumOfMeshes()
{
	return numOfMeshes;
}

glm::mat4 Models::ModelPTN::getModelMatrix()
{
	return modelMatrix;
}

glm::vec3 Models::ModelPTN::getModelPosition()
{
	return modelPosition;
}

glm::vec3 Models::ModelPTN::getModelScale()
{
	return modelScale;
}

glm::vec3 Models::ModelPTN::getModelRotation()
{
	return modelRotateAround;
}

GLfloat Models::ModelPTN::getModelAngle()
{
	return angle;
}
//
// RENDER MODEL
//
void Models::ModelPTN::render()
{
	glBindVertexArray(modelPTNLoader->VAO);

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs

	for (unsigned int i = 0; i < modelPTNLoader->meshesVector.size(); i++) {
		//glBindBuffer(GL_ARRAY_BUFFER, modelPTNLoader->meshesVector[i].VBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelPTNLoader->meshesVector[i].IBO);
		// glBindBuffer(GL_ARRAY_BUFFER, vectorOfVBOs[i]);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vectorOfIBOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, getVectorOfVBOs()[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getVectorOfIBOs()[i]);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), 0);                 // 
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

		glUseProgram(shader->getShaderProgramID()); // One shader for all meshes for now
		//
		// UPDATE UNIFORMs [ Update only uniforms related to model ]
		//
		// VERTEX SHADER
		// glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
		glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &getModelMatrix()[0][0]);
		// FRAGMENT SHADER
		glUniform1f(shader->getshineDamperID(), 15.0f);
		glUniform1f(shader->getreflectivityID(), 0.6f);
		//
		// uniform sampler2D modelTexture
		//
		// glUniform1i(shader->getmodelTextureID(), i); // shader textureID from each mesh connect with (i = 0 = GL_TEXTURE0), (i = 1 = GL_TEXTURE1) ...
		glActiveTexture(GL_TEXTURE0 + i);
		// glBindTexture(GL_TEXTURE_2D, texturesVectorId[i]);
		glBindTexture(GL_TEXTURE_2D, getTexturesVectorId()[i]);
		//
		// DRAW MESHEs
		//
		// glDrawElements(GL_TRIANGLES, modelPTNLoader->meshesVector[i].numIndices, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, getNumberOfIndicesVector()[i], GL_UNSIGNED_INT, 0);

		glUseProgram(0);
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Models::ModelPTN::renderDepth(Shaders::ShadersIf::ShadersIf* _shader)
{
	glBindVertexArray(modelPTNLoader->VAO);

	glEnableVertexAttribArray(0); // VERTEXs
	// glEnableVertexAttribArray(1); // TEXTURECOORDs
	// glEnableVertexAttribArray(2); // NORMALs

	for (unsigned int i = 0; i < modelPTNLoader->meshesVector.size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, modelPTNLoader->meshesVector[i].VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelPTNLoader->meshesVector[i].IBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), 0);                 // 
		// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
		// glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

		glUseProgram(_shader->getShaderProgramID()); // One shader for all meshes for now
													//
													// UPDATE UNIFORMs [ Update only uniforms related to model ]
													//
													// VERTEX SHADER
		// glUniformMatrix4fv(shader->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
		// FRAGMENT SHADER
		// glUniform1f(shader->getshineDamperID(), 15.0f);
		// glUniform1f(shader->getreflectivityID(), 0.6f);
		//
		// uniform sampler2D modelTexture
		//
		// glUniform1i(shader->getmodelTextureID(), i); // shader textureID from each mesh connect with (i = 0 = GL_TEXTURE0), (i = 1 = GL_TEXTURE1) ...
		// glActiveTexture(GL_TEXTURE0 + i);
		// glBindTexture(GL_TEXTURE_2D, texturesVectorId[i]);
		//
		// DRAW MESHEs
		//
		glDrawElements(GL_TRIANGLES, modelPTNLoader->meshesVector[i].numIndices, GL_UNSIGNED_INT, 0);

		glUseProgram(0);
	}
	glDisableVertexAttribArray(0);
	// glDisableVertexAttribArray(1);
	// glDisableVertexAttribArray(2);

	glBindVertexArray(0);
}




