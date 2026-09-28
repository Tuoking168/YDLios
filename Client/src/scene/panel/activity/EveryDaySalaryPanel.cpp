#include "EveryDaySalaryPanel.h"
#include "EntityDefinition.h"
#include "MsgPlayer.h"
#include "GiftDefinition.h"
#include "ErrorDefinition.h"
#include "EffectDefinition.h"
#include "EvtDataDefinition.h"
#include "ActivityModule.h"
#include "ActivityDefinition.h"
#include "ModuleData.h"
#include "ActivityDataHelper.h"

#include "userdata/ActivityData.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/luadata/LuaData.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"
#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"
#include "ext/CCMenuEx.h"

#include "network/HandleMessage.h"

#include "scene/panel/EffectSprite.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/SlideTable.h"
#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"

#include <time.h>
#include "utils/StringUtils.h"

#include "controls/CPItemComponents.h"

#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"

#include "res/CPAnimationManager.h"


static const int m_Row = 7;
static const int m_Column = 5;
static const int SIGN_REWARD_BUTTON_COUNT = 5;

static bool hasGetSignReward( int index )
{
	const int data = ActivityData::getExDataY(EvtData::evt_gfmrqd);
	const int mark = 1 << index;
	const int result = data & mark;
	return (result != 0);
}

static int getSignRewardIndex()
{
	for (int i = 0; i < SIGN_REWARD_BUTTON_COUNT; i++)
	{
		if (!hasGetSignReward(i))
		{
			return i;
		}
	}
	return 0;
}

static bool isCurrentWeek( int day, int currentDay, int currentWeek )
{
	if (currentWeek == 0)
	{
		currentWeek = 7;
	}
	return (currentDay - day < currentWeek);
}

////////////EveryDaySalaryPanel///////////////////////////////////////
EveryDaySalaryPanel::EveryDaySalaryPanel()
	: m_updater(NULL)
	, m_CurMonth(0)
	, m_CurYear(0)
	, m_CurDay(0)
	, m_CurWeek(0)
	, m_LabelCurMonth(NULL)
	, m_LabelAddupSign(NULL)
	, m_LabelPatchSign(NULL)
	, m_LabelOpenDays(NULL)
	, m_LabelAddupOnline(NULL)
	, m_LabelOnline(NULL)
	, m_LabelCurTicket(NULL)
	, m_LabelCurHonor(NULL)
	, m_LabelLastTicket(NULL)
	, m_LabelLastHonor(NULL)
	, m_indexSelected(0)
	, m_RewardMgr(NULL)
{
	m_CalendarList.clear();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

EveryDaySalaryPanel::~EveryDaySalaryPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool EveryDaySalaryPanel::init()//每周工资ui
{
	if (!FullScreenPanel::init())
	{
		return false;
	}

	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	initFrame();
	initSprite();
	initMenu();
	initLabels();
	initButtons();
	initCalendarData(); 
	initCalendar();
	selectButtonWithIndex(getSignRewardIndex());

	const int openDays = ActivityData::getWorldBeginDays();
	setOpenDays(openDays);

	int coupon = 0, honor = 0, index = 0;
	StaticData::getWeekSalaryData(openDays, coupon, honor, index);
	if (index > 0)
	{
		setOnline(index);
	}
	else
	{
		setOnline(1);
	}

	const int thisWeekHours = ActivityData::getExDataY(EvtData::evt_gfmzgz);
	setAddupOnline(thisWeekHours);
	setCurTicket(coupon * thisWeekHours);
	setCurHonor(honor * thisWeekHours);

	const int PER_WEEK = 7;
	const int lastWeekHours = ActivityData::getExDataX(EvtData::evt_gfmzgz);
	StaticData::getWeekSalaryData(openDays - PER_WEEK, coupon, honor, index);
	setLastTicket(coupon * lastWeekHours);
	setLastHonor(honor * lastWeekHours);
	
	return true;
}

void EveryDaySalaryPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if(source == "HandleMessageSyncPlayerEventDataNotify")
	{
		const int activityID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
		if (activityID == EvtData::evt_gfmrqd)
		{
			refreshmrqd();
			const int index = getSignRewardIndex();
			if (index != m_indexSelected)
			{
				selectButtonWithIndex(index);
			}
		}
	}
}

