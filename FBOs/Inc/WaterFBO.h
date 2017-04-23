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

	//
	// OPERATORs
	//
	friend std::ostream& operator<<(std::ostream& output, WaterFBO& info)
	{
		return output;
	}

private:
	//
	// CONSTRUCTOR params
	//
	};
}

#endif
