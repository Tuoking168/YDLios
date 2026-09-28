#include "RadioGroup.h"
#include "CCDirector.h"
#include "CCApplication.h"
#include "support/CCPointExtension.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCStdC.h"

#include <vector>
#include <stdarg.h>

using namespace std;

RadioGroup::RadioGroup()
: m_bIsInitial(false)
{

}

RadioGroup::~RadioGroup()
{

}

RadioGroup* RadioGroup::create()
{
	return RadioGroup::create(NULL,NULL);
}

RadioGroup* RadioGroup::create( CCMenuItem* item, ... )
{
	va_list args;
	va_start(args,item);

	RadioGroup *pRet = RadioGroup::createWithItems(item, args);

	va_end(args);

	return pRet;
}

RadioGroup* RadioGroup::createWithArray( CCArray* pArrayOfItems )
{
	RadioGroup *pRet = new RadioGroup();
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

RadioGroup* RadioGroup::createWithItem( CCMenuItem* item )
{
    return RadioGroup::create(item, NULL);
}

bool RadioGroup::ccTouchBegan( CCTouch* touch, CCEvent* event )
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
	if(setSelectItem(currentItem))
	{
		return true;
	}

	return false;
}

void RadioGroup::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	CC_UNUSED_PARAM(event);
	if (!isVisible() || !isEnabled())
	{
		return;
	}

	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return;
		}
	}
	CCMenuItem *currentItem = this->itemForTouch(touch);
	setSelectItem(currentItem);
}

bool RadioGroup::setSelectItem( CCMenuItem* currentItem )
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
			if(m_bIsInitial)
			{
				m_bIsInitial = false;	
			}
			else
			{
				m_pSelectedItem->activate();
			}
		}
	}
	return true;
}

bool RadioGroup::setSelectItem( int tag )
{
	CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(getChildByTag(tag));
	if(pChild)
	{
		return setSelectItem(pChild);
	}
	return false;
}

void RadioGroup::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	//just do nothing
}

void RadioGroup::ccTouchCancelled( CCTouch *touch, CCEvent* event )
{
	//just do nothing
}

void RadioGroup::setInitItemRandom()
{
	CCMenuItem * item = NULL;
	item = dynamic_cast<CCMenuItem*>(getChildren()->randomObject());
	setSelectItem(item);
}

void RadioGroup::setInitItem( int tag )
{
	m_bIsInitial = true;
	setSelectItem(tag);
}

RadioGroup* RadioGroup::createWithItems( CCMenuItem *item, va_list args )
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

	return RadioGroup::createWithArray(pArray);
}