void EveryDaySalaryPanel::refreshmrqd()
{
	int signCount = 0;
	const int signDay = ActivityData::getExDataX(EvtData::evt_gfmrqd);
	for (int tag = 0; tag != Calendar_End - Calendar_Start; tag ++)
	{
		CalendarInfo& calendar = m_CalendarList[tag];

		if (m_CurYear==calendar.year&&m_CurMonth==calendar.month)
		{
			if ((signDay & ((int) 1 <<calendar.day))&&calendar.isSigned==false)
			{
				CCPoint point = SystemData::getLayoutPoint("everydaysalary.button.calendar");
				CCSprite* tick = SystemData::getSpriteByPlist("everydaysalary.sprite.honggou");
				tick->setPosition(ccp(point.x+calendar.column*60,point.y-calendar.row*30));
				tick->setPositionX(tick->getPositionX()+10);
				m_pMainMenu->addChild(tick);  			
				calendar.isSigned=true;
			}

			if (calendar.isSigned)
			{
				signCount++;
			}
		}
	}

	setAddupSign(signCount);

	int patchCount = m_CurDay - signCount;
	if (patchCount < 0)
	{
		patchCount = 0;
	}
	setPatchSign(patchCount);
}

void EveryDaySalaryPanel::initFrame()
{
	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "everyDaySalaryTitle");
	addChild(title);

	CCSize size1 = SystemData::getLayoutSize("everydaysalary.frame.calendar");
	CCPoint point1 = SystemData::getLayoutPoint("everydaysalary.frame.calendar");
	CCScale9Sprite *frame1=SystemData::getScale9SpriteByPlist("guild.menuback",size1.width,size1.height);
	frame1->setAnchorPoint(CCPointZero);  
	frame1->setPosition(point1); 
	addChild(frame1);	

	CCSize size2 = SystemData::getLayoutSize("everydaysalary.frame.reward");
	CCPoint point2 = SystemData::getLayoutPoint("everydaysalary.frame.reward");
	CCScale9Sprite *frame2=SystemData::getScale9SpriteByPlist("guild.menuback",size2.width,size2.height);
	frame2->setAnchorPoint(CCPointZero);  
	frame2->setPosition(point2); 
	addChild(frame2);	

	CCSize size3 = SystemData::getLayoutSize("everydaysalary.frame.info");
	CCPoint point3 = SystemData::getLayoutPoint("everydaysalary.frame.info");
	CCScale9Sprite *frame3=SystemData::getScale9SpriteByPlist("guild.menuback",size3.width,size3.height);
	frame3->setAnchorPoint(CCPointZero);  
	frame3->setPosition(point3); 
	addChild(frame3);	

	CCSize size4 = SystemData::getLayoutSize("everydaysalary.frame.account");
	CCPoint point4 = SystemData::getLayoutPoint("everydaysalary.frame.account");
	CCScale9Sprite *frame4=SystemData::getScale9SpriteByPlist("guild.menuback",size4.width,size4.height);
	frame4->setAnchorPoint(CCPointZero);  
	frame4->setPosition(point4); 
	addChild(frame4);
}

void EveryDaySalaryPanel::initSprite()
{
	CCSprite* sprite2 = SystemData::getSpriteByPlist("everydaysalary.sprite.ewailingqu");
	sprite2->setAnchorPoint(CCPointZero); 
	addChild(sprite2);
	CCSprite* sprite3 = SystemData::getSpriteByPlist("everydaysalary.sprite.jiuyuelaiyuechun");
	sprite3->setAnchorPoint(CCPointZero);  
	addChild(sprite3);
	CCSprite* sprite4 = SystemData::getSpriteByPlist("everydaysalary.sprite.meirigongzi");
	sprite4->setAnchorPoint(CCPointZero);  
	addChild(sprite4);
	CCSize size5 = SystemData::getLayoutSize("everydaysalary.sprite.rewardline");
	CCScale9Sprite* sprite5=SystemData::getScale9SpriteByPlist("everydaysalary.sprite.rewardline",size5.width,size5.height);
	sprite5->setAnchorPoint(CCPointZero);  
	addChild(sprite5); 
	CCSize size6 = SystemData::getLayoutSize("everydaysalary.sprite.meiriline1");
	CCScale9Sprite* sprite6=SystemData::getScale9SpriteByPlist("everydaysalary.sprite.meiriline1",size6.width,size6.height);
	sprite6->setAnchorPoint(CCPointZero);  
	addChild(sprite6);  
	CCSize size7 = SystemData::getLayoutSize("everydaysalary.sprite.meiriline2");
	CCScale9Sprite* sprite7=SystemData::getScale9SpriteByPlist("everydaysalary.sprite.meiriline2",size7.width,size7.height);
	sprite7->setAnchorPoint(CCPointZero);  
	addChild(sprite7);  
	for (int i=0;i<8;i++)
	{
		CCSprite* sprite = SystemData::getSpriteByPlist("activity.sprite.item.frame");
		CCPoint point = SystemData::getLayoutPoint("everydaysalary.sprite.item"+StringUtils::toString(i));
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(point);
		addChild(sprite);
	}
}

