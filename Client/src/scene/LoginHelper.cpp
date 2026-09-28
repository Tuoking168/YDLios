#include "LoginHelper.h"
#include "cocos2d.h"
#include "MsgAuth.h"
#include "MsgLogin.h"
#include "Login.h"
#include "ErrorDefinition.h"
#include "SceneDefinition.h"
#include "UserDataModule.h"
#include "ModuleData.h"
#include "SceneFactory.h"
#include "NotificationHelper.h"
#include "PlatformDefinition.h"

#include "ext/CCFlashAnimation.h"

#include "controls/CPRichText.h"

#include "element/AnimElement.h"
#include "element/ElementDefinition.h"

#include "event/CPEventHelper.h"

#include "utils/StringUtils.h"
#include "utils/RichTextUtils.h"

#include "res/CPAnimationManager.h"

#include "script/LuaWrapper.h"

#include "logic/platform/IPlatform.h"

#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userData/SystemData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/ActivityData.h"

#include "network/HandleMessage.h"
#include "network/MsgListener.h"

#include "MsgGMaster.h"
#include "ext/md5.h"
#include "../../ios/channel/common/ChannelHelper.h"

using namespace cocos2d;

std::string		gASIP = "";


#define TAG_LOGIN_SUB_VIEW	7

//static std::string getASIP()//??????????ip???
//{
// 	if (gASIP.empty())
//	{
//		int channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
//		CPLua->push(channelID);
//		CPLua->call("gameconf", "get_ip", 1, 1);
//		CPLua->pop(gASIP);
//	}
//	return gASIP;
//}
static std::string getASIP()
{
    if (gASIP.empty())
    {
        // ???????Lua???????????????IP?          Ó²±àÂëipµØÖ·
     //   gASIP = "182.254.146.181";
	 //  gASIP = "111.228.35.62";
	   gASIP = "127.0.0.1";
    }
    return gASIP;
}
//////////LoginHelper///////////////////////////////////////////////
CCNode *LoginHelper::loginNode = NULL;
int LoginHelper::loginNodeCnt = 0;
int LoginHelper::curSerIndex = 0;

void LoginHelper::startAuthServer()
{
	const std::string &asIP = getASIP();
	// int asPort = SystemData::getConfigInt("port");  // ?????
    int asPort = 7318;  // ?????????

	//HandleMessage::s_msglistener->startServer(asIP, asPort);
	HandleMessage::startAMSServer(asIP, asPort);
	NotificationHelper::checkNetState();
}

void LoginHelper::startGameServer( int index )
{
	std::string ip;
	int port = 0;

	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	SubModuleData::getString(index, CPLoginData::SERVER_IP, ip);
	SubModuleData::getInt(index, CPLoginData::SERVER_PORT, port);

	int channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	/*if (channelID == ChannelID::mengcheng)
	{
		CPPlatformMnger.getPlatform()->selectGameSever(index);
		ip = CPPlatformMnger.getStringData(CPPlatformData::PROXY_SERVER_ID);
		std::string strPort = CPPlatformMnger.getStringData(CPPlatformData::PROXY_SERVER_PORT);
		port = SystemData::stringToInt(strPort);
		CCLog("#######gasip: %s\n", ip.c_str());
		CCLog("#######gasip: %d\n", port);
	}*/
	
	//HandleMessage::s_msglistener->startServer(ip, port);
	HandleMessage::startGSServer(ip, port);
	NotificationHelper::checkNetState();

	int serverID = 0;
	SubModuleData::getInt(index, CPLoginData::SERVER_ID, serverID);
	CPPlatformMnger.setIntData(CPPlatformData::SERVER_ID, serverID);
	CPPlatformMnger.setIntData(CPPlatformData::SERVER_INDEX, index);

	std::string serverName;
	SubModuleData::getString(index, CPLoginData::SERVER_NAME, serverName);
	CPPlatformMnger.setStringData(CPPlatformData::SERVER_NAME, serverName);

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	//============================3737
	bool requestType_is_post=true;//????get???????post???
	if (requestType_is_post)
	{
		CCHttpRequest* request = new CCHttpRequest();//???????????
		int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
		string str0 = "http://huolug.com/gameapi/api.game.reg.php";
		string ac = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"ac_loginGame"));//ac
		string uname = UserData::getStringData(CPUserData::ACCOUNT);;//uname
		string utime = StringUtils::toString(ActivityData::getWorldTime());//utime
		string gid = "13";//gid
		string sid = StringUtils::toString(serverID);
		string str13 = "";//sign
		string KEY = "ydl_bugnfrrlj847u";
		// uname+upwd+umail+utime+gid+sid+uaid+uwid+uadid+usite+ umacid +KEY)
		//	std::string str_md5 = str2+str3+str4+str5+str6+str7+str8+str9+str10+str11+str12+"ydl_bugnfrrlj847u";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		std::string str_md5 = uname+gid+sid+utime+KEY ;
		str13 = MD5::MD5(str_md5).toString();
#endif
		// 		string str = "ac=1&uname=zhangliumang&upwd=123456&umail=liumang@163.com&utime=1&gid=13&sid=1&uaid=1&uwid=1&uadid=1&usite=1&umacid=1"
		// 			+"&sign=6880f782f6fe3658f0922702af8b6e31";
		string strac = "ac=";
		string struser="&uname=";
		string strpsw="&upwd=";
		string strumail = "&umail=";
		string strutime = "&utime=";
		string strgid = "&gid=";
		string strsid = "&sid=";
		string strsign = "&sign=";

		string str_data = strac+ac+struser+uname+strutime+utime+strgid+gid+strsid+sid+strsign+str13;
		request->setUrl(str0.c_str());//?????????url??username??password?????????url??
		request->setRequestData(str_data.c_str(),strlen(str_data.c_str()));
		request->setRequestType(CCHttpRequest::kHttpPost);//?????Post??
