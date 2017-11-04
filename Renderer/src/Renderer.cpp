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
Renderer::Renderer::Renderer() 
{
	std::cout << "Renderer created!" << std::endl;
};

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
void Renderer::Renderer::renderTerrain(Shaders::ShadersIf::ShadersIf* _shader, Models::ModelTerrain0* _staticModel, Camera::CameraIf::CameraIf* _camera)
{
	glUseProgram(_shader->getShaderProgramID());
	glBindVertexArray(_staticModel->getModelVAO());

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs

	glUniformMatrix4fv(_shader->getViewMatrixID(), 1, GL_FALSE, &_camera->getViewMatrix()[0][0]);
	_camera->invertCameraMatrix();
	glUniformMatrix4fv(_shader->getViewMatrixInvID(), 1, GL_FALSE, &_camera->getInvViewMatrix()[0][0]);
	glUniformMatrix4fv(_shader->getModelMatrixID(), 1, GL_FALSE, &(_staticModel->getModelMatrix()[0][0]));
	
	glm::vec3 lightPositionTerrain(380.0f, 10.0f, 380.0f);
	glUniform3f(_shader->getLightPositionID(), lightPositionTerrain[0], lightPositionTerrain[1], lightPositionTerrain[2]);
	// FRAGMENT SHADER
	// TEXTUREs
	glUniform1i(_shader->getBackgroundTextureID(), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _staticModel->backgroundTextureID);
	
	glUniform1i(_shader->getRTextureID(), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _staticModel->rTextureID);
	
	glUniform1i(_shader->getGTextureID(), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _staticModel->gTextureID);
	
	glUniform1i(_shader->getBTextureID(), 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _staticModel->bTextureID);
	
	glUniform1i(_shader->getBlendMapID(), 4);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, _staticModel->blendMapID);

	glm::vec3 lightColorTerrain(1.0f, 1.0f, 1.0f);
	glUniform3f(_shader->getlightColorID(), lightColorTerrain[0], lightColorTerrain[1], lightColorTerrain[2]);
	glUniform1f(_shader->getshineDamperID(), 30.0f);
	glUniform1f(_shader->getreflectivityID(), 0.1f);

	// std::cout << _staticModel->numInd << std::endl;

	glDrawElements(GL_TRIANGLES, _staticModel->numInd, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	glUseProgram(0);
}

