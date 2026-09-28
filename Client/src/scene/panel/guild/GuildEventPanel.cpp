#include "GuildEventPanel.h"
#include "GuildPanel.h"

#include "userdata/netdata/GameRole.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "ext/CCMenuItemFontEx.h"
#include "ext/GeneralMenu.h"
#include "event/EventProtocol.h"

#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "ext/TouchCover.h"
#include "QuestDefinition.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "userdata/netdata/GhostManager.h"
#include "MsgScene.h"
#include "userdata/NPCFunctionData.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "event/CPEventDispatcher.h"
#include "ModuleData.h"
#include "userdata/LayoutData.h"

//-----------------------------------------------------------------------------------------------------------//


GuildEventPanel::GuildEventPanel():
	m_pMainMenu(NULL),
	m_iCurrentType(-1),
	mHeight(0),
	m_iCurrentQuestID(0),
	m_pInfo(NULL),
	m_pCurrentQuestSprite(NULL)
{
	//CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

GuildEventPanel::~GuildEventPanel()
{
	//CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

GuildEventPanel* GuildEventPanel::create()
{
	GuildEventPanel* pPanel = new GuildEventPanel();
	if(pPanel && pPanel->init(""))
	{
		pPanel->autorelease();
		return pPanel;
	}
	else
	{
		CCLog("GuildPanel create failed!");
	}
	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}


bool GuildEventPanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}
	//m_iCurrentType=TAG_GUILDINFO;

	initFrame();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);
	
	initLabels();
	initButtons();

	CCSize pPlacardSize = CCSizeMake(SystemData::getLayoutValue("guild.info.placard.w"),SystemData::getLayoutValue("guild.info.placard.h"));
	CCPoint pPlacardPoint = SystemData::getLayoutPoint("guild.info.placard");
	m_pTableView = CCTableViewEx::create(this,CCSizeMake(pPlacardSize.width/*-15*/,pPlacardSize.height/*-60*/),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setAnchorPoint(CCPointZero);	
	m_pTableView->setPosition(ccp(pPlacardPoint.x/*+5*/,pPlacardPoint.y/*+30*/));
	//m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	/*m_pLeftMenu->*/addChild(m_pTableView); 
	m_pTableView->setVisible(false);       

	this->setTouchEnabled(true);
	return true;
}

void GuildEventPanel::hide()
{
	this->removeFromParent();
}

void GuildEventPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==Button_Close)
		{
			hide();	
		}
		else if (tag==2)
		{

		}

	}
}
void GuildEventPanel::onCPEvent(const std::string &eventName)
{
}

cocos2d::CCSize GuildEventPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutSize("taskcontent_leftmenu_size").width-20, mHeight);
}

cocos2d::extension::CCTableViewCell* GuildEventPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		CCMenuEx* pMenu = CCMenuEx::create(NULL,NULL);
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);
	}
	return cell;
}

unsigned int GuildEventPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void GuildEventPanel::CloseSelf(CCObject* pSender)
{
	Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);	
}

void GuildEventPanel::handleEvent( int channel )
{	
	if(channel == EventProtocol::EVENT_TASK_RECEIVED)
	{
		//CCLog("Event Recieve");
	}
}

