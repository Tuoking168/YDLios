#include "Login.h"
#include "LoginHelper.h"
#include "ModuleData.h"
#include "Event.h"
#include "ErrorDefinition.h"
#include "SceneManager.h"
#include "ScriptUpdatePanel.h"
#include "PatchUpdatePanel.h"
#include "PlatformDefinition.h"

#include "NotificationHelper.h"
#include "panel/FloatPanel.h"

#include "logic/platform/PlatformOpID.h"
#include "logic/platform/IPlatform.h"

#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"
#include "controls/CPChecker.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "userdata/LayoutData.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SceneData.h"
#include "userdata/StaticData.h"
#include "userdata/ActivityData.h"

#include "res/PlistLoader.h"
#include "res/AudioLoader.h"
#include "res/CPAnimationManager.h"

#include "utils/StringUtils.h"

#include "ext/CCFlashAnimation.h"
#include "ext/GeneralMenu.h"
#include "ext/CCMenuEx.h"
#include "ext/md5.h"
#include "VIPModule.h"

#include "ext/json/json.h"
#include "controls/CPNodeHelper.h"

#include "script/LuaWrapper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../../ios/channel/common/ChannelHelper.h"
#endif

#include "logic/platform/AndroidPlatform.h"
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
//#include <regex>  
//#endif  
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
//#include <regex.h>
//#endif

#define STRONG_UPDATE_WITHOUT_ALERT

const float BKG_SPEED = 100;
const float CLOUD_SPEED = 80;

static const int ITEM_UNUSE_TAG = -1000;
static const float DOUBLE_CLICK_TIME = 0.2f;

#define PARTICLE_SYSTEM_TAG 102

bool Login::s_swordAnimationEnd = false;
///////////Login///////////////////////////////////////////////////////
Login::Login()
	:_light(NULL), _light_screen(NULL)
{
	LoginHelper::setLoginNode(this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CHANNELHELPER->setInLogin(true);
#endif
}

Login::~Login()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CHANNELHELPER->setInLogin(false);
#endif
	LoginHelper::setLoginNode(NULL);
}

Login * Login::create()
{
	return create(LoginView::login);
}

Login * Login::create( int viewID )
{
	Login *ret = new Login;
	if (ret && ret->initWithData(viewID))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool Login::initWithData( int viewID )
{
	if (!CCLayer::init())
	{
		return false;
	}
    Login::s_swordAnimationEnd = false;
	GameData::s_game_state = GAME_STATE_LOGIN;
	SceneData::setHasEnterScene(false);
	AudioLoader::transform(Sound::Music::login);

	PlistLoader::unloadWelcome();
	PlistLoader::loadCommon();
	PlistLoader::loadLogin();

	initUI();

	if (LoginView::login <= viewID &&
		viewID <= LoginView::selectrole)
	{
		LoginHelper::switchView(viewID);
	}
	else
	{
		LoginHelper::switchView(LoginView::login);
	}

	CPPlatform->operate(PlatformOpID::install_package_if_needed);

	return true;
}
void Login::initUI()
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
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::aboluo_rexuetianya
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::lingqisan_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::uc_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::huawei_lieyanzhanshen)
	{
		CCSprite *bkg = LayoutData::getSpriteByFile(CPModuleName::LOGIN, "bkgLieYanZhanShen");
		if (bkg)
		{
			addChild(bkg);
		}
		// When receiving check version response, it requires this value to be true to continue
		// For most channels, swordAnimationEnd() will be scheduled to set this variable to true
		// But for this one, it will not do that, so set it to true here
		// Ronghui Yu, Nov 25, 2014
		swordAnimationEnd();
		return;
	}

	CCSprite *bkg = LayoutData::getSpriteByFile(CPModuleName::LOGIN, "bkg");
	if (bkg)
	{
		addChild(bkg);
	}

	_light = CCSprite::create();
	if (_light)
	{
		_light->setAnchorPoint(ccp(0.5f, 1.0f));
		_light->setPosition(ccp(400, 480));
		_light->setVisible(false);
		const std::string &animPath = LayoutData::getString(CPModuleName::LOGIN, "light");
		CCFlashAnimation *lightAnim = CPAnimMnger.getAnimationOneDir(animPath);
		if (lightAnim) {
			_light->runAction(CCRepeatForever::create(lightAnim->getAnimate(0)));
			addChild(_light);
		}
	}

	CCSprite *bkgsword = LayoutData::getSprite(CPModuleName::LOGIN, "bkg_sword");
	if (bkgsword)
	{
		CCPoint pt = bkgsword->getPosition();
		bkgsword->setPosition(ccp(pt.x+200, pt.y+600));
		bkgsword->runAction(CCSequence::create(
                                               CCEaseIn::create(CCMoveTo::create(1.0f, pt), 8.0f),
                                               CCCallFunc::create(this, callfunc_selector(Login::swordAnimationEnd)),
                                               NULL));
		addChild(bkgsword);
	}

	CCParticleSystem* fire = CCParticleSystemQuad::create("data-a/particle/firex.plist");
	if (fire)
	{
		fire->setVisible(false);
		fire->setPosition(ccp(550, 60));
		fire->runAction(CCSequence::createWithTwoActions(
			CCDelayTime::create(1.0f),
			CCShow::create())
			);
		addChild(fire);
	}

	CCSprite *bkgswordcover = LayoutData::getSprite(CPModuleName::LOGIN, "bkg_sword_cover");
	if (bkgswordcover)
	{
		bkgswordcover->setVisible(false);
		bkgswordcover->runAction(CCSequence::createWithTwoActions(
			CCDelayTime::create(0.9f),
			CCShow::create())
			);
		addChild(bkgswordcover);

		this->runAction(CCSequence::createWithTwoActions(
			CCDelayTime::create(1.0f),
			CCJumpTo::create(0.3f, getPosition(), -4, 2))
			);
	}

	ccColor4B color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 50;
	_light_screen = CCLayerColor::create(color);
	if (_light_screen)
	{
		_light_screen->setVisible(false);
		addChild(_light_screen, 1);
	}

	CCLog("TONY BIN trace : Login!!");

	scheduleLight();
}
void Login::swordAnimationEnd()
{
    Login::s_swordAnimationEnd = true;
    CPEventHelper::dispatcher(CPEventName::UI_NOTIFY, "swordAnimationEnd", "");
}
void Login::scheduleLight()
{
	runAction(CCSequence::create(
		CCDelayTime::create(float(rand()%90)/10),
		CCCallFunc::create(this, callfunc_selector(Login::showLight)),
		CCDelayTime::create(0.4f),
		CCCallFunc::create(this, callfunc_selector(Login::hideLight)),
		NULL
		)
		);
}

void Login::showLight()
{
	if (_light && _light_screen)
	{
		_light->setPosition(ccp(300+rand()%400, 480));
		_light->setScale(float(90+rand()%40)/100);
		_light->setFlipX(rand()%2==0);
		_light->setVisible(true);
		_light_screen->setVisible(true);
	}
}

void Login::hideLight()
{
	if (_light && _light_screen)
	{
		_light->setVisible(false);
		_light_screen->setVisible(false);
		scheduleLight();
	}
}

///////////LoginFace//////////////////////////////////////////////////
static bool needShowCheckVersionButton()
{
	const int channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	const std::string &key = "hideCheckVersionBtn" + StringUtils::toString(channelID);
	const int hideFlag = LayoutData::getInt(CPModuleName::LOGIN, key);
	return (hideFlag == 0);
}

int LoginFace::s_mini=0;

LoginFace::LoginFace()
	:mChecker(NULL)
	,mVersionLabel(NULL)
	,mEnterLabel(NULL)
	,mAnnouncementLayer(NULL)
	,mAnnouncement(NULL)
    ,mNeedUpdate(TypeLoading)
    ,mTouchTip(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::LGC_PLATFORM, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_NOTIFY, this);
	CPEvtDispatcher.addEventListener(CPEventName::NET_CHANGE, this);
}

LoginFace::~LoginFace()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_PLATFORM, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_NOTIFY, this);
	CPEvtDispatcher.removeEventListener(CPEventName::NET_CHANGE, this);
	//CPEvtDispatcher.removeEventListener(this);
}

bool LoginFace::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	setKeypadEnabled(true);
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) != ChannelID::tencent_msdk)
	{
		setTouchEnabled(true);
	}
	initUI();

	return true;
}

void LoginFace::onEnter()
{
	CCLayer::onEnter();
	LoginHelper::startAuthServer();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	sendMsgTo3737();
#endif //
}

void LoginFace::initUI()
{
	CCSprite *logo = LayoutData::getSprite(CPModuleName::LOGIN, "loginLogo");
	if (logo)
	{
		const CCPoint pt = logo->getPosition();
		if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::_35i_another
			|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::wdj_jianzhixuanyuan
			|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::qihoo_jianzhixuanyuan
			|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::duoku_jianzhixuanyuan)
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
		}else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::muzhiwan_rexuetulong)
		{
			logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoReXueTuLong");
		}else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::sijiuyou_xueren)
		{
			logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoXueRen");
		}else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_chuanqizhanshen)
		{
			logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoChuanQiZhanShen");
		}else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_yingxiongchuanqi)
		{
			logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoYingXiongChuanQi");
		}
		else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::shoumeng_chiyanzhanshen)
		{
			logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoChiYanZhanShen");
		}
		else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::shoumeng_lieyanfentian)
		{
			logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoLieYanFenTian");
		}
		else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_shachengchuanqi)
		{
			logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoShaChengChuanQi");
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
		logo->setPosition(ccp(pt.x, pt.y+300));
		logo->runAction(CCSequence::createWithTwoActions(
			CCDelayTime::create(1.0f),
			CCEaseBackInOut::create(CCMoveTo::create(0.5f, pt))
			));
		addChild(logo);
	}

	initBtns();

	// announcement
	mAnnouncementLayer = CCLayer::create();
	addChild(mAnnouncementLayer);

	CCSprite *announcementBoard = LayoutData::getSprite(CPModuleName::LOGIN, "announcementBoard");
	mAnnouncementLayer->addChild(announcementBoard);

	CCLabelTTF *announcementTitleLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "announcementTitle");
	mAnnouncementLayer->addChild(announcementTitleLabel);

	//
	
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) != ChannelID::tencent_msdk)
	{
		mEnterLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "clickLogin");
		if (mEnterLabel)
		{
			mEnterLabel->setVisible(false);
			mEnterLabel->setOpacity(0);
			mEnterLabel->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(
				CCFadeIn::create(1.0f),
				CCFadeOut::create(2.0f))
				));
			addChild(mEnterLabel);
		}
	}

	// version
	mVersionLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "version");
	mVersionLabel->setString(SystemData::getVersion().c_str());
	addChild(mVersionLabel);

	// check version button
	if (needShowCheckVersionButton())
	{
		CCMenu *menu = CCMenu::create();
		menu->setPosition(CCPointZero);
		addChild(menu);

		int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
		if (channel_id != ChannelID::ios_91 && channel_id != ChannelID::_91 && channel_id != ChannelID::ios_appstore
			&& channel_id != ChannelID::ios_3737 && channel_id != ChannelID::ios_3737_hl && channel_id != ChannelID::ios_3737_pgy)
		{
			CCMenuItemImage *checkVersionBtn = LayoutData::getMenuItemLabelImage(CPModuleName::LOGIN, "checkVersion");
			if (checkVersionBtn)
			{
				checkVersionBtn->setTarget(this, menu_selector(LoginFace::onCheckVersionManual));
				menu->addChild(checkVersionBtn);
			}
		}	
	}

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);

	m_moveLabel = ScrollLabel::create();
	addChild(m_moveLabel);
    
    showTouchTip(SystemData::getLayoutString("login_checkVersion"));

}
void LoginFace::showTouchTip(std::string note)
{
    if (mTouchTip==NULL) {
        mTouchTip = CPTouchTip::create();
        if (mTouchTip) {
            mTouchTip->setString(note);
            
            CCDirector::sharedDirector()->getNotificationNode()->addChild(mTouchTip);
        }else{
            mTouchTip = NULL;
        }
    }
}
void LoginFace::hideTouchTip()
{
    if (mTouchTip) {
        mTouchTip->removeFromParent();
        mTouchTip = NULL;
    }
}

void LoginFace::initBtns()
{
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::tencent_msdk)
	{
		CCMenu *menu = CCMenu::create();
		menu->setPosition(CCPointZero);
		addChild(menu);

		CCMenuItemImage *weixinBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "weixinbtn");
		if (weixinBtn)
		{
			weixinBtn->setTag(Tag_weixin);
			weixinBtn->setTarget(this, menu_selector(LoginFace::onLoginQQorWeinxin));
			menu->addChild(weixinBtn);
		}

		CCMenuItemImage *qqphoneBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "qqphonebtn");
		if (qqphoneBtn)
		{
			qqphoneBtn->setTag(Tag_qqphone);
			qqphoneBtn->setTarget(this, menu_selector(LoginFace::onLoginQQorWeinxin));
			menu->addChild(qqphoneBtn);
		}
	}
}

void LoginFace::onLoginQQorWeinxin( CCObject *target )
{
	CCNode* pNode = dynamic_cast<CCNode*>(target);
	if (pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case Tag_weixin:
			CPPlatform->operate(PlatformOpID::weixin_login);
			break;
		case Tag_qqphone:
			CPPlatform->operate(PlatformOpID::qq_login);
			break;
		default:
			break;
		}
	}
}

void LoginFace::showStrongUpdateNote()
{
	NotePanel *subPanel = NotePanel::create(NotePanel::confirm_only);
	subPanel->setTitle(LayoutData::getString(CPModuleName::LOGIN, "strongUpdateTitle"));
	subPanel->setContent(LayoutData::getString(CPModuleName::LOGIN, "strongUpdateContent"));
	subPanel->setHandler(this, notepanel_selector(LoginFace::onVersionUpdate));
	CPTips *tips = CPTips::create(subPanel, CPTipsType::modal);
	tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
	addChild(tips);
}

void LoginFace::showScriptUpdateNote()
{
#ifndef STRONG_UPDATE_WITHOUT_ALERT
	NotePanel *subPanel = NotePanel::create(NotePanel::confirm_only);
	subPanel->setTitle(LayoutData::getString(CPModuleName::LOGIN, "scriptUpdateTitle"));
	subPanel->setContent(LayoutData::getString(CPModuleName::LOGIN, "scriptUpdateContent"));
	subPanel->setHandler(this, notepanel_selector(LoginFace::onScriptUpdate));
	CPTips *tips = CPTips::create(subPanel, CPTipsType::modal);
	tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
	addChild(tips);
#else
    if(Login::s_swordAnimationEnd)
    {
        onScriptUpdate(0);
    }
    else
    {
        mNeedUpdate = TypeOnScriptUpdate;
    }
#endif
}

void LoginFace::showOptionalUpdateNote()
{
	NotePanel *subPanel = NotePanel::create(NotePanel::confirm_only);
	subPanel->setTitle(LayoutData::getString(CPModuleName::LOGIN, "optionalUpdateTitle"));
	subPanel->setContent(LayoutData::getString(CPModuleName::LOGIN, "optionalUpdateContent"));
	subPanel->setHandler(this, notepanel_selector(LoginFace::onOptionalVersionUpdate));
	CPTips *tips = CPTips::create(subPanel, CPTipsType::modal);
	tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
	addChild(tips);
}

