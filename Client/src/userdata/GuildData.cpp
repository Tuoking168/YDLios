#include "GuildData.h"
#include "cocos2d.h"
#include "EntityDefinition.h"
#include "ErrorDefinition.h"
#include "GuildDefinition.h"
#include "ModuleData.h"
#include "GuildModule.h"
#include "utils/StringUtils.h"

#include "userdata/HeroData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/GuildData.h"


using namespace cocos2d;

//////////GuildData///////////////////////////////////////////////

bool GuildData::hasGuild()
{
	return (getMyGuildID() > 0);
}

void GuildData::clear()
{
	ModuleData::clearModule(CPModuleName::GUILD);
}

int GuildData::getGuildCnt()
{
	int playerCnt = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_LIST);
	SubModuleData::getSize(playerCnt);
	return playerCnt;
}

int GuildData::getRankByIndex( int index )
{
	return (getGuildPage() - 1) * getPerPage() + index + 1;
}

int GuildData::getGuildPage()
{
	int value = 0;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_PAGE, value);
	return value;
}
int GuildData::getGuildMaxPage()
{
	int value = 0;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_MAXPAGE, value);
	return value;
}

int GuildData::getPerPage()
{
	return 6;
}

int GuildData::getGuildID( int rank )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_LIST);
	SubModuleData::getInt(rank, CPGuildData::GUILD_ID, ret);
	return ret;
}

std::string GuildData::getGuildName( int rank )
{
	std::string guildName;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_LIST);
	SubModuleData::getString(rank, CPGuildData::GUILD_NAME, guildName);
	return guildName;
}
int GuildData::getGuildLevel( int rank )
{
	int value = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_LIST);
	SubModuleData::getInt(rank, CPGuildData::GUILD_LEVEL, value);
	return value;
}

int GuildData::getGuildState(int rank)
{
	int value = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_LIST);
	SubModuleData::getInt(rank, CPGuildData::GUILD_STATE, value);
	return value;
}

std::string GuildData::getGuildMasterName( int rank )
{
	std::string value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_LIST);
	SubModuleData::getString(rank, CPGuildData::GUILD_MASTERNAME, value);
	return value;
}
int GuildData::getGuildMasterID( int rank )
{
	int value = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_LIST);
	SubModuleData::getInt(rank, CPGuildData::GUILD_MASTERID, value);
	return value;
}
int GuildData::getGuildMemberCount( int rank )
{
	int value = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_LIST);
	SubModuleData::getInt(rank, CPGuildData::GUILD_MEMBERCOUNT, value);
	return value;
}
int GuildData::getGuildMaxMember( int level )
{
	int value = 0;
	LuaData::getProp(LuaData::GUILD_DATA,level,"maxmember", value);
	return value;
}

int GuildData::getIndexByPID( int pid )
{
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
	IDVector vect;
	SubModuleData::getIDVector(vect);
	for (int i = 0; i < (int)vect.size(); i++)
	{
		if (vect[i] == pid)
		{
			return i;
		}
	}
	return -1;
}

