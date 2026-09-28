#include "TreasureHuntPanel.h"
#include "MsgActivity.h"
#include "ActivityDefinition.h"
#include "ActivityModule.h"
#include "ModuleData.h"
#include "MainPanel.h"
#include "EffectDefinition.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/UserItemData.h"
#include "userdata/SystemData.h"
#include "userdata/HeroData.h"
#include "userdata/ActivityData.h"
#include "userdata/LayoutData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/activitydata/TreasureHuntData.h"

#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/EffectSprite.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "functionPanel/CommonPanel.h"

#include "event/EventProtocol.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "ext/GeneralMenu.h"

#include "controls/CPNodeHelper.h"
#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"
#include "controls/CPRichText.h"

#include "res/CPAnimationManager.h"

#include "network/HandleMessage.h"

#include "utils/StringUtils.h"
#include "utils/RichTextUtils.h"

#include "script/LuaWrapper.h"
#include "scene/panel/guide/GuideHelper.h"


TreasureHuntPanel::TreasureHuntPanel()
	: m_pGold(NULL)
	, m_pDepotCapacity(NULL)
	, m_pHappiness(NULL)
	,mMyRecordList(NULL)
	,mAllRecordList(NULL)
	, m_pTreasureListMenu(NULL)
	, m_updater(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

TreasureHuntPanel::~TreasureHuntPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool TreasureHuntPanel::init()//寻宝ui
{
	if (!FullScreenPanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	if(!GuideHelper::canOpenFunction(FunctionName::XUN_BAO))
	{
		return false;
	}

	buildTitles();
	buildBorders();
	buildGrids();
	buildSprites();
	buildLabels();
	buildHuntButtons();
	buildHuntHistory();
	buildHappinessIndex();

	updateGold();
	updateHappiness();
	updateCapacityOfDepot();
	updateMyHuntHistory();
	updateAllHuntHistory();
	showTreasures();

	return true;
}

void TreasureHuntPanel::huntCallback( CCObject* pSender )
{
    CCNode* pNode = dynamic_cast<CCNode*>(pSender);
    if(pNode)
    {
        int tag = pNode->getTag();
        
        // 仓库按钮直接处理，不检查冷却
        if (tag == TAG_TREASURE_DEPOT)
        {
            openDepot();
            return;
        }
        
        // 简单冷却检查（只针对寻宝按钮）
        static time_t lastClickTime = 0;
        time_t now = time(NULL);
        
        if (now - lastClickTime < 5) 
        {
            // 按钮变红色效果
            CCMenuItemImage* btn = (CCMenuItemImage*)pNode;
            
            // 设置按钮为红色
            btn->setColor(ccc3(255, 0, 0));  // RGB红色
            
            // 3.0秒后恢复原色
            CCDelayTime* delay = CCDelayTime::create(3.0f);
            
            // 正确的方法
            btn->runAction(CCSequence::create(delay, 
                CCCallFuncO::create(this, callfuncO_selector(TreasureHuntPanel::recoverButtonColor), btn), 
                NULL));
            
            return;
        }
        lastClickTime = now;
        
        switch (tag)
        {
        case TAG_TREASURE_HUNT_1:
            huntTreasure(Activity::TH_one);
            break;
        case TAG_TREASURE_HUNT_10:
            huntTreasure(Activity::TH_ten);
            break;
        case TAG_TREASURE_HUNT_50:
            huntTreasure(Activity::TH_fifty);
            break;
        default:
            break;
        }
    }
}

// 恢复按钮颜色的函数
void TreasureHuntPanel::recoverButtonColor(CCObject* pBtn)
{
    CCMenuItemImage* btn = (CCMenuItemImage*)pBtn;
    if(btn)
    {
        btn->setColor(ccc3(255, 255, 255));  // 恢复白色
    }
}

void TreasureHuntPanel::buildGrids()
{
	// there are total 21 grid
	//first add all the backgrounds of these positions
	static CCPoint beginPos = SystemData::getLayoutPoint("treasurehunt.gridbegin");
	static CCSize span = SystemData::getLayoutSize("treasurehunt.gridspan"); 
	for(int h=0;h<3;h++)
	{
		for (int w=0;w<7;w++)
		{
			CCSprite* pBkg = SystemData::getSpriteByPlist("activity.sprite.item.frame");
			pBkg->setAnchorPoint(ccp(0,0));
			pBkg->setPosition(ccpAdd(beginPos,ccp(w*span.width,-h*span.height)));
			addChild(pBkg);
		}
	}
}

void TreasureHuntPanel::showTreasures() 
{
	if (!m_pTreasureListMenu)
	{
		m_pTreasureListMenu = GeneralMenu::create();
		m_pTreasureListMenu->setPosition(CCPointZero);
		addChild(m_pTreasureListMenu);
	}
	else
	{
		m_pTreasureListMenu->removeAllChildren();
	}

	int itemNum = TreasureHuntData::_s_treasure_hunt_list.size();
	if (m_updater)
	{
		m_updater->removeFromParentAndCleanup(true);
		m_updater = NULL;
	}
	m_updater = CPUpdater::create(this, cpupdater_selector(TreasureHuntPanel::addListItem));
	m_updater->setUpdateTimes(itemNum);
	m_updater->setFinishHandler(this, callfunc_selector(TreasureHuntPanel::addListFinish));
	addChild(m_updater);
	m_updater->start();
}

void TreasureHuntPanel::addListItem(int i )
{
	const CCPoint beginPos = SystemData::getLayoutPoint("treasurehunt.gridbegin");
	const CCSize span = SystemData::getLayoutSize("treasurehunt.gridspan");
	const int c = 7;
	int h = i/c;
	int w = i%c;
	int sid = TreasureHuntData::_s_treasure_hunt_list[i].itemsid;
	CCMenuItemImage* pItem = CCMenuItemImage::create();
	pItem->setNormalImage(LayoutData::getItemIcon(sid));
	pItem->setSelectedImage(LayoutData::getItemIcon(sid));
	pItem->setTag(sid);
	pItem->setAnchorPoint(CCPointZero);
	pItem->setTarget(this,menu_selector(TreasureHuntPanel::itemClickCallback));
	pItem->setPosition(ccpAdd(beginPos,ccp(w*span.width+3,-h*span.height+3)));
	m_pTreasureListMenu->addChild(pItem);
	
	CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
	pSprite->setAnchorPoint(CCPointZero);
	pSprite->setPosition(ccpAdd(ccp(beginPos.x-7,beginPos.y-7),ccp(w*span.width,-h*span.height)));
	m_pTreasureListMenu->addChild(pSprite);
}

void TreasureHuntPanel::addListFinish()
{
	//
}

void TreasureHuntPanel::updateGold()
{
	std::string strGoldNum = SystemData::getLayoutString("treasurehunt.lblgold");
	strGoldNum += SystemData::intToString(HeroData::getProp(Entity::attr_gold));
	if(!m_pGold)	
	{
		m_pGold = SystemData::getLabelTTF("treasurehunt.lblgold");
		if(m_pGold)
		{
			addChild(m_pGold);
		}
	}
	if(m_pGold)
	{
		m_pGold->setString(strGoldNum.c_str());
	}
}

void TreasureHuntPanel::updateCapacityOfDepot()
{
	std::string strDepotCapacity = SystemData::getLayoutString("treasurehunt.lblcapacity");
	///TODO: here should be replace with real data in the future
	strDepotCapacity += SystemData::intToString(GameData::s_user->getUserItemData()->treasureDepotCapacity);
	strDepotCapacity += "/";
	strDepotCapacity += SystemData::intToString(GameData::s_user->getUserItemData()->treasureDepotCapacityMax);
	if(!m_pDepotCapacity)	
	{
		m_pDepotCapacity = SystemData::getLabelTTF("treasurehunt.lblcapacity"); 
		if(m_pDepotCapacity)
		{
			addChild(m_pDepotCapacity); 
		}
	}
	if(m_pDepotCapacity)
	{
		m_pDepotCapacity->setString(strDepotCapacity.c_str());
	}
}

void TreasureHuntPanel::rechageCallback( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		//
	}
}

void TreasureHuntPanel::openDepot()
{
	CPEventHelper::openPanel("MainPanel",TAG_Role_Panel,AVATAR,WAREHOUSE,0);
}

void TreasureHuntPanel::handleEvent( int channel )
{
	if (channel == EventProtocol::EVENT_UPDATE_TREASURE_LIST)
	{
		showTreasures(); 
		updateCapacityOfDepot();
	}
	else if(channel == EventProtocol::EVENT_UPDATE_HAPPINESS)
	{
		updateHappiness();
	}
	else if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		updateCapacityOfDepot();
	}
}

