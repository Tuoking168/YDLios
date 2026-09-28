#include "TeamOperationPanel.h"
#include "TeamDefinition.h"
#include "scene/ConfirmPrompt.h"

#include "event/EventProtocol.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/teamdata/TeamData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/teamdata/TeamMsgSender.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/FloatPanelType.h"


bool TeamOperationPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_pMenu = CCMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);
	return true;
}

void TeamOperationPanel::callback( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		std::string name=TeamData::mTeamOperation.name;
		std::vector<std::string> strvec;
		strvec.push_back(name);
		switch (tag)
		{
		case TAG_TEAM_MESSGE:
			pNode->setVisible(false);
			if(TeamData::mTeamOperation.type == TeamDefinition::tm_invite)
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::Team_invite,strvec);
			}
			else if(TeamData::mTeamOperation.type == TeamDefinition::tm_join_to)
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::Team_hasteam,strvec);
			}
			else if(TeamData::mTeamOperation.type == TeamDefinition::tm_want_join)
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::Team_application,strvec);
			}
			break;
		default:
			CCLog("ERROR, undefined tag %d.",tag);
			break;
		}
	}
}

void TeamOperationPanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_TEAM_OPERATION)
	{
		if(TeamData::mTeamOperation.type == TeamDefinition::tm_join_to)
		{
			std::string name=TeamData::mTeamOperation.name;
			std::vector<std::string> strvec;
			strvec.push_back(name);
			Game::getGameUI()->showFloatPanel(FloatPanelType::Team_hasteam,strvec);
		}
		else
		{
			// add the team operation flag button
			CCMenuItemImage* pFlag = SystemData::getMenuItemImageByPlist("group.teamflag");
			pFlag->setTarget(this,menu_selector(TeamOperationPanel::callback));
			pFlag->setAnchorPoint(ccp(0.5, 0));
			m_pMenu->addChild(pFlag, 0, TAG_TEAM_MESSGE);

			CCSize size = CCSizeZero;
			CCPoint offset = CCPointZero;
			GameData::getMyRole()->getClothSizeByHeight(size, offset);
			pFlag->setPositionY(pFlag->getPositionY() + size.height);
		}
	}
	else if (channel == EventProtocol::EVENT_TEAM_DECISION_AGREE)
	{
		//send the agree decision message to server
		TeamMsgSender::MakeDecision(TeamData::mTeamOperation.opid,TeamDefinition::tmr_accept);
	}
	else if (channel == EventProtocol::EVENT_TEAM_DECISION_REFUSE)
	{
		//send the refuse decision server
		TeamMsgSender::MakeDecision(TeamData::mTeamOperation.opid,TeamDefinition::tmr_refuse);
	}
	else
	{

	}
}
