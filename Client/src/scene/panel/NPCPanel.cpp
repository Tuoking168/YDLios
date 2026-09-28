#include "NPCPanel.h"
#include "MsgScene.h"
#include "SceneDefinition.h"
#include "MainUIModule.h"
#include <algorithm>

#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/TaskData.h"
#include "userdata/StaticData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/netdata/Ghost.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/NPCFunctionData.h"

#include "network/HandleMessage.h"

#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"

#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "scene/panel/shop/NpcShopComp.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCActionDestroy.h"

#include "controls/CPRichText.h"
#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"
#include "controls/CPNodeHelper.h"
#include "controls/CPUpdater.h"
#include "utils/TestUtils.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/AutoAttack.h"
#include "event/CPEventDispatcher.h"
#include "scene/LoginHelper.h"

#include "logic/platform/IPlatform.h"

NPCTalkPanel::NPCTalkPanel():
	m_pNPCcontent(NULL),
	m_pbkgSprite(NULL),
	m_bisShowQuest(true),
	m_pTabelView(NULL),
	m_pRichText(NULL),
	m_pTalkBkg(NULL),
	mChecker(NULL),
	m_pTime(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

NPCTalkPanel::~NPCTalkPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

NPCTalkPanel* NPCTalkPanel::create()
{
	NPCTalkPanel* pPanel = new NPCTalkPanel();
	if(pPanel && pPanel->init())
	{
		pPanel->autorelease();
		return pPanel;
	}

	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

void NPCTalkPanel::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setScale(0.0f);
	setAnchorPoint(ccp(0.5,0.5));
	runAction(CCSequence::create(CCShow::create(),CPNodeHelper::getScaleToBig(),CCCallFunc::create(this,callfunc_selector(NPCTalkPanel::sendMsgToupdateInterface)),NULL));	
}

void NPCTalkPanel::onExit()
{
	PartPanel::onExit();
}

bool NPCTalkPanel::init()
{
	if (!PartPanel::init())
	{
		return false;
	}
	const int NPCID=GameData::s_user->m_nNpcTalkId;
	Ghost* targetGhost = GameData::s_user->m_pGhostManager->getGhostById(NPCID);
	if (targetGhost)
	{
		NPCFunctionData::setNPCID(targetGhost->mStaticID);
	}
	NPCFunctionData::setReadmeAndSub(false,false); 

	setAnchorPoint(ccp(0.5,0.5));
	//背景框
	CCSprite* bkgSprite = SystemData::getSpriteByPlist("npctalk.sprite.bkg");
	bkgSprite->setAnchorPoint(CCPointZero);
	bkgSprite->setPosition(SystemData::getLayoutPoint("NPCTalk_bkg_Pos"));
	addChild(bkgSprite);


	m_nWidth=bkgSprite->getContentSize().width;
	m_nHeight=bkgSprite->getContentSize().height;
	addCover(bkgSprite->getPosition());

	this->setContentSize(CCSizeMake(m_nWidth,m_nHeight));
	 
	//下部分bkg
	m_pbkgSprite = SystemData::getScale9SpriteByPlist("NPCTalk_talkbkg",SystemData::getLayoutValue("NPCTalk_talkbkg1.w"),SystemData::getLayoutValue("NPCTalk_talkbkg1.h"));
	m_pbkgSprite->setAnchorPoint(CCPointZero);
	m_pbkgSprite->setPosition(SystemData::getLayoutPoint("NPCTalk_talkbkg1_pos"));
	addChild(m_pbkgSprite);

	//NPC名字
	CCLabelTTF* pLabel=CCLabelTTF::create(NPCFunctionData::getNPCName().c_str(),"微软雅黑",20);
	pLabel->setColor(ccYELLOW);
	pLabel->setPosition(ccp(bkgSprite->getPositionX()+m_nWidth/2,bkgSprite->getPositionY()+m_nHeight-20));
	addChild(pLabel);	

	m_pNPCcontent=CCLayer::create();
	m_pNPCcontent->setAnchorPoint(CCPointZero);
	m_pNPCcontent->setPosition(CCPointZero);
	addChild(m_pNPCcontent);
	
	//initBaseInterface();	
	int height=75;
	m_pbkgSprite->setVisible(true);
	if (NPCFunctionData::getReadme())
	{
		height=250;
		m_pbkgSprite->setVisible(false); 
	}
	//NPC口头禅
	m_pTalkBkg=SystemData::getScale9SpriteByPlist("NPCTalk_talkbkg",SystemData::getLayoutValue("NPCTalk_talkbkg.w"),SystemData::getLayoutValue("NPCTalk_talkbkg.h")+height-75);
	m_pTalkBkg->setAnchorPoint(CCPointZero);
	m_pTalkBkg->setTag(111);
	m_pTalkBkg->setPosition(ccp(SystemData::getLayoutPoint("NPCTalk_talkbkg_pos").x,SystemData::getLayoutPoint("NPCTalk_talkbkg_pos").y-height+75));
	m_pNPCcontent->addChild(m_pTalkBkg,0);

	CPRichText* pRichText=CPRichText::create(m_nWidth-50,0);

	m_pTabelView=CCTableViewEx::create(this,CCSizeMake(520,height),kCCScrollViewDirectionVertical,this,NULL);
	m_pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTabelView->setAnchorPoint(CCPointZero);
	m_pTabelView->setPosition(ccp(m_pTalkBkg->getPositionX()+10,m_pTalkBkg->getPositionY()+5));
	m_pTabelView->setContainer(pRichText);
	m_pTabelView->reloadData();  
	m_pNPCcontent->addChild(m_pTabelView);
	m_pRichText=pRichText;

	m_pMainMenu=GeneralMenu::create();
	m_pMainMenu->setAnchorPoint(CCPointZero);
	m_pMainMenu->setPosition(CCPointZero);
	addChild(m_pMainMenu);

	//关闭按钮
	CCMenuItemImage *pclose=SystemData::getMenuItemImageByPlist("NPCTalk_close");
	pclose->setPosition(ccp(bkgSprite->getPositionX()+bkgSprite->getContentSize().width-25,bkgSprite->getPositionY()+bkgSprite->getContentSize().height-25));
	pclose->setTarget(this,menu_selector(NPCTalkPanel::close));
	m_pMainMenu->addChild(pclose);

	//
	if (targetGhost)
	{
		CPEventHelper::setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_1, targetGhost->mStaticID);
		CPEventHelper::dispatcher(CPEventName::UI_OPEN, "NPCTalkPanel", "");
	}
	AutoAttack::closeAutoAttack();

	return true;
}

cocos2d::CCSize NPCTalkPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(534,m_iTalkLabelHeight);
}