void TreasureHuntPanel::buildBorders()
{
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",SystemData::getLayoutValue("treasurehunt.border.bigbg.w"),SystemData::getLayoutValue("treasurehunt.border.bigbg.h"));
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(SystemData::getLayoutPoint("treasurehunt.border.bigbg"));
	addChild(bg); 

	std::string keyList[5] = {"main","leftbottom","topright","rightmid","bottomright"};
	for (int i=0; i<5; i++)
	{
		std::string key = "treasurehunt.border."+keyList[i];
		CCSize pSize = SystemData::getLayoutSize(key);
		CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("guild.menuback",pSize.width,pSize.height);
		pBorder->setPosition(SystemData::getLayoutPoint(key));
		pBorder->setAnchorPoint(CCPointZero);  
		addChild(pBorder);
	}
}

void TreasureHuntPanel::buildLabels()
{
	std::string lblKey[10] = {"lbl0", "lbl1","lbl2","lbl3","lblcost1","lblcost10","lblcost50","personallog","serverlog","depotcapacity"};
	for (int i=0;i<10;i++)
	{
		std::string key = "treasurehunt."+lblKey[i];
		CCLabelTTF* pLabel = SystemData::getLabelTTF(key); 
		addChild(pLabel);
	}
}

void TreasureHuntPanel::buildHuntButtons()
{
	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	std::string keyList[3] = {"1","10","50"};//{"1","10","50"};
	for (int i = 0; i < 3; i++)
	{
		//button
		std::string btnKey = "treasurehunt.btn.hunt"+keyList[i];
		CCMenuItemImage* pBtn = SystemData::getScale9MenuItemImageByPlist(btnKey);
		if(pBtn)
		{
			pBtn->setTag(i);
			pBtn->setTarget(this,menu_selector(TreasureHuntPanel::huntCallback));
			pMenu->addChild(pBtn);
		}
		else
		{
			continue;
		}

		//label
		std::string lblKey = "treasurehunt.lblsearch"+keyList[i];
		CCLabelTTF* pLabel = SystemData::getLabelTTF(lblKey); 
		if(pLabel)
		{
			pLabel->setPosition(ccp(pBtn->getContentSize().width/2,pBtn->getContentSize().height/2));  
			pBtn->addChild(pLabel); 
		}
	}
	//寻宝仓库按钮
	std::string btnKey = "treasurehunt.btn.depot";
	CCMenuItemImage* pBtn = SystemData::getScale9MenuItemImageByPlist(btnKey);
	if(pBtn)
	{
		pBtn->setTag(TAG_TREASURE_DEPOT);
		pBtn->setTarget(this, menu_selector(TreasureHuntPanel::huntCallback));
		pMenu->addChild(pBtn);
	}
	std::string lblKey = "treasurehunt.lbldepot";
	CCLabelTTF* pLabel = SystemData::getLabelTTF(lblKey); 
	if(pLabel)
	{
		pLabel->setPosition(ccp(pBtn->getContentSize().width/2,pBtn->getContentSize().height/2));
		pBtn->addChild(pLabel);
	}
}

