#include "CPUpdater.h"
#include "cocos2d.h"

using namespace cocos2d;

namespace CPUpdaterState
{
	enum
	{
		stop = 0,
		start = 1,
	};
}

CPUpdater::CPUpdater()
	:mTarget(NULL)
	,mFinishTarget(NULL)
	,mHandleFunc(NULL)
	,mFinishHandleFunc(NULL)
	,mState(CPUpdaterState::stop)
	,mCurrentIndex(0)
	,mTimes(0)
{

}

CPUpdater::~CPUpdater()
{

}

CPUpdater * CPUpdater::create( CCObject *target, SEL_CPUpdater func )
{
	CPUpdater *ret = new CPUpdater;
	if (ret && ret->initWithData(target, func))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool CPUpdater::initWithData( CCObject *target, SEL_CPUpdater func )
{
	if (!CCNode::init())
	{
		return false;
	}

	if (target && func)
	{
		mTarget = target;
		mHandleFunc = func;
		return true;
	}
	return false;
}

void CPUpdater::setUpdateTimes( int times )
{
	mTimes = times;
	if (mTimes < 0)
	{
		mTimes = 0;
	}
}

void CPUpdater::start()
{
	mCurrentIndex = 0;
	mState = CPUpdaterState::start;
}

void CPUpdater::setFinishHandler( CCObject *target, SEL_CallFunc func )
{
	mFinishTarget = target;
	mFinishHandleFunc = func;
}

void CPUpdater::updateTarget()
{
	if (mState == CPUpdaterState::start)
	{
		if (mCurrentIndex < mTimes)
		{
			(mTarget->*mHandleFunc)(mCurrentIndex);
			mCurrentIndex++;
		}
		else
		{
			mState = CPUpdaterState::stop;
			if (mFinishTarget && mFinishHandleFunc)
			{
				(mFinishTarget->*mFinishHandleFunc)();
			}
		}
	}
}

void CPUpdater::visit()
{
	updateTarget();
	CCNode::visit();
}