cocos2d::extension::CCTableViewCell* NPCTalkPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
	}
	return cell;
}

unsigned int NPCTalkPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void NPCTalkPanel::sendMsgToupdateInterface()
{
	NPCFunctionData::updatedynamicData(NPCFunctionData::getNPCID());

	int portalFlag = 0;
	StaticData::getPortalNPCFlag(NPCFunctionData::getNPCID(), portalFlag);
	if (portalFlag != 0)
	{
		addPortalStonePanel();
		return;
	}

	//发送请求npc功能和任务消息，等待回应
	MsgClickNPCRequest* req = new MsgClickNPCRequest;
	req->NPCid=NPCFunctionData::getNPCID();
	HandleMessage::sendMessage(req);

	//加载菊花
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
	mChecker->start();
}

void NPCTalkPanel::updateAll()
{	
	initTaskTitle();
}

void NPCTalkPanel::initBaseInterface()
{
	//清除菊花
	if (mChecker)
	{
		mChecker->stop();
	}

	int height=75;
	m_pbkgSprite->setVisible(true);
	if (NPCFunctionData::getReadme())
	{
		height=250;
		m_pbkgSprite->setVisible(false); 
	}
	m_pTalkBkg->setContentSize(CCSizeMake(SystemData::getLayoutValue("NPCTalk_talkbkg.w"),SystemData::getLayoutValue("NPCTalk_talkbkg.h")+height-75));
	m_pTalkBkg->setPosition(ccp(SystemData::getLayoutPoint("NPCTalk_talkbkg_pos").x,SystemData::getLayoutPoint("NPCTalk_talkbkg_pos").y-height+75));
	m_pTabelView->setPosition(ccp(m_pTalkBkg->getPositionX()+10,m_pTalkBkg->getPositionY()+5));
	m_pTabelView->setViewSize(CCSizeMake(520,height));
	if (m_pRichText)
	{
		if (m_pTime)
		{
			removeChild(m_pTime);
		}

		int contentsize=0;
		LuaData::getProp_size(LuaData::NPC,NPCFunctionData::getNPCID(),"text",contentsize);
		m_pTime=CPUpdater::create(this,cpupdater_selector(NPCTalkPanel::addNPCSubContent));
		m_pTime->setFinishHandler(this,callfunc_selector(NPCTalkPanel::addNPCSubContentFinish));
		m_pTime->setUpdateTimes(contentsize);
		addChild(m_pTime);
		m_pTime->start();
	}
}

void NPCTalkPanel::setShowQuest( bool flag )
{
	m_bisShowQuest=flag;
	updateAll();
}

void NPCTalkPanel::addPortalStonePanel()
{
	GameData::s_user->questlist.clear();
	GameData::s_user->functionlist.clear();
	updateAll();
	initBaseInterface();

#define PORTAL_STONE_PANEL 121
	if (getChildByTag(PORTAL_STONE_PANEL))
	{
		removeChildByTag(PORTAL_STONE_PANEL);
	}
	PortalStonePanel *panel = PortalStonePanel::create();
	addChild(panel, 0, PORTAL_STONE_PANEL);
}

void NPCTalkPanel::close( CCObject* pSender )
{
	this->removeFromParent();
}

void NPCTalkPanel::initAll()
{

}

void NPCTalkPanel::initTaskTitle()
{
	if (getChildByTag(0))
	{
		removeChildByTag(0);
	}
	NPCTaskTitle* pPanel=NPCTaskTitle::create(m_bisShowQuest);
	pPanel->setAnchorPoint(CCPointZero);
	pPanel->setPosition(SystemData::getLayoutPoint("NPCTalk_tasktitle_Pos"));
	pPanel->setTag(0);
	addChild(pPanel);

}

void NPCTalkPanel::addNPCSubContent( int id )
{
	if (id==0)
	{
		CPRichText* pRichText=CPRichText::create(m_nWidth-50,0);
		m_pTabelView->setContainer(pRichText);
		m_pRichText=pRichText;
	}

	int i=id+1;
	std::string newContent;
	std::string oldstr;
	std::string colorstr;
	LuaData::getProp(LuaData::NPC,NPCFunctionData::getNPCID(),"text",i,"color",colorstr);
	LuaData::getProp(LuaData::NPC,NPCFunctionData::getNPCID(),"text",i,"content",oldstr);
	if (!NPCFunctionData::getNPCcontentSub(NPCFunctionData::getNPCID(),oldstr,newContent)) 
	{
		return ;
	}
	ccColor3B color=ccWHITE;
	if (colorstr=="g")
	{
		color=ccGREEN;
	}
	else if (colorstr=="b")
	{
		color=ccBLUE;
	}
	else if (colorstr=="y")
	{
		color=ccYELLOW;
	}
	else if (colorstr=="o")
	{
		color=ccORANGE;
	}
	else if (colorstr=="w")
	{
		color=ccWHITE;
	}
	CPRichTextItemLabel* pText=new CPRichTextItemLabel(newContent,"",18,color);
	if (m_pRichText)
	{
		m_pRichText->addItem(pText);
		m_iTalkLabelHeight=m_pRichText->getContentSize().height;
		m_pTabelView->reloadData();
	}
}

void NPCTalkPanel::addNPCSubContentFinish()
{
	if (m_pRichText)
	{
		m_iTalkLabelHeight=m_pRichText->getContentSize().height;
		m_pTabelView->reloadData();
	}
}

void NPCTalkPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageClickNPCResponse")
		{
			updateAll();
			initBaseInterface();
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageMapSelfEnterNotify")
		{
			close(NULL);
		}
		
	}
}


//----------------------------------------------------------------------------------------------//


NPCTaskPanel::NPCTaskPanel():
	m_pMainMenu(NULL),
	mQuestID(0)
{

}

NPCTaskPanel::~NPCTaskPanel()
{

}

