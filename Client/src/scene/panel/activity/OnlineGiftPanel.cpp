#include "OnlineGiftPanel.h"
#include "EntityDefinition.h"
#include "GiftDefinition.h"
#include "EffectDefinition.h"
#include "EvtDataDefinition.h"
#include "MsgPlayer.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/ActivityData.h"

#include "userdata/netdata/GameRole.h"

#include "event/EventProtocol.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"
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
#include "ActivityDataHelper.h"

#include "module/ModuleData.h"
#include "userdata/LayoutData.h"
#include "res/CPAnimationManager.h"

OnlineGiftPanel::OnlineGiftPanel()
	: m_updater(NULL)
	, m_TimeLabel(NULL)
	, mRewardContainer(NULL)
	, m_Time(0.0f)
{
	m_OptionsList.clear();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

OnlineGiftPanel::~OnlineGiftPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool OnlineGiftPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initSprite();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	initLabels();
	initButtons();
	initRewards();
	refreshReward();

	const int remainTime = ActivityData::getExDataY(EvtData::evt_gfmrzxlb) - ActivityData::getWorldTime();
	const int hasGet = ActivityData::getExDataZ(EvtData::evt_gfmrzxlb);
	if (hasGet == 0)
	{
		setTotalTime(remainTime);
	}
	else
	{
		m_TimeLabel->setString(SystemData::getLayoutString("onlinegift.label.time.finish").c_str());
	}

	return true;
}

void OnlineGiftPanel::initSprite()
{
	for (int i=0;i<12;i++)
	{
		CCSprite* sprite = SystemData::getSpriteByPlist("activity.sprite.item.frame");
		CCPoint point = SystemData::getLayoutPoint("onlinegift.sprite.item"+StringUtils::toString(i));
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(point);
		addChild(sprite);
	}
}
void OnlineGiftPanel::MenuCallBack(CCObject* pSender)
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
				msg->GiftCate = Gift::gift_online;
				msg->GiftType = 0;
				HandleMessage::sendMessage(msg);
				break;
			}
		default:
			break;
		}
	}
}

void OnlineGiftPanel::initLabels()
{
	CCLabelTTF* label1 = SystemData::getLabelTTF("onlinegift.label.jike");
	label1->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label1);

	CCLabelTTF* label2 = SystemData::getLabelTTF("onlinegift.label.huode");
	label2->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label2);

	m_TimeLabel = SystemData::getLabelTTF("onlinegift.label.time");
	m_TimeLabel->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_TimeLabel);
}

void OnlineGiftPanel::initButtons()
{
	CCMenuItemImage* button2 = SystemData::getMenuItemImageByPlist("onlinegift.button.getreward");
	button2->setTarget(this,menu_selector(OnlineGiftPanel::MenuCallBack));
	button2->setAnchorPoint(CCPointZero);
	button2->setTag(Button_GetReward);
	m_pMainMenu->addChild(button2);
}

void OnlineGiftPanel::initRewards()
{
	mRewardContainer = GeneralMenu::create();
	mRewardContainer->setPosition(CCPointZero);
	addChild(mRewardContainer);
}