void TreasureHuntPanel::buildSprites()
{
	CCSprite* pSprite = SystemData::getSpriteByPlist("treasurehunt.sprite.yuanbao");
	addChild(pSprite);
	std::string keyList[2] = {"strip1","strip2"};
	for (int i = 0; i < 2; i++)
	{
		std::string key = "treasurehunt.sprite."+keyList[i]; 
		CCScale9Sprite* pSprite = SystemData::getScale9SpriteByPlist(key,248,34);
		addChild(pSprite);
	}
}

void TreasureHuntPanel::buildHappinessIndex()
{
	//background
	CCScale9Sprite* pBkg = SystemData::getScale9SpriteByPlist("treasurehunt.sprite.happinessbkg");
	if(pBkg)
	{
		addChild(pBkg);
	}

	//dynamic line
	m_pHappiness = SystemData::getScale9SpriteByPlist("treasurehunt.sprite.happinessbar");
	if(m_pHappiness) 
	{
		addChild(m_pHappiness);
	}

	//labels and cut lines
	for (int i=1; i<=5; i++)
	{
		std::string strId = SystemData::intToString(i);
		std::string key = "treasurehunt.happinessvalue";
		key += strId;
		CCLabelTTF* pValue = SystemData::getLabelTTF(key);
		addChild(pValue);
		key = "treasurehunt.happinessgrade";
		key += strId;
		CCLabelTTF* pGrade = SystemData::getLabelTTF(key);
		addChild(pGrade);    

		key = "treasurehunt.sprite.cutline";
		key += strId;
		CCSprite* pCutline = SystemData::getSpriteByPlist(key);
		if(pCutline)
		{
			addChild(pCutline);
		}
	}

	CCLabelTTF* pHappiness = SystemData::getLabelTTF("treasurehunt.happiness");  
	addChild(pHappiness);  
}

void TreasureHuntPanel::updateHappiness()
{
	const CCSize &size = SystemData::getLayoutSize("treasurehunt.sprite.happinessbkg");
	if(m_pHappiness)
	{ 
		float scaleX = TreasureHuntData::_s_happiness_value/500.0f;
		if (scaleX > 1)
		{
			scaleX = 1;
		}
		m_pHappiness->setContentSize(CCSizeMake(size.width * scaleX, size.height));  
	} 
}

