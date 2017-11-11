#ifndef RENDERER__
#define RENDERER__

#include "..\if\RendererIf.h"

namespace Renderer
{ 
class Renderer : public RendererIf::RendererIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	Renderer();
	// FUNCTIONs
	virtual void renderSkyBox(Camera::CameraIf::CameraIf* _camera,
		                      Models::ModelSkyBox0* _skyBox);
	virtual void renderWater(Shaders::ShadersIf::ShadersIf* _shader, 
		                     Models::ModelWaterTile0* _modelWaterTile);
	virtual void renderModelPTN(GLfloat* _planeModelPTN, 
		                        Camera::CameraIf::CameraIf* _camera,
		                        Models::ModelPTN0* _modelPTN, 
		                        Shaders::ShadersIf::ShadersIf* _shader);
	virtual void renderDepthMap(Models::ModelPTN0* _modelPTN, Shaders::ShadersIf::ShadersIf* _shader);
	// NEW
	virtual void renderTerrain(Shaders::ShadersIf::ShadersIf* _shader, Models::ModelTerrain0* _staticModel, Camera::CameraIf::CameraIf* _camera);
	virtual void renderStaticModel(std::shared_ptr<Models::ModelsIf::ModelsIf> _staticModel, Camera::CameraIf::CameraIf* _camera);
	// OPERATORs
private:
	GLfloat distance;
	GLfloat lightPositionModelPTN[3];
	GLfloat lightColorModelPTN[3];
	GLfloat planeModelPTN[4]; //  = { 0.0f, -1.0f, 0.0f, 100000.0f };

	GLfloat moveFactor = 0;
	GLfloat WAVE_SPEED;
};
}
#endif