void LoginFace::showStrongUpdateNoteEx()
{
	NotePanel *subPanel = NotePanel::create(NotePanel::confirm_only);
	const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
	switch (type)
	{
	case NotePanel::updatetype_gameVersion:
	case NotePanel::updatetype_svnVersion:
		{
			subPanel->setTitle(LayoutData::getString(CPModuleName::LOGIN, "strongUpdateTitle"));
			subPanel->setContent(LayoutData::getString(CPModuleName::LOGIN, "strongUpdateContent"));
			subPanel->setHandler(this, notepanel_selector(LoginFace::onVersionUpdate));
		}
		break;
	case NotePanel::updatetype_dataVersion:
		{
#ifndef STRONG_UPDATE_WITHOUT_ALERT
			subPanel->setTitle(LayoutData::getString(CPModuleName::LOGIN, "scriptUpdateTitle"));
			subPanel->setContent(LayoutData::getString(CPModuleName::LOGIN, "scriptUpdateContent"));
			subPanel->setHandler(this, notepanel_selector(LoginFace::onScriptUpdate));
#else
            if(Login::s_swordAnimationEnd)
            {
                onScriptUpdate(0);
            }
            else
            {
                mNeedUpdate = TypeOnScriptUpdate;
            }
            return;
#endif
		}
		break;
	default:
		{
			subPanel->setTitle(LayoutData::getString(CPModuleName::LOGIN, "scriptUpdateTitle"));
			subPanel->setContent(LayoutData::getString(CPModuleName::LOGIN, "scriptUpdateContent"));
			subPanel->setHandler(this, notepanel_selector(LoginFace::onVersionUpdate));
		}
		break;
	}
	CPTips *tips = CPTips::create(subPanel, CPTipsType::modal);
	tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
	addChild(tips);
}

void LoginFace::showOptionalUpdateNoteEx()
{
	NotePanel *subPanel = NotePanel::create(NotePanel::normal);
	const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
	switch (type)
	{
	case NotePanel::updatetype_gameVersion:
	case NotePanel::updatetype_svnVersion:
		{
			subPanel->setTitle(LayoutData::getString(CPModuleName::LOGIN, "strongUpdateTitle"));
			subPanel->setContent(LayoutData::getString(CPModuleName::LOGIN, "strongUpdateContent"));
			subPanel->setHandler(this, notepanel_selector(LoginFace::onOptionalVersionUpdate));
		}
		break;
	case NotePanel::updatetype_dataVersion:
		{
			subPanel->setTitle(LayoutData::getString(CPModuleName::LOGIN, "scriptUpdateTitle"));
			subPanel->setContent(LayoutData::getString(CPModuleName::LOGIN, "scriptUpdateContent"));
			subPanel->setHandler(this, notepanel_selector(LoginFace::onOptionalScriptUpdate));
		}
		break;
	default:
		{
			subPanel->setTitle(LayoutData::getString(CPModuleName::LOGIN, "strongUpdateTitle"));
			subPanel->setContent(LayoutData::getString(CPModuleName::LOGIN, "strongUpdateContent"));
			subPanel->setHandler(this, notepanel_selector(LoginFace::onOptionalVersionUpdate));
		}
		break;
	}

	CPTips *tips = CPTips::create(subPanel, CPTipsType::modal);
	tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
	addChild(tips);
}

void LoginFace::refreshAnnouncement()
{
	if (!mAnnouncement)
	{
		const CCSize &announcementSize = LayoutData::getSize(CPModuleName::LOGIN, "announcement");
		mAnnouncement = CPItemComponents::create(announcementSize, new CPLayoutList);
		mAnnouncement->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "announcement"));
		mAnnouncementLayer->addChild(mAnnouncement);

		const CCSize &barSize = LayoutData::getSize(CPModuleName::LOGIN, "announcementScroll");
		CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
		mAnnouncement->setScrollbar(scrollBar);
	}
	mAnnouncement->removeAllItems();

	const std::string &announcement = LoginHelper::getAnnouncement();
	CCLabelTTF *announcementLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "announcementContent");
	announcementLabel->setString(announcement.c_str());
	mAnnouncement->addItem(announcementLabel);
}

void LoginFace::hideAnnouncement()
{
	mAnnouncementLayer->setVisible(false);
}

void LoginFace::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	mChecker->start();
	CPPlatform->login();
}

void LoginFace::onVersionUpdate( int code )
{
	CPUnused(code);
	const int platformID = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID);
	if (platformID == PlatformID::android)
	{
		PatchUpdatePanel *panel = PatchUpdatePanel::create();
		addChild(panel);
	}
	else if (platformID == PlatformID::ios)
	{
		CCLog(">warning: strong update not implemented! platform(ios)");	
	}
	else
	{
		PatchUpdatePanel *panel = PatchUpdatePanel::create();
		addChild(panel);
		CCLog(">warning: strong update not implemented! platform(win32)");
	}
}

void LoginFace::onScriptUpdate( int code )
{
    mNeedUpdate = TypeNull;
	CPUnused(code);
	ScriptUpdatePanel *panel = ScriptUpdatePanel::create();
	addChild(panel);
}

void LoginFace::onOptionalVersionUpdate( int code )
{
	if (code == NotePanel::confirm)
	{
		const int platformID = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID);
		if (platformID == PlatformID::android)
		{
			PatchUpdatePanel *panel = PatchUpdatePanel::create();
			addChild(panel);
		}
		else if (platformID == PlatformID::ios)
		{
			CCLog(">warning: optional update not implemented! platform(ios)");
			//go to appstore shop
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#if defined (APPSTORE_VERSION) || defined (C3737_VERSION) || defined (C3737_PGY_VERSION) || defined (C3737_HL_VERSION)
			CHANNELHELPER->onDownload4AppStore();
			SceneManager::exitGame();
#endif
#endif
		}
		else
		{
			//PatchUpdatePanel *panel = PatchUpdatePanel::create();
			//addChild(panel);
			CCLog(">warning: optional update not implemented! platform(win32)");
		}
	}
	if (code == NotePanel::cancel)
	{
		if (CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID) == ChannelID::ios_appstore)
		{
			SceneManager::exitGame();
		}
	}
}

void LoginFace::onOptionalScriptUpdate( int code )
{
	if (code == NotePanel::confirm)
	{
		ScriptUpdatePanel *panel = ScriptUpdatePanel::create();
		addChild(panel);
	}
}

void LoginFace::onExitGame( int code )
{
	if (code == NotePanel::confirm)
	{
		SceneManager::exitGame();
	}
}

void LoginFace::keyBackClicked()
{
	CPPlatform->operate(PlatformOpID::exitGame);
	const int channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);

	if (channelID == ChannelID::_91
		|| channelID == ChannelID::sougou
		|| channelID == ChannelID::jvyou||channelID==ChannelID::youmi_jinglongzhuan)
		return;

	static const int EXIT_NOTE_TAG = 1172;
	CCNode *panel = getChildByTag(EXIT_NOTE_TAG);
	if (panel)
	{
		panel->removeFromParent();
	}
	else
	{
		NotePanel *subPanel = NotePanel::create(NotePanel::normal, 3 * kCCMenuHandlerPriority);
		subPanel->setTitle(LayoutData::getString(CPModuleName::LOGIN, "exitGameTitle"));
		subPanel->setContent(LayoutData::getString(CPModuleName::LOGIN, "exitGameContent"));
		subPanel->setHandler(this, notepanel_selector(LoginFace::onExitGame));
		CPTips *tips = CPTips::create(subPanel, CPTipsType::modal);
		tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
		addChild(tips, 1, EXIT_NOTE_TAG);
	}
}

void LoginFace::checkVersion()
{
	static bool bFirstScriptUpdate=true;
	int serverGameVersion = 0, serverDataVersion = 0;
	LoginHelper::getServerVersion(serverGameVersion, serverDataVersion);

	int gameVersion = 0, dataVersion = 0;
	SystemData::getVersion(gameVersion, dataVersion);
    
	if (gameVersion < serverGameVersion)
	{
        showStrongUpdateNote();
	}
	else
	{
		if (dataVersion != serverDataVersion)
		{
			if (bFirstScriptUpdate)
			{
                showScriptUpdateNote();
				bFirstScriptUpdate=false;
			}

		}
	}
}

void LoginFace::checkVersionUpdate()
{
	const std::string &url = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
	const int strong = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
	const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_4);

	if (!url.empty())
	{
		if (strong != 0)
		{
            showStrongUpdateNoteEx();
		}
		else
		{
			showOptionalUpdateNoteEx();
		}
	}
}

void LoginFace::checkSVNVersion()
{
	const int serverSVNVersion = LoginHelper::getServerSVNVersion();
	const int svnVersion = SystemData::getSVNVersion();
	if (serverSVNVersion <= svnVersion)
	{
#if not defined (APPSTORE_VERSION) && not defined (C3737_VERSION) && not defined (C3737_PGY_VERSION) && not defined (C3737_HL_VERSION)
		NotificationHelper::showNote(LayoutData::getString(CPModuleName::LOGIN, "svnVersionLatest"));
#endif
#if defined (APPSTORE_VERSION) || defined (C3737_VERSION) || defined (C3737_PGY_VERSION) || defined (C3737_HL_VERSION)
		LoginHelper::checkVersionRequest();
		mChecker->start();
#endif
		return;
	}
	hideTouchTip();
	showOptionalUpdateNote();
}

void LoginFace::onCheckVersionManual( CCObject *target )
{
	mChecker->start();
	LoginHelper::checkSVNVersionRequest();
}

void LoginFace::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();

	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageAuthCheckVersionStrongUpdateResponse")//HandleMessageAuthCheckVersionStrongUpdateResponse
		{
            mNeedUpdate = TypeNull;
			mChecker->stop();
			if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) != ChannelID::tencent_msdk)
			{
				mEnterLabel->setVisible(true);
			}
			refreshAnnouncement();
			checkVersionUpdate();
            if(Login::s_swordAnimationEnd)
            {
                hideTouchTip();
            }
		}
	}
	else if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageAuthCheckVersionStrongResponse")//HandleMessageAuthCheckVersionStrongResponse
		{
			mChecker->stop();
			if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) != ChannelID::tencent_msdk)
			{
				mEnterLabel->setVisible(true);
			}
			refreshAnnouncement();
			checkVersion();
		}
		else if (source == "HandleMessageAuthCheckVersionOptionalResponse")
		{
			mChecker->stop();
			checkSVNVersion();
		}
		else if (source == "HandleMessageLoginResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				LoginHelper::switchView(LoginView::loginfeet);
			}
		}
		else if (source == "HandleMessageAuthMiniStrongResponse")
		{
			mChecker->stop();
			onOptionalVersionUpdate(NotePanel::confirm);//Ð¡°üÇ¿¸ü½ø¶ÈÌõ¿ªÊ¼
		}
	}
	else if (eventName == CPEventName::UI_NOTIFY)
	{
		if (source == "ScriptUpdatePanel::downloadDataFileEnd")
		{
			mVersionLabel->setString(SystemData::getVersion().c_str());
		}
        else if (source == "swordAnimationEnd")
        {
            if(mNeedUpdate!=TypeLoading)
            {
                hideTouchTip();
            }
            if(mNeedUpdate==TypeOnScriptUpdate)
            {
                onScriptUpdate(0);
            }
        }
	}
	else if (eventName == CPEventName::NET_CHANGE)
	{
		const int &changeType = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
		if (changeType == Event::NETWORKBORN)
		{
			//			CPEvtDispatcher.removeEventListener(CPEventName::NET_CHANGE, this);
			if (CPPlatformMnger.getIntData(CPPlatformData::HAS_LOGIN_TO_DO) != 0)
			{
				LoginHelper::loginRequest();
			}
			else
			{
#if defined (APPSTORE_VERSION) || defined (C3737_VERSION) || defined (C3737_PGY_VERSION) || defined (C3737_HL_VERSION)
				//update version by SVN
				LoginHelper::checkSVNVersionRequest();
				return;
#endif
				LoginHelper::checkVersionRequest();
				mChecker->start();
			}
		}
	}
	else if (eventName == CPEventName::LGC_PLATFORM)
	{
		if (source == "Java_com_ceapon_fire_MyPlatform_pfLoginResponse")
		{
			mChecker->start();
		}
	}
}

void LoginFace::sendMsgTo3737()
{
	bool requestType_is_post=true;//
	std::string gid="13";
	std::string	key="ydl_gresdf98ouidww4";
	int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);

	/*
	utime		//Ê±¼ä½Ø
	gid		//ÓÎÏ·ID
	uaid		//¹ã¸æÕ¾ID,(´óÇþµÀµØÖ·)
	uwid		//ÒýÓÃID(¼´¹ã¸æID),(Ð¡ÇþµÀµØÖ·)
	uadid		//ËØ²ÄID
	usite		//×ÓÕ¾ID
	umacid	//ÊÖ»úÎ¨Ò»ID
	uip		//ÓÃ»§IP
	sign		//¼ÓÃÜ´®(×éºÏ·½Ê½:md5($my_time.$my_gid. $un_aid.$un_wid.$un_adid.$un_site.$umacid.$my_uip.$KEY))
	*/

	//´ò¿ªÓÎÏ·
	if (requestType_is_post)
	{
		CCHttpRequest* request = new CCHttpRequest();//
		string str0 = "http://un.huolug.com/news/get.game.gameopen.php";
        
		string utime = StringUtils::toString(ActivityData::getWorldTime());//utime
		string gid = "13";//gid
		string uaid = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uaid_"+StringUtils::toString(channel_id)));//uaid;
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
		std::string str_md5 = utime+gid+uaid+uwid+uadid+usite+umacid+uip+key ;
		str_sign = MD5::MD5(str_md5).toString();
#endif
		
		string strutime = "utime=";
		string strgid = "&gid=";
		string struaid = "&uaid=";
		string struwid = "&uwid=";
		string struadid = "&uadid=";
		string strusite = "&usite=";
		string strumacid = "&umacid=";
		string struip = "&uip=";
		string strsign = "&sign=";
        
		string str_data = strutime+ utime+   strgid+ gid+   struaid+ uaid+   struwid+uwid+    struadid+uadid+    strusite+usite+    strumacid+umacid+    struip+uip+    strsign+str_sign    ;
		request->setUrl(str0.c_str());//
		request->setRequestData(str_data.c_str(),strlen(str_data.c_str()));
		request->setRequestType(CCHttpRequest::kHttpPost);//
		request->setResponseCallback(this, httpresponse_selector(LoginFace::onHttpRequestCompleted));//
		request->setTag("Post test");
		CCHttpClient::getInstance()->send(request);//
		request->release();//
	}
}

void LoginFace::onHttpRequestCompleted( CCHttpClient* client, CCHttpResponse* response )
{

}

void LoginFace::checkVersion4Appstore()
{
	
}

void LoginFace::onDownload4Appstore(int btnType)
{
	if (btnType == Button_QD)
	{
#if defined (APPSTORE_VERSION) || defined (C3737_VERSION) || defined (C3737_PGY_VERSION) || defined (C3737_HL_VERSION)
		CHANNELHELPER->onDownload4AppStore();
		SceneManager::exitGame();
#endif
	}
	if (btnType == Button_Close)
	{
		SceneManager::exitGame();
	}
}

//////////////////////////////////////////////////////////////////////////
NotePanel::NotePanel()
	:mTitleLabel(NULL)
	,mContentLabel(NULL)
	,mHander(NULL)
	,mHandleFunc(NULL)
	,mType(0)
	,mPriority(kCCMenuHandlerPriority)
{

}

NotePanel::~NotePanel()
{

}

