#include "MsgMaster.h"
#include "ActivityDefinition.h"
#include "EntityDefinition.h"
#include "EvtDataDefinition.h"
#include "ActivityModule.h"

#include "userdata/activitydata/WorshipData.h"
#include "userdata/activitydata/EmigratedData.h"
#include "userdata/ActivityData.h"
#include "userdata/activitydata/TreasureHuntData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/UserItemData.h"
#include "userdata/HeroData.h"

#include "event/EventDispatcher.h"
#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"
#include "userdata/IconTipsData.h"



void MsgMaster::HandleMessageSyncNotImportantActivityNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncNotImportantActivityNotify, pMsg);
	IconTipsData::m_iDoingEventid=msg->noweventid;
	IconTipsData::m_iOverEventid=msg->endeventid;
	IconTipsData::m_iWillEventid=msg->fureventid;
}

void MsgMaster::HandleMessageMobaiDataResponse( IMsg *pMsg )
{
	MsgMobaiDataResponse* msg = dynamic_cast<MsgMobaiDataResponse*>(pMsg);
	if(!msg)return;
	if (msg->errcode == Error::Success)
	{
		Worshipdata::s_experience = msg->data[Activity::Mobai_baseexp];
		Worshipdata::s_is_double = msg->data[Activity::Mobai_isdouble];
		Worshipdata::s_max_refresh_count = msg->data[Activity::Mobai_maxrefresh];
		Worshipdata::s_max_worship_count = msg->data[Activity::Mobai_maxmobaicnt];
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_UPDATE_WOSHIP_DATA);
	CPEventHelper::msgResponse("HandleMessageMobaiDataResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageUpdMyMobaiDataNotify( IMsg *pMsg )
{
	MsgUpdMyMobaiDataNotify* msg = dynamic_cast<MsgUpdMyMobaiDataNotify*>(pMsg);
	if(!msg)return;
	switch (msg->type)
	{
	case Activity::Mobai_baseexp:
		Worshipdata::s_experience = msg->data;
		break;
	case Activity::Mobai_isdouble:
		Worshipdata::s_is_double = msg->data;
		break;
	case Activity::Mobai_maxmobaicnt:
		Worshipdata::s_max_worship_count = msg->data;
		break;
	case Activity::Mobai_maxrefresh:
		Worshipdata::s_max_refresh_count = msg->data;
		break;
	case Activity::Mobai_maxaddmobaicnt:
		Worshipdata::s_max_add_count = msg->data;
		break;
	default:
		break;
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_UPDATE_WOSHIP_DATA);
}

void MsgMaster::HandleMessageRefreshMobaiPerResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgRefreshMobaiPerResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageRefreshMobaiPerResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageMobaiBishiResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMobaiBishiResponse, pMsg);
	CPEventHelper::msgResponse("HandleMsgMobaiBishiResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageAddMobaiCntResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAddMobaiCntResponse, pMsg);
	CPEventHelper::msgResponse("HandleMsgAddMobaiCntResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageSyncEventStateNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncEventStateNotify, pMsg);

	for (int i = 0; i < msg->unstarttimeid; i++)
	{
		const int &state = ActivityData::getState(i + 1);
		if (state != Activity::Activity_Begin)
		{
			ActivityData::setState(i + 1, Activity::Activity_End);
		}
	}
	ActivityData::setState(msg->eventtimeid, msg->eventstate);
	ActivityData::setUnstartID(msg->unstarttimeid);
 	CPEventHelper::msgNotify("HandleMessageSyncEventStateNotify", "");
}

void MsgMaster::HandleMessageSyncEventNotFinishCountNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncEventNotFinishCountNotify, pMsg);

	ActivityData::setNotFinishCnt(msg->eventid, msg->count);
	CPEventHelper::msgNotify("HandleMessageSyncEventNotFinishCountNotify", "", 0, msg->eventid, msg->count, 0);
}

