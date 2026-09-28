#include "ScriptUpdatePanel.h"
#include "LoadingModule.h"
#include "MsgDownload.h"
#include "LoginHelper.h"
#include "EffectDefinition.h"

#include "scene/panel/EffectSprite.h"

#include "ext/CCActionDestroy.h"

#include "controls/CPProgressBar.h"

#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/SystemData.h"
#include "userdata/UserData.h"

#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"

#include "network/HttpDownloadRunnable.h"

#include "script/LuaWrapper.h"

#include "res/PlistLoader.h"

#include "utils/StringUtils.h"


#define MAX_RETRY_COUNT 3


namespace DownloadType
{
	enum
	{
		download_null = 0,

		download_list,
		download_files,
	};
}

static bool getAnnouncement( std::string &announcement )
{
	if(Lua::instance()->call("g_get_download_file_announcement", 0, 1) &&
		Lua::instance()->pop_utf8(announcement))
	{
		return true;
	}

	CCLog(">>>Error: getAnnouncement, lua call g_get_download_file_announcement failed!");
	return false;
}

static bool getDownloadFileCnt( int &cnt )
{
	if(Lua::instance()->call("g_get_download_file_cnt", 0, 1) &&
		Lua::instance()->pop(cnt))
	{
		return true;
	}

	CCLog(">>>Error: getDownloadFileCnt, lua call g_get_download_file_cnt failed!");
	return false;
}

static bool downloadFileByName( const std::string &fileName, const std::string &fileFolder )
{
	const std::string &luaStr = ".lua";
	if(fileName.size() > luaStr.size())
	{
		HttpDownloadRunnable::instance().setLocalPath(fileFolder);
		HttpDownloadRunnable::instance().download(fileName);

		return true;
	}

	CCLog(">>>Error: downloadFileByName, fileName = %s, fileFolder = %s", fileName.c_str(), fileFolder.c_str());
	return false;
}

static void downloadFileByIndexDone(int index)
{
	Lua::instance()->push(index);
	if(Lua::instance()->call("g_set_download_file_name", 1))
	{
		return;
	}

	CCLog(">>>Error: downloadFileByIndexFinished, lua call g_get_download_file_name failed!");
}

static bool downloadFileByIndex( int index )
{
	std::string version;
	std::string fileFolder;
	std::string fileName;
	Lua::instance()->push(index);
	if(Lua::instance()->call("g_get_download_file_name", 1, 3)
		&& Lua::instance()->pop(version)
		&& Lua::instance()->pop(fileFolder)
		&& Lua::instance()->pop(fileName))
	{
		std::string path = fileFolder+"/"+fileName ;
//		UserData::setStringData(path,version,0);
//		if (UserData::getStringData(path,0) != version)
		{
//			UserData::setStringData(path,version,0);
			return downloadFileByName( fileName, fileFolder + "/");
		}
	}

	CCLog(">>>Error: downloadFileByIndex, lua call g_get_download_file_name failed!");
	return false;
}

///////ScriptUpdatePanel///////////////////////////////////////////////
ScriptUpdatePanel::ScriptUpdatePanel()
	:mProgressBar(NULL)
	,mProgressLabel(NULL)
	,mHeadAnim(NULL)
	,mDownloadCnt(0)
	,mDownloadIndex(0)
	,mDownloadType(DownloadType::download_null)
	,mRetryTimes(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

ScriptUpdatePanel::~ScriptUpdatePanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool ScriptUpdatePanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);
	PlistLoader::loadLoading();

	initUI();

	mRetryTimes = 0;
	downloadListFile();

	return true;
}

void ScriptUpdatePanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool ScriptUpdatePanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);
	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}
	return true;
}

void ScriptUpdatePanel::initUI()
{
	// bkg
	CCLayerColor *bkg = CCLayerColor::create(ccc4(0, 0, 0, 150));
	addChild(bkg);

	// progress
	CCSprite *progressBoard = LayoutData::getSprite(CPModuleName::LOADING, "progressBoard");
	addChild(progressBoard);

	const CCSize &boardSize = progressBoard->getContentSize();
	mProgressBar = CPProgressBar::create(LayoutData::getSprite(CPModuleName::LOADING, "progressBar"));
	mProgressBar->setPosition(ccp(boardSize.width/2 - 1, boardSize.height/2 + 1));
	progressBoard->addChild(mProgressBar);

	const int startX = LayoutData::getInt(CPModuleName::LOADING, "animStartX");
	mHeadAnim = EffectSprite::create(Effect::effect_loading);
	mHeadAnim->setPosition(ccp(startX, mProgressBar->getPositionY()));
	progressBoard->addChild(mHeadAnim);

	mProgressLabel = LayoutData::getLabelTTF(CPModuleName::LOADING, "percentNote");
	mProgressLabel->setPosition(ccp(boardSize.width/2, boardSize.height/2));
	progressBoard->addChild(mProgressLabel);
}

void ScriptUpdatePanel::refresh()
{
	if (mDownloadCnt > 0)
	{
		float percent = mDownloadIndex * 100.0f/mDownloadCnt;
		if (percent > 100.0f)
		{
			percent = 100.0f;
		}
		mProgressBar->setPercentage(percent);

		const int startX = LayoutData::getInt(CPModuleName::LOADING, "animStartX");
		mHeadAnim->setPositionX(startX + percent * mProgressBar->getContentSize().width/100.0f);

		const std::string &str = LayoutData::getString(CPModuleName::LOADING, "updateScript") + StringUtils::toString(percent) + "%";
		mProgressLabel->setString(str.c_str());
	}
}