//		request->setResponseCallback(this, httpresponse_selector(Login_3737::onHttpRequestCompleted));//???????????
//		request->setTag("Post test");
		CCHttpClient::getInstance()->send(request);//????????
		request->release();//???????
	}
#endif
}

void LoginHelper::restartGameServer( int index )
{
	std::string ip;
	int port = 0;

	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	SubModuleData::getString(index, CPLoginData::SERVER_IP, ip);
	SubModuleData::getInt(index, CPLoginData::SERVER_PORT, port);

	int channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	/*if (channelID == ChannelID::mengcheng)
	{
	CPPlatformMnger.getPlatform()->selectGameSever(index);
	ip = CPPlatformMnger.getStringData(CPPlatformData::PROXY_SERVER_ID);
	std::string strPort = CPPlatformMnger.getStringData(CPPlatformData::PROXY_SERVER_PORT);
	port = SystemData::stringToInt(strPort);
	CCLog("#######gasip: %s\n", ip.c_str());
	CCLog("#######gasip: %d\n", port);
	}*/

	//HandleMessage::s_msglistener->startServer(ip, port);
	HandleMessage::restartGSServer(ip, port);
	NotificationHelper::checkNetState();

	int serverID = 0;
	SubModuleData::getInt(index, CPLoginData::SERVER_ID, serverID);
	CPPlatformMnger.setIntData(CPPlatformData::SERVER_ID, serverID);
	CPPlatformMnger.setIntData(CPPlatformData::SERVER_INDEX, index);

	std::string serverName;
	SubModuleData::getString(index, CPLoginData::SERVER_NAME, serverName);
	CPPlatformMnger.setStringData(CPPlatformData::SERVER_NAME, serverName);

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	//============================3737
	bool requestType_is_post=true;//????get???????post???
	if (requestType_is_post)
	{
		CCHttpRequest* request = new CCHttpRequest();//???????????
		int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
		string str0 = "http://huolug.com/gameapi/api.game.reg.php";
		string ac = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"ac_loginGame"));//ac
		string uname = UserData::getStringData(CPUserData::ACCOUNT);;//uname
		string utime = StringUtils::toString(ActivityData::getWorldTime());//utime
		string gid = "13";//gid
		string sid = StringUtils::toString(serverID);
		string str13 = "";//sign
		string KEY = "ydl_bugnfrrlj847u";
		// uname+upwd+umail+utime+gid+sid+uaid+uwid+uadid+usite+ umacid +KEY)
		//	std::string str_md5 = str2+str3+str4+str5+str6+str7+str8+str9+str10+str11+str12+"ydl_bugnfrrlj847u";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		std::string str_md5 = uname+gid+sid+utime+KEY ;
		str13 = MD5::MD5(str_md5).toString();
#endif
		// 		string str = "ac=1&uname=zhangliumang&upwd=123456&umail=liumang@163.com&utime=1&gid=13&sid=1&uaid=1&uwid=1&uadid=1&usite=1&umacid=1"
		// 			+"&sign=6880f782f6fe3658f0922702af8b6e31";
		string strac = "ac=";
		string struser="&uname=";
		string strpsw="&upwd=";
		string strumail = "&umail=";
		string strutime = "&utime=";
		string strgid = "&gid=";
		string strsid = "&sid=";
		string strsign = "&sign=";

		string str_data = strac+ac+struser+uname+strutime+utime+strgid+gid+strsid+sid+strsign+str13;
		request->setUrl(str0.c_str());//?????????url??username??password?????????url??
		request->setRequestData(str_data.c_str(),strlen(str_data.c_str()));
		request->setRequestType(CCHttpRequest::kHttpPost);//?????Post??
		//		request->setResponseCallback(this, httpresponse_selector(Login_3737::onHttpRequestCompleted));//???????????
		//		request->setTag("Post test");
		CCHttpClient::getInstance()->send(request);//????????
		request->release();//???????
	}
#endif
}

void LoginHelper::setLoginNode( CCNode *node )
{
	if (node)
	{
		loginNodeCnt++;
	}
	else
	{
		loginNodeCnt--;
		if (loginNodeCnt > 0)
		{
			return;
		}
	}

	loginNode = node;
}

void LoginHelper::switchView( int viewID )
{
	if (loginNode)
	{
		CCNode *node = NULL;
		switch (viewID)
		{
		case LoginView::login:
			node = LoginFace::create();
			break;
		case LoginView::ios_3737_login:
			node = Login_3737::create();
			break;
		case LoginView::ios_3737_register:
			node = Register_3737::create();
			break;
		case LoginView::loginbody:
			node = LoginBody::create();
			break;
		case LoginView::loginfeet:
			node = LoginFeet::create();
			break;
		case LoginView::serverlist:
			node = ServerList::create();
			break;
		case LoginView::createrole:
			node = CreateRole::create();
			break;
		case LoginView::selectrole:
			node = SelectRole::create();
		default:
			break;
		}

		if (node)
		{
			CCNode *child = loginNode->getChildByTag(TAG_LOGIN_SUB_VIEW);
			if (child)
			{
				child->removeFromParentAndCleanup(true);
			}
			loginNode->addChild(node, 0, TAG_LOGIN_SUB_VIEW);
		}
	}
	else
	{
		CCLog(">>>Error:LoginHelper::switchView, loginNode = NULL!");
	}
}

