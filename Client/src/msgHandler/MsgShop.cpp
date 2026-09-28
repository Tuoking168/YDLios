#include "MsgMaster.h"
#include "ErrorDefinition.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/repodata/RepoData.h"

#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"

void MsgMaster::HandleMessageOpenShopResponseEx( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgOpenShopResponseEx, pMsg);
	//
	int nClientDataVer = 1;
	if (msg->serverDataVer != nClientDataVer)
	{
		CPEventHelper::msgResponse("HandleMessageOpenShopResponseEx", "", msg->errcode); 
	}
}

// This message is deprecated, use HandlMessageOpenShopResponseEx instead
void MsgMaster::HandleMessageOpenShopResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgOpenShopResponse, pMsg);
	//
	CPEventHelper::msgResponse("HandleMessageOpenShopResponseEx", "", msg->errcode); 
}

void MsgMaster::HandleMessageShopItemListNotify( IMsg *pMsg )
{
	if (!pMsg) return;
	MsgShopItemListNotify *msg = dynamic_cast<MsgShopItemListNotify *>(pMsg);
	if (!msg) return;
	
	GameData::s_user->mShopItems.resize(msg->items.size());
	for(unsigned int i=0; i<msg->items.size(); i++)
	{
		GameData::s_user->mShopItems[i] = msg->items[i];
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_GET_SHOP_DATA);

	CPEventHelper::msgNotify("HandleMessageShopItemListNotify","");
}

void MsgMaster::HandleMessageShopBackBuyNotify( IMsg *pMsg )
{
	if (!pMsg) return;
	MsgShopBackBuyNotify *msg = dynamic_cast<MsgShopBackBuyNotify *>(pMsg);
	if (!msg) return;
	RepoData::mRepoItemList.resize(msg->items.size());
	for(unsigned int i=0; i<msg->items.size(); i++)
	{
		RepoData::mRepoItemList[i] = msg->items[i];
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_GET_REPO_DATA);
}

void MsgMaster::HandleMessageShopBackBuyRmvNotify( IMsg *pMsg )
{
	if (!pMsg) return;
	MsgShopBackBuyRmvNotify *msg = dynamic_cast<MsgShopBackBuyRmvNotify *>(pMsg);
	if (!msg) return;
	for(unsigned int i=0; i<RepoData::mRepoItemList.size(); i++)
	{
		if(RepoData::mRepoItemList[i].itemiid == msg->itemiid)
		{
			RepoData::mRepoItemList.erase(RepoData::mRepoItemList.begin()+i);
			break;
		}
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_GET_REPO_DATA);
}

void MsgMaster::HandleMessageShopBackBuyAddNotify( IMsg *pMsg )
{
	if (!pMsg) return;
	MsgShopBackBuyAddNotify *msg = dynamic_cast<MsgShopBackBuyAddNotify *>(pMsg);
	if (!msg) return;
	RepoData::mRepoItemList.push_back(msg->item);
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_GET_REPO_DATA);
}

void MsgMaster::HandleMessageShopBackItemResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgShopBackBuyItemResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageShopBackItemResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageBuyItemInShopResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgBuyItemInShopResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageBuyItemInShopResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageCloseShopResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgCloseShopResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageCloseShopResponse", "", Error::Success);
}

