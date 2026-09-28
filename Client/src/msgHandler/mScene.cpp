#include "MsgMaster.h"
#include "EntityDefinition.h"
#include "SceneDefinition.h"
#include "WorldDefinition.h"
#include "ModuleData.h"

#include "userdata/GameData.h"
#include "userdata/ActivityData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/UserData.h"
#include "userdata/netdata/Ghost.h"
#include "userdata/netdata/AliveGhost.h"
#include "userdata/netdata/ItemGhost.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/SystemData.h"
#include "userdata/luadata/LuaData.h"
#include "event/EventProtocol.h"
#include "userdata/skilldata/SkillEffect.h"
#include "userdata/PlayerInfoData.h"
#include "userdata/UserItemData.h"
#include "userdata/SceneData.h"
#include "userdata/HeroData.h"
#include "userdata/StaticData.h"
#include "userdata/netdata/AutoAttack.h"

#include "logic/platform/IPlatform.h"

#include "event/CPEventHelper.h"

#include "utils/TestUtils.h"


void MsgMaster::HandleMessageEnterSceneResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgEnterSceneResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageEnterSceneResponse", "", msg->errcode);
}

void MsgMaster::HandleMessagePlayerMoveNotify(IMsg* pMsg)
{
	CP_TEST_NULL_MSG(MsgPlayerMoveNotify,pMsg);
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->handleMoveRes(msg->mMoveStep, msg->movetype, msg->dir, msg->posx, msg->posy);
}
 
void MsgMaster::HandleMessageMapByeNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgMapByeNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;
	pGhostManager->removeGhost(msg->eid);
}

void MsgMaster::HandleMessageEntityMoveNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgEntityMoveNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;
	Ghost* ghost = pGhostManager->getGhostById(msg->eid);
	if (ghost)
	{
		AliveGhost* pGhost = dynamic_cast<AliveGhost*>(ghost);
		if (pGhost)
		{
			if(msg->movetype == Avatar_Collide)
			{
				pGhost->handleCollideRes(msg->posx, msg->posy, msg->dir);
			}
			else if(msg->movetype == Avatar_Run)
			{
				pGhost->handleRunRes(msg->posx, msg->posy, msg->dir);
			}
			else if(msg->movetype == Avatar_Walk)
			{
				pGhost->handleWalkRes(msg->posx, msg->posy, msg->dir);
			}
			else if (msg->movetype == Avatar_Fly)
			{
				pGhost->handleSetPosition(msg->posx, msg->posy);
			}
		}
	}
	else
	{
		CCLog(">>>Error: id: %d not walk.", msg->eid);
	}
}

void MsgMaster::HandleMessageMeetEntityExDataNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgMeetEntityExDataNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;
	AliveGhost *ghost = dynamic_cast<AliveGhost *>(pGhostManager->getGhostById(msg->eid));
	if(ghost)
	{
		for (int i = 0; i < (int)msg->exdata.size(); i++)
		{
			const MeetExData &exData = msg->exdata[i];
			ghost->setExData(exData.type, exData.data);
		}
	}
}

void MsgMaster::HandleMessageMeetEntityExStrNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMeetEntityExStrNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;
	AliveGhost *ghost = dynamic_cast<AliveGhost *>(pGhostManager->getGhostById(msg->eid));
	if(ghost)
	{
		for (int i = 0; i < (int)msg->exstr.size(); i++)
		{
			const MeetExStr &exData = msg->exstr[i];
			ghost->setExStr(exData.type, exData.data);
		}
	}
}
//地图外观刷新
void MsgMaster::HandleMessageMapMeetPlayerNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMapMeetPlayerNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	if(GameData::s_game_state!=GAME_STATE_RUNNING)
	{
		return;
	}

	HeroAvatar* g = new HeroAvatar;
	if(g)
	{
		g->mID = msg->eid;
		g->mType = GHOST_TYPE_PLAYER;
		g->mTx = msg->posx;
		g->mTy = msg->posy;
		g->setDirection(msg->dir);
		if(msg->cloth==0)
		{
			msg->cloth=-1;
		}
		g->setDress(AVATAR_TYPE_CLOTH, msg->cloth);
		g->setDress(AVATAR_TYPE_WEAPON, msg->weapon);
		g->setDress(AVATAR_TYPE_WINGS, msg->wings);
		// ============ 新增：设置元神外观 ============
        if (msg->yuanshen != 0)
        {
            g->setDress(AVATAR_TYPE_YUANSHEN, msg->yuanshen);//自己加的元神外观
        }
        g->mMaxHp = msg->maxhp;
        g->mMaxMp = msg->maxmp;
        g->mHp = msg->hp;
        g->setMP(msg->mp);
        g->mGhostGender = msg->gender;
        g->mGhostJob = msg->staticid;
        g->mStaticID = msg->staticid;
        g->mName = msg->name;
        g->mLevel = msg->level;
        g->mReborn = msg->reborn;
        
        pGhostManager->addGhost(g);
        
        // 触发外观更新事件
        EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_AVATAR_CHANGE);
    }
}

