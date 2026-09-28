#include "SceneManager.h"
#include "cocos2d.h"
#include "SceneFactory.h"
#include "LoginHelper.h"

#include "res/AudioLoader.h"

#include "logic/platform/PlatformOpID.h"
#include "logic/platform/IPlatform.h"

#include "userdata/UserData.h"
#include "userdata/GameData.h"

#include "utils/MacroUtils.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#endif

using namespace cocos2d;


////////SceneManager/////////////////////////////////////////////////
void SceneManager::switchToLogin()
{
	UserData::saveData();
	GameData::s_user->releaseGameData();
	CCDirector::sharedDirector()->replaceScene(SceneFactory::sceneLogin());
}

void SceneManager::switchToServerList()
{
	switchToLogin();
	LoginHelper::switchView(LoginView::serverlist);
}

void SceneManager::switchToRoleList()
{
	UserData::saveData();
	GameData::s_user->releaseGameData();
	LoginHelper::returnSelectRoleFromGame();
}

void SceneManager::exitGame()
{
	CCLog(">>>SceneManager::exitGame!!");
	UserData::saveData();
	AudioLoader::stopAll();
	GameData::releaseGameDataForExit();

	CCDirector *pDirector = CCDirector::sharedDirector();
	CCNode *notificationLayer = pDirector->getNotificationNode();
	if (notificationLayer)
	{
		notificationLayer->removeFromParent();
		pDirector->setNotificationNode(NULL);
	}

	//
	CCDirector::sharedDirector()->end();
	AndroidCode(terminateProcessJNI());
	IOSCode(std::exit(0));
}

