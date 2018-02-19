#pragma once
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
	virtual void renderSkyBox(Models::ModelSkyBox0& _skyBox) {}
	virtual void renderWater(Shaders::ShadersIf::ShadersIf* _shader, 
		                     Models::ModelWaterTile0* _modelWaterTile) {};
	virtual void renderDepthMap(Models::ModelPTN0* _modelPTN, 
		                        Shaders::ShadersIf::ShadersIf* _shader) {}

	// ...
	virtual void renderStaticModels() {}
	virtual void renderStaticModel(Models::ModelsIf::ModelsIf& _staticModel) {}

	// OPERATORs	
};
}
}