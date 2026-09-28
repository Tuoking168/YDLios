#include "EveryDayActivePanel.h"
#include "EntityDefinition.h"
#include "MsgPlayer.h"
#include "GiftDefinition.h"
#include "EffectDefinition.h"
#include "EvtDataDefinition.h"
#include "ActivityModule.h"
#include "SceneDefinition.h"

#include "userdata/ActivityData.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/NPCFunctionData.h"
#include "event/EventProtocol.h"
#include "userdata/FuncData.h"

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

#include <time.h>
#include "utils/StringUtils.h"
#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "controls/CPItemComponents.h"
#include "ActivityDataHelper.h"

#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"

#include "module/ModuleData.h"
#include "userdata/LayoutData.h"
#include "res/CPAnimationManager.h"
#include "EveryDaySalaryPanel.h"

EveryDayActivePanel::EveryDayActivePanel()
	: m_updater(NULL)
	,m_hasSinged(NULL)
	,m_hasHappness(NULL)
	,m_LeftLayer(NULL)
	,m_Height(0)
	
	, m_indexSelected(0)
	, m_RewardMgr(NULL)
	, m_pHappiness(NULL)
	
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_CLOSE, this);
}

EveryDayActivePanel::~EveryDayActivePanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_CLOSE, this);
}

bool EveryDayActivePanel::init()//每日活跃ui
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
	
	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	m_RewardMgr = GeneralMenu::create();
	m_RewardMgr->setPosition(CCPointZero);
	m_RewardMgr->setAnchorPoint(CCPointZero);
	addChild(m_RewardMgr);

	initLabels();
	initButtons();

	initHappinessBar();
	loadHappiness();

	
	return true;
}

void EveryDayActivePanel::initFrame()
{
	CCSize bgSize = SystemData::getLayoutSize("everydayactive.frame.bigbg");
	CCPoint bgPoint = SystemData::getLayoutPoint("everydayactive.frame.bigbg");
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",bgSize.width,bgSize.height);
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(bgPoint);
	addChild(bg);

	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "everyDayActivityTitle");
	addChild(title);
	//整体分5个部分
	for (int i = 0; i < 5; i++)
	{ 
		CCSize size1 = SystemData::getLayoutSize("everydayactive.frame.bg"+StringUtils::toString(i));
		CCPoint point1 = SystemData::getLayoutPoint("everydayactive.frame.bg"+StringUtils::toString(i));
		CCScale9Sprite *frame1=SystemData::getScale9SpriteByPlist("guild.menuback",size1.width,size1.height); 
		frame1->setAnchorPoint(CCPointZero);  
		frame1->setPosition(point1); 
		addChild(frame1);
	}


	m_LeftLayer = CCLayer::create();
	m_LeftLayer->setAnchorPoint(CCPointZero);
	m_LeftLayer->setPosition(ccp(10,10));
	m_LeftLayer->setContentSize(SystemData::getLayoutSize("everydayactive.frame.bg1"));
	addChild(m_LeftLayer);


	m_pTableView=CCTableViewEx::create(this,SystemData::getLayoutSize("everydayactive.frame.bg4"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(355,10));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

void EveryDayActivePanel::initLabels()
{
	CCLabelTTF* willDoActive = SystemData::getLabelTTF("everydayactive.label.willdo");
	willDoActive->setFontSize(18);
	willDoActive->setColor(ccORANGE);
	willDoActive->setPosition(ccp(SystemData::getLayoutPoint("everydayactive.frame.bg0").x+SystemData::getLayoutSize("everydayactive.frame.bg0").width/2
		,SystemData::getLayoutPoint("everydayactive.frame.bg0").y+SystemData::getLayoutSize("everydayactive.frame.bg0").height/2));
	addChild(willDoActive);

	CCLabelTTF* m_LabelSigned= SystemData::getLabelTTF("everydayactive.label.signed");//您已签到
	m_LabelSigned->setColor(ccWHITE);
	m_LabelSigned->setFontSize(18);
	m_LabelSigned->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelSigned);

	int hassigneddays = 0;
	hassigneddays = getSignDays();
	m_hasSinged = CCLabelTTF::create(SystemData::intToString(hassigneddays).c_str(),"",20);
	m_hasSinged->setColor(ccGREEN);
	m_hasSinged->setPosition(ccp(m_LabelSigned->getPositionX()+32,m_LabelSigned->getPositionY()));
	addChild(m_hasSinged);

	CCLabelTTF* m_LabelActive = SystemData::getLabelTTF("everydayactive.label.active");//今天的活跃度已达到
	m_LabelActive->setColor(ccWHITE);
	m_LabelActive->setFontSize(18);
	m_LabelActive->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelActive);

	int happiness = ActivityData::getExDataX(EvtData::evt_gfmrhyd);
	m_hasHappness = CCLabelTTF::create(SystemData::intToString(happiness).c_str(),"",20);
	m_hasHappness->setColor(ccGREEN);
	m_hasHappness->setPosition(ccp(m_LabelActive->getPositionX()+100,m_LabelActive->getPositionY()));
	addChild(m_hasHappness);
	
}

