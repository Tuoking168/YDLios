#ifndef __GENERAL_MENU_H__
#define __GENERAL_MENU_H__

/*
功能：可以放入任意Node类型对象的容器。
*/

#include "cocos2d.h"
USING_NS_CC;

class GeneralMenu : public CCMenu
{
public:
	GeneralMenu();
	static GeneralMenu* create();
	virtual bool init();
	~GeneralMenu();

public:
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void addChild(CCNode * child);
	virtual void addChild(CCNode * child, int zOrder);
    virtual void addChild(CCNode * child, int zOrder, int tag);
	virtual void removeChild(CCNode* child, bool cleanup);
	virtual void registerWithTouchDispatcher();

public:
	virtual void show();

protected:
    virtual CCMenuItem* itemForTouch(CCTouch * touch);
};

#endif//__GENERAL_MENU_H__