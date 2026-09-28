#include "GameMap.h"

using namespace cocos2d;


// on "init" you need to initialize your instance
bool GameMap::init()
{
	if (!CCLayerColor::init())
	{
		return false;
	}
	CCLog("init map end!");
	return true;
}

