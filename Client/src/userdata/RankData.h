#ifndef __RankData_H__
#define __RankData_H__

#include "stdafx.h"
#include "cocos2d.h"


enum RankList
{
	rank_combatnum_all	= 0,
	rank_combatnum_zs	,
	rank_combatnum_fs,
	rank_combatnum_ds,

	rank_level_all	= 10,
	rank_level_zs,
	rank_level_fs,
	rank_level_ds,

	rank_pet_all	= 20,

	rank_rich_all	=30,

	rank_guild_level	=40,
	rank_guild_lyt,

	rank_firework = 50,

	rank_combined_chongzhi = 60,
	rank_combined_xiaofei,
	rank_max,
};


struct Rank_combatnum
{
	int rank;
	std::string name;
	std::string guildname;
	int combatnum;
	int headname;
	int job;
	int id_to_server;
};

struct Rank_level
{
	int rank;
	std::string name;
	std::string guildname;
	int job;
	int level;
	int reborn;
	int headname;
	int id_to_server;
};

struct Rank_pet
{
	int rank;
	std::string name;
	std::string petname;
	int petstars;
	int id_to_server;
};

struct Rank_money
{
	int rank;
	std::string name;
	int job;
	int level;
	int reborn;
	int money;
	int id_to_server;
};

struct Rank_guildlevel
{
	int rank;
	std::string guildname;
	int guildlevel;
	std::string guildheadname;
	int workers;
	int id_to_server;
};

struct Rank_guildlyt
{
	int rank;
	std::string guildname;
	int killcnt;
	std::string guildheadname;
	int workers;
	int id_to_server;
};

struct Rank_firework
{
	int rank;
	std::string name;
	int level;
	int fireworkcnt;
	int id_to_server;
};

struct Rank_combined
{
	int rank;
	std::string name;
	std::string guildname;
	std::string servername;
	std::string rechargeamount;
};

using namespace cocos2d;
class RankData
{
public:
	static std::map<int,Rank_combatnum> m_rankCombatNumAll;
	static std::map<int,Rank_combatnum> m_rankCombatNumZS;
	static std::map<int,Rank_combatnum> m_rankCombatNumFS;
	static std::map<int,Rank_combatnum> m_rankCombatNumDS;
	static std::map<int,Rank_level> m_rankLevelAll;
	static std::map<int,Rank_level> m_rankLevelZS;
	static std::map<int,Rank_level> m_rankLevelFS;
	static std::map<int,Rank_level> m_rankLevelDS;
	static std::map<int,Rank_pet> m_rankPet;
	static std::map<int,Rank_money> m_rankMoney;
	static std::map<int,Rank_guildlevel> m_rankGuildLevel;
	static std::map<int,Rank_guildlyt> m_rankGuildLYT;
	static std::map<int,Rank_firework> m_rankFireWork;
	static std::map<int,Rank_combined> m_rankCombined;
	static std::map<int,Rank_combined> m_rankCombined2;

public:
	static void setRankPanelType(int type);
	static int getRankPanelType();
	static void setRankServerType(int type);
	static int getRankServerType();
	static void clearList(int type);

	static int getVersion(int type);
	static void setVersion(int type, int data);
	static int getSelfRank(int type);
	static void setSelfRank(int type, int data);
private:
	static int m_iRankPanelType;
	static int m_iRankServerType;

	static std::map<int ,int > m_mVersion;
	static std::map<int ,int > m_rankSelf;
};


#endif//__Emigrated_DATA_H__