void EveryDayActivePanel::initButtons()
{
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.button",80,35);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.button.sel",80,35);
	CCMenuItemSprite *button1 =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(EveryDayActivePanel::MenuCallBack));
	if(button1)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("everydayactive.button.signed.label");
		pLabel->setFontSize(16);
		pLabel->setColor(ccWHITE);
		button1->setTag(Button_Get);    
		button1->setPosition(SystemData::getLayoutPoint("everydayactive.button.signed"));
		pLabel->setPosition(button1->getPosition());
		m_pMainMenu->addChild(button1);
		m_pMainMenu->addChild(pLabel); 
	}
}

void EveryDayActivePanel::initHappinessBar()
{
	//background
	CCScale9Sprite* pBkg = SystemData::getScale9SpriteByPlist("everydayactive.sprite.happinessbkg");
	if(pBkg)
	{
		addChild(pBkg);
	}

	//dynamic line
	m_pHappiness = SystemData::getScale9SpriteByPlist("everydayactive.sprite.happinessbar");
	if(m_pHappiness) 
	{
		addChild(m_pHappiness);
	}

	//labels and cut lines
	for (int i=1; i<10; i++)
	{
		CCSprite* pCutline = SystemData::getSpriteByPlist("everydayactive.sprite.cutline1");
		if(pCutline)
		{
			pCutline->setPosition(ccp(361+42.5*i,320));
			addChild(pCutline); 
		}
	}
}

void EveryDayActivePanel::loadHappiness()
{
	int curValue = ActivityData::getExDataX(EvtData::evt_gfmrhyd);
	if (curValue>100)
	{
		curValue = 100;
	}
	const int maxValue = 100;
	static CCSize size = SystemData::getLayoutSize("everydayactive.sprite.happinessbkg");
	if(m_pHappiness)
	{ 
		if (curValue/maxValue<=1)
		{
			m_pHappiness->setContentSize(CCSizeMake(size.width*curValue/maxValue,size.height));  
		}
	} 
}

void EveryDayActivePanel::MenuCallBack(CCObject* pSender)
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case Button_Get:
			{
				time_t t = time(0); 
				char sDay[8]; 
				strftime( sDay, sizeof(sDay), "%d",localtime(&t) ); 
				int day = atoi(sDay);
				
				int days = getSignDays();
				if (!ActivityData::getExDataX(EvtData::evt_mrmrqd))
				{
					MsgReSignDayRequest* res  = new MsgReSignDayRequest;
					res->day = day;
					HandleMessage::sendMessage(res);
					days += 1;
					m_hasSinged->setString(SystemData::intToString(days).c_str());
				}
				else
				{
					MsgReSignDayRequest* res  = new MsgReSignDayRequest;
					res->day = day;
					HandleMessage::sendMessage(res);
				}
				
			}
		default:
			break;
		}
	}
}
void EveryDayActivePanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	
	if (source=="HandleMessageSyncPlayerEventDataNotify")
	{	
		int data1 = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
		if ( data1 == EvtData::evt_gfmrhyd)
		{
			int happiness = ActivityData::getExDataX(EvtData::evt_gfmrhyd);
			m_hasHappness->setString(SystemData::intToString(happiness).c_str());
			refreshHappinessBar();
			if (m_pTableView)
			{
				CCPoint point = m_pTableView->getContentOffset();
				m_pTableView->reloadData();
				m_pTableView->setContentOffset(point);
			}
		}
	}
	if (eventName ==  CPEventName::UI_CLOSE)
	{
		if (source == "LeftPartBaseMenu::gotoNPC")
		{
			this->removeFromParent();
		}
	}
}