void MsgMaster::HandleMessageMapMeetMonsterNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMapMeetMonsterNotify, pMsg);
	
	if(GameData::s_game_state != GAME_STATE_RUNNING)
	{
		return;
	}

	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	AliveGhost* g = new AliveGhost;
	if(g)
	{
		int plantFlag = 0;
		StaticData::getMonsterPlantFlag(msg->staticid, plantFlag);
		if (plantFlag == 0)
		{
			g->mType = GHOST_TYPE_MONSTER;
		}
		else
		{
			g->mType = GHOST_TYPE_PLANT;
		}
		g->mID = msg->eid;
		g->mTx = msg->posx;
		g->mTy = msg->posy;
		g->setDirection(msg->dir);
		g->mHp = msg->hp;
		g->mMaxHp = msg->maxhp;
		g->mStaticID = msg->staticid;
		LuaData::getProp(LuaData::MONSTER,msg->staticid,"name", g->mName);
		LuaData::getProp(LuaData::MONSTER,msg->staticid,"lvl", g->mLevel);
		g->setDress(AVATAR_TYPE_CLOTH, msg->staticid);
		pGhostManager->addGhost(g);
		if (g->mType == GHOST_TYPE_MONSTER)
		{
			float scale = 1;
			StaticData::getMonsterScale(msg->staticid, scale);
			if (scale > 0)
			{
				CCSprite *body = g->getBodySprite();
				if (body)
				{
					body->setScale(scale);
				}
			}
		}
	}
}