NPCTaskPanel* NPCTaskPanel::create( int qid )
{
	NPCTaskPanel* pPanel = new NPCTaskPanel();
	if(pPanel && pPanel->init(qid))
	{
		pPanel->autorelease();
		return pPanel;
	}

	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

//bool NPCTaskPanel::init( int qid )
//{
//	if (!CCLayer::init())
//	{
//		return false;
//	}
//	setTouchEnabled(true);
//	mQuestID = qid;
//	//背景框
//	CCSprite* bkgSprite = SystemData::getSpriteByPlist("npctalk.sprite.bkg");
//	bkgSprite->setAnchorPoint(CCPointZero);
//	bkgSprite->setPosition(SystemData::getLayoutPoint("NPCTalk_bkg_Pos"));
//	addChild(bkgSprite);
//
//	m_nWidth=bkgSprite->getContentSize().width;
//	m_nHeight=bkgSprite->getContentSize().height;
//	addCover(bkgSprite->getPosition());
//
//	this->setContentSize(CCSizeMake(m_nWidth,m_nHeight));
//
//	/*CCSprite* bkgSprite = SystemData::getSprite("npctalk.sprite.bkg");
//	bkgSprite->setAnchorPoint(CCPointZero);
//	bkgSprite->setPosition(SystemData::getLayoutPoint("NPCTalk_bkg_Pos"));
//	addChild(bkgSprite);
//
//	m_nWidth=bkgSprite->getContentSize().width;
//	m_nHeight=bkgSprite->getContentSize().height;
//
//	setContentSize(CCSizeMake(m_nWidth,m_nHeight));
//
//	addCover(bkgSprite->getPosition());*/
//
//	//下部分bkg
//	CCScale9Sprite* pbkgSprite1 = SystemData::getScale9SpriteByPlist("NPCTalk_talkbkg",SystemData::getLayoutValue("NPCTalk_talkbkg1.w"),SystemData::getLayoutValue("NPCTalk_talkbkg1.h"));
//	pbkgSprite1->setAnchorPoint(CCPointZero);
//	pbkgSprite1->setPosition(SystemData::getLayoutPoint("NPCTalk_talkbkg1_pos"));
//	addChild(pbkgSprite1);
//
//	//NPC名字
//	//LuaData::getProp(LuaData::NPC,NPCFunctionData::getNPCID(),"name",NPCFunctionData::getNPCName());
//	CCLabelTTF* pLabel=CCLabelTTF::create(NPCFunctionData::getNPCName().c_str(),"微软雅黑",20);
//	pLabel->setColor(ccYELLOW);
//	pLabel->setPosition(ccp(bkgSprite->getPositionX()+m_nWidth/2,bkgSprite->getPositionY()+m_nHeight-20));
//	addChild(pLabel);	
//
//
//	m_pMainMenu=GeneralMenu::create();
//	m_pMainMenu->setAnchorPoint(CCPointZero);
//	m_pMainMenu->setPosition(CCPointZero);
//	addChild(m_pMainMenu);
//
//	//关闭按钮
//	CCMenuItemImage *pclose=SystemData::getMenuItemImageByPlist("NPCTalk_close");
//	pclose->setPosition(ccp(bkgSprite->getPositionX()+bkgSprite->getContentSize().width-25,bkgSprite->getPositionY()+bkgSprite->getContentSize().height-25));
//	pclose->setTarget(this,menu_selector(NPCTaskPanel::CloseCallBack));
//	m_pMainMenu->addChild(pclose);
//	
//
//	//返回按钮
//	CCMenuItemImage *pback=SystemData::getMenuItemImageByPlist("NPCTalk_back");
//	pback->setPosition(SystemData::getLayoutPoint("NPCTalk_back_pos"));
//	pback->setTarget(this,menu_selector(NPCTaskPanel::BackCallBack));
//	pback->setScaleX(1.2f);
//	m_pMainMenu->addChild(pback);
//
//	CCLabelTTF* pfanhui=SystemData::getLabelTTF("NPCTalk_fanhui");
//	pfanhui->setColor(ccWHITE);
//	pfanhui->setFontSize(18);
//	pfanhui->setPosition(SystemData::getLayoutPoint("NPCTalk_back_pos"));
//	m_pMainMenu->addChild(pfanhui);
//
//	addTaskContent();
//	addTaskButton();
//
//	return true;
//}
bool NPCTaskPanel::init( int qid )//npc任务第2给界面ui
{
    if (!CCLayer::init())
    {
        return false;
    }
    setTouchEnabled(true);
    mQuestID = qid;
    
    // 创建容器
    CCNode* container = CCNode::create();
    container->setPosition(CCPointZero);
    container->setAnchorPoint(ccp(0.5f, 0.5f));
    this->addChild(container);

    //背景框
    CCSprite* bkgSprite = SystemData::getSpriteByPlist("npctalk.sprite.bkg");
    bkgSprite->setAnchorPoint(CCPointZero);
    bkgSprite->setPosition(SystemData::getLayoutPoint("NPCTalk_bkg_Pos"));
    container->addChild(bkgSprite);

    m_nWidth=bkgSprite->getContentSize().width;
    m_nHeight=bkgSprite->getContentSize().height;
    addCover(bkgSprite->getPosition());

    this->setContentSize(CCSizeMake(m_nWidth,m_nHeight));

    // 下部分bkg
    CCScale9Sprite* pbkgSprite1 = SystemData::getScale9SpriteByPlist("NPCTalk_talkbkg",SystemData::getLayoutValue("NPCTalk_talkbkg1.w"),SystemData::getLayoutValue("NPCTalk_talkbkg1.h"));
    pbkgSprite1->setAnchorPoint(CCPointZero);
    pbkgSprite1->setPosition(SystemData::getLayoutPoint("NPCTalk_talkbkg1_pos"));
    container->addChild(pbkgSprite1);

    // NPC名字
    CCLabelTTF* pLabel=CCLabelTTF::create(NPCFunctionData::getNPCName().c_str(),"微软雅黑",20);
    pLabel->setColor(ccYELLOW);
    pLabel->setPosition(ccp(bkgSprite->getPositionX()+m_nWidth/2,bkgSprite->getPositionY()+m_nHeight-20));
    container->addChild(pLabel);    

    m_pMainMenu=GeneralMenu::create();
    m_pMainMenu->setAnchorPoint(CCPointZero);
    m_pMainMenu->setPosition(CCPointZero);
    container->addChild(m_pMainMenu);

    // 关闭按钮
    CCMenuItemImage *pclose=SystemData::getMenuItemImageByPlist("NPCTalk_close");
    pclose->setPosition(ccp(bkgSprite->getPositionX()+bkgSprite->getContentSize().width-25,bkgSprite->getPositionY()+bkgSprite->getContentSize().height-25));
    pclose->setTarget(this,menu_selector(NPCTaskPanel::CloseCallBack));
    m_pMainMenu->addChild(pclose);
    

    // 返回按钮
    CCMenuItemImage *pback=SystemData::getMenuItemImageByPlist("NPCTalk_back");
    pback->setPosition(SystemData::getLayoutPoint("NPCTalk_back_pos"));
    pback->setTarget(this,menu_selector(NPCTaskPanel::BackCallBack));
    pback->setScaleX(1.2f);
    m_pMainMenu->addChild(pback);

    CCLabelTTF* pfanhui=SystemData::getLabelTTF("NPCTalk_fanhui");
    pfanhui->setColor(ccWHITE);
    pfanhui->setFontSize(18);
    pfanhui->setPosition(SystemData::getLayoutPoint("NPCTalk_back_pos"));
    m_pMainMenu->addChild(pfanhui);

    addTaskContent();
    addTaskButton();

    // 移动整个容器到指定位置
    container->setPosition(ccp(200, 60)); // 将容器移动到 (200, 60)

    return true;
}
//void NPCTaskPanel::addTaskContent()
//{
//	//任务内容
//	CCScale9Sprite *pTalkBkg=SystemData::getScale9SpriteByPlist("NPCTalk_talkbkg",SystemData::getLayoutValue("NPCTalk_talkbkg.w"),SystemData::getLayoutValue("NPCTalk_talkbkg.h"));
//	pTalkBkg->setAnchorPoint(CCPointZero);
//	pTalkBkg->setPosition(SystemData::getLayoutPoint("NPCTalk_talkbkg_pos"));
//	addChild(pTalkBkg);
//
//	std::string TaskContent;
//	const int state = TaskData::getTaskState(mQuestID);
//	if (state==Quest::state_Available)
//	{
//		LuaData::getProp(LuaData::QUEST,mQuestID,"text_src",TaskContent);
//	}
//	else if (state==Quest::state_NotFinished)
//	{
//		LuaData::getProp(LuaData::QUEST,mQuestID,"des",TaskContent);
//	}
//	else if (state==Quest::state_Finished)
//	{
//		LuaData::getProp(LuaData::QUEST,mQuestID,"text_tgt",TaskContent);
//	}
//	else
//	{
//		LuaData::getProp(LuaData::QUEST,mQuestID,"des",TaskContent);
//	}
//
//
//	//任务名称
//	CCNode* pNode=CCNode::create();
//	pNode->setAnchorPoint(CCPointZero);
//
//	
//	CCLabelTTF* pLabelcontent=CCLabelTTF::create(TaskContent.c_str(),"微软雅黑",15);
//	pLabelcontent->setDimensions(CCSizeMake(m_nWidth-50,0));
//	pLabelcontent->setHorizontalAlignment(kCCTextAlignmentLeft);
//	pLabelcontent->setPosition(ccp(0,pLabelcontent->getContentSize().height));
//	pLabelcontent->setAnchorPoint(ccp(0,1));
//
//	std::string TaskName; 
//	LuaData::getProp(LuaData::QUEST,mQuestID,"name",TaskName);
//	CCLabelTTF* pLabelname=CCLabelTTF::create(TaskName.c_str(),"微软雅黑",20);
//	pLabelname->setAnchorPoint(CCPointZero); 
//	pLabelname->setPosition(pLabelcontent->getPosition());
//
//	m_iTalkLabelHeight=pLabelname->getContentSize().height+pLabelcontent->getContentSize().height;
//	pNode->setContentSize(CCSizeMake(pLabelcontent->getContentSize().width,m_iTalkLabelHeight));
//	pNode->addChild(pLabelcontent);
//	pNode->addChild(pLabelname);
//	
//
//	CCTableViewEx *pTabelView=CCTableViewEx::create(this,CCSizeMake(520,75),kCCScrollViewDirectionVertical,this,pNode);
//	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
//	pTabelView->setAnchorPoint(CCPointZero);
//	pTabelView->setPosition(ccp(SystemData::getLayoutPoint("NPCTalk_talkbkg_pos").x+10,SystemData::getLayoutPoint("NPCTalk_talkbkg_pos").y+7));
//	pTabelView->reloadData();  
//	addChild(pTabelView);
//	
//	//任务目标
//	CCSprite* ptitle_rwmb=SystemData::getSpriteByPlist("NPCTalk_rwmb");
//	ptitle_rwmb->setAnchorPoint(ccp(0,0.5));
//	ptitle_rwmb->setPosition(SystemData::getLayoutPoint("NPCTalk_rwmb_pos"));
//	addChild(ptitle_rwmb);
//	 
//	CCString *pStr=NPCFunctionData::getCString(mQuestID,12);
//	CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"微软雅黑",15);
//	pLabel->setAnchorPoint(ccp(0,1));
//	pLabel->setPosition(ccp(ptitle_rwmb->getPositionX(),ptitle_rwmb->getPositionY()-20));
//	addChild(pLabel); 
//
//	//任务奖励 
//	CCSprite* ptitle_rwjl=SystemData::getSpriteByPlist("NPCTalk_rwjl");
//	ptitle_rwjl->setAnchorPoint(ccp(0,0.5));
//	ptitle_rwjl->setPosition(SystemData::getLayoutPoint("NPCTalk_rwjl_pos"));
//	addChild(ptitle_rwjl); 
//
//
//	TaskRewardPanel* pPanel=TaskRewardPanel::create(mQuestID,1,3);
//	pPanel->settipsdir(1);
//	pPanel->setAnchorPoint(CCPointZero);
//	pPanel->setPosition(SystemData::getLayoutPoint("taskreward_pos")); 
//	addChild(pPanel);
//}
void NPCTaskPanel::addTaskContent()//npc任务第2给界面ui 2
{
	// 创建容器
	CCNode* pContainer = CCNode::create();
	pContainer->setPosition(CCPointZero);
	pContainer->setAnchorPoint(ccp(0.5f, 0.5f));
	
	// 所有子节点添加到容器（保持原始坐标）
	
	// 任务内容背景
	CCScale9Sprite *pTalkBkg=SystemData::getScale9SpriteByPlist("NPCTalk_talkbkg",SystemData::getLayoutValue("NPCTalk_talkbkg.w"),SystemData::getLayoutValue("NPCTalk_talkbkg.h"));
	pTalkBkg->setAnchorPoint(CCPointZero);
	pTalkBkg->setPosition(SystemData::getLayoutPoint("NPCTalk_talkbkg_pos"));
	pContainer->addChild(pTalkBkg);

	std::string TaskContent;
	const int state = TaskData::getTaskState(mQuestID);
	if (state==Quest::state_Available)
	{
		LuaData::getProp(LuaData::QUEST,mQuestID,"text_src",TaskContent);
	}
	else if (state==Quest::state_NotFinished)
	{
		LuaData::getProp(LuaData::QUEST,mQuestID,"des",TaskContent);
	}
	else if (state==Quest::state_Finished)
	{
		LuaData::getProp(LuaData::QUEST,mQuestID,"text_tgt",TaskContent);
	}
	else
	{
		LuaData::getProp(LuaData::QUEST,mQuestID,"des",TaskContent);
	}

	// 任务名称
	CCNode* pNode=CCNode::create();
	pNode->setAnchorPoint(CCPointZero);
	
	CCLabelTTF* pLabelcontent=CCLabelTTF::create(TaskContent.c_str(),"微软雅黑",15);
	pLabelcontent->setDimensions(CCSizeMake(m_nWidth-50,0));
	pLabelcontent->setHorizontalAlignment(kCCTextAlignmentLeft);
	pLabelcontent->setPosition(ccp(0,pLabelcontent->getContentSize().height));
	pLabelcontent->setAnchorPoint(ccp(0,1));

	std::string TaskName; 
	LuaData::getProp(LuaData::QUEST,mQuestID,"name",TaskName);
	CCLabelTTF* pLabelname=CCLabelTTF::create(TaskName.c_str(),"微软雅黑",20);
	pLabelname->setAnchorPoint(CCPointZero); 
	pLabelname->setPosition(pLabelcontent->getPosition());

	m_iTalkLabelHeight=pLabelname->getContentSize().height+pLabelcontent->getContentSize().height;
	pNode->setContentSize(CCSizeMake(pLabelcontent->getContentSize().width,m_iTalkLabelHeight));
	pNode->addChild(pLabelcontent);
	pNode->addChild(pLabelname);
	

	CCTableViewEx *pTabelView=CCTableViewEx::create(this,CCSizeMake(520,75),kCCScrollViewDirectionVertical,this,pNode);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(ccp(SystemData::getLayoutPoint("NPCTalk_talkbkg_pos").x+10,SystemData::getLayoutPoint("NPCTalk_talkbkg_pos").y+7));
	pTabelView->reloadData();  
	pContainer->addChild(pTabelView);
	
	// 任务目标
	CCSprite* ptitle_rwmb=SystemData::getSpriteByPlist("NPCTalk_rwmb");
	ptitle_rwmb->setAnchorPoint(ccp(0,0.5));
	ptitle_rwmb->setPosition(SystemData::getLayoutPoint("NPCTalk_rwmb_pos"));
	pContainer->addChild(ptitle_rwmb);
	 
	CCString *pStr=NPCFunctionData::getCString(mQuestID,12);
	CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"微软雅黑",15);
	pLabel->setAnchorPoint(ccp(0,1));
	pLabel->setPosition(ccp(ptitle_rwmb->getPositionX(),ptitle_rwmb->getPositionY()-20));
	pContainer->addChild(pLabel); 

	// 任务奖励 
	CCSprite* ptitle_rwjl=SystemData::getSpriteByPlist("NPCTalk_rwjl");
	ptitle_rwjl->setAnchorPoint(ccp(0,0.5));
	ptitle_rwjl->setPosition(SystemData::getLayoutPoint("NPCTalk_rwjl_pos"));
	pContainer->addChild(ptitle_rwjl); 

	TaskRewardPanel* pPanel=TaskRewardPanel::create(mQuestID,1,3);
	pPanel->settipsdir(1);
	pPanel->setAnchorPoint(CCPointZero);
	pPanel->setPosition(SystemData::getLayoutPoint("taskreward_pos")); 
	pContainer->addChild(pPanel);

	// 将容器添加到面板
	this->addChild(pContainer);

	// 移动容器
	pContainer->setPositionX(pContainer->getPositionX() + 200);
	pContainer->setPositionY(pContainer->getPositionY() + 60);
}
void NPCTaskPanel::addTaskButton()
{	
	//任务button
	CCLabelTTF *pLabel = NULL;
	CCMenuItemImage* pItemButton=SystemData::getMenuItemImageByPlist("NPCTalk_button");
	pItemButton->setTarget(this,menu_selector(NPCTaskPanel::MenuCallBack));
	pItemButton->setScaleX(1.2f);
	const int state = TaskData::getTaskState(mQuestID);
	if (state==Quest::state_Finished)
	{
		pLabel=SystemData::getLabelTTF("NPCTalk_wcrw");
		pItemButton->setTag(TAG_FINISH);
	}
	else if (state==Quest::state_Available)
	{
		pLabel=SystemData::getLabelTTF("NPCTalk_jsrw");
		pItemButton->setTag(TAG_AVAILABE);
	}
	else if (state==Quest::state_NotFinished)
	{
		pLabel=SystemData::getLabelTTF("NPCTalk_fqrw");
		pItemButton->setTag(TAG_NOTFINISH);
	}
	pItemButton->setPosition(SystemData::getLayoutPoint("NPCTask_button_pos"));
	pLabel->setPosition(pItemButton->getPosition());
	pLabel->setColor(ccWHITE);
	pLabel->setFontSize(18);
	m_pMainMenu->addChild(pItemButton);
	m_pMainMenu->addChild(pLabel);

}

