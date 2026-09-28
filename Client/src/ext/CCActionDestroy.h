#ifndef __CC_ACTION_DESTROY_EXT__
#define __CC_ACTION_DESTROY_EXT__

#include <string>
#include "cocos2d.h"
//#include "selector_protocol.h"

using namespace cocos2d;

class CCActionInstantRemoveFromParent : public cocos2d::CCActionInstant
{
	public:
		CCActionInstantRemoveFromParent(){}
		virtual ~CCActionInstantRemoveFromParent();
		/** creates a Place action with a position */
		static CCActionInstantRemoveFromParent * create();
		//super methods
		virtual void startWithTarget(CCNode *pTarget);
};

class CCActionInstantRemoveFromParentEx : public cocos2d::CCActionInstant
{
public:
	CCActionInstantRemoveFromParentEx(){}
	virtual ~CCActionInstantRemoveFromParentEx(){}
	/** creates a Place action with a position */
	static CCActionInstantRemoveFromParentEx * create(CCNode* pTarget);
	/** Initializes a Place action with a position */
	bool initWithTarget(CCNode* pTarget);
	//super methods
	virtual void startWithTarget(CCNode *pTarget);
protected:
	CCNode*	m_pTargetTarget;
};



#endif