void EveryDaySalaryPanel::initMenu()
{
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	m_RewardMgr = GeneralMenu::create();
	m_RewardMgr->setPosition(CCPointZero);
	m_RewardMgr->setAnchorPoint(CCPointZero);
	addChild(m_RewardMgr);
}

void EveryDaySalaryPanel::MenuCallBack(CCObject* pSender)
{
	LOG_TRACE;
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag>=Button_Sign_Start&&tag<=Button_Sign_End)
		{
			selectButtonWithIndex(tag-Button_Sign_Start);
			return;
		}

		switch (tag)
		{
		case Button_Get:
			{
				if (hasGetSignReward(m_indexSelected))
				{
					CPEventHelper::uiNotify("EveryDaySalaryPanel", "", Error::AlreadyGet);
					return;
				}
				MsgGetGiftRequest* msg = new MsgGetGiftRequest;
				msg->GiftCate = Gift::gift_sign_up;
				msg->GiftType = m_indexSelected;
				HandleMessage::sendMessage(msg);
				break;
			}
		case Button_GetReward:
			{
				const int flag = ActivityData::getExDataZ(EvtData::evt_gfmzgz);
				if (flag != 0)
				{
					CPEventHelper::uiNotify("EveryDaySalaryPanel", "", Error::AlreadyGet);
					return;
				}
				MsgGetGiftRequest* msg = new MsgGetGiftRequest;
				msg->GiftCate = Gift::gift_week;
				msg->GiftType = 0;
				HandleMessage::sendMessage(msg);
				break;
			}
		default:
			break;
		}
	}
}

void EveryDaySalaryPanel::initLabels()
{
	m_LabelCurMonth = SystemData::getLabelTTF("everydaysalary.label.curmonth");//
	m_LabelCurMonth->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelCurMonth);

	m_LabelAddupSign = SystemData::getLabelTTF("everydaysalary.label.addupsign");//
	m_LabelAddupSign->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelAddupSign);

	m_LabelPatchSign = SystemData::getLabelTTF("everydaysalary.label.patchsign");//
	m_LabelPatchSign->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelPatchSign);

	m_LabelOpenDays = SystemData::getLabelTTF("everydaysalary.label.opendays");//
	m_LabelOpenDays->setHorizontalAlignment(kCCTextAlignmentCenter);  
	addChild(m_LabelOpenDays);

	CCLabelTTF* label5 = SystemData::getLabelTTF("everydaysalary.label.open1");
	label5->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label5);
	label5->setString((SystemData::getLayoutString("everydaysalary.label.open1")+SystemData::getLayoutString("everydaysalary.label.open1.reward")).c_str());

	CCLabelTTF* label6 = SystemData::getLabelTTF("everydaysalary.label.open22");
	label6->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label6);
	label6->setString((SystemData::getLayoutString("everydaysalary.label.open22")+SystemData::getLayoutString("everydaysalary.label.open22.reward")).c_str());

	CCLabelTTF* label7 = SystemData::getLabelTTF("everydaysalary.label.open43");
	label7->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label7);
	label7->setString((SystemData::getLayoutString("everydaysalary.label.open43")+SystemData::getLayoutString("everydaysalary.label.open43.reward")).c_str());

	m_LabelAddupOnline = SystemData::getLabelTTF("everydaysalary.label.adduponline");//
	m_LabelAddupOnline->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelAddupOnline);

	m_LabelOnline = SystemData::getLabelTTF("everydaysalary.label.online");//
	m_LabelOnline->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelOnline);

	CCLabelTTF* label10 = SystemData::getLabelTTF("everydaysalary.label.curweekreward");
	label10->setHorizontalAlignment(kCCTextAlignmentLeft);  
	addChild(label10);

	CCLabelTTF* label11 = SystemData::getLabelTTF("everydaysalary.label.curticket");
	label11->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label11);

	m_LabelCurTicket = CCLabelTTF::create("Loading","Arial",18);
	m_LabelCurTicket->setPosition(ccp(label11->getPosition().x+70,label11->getPosition().y));
	m_LabelCurTicket->setAnchorPoint(label11->getAnchorPoint());
	m_LabelCurTicket->setColor(ccGREEN);  
	m_LabelCurTicket->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelCurTicket);

	CCLabelTTF* label12 = SystemData::getLabelTTF("everydaysalary.label.curhonor");
	label12->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label12);

	m_LabelCurHonor = CCLabelTTF::create("Loading","Arial",18);
	m_LabelCurHonor->setPosition(ccp(label12->getPosition().x+70,label12->getPosition().y));
	m_LabelCurHonor->setAnchorPoint(label12->getAnchorPoint());
	m_LabelCurHonor->setColor(ccGREEN);  
	m_LabelCurHonor->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelCurHonor);

	CCLabelTTF* label13 = SystemData::getLabelTTF("everydaysalary.label.lastweekreward");
	label13->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label13);

	CCLabelTTF* label14 = SystemData::getLabelTTF("everydaysalary.label.lastticket");
	label14->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label14);

	m_LabelLastTicket = CCLabelTTF::create("Loading","Arial",18);
	m_LabelLastTicket->setPosition(ccp(label14->getPosition().x+70,label14->getPosition().y));
	m_LabelLastTicket->setAnchorPoint(label14->getAnchorPoint());
	m_LabelLastTicket->setColor(ccWHITE);  
	m_LabelLastTicket->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelLastTicket);

	CCLabelTTF* label15 = SystemData::getLabelTTF("everydaysalary.label.lasthonor");
	label15->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label15);

	m_LabelLastHonor = CCLabelTTF::create("Loading","Arial",18);
	m_LabelLastHonor->setPosition(ccp(label15->getPosition().x+70,label15->getPosition().y));
	m_LabelLastHonor->setAnchorPoint(label15->getAnchorPoint());
	m_LabelLastHonor->setColor(ccWHITE);  
	m_LabelLastHonor->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelLastHonor);
}