void EveryDayActivePanel::refreshHappinessBar()
{
	int curValue = ActivityData::getExDataX(EvtData::evt_gfmrhyd);
	int maxValue = 100;
	if (curValue > 100)
	{
		curValue = 100;
	}
	CCSize size = SystemData::getLayoutSize("everydayactive.sprite.happinessbkg");
	if(m_pHappiness)
	{ 
		if (curValue/maxValue<=1)
		{
			m_pHappiness->setContentSize(CCSizeMake(size.width*curValue/maxValue,size.height));  
		}
	}
}

cocos2d::CCSize EveryDayActivePanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("everyday_Reward_cell");
}

cocos2d::extension::CCTableViewCell* EveryDayActivePanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		CCString* pStr = CCString::createWithFormat(SystemData::getLayoutString("everyday_Reward_Number").c_str(),idx+1);
		CCLabelTTF* pTitle = SystemData::getLabelTTF(pStr->getCString());
		pTitle->setAnchorPoint(ccp(0,0.5f));
		pTitle->setColor(ccWHITE);
		pTitle->setFontSize(18);
		pTitle->setPosition(ccp(SystemData::getLayoutValue("Login_Reward_cell.w")-200,SystemData::getLayoutValue("everyday_Reward_cell.h")/2));
		pLayer->addChild(pTitle);

		int score = 0;
		int everydayhappiness = 0;
		LuaData::getProp("gdEventDailyReward",idx+1,"score",score);
		everydayhappiness = ActivityData::getExDataX(EvtData::evt_gfmrhyd);
		if (everydayhappiness < score)
		{
			pTitle->setVisible(true);
		}
		else
		{
			pTitle->setVisible(false);
		}
		int size = 0;
		LuaData::getProp_size("gdEventDailyReward",idx+1,"reward",size);
		for (int i = 0;i<size;i++)
		{
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("everyday_Reward_Item",SystemData::getLayoutValue("everyday_Reward_Item.w"),SystemData::getLayoutValue("everyday_Reward_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("everyday_Reward_Item").x+65*i,SystemData::getLayoutPoint("everyday_Reward_Item").y));
			pLayer->addChild(pItemborder);

			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdEventDailyReward",idx+1,"reward",i+1,"type",reqsid);
			LuaData::getProp("gdEventDailyReward",idx+1,"reward",i+1,"count",reqcnt); 
			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setTarget(this,menu_selector(EveryDayActivePanel::itemClickCallBack));
			pItem->setPosition(pItemborder->getPosition());
			pMenu->addChild(pItem);
		}
		int isLingQu = 0;
		isLingQu = ActivityData::getExDataY(EvtData::evt_gfmrhyd);
		if (everydayhappiness >= score && !(isLingQu>>idx)&1)
		{
			CCMenuItemImage* pButton = SystemData::getMenuItemImageByPlist("Login_Reward_Button");
			pButton->setTarget(this,menu_selector(EveryDayActivePanel::getReward));
			pButton->setTag(idx+1);
			pButton->setPosition(ccp(SystemData::getLayoutPoint("Login_Reward_Item").x+70*5,SystemData::getLayoutPoint("Login_Reward_Item").y));
			pMenu->addChild(pButton);
			CCLabelTTF* pButtonLabel = SystemData::getLabelTTF("Login_Reward_LQ");
			pButtonLabel->setFontSize(20);
			pButtonLabel->setColor(ccWHITE);
			pButtonLabel->setPosition(ccp(pButton->getContentSize().width/2,pButton->getContentSize().height/2));
			pButton->addChild(pButtonLabel);
		}
		if((isLingQu>>idx)&1)
		{
			CCSprite* pFlag = SystemData::getSpriteByPlist("Login_Reward_hasget");
			pFlag->setPosition(ccp(SystemData::getLayoutPoint("Login_Reward_Item").x+70*5,SystemData::getLayoutPoint("Login_Reward_Item").y));
			pLayer->addChild(pFlag);
		}
	}
	return cell;
}

