#include "TimeLimitGiftPanel.h"
#include "EntityDefinition.h"
#include "MsgPlayer.h"
#include "GiftDefinition.h"
#include "EffectDefinition.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/ActivityData.h"
#include "event/EventProtocol.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"

#include "userdata/netdata/GameRole.h"

#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"
#include "ext/CCMenuEx.h"
#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/EffectSprite.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/SlideTable.h"

#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "controls/CPItemComponents.h"
#include "utils/StringUtils.h"
#include "utils/StringUtils.h"
#include "ActivityDataHelper.h"

#include "module/ModuleData.h"
#include "userdata/LayoutData.h"
#include "res/CPAnimationManager.h"

#define MINUTES_PER_HOUR 60
#define SECONDS_PER_MINUTE 60
#define SECONDS_PER_HOUR 3600

TimeLimitGiftPanel::TimeLimitGiftPanel()
	: m_updater(NULL)
	, m_TimeLimit(NULL)
	, m_Prefix(SystemData::getLayoutString("timelimitgift.label.timelimit"))
	, m_Day(SystemData::getLayoutString("timelimitgift.label.timelimit.day"))
	, m_Hour(SystemData::getLayoutString("timelimitgift.label.timelimit.hour"))
	, m_Min(SystemData::getLayoutString("timelimitgift.label.timelimit.min"))
	, m_Sec(SystemData::getLayoutString("timelimitgift.label.timelimit.sec"))
	, m_limitTime(0)
{
	m_OptionsList.clear();
}

TimeLimitGiftPanel::~TimeLimitGiftPanel()
{
	
}

bool TimeLimitGiftPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_limitTime = getRemainTime();

	initSprite();

	//Ö÷Òªmenu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	initLabels();
	initButtons();
	initRewards();
	
	refreshLimitTimeString();
	if (m_limitTime > 0)
	{
		schedule(schedule_selector(TimeLimitGiftPanel::updateTime), 1.0f);
	}
	
	return true;
}

void TimeLimitGiftPanel::initSprite()
{
	CCSprite* sprite2 = SystemData::getSpriteByPlist("timelimitgift.sprite.jine");
	sprite2->setAnchorPoint(CCPointZero);
	addChild(sprite2);
	CCSprite* sprite3 = SystemData::getSpriteByPlist("timelimitgift.sprite.dalibao");
	sprite3->setAnchorPoint(CCPointZero);  
	addChild(sprite3);  
	for (int i=0;i<5;i++)
	{
		CCSprite* sprite = SystemData::getSpriteByPlist("activity.sprite.item.frame");
		CCPoint point = SystemData::getLayoutPoint("timelimitgift.sprite.item"+StringUtils::toString(i));
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(point);
		addChild(sprite);
	}
}
void TimeLimitGiftPanel::MenuCallBack(CCObject* pSender)
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case Button_GetReward:
			{
				MsgGetGiftRequest* msg = new MsgGetGiftRequest;
				msg->GiftCate = Gift::gift_limittime;
				msg->GiftType = 0;
				HandleMessage::sendMessage(msg);
				break;
			}
		default:
			break;
		}
	}
}

void TimeLimitGiftPanel::initLabels()
{
	CCLabelTTF* label1 = SystemData::getLabelTTF("timelimitgift.label.qinaidewanjia");
	label1->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label1);

	CCLabelTTF* label2 = SystemData::getLabelTTF("timelimitgift.label.jike");  
	label2->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label2);

	CCLabelTTF* label3 = SystemData::getLabelTTF("timelimitgift.label.huode");
	label3->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label3);

	m_TimeLimit = SystemData::getLabelTTF("timelimitgift.label.timelimit");
	m_TimeLimit->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(m_TimeLimit);
}

void TimeLimitGiftPanel::initButtons()
{
	CCMenuItemImage* button1 = SystemData::getMenuItemImageByPlist("timelimitgift.button.getreward");
	button1->setTarget(this,menu_selector(TimeLimitGiftPanel::MenuCallBack));
	button1->setAnchorPoint(CCPointZero);
	button1->setVisible(m_limitTime > 0);
	m_pMainMenu->addChild(button1, 0, Button_GetReward); 
}

int TimeLimitGiftPanel::getRemainTime()
{
	const int totalTime = ActivityDataHelper::getDataY(Gift_TimeLimitGift, 1) * SECONDS_PER_HOUR;
	const int remainTime = totalTime - (ActivityData::getWorldTime() - ActivityData::getWorldBeginTime());
	if (remainTime > 0)
	{
		return remainTime;
	}
	return 0;
}

void TimeLimitGiftPanel::refreshLimitTimeString()
{
	if (!m_TimeLimit)
	{
		return;
	}

	const int time = m_limitTime;
	const int hour = time/SECONDS_PER_HOUR;
	const int min = time%SECONDS_PER_HOUR/SECONDS_PER_MINUTE;
	const int sec = time%SECONDS_PER_MINUTE;
	const std::string &str = m_Prefix
		+StringUtils::toString(hour)+m_Hour
		+StringUtils::toString(min)+m_Min
		+StringUtils::toString(sec)+m_Sec;
	m_TimeLimit->setString(str.c_str());
}

void TimeLimitGiftPanel::updateTime(float dt)
{
	m_limitTime -= dt;
	if (m_limitTime <= 0)
	{
		m_limitTime = 0;
		unschedule(schedule_selector(TimeLimitGiftPanel::updateTime));

		CCNode *btn = m_pMainMenu->getChildByTag(Button_GetReward);
		if (btn)
		{
			btn->setVisible(false);
		}
	}
	refreshLimitTimeString();
}

void TimeLimitGiftPanel::initRewards()
{
	for (int i=0;i<5;i++)
	{
		CCPoint point = SystemData::getLayoutPoint("timelimitgift.sprite.item"+StringUtils::toString(i));

		int sid = ActivityDataHelper::getItemStaticID(Gift_TimeLimitGift,1,i+1);
		int cnt = ActivityDataHelper::getItemCount(Gift_TimeLimitGift,1,i+1); 
		if (sid>0&&cnt>0)
		{ 
			UserItem* item = CommonFunction::createNewItem(sid);
			item->count = cnt;
			CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
			pItem->setPosition(ccp(point.x+33,point.y+33));
			pItem->setTarget(this,menu_selector(TimeLimitGiftPanel::itemCallBack));
			m_pMainMenu->addChild(pItem);

			CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
			pSprite->setPosition(pItem->getPosition());
			m_pMainMenu->addChild(pSprite);
		}
	}
}
void TimeLimitGiftPanel::showTooltip(CCMenuItem* pImage)
{
	// show tips
	CCPoint tipsPos = pImage->convertToWorldSpace(ccp(pImage->getContentSize().width,pImage->getContentSize().height-100));
	if(tipsPos.x+245>SystemData::size_x) 
	{
		tipsPos.x -= 245+pImage->getContentSize().width;
	}
	UserItem* userItem = (UserItem*)pImage->getUserData();
	if (userItem->category==ItemCate_Equip)
	{
		tipsPos.y=0;
	}
	Game::getGameUI()->showTipsPanel(userItem,TAG_Tips,tipsPos);
}
void TimeLimitGiftPanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}