#include "MsgMaster.h"
#include "EvtDataDefinition.h"
#include "OpcodeDefinition.h"
#include "UserDataModule.h"
#include "ModuleData.h"
#include "GuildModule.h"
#include "ChatModule.h"
#include "QuestDefinition.h"
#include "MsgScene.h"

#include "userdata/SystemData.h"
#include "userdata/skilldata/SkillEffect.h"
#include "EntityDefinition.h"
#include "script/LuaWrapper.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/OtherRole.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/LayoutData.h"
#include "UserData/HeroData.h"
#include "userdata/TaskData.h"
#include "userdata/ActivityData.h"
#include "userdata/activitydata/WorshipData.h"
#include "userdata/activitydata/TreasureHuntData.h"
#include "userdata/UserItemData.h"
#include "userdata/testdata/TestData.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/NPCFunctionData.h"

#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "userdata/FuncData.h"
#include "scene/panel/FloatPanel.h"

#include <math.h>
#pragma warning (disable:4018)

#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"

#include "network/HandleMessage.h"

#include "res/AudioLoader.h"
#include "logic/platform/PlatformOpID.h"
#include "logic/platform/IPlatform.h"

using namespace Entity;
using namespace std;


void MsgMaster::HandleMessageUpdPlayerBaseNotify( IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgUpdPlayerBaseNotify, pMsg);

	GameRole *myRole = GameData::getMyRole();
	myRole->mType = GHOST_TYPE_THIS;
	myRole->mName = msg->mName;

 	if(msg->cloth == 0)
 	{
 		msg->cloth = -1;
 	}
	myRole->setDress(AVATAR_TYPE_CLOTH, msg->cloth);
	myRole->setDress(AVATAR_TYPE_WINGS, msg->wing);
	myRole->setDress(AVATAR_TYPE_YUANSHEN, msg->yuanshen);//元神外观
	UserItem *pItem1= GameData::s_user->getUserItemData()->getItemByPosition(-3);
	if(pItem1==NULL)
	{
		myRole->setDress(AVATAR_TYPE_WEAPON, msg->weapon);
	}
	myRole->mGhostGender = msg->mGender;
	myRole->mGhostJob = msg->mJob;
	HeroData::setJob(msg->mJob);
	HeroData::setGender(msg->mGender);

	CPEventHelper::msgNotify("HandleMessageUpdPlayerBaseNotify", "");
}

void MsgMaster::HandleMessageUpdPlayerCombatAllNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgUpdPlayerCombatDataAllNotify, pMsg);

	for (short idx = 0; idx < Combat::prop_Normal_End && idx<msg->combatdata.size(); idx++)
	{
		GameData::s_user->m_pMainRole->CombatData[idx] = msg->combatdata[idx];
	}
	GameData::s_user->m_pMainRole->mMaxHp = GameData::s_user->m_pMainRole->CombatData[Combat::prop_HPMax];
	GameData::s_user->m_pMainRole->mMaxMp = GameData::s_user->m_pMainRole->CombatData[Combat::prop_MPMax];
	GameData::s_user->m_pMainRole->mHp = GameData::s_user->m_pMainRole->CombatData[Combat::prop_HP];
	GameData::s_user->m_pMainRole->setMP(GameData::s_user->m_pMainRole->CombatData[Combat::prop_MP]);
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_CHANGE_HP);
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_CHANGE_MP);
}

void MsgMaster::HandleMessageUpdPlayerCombatDataExNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgUpdPlayerCombatDataExNotify, pMsg);
	
	int idata = 0;
	for (int idx = 1; idx < Combat::prop_Normal_End; idx++)
	{
		if (msg->combo & (1 << (idx - 1)))
		{
			if (GameData::s_user->m_pMainRole->CombatData[idx] != msg->data[idata])
			{
				const int count = msg->data[idata] - GameData::s_user->m_pMainRole->CombatData[idx];
				GameData::s_user->m_pMainRole->CombatData[idx] = msg->data[idata];
				if (msg->opcode!=Opcode::Op_EquipPutOnOff)
				{
					CPEventHelper::msgNotify("MsgUpdPlayerCombatDataExNotify", "", msg->opcode, idx, count, 0);   
				}
			}
			idata++;
		}

		if (idata >= (int)msg->data.size())
		{
			break;
		}
	}

	GameData::s_user->m_pMainRole->mMaxHp = GameData::s_user->m_pMainRole->CombatData[Combat::prop_HPMax];
	GameData::s_user->m_pMainRole->mMaxMp = GameData::s_user->m_pMainRole->CombatData[Combat::prop_MPMax];
	GameData::s_user->m_pMainRole->mHp = GameData::s_user->m_pMainRole->CombatData[Combat::prop_HP];
	GameData::s_user->m_pMainRole->setMP(GameData::s_user->m_pMainRole->CombatData[Combat::prop_MP]);
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ATTRIBUTE_CHANGE);
}