void LoginHelper::checkVersionRequest()
{
	int gameVersion = 0, dataVersion = 0;
	int svnVersion = 0;
	SystemData::getVersion(gameVersion, dataVersion);
	svnVersion = SystemData::getSVNVersion();

	const std::string &fullChannelID = CPPlatformMnger.getStringData(CPPlatformData::FULL_CHANNEL_ID);
	if (1==LoginFace::s_mini)//§³?????
	{
		if (fullChannelID.empty())
		{
			MsgAuthMiniStrongUpdateRequest *msg = new MsgAuthMiniStrongUpdateRequest;
			msg->channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
			msg->gameVersion = gameVersion;
			msg->dataVersion = dataVersion;
			msg->svnVersion = svnVersion;
			HandleMessage::sendMessage(msg);
		}
		else
		{
			MsgAuthMiniStrongUpdateExRequest *msg = new MsgAuthMiniStrongUpdateExRequest;
			msg->channelID = fullChannelID;
			msg->gameVersion = gameVersion;
			msg->dataVersion = dataVersion;
			msg->svnVersion = svnVersion;
			HandleMessage::sendMessage(msg);
		}
		return ;
	}

	if (true)
	{
		const int mini = SystemData::getConfigInt("mini");
		if (fullChannelID.empty())
		{
			MsgAuthCheckVersionStrongUpdateRequest *msg = new MsgAuthCheckVersionStrongUpdateRequest;
			msg->channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
			msg->mini = mini;
			msg->gameVersion = gameVersion;
			msg->dataVersion = dataVersion;
			msg->svnVersion = svnVersion;
			HandleMessage::sendMessage(msg);
		}
		else
		{
			MsgAuthCheckVersionStrongUpdateExRequest *msg = new MsgAuthCheckVersionStrongUpdateExRequest;
			msg->channelID = fullChannelID;
			msg->mini = mini;
			msg->gameVersion = gameVersion;
			msg->dataVersion = dataVersion;
			msg->svnVersion = svnVersion;
			HandleMessage::sendMessage(msg);
		}
	}
	else 
	{	// Modify By Tony. 2014/09/18 17:24
		// ????????????????mini?·Úflag;
		// ??????????????;
		// ?????gameVersion??int16???2??int8;
		// ???gameVersion??????4095(0x0FFF);
		// ??????gameVersin???12¦Ë??????(0x1000);
		if (SystemData::getConfigInt("mini") != 0)
		{
			gameVersion |= (1 << 12);
		}

		if (fullChannelID.empty())
		{
			MsgAuthCheckVersionStrongWithSvnRequest *msg = new MsgAuthCheckVersionStrongWithSvnRequest;
			msg->channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
			msg->gameVersion = gameVersion;
			msg->dataVersion = dataVersion;
			msg->svnVersion = svnVersion;
			HandleMessage::sendMessage(msg);
		}
		else
		{
			MsgAuthCheckVersionStrongWithSvnExRequest *msg = new MsgAuthCheckVersionStrongWithSvnExRequest;
			msg->channelID = fullChannelID;
			msg->gameVersion = gameVersion;
			msg->dataVersion = dataVersion;
			msg->svnVersion = svnVersion;
			HandleMessage::sendMessage(msg);
		}
	}
}

void LoginHelper::getServerVersion( int &serverGameVersion, int &serverDataVersion )
{
	ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::SERVER_GAME_VERSION, serverGameVersion);
	ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::SERVER_DATA_VERSION, serverDataVersion);
}

int LoginHelper::getServerSVNVersion()
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::SERVER_SVN_VERSION, ret);
	return ret;
}

std::string LoginHelper::getDownloadURL()
{
	std::string ret;
	ModuleData::getString(CPModuleName::LOGIN, CPLoginData::DOWNLOAD_URL, ret);
	return ret;
}

std::string LoginHelper::getAnnouncement()
{
	std::string ret;
	ModuleData::getString(CPModuleName::LOGIN, CPLoginData::ANNOUNCEMENT, ret);
	return ret;
}

std::string LoginHelper::getPatchFileName()
{
	std::string ret;
	ModuleData::getString(CPModuleName::LOGIN, CPLoginData::PATCH_FILE_NAME, ret);
	return ret;
}

void LoginHelper::initAccountPassword( std::string &account, std::string &password )
{
	account = UserData::getStringData(CPUserData::ACCOUNT);
	password = UserData::getStringData(CPUserData::PASSWORD);
}

void LoginHelper::saveAccountPassword( const std::string &account, const std::string &password )
{
	UserData::setStringData(CPUserData::ACCOUNT, account);
	UserData::setStringData(CPUserData::PASSWORD, password);
	UserData::saveData();
}

void LoginHelper::checkSVNVersionRequest()
{
	const std::string &fullChannelID = CPPlatformMnger.getStringData(CPPlatformData::FULL_CHANNEL_ID);
	if (SystemData::getConfigInt("mini") != 0)
	{
		if (fullChannelID.empty())
		{
			MsgAuthMiniCheckVersionOptionalRequest *msg = new MsgAuthMiniCheckVersionOptionalRequest;
			msg->channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
			msg->svnVersion = SystemData::getSVNVersion();
			HandleMessage::sendMessage(msg);
		}
		else
		{
			MsgAuthMiniCheckVersionOptionalExRequest *msg = new MsgAuthMiniCheckVersionOptionalExRequest;
			msg->channelID = fullChannelID;
			msg->svnVersion = SystemData::getSVNVersion();
			HandleMessage::sendMessage(msg);
		}
	}
	else
	{
		if (fullChannelID.empty())
		{
			MsgAuthCheckVersionOptionalRequest *msg = new MsgAuthCheckVersionOptionalRequest;
			msg->channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
			msg->svnVersion = SystemData::getSVNVersion();
			HandleMessage::sendMessage(msg);
		}
		else
		{
			MsgAuthCheckVersionOptionalExRequest *msg = new MsgAuthCheckVersionOptionalExRequest;
			msg->channelID = fullChannelID;
			msg->svnVersion = SystemData::getSVNVersion();
			HandleMessage::sendMessage(msg);
		}
	}
	
}

