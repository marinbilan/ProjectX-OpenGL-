#pragma once
#include "..\if\RendererIf.h"

namespace Renderer
{ 
class Renderer : public RendererIf::RendererIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	Renderer(Camera::CameraIf::CameraIf& camera,
		     std::vector<Shaders::ShadersIf::ShadersIf*>& vectorShaders, 
		     std::vector<Models::ModelsIf::ModelsIf*>& vectorModels);

	// FUNCTIONs
	virtual void renderSkyBox(Models::ModelSkyBox0& _skyBox);
	virtual void renderWater(Shaders::ShadersIf::ShadersIf* _shader, 
		                     Models::ModelWaterTile0* _modelWaterTile);
	virtual void renderDepthMap(Models::ModelPTN0* _modelPTN, 
		                        Shaders::ShadersIf::ShadersIf* _shader);
	virtual void renderTerrain(Shaders::ShadersIf::ShadersIf* _shader, 
		                       Models::ModelTerrain0* _staticModel, 
		                       Camera::CameraIf::CameraIf* _camera);

	// ...
	void renderStaticModels();
	void renderStaticModel(Models::ModelsIf::ModelsIf& _staticModel);
	// OPERATORs

private:
	Camera::CameraIf::CameraIf& m_camera;
	std::vector<Shaders::ShadersIf::ShadersIf*> m_vectorShaders;
	std::vector<Models::ModelsIf::ModelsIf*> m_vectorModels;

	// TODO: remove
	GLfloat distance;
	GLfloat lightPositionModelPTN[3];
	GLfloat lightColorModelPTN[3];
	GLfloat planeModelPTN[4]; //  = { 0.0f, -1.0f, 0.0f, 100000.0f };

	GLfloat moveFactor = 0;
	GLfloat WAVE_SPEED;
};
}