void MsgMaster::HandleMessageUpdPlayerDetailNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgUpdPlayerDetailNotify, pMsg);

	GameData::s_user->m_pMainRole->Honour = msg->honor;
 	GameData::s_user->m_pMainRole->PK_NUM = msg->pkvalue;
	HeroData::setProp(Entity::attr_pkvalue, msg->pkvalue);
	HeroData::setProp(Entity::attr_money, msg->gold);
	HeroData::setProp(Entity::attr_gold, msg->vcoin);
	HeroData::setProp(Entity::attr_bagslot, msg->bagslot);
	HeroData::setProp(Entity::attr_diamond, msg->coupon);//仙玉
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
}

/**
 * 处理玩家金币更新通知消息
 * 更新本地金币数据并派发相关事件
 * 
 * @param pMsg 消息指针，包含新的金币数量
 */
void MsgMaster::HandleMessageUpdPlayerGoldNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgUpdPlayerGoldNotify, pMsg);
	
	// 计算金币变化量：新值 - 旧值
	const int count = msg->gold - HeroData::getProp(Entity::attr_money);
	
	// 更新本地金币数据
	HeroData::setProp(Entity::attr_money, msg->gold);
	
	// 派发物品更新事件，通知UI刷新
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
	
	// 如果金币数量发生变化
	if (count != 0)
	{
		// 如果是增加金币，播放获得金币音效
		if (count > 0)
		{
			AudioLoader::play(Sound::Effect::huodejinbi);
		}
		
		// 发送金币变化通知事件
		CPEventHelper::msgNotify(
			"HandleMessageUpdPlayerGoldNotify",	// 事件来源标识
			"",									// 额外信息
			Opcode::Op_Item,					// 操作码类型：物品相关
			Things_money,						// 物品类型：货币
			count,								// 变化数量
			msg->opcode							// 操作码
		);
	}
}

/**
 * 处理玩家代金券更新通知消息
 * 更新本地代金券数据并派发相关事件
 * 
 * @param pMsg 消息指针，包含新的代金券数量
 */
void MsgMaster::HandleMessageUpdPlayerCouponNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgUpdPlayerCouponNotify, pMsg);

	// 计算代金券变化量：新值 - 旧值
	const int count = msg->coupon - HeroData::getProp(Entity::attr_diamond);
	
	// 更新本地代金券数据
	HeroData::setProp(Entity::attr_diamond, msg->coupon);
	
	// 派发物品更新事件，通知UI刷新
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
	
	// 如果代金券数量发生变化
	if (count != 0)
	{
		// 发送代金券变化通知事件
		CPEventHelper::msgNotify(
			"HandleMessageUpdPlayerCouponNotify",	// 事件来源标识
			"",									// 额外信息
			Opcode::Op_Item,					// 操作码类型：物品相关
			Things_diamond,						// 物品类型：代金券
			count,								// 变化数量
			msg->opcode							// 操作码
		);
	}
}

/**
 * 处理玩家充值货币更新通知消息
 * 更新本地充值货币数据并处理充值相关逻辑
 * 
 * @param pMsg 消息指针，包含新的充值货币数量
 */
void MsgMaster::HandleMessageUpdPlayerVcoinNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgUpdPlayerVcoinNotify, pMsg);

	// 计算充值货币变化量：新值 - 旧值
	const int count = msg->vcoin - HeroData::getProp(Entity::attr_gold);
	
	// 更新本地充值货币数据
	HeroData::setProp(Entity::attr_gold, msg->vcoin);
	
	// 派发物品更新事件，通知UI刷新
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
	
	// 如果充值货币数量发生变化
	if (count != 0)
	{
		// 发送充值货币变化通知事件
		CPEventHelper::msgNotify(
			"HandleMessageUpdPlayerVcoinNotify",	// 事件来源标识
			"",									// 额外信息
			Opcode::Op_Item,					// 操作码类型：物品相关
			Things_gold,						// 物品类型：充值货币
			count,								// 变化数量
			msg->opcode							// 操作码
		);
	}

	// 如果是充值增加且操作码为109（可能表示充值成功）
	if (count > 0 && msg->opcode == 109)
	{
		// 记录充值获得的货币数量
		HeroData::setProp(Entity::attr_recharge_gold, count);
		
		// 执行平台充值成功相关操作
		CPPlatform->operate(PlatformOpID::recharge_success);
	}
}
void MsgMaster::HandleMessageUpdPlayerHonorNotify( IMsg *pMsg )
{
	MsgUpdPlayerHonorNotify* msg=dynamic_cast<MsgUpdPlayerHonorNotify*>(pMsg);
	if (msg==NULL)
	{
		return;
	}

	int count=msg->honor-GameData::s_user->m_pMainRole->Honour;
	GameData::s_user->m_pMainRole->Honour = msg->honor;
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);

	if (count!=0)
	{
		CPEventHelper::msgNotify("","",Opcode::Op_Item,Things_honor,count,msg->opcode);
	}
}

