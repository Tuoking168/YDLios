#include "PopAlertPanel.h"
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
#include "controls/CPNodeHelper.h"

//-----------------------------------------------------------------------------------------------------------//


PopAlertPanel::PopAlertPanel():
	m_pMainMenu(NULL),
	m_LabelInfo(NULL),
	m_LabelPage(NULL),
	m_selIndex(-1),
	m_pListener(NULL),
	m_pfnSelector(NULL),
	m_CancelListener(NULL),
	m_CancelSelector(NULL),
	m_AlertBg(NULL),
	m_ConfirmTitle(NULL),
	m_CancelTitle(NULL),
	m_MenuConfirm(NULL),
	m_MenuCancel(NULL),
	m_Title(NULL),
	m_PressConfirm(false)
	, m_Type(0)
	, m_Line(NULL)
	, m_OptionCount(0)
{

}

PopAlertPanel::~PopAlertPanel()
{

}
void PopAlertPanel::onEnter()
{
	BasePanel::onEnter();
	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}
PopAlertPanel* PopAlertPanel::create(int pType,int optionCnt)
{
	PopAlertPanel* pPanel = new PopAlertPanel();
	if(pPanel && pPanel->init(pType,optionCnt))
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


bool PopAlertPanel::init(int pType,int optionCnt)
{
	if (!CCLayer::init())
	{
		return false;
	}
	//m_Size = alertSize;
	m_Type = pType;
	m_OptionCount = optionCnt;

	this->setZOrder(999);

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
	/*
	CCSize pPlacardSize = CCSizeMake(SystemData::getLayoutValue("guild.browse.tablebg.w"),SystemData::getLayoutValue("guild.browse.tablebg.h"));
	CCPoint pPlacardPoint = SystemData::getLayoutPoint("guild.browse.tablebg");
	m_pTableView = CCTableViewEx::create(this,CCSizeMake(pPlacardSize.width,pPlacardSize.height-60),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setAnchorPoint(CCPointZero);	
	m_pTableView->setPosition(ccp(pPlacardPoint.x,pPlacardPoint.y+60));
	//m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	addChild(m_pTableView); 
	m_pTableView->setVisible(false);        
	*/
	this->setTouchEnabled(true);

	return true;
}



void PopAlertPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==Tag_Close)
		{
			
		}
		else if (tag==Tag_Confirm)
		{
			m_PressConfirm = true;
			handleConfirmPressed();
		}
		else if (tag==Tag_Cancel)
		{
			m_PressConfirm = false;
			handleCancelPressed();
		}
		closeSelf();		
	}
}

cocos2d::CCSize PopAlertPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutSize("guild.browse.tablebg").width, 45); 
}

cocos2d::extension::CCTableViewCell* PopAlertPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		initCell(cell);
	}
	return cell;
}

unsigned int PopAlertPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 6;
}

void PopAlertPanel::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
	if (m_selIndex>=0)
	{
		CCTableViewCell* cell = table->cellAtIndex(m_selIndex);
		cell->removeChildByTag(99);
	}
	m_selIndex = cell->getIdx();
	CCScale9Sprite *selectBg= LayoutData::getScale9Sprite(CPModuleName::GUILD, "listSelFlag");
	selectBg->setContentSize(cellSizeForTable(table));
	selectBg->setAnchorPoint(CCPointZero);
	cell->addChild(selectBg,-1,99); 
	
}

void PopAlertPanel::closeSelf()
{
	//Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);	
	this->removeFromParentAndCleanup(true);
}