void ScriptUpdatePanel::downloadListFile()
{
	CCLog(">>>downloadFilelist!");
	const std::string &url = LoginHelper::getDownloadURL();
	const int k = url.find_last_of("/");
	if(k >= 0)
	{
		const std::string &urlHead = url.substr(0, k + 1);
		const std::string &fileName = url.substr(k + 1);
		if(!fileName.empty())
		{
			HttpDownloadRunnable::instance().initThread();
			HttpDownloadRunnable::instance().setURLHead(urlHead);

			mDownloadType = DownloadType::download_list;
			if (!downloadFileByName(fileName, ""))
			{
				downloadDataFileEnd();
			}
		}
		else
		{
			CCLog(">>>Error: downloadListFile, fileName empty! url = %s", url.c_str());
			downloadDataFileEnd();
		}
	}
	else
	{
		CCLog(">>>Error: downloadListFile, wrong url! url = %s", url.c_str());
		downloadDataFileEnd();
	}
}

void ScriptUpdatePanel::downloadListFileResult( const std::string &result )
{
	CCLog(">>>downloadListFileResult: %s", result.c_str());
	if(!result.empty())
	{
		const std::string &fileName = result.substr(0, result.find_last_of("."));
		char cmd[128];
		sprintf(cmd, "require '%s'", fileName.c_str());
		bool test = Lua::instance()->call(cmd);
		if(test)
		{
			downloadDataFileBegin();
		}
		else
		{
			CCLog(">>>Error: downloadListFileResult, executeString filed!");
			downloadDataFileEnd();
		}
	}
	else
	{
		CCLog(">>>download file list again(%d)!", mRetryTimes);
		if(mRetryTimes >= MAX_RETRY_COUNT)
		{
			downloadDataFileEnd();
			return;
		}

		downloadListFile();
		mRetryTimes++;
	}
}

void ScriptUpdatePanel::downloadDataFileBegin()
{
	CCLog(">>>downloadDataFileBegin!");

	mDownloadType = DownloadType::download_files;
	mRetryTimes = 0;
	mDownloadIndex = 1;

	int downloadCnt = 0;
	bool test = getDownloadFileCnt(downloadCnt);
	if(test)
	{
		mDownloadCnt = downloadCnt;
		if (mDownloadCnt > 0)
		{
			if(!downloadFileByIndex(mDownloadIndex))
			{
				downloadDataFileEnd();
			}
		}
		else
		{
			downloadDataFileEnd(true);
		}
		
	}
	else
	{
		downloadDataFileEnd();
	}
}

void ScriptUpdatePanel::downloadDataFileResult( const std::string &result )
{
	CCLog(">>>downloadDataFileResult: %s", result.c_str());

	if(!result.empty())
	{
		mRetryTimes = 0;
		downloadFileByIndexDone(mDownloadIndex++);
	}
	else
	{
		CCLog(">>>download file again(%d), file index = %d", mRetryTimes, mDownloadIndex);

		if(mRetryTimes >= MAX_RETRY_COUNT)
		{
			downloadDataFileEnd();
			return;
		}
		mRetryTimes++;
	}

	if(mDownloadIndex >= mDownloadCnt + 1)
	{
		downloadDataFileEnd(true);
	}
	else
	{
		bool test = downloadFileByIndex(mDownloadIndex);
		if(!test)
		{
			downloadDataFileEnd();
		}
	}
}

void ScriptUpdatePanel::downloadDataFileEnd( bool success /*= false*/ )
{
	mDownloadType = DownloadType::download_null;
	HttpDownloadRunnable::instance().exit();
	if(success)
	{
		CCLog(">>>downloadDataFileEnd(success)!");
		
		int gameVersion = 0, dataVersion = 0;
		LoginHelper::getServerVersion(gameVersion, dataVersion);
		SystemData::setDataVersion(dataVersion);

		CPEventHelper::uiNotify("ScriptUpdatePanel::downloadDataFileEnd", "", 0);
		StaticData::reloadLuaFiles();

		// show announcement
		std::string announcement;
		getAnnouncement(announcement);
		if(!announcement.empty())
		{
			const std::string &title = LayoutData::getString(CPModuleName::LOGIN, "announcementTitle");
			CCMessageBox(announcement.c_str(), title.c_str());
		}
	}
	else
	{
		CCLog(">>>downloadDataFileEnd(failed)!!!");
	}

	runAction(CCSequence::create(
		CCDelayTime::create(0.1f)
		, CCActionInstantRemoveFromParent::create()
		, NULL));
}

void ScriptUpdatePanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageDownload")
		{
			const std::string &result = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
			if(mDownloadType == DownloadType::download_list)
			{
				downloadListFileResult(result);
			}
			else if(mDownloadType == DownloadType::download_files)
			{
				refresh();
				downloadDataFileResult(result);
			}
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageDownloadProgress")
		{
			const std::string &key = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
			const int percent = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
			CCLog("download>%s(%d%%)", key.c_str(), percent);
		}
	}
}
