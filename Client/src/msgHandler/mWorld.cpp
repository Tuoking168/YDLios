#include "MsgMaster.h"
#include "CCCommon.h"
#include "EvtDataDefinition.h"
#include "ActivityDefinition.h"
#include "WorldDefinition.h"
#include "ErrorDefinition.h"
#include "ScriptPatchManager.h"

#include "scene/NotificationHelper.h"

#include "event/CPEventHelper.h"

#include "userdata/ActivityData.h"
#include "userdata/RankData.h"
#include "userdata/GameData.h"
#include "userdata/WorldData.h"


using namespace cocos2d;

void MsgMaster::HandleMessageWorldDataNotify( IMsg* pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncWorldDataNotify, pMsg);
	ActivityData::setWorldIntProp(msg->wid, 0, msg->datax);
	ActivityData::setWorldIntProp(msg->wid, 1, msg->datay);
	ActivityData::setWorldIntProp(msg->wid, 2, msg->dataz);
	ActivityData::setWorldStringProp(msg->wid, 0, msg->datas);

	switch (msg->wid)
	{
	case  EvtData::evt_qfs:
		ActivityData::setQiFuShuData(Activity::qfs_treeexp,msg->datax);
		ActivityData::setQiFuShuData(Activity::qfs_treelvl,msg->datay);
		ActivityData::setQiFuShuData(Activity::qfs_addexp,msg->dataz);
		break;
	case  EvtData::evt_zmjz:
		ActivityData::setZhuMoJieZhenData(Activity::zmjz_spidercnt,msg->datax);
		break;
	case EvtData::evt_gcz:
		ActivityData::setGCZData(Activity::GCZ_tmp_master_guild_id,msg->datax);
		ActivityData::setGCZData(Activity::GCZ_master_guild_id,msg->datay);
		ActivityData::setGCZData(Activity::GCZ_occupy_count,msg->dataz);
		ActivityData::setGCZMasterName(msg->datas);
		break;
	}
	CPEventHelper::msgNotify("HandleMessageWorldDataNotify", "", 0, msg->wid, 0, 0);
}

void MsgMaster::HandleMessageSyncWorldDataExNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncWorldDataExNotify, pMsg);
	
	typedef MsgSyncWorldDataExNotify::intList IntVect;
	typedef MsgSyncWorldDataExNotify::stringList StrVect;
	const IntVect &intVect = msg->data;
	for (int i = 0; i < (int)intVect.size(); i++)
	{
		ActivityData::setWorldIntProp(msg->wid, i, intVect[i]);
	}

	const StrVect &strVect = msg->str;
	for (int i = 0; i < (int)strVect.size(); i++)
	{
		ActivityData::setWorldStringProp(msg->wid, i, strVect[i]);
	}
	
	CPEventHelper::msgNotify("HandleMessageSyncWorldDataExNotify", "", 0, msg->wid, 0, 0);
}

void MsgMaster::HandleMessageSyncFloatNoticeNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncFloatNoticeNotify, pMsg);

	if(GameData::s_game_state != GAME_STATE_RUNNING)
	{
		return;
	}
	NotificationHelper::showTopNote(msg->basestring);
}

void MsgMaster::HandleMessageSyncWorldBossNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncWorldBossNotify, pMsg);

	for (int i = 0; i < (int)msg->Bosses.size(); i++)
	{
		const BossData &data = msg->Bosses[i];
		ActivityData::setWorldBossData(data.eventid, data.bossid, data.bossexp, data.bossstate, data.killpid, data.killname);
	}
	CPEventHelper::msgNotify("HandleMessageSyncWorldBossNotify", "");
}

void MsgMaster::HandleMessageSyncWorldBeginTimeNotify( IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgSyncWorldBeginTimeNotify, pMsg);

	ActivityData::setWorldBeginTime(msg->Begintime);
}


void MsgMaster::HandleMessageGetWorldChartResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGetWorldChartResponse, pMsg);
	
	CPEventHelper::dispatcher(CPEventName::UI_CHANGE,"CombinedRank","CombinedServerRankRightPanel");
	CPEventHelper::dispatcher(CPEventName::UI_CHANGE,"RankLeftPanel","RankRightPanel");
}

void MsgMaster::HandleMessageGetWorldChartNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGetWorldChartNotify, pMsg);
	int charttype = msg->charttype;

	if (msg->posttimes == 1)
	{
		RankData::clearList(charttype);
	}

	std::vector< ChartElem >& resList = msg->charts;
	int index = 1;

	if (charttype == WorldDefination::blob_combinedserver_chongzhi || charttype == WorldDefination::blob_combinedserver_xiaofei)
	{
		for (std::vector<ChartElem>::iterator it = resList.begin(); it != resList.end(); ++it)
		{
			Rank_combined r_cb;
			r_cb.rank = it->id;
			std::vector< ChartStrData >& chartStrList = it->strs;
			for (std::vector< ChartStrData >::iterator strit = chartStrList.begin();strit!=chartStrList.end();strit++)
			{				
				switch (strit->idx)
				{
				case WorldDefination::chart_combined_str_name:
					r_cb.name = strit->data;
					break;
				case WorldDefination::chart_combined_str_guildname:
					r_cb.guildname = strit->data;
					break;
				case WorldDefination::chart_combined_str_servername:
					r_cb.servername = strit->data;
					break;
				case WorldDefination::chart_combined_str_rechargeamount:
					r_cb.rechargeamount = strit->data;
					break;
				default:
					break;
				}
			}
			(charttype == WorldDefination::blob_combinedserver_chongzhi?RankData::m_rankCombined[r_cb.rank]:RankData::m_rankCombined2[r_cb.rank]) = r_cb;
		}
		RankData::setVersion(charttype,msg->version);

		if (msg->posttimes == 1)
		{
			CPEventHelper::dispatcher(CPEventName::UI_CHANGE,"CombinedRank","CombinedServerRankRightPanel");
		}
		else
		{
			CPEventHelper::dispatcher(CPEventName::UI_CHANGE,"HandleMessageGetWorldChartNotify","CombinedServerRankRightPanel");
		}
		return;
	}

	else if (charttype==WorldDefination::blob_combadata || charttype ==WorldDefination::blob_ds_cbt || charttype ==WorldDefination::blob_fs_cbt || charttype ==WorldDefination::blob_zs_cbt )
	{
		
		for (std::vector< ChartElem >::iterator it = resList.begin();it!=resList.end();it++)
		{
			Rank_combatnum r_cbt_num;
			r_cbt_num.id_to_server = it->id;

			std::vector< ChartIntData >& chartIntList = it->nums;
			for (std::vector< ChartIntData >::iterator intit = chartIntList.begin();intit!=chartIntList.end();intit++)
			{
				switch (intit->idx)
				{
				case WorldDefination::chart_rank:
					r_cbt_num.rank = intit->data;
					break;
				case WorldDefination::chart_cbt_num_combatdata:
					r_cbt_num.combatnum = intit->data;
					break;
				case WorldDefination::chart_cbt_num_headrank:
					r_cbt_num.headname = intit->data;
					break;
				case WorldDefination::chart_cbt_num_job:
					r_cbt_num.job = intit->data;
					break;
				default:
					break;
				}
			}

			std::vector< ChartStrData >& chartStrList = it->strs;
			for (std::vector< ChartStrData >::iterator strit = chartStrList.begin();strit!=chartStrList.end();strit++)
			{
				switch (strit->idx)
				{
				case WorldDefination::chart_cbt_str_playername:
					r_cbt_num.name = strit->data;
					break;
				case WorldDefination::chart_guild_str_guildname:
					r_cbt_num.guildname = strit->data;
					break;
				default:
					break;
				}
			}
			switch (charttype)
			{
			case WorldDefination::blob_combadata:
				RankData::m_rankCombatNumAll[r_cbt_num.rank] = r_cbt_num;
				break;
			case WorldDefination::blob_zs_cbt:
				RankData::m_rankCombatNumZS[r_cbt_num.rank] = r_cbt_num;
				break;
			case WorldDefination::blob_fs_cbt:
				RankData::m_rankCombatNumFS[r_cbt_num.rank] = r_cbt_num;
				break;
			case WorldDefination::blob_ds_cbt:
				RankData::m_rankCombatNumDS[r_cbt_num.rank] = r_cbt_num;
				break;
			default:
				break;
			}
		}
	}
	else if (charttype==WorldDefination::blob_leveldata || charttype ==WorldDefination::blob_ds_level || charttype ==WorldDefination::blob_fs_level || charttype ==WorldDefination::blob_zs_level )
	{
		for (std::vector< ChartElem >::iterator it = resList.begin();it!=resList.end();it++)
		{
			Rank_level r_player_level;
			r_player_level.id_to_server = it->id;

			std::vector< ChartIntData >& chartIntList = it->nums;
			for (std::vector< ChartIntData >::iterator intit = chartIntList.begin();intit!=chartIntList.end();intit++)
			{
				switch (intit->idx)
				{
				case WorldDefination::chart_rank:
					r_player_level.rank = intit->data;
					break;
				case WorldDefination::chart_cbt_num_job:
					r_player_level.job = intit->data;
					break;
				case WorldDefination::chart_cbt_num_level:
					r_player_level.level = intit->data;
					break;
				case WorldDefination::chart_cbt_num_reborn:
					r_player_level.reborn = intit->data;
					break;
				case WorldDefination::chart_cbt_num_headrank:
					r_player_level.headname = intit->data;
					break;
				default:
					break;
				}
			}

			std::vector< ChartStrData >& chartStrList = it->strs;
			for (std::vector< ChartStrData >::iterator strit = chartStrList.begin();strit!=chartStrList.end();strit++)
			{
				switch (strit->idx)
				{
				case WorldDefination::chart_cbt_str_playername:
					r_player_level.name = strit->data;
					break;
				case WorldDefination::chart_guild_str_guildname:
					r_player_level.guildname = strit->data;
					break;
				default:
					break;
				}
			}
			switch (charttype)
			{
			case WorldDefination::blob_leveldata:
				RankData::m_rankLevelAll[r_player_level.rank] = r_player_level;
				break;
			case WorldDefination::blob_zs_level:
				RankData::m_rankLevelZS[r_player_level.rank] = r_player_level;
				break;
			case WorldDefination::blob_fs_level:
				RankData::m_rankLevelFS[r_player_level.rank] = r_player_level;
				break;
			case WorldDefination::blob_ds_level:
				RankData::m_rankLevelDS[r_player_level.rank] = r_player_level;
				break;
			default:
				break;
			}
		}
	}
	else if(charttype==WorldDefination::blob_money_top)
	{
		for (std::vector< ChartElem >::iterator it = resList.begin();it!=resList.end();it++)
		{
			Rank_money r_player_money;
			r_player_money.id_to_server = it->id;

			std::vector< ChartIntData >& chartIntList = it->nums;
			for (std::vector< ChartIntData >::iterator intit = chartIntList.begin();intit!=chartIntList.end();intit++)
			{
				switch (intit->idx)
				{
				case WorldDefination::chart_rank:
					r_player_money.rank = intit->data;
					break;
				case WorldDefination::chart_cbt_num_job:
					r_player_money.job = intit->data;
					break;
				case WorldDefination::chart_cbt_num_level:
					r_player_money.level = intit->data;
					break;
				case WorldDefination::chart_cbt_num_reborn:
					r_player_money.reborn = intit->data;
					break;
				case WorldDefination::chart_cbt_num_money:
					r_player_money.money = intit->data;
					break;
				default:
					break;
				}
			}

			std::vector< ChartStrData >& chartStrList = it->strs;
			for (std::vector< ChartStrData >::iterator strit = chartStrList.begin();strit!=chartStrList.end();strit++)
			{
				switch (strit->idx)
				{
				case WorldDefination::chart_cbt_str_playername:
					r_player_money.name = strit->data;
					break;
				default:
					break;
				}
			}

			RankData::m_rankMoney[r_player_money.rank] = r_player_money;			
		}
	}
	else if(charttype==WorldDefination::blob_guildlevel_top)
	{
		for (std::vector< ChartElem >::iterator it = resList.begin();it!=resList.end();it++)
		{
			Rank_guildlevel r_guild_level;
			r_guild_level.id_to_server = it->id;

			std::vector< ChartIntData >& chartIntList = it->nums;
			for (std::vector< ChartIntData >::iterator intit = chartIntList.begin();intit!=chartIntList.end();intit++)
			{
				switch (intit->idx)
				{
				case WorldDefination::chart_rank:
					r_guild_level.rank = intit->data;
					break;
				case WorldDefination::chart_guild_workers:
					r_guild_level.workers = intit->data;
					break;
				case WorldDefination::chart_guild_level:
					r_guild_level.guildlevel = intit->data;
					break;
				default:
					break;
				}
			}

			std::vector< ChartStrData >& chartStrList = it->strs;
			for (std::vector< ChartStrData >::iterator strit = chartStrList.begin();strit!=chartStrList.end();strit++)
			{
				switch (strit->idx)
				{
				case WorldDefination::chart_cbt_str_playername:
					r_guild_level.guildheadname = strit->data;
					break;
				case WorldDefination::chart_guild_str_guildname:
					r_guild_level.guildname = strit->data;
					break;
				default:
					break;
				}
			}

			RankData::m_rankGuildLevel[r_guild_level.rank] = r_guild_level;			
		}
	}
	else if(charttype==WorldDefination::blob_guildylt_top)
	{
		for (std::vector< ChartElem >::iterator it = resList.begin();it!=resList.end();it++)
		{
			Rank_guildlyt r_guild_lyt;
			r_guild_lyt.id_to_server = it->id;

			std::vector< ChartIntData >& chartIntList = it->nums;
			for (std::vector< ChartIntData >::iterator intit = chartIntList.begin();intit!=chartIntList.end();intit++)
			{
				switch (intit->idx)
				{
				case WorldDefination::chart_rank:
					r_guild_lyt.rank = intit->data;
					break;
				case WorldDefination::chart_guild_workers:
					r_guild_lyt.workers = intit->data;
					break;
				case WorldDefination::chart_guild_killlyt:
					r_guild_lyt.killcnt = intit->data;
					break;
				default:
					break;
				}
			}

			std::vector< ChartStrData >& chartStrList = it->strs;
			for (std::vector< ChartStrData >::iterator strit = chartStrList.begin();strit!=chartStrList.end();strit++)
			{
				switch (strit->idx)
				{
				case WorldDefination::chart_cbt_str_playername:
					r_guild_lyt.guildheadname = strit->data;
					break;
				case WorldDefination::chart_pet_str_petname:
					r_guild_lyt.guildname = strit->data;
					break;
				default:
					break;
				}
			}

			RankData::m_rankGuildLYT[r_guild_lyt.rank] = r_guild_lyt;			
		}
	}
	else if(charttype==WorldDefination::blob_pet_top)
	{
		for (std::vector< ChartElem >::iterator it = resList.begin();it!=resList.end();it++)
		{
			Rank_pet r_player_pet;
			r_player_pet.id_to_server = it->id;

			std::vector< ChartIntData >& chartIntList = it->nums;
			for (std::vector< ChartIntData >::iterator intit = chartIntList.begin();intit!=chartIntList.end();intit++)
			{
				switch (intit->idx)
				{
				case WorldDefination::chart_rank:
					r_player_pet.rank = intit->data;
					break;
				case WorldDefination::chart_pet_level:
					r_player_pet.petstars = intit->data;
					break;
				default:
					break;
				}
			}

			std::vector< ChartStrData >& chartStrList = it->strs;
			for (std::vector< ChartStrData >::iterator strit = chartStrList.begin();strit!=chartStrList.end();strit++)
			{
				switch (strit->idx)
				{
				case WorldDefination::chart_cbt_str_playername:
					r_player_pet.name = strit->data;
					break;
				case WorldDefination::chart_pet_str_petname:
					r_player_pet.petname = strit->data;
					break;
				default:
					break;
				}
			}

			RankData::m_rankPet[r_player_pet.rank] = r_player_pet;			
		}
	}
	else if(charttype==WorldDefination::blob_fireworks_data)
	{
		for (std::vector< ChartElem >::iterator it = resList.begin();it!=resList.end();it++)
		{
			Rank_firework r_player_firework;
			r_player_firework.id_to_server = it->id;

			std::vector< ChartIntData >& chartIntList = it->nums;
			for (std::vector< ChartIntData >::iterator intit = chartIntList.begin();intit!=chartIntList.end();intit++)
			{
				switch (intit->idx)
				{
				case WorldDefination::chart_rank:
					r_player_firework.rank = intit->data;
					break;
				case WorldDefination::chart_cbt_num_level:
					r_player_firework.level = intit->data;
					break;
				case WorldDefination::chart_fireworks_bless:
					r_player_firework.fireworkcnt = intit->data;
					break;
				default:
					break;
				}
			}

			std::vector< ChartStrData >& chartStrList = it->strs;
			for (std::vector< ChartStrData >::iterator strit = chartStrList.begin();strit!=chartStrList.end();strit++)
			{
				switch (strit->idx)
				{
				case WorldDefination::chart_cbt_str_playername:
					r_player_firework.name = strit->data;
					break;
				default:
					break;
				}
			}

			RankData::m_rankFireWork[r_player_firework.rank] = r_player_firework;			
		}
	}
	RankData::setVersion(charttype,msg->version);
	RankData::setSelfRank(charttype,msg->selfrank);

	if (msg->posttimes == 1)
	{
		CPEventHelper::dispatcher(CPEventName::UI_CHANGE,"RankLeftPanel","RankRightPanel");
	}
	else
	{
		CPEventHelper::dispatcher(CPEventName::UI_CHANGE,"HandleMessageGetWorldChartNotify","RankRightPanel");
	}
}

void MsgMaster::HandleMessageSyncWorldDataResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncWorldDataResponse, pMsg);

	WorldData::setWorldDataNormal(msg->wid,msg->datax,msg->datay,msg->dataz,msg->version);
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_2, msg->wid);
	CPEventHelper::msgResponse("HandleMessageSyncWorldDataResponse", "", Error::Success);
}

void MsgMaster::HandleMessageSyncWorldDataStringResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncWorldDataStringResponse, pMsg);

	WorldData::setWorldDataString(msg->wid,msg->datas,msg->version);
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_2, msg->wid);
	CPEventHelper::msgResponse("HandleMessageSyncWorldDataStringResponse", "", Error::Success);
}

void MsgMaster::HandleMessageScriptDataResponse(IMsg* pMsg)
{
	CP_TEST_NULL_MSG(MsgScriptDataResponse, pMsg);
	ScriptPatchManager::instance()->HandleScriptDataResponse(msg);
}

void MsgMaster::HandleMessageScriptPatchNotify(IMsg* pMsg)
{
	CP_TEST_NULL_MSG(MsgScriptPatchNotify, pMsg);
	ScriptPatchManager::instance()->HandleScriptPatchNotify(msg);
}