void PopAlertPanel::initFrame()
{
	if (m_Type==Type_Big)
	{
		m_AlertBg = SystemData::getSpriteByPlist("openactivity.alert.frame.background");
		m_AlertBg->setAnchorPoint(ccp(0.5,0.5));  
		addChild(m_AlertBg);

		CCSize bgSize = SystemData::getLayoutSize("openactivity.alert.frame.scalebg");
		CCPoint bgPoint = SystemData::getLayoutPoint("openactivity.alert.frame.scalebg");
		CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("openactivity.alert.frame.scalebg",bgSize.width,bgSize.height);
		bg->setAnchorPoint(ccp(0.5,0.5));
		bg->setPosition(bgPoint); 
		addChild(bg);
	}
	else
	{
		m_AlertBg=SystemData::getSpriteByPlist("ui_float_menu_border");
		m_AlertBg->setAnchorPoint(ccp(0.5,0.5));
		m_AlertBg->setPosition(ccp(400,240));
		addChild(m_AlertBg);
	}
	
	m_Line=SystemData::getScale9SpriteByPlist("popalert.normal.sprite.line",m_AlertBg->getContentSize().width,3); 
	m_Line->setAnchorPoint(ccp(0.5,0.5));  
	m_Line->setPosition(ccp(m_AlertBg->getContentSize().width/2,m_AlertBg->getContentSize().height-90));  
	if (m_Type==Type_Small)
	{
		//m_Line->setPosition(ccp(m_AlertBg->getContentSize().width/2,m_AlertBg->getContentSize().height-80));  
	}
	m_AlertBg->addChild(m_Line); 
	m_Line->setVisible(false);
	/*
	//CCSize bigBgSize = SystemData::getLayoutSize("popalert.normal.bigbg");
	m_AlertBg=SystemData::getScale9SpriteByPlist("popalert.normal.bigbg",m_Size.width,m_Size.height);
	m_AlertBg->setAnchorPoint(ccp(0.5,0.5));
	m_AlertBg->setPosition(ccp(400,240));
	addChild(m_AlertBg);
	 
	CCSize titleSize = SystemData::getLayoutSize("popalert.normal.titlebg");
	CCScale9Sprite* titleBg=SystemData::getScale9SpriteByPlist("popalert.normal.titlebg",m_Size.width,titleSize.height);
	titleBg->setAnchorPoint(ccp(0,1));
	titleBg->setPosition(ccp(0,m_Size.height));
	m_AlertBg->addChild(titleBg);
	*/
}
void PopAlertPanel::showLine(bool lineVisible)
{
	if (m_Line)
	{
		m_Line->setVisible(lineVisible);
	}
}
void PopAlertPanel::initLabels()
{
	/*
	m_LabelPage =  SystemData::getLabelTTF("guild.browse.title.page");
	m_LabelPage->setColor(ccWHITE);
	m_LabelPage->setFontSize(15);   
	m_LabelPage->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(m_LabelPage); 
	*/
	m_Title =  SystemData::getLabelTTF("popalert.normal.label.title"); 
	m_Title->setColor(ccYELLOW);
	m_Title->setFontSize(22);    
	m_Title->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_Title->setDimensions(CCSizeMake(SystemData::getLayoutValue("popalert.normal.label.title.w"),SystemData::getLayoutValue("popalert.normal.label.title.h")));
	//addChild(m_Title); 
	m_Title->setAnchorPoint(ccp(0.5,1));
	m_Title->setPosition(ccp(m_AlertBg->getContentSize().width/2,m_AlertBg->getContentSize().height-10));
	m_AlertBg->addChild(m_Title);

	m_LabelInfo =  SystemData::getLabelTTF("popalert.normal.label.alert"); 
	m_LabelInfo->setColor(ccWHITE);
	m_LabelInfo->setFontSize(18);    
	m_LabelInfo->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_LabelInfo->setDimensions(CCSizeMake(SystemData::getLayoutValue("popalert.normal.label.alert.w"),SystemData::getLayoutValue("popalert.normal.label.alert.h")));
	m_LabelInfo->setAnchorPoint(ccp(0.5,0.5));
	m_LabelInfo->setPosition(ccp(m_AlertBg->getContentSize().width/2,m_AlertBg->getContentSize().height/2));
	m_AlertBg->addChild(m_LabelInfo); 
}

void PopAlertPanel::initButtons()
{
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("popalert.normal.button.close");
	pClose->setTag(Tag_Close);
	pClose->setTarget(this,menu_selector(PopAlertPanel::MenuCallBack));
	//pClose->setAnchorPoint(ccp(1,1));
	//pClose->setPosition(ccp(m_Size.width,m_Size.height));
	pClose->setPosition(ccp(m_AlertBg->getContentSize().width-25,m_AlertBg->getContentSize().height-25));
	m_pMainMenu->addChild(pClose);

	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("activity.button.frame",100,45);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",100,45);
	m_MenuConfirm =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(PopAlertPanel::MenuCallBack));
	if(m_MenuConfirm)
	{
		m_ConfirmTitle=SystemData::getLabelTTF("popalert.normal.button.confirm.text");
		m_ConfirmTitle->setFontSize(18);
		m_ConfirmTitle->setColor(ccWHITE);
		m_MenuConfirm->setTag(Tag_Confirm);
		m_MenuConfirm->setPosition(ccp(m_AlertBg->getContentSize().width/(2*m_OptionCount),m_AlertBg->getContentSize().height/8));
		m_ConfirmTitle->setPosition(m_MenuConfirm->getPosition());
		m_pMainMenu->addChild(m_MenuConfirm);
		m_pMainMenu->addChild(m_ConfirmTitle);
		
		if (m_Type==Type_Big)
		{
			m_MenuConfirm->setPositionY(m_MenuConfirm->getPositionY()-10);
			m_ConfirmTitle->setPosition(m_MenuConfirm->getPosition());
		}
		
	}

	CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("activity.button.frame",100,45);
	CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",100,45);
	m_MenuCancel =CCMenuItemSprite::create(p3,pSel3,NULL,this,menu_selector(PopAlertPanel::MenuCallBack));
	if(m_MenuCancel)
	{
		m_CancelTitle=SystemData::getLabelTTF("popalert.normal.button.cancel.text");
		m_CancelTitle->setFontSize(18);
		m_CancelTitle->setColor(ccWHITE);
		m_MenuCancel->setTag(Tag_Cancel);
		m_MenuCancel->setPosition(ccp(m_OptionCount==1?9999:m_AlertBg->getContentSize().width/4*3,m_AlertBg->getContentSize().height/8));
		m_CancelTitle->setPosition(m_MenuCancel->getPosition());
		m_pMainMenu->addChild(m_MenuCancel);
		m_pMainMenu->addChild(m_CancelTitle);
		
		if (m_Type==Type_Big)
		{
			m_MenuCancel->setPositionY(m_MenuCancel->getPositionY()-10);
			m_CancelTitle->setPosition(m_MenuCancel->getPosition());
		}
		
	}
}

