#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__


#include "cocos2d.h"

using namespace cocos2d;

class GameMap : public CCLayerColor
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static node()" method manually
    CREATE_FUNC(GameMap);

public:
};
#endif//__GAME_MAP_H__