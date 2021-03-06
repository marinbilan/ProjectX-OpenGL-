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
Renderer::Renderer::Renderer(Camera::CameraIf::CameraIf& camera,
	                         std::vector<Shaders::ShadersIf::ShadersIf*>& vectorShaders,
	                         std::vector<Models::ModelsIf::ModelsIf*>& vectorModels) :
	                         m_camera(camera),
	                         m_vectorShaders(vectorShaders),
	                         m_vectorModels(vectorModels)
{
	std::cout << "Renderer Constructor Called! " << std::endl;
}

// FUNCTIONs
void Renderer::Renderer::renderSkyBox(Models::ModelSkyBox0& _skyBox)
{
	glBindVertexArray(_skyBox.getModelVAO());
	glUseProgram(_skyBox.getShader().getShaderProgramID());

	glBindBuffer(GL_ARRAY_BUFFER, _skyBox.getModelVBO());
	glVertexAttribPointer(_skyBox.getShader().getPositionsID(), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(_skyBox.getShader().getPositionsID());

	m_camera.stopTranslate();
	m_camera.updateCameraUniform(&_skyBox.getShader());
	m_camera.updateCameraPosition();
	glUniformMatrix4fv(_skyBox.getShader().getModelMatrixID(), 1, GL_FALSE, &_skyBox.getModelMatrix()[0][0]);

	GLfloat lightPosition[] = { 0.0f, 5.0f, 15.0f };
	GLfloat lightColour[] = { 1.0f, 1.0f, 1.0f };

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _skyBox.getTextureID());

	glDrawArrays(GL_TRIANGLES, 0, _skyBox.getNumVertices());

	glDisableVertexAttribArray(_skyBox.getShader().getPositionsID());

	glUseProgram(0);
	glBindVertexArray(0);
}

void Renderer::Renderer::renderWater(Shaders::ShadersIf::ShadersIf* _shader, 
	                                 Models::ModelWaterTile0* _modelWaterTile)
{
	WAVE_SPEED = 0.001;
	moveFactor += WAVE_SPEED;
	glUseProgram(_shader->getShaderProgramID());
	glUniform1f(_shader->getMoveFactorID(), moveFactor);
	_modelWaterTile->renderModel(); // plane high (y = +100000) TODO
}

void Renderer::Renderer::renderDepthMap(Models::ModelPTN0* _modelPTN, Shaders::ShadersIf::ShadersIf* _shader)
{
	glUseProgram(_shader->getShaderProgramID());
	// RENDER MODEL
	_modelPTN->renderDepth(_shader);
	glUseProgram(0);
}

void Renderer::Renderer::renderTerrain(Shaders::ShadersIf::ShadersIf* _shader, 
	                                   Models::ModelTerrain0* _staticModel, 
	                                   Camera::CameraIf::CameraIf* _camera)
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
	
	glm::vec3 lightPositionTerrain(380.0f, 77.0f, 380.0f);
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
	glUniform3f(_shader->getLightColorID(), lightColorTerrain[0], lightColorTerrain[1], lightColorTerrain[2]);
	glUniform1f(_shader->getShineDamperID(), 30.0f);
	glUniform1f(_shader->getReflectivityID(), 0.1f);

	glDrawElements(GL_TRIANGLES, _staticModel->numInd, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	glUseProgram(0);
}

// ...
// RENDER ALL STATIC MODELs
void Renderer::Renderer::renderStaticModels()
{
	for (auto& it : m_vectorModels)
	{
		renderStaticModel(*it);
	}
}

