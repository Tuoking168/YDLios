#ifndef __SOCIAL_DATA_H__
#define __SOCIAL_DATA_H__

#include <vector>
#include <string>
#include <map>

class SocialData
{
public:
	static bool isFriend(const int pid);
	static bool isMaster(const int pid);
	static bool isApprentice(const int pid);
	static bool isCouple(const int pid);
	static bool isEnemy(const int pid);


	static int getFriendDataCnt();
	static void addFriendData(int pid,const std::string& name);
	static void rmvFriendData(int pid,const std::string& name = "");
	static std::string getFriendName(int pid);
	static std::map<int ,std::string>& getFriendList();

	static int getMasterDataCnt();
	static void addMasterData(int pid,const std::string& name);
	static void rmvMarsterData(int pid,const std::string& name = "");
	static std::string getMasterName(int pid);
	static std::map<int ,std::string>& getMasterList();

	static int getApprenticeDataCnt();
	static void addApprenticeData(int pid,const std::string& name);
	static void rmvApprenticeData(int pid,const std::string& name = "");
	static std::string getApprenticeName(int pid);
	static std::map<int ,std::string>& getApprenticeList();
public:
	struct RelationData
	{
		RelationData()
		{
			pid = 0;
			name = "";
			gender = 0;
			clazz = 0;
			level = 0;
		}
		int pid;
		std::string	name;
		char gender;
		char clazz;
		int level;
	};

	static void sortRelationList(int flag);
	typedef std::vector<RelationData> RelationList;
	static RelationList mFriends;
	static RelationList mMasters;
	static RelationList mApprentices;
	static RelationList mCouples;
	static RelationList mEnemies;

	static RelationList mMasterList;
	static RelationList mApprenticeList;

	static int delPid;
	static std::string delName;
	static int delType;

	static int masterPid;
	static std::string masterName;
	static int apprenticePid;
	static std::string apprenticeName;

	static int bridegroomPid;
	static std::string bridegroomName;
	static int bridePid;
	static std::string brideName;

	static std::string notifyMsgKey;
	static std::string notifyMsgValue;

	static std::map<int ,std::string> addFriendMap;
	static std::map<int ,std::string> addMasterMap;
	static std::map<int ,std::string> addApprenticeMap;
};

#endif//__SOCIAL_DATA_H__