#include "RechargePanel.h"
#include "VIPModule.h"
#include "MsgWorld.h"
#include "ItemDefinition.h"
#include "PlatformDefinition.h"

#include "utils/StringUtils.h"

#include "logic/platform/IPlatform.h"

#include "controls/CPItemComponents.h"

#include "userdata/LayoutData.h"
#include "userdata/HeroData.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/SystemData.h"
#if defined APPSTORE_VERSION
#include "../../../../ios/channel/common/ChannelHelper.h"
#endif

#define RECHARGE_SUB_PANEL_TAG	12

namespace RechargeView
{
	enum
	{
		normal = 0,

		alipay = 1,
		yi_dong_card = 2,
		lian_tong_card = 3,
		dian_xin_card = 4,

		max,
	};
}

///////RechargePanel/////////////////////////////////////////////
RechargePanel::RechargePanel()
	:mSwitchList(NULL)
	,mCurrentView(RechargeView::normal)
{

}

RechargePanel::~RechargePanel()
{

}

bool RechargePanel::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}

	// 35i 使用非定额支付
	const int channelID = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	if (channelID == ChannelID::_35i
		|| channelID == ChannelID::_35i_another)
	{
		CPPlatform->pay(0);
		return false;
	}

	initUI();

	mSwitchList->setCurrentIndex(mCurrentView);
	switchView();

	return true;
}

void RechargePanel::onEnter()
{
	FullScreenPanel::onEnter();
#if defined APPSTORE_VERSION
    CHANNELHELPER->endPay();
#endif
}

void RechargePanel::initUI()
{
	// title
	CCSprite *title = LayoutData::getSprite(CPModuleName::VIP, "rechargeTitle");
	addChild(title);

	// board
	CCScale9Sprite *leftBoard = LayoutData::getScale9Sprite(CPModuleName::VIP, "rechargeLeftBoard");
	addChild(leftBoard);

	CCScale9Sprite *rightBoard = LayoutData::getScale9Sprite(CPModuleName::VIP, "rechargeRightBoard");
	addChild(rightBoard);

	CCScale9Sprite *rightSubBoard = LayoutData::getScale9Sprite(CPModuleName::VIP, "rechargeRightSubBoard");
	addChild(rightSubBoard);

	// switch list
	const CCSize &switchSize = LayoutData::getSize(CPModuleName::VIP, "rechargeList");
	mSwitchList = CPItemComponents::create(switchSize, new CPLayoutList);
	mSwitchList->setPosition(LayoutData::getPoint(CPModuleName::VIP, "rechargeList"));
	addChild(mSwitchList);
	if (true)
	{
		CCMenuItemImage *btn = LayoutData::getMenuItemLabelImage(CPModuleName::VIP, "recharge0");
		btn->setTarget(this, menu_selector(RechargePanel::onList));
		mSwitchList->addItem(btn);
	}
	else
	{
		mCurrentView = RechargeView::alipay;
		for (int i = RechargeView::alipay; i < RechargeView::max; i++)
		{
			const std::string &key = "recharge" + StringUtils::toString(i);
			CCMenuItemImage *btn = LayoutData::getMenuItemLabelImage(CPModuleName::VIP, key);
			btn->setTarget(this, menu_selector(RechargePanel::onList));
			mSwitchList->addItem(btn);
			btn->setTag(i);
		}
	}

	// recharge type note
	CCLabelTTF *noteLabel = LayoutData::getLabelTTF(CPModuleName::VIP, "rechargeTypeHead");
	addChild(noteLabel);

	// get gold note
	CCLabelTTF *goldLabel = LayoutData::getLabelTTF(CPModuleName::VIP, "rechargeGetGold");
	addChild(goldLabel);

	CCSprite *goldIcon = LayoutData::getSprite(CPModuleName::VIP, "rechargeGold");
	addChild(goldIcon);
}

