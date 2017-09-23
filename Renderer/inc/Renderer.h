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
	virtual void renderSkyBox(Camera::Camera* _camera, 
		                      Models::Model_skyBox* _skyBox);
	virtual void renderWater(Shaders::ShadersIf::ShadersIf* _shader, 
		                     Models::Model_Water_Tile* _modelWaterTile);
	virtual void renderModelPTN(GLfloat* _planeModelPTN, 
		                        Camera::Camera* _camera,
		                        Models::ModelPTN* _modelPTN, 
		                        Shaders::ShadersIf::ShadersIf* _shader);
	virtual void renderDepthMap(Models::ModelPTN* _modelPTN, Shaders::ShadersIf::ShadersIf* _shader);
	virtual void renderModelLearningOpenGL(Camera::Camera* _camera,  
		                                   Shaders::ShadersIf::ShadersIf* _shader,
		                                   Models::ModelLearnOpenGL* _modelLearningOpenGL);
	// NEW
	virtual void renderStaticModel(GLfloat* _planeModelPTN,
		                           Camera::CameraIf::CameraIf* _camera,
		                           Models::ModelsIf::ModelsIf* _staticModel,
		                           Shaders::ShadersIf::ShadersIf* _shader);
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