#ifndef FBOSHADDOWMAPPING__
#define FBOSHADDOWMAPPING__
// ModelIf
#include "../if/FBOIf.h"

namespace FBOs
{
class FBOShaddowMapping : public FBOIf::FBOIf
{
public:
	// CONSTRUCTORs / DESTRUCTORs
	FBOShaddowMapping(int _shadowWidth, int _shadowHeight, int _screenWidth, int _screenHeight);
	~FBOShaddowMapping();
	// FUNCTIONs
	virtual void createFBOShadowMapping();
	virtual void bindFBOShadowMapping();
	virtual void unbindFBOShadowMapping();
	virtual GLuint getFBOShadowMapID();
	virtual GLuint getFBOShadowMapTextureID();
	// OPERATORs
	friend std::ostream& operator<<(std::ostream& output, FBOShaddowMapping& info)
	{
		return output;
	}
private:
	int shadowWidth;
	int shadowHeight;
	int screenWidth;
	int screenHeight;
	GLuint FBOShadowMapID;
	GLuint FBOShadowMapTextureID; // Depth Map
	};
}

#endif
