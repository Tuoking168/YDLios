#include "ActivityData.h"
#include "ModuleData.h"
#include "ActivityModule.h"
#include <ctime>

#include "utils/StringUtils.h"
#include "script/LuaWrapper.h"


static void setActivityData( const std::string &keyHead, int id, int data )
{
	const std::string fullKey = keyHead + StringUtils::toString(id);
	ModuleData::setInt(CPModuleName::ACTIVITY, fullKey, data);
}

static int getActivityData( const std::string &keyHead, int id )
{
	int ret = 0;
	const std::string fullKey = keyHead + StringUtils::toString(id);
	ModuleData::getInt(CPModuleName::ACTIVITY, fullKey, ret);
	return ret;
}

///////////ActivityData////////////////////////////////////////////
int ActivityData::getActivityID( const std::string &idName )
{
	int ret = 0;
	Lua::instance()->push(idName);
	Lua::instance()->call("get_activity_id_by_id_name", 1, 1);
	Lua::instance()->pop(ret);
	return ret;
}

void ActivityData::clear()
{
	ModuleData::clearModule(CPModuleName::ACTIVITY);
}

void ActivityData::setState( int timeID, int state)
{
	setActivityData(CPActivityData::STATE_, timeID, state);
}

int ActivityData::getState( int timeID )
{
	return getActivityData(CPActivityData::STATE_, timeID);
}

void ActivityData::setUnstartID( int unstartID )
{
	ModuleData::setInt(CPModuleName::ACTIVITY, CPActivityData::UNSTART_ID, unstartID);
}

int ActivityData::getUnstartID()
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::ACTIVITY, CPActivityData::UNSTART_ID, ret);
	return ret;
}

void ActivityData::setNotFinishCnt( int activityID, int cnt )
{
	setActivityData(CPActivityData::NOT_FINISH_CNT_, activityID, cnt);
}

int ActivityData::getNotFinishCnt( int activityID )
{
	return getActivityData(CPActivityData::NOT_FINISH_CNT_, activityID);
}

void ActivityData::setExData( int activityID, int dataX, int dataY, int dataZ )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::EX_DATA_LIST);
	SubModuleData::setInt(activityID, CPActivityData::EX_DATA_X, dataX);
	SubModuleData::setInt(activityID, CPActivityData::EX_DATA_Y, dataY);
	SubModuleData::setInt(activityID, CPActivityData::EX_DATA_Z, dataZ);
}

void ActivityData::getExData( int activityID, int &dataX, int &dataY, int &dataZ )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::EX_DATA_LIST);
	SubModuleData::getInt(activityID, CPActivityData::EX_DATA_X, dataX);
	SubModuleData::getInt(activityID, CPActivityData::EX_DATA_Y, dataY);
	SubModuleData::getInt(activityID, CPActivityData::EX_DATA_Z, dataZ);
}

int ActivityData::getExDataX( int activityID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::EX_DATA_LIST);
	SubModuleData::getInt(activityID, CPActivityData::EX_DATA_X, ret);
	return ret;
}

int ActivityData::getExDataY( int activityID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::EX_DATA_LIST);
	SubModuleData::getInt(activityID, CPActivityData::EX_DATA_Y, ret);
	return ret;
}

int ActivityData::getExDataZ( int activityID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::EX_DATA_LIST);
	SubModuleData::getInt(activityID, CPActivityData::EX_DATA_Z, ret);
	return ret;
}

void ActivityData::setWorldTime( int worldTime )
{
	ModuleData::setInt(CPModuleName::ACTIVITY, CPActivityData::WORLD_TIME, worldTime);
}

int ActivityData::getWorldTime()
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::ACTIVITY, CPActivityData::WORLD_TIME, ret);
	return ret;
}

void ActivityData::setWorldBeginTime( int begintime )
{
	ModuleData::setInt(CPModuleName::ACTIVITY, CPActivityData::WORLD_BEGIN_TIME, begintime);
}

int ActivityData::getWorldBeginTime()
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::ACTIVITY, CPActivityData::WORLD_BEGIN_TIME, ret);
	return ret;
}