NotePanel * NotePanel::create( int type )
{
	return create(type, kCCMenuHandlerPriority);
}

NotePanel * NotePanel::create( int type, int priority )
{
	NotePanel *ret = new NotePanel;
	if (ret && ret->initWithData(type, priority))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

void NotePanel::setTitle( const std::string &title )
{
	mTitleLabel->setString(title.c_str());
}

void NotePanel::setContent( const std::string &content )
{
	mContentLabel->setString(content.c_str());
}

void NotePanel::setHandler( CCObject *target, SEL_NotePanel func )
{
	mHander = target;
	mHandleFunc = func;
}

bool NotePanel::initWithData( int type, int priority )
{
	if (!CPTipsSub::init())
	{
		return false;
	}

	mType = type;
	mPriority = priority;
	initUI();

	return true;
}

void NotePanel::initUI()
{
	// dark bkg
	CCLayerColor *bkg = CCLayerColor::create(ccc4(0, 0, 0, 0), SystemData::size_x * 3, SystemData::size_y * 3);
	bkg->runAction(CCFadeTo::create(0.5f, 150));
	bkg->setPosition(ccp(-SystemData::size_x, -SystemData::size_y));
	addChild(bkg);

	// board
	CCSprite *board = LayoutData::getSprite(CPModuleName::COMMON, "floatBoard");
	addChild(board);
	setContentSize(board->getContentSize());

	// title
	mTitleLabel = LayoutData::getLabelTTF(CPModuleName::COMMON, "floatTitle");
	addChild(mTitleLabel);

	// content
	mContentLabel = LayoutData::getLabelTTF(CPModuleName::COMMON, "floatContent");
	addChild(mContentLabel);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setTouchPriority(mPriority);
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *confirmBtn = LayoutData::getMenuItemLabelImage(CPModuleName::COMMON, "floatConfirm");
	confirmBtn->setTarget(this, menu_selector(NotePanel::onClick));
	menu->addChild(confirmBtn, 0, confirm);

	CCMenuItemImage *cancelBtm = LayoutData::getMenuItemLabelImage(CPModuleName::COMMON, "floatCancel");
	cancelBtm->setTarget(this, menu_selector(NotePanel::onClick));
	menu->addChild(cancelBtm, 0, cancel);

	if (mType == confirm_only)
	{
		confirmBtn->setPositionX(getContentSize().width/2);
		cancelBtm->setVisible(false);
	}
}

void NotePanel::onClick( CCObject *target )
{
	if (mHander && mHandleFunc)
	{
		CCNode *node = dynamic_cast<CCNode *>(target);
		if (node)
		{
			(mHander->*mHandleFunc)(node->getTag());
		}
	}
	close();
}

//////////LoginBody////////////////////////////////////////////////////
LoginBody::LoginBody()
	:userNameBox(NULL)
	,passwordBox(NULL)
	,mChecker(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

LoginBody::~LoginBody()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool LoginBody::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	setKeypadEnabled(true);
	initUI();

	return true;
}

void LoginBody::onEnter()
{
	CCLayer::onEnter();
}

void LoginBody::initUI()
{    
	const ccColor3B whiteColor = LayoutData::getColor3(CPModuleName::COMMON, "white");
	// title logo
	CCSprite *logo = LayoutData::getSprite(CPModuleName::LOGIN, "loginLogo");
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::muzhiwan_rexuetulong)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::LOGIN, "logoReXueTuLong");
	}
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::coolpay_lieyanzhanshen)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::LOGIN, "logoLieYanZhanShen");
	}
	if (logo)
	{
		logo->setScale(0.8f);
		addChild(logo);
	}

	CCLabelTTF *loginPromptLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN,"loginPrompt");
	addChild(loginPromptLabel);

	// edit box
	std::string account, password;
	LoginHelper::initAccountPassword(account, password);
	userNameBox = LayoutData::getEditBox(CPModuleName::LOGIN, "account"); 
	userNameBox->setAnchorPoint(ccp(0,0));
	userNameBox->setText(account.c_str());

	const CCSize &whiteArea = userNameBox->getContentSize();
	CCClippingNode *clippingNode = CPNodeHelper::getClippingNode(whiteArea);
	clippingNode->setPosition(ccp(userNameBox->getPositionX()-whiteArea.width/2,userNameBox->getPositionY()-whiteArea.height/2));
	addChild(clippingNode);
	userNameBox->setPosition(ccp(0,0));
	clippingNode->addChild(userNameBox);

	passwordBox = LayoutData::getEditBox(CPModuleName::LOGIN, "password");
	passwordBox->setInputFlag(kEditBoxInputFlagPassword);
	passwordBox->setAnchorPoint(ccp(0,0));
	passwordBox->setText(password.c_str());

	const CCSize &whiteArea_pwd = passwordBox->getContentSize();
	CCClippingNode *clippingNode_pwd = CPNodeHelper::getClippingNode(whiteArea_pwd);
	clippingNode_pwd->setPosition(ccp(passwordBox->getPositionX()-whiteArea_pwd.width/2,passwordBox->getPositionY()-whiteArea_pwd.height/2));
	addChild(clippingNode_pwd);
	passwordBox->setPosition(ccp(0,0));
	clippingNode_pwd->addChild(passwordBox);

	// label
	CCLabelTTF *accountLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "account");
	accountLabel->setColor(whiteColor);
	addChild(accountLabel);

	CCLabelTTF *passwordLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "password");
	passwordLabel->setColor(whiteColor);
	addChild(passwordLabel);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *loginBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "login");
	loginBtn->setTarget(this, menu_selector(LoginBody::onLogin));
	loginBtn->setScaleX(2.0f);
	loginBtn->setPositionY(90);
	menu->addChild(loginBtn);

	CCLabelTTF *loginLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "login");
	loginLabel->setColor(whiteColor);
	loginLabel->setPosition(loginBtn->getPosition());
	addChild(loginLabel);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void LoginBody::onLogin( CCObject *target )
{
	string username = userNameBox->getText();
	string password = passwordBox->getText(); 
	for (int i = 0; i < username.length(); i ++)  
	{  
		unsigned char ch = username.at(i);  
		if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '-' || ch == '_'))  
		{  
			CPEventHelper::uiNotify("","",-5005);
			return ;
		}  
	}   
	if (username.empty() || password.empty())
	{
		CPEventHelper::uiNotify("","",-4005);
		return;
	}
	mChecker->start(LayoutData::getString(CPModuleName::LOGIN, "loginNote"));
	CPPlatformMnger.setStringData(CPPlatformData::UIN, userNameBox->getText());
	CPPlatformMnger.setStringData(CPPlatformData::USER_NAME, userNameBox->getText());
	CPPlatformMnger.setStringData(CPPlatformData::SESSION_ID, passwordBox->getText());
	LoginHelper::loginRequest();

	//	LoginHelper::switchView(LoginView::loginfeet);
}

void LoginBody::keyBackClicked()
{
	SceneManager::exitGame();
}

void LoginBody::onCPEvent( const std::string &eventName )
{
	const string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageLoginResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				CCLog(">>>Login success!");
				LoginHelper::saveAccountPassword(userNameBox->getText(), passwordBox->getText());
				LoginHelper::switchView(LoginView::loginfeet);
			}
		}
	}
}

/////////////Login_3737////////////////////////////////////////////////
Login_3737::Login_3737()
	:userNameBox(NULL)
	,passwordBox(NULL)
	,m_labelStatusCode(NULL)
	,mChecker(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH,this);
}

Login_3737::~Login_3737()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH,this);
}

bool Login_3737::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();
	initButtons();
	setKeypadEnabled(true);
	return true;
}

void Login_3737::initUI()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pborder=LayoutData::getSprite(CPModuleName::LOGIN,"ios_3737_dengluboard");
	pborder->setPosition(ccp(winsize.width/2,winsize.height/2));
	addChild(pborder);

	// edit box
	std::string account, password;
	LoginHelper::initAccountPassword(account, password);
	userNameBox = LayoutData::getEditBox(CPModuleName::LOGIN, "ios_3737_account");
	userNameBox->setAnchorPoint(ccp(0,0));
	userNameBox->setText(account.c_str());

	const CCSize &whiteArea = userNameBox->getContentSize();
	CCClippingNode *clippingNode = CPNodeHelper::getClippingNode(whiteArea);
	clippingNode->setPosition(ccp(userNameBox->getPositionX(),userNameBox->getPositionY()-whiteArea.height/2));
	addChild(clippingNode);
	userNameBox->setPosition(ccp(0,0));

	clippingNode->addChild(userNameBox);
	passwordBox = LayoutData::getEditBox(CPModuleName::LOGIN, "ios_3737_password");
	passwordBox->setAnchorPoint(ccp(0,0));
	passwordBox->setInputFlag(kEditBoxInputFlagPassword);
	passwordBox->setText(password.c_str());

	const CCSize &whiteArea_pwd = passwordBox->getContentSize();
	CCClippingNode *clippingNode_pwd = CPNodeHelper::getClippingNode(whiteArea_pwd);
	clippingNode_pwd->setPosition(ccp(passwordBox->getPositionX(),passwordBox->getPositionY()-whiteArea_pwd.height/2));
	passwordBox->setPosition(ccp(0,0));

	addChild(clippingNode_pwd);
	clippingNode_pwd->addChild(passwordBox);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(CHANNELHELPER->isQuickPlay())
    {
        userNameBox->setText(CHANNELHELPER->getQuickUserName().c_str());
        passwordBox->setText(CHANNELHELPER->getQuickPassword().c_str());
    }
#endif
}

void Login_3737::initButtons()
{
	GeneralMenu* menu = GeneralMenu::create();
	if (menu)
	{
		menu->setAnchorPoint(CCPointZero);
		menu->setPosition(CCPointZero);
		addChild(menu);
	}

	CCMenuItemImage* ZhuceZH = LayoutData::getMenuItemImg(CPModuleName::LOGIN,"ios_3737_zczh");
	ZhuceZH->setTarget(this,menu_selector(Login_3737::onRegister));
	menu->addChild(ZhuceZH);

	CCMenuItemImage* DengluZH = LayoutData::getMenuItemImg(CPModuleName::LOGIN,"ios_3737_dlzh");
	DengluZH->setTarget(this,menu_selector(Login_3737::onLogin));
	menu->addChild(DengluZH);

	CCMenuItemImage* QuickPlay = LayoutData::getMenuItemImg(CPModuleName::LOGIN,"ios_3737_kssw");
	QuickPlay->setTarget(this,menu_selector(Login_3737::onQuickPlay));
	menu->addChild(QuickPlay);

	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ios_appstore)
	{
		CCMenuItemImage *weixinBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "weixinbtn_appstore");
		if (weixinBtn)
		{
			weixinBtn->setTag(Tag_weixin);
//			weixinBtn->setTarget(this, menu_selector(Login_3737::onLoginQQorWeinxin));
//			menu->addChild(weixinBtn);
		}

		CCMenuItemImage *qqphoneBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "qqphonebtn_appstore");
		if (qqphoneBtn)
		{
			qqphoneBtn->setTag(Tag_qqphone);
//			qqphoneBtn->setTarget(this, menu_selector(Login_3737::onLoginQQorWeinxin));
//			menu->addChild(qqphoneBtn);
		}
	}
}

void Login_3737::onLoginQQorWeinxin( CCObject* target )
{
	CCNode* pNode = dynamic_cast<CCNode*>(target);
	if (pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case Tag_weixin:
			//CPPlatform->operate(PlatformOpID::weixin_login);

#if defined APPSTORE_VERSION
                CHANNELHELPER->WXAuth();
#endif
			break;
		case Tag_qqphone:
			//CPPlatform->operate(PlatformOpID::qq_login);
#if defined APPSTORE_VERSION
                CHANNELHELPER->QQAuth();
#endif
			break;
		default:
			break;
		}
	}
}


void Login_3737::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (CPEventHelper::getEventSource() == "HandleMessageLoginResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				CCLog(">>>Login success!");
				LoginHelper::saveAccountPassword(userNameBox->getText(), passwordBox->getText());
				LoginHelper::switchView(LoginView::loginfeet);
			}
		}
	}
}

void Login_3737::onEnter()
{
	CCLayer::onEnter();
}

//quick play
void Login_3737::onQuickPlay( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(CHANNELHELPER->isQuickPlay())
    {
        onLogin(pSender);
        return;
    }
#endif
    mChecker->start();
    //onQuickPlayCompleted(NULL,NULL);
    //return;
    
    int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
    CCHttpRequest* request = new CCHttpRequest();//
    string str0 = "http://huolug.com/gameapi/api.game.reg.php";
    string ac = "6";//StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"ac_loginPlatform"));//ac
    string utime = StringUtils::toString(ActivityData::getWorldTime());//utime
    string gid = "13";//gid
    string sid = "0";
    string uaid = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uaid_"+StringUtils::toString(channel_id)));
    string uwid = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uwid_"+StringUtils::toString(channel_id)));
    string uadid = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uadid_"+StringUtils::toString(channel_id)));
    string usite = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"usite_"+StringUtils::toString(channel_id)));
    string umacid = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    umacid = CHANNELHELPER->getDeviceID();
#endif
    string strmd5 = "";//sign
    string KEY = "ydl_bugnfrrlj847u";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string str_md5 = utime+gid+sid+uaid+uwid+uadid+usite+umacid+KEY ;
    strmd5 = MD5::MD5(str_md5).toString();
#endif
    string strac = "ac=";
    string strutime = "&utime=";
    string strgid = "&gid=";
    string strsid = "&sid=";
    string struaid = "&uaid=";
    string struwid = "&uwid=";
    string struadid = "&uadid=";
    string strusite = "&usite=";
    string strumacid = "&umacid=";
    string strsign = "&sign=";
    
    string str_data = strac+ac+strutime+utime+strgid+gid+strsid+sid+struaid+uaid+struwid+uwid+struadid+uadid+strusite+usite+strumacid+umacid+strsign+strmd5;
    CCLOG("onQuickPlayRequest:%s,md5:%s",str_data.c_str(),str_md5.c_str());
    request->setUrl(str0.c_str());//
    request->setRequestData(str_data.c_str(),strlen(str_data.c_str()));
    request->setRequestType(CCHttpRequest::kHttpPost);//
    request->setResponseCallback(this, httpresponse_selector(Login_3737::onQuickPlayCompleted));//
    CCHttpClient::getInstance()->send(request);//
    request->release();//
}

void Login_3737::onQuickPlayAlert( int btnType )
{
    if (btnType == Button_QD)
    {
        LoginHelper::switchView(LoginView::ios_3737_register);
    }
    else if(btnType == Button_QX)
    {
        CCLOG("%s",__FUNCTION__);
        LoginHelper::loginRequest();
    }
}