unsigned int EveryDayActivePanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutValue("everydayactive_size");
}

void EveryDayActivePanel::itemClickCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void EveryDayActivePanel::getReward( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::sendFuncMsgWithID(14,tag,1,0);
	}
}

void EveryDayActivePanel::onEnter()
{
	CCLayer::onEnter();
	updateLeft();
}

void EveryDayActivePanel::updateLeft()
{
	m_LeftLayer->removeAllChildren();
	CCLayer* layer=NULL;
	
	layer=EveryDayActivePanelLeftPart::create();
	
	if (layer)
	{
		m_Height=layer->getContentSize().height;
		layer->setAnchorPoint(CCPointZero);
		m_LeftLayer->addChild(layer);
	}
}

int EveryDayActivePanel::getSignDays()
{
	int signCount = 0;
	int signDay = ActivityData::getExDataX(EvtData::evt_gfmrqd);
	for (int i=0;i<31;i++)
	{
		if ((signDay&(1<<i)) > 0)
		{
			signCount++;
		}
	}
	return signCount;
}



//----------------------------------------------------------------------------------------------------------------------------


EveryDayActivePanelLeftPart::EveryDayActivePanelLeftPart():
	m_pTopMenu(NULL),
	m_pTabelView(NULL),
	m_pLeftLayer(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

EveryDayActivePanelLeftPart::~EveryDayActivePanelLeftPart()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool EveryDayActivePanelLeftPart::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	m_pTopMenu = GeneralMenu::create();
	if (m_pTopMenu)
	{
		m_pTopMenu->setAnchorPoint(CCPointZero);
		m_pTopMenu->setPosition(CCPointZero);
		addChild(m_pTopMenu);
	}
	else
		return false;

	m_pLeftLayer = CCLayer::create();
	m_pLeftLayer->setAnchorPoint(CCPointZero);
	m_pLeftLayer->setPosition(CCPointZero);

	m_pTabelView=CCTableViewEx::create(this,CCSizeMake(335, 378),kCCScrollViewDirectionVertical,this,NULL);
	m_pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTabelView->setAnchorPoint(CCPointZero);
	m_pTabelView->setPosition(CCPointZero);
	m_pTabelView->reloadData();  
	m_pTopMenu->addChild(m_pTabelView);

	updateView();
	return true;
}

cocos2d::CCSize EveryDayActivePanelLeftPart::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutSize("everydayactive_frame_left").width,m_Height);
}

cocos2d::extension::CCTableViewCell* EveryDayActivePanelLeftPart::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
	}
	return cell;
}

unsigned int EveryDayActivePanelLeftPart::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void EveryDayActivePanelLeftPart::updateView()
{
	m_pTabelView->removeAllChildren();
	CCLayer* layer=NULL;
	layer=LeftPartBaseMenu::create();

	if (layer)
	{
		m_Height=layer->getContentSize().height;
		layer->setAnchorPoint(CCPointZero);
		m_pTabelView->setContainer(layer);
	}
	m_pTabelView->reloadData();
}

void EveryDayActivePanelLeftPart::onCPEvent( const std::string &eventName )
{
	const std::string &evtSource = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (evtSource=="HandleMessageSyncPlayerEventDataNotify")
		{
			updateView();
		}
	}
}

void EveryDayActivePanelLeftPart::onEnter()
{
	CCLayer::onEnter();
	updateView();
}

//-------------------------------------------------------------------------------------------------------------------------------

