#include "PopPullDownPanel.h"
#include "GuildPanel.h"
#include "GuildModule.h"
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
#include "userdata/LayoutData.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "event/CPEventHelper.h"
#include "userdata/GuildData.h"
#include "MsgGuild.h"

//-----------------------------------------------------------------------------------------------------------//


PopPullDownPanel::PopPullDownPanel():
	m_LabelInfo(NULL),
	m_LabelPage(NULL),
	m_selIndex(-1),
	m_Show(false),
	m_pTipTable(NULL),
	m_pLabel(NULL),
	m_Pid(0)
{

}

PopPullDownPanel::~PopPullDownPanel()
{

}

PopPullDownPanel* PopPullDownPanel::create()
{
	PopPullDownPanel* pPanel = new PopPullDownPanel();
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


bool PopPullDownPanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}
	/*
	m_nHeight = SystemData::size_y+1000;
	m_nWidth = SystemData::size_x+1000;

	addCover(ccp(-1000,-1000));
	*/
	m_Size =  SystemData::getLayoutSize("poppulldown.normal.button");
	initFrame();

	//initLabels();
	//initButtons();
	
	return true;
}



void PopPullDownPanel::MenuCallBack( CCObject* pSender )
{
	
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		
		if (m_Show)
		{
			PullUp();
		}
		else
		{
			PullDown();
		}
	}
	
}
/*
cocos2d::CCSize PopPullDownPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutSize("guild.browse.tablebg").width, 45); 
}

cocos2d::extension::CCTableViewCell* PopPullDownPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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

unsigned int PopPullDownPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 6;
}

void PopPullDownPanel::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
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
*/
void PopPullDownPanel::initFrame()
{
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("poppulldown.normal.button.frame",m_Size.width,m_Size.height);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("poppulldown.normal.button.frame.sel",m_Size.width,m_Size.height);
	CCMenuItemSprite *pNicknamebutton =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));
	if(pNicknamebutton)
	{
		m_pLabel=SystemData::getLabelTTF("poppulldown.normal.text");
		m_pLabel->setFontSize(18); 
		m_pLabel->setColor(ccWHITE); 
		m_pLabel->setHorizontalAlignment(kCCTextAlignmentCenter); 
		//pNicknamebutton->setTag(TAG_GUILDINFO);
		pNicknamebutton->setPosition(ccp(0,0/*pLabel->getPositionX(),cellSizeForTable(m_pTableView).height/2*/));
		m_pLabel->setPosition(ccp(-10,0/*pNicknamebutton->getPositionX()-10,pNicknamebutton->getPositionY()*/));

		m_Arrow = SystemData::getSpriteByPlist("poppulldown.normal.arrow");
		m_Arrow->setPosition(ccp(m_Size.width*0.88f,m_Size.height*0.5f));
		m_Arrow->setAnchorPoint(ccp(0.5,0.5));
		m_Arrow->setFlipY(true);
		pNicknamebutton->addChild(m_Arrow);
		
		GeneralMenu* cellMenu = GeneralMenu::create();
		cellMenu->setPosition(CCPointZero);
		cellMenu->setAnchorPoint(CCPointZero);
		addChild(cellMenu);
		
		cellMenu->addChild(pNicknamebutton);
		cellMenu->addChild(m_pLabel);
	}
}

void PopPullDownPanel::initCell(CCTableViewCell *cell)
{
	/*
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
	*/
}

