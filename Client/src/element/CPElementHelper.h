#ifndef __CPElementHelper_h__
#define __CPElementHelper_h__

#include "utils/MacroUtils.h"

namespace AnimType
{
	enum
	{
		null = 0,

		cloth = 1,
		weapon = 2,	
		wings = 3,
		yuanshen = 4,//元神外观
		horse = 5,
		horsehead = 6,

		pet = 10,
		npc = 11,
		monster = 12,
		slave = 13,

		effect = 20,
	};
}
class CCFlashAnimation;
class CPElementHelper
{
public:
	static CCFlashAnimation *getAnim(int animType, int id, int animState);

private:
	CP_MAKE_STATIC_CLASS(CPElementHelper);
};

#endif //__CPElementHelper_h__