void LoginHelper::loginRequest()
{
	CPPlatformMnger.setIntData(CPPlatformData::HAS_LOGIN_TO_DO, 0);
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	SubModuleData::clearAll();

	//send data to 3737
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	sendLoginPlatformTo3737();
#endif
    int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	if (true)//(channel_id != ChannelID::ios_vtcid)
	{
	MsgAuthLoginRequest* req = new MsgAuthLoginRequest;
	req->fullChannelId = CPPlatformMnger.getStringData(CPPlatformData::FULL_CHANNEL_ID);;
	req->channelId = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	req->platformId = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID);
	req->loginType = CPPlatformMnger.getIntData(CPPlatformData::LOGIN_TYPE);
	req->uid = CPPlatformMnger.getStringData(CPPlatformData::UIN);
	req->name = CPPlatformMnger.getStringData(CPPlatformData::USER_NAME);
	req->data = CPPlatformMnger.getStringData(CPPlatformData::SESSION_ID);
	req->deviceId = CPPlatformMnger.getStringData(CPPlatformData::DEVICE_ID);
	req->serverId = UserData::getIntData(CPUserData::SERVER_ID);

	// ????????????uid + name + channelId
std::string signData = req->uid + req->name + StringUtils::toString(req->channelId);
// ???????????
std::string clientSign = ClientAuth::generateClientSign(signData);
// ??????????
std::string originalData = req->data;
// ??????????????????§µ????????????|AUTH|????|???
req->data = req->data + "|AUTH|" + clientSign;

// ???????????????
CCLog("LoginHelper::loginRequest - original data: %s", originalData.c_str());
CCLog("LoginHelper::loginRequest - sign data: %s", signData.c_str());
CCLog("LoginHelper::loginRequest - client sign: %s", clientSign.c_str());
CCLog("LoginHelper::loginRequest - final data: %s", req->data.c_str());

	CCLog("login channel id: %d", req->channelId);
	HandleMessage::sendMessage(req);
    }
	else
	{
		const std::string &fullChannelID = CPPlatformMnger.getStringData(CPPlatformData::FULL_CHANNEL_ID);
		if (fullChannelID.empty())
		{
			MsgAuthBindRequest* req = new MsgAuthBindRequest;
			req->channelId = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
			req->platformId = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID);
			req->loginType = CPPlatformMnger.getIntData(CPPlatformData::LOGIN_TYPE);
			req->uid = CPPlatformMnger.getStringData(CPPlatformData::UIN);
			req->name = CPPlatformMnger.getStringData(CPPlatformData::USER_NAME);
			req->data = CPPlatformMnger.getStringData(CPPlatformData::SESSION_ID);
			CCLog("login channel id: %d", req->channelId);
			HandleMessage::sendMessage(req);
		}
		else
		{
			MsgAuthBindExRequest* req = new MsgAuthBindExRequest;
			req->channelId = fullChannelID;
			req->platformId = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID);
			req->loginType = CPPlatformMnger.getIntData(CPPlatformData::LOGIN_TYPE);
			req->uid = CPPlatformMnger.getStringData(CPPlatformData::UIN);
			req->name = CPPlatformMnger.getStringData(CPPlatformData::USER_NAME);
			req->data = CPPlatformMnger.getStringData(CPPlatformData::SESSION_ID);
			CCLog("login channel id: %s", req->channelId.c_str());
			HandleMessage::sendMessage(req);
		}
	}
}

void LoginHelper::registerRequest( const std::string &account, const std::string &passward )
{
	//
}

// Modify By Tony. 2014/9/22 10:00
// ?????????????§Ò?
void LoginHelper::authServerListResquest()
{
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	int cnt = 0;
	SubModuleData::getSize(cnt);

	if (cnt > 1)
	{
		// To do:
		// ???????§Ò??????????????????§Ò?
		LoginHelper::switchView(LoginView::serverlist);
	}
	else
	{
		SubModuleData::clearAll();
		MsgAuthServerListRequest* req = new MsgAuthServerListRequest;
		const std::string &fullChannelID = CPPlatformMnger.getStringData(CPPlatformData::FULL_CHANNEL_ID);
		int channelId = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
		int aid = 0;
		ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
		req->fullChannelID = fullChannelID;
		req->channelID = channelId;
		req->aid = aid;
		req->region = -1;

		HandleMessage::sendMessage(req);
	}
}

int LoginHelper::getServerID(int idx)
{
	int serverID = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	SubModuleData::getInt(idx, CPLoginData::SERVER_ID, serverID);
	CPPlatformMnger.setIntData(CPPlatformData::SERVER_ID, serverID);
	return serverID;
}

int LoginHelper::getServerIndexById(int id)
{
	int cnt = 0;
	cnt = getServerCnt();
	for (int i = 0;i < cnt;i++)
	{
		int serID = getServerID(i);
		if (id == serID)
		{
			return i;
		}
	}
	return 0;
}

int LoginHelper::getSavedServerIndexBysavedId(int id)
{
	int idx = 0;
	int savedSerId = 0;
	savedSerId = getSavedServerId();
	if (id == -1)
	{
		return -1;
	}
	if (id == getServerID(0))
	{
		return 0;
	}
	for (int i = 0;i < savedSerId;i++)
	{
		idx = getServerIndexById(savedSerId-i);
		if (idx != 0)
		{
			return idx;
		}
	}
	return idx;
}

int LoginHelper::getSavedServerIndex()
{
	return UserData::getIntDataForSeverPick(CPUserData::SERVER_INDEX);
}

int LoginHelper::getSavedServerId()
{
	return UserData::getIntDataForSeverPick(CPUserData::SERVER_ID);
}

int LoginHelper::getSavedRegionIndex()
{
	return UserData::getIntData(CPUserData::REGION_INDEX);
}

void LoginHelper::saveServerAndRegionIndex( int serverIndex, int regionIndex )
{
	UserData::setIntData(CPUserData::SERVER_INDEX, serverIndex);
	UserData::setIntData(CPUserData::REGION_INDEX, regionIndex);
	UserData::saveData();
}