void PopPullDownPanel::PullDown()
{
	CCPoint worldPoint = this->getParent()->convertToWorldSpace(this->getPosition());
	worldPoint.x = worldPoint.x-m_Size.width/2;
	worldPoint.y = worldPoint.y-m_Size.height/2;
	CCLog("__________droid1_____worldpoint(%f,%f)",worldPoint.x,worldPoint.y);
	/*
	CCPoint pPlacardPoint = SystemData::getLayoutPoint("guild.browse.tablebg");
	m_pTableView = CCTableViewEx::create(this,CCSizeMake(m_Size.width,20*6),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setAnchorPoint(ccp(0,1));//setAnchorPoint(CCPointZero);	
	m_pTableView->setPosition(ccp(0,0));//setPosition(ccp(pPlacardPoint.x,pPlacardPoint.y));
	//m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	addChild(m_pTableView);      
	*/
	//showTipTable(worldPoint);
	GuildData::setNicknameTipPostion(worldPoint);
	GuildData::setNicknameSelectPid(m_Pid);
	CPEventHelper::uiNotify("UIShowMemberNicknameTipTable", "", 0);
	//arrow
	//m_Arrow->setFlipY(false);____droid________

	setShowMode(true);
}
void PopPullDownPanel::PullUp()
{
	//m_pTableView->removeFromParentAndCleanup(true);
	//m_pTableView = NULL;
	CPEventHelper::uiNotify("UIHideMemberNicknameTipTable", "", 0);
	//arrow
	//m_Arrow->setFlipY(true);____droid________
	//hideTipTable();
	setShowMode(false);
}
void PopPullDownPanel::setShowMode(bool mShow)
{
	m_Show = mShow;
}
void PopPullDownPanel::showTipTable(CCPoint curPoint)
{
	if (m_pTipTable)
	{
		m_pTipTable->removeFromParentAndCleanup(true);
		m_pTipTable = NULL;
	}
	CCPoint pPlacardPoint = SystemData::getLayoutPoint("guild.browse.tablebg");
	m_pTipTable = PopPullDownTable::create();//(this,CCSizeMake(m_Size.width,20*6),kCCScrollViewDirectionVertical,this,NULL);
	m_pTipTable->setAnchorPoint(ccp(0,1));//setAnchorPoint(CCPointZero);	
	m_pTipTable->setPosition(CCPointZero);
	//m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTipTable->setData("");
	addChild(m_pTipTable);   
}
void PopPullDownPanel::hideTipTable()
{
	if (m_pTipTable)
	{
		m_pTipTable->removeFromParentAndCleanup(true);
		m_pTipTable = NULL;
	}
}
void PopPullDownPanel::setNickname(int job)
{
	if (m_pLabel)
	{
		m_pLabel->setString(GuildData::getGuildNickname(job).c_str());
	}
}
void PopPullDownPanel::setOwnerPID(int mPid)
{
	m_Pid = mPid;
}
//-----------------------------------------------------------------------------------------------------------//


PopPullDownTable::PopPullDownTable():
	m_selIndex(-1),
	m_Show(false),
	m_pTableView(NULL),
	m_TitlePanel(NULL)
{

}

PopPullDownTable::~PopPullDownTable()
{

}

PopPullDownTable* PopPullDownTable::create()
{
	PopPullDownTable* pPanel = new PopPullDownTable();
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


bool PopPullDownTable::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}
	
// 	m_nHeight = SystemData::size_y+1000;
// 	m_nWidth = SystemData::size_x+1000;
// 
// 	addCover(ccp(-1000,-1000));

	m_Size =  SystemData::getLayoutSize("poppulldown.normal.button");
	initFrame();
	
	this->setTouchEnabled(true);
	return true;
}



void PopPullDownTable::MenuCallBack( CCObject* pSender )
{
	
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		
		
	}
	
}

cocos2d::CCSize PopPullDownTable::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(m_Size/*SystemData::getLayoutSize("guild.browse.tablebg")*/.width, m_Size.height); 
}

cocos2d::extension::CCTableViewCell* PopPullDownTable::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		/*
		CCMenuEx* pMenu = CCMenuEx::create(NULL,NULL);
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);
		*/
		initCell(cell);
	}
	loadCell(cell,idx);
	return cell;
}

unsigned int PopPullDownTable::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return m_data.size();
}

void PopPullDownTable::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
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

	int pid = GuildData::getNicknameSelectPid();
	if (pid)
	{
		//select
		//send msg
		MsgGuildMemberNicknameChangeRequest* req = new MsgGuildMemberNicknameChangeRequest();
		req->pid = pid;
		req->nickname = m_selIndex;
		HandleMessage::sendMessage(req);

		GuildData::changeMemberNickname(m_selIndex);
		CPEventHelper::uiNotify("UIHideMemberNicknameTipTable", "", 0);
	}
	
}

