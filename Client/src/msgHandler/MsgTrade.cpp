#include "MsgMaster.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "event/EventProtocol.h"
#include "EntityDefinition.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "scene/panel/FloatPanelType.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "TradeDefinition.h"
#include "userdata/luadata/LuaData.h"
#include "ItemDefinition.h"
#include "userdata/UserItemData.h"
#include "scene/panel/TradeOperation.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "event/CPEventHelper.h"
#include "network/HandleMessage.h"
#include "userdata/HeroData.h"
#include "module/UserDataModule.h"
#include "userdata/BoothData.h"

//交易前操作
void MsgMaster::HandleMessageItemTradeOperationNotifiy( IMsg *pMsg )
{
	MsgItemTradeOperationNotifiy *msg = dynamic_cast<MsgItemTradeOperationNotifiy *>(pMsg);
	if (!msg) return;

	GameData::s_user->m_pMainRole->m_iTargeteid=msg->targeteid;
	GameData::s_user->m_pMainRole->m_iTargetname=msg->targetname;
	if (msg->traderesult==TradeState::Trade_ApplyFor)//如果是申请
	{
		if (UserData::getIntData(HeroData::getPID(),CPUserData::REFUSE_TRADE))
		{
			// 终止交易
			MsgItemTradeRefuse* msg=new MsgItemTradeRefuse;
			HandleMessage::sendMessage(msg);
			return;
		}

		//弹出是否交易窗口
		std::vector<std::string> strlist;
		std::string othername=msg->targetname;
		strlist.push_back(othername);

		TradeOperation* p=TradeOperation::create();
		p->setStrList(strlist);
		p->setAnchorPoint(CCPointZero);
		p->setTag(1000);
		p->setPosition(ccp(-55,-120));
		GameData::s_user->m_pMainRole->getBodySprite()->addChild(p);
	}
	else if (msg->traderesult==TradeState::Trade_Agree)//对方接受
	{
		//打开交易界面
		Game::getGameUI()->showTradePanel();
	}
	else if (msg->traderesult==TradeState::Trade_NotAllow)
	{
		CPEventHelper::uiNotify("","",Error::TradeNotAllow);
	}
	else //拒绝
	{
		int type=FloatPanelType::TradeTips_Refuse;
		switch (msg->traderesult)
		{
		case TradeState::Trade_Buzy:
			type=FloatPanelType::TradeTips_Buzy;
			break;
		case TradeState::Trade_NoReflect:
			type=FloatPanelType::TradeTips_NotReflect;
			break;
		case TradeState::Trade_Refuse:
			type=FloatPanelType::TradeTips_Refuse;
			break;
		case TradeState::Trade_NotAllow:
			type=FloatPanelType::TradeTips_NotAllow;
			break;
		default:
			break;
		} 
		if (msg->traderesult==TradeState::Trade_SelfNoReflect)
		{
			if (GameData::s_user->m_pMainRole->getBodySprite()->getChildByTag(1000))
			{
				GameData::s_user->m_pMainRole->getBodySprite()->removeChildByTag(1000);
			}
			return;
		}
		//弹出拒绝窗口
		std::vector<std::string> strlist;
		std::string othername=msg->targetname;
		strlist.push_back(othername);
		Game::getGameUI()->showFloatPanel(type,strlist);

	}
}


//交易中通知物品变动
void MsgMaster::HandleMessageItemTradeOtherChangeItem( IMsg *pMsg )
{
	MsgItemTradeOtherChangeItem *msg = dynamic_cast<MsgItemTradeOtherChangeItem *>(pMsg);
	if (!msg) return;

	if (msg->position<ItemPos::Trade_Bag_Start || msg->position>ItemPos::Trade_Bag_End)
	{
		std::vector< UserItem* >::iterator it;
		for (it=GameData::s_user->m_pMainRole->m_pTradeItemList.begin();it!=GameData::s_user->m_pMainRole->m_pTradeItemList.end();it++)
		{
			UserItem* item=(UserItem*)*it;
			if (item->iid==msg->iid)
			{
				GameData::s_user->m_pMainRole->m_pTradeItemList.erase(it);
				delete item;
				break;
			}
		}		
	}
	else
	{
		UserItem* item=CommonFunction::createNewItem(msg->sid);
		item->iid=msg->iid;
		item->count=msg->cnt;
		item->position=msg->position;
		GameData::s_user->m_pMainRole->m_pTradeItemList.push_back(item);
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TRADEITEM_UPDATA);
}