void Login_3737::onQuickPlayCompleted( CCHttpClient* client, CCHttpResponse* response )
{
    mChecker->stop();
    if (!response)
    {
        return;
    }
    if (!response->isSucceed())//
    {
        CCString strError;
        strError.initWithFormat("Receive Error! \n%s\n",response->getErrorBuffer());
        m_labelStatusCode->setString(strError.getCString());
        return ;
    }
    
    std::vector<char> *buffer = response->getResponseData();//
    string recieveData;
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        recieveData += (*buffer)[i];
    }
    
    Json::Reader reader;
    Json::Value root;
    reader.parse(recieveData,root);
    Json::Value data1 = root.get("s","-4010");
    CCLog("#################### %s",recieveData.c_str());
    
    if (data1.isString())
    {
        string data1_str = data1.asString();
        if (data1_str == "1000")
        {
            //
            string username;
            string password;
            Json::Value data1_data = root.get("d","");
            string uname = data1_data.get("uname","").asCString();
            string upwd = data1_data.get("upwd","").asCString();
            string uid = data1_data.get("uid","").asCString();
            if (uname == "" || uid == "")
            {
                CPEventHelper::uiNotify("","",-4010);
                return;
            }
            string umacid = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            umacid = CHANNELHELPER->getDeviceID();
#endif
            CPPlatformMnger.setStringData(CPPlatformData::UIN, uid);
            CPPlatformMnger.setStringData(CPPlatformData::USER_NAME, uname);
            CPPlatformMnger.setStringData(CPPlatformData::DEVICE_ID,umacid);
            //LoginHelper::loginRequest();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            CHANNELHELPER->setQuickUser(uname, upwd, uid);
#endif
            StrVector vect;
            FloatPanel::show(57, vect, this, floatpanel_selector(Login_3737::onQuickPlayAlert));
            //FloatPanel::show(FloatPanelType::Exit_activity_scene, vect, this, floatpanel_selector(ActivityStatePanel::onQuickPlayAlert));
        }
        //
        int data1_int = atoi(data1_str.c_str());
        CPEventHelper::uiNotify("","",-data1_int);
    }
}

void Login_3737::onRegister( CCObject* pSender )
{
	//	this->removeFromParent();
	LoginHelper::switchView(LoginView::ios_3737_register);
}
void Login_3737::goLogin()
{
    CCHttpRequest* request = new CCHttpRequest();//
    string str0 = "http://huolug.com/gameapi/api.game.reg.php";
    string ac = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"ac_loginPlatform"));//ac
    string uname = userNameBox->getText();//uname
    string upwd = passwordBox->getText();//upwd
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(CHANNELHELPER->isQuickPlay(uname))
    {
        uname = CHANNELHELPER->getQuickUserName();
        upwd = CHANNELHELPER->getQuickPassword();
    }
#endif
    string umail = "";//umail
    string utime = StringUtils::toString(ActivityData::getWorldTime());//utime
    string gid = "13";//gid
    string ulife = "2";
    string umacid = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    umacid = CHANNELHELPER->getDeviceID();//"e12f03g50a10";//umacid
#endif
    string str13 = "";//sign
    string KEY = "ydl_bugnfrrlj847u";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string str_md5 = uname+upwd+ulife+gid+utime+umacid+KEY ;
    str13 = MD5::MD5(str_md5).toString();
#endif
    string strac = "ac=";
    string struser="&uname=";
    string strpsw="&upwd=";
    string strumail = "&umail=";
    string strutime = "&utime=";
    string strgid = "&gid=";
    string strsid = "&sid=";
    string struaid = "&uaid=";
    string struwid = "&uwid=";
    string struadid = "&uadid=";
    string strusite = "&usite=";
    string strumacid = "&umacid=";
    string strsign = "&sign=";
    string strulife = "&ulife=";
    
    string str_data = strac+ac+struser+uname+strpsw+upwd+strulife+ulife+strumail+umail+strutime+utime+strgid+gid+strumacid+umacid+strsign+str13;
    request->setUrl(str0.c_str());//
    request->setRequestData(str_data.c_str(),strlen(str_data.c_str()));
    request->setRequestType(CCHttpRequest::kHttpPost);//
    request->setResponseCallback(this, httpresponse_selector(Login_3737::onHttpRequestCompleted));//
    request->setTag("Post test");
    CCHttpClient::getInstance()->send(request);//
    request->release();//
}
void Login_3737::onQuickLoginAlert( int btnType )
{
    if (btnType == Button_QD)
    {
        LoginHelper::switchView(LoginView::ios_3737_register);
    }
    else if(btnType == Button_QX)
    {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CHANNELHELPER->rmvQuickUser();
#endif
        goLogin();
    }
}
void Login_3737::onLogin( CCObject* pSender )
{
	int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	if (channel_id == ChannelID::ios_appstore||channel_id == ChannelID::ios_3737
		||channel_id == ChannelID::ios_3737_pgy
		||channel_id == ChannelID::ios_3737_hl)
	{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if (CHANNELHELPER->isQuickPlay()&&CHANNELHELPER->getQuickUserName()!=userNameBox->getText())
        {
            StrVector vect;
            FloatPanel::show(58, vect, this, floatpanel_selector(Login_3737::onQuickLoginAlert));
            return;
        }
        else
        {
            goLogin();
        }
#endif

	}
	else
	{
		mChecker->start(LayoutData::getString(CPModuleName::LOGIN, "loginNote"));
		CPPlatformMnger.setStringData(CPPlatformData::UIN, userNameBox->getText());
		CPPlatformMnger.setStringData(CPPlatformData::USER_NAME, userNameBox->getText());
		CPPlatformMnger.setStringData(CPPlatformData::SESSION_ID, passwordBox->getText());
		LoginHelper::loginRequest();
	}
}

void Login_3737::onHttpRequestCompleted( CCHttpClient* client, CCHttpResponse* response )
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())//
	{  
		CCString strError;
		strError.initWithFormat("Receive Error! \n%s\n",response->getErrorBuffer());
		m_labelStatusCode->setString(strError.getCString());
		return ;   
	}  

	std::vector<char> *buffer = response->getResponseData();//
	string recieveData;
	for (unsigned int i = 0; i < buffer->size(); i++)
	{  
		recieveData += (*buffer)[i];
	}

	Json::Reader reader;
	Json::Value root;
	reader.parse(recieveData,root);
	Json::Value data1 = root.get("s","-4010");
	CCLog("#################### %s",data1.asString().c_str());

	if (data1.isString())
	{
		string data1_str = data1.asString();
		if (data1_str == "4000")
		{
			//
			string username;
			string password;
			Json::Value data1_data = root.get("d","");
			string uname = data1_data.get("uname","").asCString();
			string uid = data1_data.get("uid","").asCString();
			if (uname == "" || uid == "")
			{
				CPEventHelper::uiNotify("","",-4010);
				return;
			}
			string umacid = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			umacid = CHANNELHELPER->getDeviceID();//"e12f03g50a10";//umacid
#endif
			CPPlatformMnger.setStringData(CPPlatformData::UIN, uid);
			CPPlatformMnger.setStringData(CPPlatformData::USER_NAME, uname);
			CPPlatformMnger.setStringData(CPPlatformData::DEVICE_ID,umacid);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            if (CHANNELHELPER->isQuickPlay(uname))
            {
                StrVector vect;
                FloatPanel::show(58, vect, this, floatpanel_selector(Login_3737::onQuickPlayAlert));
                return;
            }
#endif
			LoginHelper::loginRequest();
		}
		//
		int data1_int = atoi(data1_str.c_str());
		CPEventHelper::uiNotify("","",-data1_int);
	}
}

//=================================================

Register_3737::Register_3737()
	:userNameBox(NULL)
	,passwordBox(NULL)
	,passwordBox01(NULL)
{

}

Register_3737::~Register_3737()
{

}

bool Register_3737::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();
	initButtons();
	return true;
}

void Register_3737::initUI()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pborder=LayoutData::getSprite(CPModuleName::LOGIN,"ios_3737_zhuceboard");
	pborder->setPosition(ccp(winsize.width/2,winsize.height/2));
	addChild(pborder);

	// edit box
	std::string account, password;
	LoginHelper::initAccountPassword(account, password);
	userNameBox = LayoutData::getEditBox(CPModuleName::LOGIN, "ios_3737_account_zc");
	userNameBox->setAnchorPoint(ccp(0,0));
	//	userNameBox->setText(account.c_str());
	//	addChild(userNameBox);

	const CCSize &whiteArea_uname = userNameBox->getContentSize();
	CCClippingNode *clippingNode_uname = CPNodeHelper::getClippingNode(whiteArea_uname);
	clippingNode_uname->setPosition(ccp(userNameBox->getPositionX(),userNameBox->getPositionY()-whiteArea_uname.height/2));
	userNameBox->setPosition(ccp(0,0));
	addChild(clippingNode_uname);
	clippingNode_uname->addChild(userNameBox);

	passwordBox = LayoutData::getEditBox(CPModuleName::LOGIN, "ios_3737_password_zc");
	passwordBox->setAnchorPoint(ccp(0,0));
	passwordBox->setInputFlag(kEditBoxInputFlagPassword);
	//	passwordBox->setText(password.c_str());
	//	addChild(passwordBox);

	const CCSize &whiteArea_pwd = passwordBox->getContentSize();
	CCClippingNode *clippingNode_pwd = CPNodeHelper::getClippingNode(whiteArea_pwd);
	clippingNode_pwd->setPosition(ccp(passwordBox->getPositionX(),passwordBox->getPositionY()-whiteArea_pwd.height/2));
	passwordBox->setPosition(ccp(0,0));
	addChild(clippingNode_pwd);
	clippingNode_pwd->addChild(passwordBox);

	passwordBox01 = LayoutData::getEditBox(CPModuleName::LOGIN, "ios_3737_password_zc01");
	passwordBox01->setAnchorPoint(ccp(0,0.0));
	passwordBox01->setInputFlag(kEditBoxInputFlagPassword);
	//	passwordBox01->setText(password.c_str());
	//	addChild(passwordBox01);

	const CCSize &whiteArea_pwd2 = passwordBox->getContentSize();
	CCClippingNode *clippingNode_pwd2 = CPNodeHelper::getClippingNode(whiteArea_pwd2);
	clippingNode_pwd2->setPosition(ccp(passwordBox01->getPositionX(),passwordBox01->getPositionY()-whiteArea_pwd2.height/2));
	passwordBox01->setPosition(ccp(0,0));
	addChild(clippingNode_pwd2);
	clippingNode_pwd2->addChild(passwordBox01);
}

void Register_3737::initButtons()
{
	GeneralMenu* menu = GeneralMenu::create(); 
	if (menu)
	{
		menu->setAnchorPoint(CCPointZero);
		menu->setPosition(CCPointZero);
		addChild(menu);
	}

	CCMenuItemImage* QxZC = LayoutData::getMenuItemImg(CPModuleName::LOGIN,"ios_3737_qxzc");
	QxZC->setTarget(this,menu_selector(Register_3737::onQxRegister));
	menu->addChild(QxZC);

	CCMenuItemImage* ZhuceZH = LayoutData::getMenuItemImg(CPModuleName::LOGIN,"ios_3737_zczh01");
	ZhuceZH->setTarget(this,menu_selector(Register_3737::onRegister));
	menu->addChild(ZhuceZH);
}


void Register_3737::onCPEvent( const std::string &eventName )
{

}

void Register_3737::onQxRegister( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(CHANNELHELPER->isBindInGame())
    {
        this->removeFromParent();
        return;
    }
#endif
    LoginHelper::switchView(LoginView::ios_3737_login);

}

void Register_3737::onRegister( CCObject* pSender )
{
	//
	string username = userNameBox->getText();
	string pwd = passwordBox->getText();
	string pwd1 = passwordBox01->getText();
	if (username.empty() || pwd.empty() || pwd1.empty())
	{
		CPEventHelper::uiNotify("","",-4005);
		return;
	}
	if (!checkUsername(username))
	{
		CPEventHelper::uiNotify("","",-2003);
		return;
	}
	CCLog("##############%s,%s,%s",username.c_str(),pwd.c_str(),pwd1.c_str());
	if (username == "" || passwordBox->getText() == "" || passwordBox01->getText() == "")
	{
		//		
		CPEventHelper::uiNotify("","",-4005);
		return;
	}
	//
	if (pwd != pwd1)
	{
		CPEventHelper::uiNotify("","",-2004);
		return;
	}
	//
    bool isQuickPlay = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    isQuickPlay = CHANNELHELPER->isQuickPlay();
#endif
	if (!isQuickPlay)
	{
		CCHttpRequest* request = new CCHttpRequest();//
		int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
		string str0 = "http://huolug.com/gameapi/api.game.reg.php";
		string str1 = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"ac_register"));//ac
		string str2 = userNameBox->getText();//uname
		string str3 = passwordBox->getText();//upwd
		string str4 = "";//umail
		string str5 = StringUtils::toString(ActivityData::getWorldTime());//utime
		string str6 = "13";//gid
		string str7 = "0";//sid
		string str8 = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uaid_"+StringUtils::toString(channel_id)));//uaid
		string str9 = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uwid_"+StringUtils::toString(channel_id)));//uwid
		string str10 = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uadid_"+StringUtils::toString(channel_id)));//uadid
		string str11 = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"usite_"+StringUtils::toString(channel_id)));//usite
		string str12 = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		str12 = CHANNELHELPER->getDeviceID();//"e12f03g50a10";//umacid
#endif
		string str13 = "";//sign
		// uname+upwd+umail+utime+gid+sid+uaid+uwid+uadid+usite+ umacid +KEY)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		std::string str_md5 = str2+str3+str4+str5+str6+str7+str8+str9+str10+str11+str12+"ydl_bugnfrrlj847u";
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
		string struaid = "&uaid=";
		string struwid = "&uwid=";
		string struadid = "&uadid=";
		string strusite = "&usite=";
		string strumacid = "&umacid=";
		string strsign = "&sign=";

		string str_data = strac+str1+struser+str2+strpsw+str3+strumail+str4+strutime+str5+strgid+str6
			+strsid+str7+struaid+str8+struwid+str9+struadid+str10+strusite+str11+strumacid+str12
			+strsign+str13;
		request->setUrl(str0.c_str());//
		request->setRequestData(str_data.c_str(),strlen(str_data.c_str()));
		request->setRequestType(CCHttpRequest::kHttpPost);//
		request->setResponseCallback(this, httpresponse_selector(Register_3737::onHttpRequestCompleted));//
		request->setTag("POST test");
		CCHttpClient::getInstance()->send(request);//
		request->release();//
	}
	else
	{
        CCHttpRequest* request = new CCHttpRequest();//
        int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
        string str0 = "http://huolug.com/gameapi/api.game.reg.php";
        string str1 = "8";//StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"ac_register"));//ac
        string uid = "0";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        uid = CHANNELHELPER->getQuickUid();
#endif
        string str2 = userNameBox->getText();//uname
        string str3 = passwordBox->getText();//upwd
        string str4 = "";//umail
        string str5 = StringUtils::toString(ActivityData::getWorldTime());//utime
        string str6 = "13";//gid
        string str7 = "0";//sid
        string str8 = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uaid_"+StringUtils::toString(channel_id)));//uaid
        string str9 = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uwid_"+StringUtils::toString(channel_id)));//uwid
        string str10 = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"uadid_"+StringUtils::toString(channel_id)));//uadid
        string str11 = StringUtils::toString(LayoutData::getInt(CPModuleName::LOGIN,"usite_"+StringUtils::toString(channel_id)));//usite
        string uoldname = "";//CHANNELHELPER->getQuickUserName();
        string uoldpwd = "";//CHANNELHELPER->getQuickPassword();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        uoldname = CHANNELHELPER->getQuickUserName();
        uoldpwd = CHANNELHELPER->getQuickPassword();
#endif
        string str13 = "";//sign
        std::string str_md5 = "";
        // uname+upwd+umail+utime+gid+sid+uaid+uwid+uadid+usite+ umacid +KEY)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        str_md5 = uid+str2+str3+str4+str5+str6+str7+str8+str9+str10+str11+uoldname+"ydl_bugnfrrlj847u";
        str13 = MD5::MD5(str_md5).toString();
