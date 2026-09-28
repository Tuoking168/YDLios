#include "ResLoading.h"
#include "LoadingModule.h"
#include "SceneFactory.h"
#include "PlatformDefinition.h"
#include "EffectDefinition.h"

#include "scene/SceneManager.h"
#include "scene/panel/EffectSprite.h"

#include "controls/CPProgressBar.h"
#include "controls/CPUpdater.h"
#include "controls/CPRichText.h"

#include "res/PlistLoader.h"
#include "res/AudioLoader.h"

#include "utils/StringUtils.h"
#include "utils/RichTextUtils.h"

#include "script/LuaWrapper.h"

#include "logic/platform/IPlatform.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"

static std::string getRandomTips()
{
	std::string ret;
	Lua::instance()->call("g_get_random_tips", 0, 1);
	Lua::instance()->pop_utf8(ret);
	return ret;
}

/////////ResLoading//////////////////////////////////////////////
ResLoading::ResLoading()
	:mProgressBar(NULL)
	,mPercentLabel(NULL)
	,mHeadAnim(NULL)
	,mTotalSource(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

ResLoading::~ResLoading()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool ResLoading::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	PlistLoader::unloadLogin();
	PlistLoader::loadLoading();

	mTotalSource = PlistLoader::getMainCount();

	initUI();

	return true;
}

void ResLoading::initUI()
{
	// bkg
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::jvyou
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::shouyougu_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::kugou_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::vivo_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::coolpay_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::lenovo_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::qixiazi_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::youlong_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::lingqisan_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::uc_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::huawei_lieyanzhanshen)
	{
		CCSprite *bkg = LayoutData::getSpriteByFile(CPModuleName::LOADING, "bkgLieYanZhanShen");
		addChild(bkg);
	}
	else
	{
		CCSprite *bkg = LayoutData::getSprite(CPModuleName::LOADING, "bkg");
		addChild(bkg);
	}
	
	// progress
	CCSprite *progressBoard = LayoutData::getSprite(CPModuleName::LOADING, "progressBoard");
	addChild(progressBoard);

	const CCSize &boardSize = progressBoard->getContentSize();
	mProgressBar = CPProgressBar::create(LayoutData::getSprite(CPModuleName::LOADING, "progressBar"));
	if (!mProgressBar) return;
	mProgressBar->setPosition(ccp(boardSize.width/2 - 1, boardSize.height/2 + 1));
	progressBoard->addChild(mProgressBar);

	const int startX = LayoutData::getInt(CPModuleName::LOADING, "animStartX");
	mHeadAnim = EffectSprite::create(Effect::effect_loading);
	if (!mHeadAnim) return;
	mHeadAnim->setPosition(ccp(startX, mProgressBar->getPositionY()));
	progressBoard->addChild(mHeadAnim);

	mPercentLabel = LayoutData::getLabelTTF(CPModuleName::LOADING, "percentNote");
	mPercentLabel->setPosition(ccp(boardSize.width/2, boardSize.height/2));
	progressBoard->addChild(mPercentLabel);

	// note
	const int fontSize = LayoutData::getInt(CPModuleName::LOADING, "tipsNoteFontSize");
	CPRichText *tipsNote = RichTextUtils::getRichText(getRandomTips(), fontSize);
	tipsNote->setPosition(LayoutData::getPoint(CPModuleName::LOADING, "tipsNote"));
	addChild(tipsNote);

	// update
	CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(ResLoading::onUpdate));
	updater->setUpdateTimes(mTotalSource);
	updater->setFinishHandler(this, callfunc_selector(ResLoading::onUpdateEnd));
	addChild(updater);
	updater->start();
}

void ResLoading::onUpdate( int index )
{
	PlistLoader::loadMain(index + 1);
	const float percent = (index + 1) * 100.0f/(mTotalSource + 0.1f);
	if (mProgressBar) mProgressBar->setPercentage(percent);

	const int startX = LayoutData::getInt(CPModuleName::LOADING, "animStartX");
	mHeadAnim->setPositionX(startX + percent * mProgressBar->getContentSize().width/100.0f);

	std::string progressStr = StringUtils::toString(percent) + "%";
	if (mPercentLabel) mPercentLabel->setString(progressStr.c_str());
}

void ResLoading::onUpdateEnd()
{
	if (mProgressBar) mProgressBar->setPercentage(100.0f);
	std::string progressStr = StringUtils::toString(100) + "%";
	if (mPercentLabel) mPercentLabel->setString(progressStr.c_str());
	enterGame();
}

void ResLoading::enterGame()
{
	GameData::s_game_state = GAME_STATE_RUNNING;
	GameData::s_user->enterGameRequest();
	scheduleOnce(schedule_selector(ResLoading::checkTimeOut), 60.0f);
}

void ResLoading::checkTimeOut( float dt )
{
	backLogin();
}

void ResLoading::backLogin()
{
	SceneManager::switchToLogin();
}

void ResLoading::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageEnterGameResponse")
		{
			if (!CPEventHelper::isRequestSuccess())
			{
				backLogin();
			}
		}
	}
}
