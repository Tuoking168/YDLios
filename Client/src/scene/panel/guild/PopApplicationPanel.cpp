#include "PopApplicationPanel.h"
#include "GuildPanel.h"
#include "GuildModule.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/LayoutData.h"
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
#include "userdata/GuildData.h"
#include "GuildDefinition.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "ModuleData.h"

//-----------------------------------------------------------------------------------------------------------//


PopApplicationPanel::PopApplicationPanel():
	m_pMainMenu(NULL),
	m_LabelInfo(NULL),
	m_LabelPage(NULL),
	m_selIndex(-1),
	m_pListener(NULL),
	m_pfnSelector(NULL)
	, m_AlertBg(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

PopApplicationPanel::~PopApplicationPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

PopApplicationPanel* PopApplicationPanel::create()
{
	PopApplicationPanel* pPanel = new PopApplicationPanel();
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


bool PopApplicationPanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_nHeight = SystemData::size_y+1000;
	m_nWidth = SystemData::size_x+1000;

	addCover(ccp(-1000,-1000));

	initFrame();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	m_AlertBg->addChild(m_pMainMenu);

	initLabels();
	initButtons();
	
	CCSize pPlacardSize = m_AlertBg->getContentSize();//SystemData::getLayoutSize("popalert.normal.bigbg");
	CCPoint pPlacardPoint =CCPointZero; //SystemData::getLayoutPoint("guild.browse.tablebg");
	m_pTableView = CCTableViewEx::create(this,CCSizeMake(pPlacardSize.width,pPlacardSize.height-170),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setAnchorPoint(CCPointZero);	
	m_pTableView->setPosition(ccp(15,75));
	//m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_AlertBg->addChild(m_pTableView); 
	//m_pTableView->setVisible(false);        
	
	this->setTouchEnabled(true);

	return true;
}



void PopApplicationPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==Tag_Close)
		{
			closeSelf();	
		}
		else if (tag==Tag_Confirm)
		{
			//handleConfirmPressed();
			MsgApplicationResultRequest* req = new MsgApplicationResultRequest();
			req->pid = GuildData::getGuildApplicationPID(m_selIndex);
			req->Decide = GuildType::app_accept;
			HandleMessage::sendMessage(req);
		}
		else if (tag==Tag_Cancel)
		{
			MsgApplicationResultRequest* req = new MsgApplicationResultRequest();
			req->pid = GuildData::getGuildApplicationPID(m_selIndex);
			req->Decide = GuildType::app_refuse;
			HandleMessage::sendMessage(req);
		}
		else if (tag == Tag_Refuse_All)
		{
			MsgGuildRefuseAllApplicationRequest *req
				= new MsgGuildRefuseAllApplicationRequest();
			HandleMessage::sendMessage(req);
		}
	}
}

cocos2d::CCSize PopApplicationPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	//return CCSizeMake(SystemData::getLayoutSize("guild.browse.tablebg").width, 45); 
	return CCSizeMake(m_AlertBg->getContentSize().width-30, 45); 
}

cocos2d::extension::CCTableViewCell* PopApplicationPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		initCell(cell);
	}
	loadCell(cell,idx);
	return cell;
}

unsigned int PopApplicationPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return GuildData::getGuildApplicationCnt();
}

void PopApplicationPanel::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
	if (m_selIndex>=0)
	{
		CCTableViewCell* cell = table->cellAtIndex(m_selIndex);
		if (cell)
		{
			cell->removeChildByTag(99);
		}
	}
	m_selIndex = cell->getIdx();
	CCScale9Sprite *selectBg= LayoutData::getScale9Sprite(CPModuleName::GUILD, "listSelFlag");
	selectBg->setContentSize(cellSizeForTable(table));
	selectBg->setAnchorPoint(CCPointZero);
	cell->addChild(selectBg,-1,99); 
	
}

void PopApplicationPanel::closeSelf()
{
	//Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);	
	this->removeFromParentAndCleanup(true);
}

