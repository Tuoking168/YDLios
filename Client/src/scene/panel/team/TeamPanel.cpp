#include "TeamPanel.h"
#include "TeamModule.h"
#include "EntityDefinition.h"
#include <algorithm>

#include "scene/panel/OperateMenu.h"

#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"
#include "controls/CPChecker.h"

#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/PlayerInfoData.h"
#include "userdata/teamdata/TeamData.h"
#include "userdata/teamdata/TeamMsgSender.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"


static bool compare( const TeamData::TeamMember &data1, const TeamData::TeamMember &data2 )
{
	return (data1.teamleader != 0);
}

////////////TeamPanel///////////////////////////////////////////////
TeamPanel::TeamPanel()
	:mTeamList(NULL)
	,mExitBtn(NULL)
	,mChecker(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

TeamPanel::~TeamPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool TeamPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initUI();

	return true;
}

void TeamPanel::onEnter()
{
	CCLayer::onEnter();
	refresh();
}

void TeamPanel::initUI()
{
	// board
	CCScale9Sprite *stateBoard = LayoutData::getScale9Sprite(CPModuleName::TEAM, "teamListBoard");
	addChild(stateBoard);

	// title
	CCScale9Sprite *titleBoard = LayoutData::getScale9Sprite(CPModuleName::TEAM, "teamListTitleBoard");
	addChild(titleBoard);

	// exit menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);
	mExitBtn = LayoutData::getMenuItemImg(CPModuleName::TEAM, "exitTeam");
	mExitBtn->setTarget(this, menu_selector(TeamPanel::onExitTeam));
	menu->addChild(mExitBtn);

	// state list
	const CCSize &stateSize = LayoutData::getSize(CPModuleName::TEAM, "teamList");
	const CCPoint &statePoint = LayoutData::getPoint(CPModuleName::TEAM, "teamList");
	mTeamList = CPItemComponents::create(stateSize, new CPLayoutList);
	mTeamList->setClickSensitive(true);
	mTeamList->setPosition(statePoint);
	addChild(mTeamList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::TEAM, "listScrollBar");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mTeamList->setScrollbar(scrollBar);
	
	//
	m_pOpMenu = OperateMenu::create(OperateMenu::Operate_Type_Team);
	m_pOpMenu->setAnchorPoint(CCPointZero);
	m_pOpMenu->setPosition(LayoutData::getPoint(CPModuleName::TEAM, "teamOperateMenu"));
	m_pOpMenu->setVisible(false);
	addChild(m_pOpMenu);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void TeamPanel::refresh()
{
	mTeamList->removeAllItems();

	std::sort(TeamData::mTeamMembers.begin(), TeamData::mTeamMembers.end(), compare);

	std::string name;
	for (int i = 0; i < (int)TeamData::mTeamMembers.size(); i++)
	{
		CCScale9Sprite *selNode = LayoutData::getScale9Sprite(CPModuleName::TEAM, "listSel");
		CCNode *normNode = CCNode::create();
		normNode->setContentSize(selNode->getContentSize());
		CCMenuItemSprite *btn = CCMenuItemSprite::create(normNode, selNode);
		btn->setTarget(this, menu_selector(TeamPanel::onMember));
		mTeamList->addItem(btn);

		const TeamData::TeamMember &tm = TeamData::mTeamMembers[i];
		if (tm.pid == HeroData::getPID())
		{
			btn->setEnabled(false);
		}
		name = tm.name;
		if (tm.teamleader != 0)
		{
			name += LayoutData::getString(CPModuleName::TEAM, "teamLeader");
		}
		CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::TEAM, "memberName");
		nameLabel->setString(name.c_str());
		btn->addChild(nameLabel);
	}
	mTeamList->setCurrentIndex(0);

	//
	mExitBtn->setVisible(TeamData::mTeamMembers.size() > 0);
}

void TeamPanel::onMember( CCObject *target )
{
	const int index = mTeamList->getCurrentIndex();
	if (0 <= index && index < (int)TeamData::mTeamMembers.size())
	{
		const TeamData::TeamMember &member = TeamData::mTeamMembers[index];
		PlayerInfoData::_target_player_info.eid = 0;
		PlayerInfoData::_target_player_info.pid = member.pid;
		PlayerInfoData::_target_player_info.name = member.name;
		PlayerInfoData::_target_player_info.hp = 0;
		PlayerInfoData::_target_player_info.mp = 0;
		PlayerInfoData::_target_player_info.maxhp = 0;
		PlayerInfoData::_target_player_info.maxmp = 0;
		PlayerInfoData::_target_player_info.lvl = 0;
		PlayerInfoData::_target_player_info.staticid = 0;
		PlayerInfoData::_target_player_info.gender = 0;
		m_pOpMenu->setVisible(true);
		m_pOpMenu->setTag(mTeamList->getCurrentIndex());
	}
}

void TeamPanel::onExitTeam( CCObject *target )
{
	mChecker->start();
	TeamMsgSender::Quit();
}

void TeamPanel::onCPEvent( const std::string &evtName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (evtName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageTeamQuitResponse")
		{
			mChecker->stop();
		}
	}
	else if (evtName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageTeamInfoNotify" ||
			source == "HandleMessageTeamInfoRmvNotify" ||
			source == "HandleMessageTeamInfoUpdNotify")
		{
			refresh();
		}
		else if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (type == Entity::attr_team_id)
			{
				if (HeroData::getProp(Entity::attr_team_id) <= 0)
				{
					TeamData::mTeamMembers.clear();
					refresh();
				}
			}
		}
	}
}