void MsgMaster::HandleMessageUpdBaseCoolDownNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgUpdBaseCoolDownNotify, pMsg);

	HeroData::setCommonCD(msg->cdtype, msg->cdtime, msg->data);
	CPEventHelper::msgNotify("HandleMessageUpdBaseCoolDownNotify", "");
}

void MsgMaster::HandleMessageCleanCoolDownResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgCleanCoolDownResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageCleanCoolDownResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageUpdPlayerReputationNotify(IMsg *pMsg)
{
	//
}

void MsgMaster::HandleMessageUpdPlayerMeritoriousNotify( IMsg *pMsg )
{
	// 
}

void MsgMaster::HandleMessageUpdPlayerPropsDataNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgUpdPlayerPropsDataNotify, pMsg);

	const int oldData = HeroData::getProp(msg->type);
	const int diff = msg->data - oldData;

	HeroData::setProp(msg->type, msg->data);
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->setExData(msg->type,msg->data);

	CPEventHelper::msgNotify("HandleMessageUpdPlayerPropsDataNotify", "", Opcode::Op_PropUpdate, msg->type, msg->data, diff, msg->opcode);
	
	switch (msg->type)
	{
	case Entity::attr_dog_cnt:
		{
			//如果有狗，就通知界面显示与狗相关技能按钮
			if (msg->data > 0)
			{
				CPEventHelper::uiNotify("UIShowDogSkillPanel", "", 0);
			}
			else
			{
				CPEventHelper::uiNotify("UIHideDogSkillPanel", "", 0);
			}
			break;
		}
	case Entity::attr_dog_mode:
		{
			CPEventHelper::uiNotify("UIRefreshDogMode", "", 0);
			const int opcode = (msg->data==Entity::edogm_Normal)?Opcode::Op_DogAttack:Opcode::Op_DogDefense;
			CPEventHelper::msgNotify("","",opcode,0,0,0); 
			break;
		}
	case Entity::attr_intergration:
	case Entity::attr_bagslot:
		{
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
			break;
		}
	case Entity::attr_guild_contribution:
	case Entity::attr_guild_post:
		{
			CPEventHelper::msgResponse("HandleMessageGuildMemberInfoByPidResponse", "", 0);
			break;
		}
	}
}

void MsgMaster::HandleMessagePlayerUseSkillResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgPlayerUseSkillResponse, pMsg);
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_2, msg->skillid);
	CPEventHelper::msgResponse("HandleMessagePlayerUseSkillResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageUpdPlayerLvlExpNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgUpdPlayerLvlExpNotify, pMsg);

	const int64 count = msg->mExperience-GameData::s_user->m_pMainRole->mExperience;
 	GameData::s_user->m_pMainRole->mExperience = msg->mExperience;
 	GameData::s_user->m_pMainRole->mExperienceNext = msg->mExperienceNext;
 
	HeroData::setLevel(msg->mLevel);

	const int dLevel = msg->mLevel - GameData::s_user->m_pMainRole->mLevel;
	if (dLevel != 0)
	{
		GameData::s_user->m_pMainRole->mLevel = msg->mLevel;
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_CHANGE_LEVEL);
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_EXPERIENCE_CHANGE);
	
	const bool isInitData = (dLevel == msg->mLevel);
	if (!isInitData)
	{
		CPEventHelper::msgNotify("HandleMessageUpdPlayerLvlExpNotify", "", Opcode::Op_PlayerLvlExp, dLevel, count, msg->opcode);
	}
	else
	{
		CPEventHelper::msgNotify("HandleMessageUpdPlayerLvlExpNotify|Init", "", Opcode::Op_PlayerLvlExp, dLevel, count, msg->opcode);
	}
}

