#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
// GLEW //
#include "..\..\__libs\glew-1.13.0\include\GL\glew.h"
// GLFW
#include "..\..\__libs\glfw-3.2.1.bin.WIN32\include\GLFW\glfw3.h"
// GLM
#include "..\..\__libs\glm\glm\glm.hpp"
#include "..\..\__libs\glm\glm\gtc\matrix_transform.hpp"
// FREEIMAGE
#include "..\..\__libs\FreeImage\include\FreeImage.h"
// SHADERS DB
#include "..\..\Db\ShadersDb\shadersDB.h"


// SHADERS [ Projection ]
#include "Shaders\if\ShaderIf.h"
#include "Shaders\\inc\ShaderLearningOpenGL1.h"
#include "Shaders\inc\ShaderPTN.h" 
#include "Shaders\inc\Shader_Water_Tile.h"
#include "Shaders\inc\Shader_2.h"   
#include "Shaders\inc\Shader_3.h"
#include "Shaders\inc\ShaderDepthMapFBO.h"
// CAMERA [ View ]
#include "Camera\if\CameraIf.h"
#include "Camera\inc\Camera.h"
// MODELs [ Model ]
#include "Models\if\ModelIf.h"
#include "Models\inc\ModelPTN.h"
#include "Models\inc\Model_skyBox.h"
#include "Models\inc\Model_Water_Tile.h"
#include "Models\inc\Model_GUI.h"
#include "Models\inc\ModelLearnOpenGL.h"
// WATER FBO
#include "Water\WaterFrameBuffers.h"
// LOADER
#include "Loader\if\LoaderIf.h"
#include "Loader\inc\TextureLoader.h"
#include "Loader\inc\ModelLoader.h"
#include "FBOs\Inc\WaterFBO.h"
#include "Renderer\inc\Renderer.h"
// FBO
#include "FBOs\if\FBOIf.h"
#include "FBOs\inc\WaterFBO.h"
#include "FBOs\inc\FBOShaddowMapping.h"
// CONTROLS
//#include "Controls\Contorls.h"