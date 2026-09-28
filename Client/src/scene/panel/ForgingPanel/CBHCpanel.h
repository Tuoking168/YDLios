#ifndef _CBHCpanel_H_
#define _CBHCpanel_H_	
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;



class CBHCpanel : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
public:
	CBHCpanel(void);
	~CBHCpanel(void);
	static CBHCpanel* create();
	//CREATE_FUNC(CBHCpanel);
	virtual bool init(const char* filename);

private:
	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void visit();
};

#endif//_CBHCpanel_H_