#include "TradeOperation.h"
#include "ext/GeneralMenu.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/FloatPanelType.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventHelper.h"
#include "MsgTrade.h"
#include "EntityDefinition.h"
#include "network/HandleMessage.h"

bool TradeOperation::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCMenuItemImage* pItem=SystemData::getMenuItemImageByPlist("Trade_Flag");
	pItem->setTarget(this,menu_selector(TradeOperation::callback));
	pItem->setAnchorPoint(CCPointZero);
	pItem->setPosition(CCPointZero);
	pMenu->addChild(pItem);

	return true;
}

void TradeOperation::callback( CCObject* pSender )
{
	Game::getGameUI()->showFloatPanel(FloatPanelType::TradeTips_Apply,m_vStr);
	this->removeFromParent();
}

void TradeOperation::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if(source == "TradeTipsApply")
		{
			MsgItemTradeOperationReply* msg=new MsgItemTradeOperationReply;
			msg->traderesult = TradeState::Trade_Agree;
			msg->targeteid = GameData::s_user -> m_pMainRole->m_iTargeteid;
			HandleMessage::sendMessage(msg);
		}
		else if(source == "TradeTipsOver")
		{
			// жуж╧╫╩рв
				MsgItemTradeRefuse* msg=new MsgItemTradeRefuse;
				HandleMessage::sendMessage(msg);		
		}
	}
}

void TradeOperation::handleEvent( int channel )
{
	
}

void TradeOperation::setStrList( std::vector<std::string> strlist )
{
	m_vStr=strlist;
}