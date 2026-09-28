#include "CPDelayRefresh.h"
#include "cocos2d.h"

using namespace cocos2d;


CPDelayRefresh::CPDelayRefresh()
	:mHandler(NULL)
	,mHandleFunc(NULL)
	,mDelayTime(0.5f)
{

}

CPDelayRefresh::~CPDelayRefresh()
{

}

CPDelayRefresh * CPDelayRefresh::create( cocos2d::CCObject *target, cocos2d::SEL_CallFunc func )
{
	CPDelayRefresh *ret = new CPDelayRefresh;
	if (ret && ret->initWithData(target, func))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool CPDelayRefresh::initWithData( cocos2d::CCObject *target, cocos2d::SEL_CallFunc func )
{
	if (!CCNode::init())
	{
		return false;
	}

	if (target && func)
	{
		mHandler = target;
		mHandleFunc = func;
		return true;
	}
	return false;
}

void CPDelayRefresh::setDelayTime( float dt )
{
	mDelayTime = dt;
	if (mDelayTime < 0)
	{
		mDelayTime = 0;
	}
}

void CPDelayRefresh::refresh()
{
	stopAllActions();

	CCDelayTime *dl = CCDelayTime::create(mDelayTime);
	CCCallFunc *func = CCCallFunc::create(mHandler, mHandleFunc);
	CCAction *action = CCSequence::create(dl, func, NULL);
	runAction(action);
}
