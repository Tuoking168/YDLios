#ifndef	___USER_DATA_____
#define ___USER_DATA_____


#include "cocos2d.h"
#include "CommonType.h"
#include "mapdata/MapData.h"
#include "event/EventDispatcher.h"
#include "userdata/netdata/NetItem.h"
#include "MsgQuest.h"
#include "MsgShop.h"
#include "EntityDefinition.h"

#include <string>
#include <vector>
#include <queue>
#include <pthread.h>


class GhostManager;
class GameRole;
class PixesMap;
class UserItemData;
class UserPetData;
class OtherRole;

struct NetMap
{
	NetMap()
		:mID(0)
	{}
	std::string mMapFile;
	std::string mName;
	int mID;
};

struct TaskTip
{
	TaskTip()
		:id(0)
		,fontsize(10)
		,c(ccWHITE)
	{}
	int id;
	std::string str;
	ccColor3B c;
	int fontsize;
};

class UserData
{
public:
	const static int CARRER_ZS	= Entity::etj_zs;
	const static int CARRER_FS	= Entity::etj_fs;
	const static int CARRER_DS	= Entity::etj_ds;
	const static int CARRER_OMNI	= Entity::etj_omni;

	const static int SEX_MALE	= Entity::etgd_male;
	const static int SEX_FEMALE	= Entity::etgd_female;

public:
	GameRole* m_pMainRole;
	OtherRole* m_pOtherRole;
	PixesMap* m_pPixesMap;
	GhostManager* m_pGhostManager;

	std::map<int,NetItem*> mOthersItems;
	std::map<int,bool>     mOthersFlags;
	
	std::vector<ShopData> mShopItems;

	std::string		m_gameVersion;
	char			m_bloadCompleted;

public:
	bool			m_bCharListRecieved;
	bool			m_bAttackModeChanged;
	bool			m_bLevelChanged;
	bool			m_bExperienceChanged;
	unsigned int	m_nNpcTalkId;
	std::string		m_unCreatRoleTip;
	std::string		m_strLocalAlertMsg;

	int				m_nPingNum;

	bool			m_bIsFloatPanel;
	bool			m_bIsMainPanel;

	bool            m_changeEquipMsg;//收到需要替换装备的提示消息
	int             ChangePos;
	int             ChangeTypeID;
	std::string     ChangemName;

	bool			m_skillSelectIce;
	int				m_itemKeyUsePos;
	int				m_itemKeyUseID;
	int				mPayType;

	int			m_whetherBanyueUse;
	int			m_whetherChishaUse;
public:
	static long m_currenttime;
	long m_pingtime;

	NetMap mMap;

	typedef std::vector< int > mQuestListID;
	mQuestListID questlist;

	typedef std::vector< npcFunction > mfunctionNPC;
	mfunctionNPC functionlist;

public:
	UserData();
	~UserData();
	
	static long millisecondNow();
	long getTime();
	
	void addMapConns();
	void enterGameRequest();

	void clearOtherRole();

	void switch2GameScene();
	void releaseGameData();
	void UpdStoneArray();

	UserItemData* getUserItemData();
	UserPetData* getUserPetData();

	static int getemptyFast();
	static void initSetting();

public:
	static void loadData();
	static void saveData();

	// setter
	static void setIntData(const std::string &key, int data);
	static void setIntData(int pid, const std::string &key, int data);
	static void setIntData(int pid, const std::string &key, int id, int data);
	static void setStringData(const std::string &key, const std::string &data);
	static void setStringData(int pid, const std::string &key, const std::string &data);
	static void setStringData(int pid, const std::string &key, int id, const std::string &data);

	static void setStringData(const std::string &key, const std::string &data,int tag);
	static std::string getStringData(const std::string &key,int tag);

	// getter
	static int getIntData(const std::string &key);
	static int getIntData(int pid, const std::string &key);
	static int getIntData(int pid, const std::string &key, int id);
	static std::string getStringData(const std::string &key);
	static std::string getStringData(int pid, const std::string &key);
	static std::string getStringData(int pid, const std::string &key, int id);

	static int getIntDataForSeverPick( const std::string &key );

	// clear
	static void clear(int pid);

private:
	void addMapConnGhost(NetMapConn*);
	void releaseDataForTransfer();
	void releaseModuleData();
	void releaseUIData();

private:
	UserItemData* userItemData;
	UserPetData*  userPetData;
};




#endif //___USER_DATA_____