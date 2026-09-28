#include "BossLifeBar.h"
#include "MainUIModule.h"

#include "controls/CPProgressBar.h"

#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/GameData.h"
#include "userdata/netdata/GameRole.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "utils/StringUtils.h"


BossLifeBar::BossLifeBar()
	:mLifeBar(NULL)
	,mLifeLabel(NULL)
{

}

BossLifeBar::~BossLifeBar()
{

}

bool BossLifeBar::init()
{
	if (!CCNode::init())
	{
		return false;
	}
	
	initUI();
	refresh();

	return true;
}

void BossLifeBar::onEnter()
{
	CCNode::onEnter();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

void BossLifeBar::onExit()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CCNode::onExit();
}

void BossLifeBar::initUI()
{
	// board
	CCSprite *board = LayoutData::getSprite(CPModuleName::MAIN_UI, "bossLifeBarBoard");
	addChild(board);
	
	const CCSize &size = board->getContentSize();
	mLifeBar = CPProgressBar::create(LayoutData::getSprite(CPModuleName::MAIN_UI, "bossLifeBar"));
	mLifeBar->setPosition(ccp(size.width/2, size.height/2));
	addChild(mLifeBar);

	mLifeLabel = LayoutData::getLabelTTF(CPModuleName::MAIN_UI, "bossLife");
	mLifeLabel->setPosition(mLifeBar->getPosition());
	addChild(mLifeLabel);

	//
	setContentSize(size);
}

void BossLifeBar::refresh()
{
	GameRole *myRole = GameData::getMyRole();
	if (myRole)
	{
		AliveGhost *boss = myRole->getTheAim();
		if (boss)
		{
			const float percent = boss->mHp * 100.0f/(boss->mMaxHp + 0.1f);
			mLifeBar->setPercentage(percent);

			const std::string &lifeStr = StringUtils::toString(boss->mHp) + "/" + StringUtils::toString(boss->mMaxHp);
			mLifeLabel->setString(lifeStr.c_str());
		}
	}
}

void BossLifeBar::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageEntityHpChangeNotify" ||
			source == "HandleMessageEntityHpChangeDelayNotify" ||
			source == "HandleMessageEntityMaxHPChangeNotify")
		{
			const int ghostID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			GameRole *myRole = GameData::getMyRole();
			if (myRole)
			{
				AliveGhost *aim = myRole->getTheAim();
				if (aim && aim->mID == ghostID)
				{
					refresh();
				}
			}
		}
	}
}
