#include "OperateMenu.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "MsgTrade.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ChatPanel.h"
#include "network/HandleMessage.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/teamdata/TeamData.h"
#include "MsgTeam.h"
#include "userdata/PlayerInfoData.h"
#include "userdata/teamdata/TeamMsgSender.h"
#include "social/SocialHelper.h"
#include "event/CPEventHelper.h"
#include "MsgPlayer.h"
#include "SceneDefinition.h"
#include "TradeDefinition.h"
#include "userdata/StaticData.h"
#include "MsgGuild.h"


#define TEAM_OP_COUNT 10
#define PLAYER_OP_COUNT 10
#define GUILD_OP_COUNT 8

enum OperateTag
{
	Operate_tag_addfriend,			//加好友
	Operate_tag_trade,				//交易
	Operate_tag_privatechat,		//悄悄话
	Operate_tag_check,				//观察
	Operate_tag_inviteguild,        //邀请入会
	Operate_tag_addenemy,			//添加仇人
	Operate_tag_shoutu,				//收徒
	Operate_tag_apprentice,         //拜师
	Operate_tag_proposal,		//求婚
	Operate_tag_inviteteam,         //邀请组队
	Operate_tag_kickout,			//踢出队伍
	Operate_tag_appointleader,		//委任队长
	Operate_tag_max
};

static std::string TeamOperateKey[TEAM_OP_COUNT] = {"kickout","appointleader","addfriend","trade","privatechat","check","inviteguild","addenemy","shoutu","apprentice"};
static int TeamOperateTag[TEAM_OP_COUNT] = {Operate_tag_kickout
	,Operate_tag_appointleader
	,Operate_tag_addfriend
	,Operate_tag_trade
	,Operate_tag_privatechat
	,Operate_tag_check
	,Operate_tag_inviteguild
	,Operate_tag_addenemy
	,Operate_tag_shoutu
	,Operate_tag_apprentice};
static std::string PlayerOperateKey[PLAYER_OP_COUNT] = {"addfriend","trade","privatechat","check","inviteguild","addenemy","shoutu","apprentice","proposal","inviteteam"};
static std::string GuildOperateKey[GUILD_OP_COUNT] = {"addfriend","trade","privatechat","check","inviteguild","addenemy","shoutu","apprentice"};

/////////OperateMenu////////////////////////////////////////////////
OperateMenu::OperateMenu()
	: m_nType(0)
	,mPlayerID(0)
{

}

OperateMenu::~OperateMenu()
{

}

bool OperateMenu::init( int type )
{
	if (!CCLayer::init())
	{
		return false;
	}

	m_nType = type;
	if (m_nType == Operate_Type_Team)
	{
		initMenu(TeamOperateKey, TeamOperateTag, TEAM_OP_COUNT);
	}
	else if(m_nType == Operate_Type_Player)
	{
		initMenu(PlayerOperateKey, NULL, PLAYER_OP_COUNT);
		this->setPosition(ccp(455, 470));
	}
	else if(m_nType == Operate_Type_Guild)
	{
		initMenu(GuildOperateKey, NULL, GUILD_OP_COUNT);
	}
	
	return true;
}

void OperateMenu::initMenu( std::string *keyList, int *tagList, int count )
{
	if(keyList)
	{
		const CCSize &boardSize = SystemData::getLayoutSize("operate.btn");
		CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("operate.border");
		pBorder->setContentSize(CCSizeMake(boardSize.width + 18, count * boardSize.height + 21));	
		pBorder->setPosition(ccp(-9, 8));
		pBorder->setAnchorPoint(ccp(0, 1));
		addChild(pBorder);

		//the operating menu
		CCMenu* pOpMenu = CCMenu::create();
		pOpMenu->setPosition(CCPointZero);
		pOpMenu->setAnchorPoint(CCPointZero);
		addChild(pOpMenu);

		//show the operating menus
		for(int i = 0; i < count; i++)
		{
			CCMenuItemImage* pItem = SystemData::getScale9MenuItemImageByPlist("operate.btn");
			pItem->setAnchorPoint(ccp(0, 1));	
			pItem->setPosition(ccp(0, -i * pItem->getContentSize().height));
			pItem->setTarget(this, menu_selector(OperateMenu::callback));
			pOpMenu->addChild(pItem, 0, i);
			if (tagList)
			{
				pItem->setTag(tagList[i]);
			}

			const std::string &labelkey = "operate." + keyList[i];
			CCLabelTTF* plabel = SystemData::getLabelTTF(labelkey);
			plabel->setColor(ccWHITE);
			plabel->setFontSize(20);
			plabel->setPosition(LayoutData::getCenter(pItem->getContentSize()));
			pItem->addChild(plabel);

			if (i==Operate_tag_trade)
			{
				if (!checkCanTrade())
				{
					pItem->setColor(ccGRAY);
				}
			}	
			if (i == 0)
			{
				m_rect = CCRectMake(0, -pItem->getContentSize().height * count, pItem->getContentSize().width, pItem->getContentSize().height * count);		
			}
		}
	}
}