void RechargePanel::switchView()
{
	CCLayer *subPanel = NULL;
	switch (mCurrentView)
	{
	case RechargeView::normal:
		subPanel = NormalRechargePanel::create();
		break;
	case RechargeView::alipay:
		break;
	case RechargeView::yi_dong_card:
		break;
	case RechargeView::lian_tong_card:
		break;
	case RechargeView::dian_xin_card:
		break;
	default:
		CCLog(">>>Error: RechargePanel::switchView, unknown view = %d", mCurrentView);
		break;
	}

	if (subPanel)
	{
		CCNode *child = getChildByTag(RECHARGE_SUB_PANEL_TAG);
		if (child)
		{
			child->removeFromParent();
		}
		addChild(subPanel, 0, RECHARGE_SUB_PANEL_TAG);
	}
}

void RechargePanel::onList( CCObject *target )
{
	const int view = mSwitchList->getCurrentIndex();
	if (view != mCurrentView)
	{
		mCurrentView = view;
		switchView();
	}
}

void RechargePanel::onCPEvent( const std::string &eventName )
{

}

//////////NormalRechargePanel//////////////////////////////////////////////
NormalRechargePanel::NormalRechargePanel()
	:mRechargeValueList(NULL)
	,goldBox(NULL)
	,mGoldLabel(NULL)
{

}

NormalRechargePanel::~NormalRechargePanel()
{

}

bool NormalRechargePanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initUI();
	mRechargeValueList->setCurrentIndex(0);
	refreshGold();

	return true;
}

void NormalRechargePanel::onEnter()
{
	CCLayer::onEnter();
}

void NormalRechargePanel::initUI()
{
	CCLabelTTF *rechargeTypeLabel = LayoutData::getLabelTTF(CPModuleName::VIP, "rechargeType0");
	addChild(rechargeTypeLabel);

	CCLabelTTF *chooseLabel = LayoutData::getLabelTTF(CPModuleName::VIP, "rechargeChoose");
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ios_91)
	{
		chooseLabel = LayoutData::getLabelTTF(CPModuleName::VIP, "rechargeChoose_91");
	}
	addChild(chooseLabel);

	const CCSize &listSize = LayoutData::getSize(CPModuleName::VIP, "normalRechargeList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::VIP, "normalRechargeListItem");
	const int firstLine = LayoutData::getInt(CPModuleName::VIP, "rechargeFirstLine");
	mRechargeValueList = CPItemComponents::create(listSize, new CPLayoutGrid(firstLine, itemSize, true));
	mRechargeValueList->setPosition(LayoutData::getPoint(CPModuleName::VIP, "normalRechargeList"));
	addChild(mRechargeValueList);
	int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
	int cnt = LayoutData::getInt(CPModuleName::VIP, "rechargeValueCnt");
	int cnt_channel = LayoutData::getInt(CPModuleName::VIP,"rechargeValueCnt_"+StringUtils::toString(channel_id));
	if (cnt_channel > 0)
	{
		cnt = cnt_channel;
	}
    if (channel_id == ChannelID::ios_appstore) {
        cnt = LayoutData::getInt(CPModuleName::VIP, "appstore_rechargeValueCnt");
    }
	for (int i = 0; i < cnt; i++)
	{
		CCMenuItem *btn = getRechargeNum(i);
		btn->setTarget(this, menu_selector(NormalRechargePanel::onChangeNum));
		mRechargeValueList->addItem(btn);
	}

	mGoldLabel = LayoutData::getLabelTTF(CPModuleName::VIP, "rechargeGetGoldNum");
	addChild(mGoldLabel);

	//---------a bo luo
	if (channel_id == ChannelID::aboluo_rexuetianya)
	{
		 goldBox = LayoutData::getEditBox(CPModuleName::VIP, "extraGold");
		 CCLabelTTF *chooseLabel = LayoutData::getLabelTTF(CPModuleName::VIP, "exarechargeChoose");
		 if (goldBox)
		 {
			 goldBox->setTouchPriority(kCCMenuHandlerPriority);
			 goldBox->setInputMode(kEditBoxInputModeNumeric);
			 goldBox->setDelegate(this);
			 addChild(goldBox);
			 addChild(chooseLabel);
		 }
	}

	// recharge menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *rechargeBtn = LayoutData::getMenuItemImg(CPModuleName::VIP, "recharge");
	rechargeBtn->setTarget(this, menu_selector(NormalRechargePanel::onRecharge));
	menu->addChild(rechargeBtn);
}

