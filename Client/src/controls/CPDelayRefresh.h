#ifndef __CPDelayRefresh_h__
#define __CPDelayRefresh_h__

#include "CCNode.h"

class CPDelayRefresh : public cocos2d::CCNode
{
public:
	CPDelayRefresh();
	~CPDelayRefresh();

public:
	static CPDelayRefresh *create(cocos2d::CCObject *target, cocos2d::SEL_CallFunc func);

	void setDelayTime(float dt);
	void refresh();

private:
	bool initWithData(cocos2d::CCObject *target, cocos2d::SEL_CallFunc func);

private:
	cocos2d::CCObject *mHandler;
	cocos2d::SEL_CallFunc mHandleFunc;

	float mDelayTime;
};

#endif //__CPDelayRefresh_h__