int GuildData::getGuildMemberPage()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_PAGE, value);
	return value;
}
int GuildData::getGuildMemberMaxPage()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_MAXPAGE, value);
	return value;
}
int GuildData::getGuildMemberCnt()
{
	int playerCnt = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	SubModuleData::getSize(playerCnt);
	return playerCnt;
}
int GuildData::getGuildMemberPID(int index)
{
	int pid = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	IDVector vect;
	SubModuleData::getIDVector(vect);
	if (0 <= index && index < (int)vect.size())
	{
		pid = vect[index];
	}
	return pid;
}
std::string GuildData::getGuildMemberName(int index)
{
	std::string value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	SubModuleData::getString(getGuildMemberPID(index), CPGuildData::GUILD_MEMBER_NAME, value);
	return value;
}
int GuildData::getGuildMemberLevel(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	SubModuleData::getInt(getGuildMemberPID(index), CPGuildData::GUILD_MEMBER_LEVEL, value);
	return value;
}
int GuildData::getGuildMemberRank(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	SubModuleData::getInt(getGuildMemberPID(index), CPGuildData::GUILD_MEMBER_RANK, value);
	return value;
}
int GuildData::getGuildMemberArenaRank(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	SubModuleData::getInt(getGuildMemberPID(index), CPGuildData::GUILD_MEMBER_ARENARANK, value);
	return value;
}
int GuildData::getGuildMemberJob(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	SubModuleData::getInt(getGuildMemberPID(index), CPGuildData::GUILD_MEMBER_JOB, value);
	if (value>GuildType::post_normal||value<0)
	{
		value=GuildType::post_normal;
	}
	return value;
}
int GuildData::getGuildMemberNickname(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	SubModuleData::getInt(getGuildMemberPID(index), CPGuildData::GUILD_MEMBER_NICKNAME, value);
	return value;
}
int GuildData::getGuildMemberContribution(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	SubModuleData::getInt(getGuildMemberPID(index), CPGuildData::GUILD_MEMBER_CONTRIBUTION, value);
	return value;
}
int GuildData::getGuildMemberTodayContribution(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	SubModuleData::getInt(getGuildMemberPID(index), CPGuildData::GUILD_MEMBER_TODAYCONTRIBUTION, value);
	return value;
}
std::string GuildData::getGuildMemberLastonline(int index)
{
	std::string value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	SubModuleData::getString(getGuildMemberPID(index), CPGuildData::GUILD_MEMBER_LASTONLINE, value);
	return value;
}

int GuildData::getMyGuildID()
{
	return HeroData::getProp(Entity::attr_guild_id);
}

int GuildData::getMyGuildRank()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_RANK, value);
	return value;
}
std::string GuildData::getMyGuildName()
{
	std::string value;
	ModuleData::getString(CPModuleName::GUILD, CPGuildData::GUILD_NAME, value);
	return value;
}
int GuildData::getMyGuildLevel()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_LEVEL, value);
	return value;
}
std::string GuildData::getMyGuildMasterName()
{
	std::string value;
	ModuleData::getString(CPModuleName::GUILD, CPGuildData::GUILD_MASTERNAME, value);
	return value;
}
int GuildData::getMyGuildMasterID()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_MASTERID, value);
	return value;
}
int GuildData::getMyGuildMemberCount()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBERCOUNT, value);
	return value;
}
int GuildData::getMyGuildMaxMember()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_MAXMEMBER, value);
	return value;
}
int GuildData::getMyGuildContribution()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_CONTRIBUTION, value);
	return value;
}
int GuildData::getMyGuildMoney()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_MONEY, value);
	return value;
}
int GuildData::getMyJob()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_JOB, value);
	return value;
}
int GuildData::getMyNickname()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_NICKNAME, value);
	return value;
}
int GuildData::getMyContribution()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_CONTRIBUTION, value);
	return value;
}

int GuildData::getJobReward(int job)
{
	int sid = 0;
	if (LuaData::getProp(LuaData::GUILD_JOB_REWARD,job,"reward",sid))
	{
		return sid;
	}
	return 0;
}
int GuildData::getJobRewardCount(int job)
{
	int value;
	if (LuaData::getProp(LuaData::GUILD_JOB_REWARD,job,"count",value))
	{
		return value;
	}
	return 0;
}

int GuildData::getGuildApplicationPID(int index)
{
	int pid = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_APPLICATION_LIST);
	IDVector vect;
	SubModuleData::getIDVector(vect);
	if (0 <= index && index < (int)vect.size())
	{
		pid = vect[index];
	}
	return pid;
}
std::string GuildData::getGuildApplicationName(int index)
{
	std::string value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_APPLICATION_LIST);
	SubModuleData::getString(getGuildApplicationPID(index), CPGuildData::GUILD_APPLICATION_NAME, value);
	return value;
}
int GuildData::getGuildApplicationLevel(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_APPLICATION_LIST);
	SubModuleData::getInt(getGuildApplicationPID(index), CPGuildData::GUILD_APPLICATION_LEVEL, value);
	return value;
}

