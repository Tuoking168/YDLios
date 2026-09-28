#ifndef __CPUpdater_h__
#define __CPUpdater_h__

#include "CCNode.h"

typedef void (cocos2d::CCObject::*SEL_CPUpdater)(int);
#define cpupdater_selector(_SELECTOR) (SEL_CPUpdater)(&_SELECTOR)
class CPUpdater : public cocos2d::CCNode
{
public:
	CPUpdater();
	~CPUpdater();

public:
	static CPUpdater *create(cocos2d::CCObject *target, SEL_CPUpdater func);

	void setUpdateTimes(int times);
	void start();

	void setFinishHandler(cocos2d::CCObject *target, cocos2d::SEL_CallFunc func);

private:
	bool initWithData(cocos2d::CCObject *target, SEL_CPUpdater func);
	void updateTarget();
	void visit();

private:
	cocos2d::CCObject *mTarget;
	cocos2d::CCObject *mFinishTarget;
	SEL_CPUpdater mHandleFunc;
	cocos2d::SEL_CallFunc mFinishHandleFunc;

	int mState;
	int mCurrentIndex;
	int mTimes;
};

#endif //__CPUpdater_h__