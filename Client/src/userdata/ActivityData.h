#ifndef __ActivityData_h__
#define __ActivityData_h__

#include "utils/MacroUtils.h"
#include <string>
#include <vector>

typedef std::vector<int> IDVector;
class ActivityData
{
public:
	static int getActivityID(const std::string &idName);
	static void clear();

	// common data
	static void setState(int timeID, int state);
	static int getState(int timeID);

	static void setUnstartID(int unstartID);
	static int getUnstartID();

	static void setNotFinishCnt(int activityID, int cnt);
	static int getNotFinishCnt(int activityID);

	static void setExData(int activityID, int dataX, int dataY, int dataZ);
	static void getExData(int activityID, int &dataX, int &dataY, int &dataZ);
	static int getExDataX(int activityID);
	static int getExDataY(int activityID);
	static int getExDataZ(int activityID);

	static void setWorldTime(int worldTime);
	static int getWorldTime();

	static void setWorldBeginTime(int begintime);
	static int getWorldBeginTime();
	static int getWorldBeginDays();

	static void setHideList(const IDVector &vect);
	static bool isHide(int ctrlID);
	static IDVector getHideList();

	static void setWorldIntProp(int id, int index, int data);
	static void setWorldIntProp(int id, int index, int data, int version);
	static void setWorldStringProp(int id, int index, const std::string &data);
	static void setWorldStringProp(int id, int index, const std::string &data, int version);
	static int getWorldIntProp(int id, int index);
	static std::string getWorldStringProp(int id, int index);
	static int getWorldIntPropVersion(int id);
	static int getWorldStringPropVersion(int id);
	static void clearWorldProp(int id);

	// mo bai
	static void setMoBaiData(int key, int data);
	static int getMoBaiData(int key);

	// cai shen chuang guan
	static void setCaiShenChuangGuanData(int key, int data);
	static int getCaiShenChuangGuanData(int key);

	// mei nv hu song
	static void setMeiNvHuSongData(int key, int data);
	static int getMeiNvHuSongData(int key);

	// qi fu shu
	static void setQiFuShuData(int key, int data);
	static int getQiFuShuData(int key);

	// zhu mo jie zhen
	static void setZhuMoJieZhenData(int key, int data);
	static int getZhuMoJieZhenData(int key);

	// arena
	// 静态函数声明：设置竞技场竞争对手数据
	static void setArenaCompetitor(int rank, int pid, int level, const std::string &nane, int reborn, int job, int gender, int cloth, int weapon, int wings, const std::string &guildName);
	static void getArenaCompetitor(int rank, int &pid, int &level, std::string &nane, int &reborn, int &job, int &gender, int &cloth, int &weapon, int &wings, std::string &guildName);
	static int getArenaCompetitorPID(int rank);
	static IDVector getArenaCompetitorList();
	static void clearArenaCompetitorList();
	// 静态函数声明：设置竞技场战斗开始的对手数据
// static 关键字表示这是一个类静态函数，可以通过类名直接调用
	static void setArenaFightBegin(int id, int level, const std::string &nane, int reborn, int job, int gender, int cloth, int weapon, int wings, int maxHP);
	static void getArenaFightBegin(int id, int &level, std::string &nane, int &reborn, int &job, int &gender, int &cloth, int &weapon, int &wings, int &maxHP);
	static void clearArenaFightBegin();

	static void setArenaFightData(int index, int id, int damage);
	static void getArenaFightData(int index, int &id, int &damage);
	static int getArenaFightDataSize();
	static void clearArenaFightData();

	static void setArenaWinner(int winnerID);
	static int getArenaWinner();

	static void setArenaRecord(int index, const std::string &name, int challengerFlag, int winFlag);
	static void getArenaRecord(int index, std::string &name, int &challengerFlag, int &winFlag);
	static int getArenaRecordSize();
	static void clearArenaRecord();

	static void setArenaRank(int rank, int pid, const std::string &name, int job, int fightPoint);
	static void getArenaRank(int rank, int &pid, std::string &name, int &job, int &fightPoint);
	static int getArenaRankPID(int rank);
	static std::string getArenaRankName(int rank);
	static IDVector getArenaRankVect();
	static void clearArenaRank();

	// boss
	static void setWorldBossData(int activityID, int bossSID, int exp, int state, int killerPID, const std::string &killerName);
	static int getWorldBossSID(int activityID);
	static int getWorldBossEXP(int activityID);
	static int getWorldBossState(int activityID);
	static int getWorldBossKillerPID(int activityID);
	static std::string getWorldBossKillerName(int activityID);

	// instance
	static void setInstanceData(int activityID, int enterCount);
	static int getInstanceEnterCount(int activityID);
	static void setInstanceAllCountData(int activityID, int enterCount);
	static int getInstanceEnterAllCount(int activityID);
	static void clearInstanceData();

	// treasure hunt
	static void setTreasureRecord(int index, bool isMy, const std::string &name, int sid, int strong, int reborn);
	static void getTreasureRecord(int index, bool isMy, std::string &name, int &sid, int &strong, int &reborn);
	static int getTreasureRecordSize(bool isMy);
	static void clearTreasureRecord(bool isMy);

	//攻城战
	static void setGCZData( int key, int data );
	static int getGCZData( int key );
	static void setGCZMasterName( std::string& data );
	static std::string getGCZMasterName();

	// single recharge
	static int getSingleRechargeReward(int index);

private:
	CP_MAKE_STATIC_CLASS(ActivityData);
};
#endif //__ActivityData_h__