int GuildData::getGuildApplicationCnt()
{
	int appCnt = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_APPLICATION_LIST);
	SubModuleData::getSize(appCnt);
	return appCnt;

}

int GuildData::getGuildNicknameJob(int index)
{
	int nid = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_NICKNAME_LIST);
	IDVector vect;
	SubModuleData::getIDVector(vect);
	if (0 <= index && index < (int)vect.size())
	{
		nid = vect[index];
	}
	return nid;
}
std::string GuildData::getGuildNickname(int index)
{
	std::string value;
	//SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_NICKNAME_LIST);
	//SubModuleData::getString(getGuildNicknameJob(index), CPGuildData::GUILD_NICKNAME_NAME, value);
	value = GuildData::getGuildStringProp(index+GuildType::guild_nick_normal);
	return value;
}
int GuildData::getGuildNicknameCnt()
{
// 	int nCnt = 0;
// 	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_NICKNAME_LIST);
// 	SubModuleData::getSize(nCnt);
// 	return nCnt;
	/*
	int value;
	if (LuaData::getProp_size("gdGuildJobReward",0,"",value))
	{
		return value;
	}
	return 0;
	*/
	return 4;
}

void  GuildData::setNicknameTipPostion(CCPoint tSize)
{
	ModuleData::setFloat(CPModuleName::GUILD, CPGuildData::GUILD_NICKNAME_TIP_X, tSize.x);
	ModuleData::setFloat(CPModuleName::GUILD, CPGuildData::GUILD_NICKNAME_TIP_Y, tSize.y);
}
CCPoint  GuildData::getNicknameTipPostion()
{
	CCPoint value;
	ModuleData::getFloat(CPModuleName::GUILD, CPGuildData::GUILD_NICKNAME_TIP_X, value.x);
	ModuleData::getFloat(CPModuleName::GUILD, CPGuildData::GUILD_NICKNAME_TIP_Y, value.y);
	return value;
}
std::string GuildData::getDefaultNickname(int job)
{
	std::string nickname = "";
	if (LuaData::getProp(LuaData::GUILD_JOB_REWARD,job,"nickname",nickname))
	{
		if (nickname.empty()||nickname.length()<=0||nickname=="0")
		{
			LuaData::getProp(LuaData::GUILD_JOB_REWARD,GuildType::post_normal,"nickname",nickname);
		}
	}
	return nickname;
}
void GuildData::setNicknameSelectPid(int index)
{
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_NICKNAME_SELECT,index);
}
int GuildData::getNicknameSelectPid()
{
	int value;
	ModuleData::getInt(CPModuleName::GUILD, CPGuildData::GUILD_NICKNAME_SELECT, value);
	return value;
}
void GuildData::changeMemberNickname(int job)
{
	int pid = getNicknameSelectPid();
	if (pid)
	{
		SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_JOB, job);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_NICKNAME, job);
	}
}