void MsgMaster::HandleMessageQuestUpdateList( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgQuestUpdateListNotify, pMsg);

	if (msg->quests.empty())
	{
		TaskData::setTask(0, Quest::line_Main, Quest::state_Available, 0, 0, 0);
		MsgQuestAcceptRequest* req = new MsgQuestAcceptRequest;
		req->qid = Quest::line_Main;
		req->sid = 0;
		HandleMessage::sendMessage(req);
		return;
	}

	TaskData::clearTasks();
	for (int i = 0; i < (int)msg->quests.size(); i++)
	{
		const QuestInfo &info = msg->quests[i];
		TaskData::setTask(info.sid, info.qid, info.state, info.datax, info.datay, info.dataz);
	}

	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TASK_RECEIVED);
	CPEventHelper::msgNotify("HandleMessageQuestUpdateList", "", 0, 0, 0, 0);
}

void MsgMaster::HandleMessageQuestUpdate( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgQuestUpdateNotify, pMsg);
	
	const QuestInfo &info = msg->quest;
	TaskData::setTask(info.sid, info.qid, info.state, info.datax, info.datay, info.dataz);

	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TASK_RECEIVED);
	CPEventHelper::msgNotify("HandleMessageQuestUpdate", "", msg->opcode, info.sid, info.state, info.qid);
}

void MsgMaster::HandleMessageQuestAcceptResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgQuestAcceptResponse, pMsg);

	CPEventHelper::msgResponse("", "", msg->errcode);
}

void MsgMaster::HandleMessageQuestSubmitResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgQuestSubmitResponse, pMsg);

	CPEventHelper::msgResponse("", "", msg->errcode);
}

void MsgMaster::HandleMessageQuestRemoveResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgQuestRemoveResponse, pMsg);

	CPEventHelper::msgResponse("", "", msg->errcode);
}

void MsgMaster::HandleMessageReviveEntityResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgReviveEntityResponse, pMsg);

	if (msg->errcode == Error::Success)
	{
		CPUnused(msg->eid);
		CPUnused(msg->sceneid);
		
		GameRole* myRole = GameData::getMyRole();
		if (myRole)
		{
			myRole->setState(AVATAR_ACTION_IDLE);
			myRole->mTx = msg->posx;
			myRole->mTy = msg->posy;
		}
	}
	CPEventHelper::msgResponse("HandleMessageReviveEntityResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageClickNPCResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgClickNPCResponse, pMsg);

	if (msg->errcode == Error::Success)
	{
		GameData::s_user->questlist.clear();
		GameData::s_user->functionlist.clear();
		//给当前NPC的任务，功能填充
		std::vector<npcFunction>::iterator it;
		for (it=msg->function.begin();it!=msg->function.end();it++)
		{
			npcFunction i=(npcFunction)*it;
			if (i.functionid==0)//任务
			{
				int state = TaskData::getTaskState(i.data);
				if (state!=Quest::state_Submited)
				{
					GameData::s_user->questlist.push_back(i.data);
				}
			}
			else//NPC功能
			{				
				GameData::s_user->functionlist.push_back(i);
			}
		}
		//发送监听提示更新对话框界面
		//EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_NPC_CLICK);
	}
	CPEventHelper::msgResponse("HandleMessageClickNPCResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageClickNPCFunctionScriptResponse( IMsg *pMsg )
{
	MsgClickNPCFunctionScriptResponse *msg = dynamic_cast<MsgClickNPCFunctionScriptResponse *>(pMsg);
	if (!msg) return;
	
	CPEventHelper::msgResponse("HandleMessageClickNPCFunctionScriptResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageCrossServerResponse( IMsg *pMsg )
{
	MsgCrossServerResponse *msg = dynamic_cast<MsgCrossServerResponse *>(pMsg);
	if (!msg) return;

	CPEventHelper::msgNotify("HandleMessageCrossServerNotify", "", msg->errcode, msg->ip, msg->port, msg->ServerID);
}


void MsgMaster::HandleMessageUpdPlayerSkillDataNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgUpdPlayerSkillDataNotify, pMsg);

	for(unsigned int i = 0; i < msg->skilldata.size(); i++)
	{
		const SkillInfo &info = msg->skilldata[i];
		HeroData::setSkillExp(info.sid, info.exp);
		if (UserData::getIntData(HeroData::getPID(),CPUserData::SET_FAST) == 0)
		{
			int position = info.position;
			if(position <= 0)
			{
				LuaData::getProp(LuaData::SKILL,info.sid,"position", position);
			}
			UserData::setIntData(HeroData::getPID(), CPUserData::FAST_TYPE_, position, 1);
			UserData::setIntData(HeroData::getPID(), CPUserData::FAST_NUM_, position, info.sid);
		}
	}

	if (UserData::getIntData(HeroData::getPID(),CPUserData::SET_FAST) == 0)
	{
		UserData::setIntData(HeroData::getPID(),CPUserData::SET_FAST, 1);
	}
	UserData::saveData();
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_NET_SKILL_CHANGE);
}

void MsgMaster::HandleMessageUpdSkillExpNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgUpdSkillExpNotify, pMsg);

	HeroData::setSkillExp(msg->sid, msg->exp);
	CPEventHelper::msgNotify("HandleMessageUpdSkillExpNotify", "", 0, msg->sid, msg->exp, 0);
}