void Renderer::Renderer::renderStaticModel(Models::ModelsIf::ModelsIf* _staticModel, Camera::CameraIf::CameraIf* _camera)
{
	glBindVertexArray(_staticModel->getModelVAO());

	for (unsigned int i = 0; i < _staticModel->getVectorOfMeshes().size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, _staticModel->getVectorOfMeshes()[i].VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _staticModel->getVectorOfMeshes()[i].IBO);
		//
		// GET SHADER FOR EACH MESH IN MODEL
		//
		Models::Mesh mesh = _staticModel->getVectorOfMeshes()[i];

		glUseProgram(mesh.meshShaderPtr->getShaderProgramID());
		if (!mesh.meshShaderPtr->getShaderName().compare("ShaderMarker0"))
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0); // VERTs

			glEnableVertexAttribArray(0); // VERTs
			// VERTEX SHADER UNIFORMS
			// Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(mesh.meshShaderPtr->getViewMatrixID(), 1, GL_FALSE, &_camera->getViewMatrix()[0][0]);
			glUniformMatrix4fv(mesh.meshShaderPtr->getModelMatrixID(), 1, GL_FALSE, &(_staticModel->getModelMatrix()[0][0]));

			GLfloat lightPosition1[] = { 380.0f, 10.0f, 380.0f };
			GLfloat lightColor1[] = { 1.0f, 1.0f, 1.0f };
			GLfloat objectColor1[] = { 1.0f, 1.0f, 1.0f };

			glUniform3f(mesh.meshShaderPtr->getLightColorID(), lightColor1[0], lightColor1[1], lightColor1[2]);
			glUniform3f(mesh.meshShaderPtr->getObjectColorID(), objectColor1[0], objectColor1[1], objectColor1[2]);
			glDrawElements(GL_TRIANGLES, _staticModel->getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			glUseProgram(0);
		}
		else if (!mesh.meshShaderPtr->getShaderName().compare("ShaderLearningOpenGL0"))
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vert), 0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vert), (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

			glEnableVertexAttribArray(0); // VERTEXs
			glEnableVertexAttribArray(1); // NORMALs
			// VERTEX SHADER UNIFORMS
			// Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(mesh.meshShaderPtr->getViewMatrixID(), 1, GL_FALSE, &_camera->getViewMatrix()[0][0]);
			glUniformMatrix4fv(mesh.meshShaderPtr->getModelMatrixID(), 1, GL_FALSE, &(_staticModel->getModelMatrix()[0][0]));
			glm::mat4 modelInv = glm::inverse(_staticModel->getModelMatrix());
			glUniformMatrix4fv(mesh.meshShaderPtr->getModelMatrixInvID(), 1, GL_FALSE, &modelInv[0][0]);

			GLfloat lightPosition1[] = { 385.0f, 77.0f, 485.0f };
			GLfloat lightColor1[] = { 1.0f, 1.0f, 1.0f };
			GLfloat objectColor1[] = { 1.0f, 1.0f, 1.0f };

			glUniform3f(mesh.meshShaderPtr->getLightPositionID(), lightPosition1[0], lightPosition1[1], lightPosition1[2]);
			glUniform3f(mesh.meshShaderPtr->getLightColorID(), lightColor1[0], lightColor1[1], lightColor1[2]);
			glUniform3f(mesh.meshShaderPtr->getObjectColorID(), objectColor1[0], objectColor1[1], objectColor1[2]);
			glDrawElements(GL_TRIANGLES, _staticModel->getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			glUseProgram(0);
		}
		else if (!mesh.meshShaderPtr->getShaderName().compare("ShaderPTN0"))
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)


			glEnableVertexAttribArray(0); // VERTEXs
			glEnableVertexAttribArray(1); // TEXTURECOORDs
			glEnableVertexAttribArray(2); // NORMALs
			// VERTEX SHADER UNIFORMS
			// Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(mesh.meshShaderPtr->getViewMatrixID(), 1, GL_FALSE, &_camera->getViewMatrix()[0][0]);
			_camera->invertCameraMatrix();
			glUniformMatrix4fv(mesh.meshShaderPtr->getViewMatrixInvID(), 1, GL_FALSE, &_camera->getInvViewMatrix()[0][0]);
			glUniformMatrix4fv(mesh.meshShaderPtr->getModelMatrixID(), 1, GL_FALSE, &(_staticModel->getModelMatrix()[0][0]));
			// TODO: Remove from here
			glm::vec3 lightPositionModelPTN(385.0f, 50.0f, 435.0f);
			glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);
			glUniform3f(mesh.meshShaderPtr->getLightID(), lightPositionModelPTN[0], lightPositionModelPTN[1], lightPositionModelPTN[2]);
			glm::vec4 planeModelPTN(0.0f, -1.0f, 0.0f, 100000.0f);
			glUniform4f(mesh.meshShaderPtr->getplaneID(), planeModelPTN[0], planeModelPTN[1], planeModelPTN[2], planeModelPTN[3]);
			// FRAGMENT SHADER UNIFORMS
			glUniform3f(mesh.meshShaderPtr->getlightColorID(), lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
			glUniform1f(mesh.meshShaderPtr->getshineDamperID(), 15.0f);
			glUniform1f(mesh.meshShaderPtr->getreflectivityID(), 0.6f);

			glUniform1i(mesh.meshShaderPtr->getmodelTextureID(), i);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, _staticModel->getVectorOfMeshes()[i].texture0ID);
			// RENDER MESH
			glDrawElements(GL_TRIANGLES, _staticModel->getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			//
			glUseProgram(0);
		}
		else if (!mesh.meshShaderPtr->getShaderName().compare("ShaderNormalMapPTNT0"))
		{
			//std::cout << "RENDER " << sizeof(Loader::VertNormalMap) <<  std::endl;
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::VertNormalMap), 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Loader::VertNormalMap), (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::VertNormalMap), (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::VertNormalMap), (const GLvoid*)32); // Tangent

			glEnableVertexAttribArray(0); // VERTEXs
			glEnableVertexAttribArray(1); // TEXTURECOORDs
			glEnableVertexAttribArray(2); // NORMALs
			glEnableVertexAttribArray(3); // TANGENTs
			//
			// VERTEX SHADER UNIFORMs
			//
            // Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(mesh.meshShaderPtr->getViewMatrixID(), 1, GL_FALSE, &_camera->getViewMatrix()[0][0]);
			// _camera->invertCameraMatrix();
			// glUniformMatrix4fv(mesh.meshShaderPtr->getViewMatrixInvID(), 1, GL_FALSE, &_camera->getInvViewMatrix()[0][0]);
			glUniformMatrix4fv(mesh.meshShaderPtr->getModelMatrixID(), 1, GL_FALSE, &(_staticModel->getModelMatrix()[0][0]));
			// TODO: Remove from here
			glm::vec3 lightPositionEyeSpace(385.0f, 10.0f, 435.0f);
			glUniform3f(mesh.meshShaderPtr->getLightPositionEyeSpaceID(), lightPositionEyeSpace[0], lightPositionEyeSpace[1], lightPositionEyeSpace[2]);
			//
			// FRAGMENT SHADER UNIFORMs
			//
			glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);
			glUniform3f(mesh.meshShaderPtr->getlightColorID(), lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
			glUniform1f(mesh.meshShaderPtr->getshineDamperID(), 22.0f);
			glUniform1f(mesh.meshShaderPtr->getreflectivityID(), 0.6f);

			glUniform1i(mesh.meshShaderPtr->getmodelTextureID(), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _staticModel->getVectorOfMeshes()[i].texture0ID);

			glUniform1i(mesh.meshShaderPtr->getNormalMapID(), 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, _staticModel->getVectorOfMeshes()[i].textureNormalMap0ID);
			// RENDER MESH
			glDrawElements(GL_TRIANGLES, _staticModel->getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			//
			glUseProgram(0);
		}

	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindVertexArray(0); // Unbind VAO
}