static bool getNPCClothIDAndName( int npcID, int &clothID, std::string &name )
{
	clothID = npcID;
	LuaData::getProp(LuaData::NPC, npcID, "name", name);

	// 全服第一
	int testJob = 0, testGender = 0;
	StaticData::getFirstRankJobTest(npcID, testJob, testGender);
	if (testJob == Entity::etj_zs)
	{
		const int pid1 = ActivityData::getWorldIntProp(WorldDefination::prop_first_zs_data, WorldDefination::firstplayer_pid);
		if (pid1 > 0)
		{
			const int gender = ActivityData::getWorldIntProp(WorldDefination::prop_first_zs_data, WorldDefination::firstplayer_gender);
			if (testGender == gender)
			{
				name += "(";
				name += ActivityData::getWorldStringProp(WorldDefination::prop_first_zs_data, WorldDefination::firstplayer_name);
				name += ")";
				return true;
			}
		}

		const int pid2 = ActivityData::getWorldIntProp(WorldDefination::prop_first_other_zs_data, WorldDefination::firstplayer_pid);
		if (pid2 > 0)
		{
			const int gender = ActivityData::getWorldIntProp(WorldDefination::prop_first_other_zs_data, WorldDefination::firstplayer_gender);
			if (testGender == gender)
			{
				name += "(";
				name += ActivityData::getWorldStringProp(WorldDefination::prop_first_other_zs_data, WorldDefination::firstplayer_name);
				name += ")";
				return true;
			}
		}
		return false;
	}
	else if (testJob == Entity::etj_fs)
	{
		const int pid1 = ActivityData::getWorldIntProp(WorldDefination::prop_first_fs_data, WorldDefination::firstplayer_pid);
		if (pid1 > 0)
		{
			const int gender = ActivityData::getWorldIntProp(WorldDefination::prop_first_fs_data, WorldDefination::firstplayer_gender);
			if (gender == testGender)
			{
				name += "(";
				name += ActivityData::getWorldStringProp(WorldDefination::prop_first_fs_data, WorldDefination::firstplayer_name);
				name += ")";
				return true;
			}
		}

		const int pid2 = ActivityData::getWorldIntProp(WorldDefination::prop_first_other_fs_data, WorldDefination::firstplayer_pid);
		if (pid2 > 0)
		{
			const int gender = ActivityData::getWorldIntProp(WorldDefination::prop_first_other_fs_data, WorldDefination::firstplayer_gender);
			if (gender == testGender)
			{
				name += "(";
				name += ActivityData::getWorldStringProp(WorldDefination::prop_first_other_fs_data, WorldDefination::firstplayer_name);
				name += ")";
				return true;
			}
		}
		return false;
	}
	else if (testJob == Entity::etj_ds)
	{
		const int pid1 = ActivityData::getWorldIntProp(WorldDefination::prop_first_ds_data, WorldDefination::firstplayer_pid);
		if (pid1 > 0)
		{
			const int gender = ActivityData::getWorldIntProp(WorldDefination::prop_first_ds_data, WorldDefination::firstplayer_gender);
			if (gender == testGender)
			{
				name += "(";
				name += ActivityData::getWorldStringProp(WorldDefination::prop_first_ds_data, WorldDefination::firstplayer_name);
				name += ")";
				return true;
			}
		}

		const int pid2 = ActivityData::getWorldIntProp(WorldDefination::prop_first_other_ds_data, WorldDefination::firstplayer_pid);
		if (pid2 > 0)
		{
			const int gender = ActivityData::getWorldIntProp(WorldDefination::prop_first_other_ds_data, WorldDefination::firstplayer_gender);
			if (gender == testGender)
			{
				name += "(";
				name += ActivityData::getWorldStringProp(WorldDefination::prop_first_other_ds_data, WorldDefination::firstplayer_name);
				name += ")";
				return true;
			}
		}
		return false;
	}

	// 城主
	int cityMasterFlag = 0;
	StaticData::getCityMasterFlag(npcID, cityMasterFlag);
	if (cityMasterFlag != 0)
	{
		if (ActivityData::getWorldIntProp(WorldDefination::city_master_player, WorldDefination::city_master_pid) > 0)
		{
			const int job = ActivityData::getWorldIntProp(WorldDefination::city_master_player, WorldDefination::city_master_job);
			const int gender = ActivityData::getWorldIntProp(WorldDefination::city_master_player, WorldDefination::city_master_gender);
			StaticData::getCityMasterCloth(job, gender, clothID);
			name += "(";
			name += ActivityData::getWorldStringProp(WorldDefination::city_master_player, WorldDefination::city_master_name);
			name += ")";
		}
		else
		{
			StaticData::getCityMasterCloth(Entity::etj_zs, Entity::etgd_male, clothID);
		}
	}
	return true;
}
void MsgMaster::HandleMessageMapMeetNPCNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMapMeetNPCNotify, pMsg);

	CCLog(">>>>>>add ghost npc id = %d",msg->eid);
	if(GameData::s_game_state!=GAME_STATE_RUNNING)
	{
		return;
	}

	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	int clothID = 0;
	std::string name;
	if (!getNPCClothIDAndName(msg->staticid, clothID, name))
	{
		return;
	}
	
	if (clothID <= 0)
	{
		clothID = msg->staticid;
	}

	AliveGhost* g = new AliveGhost;
	if(g)
	{
		g->mID = msg->eid;
		g->mType = GHOST_TYPE_NPC;
		g->mTx = msg->posx;
		g->mTy = msg->posy;
		g->mStaticID = msg->staticid;
		g->setDress(AVATAR_TYPE_CLOTH, clothID);
		g->mName = name;
		LuaData::getProp(LuaData::NPC,msg->staticid, "lvl", g->mLevel);
		pGhostManager->addGhost(g);
	}
}

void MsgMaster::HandleMessageMapMeetItemNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMapMeetItemNotify, pMsg);

	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	ItemGhost* g = new ItemGhost;
	if (g)
	{
		g->mStaticID = msg->staticid;
		g->mID = msg->eid;
		g->mTx = msg->posx;
		g->mTy = msg->posy;
		g->mType = GHOST_TYPE_MAP_ITEM;
		g->mCount = msg->count;
		pGhostManager->addGhost(g);
	}
}

void MsgMaster::HandleMessageMapMeetDogNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMapMeetDogNotify, pMsg);
	
	CCLog(">>>>>>add dog id = %d",msg->eid);
	if(GameData::s_game_state != GAME_STATE_RUNNING)
	{
		return;
	}

	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	AliveGhost *g = new AliveGhost;
	g->mID = msg->eid;
	g->mType = GHOST_TYPE_SLAVE;
	g->mTx = msg->posx;
	g->mTy = msg->posy;
	g->setDirection(msg->dir);
	g->mHp = msg->hp;
	g->mMaxHp = msg->maxhp;
	g->mLevel = msg->level;
	g->mDogSid = msg->did;
	g->setDirection(msg->dir);
	g->setDress(AVATAR_TYPE_CLOTH, msg->did);
	g->setOwnerInfo(msg->ownerpid, msg->ownername);
	pGhostManager->addGhost(g);
}


void MsgMaster::HandleMessageMapMeetPetNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMapMeetPetNotify, pMsg);

	CCLog(">>>>>>add pet id = %d",msg->eid);
	if(GameData::s_game_state!=GAME_STATE_RUNNING)
	{
		return;
	}

	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	AliveGhost* g = new AliveGhost;
	if(g)
	{
		g->mID = msg->eid;
		g->mType = GHOST_TYPE_PET;
		g->mTx = msg->posx;
		g->mTy = msg->posy;
		g->setDirection(msg->dir);
		g->mHp = msg->hp;
		g->mMaxHp = msg->maxhp;
		int level = msg->level;
		g->mLevel = level & 0x00FF;//hou 8 wei biao shi chong wu deng ji
		g->mPetReborn = (level & 0xFF00) >> 8;//qian 8 wei biao shi chong wu zhuan sheng deng ji
		g->setDirection(msg->dir);
		g->mName = msg->ownername + SystemData::getLayoutString("role.string.whosepet");
		g->setDress(AVATAR_TYPE_CLOTH, msg->staticid);
		g->setOwnerInfo(msg->ownerpid, msg->ownername);
		pGhostManager->addGhost(g);
	}
}

void MsgMaster::HandleMessageMapMeetMarketNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMapMeetMarketNotify, pMsg);

	CCLog(">>>>>>add pet id = %d",msg->eid);
	if(GameData::s_game_state!=GAME_STATE_RUNNING)
	{
		return;
	}

	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	ItemGhost *g = new ItemGhost;
	if(g)
	{
		g->mID = msg->eid;
		g->mType = GHOST_TYPE_COLLECTION;
		g->mTx = msg->posx;
		g->mTy = msg->posy;
		g->mStaticID = msg->pid;
		g->mName = msg->ad;
		g->setOwnerInfo(msg->pid, msg->name);
		pGhostManager->addGhost(g);
	}
}

void MsgMaster::HandleMessageMapMeetSkillNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMapMeetSkillNotify, pMsg);

	CCLog(">>>>>>add skill id = %d",msg->eid);
	if(GameData::s_game_state!=GAME_STATE_RUNNING)
	{
		return;
	}
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;
	ItemGhost* g = NULL;
	g = new ItemGhost;
	if (g)
	{
		g->mStaticID = msg->staticid;
		g->mID = msg->eid;
		g->mTx = msg->posx;
		g->mTy = msg->posy;
		g->mType = GHOST_TYPE_SKILL;
		pGhostManager->addGhost(g);
	}
}

void MsgMaster::HandleMessageEntityEffectNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgEntityEffectNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	AliveGhost *ghost = dynamic_cast<AliveGhost *>(pGhostManager->getGhostById(msg->eid));
	if(ghost)
	{
		ghost->setExData(Entity::attr_effect_data, msg->effect);
	}
}

void MsgMaster::HandleMessageSyncEntityLevelupNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncEntityLevelupNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	AliveGhost *ghost = dynamic_cast<AliveGhost *>(pGhostManager->getGhostById(msg->eid));
	if(ghost)
	{
		SkillEffect *skill = ghost->m_skill;
		if (skill)
		{
			skill->runSkill(SKILL_TYPE_LevelUp * 10, ghost->mTx, ghost->mTy, NULL);
		}
		ghost->mLevel = msg->lvl;
		ghost->mMaxHp = msg->maxhp;
		ghost->mMaxMp = msg->maxmp;
		ghost->mHp = msg->hp;
		ghost->setMP(msg->mp);
		ghost->delayHpChange(msg->hp, 0);
		if (ghost->mType == GHOST_TYPE_SLAVE
			|| ghost->mType == GHOST_TYPE_PET)
		{
			ghost->refreshNameLabel(true);
		}
	}

	CPEventHelper::msgNotify("HandleMessageSyncEntityLevelupNotify", "", 0, msg->eid, 0, 0);
}

void MsgMaster::HandleSyncEntityRideStateNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncEntityRideStateNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	AliveGhost *ghost = dynamic_cast<AliveGhost *>(pGhostManager->getGhostById(msg->EntityID));
	if(ghost)
	{
		ghost->setExData(Entity::attr_horse_ride_state, msg->RideState);
		ghost->setExData(Entity::attr_horse_level, msg->HorseLevel);
	}

	if (ghost->mType == GHOST_TYPE_THIS)
	{
		HeroData::setProp(Entity::attr_horse_ride_state, msg->RideState);
	}

	CPEventHelper::msgNotify("HandleSyncEntityRideStateNotify", "", 0, 0, 0, 0);
}

void MsgMaster::HandleMessageEntityUseSkillNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgEntityUseSkillNotify, pMsg);

	if(GameData::s_game_state != GAME_STATE_RUNNING)
	{
		return;
	}
	GameRole* myRole = GameData::getMyRole();
	if (!myRole) return;
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	if (msg->eidSrc == myRole->mID)
	{
		return;
	}

	AliveGhost* pGhost = dynamic_cast<AliveGhost*>(pGhostManager->getGhostById(msg->eidSrc));
	if(pGhost)
	{
		StateInfo info;
		const int &typeEnum = msg->skillid/10;
		if (typeEnum == SKILL_TYPE_YiBanGongJi ||
			typeEnum == SKILL_TYPE_WaKuang ||
			(SKILL_TYPE_JiChuJianShu <= typeEnum && typeEnum < SKILL_TYPE_HuoQiang) ||
			pGhost->mType == GHOST_TYPE_MONSTER)
		{
			info.state = AVATAR_ACTION_ATTACK;
		}
		else
		{
			info.state = AVATAR_ACTION_MAGIC;
		}
		info.pid = msg->eidTgt;
		info.skilltype = msg->skillid;
		pGhost->setState(info);
	}
}

void MsgMaster::HandleMessageEntityBeUsedSkillNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgEntityBeUsedSkillNotify, pMsg);

	if(GameData::s_game_state != GAME_STATE_RUNNING)
	{
		return;
	}

	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	AliveGhost *pGhost = dynamic_cast<AliveGhost*>(pGhostManager->getGhostById(msg->eidTgt));
	if(pGhost)
	{
		pGhost->playEffect(msg->skillid, msg->issrc);
	}
}

void MsgMaster::HandleMessageEntityHpChangeNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgEntityHpChangeNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;
	AliveGhost* pGhost = dynamic_cast<AliveGhost*>(pGhostManager->getGhostById(msg->eid));
	if(pGhost)
	{
		pGhost->delayHpChange(msg->hp, 3);
	}

	CPEventHelper::msgNotify("HandleMessageEntityHpChangeNotify", "", 0, msg->eid, 0, 0); 
}

void MsgMaster::HandleMessageEntityMaxHPChangeNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgEntityMaxHPChangeNotify, pMsg);

	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	AliveGhost* pGhost = dynamic_cast<AliveGhost*>(pGhostManager->getGhostById(msg->eid));
	if(pGhost)
	{
		pGhost->mHp = msg->hp;
		pGhost->mMaxHp = msg->maxhp;
	}
	CPEventHelper::msgNotify("HandleMessageEntityMaxHPChangeNotify", "", 0, msg->eid, msg->hp, msg->maxhp);
}

