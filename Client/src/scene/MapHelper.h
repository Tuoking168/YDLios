#ifndef __MapHelper_h__
#define __MapHelper_h__

#include "CCNode.h"
#include "utils/MacroUtils.h"

namespace MapSignType
{
	enum
	{
		me,
		player,
		monster,
		pet,
		npc,
		target_pos,
		portal,
		boss,
	};
}

class MapHelper
{
public:
	static cocos2d::CCNode *getSignNode( int signType );

private:
	CP_MAKE_STATIC_CLASS(MapHelper);
};

#endif //__MapHelper_h__