void NormalRechargePanel::refreshGold()
{
	const int index = mRechargeValueList->getCurrentIndex();
    int yuan = LayoutData::getInt(CPModuleName::VIP, "rechargeValue" + StringUtils::toString(index));
    int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
    if (channel_id == ChannelID::ios_appstore) {
        yuan = LayoutData::getInt(CPModuleName::VIP, "appstore_rechargeValue" + StringUtils::toString(index));
    }
	const int goldPerYuan = LayoutData::getInt(CPModuleName::VIP, "goldPerYuan");
	const std::string &goldStr = "x" + StringUtils::toString(goldPerYuan * yuan);
	mGoldLabel->setString(goldStr.c_str());
	if (channel_id == ChannelID::aboluo_rexuetianya)
	{
		if (goldBox)
		{
			std::string str_yuan = goldBox->getText();
			if (str_yuan != "")
			{
				yuan = SystemData::stringToInt(str_yuan.c_str());
				str_yuan = "x" + StringUtils::toString(goldPerYuan * yuan);
				mGoldLabel->setString(str_yuan.c_str());
			}
		}
	}
}

void NormalRechargePanel::onChangeNum( CCObject *target )
{
	refreshGold();
}

void NormalRechargePanel::onRecharge( CCObject *target )
{
	int canRecharge = 0;
	LuaData::getProp("gdGame","canRecharge",canRecharge);
	if (canRecharge == 1)
	{
		const int index = mRechargeValueList->getCurrentIndex();
        int yuan = LayoutData::getInt(CPModuleName::VIP, "rechargeValue" + StringUtils::toString(index));
        int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
        if (channel_id == ChannelID::ios_appstore) {
            yuan = LayoutData::getInt(CPModuleName::VIP, "appstore_rechargeValue" + StringUtils::toString(index));
        }
		if (channel_id == ChannelID::aboluo_rexuetianya)
		{
			std::string str_yuan = goldBox->getText();
			if (str_yuan != "")
			{
				yuan = SystemData::stringToInt(str_yuan.c_str());
				if (yuan <= 0)
				{
					yuan = 1;
					goldBox->setText("1");
				}
			}
		}
		CPPlatform->pay(yuan);
	}
	else
	{
		CPEventHelper::uiNotify("SocialPanel", "", Error::FeaturesNotYetOpen);
	}
}

CCMenuItem * NormalRechargePanel::getRechargeNum( int index )
{
	const CCSize &size = LayoutData::getSize(CPModuleName::VIP, "normalRechargeListItem");
	CCSprite *norm = LayoutData::getSprite(CPModuleName::VIP, "rechargeValueCheckedBoard");
	CCSprite *sel = LayoutData::getSprite(CPModuleName::VIP, "rechargeValueCheckedBoard");
	CCSprite *flag = LayoutData::getSprite(CPModuleName::VIP, "rechargeValueCheckedFlag");
	sel->addChild(flag);
	CCMenuItemSprite *ret = CCMenuItemSprite::create(norm, sel);
	ret->setContentSize(size);

    int yuan = LayoutData::getInt(CPModuleName::VIP, "rechargeValue" + StringUtils::toString(index));
    int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
    if (channel_id == ChannelID::ios_appstore) {
        yuan = LayoutData::getInt(CPModuleName::VIP, "appstore_rechargeValue" + StringUtils::toString(index));
    }
	std::string yuanWords;
	yuanWords = LayoutData::getString(CPModuleName::VIP, "yuan");
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ios_91)
	{
		yuanWords = LayoutData::getString(CPModuleName::VIP,"yuan_91");
	}
	const std::string &yuanStr = StringUtils::toString(yuan) + yuanWords;
	CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::VIP, "rechargeValue");
	label->setString(yuanStr.c_str());
	ret->addChild(label);
	return ret;
}

void NormalRechargePanel::editBoxTextChanged( CCEditBox* editBox, const std::string& text )//goldBox callBack
{
	refreshGold();
}

void NormalRechargePanel::editBoxReturn( CCEditBox* editBox )
{

}