void Renderer::Renderer::renderStaticModel(Models::ModelsIf::ModelsIf& _staticModel)
{
	glBindVertexArray(_staticModel.getModelVAO());

	for (unsigned int i = 0; i < _staticModel.getVectorOfMeshes().size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, _staticModel.getVectorOfMeshes()[i].VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _staticModel.getVectorOfMeshes()[i].IBO);

		// GET SHADER FOR EACH MESH IN MODEL
		glUseProgram(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getShaderProgramID());
		if (!_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getShaderName().compare("ShaderMarker0"))
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0); // VERTs
			glEnableVertexAttribArray(0); // VERTs
										  // VERTEX SHADER UNIFORMS
										  // Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getViewMatrixID(), 1, GL_FALSE, &m_camera.getViewMatrix()[0][0]);
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelMatrixID(), 1, GL_FALSE, &(_staticModel.getModelMatrix()[0][0]));

			GLfloat lightPosition1[] = { 380.0f, 7.0f, 380.0f };
			GLfloat lightColor1[] = { 1.0f, 1.0f, 1.0f };
			GLfloat objectColor1[] = { 1.0f, 1.0f, 1.0f };

			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getLightColorID(), lightColor1[0], lightColor1[1], lightColor1[2]);
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getObjectColorID(), objectColor1[0], objectColor1[1], objectColor1[2]);
			glDrawElements(GL_TRIANGLES, _staticModel.getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			glUseProgram(0);
		}
		else if (!_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getShaderName().compare("ShaderLearningOpenGL0"))
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vert), 0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Loader::Vert), (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

			glEnableVertexAttribArray(0); // VERTEXs
			glEnableVertexAttribArray(1); // NORMALs
										  // VERTEX SHADER UNIFORMS
										  // Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getViewMatrixID(), 1, GL_FALSE, &m_camera.getViewMatrix()[0][0]);
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelMatrixID(), 1, GL_FALSE, &(_staticModel.getModelMatrix()[0][0]));
			glm::mat4 modelInv = glm::inverse(_staticModel.getModelMatrix());
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelMatrixInvID(), 1, GL_FALSE, &modelInv[0][0]);

			// FRAGMENT SHADER UNIFORMs
			// Material
			glm::vec3 materialAmbient(1.0f, 0.5f, 0.31f);
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getMaterialAmbientID(), materialAmbient[0], materialAmbient[1], materialAmbient[2]);
			glm::vec3 materialDiffuse(1.0f, 0.5f, 0.31f);
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getMaterialDiffuseID(), materialDiffuse[0], materialDiffuse[1], materialDiffuse[2]);
			glm::vec3 materialSpecular(0.5f, 0.5f, 0.5f);
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getMaterialSpecularID(), materialSpecular[0], materialSpecular[1], materialSpecular[2]);
			float materialShinines = 32.0f;
			glUniform1f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getMaterialShininessID(), materialShinines);

			// Light (Try sin from tutorial)
			GLfloat lightPosition1[] = { 385.0f, 27.0f, 385.0f };
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getLightPositionID(), lightPosition1[0], lightPosition1[1], lightPosition1[2]);

			glm::vec3 lightAmbient(0.2f, 0.2f, 0.2f);
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getLightAmbientID(), lightAmbient[0], lightAmbient[1], lightAmbient[2]);
			glm::vec3 lightDiffuse(0.5f, 0.5f, 0.5f);
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getLightDiffuseID(), lightDiffuse[0], lightDiffuse[1], lightDiffuse[2]);
			glm::vec3 lightSpecular(1.0f, 1.0f, 1.0f);
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getLightSpecularID(), lightSpecular[0], lightSpecular[1], lightSpecular[2]);

			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getCameraPositionID(), m_camera.getcameraPosition()[0], m_camera.getcameraPosition()[1], m_camera.getcameraPosition()[2]);

			glDrawElements(GL_TRIANGLES, _staticModel.getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			glUseProgram(0);
		}
		else if (!_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getShaderName().compare("ShaderPTN0"))
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

			glEnableVertexAttribArray(0); // VERTEXs
			glEnableVertexAttribArray(1); // TEXTURECOORDs
			glEnableVertexAttribArray(2); // NORMALs
										  // VERTEX SHADER UNIFORMS
										  // Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getViewMatrixID(), 1, GL_FALSE, &m_camera.getViewMatrix()[0][0]);
			m_camera.invertCameraMatrix();
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getViewMatrixInvID(), 1, GL_FALSE, &m_camera.getInvViewMatrix()[0][0]);
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelMatrixID(), 1, GL_FALSE, &(_staticModel.getModelMatrix()[0][0]));
			// TODO: Remove from here
			glm::vec3 lightPositionModelPTN(385.0f, 77.0f, 385.0f);
			glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getLightPositionID(), lightPositionModelPTN[0], lightPositionModelPTN[1], lightPositionModelPTN[2]);
			glm::vec4 planeModelPTN(0.0f, -1.0f, 0.0f, 100000.0f);
			glUniform4f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getPlaneID(), planeModelPTN[0], planeModelPTN[1], planeModelPTN[2], planeModelPTN[3]);
			// FRAGMENT SHADER UNIFORMS
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getLightColorID(), lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
			glUniform1f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getShineDamperID(), 5.0f);
			glUniform1f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getReflectivityID(), 0.1f);

			glUniform1i(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelTextureID(), i);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, _staticModel.getVectorOfMeshes()[i].texture0ID);
			// RENDER MESH
			glDrawElements(GL_TRIANGLES, _staticModel.getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			//
			glUseProgram(0);
		}
		else if (!_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getShaderName().compare("ShaderPTN1"))
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)


			glEnableVertexAttribArray(0); // VERTEXs
			glEnableVertexAttribArray(1); // TEXTURECOORDs
			glEnableVertexAttribArray(2); // NORMALs
										  // VERTEX SHADER UNIFORMS
										  // Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getViewMatrixID(), 1, GL_FALSE, &m_camera.getViewMatrix()[0][0]);
			m_camera.invertCameraMatrix();
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getViewMatrixInvID(), 1, GL_FALSE, &m_camera.getInvViewMatrix()[0][0]);
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelMatrixID(), 1, GL_FALSE, &(_staticModel.getModelMatrix()[0][0]));
			// TODO: Remove from here
			glm::vec3 lightPositionModelPTN(385.0f, 7.0f, 385.0f);
			glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getLightPositionID(), lightPositionModelPTN[0], lightPositionModelPTN[1], lightPositionModelPTN[2]);
			glm::vec4 planeModelPTN(0.0f, -1.0f, 0.0f, 100000.0f);
			glUniform4f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getPlaneID(), planeModelPTN[0], planeModelPTN[1], planeModelPTN[2], planeModelPTN[3]);
			// FRAGMENT SHADER UNIFORMS
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getLightColorID(), lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
			glUniform1f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getShineDamperID(), 25.0f);
			glUniform1f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getReflectivityID(), 5.0f);

			glUniform1i(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelTextureID(), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _staticModel.getVectorOfMeshes()[i].texture0ID);

			glUniform1i(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getSpecularMapID(), 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, _staticModel.getVectorOfMeshes()[i].textureSpecularMap0ID);
			// RENDER MESH
			glDrawElements(GL_TRIANGLES, _staticModel.getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			//
			glUseProgram(0);
		}
		else if (!_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getShaderName().compare("ShaderPTN2"))
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

			glEnableVertexAttribArray(0); // VERTEXs
			glEnableVertexAttribArray(1); // TEXTURECOORDs
			glEnableVertexAttribArray(2); // NORMALs
										  // VERTEX SHADER UNIFORMS
										  // Projection matrix updated in shader constructor (Only once)
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getViewMatrixID(), 1, GL_FALSE, &m_camera.getViewMatrix()[0][0]);
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelMatrixID(), 1, GL_FALSE, &(_staticModel.getModelMatrix()[0][0]));
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getCameraPositionID(), m_camera.getcameraPosition()[0], m_camera.getcameraPosition()[1], m_camera.getcameraPosition()[2]);

			// FRAGMENT SHADER UNIFORMS
			glUniform1i(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelTextureID(), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _staticModel.getVectorOfMeshes()[i].texture0ID);

			glUniform1i(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getSpecularMapID(), 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 15); // Remove hardcoded value
													// RENDER MESH
			glDrawElements(GL_TRIANGLES, _staticModel.getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
			//
			glUseProgram(0);
		}
		else if (!_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getShaderName().compare("ShaderNormalMapPTNT0"))
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
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getViewMatrixID(), 1, GL_FALSE, &m_camera.getViewMatrix()[0][0]);
			// m_camera.invertCameraMatrix();
			// glUniformMatrix4fv(mesh.meshShaderPtr->getViewMatrixInvID(), 1, GL_FALSE, &m_camera.getInvViewMatrix()[0][0]);
			glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelMatrixID(), 1, GL_FALSE, &(_staticModel.getModelMatrix()[0][0]));
			// TODO: Remove from here
			glm::vec3 lightPositionEyeSpace(395.0f, 7.0f, 385.0f);
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getLightPositionEyeSpaceID(), lightPositionEyeSpace[0], lightPositionEyeSpace[1], lightPositionEyeSpace[2]);
			//
			// FRAGMENT SHADER UNIFORMs
			//
			glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);
			glUniform3f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getLightColorID(), lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
			glUniform1f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getShineDamperID(), 15.0f);
			glUniform1f(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getReflectivityID(), 0.2f);

			glUniform1i(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelTextureID(), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _staticModel.getVectorOfMeshes()[i].texture0ID);

			glUniform1i(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getNormalMapID(), 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, _staticModel.getVectorOfMeshes()[i].textureNormalMap0ID);
			// RENDER MESH
			glDrawElements(GL_TRIANGLES, _staticModel.getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
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