void MsgMaster::HandleMessageAddSkillNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAddSkillNotify, pMsg);

	HeroData::setSkillExp(msg->sid, msg->exp);

	int position = 0;
	LuaData::getProp(LuaData::SKILL, msg->sid, "position", position);
	UserData::setIntData(HeroData::getPID(), CPUserData::FAST_TYPE_, position, 1);
	UserData::setIntData(HeroData::getPID(), CPUserData::FAST_NUM_, position, msg->sid);
	UserData::saveData();
	
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_NET_SKILL_CHANGE);
	CPEventHelper::msgNotify("HandleMessageAddSkillNotify", "", msg->opcode/*Opcode::Op_AddSkill*/, msg->sid, 0, 0);
}

void MsgMaster::HandleMessageRmvSkillNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgRmvSkillNotify, pMsg);

	HeroData::clearSkill(msg->sid);
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_NET_SKILL_CHANGE);
}

void MsgMaster::HandleMessageUpdSkillCoolDownNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgUpdSkillCoolDownNotify, pMsg);

	HeroData::setSkillCD(msg->sid, msg->cooldown);
	CPEventHelper::msgNotify("HandleMessageUpdSkillCoolDownNotify", "", 0, msg->sid, msg->cooldown, 0);
}

void MsgMaster::HandleMessageSpecialQuestCountResponse( IMsg *pMsg )
{
	MsgSpecialQuestCountResponse* msg=dynamic_cast<MsgSpecialQuestCountResponse*> (pMsg);
	if(!msg) return;

	switch (msg->qtype)
	{
	case Entity::attr_quest_remain_cnt_exp:
		GameData::s_user->m_pMainRole->m_iExpCount=msg->count;
		break;
	case Entity::attr_quest_remain_cnt_honor:
		GameData::s_user->m_pMainRole->m_iHonorCount=msg->count;
		break;
	case Entity::attr_quest_remain_cnt_money:
		GameData::s_user->m_pMainRole->m_iMoneyCount=msg->count;
		break;
	default:
		break;
	}
}

void MsgMaster::HandleMessageEntityMarketInfoNotify( IMsg *pMsg )
{
	MsgEntityMarketInfoNotify* msg=dynamic_cast<MsgEntityMarketInfoNotify*> (pMsg);
	if(!msg) return;

	//HeroData::setProp(Entity::attr_market_state,msg->mymarket);
	int ishigh,ismine;
	ishigh = (msg->mymarket)&(1<<1);
	ismine = (msg->mymarket)&1;
	if (ishigh>0)
	{
		ishigh=1;
	}
	if (ismine==1)
	{
		GameData::s_user->m_pMainRole->m_bMyBooth=true;
	}
	else
	{

		GameData::s_user->m_pMainRole->m_bMyBooth=false;
	}

	std::vector< UserItem* >::iterator it1;
	for (it1=GameData::s_user->m_pMainRole->m_pMarketItemList.begin();it1!=GameData::s_user->m_pMainRole->m_pMarketItemList.end();it1++)
	{
		delete *it1;
	}
	GameData::s_user->m_pMainRole->m_pMarketItemList.clear();
	GameData::s_user->m_pMainRole->m_iTargetpid=msg->pid;	
	GameData::s_user->m_pMainRole->m_sBoothTargetName=msg->name;	
	std::vector< MarketItemInfo >::iterator it;
	for (it=msg->items.begin();it!=msg->items.end();it++)
	{
		MarketItemInfo marketitem=(MarketItemInfo)*it;
		UserItem* userItem=CommonFunction::createNewItem(marketitem.sid);
		userItem->count=marketitem.cnt;
		userItem->position=marketitem.position;
		userItem->iid=marketitem.iid;
		userItem->data[ItemEquip::Item_Market_Type]=marketitem.selltype;
		userItem->data[ItemEquip::Item_Market_Price]=marketitem.price;

		GameData::s_user->m_pMainRole->m_pMarketItemList.push_back(userItem);
	}
	CPEventHelper::msgNotify("MsgEntityMarketInfoNotify","",0,ishigh,0,0);
	//EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);

}