void NPCTaskPanel::MenuCallBack( CCObject * pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	int Tag = 0;
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==TAG_FINISH)
		{
			NPCFunctionData::SubmitQuest(mQuestID);
		}
		else if (tag==TAG_AVAILABE)
		{
			NPCFunctionData::AcceptQuest(mQuestID);
		}
		else if (tag==TAG_NOTFINISH)
		{
			NPCFunctionData::GiveUpQuest(mQuestID);
		}
		else if(tag==TAG_SHOES)
		{
			//获取NPC或者怪物坐标，直接转场景到制定地点
			if (mQuestID > 0)
			{
				NPCFunctionData::getShoesFunc(mQuestID,TAG_GOTOTASK);
			}
		}
		Tag = tag;
		MsgClickNPCRequest* req = new MsgClickNPCRequest;
		req->NPCid=NPCFunctionData::getNPCID();
		HandleMessage::sendMessage(req);
	}
	//BackCallBack(NULL);
	int avalcnt = 0;
	std::vector<int>::iterator it =  GameData::s_user->questlist.begin();
	for (it;it!=GameData::s_user->questlist.end();it++)
	{
		if(TaskData::getTaskState(*it) == Quest::state_Available || TaskData::getTaskState(*it) == Quest::state_Finished)
		{
			avalcnt++;
		}
	}
	if (avalcnt<=1 && (Tag==TAG_AVAILABE || Tag==TAG_FINISH))
	{
		Close();
	}
	else
	{
		BackCallBack(NULL); 
	}
}