//交易中物品变动回复
void MsgMaster::HandleMessageItemTradeChangeResponse( IMsg *pMsg )
{
	MsgItemTradeChangeResponse *msg = dynamic_cast<MsgItemTradeChangeResponse *>(pMsg);
	if (!msg) return;

	if (msg->errorcode==Error::Success)
	{
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TRADEITEM_UPDATA);
	}
	else
	{
		//摆放失败
		CPEventHelper::msgResponse("HandleMessageItemTradeChangeResponse","",msg->errorcode);
	}

}


//交易中锁定
void MsgMaster::HandleMessageItemTradeLockInfo( IMsg *pMsg )
{
	MsgItemTradeLockInfo *msg = dynamic_cast<MsgItemTradeLockInfo *>(pMsg);
	if (!msg) return;

	if (msg->targeteid==GameData::s_user->m_pMainRole->mID)
	{
		if (msg->lock==0)
		{
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TRADE_SELFUNLOCK);
			if (BoothData::getTradeLockState())
			{
				CPEventHelper::uiNotify("","",Error::TradeSelfUnLock);
				BoothData::setTradeLockState(false);
			}
		}
		else if (msg->lock==1)
		{
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TRADE_SELFLOCK);
			if (!BoothData::getTradeLockState())
			{
				CPEventHelper::uiNotify("","",Error::TradeSelfLock);
				BoothData::setTradeLockState(true);
			}
		}
	}
	else if (msg->targeteid==GameData::s_user->m_pMainRole->m_iTargeteid)
	{
		if (msg->lock==0)
		{
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TRADE_OTHERUNLOCK);
			if (BoothData::getTradeOtherLockState())
			{
				CPEventHelper::uiNotify("","",Error::TradeOtherUnLock);
				BoothData::setTradeOtherLockState(false);
			}
		}
		else if (msg->lock==1)
		{
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TRADE_OTHERLOCK);
			if (!BoothData::getTradeOtherLockState())
			{
				CPEventHelper::uiNotify("","",Error::TradeOtherLock);
				BoothData::setTradeOtherLockState(true);
			}
		}
	}
}


//交易结果
void MsgMaster::HandleMessageItemTradeOverInfo( IMsg *pMsg )
{
	MsgItemTradeOverInfo *msg = dynamic_cast<MsgItemTradeOverInfo *>(pMsg);
	if (!msg) return;

	if(msg->errorcode==Error::TradeFailed)
	{
		Game::getGameUI()->hidePanel(TAG_TRADE_PANEL);
		Game::getGameUI()->showFloatPanel(FloatPanelType::TradeTips_Failed);

	}
	else if (msg->errorcode==Error::TradeSuccess)
	{
		Game::getGameUI()->hidePanel(TAG_TRADE_PANEL);
		Game::getGameUI()->showFloatPanel(FloatPanelType::TradeTips_Success);
	}
	GameData::s_user->m_pMainRole->m_pTradeItemList.clear();
	GameData::s_user->m_pMainRole->m_iTargetMoney1=0;
	GameData::s_user->m_pMainRole->m_iTargetMoney2=0;
	BoothData::setTradeLockState(false);
	BoothData::setTradeOtherLockState(false);
}

//交易中金币变动
void MsgMaster::HandleMessageItemTradeChangeMoney( IMsg *pMsg )
{
	MsgItemTradeChangeMoney *msg = dynamic_cast<MsgItemTradeChangeMoney *>(pMsg);
	if (!msg) return;

	if (msg->moneytype==Entity::attr_money)
	{
		GameData::s_user->m_pMainRole->m_iTargetMoney1=msg->cnt;
	}
	if (msg->moneytype==Entity::attr_gold)
	{
		GameData::s_user->m_pMainRole->m_iTargetMoney2=msg->cnt;
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TRADEITEM_UPDATA);
}