void LoginHelper::saveServerId( int serverId )
{
	UserData::setIntData(CPUserData::SERVER_ID,serverId);
	UserData::saveData();
}

int LoginHelper::getRegionCnt()
{
	int region = 0;
	std::set<int> regionSet;
	IDVector vect;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	SubModuleData::getIDVector(vect);
	for (int i = 0; i < (int)vect.size(); i++)
	{
		SubModuleData::getInt(vect[i], CPLoginData::SERVER_REGION, region);
		regionSet.insert(region);
	}
	return regionSet.size();
}

int LoginHelper::getServerCnt()
{
	int serverCnt = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	SubModuleData::getSize(serverCnt);
	return serverCnt;
}

CCNode * LoginHelper::getServerStateIcon( int index )
{
	int state = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	SubModuleData::getInt(index, CPLoginData::SERVER_STATE, state);

	CCSprite *stateIcon = NULL;
	if (index%2)
	{
		stateIcon = LayoutData::getSprite(CPModuleName::LOGIN, "hotFlag");
	}
	else
	{
		stateIcon = LayoutData::getSprite(CPModuleName::LOGIN, "newFlag");
	}
	return stateIcon;
}

int LoginHelper::getServerState(int index)
{
	int state = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	SubModuleData::getInt(index, CPLoginData::SERVER_STATE, state);
	return state;
}

std::string LoginHelper::getServerName( int index )
{
	std::string serverName;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	SubModuleData::getString(index, CPLoginData::SERVER_NAME, serverName);
	return serverName;
}

int LoginHelper::getServerRegion( int index )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	SubModuleData::getInt(index, CPLoginData::SERVER_REGION, ret);
	return ret;
}

std::string LoginHelper::getPlayerCntNote( int index )
{
	int cnt = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	SubModuleData::getInt(index, CPLoginData::SERVER_PLAYER_CNT, cnt);
	if (cnt > 0)
	{
		return StringUtils::toString(cnt);
	}
	return "";
}

//void LoginHelper::enterServerRequest()
//{
//    int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
//	if (true)//(channel_id != ChannelID::ios_vtcid)
//	{
//		ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SEVERQUEUE, 0);
//		int aid = 0;
//		ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
//		MsgEnterServerRequestEx *msg = new MsgEnterServerRequestEx;
//		msg->aid = aid;
//		msg->channelId = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
//		msg->fullChannelId = CPPlatformMnger.getStringData(CPPlatformData::FULL_CHANNEL_ID);
//		msg->platformId = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID);
//		msg->deviceId = CPPlatformMnger.getStringData(CPPlatformData::DEVICE_ID);
//		msg->token = CPPlatformMnger.getIntData(CPPlatformData::LOGIN_TOKEN);
//		HandleMessage::sendMessage(msg);
//    }
//    else
//    {
//        ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SEVERQUEUE, 0);
//        int aid = 0;
//        ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
//        //MsgEnterServerRequestEx *msg = new MsgEnterServerRequestEx;
//        MsgEnterServerRequest *msg = new MsgEnterServerRequest;
//        msg->aid = aid;
//        msg->channelId = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
//        msg->fullChannelId = CPPlatformMnger.getStringData(CPPlatformData::FULL_CHANNEL_ID);
//        msg->platformId = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID);
//        msg->deviceId = CPPlatformMnger.getStringData(CPPlatformData::DEVICE_ID);
//        //msg->token = CPPlatformMnger.getIntData(CPPlatformData::LOGIN_TOKEN);
//        HandleMessage::sendMessage(msg);
//    }
//}

void LoginHelper::enterServerRequest()//???????????Tuoking_223
{
    int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
    
    if (true)  // (channel_id != ChannelID::ios_vtcid)
    {
        ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SEVERQUEUE, 0);
        int aid = 0;
        ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
        
        MsgEnterServerRequestEx *msg = new MsgEnterServerRequestEx;
        
        // ???????????
        msg->aid = aid;
        msg->channelId = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
        msg->fullChannelId = CPPlatformMnger.getStringData(CPPlatformData::FULL_CHANNEL_ID);
        msg->platformId = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID);
        
        // ????????AMS?????token
        msg->token = CPPlatformMnger.getIntData(CPPlatformData::LOGIN_TOKEN);
        
        // ???deviceId????????????????
        std::string deviceId = CPPlatformMnger.getStringData(CPPlatformData::DEVICE_ID);
        deviceId += "Tuoking_223";  // ??????????
        msg->deviceId = deviceId;
        
        HandleMessage::sendMessage(msg);
    }
    else
    {
        // ????????????????
        ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SEVERQUEUE, 0);
        int aid = 0;
        ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
        
        MsgEnterServerRequest *msg = new MsgEnterServerRequest;
        msg->aid = aid;
        msg->channelId = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
        msg->fullChannelId = CPPlatformMnger.getStringData(CPPlatformData::FULL_CHANNEL_ID);
        msg->platformId = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID);
        
        // MsgEnterServerRequest???????token???
        // ??deviceId????????
        std::string deviceId = CPPlatformMnger.getStringData(CPPlatformData::DEVICE_ID);
        deviceId += "Tuoking_223";
        msg->deviceId = deviceId;
        
        HandleMessage::sendMessage(msg);
    }
}



void LoginHelper::enterCrossServerRequest()
{

	ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SEVERQUEUE, 0);
	int aid = 0;
	ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
	MsgEnterCrossServerRequest *msg = new MsgEnterCrossServerRequest;
	//msg->serverid = UserData::getIntData(CPUserData::SERVER_ID);
	msg->serverid = CPPlatformMnger.getIntData(CPPlatformData::SERVER_ID);
	msg->aid = aid;
	msg->channelId = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	msg->fullChannelId = CPPlatformMnger.getStringData(CPPlatformData::FULL_CHANNEL_ID);
	msg->platformId = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID);
	msg->deviceId = CPPlatformMnger.getStringData(CPPlatformData::DEVICE_ID);
	msg->token = CPPlatformMnger.getIntData(CPPlatformData::LOGIN_TOKEN);
	HandleMessage::sendMessage(msg);
   
}