int GuildData::getGuildAllMemberCnt()
{
	int playerCnt = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	SubModuleData::getSize(playerCnt);
	return playerCnt;
}
int GuildData::getGuildAllMemberPID(int index)
{
	int pid = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	IDVector vect;
	SubModuleData::getIDVector(vect);
	if (0 <= index && index < (int)vect.size())
	{
		pid = vect[index];
	}
	return pid;
}
std::string GuildData::getGuildAllMemberName(int index)
{
	std::string value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	SubModuleData::getString(getGuildAllMemberPID(index), CPGuildData::GUILD_MEMBER_NAME, value);
	return value;
}
int GuildData::getGuildAllMemberLevel(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	SubModuleData::getInt(getGuildAllMemberPID(index), CPGuildData::GUILD_MEMBER_LEVEL, value);
	return value;
}
int GuildData::getGuildAllMemberRank(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	SubModuleData::getInt(getGuildAllMemberPID(index), CPGuildData::GUILD_MEMBER_RANK, value);
	return value;
}
int GuildData::getGuildAllMemberArenaRank(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	SubModuleData::getInt(getGuildAllMemberPID(index), CPGuildData::GUILD_MEMBER_ARENARANK, value);
	return value;
}
int GuildData::getGuildAllMemberJob(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	SubModuleData::getInt(getGuildAllMemberPID(index), CPGuildData::GUILD_MEMBER_JOB, value);
	if (value>GuildType::post_normal||value<0)
	{
		value=GuildType::post_normal;
	}
	return value;
}
int GuildData::getGuildAllMemberNickname(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	SubModuleData::getInt(getGuildAllMemberPID(index), CPGuildData::GUILD_MEMBER_NICKNAME, value);
	return value;
}
int GuildData::getGuildAllMemberContribution(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	SubModuleData::getInt(getGuildAllMemberPID(index), CPGuildData::GUILD_MEMBER_CONTRIBUTION, value);
	return value;
}
int GuildData::getGuildAllMemberTodayContribution(int index)
{
	int value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	SubModuleData::getInt(getGuildAllMemberPID(index), CPGuildData::GUILD_MEMBER_TODAYCONTRIBUTION, value);
	return value;
}
std::string GuildData::getGuildAllMemberLastonline(int index)
{
	std::string value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	SubModuleData::getString(getGuildAllMemberPID(index), CPGuildData::GUILD_MEMBER_LASTONLINE, value);
	return value;
}
int GuildData::getGCZAttackGuildCnt()
{
	int playerCnt = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GCZ_ATTACK_GUILD_LIST);
	SubModuleData::getSize(playerCnt);
	return playerCnt;
}
std::string GuildData::getGCZAttackGuildName(int index)
{
	std::string value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GCZ_ATTACK_GUILD_LIST);
	SubModuleData::getString(index, CPGuildData::GUILD_NAME, value);
	return value;
}
int GuildData::getGCZLastAttackGuildCnt()
{
	int playerCnt = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GCZ_LAST_ATTACK_GUILD_LIST);
	SubModuleData::getSize(playerCnt);
	return playerCnt;
}
std::string GuildData::getGCZLastAttackGuildName(int index)
{
	std::string value;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GCZ_LAST_ATTACK_GUILD_LIST);
	SubModuleData::getString(index, CPGuildData::GUILD_NAME, value);
	return value;
}

void GuildData::setGuildProp( int key, int value )
{
	const std::string fullKey = CPGuildData::GUILD_PROP_ + StringUtils::toString(key);
	ModuleData::setInt(CPModuleName::GUILD, fullKey, value);
}

int GuildData::getGuildProp( int key )
{
	int ret = 0;
	const std::string fullKey = CPGuildData::GUILD_PROP_ + StringUtils::toString(key);
	ModuleData::getInt(CPModuleName::GUILD, fullKey, ret);
	return ret;
}
void GuildData::setGuildStringProp( int key, std::string value )
{
	const std::string fullKey = CPGuildData::GUILD_STRING_PROP_ + StringUtils::toString(key);
	ModuleData::setString(CPModuleName::GUILD, fullKey, value);
}

std::string GuildData::getGuildStringProp( int key )
{
	std::string ret = "";
	const std::string fullKey = CPGuildData::GUILD_STRING_PROP_ + StringUtils::toString(key);
	ModuleData::getString(CPModuleName::GUILD, fullKey, ret);
	return ret;
}

void GuildData::setGuildTanXianData( int index, int sid )
{
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_BUILDING_TANXIAN_ITEM_LIST);
	SubModuleData::setInt(index, CPGuildData::GUILD_BUILDING_TANXIAN_ITEM, sid);
}

int GuildData::getGuildTanXianData( int index )
{
	int sid = 0;
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_BUILDING_TANXIAN_ITEM_LIST);
	SubModuleData::getInt(index, CPGuildData::GUILD_BUILDING_TANXIAN_ITEM, sid);
	return sid;
}

void GuildData::clearGuildTanXianData()
{
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_BUILDING_TANXIAN_ITEM_LIST);
	SubModuleData::clearAll();
}
