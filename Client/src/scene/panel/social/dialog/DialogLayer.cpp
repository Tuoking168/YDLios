#include "DialogLayer.h"
#include "controls/CPItemComponents.h"

DialogLayer::DialogLayer():
    mMenu(NULL),
	mMenuItemArray(NULL),
	mItemComps(NULL),
    mTouchedMenu(false),
	clickType(0)
{
}

DialogLayer::~DialogLayer()
{
}

bool DialogLayer::init()
{
    bool bRet = false;
    
    do {
        onInitDialog();
        initMenu();

        bRet = true;
    } while (0);
    
    return bRet;
}


void DialogLayer::pushMenu(CCMenuItem *pMenuItem)
{
    if (!mMenuItemArray) {
        mMenuItemArray = CCArray::create();
    }

    mMenuItemArray->addObject(pMenuItem);
}

void DialogLayer::addCompMenu(CPItemComponents *pComp)
{
	mItemComps = pComp;
	addChild(mItemComps);
}

bool DialogLayer::initMenu()
{
    if (mMenuItemArray && mMenuItemArray->count() > 0) {
        if (!mMenu) {
            mMenu = CCMenu::createWithArray(mMenuItemArray);
            mMenu->setPosition(CCPointZero);
            addChild(mMenu);
        }
    }

    return true;
}

void DialogLayer::onEnter()
{
	CCLayer::onEnter();
    // 屏蔽所有priority比自己大的消息
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
}

void DialogLayer::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool DialogLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	// 因为拦截了所有消息(包括按钮) 所以需要将消息手动传给模态对话框上的按钮
	if (mMenu && !mTouchedMenu) {
		mTouchedMenu = mMenu->ccTouchBegan(pTouch, pEvent);
		if(mTouchedMenu)
		{
			clickType = 1;
		}
	}    
	if (mItemComps && !mTouchedMenu) {
		mTouchedMenu = mItemComps->ccTouchBegan(pTouch, pEvent);
		if(mTouchedMenu)
		{
			clickType = 2;
		}
	}
    
    return true;
}

void DialogLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (mTouchedMenu) {
		if (mMenu && clickType == 1) {
			mMenu->ccTouchMoved(pTouch, pEvent);
		}
		if (mItemComps && clickType == 2) {
			mItemComps->ccTouchMoved(pTouch, pEvent);
		}
    }
}

void DialogLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (mTouchedMenu) {
		if (mMenu && clickType == 1) {
			mMenu->ccTouchEnded(pTouch, pEvent);
		}
		if (mItemComps && clickType == 2) {
			mItemComps->ccTouchEnded(pTouch, pEvent);
		}
        mTouchedMenu = false;
		clickType = 0;
    }
}

void DialogLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (mTouchedMenu) {
		if (mMenu && clickType == 1) {
			mMenu->ccTouchEnded(pTouch, pEvent);
		}
		if (mItemComps && clickType == 2) {
			mItemComps->ccTouchEnded(pTouch, pEvent);
		}
		mTouchedMenu = false;
		clickType = 0;
    }
}
