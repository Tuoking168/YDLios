#include "TargetPanel.h"
#include "MainUIModule.h"
#include "OperateMenu.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/LayoutData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/OtherRole.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/HeadPanel.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"


TargetPanel::TargetPanel()
	:mHeadPanel(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

TargetPanel::~TargetPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool TargetPanel::init()
{	
	if (!CCLayer::init())
	{
		return false;
	}
	
	initUI();
	refresh();

	return true;
}

void TargetPanel::onEnter()
{
	CCLayer::onEnter();
	CPEventHelper::setEventStringData(CPEventName::UI_CHANGE, CPEventData::VALUE_1, "up");
	CPEventHelper::dispatcher(CPEventName::UI_CHANGE, "TargetPanel", "");
}

void TargetPanel::onExit()
{
	CPEventHelper::setEventStringData(CPEventName::UI_CHANGE, CPEventData::VALUE_1, "down");
	CPEventHelper::dispatcher(CPEventName::UI_CHANGE, "TargetPanel", "");
	CCLayer::onExit();
}

void TargetPanel::initUI()
{
	mHeadPanel = HeadPanel::create(true);
	mHeadPanel->setClickHandler(this, callfunc_selector(TargetPanel::menucallback));
	mHeadPanel->setAnchorPoint(CCPointZero);
	addChild(mHeadPanel);

	//
	CCMenu* menu=CCMenu::create();
	menu->setPosition(CCPointZero);
	mHeadPanel->addChild(menu);

	CCMenuItemImage* pclose = LayoutData::getMenuItemImg(CPModuleName::MAIN_UI, "headPanelClose");
	pclose->setTarget(this,menu_selector(TargetPanel::closeCallBack));
	pclose->setScale(1.0f);
	menu->addChild(pclose);
}

void TargetPanel::refresh()
{
	GameRole* myRole = GameData::getMyRole();
	if (!myRole) return;
	const AliveGhost *otherRole = myRole->getTheAim();
	if (otherRole && otherRole->mType == GHOST_TYPE_PLAYER)
	{
		mHeadPanel->setName(otherRole->mName);
		mHeadPanel->setLevel(otherRole->mLevel);
		mHeadPanel->setJob(otherRole->mGhostJob);
		mHeadPanel->setGender(otherRole->mGhostGender);
		mHeadPanel->setHP(otherRole->mHp, otherRole->mMaxHp);
		mHeadPanel->setMP(otherRole->mMp, otherRole->mMaxMp);
	}
}

void TargetPanel::menucallback()
{
	Game::getGameUI()->showOperationMenu(OperateMenu::Operate_Type_Player);
}

void TargetPanel::closeCallBack( CCObject* pSender )
{
	GameData::s_user->m_pMainRole->changeTheAim(NULL);
	GameUI* ui = Game::getGameUI();
	if (ui)
	{
		ui->hideTargetPanel();
	}
}

void TargetPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageSyncEntityLevelupNotify"
			|| source == "HandleMessageEntityHpChangeNotify"
			|| source == "HandleMessageEntityMaxHPChangeNotify"
			|| source == "HandleMessageEntityHpChangeDelayNotify"
			|| source == "HandleMessageEntityMpChangeNotify")
		{
			const AliveGhost *otherRole = GameData::getMyRole()->getTheAim();
			const int entityID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (otherRole && entityID == otherRole->mID)
			{
				refresh();
			}
		}
	}
}