void EveryDaySalaryPanel::setCurMonth(int pMonth)
{
	if (!m_LabelCurMonth)return;
	std::string pSuffix = SystemData::getLayoutString("everydaysalary.label.curmonth");
	std::string str = StringUtils::toString(pMonth)+pSuffix;
	m_LabelCurMonth->setString(str.c_str());
}

void EveryDaySalaryPanel::setAddupSign(int pCnt)
{
	if (!m_LabelAddupSign)return;
	std::string pPrefix = SystemData::getLayoutString("everydaysalary.label.addupsign");
	std::string str = pPrefix + StringUtils::toString(pCnt);
	m_LabelAddupSign->setString(str.c_str());
}

void EveryDaySalaryPanel::setPatchSign(int pCnt)
{
	if (!m_LabelPatchSign)return;
	std::string pPrefix = SystemData::getLayoutString("everydaysalary.label.patchsign");
	std::string str = pPrefix + StringUtils::toString(pCnt);
	m_LabelPatchSign->setString(str.c_str());
}

void EveryDaySalaryPanel::setOpenDays(int pDays)
{
	if (!m_LabelOpenDays)return;
	std::string pPrefix = SystemData::getLayoutString("everydaysalary.label.opendays");
	std::string pSuffix = SystemData::getLayoutString("everydaysalary.label.opendays.day");
	std::string str = pPrefix + StringUtils::toString(pDays) + pSuffix;
	m_LabelOpenDays->setString(str.c_str());
}

void EveryDaySalaryPanel::setAddupOnline(int pTime)
{
	if (!m_LabelAddupOnline)return;
	const std::string &pPrefix = SystemData::getLayoutString("everydaysalary.label.adduponline");
	const std::string &pSuffix1 = SystemData::getLayoutString("everydaysalary.label.adduponline.hour");
	const std::string &str = pPrefix + StringUtils::toString(pTime) + pSuffix1;
	m_LabelAddupOnline->setString(str.c_str());
}

