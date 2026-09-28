#ifndef __GAME_ALIVE__
#define __GAME_ALIVE__

#include "cocos2d.h"

using namespace cocos2d;



class GameAlive : public CCLayer
{
public:
	GameAlive();
	~GameAlive();
	virtual bool init();
	virtual void sortAllChildren();

	CREATE_FUNC(GameAlive);
};



#endif //__GAME_ALIVE__