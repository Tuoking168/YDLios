#include "WelcomeScene.h"
#include "SceneFactory.h"
#include "LoginModule.h"
#include "PlatformDefinition.h"

#include "res/PlistLoader.h"
#include "res/Path.h"

#include "userdata/GameData.h"
#include "userdata/LayoutData.h"

#include "logic/platform/IPlatform.h"

#include "utils/StringUtils.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "../SystemData.h"


using namespace cocos2d;


// on "init" you need to initialize your instance
bool WelcomeScene::init()
{
	if (!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
	{
		return false;
	}
	PlistLoader::loadCommon();
	PlistLoader::loadWelcome();
	doLoad();

	initUI();

	CCLog("start loading scene done!!!");
	return true;
}

void WelcomeScene::initUI()
{
#define DELAY_TIME 2.0f
#define FADE_TIME 1.0f

	float totalDelayTime = 0;
 
	const int channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	const std::string &channelLogoFrameName = LayoutData::getString(CPModuleName::LOGIN, "channelLogo" + StringUtils::toString(channelID));
	if (!channelLogoFrameName.empty())
	{
		CCSprite *channelLogo = LayoutData::getSpriteByFrameName(channelLogoFrameName);
		channelLogo->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
		addChild(channelLogo);
		channelLogo->runAction(CCSequence::create(
			CCDelayTime::create(DELAY_TIME)
			, CCFadeOut::create(FADE_TIME)
			, NULL));
		totalDelayTime += DELAY_TIME + FADE_TIME;
	}
 
	CCSprite *logo = LayoutData::getSprite(CPModuleName::LOGIN, "welcome");
	CCSprite *logo_lingfeng = LayoutData::getSprite(CPModuleName::LOGIN, "logo_lingfeng");
	CCSprite *logo_ceapon = LayoutData::getSprite(CPModuleName::LOGIN, "logo_ceapon");
	int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::_35i_another
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::wdj_jianzhixuanyuan
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::qihoo_jianzhixuanyuan
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::duoku_jianzhixuanyuan
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::mi_jianzhixuanyuan)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoJianZhiXuanYuan");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::jvyou
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
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoLieYanZhanShen");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::muzhiwan_rexuetulong
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::shouyougu_ruanyou)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoReXueTuLong");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::sijiuyou_xueren)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoXueRen");
	}else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_chuanqizhanshen)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoChuanQiZhanShen");
	}else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_yingxiongchuanqi)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoYingXiongChuanQi");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_shachengchuanqi)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoShaChengChuanQi");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::shoumeng_chiyanzhanshen)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoChiYanZhanShen");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::youmi_menghuishacheng)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoMengHuiShaCheng");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::youmi_jinglongzhuan)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoJingLongZhuan");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::aboluo_rexuetianya)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoReXueTianYa");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::fivegame_damodaoge)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoDaMoDaoGe");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::yayawan_badao)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoBaDao");
	}
	logo->setOpacity(0);
	addChild(logo);
	//
	std::string warning = SystemData::getLayoutString("friendly_warning.text");
	std::string title = SystemData::getLayoutString("friendly_warning.title");
	if (!warning.empty() && !title.empty())
	{
		CCLayer* layer = CCLayer::create();
		std::string fontName = SystemData::getLayoutString("friendly_warning.font.name");
		float titleFontSize = SystemData::getLayoutValue("friendly_warning.title.font.size");
		CCLabelTTF* titleLabel = CCLabelTTF::create(title.c_str(), fontName.c_str(), titleFontSize);
		titleLabel->setFontFillColor(ccc3(0, 0, 0));
		titleLabel->setColor(ccc3(0, 0, 0));
		layer->addChild(titleLabel);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		titleLabel->setAnchorPoint(CCPoint(0.5f, 1.0f));
		titleLabel->setPosition(CCPoint(winSize.width / 2.0f, winSize.height - 5));
		float fontSize = SystemData::getLayoutValue("friendly_warning.text.font.size");
		std::string::size_type pos = 0;
		float lineSpace = SystemData::getLayoutValue("friendly_warning.line.space");
		float ybase = winSize.height - titleFontSize - 10;
		int nstatement = 0;
		while (true)
		{
			std::string::size_type npos = warning.find('\n', pos);
			int count = npos == std::string::npos ? warning.size() - pos : npos - pos;
			std::string statement = warning.substr(pos, count);
			CCLabelTTF* warningLabel = CCLabelTTF::create(statement.c_str(), fontName.c_str(), fontSize);
			warningLabel->setFontFillColor(ccc3(0, 0, 0));
			warningLabel->setColor(ccc3(0, 0, 0));
			
			warningLabel->setAnchorPoint(CCPoint(0.5f, 1.0f));
			warningLabel->setPosition(CCPoint(winSize.width / 2.0f, ybase - lineSpace * nstatement));
			layer->addChild(warningLabel);
			if (npos == std::string::npos) break;
			pos = npos + 1;
			++ nstatement;
		}
		addChild(layer);
	}
	
	if (logo_lingfeng)
	{
		logo_lingfeng->setOpacity(0);
		addChild(logo_lingfeng);
	}
	if (logo_ceapon)
	{
		logo_ceapon->setOpacity(0);
		addChild(logo_ceapon);
	}
	if (totalDelayTime > 0)
	{
		logo->runAction(CCSequence::create(
			CCDelayTime::create(DELAY_TIME)
			, CCFadeIn::create(FADE_TIME)
			, CCDelayTime::create(DELAY_TIME)
			, CCFadeOut::create(FADE_TIME)
			, NULL));
		
		if (logo_lingfeng)
		{
			logo_lingfeng->runAction(CCSequence::create(
				CCDelayTime::create(DELAY_TIME)
				, CCFadeIn::create(FADE_TIME)
				, CCDelayTime::create(DELAY_TIME)
				, CCFadeOut::create(FADE_TIME)
				, NULL));
		}
		if (logo_ceapon)
		{
			logo_ceapon->runAction(CCSequence::create(
				CCDelayTime::create(DELAY_TIME)
				, CCFadeIn::create(FADE_TIME)
				, CCDelayTime::create(DELAY_TIME)
				, CCFadeOut::create(FADE_TIME)
				, NULL));
		}
	}
	else
	{
		logo->runAction(CCSequence::create(
			CCFadeIn::create(0)
			, CCDelayTime::create(DELAY_TIME)
			, CCFadeOut::create(FADE_TIME)
			, NULL));
		if (logo_lingfeng)
		{
			logo_lingfeng->runAction(CCSequence::create(
				CCFadeIn::create(0)
				, CCDelayTime::create(DELAY_TIME)
				, CCFadeOut::create(FADE_TIME)
				, NULL));
		}
		if (logo_ceapon)
		{
			logo_ceapon->runAction(CCSequence::create(
				CCFadeIn::create(0)
				, CCDelayTime::create(DELAY_TIME)
				, CCFadeOut::create(FADE_TIME)
				, NULL));
		}	
	}
	totalDelayTime += DELAY_TIME + FADE_TIME;
 
	runAction(CCSequence::create(
	 	CCDelayTime::create(totalDelayTime),
		 CCCallFunc::create(this, callfunc_selector(WelcomeScene::loadingOut))
		, NULL));
}

void WelcomeScene::onEnter()
{
	CCLayer::onEnter();
}

void WelcomeScene::doLoad()
{
	CCLog("loading user data ... ...");
	GameData::initUserData();
	GameData::initNetWorkHandle();
	GameData::initMapData();
}

void WelcomeScene::loadingOut()
{
	PathR::initialize();
	PathW::initialize();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(
		SceneFactory::switch_time,SceneFactory::sceneLogin()));
}