#endif
        // 		string str = "ac=1&uname=zhangliumang&upwd=123456&umail=liumang@163.com&utime=1&gid=13&sid=1&uaid=1&uwid=1&uadid=1&usite=1&umacid=1"
        // 			+"&sign=6880f782f6fe3658f0922702af8b6e31";
        string strac = "ac=";
        string struid = "&uid=";
        string struser="&uname=";
        string strpsw="&upwd=";
        string strumail = "&umail=";
        string strutime = "&utime=";
        string strgid = "&gid=";
        string strsid = "&sid=";
        string struaid = "&uaid=";
        string struwid = "&uwid=";
        string struadid = "&uadid=";
        string strusite = "&usite=";
        string struoldname = "&uoldname=";
        string struoldpwd = "&uoldpwd=";
        string strsign = "&sign=";
        
        string str_data = strac+str1+struid+uid+struser+str2+strpsw+str3+strumail+str4+strutime+str5+strgid+str6
        +strsid+str7+struaid+str8+struwid+str9+struadid+str10+strusite+str11+struoldname+uoldname+struoldpwd+uoldpwd
        +strsign+str13;
        CCLOG("onBind:%s,md5:%s",str_data.c_str(),str_md5.c_str());
        request->setUrl(str0.c_str());//
        request->setRequestData(str_data.c_str(),strlen(str_data.c_str()));
        request->setRequestType(CCHttpRequest::kHttpPost);//
        request->setResponseCallback(this, httpresponse_selector(Register_3737::onQuickBindCompleted));//
        CCHttpClient::getInstance()->send(request);//
        request->release();//
	}
}

void Register_3737::onHttpRequestCompleted( CCHttpClient* client, CCHttpResponse* response )
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())//
	{  
		CCString strError;
		strError.initWithFormat("Receive Error! \n%s\n",response->getErrorBuffer());
		m_labelStatusCode->setString(strError.getCString());
		return ;   
	}  

	std::vector<char> *buffer = response->getResponseData();//
	string recieveData;
	for (unsigned int i = 0; i < buffer->size(); i++)
	{  
		recieveData += (*buffer)[i];
	}

	Json::Reader reader;
	Json::Value root;
	reader.parse(recieveData,root);
	Json::Value data1 = root.get("s","10007");
	CCLog("#################### %s",recieveData.c_str());

	if (data1.isString())
	{
		string data1_str = data1.asString();
		if (data1_str == "1000")
		{
			//
			LoginHelper::saveAccountPassword(userNameBox->getText(), passwordBox->getText());
			LoginHelper::switchView(LoginView::ios_3737_login);
		}
		//
		int data1_int = atoi(data1_str.c_str());
		CPEventHelper::uiNotify("","",-data1_int);
	}
}
void Register_3737::onQuickBindCompleted( CCHttpClient* client, CCHttpResponse* response )
{
    if (!response)
    {
        return;
    }
    if (!response->isSucceed())//
    {
        CCString strError;
        strError.initWithFormat("Receive Error! \n%s\n",response->getErrorBuffer());
        m_labelStatusCode->setString(strError.getCString());
        return ;
    }
    
    std::vector<char> *buffer = response->getResponseData();//
    string recieveData;
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        recieveData += (*buffer)[i];
    }
    
    Json::Reader reader;
    Json::Value root;
    reader.parse(recieveData,root);
    Json::Value data1 = root.get("s","90007");
    CCLog("#################### %s",recieveData.c_str());
    
    if (data1.isString())
    {
        string data1_str = data1.asString();
        if (data1_str == "9000")
        {
            //
            LoginHelper::saveAccountPassword(userNameBox->getText(), passwordBox->getText());
            bool isBindInGame = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            CHANNELHELPER->rmvQuickUser();
            isBindInGame = CHANNELHELPER->isBindInGame();
#endif
            if (isBindInGame)
            {
                CCLOG("TODO:onQuickBindCompleted BindInGame");
                this->removeFromParent();
            }
            else
            {
                LoginHelper::switchView(LoginView::ios_3737_login);
            }
            StrVector vect;
            string username = userNameBox->getText();
            vect.push_back(username);
            FloatPanel::show(59, vect, this, NULL);
        }
        //
        int data1_int = atoi(data1_str.c_str());
        CPEventHelper::uiNotify("","",-data1_int);
    }
}

bool Register_3737::checkUsername(string username)
{  
	//	string patten_str = "([0-9A-Za-z\\-_\\.@]+){3,18}";
	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
	//	regex pattern(patten_str);
	//	if ( regex_match( username, pattern ) )  
	//	{   
	//		return true;  
	//	}
	//	return false;
	//	
	//#endif  
	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
	//	regmatch_t pmatch[18];
	//	regex_t match_regex;
	////username = "asdhjsdad@163.com";
	//	regcomp( &match_regex,
	//		//patten_str.c_str(),
	//            "([0-9A-Za-z\\-_\\.@]+)",
	//            //"([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)",
	//		REG_EXTENDED );
	//    int ret = regexec( &match_regex, username.c_str(), 18, pmatch, 0 );
	//    CCLOG("ret = %d",regexec( &match_regex, username.c_str(), 18, pmatch, 0 ));
	//	if ( regexec( &match_regex, username.c_str(), 18, pmatch, REG_NOTBOL ) == REG_NOMATCH )
	//	{
	//		return true;
	//	}
	//	regfree( &match_regex );
	//	return false;
	//#endif
	//	return false;

	int ret = 0;
	Lua::instance()->push(username);
	if (Lua::instance()->call("g_check_username", 1, 1))
	{
		Lua::instance()->pop(ret);
	}
	return ret;
}


/////////////LoginFeet/////////////////////////////////////////////////

static const ccColor3B ccPURPLE={153,50,254};
static const ccColor3B ccL_white={255,251,240};

static const ccColor3B ccL_yellow={238,246,18};
LoginFeet::LoginFeet():
	serverName(NULL),
	choseServer(NULL),
	index(0),
	label_login(NULL),
	mEnterLabel(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

LoginFeet::~LoginFeet()
{
	//CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	//CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	// This calling will remove me from the dispatcher regardless the event name
	CPEvtDispatcher.removeEventListener(this);
}

bool LoginFeet::init()//点击屏幕开始游戏界面ui
{
	if (!CCLayer::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	setTouchEnabled(true);
	index = LoginHelper::getSavedServerIndex();
	initUI();
	return true;
}

void LoginFeet::initUI()
{

	CCSprite *logo = NULL;
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::_35i_another
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::wdj_jianzhixuanyuan
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::qihoo_jianzhixuanyuan
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::duoku_jianzhixuanyuan)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::LOGIN, "logoJianZhiXuanYuan");
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
		logo = LayoutData::getSpriteByFile(CPModuleName::LOGIN, "logoLieYanZhanShen");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::muzhiwan_rexuetulong)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::LOGIN, "logoReXueTuLong");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::sijiuyou_xueren)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::LOGIN, "logoXueRen");
	}else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_chuanqizhanshen)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::LOGIN, "logoChuanQiZhanShen");
	}else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_yingxiongchuanqi)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::LOGIN, "logoYingXiongChuanQi");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::shoumeng_chiyanzhanshen)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoChiYanZhanShen");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::shoumeng_lieyanfentian)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoLieYanFenTian");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_shachengchuanqi)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoShaChengChuanQi");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::youmi_menghuishacheng)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoMengHuiShaCheng");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::aboluo_rexuetianya)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logorexuetianya");
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
 	else
	{
	//	logo = LayoutData::getSprite(CPModuleName::LOGIN, "loginLogo");
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoJingLongZhuan");
	}
	
	if (logo)
	{
		addChild(logo);
	}

	CCMenu* menu = CCMenu::create();
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	addChild(menu);

	//	CCScale9Sprite* bg = LayoutData::getScale9Sprite(CPModuleName::LOGIN,"wordsbg");
	//	bg->setPosition(LayoutData::getPoint(CPModuleName::LOGIN,"xianshibg"));
	//	addChild(bg);

	CCScale9Sprite * normalsprite1 = LayoutData::getScale9Sprite(CPModuleName::LOGIN,"wordsbg");
	CCScale9Sprite * selectsprite1 = LayoutData::getScale9Sprite(CPModuleName::LOGIN,"wordsbg"); 

	if (normalsprite1 != NULL && selectsprite1 != NULL)
	{
		CCMenuItemSprite *bg = CCMenuItemSprite::create(normalsprite1,selectsprite1);
		bg->setPosition(LayoutData::getPoint(CPModuleName::LOGIN,"xianshibg"));
		bg->setTarget(this,menu_selector(LoginFeet::menuCallBack));
		bg->setTag(bgtag);
		menu->addChild(bg);
	}

	if (checkPlayerOld())
	{
		//		label_login = LayoutData::getLabelTTF(CPModuleName::LOGIN,"lastlogin");
	}
	else
	{
		//		label_login = LayoutData::getLabelTTF(CPModuleName::LOGIN,"hotnewserver");
	}
	if (label_login)
	{
		//		label_login->setFontSize(24);
		//		label_login->setColor(ccPURPLE);
		//		label_login->setAnchorPoint(ccp(1,0.5));
		//		addChild(label_login);

	}

	int idx = LoginHelper::getSavedServerIndexBysavedId(LoginHelper::getSavedServerId());
	if (idx == -1)
	{
		idx = ServerList::initIndex();
	}
	if (!checkPlayerOld())
	{
		//
		idx = ServerList::initIndex();
	}
	index = idx;
	std::string name = LoginHelper::getServerName(idx);
	if (name != "")
	{
		serverName = CCLabelTTF::create(name.c_str(),"",24);
		serverName->setColor(ccL_white);
		serverName->setAnchorPoint(ccp(1,0.5));
		serverName->setPosition(LayoutData::getPoint(CPModuleName::LOGIN,"servername"));
		addChild(serverName);
	}

	mEnterLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "clickEnter");
	if (mEnterLabel)
	{
		mEnterLabel->setOpacity(0);
		mEnterLabel->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(
			CCFadeIn::create(1.0f),
			CCFadeOut::create(2.0f))
			));
		addChild(mEnterLabel);
	}

	choseServer=CCMenuItemFont::create(SystemData::getLayoutString("login_choseserver").c_str());
	choseServer->setAnchorPoint(ccp(0,0.5));
	choseServer->setFontSizeObj(24);
	choseServer->setColor(ccL_yellow);
	choseServer->setPosition(LayoutData::getPoint(CPModuleName::LOGIN,"choseserver"));
	choseServer->setTarget(this,menu_selector(LoginFeet::menuCallBack));
	choseServer->setTag(chose);

	CCMenuItemImage *returnBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "returnBack");
	returnBtn->setTarget(this, menu_selector(LoginFeet::onReturn));
	menu->addChild(returnBtn);

	menu->addChild(choseServer);
}

void LoginFeet::onEnter()
{
	CCLayer::onEnter();
}

void LoginFeet::menuCallBack( CCObject* target )
{
	CCNode* pNode = dynamic_cast<CCNode*>(target);
	if (pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case bgtag:
			// Modify By Tony. 2014/09/22 09:22
			// µÇÂ¼Á÷³ÌÐÞ¸Ä;
			// ÕËºÅÑéÖ¤Ê±AMSÖ»·µ»ØÉÏ´ÎµÇÂ¼µÄ·þÎñÆ÷»òÍÆ¼ö·þÎñÆ÷;
			// Ñ¡Ôñ·þÎñÆ÷ÁÐ±íºó¿ªÊ¼»ñÈ¡·þÎñÆ÷ÁÐ±í;
			// ÁÐ±í»ñÈ¡³É¹¦ºó´ò¿ª·þÎñÆ÷Ñ¡Ôñ½çÃæ;
			// ÇëÇó·þÎñÆ÷ÁÐ±í;

			LoginHelper::authServerListResquest();
			//LoginHelper::switchView(LoginView::serverlist);
			break;
		case chose:
			// Modify By Tony. 2014/09/22 09:22
			// µÇÂ¼Á÷³ÌÐÞ¸Ä;
			// ÕËºÅÑéÖ¤Ê±AMSÖ»·µ»ØÉÏ´ÎµÇÂ¼µÄ·þÎñÆ÷»òÍÆ¼ö·þÎñÆ÷;
			// Ñ¡Ôñ·þÎñÆ÷ÁÐ±íºó¿ªÊ¼»ñÈ¡·þÎñÆ÷ÁÐ±í;
			// ÁÐ±í»ñÈ¡³É¹¦ºó´ò¿ª·þÎñÆ÷Ñ¡Ôñ½çÃæ;
			// ÇëÇó·þÎñÆ÷ÁÐ±í;

			LoginHelper::authServerListResquest();
			//LoginHelper::switchView(LoginView::serverlist);
			break;
		case enter:
			{
				int state = LoginHelper::getServerState(index);
				if (index >= 0 && state != 4)
				{
					CPEvtDispatcher.addEventListener(CPEventName::NET_CHANGE, this);
					LoginHelper::startGameServer(index);
					LoginHelper::saveServerId(LoginHelper::getServerID(index));
				}
			}
			break;
		default:
			break;
		}
	}
}

void LoginFeet::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (CPEventHelper::getEventSource() == "HandleMessageEnterServerResponse")
		{
			//			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				CPPlatform->operate(PlatformOpID::enter_server);
				//				LoginHelper::saveServerAndRegionIndex(index, mRegionIndex);
				if(LoginHelper::getPlayerCnt() > 0)
				{
					LoginHelper::switchView(LoginView::selectrole);
				}
				else
				{
					LoginHelper::switchView(LoginView::createrole);
				}
			}
			else
			{
				LoginHelper::switchView(LoginView::loginbody);
			}
		}
		else if (CPEventHelper::getEventSource() == "HandleMessageAuthServerListNotifyEnd")
		{
			// Modify By Tony. 2014/09/22 09:22
			// µÇÂ¼Á÷³ÌÐÞ¸Ä;
			// ÕËºÅÑéÖ¤Ê±AMSÖ»·µ»ØÉÏ´ÎµÇÂ¼µÄ·þÎñÆ÷»òÍÆ¼ö·þÎñÆ÷;
			// Ñ¡Ôñ·þÎñÆ÷ÁÐ±íºó¿ªÊ¼»ñÈ¡·þÎñÆ÷ÁÐ±í;
			// ÁÐ±í»ñÈ¡³É¹¦ºó´ò¿ª·þÎñÆ÷Ñ¡Ôñ½çÃæ;
			if (CPEventHelper::isRequestSuccess())
			{
				// ´ò¿ª·þÎñÆ÷½çÃæ;
				LoginHelper::switchView(LoginView::serverlist);
			}

		}
	}
	else if (eventName == CPEventName::NET_CHANGE)
	{
		const int &changeType = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
		if (changeType == Event::NETWORKBORN)
		{
			CPEvtDispatcher.removeEventListener(CPEventName::NET_CHANGE, this);
			if (index < 0)
			{
				index = 0;
				LoginHelper::setcurSerIndex(index);
			}
			if (index >= 0)
			{
				//				mChecker->start(LayoutData::getString(CPModuleName::LOGIN, "enterServerNote"));
				LoginHelper::enterServerRequest();
				LoginHelper::setcurSerIndex(index);
			}
		}
	}
}

void LoginFeet::onReturn( CCObject* target )
{
	LoginHelper::switchView(LoginView::login);
}

bool LoginFeet::checkPlayerOld()
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

