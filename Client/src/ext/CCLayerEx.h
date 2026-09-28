//////////////////////////////////////////////////////////////////////////
//change the CCMenu
//when there is a touch event
//but there follows an move
//don't echo the event
//go on dispatch it
//////////////////////////////////////////////////////////////////////////

#ifndef __CC_LAYER_EX_H__
#define __CC_LAYER_EX_H__

#include "cocos2d.h"
using namespace cocos2d;

class CCLayerEx : public CCLayer
{
public:
	CCLayerEx();

	void onEnter();

	virtual void registerWithTouchDispatcher();
	void setHandlerPriority(int newPriority);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent); return true;};
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}

	CREATE_FUNC(CCLayerEx);
};
	
class CCLayerWithMask : public CCLayerEx
{
public:
	CCLayerWithMask();

	virtual void onEnter();

	CREATE_FUNC(CCLayerWithMask);
protected:
	CCSprite*	m_theMask;
};

#endif  // __CCMENU_EX_H__