void OnlineGiftPanel::refreshReward()
{
	mRewardContainer->removeAllChildren();

	int giftID = ActivityData::getExDataX(EvtData::evt_gfmrzxlb);
	if (giftID < 1)
	{
		giftID = 1;
	}

	//当前奖励
	for (int i=0;i<6;i++)
	{
		CCPoint point = SystemData::getLayoutPoint("onlinegift.sprite.item"+StringUtils::toString(i));

		int sid = ActivityDataHelper::getItemStaticID(Gift_OnlineGift,giftID,i+1);
		int cnt = ActivityDataHelper::getItemCount(Gift_OnlineGift,giftID,i+1); 
		if (sid>0&&cnt>0)
		{ 
			UserItem* item = CommonFunction::createNewItem(sid);
			item->count = cnt;
			CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
			pItem->setPosition(ccp(point.x+33,point.y+33));
			pItem->setTarget(this,menu_selector(OnlineGiftPanel::itemCallBack));
			mRewardContainer->addChild(pItem);

			CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
			pSprite->setPosition(pItem->getPosition());
			mRewardContainer->addChild(pSprite);
		}
	}

	//下次奖励
	for (int i=6;i<12;i++)
	{
		CCPoint point = SystemData::getLayoutPoint("onlinegift.sprite.item"+StringUtils::toString(i));

		int sid = ActivityDataHelper::getItemStaticID(Gift_OnlineGift,giftID+1,i-5);
		int cnt = ActivityDataHelper::getItemCount(Gift_OnlineGift,giftID+1,i-5); 
		if (sid>0&&cnt>0)
		{ 
			UserItem* item = CommonFunction::createNewItem(sid);
			item->count = cnt;
			CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
			pItem->setPosition(ccp(point.x+33,point.y+33));
			pItem->setTarget(this,menu_selector(OnlineGiftPanel::itemCallBack));
			mRewardContainer->addChild(pItem);

			CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
			pSprite->setPosition(pItem->getPosition());
			mRewardContainer->addChild(pSprite);
		}
	}
}

void OnlineGiftPanel::showTooltip(CCMenuItem* pImage)
{
	// show tips
	CCPoint tipsPos = pImage->convertToWorldSpace(ccp(pImage->getContentSize().width,pImage->getContentSize().height-160));
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
void OnlineGiftPanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}
void OnlineGiftPanel::setTimeString(int pSec)
{
	if (!m_TimeLabel)
	{
		return;
	}

	if (pSec<=0)
	{
		//
		const std::string &str = SystemData::getLayoutString("onlinegift.label.time.done");
		m_TimeLabel->setString(str.c_str());
		return;
	}

	int hour = pSec%(3600*24)/3600;
	int min = pSec%3600/60;
	int sec = pSec%60;
	
	const std::string &m_Hour = SystemData::getLayoutString("onlinegift.label.time.hour");
	const std::string &m_Min = SystemData::getLayoutString("onlinegift.label.time.min");
	const std::string &m_Sec = SystemData::getLayoutString("onlinegift.label.time.sec");
	const std::string &m_Prefix = SystemData::getLayoutString("onlinegift.label.time");
	const std::string &str = 
		StringUtils::toString(hour)+m_Hour
		+StringUtils::toString(min)+m_Min
		+StringUtils::toString(sec)+m_Sec
		+ m_Prefix;
	m_TimeLabel->setString(str.c_str());
}

void OnlineGiftPanel::setTotalTime(int pSec)
{
	if (pSec<0)
	{
		pSec = 0;
	}
	m_Time = pSec;
	setTimeString(pSec);
	unschedule(schedule_selector(OnlineGiftPanel::updateTime));
	if (m_Time > 0)
	{
		schedule(schedule_selector(OnlineGiftPanel::updateTime));
	}
}

void OnlineGiftPanel::updateTime(float dt)
{
	m_Time -= dt;
	if (m_Time <= 0)
	{
		m_Time = 0;
		unschedule(schedule_selector(OnlineGiftPanel::updateTime));
	}
	setTimeString(m_Time);
}

void OnlineGiftPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageSyncPlayerEventDataNotify")
		{
			const int activityID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (activityID == EvtData::evt_gfmrzxlb)
			{
				const int remainTime = ActivityData::getExDataY(EvtData::evt_gfmrzxlb) - ActivityData::getWorldTime();
				const int hasGet = ActivityData::getExDataZ(EvtData::evt_gfmrzxlb);
				if (hasGet == 0)
				{
					setTotalTime(remainTime);
				}
				else
				{
					m_TimeLabel->setString(SystemData::getLayoutString("onlinegift.label.time.finish").c_str());
				}
				refreshReward();
			}
		}
	}
}