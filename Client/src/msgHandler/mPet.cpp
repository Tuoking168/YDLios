#include "MsgMaster.h"
#include "userdata/GameData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/UserData.h"
#include "userdata/UserPetData.h"
#include "userdata/HeroData.h"
#include "userdata/BoothData.h"
#include "userdata/netdata/GameRole.h"
#include "EntityDefinition.h"
#include "event/EventProtocol.h"

//#include "ModuleData.h"
#include "event/CPEventHelper.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/MainPanel.h"
#include "ErrorDefinition.h"


void MsgMaster::HandleMessageUpdPetInfoBaseNotify( IMsg *pMsg )
{
	MsgUpdPetInfoBaseNotify *msg = dynamic_cast<MsgUpdPetInfoBaseNotify *>(pMsg);
	if (!msg)return;
	
	//宠物基础属性
	typedef std::vector< PetInfo > PetInfoList;
	PetInfoList petbase	=msg->petBase;
	PetInfoList::iterator it=petbase.begin();
	for (it;it!=petbase.end();it++)
	{
		PetInfo petinfo=(PetInfo)*it;
		UserPet* pPet=GameData::s_user->getUserPetData()->getPetByIid(petinfo.id); 
		if (pPet)
		{
			pPet->lvl=petinfo.lvl;
			pPet->exp=petinfo.exp;
			pPet->name=petinfo.name;
			pPet->sid=petinfo.sid;
			pPet->state=petinfo.state;
		}	
		else
		{
			UserPet* pNewPet= new UserPet;
			pNewPet->iid=petinfo.id;
			pNewPet->lvl=petinfo.lvl;
			pNewPet->exp=petinfo.exp;
			pNewPet->name=petinfo.name;
			pNewPet->sid=petinfo.sid;
			pNewPet->state=petinfo.state;

			for (int i=Entity::attr_pet_start;i<Entity::attr_pet_end;i++)
			{
				pNewPet->exdata[i]=0;
			}
			GameData::s_user->getUserPetData()->addPet(pNewPet);
		}
		if (petinfo.state==Entity::pet_on)
		{
			GameData::s_user->m_pMainRole->m_iCurrentPetiid=petinfo.id;
		}
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PET_UPDDATA);
}

void MsgMaster::HandleMessageUpdPetCombatNotify( IMsg *pMsg )
{	
	MsgUpdPetCombatNotify *msg = dynamic_cast<MsgUpdPetCombatNotify *>(pMsg);
	if (!msg)return;

	UserPet* pPet=GameData::s_user->getUserPetData()->getPetByIid(msg->id);
	if (pPet)
	{
		for (int i= Combat::prop_Start;i< Combat::prop_Normal_End;i++)
		{
			pPet->data[i]=msg->combatdata[i];
		}
	}	
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PET_UPDDATA);
}

void MsgMaster::HandleMessageRmvPetResponse( IMsg *pMsg )
{
	MsgRmvPetResponse* msg = dynamic_cast<MsgRmvPetResponse *>(pMsg);
	if (!msg)return;
		
}

void MsgMaster::HandleMessageActivePetStateResponse( IMsg *pMsg )
{
	MsgActivePetStateResponse *msg = dynamic_cast<MsgActivePetStateResponse *>(pMsg);
	if (!msg)return;


	CPEventHelper::msgResponse("","",msg->errcode);
}

void MsgMaster::HandleMessagePetStateNotify( IMsg *pMsg )//更新宠物状态
{
	MsgPetStateNotify *msg = dynamic_cast<MsgPetStateNotify *>(pMsg);
	if (!msg)return;

	UserPet* pPet=GameData::s_user->getUserPetData()->getPetByIid(msg->id);
	if (pPet)
	{
		pPet->state=msg->state;
		if (pPet->state==Entity::pet_sleep)
		{
			GameData::s_user->m_pMainRole->m_iCurrentPetiid=0;
		}
		else if (pPet->state==Entity::pet_on)			
		{
			GameData::s_user->m_pMainRole->m_iCurrentPetiid=pPet->iid;
		}
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PET_UPDDATA);
}

void MsgMaster::HandleMessageRelivePetResponse( IMsg *pMsg )//复活宠物
{
	MsgRelivePetResponse *msg = dynamic_cast<MsgRelivePetResponse *>(pMsg);
	if (!msg)return;
}

