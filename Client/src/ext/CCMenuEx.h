//////////////////////////////////////////////////////////////////////////
//change the CCMenu
//when there is a touch event
//but there follows an move
//don't echo the event
//go on dispatch it
//////////////////////////////////////////////////////////////////////////

#ifndef __CCMENU_EX_H__
#define __CCMENU_EX_H__

#include "cocos2d.h"
using namespace cocos2d;

#define MOVE_RANGE 10 //ignore the move if its very little to make the user feel more comfortable

class CCMenuEx : public CCMenu
{
public:
	CCMenuEx();
	//this memeber function must be overwrite to create the object of the CCMenuEx type
	//the static function will be used like a global function
	//if we use its parent class's static init function we will creates one object of its parent 
	static CCMenuEx* create();
	static CCMenuEx* create(CCMenuItem* item);
	static CCMenuEx* create(CCMenuItem* item, ...);
	static CCMenuEx* createWithItems(CCMenuItem *firstItem, va_list args);
	static CCMenuEx* createWithArray(CCArray* pArrayOfItems);

	void setTouchPriority(int priority);
	

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch *touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

	//register the touch type as Targeted, and don't swallow it
	virtual void registerWithTouchDispatcher();

protected:
	short m_nMovedCnt; //record how many move events the menu has received
	int m_nPriority;
};
	

#endif  // __CCMENU_EX_H__