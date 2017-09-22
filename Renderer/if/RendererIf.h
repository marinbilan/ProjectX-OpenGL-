#ifndef RENDERERIF__
#define RENDERERIF__

#include "..\..\Camera\if\CameraIf.h"
#include "..\..\Camera\inc\Camera.h"
#include "..\..\Shaders\if\ShaderIf.h"
#include "..\..\Models\if\ModelIf.h"


#include "..\..\Models\inc\Model_skyBox.h"
#include "..\..\Models\inc\Model_Water_Tile.h"
#include "..\..\Models\inc\ModelPTN.h"
#include "..\..\Models\inc\ModelLearnOpenGL.h"

namespace Renderer
{
namespace RendererIf
{
class RendererIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs [ DO not need constructor in interface class! ] RendererIf() {}
	virtual ~RendererIf()
	{
		std::cout << "RendererIf destructor called!" << std::endl;
	}
	// FUNCTIONs
	virtual void renderSkyBox(Camera::Camera* _camera, 
		                      Models::Model_skyBox* _skyBox) {}
	virtual void renderWater(Shaders::ShadersIf::ShadersIf* _shader, 
		                     Models::Model_Water_Tile* _modelWaterTile) {};
	virtual void renderModelPTN(GLfloat* _planeModelPTN, 
		                        Camera::Camera* _camera, 
		                        Models::ModelPTN* _modelPTN, 
		                        Shaders::ShadersIf::ShadersIf* _shader) {}
	virtual void renderDepthMap(Models::ModelPTN* _modelPTN, Shaders::ShadersIf::ShadersIf* _shader) {}
	virtual void renderModelLearningOpenGL(Shaders::ShadersIf::ShadersIf* _shader,
		                                   Camera::Camera* _camera,
		                                   Models::ModelLearnOpenGL* _modelLearningOpenGL) {}
	// NEW
	virtual void renderStaticModel(GLfloat* _planeModelPTN,
		                           Camera::Camera* _camera, 
		                           Models::ModelsIf::ModelsIf* _staticModel,
		                           Shaders::ShadersIf::ShadersIf* _shader) {}
	// OPERATORs	
};
}
}
#endif