void MsgMaster::HandleMessageEntityHpChangeDelayNotify( IMsg* pMsg )
{
	CP_TEST_NULL_MSG(MsgEntityHpChangeDelayNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;
	AliveGhost* pGhost = dynamic_cast<AliveGhost*>(pGhostManager->getGhostById(msg->eid));
	if(pGhost)
	{
		pGhost->delayHpChange(msg->hp,msg->delay);
	}

	CPEventHelper::msgNotify("HandleMessageEntityHpChangeDelayNotify", "", 0, msg->eid, 0, 0);
}

void MsgMaster::HandleMessageEntityBeAttackedDelayNotify( IMsg* pMsg )
{
	CP_TEST_NULL_MSG(MsgEntityBeAttackedDelayNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;
	AliveGhost* pGhost = dynamic_cast<AliveGhost*>(pGhostManager->getGhostById(msg->eid));
	if(pGhost)
	{
		pGhost->delayBeAttack(msg->type, msg->delay);
	}
}

void MsgMaster::HandleMessageImBeAttackedDelayNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgImBeAttackedDelayNotify, pMsg);

	CPEventHelper::msgNotify("HandleMessageImBeAttackedDelayNotify", "", 0, msg->eid, 0, 0);
}

void MsgMaster::HandleMessageEntityMpChangeNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgEntityMpChangeNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;
	AliveGhost* pGhost = dynamic_cast<AliveGhost*>(pGhostManager->getGhostById(msg->eid));
	if(pGhost)
	{
		pGhost->setMP(msg->mp);
	}
	CPEventHelper::msgNotify("HandleMessageEntityMpChangeNotify", "", 0, msg->eid, 0, 0);
}
//这是一个典型的网络消息处理函数，
//实现了MVC模式中的控制器功能，
//	处理网络消息并更新模型（幽灵装备状态）
//，然后通知视图更新显示。
void MsgMaster::HandleMessageEntityEquipChangeNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgEntityEquipChangeNotify, pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;
	AliveGhost* pGhost = dynamic_cast<AliveGhost*>(pGhostManager->getGhostById(msg->eid));
	if(pGhost)
	{
		int itemSid = 0;
		if(msg->status == 1)
		{
			itemSid = msg->sid;
		}

		switch(msg->type)
		{
		case ItemType_Equip_Cloth:
			if(itemSid == 0)
			{
				itemSid = -1;
			}
			pGhost->setDress(AVATAR_TYPE_CLOTH, itemSid);
			break;
		case ItemType_Equip_Weapon:
			pGhost->setDress(AVATAR_TYPE_WEAPON, itemSid);
			break;
		case ItemType_Equip_Wings:
			pGhost->setDress(AVATAR_TYPE_WINGS, itemSid);
			break;
		case ItemType_Equip_Yuanshen:
			pGhost->setDress(AVATAR_TYPE_YUANSHEN, itemSid);//元神外观刷新
			break;
		}
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_AVATAR_CHANGE);
	}
}

void MsgMaster::HandleMessageFetchItemResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgFetchItemResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageFetchItemResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageAbandonItemResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAbandonItemResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageAbandonItemResponse", "", msg->errcode);
	if (msg->errcode == Error::Success)
	{
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
	}
}

void MsgMaster::HandleMessagePickPlantResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgPickPlantResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessagePickPlantResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageMapSelfEnterNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMapSelfEnterNotify, pMsg);

	CCLog(">>>map self enter notify:");

	GameRole* myRole = GameData::getMyRole();
	if (myRole)
	{
		myRole->mID = msg->eid;
		myRole->mTx = msg->posx;
		myRole->mTy = msg->posy;
		myRole->setDirection(msg->dir);
		myRole->m_serverTx = msg->posx;
		myRole->m_serverTy = msg->posy;
		myRole->m_serverDir = msg->dir;
		myRole->m_state = AVATAR_ACTION_IDLE;
	}
	NetMap* map = GameData::getCurrentMap();
	if (!map) return;
	map->mID = msg->sceneid;
	LuaData::getProp(LuaData::MAP, msg->sceneid,"resource", GameData::getCurrentMap()->mMapFile);
	LuaData::getProp(LuaData::MAP, msg->sceneid,"name", GameData::getCurrentMap()->mName);
	
	CCLog(">>>map id = %d, map name = %s", msg->sceneid, map->mName.c_str());
	CPPlatform->operate(PlatformOpID::enterScene);

	if (AutoAttack::checkAutoAttack() && map->mID != 1003)
	{
		AutoAttack::closeAutoAttack();
	}

	GameData::s_user->switch2GameScene();
	CPEventHelper::msgNotify("HandleMessageMapSelfEnterNotify", "");
}