void EveryDaySalaryPanel::setOnline(int pType)
{
	if (!m_LabelOnline)return;
	std::string pPrefix = SystemData::getLayoutString("everydaysalary.label.online"); 
	std::string pSuffix = "";
	if (pType==1)		//1-21
	{
		pSuffix = SystemData::getLayoutString("everydaysalary.label.open1.reward");
	}
	else if (pType==2)		//22-42
	{
		pSuffix = SystemData::getLayoutString("everydaysalary.label.open22.reward");
	}
	else if (pType==3)		//>=43
	{
		pSuffix = SystemData::getLayoutString("everydaysalary.label.open43.reward");
	}
	std::string str = pPrefix + pSuffix ;
	m_LabelOnline->setString(str.c_str());
}

void EveryDaySalaryPanel::setCurTicket(int pCnt)
{
	if (!m_LabelCurTicket)return;
	m_LabelCurTicket->setString(StringUtils::toString(pCnt).c_str());
}

void EveryDaySalaryPanel::setCurHonor(int pCnt)
{
	if (!m_LabelCurHonor)return;
	m_LabelCurHonor->setString(StringUtils::toString(pCnt).c_str());
}

void EveryDaySalaryPanel::setLastTicket(int pCnt)
{
	if (!m_LabelLastTicket)return;
	m_LabelLastTicket->setString(StringUtils::toString(pCnt).c_str());
}

void EveryDaySalaryPanel::setLastHonor(int pCnt)
{
	if (!m_LabelLastHonor)return;
	m_LabelLastHonor->setString(StringUtils::toString(pCnt).c_str());
}

void EveryDaySalaryPanel::initButtons()
{
	for (int i = 0; i < SIGN_REWARD_BUTTON_COUNT; i++)
	{
		CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.placard.button",80,35);
		CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",80,35);
		CCMenuItemSprite *button =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(EveryDaySalaryPanel::MenuCallBack));
		if(button)
		{ 
			CCLabelTTF *pLabel=SystemData::getLabelTTF("everydaysalary.button.sign"+StringUtils::toString(i)+".label");
			pLabel->setFontSize(16);
			pLabel->setColor(ccWHITE);
			button->setTag(Button_Sign_Start+i);
			button->setPosition(SystemData::getLayoutPoint("everydaysalary.button.sign"+StringUtils::toString(i)));
			pLabel->setPosition(button->getPosition());
			m_pMainMenu->addChild(button);
			m_pMainMenu->addChild(pLabel);
		}
	}

	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.button",80,35);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.button.sel",80,35);
	CCMenuItemSprite *button1 =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(EveryDaySalaryPanel::MenuCallBack));
	if(button1)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("everydaysalary.button.signreward.label");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		button1->setTag(Button_Get);
		button1->setPosition(SystemData::getLayoutPoint("everydaysalary.button.signreward"));
		pLabel->setPosition(button1->getPosition());
		m_pMainMenu->addChild(button1);
		m_pMainMenu->addChild(pLabel);
	}
	CCMenuItemImage* button2 = SystemData::getMenuItemImageByPlist("everydaysalary.button.getreward");
	button2->setTarget(this,menu_selector(EveryDaySalaryPanel::MenuCallBack));
	button2->setAnchorPoint(CCPointZero);
	button2->setTag(Button_GetReward);
	m_pMainMenu->addChild(button2);
}

void EveryDaySalaryPanel::loadRewards(int idx)
{
	m_RewardMgr->removeAllChildrenWithCleanup(true);
	for (int i=0;i<6;i++)
	{
		CCPoint point = SystemData::getLayoutPoint("everydaysalary.sprite.item"+StringUtils::toString(i));

		int sid = ActivityDataHelper::getItemStaticID(Gift_EveryDaySalary,idx+1,i+1);
		int cnt = ActivityDataHelper::getItemCount(Gift_EveryDaySalary,idx+1,i+1); 
		if (sid>0&&cnt>0)
		{ 
			UserItem* item = CommonFunction::createNewItem(sid);
			item->count = cnt;
			CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
			pItem->setPosition(ccp(point.x+33,point.y+33));
			pItem->setTarget(this,menu_selector(EveryDaySalaryPanel::itemCallBack));
			m_RewardMgr->addChild(pItem);

			CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
			pSprite->setPosition(pItem->getPosition());
			m_RewardMgr->addChild(pSprite);
		}
	}
	for (int i=6;i<8;i++)
	{
		CCPoint point = SystemData::getLayoutPoint("everydaysalary.sprite.item"+StringUtils::toString(i));

		int sid = ActivityDataHelper::getExItemStaticID(Gift_EveryDaySalary,idx+1,i-5);
		int cnt = ActivityDataHelper::getExItemCount(Gift_EveryDaySalary,idx+1,i-5); 
		if (sid>0&&cnt>0)
		{ 
			UserItem* item = CommonFunction::createNewItem(sid);
			item->count = cnt;
			CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
			pItem->setPosition(ccp(point.x+33,point.y+33));
			pItem->setTarget(this,menu_selector(EveryDaySalaryPanel::itemCallBack));
			m_RewardMgr->addChild(pItem);

			CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
			pSprite->setPosition(pItem->getPosition());
			m_RewardMgr->addChild(pSprite);
		}
	}
}

