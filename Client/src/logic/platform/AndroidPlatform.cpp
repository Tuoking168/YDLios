#include "AndroidPlatform.h"
#include "CCCommon.h"
#include "ModuleData.h"
#include "LoginModule.h"
#include "EntityDefinition.h"
#include <signal.h>

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/GuildData.h"
#include "userdata/netdata/GameRole.h"

#include "scene/LoginHelper.h"
#include "scene/SceneManager.h"
#include "scene/NotificationHelper.h"

#include "event/CPEventHelper.h"
#include "PlatformDefinition.h"

#include "res/Path.h"

#include <android/jni/JniHelper.h>


using namespace cocos2d;


#define  CLASS_NAME "com/ceapon/fire/MyPlatform"

//
struct sigaction old_sa[NSIG];
static void onSigaction(int signal, siginfo_t *info, void *reserved)
{
	CCLog(">>>onSigaction(%d)", signal);
	if (info)
	{
		CCLog(">>>onSigaction(%d, %d, %d)", info->si_signo, info->si_errno, info->si_code);
	}
	CPPlatform->operate(PlatformOpID::sendLog);
    old_sa[signal].sa_handler(signal);
}

static void initCrashReporter()
{
    struct sigaction handler;
    memset(&handler, 0, sizeof(struct sigaction));

    handler.sa_sigaction = onSigaction;
    handler.sa_flags = SA_RESETHAND;

#define CATCHSIG(X) sigaction(X, &handler, &old_sa[X])

    CATCHSIG(SIGILL); // 无效指令
    CATCHSIG(SIGABRT); // 异常中止
    CATCHSIG(SIGBUS); // 无效的地址
    CATCHSIG(SIGFPE); // 浮点异常
    CATCHSIG(SIGSEGV); // 无效内存访问
    CATCHSIG(SIGSTKFLT); // 内存不足
    CATCHSIG(SIGPIPE); // 向无效管道写数据
}

//
static std::string getStringUTFChars( JNIEnv *env, jstring jstr )
{
	std::string str;
	if(env && jstr)
	{
		const char *ch = env->GetStringUTFChars(jstr, 0);
		if(ch)
		{
			str = ch;
			env->ReleaseStringUTFChars(jstr, ch);
		}
	}	

	return str;
}

static jstring getJavaString( JNIEnv *env, const std::string &str)
{
	jstring jstr = NULL;
	if(env)
	{
		jstr = env->NewStringUTF(str.c_str());
	}
	return jstr;
}

// VoidVoid = void return and void parameter
static void callStaticVoidVoidMethod( const std::string &methodName )
{
	CCLog(">>>callStaticVoidVoidMethod, %s", methodName.c_str());
	JniMethodInfo info;
	bool test = JniHelper::getStaticMethodInfo(info, CLASS_NAME, methodName.c_str(), "()V");
	if(test)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
		info.env->DeleteLocalRef(info.classID);
	}
}

// VoidInt = void return and Int parameter
static void callStaticVoidIntMethod( const std::string &methodName, int data )
{
	CCLog(">>>callStaticVoidIntMethod, %s, %d", methodName.c_str(), data);
	JniMethodInfo info;
	bool test = JniHelper::getStaticMethodInfo(info, CLASS_NAME, methodName.c_str(), "(I)V");
	if(test)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID, data);
		info.env->DeleteLocalRef(info.classID);
	}
}

// StringString = String return and String parameter
static std::string callStaticStringStringMethod( const std::string &methodName, const std::string &data )
{
	CCLog(">>>callStaticStringStringMethod, %s, %s", methodName.c_str(), data.c_str());
	std::string ret;
	JniMethodInfo info;
	bool test = JniHelper::getStaticMethodInfo(info, CLASS_NAME, methodName.c_str(), "(Ljava/lang/String;)Ljava/lang/String;");
	if(test)
	{
		jstring jdata = getJavaString(info.env, data);
		if (jdata)
		{
			jstring jret = (jstring)info.env->CallStaticObjectMethod(info.classID, info.methodID, jdata);
			ret = getStringUTFChars(info.env, jret);
		}
		info.env->DeleteLocalRef(info.classID);
	}

	return ret;
}

////////////AndroidPlatform///////////////////////////////////////
AndroidPlatform::AndroidPlatform()
{
	initCrashReporter();
}

AndroidPlatform::~AndroidPlatform()
{

}

void AndroidPlatform::login()
{
	const int channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);

	if(channelID == ChannelID::coolpay_lieyanzhanshen||channelID == ChannelID::coolpay)
	{
	  LoginHelper::switchView(LoginView::loginbody);
	}
	else
	{
		callStaticVoidVoidMethod("pfLoginRequest");
	}
}

void AndroidPlatform::pay( int yuan )
{
	callStaticVoidIntMethod("pfPayRequest", yuan);
}

void AndroidPlatform::operate( int opID )
{
	callStaticVoidIntMethod("pfOperate", opID);
}

