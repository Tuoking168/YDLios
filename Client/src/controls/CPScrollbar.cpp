#include "CPScrollbar.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace cocos2d::extension;

CPScrollbar::CPScrollbar()
	:mBar(NULL)
	,mArea(CCSizeZero)
	,mVertical(true)
	,mMaxPosition(0)
	,mCurrentPosition(0)
{

}

CPScrollbar::~CPScrollbar()
{

}

CPScrollbar * CPScrollbar::create( CCScale9Sprite *bar, CCSize size )
{
	return create(bar, size, true);
}

CPScrollbar * CPScrollbar::create( CCScale9Sprite *bar, CCSize size, bool vertical )
{
	CPScrollbar *ret = new CPScrollbar;
	if (ret && ret->initWithData(bar, size, vertical))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool CPScrollbar::initWithData( CCScale9Sprite *bar, CCSize size, bool vertical )
{
	if (!CCNode::init())
	{
		return false;
	}

	if (bar && size.width > 0 && size.height > 0)
	{
		mBar = bar;
		mArea = size;
		mVertical = vertical;

		initUI();

		setContentSize(size);
		setAnchorPoint(ccp(0.5f, 0.5f));
		setPosition(CCPointZero);

		return true;
	}
	return false;
}

void CPScrollbar::initUI()
{
	mBar->setPosition(ccp(mArea.width/2, mArea.height/2));
	addChild(mBar);
}

void CPScrollbar::setMaxPosition( float pos )
{
	mMaxPosition = pos;
	if (mMaxPosition < 0)
	{
		mMaxPosition = 0;
	}
}

void CPScrollbar::setCurrentPosition( float pos )
{
	mCurrentPosition = pos;
	if (mCurrentPosition < 0)
	{
		mCurrentPosition = 0;
	}
	else if (mCurrentPosition > mMaxPosition)
	{
		mCurrentPosition = mMaxPosition;
	}
}

void CPScrollbar::refreshUI()
{
	if (mMaxPosition < 1)
	{
		mBar->setVisible(false);
		return;
	}

	const float posPercent = (mMaxPosition - mCurrentPosition)/mMaxPosition;
	if (mVertical)
	{
		float percent = mArea.height/(mArea.height + mMaxPosition);
		float barLen = mArea.height * percent;
		mBar->setContentSize(CCSizeMake(mArea.width, barLen));

		float y = (mArea.height - barLen) * posPercent + barLen/2;
		mBar->setPosition(ccp(mArea.width/2, y));
	}
	else
	{
		float percent = mArea.width/(mArea.width + mMaxPosition);
		float barLen = mArea.width * percent;
		mBar->setContentSize(CCSizeMake(barLen, mArea.height));

		float x = (mArea.width - barLen) * (1 - posPercent) + barLen/2;
		mBar->setPosition(ccp(x, mArea.height/2));
	}
	mBar->setVisible(true);
}

void CPScrollbar::visit()
{
	refreshUI();
	CCNode::visit();
}