void MsgMaster::HandleMessageSetPlayerPkModeResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSetPlayerPkModeResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageSetPlayerPkModeResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageChatNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgChatNotify, pMsg);

	// last chat type
	ModuleData::setInt(CPModuleName::CHAT, CPChatData::LAST_CHAT_TYPE, msg->chatType);

	// add record list
	int maxCnt = LayoutData::getInt(CPModuleName::CHAT, "normRecord");
	std::string listType = CPChatData::NORM_CHAT_LIST;
	if (msg->chatType == ChatDefinition::type_horn)
	{
		listType = CPChatData::HORN_CHAT_LIST;
		maxCnt = LayoutData::getInt(CPModuleName::CHAT, "hornRecord");
	}
	int lastChatID = 0;
	ModuleData::getInt(CPModuleName::CHAT, CPChatData::LAST_CHAT_ID, lastChatID);
	lastChatID++;
	SubModuleData::init(CPModuleName::CHAT, listType);
	SubModuleData::setInt(lastChatID, CPChatData::CHAT_TYPE, msg->chatType);
	SubModuleData::setInt(lastChatID, CPChatData::PID, msg->pid);
	SubModuleData::setString(lastChatID, CPChatData::PLAYER_NAME, msg->playerName);
	SubModuleData::setInt(lastChatID, CPChatData::GENDER, msg->gender);
	SubModuleData::setInt(lastChatID, CPChatData::VIP_LEVEL, msg->vipLevel);
	SubModuleData::setString(lastChatID, CPChatData::CHAT_TEXT, msg->chatText);
	ModuleData::setInt(CPModuleName::CHAT, CPChatData::LAST_CHAT_ID, lastChatID);

	IDVector vect;
	SubModuleData::getIDVector(vect);
	
	if ((int)vect.size() > maxCnt && maxCnt > 0)
	{
		SubModuleData::clearData(vect[0]);
	}

	//
	CPEventHelper::msgNotify("HandleMessageChatNotify", "", 0, 0, 0, 0);
}

void MsgMaster::HandleMessageChatResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgChatResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageChatResponse", "", msg->errcode);
}


void MsgMaster::HandleMessageUnlockBagSlotResponse( IMsg *pMsg )
{
	MsgUnlockBagSlotResponse *msg = dynamic_cast<MsgUnlockBagSlotResponse *>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgResponse("HandleMessageUnlockBagSlotResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageSyncPlayerEventDataNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncPlayerEventDataNotify, pMsg);

	ActivityData::setExData(msg->eventid, msg->datax, msg->datay, msg->dataz);
	CPEventHelper::msgNotify("HandleMessageSyncPlayerEventDataNotify", "", 0, msg->eventid, 0, 0);

	//dispatch events to UI
	switch (msg->eventid)
	{
	case EvtData::evt_cscg:
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_UPDATE_EMIGRATED_DATA);
		break;
	case EvtData::evt_xb:
		TreasureHuntData::_s_happiness_value = msg->datax;
		TreasureHuntData::_s_happiness_grade = msg->datay;
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_UPDATE_HAPPINESS);
		break;
	default:
		break;
	}
}

void MsgMaster::HandleMessageSyncPlayerLimitTimeRewardNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncPlayerLimitTimeRewardNotify, pMsg);

	HeroData::setRewardTime(msg->rewardtype, msg->remaintime, msg->datax, msg->datay, msg->dataz);
	CPEventHelper::msgNotify("HandleMessageSyncPlayerLimitTimeRewardNotify", "");
}