void LoginFeet::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{

	int state = LoginHelper::getServerState(index);
	if (index >= 0 && state != 4)
	{
		CPEvtDispatcher.addEventListener(CPEventName::NET_CHANGE, this);
		LoginHelper::startGameServer(index);
		LoginHelper::saveServerId(LoginHelper::getServerID(index));
		//		CCLog("getSavedServerId     %d",LoginHelper::getSavedServerId());
	}
}


/////////////ServerList///////////////////////////////////////////////
ServerList::ServerList()
	:listLayer(NULL)
	,switchMenu(NULL)
	,itemList(NULL)
	,latelyLogin(NULL)
	,deepRecommend(NULL)
	,lastLabel(NULL)
	,recommend(NULL)
	,mChecker(NULL)
	,mRegionIndex(0)
	,m_bisOver(true)
	,m_CurrentChoseServer(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

ServerList::~ServerList()
{
	CPEvtDispatcher.removeEventListener(this);
}

int ServerList::index;

bool ServerList::init()//服务器选择界面ui
{
	if (!CCLayer::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	setKeypadEnabled(true);

	initUI_I();
	buildSwitchMenu();

	// 	int index = LoginHelper::getSavedRegionIndex();//
	const int cnt = LoginHelper::getRegionCnt();
	// 	if (index < 0 || index >= cnt)
	// 	{
	// 		index = cnt-1;
	// 	}
	int savedServerIndex = LoginHelper::getSavedServerIndex();
	if (savedServerIndex == -1)
	{
		int idx = LoginHelper::getSavedServerIndexBysavedId(LoginHelper::getSavedServerId());
		if (idx == -1 || !LoginHelper::checkPlayerOld())
		{
			idx = ServerList::initIndex();
		}
		savedServerIndex = idx;
	}
	int deep_region = LoginHelper::getServerRegion(savedServerIndex);
	switchMenu->setCurrentIndex(cnt - 1 -deep_region);
	mRegionIndex = deep_region;
	//	mRegionIndex = index;

	refreshList();

	//	itemList->setCurrentIndex(savedServerIndex);//
	//	m_CurrentChoseServer->setString(LoginHelper::getServerName(savedServerIndex).c_str());

	return true;
}

void ServerList::initUI_I()
{
	initUI_II();

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *returnBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "returnBack");
	returnBtn->setTarget(this, menu_selector(ServerList::onReturn));
	menu->addChild(returnBtn);

	CCMenuItemImage *enterBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "enterInto");
	enterBtn->setTarget(this, menu_selector(ServerList::onEnterServer));
	menu->addChild(enterBtn);
	//--------------------------------------------------------------------------------------------------------------//
	CCScale9Sprite * normalsprite = LayoutData::getScale9Sprite(CPModuleName::LOGIN,"norm");
	CCScale9Sprite * selectsprite = LayoutData::getScale9Sprite(CPModuleName::LOGIN,"sel"); 

	CCScale9Sprite * normalsprite1 = LayoutData::getScale9Sprite(CPModuleName::LOGIN,"norm");
	CCScale9Sprite * selectsprite1 = LayoutData::getScale9Sprite(CPModuleName::LOGIN,"sel"); 



	latelyLogin = CCMenuItemSprite::create(normalsprite,selectsprite);//×î½üµÇÂ¼
	deepRecommend = CCMenuItemSprite::create(normalsprite1,selectsprite1);//Ç¿ÁÒÍÆ¼ö
	//--------------------------------------------------------------------------------------------------------------//
	latelyLogin->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "latelyLogin"));
	deepRecommend->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "deepRecommend"));
	latelyLogin->setTag(Tag_late);
	latelyLogin->setTarget(this, menu_selector(ServerList::onLatelyOrRecommendEnter));

	lastLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "serverName");
	int idx = LoginHelper::getSavedServerIndexBysavedId(LoginHelper::getSavedServerId());
	if (idx == -1 || !LoginHelper::checkPlayerOld())
	{
		idx = ServerList::initIndex();
	}

	int serverID = LoginHelper::getServerID(idx);
	lastLabel->setString(LoginHelper::getServerName(idx).c_str());
	{
		int state = LoginHelper::getServerState(idx);
		if (state == TAG_State_deeptuijian)
		{
			state = TAG_State_tuijian;
		}
		CCSprite* statusSpritesvr = LayoutData::getSprite(CPModuleName::LOGIN,"statusFlag"+StringUtils::toString(state+1));
		statusSpritesvr->setPositionX(latelyLogin->getContentSize().width-124);
		statusSpritesvr->setPositionY(latelyLogin->getContentSize().height/2);
		latelyLogin->addChild(statusSpritesvr);
	}
	lastLabel->setPosition(ccp(latelyLogin->getContentSize().width/2+10,latelyLogin->getContentSize().height/2));  
	latelyLogin->addChild(lastLabel);

	deepRecommend->setTag(TAG_State_deeptuijian);
	deepRecommend->setTarget(this, menu_selector(ServerList::onEnterRecServer));
	int serverCnt = LoginHelper::getServerCnt();
	if (serverCnt > 0)
	{
		menu->addChild(deepRecommend);
	}
	if (idx < serverCnt && idx >=0)
	{
		menu->addChild(latelyLogin);
	}
	{
		int state = 0;
		index = initIndex();
		recommend = LayoutData::getLabelTTF(CPModuleName::LOGIN, "serverName");
		recommend->setString(LoginHelper::getServerName(index).c_str());//
		state = LoginHelper::getServerState(index);
		if (state == TAG_State_deeptuijian)
		{
			state = TAG_State_tuijian;
		}
		CCSprite* statusSpritesvr = LayoutData::getSprite(CPModuleName::LOGIN,"statusFlag"+StringUtils::toString(state+1));
		statusSpritesvr->setPositionX(deepRecommend->getContentSize().width-124);
		statusSpritesvr->setPositionY(deepRecommend->getContentSize().height/2);
		deepRecommend->addChild(statusSpritesvr);
		recommend->setPosition(ccp(deepRecommend->getContentSize().width/2+10,deepRecommend->getContentSize().height/2));  
		deepRecommend->addChild(recommend);
	}

	CCLabelTTF *latelyLoginLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "latelyLogin");
	addChild(latelyLoginLabel);  

	CCLabelTTF *deepRecommendLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "deepRecommend");
	addChild(deepRecommendLabel);

	// list layer
	listLayer = CCLayer::create();
	addChild(listLayer);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);

}

void ServerList::initUI_II()
{
	// board 
	CCSprite *board = LayoutData::getSprite(CPModuleName::LOGIN, "serverListBoard");
	addChild(board);

	// label 
	CCLabelTTF *backLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "backToLogin");
	addChild(backLabel);  

	CCLabelTTF *enterLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "enterServer");
	addChild(enterLabel);

	for (int i = 0;i < TAG_State_MAX;i++)
	{
		CCSprite* statusSprite = LayoutData::getSprite(CPModuleName::LOGIN,"statusFlag"+StringUtils::toString(i+1));
		CCLabelTTF* statuslabel = LayoutData::getLabelTTF(CPModuleName::LOGIN,"statusLabel"+StringUtils::toString(i+1));
		statusSprite->setPosition(ccp(LayoutData::getPoint(CPModuleName::LOGIN,"status").x+i*90,LayoutData::getPoint(CPModuleName::LOGIN,"status").y));
		addChild(statusSprite);
		addChild(statuslabel);
	}

	m_CurrentChoseServer = LayoutData::getLabelTTF(CPModuleName::LOGIN, "serverName");
	if (m_CurrentChoseServer)
	{
		m_CurrentChoseServer->setAnchorPoint(ccp(0,0.5));
		m_CurrentChoseServer->setPosition(ccp(400,50));
		addChild(m_CurrentChoseServer);
	}

	std::string name_01 = LayoutData::getString(CPModuleName::LOGIN,"currentChoseserver");
	CCLabelTTF* label_01 = CCLabelTTF::create(name_01.c_str(),"",18);
	if (label_01)
	{
		label_01->setAnchorPoint(ccp(1,0.5));
		label_01->setPosition(ccp(400,50));
		addChild(label_01);
	}
}

void ServerList::buildSwitchMenu()
{
	CCSize menuSize = LayoutData::getSize(CPModuleName::LOGIN, "switchMenu");
	CCSize itemSize = LayoutData::getSize(CPModuleName::LOGIN, "switchItem");

	switchMenu = CPItemComponents::create(menuSize, new CPLayoutList(itemSize, true));
	switchMenu->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "switchMenu"));
	addChild(switchMenu);

	const int cnt = LoginHelper::getRegionCnt();// 

	std::string sectionName;
	std::string sectionTail = LayoutData::getString(CPModuleName::LOGIN, "section");
	for (int i = cnt-1; i >= 0; i--)
	{
		CCMenuItemImage *btn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "switch");
		btn->setTarget(this, menu_selector(ServerList::onSwitch));
		switchMenu->addItem(btn);

		sectionName = LayoutData::getString(CPModuleName::COMMON, "num" + StringUtils::toString(i + 1)) + sectionTail;
		CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::LOGIN, "sectionName");
		label->setString(sectionName.c_str());
		label->setColor(ccWHITE);
		btn->addChild(label);
	}
}

void ServerList::refreshList()
{
	listLayer->removeAllChildrenWithCleanup(true);


	CCSize listSize = LayoutData::getSize(CPModuleName::LOGIN, "serverList");
	CCSize serverItemSize = LayoutData::getSize(CPModuleName::LOGIN,"serverItem");
	itemList = CPItemComponents::create(listSize, new CPLayoutGrid(3,serverItemSize,true));
	itemList->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "serverList"));
	listLayer->addChild(itemList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::LOGIN, "serverScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	itemList->setScrollbar(scrollBar);

	const ccColor3B &color = LayoutData::getColor3(CPModuleName::COMMON, "white");
	const int serverCnt = LoginHelper::getServerCnt();
	int firstIndex = serverCnt-1;
	for (int i = serverCnt-1; i >= 0; i--)
	{
		if (LoginHelper::getServerRegion(i) != mRegionIndex)
		{
			continue;
		}

		CCNode *norm = CCNode::create();
		norm->setContentSize(serverItemSize);

		CCScale9Sprite * normalsprite = LayoutData::getScale9Sprite(CPModuleName::LOGIN,"norm");
		normalsprite->setPosition(LayoutData::getCenter(serverItemSize));
		norm->addChild(normalsprite);

		CCNode *sel = CCNode::create();
		sel->setContentSize(serverItemSize);

		CCScale9Sprite * selectsprite = LayoutData::getScale9Sprite(CPModuleName::LOGIN,"sel"); 
		selectsprite->setPosition(LayoutData::getCenter(serverItemSize));
		sel->addChild(selectsprite);

		CCMenuItemSprite* btnsprite = CCMenuItemSprite::create(norm,sel);
		btnsprite->setOpacity(0.8f);
		itemList->addItem(btnsprite);
		btnsprite->setTarget(this, menu_selector(ServerList::onList));

		btnsprite->setTag(i);
		if (itemList->getItemCount() == 1)
		{
			firstIndex = i;
		}

		// name
		CCLabelTTF *name = LayoutData::getLabelTTF(CPModuleName::LOGIN, "serverName");
		name->setString(LoginHelper::getServerName(i).c_str());
		name->setColor(ccWHITE);
		name->setPosition(ccp(btnsprite->getContentSize().width/2+10,btnsprite->getContentSize().height/2));
		name->setAnchorPoint(ccp(0.5f,0.5f));
		name->setFontSize(18);
		btnsprite->addChild(name);

		// player cnt
		std::string str = LoginHelper::getPlayerCntNote(i);
		if (str != "")//
		{
			CCSprite *yuanIcon = LayoutData::getSprite(CPModuleName::LOGIN,"yuanFlag");
			yuanIcon->setPosition(LayoutData::getPoint(CPModuleName::LOGIN,"yuanIconPos"));
			CCLabelTTF *playerCnt = LayoutData::getLabelTTF(CPModuleName::LOGIN, "playerCnt");
			playerCnt->setString(LoginHelper::getPlayerCntNote(i).c_str());
			playerCnt->setColor(ccWHITE);
			playerCnt->setPosition(yuanIcon->getPosition());

			btnsprite->addChild(yuanIcon);
			btnsprite->addChild(playerCnt);
		}

		//server status

		int state = LoginHelper::getServerState(i);
		switch (state)
		{
		case 0:
			addState(btnsprite,1);
			break;
		case 1:
			addState(btnsprite,2);
			break;
		case 2:
			addState(btnsprite,3);
			break;
		case 3:
			addState(btnsprite,4);
			break;
		case 4:
			addState(btnsprite,5);
			break;
		case 5:
			addState(btnsprite,1);
			break;
		default:
			break;
		}
	}
	itemList->setCurrentIndex(firstIndex);
	if (m_CurrentChoseServer)
	{
		m_CurrentChoseServer->setString(LoginHelper::getServerName(firstIndex).c_str());
	}
	//	itemList->setPercent(100);
}

void ServerList::addState(CCMenuItemSprite* btnsprite,int tag)
{
	CCSprite* statusSpritesvr = LayoutData::getSprite(CPModuleName::LOGIN,"statusFlag"+StringUtils::toString(tag));
	statusSpritesvr->setPositionX(btnsprite->getContentSize().width-147);
	statusSpritesvr->setPositionY(btnsprite->getContentSize().height/2);
	btnsprite->addChild(statusSpritesvr);
}

void ServerList::onReturn( CCObject *target )
{
	LoginHelper::switchView(LoginView::login);
}

void ServerList::onEnterServer( CCObject *target )
{
	mChecker->start();
	const int serverIndex = itemList->getCurrentIndex();
	int state = LoginHelper::getServerState(serverIndex);
	if (serverIndex >= 0 && state != TAG_State_weihu)
	{
		CPEvtDispatcher.addEventListener(CPEventName::NET_CHANGE, this);
		LoginHelper::startGameServer(serverIndex);
		LoginHelper::saveServerId(LoginHelper::getServerID(serverIndex));
	}
}

void ServerList::onEnterRecServer( CCObject *target)
{
	mChecker->start();
	CCNode* pNode = dynamic_cast<CCNode*>(target);
	if (pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_State_deeptuijian:
			CPEvtDispatcher.addEventListener(CPEventName::NET_CHANGE, this);
			LoginHelper::startGameServer(index);
			//			itemList->setCurrentIndex(index);
			LoginHelper::saveServerId(LoginHelper::getServerID(index));
			break;
		default:
			break;
		}
	}
}

void ServerList::onLatelyOrRecommendEnter(CCObject *target)
{
	mChecker->start();
	int idx = LoginHelper::getSavedServerIndexBysavedId(LoginHelper::getSavedServerId());
	if (idx == -1 || !LoginHelper::checkPlayerOld())
	{
		idx = ServerList::initIndex();
	}
	int serverIndex = idx;
	int state = LoginHelper::getServerState(serverIndex);
	if (serverIndex >= 0 && state != TAG_State_weihu)
	{
		CPEvtDispatcher.addEventListener(CPEventName::NET_CHANGE, this);
		LoginHelper::startGameServer(serverIndex);
		LoginHelper::saveServerId(LoginHelper::getServerID(serverIndex));
	}
}

void ServerList::onSwitch( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		selSection(LoginHelper::getRegionCnt()-1-node->getTag());
	}
}

void ServerList::onList( CCObject *target )
{
	//
	/*CCMenuItem * p = dynamic_cast<CCMenuItem *>(target);*/
	if (target)
	{
		CCNode *pNode = dynamic_cast<CCNode *>(target);
		int tag = pNode->getTag();
		if(isDoubleClickItem(tag))
		{
			onEnterServer(pNode);
		}
		else
		{
			scheduleOnce(schedule_selector(ServerList::singleClickCallback),DOUBLE_CLICK_TIME);
		}	
	}

}