void EveryDaySalaryPanel::selectButtonWithIndex(int idx)
{
	CCMenuItem* selButton = (CCMenuItem*)m_pMainMenu->getChildByTag(Button_Sign_Start+idx);
	if (!selButton)
	{
		return;
	}
	selButton->selected();

	CCMenuItem* curButton = (CCMenuItem*)m_pMainMenu->getChildByTag(Button_Sign_Start+m_indexSelected);
	if (curButton)
	{
		curButton->unselected();
	}
	
	m_indexSelected = idx;
	loadRewards(idx);
}

void EveryDaySalaryPanel::showTooltip(CCMenuItem* pImage)
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

void EveryDaySalaryPanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}
//日历
void EveryDaySalaryPanel::initCalendar()
{
	setCurMonth(m_CurMonth);
	for (int i=0;i<7;i++)
	{
		CCLabelTTF* label = SystemData::getLabelTTF("everydaysalary.sprite.weekday"+StringUtils::toString(i)+".label");
		CCScale9Sprite* sprite = SystemData::getScale9SpriteByPlist("everydaysalary.sprite.weekday"+StringUtils::toString(i),60,30);
		label->setPosition(sprite->getPosition());
		label->setColor(ccYELLOW);
		addChild(sprite);
		addChild(label);
	}
	
	if (m_updater)
	{
		m_updater->removeFromParentAndCleanup(true);
		m_updater = NULL;
	}
	m_updater = CPUpdater::create(this, cpupdater_selector(EveryDaySalaryPanel::addListItem));
	m_updater->setUpdateTimes(m_CalendarList.size());
	addChild(m_updater);
	m_updater->start();
}

void EveryDaySalaryPanel::addListItem(int idx )
{
	if (idx >= (int)m_CalendarList.size())
	{
		return;
	}
	CalendarInfo calendar = m_CalendarList[idx];
	CCPoint point = SystemData::getLayoutPoint("everydaysalary.button.calendar");
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("everydaysalary.button.calendar",60,30);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("everydaysalary.button.calendar.sel",60,30);
	p1->setPosition(CCPointZero);
	p1->setAnchorPoint(CCPointZero);
	pSel1->setPosition(CCPointZero);
	pSel1->setAnchorPoint(CCPointZero);
	pSel1->setColor(ccBLACK);
	pSel1->setOpacity(100);
	CCMenuItemSprite *button =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(EveryDaySalaryPanel::clickCalendar));
	if(button)
	{ 
		CCLabelTTF *pLabel=CCLabelTTF::create(StringUtils::toString(calendar.day).c_str(),"Arial",16);
		pLabel->setColor(ccWHITE);
		bool isWeekends = calendar.column==0||calendar.column==6;
		if (m_CurMonth==calendar.month)
		{
			pLabel->setColor(isWeekends?ccc3(0,228,255):ccWHITE);
		}
		else
		{
			pLabel->setColor(isWeekends?ccc3(0,186,255):ccGRAY);
		}
		button->setTag(Calendar_Start+idx);    
		button->setPosition(ccp(point.x+calendar.column*60,point.y-calendar.row*30));
		pLabel->setPosition(button->getPosition());
		pLabel->setPositionX(pLabel->getPositionX()-10);
		m_pMainMenu->addChild(button);  
		m_pMainMenu->addChild(pLabel);
		if (calendar.isSigned)
		{
			CCPoint point = SystemData::getLayoutPoint("everydaysalary.button.calendar");
			CCSprite* tick = SystemData::getSpriteByPlist("everydaysalary.sprite.honggou");
			tick->setPosition(button->getPosition());
			tick->setPositionX(tick->getPositionX()+10);
			m_pMainMenu->addChild(tick);  
		}
	}
}