void PopPullDownTable::initFrame()
{
	CCPoint pPlacardPoint = SystemData::getLayoutPoint("guild.browse.tablebg");
	m_pTableView = CCTableViewEx::create(this,CCSizeMake(m_Size.width,m_Size.height*GuildData::getGuildNicknameCnt()),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setAnchorPoint(ccp(0,0));
	int height = this->getContentSize().height;
	m_pTableView->setPosition(ccp(0,0));//setPosition(ccp(pPlacardPoint.x,pPlacardPoint.y));
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	//m_pTableView->setBounceable(false);
	addChild(m_pTableView);      
	/*
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("poppulldown.normal.button.frame",m_Size.width,m_Size.height);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("poppulldown.normal.button.frame.sel",m_Size.width,m_Size.height);
	CCMenuItemSprite *pNicknamebutton =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));
	if(pNicknamebutton)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("poppulldown.normal.text");
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE); 
		pLabel->setHorizontalAlignment(kCCTextAlignmentCenter); 
		//pNicknamebutton->setTag(TAG_GUILDINFO);
		pNicknamebutton->setPosition(ccp(0,0));
		pLabel->setPosition(ccp(-10,0));
	}
	*/
}
void PopPullDownTable::initLabels()
{
	CCLabelTTF* tRank = SystemData::getLabelTTF("guild.browse.title.rank");
	tRank->setColor(ccWHITE);
	tRank->setFontSize(18);
	tRank->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tRank);
}

void PopPullDownTable::initButtons()
{
	/*
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.button",100,45);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,45);
	CCMenuItemSprite *pDetail =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(PopPullDownPanel::MenuCallBack));//行会信息按钮
	if(pDetail)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.button.detail.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		//pDetail->setTag(TAG_GUILDINFO);
		pDetail->setPosition(SystemData::getLayoutPoint("guild.browse.button.detail"));
		pLabel->setPosition(pDetail->getPosition());
		m_pMainMenu->addChild(pDetail);
		m_pMainMenu->addChild(pLabel);
	}
	*/
}

void PopPullDownTable::initCell(CCTableViewCell *cell)
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
	tRank->setTag(Cell_Nickname);

	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("poppulldown.normal.button.frame",m_Size.width,m_Size.height);
	p1->setPosition(ccp(tRank->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	cell->addChild(p1);

	cell->addChild(tRank);
	/*/------------------------------
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("poppulldown.normal.button.frame",m_Size.width,m_Size.height);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("poppulldown.normal.button.frame.sel",m_Size.width,m_Size.height);
	CCMenuItemSprite *pNicknamebutton =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));
	if(pNicknamebutton)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("poppulldown.normal.text");
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE); 
		pLabel->setHorizontalAlignment(kCCTextAlignmentCenter); 
		//pNicknamebutton->setTag(TAG_GUILDINFO);
		pNicknamebutton->setPosition(ccp(0,0));
		pLabel->setPosition(ccp(-10,0));

		m_Arrow = SystemData::getSprite("poppulldown.normal.arrow");
		m_Arrow->setPosition(ccp(m_Size.width*0.88f,m_Size.height*0.5f));
		m_Arrow->setAnchorPoint(ccp(0.5,0.5));
		m_Arrow->setFlipY(true);
		pNicknamebutton->addChild(m_Arrow);

		GeneralMenu* cellMenu = GeneralMenu::create();
		cellMenu->setPosition(CCPointZero);
		cellMenu->setAnchorPoint(CCPointZero);
		cell->addChild(cellMenu);

		cellMenu->addChild(pNicknamebutton);
		cellMenu->addChild(pLabel);
	}
	*/
}
void PopPullDownTable::loadCell(CCTableViewCell *cell,unsigned int idx)
{
	CCLabelTTF* tJob = (CCLabelTTF*)cell->getChildByTag(Cell_Nickname);

		if (idx<m_data.size())
		{
			tJob->setString(m_data[idx].c_str());
		}
}
void PopPullDownTable::setData(std::string vkey)
{
	//set vector
	int cnt = GuildData::getGuildNicknameCnt();
	for (int i=0;i<cnt;i++)
	{
		int job = GuildData::getGuildNicknameJob(i);
		m_data.push_back(GuildData::getGuildNickname(job));
	}
	m_pTableView->reloadData();
}
void PopPullDownTable::setTitlePanel(BasePanel* mPanel)
{
	m_TitlePanel = mPanel;
}
void PopPullDownTable::registerWithTouchDispatcher()
{
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
bool PopPullDownTable::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//this->setVisible(false);
	
	CPEventHelper::uiNotify("UIHideMemberNicknameTipTable", "", 0);
	/*
	PopPullDownPanel* mPanel = (PopPullDownPanel*)m_TitlePanel;
	if (mPanel)
	{
		mPanel->setShowMode(false);
	}
	*/
	
	return true;
}