void MsgMaster::HandleMessageGetPlayerLimitTimeRewardResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGetPlayerLimitTimeRewardResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageGetPlayerLimitTimeRewardResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageOpenHonorResponse( IMsg *pMsg )
{
	MsgOpenHonorResponse *msg = dynamic_cast<MsgOpenHonorResponse *>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgResponse("HandleMessageOpenHonorResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageOpenHonorByGoldResponse( IMsg *pMsg )
{
	MsgOpenHonorByGoldResponse *msg = dynamic_cast<MsgOpenHonorByGoldResponse *>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgResponse("HandleMessageOpenHonorByGoldResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageUpgradeHonorResponse( IMsg *pMsg )
{
	MsgUpgradeHonorResponse *msg = dynamic_cast<MsgUpgradeHonorResponse *>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgResponse("HandleMessageUpgradeHonorResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageUpgradeHonorByGoldResponse( IMsg *pMsg )
{
	MsgUpgradeHonorByGoldResponse *msg = dynamic_cast<MsgUpgradeHonorByGoldResponse *>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgResponse("HandleMessageUpgradeHonorByGoldResponse", "", msg->errcode);
}


void MsgMaster::HandleMessageCloseHonorNotify( IMsg *pMsg )
{
	MsgCloseHonorNotify *msg = dynamic_cast<MsgCloseHonorNotify *>(pMsg);
	if (!msg)
	{
		return;
	}

}

void MsgMaster::HandleMessagePlayerUpdGeneNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgPlayerUpdGeneNotify, pMsg);

	HeroData::updateBuff(msg->gid, msg->duration,ActivityData::getWorldTime());
	CPEventHelper::msgNotify("HandleMessagePlayerUpdGeneNotify", "", 0, msg->gid, 0, 0);
}

void MsgMaster::HandleMessagePlayerRmvGeneNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgPlayerRmvGeneNotify, pMsg);

	HeroData::removeBuff(msg->gid);
	CPEventHelper::msgNotify("HandleMessagePlayerRmvGeneNotify", "", 0, msg->gid, 0, 0);
}

void MsgMaster::HandleMessageReBornResponse( IMsg *pMsg )
{

	MsgReBornResponse *msg = dynamic_cast<MsgReBornResponse *>(pMsg);
	if (!msg)
	{
		return;
	}

	CPEventHelper::msgResponse("MsgReBornResponse", "", msg->errcode);

}

void MsgMaster::HandleMesssagePlayerDeadInfoNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgPlayerDeadInfoNotify, pMsg);

	CPEventHelper::msgNotify("HandleMesssagePlayerDeadInfoNotify", "", 0, msg->killname,msg->killertype, msg->killsid);
}


void MsgMaster::HandleMessageGetOtherPlayerDataResponse( IMsg* pMsg )
{
	CP_TEST_NULL_MSG(MsgGetOtherPlayerDataResponse, pMsg);

	CPEventHelper::msgResponse("MsgGetOtherPlayerDataResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageSyncOtherPlayerDataNotify( IMsg* pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncOtherPlayerDataNotify, pMsg);

	GameData::s_user->clearOtherRole();
	GameData::s_user->m_pOtherRole->mID=msg->pid;
	GameData::s_user->m_pOtherRole->mGhostJob=msg->job;
	GameData::s_user->m_pOtherRole->mGhostGender=msg->gender;
	GameData::s_user->m_pOtherRole->mLevel=msg->lvl;
	GameData::s_user->m_pOtherRole->mName=msg->name;
	GameData::s_user->m_pOtherRole->mRebornlvl=msg->reborn;
	GameData::s_user->m_pOtherRole->Honour=msg->honor;
	GameData::s_user->m_pOtherRole->mPKValue=msg->pkvalue;
	GameData::s_user->m_pOtherRole->mCombatNum=msg->combatdatanum;
	for (int idx = 1; idx < Combat::prop_Normal_End; idx++)
	{
		GameData::s_user->m_pOtherRole->CombatData[idx] = msg->combatdata[idx];
	}
}
// 处理同步其他玩家装备信息的网络消息
// 参数：pMsg - 收到的网络消息
void MsgMaster::HandleMessageSyncOtherPlayerEquipNotify( IMsg* pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncOtherPlayerEquipNotify, pMsg);

	for (std::map<short,UserItem*>::iterator itt = GameData::s_user->m_pOtherRole->m_pAllItemMap.begin();itt!=GameData::s_user->m_pOtherRole->m_pAllItemMap.end();itt++)
	{
		UserItem* item = itt->second;
		if (item)
		{
			delete item;
		}
	}
	GameData::s_user->m_pOtherRole->m_pAllItemMap.clear();


	GameData::s_user->m_pOtherRole->setDress(AVATAR_TYPE_CLOTH, -1);
	std::vector<OtherEquip>::iterator it=msg->equips.begin();
	for (it;it!=msg->equips.end();it++)
	{
		OtherEquip item=*it;
		UserItem* pItem=CommonFunction::createNewItem(item.sid);
		pItem->position=item.position;
		pItem->iid=item.iid;
		pItem->data[ItemEquip::Item_RebornLvl]=item.itemreborn;
		pItem->data[ItemEquip::Item_EnhanceLevel]=item.itemlvl;
		GameData::s_user->m_pOtherRole->m_pAllItemList.push_back(pItem);
		GameData::s_user->m_pOtherRole->m_pAllItemMap[item.position]=pItem;
		if (ItemPosition_Equip_Cloth==pItem->position)
		{
			GameData::s_user->m_pOtherRole->setDress(AVATAR_TYPE_CLOTH, pItem->sid);
		}
		if (ItemPosition_Equip_Wings==pItem->position)
		{
			GameData::s_user->m_pOtherRole->setDress(AVATAR_TYPE_WINGS, pItem->sid);
		}
		
		
	}
	it=msg->equips.begin();
	for (it;it!=msg->equips.end();it++)
	{
		OtherEquip item=*it;
		if (ItemPosition_Equip_Fashion==item.position)
		{
			GameData::s_user->m_pOtherRole->setDress(AVATAR_TYPE_CLOTH, item.sid);
		}
	}

	std::map<short,UserItem*>::iterator itemit=GameData::s_user->m_pOtherRole->m_pAllItemMap.find(ItemPosition_Equip_Weapon);
	if (itemit!=GameData::s_user->m_pOtherRole->m_pAllItemMap.end())
	{
		UserItem *pItem1=itemit->second;
		if(pItem1)
		{
			GameData::s_user->m_pOtherRole->setDress(AVATAR_TYPE_WEAPON, pItem1->sid);
		}
	}
	itemit=GameData::s_user->m_pOtherRole->m_pAllItemMap.find(ItemPosition_Equip_Weapon_Two);
	if (itemit!=GameData::s_user->m_pOtherRole->m_pAllItemMap.end())
	{
		UserItem *pItem1=itemit->second;
		if(pItem1)
		{
			GameData::s_user->m_pOtherRole->setDress(AVATAR_TYPE_WEAPON, pItem1->sid);
		}
	}
	

	GameData::s_user->m_pOtherRole->UpdStoneArray();
	CPEventHelper::openPanel("SelectRolePanel");
}