int LoginHelper::getSavedRoleIndex()
{
	return UserData::getIntData(CPUserData::ROLE_INDEX);
}

void LoginHelper::saveRoleIndex( int roleIndex )
{
	UserData::setIntData(CPUserData::ROLE_INDEX, roleIndex);
	UserData::saveData();
}

int LoginHelper::getPlayerCnt()
{
	int playerCnt = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
	SubModuleData::getSize(playerCnt);
	return playerCnt;
}

int LoginHelper::getPID( int index )
{
	int pid = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
	IDVector vect;
	SubModuleData::getIDVector(vect);
	if (0 <= index && index < (int)vect.size())
	{
		pid = vect[index];
	}
	return pid;
}

std::string LoginHelper::getPlayerName( int index )
{
	std::string playName;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
	SubModuleData::getString(getPID(index), CPLoginData::PLAYER_NAME, playName);
	return playName;
}

int LoginHelper::getPlayerGender( int index )
{
	int gender = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
	SubModuleData::getInt(getPID(index), CPLoginData::PLAYER_GENDER, gender);
	return gender;
}

int LoginHelper::getPlayerJob( int index )
{
	int job = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
	SubModuleData::getInt(getPID(index), CPLoginData::PLAYER_JOB, job);
	return job;
}

int LoginHelper::getPlayerLevel( int index )
{
	int level = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
	SubModuleData::getInt(getPID(index), CPLoginData::PLAYER_LEVEL, level);
	return level;
}

int LoginHelper::getPlayerCloth( int index )
{
	int cloth = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
	SubModuleData::getInt(getPID(index), CPLoginData::PLAYER_CLOTH, cloth);
	return cloth;
}

int LoginHelper::getPlayerWeapon( int index )
{
	int weapon = 0;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
	SubModuleData::getInt(getPID(index), CPLoginData::PLAYER_WEAPON, weapon);
	return weapon;
}

CCNode * LoginHelper::getRoleAnim( int job, int gender )
{
	if (job == UserData::CARRER_OMNI) job = UserData::CARRER_ZS;
	const std::string key = "roleAnim" + StringUtils::toString(job) + StringUtils::toString(gender);
	return CPAnimMnger.getOneDirAnimSprite(LayoutData::getString(CPModuleName::LOGIN, key));
}

CCNode * LoginHelper::getRoleAnim( int index )
{
	return getRoleAnim(getPlayerJob(index), getPlayerGender(index));
}

CCNode * LoginHelper::getRoleSelAnim()
{
	CCSprite *ret = CCSprite::create();
	CCFlashAnimation *anim = CPAnimMnger.getAnimationOneDir(LayoutData::getString(CPModuleName::LOGIN, "roleSelAnim"));
	if (anim)
	{
		CCSpriteFrame *frame = anim->getSprite(0);
		if (frame)
		{
			ret->setContentSize(frame->getRect().size);
		}
		ret->runAction(CCRepeatForever::create(anim->getAnimate(0)));
	}
	return ret;
}

CCSprite * LoginHelper::getJobBoard( int index )
{
	if (getPID(index) <= 0)
	{
		return NULL;
	}

	CCSprite *jobBoard = LayoutData::getSprite(CPModuleName::LOGIN, "jobBoard");
	CCSprite *jobIcon = NULL;
	int job = getPlayerJob(index);
	if(job == UserData::CARRER_ZS)
	{
		jobIcon = LayoutData::getSprite(CPModuleName::LOGIN, "jobWordZS");
	}
	else if(job == UserData::CARRER_FS)
	{
		jobIcon = LayoutData::getSprite(CPModuleName::LOGIN, "jobWordFS");
	}
	else if(job == UserData::CARRER_OMNI)
	{
		jobIcon = LayoutData::getSprite(CPModuleName::LOGIN, "jobWordZS");
	}
	else
	{
		jobIcon = LayoutData::getSprite(CPModuleName::LOGIN, "jobWordDS");
	}
	jobBoard->addChild(jobIcon);

	const std::string &nameStr = getPlayerName(index) + "[gLv." + StringUtils::toString(getPlayerLevel(index)) + "]";
	CPRichText *nameLabel = RichTextUtils::getRichText(nameStr, LayoutData::getInt(CPModuleName::LOGIN, "selRoleNameFontSize"));
	if (nameLabel)
	{
		nameLabel->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "selRoleName"));
		jobBoard->addChild(nameLabel);
	}

	return jobBoard;
}

void LoginHelper::delRoleRequest( int index )
{
	const int pid = getPID(index);
	MsgDeletePlayerRequest* req = new MsgDeletePlayerRequest;
	req->pid = pid;
	HandleMessage::sendMessage(req);

	UserData::clear(pid);
}

void LoginHelper::enterGame( int index )
{
	if (getPID(index) > 0)
	{
		saveRoleIndex(index);

		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->mName = getPlayerName(index);
		HeroData::setPID(getPID(index));
		HeroData::setJob(getPlayerJob(index));
		HeroData::setLevel(getPlayerLevel(index));
		GameData::s_game_state = GAME_STATE_LODING;
		CCDirector::sharedDirector()->replaceScene(SceneFactory::sceneResLoading());
		//send deviceID and uwid to AS

		//send data to 3737
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		sendDeviceIDToAMS();
		sendEnterGameTo3737(index);
#endif
		CPPlatform->operate(PlatformOpID::enter_game);

/*		int channelid = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
		if (channelid == ChannelID::tencent
			|| channelid == ChannelID::tencent_huanliang)
		{
			MsgUpdateDataToASRequest* ms = new MsgUpdateDataToASRequest();
			ms->channelid = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
			ms->serverid = CPPlatformMnger.getIntData(CPPlatformData::SERVER_ID);
			int aid = 0;
			ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
			ms->aid = aid;
			ms->pid = HeroData::getPID();
			ms->operation = 1;
			ms->data = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_MID);
			CCLog("MsgUpdateDataToASRequest MID: %s", ms->data.c_str());
			HandleMessage::sendMessage(ms);
		}*/
	}
}

