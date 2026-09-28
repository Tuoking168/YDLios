#include "RankData.h"
#include "event/CPEventHelper.h"
#include <cstring>
#include "WorldDefinition.h"
#include "MsgWorld.h"
#include "network/HandleMessage.h"

static std::map<int,Rank_combatnum> emptyMap1;
static std::map<int,Rank_level> emptyMap2;
static std::map<int,Rank_pet> emptyMap3;
static std::map<int,Rank_money> emptyMap4;
static std::map<int,Rank_guildlevel> emptyMap5;
static std::map<int,Rank_guildlyt> emptyMap6;
static std::map<int,int> emptyMap7;
static std::map<int,Rank_firework> emptyMap8;
static std::map<int,Rank_combined> emptyMap9;

std::map<int,Rank_combatnum> RankData::m_rankCombatNumAll = emptyMap1;
std::map<int,Rank_combatnum> RankData::m_rankCombatNumZS = emptyMap1;
std::map<int,Rank_combatnum> RankData::m_rankCombatNumFS = emptyMap1;
std::map<int,Rank_combatnum> RankData::m_rankCombatNumDS = emptyMap1;
std::map<int,Rank_level> RankData::m_rankLevelAll= emptyMap2;
std::map<int,Rank_level> RankData::m_rankLevelZS= emptyMap2;
std::map<int,Rank_level> RankData::m_rankLevelFS= emptyMap2;
std::map<int,Rank_level> RankData::m_rankLevelDS= emptyMap2;
std::map<int,Rank_pet> RankData::m_rankPet= emptyMap3;
std::map<int,Rank_money> RankData::m_rankMoney= emptyMap4;
std::map<int,Rank_guildlevel> RankData::m_rankGuildLevel= emptyMap5;
std::map<int,Rank_guildlyt> RankData::m_rankGuildLYT= emptyMap6;
std::map<int,Rank_firework> RankData::m_rankFireWork= emptyMap8;
std::map<int,Rank_combined> RankData::m_rankCombined = emptyMap9;
std::map<int,Rank_combined> RankData::m_rankCombined2 = emptyMap9;

std::map<int ,int > RankData::m_mVersion = emptyMap7;
std::map<int ,int > RankData::m_rankSelf = emptyMap7;

int RankData::m_iRankPanelType = 0;
int RankData::m_iRankServerType = 0;

void RankData::setRankPanelType( int type )
{
	RankData::m_iRankPanelType = type;

	int charttype = WorldDefination::blob_combadata; 
	switch (type)
	{
	case rank_combatnum_all:
		charttype = WorldDefination::blob_combadata;
		break;
	case rank_combatnum_zs:
		charttype = WorldDefination::blob_zs_cbt;
		break;
	case rank_combatnum_fs:
		charttype = WorldDefination::blob_fs_cbt;
		break;
	case rank_combatnum_ds:
		charttype = WorldDefination::blob_ds_cbt;
		break;
	case rank_level_all:
		charttype = WorldDefination::blob_leveldata;
		break;
	case rank_level_zs:
		charttype = WorldDefination::blob_zs_level;
		break;
	case rank_level_fs:
		charttype = WorldDefination::blob_fs_level;
		break;
	case rank_level_ds:
		charttype = WorldDefination::blob_ds_level;
		break;
	case rank_pet_all:
		charttype = WorldDefination::blob_pet_top;
		break;
	case rank_rich_all:
		charttype = WorldDefination::blob_money_top;
		break;
	case rank_guild_level:
		charttype = WorldDefination::blob_guildlevel_top;
		break;
	case rank_guild_lyt:
		charttype = WorldDefination::blob_guildylt_top;
		break;
	case rank_firework:
		charttype = WorldDefination::blob_fireworks_data;
		break;
	case rank_combined_chongzhi:
		charttype = WorldDefination::blob_combinedserver_chongzhi;
		break;
	case rank_combined_xiaofei:
		charttype = WorldDefination::blob_combinedserver_xiaofei;
		break;
	default:
		break;
	}
	RankData::setRankServerType(charttype);

	MsgGetWorldChartRequest* msg = new MsgGetWorldChartRequest;
	msg->charttype = charttype;
	msg->version = RankData::getVersion(charttype);
	HandleMessage::sendMessage(msg);
}

int RankData::getRankPanelType()
{
	return RankData::m_iRankPanelType;
}

void RankData::clearList( int type )
{
	switch (type)
	{
	case WorldDefination::blob_combadata:
		RankData::m_rankCombatNumAll.clear();
		break;
	case WorldDefination::blob_zs_cbt:
		RankData::m_rankCombatNumZS.clear();
		break;
	case WorldDefination::blob_fs_cbt:
		RankData::m_rankCombatNumFS.clear();
		break;
	case WorldDefination::blob_ds_cbt:
		RankData::m_rankCombatNumDS.clear();
		break;
	case WorldDefination::blob_leveldata:
		RankData::m_rankLevelAll.clear();
		break;
	case WorldDefination::blob_zs_level:
		RankData::m_rankLevelZS.clear();
		break;
	case WorldDefination::blob_fs_level:
		RankData::m_rankLevelFS.clear();
		break;
	case WorldDefination::blob_ds_level:
		RankData::m_rankLevelDS.clear();
		break;
	case WorldDefination::blob_money_top:
		RankData::m_rankMoney.clear();
		break;
	case WorldDefination::blob_pet_top:
		RankData::m_rankPet.clear();
		break;
	case WorldDefination::blob_fireworks_data:
		RankData::m_rankFireWork.clear();
		break;
	case WorldDefination::blob_combinedserver_chongzhi:
		RankData::m_rankCombined.clear();
		break;
	case WorldDefination::blob_combinedserver_xiaofei:
		RankData::m_rankCombined2.clear();
		break;
	default:
		break;
	}
}

int RankData::getVersion( int type )
{
	std::map<int,int>::iterator it = RankData::m_mVersion.find(type);
	if (it!=RankData::m_mVersion.end())
	{
		return it->second;
	}
	return 0;
}

void RankData::setVersion( int type, int data )
{
	RankData::m_mVersion[type] = data;
}

int RankData::getSelfRank( int type )
{
	std::map<int,int>::iterator it = RankData::m_rankSelf.find(type);
	if (it!=RankData::m_rankSelf.end())
	{
		return it->second;
	}
	return 0;
}

void RankData::setSelfRank( int type, int data )
{
	RankData::m_rankSelf[type] = data;
}

void RankData::setRankServerType( int type )
{
	m_iRankServerType = type;
}

int RankData::getRankServerType()
{
	return m_iRankServerType;
}