int ActivityData::getWorldBeginDays()
{
	static const int SECOND_PER_DAY = 86400;
	int openTime = time(0) - getWorldBeginTime();
	if (openTime < 0)
	{
		openTime = 0;
	}
	return openTime/SECOND_PER_DAY + 1;
}

void ActivityData::setHideList( const IDVector &vect )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::HIDE_LIST);
	SubModuleData::clearAll();
	for (int i = 0; i < (int)vect.size(); i++)
	{
		SubModuleData::setInt(vect[i], CPActivityData::HIDE_STATE, 1);
	}
}

bool ActivityData::isHide( int ctrlID )
{
	int flag = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::HIDE_LIST);
	SubModuleData::getInt(ctrlID, CPActivityData::HIDE_STATE, flag);
	return (flag != 0);
}

IDVector ActivityData::getHideList()
{
	IDVector ret;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::HIDE_LIST);
	SubModuleData::getIDVector(ret);
	return ret;
}

void ActivityData::setWorldIntProp( int id, int index, int data )
{
	setWorldIntProp(id, index, data, 0);
}

void ActivityData::setWorldIntProp( int id, int index, int data, int version )
{
	const std::string &subModule = CPActivityData::WORLD_INT_PROP_ + StringUtils::toString(id);
	SubModuleData::init(CPModuleName::ACTIVITY, subModule);
	SubModuleData::setInt(index, CPActivityData::WORLD_PROP, data);
	SubModuleData::setInt(index, CPActivityData::WORLD_PROP_VERSION, version);
}

void ActivityData::setWorldStringProp( int id, int index, const std::string &data )
{
	setWorldStringProp(id, index, data, 0);
}

void ActivityData::setWorldStringProp( int id, int index, const std::string &data, int version )
{
	const std::string &subModule = CPActivityData::WORLD_STRING_PROP_ + StringUtils::toString(id);
	SubModuleData::init(CPModuleName::ACTIVITY, subModule);
	SubModuleData::setString(index, CPActivityData::WORLD_PROP, data);
	SubModuleData::setInt(index, CPActivityData::WORLD_PROP_VERSION, version);
}

int ActivityData::getWorldIntProp( int id, int index )
{
	int ret = 0;
	const std::string &subModule = CPActivityData::WORLD_INT_PROP_ + StringUtils::toString(id);
	SubModuleData::init(CPModuleName::ACTIVITY, subModule);
	SubModuleData::getInt(index, CPActivityData::WORLD_PROP, ret);
	return ret;
}

std::string ActivityData::getWorldStringProp( int id, int index )
{
	std::string ret;
	const std::string &subModule = CPActivityData::WORLD_STRING_PROP_ + StringUtils::toString(id);
	SubModuleData::init(CPModuleName::ACTIVITY, subModule);
	SubModuleData::getString(index, CPActivityData::WORLD_PROP, ret);
	return ret;
}

int ActivityData::getWorldIntPropVersion( int id )
{
	int ret = 0;
	const std::string &subModule = CPActivityData::WORLD_INT_PROP_ + StringUtils::toString(id);
	SubModuleData::init(CPModuleName::ACTIVITY, subModule);
	SubModuleData::getInt(0, CPActivityData::WORLD_PROP_VERSION, ret);
	return ret;
}

int ActivityData::getWorldStringPropVersion( int id )
{
	int ret = 0;
	const std::string &subModule = CPActivityData::WORLD_STRING_PROP_ + StringUtils::toString(id);
	SubModuleData::init(CPModuleName::ACTIVITY, subModule);
	SubModuleData::getInt(0, CPActivityData::WORLD_PROP_VERSION, ret);
	return ret;
}

void ActivityData::clearWorldProp( int id )
{
	std::string subModule = CPActivityData::WORLD_INT_PROP_ + StringUtils::toString(id);
	SubModuleData::init(CPModuleName::ACTIVITY, subModule);
	SubModuleData::clearAll();

	subModule = CPActivityData::WORLD_STRING_PROP_ + StringUtils::toString(id);
	SubModuleData::init(CPModuleName::ACTIVITY, subModule);
	SubModuleData::clearAll();
}

void ActivityData::setMoBaiData( int key, int data )
{
	setActivityData(CPActivityData::MO_BAI_, key, data);
}

