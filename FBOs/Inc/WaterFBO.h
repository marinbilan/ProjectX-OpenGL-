#ifndef WATERFBO__
#define WATERFBO__
//
// ModelIf
//
#include "../if/FBOIf.h"

namespace FBOs
{
class WaterFBO : public FBOIf::FBOIf
{
public:
	//
	// CONSTRUCTORs / DESTRUCTORs
	//
	WaterFBO();

	~WaterFBO();
	//
	// FUNCTIONs
	// 
	virtual void bindReflectionFrameBuffer();
	virtual void bindRefractionFrameBuffer();
	virtual void unbindCurrentFrameBuffer();
	virtual int getReflectionTexture();
	virtual int getRefractionTexture();
	virtual int getRefractionDepthTexture();
	virtual void initialiseReflectionFrameBuffer();
	virtual void initialiseRefractionFrameBuffer();
	virtual void bindFrameBuffer(int frameBuffer, int width, int height);
	virtual int createFrameBuffer();
	int createTextureAttachment(int width, int height);
	int createDepthTextureAttachment(int width, int height);
	int createDepthBufferAttachment(int width, int height);
	//
	// OPERATORs
	//
	friend std::ostream& operator<<(std::ostream& output, WaterFBO& info)
	{
		return output;
	}

private:
	int REFLECTION_WIDTH;
	int REFLECTION_HEIGHT;

	int REFRACTION_WIDTH;
	int REFRACTION_HEIGHT;

	int reflectionFrameBuffer;
	int reflectionTexture;
	int reflectionDepthBuffer;

	int refractionFrameBuffer;
	int refractionTexture;
	int refractionDepthTexture;
	//
	// CONSTRUCTOR params
	//
	};
}

#endif
