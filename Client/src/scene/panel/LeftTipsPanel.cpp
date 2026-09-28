#include "LeftTipsPanel.h"
#include "EntityDefinition.h"
#include "MainUIModule.h"
#include "TaskPanel.h"
#include "ActivityStatePanel.h"
#include "EvtDataDefinition.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "scene/panel/team/TeamPanel.h"

#include "controls/CPItemComponents.h"
#include "controls/CPNodeHelper.h"
#include "controls/CPDelayRefresh.h"

#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/HeroData.h"

#include "utils/StringUtils.h"

#define SUB_PANEL_TAG 2

namespace LeftMenu
{
	enum
	{
		begin = 0,

		renwu = 0,
		zudui,
		activity,

		end,
	};
}

////////////LeftTipsPanel//////////////////////////////////////////////
LeftTipsPanel::LeftTipsPanel()
	:mContainer(NULL)
	,mSwitchMenu(NULL)
	,mShowButton(NULL)
	,mDelayRefresh(NULL)
	,mCurrentIndex(LeftMenu::renwu)
	,mIsShow(true)
{
	CPEvtDispatcher.addEventListener(CPEventName::UI_OPEN, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

LeftTipsPanel::~LeftTipsPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::UI_OPEN, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool LeftTipsPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initUI();

	return true;
}

void LeftTipsPanel::onEnter()
{
	CCLayer::onEnter();
}

void LeftTipsPanel::initUI()
{
	const CCPoint &showPt = LayoutData::getPoint(CPModuleName::MAIN_UI, "leftMenuShow");
	const CCSize &winSize = CCDirector::sharedDirector()->getWinSize();
	mContainer = CCNode::create();
	mContainer->setContentSize(winSize);
	mContainer->setAnchorPoint(ccp(showPt.x/winSize.width, showPt.y/winSize.height));
	mContainer->setPosition(showPt);
	addChild(mContainer);

	// switch menu
	const CCSize &switchSize = LayoutData::getSize(CPModuleName::MAIN_UI, "leftMenu");
	mSwitchMenu = CPItemComponents::create(switchSize, new CPLayoutList(CCSizeZero, false));
	mSwitchMenu->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "leftMenu"));
	mContainer->addChild(mSwitchMenu);
	for (int i = LeftMenu::begin; i < LeftMenu::end; i++)
	{
		CCMenuItemSprite *item = getSwitchButton(i);
		item->setTarget(this, menu_selector(LeftTipsPanel::onSwitch));
		mSwitchMenu->addItem(item);
	}

	// show or hide menu
	CCMenu *hideMenu = CCMenu::create();
	hideMenu->setPosition(CCPointZero);
	mContainer->addChild(hideMenu);

	CCMenuItemSprite *hideBtn = getArrowButton(true);
	hideBtn->setTarget(this, menu_selector(LeftTipsPanel::onHide));
	hideBtn->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "leftMenuHide"));
	hideMenu->addChild(hideBtn);

	CCMenu *showMenu = CCMenu::create();
	showMenu->setPosition(CCPointZero);
	addChild(showMenu);

	mShowButton = getArrowButton(false);
	mShowButton->setTarget(this, menu_selector(LeftTipsPanel::onShow));
	mShowButton->setScale(0);
	mShowButton->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "leftMenuShow"));
	showMenu->addChild(mShowButton);

	// delay refresh
	mDelayRefresh = CPDelayRefresh::create(this, callfunc_selector(LeftTipsPanel::switchPanel));
	addChild(mDelayRefresh);
}

void LeftTipsPanel::switchPanel()
{
	CCNode *subPanel = mContainer->getChildByTag(SUB_PANEL_TAG);
	if (subPanel)
	{
		subPanel->removeFromParentAndCleanup(true);
		subPanel = NULL;
	}
	switch (mCurrentIndex)
	{
	case LeftMenu::renwu:
		subPanel=TaskTipsPanel::create();
		break;
	case LeftMenu::zudui:
		subPanel = TeamPanel::create();
		break;
	case LeftMenu::activity:
		subPanel = ActivityStatePanel::create();
		break;
	}

	if (subPanel)
	{
		subPanel->setTag(SUB_PANEL_TAG);
		mContainer->addChild(subPanel);
	}
}

void LeftTipsPanel::switchPanel( int index )
{
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
		mSwitchMenu->setCurrentIndex(mCurrentIndex);
		switchPanel();
	}
}

