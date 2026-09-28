#include "MsgMaster.h"
#include "ModuleData.h"
#include "ChatModule.h"
#include "OpcodeDefinition.h"
#include "PetDefinition.h"
#include "ActivityDefinition.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/UserItemData.h"

#include "scene/panel/functionPanel/CharacterPanel.h"
#include "scene/panel/functionPanel/BagPanel.h"

#include "userdata/luadata/LuaData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/OtherRole.h"

#include "event/CPEventHelper.h"
#include "event/EventProtocol.h"

#include "utils/TestUtils.h"
#include "logic/BagOperator.h"


void MsgMaster::HandleMessageItemInfoNotify( IMsg *pMsg )
{
	MsgItemInfoNotify *msg = dynamic_cast<MsgItemInfoNotify *>(pMsg);
	if (!msg)return;

	UserItems items;
	UserItemsByIid itemsByIid;
	for(unsigned int i=0; i<msg->item_list.size();i++)
	{
		UserItem* item = new UserItem;
		item->iid = msg->item_list[i].iid;
		item->sid = msg->item_list[i].sid;
		item->position = msg->item_list[i].position;
		item->count = msg->item_list[i].count;
		item->bind = msg->item_list[i].bind;
		GameData::s_user->getUserItemData()->addItem(item);
	}
	GameData::s_user->UpdStoneArray();
}

void MsgMaster::HandleMessageItemAddNotify( IMsg *pMsg )
{
	//Deprecated
}

void MsgMaster::HandleMessageItemAddNotifyEx( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgItemAddNotifyEx, pMsg);
	
	const ItemInfo &info = msg->iteminfo;
	UserItem* userItem = GameData::s_user->getUserItemData()->getItemByIid(info.iid);
	if(!userItem)
	{
		UserItem* item = new UserItem;
		item->iid = info.iid;
		item->sid = info.sid;
		item->position = info.position;
		item->count = info.count;
		item->bind = info.bind;
		GameData::s_user->getUserItemData()->addItem(item);
		for (int i = 0; i < (int)msg->data.size(); i++)
		{
			const ItemExData &dataEx = msg->data[i];
			item->data[dataEx.nIdx] = dataEx.data;
		}
		if (item->position >ItemPos::Hollow_Bag_End || item->position<ItemPos::Hollow_Bag_Start)
		{
			if (msg->opcode == Opcode::Op_pet_pick_up)
			{
				CPEventHelper::msgNotify("HandleMessageItemAddNotifyEx", "pet", Opcode::Op_Item_Create, info.sid, info.count, info.iid, msg->opcode);
			}
			else if (msg->opcode == Opcode::Op_Treasure_hunt)
			{
				CPEventHelper::msgNotify("HandleMessageItemAddNotifyEx", "hunt", Opcode::Op_Item_Create, info.sid, info.count, info.iid, msg->opcode);
			}
			else
			{
				CPEventHelper::msgNotify("HandleMessageItemAddNotifyEx", "", Opcode::Op_Item_Create, info.sid, info.count, info.iid, msg->opcode);
			}
		}
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
}

void MsgMaster::HandleMessageItemRmvNotify( IMsg *pMsg )
{
	MsgItemRmvNotify *msg = dynamic_cast<MsgItemRmvNotify *>(pMsg);
	if (!msg)return;
	/*UserItems &items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->iid==msg->iid)
		{
			items.erase(it);
			break;
		}
	}	
	UserItemsByIid &itemsid = GameData::s_user->getUserItemData()->userItemsByIid;
	for(std::map<int,UserItem*>::iterator it = itemsid.begin(); it!=itemsid.end(); it++) 
	{
		int iid = it->first;
		if (iid==msg->iid)
		{
			itemsid.erase(it);
			break;
		}
	}	*/
	UserItems &items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->iid==msg->iid)
		{
			CPEventHelper::msgNotify("HandleMessageItemRmvNotify","",Opcode::Op_Item_Delete,pItem->sid,pItem->count,msg->opcode);
			break;
		}
	}
	GameData::s_user->getUserItemData()->rmvItemByiid(msg->iid);
	GameData::s_user->UpdStoneArray();
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
}

