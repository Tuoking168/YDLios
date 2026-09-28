#include "RadioGroupEx.h"
#include "CCDirector.h"
#include "CCApplication.h"
#include "support/CCPointExtension.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCStdC.h"

#include <vector>
#include <stdarg.h>

using namespace std;

const static int MOVE_RANGE = 10;

RadioGroupEx::RadioGroupEx()
{

}

RadioGroupEx::~RadioGroupEx()
{

}

RadioGroupEx* RadioGroupEx::create()
{
	return RadioGroupEx::create(NULL,NULL);
}

RadioGroupEx* RadioGroupEx::create( CCMenuItem* item, ... )
{
	va_list args;
	va_start(args,item);
	RadioGroupEx *pRet = new RadioGroupEx();
	if (pRet && pRet->createWithItems(item, args))
	{
		pRet->autorelease();
		va_end(args);
		return pRet;
	}
	va_end(args);
	CC_SAFE_DELETE(pRet);
	return NULL;	
}

RadioGroupEx* RadioGroupEx::createWithArray( CCArray* pArrayOfItems )
{
	RadioGroupEx *pRet = new RadioGroupEx();
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

RadioGroupEx* RadioGroupEx::createWithItem( CCMenuItem* item )
{
    return RadioGroupEx::create(item, NULL);
}

bool RadioGroupEx::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
	CC_UNUSED_PARAM(event);
	if (!isVisible() || !isEnabled())
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
	CCMenuItem *currentItem = this->itemForTouch(touch);
	setSelectItem(currentItem);

	return false;
}

void RadioGroupEx::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	//just do nothing
}

bool RadioGroupEx::setSelectItem( CCMenuItem* currentItem )
{
	if(currentItem == NULL)
	{
		return false;
	}
	if (currentItem != m_pSelectedItem) 
	{
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
		}
		m_pSelectedItem = currentItem;
		if (m_pSelectedItem)
		{
			m_pSelectedItem->selected();
			m_pSelectedItem->activate();
		}
	}
	return true;
}

bool RadioGroupEx::setSelectItem( int tag )
{
	CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(getChildByTag(tag));
	if(pChild)
	{
		return setSelectItem(pChild);
	}
	return false;
}

void RadioGroupEx::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	//just do nothing
}

void RadioGroupEx::ccTouchCancelled( CCTouch *touch, CCEvent* event )
{
	//just do nothing
}

void RadioGroupEx::setInitItemRandom()
{
	CCMenuItem * item = NULL;
	item = dynamic_cast<CCMenuItem*>(getChildren()->randomObject());
	setSelectItem(item);
}

void RadioGroupEx::clearSelect()
{
	if (m_pSelectedItem)
	{
		m_pSelectedItem->unselected();
		m_pSelectedItem = NULL;
	}
}