void PopApplicationPanel::initFrame()
{
	m_AlertBg=SystemData::getSpriteByPlist("ui_float_menu_border");
	m_AlertBg->setAnchorPoint(ccp(0.5,0.5));
	m_AlertBg->setPosition(ccp(400,240));
	addChild(m_AlertBg);

	CCScale9Sprite* m_Line=SystemData::getScale9SpriteByPlist("popalert.normal.sprite.line",m_AlertBg->getContentSize().width,3); 
	m_Line->setAnchorPoint(ccp(0.5,0.5));  
	m_Line->setPosition(ccp(m_AlertBg->getContentSize().width/2,m_AlertBg->getContentSize().height-90));  
	m_AlertBg->addChild(m_Line); 
	/*
	CCSize bigBgSize = SystemData::getLayoutSize("popalert.normal.bigbg");
	CCScale9Sprite* bigBg=SystemData::getScale9SpriteByPlist("popalert.normal.bigbg",bigBgSize.width,bigBgSize.height);
	addChild(bigBg);
	 
	CCSize titleSize = SystemData::getLayoutSize("popalert.normal.titlebg");
	CCScale9Sprite* titleBg=SystemData::getScale9SpriteByPlist("popalert.normal.titlebg",titleSize.width,titleSize.height);
	addChild(titleBg);
	*/
}

void PopApplicationPanel::initLabels()
{
	/*
	m_LabelPage =  SystemData::getLabelTTF("guild.browse.title.page");
	m_LabelPage->setColor(ccWHITE);
	m_LabelPage->setFontSize(15);   
	m_LabelPage->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(m_LabelPage); 
	*/
	CCLabelTTF* m_Title =  SystemData::getLabelTTF("popalert.normal.label.title"); 
	m_Title->setColor(ccYELLOW);
	m_Title->setFontSize(22);    
	m_Title->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_Title->setDimensions(CCSizeMake(SystemData::getLayoutValue("popalert.normal.label.title.w"),SystemData::getLayoutValue("popalert.normal.label.title.h")));
	m_Title->setAnchorPoint(ccp(0.5,1));
	m_Title->setPosition(ccp(m_AlertBg->getContentSize().width/2,m_AlertBg->getContentSize().height-10));
	m_AlertBg->addChild(m_Title);
	m_Title->setString(SystemData::getLayoutString("popalert.applist.title").c_str());

	m_LabelInfo =  SystemData::getLabelTTF("popalert.normal.label.alert"); 
	m_LabelInfo->setColor(ccWHITE);
	m_LabelInfo->setFontSize(18);    
	m_LabelInfo->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_LabelInfo->setDimensions(CCSizeMake(SystemData::getLayoutValue("popalert.normal.label.alert.w"),SystemData::getLayoutValue("popalert.normal.label.alert.h")));
	addChild(m_LabelInfo); 

	CCLabelTTF* tName = SystemData::getLabelTTF("guild.member.alert.title.name");
	//tName->setPosition(ccp(tName->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tName->setColor(ccYELLOW);
	tName->setFontSize(20);     
	//tName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	m_AlertBg->addChild(tName);

	CCLabelTTF* tLevel = SystemData::getLabelTTF("guild.member.alert.title.master");
	//tLevel->setPosition(ccp(tLevel->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tLevel->setColor(ccYELLOW); 
	tLevel->setFontSize(20);    
	//tLevel->setHorizontalAlignment(kCCTextAlignmentLeft); 
	m_AlertBg->addChild(tLevel);
}