void LeftTipsPanel::autoSwitch()
{
	const int curJoinedActivity = HeroData::getProp(Entity::attr_event_in);
	if (curJoinedActivity != 0)
	{
		switchPanel(LeftMenu::activity);
	}
	else
	{
		mCurrentIndex = LeftMenu::renwu;
		mSwitchMenu->setCurrentIndex(LeftMenu::renwu);
		switchPanel();
	}
}

void LeftTipsPanel::onSwitch( CCObject *target )
{
	const int index = mSwitchMenu->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
		switchPanel();
	}
}

void LeftTipsPanel::onShow( CCObject *target )
{
	show();
}

void LeftTipsPanel::onHide( CCObject *target )
{
	hide();
}

void LeftTipsPanel::show()
{
	if (!mIsShow)
	{
		mIsShow = true;
		mShowButton->stopAllActions();
		mContainer->stopAllActions();
		
		mShowButton->runAction(CPNodeHelper::getScaleToSmall());

		CCDelayTime *dl = CCDelayTime::create(0.3f);
		CCAction *st = CPNodeHelper::getScaleToBig();
		CCAction *action = CCSequence::create(dl, st, NULL);
		mContainer->runAction(action);
	}
}

void LeftTipsPanel::hide()
{
	if (mIsShow)
	{
		mIsShow = false;
		mShowButton->stopAllActions();
		mContainer->stopAllActions();
		mContainer->runAction(CPNodeHelper::getScaleToSmall());

		CCDelayTime *dl = CCDelayTime::create(0.3f);
		CCAction *st = CPNodeHelper::getScaleToBig();
		CCAction *action = CCSequence::create(dl, st, NULL);
		mShowButton->runAction(action);
	}
}

CCMenuItemSprite * LeftTipsPanel::getSwitchButton( int index )
{
	CCScale9Sprite *normBoard = LayoutData::getScale9Sprite(CPModuleName::MAIN_UI, "leftMenuBoardNorm");
	const CCSize &size = normBoard->getContentSize();
    std::string key = "leftMenuNorm" + StringUtils::toString(index);
	CCSprite *norm = LayoutData::getSprite(CPModuleName::MAIN_UI, key);
	norm->setPosition(ccp(size.width/2, size.height/2));
	normBoard->addChild(norm);

	CCScale9Sprite *selBoard = LayoutData::getScale9Sprite(CPModuleName::MAIN_UI, "leftMenuBoardSel");
	key = "leftMenuSel" + StringUtils::toString(index);
	CCSprite *sel = LayoutData::getSprite(CPModuleName::MAIN_UI, key);
	sel->setPosition(ccp(size.width/2, size.height/2));
	selBoard->addChild(sel);

	return CCMenuItemSprite::create(normBoard, selBoard);
}

CCMenuItemSprite * LeftTipsPanel::getArrowButton( bool isClose )
{
	CCScale9Sprite *normBoard = LayoutData::getScale9Sprite(CPModuleName::MAIN_UI, "leftMenuArrowBoardNorm");

	const CCSize &size = normBoard->getContentSize();
	CCSprite *norm = LayoutData::getSprite(CPModuleName::MAIN_UI, "leftMenuArrowNorm");
	norm->setPosition(ccp(size.width/2, size.height/2));
	normBoard->addChild(norm);

	CCScale9Sprite *selBoard = LayoutData::getScale9Sprite(CPModuleName::MAIN_UI, "leftMenuArrowBoardSel");
	CCSprite *sel = LayoutData::getSprite(CPModuleName::MAIN_UI, "leftMenuArrowSel");
	sel->setPosition(ccp(size.width/2, size.height/2));
	selBoard->addChild(sel);

	if (isClose)
	{
		norm->setFlipX(true);
		sel->setFlipX(true);
	}

	return CCMenuItemSprite::create(normBoard, selBoard);
}

void LeftTipsPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::UI_OPEN)
	{
		const std::string &target = CPEventHelper::getEventTarget();
		if (target == "LeftTipsPanel")
		{
			show();
			switchPanel(CPEventHelper::getEventIntData(CPEventData::VALUE_1));
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if ((Entity::attr_script_start <= type && type <= Entity::attr_script_end) ||
				type == Entity::attr_event_in)
			{
				const int curJoinedActivity = HeroData::getProp(Entity::attr_event_in);
				if (curJoinedActivity == EvtData::evt_mnhs)
				{
					mCurrentIndex = LeftMenu::activity;
					mSwitchMenu->setCurrentIndex(mCurrentIndex);
					mDelayRefresh->refresh();
				}
			}
		}
		else if (source == "HandleMessageMapSelfEnterNotify")
		{
			autoSwitch();
		}
	}
}
