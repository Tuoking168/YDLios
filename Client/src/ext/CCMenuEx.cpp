#include "CCMenuEx.h"

CCMenuEx::CCMenuEx()
: CCMenu()
{
	m_nPriority = kCCMenuHandlerPriority;
}

CCMenuEx* CCMenuEx::create()
{
	return create(NULL,NULL);
}

CCMenuEx* CCMenuEx::create( CCMenuItem* item )
{
	return create(item, NULL);
}

CCMenuEx* CCMenuEx::create( CCMenuItem* item, ... )
{
	va_list args;
	va_start(args,item);

	CCMenuEx *pRet = CCMenuEx::createWithItems(item, args);

	va_end(args);

	return pRet;
}

void CCMenuEx::setTouchPriority(int priority)
{
	m_nPriority = priority;
}

bool CCMenuEx::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
	if(!CCMenu::ccTouchBegan(touch,event))
	{
		return false;
	}
	m_nMovedCnt = 0;
	return true;
}

void CCMenuEx::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	CCMenu::ccTouchMoved(touch,event);
	m_nMovedCnt++;
}

void CCMenuEx::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	if(m_nMovedCnt>MOVE_RANGE)
	{
		//if there is enough move , treat it as move not select 
		CCMenu::ccTouchCancelled(touch,event);
	}
	else
	{
		CCMenu::ccTouchEnded(touch,event);
	}
}

void CCMenuEx::ccTouchCancelled( CCTouch *touch, CCEvent* event )
{
	CCMenu::ccTouchCancelled(touch,event);
}

void CCMenuEx::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_nPriority, false);
}

CCMenuEx* CCMenuEx::createWithItems( CCMenuItem *item, va_list args )
{
	CCArray* pArray = NULL;
	if( item )
	{
		pArray = CCArray::create(item, NULL);
		CCMenuItem *i = va_arg(args, CCMenuItem*);
		while(i)
		{
			pArray->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
	}

	return CCMenuEx::createWithArray(pArray);
}

CCMenuEx* CCMenuEx::createWithArray( CCArray* pArrayOfItems )
{
	CCMenuEx *pRet = new CCMenuEx();
	if (pRet && pRet->initWithArray(pArrayOfItems))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}