LeftPartBaseMenu::LeftPartBaseMenu():
	m_iFirstHeight(0),
	m_iSecondHeight(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

LeftPartBaseMenu::~LeftPartBaseMenu()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool LeftPartBaseMenu::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	everydayActive_id_begin = SystemData::getLayoutValue("everydayActive_id_Begin");
	everydayActive_id_end = SystemData::getLayoutValue("everydayActive_id_End");
	initSecondPart();
	initFirstPart();

	this->setContentSize(CCSizeMake(SystemData::getLayoutSize("everydayactive.frame.bg1").width,m_iFirstHeight + m_iSecondHeight ));

	return true;
}

void LeftPartBaseMenu::initFirstPart()
{
	CCPoint pos = CCPointZero;
	m_iFirstHeight = 0;
	if (getChildByTag(1))
	{
		removeChildByTag(1);
	}
	CCLayer *pLayer=CCLayer::create();
	pLayer->setTag(1);
	pLayer->setContentSize(SystemData::getLayoutSize("everydayactive_frame_left"));

	GeneralMenu* menu = GeneralMenu::create(); 
	menu->setPosition(CCPointZero);
	menu->setAnchorPoint(CCPointZero);
	pLayer->addChild(menu);

	int size = SystemData::getLayoutValue("everydayActive_id_size");
	int count = 0;
	for (int i = everydayActive_id_begin;i < everydayActive_id_end+1 ;i++)
	{
		int id = 0;
		LuaData::getProp("gdEventData",i,"id",id);
		if (ActivityData::getExDataY(i) || id==0)
		{
			continue;
		}
		CCLabelTTF* l = CCLabelTTF::create();
		l->setAnchorPoint(CCPointZero);
		l->setPosition(ccp(15,-40-57*count));
		menu->addChild(l);
		int needGold = 0;
		LuaData::getProp("gdEventData",i,"goldenable",needGold);
		if (needGold)
		{
			CCMenuItemImage* miao = SystemData::getMenuItemImageByPlist("everydayactive.cell.button.miao");
			miao->setTag(i);
			miao->setTarget(this,menu_selector(LeftPartBaseMenu::miaoDoActivite));
			miao->setAnchorPoint(CCPointZero);
			miao->setPosition(ccp(15,-40-57*count));
			menu->addChild(miao);
		}
		else
		{

		}

		std::string name="";
		LuaData::getProp("gdEventData",i,"name",name);
		CCLabelTTF* activeName = CCLabelTTF::create(name.c_str(),"",18);
		activeName->setAnchorPoint(CCPointZero);
		activeName->setPosition(ccp(l->getPositionX()+50,l->getPositionY()+15));
		menu->addChild(activeName);

		int totalTimes = 0;
		LuaData::getProp("gdEventData",i,"times",totalTimes);
		CCString* doneTimes = CCString::createWithFormat("%d/%d",ActivityData::getExDataX(i),totalTimes);
		CCLabelTTF* doneTimesLabel = CCLabelTTF::create(doneTimes->getCString(),"",18);
		doneTimesLabel->setColor(ccGREEN);
		doneTimesLabel->setAnchorPoint(CCPointZero);
		doneTimesLabel->setPosition(ccp(activeName->getPositionX()+100,activeName->getPositionY()));
		menu->addChild(doneTimesLabel);

		int goalNpc = 0;
		LuaData::getProp("gdEventData",i,"npc",goalNpc);
		if (goalNpc)
		{
			CCMenuItemFont *pLabel1=CCMenuItemFont::create(SystemData::getLayoutString("help_btn_text1").c_str(),this,menu_selector(LeftPartBaseMenu::gotoNPC));
			//			pLabel1->setColor(ccYELLOW);
			pLabel1->setTag(goalNpc);
			pLabel1->setFontSizeObj(18);
			pLabel1->setAnchorPoint(CCPointZero);
			pLabel1->setPosition(ccp(doneTimesLabel->getPositionX()+50,doneTimesLabel->getPositionY()));
			menu->addChild(pLabel1);

			CCMenuItemImage *pShoes=SystemData::getMenuItemImageByPlist("tasktips_shoes");	
			pShoes->setTag(goalNpc);
			pShoes->setAnchorPoint(CCPointZero);
			pShoes->setScale(0.6f);
			pShoes->setPosition(ccp(pLabel1->getPositionX()+78,pLabel1->getPositionY()));
			pShoes->setTarget(this,menu_selector(LeftPartBaseMenu::useShoes));
			menu->addChild(pShoes);
		}

		if (true)
		{
			if (activeName->getPositionY()<pos.y)
			{
				pos = activeName->getPosition();
			}
		}
		count++;
	}

	m_iFirstHeight = -pos.y;
	m_iFirstHeight += 20;
	pLayer->setAnchorPoint(ccp(0,0));
	pLayer->setPosition(ccp(0,m_iFirstHeight+m_iSecondHeight));
	this->addChild(pLayer);
}