void PopApplicationPanel::initButtons()
{
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("popalert.normal.button.close");
	pClose->setTag(Tag_Close);
	pClose->setTarget(this,menu_selector(PopApplicationPanel::MenuCallBack));
	//pClose->setAnchorPoint(ccp(1,1));
	//pClose->setPosition(ccp(m_Size.width,m_Size.height));
	pClose->setPosition(ccp(m_AlertBg->getContentSize().width-25,m_AlertBg->getContentSize().height-25));
	m_pMainMenu->addChild(pClose);

	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("guild.info.placard.button",100,45);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",100,45);
	CCMenuItemSprite *pConfirm =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(PopApplicationPanel::MenuCallBack));
	if(pConfirm)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("popalert.normal.button.confirm.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pConfirm->setTag(Tag_Confirm);
		pConfirm->setPosition(/*SystemData::getLayoutPoint("popalert.normal.button.confirm")*/ccp(m_AlertBg->getContentSize().width/4,m_AlertBg->getContentSize().height/8));
		pLabel->setPosition(pConfirm->getPosition());
		m_pMainMenu->addChild(pConfirm);
		m_pMainMenu->addChild(pLabel);

		pLabel->setString(SystemData::getLayoutString("popalert.member.application.yes").c_str());
	}

	CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("guild.info.placard.button",100,45);
	CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",100,45);
	CCMenuItemSprite *pCancel =CCMenuItemSprite::create(p3,pSel3,NULL,this,menu_selector(PopApplicationPanel::MenuCallBack));
	if(pCancel)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("popalert.normal.button.cancel.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pCancel->setTag(Tag_Cancel);
		pCancel->setPosition(/*SystemData::getLayoutPoint("popalert.normal.button.cancel")*/ccp(m_AlertBg->getContentSize().width/4*3,m_AlertBg->getContentSize().height/8));
		pLabel->setPosition(pCancel->getPosition());
		m_pMainMenu->addChild(pCancel);
		m_pMainMenu->addChild(pLabel);

		pLabel->setString(SystemData::getLayoutString("popalert.member.application.no").c_str());
	}

	CCMenuItemSprite* refuseAll = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "refuseAllApplication");
	if (refuseAll)
	{
		refuseAll->setTag(Tag_Refuse_All);
		refuseAll->setPosition(ccp(m_AlertBg->getContentSize().width/4 * 2,
			m_AlertBg->getContentSize().height/8));
		refuseAll->setTarget(this, menu_selector(PopApplicationPanel::MenuCallBack));
		m_pMainMenu->addChild(refuseAll);
	}
}

void PopApplicationPanel::initCell(CCTableViewCell *cell)
{
	if (m_selIndex==cell->getIdx())
	{
		//tableCellTouched(m_pTableView,cell);//这里需要修复滑动重现之后的cell标记消失的bug
	}
	CCLabelTTF* tName = SystemData::getLabelTTF("guild.browse.title.name");
	tName->setPosition(ccp(tName->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tName->setColor(ccWHITE);
	tName->setFontSize(18);     
	tName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	tName->setTag(Cell_Name);
	cell->addChild(tName);

	CCLabelTTF* tLevel = SystemData::getLabelTTF("guild.browse.title.master");
	tLevel->setPosition(ccp(tLevel->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tLevel->setColor(ccWHITE);
	tLevel->setFontSize(18);   
	tLevel->setHorizontalAlignment(kCCTextAlignmentLeft); 
	tLevel->setTag(Cell_Level);
	cell->addChild(tLevel);
}
void PopApplicationPanel::loadCell(CCTableViewCell *cell,unsigned int idx)
{
	std::string s_Level;
	std::stringstream ss_Level;
	ss_Level<<GuildData::getGuildApplicationLevel(idx);
	ss_Level>>s_Level;

	CCLabelTTF* tName = (CCLabelTTF*)cell->getChildByTag(Cell_Name);
	tName->setString(GuildData::getGuildApplicationName(idx).c_str());

	CCLabelTTF* tLvl = (CCLabelTTF*)cell->getChildByTag(Cell_Level);
	tLvl->setString(s_Level.c_str());
}
void PopApplicationPanel::setConfirmTarget(CCObject *rec, SEL_MenuHandler selector)
{
	m_pListener = rec;
    m_pfnSelector = selector;
}
void PopApplicationPanel::handleConfirmPressed()
{
	if (m_pListener && m_pfnSelector)
    {
		 (m_pListener->*m_pfnSelector)(this);
	}
}
void PopApplicationPanel::setString(std::string alert)
{
	m_LabelInfo->setString(alert.c_str());
}
void PopApplicationPanel::setData(std::string vkey)
{
	//set vector
	m_pTableView->reloadData();
}

void PopApplicationPanel::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{

}
void PopApplicationPanel::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{

}
void PopApplicationPanel::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{

}

void PopApplicationPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		//if(source == "HandleMessageGuildApplicationChangeNotify")
		{
			if (m_pTableView)
			{
				m_pTableView->reloadData();
				CCLog("_____droid_________________app list count: %d",GuildData::getGuildApplicationCnt());
			}
		}
	}
}