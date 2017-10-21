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

void Renderer::Renderer::renderSkyBox(Camera::CameraIf::CameraIf* _camera,
	                                  Models::ModelSkyBox0* _skyBox)
{
	_skyBox->renderModel();
}

void Renderer::Renderer::renderWater(Shaders::ShadersIf::ShadersIf* _shader, 
	                                 Models::ModelWaterTile0* _modelWaterTile)
{
	WAVE_SPEED = 0.001;
	moveFactor += WAVE_SPEED;
	glUseProgram(_shader->getShaderProgramID());
	glUniform1f(_shader->getmoveFactorID(), moveFactor);
	_modelWaterTile->renderModel(); // plane high (y = +100000) TODO
}

void Renderer::Renderer::renderModelPTN(GLfloat* _planeModelPTN, 
	                                    Camera::CameraIf::CameraIf* _camera,
	                                    Models::ModelPTN0* _modelPTN, 
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

void Renderer::Renderer::renderDepthMap(Models::ModelPTN0* _modelPTN, Shaders::ShadersIf::ShadersIf* _shader)
{
	glUseProgram(_shader->getShaderProgramID());
	// RENDER MODEL
	_modelPTN->renderDepth(_shader);
	glUseProgram(0);
}

// NEW
void Renderer::Renderer::renderStaticModel(glm::vec4                      _planeModelPTN,
	                                       Camera::CameraIf::CameraIf*    _camera,
	                                       Models::ModelsIf::ModelsIf*    _staticModel,
	                                       Shaders::ShadersIf::ShadersIf* _shader)
{
	glBindVertexArray(_staticModel->getModelVAO());

	for (unsigned int i = 0; i < _staticModel->getVectorOfMeshes().size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, _staticModel->getVectorOfMeshes()[i].VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _staticModel->getVectorOfMeshes()[i].IBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vertex), (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

		glEnableVertexAttribArray(0); // VERTEXs
		glEnableVertexAttribArray(1); // TEXTURECOORDs
		glEnableVertexAttribArray(2); // NORMALs

		glUseProgram(_shader->getShaderProgramID());
		if (!_shader->getShaderName().compare("ShaderPTN0"))
		{
			// VERTEX SHADER UNIFORMS
			// Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(_shader->getViewMatrixID(), 1, GL_FALSE, &_camera->getViewMatrix()[0][0]);
			_camera->invertCameraMatrix();
			glUniformMatrix4fv(_shader->getViewMatrixInvID(), 1, GL_FALSE, &_camera->getInvViewMatrix()[0][0]);
			glUniformMatrix4fv(_shader->getModelMatrixID(), 1, GL_FALSE, &(_staticModel->getModelMatrix()[0][0]));
			// TODO: Remove from here
			glm::vec3 lightPositionModelPTN(25.0f, 25.0f, 25.0f);
			glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);
			glUniform3f(_shader->getLightID(), lightPositionModelPTN[0], lightPositionModelPTN[1], lightPositionModelPTN[2]);
			glUniform4f(_shader->getplaneID(), _planeModelPTN[0], _planeModelPTN[1], _planeModelPTN[2], _planeModelPTN[3]);
			// FRAGMENT SHADER UNIFORMS
			glUniform3f(_shader->getlightColorID(), lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
			glUniform1f(_shader->getshineDamperID(), 15.0f);
			glUniform1f(_shader->getreflectivityID(), 0.6f);

			glUniform1i(_shader->getmodelTextureID(), i);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, _staticModel->getVectorOfMeshes()[i].texture0ID);
			// RENDER MESH
			glDrawElements(GL_TRIANGLES, _staticModel->getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			//
			glUseProgram(0);
		}
		else if (!_shader->getShaderName().compare("ShaderPTNDepth0"))
		{
			// VERTEX SHADER UNIFORMS
			// Ortho matrix updated in shader constructor (Only once)
			glm::mat4 lightView0 = glm::lookAt(glm::vec3(-10.5f, 10.5f, 10.5f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			// View Matrix
			glUniformMatrix4fv(_shader->getViewMatrixID(), 1, GL_FALSE, &lightView0[0][0]);
			// Model Matrix
			glUniformMatrix4fv(_shader->getModelMatrixID(), 1, GL_FALSE, &(_staticModel->getModelMatrix()[0][0]));

			// RENDER MESH
			glDrawElements(GL_TRIANGLES, _staticModel->getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			//
			glUseProgram(0);
		}
		else if (!_shader->getShaderName().compare("ShaderPTNDepth1"))
		{
			//std::cout << "OK" << std::endl;
			// VERTEX SHADER UNIFORMS
			// Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(_shader->getViewMatrixID(), 1, GL_FALSE, &_camera->getViewMatrix()[0][0]);
			_camera->invertCameraMatrix();
			glUniformMatrix4fv(_shader->getViewMatrixInvID(), 1, GL_FALSE, &_camera->getInvViewMatrix()[0][0]);
			glUniformMatrix4fv(_shader->getModelMatrixID(), 1, GL_FALSE, &(_staticModel->getModelMatrix()[0][0]));
			// ---- DEPTH TESTING PARAMs ----
			float near_plane = 1.0f, far_plane = 175.5f;
			glm::mat4 lightOrtho = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
			glm::mat4 lightView = glm::lookAt(glm::vec3(-10.5f, 10.5f, 10.5f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 lightSpaceMatrix = lightOrtho * lightView;
			glUniformMatrix4fv(_shader->getLightSpaceMatrixID(), 1, GL_FALSE, &(lightSpaceMatrix[0][0]));
			// ------------------------------
			glm::vec3 lightPositionModelPTN(25.0f, 25.0f, 25.0f);
			glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);
			glUniform3f(_shader->getLightID(), lightPositionModelPTN[0], lightPositionModelPTN[1], lightPositionModelPTN[2]);
			glUniform4f(_shader->getplaneID(), _planeModelPTN[0], _planeModelPTN[1], _planeModelPTN[2], _planeModelPTN[3]);
			// FRAGMENT SHADER UNIFORMS
			glUniform3f(_shader->getlightColorID(), lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
			glUniform1f(_shader->getshineDamperID(), 15.0f);
			glUniform1f(_shader->getreflectivityID(), 0.6f);

			glUniform1i(_shader->getmodelTextureID(), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _staticModel->getVectorOfMeshes()[i].texture0ID);

			glUniform1i(_shader->getShadowMapID(), 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 10);
			// RENDER MESH
			glDrawElements(GL_TRIANGLES, _staticModel->getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			//
			glUseProgram(0);
		}
		else if (!_shader->getShaderName().compare("LearningOpenGL0"))
		{
			// VERTEX SHADER UNIFORMS
			// Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(_shader->getViewMatrixID(), 1, GL_FALSE, &_camera->getViewMatrix()[0][0]);
			glUniformMatrix4fv(_shader->getModelMatrixID(), 1, GL_FALSE, &(_staticModel->getModelMatrix()[0][0]));

			GLfloat objectColor1[] = { 1.0f, 0.0f, 0.0f };
			GLfloat lightColor1[] = { 1.0f, 1.0f, 1.0f };

			glUniform3f(_shader->getObjectColorID(), objectColor1[0], objectColor1[1], objectColor1[2]);
			glUniform3f(_shader->getLightColorID(), lightColor1[0], lightColor1[1], lightColor1[2]);
			glDrawElements(GL_TRIANGLES, _staticModel->getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			glUseProgram(0);
		}
		else if (!_shader->getShaderName().compare("ShaderShadowMap"))
		{
			// VERTEX SHADER UNIFORMS
			// Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(_shader->getViewMatrixID(), 1, GL_FALSE, &(_camera->getViewMatrix()[0][0]));
			glUniformMatrix4fv(_shader->getModelMatrixID(), 1, GL_FALSE, &(_staticModel->getModelMatrix()[0][0]));
			// TODO: Remove calculations from here
			float near_plane = 1.0f, far_plane = 7.5f;
			glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
			glm::mat4 lightView = glm::lookAt(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 lightSpaceMatrix = lightProjection * lightView;
			glUniformMatrix4fv(_shader->getLightSpaceMatrixID(), 1, GL_FALSE, &(lightSpaceMatrix[0][0])); // NEW OK
			glm::mat3 tempMat3 = glm::mat3(_staticModel->getModelMatrix());
			glm::mat3 _mat3 = glm::inverse(tempMat3);
			glUniformMatrix3fv(_shader->getInvMat3ModelID(), 1, GL_FALSE, &(_mat3[0][0]));
			// FRAGMENT SHADER UNIFORMS
			//glUniform1i(_shader->getDiffuseTextureID(), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _staticModel->getVectorOfMeshes()[i].texture0ID);
			//glUniform1i(_shader->getShadowMapID(), 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 10);

			glm::vec3 lightPos(-0.5f, 0.5f, 0.5f);
			glUniform3f(_shader->getLightID(), lightPos[0], lightPos[1], lightPos[2]);
			glUniform3f(_shader->getCameraPositionID(), _camera->getcameraPosition()[0], _camera->getcameraPosition()[1], _camera->getcameraPosition()[2]);

			glDrawElements(GL_TRIANGLES, _staticModel->getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
		}
		else if (!_shader->getShaderName().compare("ThinMatrixDepthShader"))
		{
			// VERTEX SHADER UNIFORMS
			float near_plane = 1.0f, far_plane = 7.5f;
			glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
			glm::mat4 lightView = glm::lookAt(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			glm::mat4 mvpMatrix = lightProjection * lightView * _staticModel->getModelMatrix();
			glUniformMatrix4fv(_shader->getmvpMatrixID(), 1, GL_FALSE, &mvpMatrix[0][0]);

			glDrawElements(GL_TRIANGLES, _staticModel->getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			glUseProgram(0);
		}
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
