#include "MidScreenPanel.h"

#include "userdata/LayoutData.h"

MidScreenPanel::MidScreenPanel()
{

}

MidScreenPanel::~MidScreenPanel()
{

}

bool MidScreenPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);

	initUI();

	return true;
}

void MidScreenPanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool MidScreenPanel::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);

	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}
	return true;
}

void MidScreenPanel::close()
{
	removeFromParentAndCleanup(true);
}

void MidScreenPanel::initUI()
{
	// bkg
	CCScale9Sprite *bkg1 = LayoutData::getScale9Sprite(CPModuleName::COMMON, "midBkg");
	addChild(bkg1);

	CCScale9Sprite *bkg2 = LayoutData::getScale9Sprite(CPModuleName::COMMON, "midBkg");
	addChild(bkg2);

	// title
	CCSprite *titleBoard = LayoutData::getSprite(CPModuleName::COMMON, "midTitleBoard");
	addChild(titleBoard);

	CCSprite *titleBoardDecorationL = LayoutData::getSprite(CPModuleName::COMMON, "midTitleBoardDecorationL");
	addChild(titleBoardDecorationL);

	CCSprite *titleBoardDecorationR = LayoutData::getSprite(CPModuleName::COMMON, "midTitleBoardDecorationR");
	addChild(titleBoardDecorationR);

	// close button
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "midClose");
	closeBtn->setTarget(this, menu_selector(MidScreenPanel::onClose));
	menu->addChild(closeBtn);
}

void MidScreenPanel::onClose( CCObject *target )
{
	close();
}
