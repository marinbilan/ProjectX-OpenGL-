// SHADERS DB
#include "..\..\Db\ShadersDb\shadersDB.h"

// SHADERS [ Projection ]
#include "Shaders\if\ShaderIf.h"

#include "Shaders\inc\ShaderSkyBox0.h"
#include "Shaders\inc\ShaderWaterTile0.h"
#include "Shaders\inc\ShaderLearningOpenGL0.h"
#include "Shaders\inc\ShaderPTN0.h"
#include "Shaders\inc\ShaderGUI0.h"
// CAMERA [ View ]
#include "Camera\if\CameraIf.h"

#include "Camera\inc\Camera.h"
// MODELs [ Model ]
#include "Models\if\ModelIf.h"

#include "Models\inc\ModelSkyBox0.h"
#include "Models\inc\ModelWaterTile0.h"
#include "Models\inc\ModelLearnOpenGL0.h"
#include "Models\inc\ModelPTN0.h"
#include "Models\inc\ModelGUI0.h"
// LOADER
#include "Loader\if\LoaderIf.h"

#include "Loader\inc\TextureLoader.h"
#include "Loader\inc\ModelLoader.h"
#include "Loader\inc\ModelLoaderLearningOpenGL.h"
#include "FBOs\inc\WaterFBO.h"
// RENDERER
#include "Renderer\inc\Renderer.h"
// FBO
#include "FBOs\if\FBOIf.h"

#include "FBOs\inc\FBOShaddowMapping.h"
// CONTROLS