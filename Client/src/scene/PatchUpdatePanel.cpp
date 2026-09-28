#include "PatchUpdatePanel.h"
#include "LoadingModule.h"
#include "MsgDownload.h"
#include "LoginHelper.h"
#include "ModuleData.h"
#include "EffectDefinition.h"

#include "scene/panel/EffectSprite.h"

#include "controls/CPProgressBar.h"

#include "userdata/LayoutData.h"

#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"

#include "network/HttpDownloadRunnable.h"

#include "res/PlistLoader.h"

#include "logic/platform/IPlatform.h"

#include "utils/StringUtils.h"


#define MAX_RETRY_COUNT 3

static bool downloadFileByName( const std::string &fileName, const std::string &fileFolder )
{
	const std::string &patchStr = ".patch";
	const std::string &folderStr = "/";
	if(fileName.size() > patchStr.size()
		&& fileFolder.size() > folderStr.size())
	{
		HttpDownloadRunnable::instance().setLocalPath(fileFolder, true);
		HttpDownloadRunnable::instance().download(fileName);
		return true;
	}

	CCLog(">>>Error: downloadFileByName, fileName = %s, fileFolder = %s", fileName.c_str(), fileFolder.c_str());
	return false;
}

////////////PatchUpdatePanel/////////////////////////////////////////
PatchUpdatePanel::PatchUpdatePanel()
	:mProgressBar(NULL)
	,mProgressLabel(NULL)
	,mHeadAnim(NULL)
	,mRetryTimes(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

PatchUpdatePanel::~PatchUpdatePanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool PatchUpdatePanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);
	PlistLoader::loadLoading();

	initUI();

	mRetryTimes = 0;
	downloadPatchFile();

	return true;
}

void PatchUpdatePanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool PatchUpdatePanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
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

void PatchUpdatePanel::initUI()
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

void PatchUpdatePanel::refresh( int percent )
{
	mProgressBar->setPercentage(percent);

	const int startX = LayoutData::getInt(CPModuleName::LOADING, "animStartX");
	mHeadAnim->setPositionX(startX + percent * mProgressBar->getContentSize().width/100.0f);

	const std::string &str = LayoutData::getString(CPModuleName::LOADING, "updatePatch") + StringUtils::toString(percent) + "%";
	mProgressLabel->setString(str.c_str());
}

void PatchUpdatePanel::downloadPatchFile()
{
	CCLog(">>>downloadPatchFile!");
	const std::string url = LoginHelper::getDownloadURL();
	const int k = url.find_last_of("/");
	if(k >= 0)
	{
		const std::string &urlHead = url.substr(0, k + 1);
		const std::string &fileName = url.substr(k + 1);
		if(!fileName.empty())
		{
			ModuleData::setString(CPModuleName::LOGIN, CPLoginData::PATCH_FILE_NAME, fileName);
			HttpDownloadRunnable::instance().initThread();
			HttpDownloadRunnable::instance().setURLHead(urlHead);

			const std::string &witePath = CPPlatformMnger.getStringData(CPPlatformData::EXT_WRITE_PATH)
				+ CPPlatformMnger.getStringData(CPPlatformData::PACKAGE_NAME) + "/";
			if (!downloadFileByName(fileName, witePath))
			{
				downloadPatchFileEnd();
			}
		}
		else
		{
			CCLog(">>>Error: downloadPatchFile, fileName empty! url = %s", url.c_str());
			downloadPatchFileEnd();
		}
	}
	else
	{
		CCLog(">>>Error: downloadPatchFile, wrong url! url = %s", url.c_str());
		downloadPatchFileEnd();
	}
}

void PatchUpdatePanel::downloadPatchFileResult( const std::string &result )
{
	CCLog(">>>downloadPatchFileResult: %s", result.c_str());
	if(!result.empty())
	{
		downloadPatchFileEnd(true);
	}
	else
	{
		CCLog(">>>download patch file again(%d)!", mRetryTimes);
		if(mRetryTimes >= MAX_RETRY_COUNT)
		{
			downloadPatchFileEnd();
			return;
		}

		downloadPatchFile();
		mRetryTimes++;
	}
}

void PatchUpdatePanel::downloadPatchFileEnd( bool success /*= false*/ )
{
	HttpDownloadRunnable::instance().exit();
	if(success)
	{
		CCLog(">>>downloadPatchFileEnd(success)!");
		mProgressLabel->setString(LayoutData::getString(CPModuleName::LOADING, "patchNewPackage").c_str());
		CPPlatform->operate(PlatformOpID::patch_and_install_package);
	}
	else
	{
		CCLog(">>>downloadPatchFileEnd(failed)!!!");
		mProgressLabel->setString(LayoutData::getString(CPModuleName::LOADING, "updatePatchFailed").c_str());
	}
}

void PatchUpdatePanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageDownload")
		{
			const std::string &result = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
			downloadPatchFileResult(result);
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageDownloadProgress")
		{
			const int percent = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
			refresh(percent);
		}
	}
}