void MsgMaster::HandleMessageItemUpdCountNotify( IMsg *pMsg )
{
	MsgItemUpdCountNotify *msg = dynamic_cast<MsgItemUpdCountNotify *>(pMsg);
	if (!msg)return;

	UserItems &items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->iid==msg->iid)
		{
			int count=msg->count-pItem->count;
			pItem->count=msg->count;
			if (pItem->sid<100)
			{
				CPEventHelper::msgNotify("HandleMessageItemUpdCountNotify","",Opcode::Op_Item,pItem->sid,count,msg->opcode);
			}
			else
			{
				if (count>0)
				{
					CPEventHelper::msgNotify("HandleMessageItemUpdCountNotify","",Opcode::Op_Item_Create,pItem->sid,count,msg->iid, msg->opcode);
				}
				else
				{
					CPEventHelper::msgNotify("HandleMessageItemUpdCountNotify","",Opcode::Op_Item_Delete,pItem->sid,-count,msg->iid, msg->opcode);
				}
			}
			break;
		}
	}	

	GameData::s_user->UpdStoneArray();
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
}

void MsgMaster::HandleMessageItemUpdPositionNotify( IMsg *pMsg )
{
	MsgItemUpdPositionNotify *msg = dynamic_cast<MsgItemUpdPositionNotify *>(pMsg);
	if (!msg)return;
	UserItem* userItem = GameData::s_user->getUserItemData()->getItemByIid(msg->iid);
	if(userItem)
	{
		bool flag=false;

		if ( userItem->position<0 || msg->position<0 )
		{
			flag=true;
		}
		int lastpos = userItem->position;
		bool hollowFlag = false;
		if (lastpos>=ItemPos::Hollow_Bag_Start && lastpos<=ItemPos::Hollow_Bag_End)
		{
			flag = false;
			hollowFlag = true;
		}
		//TestUtils::timeTestBegin();
		GameData::s_user->getUserItemData()->changeItemPosition(userItem->iid, userItem->position, msg->position);
		//TestUtils::timeTestEnd("changeItemPosition");

		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);

		if ( flag )
		{
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ATTRIBUTE_CHANGE);
		}
		if ( hollowFlag )
		{
			CPEventHelper::msgNotify("HandleMessageItemUpdPositionNotify","",Opcode::Op_Item_Create,userItem->sid,userItem->count,msg->iid, msg->opcode);
		}
		CPEventHelper::msgNotify("MsgItemUpdPositionNotify","",msg->opcode,msg->position,0,0,0);
	}
}

void MsgMaster::HandleMessageItemUpdElvlNotify( IMsg *pMsg )
{
	
}

void MsgMaster::HandleMessageItemUpdSlotNotify( IMsg *pMsg )
{
	
}

void MsgMaster::HandleMessageItemUpdDataComboNotify( IMsg *pMsg )
{
	
}

void MsgMaster::HandleMessageItemUpdSidNotify(IMsg *pMsg)
{
	MsgItemUpdSidNotify *msg = dynamic_cast<MsgItemUpdSidNotify *>(pMsg);
	if (!msg)return;
	UserItems &items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->iid==msg->iid)
		{
			pItem->sid=msg->sid; 
			LuaData::getProp(LuaData::ITEM,msg->sid,"icon",pItem->icon);
			LuaData::getProp(LuaData::ITEM,msg->sid,"name",pItem->name);
		}
	}

	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
}
void MsgMaster::HandleMessageItemUpdSkillNotify( IMsg *pMsg )
{

}

void MsgMaster::HandleMessageItemOperationNotify( IMsg *pMsg )
{
	MsgItemOperationNotify *msg = dynamic_cast<MsgItemOperationNotify *>(pMsg);
	if (!msg)return;

	if(msg->errcode == Error::Item_Same_Position)//整理背包 不需要提示这个error给用户看到
	{
		return;
	}
	CPEventHelper::msgResponse("","",msg->errcode);
	
}

void MsgMaster::HandleMessageBuyItemResponse( IMsg *pMsg )
{
	
}
void MsgMaster::HandleMessageBagisFull( IMsg *pMsg )
{
}