void MsgMaster::HandleMessageMapSelfLeaveNotify( IMsg* pMsg )
{
	CP_TEST_NULL_MSG(MsgMapSelfLeaveNotify, pMsg);

	//clear the resource for the transfer
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (pGhostManager)
	{
		pGhostManager->release();
	}
	CPEventHelper::msgNotify("HandleMessageMapSelfLeaveNotify", "", 0, 0, 0, 0);
}

void MsgMaster::HandleMessageSceneMonstersCleanNotify(IMsg* pMsg)
{
	CP_TEST_NULL_MSG(MsgSyncSceneMonstersCleanNotify, pMsg);

	GameRole *myRole = GameData::getMyRole();
	if (myRole)
	{
		myRole->onSceneMonstersClean(msg->sid);
	}
}

void MsgMaster::HandleMessageMapSelfEnterVirtalSceneNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMapSelfEnterVirtalSceneNotify, pMsg);

	GameRole *myRole = GameData::getMyRole();
	if (myRole)
	{
		myRole->mID = msg->eid;
		myRole->setDirection(msg->dir);
		myRole->mTx = msg->posx;
		myRole->mTy = msg->posy;
		GameData::s_user->mMap.mID = msg->sceneid;
	}
	CPEventHelper::msgNotify("HandleMessageMapSelfEnterVirtalSceneNotify", "");
}

void MsgMaster::HandleMessageEntityTurnNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgEntityTurnNotify, pMsg);
	GameRole* myRole = GameData::getMyRole();
	if (!myRole) return;
	if (msg->eid == myRole->mID)
	{
		return;
	}

	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;

	AliveGhost* pGhost = dynamic_cast<AliveGhost*>(pGhostManager->getGhostById(msg->eid));
	if(pGhost)
	{
		pGhost->setDirection(msg->dir);
	}
}

void MsgMaster::HandleMessageEntityPlayerInfoNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgEntityPlayerInfoNotify, pMsg);

	PlayerInfoData::_target_player_info.eid = msg->eid;
	PlayerInfoData::_target_player_info.pid = msg->pid;
	PlayerInfoData::_target_player_info.name = msg->name;
	PlayerInfoData::_target_player_info.hp = msg->hp;
	PlayerInfoData::_target_player_info.mp = msg->mp;
	PlayerInfoData::_target_player_info.maxhp = msg->maxhp;
	PlayerInfoData::_target_player_info.maxmp = msg->maxmp;
	PlayerInfoData::_target_player_info.lvl = msg->lvl;
	PlayerInfoData::_target_player_info.staticid = msg->staticid;
	PlayerInfoData::_target_player_info.gender = msg->gender;
	///TODO: dispatch an event notify the UI level the info

	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PLAYER_CLICK);
}

void MsgMaster::HandleMessageUpdScenePropsNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgUpdScenePropsNotify,pMsg);
	SceneData::setProp(msg->prop, msg->data);
	CPEventHelper::msgNotify("HandleMessageUpdScenePropsNotify", "", 0, 0, 0, 0);
}

void MsgMaster::HandleMessageUpdSceneStringNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgUpdSceneStringNotify, pMsg);
	SceneData::setStringProp(msg->nidx, msg->str);
	CPEventHelper::msgNotify("HandleMessageUpdSceneStringNotify", "", 0, 0, 0, 0);
}

void MsgMaster::HandleMessageSyncEntitySpeedNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgsyncEntitySpeedNotify,pMsg);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (!pGhostManager) return;
	AliveGhost* pGhost = dynamic_cast<AliveGhost*>(pGhostManager->getGhostById(msg->eid));
	if(pGhost)
	{
		pGhost->setExData(Entity::attr_move_speed, msg->speed);
	}
}

void MsgMaster::HandleMessagePlayerMineonPosResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgPlayerMineonPosResponse,pMsg);
	GameRole* myRole = GameData::getMyRole();
	if (!myRole) return;
	if (msg->errcode == Error::Success)
	{
		myRole->setState(AVATAR_ACTION_MINE);
		CPEventHelper::setEventIntData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2, msg->mineid);
		CPEventHelper::uiNotify("UINotifyPlayerMine","",0);
	}
	else
	{
		myRole->setState(AVATAR_ACTION_IDLE);
		CPEventHelper::msgResponse("HandleMessagePlayerMineonPosResponse","",msg->errcode); 
	}
}