OperateMenu* OperateMenu::create( int type )
{
	OperateMenu* pMenu = new OperateMenu;
	if(pMenu && pMenu->init(type))
	{
		pMenu->autorelease();
		return pMenu;
	}

	if(pMenu)
	{
		delete pMenu;
	}
	return NULL;
}

void OperateMenu::setPlayerID( int pid )
{
	mPlayerID = pid;
}

void OperateMenu::setPlayerName( const std::string &name )
{
	mPlayerName = name;
}

void OperateMenu::callback( CCObject* pSender )
{
	///TODO: send the quiting team message
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tgtid = 0;
		std::string playerName;
		if(m_nType == Operate_Type_Player)
		{
			tgtid = PlayerInfoData::_target_player_info.pid;
			playerName = PlayerInfoData::_target_player_info.name;
		}
		else if(m_nType == Operate_Type_Team)
		{
			tgtid = TeamData::mTeamMembers[this->getTag()].pid;
		}

		if (mPlayerID > 0)
		{
			tgtid = mPlayerID;
		}

		if (!mPlayerName.empty())
		{
			playerName = mPlayerName;
		}

		//
		const int tag = pNode->getTag();
		switch (tag)
		{
		case Operate_tag_addfriend:
			SocialHelper::requestAddFriend(tgtid, "");
			break;
		case Operate_tag_addenemy:
			SocialHelper::addEnemy(tgtid);
			break;
		case Operate_tag_check:
			sendpostCheck(tgtid);
			break;
		case Operate_tag_trade:
			sendpostTrade(GameData::s_user->m_pMainRole->m_iTargeteid);
			break;
		case Operate_tag_privatechat:
			ChatPanelHelper::openChatWithPartner(tgtid, playerName);
			break;
		case Operate_tag_inviteguild:
			{
				MsgGuildInviteRequestEx* req = new MsgGuildInviteRequestEx;
				req->pid = tgtid;
				HandleMessage::sendMessage(req);
				break;
			}
		case Operate_tag_shoutu:
			SocialHelper::requestAddApprentice(tgtid);
			break;
		case Operate_tag_apprentice:
			SocialHelper::requestAddMaster(tgtid);
			break;
		case Operate_tag_proposal:
			SocialHelper::requestAddCouple(tgtid);
			break;
		case Operate_tag_inviteteam:
			{
				//send message to invite the player
				TeamMsgSender::Invite(tgtid);
				break;
			}
		case Operate_tag_kickout:
			{
				TeamMsgSender::kickPlayer(tgtid);
				break;
			}
		case Operate_tag_appointleader:
			{
				TeamMsgSender::setLeader(tgtid);
				break;
			}
		default:
			break;
		}
		setVisible(false); 
	}
}

void OperateMenu::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void OperateMenu::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority-1,false);
}

bool OperateMenu::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos = convertToNodeSpace(pTouch->getLocation());
	if(!m_rect.containsPoint(pos))
	{
		setVisible(false);
	}
	return false;
}

void OperateMenu::sendpostTrade( int eid )
{
	if (!checkCanTrade())
	{
		CPEventHelper::uiNotify("OperateMenu","",Error::TradeNotAllow);
		return;
	}
	MsgItemTradeOperationRequest* msg=new MsgItemTradeOperationRequest;
	msg->targeteid = eid;
	HandleMessage::sendMessage(msg);
}

void OperateMenu::sendpostCheck( int pid )
{
	MsgGetOtherPlayerDataRequest* msg=new MsgGetOtherPlayerDataRequest;
	msg->pid = pid;
	HandleMessage::sendMessage(msg);
}

bool OperateMenu::checkCanTrade()
{
	int mapType=0;
	if (StaticData::getMapType(GameData::s_user->mMap.mID,mapType)) 
	{
		if (mapType==Scene::stSceneEvent)
		{
			return false;
		}
	}
	return true;
}