void MsgMaster::HandleMessageItemUpdData( IMsg *pMsg )
{
	MsgItemUpdDataNotify *msg = dynamic_cast<MsgItemUpdDataNotify *>(pMsg);
	if (!msg)return;


	bool flag=false;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->iid==msg->iid)
		{
			int cnt = msg->data - pItem->data[msg->idx];
			pItem->data[msg->idx]=msg->data;
			if (pItem->position<0)
			{
				flag=true; 
			}
			CPEventHelper::msgNotify("HandleMessageItemUpdData", "ItemEx", msg->opcode, msg->idx, cnt, msg->data, pItem->sid); 
		}
	}	
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
	if (flag)
	{
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ATTRIBUTE_CHANGE);
	}
}

void MsgMaster::HandlemessageItemUpdExDataNotify( IMsg *pMsg )
{
	MsgItemUpdExDataNotify *msg = dynamic_cast<MsgItemUpdExDataNotify *>(pMsg);
	if (!msg)return;
	bool flag=false;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->iid==msg->iid)
		{
			for (MsgItemUpdExDataNotify::ItemExDataList::iterator itex = msg->data.begin();
				itex != msg->data.end(); itex ++)
			{
				pItem->data[itex->nIdx]=itex->data;
			}
			if (pItem->position<0)
			{
				flag=true;
			}						
		}
	}	
	CPEventHelper::msgNotify("HandlemessageItemUpdExDataNotify","ItemEx",msg->opcode,0,0,0); 
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
	if (flag)
	{
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ATTRIBUTE_CHANGE);
	}
}


void MsgMaster::HandleMessageItemFailorSuccess( IMsg *pMsg )
{

	MsgItemFailorSuccessNotify *msg = dynamic_cast<MsgItemFailorSuccessNotify *>(pMsg);
	if (!msg)return;

	if (msg->data==0)//失败
	{
		if (msg->idx==Opcode::Op_Item_Enhance)
		{
			//CPEventHelper::uiNotify("","",Error::ItemFaild);
		}
		else
		{
			//CPEventHelper::uiNotify("","",Error::ItemFaild);
		}
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_FAILED);
	}
	else if (msg->data==1)//成功
	{
		if (msg->idx==Opcode::Op_Item_Enhance)
		{
			//CPEventHelper::uiNotify("","",Error::ItemSuccess);
		}
		else
		{
			//CPEventHelper::uiNotify("","",Error::ItemSuccess);
		}
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_SUCCESS);
	}

	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
}


void MsgMaster::HandleMessageMarketSetItemResponse( IMsg *pMsg )
{
	MsgMarketSetItemResponse *msg = dynamic_cast<MsgMarketSetItemResponse *>(pMsg);
	if (!msg)return;

	if (msg->errcode==Error::Success)
	{
		CPEventHelper::uiNotify("","",Error::BoothUpSuccess); 
	}
}

void MsgMaster::HandleMessageMsgItemOperationResponsePile( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgItemOperationResponsePile, pMsg);

	if (msg->errorcode == Error::Success)
	{
		//发送下一条步奏
		BagOperator::DoNextPile();
	}
	else
	{
		BagOperator::setcanSort(true);
	}
}

void MsgMaster::HandleMessageItemOperationResponseRepair( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgItemOperationResponseRepair, pMsg);

	if (msg->errcode == Error::Success)
	{
		//发送下一条步奏
		BagOperator::DoNextRepair();
	}
	else
	{
		CPEventHelper::uiNotify("","",msg->errcode); 
	}
}