void EveryDaySalaryPanel::clickCalendar(CCObject* pSender)
{
	LOG_TRACE;
	CCMenuItem* pNode = dynamic_cast<CCMenuItem*>(pSender);
	if(pNode)
	{
		const int tag = pNode->getTag()-Calendar_Start;
		if (tag >= (int)m_CalendarList.size())
		{
			return;
		}
		const CalendarInfo& calendar = m_CalendarList[tag];
		if (m_CurYear == calendar.year
			&& m_CurMonth == calendar.month
			&& m_CurDay >= calendar.day
			&& calendar.isSigned == false)
		{
			if (!isCurrentWeek(calendar.day, m_CurDay, m_CurWeek))
			{
				CPEventHelper::uiNotify("EveryDaySalaryPanel", "", Error::Day_Sign_Only_Retroactive_This_Week);
				return;
			}
			MsgReSignDayRequest* res  = new MsgReSignDayRequest;
			res->day = calendar.day;
			HandleMessage::sendMessage(res);
		}
	}
}

int EveryDaySalaryPanel::getMaxDay(int month,int year)
{
	if (month<=0||month>12||year<=0)
	{
		return -1;
	}
	int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (!(year%4))
	{
		if (month==2)
		{
			return 29;
		}
	}
	return monthDays[month-1];
}

int EveryDaySalaryPanel::getDayIndex(int day,int week)
{
	if (day<=0||day>31||week<0||week>=7)
	{
		return -1;
	}
	int index = -1;
	for (int i = 0; i < m_Column; i++)
	{
		index = m_Row*i+week;
		if (index+1>=day) 
		{
			return index;
		}
	}
	return index;
}

int EveryDaySalaryPanel::getLastMonth(int month,int& year)
{
	if (month<=0||month>12||year<=0)
	{
		return -1;
	}
	month--;
	if (month<=0)
	{
		year--;
		month=12;
	}
	return month;
}

int EveryDaySalaryPanel::getNextMonth(int month,int& year)
{
	if (month<=0||month>12||year<=0)
	{
		return -1;
	}
	month++;
	if (month>12)
	{
		year++;
		month=1;
	}
	return month;
}

void EveryDaySalaryPanel::initCalendarData()
{
	time_t t = time(0); 
	char sYear[8]; 
	char sMonth[8]; 
	char sDay[8]; 
	char sWeek[8]; 
	strftime( sYear, sizeof(sYear), "%Y",localtime(&t) ); 
	strftime( sMonth, sizeof(sMonth), "%m",localtime(&t) ); 
	strftime( sDay, sizeof(sDay), "%d",localtime(&t) ); 
	strftime( sWeek, sizeof(sWeek), "%w",localtime(&t) ); 
	int year = atoi(sYear);
	int month = atoi(sMonth);
	int day = atoi(sDay);
	int week = atoi(sWeek);
	m_CurYear = year;
	m_CurMonth = month;
	m_CurDay = day;
	m_CurWeek = week;
	int index = getDayIndex(day,week);
	int curMaxday = getMaxDay(month,year);
	int lastYear = year;
	int lastMonth = getLastMonth(month,lastYear);
	int lastMaxday = getMaxDay(lastMonth,lastYear);
	int nextYear = year;
	int nextMonth = getNextMonth(month,nextYear);

	int signCount = 0;
	const int signDay = ActivityData::getExDataX(EvtData::evt_gfmrqd);
	for (int i = 0; i < m_Column; i++)
	{
		for (int j = 0; j < m_Row; j++)
		{
			int idx = m_Row*i+j;
			CalendarInfo calendar;
			calendar.row = i;
			calendar.column = j;
			
			calendar.isSigned = false;
			const int tDay = day-index+idx;
			if (tDay<=0)
			{
				calendar.month=lastMonth;
				calendar.year = lastYear;
				calendar.day = tDay+lastMaxday;
			}
			else if (tDay>curMaxday)
			{
				calendar.month=nextMonth;
				calendar.year = nextYear;
				calendar.day = tDay-curMaxday;
			}
			else
			{
				calendar.month=month;
				calendar.year = year;
				calendar.day = tDay;
				if(signDay & ((int) 1 <<calendar.day))
				{
					calendar.isSigned = true;
				}
			}
			m_CalendarList.push_back(calendar);

			if (calendar.isSigned)
			{
				signCount++;
			}
		}
	}

	setAddupSign(signCount);

	int patchCount = m_CurDay - signCount;
	if (patchCount < 0)
	{
		patchCount = 0;
	}
	setPatchSign(patchCount);
}