void NPCTaskPanel::BackCallBack( CCObject *pSender )
{
	Game::getGameUI()->hidePanel(TAG_NPCTASK_PANEL);
	Game::getGameUI()->showTalkPanel(false);
}

void NPCTaskPanel::CloseCallBack( CCObject *pSender )
{
	Close();
}

void NPCTaskPanel::Close()
{
	int tag=this->getTag();
	this->removeFromParent();
	Game::getGameUI()->hidePanel(TAG_NPCTASK_PANEL);
	//this->removeFromParent();
	Game::getGameUI()->hidePanel(TAG_TALK_PANEL);/*
	if (Game::getGameUI()->getChildByTag(TAG_NPCTASK_PANEL))
	{
	}
	if (Game::getGameUI()->getChildByTag(TAG_TALK_PANEL))
	{
	}*/
}

void NPCTaskPanel::ItemCallBack( CCObject * pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		UserItem* pItem=(UserItem*)pImage->getUserData();
		Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
	}
}

cocos2d::CCSize NPCTaskPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(534,m_iTalkLabelHeight);
}

cocos2d::extension::CCTableViewCell* NPCTaskPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
	}
	return cell;
}

unsigned int NPCTaskPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void NPCTaskPanel::onEnter()
{
	CCLayer::onEnter();
}