void LoginHelper::returnSelectRoleFromGame()
{
	Login *loginLayer = Login::create(LoginView::selectrole);
	if (!loginLayer) return;
	CCScene *loginScene = CCScene::create();
	if (!loginScene) return;
	loginScene->addChild(loginLayer);
	CCDirector::sharedDirector()->replaceScene(loginScene);

	//startAuthServer();
	//startGameServer(getSavedServerIndex());

	// Modify By Tony. 2014/9/30 9:59
	// using method of enterServerRequest must reconnect to gs
	int index = CPPlatformMnger.getIntData(CPPlatformData::SERVER_INDEX);
	restartGameServer(index);
	enterServerRequest();
}

bool LoginHelper::testCreateName( const std::string &userName, std::string &outStr )
{
	outStr = userName;
	if (outStr.empty())
	{
		return false;
	}

	outStr = CPPlatform->convert(outStr);
	if (outStr == userName)
	{
		if (StringUtils::filterString(outStr, outStr))
		{
			if (!StringUtils::hasSpecialWords(outStr))
			{
				CCLabelTTF* label = CCLabelTTF::create(outStr.c_str(),"",16);
				if (label)
				{
					return true;
				}
				else
				{
					CPEventHelper::uiNotify("LoginHelper", "", Error::Contains_Special_Words);
				}
			}
			else
			{
				CPEventHelper::uiNotify("LoginHelper", "", Error::Contains_Special_Words);
			}
		}
		else
		{
			CPEventHelper::uiNotify("LoginHelper", "", Error::Contains_Sensitive_Words);
		}
	}
	else
	{
		CPEventHelper::uiNotify("LoginHelper", "", Error::Contains_Whitespace_Words);
	}
	
	return false;
}

void LoginHelper::createRoleRequest( int index, const std::string &userName )
{
	MsgCreatePlayerRequest* req = new MsgCreatePlayerRequest;
	req->career = getJobByIndex(index);
	req->PlayerName = userName;
	req->gender = getGenderByIndex(index);
	HandleMessage::sendMessage(req);
}

int LoginHelper::getJobByIndex( int index )
{
	if ( index == 1 || index == 5)
	{
		return UserData::CARRER_FS;
	}
	else if (index == 2 || index == 6)
	{
		return UserData::CARRER_DS;
	}
	else if (index == 3 || index == 7)
	{
		return UserData::CARRER_OMNI;
	}
	return UserData::CARRER_ZS;
}

int LoginHelper::getGenderByIndex( int index )
{
	if (index > 3)
	{
		return UserData::SEX_FEMALE;
	}
	return UserData::SEX_MALE;
}

std::string LoginHelper::getRandomName( int index )
{
	std::string randomName;
	Lua::instance()->push(getGenderByIndex(index));
	if (Lua::instance()->call("cb_get_random_name", 1, 1 ) &&
		Lua::instance()->pop_utf8(randomName))
	{
		return randomName;
	}
	else
	{
		CCLog(">>>Error, LoginHelper::getRandomName, failed to call function name : cb_get_random_name");
		return "RandomName";
	}
}

int LoginHelper::getIndexByPID( int pid )
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

void LoginHelper::setListDataAndEnterGame( int index, const std::string &playerName )
{
	const int pid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
	if (pid > 0)
	{
		SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
		SubModuleData::setInt(pid, CPLoginData::PLAYER_ID, pid);
		SubModuleData::setInt(pid, CPLoginData::PLAYER_JOB, getJobByIndex(index));
		SubModuleData::setInt(pid, CPLoginData::PLAYER_GENDER, getGenderByIndex(index));
		SubModuleData::setString(pid, CPLoginData::PLAYER_NAME, playerName);

		enterGame(getIndexByPID(pid));
	}
}

void LoginHelper::clear()
{
	ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SEVERQUEUE, 0);
}

void LoginHelper::setcurSerIndex(int index)
{
	curSerIndex = index;
}

int LoginHelper::getcurSerIndex()
{
	return curSerIndex;
}

bool LoginHelper::checkPlayerOld()
{
	int cnt = LoginHelper::getServerCnt();
	for (int i = 0;i < cnt;i++)
	{
		std::string str = LoginHelper::getPlayerCntNote(i);
		if (str != "")
		{
			return true;
		}
	}
	return false;
}

void LoginHelper::sendLoginPlatformTo3737()
{
	//?????
	/*
	uid		//???ID
	uname		//?????
	utime		//????
	gid		//???ID
	sid		//?????ID
	uaid		//????ID,(?????????)
	uwid		//????ID(?????ID),(§³???????)
	uadid		//???ID
	usite		//???ID
	umacid	//???¦·?ID
	uip		//???IP
	sign		//?????(?????:md5($my_uid.$my_uname.$my_time.$my_gid.$my_sid.$un_aid.$un_wid.$un_adid.$un_site.$umacid.$my_uip.$KEY))
	*/
	bool requestType_is_post=true;//
	std::string gid="13";
	std::string	key="ydl_gresdf98ouidww4";
	int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);

	if (requestType_is_post)
	{
		CCHttpRequest* request = new CCHttpRequest();//
		string str0 = "http://un.huolug.com/news/get.game.gamelogin.php";
        
		string uid = CPPlatformMnger.getStringData(CPPlatformData::UIN);
		string uname = CPPlatformMnger.getStringData(CPPlatformData::USER_NAME);
		string utime = StringUtils::toString(ActivityData::getWorldTime());//utime
		string gid = "13";//gid
		string sid = "0";//at this time is not in server so send 0
		string uaid = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uaid_"+StringUtils::toString(channel_id)));
		string uwid = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uwid_"+StringUtils::toString(channel_id)));
		string uadid = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uadid_"+StringUtils::toString(channel_id)));
		string usite = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"usite_"+StringUtils::toString(channel_id)));
		string umacid = "";
		string uip = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		umacid = CHANNELHELPER->getDeviceID();//"e12f03g50a10";//umacid
		uip = CHANNELHELPER->getIPAddress();