int ActivityData::getMoBaiData( int key )
{
	return getActivityData(CPActivityData::MO_BAI_, key);
}

void ActivityData::setCaiShenChuangGuanData( int key, int data )
{
	setActivityData(CPActivityData::CAI_SHEN_CHUANG_GUAN_, key, data);
}

int ActivityData::getCaiShenChuangGuanData( int key )
{
	return getActivityData(CPActivityData::CAI_SHEN_CHUANG_GUAN_, key);
}

void ActivityData::setMeiNvHuSongData( int key, int data )
{
	setActivityData(CPActivityData::MEI_NV_HU_SONG_, key, data);
}

int ActivityData::getMeiNvHuSongData( int key )
{
	return getActivityData(CPActivityData::MEI_NV_HU_SONG_, key);
}

void ActivityData::setQiFuShuData( int key, int data )
{
	setActivityData(CPActivityData::QI_FU_SHU_, key, data);
}

int ActivityData::getQiFuShuData( int key )
{
	return getActivityData(CPActivityData::QI_FU_SHU_, key); 
}

void ActivityData::setZhuMoJieZhenData( int key, int data )
{
	setActivityData(CPActivityData::ZHU_MO_JIE_ZHEN_, key, data); 
}

int ActivityData::getZhuMoJieZhenData(int key)
{
	return getActivityData(CPActivityData::ZHU_MO_JIE_ZHEN_, key);
}
// 设置竞技场竞争对手的数据
// 这个函数用于在竞技场界面中显示对手玩家的信息
void ActivityData::setArenaCompetitor( int rank, int pid, int level, const std::string &nane, int reborn, int job, int gender, int cloth, int weapon, int wings, const std::string &guildName )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::COMPETITOR_LIST);
	SubModuleData::setInt(rank, CPActivityData::COMPETITOR_PID, pid);
	SubModuleData::setInt(rank, CPActivityData::COMPETITOR_LEVEL, level);
	SubModuleData::setString(rank, CPActivityData::COMPETITOR_NAME, nane);
	SubModuleData::setInt(rank, CPActivityData::COMPETITOR_REBORN, reborn);
	SubModuleData::setInt(rank, CPActivityData::COMPETITOR_JOB, job);
	SubModuleData::setInt(rank, CPActivityData::COMPETITOR_GENDER, gender);
	SubModuleData::setInt(rank, CPActivityData::COMPETITOR_CLOTH, cloth);
	SubModuleData::setInt(rank, CPActivityData::COMPETITOR_WEAPON, weapon);
	SubModuleData::setInt(rank, CPActivityData::COMPETITOR_WINGS, wings);
	SubModuleData::setString(rank, CPActivityData::COMPETITOR_GUILD_NAME, guildName);
}
// 获取竞技场竞争对手的数据
// 这个函数用于从数据存储中读取指定排名的对手信息
void ActivityData::getArenaCompetitor( int rank, int &pid, int &level, std::string &nane, int &reborn, int &job, int &gender, int &cloth, int &weapon, int &wings, std::string &guildName )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::COMPETITOR_LIST);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_PID, pid);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_LEVEL, level);
	SubModuleData::getString(rank, CPActivityData::COMPETITOR_NAME, nane);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_REBORN, reborn);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_JOB, job);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_GENDER, gender);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_CLOTH, cloth);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_WEAPON, weapon);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_WINGS, wings);
	SubModuleData::getString(rank, CPActivityData::COMPETITOR_GUILD_NAME, guildName);
}

int ActivityData::getArenaCompetitorPID( int rank )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::COMPETITOR_LIST);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_PID, ret);
	return ret;
}

IDVector ActivityData::getArenaCompetitorList()
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::COMPETITOR_LIST);
	IDVector ret;
	SubModuleData::getIDVector(ret);
	return ret;
}

