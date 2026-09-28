#include "SystemSetting.h"
#include "MainUIModule.h"
#include "PlatformDefinition.h"

#include "userdata/LayoutData.h"

#include "scene/SceneManager.h"
#include "scene/panel/MainPanel.h"

#include "event/CPEventHelper.h"

#include "utils/StringUtils.h"

#include "controls/CPNodeHelper.h"

#include "logic/platform/IPlatform.h"
#include "logic/platform/PlatformOpID.h"
#include "userdata/SystemData.h"
#include "userdata/UserData.h"
#include "ext/GeneralMenu.h"
#include "ext/CCMenuItemTextImage.h"
#include "scene/Login.h"
#include "scene/LoginHelper.h"
#include "res/PlistLoader.h"


#include "ext/../../ios/channel/common/ChannelHelper.h"

namespace SettingMenu
{
	enum
	{
		begin = 0,
		return_login = 0,
		return_select_role = 1,
		system_setting = 2,
		exit_game = 3,
		account_management = 4,
		enter_bbs = 5,
		enter_userCenter = 6,
		account_info = 7,
		max,
	};
};

static bool needShowAccountManagement()
{
	const int channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	const std::string &key = "showAccountManagementBtn" + StringUtils::toString(channelID);
	const int showFlag = LayoutData::getInt(CPModuleName::MAIN_UI, key);
	return (showFlag != 0);
}

static bool needShowBBS()
{
	const int channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	const std::string &key = "showBBSBtn" + StringUtils::toString(channelID);
	const int showFlag = LayoutData::getInt(CPModuleName::MAIN_UI, key);
	return (showFlag != 0);
}

///////SystemSetting/////////////////////////////////////////////////
SystemSetting::SystemSetting()
{

}

SystemSetting::~SystemSetting()
{

}

bool SystemSetting::init()//系统ui
{
	if (!BaseNotePanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	initUI();
	
	return true;
}
void SystemSetting::onEnter()
{
	BaseNotePanel::onEnter();
	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}
void SystemSetting::initUI()
{
	setTitle(LayoutData::getString(CPModuleName::MAIN_UI, "systemSettingTitle"));

	//
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	for (int i = SettingMenu::begin; i < SettingMenu::max; i++)
	{
		const std::string &key = "systemSetting" + StringUtils::toString(i);
		CCMenuItemImage *btn = LayoutData::getMenuItemLabelImage(CPModuleName::MAIN_UI, key);
		btn->setTarget(this, menu_selector(SystemSetting::onClick));
// 		if (i == SettingMenu::enter_userCenter)
// 		{
// 			if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID)==ChannelID::ios_itools)
// 			{
// 				menu->addChild(btn, 0, i);
// 				continue;
// 			}
// 			else
// 			{
// 				continue;
// 			}
// 		}
		if (i == SettingMenu::enter_userCenter)
		{
#if defined (IT_VERSION) || defined (TB_VERSION) || defined (PP_VERSION)  || defined (C91_VERSION)  || defined (KY_VERSION)|| defined (I4_VERSION)
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
			menu->addChild(btn, 0, i);	
#endif
#endif
		}
		else if (i == SettingMenu::account_info)
		{
			//try play account ! if upgrade , disappear!
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			if(CHANNELHELPER->isQuickPlay())
			{
				menu->addChild(btn, 0, i);
			}
#endif
		}
		else
		{
			menu->addChild(btn, 0, i);
		}
	}

	//
	if (!needShowAccountManagement())
	{
		CCNode *node = menu->getChildByTag(SettingMenu::account_management);
		if (node)
		{
			node->setVisible(false);
		}
	}
	
	if (!needShowBBS())
	{
		CCNode *node = menu->getChildByTag(SettingMenu::enter_bbs);
		if (node)
		{
			node->setVisible(false);
		}
	}
}

void SystemSetting::onClick( CCObject *target )
{
	CCNode *btn = dynamic_cast<CCNode *>(target);
	if(btn)
	{
		const int tag = btn->getTag();
		switch (tag)
		{
		case SettingMenu::return_login:
		CPPlatform->operate(PlatformOpID::delete_amount);
			SceneManager::switchToLogin();
			break;
		case SettingMenu::return_select_role:
			SceneManager::switchToRoleList();
			break;
		case SettingMenu::system_setting:
			CPEventHelper::openPanel("MainPanel", TAG_Setting_Panel, 0, 0, 1);
			break;
		case SettingMenu::exit_game:
			{
				CPPlatform->operate(PlatformOpID::exitGame);
				const int channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
				if (channelID == ChannelID::_91
					|| channelID == ChannelID::sougou
					|| channelID == ChannelID::jvyou
					||channelID ==ChannelID::youmi_jinglongzhuan
					|| channelID == ChannelID::qihoo
					|| channelID == ChannelID::uc
					|| channelID == ChannelID::aiyouxi
					|| channelID == ChannelID::uc_lieyanzhanshen
					 )
					break;
				SceneManager::exitGame();
				break;
			}
		case SettingMenu::account_management:
			CPPlatform->operate(PlatformOpID::account_management);
			break;
		case SettingMenu::enter_bbs:
			CPPlatform->operate(PlatformOpID::enter_bbs);
			break;
        case SettingMenu::enter_userCenter:
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            CHANNELHELPER->showUserCenter();
#endif
            break;
		case SettingMenu::account_info:
			this->removeFromParent();
			CPEventHelper::openPanel("AccountInfo");
			break;
		default:
			CCLog(">>>Error: SystemSetting::onClick, unknown tag = %d", tag);
			break;
		}
	}
}


AccountInfo::AccountInfo():
	userName(""),
	userPwd("")
{

}

AccountInfo::~AccountInfo()
{

}

bool AccountInfo::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();
	initUsDesc();
	initButton();
	return true;
}

