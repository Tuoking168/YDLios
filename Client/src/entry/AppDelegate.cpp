#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "CCScheduler.h"
#include "log.h"

#include "userdata/SystemData.h"

#include "network/HandleMessage.h"
#include "network/MsgListener.h"
#include "NetRunnable.h"

#include "scene/SceneFactory.h"
#include "scene/NotificationLayer.h"
#include "scene/SceneFactory.h"

#include "res/Path.h"
#include "res/AudioLoader.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "ext/Properties.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//#import <WGPlatform/WGPlatform.h>
//#import "WGPlatform/WGInterface.h"
//#import <WGPlatform/WGPublicDefine.h>
#endif

using namespace cocos2d;
using namespace CocosDenshion;


static void logger( const std::string &type, const std::string &content )
{
	CCLog("%s%s", type.c_str(), content.c_str());
}

/////////AppDelegate////////////////////////////////////////////////
AppDelegate::AppDelegate()
{
	CPLog::setLogger(logger);
}

AppDelegate::~AppDelegate() 
{
	// Modify By Tony. 2014/9/28 10:54
	// refactor code;
	// use different listener;
	// gsMsglistener is used for connecting GS
	// amsMsglistener is used for connecting AMS

	//HandleMessage::s_msglistener->stopServer();
	//HandleMessage::s_msglistener->release();
	HandleMessage::releaseMsgListener();
}

bool AppDelegate::applicationDidFinishLaunching() 
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();

	PathR::initialize();
	PathW::initialize();
	SystemData::initializeBasic();

	// Modify By Tony. 2014/9/28 10:54
	// refactor code;
	// use different listener;
	// gsMsglistener is used for connecting GS
	// amsMsglistener is used for connecting AMS

	//HandleMessage::s_msglistener = new MsgListener();
	//pDirector->getScheduler()->scheduleUpdateForTarget(HandleMessage::s_msglistener, -1, false);
	//HandleMessage::s_msglistener->retain();
	HandleMessage::createMsgListener();

	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 30);

	pDirector->setProjection(kCCDirectorProjection2D);

	//load system data
	CCLog("initialize system data!!!");
	SystemData::initialize();

#ifdef _DEBUG
	// turn on display FPS
	pDirector->setDisplayStats(true);
#else
	pDirector->setDisplayStats(false);
#endif

	// create a scene. it's an autorelease object
	CCScene *pScene = SceneFactory::sceneWelcomeScene();

	// run
	pDirector->runWithScene(pScene);
	//////////////////////////////////////////////////////////////////////////
	CCNode *notNode = NotificationLayer::create();
	pDirector->setNotificationNode(notNode);
	notNode->onEnter();

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->pause();
	CCDirector::sharedDirector()->stopAnimation();
    CCLog("AppDelegate::applicationDidEnterBackground");

	// if you use SimpleAudioEngine, it must be pause
	if (!AudioLoader::isSilent())
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}

	// Modify By Tony. 2014/9/28 10:54
	// refactor code;
	// use different listener;
	// gsMsglistener is used for connecting GS
	// amsMsglistener is used for connecting AMS

// 	if (HandleMessage::s_msglistener && HandleMessage::s_msglistener->m_network)
// 	{
// 		HandleMessage::s_msglistener->m_network->setIsBackground(true);
// 	}
	HandleMessage::setIsBackground(true);
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	// Please refer to http://discuss.cocos2d-x.org/t/cocos2d-x-resume-from-background-issue/2717
	// for more information about why a stopAnimation is needed here
	CCDirector::sharedDirector()->stopAnimation();
	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->startAnimation();
    CCLog("AppDelegate::applicationWillEnterForeground");

	// if you use SimpleAudioEngine, it must resume here
	if (!AudioLoader::isSilent())
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}

	// Modify By Tony. 2014/9/28 10:54
	// refactor code;
	// use different listener;
	// gsMsglistener is used for connecting GS
	// amsMsglistener is used for connecting AMS

// 	if (HandleMessage::s_msglistener && HandleMessage::s_msglistener->m_network)
// 	{
// 		HandleMessage::s_msglistener->m_network->setIsBackground(false);
// 	}
	HandleMessage::setIsBackground(false);
}