void MsgMaster::HandleMessageSyncActivityBossStateNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncActivityBossStateNotify, pMsg);

	msg->ActOrBoss;
	msg->sid;
	msg->state;
	msg->statetime;
	
	if((msg->state==Activity::AoB_will_begin || msg->state==Activity::AoB_has_began) && msg->ActOrBoss==Activity::AoB_Activity)
	{
		if (msg->state==Activity::AoB_will_begin)
		{
			IconTipsData::m_iWillEventid=msg->sid;
		}
		else if (msg->state==Activity::AoB_has_began)
		{
			if (IconTipsData::m_iWillEventid == msg->sid)
			{
				IconTipsData::m_iWillEventid = 0;
			}
			IconTipsData::m_iDoingEventid=msg->sid;
		}
	}
	else if (msg->state==Activity::AoB_is_end && msg->ActOrBoss==Activity::AoB_Activity)
	{
		if (IconTipsData::m_iDoingEventid == msg->sid)
		{
			IconTipsData::m_iDoingEventid = 0;
		}
		IconTipsData::m_iOverEventid=msg->sid;
	}

	CPEventHelper::msgNotify("HandleMessageSyncActivityBossStateNotify", "", Opcode::Op_ActivityStateChange, msg->ActOrBoss, msg->sid, msg->state);
}

void MsgMaster::HandleMessageCaiShenChuangGuanMissionUp( IMsg *pMsg )
{
	MsgCaiShenChuangGuanMissionUpNotify* msg=dynamic_cast<MsgCaiShenChuangGuanMissionUpNotify *>(pMsg);
	if (!msg)
	{
		return;
	}
	int cnt = 0, k = 0,v = 0;
	ActivityData::getExData(EvtData::evt_cscg,cnt,k,v);
	ActivityData::setExData(EvtData::evt_cscg,cnt,k,msg->pos);
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_UPDATE_EMIGRATED_MISSIONUP);
}

void MsgMaster::HandleMessageCaiShenChuangGuanfreshtimeResponse( IMsg *pMsg )
{
	MsgCaiShenChuangGuanfreshtimeResponse* msg=dynamic_cast<MsgCaiShenChuangGuanfreshtimeResponse *>(pMsg);
	if (!msg)
	{
		return;
	}

	CPEventHelper::msgResponse("MsgCaiShenChuangGuanfreshtimeResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageUpdCaiShenChuangGuanDataNotify( IMsg *pMsg )
{
	MsgUpdCaiShenChuangGuanDataNotify* msg=dynamic_cast<MsgUpdCaiShenChuangGuanDataNotify *>(pMsg);
	if (!msg)
	{
		return;
	}
}

void MsgMaster::HandleMessageCaiShenChuangGuanRestartResponse( IMsg *pMsg )
{
	MsgCaiShenChuangGuanReStartResponse* msg=dynamic_cast<MsgCaiShenChuangGuanReStartResponse *>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgResponse("HandleMessageCaiShenChuangGuanRestartResponse", "", msg->errorcode);
}

void MsgMaster::HandleMessageCaiShenChuangGuanDataResponse( IMsg *pMsg )
{
	MsgCaiShenChuangGuanDataResponse* msg=dynamic_cast<MsgCaiShenChuangGuanDataResponse *>(pMsg);
	if (!msg)
	{
		return;
	}
	Emigrateddata::cscg_list.clear();
	std::vector<int>::iterator it=msg->data.begin();
	for (it;it!=msg->data.end();it++)
	{
		Emigrateddata::cscg_list.push_back(*it);
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_UPDATE_EMIGRATED_DATALIST);
}

void MsgMaster::HandleMessageCaiShenChuangGuanCaseOver( IMsg *pMsg )
{
	MsgCaiShenChuangGuanCaseOverResponse* msg=dynamic_cast<MsgCaiShenChuangGuanCaseOverResponse *>(pMsg);
	if (!msg)
	{
		return;
	}

	if (msg->type!=0)
	{
		CPEventHelper::msgNotify("", "", msg->opcode,msg->type,0,0);
		stepcase icase;
		icase.type=msg->type;
		icase.data=msg->data;
		Emigrateddata::cscg_caselist.push_back(icase);
	}
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_UPDATE_EMIGRATED_ROUNDOVER);
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_UPDATE_EMIGRATED_DATALIST);
}