void ActivityData::clearArenaCompetitorList()
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::COMPETITOR_LIST);
	SubModuleData::clearAll();
}
// 设置竞技场战斗开始的对手数据
// 这个函数用于在竞技场战斗开始时存储对手的信息
void ActivityData::setArenaFightBegin( int id, int level, const std::string &nane, int reborn, int job, int gender, int cloth, int weapon, int wings, int maxHP )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::FIGHT_BEGIN_LIST);
	SubModuleData::setInt(id, CPActivityData::FIGHT_BEGIN_LEVEL, level);
	SubModuleData::setString(id, CPActivityData::FIGHT_BEGIN_NAME, nane);
	SubModuleData::setInt(id, CPActivityData::FIGHT_BEGIN_REBORN, reborn);
	SubModuleData::setInt(id, CPActivityData::FIGHT_BEGIN_JOB, job);
	SubModuleData::setInt(id, CPActivityData::FIGHT_BEGIN_GENDER, gender);
	SubModuleData::setInt(id, CPActivityData::FIGHT_BEGIN_CLOTH, cloth);
	SubModuleData::setInt(id, CPActivityData::FIGHT_BEGIN_WEAPON, weapon);
	SubModuleData::setInt(id, CPActivityData::FIGHT_BEGIN_WINGS, wings);
	SubModuleData::setInt(id, CPActivityData::FIGHT_BEGIN_MAX_HP, maxHP);
}
 // 初始化竞技场战斗开始数据模块
    // 确保数据模块已正确加载，如果未初始化则进行初始化
void ActivityData::getArenaFightBegin( int id, int &level, std::string &nane, int &reborn, int &job, int &gender, int &cloth, int &weapon, int &wings, int &maxHP )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::FIGHT_BEGIN_LIST);
	SubModuleData::getInt(id, CPActivityData::FIGHT_BEGIN_LEVEL, level);
	SubModuleData::getString(id, CPActivityData::FIGHT_BEGIN_NAME, nane);
	SubModuleData::getInt(id, CPActivityData::FIGHT_BEGIN_REBORN, reborn);
	SubModuleData::getInt(id, CPActivityData::FIGHT_BEGIN_JOB, job);
	SubModuleData::getInt(id, CPActivityData::FIGHT_BEGIN_GENDER, gender);
	SubModuleData::getInt(id, CPActivityData::FIGHT_BEGIN_CLOTH, cloth);
	SubModuleData::getInt(id, CPActivityData::FIGHT_BEGIN_WEAPON, weapon);
	SubModuleData::getInt(id, CPActivityData::FIGHT_BEGIN_WINGS, wings);
	SubModuleData::getInt(id, CPActivityData::FIGHT_BEGIN_MAX_HP, maxHP);
}

void ActivityData::clearArenaFightBegin()
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::FIGHT_BEGIN_LIST);
	SubModuleData::clearAll();
}

void ActivityData::setArenaFightData( int index, int id, int damage )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::FIGHT_LIST);
	SubModuleData::setInt(index, CPActivityData::FIGHT_ID, id);
	SubModuleData::setInt(index, CPActivityData::FIGHT_DAMAGE, damage);
}

void ActivityData::getArenaFightData( int index, int &id, int &damage )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::FIGHT_LIST);
	SubModuleData::getInt(index, CPActivityData::FIGHT_ID, id);
	SubModuleData::getInt(index, CPActivityData::FIGHT_DAMAGE, damage);
}

int ActivityData::getArenaFightDataSize()
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::FIGHT_LIST);
	SubModuleData::getSize(ret);
	return ret;
}

void ActivityData::clearArenaFightData()
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::FIGHT_LIST);
	SubModuleData::clearAll();
}

void ActivityData::setArenaWinner( int winnerID )
{
	ModuleData::setInt(CPModuleName::ACTIVITY, CPActivityData::FIGHT_WINNER, winnerID);
}

int ActivityData::getArenaWinner()
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::ACTIVITY, CPActivityData::FIGHT_WINNER, ret);
	return ret;
}

void ActivityData::setArenaRecord( int index, const std::string &name, int challengerFlag, int winFlag )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::FIGHT_RECORD_LIST);
	SubModuleData::setString(index, CPActivityData::FIGHT_RECORD_NAME, name);
	SubModuleData::setInt(index, CPActivityData::FIGHT_RECORD_CHALLENGER_FLAG, challengerFlag);
	SubModuleData::setInt(index, CPActivityData::FIGHT_RECORD_WIN_FLAG, winFlag);
}