std::string AndroidPlatform::convert( const std::string &data )
{
	return callStaticStringStringMethod("pfConvert", data);
}

void AndroidPlatform::selectGameSever( int selectedserver )
{
	callStaticVoidIntMethod("pfselectGameSever", selectedserver);
}

////////////called by java////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfUpdateSuccess( JNIEnv *env, jclass cls )
	{
		//
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfSetChannelId( JNIEnv *env, jclass cls, jint channelID)
	{
		CPPlatformMnger.setIntData(CPPlatformData::CHANNEL_ID, channelID);
	}
	
	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfSetMID( JNIEnv *env, jclass cls, jstring mid)
	{
		CPPlatformMnger.setStringData(CPPlatformData::PLATFORM_MID, getStringUTFChars(env, mid));
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfSetFullChannelId( JNIEnv *env, jclass cls, jstring channelID)
	{
		CPPlatformMnger.setStringData(CPPlatformData::FULL_CHANNEL_ID, getStringUTFChars(env, channelID));
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfSetPlatformId( JNIEnv *env, jclass cls, jint platformID)
	{
		CPPlatformMnger.setIntData(CPPlatformData::PLATFORM_ID, platformID);
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfSetDeviceId( JNIEnv *env, jclass cls, jstring deviceId)
	{
		CPPlatformMnger.setStringData(CPPlatformData::DEVICE_ID, getStringUTFChars(env, deviceId));
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfSetPhoneInfo( JNIEnv *env, jclass cls, jstring info)
	{
		CPPlatformMnger.setStringData(CPPlatformData::PHONE_INFO, getStringUTFChars(env, info));
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfSetProxyServer( JNIEnv *env, jclass cls, jstring proxyIP, jstring proxyport)
	{
		CPPlatformMnger.setStringData(CPPlatformData::PROXY_SERVER_ID, getStringUTFChars(env, proxyIP));
		CPPlatformMnger.setStringData(CPPlatformData::PROXY_SERVER_PORT, getStringUTFChars(env, proxyport));
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfSetExtWritePath( JNIEnv *env, jclass cls, jstring extPath)
	{
		CPPlatformMnger.setStringData(CPPlatformData::EXT_WRITE_PATH, getStringUTFChars(env, extPath));
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfSetPackageName( JNIEnv *env, jclass cls, jstring packageName)
	{
		CPPlatformMnger.setStringData(CPPlatformData::PACKAGE_NAME, getStringUTFChars(env, packageName));
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfLoginRequest( JNIEnv *env, jclass cls, jstring uid, jstring username, jstring password, jint loginType)
	{
		const std::string &uin = getStringUTFChars(env, uid);
		const std::string &sessionID = getStringUTFChars(env, password);
		const std::string &userName = getStringUTFChars(env, username);
		if (uin == sessionID && sessionID == userName && userName == "local-login")
		{
			LoginHelper::switchView(LoginView::loginbody);
		}
		else
		{
			CPPlatformMnger.setStringData(CPPlatformData::UIN, uin);
			CPPlatformMnger.setStringData(CPPlatformData::SESSION_ID, sessionID);
			CPPlatformMnger.setStringData(CPPlatformData::USER_NAME, userName);
			CPPlatformMnger.setIntData(CPPlatformData::LOGIN_TYPE, loginType);
			LoginHelper::loginRequest();

			CPEventHelper::dispatcher(CPEventName::LGC_PLATFORM, "Java_com_ceapon_fire_MyPlatform_pfLoginResponse", "");
		}
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfLoginWhenOKRequest( JNIEnv *env, jclass cls, jstring uid, jstring username, jstring password, jint loginType)
	{
		const std::string &uin = getStringUTFChars(env, uid);
		const std::string &sessionID = getStringUTFChars(env, password);
		const std::string &userName = getStringUTFChars(env, username);
		if (uin == sessionID && sessionID == userName && userName == "local-login")
		{
			LoginHelper::switchView(LoginView::loginbody);
		}
		else
		{
			CPPlatformMnger.setStringData(CPPlatformData::UIN, uin);
			CPPlatformMnger.setStringData(CPPlatformData::SESSION_ID, sessionID);
			CPPlatformMnger.setStringData(CPPlatformData::USER_NAME, userName);
			CPPlatformMnger.setIntData(CPPlatformData::LOGIN_TYPE, loginType);
			CPPlatformMnger.setIntData(CPPlatformData::HAS_LOGIN_TO_DO, 1);
		}
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfLoginResponse( JNIEnv *env, jclass cls, jstring uin, jstring sid )
	{
		const std::string &uinStr = getStringUTFChars(env, uin);
		const std::string &sessionID = getStringUTFChars(env, sid);

		CPPlatformMnger.setStringData(CPPlatformData::UIN, uinStr);
		CPPlatformMnger.setStringData(CPPlatformData::SESSION_ID, sessionID);
		LoginHelper::loginRequest();

		CPEventHelper::dispatcher(CPEventName::LGC_PLATFORM, "Java_com_ceapon_fire_MyPlatform_pfLoginResponse", "");
	}

	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfPayResponse( JNIEnv *env, jclass cls, jstring guid )
	{
		//
	}

	JNIEXPORT int JNICALL Java_com_ceapon_fire_MyPlatform_pfGetServerID( JNIEnv *env, jclass cls )
	{
		return CPPlatformMnger.getIntData(CPPlatformData::SERVER_ID);
	}

	JNIEXPORT int JNICALL Java_com_ceapon_fire_MyPlatform_pfGetAid( JNIEnv *env, jclass cls )
	{
		int aid = 0;
		ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
		return aid;
	}

	JNIEXPORT int JNICALL Java_com_ceapon_fire_MyPlatform_pfGetPid( JNIEnv *env, jclass cls )
	{
		return HeroData::getPID();
	}

	JNIEXPORT jstring JNICALL Java_com_ceapon_fire_MyPlatform_pfGetUrl( JNIEnv *env, jclass cls )
	{
		return getJavaString(env, LoginHelper::getDownloadURL());
	}

	JNIEXPORT int JNICALL Java_com_ceapon_fire_MyPlatform_pfGetBalance( JNIEnv *env, jclass cls )
	{
		return HeroData::getProp(Entity::attr_gold);
	}
	
	JNIEXPORT int JNICALL Java_com_ceapon_fire_MyPlatform_pfGetRechargeGold( JNIEnv *env, jclass cls )
	{
		return HeroData::getProp(Entity::attr_recharge_gold);
	}

	JNIEXPORT int JNICALL Java_com_ceapon_fire_MyPlatform_pfGetLvl( JNIEnv *env, jclass cls )
	{
		return HeroData::getLevel();
	}

	JNIEXPORT int JNICALL Java_com_ceapon_fire_MyPlatform_pfGetVipLvl( JNIEnv *env, jclass cls )
	{
		return HeroData::getProp(Entity::attr_vip_level);
	}

	JNIEXPORT jstring JNICALL Java_com_ceapon_fire_MyPlatform_pfGetGuild( JNIEnv *env, jclass cls )
	{
		if (HeroData::getProp(Entity::attr_guild_id) > 0)
		{
			return getJavaString(env, GuildData::getMyGuildName());
		}
		return getJavaString(env, "");
	}

	JNIEXPORT jstring JNICALL Java_com_ceapon_fire_MyPlatform_pfGetPlayerName( JNIEnv *env, jclass cls )
	{
		GameRole *myRole = GameData::getMyRole();
		if (myRole)
		{
			return getJavaString(env, myRole->mName);
		}
		return getJavaString(env, "");
	}

	JNIEXPORT jstring JNICALL Java_com_ceapon_fire_MyPlatform_pfGetServerName( JNIEnv *env, jclass cls )
	{
		return getJavaString(env, CPPlatformMnger.getStringData(CPPlatformData::SERVER_NAME));
	}

	JNIEXPORT jstring JNICALL Java_com_ceapon_fire_MyPlatform_pfGetToken( JNIEnv *env, jclass cls )
	{
		return getJavaString(env, CPPlatformMnger.getStringData(CPPlatformData::TOKEN));
	}
	
	JNIEXPORT jstring JNICALL Java_com_ceapon_fire_MyPlatform_pfGetUid( JNIEnv *env, jclass cls )
	{
		return getJavaString(env, CPPlatformMnger.getStringData(CPPlatformData::UIN));
	}
	
	JNIEXPORT jstring JNICALL Java_com_ceapon_fire_MyPlatform_pfGetUserName( JNIEnv *env, jclass cls )
	{
		return getJavaString(env, CPPlatformMnger.getStringData(CPPlatformData::USER_NAME));
	}

	JNIEXPORT int JNICALL Java_com_ceapon_fire_MyPlatform_pfGetMapId( JNIEnv *env, jclass cls )
	{
		NetMap *map = GameData::getCurrentMap();
		if (map)
		{
			return map->mID;
		}
		return 0;
	}
	
	JNIEXPORT jstring JNICALL Java_com_ceapon_fire_MyPlatform_pfGetMapName( JNIEnv *env, jclass cls )
	{
		NetMap *map = GameData::getCurrentMap();
		if (map)
		{
			return getJavaString(env, map->mName);
		}
		return getJavaString(env, "");
	}
	
	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfExit( JNIEnv *env, jclass cls )
	{
		SceneManager::exitGame();
	}
	
	JNIEXPORT void JNICALL Java_com_ceapon_fire_MyPlatform_pfLogout( JNIEnv *env, jclass cls )
	{
		NotificationHelper::delayRun(0.05f, SceneManager::switchToLogin);
	}

	JNIEXPORT jstring JNICALL Java_com_ceapon_fire_MyPlatform_pfGetPatchFileName( JNIEnv *env, jclass cls )
	{
		return getJavaString(env, LoginHelper::getPatchFileName());
	}
	
#ifdef __cplusplus
}
#endif
