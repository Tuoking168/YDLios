#include "TouchCover.h"

TouchCover::TouchCover()
{
	m_nPriority = kCCMenuHandlerPriority;
}

TouchCover* TouchCover::create( CCRect& innerRect,CCRect& outlineRect /*= CCRectMake(0,0,480,800)*/ )
{
	TouchCover* pTouchCover = new TouchCover();
	if(pTouchCover && pTouchCover->initWithRect(innerRect,outlineRect))
	{
		pTouchCover->autorelease();
		return pTouchCover;
	}
	return NULL;
}

bool TouchCover::initWithRect( CCRect& innerRect,CCRect& outlineRect )
{
	m_innnerRect = innerRect;
	m_outlineRect = outlineRect;
	setAnchorPoint(CCPointZero);
	setPosition(CCPointZero);
	return true;
}

bool TouchCover::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
	if (! isVisible())
	{
		return false;
	}
	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}
	return isSwallowTouch(touch->getLocation());
}

void TouchCover::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_nPriority, true);
}

void TouchCover::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

bool TouchCover::isTouchInInnerRect( CCPoint touchpos )
{
	touchpos = this->getParent()->convertToNodeSpace(touchpos);
	return m_innnerRect.containsPoint(touchpos);
}

bool TouchCover::isTouchInOutlineRect( CCPoint touchpos )
{
	touchpos = this->getParent()->convertToNodeSpace(touchpos);
	return m_outlineRect.containsPoint(touchpos);
}

bool TouchCover::isSwallowTouch( CCPoint touchpos )
{
	return !isTouchInInnerRect(touchpos)&&isTouchInOutlineRect(touchpos);
}

void TouchCover::setoutlineRect( const CCRect& outlineRect )
{
	m_outlineRect=outlineRect;
}

void TouchCover::setTouchPriority( int priority )
{
	m_nPriority = priority;
}