void ServerList::selSection( int index )
{
	if (index != mRegionIndex)
	{
		mRegionIndex = index;
		refreshList();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------

bool ServerList::isDoubleClickItem( int tag )
{
	float curTime = SystemData::getSystemTime();
	CCLog("prepos: %d, curPos: %d.",m_nPreTag,tag);
	CCLog("pretime: %f, curTime: %f.",m_nPreTime,curTime);
	if(m_nPreTag==tag && curTime-m_nPreTime < DOUBLE_CLICK_TIME)
	{
		m_nPreTag = ITEM_UNUSE_TAG;
		m_nPreTime = curTime;
		m_bDoubleClick = true;
		m_bisOver=false;
		return true;
	}
	m_nPreTag = tag;
	m_nPreTime = curTime;
	m_bDoubleClick = false;
	return false;
}

void ServerList::singleClickCallback( float dt )
{
	if(!m_bDoubleClick)
	{
		m_nPreTag = ITEM_UNUSE_TAG;
		m_nPreTime = SystemData::getSystemTime();
	}
	//µ±Ç°Ñ¡·þLabel
	int serverIndex = itemList->getCurrentIndex();

	if (m_CurrentChoseServer)
	{
		m_CurrentChoseServer->setString(LoginHelper::getServerName(serverIndex).c_str());
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------

void ServerList::keyBackClicked()
{
	LoginHelper::switchView(LoginView::login);
}

void ServerList::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (CPEventHelper::getEventSource() == "HandleMessageEnterServerResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				CPPlatform->operate(PlatformOpID::enter_server);
				LoginHelper::saveServerAndRegionIndex(itemList->getCurrentIndex(), mRegionIndex);
				if(LoginHelper::getPlayerCnt() > 0)
				{
					LoginHelper::switchView(LoginView::selectrole);
				}
				else
				{
					LoginHelper::switchView(LoginView::createrole);
				}
			}
		}
	}
	else if (eventName == CPEventName::NET_CHANGE)
	{
		const int &changeType = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
		if (changeType == Event::NETWORKBORN)
		{
			CPEvtDispatcher.removeEventListener(CPEventName::NET_CHANGE, this);
			int serverIndex = itemList->getCurrentIndex();
			if (serverIndex < 0)
			{
				serverIndex = LoginHelper::getSavedServerIndex();
				if (serverIndex < 0)
				{
					serverIndex = 0;
				}
				LoginHelper::setcurSerIndex(serverIndex);
			}
			if (serverIndex >= 0)
			{
				mChecker->start(LayoutData::getString(CPModuleName::LOGIN, "enterServerNote"));
				LoginHelper::enterServerRequest();
				LoginHelper::setcurSerIndex(serverIndex);
			}
		}
	}
}

int ServerList::initIndex()
{
	int state = 0;
	int tjcnt = 0;
	int zccnt = 0;
	int yjcnt = 0;
	int bmcnt = 0;
	int whcnt = 0;
	int indextj = 0;
	int indexzc = 0;
	int indexyj = 0;
	int indexbm = 0;
	int indexwh = 0;
	int serverCnt = LoginHelper::getServerCnt();
	for (int i = 0; i < serverCnt; i++)
	{		
		state = LoginHelper::getServerState(i);
		if (state == TAG_State_deeptuijian)
		{
			index = i;
			break;
		}
		switch (state)
		{
		case TAG_State_weihu:
			{
				indexwh = i;
				whcnt++;
			}
			break;
		case TAG_State_baoman:
			{
				indexbm = i;
				bmcnt++;
			}
			break;
		case TAG_State_yongji:
			{
				indexyj = i;
				yjcnt++;
			}
			break;
		case TAG_State_zhengchang:
			{
				indexzc = i;
				zccnt++;
			}
			break;
		case TAG_State_tuijian:
			{
				indextj = i;
				tjcnt++;
			}
			break;
		default:
			break;
		}
	}
	if (state == TAG_State_deeptuijian)
	{

	}
	else if (tjcnt)
	{
		index = indextj;
	} 
	else if(zccnt)
	{
		index = indexzc;
	} 
	else if(yjcnt)
	{
		index = indexyj;
	} 
	else if(bmcnt)
	{
		index = indexbm;
	} 
	else if(whcnt)
	{
		index = indexwh;
	}
	return index;
}


///////////CreateRole///////////////////////////////////////////////////
CreateRole::CreateRole()
	:roleList(NULL)
	,userNameBox(NULL)
	,mChecker(NULL)
	,mRefreshLayer(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

CreateRole::~CreateRole()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool CreateRole::init()//创建角色界面ui
{
	if (!CCLayer::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	GameData::s_game_state = GAME_STATE_CREATE;

	initUI();
	roleList->setCurrentIndex(0);
	refresh();

	return true;
}

void CreateRole::onEnter()
{
	CCLayer::onEnter();
}

void CreateRole::initUI()
{
	// desc board
	CCSprite *descBoard = LayoutData::getSprite(CPModuleName::LOGIN, "jobDescBoard");
	addChild(descBoard);

	// stand stone
	CCSprite *standStone = LayoutData::getSprite(CPModuleName::LOGIN, "createRoleStandStone");
	addChild(standStone);

	// role list
	const int per = LayoutData::getInt(CPModuleName::LOGIN, "createRolePer");
	CCSize listSize = LayoutData::getSize(CPModuleName::LOGIN, "createList");
	CCPoint listPt = LayoutData::getPoint(CPModuleName::LOGIN, "createList");
	roleList = CPItemComponents::create(listSize, new CPLayoutGrid(per));
	roleList->setPosition(listPt);
	addChild(roleList);

	char ch[32];
	const int cnt = LayoutData::getInt(CPModuleName::LOGIN, "createRoleCnt");
	for (int i = 0; i < cnt; i++ )
	{
		sprintf(ch, "roleList_%d", i);
		CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::LOGIN, ch);
		item->setTarget(this, menu_selector(CreateRole::onList));
		roleList->addItem(item);
	}

	// refresh layer
	mRefreshLayer = CCLayer::create();
	addChild(mRefreshLayer);

	// user name
	int maxlen = 0;
	StaticData::getGlobalData("roleNameMaxLen", maxlen);
	userNameBox = LayoutData::getEditBox(CPModuleName::LOGIN, "userName");
	userNameBox->setMaxLength(maxlen);
	userNameBox->setDelegate(this);
	userNameBox->setText(LoginHelper::getRandomName(0).c_str());
	addChild(userNameBox);

	// label
	CCLabelTTF *backLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "backToRole");
	addChild(backLabel);

	CCLabelTTF *roleCreateLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "roleCreate");
	addChild(roleCreateLabel);

	CCLabelTTF *enterLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "createAndEnter");
	addChild(enterLabel);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *randomBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "randomName");
	randomBtn->setTarget(this, menu_selector(CreateRole::onRandom));
	menu->addChild(randomBtn);

	CCMenuItemImage *createBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "enterInto");
	createBtn->setTarget(this, menu_selector(CreateRole::onCreate));
	menu->addChild(createBtn);

	CCMenuItemImage *returnBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "returnBack");
	returnBtn->setTarget(this, menu_selector(CreateRole::onReturn));
	menu->addChild(returnBtn);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void CreateRole::refresh()
{
	mRefreshLayer->removeAllChildren();

	const int job = LoginHelper::getJobByIndex(roleList->getCurrentIndex());
	// job icon
	CCSprite *jobIcon = LayoutData::getSprite(CPModuleName::LOGIN, "jobIcon" + StringUtils::toString(job));
	mRefreshLayer->addChild(jobIcon);

	// desc
	CCLabelTTF *descLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "jobDesc" + StringUtils::toString(job));
	mRefreshLayer->addChild(descLabel);

	// anim
	const int gender = LoginHelper::getGenderByIndex(roleList->getCurrentIndex());
	CCNode *anim = LoginHelper::getRoleAnim(job, gender);
	anim->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "createRoleAnimMale"));
	mRefreshLayer->addChild(anim);

	if (gender == UserData::SEX_FEMALE)
	{
		anim->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "createRoleAnimFemale"));
	}

	// particle
	CCParticleSystem* starx = CCParticleSystemQuad::create(LayoutData::getString(CPModuleName::LOGIN, "particle").c_str());
	if (starx)
	{
		starx->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "particleCreateRole"));
		mRefreshLayer->addChild(starx, 1, PARTICLE_SYSTEM_TAG);
	}
}

void CreateRole::editBoxEditingDidBegin( CCEditBox *editBox )
{
	mUserNameBeforeEdit = userNameBox->getText();
	userNameBox->setText("");
}

void CreateRole::editBoxReturn( extension::CCEditBox *editBox )
{
	const std::string &userName = userNameBox->getText();
	if (userName.empty())
	{
		userNameBox->setText(mUserNameBeforeEdit.c_str());
	}
}

void CreateRole::onList( CCObject *target )
{
	refresh();
	userNameBox->setText(LoginHelper::getRandomName(roleList->getCurrentIndex()).c_str());
}

void CreateRole::onRandom( CCObject *target )
{
	userNameBox->setText(LoginHelper::getRandomName(roleList->getCurrentIndex()).c_str());
}

void CreateRole::onCreate( CCObject *target )
{
	mChecker->start();
	mLastCreateName.clear();
	if (LoginHelper::testCreateName(userNameBox->getText(), mLastCreateName))
	{
		mChecker->start(LayoutData::getString(CPModuleName::LOGIN, "createRoleNote"));
		LoginHelper::createRoleRequest(roleList->getCurrentIndex(), mLastCreateName);
	}
}

void CreateRole::onReturn( CCObject *target )
{
	LoginHelper::switchView(LoginView::selectrole);
}

void CreateRole::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (CPEventHelper::getEventSource() == "MsgCreatePlayerResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				LoginHelper::setListDataAndEnterGame(roleList->getChildrenCount(), mLastCreateName);
				CPPlatform->operate(PlatformOpID::create_role);
			}
		}
	}
}
/////////////CCMenuR  实现选择角色滑动//////////////////////////////////
CCMenuR::CCMenuR()
	: CCMenu()
{
	m_nPriority = kCCMenuHandlerPriority;
}

CCMenuR* CCMenuR::create()
{
	return create(NULL,NULL);
}

CCMenuR* CCMenuR::create( CCMenuItem* item )
{
	return create(item, NULL);
}

CCMenuR* CCMenuR::create( CCMenuItem* item, ... )
{
	va_list args;
	va_start(args,item);

	CCMenuR *pRet = CCMenuR::createWithItems(item, args);

	va_end(args);

	return pRet;
}
CCMenuR* CCMenuR::createWithItems( CCMenuItem *item, va_list args )
{
	CCArray* pArray = NULL;
	if( item )
	{
		pArray = CCArray::create(item, NULL);
		CCMenuItem *i = va_arg(args, CCMenuItem*);
		while(i)
		{
			pArray->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
	}

	return CCMenuR::createWithArray(pArray);
}

CCMenuR* CCMenuR::createWithArray( CCArray* pArrayOfItems )
{
	CCMenuR *pRet = new CCMenuR();
	if (pRet && pRet->initWithArray(pArrayOfItems))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

void CCMenuR::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_nPriority, false);
}

bool CCMenuR::ccTouchBegan(CCTouch* touch, CCEvent* event){
	m_TouchPos = convertToNodeSpace(touch->getLocation());
	if(!CCMenu::ccTouchBegan(touch,event))
	{
		return false;
	}
	return true;
}

void CCMenuR::ccTouchEnded(CCTouch* touch, CCEvent* event){
	CCMenu::ccTouchEnded(touch,event);
	m_nMoveddir = 0;
}

void CCMenuR::ccTouchMoved(CCTouch* touch, CCEvent* event){
	CCMenu::ccTouchMoved(touch,event);
	CCPoint pos = convertToNodeSpace(touch->getLocation());
	if (pos.x - m_TouchPos.x > 0 )
	{
		m_nMoveddir = 1;
	}else if (m_TouchPos.x - pos.x > 0 )
	{
		m_nMoveddir = 2;
	}	
}

int CCMenuR::getDir(){
	return m_nMoveddir;
}

///////////SelectRole/////////////////////////////////////////////////
#define ROLE_NODE_TAG 3
#define SEL_ANIM_TAG 3

SelectRole::SelectRole()
	:mListMenu(NULL)
	,mDelBtn(NULL)
	,mChecker(NULL)
	,mPrePageBtn(NULL)
	,mNextPagebtn(NULL)
	,mPageLabel(NULL)
	,mCurrentIndex(-1)
	,mCurrentPage(1)
	,mMaxPage(0)
	,mCurWaitingPos(0)
	,mWaitingLable(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

SelectRole::~SelectRole()//登入选择角色界面ui
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool SelectRole::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	GameData::s_game_state = GAME_STATE_SELECT;
	initIndexAndPage();

	initUI();
	refreshButtonStateAndPage();
	refreshList(false);
	selectRole(mCurrentIndex, false);

	return true;
}

void SelectRole::onEnter()
{
	CCLayer::onEnter();
}

void SelectRole::initIndexAndPage()
{
	const int roleCount = LoginHelper::getPlayerCnt();
	if (roleCount <= 1)
	{
		mCurrentIndex = 0;
		mCurrentPage = 1;
		mMaxPage = 1;
	}
	else
	{
		mCurrentIndex = LoginHelper::getSavedRoleIndex();
		if (mCurrentIndex < 0 || roleCount <= mCurrentIndex)
		{
			mCurrentIndex = 0;
		}

		//
		int perPage = LayoutData::getInt(CPModuleName::LOGIN, "selRoleCnt");
		perPage = (perPage > 0 ? perPage : 3);
		mCurrentPage = 1 + mCurrentIndex/perPage;
		mMaxPage = 1 + (roleCount - 1)/perPage;
	}
}

void SelectRole::initUI()
{
	// label
	CCLabelTTF *backLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "backToServer");
	addChild(backLabel);

	CCLabelTTF *enterLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "enterGame");
	addChild(enterLabel);

	mPageLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, "selRolePage");
	addChild(mPageLabel);

	// list layer
	mListMenu = CCMenuR::create();
	mListMenu->setPosition(CCPointZero);
	addChild(mListMenu);

	//
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	mDelBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "delRole");
	mDelBtn->setTarget(this, menu_selector(SelectRole::onDelete));
	mDelBtn->setScale(0.9f);
	menu->addChild(mDelBtn);

	mPrePageBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "prePage");
	mPrePageBtn->setTarget(this, menu_selector(SelectRole::onPrePage));
	menu->addChild(mPrePageBtn);

	mNextPagebtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "nextPage");
	mNextPagebtn->setTarget(this, menu_selector(SelectRole::onNextPage));
	menu->addChild(mNextPagebtn);

	CCMenuItemImage *backBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "returnBack");
	backBtn->setTarget(this, menu_selector(SelectRole::onBackServer));
	menu->addChild(backBtn);

	CCMenuItemImage *enterBtn = LayoutData::getMenuItemImg(CPModuleName::LOGIN, "enterInto");
	enterBtn->setTarget(this, menu_selector(SelectRole::onEnterGame));
	menu->addChild(enterBtn);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);

	updateWaitingLabel();
}

