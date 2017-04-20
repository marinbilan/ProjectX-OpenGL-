//
// Shaders [ Projection ]
//
#include "..\Shaders\if\ShaderIf.h"

#include "..\Shaders\inc\Shader_PNT.h" // VANQUISH ASSIMP PNT  < pos, norms, texCords >
									   // VERTEX SHADER        | proj, view, viewInv, transform, lightPos |
									   // FRAGMENT SHADER      | modelTexture, lightColour, shineDamper, reflectivity |
#include "..\Shaders\inc\Shader_Water.h"
#include "..\Shaders\inc\Shader_Water_Tile.h"

#include "..\Shaders\inc\Shader_7.h"   // ASSIMP and NORMAL MAPPING
#include "..\Shaders\inc\Shader_1.h"   // MODEL         PN  [ PROJECTION ]    <pos, norms | proj, view, model | light, normsRot>
#include "..\Shaders\inc\Shader_2.h"   // GUI           P   [ NO PROJECTION ] <pos | model >
#include "..\Shaders\inc\Shader_3.h"   // SKYBOX        P   [ PROJECTION ]    <pos | proj, view >