#ifndef __GuildData_h__
#define __GuildData_h__

#include <string>
#include "LoginModule.h"
#include "CCSprite.h"
#include "MsgGuild.h"

using namespace cocos2d;

class GuildData
{
public:
	static bool hasGuild();
	static void clear();

	//My Guild Info
	static int getMyGuildID();
	static int getMyGuildRank();
	static std::string getMyGuildName();
	static int getMyGuildLevel();
	static std::string getMyGuildMasterName();
	static int getMyGuildMasterID();
	static int getMyGuildMemberCount();
	static int getMyGuildMaxMember();
	static int getMyGuildContribution();
	static int getMyGuildMoney();

	static int getMyJob();
	static int getMyNickname();
	static int getMyContribution();

	// Guild list
	static int getGuildPage();
	static int getGuildMaxPage();
	static int getPerPage();
	static int getGuildCnt();
	static int getRankByIndex(int index);
	static int getGuildID(int rank);
	static std::string getGuildName(int rank);
	static int getGuildLevel(int rank);
	static int getGuildState(int rank);
	static std::string getGuildMasterName(int rank);
	static int getGuildMasterID(int rank);
	static int getGuildMemberCount(int rank);
	static int getGuildMaxMember(int level);

	//Guild Member List
	static int getGuildMemberPage();
	static int getGuildMemberMaxPage();
	static int getGuildMemberCnt();
	static int getGuildMemberPID(int index);
	static std::string getGuildMemberName(int index);
	static int getGuildMemberLevel(int index);
	static int getGuildMemberRank(int index);
	static int getGuildMemberArenaRank(int index);
	static int getGuildMemberJob(int index);
	static int getGuildMemberNickname(int index);
	static int getGuildMemberContribution(int index);
	static int getGuildMemberTodayContribution(int index);
	static std::string getGuildMemberLastonline(int index);

	//application list
	static int getGuildApplicationPID(int index);
	static std::string getGuildApplicationName(int index);
	static int getGuildApplicationLevel(int index);
	static int getGuildApplicationCnt();
	//nickname list
	static int getGuildNicknameJob(int index);
	static std::string getGuildNickname(int index);
	static int getGuildNicknameCnt();
	// create role
	static int getIndexByPID(int pid);

	static int getJobReward(int job);
	static int getJobRewardCount(int job);
	static std::string getDefaultNickname(int job);

	static void changeMemberNickname(int job);

	//UI
	static void setNicknameTipPostion(CCPoint tSize);
	static CCPoint getNicknameTipPostion();
	static void setNicknameSelectPid(int index);
	static int getNicknameSelectPid();
	
	//All Guild Member List
	static int getGuildAllMemberCnt();
	static int getGuildAllMemberPID(int index);
	static std::string getGuildAllMemberName(int index);
	static int getGuildAllMemberLevel(int index);
	static int getGuildAllMemberRank(int index);
	static int getGuildAllMemberArenaRank(int index);
	static int getGuildAllMemberJob(int index);
	static int getGuildAllMemberNickname(int index);
	static int getGuildAllMemberContribution(int index);
	static int getGuildAllMemberTodayContribution(int index);
	static std::string getGuildAllMemberLastonline(int index);

	//gcz attack guild List
	static int getGCZAttackGuildCnt();
	static std::string getGCZAttackGuildName(int index);
	static int getGCZLastAttackGuildCnt();
	static std::string getGCZLastAttackGuildName(int index);

	static void setGuildProp( int key, int value );
	static int getGuildProp( int key );
	static void setGuildStringProp( int key, std::string value );
	static std::string getGuildStringProp( int key );

	//guildBuilding  List
	static void  setGuildTanXianData(int index, int sid);
	static int getGuildTanXianData(int index);
	static void clearGuildTanXianData();

private:
	GuildData();
	GuildData(const GuildData &);
	GuildData &operator=(const GuildData &);  
	~GuildData();

};

#endif //__GuildData_h__