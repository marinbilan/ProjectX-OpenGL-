#ifndef RENDERERIF__
#define RENDERERIF__

#include "..\..\Camera\if\CameraIf.h"
#include "..\..\Shaders\if\ShaderIf.h"
#include "..\..\Models\if\ModelIf.h"

// TODO: Remove this
#include "..\..\Models\inc\ModelSkyBox0.h"
#include "..\..\Models\inc\ModelWaterTile0.h"
#include "..\..\Models\inc\ModelPTN0.h"
#include "..\..\Models\inc\ModelLearnOpenGL0.h"
#include "..\..\Models\inc\ModelTerrain0.h"

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
	virtual void renderSkyBox(Camera::CameraIf::CameraIf* _camera,
		                      Models::ModelSkyBox0* _skyBox) {}
	virtual void renderWater(Shaders::ShadersIf::ShadersIf* _shader, 
		                     Models::ModelWaterTile0* _modelWaterTile) {};
	virtual void renderModelPTN(GLfloat* _planeModelPTN, 
		                        Camera::CameraIf::CameraIf* _camera,
		                        Models::ModelPTN0* _modelPTN, 
		                        Shaders::ShadersIf::ShadersIf* _shader) {}
	virtual void renderDepthMap(Models::ModelPTN0* _modelPTN, Shaders::ShadersIf::ShadersIf* _shader) {}
	// NEW
	virtual void renderStaticModel(std::shared_ptr<Models::ModelsIf::ModelsIf> _staticModel, Camera::CameraIf::CameraIf* _camera) {}
	// OPERATORs	
};
}
}
#endif