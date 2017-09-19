//
// Shaders [ Projection ]
//
#include "..\Shaders\if\ShaderIf.h"

#include "..\Shaders\\inc\ShaderLearningOpenGL1.h"

#include "..\Shaders\inc\ShaderPTN.h" // VANQUISH ASSIMP PNT  < pos, norms, texCords >
									   // VERTEX SHADER        | proj, view, viewInv, transform, lightPos |
									   // FRAGMENT SHADER      | modelTexture, lightColour, shineDamper, reflectivity |
#include "..\Shaders\inc\Shader_Water_Tile.h"
#include "..\Shaders\inc\Shader_2.h"   // GUI           P   [ NO PROJECTION ] <pos | model >
#include "..\Shaders\inc\Shader_3.h"   // SKYBOX        P   [ PROJECTION ]    <pos | proj, view >
#include "..\Shaders\inc\ShaderDepthMapFBO.h"