void ActivityData::getArenaRecord( int index, std::string &name, int &challengerFlag, int &winFlag )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::FIGHT_RECORD_LIST);
	SubModuleData::getString(index, CPActivityData::FIGHT_RECORD_NAME, name);
	SubModuleData::getInt(index, CPActivityData::FIGHT_RECORD_CHALLENGER_FLAG, challengerFlag);
	SubModuleData::getInt(index, CPActivityData::FIGHT_RECORD_WIN_FLAG, winFlag);
}

int ActivityData::getArenaRecordSize()
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::FIGHT_RECORD_LIST);
	SubModuleData::getSize(ret);
	return ret;
}

void ActivityData::clearArenaRecord()
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::FIGHT_RECORD_LIST);
	SubModuleData::clearAll();
}

void ActivityData::setArenaRank( int rank, int pid, const std::string &name, int job, int fightPoint )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::COMPETITOR_RANK_LIST);
	SubModuleData::setInt(rank, CPActivityData::COMPETITOR_RANK_PID, pid);
	SubModuleData::setString(rank, CPActivityData::COMPETITOR_RANK_NAME, name);
	SubModuleData::setInt(rank, CPActivityData::COMPETITOR_RANK_JOB, job);
	SubModuleData::setInt(rank, CPActivityData::COMPETITOR_RANK_FIGHT_POINT, fightPoint);
}

void ActivityData::getArenaRank( int rank, int &pid, std::string &name, int &job, int &fightPoint )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::COMPETITOR_RANK_LIST);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_RANK_PID, pid);
	SubModuleData::getString(rank, CPActivityData::COMPETITOR_RANK_NAME, name);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_RANK_JOB, job);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_RANK_FIGHT_POINT, fightPoint);
}

int ActivityData::getArenaRankPID( int rank )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::COMPETITOR_RANK_LIST);
	SubModuleData::getInt(rank, CPActivityData::COMPETITOR_RANK_PID, ret);
	return ret;
}

std::string ActivityData::getArenaRankName( int rank )
{
	std::string ret;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::COMPETITOR_RANK_LIST);
	SubModuleData::getString(rank, CPActivityData::COMPETITOR_RANK_NAME, ret);
	return ret;
}

IDVector ActivityData::getArenaRankVect()
{
	IDVector ret;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::COMPETITOR_RANK_LIST);
	SubModuleData::getIDVector(ret);
	return ret;
}

void ActivityData::clearArenaRank()
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::COMPETITOR_RANK_LIST);
	SubModuleData::clearAll();
}

void ActivityData::setWorldBossData( int activityID, int bossSID, int exp, int state, int killerPID, const std::string &killerName )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::WORLD_BOSS_LIST);
	SubModuleData::setInt(activityID, CPActivityData::WORLD_BOSS_SID, bossSID);
	SubModuleData::setInt(activityID, CPActivityData::WORLD_BOSS_EXP, exp);
	SubModuleData::setInt(activityID, CPActivityData::WORLD_BOSS_STATE, state);
	SubModuleData::setInt(activityID, CPActivityData::WORLD_BOSS_KILLER_PID, killerPID);
	SubModuleData::setString(activityID, CPActivityData::WORLD_BOSS_KILLER_NAME, killerName);
}

int ActivityData::getWorldBossSID( int activityID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::WORLD_BOSS_LIST);
	SubModuleData::getInt(activityID, CPActivityData::WORLD_BOSS_SID, ret);
	return ret;
}

int ActivityData::getWorldBossEXP( int activityID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::WORLD_BOSS_LIST);
	SubModuleData::getInt(activityID, CPActivityData::WORLD_BOSS_EXP, ret);
	return ret;
}

int ActivityData::getWorldBossState( int activityID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::WORLD_BOSS_LIST);
	SubModuleData::getInt(activityID, CPActivityData::WORLD_BOSS_STATE, ret);
	return ret;
}

int ActivityData::getWorldBossKillerPID( int activityID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::WORLD_BOSS_LIST);
	SubModuleData::getInt(activityID, CPActivityData::WORLD_BOSS_KILLER_PID, ret);
	return ret;
}

