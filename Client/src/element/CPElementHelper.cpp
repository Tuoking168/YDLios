#include "CPElementHelper.h"
#include "CCCommon.h"
#include <string>

#include "res/CPAnimationManager.h"

#include "script/LuaWrapper.h"

#include "userdata/StaticData.h"


using namespace cocos2d;


/////////CPElementHelper///////////////////////////////////////////
CCFlashAnimation * CPElementHelper::getAnim( int animType, int id, int animState )
{
	std::string animPath;
	StaticData::getAnimPath(animType, id, animState, animPath);
	if (!animPath.empty())
	{
		return CPAnimMnger.getAnimationMultDir(animPath);
	}
	return NULL;
}