void NPCTaskPanel::onExit()
{
	CCLayer::onExit();
}

//----------------------------------------------------------------------------------------------------------//

NPCTaskTitle::NPCTaskTitle():
	m_pTaskMenu(NULL),
	m_bHasTask(true),
	mCurrentDefaultQuest(0),
	m_iQuestHeight(0),
	m_FuncHeight(0),
	m_bIsShowQuest(true)
{

}

NPCTaskTitle::~NPCTaskTitle()
{

}

NPCTaskTitle* NPCTaskTitle::create(bool flag)
{
	NPCTaskTitle* pPanel = new NPCTaskTitle();
	if(pPanel && pPanel->init(flag))
	{
		pPanel->autorelease();
		return pPanel;
	}

	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

bool NPCTaskTitle::init(bool flag)
{
	m_bIsShowQuest=flag;
	initInterFace();
	return true;
}

cocos2d::CCSize NPCTaskTitle::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(535,41);
}

cocos2d::extension::CCTableViewCell* NPCTaskTitle::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		CCMenuEx* pMenu=CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);
		
		if (0 <= idx && idx < (int)mQuestList.size())
		{
			const int qid = mQuestList[idx];
			CCLabelTTF* pLabel=NPCFunctionData::getSingleQuest(qid);
			if (pLabel==NULL)
			{
				return cell;
			}
			CCLabelTTF* pLabel1=NPCFunctionData::getSingleQuest(qid);
			CCScale9Sprite* pselect=SystemData::getScale9SpriteByPlist("NPCTalk_select",535,41);
			pLabel->setPosition(ccp(60,pselect->getContentSize().height/2));
			pLabel1->setPosition(ccp(60,pselect->getContentSize().height/2));
			if (mCurrentDefaultQuest > 0 && idx!=0)
			{
				pselect->setOpacity(0);
			}
			pselect->addChild(pLabel);
			CCScale9Sprite* pselect1=SystemData::getScale9SpriteByPlist("NPCTalk_select",535,41); 
			pselect1->addChild(pLabel1);
			CCMenuItemSprite* pItem=CCMenuItemSprite::create(pselect,pselect1,NULL,this,menu_selector(NPCTaskTitle::MenuCallBack));
			pItem->setAnchorPoint(CCPointZero);
			pItem->setTag(qid + TaskData::getTaskLine(qid)*FlagNum);
			pMenu->addChild(pItem);

			if (qid != mCurrentDefaultQuest)
			{
				mCurrentDefaultQuest = qid;
			}
		}
	}
	return cell;
}

unsigned int NPCTaskTitle::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return mQuestList.size();
}

void NPCTaskTitle::initInterFace()
{
	initQuestList();
	m_TaskHeight=mQuestList.size();
	m_FuncHeight=GameData::s_user->functionlist.size();

	if (m_TaskHeight+m_FuncHeight>4)
	{
		if (m_FuncHeight!=0 && m_TaskHeight>=4 && m_FuncHeight>=1)
		{
			m_TaskHeight=3;
			m_FuncHeight=1;
		}
		else if (m_FuncHeight!=0 && m_TaskHeight>=4 && m_FuncHeight>=2)
		{
			m_TaskHeight=2;
			m_FuncHeight=2;
		}
	}

	//加载NPC任务
	addTaskInterFace();

	//加载NPC功能
	initNPCFunction();

	checkQuestOnlyOne();
	//addSelectButton(mCurrentDefaultQuest);
}

void NPCTaskTitle::addTaskInterFace()
{
	if (m_TaskHeight==0)
	{
		return;
	}
	
	CCTableViewEx *pTabelView=CCTableViewEx::create(this,CCSizeMake(587,123-(3-m_TaskHeight)*41),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(ccp(3,120-(m_TaskHeight-1)*41));
	pTabelView->reloadData(); 
	if ((int)mQuestList.size() <= 3)
	{
		pTabelView->setTouchEnabled(false);
	}
	addChild(pTabelView,1);
}

void NPCTaskTitle::initNPCFunction()
{
	NPCFunctionPanel* pPanel=NPCFunctionPanel::create(m_TaskHeight);
	pPanel->setAnchorPoint(CCPointZero);
	pPanel->setPosition(CCPointZero);
	addChild(pPanel,0);

}

void NPCTaskTitle::addTaskContent( int qid )
{
	CCLog("Press Task Head!");
	/*NPCTaskPanel* pPanel=NPCTaskPanel::create(qid);
	pPanel->setTag(0);
	addChild(pPanel);*/
	//Game::getGameUI()->showNPCTaskPanel(qid);
}

void NPCTaskTitle::MenuCallBack( CCObject * pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		const int tag = pNode->getTag();
		if (tag>FlagNum)
		{
			//QuestInfo* pInfo=(QuestInfo*)pNode->getUserData();
			int qid = tag%FlagNum;
			Game::getGameUI()->showNPCTaskPanel(qid);
		}
		else if(tag==TAG_ACCEPTQUEST)
		{
			if (mCurrentDefaultQuest > 0)
			{
				Game::getGameUI()->showNPCTaskPanel(mCurrentDefaultQuest);
			}
		}
		else if(tag==TAG_FINISH)
		{
			if (mCurrentDefaultQuest > 9)
			{
				Game::getGameUI()->showNPCTaskPanel(mCurrentDefaultQuest);
			}
		}
		else if (tag==TAG_CLOSE)
		{
			Game::getGameUI()->hidePanel(TAG_TALK_PANEL);
		}
	}
}