void GuildEventPanel::initFrame()
{
	// 添加背景
	CCScale9Sprite *bg = LayoutData::getScale9Sprite(CPModuleName::COMMON, "bkg");
	addChild(bg);

	// 添加顶部Bar
	CCScale9Sprite *topbar = LayoutData::getScale9Sprite(CPModuleName::COMMON, "titleBoard");
	addChild(topbar);

	CCScale9Sprite *bkg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",SystemData::getLayoutValue("guild.bg.w"),SystemData::getLayoutValue("guild.bg.h"));
	//CCScale9Sprite *bkg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",709,470);
	bkg->setAnchorPoint(CCPointZero);
	bkg->setPosition(SystemData::getLayoutPoint("guild.bg"));
	addChild(bkg);

	m_nWidth = 709;//bkg->getContentSize().width;
	m_nHeight = 470;//bkg->getContentSize().height;
	addCover();//swallow the touch event in case of leaking to the map layer
	/*
	//输出框
	CCScale9Sprite *outputView=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.chat.outputbg.w"),SystemData::getLayoutValue("guild.chat.outputbg.h"));
	outputView->setAnchorPoint(CCPointZero);
	outputView->setPosition(SystemData::getLayoutPoint("guild.chat.outputbg"));
	addChild(outputView);
	//输入框
	CCScale9Sprite *inputView=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.chat.inputbg.w"),SystemData::getLayoutValue("guild.chat.inputbg.h"));
	inputView->setAnchorPoint(CCPointZero);
	inputView->setPosition(SystemData::getLayoutPoint("guild.chat.inputbg"));
	addChild(inputView);
	//公告栏
	CCScale9Sprite *pPlacard=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.chat.placardbg.w"),SystemData::getLayoutValue("guild.chat.placardbg.h"));
	pPlacard->setAnchorPoint(CCPointZero);  
	pPlacard->setPosition(SystemData::getLayoutPoint("guild.chat.placardbg")); 
	addChild(pPlacard);	
	//群成员标题
	CCScale9Sprite *pTableTitle=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.chat.headerbg.w"),SystemData::getLayoutValue("guild.chat.headerbg.h"));
	pTableTitle->setAnchorPoint(CCPointZero);  
	pTableTitle->setPosition(SystemData::getLayoutPoint("guild.chat.headerbg")); 
	addChild(pTableTitle);	
	//群成员列表
	CCScale9Sprite *pTable=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.chat.tablebg.w"),SystemData::getLayoutValue("guild.chat.tablebg.h"));
	pTable->setAnchorPoint(CCPointZero);  
	pTable->setPosition(SystemData::getLayoutPoint("guild.chat.tablebg")); 
	addChild(pTable);	
	*/
}


void GuildEventPanel::initLabels()
{
	CCLabelTTF* tName = SystemData::getLabelTTF("guild.member.title.name");
	tName->setColor(ccWHITE);
	tName->setFontSize(18);     
	tName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tName);

	CCLabelTTF* tJob = SystemData::getLabelTTF("guild.member.title.job");
	tJob->setColor(ccWHITE);
	tJob->setFontSize(18);   
	tJob->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tJob);

	CCLabelTTF* tLevel = SystemData::getLabelTTF("guild.member.title.level");
	tLevel->setColor(ccWHITE);
	tLevel->setFontSize(18);
	tLevel->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tLevel);

	CCLabelTTF* tContribution = SystemData::getLabelTTF("guild.member.title.contribution");
	tContribution->setColor(ccWHITE);
	tContribution->setFontSize(18);   
	tContribution->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tContribution);

	CCLabelTTF* tNickname = SystemData::getLabelTTF("guild.member.title.nickname");
	tNickname->setColor(ccWHITE);
	tNickname->setFontSize(18);   
	tNickname->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tNickname);

	CCLabelTTF* tOperate = SystemData::getLabelTTF("guild.member.title.operate");
	tOperate->setColor(ccWHITE);
	tOperate->setFontSize(18);   
	tOperate->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tOperate);

	CCLabelTTF* tNicknameSel = SystemData::getLabelTTF("guild.member.title.nicknamesel");
	tNicknameSel->setColor(ccWHITE);
	tNicknameSel->setFontSize(18);   
	tNicknameSel->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tNicknameSel);

	m_LabelPage =  SystemData::getLabelTTF("guild.member.title.page");
	m_LabelPage->setColor(ccWHITE);
	m_LabelPage->setFontSize(15);   
	m_LabelPage->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(m_LabelPage); 
}

void GuildEventPanel::initButtons()
{
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("shop.close");
	pClose->setTarget(this,menu_selector(GuildEventPanel::MenuCallBack));
	pClose->setTag(Button_Close);
	pClose->setPosition(ccp(716,483));
	pClose->setAnchorPoint(ccp(1,1));
	m_pMainMenu->addChild(pClose);

	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.button",100,40);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,40);
	CCMenuItemSprite *pDetail =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(GuildEventPanel::MenuCallBack));//行会信息按钮
	if(pDetail)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.detail.text");
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		//pDetail->setTag(TAG_GUILDINFO);
		pDetail->setPosition(SystemData::getLayoutPoint("guild.member.button.detail"));
		pLabel->setPosition(pDetail->getPosition());
		m_pMainMenu->addChild(pDetail);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("guild.info.button",100,40);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,40);
	CCMenuItemSprite *pChat =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(GuildEventPanel::MenuCallBack));//行会信息按钮
	if(pChat)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.chat.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		//pChat->setTag(TAG_GUILDINFO);
		pChat->setPosition(SystemData::getLayoutPoint("guild.member.button.chat"));
		pLabel->setPosition(pChat->getPosition());
		m_pMainMenu->addChild(pChat);
		m_pMainMenu->addChild(pLabel);
	}
}