void MsgMaster::HandleMessageItemInfoDataGetResponse( IMsg *pMsg )
{
	MsgItemInfoDataGetResponse* msg=dynamic_cast<MsgItemInfoDataGetResponse*> (pMsg);
	if(!msg) return;

	if (GameData::s_user->m_pMainRole->m_pMarketItemList.size()!=0)
	{
		std::vector< UserItem* >::iterator it;
		for (it=GameData::s_user->m_pMainRole->m_pMarketItemList.begin();it!=GameData::s_user->m_pMainRole->m_pMarketItemList.end();it++)
		{
			UserItem* userItem=(UserItem*)*it;
			if (userItem->iid==msg->iid)
			{
				std::vector<ItemExData >::iterator it1;
				for (it1=msg->data.begin();it1!=msg->data.end();it1++)
				{
					ItemExData itemex=(ItemExData)*it1;
					userItem->data[itemex.nIdx]=itemex.data;
					userItem->pid = msg->pid;
				}
			}
		}
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_MARKETITEM_UPDATA);
		CPEventHelper::msgResponse("MsgItemInfoDataGetResponse","",msg->errcode);
	}
	
	if (GameData::s_user->m_pOtherRole->m_pAllItemMap.size()!=0)
	{
		std::vector< UserItem* >::iterator it;
		for (it=GameData::s_user->m_pOtherRole->m_pAllItemList.begin();it!=GameData::s_user->m_pOtherRole->m_pAllItemList.end();it++)
		{
			UserItem* userItem=*it;
			if (userItem->iid==msg->iid)
			{
				std::vector<ItemExData >::iterator it1;
				for (it1=msg->data.begin();it1!=msg->data.end();it1++)
				{
					ItemExData itemex=(ItemExData)*it1;
					userItem->data[itemex.nIdx]=itemex.data;
					userItem->pid = msg->pid;
				}
			}
		}
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SELECT_ITEM);
	}

	if (GameData::s_user->m_pMainRole->m_pTradeItemList.size()!=0)
	{
		std::vector< UserItem* >::iterator it;
		for (it=GameData::s_user->m_pMainRole->m_pTradeItemList.begin();it!=GameData::s_user->m_pMainRole->m_pTradeItemList.end();it++)
		{
			UserItem* userItem=(UserItem*)*it;
			if (userItem->iid==msg->iid)
			{
				std::vector<ItemExData >::iterator it1;
				for (it1=msg->data.begin();it1!=msg->data.end();it1++)
				{
					const ItemExData &itemex=(ItemExData)*it1;
					userItem->data[itemex.nIdx]=itemex.data;
					userItem->pid = msg->pid;
				}
			}
		}
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TRADEITEM_INFO);
	}

	// chat item show
	if (msg->errcode == Error::Success)
	{
		int itemPID = 0, itemID = 0;
		ModuleData::getInt(CPModuleName::CHAT, CPChatData::CHAT_ITEM_PID, itemPID);
		ModuleData::getInt(CPModuleName::CHAT, CPChatData::CHAT_ITEM_ID, itemID);
		if (itemPID == msg->pid
			&& itemID == msg->iid)
		{
			SubModuleData::init(CPModuleName::CHAT, CPChatData::CHAT_ITEM_DATA_LIST);
			SubModuleData::clearAll();
			for (int i = 0; i < (int)msg->data.size(); i++)
			{
				const ItemExData &itemExData = msg->data[i];
				SubModuleData::setInt(itemExData.nIdx, CPChatData::CHAT_ITEM_DATA, itemExData.data);
			}
		}
	}	
	CPEventHelper::msgResponse("HandleMessageItemInfoDataGetResponse", "", msg->errcode);
}

// horse
void MsgMaster::HandleHorsePeiYangAck(IMsg *pMsg)
{
	MsgHorsePeiYangAck* msg=dynamic_cast<MsgHorsePeiYangAck*> (pMsg);
	if(!msg) return;

	if (msg->ErrorCode != Error::Success)
	{
		CPEventHelper::uiNotify("", "", msg->ErrorCode); 
		return;
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_HORSE_ADD_EXP);
}

void MsgMaster::HandleHorseJinJieAck(IMsg *pMsg)
{
	MsgHorseJinJieAck* msg=dynamic_cast<MsgHorseJinJieAck*> (pMsg);
	if(!msg) return;

	if (msg->ErrorCode != Error::Success)
	{
		CPEventHelper::uiNotify("", "", msg->ErrorCode); 
		return;
	}

	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_HORSE_LEVEL_UP);
}

void MsgMaster::HandleHorseEquipQiangHuaAck(IMsg *pMsg)
{
	MsgHorseEquipQiangHuaAck* msg=dynamic_cast<MsgHorseEquipQiangHuaAck*> (pMsg);
	if(!msg) return;

	if (msg->ErrorCode != Error::Success)
	{
		CPEventHelper::uiNotify("", "", msg->ErrorCode); 
		return;
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_HORSE_EQUIP_ADD_EXP);
}

void MsgMaster::HandleHorseEquipJinJieAck(IMsg *pMsg)
{
	MsgHorseEquipJinJieAck* msg=dynamic_cast<MsgHorseEquipJinJieAck*> (pMsg);
	if(!msg) return;

	if (msg->ErrorCode != Error::Success)
	{
		CPEventHelper::uiNotify("", "", msg->ErrorCode); 
		return;
	}

	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_HORSE_EQUIP_LEVEL_UP);
}