void MsgMaster::HandleMessageCaiShenChuangGuanMeetCaseResponse( IMsg *pMsg )
{
	MsgCaiShenChuangGuanMeetCaseResponse* msg=dynamic_cast<MsgCaiShenChuangGuanMeetCaseResponse *>(pMsg);
	if (!msg)
	{
		return;
	}
	/*stepcase icase;
	icase.type=msg->casetype;
	icase.data=msg->casedata;
	Emigrateddata::cscg_caselist.push_back(icase);
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_UPDATE_EMIGRATED_CASEMEET);*/
}

void MsgMaster::HandleMessageUpdMeiNvHuSongDataNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgUpdMeiNvHuSongDataNotify, pMsg);
	ActivityData::setMeiNvHuSongData(msg->type, msg->data);
	CPEventHelper::msgNotify("HandleMessageUpdMeiNvHuSongDataNotify", "");
}

void MsgMaster::HandleMessageMeiNvHuSongEnterResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMeiNvHuSongEnterResponse, pMsg);
	for (int i = 0; i < (int)msg->datalist.size(); i++)
	{
		ActivityData::setMeiNvHuSongData(i, msg->datalist[i]);
	}
	CPEventHelper::msgResponse("HandleMessageMeiNvHuSongEnterResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageMeiNvHuSongStartResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMeiNvHuSongStartResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageMeiNvHuSongStartResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageMeiNvHuSongRefreshResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgMeiNvHuSongRefreshResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageMeiNvHuSongRefreshResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageListTreasureResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgListTreasureResponse, pMsg);
	TreasureHuntData::_s_treasure_hunt_list = msg->TreasureList;	
	//send event to UI to update the treasure list
	GameData::s_user->getUserItemData()->treasureDepotCapacity = msg->depotCapacity;
	GameData::s_user->getUserItemData()->treasureDepotCapacityMax = msg->depotCapacityMax;
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_UPDATE_TREASURE_LIST);
}

void MsgMaster::HandleMessageHuntTreasureResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgHuntTreasureResponse, pMsg);
	GameData::s_user->getUserItemData()->treasureDepotCapacity = msg->depotCapacity;
	GameData::s_user->getUserItemData()->treasureDepotCapacityMax = msg->depotCapacityMax;
	CPEventHelper::msgResponse("HandleMessageHuntTreasureResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGetHuntTreasureRewardResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGetHuntTreasureRewardResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageGetHuntTreasureRewardResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageSyncTreasureHuntRecordNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncTreasureHuntRecordNotify, pMsg);

	for (int i = 0; i < (int)msg->records.size(); i++)
	{
		const TreasureHuntRecord &record = msg->records[i];
		ActivityData::setTreasureRecord(i, (msg->isworlddata == 0), record.name, record.sid, record.strong, record.reborn);
	}

	if (msg->isworlddata)
	{
		CPEventHelper::msgNotify("HandleMessageSyncTreasureHuntRecordNotify|All", "");
	}
	else
	{
		CPEventHelper::msgNotify("HandleMessageSyncTreasureHuntRecordNotify|My", "");
	}
}

void MsgMaster::HandleMessageSpiderThorwItemResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSpiderThorwItemResponse, pMsg);

	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SPIDER_ITEM_OVER);
	CPEventHelper::msgResponse("HandleMessageSpiderThorwItemResponse", "", msg->errcode); 
}

void MsgMaster::HandleMessageOpenArenaResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgOpenArenaResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageOpenArenaResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageArenaListNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgArenaListNotify, pMsg);
	ActivityData::clearArenaCompetitorList();
	for (int i = 0; i < (int)msg->arenalist.size(); i++)
	{
		const ArenaData &data = msg->arenalist[i];
		ActivityData::setArenaCompetitor(data.rank, data.pid, data.lvl, data.name, data.reborn, data.job, data.gender, data.cloth, data.weapon, data.wing, data.guildname);
	}
	HeroData::setProp(Entity::attr_arena_rank, msg->rank);
	HeroData::setProp(Entity::attr_arena_wincount, msg->win);
	HeroData::setProp(Entity::attr_arena_buff, msg->buff);
	CPEventHelper::msgNotify("HandleMessageArenaListNotify", "");
}

void MsgMaster::HandleMessageRefreshArenaBuffResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgRefreshArenaBuffResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageRefreshArenaBuffResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageArenaFightResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgArenaFightResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageArenaFightResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageArenaFightNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgArenaFightNotify, pMsg);

	ActivityData::clearArenaFightBegin();
	for (int i = 0; i < (int)msg->begindata.size(); i++)
	{
		const ArenaBeginData &data = msg->begindata[i];
		ActivityData::setArenaFightBegin(data.id, data.lvl, data.name, data.reborn, data.job, data.gender, data.cloth, data.weapon, data.wing, data.maxhp);
	}

	ActivityData::clearArenaFightData();
	for (int i = 0; i < (int)msg->fightdata.size(); i++)
	{
		const ArenaFightData &data = msg->fightdata[i];
		ActivityData::setArenaFightData(i, data.id, data.damage);
	}
	ActivityData::setArenaWinner(msg->winner);
	CPEventHelper::msgNotify("HandleMessageArenaFightNotify", "");
}

void MsgMaster::HandleMessageBuyArenaFightCntResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgBuyArenaFightCntResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageBuyArenaFightCntResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGetPlayerArenaFightRecordResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGetPlayerArenaFightRecordResponse, pMsg);

	ActivityData::clearArenaRecord();
	for (int i = 0; i < (int)msg->records.size(); i++)
	{
		const ArenaFightRecord &record = msg->records[i];
		ActivityData::setArenaRecord(i, record.name, record.ischallenger, record.iswin);
	}
	CPEventHelper::msgResponse("HandleMessageGetPlayerArenaFightRecordResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGetArenaHeroResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGetArenaHeroResponse, pMsg);

	if (msg->errcode == Error::Success)
	{
		ActivityData::clearArenaRank();
		for (int i = 0; i < (int)msg->heros.size(); i++)
		{
			const ArenaHero &data = msg->heros[i];
			ActivityData::setArenaRank(data.rank, data.pid, data.name, data.job, data.cbt);
		}
		CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_2, msg->page);
		CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_3, msg->maxpage);
	}
	CPEventHelper::msgResponse("HandleMessageGetArenaHeroResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGetInstanceCntResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGetInstanceCntResponse, pMsg);

	ActivityData::clearInstanceData();
	for (int i = 0; i < (int)msg->instance.size(); i++)
	{
		const InstanceData &data = msg->instance[i];
		ActivityData::setInstanceData(data.InstanceID, data.InstanceCnt);
		ActivityData::setInstanceAllCountData(data.InstanceID, data.InstanceAllCnt);
	}
	CPEventHelper::msgResponse("HandleMessageGetInstanceCntResponse", "", 0);
}

void MsgMaster::HandleMessageGetGiftByCodeResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGetGiftByCodeResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageGetGiftByCodeResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageHideActivityListNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgHideActivityListNotify, pMsg);

	ActivityData::setHideList(msg->hideList);
	CPEventHelper::msgNotify("HandleMessageHideActivityListNotify", "");
	CPEventHelper::dispatcher(CPEventName::UI_CHANGE,"HandleMessageHideActivityListNotify","TopActiviy");
}
