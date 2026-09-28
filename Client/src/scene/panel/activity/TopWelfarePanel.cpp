#include "TopWelfarePanel.h"
#include "EntityDefinition.h"
#include "ActivityModule.h"

#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/GameRole.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"
#include "ext/CCActionDestroy.h"

#include "network/HandleMessage.h"

#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/SlideTable.h"
#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "utils/StringUtils.h"
#include "EveryDaySalaryPanel.h"
#include "FirstChargePanel.h"
#include "EveryDayFirstChargePanel.h"
#include "AddUpChargePanel.h"
#include "MonthGiftPanel.h"
#include "TimeLimitGiftPanel.h"
#include "OnlineGiftPanel.h"
#include "ConsumeDrawPanel.h"
#include "SingleRechargePanel.h"


TopWelfarePanel::TopWelfarePanel()
{
}

TopWelfarePanel::~TopWelfarePanel()
{
	
}

bool TopWelfarePanel::init()//福利ui
{
	if (!MenuListPanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "welfareTitle");
	addChild(title);
    
  
    
	return true;
}

void TopWelfarePanel::hide()
{
	this->removeFromParent();
}

const std::string TopWelfarePanel::dataTableName()
{
	return "gdWelfareOptions";
}

void TopWelfarePanel::onSwitch(int tag)
{
	CCLog("______________%s__%d",__FUNCTION__,tag);
	switch (tag)
	{
	case Panel_FirstCharge:
		{
			showGirl(1);
			FirstChargePanel* panel = FirstChargePanel::create();
			addPanel(panel);
			break;
		}
	case Panel_EveryDayFirstCharge:
		{
			showGirl(2);
			EveryDayFirstChargePanel* panel = EveryDayFirstChargePanel::create();
			addPanel(panel);
			break;
		}
	case Panel_AddUpCharge: 
		{
			showGirl(1);
			AddUpChargePanel* panel = AddUpChargePanel::create();
			addPanel(panel);
			break;
		}
	case Panel_MonthGift:
		{
			showGirl(2);
			MonthGiftPanel* panel = MonthGiftPanel::create();
			addPanel(panel);
			break;
		}
	case Panel_TimeLimitGift:
		{
			TimeLimitGiftPanel* panel = TimeLimitGiftPanel::create();
			addPanel(panel);
			break;
		}
	case Panel_OnlineGift:
		{
			OnlineGiftPanel* panel = OnlineGiftPanel::create();
			addPanel(panel);
			break;
		}
	case Panel_ConsumeDraw:
		{
			ConsumeDrawPanel* panel = ConsumeDrawPanel::create();
			addPanel(panel);
			break;
		}
	case Panel_SingleRecharge:
		{
			SingleRechargePanel *panel = SingleRechargePanel::create();
			addPanel(panel);
			break;
		}
	default:
		break;
	}
}
void TopWelfarePanel::showGirl(int girlID)
{
	//妹子
	if (girlID)
	{
		CCSprite* girlSprite = SystemData::getSpriteByPlist("activity.sprite.girl"+StringUtils::toString(girlID));
		if (!girlSprite)
			return;
		girlSprite->setPosition(SystemData::getLayoutPoint("activity.sprite.girl"));
		girlSprite->setAnchorPoint(ccp(1,0));
		addPanel(girlSprite);
	}
}