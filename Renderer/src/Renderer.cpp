#include "../inc/Renderer.h"
//
// CONSTRUCTORs / DESTRUCTORs
//
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