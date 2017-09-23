#include "../inc/Renderer.h"
//
// #### IMPORTANT: For each render function: ####
//
// 1 ] Bind VAO glBindVertexArray(VAO); 
// 2 ] Set Pointers    (glVertexAttribPointer); 
// 3 ] Enable Pointers (glEnableVertexAttribArray); 
// For each mesh:
	// 4.1 ] glBindBuffer(GL_ARRAY_BUFFER)
	// 4.2 ] glBindBuffer(GL_ELEMENT_ARRAY_BUFFER)
	// 4.3 ] Active shader glUseProgram(ShaderID);
	// 4.4 ] Update Uniform(s)

	// 4.5 ] Active Textures
	// 4.6 ] Bind Textures
	// 4.7 ] Render mesh (model) (glDrawElements ili another method)
// 5 ] Disable everything

// CONSTRUCTORs / DESTRUCTORs
Renderer::Renderer::Renderer() {};

void Renderer::Renderer::renderSkyBox(Camera::Camera* _camera, 
	                                  Models::Model_skyBox* _skyBox)
{
	_skyBox->renderModel();
}

void Renderer::Renderer::renderWater(Shaders::ShadersIf::ShadersIf* _shader, 
	                                 Models::Model_Water_Tile* _modelWaterTile)
{
	WAVE_SPEED = 0.001;
	moveFactor += WAVE_SPEED;
	glUseProgram(_shader->getShaderProgramID());
	glUniform1f(_shader->getmoveFactorID(), moveFactor);
	_modelWaterTile->renderModel(); // plane high (y = +100000) TODO
}

void Renderer::Renderer::renderModelPTN(GLfloat* _planeModelPTN, 
	                                    Camera::Camera* _camera, 
	                                    Models::ModelPTN* _modelPTN, 
	                                    Shaders::ShadersIf::ShadersIf* _shader)
{
	// Light Position
	lightPositionModelPTN[0] = 25.0f;
	lightPositionModelPTN[1] = 25.0f;
	lightPositionModelPTN[2] = 25.0f;
	// Light Color
	lightColorModelPTN[0] = 1.0f;
	lightColorModelPTN[1] = 1.0f;
	lightColorModelPTN[2] = 1.0f;

	glUseProgram(_shader->getShaderProgramID());
	_camera->updateCameraUniformInv(_shader);
	// UPDATE UNIFORMs (Not related to model)
	glUniform4f(_shader->getplaneID(), _planeModelPTN[0], _planeModelPTN[1], _planeModelPTN[2], _planeModelPTN[3]);
	glUniform3f(_shader->getLightID(), lightPositionModelPTN[0], lightPositionModelPTN[1], lightPositionModelPTN[2]);
	glUniform3f(_shader->getlightColorID(), lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
	// RENDER MODEL
	_modelPTN->render();
	glUseProgram(0);
}

void Renderer::Renderer::renderDepthMap(Models::ModelPTN* _modelPTN, Shaders::ShadersIf::ShadersIf* _shader)
{
	glUseProgram(_shader->getShaderProgramID());
	// RENDER MODEL
	_modelPTN->renderDepth(_shader);
	glUseProgram(0);
}

void Renderer::Renderer::renderModelLearningOpenGL(Camera::Camera* _camera, 
	                                               Shaders::ShadersIf::ShadersIf* _shader,
	                                               Models::ModelLearnOpenGL* _modelLearningOpenGL)
{
	GLfloat objectColor1[] = { 1.0f, 0.0f, 0.0f };
	GLfloat lightColor1[] = { 1.0f, 1.0f, 1.0f };
	glUseProgram(_shader->getShaderProgramID());
	_camera->updateCameraUniformInv(_shader);
	glUniform3f(_shader->getObjectColorID(), objectColor1[0], objectColor1[1], objectColor1[2]);
	glUniform3f(_shader->getLightColorID(), lightColor1[0], lightColor1[1], lightColor1[2]);
	_modelLearningOpenGL->render();
	glUseProgram(0);
}
// NEW
void Renderer::Renderer::renderStaticModel(glm::vec4                      _planeModelPTN,
	                                       Camera::CameraIf::CameraIf*    _camera,
	                                       Models::ModelsIf::ModelsIf*    _staticModel,
	                                       Shaders::ShadersIf::ShadersIf* _shader)
{
	// TODO: Remove from here
	glm::vec3 lightPositionModelPTN(25.0f, 25.0f, 25.0f);
	glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);

	glBindVertexArray(_staticModel->getModelVAO());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs

	for (unsigned int i = 0; i < _staticModel->getNumOfMeshes(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, _staticModel->getVectorOfVBOs()[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _staticModel->getVectorOfIBOs()[i]);
		// Get shader from vector od shaderIds. If shafer is ...
		glUseProgram(_shader->getShaderProgramID());
		if (!_shader->getShaderName().compare("shaderPTN1"))
		{
			// VERTEX SHADER UNIFORMS
			// Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(_shader->getViewMatrixID(), 1, GL_FALSE, &_camera->getViewMatrix()[0][0]);
			_camera->invertCameraMatrix();
			glUniformMatrix4fv(_shader->getViewMatrixInvID(), 1, GL_FALSE, &_camera->getInvViewMatrix()[0][0]);
			glUniformMatrix4fv(_shader->getModelMatrixID(), 1, GL_FALSE, &(_staticModel->getModelMatrix()[0][0]));
			glUniform3f(_shader->getLightID(), lightPositionModelPTN[0], lightPositionModelPTN[1], lightPositionModelPTN[2]);
			glUniform4f(_shader->getplaneID(), _planeModelPTN[0], _planeModelPTN[1], _planeModelPTN[2], _planeModelPTN[3]);
			// FRAGMENT SHADER UNIFORMS
			glUniform3f(_shader->getlightColorID(), lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
			glUniform1f(_shader->getshineDamperID(), 15.0f);
			glUniform1f(_shader->getreflectivityID(), 0.6f);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, _staticModel->getTexturesVectorId()[i]);
			// RENDER MESH
			glDrawElements(GL_TRIANGLES, _staticModel->getNumberOfIndicesVector()[i], GL_UNSIGNED_INT, 0);
			//
			glUseProgram(0);
		}
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