void MsgMaster::HandleMessageFeedPetResponse( IMsg* pMsg )//喂养宠物
{
	MsgFeedPetResponse *msg = dynamic_cast<MsgFeedPetResponse *>(pMsg);
	if (!msg)return;

	CPEventHelper::msgResponse("HandleMessageFeedPetResponse","",msg->errcode);
	//EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PET_UPDDATA);
}

void MsgMaster::HandleMessageUpdPetLvlExpNotify( IMsg *pMsg )//宠物经验
{
	MsgUpdPetLvlExpNotify *msg = dynamic_cast<MsgUpdPetLvlExpNotify *>(pMsg);
	if (!msg)return;

	UserPet* pPet=GameData::s_user->getUserPetData()->getPetByIid(msg->id);
	int n=EventProtocol::EVENT_PET_UPDDATA;
	if (pPet)
	{
		int expcnt=msg->exp-pPet->exp;
		if (expcnt<=0)
		{
			expcnt=-expcnt;
		}
		if (pPet->lvl==msg->lvl)
		{
			n=EventProtocol::EVENT_PET_GETEXP; 
		}
		else
		{
			n=EventProtocol::EVENT_PET_LEVELUP;
		}
		pPet->lvl=msg->lvl;
		pPet->exp=msg->exp;
		CPEventHelper::msgNotify("HandleMessageUpdPetLvlExpNotify","",msg->opcode,expcnt,0,0); 
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(n);
}

void MsgMaster::HandleMessageAddPetNotify( IMsg *pMsg )
{
	//得到宠物
	MsgAddPetNotify *msg = dynamic_cast<MsgAddPetNotify *>(pMsg);
	if (!msg)return;

	int iid = msg->petBase.id;
	int sid = msg->petBase.sid;
	int exp = msg->petBase.exp;
	int lvl = msg->petBase.lvl;
	int state = msg->petBase.state;
	std::string name = msg->petBase.name;

	UserPet* pet = new UserPet;
	pet->iid = iid;
	pet->sid = sid;
	pet->exp = exp;
	pet->lvl = lvl;
	pet->name = name;
	pet->state = state;
	for (int i=Combat::prop_Start;i<Combat::prop_Normal_End;i++)
	{
		pet->data[i]=msg->combatdata[i];
	}
	for (int i=Entity::attr_pet_start;i<Entity::attr_pet_end;i++)
	{
		pet->exdata[i]=0;
	}

	GameData::s_user->getUserPetData()->addPet(pet);

	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PET_UPDDATA);
}


void MsgMaster::HandleMessageSetPetPickStateResponse( IMsg *pMsg )
{
	MsgSetPetPickStateResponse *msg = dynamic_cast<MsgSetPetPickStateResponse *>(pMsg);
	if (!msg)return;
}


void MsgMaster::HandleMessageOpenMarketResponse( IMsg *pMsg )
{
	MsgOpenMarketResponse* msg = dynamic_cast<MsgOpenMarketResponse *>(pMsg);
	if (!msg)return;

	Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);
	if (msg->errcode == Error::Success)
	{
		HeroData::setProp(Entity::attr_market_state,1);
	}
	else
	{
		CPEventHelper::uiNotify("", "", msg->errcode); 
	}
}

void MsgMaster::HandleMessageCloseMarketResponse( IMsg *pMsg )
{
	MsgCloseMarketResponse* msg = dynamic_cast<MsgCloseMarketResponse *>(pMsg);
	if (!msg)return;
	
	Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);
	HeroData::setProp(Entity::attr_market_state,0);
}


void MsgMaster::HandleMessageImprisonPetResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgImprisonPetResponse, pMsg);
	if (!msg) return;

	CPEventHelper::msgNotify("HandleMessageImprisonPetResponse", "", Opcode::Op_ImprisonPet, msg->errcode, 0, 0);
}

void MsgMaster::HandleMessageRmvPetNotify( IMsg *pMsg )
{
	MsgRmvPetNotify* msg = dynamic_cast<MsgRmvPetNotify *>(pMsg);
	if (!msg)return;
	//msg->petid;
	GameData::s_user->getUserPetData()->rmvPetByiid(msg->petid);
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PET_REMOVE);

}