void LeftPartBaseMenu::initSecondPart()
{
	CCPoint pos = CCPointZero;
	m_iSecondHeight = 0;
	if (getChildByTag(2))
	{
		removeChildByTag(2);
	}
	CCLayer *pLayer=CCLayer::create();
	pLayer->setContentSize(SystemData::getLayoutSize("everydayactive.frame.bg1"));
	pLayer->setTag(2);

	int count = 0;
	if (true)
	{
		CCSprite* fengetiao = SystemData::getSpriteByPlist("everyday_activity_getiao");

		fengetiao->setPosition(ccp(pLayer->getContentSize().width/2,pos.y));
		pLayer->addChild(fengetiao);
		CCLabelTTF* doneActive = SystemData::getLabelTTF("everydayactive.label.done");
		doneActive->setColor(ccORANGE);
		doneActive->setFontSize(18);
		doneActive->setPosition(ccp(fengetiao->getPositionX(),fengetiao->getPositionY()-20));
		pLayer->addChild(doneActive);

		for (int i = everydayActive_id_begin;i < everydayActive_id_end + 1 ;i++)
		{
			if (ActivityData::getExDataY(i))
			{
				std::string activeName = "";
				int active = 0;
				LuaData::getProp("gdEventData",i,"name",activeName);
				LuaData::getProp("gdEventData",i,"active",active);
				CCLabelTTF* doneActiveName = CCLabelTTF::create(activeName.c_str(),"",18);
				doneActiveName->setPosition(ccp(doneActive->getPositionX()-100,doneActive->getPositionY()-30*(count+1)));
				pLayer->addChild(doneActiveName);

				CCLabelTTF* doneActiveActive = CCLabelTTF::create(SystemData::intToString(active).c_str(),"",18);
				doneActiveActive->setPosition(ccp(doneActiveName->getPositionX()+200,doneActiveName->getPositionY()));
				pLayer->addChild(doneActiveActive);

				if (doneActiveName->getPositionY()<pos.y)
				{
					pos = doneActiveName->getPosition();
				}
			}
			else
			{
				continue;
			}
			count++;
		}
		
	}
	m_iSecondHeight -= pos.y;
	m_iSecondHeight += 20;
	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setPosition(ccp(0, m_iSecondHeight));
	this->addChild(pLayer);
}

void LeftPartBaseMenu::gotoNPC( CCObject* pSender )
{
	CCNode * pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int goalID = pNode->getTag();
		GameData::s_user->m_pGhostManager->gotoGhostPos(goalID,"npcs");
		CPEventHelper::dispatcher(CPEventName::UI_CLOSE, "LeftPartBaseMenu::gotoNPC", "");
	}
}

void LeftPartBaseMenu::useShoes( CCObject* pSender )
{
	CCNode * pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int goalID = pNode->getTag();
		NPCFunctionData::useShoes(goalID,Scene::seNpc);
		CPEventHelper::dispatcher(CPEventName::UI_CLOSE, "LeftPartBaseMenu::gotoNPC", "");
	}
}

void LeftPartBaseMenu::miaoDoActivite( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::sendFuncMsgWithID(14,tag,0,0);
	}
}

void LeftPartBaseMenu::onCPEvent(const std::string &eventName)
{
	const std::string &evtSource = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (evtSource == "HandleMessageSyncPlayerEventDataNotify")
		{
			initSecondPart();
			initFirstPart();
		}
	}
}



