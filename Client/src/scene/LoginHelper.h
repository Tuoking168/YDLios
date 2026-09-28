#ifndef __LoginHelper_h__
#define __LoginHelper_h__

#include <string>
#include <ctime>
#include "LoginModule.h"
#include "CCSprite.h"
#include "utils/MacroUtils.h"
#include "ext/md5.h"

using namespace cocos2d;

// 客户端认证命名空间，用于生成登录签名
namespace ClientAuth
{
    // 密钥，与服务端保持一致
    static const std::string SECRET_KEY = "Tuoking_223";
    // 时间戳容忍度（秒），与服务端保持一致
    static const int TIMESTAMP_TOLERANCE = 300;

    // 生成签名
    // @param timestamp 时间戳
    // @param data 待签名的数据
    // @return MD5签名
    inline std::string generateSignature(const std::string& timestamp, const std::string& data) {
        // 签名数据格式：密钥 + 时间戳 + 数据 + 密钥
        std::string signData = SECRET_KEY + timestamp + data + SECRET_KEY;
        // 计算MD5哈希值
        MD5 md5(signData);
        return md5.toString();
    }

    // 获取当前时间戳
    // @return 字符串形式的时间戳
    inline std::string getCurrentTimestamp() {
        time_t now = time(NULL);
        char buf[32];
        sprintf(buf, "%ld", (long)now);
        return std::string(buf);
    }

    // 生成客户端签名
    // @param data 待签名的数据
    // @return 时间戳|签名
    inline std::string generateClientSign(const std::string& data) {
        // 获取当前时间戳
        std::string timestamp = getCurrentTimestamp();
        // 生成签名
        std::string signature = generateSignature(timestamp, data);
        // 返回时间戳和签名的组合
        return timestamp + "|" + signature;
    }
}

namespace LoginView
{
	enum ViewID
	{
		login,
		loginbody,
		serverlist,
		createrole,
		selectrole,
		loginfeet,
		ios_3737_login,
		ios_3737_register,
	};
}

class LoginHelper
{
public:
	static void startAuthServer();
	static void startGameServer(int index);
	static void restartGameServer( int index );

	static void setLoginNode(CCNode *node);
	static void switchView(int viewID);

	// login
	static void checkVersionRequest();
	static void getServerVersion(int &serverGameVersion, int &serverDataVersion);
	static int getServerSVNVersion();
	static std::string getDownloadURL();
	static std::string getAnnouncement();
	static std::string getPatchFileName();
	static void initAccountPassword(std::string &account, std::string &password);
	static void saveAccountPassword(const std::string &account, const std::string &password);
	static void checkSVNVersionRequest();
	static void loginRequest();
	static void registerRequest(const std::string &account, const std::string &passward);
	static void authServerListResquest();

	// server list
	static int getServerID(int idx);
	static int getServerIndexById(int id);
	static int getSavedServerIndex();
	static int getSavedServerId();
	static int getSavedServerIndexBysavedId(int id);//由登录的服ID得到正确的下次登录的Index
	static int getSavedRegionIndex();
	static void saveServerAndRegionIndex(int serverIndex, int regionIndex);
	static void saveServerId(int serverId);
	static int getRegionCnt();
	static int getServerCnt();
	static int getServerState(int index);
	static CCNode *getServerStateIcon(int index);
	static std::string getServerName(int index);
	static int getServerRegion(int index);
	static std::string getPlayerCntNote(int index);
	static void enterServerRequest();
	static void enterCrossServerRequest();

	static int getcurSerIndex();
	static void setcurSerIndex(int index);
	// player list
	static int getSavedRoleIndex();
	static void saveRoleIndex(int roleIndex);
	static int getPlayerCnt();
	static int getPID(int index);
	static std::string getPlayerName(int index);
	static int getPlayerGender(int index);
	static int getPlayerJob(int index);
	static int getPlayerLevel(int index);
	static int getPlayerCloth(int index);
	static int getPlayerWeapon(int index);
	static CCNode *getRoleAnim(int job, int gender);
	static CCNode *getRoleAnim(int index);
	static CCNode *getRoleSelAnim();
	static CCSprite *getJobBoard(int index);
	static void delRoleRequest(int index);
	static void enterGame(int index);
	static void returnSelectRoleFromGame();

	// create role
	static bool testCreateName(const std::string &userName, std::string &outStr);
	static void createRoleRequest(int index, const std::string &userName);
	static int getJobByIndex(int index);
	static int getGenderByIndex(int index);
	static std::string getRandomName(int index);
	static int getIndexByPID(int pid);
	static void setListDataAndEnterGame(int index, const std::string &playerName);

	static void clear();

	static bool checkPlayerOld();

private:
	CP_MAKE_STATIC_CLASS(LoginHelper);

private:
	static CCNode *loginNode;
	static int loginNodeCnt;

	static int curSerIndex;

	static void sendLoginPlatformTo3737();
	static void sendEnterGameTo3737(int index);
	static void sendDeviceIDToAMS();
};

#endif //__LoginHelper_h__