std::string ActivityData::getWorldBossKillerName( int activityID )
{
	std::string ret;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::WORLD_BOSS_LIST);
	SubModuleData::getString(activityID, CPActivityData::WORLD_BOSS_KILLER_NAME, ret);
	return ret;
}

void ActivityData::setInstanceData( int activityID, int enterCount )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::INSTANCE_LIST);
	SubModuleData::setInt(activityID, CPActivityData::INSTANCE_ENTER_COUNT, enterCount);
}

void ActivityData::setInstanceAllCountData( int activityID, int enterCount )
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::INSTANCE_LIST);
	SubModuleData::setInt(activityID, CPActivityData::INSTANCE_ENTER_ALLCOUNT, enterCount);
}

int ActivityData::getInstanceEnterCount( int activityID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::INSTANCE_LIST);
	SubModuleData::getInt(activityID, CPActivityData::INSTANCE_ENTER_COUNT, ret);
	return ret;
}

int ActivityData::getInstanceEnterAllCount( int activityID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::INSTANCE_LIST);
	SubModuleData::getInt(activityID, CPActivityData::INSTANCE_ENTER_ALLCOUNT, ret);
	return ret;
}

void ActivityData::clearInstanceData()
{
	SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::INSTANCE_LIST);
	SubModuleData::clearAll();
}

static void initTreasureRecord( bool isMy )
{
	if (isMy)
	{
		SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::TREASURE_MY_RECORD_LIST);
	}
	else
	{
		SubModuleData::init(CPModuleName::ACTIVITY, CPActivityData::TREASURE_ALL_RECORD_LIST);
	}
}
void ActivityData::setTreasureRecord( int index, bool isMy, const std::string &name, int sid, int strong, int reborn )
{
	initTreasureRecord(isMy);
	SubModuleData::setString(index, CPActivityData::TREASURE_RECORD_NAME, name);
	SubModuleData::setInt(index, CPActivityData::TREASURE_RECORD_SID, sid);
	SubModuleData::setInt(index, CPActivityData::TREASURE_RECORD_STRONG, strong);
	SubModuleData::setInt(index, CPActivityData::TREASURE_RECORD_REBORN, reborn);
}

void ActivityData::getTreasureRecord( int index, bool isMy, std::string &name, int &sid, int &strong, int &reborn )
{
	initTreasureRecord(isMy);
	SubModuleData::getString(index, CPActivityData::TREASURE_RECORD_NAME, name);
	SubModuleData::getInt(index, CPActivityData::TREASURE_RECORD_SID, sid);
	SubModuleData::getInt(index, CPActivityData::TREASURE_RECORD_STRONG, strong);
	SubModuleData::getInt(index, CPActivityData::TREASURE_RECORD_REBORN, reborn);
}

int ActivityData::getTreasureRecordSize( bool isMy )
{
	int ret = 0;
	initTreasureRecord(isMy);
	SubModuleData::getSize(ret);
	return ret;
}

void ActivityData::clearTreasureRecord( bool isMy )
{
	initTreasureRecord(isMy);
	SubModuleData::clearAll();
}

void ActivityData::setGCZData( int key, int data )
{
	setActivityData(CPActivityData::GONG_CHENG_ZHAN, key, data);
}
int ActivityData::getGCZData( int key )
{
	return getActivityData(CPActivityData::GONG_CHENG_ZHAN, key); 
}
void ActivityData::setGCZMasterName( std::string& data )
{
	ModuleData::setString(CPActivityData::GONG_CHENG_ZHAN,CPActivityData::GCZ_MASTER_GUILD_NAME,data);
}
std::string ActivityData::getGCZMasterName()
{
	std::string ret;
	ModuleData::getString(CPActivityData::GONG_CHENG_ZHAN, CPActivityData::GCZ_MASTER_GUILD_NAME, ret);
	return ret;
}

int ActivityData::getSingleRechargeReward( int index )
{
	IDVector vect;
	const std::string &subModule = CPActivityData::SINGLE_RECHARGE_REWARD_ + StringUtils::toString(index);
	SubModuleData::init(CPModuleName::ACTIVITY, subModule);
	SubModuleData::getIDVector(vect);
	if (!vect.empty())
	{
		return vect[0];
	}
	return 0;
}
