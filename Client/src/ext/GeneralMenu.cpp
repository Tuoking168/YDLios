#include "GeneralMenu.h"


GeneralMenu::GeneralMenu()
{

}

GeneralMenu::~GeneralMenu()
{

}

bool GeneralMenu::init()
{
	if(!CCMenu::init())
	{
		return false;
	}
	return true;
}

void GeneralMenu::addChild( CCNode * child, int zOrder, int tag )
{
//	CCAssert( dynamic_cast<CCMenuItem*>(child) != NULL, "Menu only supports MenuItem objects as children");
	CCLayer::addChild(child, zOrder, tag);
}

void GeneralMenu::addChild( CCNode * child )
{
	CCLayer::addChild(child);
}

void GeneralMenu::addChild( CCNode * child, int zOrder )
{
    CCLayer::addChild(child, zOrder);
}

CCMenuItem* GeneralMenu::itemForTouch( CCTouch * touch )
{
	CCPoint touchLocation = touch->getLocation();

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
			if (pChild && pChild->isVisible() && pChild->isEnabled())
			{
				CCPoint local = pChild->convertToNodeSpace(touchLocation);
				CCRect r = pChild->rect();
				r.origin = CCPointZero;

				if (r.containsPoint(local))
				{
					return pChild;
				}
			}
		}
	}

	return NULL;
}

bool GeneralMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	if (m_eState != kCCMenuStateWaiting || ! isVisible() || !isEnabled())
	{
		return false;
	}
	for (CCNode *c = m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}
	m_pSelectedItem = itemForTouch(touch);
	if (m_pSelectedItem)
	{
		m_eState = kCCMenuStateTrackingTouch;
		m_pSelectedItem->selected();
		return true;
	}
	return false;
}

void GeneralMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
	CCMenuItem *currentItem = itemForTouch(touch);
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
		}
	}
}

void GeneralMenu::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

GeneralMenu* GeneralMenu::create()
{
	GeneralMenu* pMenu = new GeneralMenu();
	if(pMenu && pMenu->init())
	{
		pMenu->autorelease();
		return pMenu;
	}
	CCLog("Failed to create GeneralMenu");
	return NULL;
}

void GeneralMenu::show()
{
	setVisible(true);
}

void GeneralMenu::removeChild( CCNode* child, bool cleanup )
{
	CCMenuItem *pMenuItem = dynamic_cast<CCMenuItem*>(child);

	if (m_pSelectedItem == pMenuItem)
	{
		m_pSelectedItem = NULL;
	}

	CCNode::removeChild(child, cleanup);
}