#endif
		string str_sign = "";//sign
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		std::string str_md5 = uid+uname+utime+gid+sid+uaid+uwid+uadid+usite+umacid+uip+key ;
		str_sign = MD5::MD5(str_md5).toString();
#endif
        
		string struid = "uid=";
		string struname = "&uname=";
		string strutime = "&utime=";
		string strgid = "&gid=";
		string strsid = "&sid=";
		string struaid = "&uaid=";
		string struwid = "&uwid=";
		string struadid = "&uadid=";
		string strusite = "&usite=";
		string strumacid = "&umacid=";
		string struip = "&uip=";
		string strsign = "&sign=";
        
		string str_data = struid+uid +struname+uname+ strutime+utime+ strgid+gid+ strsid+sid+ struaid+uaid+ struwid+uwid+ struadid+uadid+ strusite+usite+ strumacid+umacid+ struip+uip+    strsign+str_sign    ;
		request->setUrl(str0.c_str());//
		request->setRequestData(str_data.c_str(),strlen(str_data.c_str()));
		request->setRequestType(CCHttpRequest::kHttpPost);//
        //		request->setResponseCallback(this, httpresponse_selector(Login_3737::onHttpRequestCompleted));//
		request->setTag("Post test");
		CCHttpClient::getInstance()->send(request);//
		request->release();//
	}
}

void LoginHelper::sendEnterGameTo3737(int index)
{
	//???????
	/*
	uid		//???ID(????ID)
	uname		//?????(???????)
	uguid		//??????????ID
	ugname		//????????????
	utime		//????
	gid		//???ID
	sid		//?????ID
	uaid		//????ID,(?????????)
	uwid		//????ID(?????ID),(§³???????)
	uadid		//???ID
	usite		//???ID
	umacid	//???¦·?ID
	uip		//???IP
	sign		//?????(?????:md5($my_uid.$my_uname.$my_time.$my_gid.$my_sid.$un_aid.$un_wid.$un_adid.$un_site.$umacid.$uguid.$ugname.$my_uip.$KEY)

	*/
	bool requestType_is_post=true;//
	std::string gid="13";
	std::string	key="ydl_gresdf98ouidww4";
	int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	if (requestType_is_post)
	{
		CCHttpRequest* request = new CCHttpRequest();//
		string str0 = "http://un.huolug.com/news/get.game.gamereg.php";
        
		string uid = CPPlatformMnger.getStringData(CPPlatformData::UIN);
		string uname = CPPlatformMnger.getStringData(CPPlatformData::USER_NAME);
		string uguid = StringUtils::toString(LoginHelper::getPID(index));
		string ugname = LoginHelper::getPlayerName(index);
		string utime = StringUtils::toString(ActivityData::getWorldTime());//utime
		string gid = "13";//gid
		string sid = StringUtils::toString(LoginHelper::getSavedServerId());//CPPlatformMnger.getStringData(CPPlatformData::SERVER_ID);
		string uaid = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uaid_"+StringUtils::toString(channel_id)));
		string uwid = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uwid_"+StringUtils::toString(channel_id)));
		string uadid = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uadid_"+StringUtils::toString(channel_id)));
		string usite = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"usite_"+StringUtils::toString(channel_id)));
		string umacid = "";
		string uip = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		umacid = CHANNELHELPER->getDeviceID();//"e12f03g50a10";//umacid
		uip = CHANNELHELPER->getIPAddress();
#endif
		string str_sign = "";//sign
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		std::string str_md5 = uid+uname+utime+gid+sid+uaid+uwid+uadid+usite+umacid+uguid+ugname+uip+key ;
		str_sign = MD5::MD5(str_md5).toString();
#endif
        
		string struid = "uid=";
		string struname = "&uname=";
		string struguid = "&uguid=";
		string strugname = "&ugname=";
		string strutime = "&utime=";
		string strgid = "&gid=";
		string strsid = "&sid=";
		string struaid = "&uaid=";
		string struwid = "&uwid=";
		string struadid = "&uadid=";
		string strusite = "&usite=";
		string strumacid = "&umacid=";
		string struip = "&uip=";
		string strsign = "&sign=";
        
		string str_data = struid+uid+  struname+uname+ struguid+uguid+  strugname+ugname+  strutime+utime+   strgid+gid+ strsid+sid+  struaid+uaid+   struwid+uwid+    struadid+uadid+    strusite+usite+    strumacid+umacid+    struip+uip+    strsign+str_sign    ;
		request->setUrl(str0.c_str());//
		request->setRequestData(str_data.c_str(),strlen(str_data.c_str()));
		request->setRequestType(CCHttpRequest::kHttpPost);//
        //		request->setResponseCallback(this, httpresponse_selector(Login_3737::onHttpRequestCompleted));//
		request->setTag("Post test");
		CCHttpClient::getInstance()->send(request);//
		request->release();//
	}
}

void LoginHelper::sendDeviceIDToAMS()
{
	MsgPlayerLoginLogoutNotify *req = new MsgPlayerLoginLogoutNotify;
	req->deviceId = CPPlatformMnger.getStringData(CPPlatformData::DEVICE_ID);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	req->deviceId = CHANNELHELPER->getDeviceID();
#endif
	HandleMessage::sendMessage(req);
}