void MsgMaster::HandleMessageGetGiftResponse( IMsg* pMsg )
{
	CP_TEST_NULL_MSG(MsgGetGiftResponse, pMsg);

	CPEventHelper::msgResponse("MsgGetGiftResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageSyncWorldTimeNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncWorldTimeNotify, pMsg);

	ActivityData::setWorldTime(msg->nowtime);
	CPEventHelper::msgNotify("HandleMessageSyncWorldTimeNotify", "");
}

void MsgMaster::HandleMessageReSignDayResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgReSignDayResponse, pMsg);
	CPEventHelper::msgResponse("MsgReSignDayResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageFuncDataNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgFuncDataNotify, pMsg);

	//调用脚本
	FuncData::setCurFuncID(msg->funcid);
	FuncData::setdatax(msg->datax);
	FuncData::setdatay(msg->datay);
	FuncData::setdataz(msg->dataz);
	NPCFunctionData::doFuncScript(msg->funcid,msg->datax,msg->datay,msg->dataz,msg->datas); 
	CPEventHelper::msgNotify("HandleMessageFuncDataNotify", "", 0, msg->datax, msg->datay, msg->dataz, msg->datas);
}

void MsgMaster::HandleMessageFuncDataOperatorResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgFuncDataOperatorResponse, pMsg);

	if (msg->errcode!=Error::Success)
	{
		CPEventHelper::msgResponse("MsgFuncDataOperatorResponse", "", msg->errcode);
	}
	else
	{
		if (msg->funcid==16 || msg->funcid == 21)
		{
			CPEventHelper::setEventIntData(CPEventName::UI_CLOSE,CPEventData::VALUE_1,msg->funcid);
			CPEventHelper::dispatcher(CPEventName::UI_CLOSE,"MsgFuncDataOperatorResponse","GameUI");
		}
	}
}

void MsgMaster::HandleMessageHeadTitleOperationResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgHeadTitleOperationResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageHeadTitleOperationResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageReNameResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgReNameResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageReNameResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageCommonResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgCommonResponse, pMsg);
	if (!msg)return;

	if (msg->errcode != Error::Success)
	{
		CPEventHelper::uiNotify("", "", msg->errcode); 
	}
	CPEventHelper::msgResponse("HandleMessageCommonResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageFloatPanelNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgFloatPanelNotify, pMsg);
	if (!msg)return;

	CPEventHelper::openPanel("FloatPanel", FloatPanelType::Common_Notice, msg->basestring);
}
