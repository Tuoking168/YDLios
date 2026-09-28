#include "FullScreenPanel.h"
#include "userdata/LayoutData.h"

FullScreenPanel::FullScreenPanel()
{

}

FullScreenPanel::~FullScreenPanel()
{

}

bool FullScreenPanel::init()//社交界面ui
{
	if (!CCLayer::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));
	setTouchEnabled(true);

	initUI();

	return true;
}

void FullScreenPanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool FullScreenPanel::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
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

void FullScreenPanel::close()
{
	removeFromParentAndCleanup(true);
}

void FullScreenPanel::initUI()
{
	// bkg
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::COMMON, "bkg");
	addChild(bkg);

	// title
	CCScale9Sprite *titleBoard = LayoutData::getScale9Sprite(CPModuleName::COMMON, "titleBoard");
	addChild(titleBoard);

	CCSprite *titleBoardDecorationL = LayoutData::getSprite(CPModuleName::COMMON, "titleBoardDecorationL");
	addChild(titleBoardDecorationL);

	CCSprite *titleBoardDecorationR = LayoutData::getSprite(CPModuleName::COMMON, "titleBoardDecorationR");
	addChild(titleBoardDecorationR);

	CCSprite *titleDecorationL = LayoutData::getSprite(CPModuleName::COMMON, "titleDecorationL");
	addChild(titleDecorationL);

	CCSprite *titleDecorationR = LayoutData::getSprite(CPModuleName::COMMON, "titleDecorationR");
	addChild(titleDecorationR);

	// close button
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "close");
	closeBtn->setTarget(this, menu_selector(FullScreenPanel::onClose));
	menu->addChild(closeBtn);
}

void FullScreenPanel::onClose( CCObject *target )
{
	close();
}