void MsgMaster::HandleMessageSyncPetExPropDataNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncPetExPropDataNotify, pMsg);
	if (!msg) return;
	
	UserPet* pPet=GameData::s_user->getUserPetData()->getPetByIid(msg->petid);
	if (pPet)
	{
		pPet->exdata[msg->idx]=msg->data;
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PET_UPDDATA);
		CPEventHelper::msgNotify("HandleMessageSyncPetExPropDataNotify", "",0,msg->idx,0,0,0);
	}

}

void MsgMaster::HandleMessageAddPetEggNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAddPetEggNotify, pMsg);
	if (!msg) return;

	UserPet* pPetEgg = GameData::s_user->getUserPetData()->getPetEggInfo(msg->id);
	if (pPetEgg)
	{
		pPetEgg->iid=msg->petBase.id;
		pPetEgg->lvl=msg->petBase.lvl;
		pPetEgg->exp=msg->petBase.exp;
		pPetEgg->name=msg->petBase.name;
		pPetEgg->sid=msg->petBase.sid;
		pPetEgg->state=msg->petBase.state;

		for (int i= Combat::prop_Start;i< Combat::prop_Normal_End;i++)
		{
			pPetEgg->data[i]=msg->combatdata[i];
		}
	}	
	else
	{
		UserPet* pNewPet= new UserPet;
		pNewPet->iid=msg->petBase.id;
		pNewPet->lvl=msg->petBase.lvl;
		pNewPet->exp=msg->petBase.exp;
		pNewPet->name=msg->petBase.name;
		pNewPet->sid=msg->petBase.sid;
		pNewPet->state=msg->petBase.state;
		GameData::s_user->getUserPetData()->addPetEgg(pNewPet,msg->id);

		for (int i= Combat::prop_Start;i< Combat::prop_Normal_End;i++)
		{
			pNewPet->data[i]=msg->combatdata[i];  
		}
	}
}

void MsgMaster::HandleMessageAddPetEggExNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAddPetEggExNotify, pMsg);
	if (!msg) return;

	UserPet* pPetEgg = GameData::s_user->getUserPetData()->getPetEggInfo(msg->id);
	if (pPetEgg)
	{
		pPetEgg->exdata[msg->idx] = msg->data;
	}
}

void MsgMaster::HandleMessageDogOptionResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgDogOptionResponse, pMsg);
	if (!msg) return;
	CPEventHelper::msgResponse("HandleMessageDogOptionResponse", "", msg->errcode);
}


void MsgMaster::HandleMessageImprovePetAdvanceResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgImprovePetAdvanceResponse, pMsg);
	if (!msg) return;
	CPEventHelper::msgResponse("HandleMessageImprovePetAdvanceResponse", "", msg->errcode);
}


void MsgMaster::HandleMessageChangePetBestAttrResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgChangePetBestAttrResponse, pMsg);
	if (!msg) return;
	CPEventHelper::msgResponse("HandleMessageChangePetBestAttrResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageSleepPetStateResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSleepPetStateResponse, pMsg);

	CPUnused(msg->id);
	CPUnused(msg->opcode);
	CPEventHelper::msgResponse("HandleMessageSleepPetStateResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageBuyEntityMarketThingResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgBuyEntityMarketThingResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageBuyEntityMarketThingResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageSetPetPickSettingResponse( IMsg *pMsg )
{

	CP_TEST_NULL_MSG(MsgSetPetPickSettingResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageSetPetPickSettingResponse", "", msg->errcode);
}

void MsgMaster::HandleMessagePetRebornResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgpetRebornResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessagePetRebornResponse", "", msg->errcode);
	CPEventHelper::msgNotify("HandleMessagePetRebornResponse", "",0,0,0,0,0);
}

void MsgMaster::HandleMessageAddMarketWordsResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgaddMarketWordsResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageAddMarketWordsResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGetMarketWordsResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsggetMarketWordsResponse, pMsg);
	MsggetMarketWordsResponse* wordsMsg = dynamic_cast<MsggetMarketWordsResponse*>(pMsg);
	std::vector< MarketWords > words = wordsMsg->words;
	BoothData::setWords(words);
	CPEventHelper::msgResponse("HandleMessageGetMarketWordsResponse", "", msg->errcode);
}