void NPCTaskTitle::addSelectButton( int qid )
{
	if (m_pTaskMenu==NULL)
	{
		m_pTaskMenu=GeneralMenu::create();
		m_pTaskMenu->setAnchorPoint(CCPointZero);
		m_pTaskMenu->setPosition(CCPointZero);
		addChild(m_pTaskMenu,999);
	}
	if (qid > 0)
	{
		const int state = TaskData::getTaskState(qid);
		if (state==Quest::state_Finished)
		{
			CCMenuItemImage* pButtonItem=SystemData::getMenuItemImageByPlist("NPCTalk_button");
			pButtonItem->setTarget(this,menu_selector(NPCTaskTitle::MenuCallBack));
			pButtonItem->setScaleX(1.2f);
			pButtonItem->setPosition(ccp(SystemData::getLayoutPoint("NPCTask_button_pos").x-SystemData::getLayoutPoint("NPCTalk_tasktitle_Pos").x,SystemData::getLayoutPoint("NPCTask_button_pos").y-SystemData::getLayoutPoint("NPCTalk_tasktitle_Pos").y));
			pButtonItem->setTag(TAG_FINISH);
			CCLabelTTF *ptitle=SystemData::getLabelTTF("NPCTalk_wcrw");
			ptitle->setFontSize(18);
			ptitle->setColor(ccWHITE);
			ptitle->setPosition(pButtonItem->getPosition());
			m_pTaskMenu->addChild(pButtonItem);
			m_pTaskMenu->addChild(ptitle);
		}
		else if (state==Quest::state_Available)
		{			 
			CCMenuItemImage* pButtonItem=SystemData::getMenuItemImageByPlist("NPCTalk_button");
			pButtonItem->setTarget(this,menu_selector(NPCTaskTitle::MenuCallBack));
			pButtonItem->setScaleX(1.2f);
			pButtonItem->setPosition(ccp(SystemData::getLayoutPoint("NPCTask_button_pos").x-SystemData::getLayoutPoint("NPCTalk_tasktitle_Pos").x,SystemData::getLayoutPoint("NPCTask_button_pos").y-SystemData::getLayoutPoint("NPCTalk_tasktitle_Pos").y));
			pButtonItem->setTag(TAG_ACCEPTQUEST);
			CCLabelTTF *ptitle=SystemData::getLabelTTF("NPCTalk_jsrw");
			ptitle->setFontSize(18);
			ptitle->setColor(ccWHITE);
			ptitle->setPosition(pButtonItem->getPosition());
			m_pTaskMenu->addChild(pButtonItem);
			m_pTaskMenu->addChild(ptitle);
		}
	}
	
}

void NPCTaskTitle::ChangeMap(int mapid)
{
	MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
	sceneMsg->sid = mapid;
	sceneMsg->reason = Scene::seInstance;	
	HandleMessage::sendMessage(sceneMsg);
}

static bool upSort(int qid1, int qid2)
{
	const int state1 = TaskData::getTaskState(qid1);
	const int state2 = TaskData::getTaskState(qid2);
	return (state1 < state2);
}

void NPCTaskTitle::initQuestList()
{
	mQuestList = GameData::s_user->questlist;
	
	sort(mQuestList.begin(),mQuestList.end(),upSort);
	if (mQuestList.empty())
	{
		m_bHasTask=false;
	}
}

void NPCTaskTitle::checkQuestOnlyOne()
{
	if (m_bIsShowQuest)
	{
		if (m_TaskHeight==1)
		{
			int quest_state=TaskData::getTaskState(mCurrentDefaultQuest);
			if (quest_state==Quest::state_Available || quest_state==Quest::state_Finished)
			{
				//int sid = TaskData::getFirstTask(mCurrentDefaultQuest);
				int lvl = 0;
				LuaData::getProp(LuaData::QUEST,mCurrentDefaultQuest,"req_lvl",lvl);
				if ((HeroData::getProp(Entity::attr_reborn)<=0 && HeroData::getLevel()>=lvl )|| HeroData::getProp(Entity::attr_reborn)>0)
				{
					Game::getGameUI()->showNPCTaskPanel(mCurrentDefaultQuest);
				}
			}
		}
	}
}

void NPCTaskTitle::setShowQuest( bool flag )
{
	m_bIsShowQuest=flag;
	checkQuestOnlyOne();
}

//-----------------------------------------------------------------------------------------------------------------//

NPCFunctionPanel::NPCFunctionPanel():
	m_pFuncList(NULL),
	m_iFuncCount(0)
{

}

NPCFunctionPanel::~NPCFunctionPanel()
{

}

bool NPCFunctionPanel::init(int taskcount)
{
	//m_pFuncList=NPCFunctionData::getnpcFunction(GameData::s_user->functionlist,NPCFunctionData::getIsSub());
	m_iFuncCount=GameData::s_user->functionlist.size();

	if (NPCFunctionData::getReadme())
	{
		taskcount=3;
	}
	CCTableViewEx *pTabelView=CCTableViewEx::create(this,CCSizeMake(587,(4-taskcount)*40),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(ccp(3,5));
	pTabelView->reloadData(); 
	if (m_iFuncCount<=(4-taskcount))
	{
		pTabelView->setTouchEnabled(false);
	}
	addChild(pTabelView);

	if (NPCFunctionData::getIsSub())
	{
		for (std::vector<npcFunction>::iterator it=GameData::s_user->functionlist.begin();it!=GameData::s_user->functionlist.end();it++)
		{
			npcFunction func=(npcFunction)*it;
			if (func.functionid==7)
			{
				npcFunction* pfunc = new npcFunction;
				pfunc->data = func.data;
				pfunc->functionid = func.functionid;
				pfunc->show = func.show;
				pfunc->numid = func.numid;
				GeneralMenu* pMenu= GeneralMenu::create();
				pMenu->setAnchorPoint(CCPointZero);
				pMenu->setPosition(CCPointZero);
				addChild(pMenu);
				CCMenuItemImage* pButtonItem=SystemData::getMenuItemImageByPlist("NPCTalk_button");
				pButtonItem->setTarget(this,menu_selector(NPCFunctionPanel::MenuCallBack));
				pButtonItem->setScaleX(1.2f);
				pButtonItem->setPosition(ccp(75,-22));
				pButtonItem->setTag(TAG_BACK);
				pButtonItem->setUserData(pfunc);
				CCLabelTTF *ptitle=SystemData::getLabelTTF("NPCTalk_fh");
				ptitle->setFontSize(18);
				ptitle->setColor(ccWHITE);
				ptitle->setPosition(pButtonItem->getPosition());
				pMenu->addChild(pButtonItem);
				pMenu->addChild(ptitle);
				break;				
			}
		}
	}

	return true;
}

NPCFunctionPanel* NPCFunctionPanel::create(int taskcount)
{
	NPCFunctionPanel* pPanel = new NPCFunctionPanel();
	if(pPanel && pPanel->init(taskcount))
	{
		pPanel->autorelease();
		return pPanel;
	}

	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

cocos2d::CCSize NPCFunctionPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(535,41);
}

cocos2d::extension::CCTableViewCell* NPCFunctionPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		CCMenuEx* pMenu=CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		CCArray* pArray=NPCFunctionData::getnpcFunction(GameData::s_user->functionlist,NPCFunctionData::getIsSub());
		CCObject* pObject;
		CCMenuItemSprite* pItem=NULL;
		int i=0;
		CCARRAY_FOREACH(pArray,pObject)
		{
			if (idx==i)
			{
				pItem=(CCMenuItemSprite*)pObject;
				break;
			}
			i++;
		}
		if (pItem && pItem->getTag()!=TAG_BACK)
		{
			CCScale9Sprite* pselect=SystemData::getScale9SpriteByPlist("NPCTalk_select",535,41);
			CCScale9Sprite* pselect1=SystemData::getScale9SpriteByPlist("NPCTalk_select",535,41);

			pselect->setOpacity(0);
			CCMenuItemSprite* p=CCMenuItemSprite::create(pselect,pselect1,NULL,this,menu_selector(NPCFunctionPanel::MenuCallBack));
			p->setTag(pItem->getTag());
			p->setAnchorPoint(CCPointZero);	
			p->setUserData(pItem->getUserData());
			pMenu->addChild(p);

			pItem->setPosition(ccp(10,pselect->getContentSize().height/2));
			pItem->setAnchorPoint(ccp(0,0.5));
			pMenu->addChild(pItem);
		}
	}
	return cell;
}

