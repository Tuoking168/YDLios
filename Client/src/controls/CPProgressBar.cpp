#include "CPProgressBar.h"
#include "cocos2d.h"

using namespace cocos2d;

#define   DT	0.05f

CPProgressBar::CPProgressBar()
	:mProgress(NULL)
	,mHead(NULL)
	,mTail(NULL)
	,mfp(0)
	,mdfp(0)
{

}

CPProgressBar::~CPProgressBar()
{

}

CPProgressBar * CPProgressBar::create( cocos2d::CCSprite *body )
{
	return create(body, NULL, NULL);
}

CPProgressBar * CPProgressBar::create( cocos2d::CCSprite *body, cocos2d::CCNode *nHead, cocos2d::CCNode *nTail )
{
	CPProgressBar *ret = new CPProgressBar;
	if (ret && ret->initWithData(body, nHead, nTail))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool CPProgressBar::initWithData( cocos2d::CCSprite *body, cocos2d::CCNode *nHead, cocos2d::CCNode *nTail )
{
	if (!CCNode::init())
	{
		return false;
	}

	if (!body)
	{
		return false;
	}

	//
	mProgress = CCProgressTimer::create(body);
	mProgress->setType(kCCProgressTimerTypeBar);
	mProgress->setMidpoint(ccp(0, 0.5f));
	mProgress->setBarChangeRate(ccp(1, 0));
	addChild(mProgress);

	mHead = nHead;
	mTail = nTail;

	CCSize totalSize = body->getContentSize();
	CCSize tailSize = CCSizeZero;
	if (mTail)
	{
		tailSize = mTail->getContentSize();
		totalSize.width += tailSize.width;
		if (tailSize.height > totalSize.height)
		{
			totalSize.height = tailSize.height;
		}
	}

	if (mHead)
	{
		CCSize headSize = mHead->getContentSize();
		totalSize.width += headSize.width/2;
		if (headSize.height > totalSize.height)
		{
			totalSize.height = headSize.height;
		}
	}

	if(mTail)
	{
		mTail->setAnchorPoint(ccp(0, 0.5f));
		mTail->setPosition(ccp(0, totalSize.height/2));
		addChild(mTail);
	}

	mProgress->setAnchorPoint(ccp(0, 0.5f));
	mProgress->setPosition(ccp(tailSize.width, totalSize.height/2));

	if(nHead)
	{
		nHead->setAnchorPoint(ccp(0.5f, 0.5f));
		nHead->setPosition(ccp(0, totalSize.height/2));
		addChild(nHead);
	}

	//
	setContentSize(totalSize);
	setAnchorPoint(ccp(0.5f, 0.5f));

	return true;
}

void CPProgressBar::setPercentage( float fp )
{
	mProgress->setPercentage(fp);
	short dp = getPercentage();
	if(dp >= 1)
	{
		float x = 0;
		CCNode *sp = mTail;
		if(sp)
		{
			x = sp->getContentSize().width;
			if(!sp->isVisible()) sp->setVisible(true);
		}

		sp = mHead;
		if(sp)
		{
			if(!sp->isVisible()) sp->setVisible(true);
			x += mProgress->getContentSize().width * dp/100.0f;
			sp->setPositionX(x - 1);
		}
	}
	else
	{
		if(mHead)	mHead->setVisible(false);
		if(mTail)	mTail->setVisible(false);
	}
}

float CPProgressBar::getPercentage( void )
{
	return mProgress->getPercentage();
}

void CPProgressBar::runProgressTo( float dt, float fp )
{
	if(dt > 0 && fp >= 0)
	{
		unschedule(schedule_selector(CPProgressBar::doUpdate));
		if(fp > 100) fp = 100;
		if(fp != getPercentage())
		{
			mfp  = fp;
			mdfp = (fp - getPercentage()) * DT/dt;
			schedule(schedule_selector(CPProgressBar::doUpdate), DT);
		}		
	}	
}

void CPProgressBar::doUpdate( float dt )
{
	setPercentage(getPercentage() + mdfp);
	float fp = getPercentage();
	if(mdfp < 0)
	{
		if(fp <= mfp)
		{
			unschedule(schedule_selector(CPProgressBar::doUpdate));
		}
	}
	else
	{
		if(fp >= mfp)
		{
			unschedule(schedule_selector(CPProgressBar::doUpdate));
		}
	}
}

