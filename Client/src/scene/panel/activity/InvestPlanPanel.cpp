#include "InvestPlanPanel.h"
#include "EntityDefinition.h"
#include "EffectDefinition.h"
#include "ActivityDataHelper.h"
#include "ModuleData.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/LayoutData.h"
#include "userdata/ActivityData.h"


#include "userdata/netdata/GameRole.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/NPCFunctionData.h"

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

#include "scene/panel/EffectSprite.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/SlideTable.h"
#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "controls/CPItemComponents.h"
#include "controls/CPRichText.h"

#include "utils/StringUtils.h"

#include "res/CPAnimationManager.h"

#define HOURS_PER_DAY 24
#define MINUTES_PER_HOUR 60
#define SECONDS_PER_MINUTE 60
#define SECONDS_PER_HOUR 3600

InvestPlanPanel::InvestPlanPanel()
	: m_updater(NULL)
	, m_pSlideItems(NULL)
	, m_PageInfo(NULL)
	,mTimeLabel(NULL)
{
	m_OptionsList.clear();
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
}

InvestPlanPanel::~InvestPlanPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
}

bool InvestPlanPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	initSprite();

	//Ö÷Òªmenu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	CCPoint beginPos = SystemData::getLayoutPoint("investplan.frame.table.begin");
	CCSize slideSize = SystemData::getLayoutSize("investplan.frame.table");
	CCSize spanSize = SystemData::getLayoutSize("investplan.frame.span");
	m_pSlideItems = SlideTable::create(beginPos.x,beginPos.y,slideSize.width,slideSize.height,1,3,spanSize.width,spanSize.height);
	m_pSlideItems->setPosition(SystemData::getLayoutPoint("investplan.frame.table"));
	addChild(m_pSlideItems);          
	m_pSlideItems->setPageFlagVisible(false);
	m_pSlideItems->setPageChangeTarget(this,menu_selector(InvestPlanPanel::pageChangeCallBack));
	 
	initLabels();
	initButtons();
	initItemPages();
	
	return true;
}

void InvestPlanPanel::initSprite()
{
	CCSprite* sprite1 = SystemData::getSpriteByPlist("investplan.sprite.lingfengxian");
	sprite1->setAnchorPoint(CCPointZero);
	addChild(sprite1); 
}

void InvestPlanPanel::refreshTimeLabel()
{
	const int remainTime = getRemainTime();
	const int day = remainTime/(SECONDS_PER_HOUR * HOURS_PER_DAY);
	const int hour = remainTime%(SECONDS_PER_HOUR * HOURS_PER_DAY)/SECONDS_PER_HOUR;
	const int min = remainTime%SECONDS_PER_HOUR/SECONDS_PER_MINUTE;
	const int sec = remainTime%SECONDS_PER_MINUTE;
	const std::string &str = SystemData::getLayoutString("investplan.label.time")
		+ StringUtils::toString(day) + LayoutData::getString(CPModuleName::COMMON, "day")
		+ StringUtils::toString(hour) + LayoutData::getString(CPModuleName::COMMON, "hour")
		+ StringUtils::toString(min) + LayoutData::getString(CPModuleName::COMMON, "minute")
		+ StringUtils::toString(sec) + LayoutData::getString(CPModuleName::COMMON, "second");
	mTimeLabel->setString(str.c_str());
}

void InvestPlanPanel::initLabels()
{
	CPRichText* pText=NPCFunctionData::getBigContent(SystemData::getLayoutValue("investplan.label.info.tag"),576,0); 
	pText->setAnchorPoint(ccp(0,1));
	pText->setPosition(SystemData::getLayoutPoint("investplan.label.info")); 
	addChild(pText);

	mTimeLabel = SystemData::getLabelTTF("investplan.label.time");
	mTimeLabel->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(mTimeLabel);

	m_PageInfo = SystemData::getLabelTTF("investplan.label.page");
	m_PageInfo->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(m_PageInfo);
}