unsigned int NPCFunctionPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return m_iFuncCount;
}

CCMenuItemSprite* NPCFunctionPanel::getFuncButton( int n )
{
	CCObject* pObject;
	int i=0;
	CCARRAY_FOREACH(m_pFuncList,pObject)
	{
		if (n==i)
		{
			return (CCMenuItemSprite*)pObject;
		}
		i++;
	}
	return NULL;
}

void NPCFunctionPanel::MenuCallBack( CCObject * pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==TAG_CHANGEMAP)
		{
			//传送被点击
			npcFunction *func=(npcFunction *)pNode->getUserData();
			ChangeMap(func->data);
		}
		else if (tag==TAG_NPCSHOP)//打开npc商店
		{
			npcFunction *func=(npcFunction *)pNode->getUserData();
			CPEventHelper::openPanel("NpcShopComp", func->data, 0, 0, 0);

			Game::getGameUI()->hidePanel(TAG_TALK_PANEL);
		}
		else if (tag==TAG_SCRIPT_C)
		{
			int NPCID=NPCFunctionData::getNPCID();
			npcFunction *func=(npcFunction *)pNode->getUserData();
			NPCFunctionData::clickFunctionScriptC(NPCID, func->data);

			Game::getGameUI()->hidePanel(TAG_TALK_PANEL);
		}
		else if (tag==TAG_SCRIPT_S)
		{
			int NPCID=NPCFunctionData::getNPCID();
			npcFunction *func=(npcFunction *)pNode->getUserData();
			NPCFunctionData::clickFunctionScriptS(NPCID, func->data);

			if (NPCFunctionData::clickNPCclosePanel(NPCID,func->data))
			{
				Game::getGameUI()->hidePanel(TAG_TALK_PANEL);
			}
		}
		else if (tag==TAG_CONNNPC)
		{
			npcFunction *func=(npcFunction *)pNode->getUserData();
			NPCFunctionData::clickOtherNpc(func->data,true);
		}
		else if (tag==TAG_SHOWTALK)
		{
			npcFunction *func=(npcFunction *)pNode->getUserData();
			NPCFunctionData::clickOtherNpc(func->data,true,true); 
		}
		else if (tag==TAG_BACK)
		{
			npcFunction *func=(npcFunction *)pNode->getUserData();
			NPCFunctionData::clickOtherNpc(func->data); 
		}
		else if (tag==TAG_BACKSCENE)
		{
			npcFunction *func=(npcFunction *)pNode->getUserData();
			ChangeMapBack();
		}
	}
}

void NPCFunctionPanel::ChangeMap( int mapid )
{
	MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
	sceneMsg->sid = mapid;
	sceneMsg->reason = Scene::seInstance;	
	HandleMessage::sendMessage(sceneMsg);
}

void NPCFunctionPanel::ChangeMapBack()
{
	MsgEnterSceneRequest* sceneMsg = new MsgEnterSceneRequest;
	sceneMsg->sid = GameData::s_user->mMap.mID;
	sceneMsg->reason = Scene::seBack;	
	HandleMessage::sendMessage(sceneMsg);
}

void NPCFunctionPanel::ChangeCrossServer()
{
	MsgCrossServerRequest* pmsg = new MsgCrossServerRequest;
	HandleMessage::sendMessage(pmsg);
}

////////PortalPanel//////////////////////////////////////////////////
PortalStonePanel::PortalStonePanel()
{

}

PortalStonePanel::~PortalStonePanel()
{

}

bool PortalStonePanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initUI();

	return true;
}

void PortalStonePanel::initUI()
{
	const CCSize &tableSize = LayoutData::getSize(CPModuleName::MAIN_UI, "portalStone");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::MAIN_UI, "portalStoneItem");
	const int perLine = LayoutData::getInt(CPModuleName::MAIN_UI, "portalStonePerLine");
	mPortals = CPItemComponents::create(tableSize, new CPLayoutGrid(perLine, itemSize, true));
	mPortals->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "portalStone"));
	addChild(mPortals);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::MAIN_UI, "portalStoneScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mPortals->setScrollbar(scrollBar);

	const int npcID = NPCFunctionData::getNPCID();
	int count = 0;
	std::string caption;
	StaticData::getNPCFunctionCount(npcID, count);
	for (int i = 0; i < count; i++)
	{
		StaticData::getNPCFunctionCaption(npcID, i + 1, caption);
		if (!caption.empty())
		{
			CCNode *node = CCNode::create();
			node->setContentSize(itemSize);
			mPortals->addItem(node);

			CCMenu *menu = CCMenu::create();
			menu->setPosition(CCPointZero);
			node->addChild(menu);

			CCMenuItemFont *btn = LayoutData::getMenuItemFont(CPModuleName::MAIN_UI, "portalStoneName");
			btn->setString(caption.c_str());
			btn->setAnchorPoint(ccp(0, 1));
			btn->setPosition(ccp(0, itemSize.height));
			menu->addChild(btn, 0, i + 1);
			if (caption == GameData::s_user->mMap.mName)
			{
				btn->setColor(ccGREEN);
			}
			else
			{
				btn->setTarget(this, menu_selector(PortalStonePanel::onTeleport));
			}
		}
	}
}

void PortalStonePanel::onTeleport( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int index = node->getTag();
		if (1==SystemData::getConfigInt("mini") && (7== index || 10 == index || 11==index || 12==index))
		{
			CPEventHelper::msgNotify("PreventMiniSwitchToUnknownMap", "",0,0,0,0);
			return ;
		}
		NPCFunctionData::clickFunctionScriptS(NPCFunctionData::getNPCID(), index);
	}
}