void TreasureHuntPanel::buildTitles()
{
	//add the other sprites
	std::string key = "treasurehunt.sprite.title";
	CCSprite* pSprite = SystemData::getSpriteByPlist(key);
	addChild(pSprite);
}

void TreasureHuntPanel::buildHuntHistory()
{
	const CCSize &recordSize = LayoutData::getSize(CPModuleName::ACTIVITY, "treasureRecordList");
	mMyRecordList = CPItemComponents::create(recordSize, new CPLayoutList);
	mMyRecordList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "treasureMyRecordList"));
	addChild(mMyRecordList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "treasureRecordListScroll");
	CPScrollbar *myScrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mMyRecordList->setScrollbar(myScrollBar);
	 
	//
	mAllRecordList = CPItemComponents::create(recordSize, new CPLayoutList);
	mAllRecordList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "treasureAllRecordList"));
	addChild(mAllRecordList);

	CPScrollbar *allScrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mAllRecordList->setScrollbar(allScrollBar);
}

void TreasureHuntPanel::updateMyHuntHistory()
{
	mMyRecordList->removeAllItems();
	const int fontSize = LayoutData::getInt(CPModuleName::ACTIVITY, "treasureRecordFontSize");
	const CCSize &recordSize = LayoutData::getSize(CPModuleName::ACTIVITY, "treasureRecordList");
	for (int i = 0; i < ActivityData::getTreasureRecordSize(true); i++)
	{
		CPRichText *text = RichTextUtils::getRichText(TreasureHuntHelper::getRecord(i, true), fontSize, recordSize.width, 0);
		mMyRecordList->addItem(text);
	}
}

void TreasureHuntPanel::updateAllHuntHistory()
{
	mAllRecordList->removeAllItems();
	const int fontSize = LayoutData::getInt(CPModuleName::ACTIVITY, "treasureRecordFontSize");
	const CCSize &recordSize = LayoutData::getSize(CPModuleName::ACTIVITY, "treasureRecordList");
	for (int i = 0; i < ActivityData::getTreasureRecordSize(false); i++)
	{
		CPRichText *text = RichTextUtils::getRichText(TreasureHuntHelper::getRecord(i, false), fontSize, recordSize.width, 0);
		mAllRecordList->addItem(text);
	}
}

void TreasureHuntPanel::huntTreasure( int type )
{
	MsgHuntTreasureRequest *req = new MsgHuntTreasureRequest;
	req->hunttype = type;
	HandleMessage::sendMessage(req);
}

void TreasureHuntPanel::itemClickCallback( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		// show tips
		CCPoint tipsPos = pNode->convertToWorldSpace(ccp(pNode->getContentSize().width,pNode->getContentSize().height-258));
		if(tipsPos.x+245>SystemData::size_x)
		{
			tipsPos.x -= 245+pNode->getContentSize().width;
		}
		m_clickedItem = *(CommonFunction::createNewItem(tag));
		if (m_clickedItem.category==ItemCate_Equip)
		{
			tipsPos.y=10;
		}
		Game::getGameUI()->showTipsPanel(&m_clickedItem,TAG_Tips,tipsPos);
	}
}

void TreasureHuntPanel::onEnterTransitionDidFinish()
{
	MsgListTreasureRequest* req = new MsgListTreasureRequest;
	HandleMessage::sendMessage(req);
}

void TreasureHuntPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if(source == "HandleMessageHuntTreasureResponse")
		{
			updateGold();
			updateCapacityOfDepot();
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageSyncTreasureHuntRecordNotify|All")
		{
			updateAllHuntHistory();
		}
		else if (source == "HandleMessageSyncTreasureHuntRecordNotify|My")
		{
			updateMyHuntHistory();
		}
	}
}

void TreasureHuntPanel::onEnter()
{
	FullScreenPanel::onEnter();
	EventDispatcher::sharedEventDispather()->addListener(this); 
	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}
void TreasureHuntPanel::onExit()
{
	EventDispatcher::sharedEventDispather()->removeListener(this);
	FullScreenPanel::onExit();
}

//////////TreasureHuntHelper//////////////////////////////////////////
std::string TreasureHuntHelper::getRecord(  int index, bool isMy )
{
	std::string name;
	int sid = 0, strong = 0, reborn = 0;
	ActivityData::getTreasureRecord(index, isMy, name, sid, strong, reborn);

	std::string ret;
	Lua::instance()->push_utf8(name);
	Lua::instance()->push(sid);
	Lua::instance()->push(strong);
	Lua::instance()->push(reborn);
	if (Lua::instance()->call("activity_get_treasure_record", 4, 1) &&
		Lua::instance()->pop_utf8(ret))
	{
		return ret;
	}
	CCLog(">>>Error: TreasureHuntHelper::getRecord, index = %d", index);
	return "";
}