void InvestPlanPanel::initButtons()
{
	CCMenuItemImage* button1 = SystemData::getMenuItemImageByPlist("investplan.button.up");
	button1->setAnchorPoint(CCPointZero);
	m_pMainMenu->addChild(button1);
	CCSprite* sprite1 = SystemData::getSpriteByPlist("investplan.button.up");
	sprite1->setFlipX(true);
	sprite1->setPosition(CCPointZero);
	sprite1->setAnchorPoint(CCPointZero);
	CCSprite* sprite2 = SystemData::getSpriteByPlist("investplan.button.up.sel");
	sprite2->setFlipX(true);
	sprite2->setPosition(CCPointZero);
	sprite2->setAnchorPoint(CCPointZero);
	button1->setNormalImage(sprite1);
	button1->setSelectedImage(sprite2);
	button1->setEnabled(false); 

	CCMenuItemImage* button2 = SystemData::getMenuItemImageByPlist("investplan.button.down");
	button2->setAnchorPoint(CCPointZero);
	m_pMainMenu->addChild(button2);
	button2->setEnabled(false); 

	CCMenuItemImage* button3 = SystemData::getMenuItemImageByPlist("investplan.button.open");
	button3->setTarget(this, menu_selector(InvestPlanPanel::onOpen));
	button3->setAnchorPoint(CCPointZero);
	m_pMainMenu->addChild(button3);
	if (false
		|| getRemainTime() <= 0)
	{
		button3->setVisible(false);
	}
}

void InvestPlanPanel::onOpen( CCObject *target )
{
	//
}

void InvestPlanPanel::onGet( CCObject *target )
{
	//
}

void InvestPlanPanel::showTooltip(CCMenuItem* pImage)
{
	// show tips
	CCPoint tipsPos = pImage->convertToWorldSpace(ccp(pImage->getContentSize().width,pImage->getContentSize().height-125));
	if(tipsPos.x+245>SystemData::size_x) 
	{
		tipsPos.x -= 245+pImage->getContentSize().width;
	}
	UserItem* userItem = (UserItem*)pImage->getUserData();
	if (userItem->category==ItemCate_Equip)
	{
		tipsPos.y=0;
	}
	if (tipsPos.y>200)
	{
		tipsPos.y=200;
	}
	Game::getGameUI()->showTipsPanel(userItem,TAG_Tips,tipsPos);
}

void InvestPlanPanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}