void SelectRole::refreshButtonStateAndPage()
{
	mPrePageBtn->setVisible(true);
	mNextPagebtn->setVisible(true);
	if (mCurrentPage <= 1)
	{
		mPrePageBtn->setVisible(false);
	}

	if (mCurrentPage >= mMaxPage)
	{
		mNextPagebtn->setVisible(false);
	}

	if (mMaxPage == 1)
	{
		mPageLabel->setString("");
	}
	else
	{
		const std::string &page = StringUtils::toString(mCurrentPage) + "/" + StringUtils::toString(mMaxPage);
		mPageLabel->setString(page.c_str());
	}
}

void SelectRole::refreshList( bool withAnim )
{
	clearListMenu();

	const CCSize &itemSize = LayoutData::getSize(CPModuleName::LOGIN, "roleItem");
	const CCPoint &itemPt = LayoutData::getPoint(CPModuleName::LOGIN, "roleItem");
	const int perPage = LayoutData::getInt(CPModuleName::LOGIN, "selRoleCnt");
	for (int i = 0; i < perPage; i++)
	{
		const int &index = i + (mCurrentPage - 1) * perPage;
		const std::string &key = "roleItem" + StringUtils::toString(i);
		CCMenuItem *btn = CCMenuItem::create();
		btn->setTarget(this, menu_selector(SelectRole::onList));
		btn->setScale(LayoutData::getFloat(CPModuleName::LOGIN, key));
		btn->setContentSize(itemSize);
		btn->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, key));
		mListMenu->addChild(btn, 0, index);

		CCNode *roleNode = createRoleNode(index, itemSize);
		roleNode->setAnchorPoint(CCPointZero);
		btn->addChild(roleNode, 0, ROLE_NODE_TAG);

		mIndexToPos[index] = i;
	}

	if (withAnim)
	{
		mCurrentIndex = -1;
		selectRole(getCurrentFirstIndex(), withAnim);
	}
}

void SelectRole::clearListMenu()
{
	typedef std::vector<CCNode *> NodeVect;
	NodeVect nodeVect;
	CCArray *children = mListMenu->getChildren();
	if ( children && children->count() > 0 )
	{
		CCObject* child = NULL;
		CCARRAY_FOREACH(children, child)
		{
			CCNode* pNode = dynamic_cast<CCNode *>(child);
			if (pNode)
			{
				nodeVect.push_back(pNode);
			}
		}
	}

	for (int i = 0; i < (int)nodeVect.size(); i++)
	{
		mListMenu->removeChild(nodeVect[i], true);
	}

	//
	mIndexToPos.clear();
}

CCNode * SelectRole::createRoleNode( int index, const CCSize &nodeSize )
{
	CCNode *ret = CCNode::create();
	ret->setContentSize(nodeSize);

	// stone
	CCSprite *stone = LayoutData::getSprite(CPModuleName::LOGIN, "roleStandStone");
	ret->addChild(stone);

	if (LoginHelper::getPID(index) > 0)
	{
		// job
		CCSprite *jobBoard = LoginHelper::getJobBoard(index);
		ret->addChild(jobBoard);

		// sel anim
		CCNode *selAnim = LoginHelper::getRoleSelAnim();
		selAnim->setVisible(false);
		selAnim->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "selAnim"));
		ret->addChild(selAnim, 0, SEL_ANIM_TAG);

		// anim
		CCNode *roleAnim = LoginHelper::getRoleAnim(index);
		roleAnim->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "roleAnimMale"));
		ret->addChild(roleAnim);
		if (LoginHelper::getPlayerGender(index) == UserData::SEX_FEMALE)
		{
			roleAnim->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "roleAnimFemale"));
		}
	}
	else
	{
		CCSprite *createRole = LayoutData::getSprite(CPModuleName::LOGIN, "createSel");
		ret->addChild(createRole);
	}
	return ret;
}

void SelectRole::selectRole( int index, bool withAnim )
{
	if (index == mCurrentIndex && withAnim)
	{
		mChecker->start();
		LoginHelper::enterGame(mCurrentIndex);
		return;
	}

	if (index < 0 || LoginHelper::getPlayerCnt() <= index)
	{
		index = 0;
	}

	mCurrentIndex = index;
	const int pos = mIndexToPos[mCurrentIndex];
	const int leftIndex = getIndexByPos(pos_left);
	const int middleIndex = getIndexByPos(pos_middle);
	const int rightIndex = getIndexByPos(pos_right);
	mDelBtn->setVisible(false);
	if (pos == pos_left)
	{
		moveTo(leftIndex, pos_middle, withAnim);
		moveTo(middleIndex, pos_right, withAnim);
		moveTo(rightIndex, pos_left, withAnim);
	}
	else if (pos == pos_right)
	{
		moveTo(rightIndex, pos_middle, withAnim);
		moveTo(middleIndex, pos_left, withAnim);
		moveTo(leftIndex, pos_right, withAnim);
	}
	else
	{
		moveTo(leftIndex, pos_left, withAnim);
		moveTo(middleIndex, pos_middle, withAnim);
		moveTo(rightIndex, pos_right, withAnim);
	}
}

void SelectRole::moveTo( int index, int targetPos, bool withAnim )
{
	CCNode *item = mListMenu->getChildByTag(index);
	if (item)
	{
		CCNode *roleNode = item->getChildByTag(ROLE_NODE_TAG);
		if (roleNode)
		{
			CCNode *selAnim = roleNode->getChildByTag(SEL_ANIM_TAG);
			if (selAnim)
			{
				selAnim->setVisible(targetPos == pos_middle);
			}
		}

		item->setZOrder(0);
		if (targetPos == pos_middle)
		{
			CCParticleSystem* starx = CCParticleSystemQuad::create(LayoutData::getString(CPModuleName::LOGIN, "particle").c_str());
			if (starx)
			{
				starx->setPosition(LayoutData::getPoint(CPModuleName::LOGIN, "particleSelectRole"));
				item->addChild(starx, 1, PARTICLE_SYSTEM_TAG);
			}
			item->setZOrder(1);
		}
		else
		{
			CCNode *starx = item->getChildByTag(PARTICLE_SYSTEM_TAG);
			if (starx)
			{
				starx->removeFromParent();
			}
		}

		const float delay = (withAnim ? 0.5f : 0);
		item->stopAllActions();
		const std::string &key = "roleItem" + StringUtils::toString(targetPos);
		CCMoveTo *mt = CCMoveTo::create(delay, LayoutData::getPoint(CPModuleName::LOGIN, key));
		CCScaleTo *st = CCScaleTo::create(delay, LayoutData::getFloat(CPModuleName::LOGIN, key));
		CCActionInterval *act = CCSpawn::create(mt, st, NULL);
		CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(SelectRole::onMoveEnd));
		CCAction *action = CCSequence::create(act, func, NULL);
		item->runAction(action);
		mIndexToPos[index] = targetPos;
	}
}

int SelectRole::getIndexByPos( int pos )
{
	IndexToPos::iterator it = mIndexToPos.begin();
	IndexToPos::iterator itEnd = mIndexToPos.end();
	while (it != itEnd)
	{
		if (it->second == pos)
		{
			return it->first;
		}
		it++;
	}
	return 0;
}

void SelectRole::onBackServer( CCObject *target )
{

	LoginHelper::startAuthServer();
	LoginHelper::authServerListResquest();
	//LoginHelper::switchView(LoginView::serverlist);
}

void SelectRole::onEnterGame( CCObject *target )
{
	int position = 0;
	ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::SEVERQUEUE, position);
	if (position>0)
	{
		updateWaitingLabel();
		CPEventHelper::uiNotify("onEnterGame","",Error::PlayerInStillInQueue);
	}
	else
	{
		mChecker->start();
		LoginHelper::enterGame(mCurrentIndex);
	}
}

void SelectRole::onList( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (!node)
	{
		return;
	}
	int dir = mListMenu->getDir();
	int index = node->getTag();
	if (dir == 1)
	{
		if (mCurrentIndex == 0)
			index = 2;
		else if(mCurrentIndex == 1)
			index = 0;
		else
			index = 1;
	}
	else if (dir == 2)
	{
		if(mCurrentIndex == 0)
			index = 1;
		else if(mCurrentIndex == 1)
			index = 2;
		else
			index = 0;
	}
	if (LoginHelper::getPID(index) > 0)
	{
		selectRole(index, true);
	}
	else if (mMaxPage > 1)
	{
		CPEventHelper::uiNotify("SelectRole", "", Error::RoleTooMuch);
	}
	else
	{
		GameData::s_game_state = GAME_STATE_CREATE;
		LoginHelper::switchView(LoginView::createrole);
	}
}

void SelectRole::onDelete( CCObject *target )
{
	FloatPanel *floatPanel = FloatPanel::create(FloatPanelType::LOGIN_DelRole);
	floatPanel->setHandler(this, floatpanel_selector(SelectRole::onDeleteSelect));
	addChild(floatPanel, 1);
}

void SelectRole::onPrePage( CCObject *target )
{
	if (mCurrentPage <= 1)
	{
		return;
	}

	mCurrentPage--;
	refreshButtonStateAndPage();
	refreshList(true);
}

void SelectRole::onNextPage( CCObject *target )
{
	if (mCurrentPage >= mMaxPage)
	{
		return;
	}

	mCurrentPage++;
	refreshButtonStateAndPage();
	refreshList(true);
}

void SelectRole::onDeleteSelect( int btnTag )
{
	mChecker->start();
	if (btnTag == Button_QD)
	{
		mChecker->start(LayoutData::getString(CPModuleName::LOGIN, "delRoleNote"));
		LoginHelper::delRoleRequest(mCurrentIndex);
	}
}

void SelectRole::onMoveEnd()
{
	if (LoginHelper::getPID(mCurrentIndex) > 0)
	{
		mDelBtn->setVisible(true);
	}
}

void SelectRole::updateWaitingLabel()
{
	int position = 0;
	ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::SEVERQUEUE, position);
	if (position==0 && mCurWaitingPos==0)
	{
		return;
	}

	if (mWaitingLable==NULL)
	{
		mWaitingLable = LayoutData::getLabelTTF(CPModuleName::LOGIN, "waitInQueue");
		mWaitingLable->runAction(CCFadeIn::create(1.0f));

		this->addChild(mWaitingLable);
	}

	if (position>0)
	{
		CCString* pStr=CCString::createWithFormat(LayoutData::getString(CPModuleName::LOGIN, "waitInQueueStr").c_str(),position);
		if (pStr && mWaitingLable)
		{
			mWaitingLable->setString(pStr->getCString());
		}
	}
	else
	{
		mWaitingLable->runAction(CCFadeOut::create(1.0f));
	}
}

int SelectRole::getCurrentFirstIndex()
{
	const int perPage = LayoutData::getInt(CPModuleName::LOGIN, "selRoleCnt");
	return (mCurrentPage - 1) * perPage;
}

void SelectRole::onCPEvent( const std::string &eventName )
{
	mChecker->stop();
	if (eventName == CPEventName::MSG_FINISH)
	{
		const std::string &source = CPEventHelper::getEventSource();
		if (source == "HandleMessageEnterServerResponse" ||
			source == "HandleMessageDeletePlayerResponse")
		{
			if (CPEventHelper::isRequestSuccess())
			{
				initIndexAndPage();
				refreshButtonStateAndPage();
				if (source == "HandleMessageEnterServerResponse")
				{
					refreshList(false);
					selectRole(LoginHelper::getSavedRoleIndex(), false);
				}
				else
				{
					refreshList(true);
				}
			}

		}
		else if (source == "HandleMsgServerQueueNotify")
		{
			updateWaitingLabel();
		}
		else if (CPEventHelper::getEventSource() == "HandleMessageAuthServerListNotifyEnd")
		{
			// Modify By Tony. 2014/09/22 09:22
			// µÇÂ¼Á÷³ÌÐÞ¸Ä;
			// ÕËºÅÑéÖ¤Ê±AMSÖ»·µ»ØÉÏ´ÎµÇÂ¼µÄ·þÎñÆ÷»òÍÆ¼ö·þÎñÆ÷;
			// Ñ¡Ôñ·þÎñÆ÷ÁÐ±íºó¿ªÊ¼»ñÈ¡·þÎñÆ÷ÁÐ±í;
			// ÁÐ±í»ñÈ¡³É¹¦ºó´ò¿ª·þÎñÆ÷Ñ¡Ôñ½çÃæ;
			if (CPEventHelper::isRequestSuccess())
			{
				// ´ò¿ª·þÎñÆ÷½çÃæ;
				LoginHelper::switchView(LoginView::serverlist);
			}

		}
	}
}


// Modify By Tony. 2014/10/9 9:26
// GameNotifition


ScrollLabel::ScrollLabel()
{
	m_labelList = NULL;
}
ScrollLabel::~ScrollLabel()
{
	if(m_labelList)
	{
		m_labelList->removeAllObjects();
		m_labelList->release();
		m_labelList = NULL;
	}
	/*if(m_pTarget)
	{
	m_pTarget->release();
	m_pTarget = NULL;
	}*/

}



bool ScrollLabel::init()
{
	if (!CCNode::init())
	{
		return false;
	}
	
	initUI();
	return true;
}
void ScrollLabel::initUI()
{

	if (!m_labelList)
	{
		m_labelList = CCArray::create();
		m_labelList->retain();
	}
	const char *gameannouncement[] = 
	{
		"gameannouncement1", "gameannouncement2", "gameannouncement3", "gameannouncement4"
	};

	for (int i = 0; i < 4; i++)
	{
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::LOGIN, gameannouncement[i]);;
		pLabel->setAnchorPoint(ccp(0.5f,0));
		m_labelList->addObject(pLabel);
		addChild(pLabel);
	}

	float height = 0.0f;
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(m_labelList, pObject)
	{
		CCLabelTTF* pLabel = dynamic_cast<CCLabelTTF*>(pObject);
		CCSize size = pLabel->getContentSize();
		pLabel->setPositionY(height);
		height -= size.height;
	}

	scheduleScroll();

}


void ScrollLabel::scheduleScroll()
{
	runAction(CCSequence::create(
		CCDelayTime::create(2.5f),
		CCCallFunc::create(this, callfunc_selector(ScrollLabel::fadeFirstLine)),
		CCDelayTime::create(0.5f),
		CCCallFunc::create(this, callfunc_selector(ScrollLabel::moveLine)),
		NULL
		)
		);
}

void ScrollLabel::fadeFirstLine()
{
	if (m_labelList->count() == 0)
	{
		return;
	}
	CCObject* pObject = m_labelList->objectAtIndex(0);
	if (!pObject)
	{
		return;
	}

	CCLabelTTF* pLabel = dynamic_cast<CCLabelTTF*>(pObject);
	pLabel->runAction(CCFadeOut::create(0.5));
}

void ScrollLabel::moveLine()
{
	if (m_labelList->count() == 0)
	{
		return;
	}

	CCObject *pfirstObject = m_labelList->objectAtIndex(0);
	m_labelList->removeObject(pfirstObject, false);
	m_labelList->addObject(pfirstObject);
	//m_labelList->exchangeObjectAtIndex(0, m_labelList->count() - 1);
	CCObject* pObject = m_labelList->objectAtIndex(0);
	if (!pObject)
	{
		return;
	}

	CCLabelTTF* pLabel = dynamic_cast<CCLabelTTF*>(pObject);
	pLabel->setOpacity(0xFF);
	pLabel->setPositionY(-pLabel->getContentSize().height);
	pLabel->runAction(CCEaseIn::create(CCMoveTo::create(1.0f, CCPointMake(pLabel->getPositionX(), 0)), 8.0f));
	scheduleScroll();
}