void AccountInfo::onEnter()
{
	CCLayer::onEnter();
}

void AccountInfo::initUI()
{
	CCSprite* pborder=SystemData::getSpriteByPlist("ui_panel_accountinfo");
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	pborder->setPosition(ccp(winsize.width/2,winsize.height/2));
	addChild(pborder);
}

void AccountInfo::initUsDesc()
{
	CCLabelTTF* shuoming = LayoutData::getLabelTTF("main_ui","accountinfo_shuoming");
	addChild(shuoming);

	std::string str1 = LayoutData::getString("main_ui","accountinfo_01");
	CCLabelTTF* str1_label = CCLabelTTF::create(str1.c_str(),"",15);
	str1_label->setAnchorPoint(ccp(0,0.5));
	str1_label->setPosition(ccp(160,311));
	std::string str2 = LayoutData::getString("main_ui","accountinfo_02");
	CCLabelTTF* str2_label = CCLabelTTF::create(str2.c_str(),"",15);
	str2_label->setAnchorPoint(ccp(0,0.5));
	str2_label->setPosition(ccp(160,280));
	addChild(str1_label);
	addChild(str2_label);

	CCLabelTTF* dangqian = LayoutData::getLabelTTF("main_ui","accountinfo_dangqian");
	addChild(dangqian);

	CCLabelTTF* zhanghao = LayoutData::getLabelTTF("main_ui","accountinfo_shiwanzh");
	addChild(zhanghao);

	CCLabelTTF* mima = LayoutData::getLabelTTF("main_ui","accountinfo_shiwanmm");
	addChild(mima);

	userName = UserData::getStringData("account");
	userPwd = UserData::getStringData("password");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	userName = CHANNELHELPER->getQuickUserName();
	userPwd = CHANNELHELPER->getQuickPassword();
#endif
	CCLabelTTF* name_label = CCLabelTTF::create(userName.c_str(),"",15);
	CCLabelTTF* pwd_label = CCLabelTTF::create(userPwd.c_str(),"",15);
	name_label->setAnchorPoint(ccp(0,0.5));
	name_label->setPosition(ccp(300,zhanghao->getPositionY()));
	pwd_label->setAnchorPoint(ccp(0,0.5));
	pwd_label->setPosition(ccp(500,mima->getPositionY()));
	addChild(name_label);
	addChild(pwd_label);
}

void AccountInfo::initButton()
{
	GeneralMenu* menu = GeneralMenu::create();
	if (menu)
	{
		menu->setAnchorPoint(CCPointZero);
		menu->setPosition(CCPointZero);
		addChild(menu);
	}
	CCMenuItemImage* pclose=LayoutData::getMenuItemImg("main_ui","contactusTuichu");
	pclose->setTarget(this,menu_selector(AccountInfo::onClose));
	menu->addChild(pclose);

	CCMenuItemTextImage *pPutOff =  SystemData::getMenuItemTextImage("ui.button",SystemData::getLayoutString("panel_shengjiac_label").c_str(),"微软雅黑",15,ccWHITE);
	pPutOff->setTarget(this,menu_selector(AccountInfo::onClick));
	pPutOff->setPosition(ccp(400,105));
	menu->addChild(pPutOff);
}

void AccountInfo::onClick( CCObject *target )
{
	this->removeFromParent();
	PlistLoader::loadLogin();
	CPEventHelper::openPanel("Register_3737");
//	LoginHelper::switchView(LoginView::ios_3737_register);
}

void AccountInfo::onClose( CCObject* pSender )
{
	this->removeFromParent();
}