void InvestPlanPanel::addListItem(int i )
{
	CCNode* pItem = CCNode::create();
	m_pSlideItems->addElement(pItem);

	CCSprite *bg=SystemData::getSpriteByPlist("investplan.cell.frame.background");
	bg->setAnchorPoint(CCPointZero);
	pItem->addChild(bg);  

	for (int j=0;j<2;j++)
	{
		CCSprite* sprite = SystemData::getSpriteByPlist("activity.sprite.item.frame");
		CCPoint point = SystemData::getLayoutPoint("investplan.cell.sprite.reward"+StringUtils::toString(j));
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(point); 
		pItem->addChild(sprite); 
	}
	
	CCMenuEx* m_pMenu = CCMenuEx::create();
	m_pMenu->setPosition(CCPointZero);
	m_pMenu->setAnchorPoint(CCPointZero); 
	pItem->addChild(m_pMenu); 
	CCScale9Sprite* normNode=SystemData::getScale9SpriteByPlist("guild.info.placard.button",80,35);
	CCScale9Sprite* selNode=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",80,35);
	CCScale9Sprite* disNode = SystemData::getScale9SpriteByPlist("guild.info.placard.button.dis", 80, 35);
	CCMenuItemSprite *button = CCMenuItemSprite::create(normNode, selNode, disNode);
	if(button)
	{  
		button->setTarget(this, menu_selector(InvestPlanPanel::onGet));
		button->setPosition(SystemData::getLayoutPoint("investplan.cell.button.get"));
		m_pMenu->addChild(button);

		CCLabelTTF *pLabel=SystemData::getLabelTTF("investplan.cell.button.get.label"); 
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		pLabel->setPosition(LayoutData::getCenter(button->getContentSize())); 
		button->addChild(pLabel);
		if (false)
		{
			button->setEnabled(false);
		}
	}
	CPRichText* pRichText=CPRichText::create(170,20); 
	CCPoint labelPoint=SystemData::getLayoutPoint("investplan.cell.label.money");
	pRichText->setAnchorPoint(ccp(0.5,0.5));
	pRichText->setPosition(labelPoint); 
	pItem->addChild(pRichText);

	int rewardSid1 = ActivityDataHelper::getInvestPlanItemFir(i+1);
	int rewardCount1 = ActivityDataHelper::getInvestPlanItemCountFir(i+1);
	if (rewardSid1>0&&rewardCount1>0)
	{ 
		UserItem* item = CommonFunction::createNewItem(rewardSid1);
		item->count = rewardCount1;
		CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
		CCPoint point = SystemData::getLayoutPoint("investplan.cell.sprite.reward"+StringUtils::toString(0));
		pItem->setPosition(ccp(point.x+33,point.y+33));
		pItem->setTarget(this,menu_selector(InvestPlanPanel::itemCallBack));
		m_pMenu->addChild(pItem);

		CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
		pSprite->setPosition(LayoutData::getCenter(pItem->getContentSize()));
		pItem->addChild(pSprite);

		std::string goldSuffix = ActivityDataHelper::getInvestPlanItemNameFir(i+1);
		CPRichTextItemLabel* pText1=new CPRichTextItemLabel(goldSuffix,"",16,ccYELLOW);
		pRichText->addItem(pText1);
	} 
	int rewardSid2 = ActivityDataHelper::getInvestPlanItemSec(i+1);
	int rewardCount2 = ActivityDataHelper::getInvestPlanItemCountSec(i+1);
	if (rewardSid2>0&&rewardCount2>0)
	{ 
		UserItem* item = CommonFunction::createNewItem(rewardSid2);
		item->count = rewardCount2;
		CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
		CCPoint point = SystemData::getLayoutPoint("investplan.cell.sprite.reward"+StringUtils::toString(1));
		pItem->setPosition(ccp(point.x+33,point.y+33));
		pItem->setTarget(this,menu_selector(InvestPlanPanel::itemCallBack));
		m_pMenu->addChild(pItem);

		CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
		pSprite->setPosition(LayoutData::getCenter(pItem->getContentSize()));
		pItem->addChild(pSprite);

		std::string ticketSuffix = ActivityDataHelper::getInvestPlanItemNameSec(i+1);
		CPRichTextItemLabel* pText2=new CPRichTextItemLabel("+"+ticketSuffix,"",16,ccGREEN);
		pRichText->addItem(pText2);
	} 
}

void InvestPlanPanel::initItemPages()
{
	m_pSlideItems->clear();
	
	int itemNum = ActivityDataHelper::getInvestPlanSize();
	
	if (m_updater)
	{
		m_updater->removeFromParentAndCleanup(true);
		m_updater = NULL;
	}
	m_updater = CPUpdater::create(this, cpupdater_selector(InvestPlanPanel::addListItem));
	m_updater->setUpdateTimes(itemNum);
	addChild(m_updater);
	m_updater->start();
}
void InvestPlanPanel::pageChangeCallBack(CCObject* pSender)
{
	if (!m_pSlideItems||!m_PageInfo)
	{
		return;
	}
	int curPage = m_pSlideItems->getCurPage()+1;
	int totalPage = m_pSlideItems->getTotalPage();
	std::string pageStr = StringUtils::toString(curPage)+"/"+StringUtils::toString(totalPage);
	m_PageInfo->setString(pageStr.c_str());
}

int InvestPlanPanel::getRemainTime()
{
	const int totalTime = ActivityDataHelper::getDataX(Gift_InvestPlan, 1) * HOURS_PER_DAY * SECONDS_PER_HOUR;
	const int remainTime = totalTime - (ActivityData::getWorldTime() - ActivityData::getWorldBeginTime());
	if (remainTime > 0)
	{
		return remainTime;
	}
	return 0;
}

void InvestPlanPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			refreshTimeLabel();
		}
	}
}