void PopAlertPanel::initCell(CCTableViewCell *cell)
{
	if (m_selIndex==cell->getIdx())
	{
		//tableCellTouched(m_pTableView,cell);//这里需要修复滑动重现之后的cell标记消失的bug
	}
	CCLabelTTF* tRank = SystemData::getLabelTTF("guild.browse.title.rank");
	tRank->setPosition(ccp(tRank->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tRank->setColor(ccWHITE);
	tRank->setFontSize(18);
	tRank->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tRank);

	CCLabelTTF* tName = SystemData::getLabelTTF("guild.browse.title.name");
	tName->setPosition(ccp(tName->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tName->setColor(ccWHITE);
	tName->setFontSize(18);     
	tName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tName);

	CCLabelTTF* tMaster = SystemData::getLabelTTF("guild.browse.title.master");
	tMaster->setPosition(ccp(tMaster->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tMaster->setColor(ccWHITE);
	tMaster->setFontSize(18);   
	tMaster->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tMaster);

	CCLabelTTF* tNum = SystemData::getLabelTTF("guild.browse.title.num");
	tNum->setPosition(ccp(tNum->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tNum->setColor(ccWHITE);
	tNum->setFontSize(18);   
	tNum->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tNum);

	CCLabelTTF* tRelation = SystemData::getLabelTTF("guild.browse.title.relation");
	tRelation->setPosition(ccp(tRelation->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tRelation->setColor(ccWHITE);
	tRelation->setFontSize(18);   
	tRelation->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tRelation);

	CCLabelTTF* tStatus = SystemData::getLabelTTF("guild.browse.title.status");
	tStatus->setPosition(ccp(tStatus->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tStatus->setColor(ccWHITE);
	tStatus->setFontSize(18);   
	tStatus->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tStatus);
}
void PopAlertPanel::setConfirmTarget(CCObject *rec, SEL_MenuHandler selector)
{
	m_pListener = rec;
    m_pfnSelector = selector;
}
void PopAlertPanel::handleConfirmPressed()
{
	if (m_pListener && m_pfnSelector)
    {
		 (m_pListener->*m_pfnSelector)(this);
	}
}
void PopAlertPanel::setCancelTarget(CCObject *rec, SEL_MenuHandler selector)
{
	m_CancelListener = rec;
	m_CancelSelector = selector;
}
void PopAlertPanel::handleCancelPressed()
{
	if (m_CancelListener && m_CancelSelector)
	{
		(m_CancelListener->*m_CancelSelector)(this);
	}
}
void PopAlertPanel::setString(std::string alert)
{
	if (m_LabelInfo)
	{
		m_LabelInfo->setString(alert.c_str());
	}
}
void PopAlertPanel::setConfirmTitle(std::string cTitle)
{
	if (m_ConfirmTitle)
	{
		m_ConfirmTitle->setString(cTitle.c_str());
		if (m_MenuConfirm)
		{
			float pWidth = m_ConfirmTitle->getContentSize().width;
			pWidth=(pWidth<80)?100:(pWidth+20);
			CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("activity.button.frame",pWidth,45); 
			CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",pWidth,45);
			m_MenuConfirm->setNormalImage(p3);
			m_MenuConfirm->setSelectedImage(pSel3);
		}
	}
}
void PopAlertPanel::setCancelTitle(std::string cTitle)
{
	if (m_CancelTitle)
	{
		m_CancelTitle->setString(cTitle.c_str());
		if (m_MenuCancel)
		{
			float pWidth = m_CancelTitle->getContentSize().width;
			pWidth=(pWidth<80)?100:(pWidth+20);
			CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("activity.button.frame",pWidth,45);
			CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",pWidth,45);
			m_MenuCancel->setNormalImage(p3);
			m_MenuCancel->setSelectedImage(pSel3);
		}
	}
}
void PopAlertPanel::setTitle(std::string cTitle)
{
	if (m_Title)
	{
		m_Title->setString(cTitle.c_str());
	}
}
bool PopAlertPanel::isPressConfirm()
{
	return m_PressConfirm;
}
void PopAlertPanel::addSubView(CCNode* pChild)
{
	if(!m_AlertBg||!pChild)
		return;
	m_AlertBg->addChild(pChild);
}
CCNode* PopAlertPanel::getSubViewByTag(int tag)
{
	return m_AlertBg;
}
