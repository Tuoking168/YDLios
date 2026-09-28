#include "GuildBrowsePanel.h"
#include "GuildPanel.h"
#include "GuildModule.h"
#include "GuildDefinition.h"
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
#include "scene/LoginHelper.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/LayoutData.h"
#include "Userdata/StaticData.h"
#include "MsgGuild.h"
#include "userdata/NPCFunctionData.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "controls/CPChecker.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "ModuleData.h"
#include "userdata/GuildData.h"
#include "PopAlertPanel.h"
#include "ext/TextField.h"
#include "utils/StringUtils.h"

#include "GuildPanel.h"
//-----------------------------------------------------------------------------------------------------------//


GuildBrowsePanel::GuildBrowsePanel():
	m_pMainMenu(NULL),
	m_pLeftMenu(NULL),
	m_iCurrentType(-1),
	m_pRightMenu(NULL),
	mHeight(0),
	m_iCurrentQuestID(0),
	m_pInfo(NULL),
	m_pCurrentQuestSprite(NULL),
	m_LabelInfo(NULL),
	m_LabelPage(NULL),
	m_selIndex(-1)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

GuildBrowsePanel::~GuildBrowsePanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

GuildBrowsePanel* GuildBrowsePanel::create()
{
	GuildBrowsePanel* pPanel = new GuildBrowsePanel();
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


bool GuildBrowsePanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false; 
	}

	initFrame();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	m_pLeftMenu = GeneralMenu::create();
	m_pLeftMenu->setPosition(CCPointZero);
	m_pLeftMenu->setAnchorPoint(CCPointZero);
	addChild(m_pLeftMenu);

	m_pRightMenu= GeneralMenu::create();
	m_pRightMenu->setPosition(CCPointZero);
	m_pRightMenu->setAnchorPoint(CCPointZero);
	addChild(m_pRightMenu);

	initLabels();
	initButtons();
	
	CCSize pPlacardSize = CCSizeMake(SystemData::getLayoutValue("guild.browse.tablebg.w"),SystemData::getLayoutValue("guild.browse.tablebg.h"));
	CCPoint pPlacardPoint = SystemData::getLayoutPoint("guild.browse.tablebg");
	m_pTableView = CCTableViewEx::create(this,CCSizeMake(pPlacardSize.width,pPlacardSize.height-60),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setAnchorPoint(CCPointZero);	
	m_pTableView->setPosition(ccp(pPlacardPoint.x,pPlacardPoint.y+60));
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setBounceable(false);
	addChild(m_pTableView);  

	loadGuildsHomePage();

	return true; 
}

void GuildBrowsePanel::loadGuildDetailView()
{
	PopAlertPanel* alert = PopAlertPanel::create(PopAlertPanel::Type_Big);
	alert->setConfirmTitle(SystemData::getLayoutString("popalert.changenickname.left"));
	alert->setCancelTitle(SystemData::getLayoutString("popalert.changenickname.right"));
	addChild(alert);
}

void GuildBrowsePanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==Tag_Detail)
		{
			if (m_selIndex<0)
			{
				return;
			}	
			GuildDetailPanel* panel = GuildDetailPanel::create(m_selIndex);
			addChild(panel);
		}
		else if (tag==Tag_Alliance)
		{
			CPEventHelper::uiNotify("", "", 90);
		}
		else if(tag==Tag_Combat)
		{			
			CPEventHelper::uiNotify("", "", 90);
		}
		else if(tag==Tag_Filter)
		{
			
		}
		else if(tag==Tag_Apply)
		{	
			if (m_selIndex<0)
			{
				return;
			}
			MsgApplicationToGuildRequest* req = new MsgApplicationToGuildRequest();
			req->GuildID = GuildData::getGuildID(GuildData::getRankByIndex(m_selIndex));
			HandleMessage::sendMessage(req);
		}
		else if (tag == Tag_Cancel_Apply)
		{
			int rank = GuildData::getRankByIndex(m_selIndex);
			if (GuildData::getGuildState(rank) ==
				GuildType::state_not_apply)
			{
				CPEventHelper::uiNotify("", "", 942);
			}
			else
			{
				MsgCancelApplicationToGuildRequest* request =
					new MsgCancelApplicationToGuildRequest();
				request->GuildID = GuildData::getGuildID(rank);
				HandleMessage::sendMessage(request);
			}
		}
		else if(tag==Tag_Add)
		{	
			createGuild();
		}
		else if(tag==Tag_Page_Home)
		{
			loadGuildsHomePage();
		}
		else if(tag==Tag_Page_End)
		{
			loadGuildsEndPage();
		}
		else if(tag==Tag_Page_Up)
		{
			loadGuildsPageUp();
		}
		else if(tag==Tag_Page_Down)
		{
			loadGuildsPageDown();
		}
		else if(tag == Alert_Create_Guild)
		{
			CCEditBox* textfield = (CCEditBox*)pNode->getChildByTag(Alert_Create_Guild);
			if (!textfield)
			{
				return;
			}
			std::string outStr;
			if (LoginHelper::testCreateName(textfield->getText(), outStr))
			{
				MsgCreateGuildRequest* req = new MsgCreateGuildRequest();
				req->GuildName = outStr;
				HandleMessage::sendMessage(req);
			}
		}
	}
	
}

cocos2d::CCSize GuildBrowsePanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutSize("guild.browse.tablebg").width, 45); 
}

cocos2d::extension::CCTableViewCell* GuildBrowsePanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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

unsigned int GuildBrowsePanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return GuildData::getGuildCnt();
}

void GuildBrowsePanel::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
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

void GuildBrowsePanel::CloseSelf(CCObject* pSender)
{
	Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);	
}

void GuildBrowsePanel::handleEvent( int channel )
{	
	if(channel == EventProtocol::EVENT_TASK_RECEIVED)
	{
		//CCLog("Event Recieve");
	}
}

void GuildBrowsePanel::initFrame()
{
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",SystemData::getLayoutValue("guild.bg.w"),SystemData::getLayoutValue("guild.bg.h"));
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(SystemData::getLayoutPoint("guild.bg"));
	addChild(bg);
	//提示信息
	CCScale9Sprite *infoview=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.browse.infoview.w"),SystemData::getLayoutValue("guild.browse.infoview.h"));
	infoview->setAnchorPoint(CCPointZero);
	infoview->setPosition(SystemData::getLayoutPoint("guild.browse.infoview"));
	addChild(infoview);
	//表格头
	CCScale9Sprite *headerview=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.browse.headerview.w"),SystemData::getLayoutValue("guild.browse.headerview.h"));
	headerview->setAnchorPoint(CCPointZero);
	headerview->setPosition(SystemData::getLayoutPoint("guild.browse.headerview"));
	addChild(headerview);
	//右侧框
	CCScale9Sprite *pRightborder=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.browse.rightbg.w"),SystemData::getLayoutValue("guild.browse.rightbg.h"));
	pRightborder->setAnchorPoint(CCPointZero);  
	pRightborder->setPosition(SystemData::getLayoutPoint("guild.browse.rightbg")); 
	addChild(pRightborder);	
	//列表背景
	CCScale9Sprite *pTable=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.browse.tablebg.w"),SystemData::getLayoutValue("guild.browse.tablebg.h"));
	pTable->setAnchorPoint(CCPointZero);  
	pTable->setPosition(SystemData::getLayoutPoint("guild.browse.tablebg")); 
	addChild(pTable);	
}

void GuildBrowsePanel::initLabels()
{
	CCLabelTTF* tRank = SystemData::getLabelTTF("guild.browse.title.rank");
	tRank->setColor(ccWHITE);
	tRank->setFontSize(18);
	tRank->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tRank);

	CCLabelTTF* tName = SystemData::getLabelTTF("guild.browse.title.name");
	tName->setColor(ccWHITE);
	tName->setFontSize(18);     
	tName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tName);

	CCLabelTTF* tMaster = SystemData::getLabelTTF("guild.browse.title.master");
	tMaster->setColor(ccWHITE);
	tMaster->setFontSize(18);   
	tMaster->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tMaster);

	CCLabelTTF* tNum = SystemData::getLabelTTF("guild.browse.title.num");
	tNum->setColor(ccWHITE);
	tNum->setFontSize(18);   
	tNum->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tNum);

	CCLabelTTF* tLevel = SystemData::getLabelTTF("guild.browse.title.level");
	tLevel->setColor(ccWHITE);
	tLevel->setFontSize(18);   
	tLevel->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tLevel);

	CCLabelTTF* tStatus = SystemData::getLabelTTF("guild.browse.title.status");
	tStatus->setColor(ccWHITE);
	tStatus->setFontSize(18);   
	tStatus->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tStatus);

	m_LabelPage =  SystemData::getLabelTTF("guild.browse.title.page");  
	m_LabelPage->setColor(ccWHITE); 
	m_LabelPage->setFontSize(15);   
	m_LabelPage->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(m_LabelPage); 

	m_LabelInfo =  SystemData::getLabelTTF("guild.browse.title.info");      

	m_LabelInfo->setColor(ccWHITE);
	m_LabelInfo->setFontSize(18);   
	m_LabelInfo->setHorizontalAlignment(kCCTextAlignmentLeft);
	m_LabelInfo->setDimensions(CCSizeMake(SystemData::getLayoutValue("guild.browse.infoview.w"),SystemData::getLayoutValue("guild.browse.infoview.h")));
	addChild(m_LabelInfo); 
}

void GuildBrowsePanel::initButtons()
{
	std::string tail = "";
	if (GuildData::hasGuild())
	{
		tail = ".hasguild";
	}
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.button",100,45);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,45);
	CCMenuItemSprite *pDetail =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(GuildBrowsePanel::MenuCallBack));//行会信息按钮
	if(pDetail)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.button.detail.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pDetail->setTag(Tag_Detail);
		pDetail->setPosition(SystemData::getLayoutPoint("guild.browse.button.detail"+tail));
		pLabel->setPosition(pDetail->getPosition());
		m_pMainMenu->addChild(pDetail);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("guild.info.button",100,45);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,45);
	CCMenuItemSprite *pAlliance =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(GuildBrowsePanel::MenuCallBack));
	if(pAlliance && GuildData::hasGuild())
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.button.alliance.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pAlliance->setTag(Tag_Alliance);
		pAlliance->setPosition(SystemData::getLayoutPoint("guild.browse.button.alliance"+tail));
		pLabel->setPosition(pAlliance->getPosition());
		m_pMainMenu->addChild(pAlliance);
		m_pMainMenu->addChild(pLabel);

		if (!GuildData::hasGuild())
		{
			pAlliance->setVisible(false);
			pLabel->setVisible(false);
		}
	}

	// 取消申请按钮
	if (!GuildData::hasGuild())
	{	
		CCMenuItemSprite* cancelApplyBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "cancelApply");
		cancelApplyBtn->setTarget(this, menu_selector(GuildBrowsePanel::MenuCallBack));
		cancelApplyBtn->setTag(Tag_Cancel_Apply);
		m_pMainMenu->addChild(cancelApplyBtn);
		
	}

	CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("guild.info.button",100,45);
	CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,45);
	CCMenuItemSprite *pCombat =CCMenuItemSprite::create(p3,pSel3,NULL,this,menu_selector(GuildBrowsePanel::MenuCallBack));//行会信息按钮
	if(pCombat && GuildData::hasGuild())
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.button.combat.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pCombat->setTag(Tag_Combat);
		pCombat->setPosition(SystemData::getLayoutPoint("guild.browse.button.combat"+tail));
		pLabel->setPosition(pCombat->getPosition());
		m_pMainMenu->addChild(pCombat);
		m_pMainMenu->addChild(pLabel);
	}
	
	CCScale9Sprite* p10=SystemData::getScale9SpriteByPlist("guild.info.button",100,45);
	CCScale9Sprite* pSel10=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,45);
	CCMenuItemSprite *pApply =CCMenuItemSprite::create(p10,pSel10,NULL,this,menu_selector(GuildBrowsePanel::MenuCallBack));
	if(pApply)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.button.apply.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pApply->setTag(Tag_Apply); 
		pApply->setPosition(SystemData::getLayoutPoint("guild.browse.button.apply"+tail));
		pLabel->setPosition(pApply->getPosition());
		m_pMainMenu->addChild(pApply);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p9=SystemData::getScale9SpriteByPlist("guild.info.button",100,45);
	CCScale9Sprite* pSel9=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,45);
	CCMenuItemSprite *pAdd =CCMenuItemSprite::create(p9,pSel9,NULL,this,menu_selector(GuildBrowsePanel::MenuCallBack));
	if(pAdd)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.button.add.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pAdd->setTag(Tag_Add); 
		pAdd->setPosition(SystemData::getLayoutPoint("guild.browse.button.add"+tail));
		pLabel->setPosition(pAdd->getPosition());
		m_pMainMenu->addChild(pAdd);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p5=SystemData::getScale9SpriteByPlist("guild.info.placard.button",80,35);
	CCScale9Sprite* pSel5=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",80,35);
	CCMenuItemSprite *pHomepage =CCMenuItemSprite::create(p5,pSel5,NULL,this,menu_selector(GuildBrowsePanel::MenuCallBack));//行会信息按钮
	if(pHomepage)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.button.homepage.text");
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		pHomepage->setTag(Tag_Page_Home);
		pHomepage->setPosition(SystemData::getLayoutPoint("guild.browse.button.homepage"));
		pLabel->setPosition(pHomepage->getPosition());
		m_pMainMenu->addChild(pHomepage);
		m_pMainMenu->addChild(pLabel);  
	}

	CCScale9Sprite* p6=SystemData::getScale9SpriteByPlist("guild.info.placard.button",80,35);
	CCScale9Sprite* pSel6=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",80,35);
	CCMenuItemSprite *pPageup =CCMenuItemSprite::create(p6,pSel6,NULL,this,menu_selector(GuildBrowsePanel::MenuCallBack));//行会信息按钮
	if(pPageup)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.button.pageup.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pPageup->setTag(Tag_Page_Up);
		pPageup->setPosition(SystemData::getLayoutPoint("guild.browse.button.pageup"));
		pLabel->setPosition(pPageup->getPosition());
		m_pMainMenu->addChild(pPageup);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p7=SystemData::getScale9SpriteByPlist("guild.info.placard.button",80,35);
	CCScale9Sprite* pSel7=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",80,35);
	CCMenuItemSprite *pPagedown =CCMenuItemSprite::create(p7,pSel7,NULL,this,menu_selector(GuildBrowsePanel::MenuCallBack));//行会信息按钮
	if(pPagedown)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.button.pagedown.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pPagedown->setTag(Tag_Page_Down);
		pPagedown->setPosition(SystemData::getLayoutPoint("guild.browse.button.pagedown"));
		pLabel->setPosition(pPagedown->getPosition());
		m_pMainMenu->addChild(pPagedown);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p8=SystemData::getScale9SpriteByPlist("guild.info.placard.button",80,35);
	CCScale9Sprite* pSel8=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",80,35);
	CCMenuItemSprite *pEndpage =CCMenuItemSprite::create(p8,pSel8,NULL,this,menu_selector(GuildBrowsePanel::MenuCallBack));//行会信息按钮
	if(pEndpage)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.button.endpage.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pEndpage->setTag(Tag_Page_End);
		pEndpage->setPosition(SystemData::getLayoutPoint("guild.browse.button.endpage"));
		pLabel->setPosition(pEndpage->getPosition());
		m_pMainMenu->addChild(pEndpage);
		m_pMainMenu->addChild(pLabel);
	}
}

void GuildBrowsePanel::initCell(CCTableViewCell *cell)
{
	CCLabelTTF* tRank = SystemData::getLabelTTF("guild.browse.title.rank");
	tRank->setPosition(ccp(tRank->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tRank->setTag(Tag_Rank);
	tRank->setColor(ccWHITE);
	tRank->setFontSize(18);
	tRank->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tRank);

	CCLabelTTF* tName = SystemData::getLabelTTF("guild.browse.title.name");
	tName->setPosition(ccp(tName->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tName->setTag(Tag_Name);
	tName->setColor(ccWHITE);
	tName->setFontSize(18);     
	tName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tName);

	CCLabelTTF* tMaster = SystemData::getLabelTTF("guild.browse.title.master");
	tMaster->setPosition(ccp(tMaster->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tMaster->setTag(Tag_Master);
	tMaster->setColor(ccWHITE);
	tMaster->setFontSize(18);   
	tMaster->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tMaster);

	CCLabelTTF* tNum = SystemData::getLabelTTF("guild.browse.title.num");
	tNum->setPosition(ccp(tNum->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tNum->setTag(Tag_Num);
	tNum->setColor(ccWHITE);
	tNum->setFontSize(18);   
	tNum->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tNum);

	CCLabelTTF* tLevel = SystemData::getLabelTTF("guild.browse.title.level");
	tLevel->setPosition(ccp(tLevel->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tLevel->setTag(Tag_Level);
	tLevel->setColor(ccWHITE);
	tLevel->setFontSize(18);
	tLevel->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tLevel);

	CCLabelTTF* tStatus = SystemData::getLabelTTF("guild.browse.title.status");
	tStatus->setPosition(ccp(tStatus->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tStatus->setTag(Tag_Status);
	tStatus->setColor(ccWHITE);
	tStatus->setFontSize(18);   
	tStatus->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tStatus);
}
void GuildBrowsePanel::loadCell(CCTableViewCell *cell,unsigned int idx)
{
	const int rank = GuildData::getRankByIndex(idx);
	const std::string &s_Rank = StringUtils::toString(rank);	
	CCLabelTTF* tRank = (CCLabelTTF*)cell->getChildByTag(Tag_Rank);
	tRank->setString(s_Rank.c_str());

	CCLabelTTF* tName = (CCLabelTTF*)cell->getChildByTag(Tag_Name);
	tName->setString(GuildData::getGuildName(rank).c_str());

	CCLabelTTF* tMaster = (CCLabelTTF*)cell->getChildByTag(Tag_Master);
	tMaster->setString(GuildData::getGuildMasterName(rank).c_str());

	const std::string &s_Num = StringUtils::toString(GuildData::getGuildMemberCount(rank));
	CCLabelTTF* tNum = (CCLabelTTF*)cell->getChildByTag(Tag_Num);
	tNum->setString(s_Num.c_str());

	const std::string &s_level = StringUtils::toString(GuildData::getGuildLevel(rank));
	CCLabelTTF* tLevel = (CCLabelTTF*)cell->getChildByTag(Tag_Level);
	tLevel->setString(s_level.c_str());

	std::string stateStr;
	int state = GuildData::getGuildState(rank);
	if (state == GuildType::state_apply)
		stateStr = LayoutData::getString(CPModuleName::GUILD, "hasApply");
	else
		stateStr = LayoutData::getString(CPModuleName::GUILD, "notApply");

	CCLabelTTF* tState = (CCLabelTTF*)cell->getChildByTag(Tag_Status);
	tState->setString(stateStr.c_str());
}
void GuildBrowsePanel::loadGuildsRequest(int vPage)
{
	MsgGetGuildsInfoRequest* req = new MsgGetGuildsInfoRequest();
	req->page = vPage;
	HandleMessage::sendMessage(req);
}
void GuildBrowsePanel::loadGuildsPageUp()
{
	int page = GuildData::getGuildPage()-1;
	if (page<=0)
	{
		CCLog("Error____________Page invalid");
		return;
	}
	loadGuildsRequest(page);
}
void GuildBrowsePanel::loadGuildsPageDown()
{
	int page = GuildData::getGuildPage()+1;
	int maxPage = GuildData::getGuildMaxPage();
	if (page>maxPage)
	{
		CCLog("Error____________Page invalid");
		return;
	}
	loadGuildsRequest(page);
}
void GuildBrowsePanel::loadGuildsHomePage()
{
	loadGuildsRequest(1);
}
void GuildBrowsePanel::loadGuildsEndPage()
{
	int maxPage = GuildData::getGuildMaxPage();
	if (maxPage<=0)
	{
		CCLog("Error____________Page invalid");
		return;
	}
	loadGuildsRequest(maxPage);
}
void GuildBrowsePanel::createGuild()
{
	CCSize alertSize = SystemData::getLayoutSize("popalert.normal.bigbg");
	PopAlertPanel* alert = PopAlertPanel::create();
	alert->setConfirmTarget(this,menu_selector(GuildBrowsePanel::MenuCallBack));
	alert->setTag(Alert_Create_Guild);
	addChild(alert);

	CCEditBox *ret = NULL;
	CCScale9Sprite *scaleSprite = CCScale9Sprite::createWithSpriteFrameName(SystemData::getLayoutString("guild.browse.label.guildname.inputframe").c_str());
	if (!scaleSprite)
	{
		scaleSprite = CCScale9Sprite::create(SystemData::getLayoutString("guild.browse.label.guildname.inputframe").c_str());
	}
	if (scaleSprite)
	{
		int maxlen = 0;
		StaticData::getGlobalData("guildNameMaxLen", maxlen);
		ret = CCEditBox::create(SystemData::getLayoutSize("guild.browse.label.guildname.inputframe"), scaleSprite);
		ret->setMaxLength(maxlen);
		ret->setPlaceHolder(SystemData::getLayoutString("guild.browse.label.guildname.inputframe.placeholder").c_str());
		ret->setFontName(SystemData::getLayoutString("guild.browse.label.guildname.inputframe.font").c_str());
		ret->setPlaceholderFontName(SystemData::getLayoutString("guild.browse.label.guildname.inputframe.font").c_str());
		ret->setFontSize(SystemData::getLayoutValue("guild.browse.label.guildname.inputframe.fontsize"));
		ret->setPlaceholderFontSize(SystemData::getLayoutValue("guild.browse.label.guildname.inputframe.fontsize"));
		ret->setAnchorPoint(ccp(0.5,0.5));
		ret->setPosition(SystemData::getLayoutPoint("guild.browse.label.guildname.inputframe"));
		ret->setTouchPriority(kCCMenuHandlerPriority);
		ret->setTag(Alert_Create_Guild); 
		alert->addChild(ret);
	}
	
	CCSprite* sprite = SystemData::getSpriteByPlist("activity.sprite.item.frame");
	CCPoint point = SystemData::getLayoutPoint("guild.browse.alert.itemframe"); 
	sprite->setAnchorPoint(CCPointZero);
	sprite->setPosition(point);
	alert->addChild(sprite);
	
	GeneralMenu* pMenu = GeneralMenu::create(); 
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);
	alert->addChild(pMenu); 

	int sid = SystemData::getLayoutValue("guild.browse.alert.itemsid");
	int cnt = SystemData::getLayoutValue("guild.browse.alert.itemcount"); 
	if (sid>0&&cnt>0)
	{ 
		UserItem* item = CommonFunction::createNewItem(sid);
		item->count = cnt;
		CCMenuItemImage* pItem=CommonFunction::getItemIcon(item);
		pItem->setPosition(ccp(point.x+33,point.y+33));
		pItem->setTarget(this,menu_selector(GuildBrowsePanel::itemCallBack));
		pMenu->addChild(pItem);
	} 

	CCSize size1 = SystemData::getLayoutSize("guild.browse.alert.infolabel"); 
	CPRichText* infoLabel=CPRichText::create(size1.width,size1.height); 
	CCPoint labelPoint1=SystemData::getLayoutPoint("guild.browse.alert.infolabel");
	infoLabel->setAnchorPoint(ccp(0.5,0.5));
	infoLabel->setPosition(labelPoint1); 
	alert->addChild(infoLabel);
	for (int i=0;i<3;i++) 
	{
		std::string pRichStr1 = SystemData::getLayoutString("guild.browse.alert.sublabel"+StringUtils::toString(i)+".text");
		int fontSize = SystemData::getLayoutValue("guild.browse.alert.sublabel"+StringUtils::toString(i)+".fontsize");
	 	CPRichTextItemLabel* pText1=new CPRichTextItemLabel(pRichStr1,"",fontSize,SystemData::getLayoutColor3B("guild.browse.alert.sublabel"+StringUtils::toString(i)));
	 	infoLabel->addItem(pText1);
	}
}
void GuildBrowsePanel::showTooltip(CCMenuItem* pImage)
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
void GuildBrowsePanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}
void GuildBrowsePanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageCreateGuildResponse")
		{
			if (CPEventHelper::isRequestSuccess())
			{
				CPEventHelper::uiNotify("SwitchGuildInfo", "", 0);
			}
		}
		else if(source == "HandleMessageGuildsInfoResponse")
		{
			if (m_LabelPage)
			{
				CCString* sPage = CCString::createWithFormat("%d/%d",GuildData::getGuildPage(),GuildData::getGuildMaxPage());
				m_LabelPage->setString(sPage->getCString());
			}
			m_pTableView->reloadData();
			int num = numberOfCellsInTableView(m_pTableView);
			if (num > 0)
			{
				if (m_selIndex < 0)
					m_selIndex = 0;

				if (m_selIndex >= num)
					m_selIndex = num - 1;

				tableCellTouched(m_pTableView, m_pTableView->cellAtIndex(m_selIndex));
			}
			
		}
		else if (source == "HandleMessageApplicationToGuildResponse" ||
			source == "HandleMessageCancelApplicationToGuildResponse")
		{
			loadGuildsRequest(GuildData::getGuildPage());
		}
		
	}
}

/////////////GuildDetailPanel/////////////////////////////////////////////
GuildDetailPanel::GuildDetailPanel()
	:m_pMainMenu(NULL)
	,m_selIndex(-1)
	,m_background(NULL)
	,mChecker(NULL)
	,m_GuildName(NULL)
	,m_GuildCount(NULL)
	,m_GuildMaster(NULL)
	,m_GuildStatus(NULL)
	,m_GuildPlacard(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

GuildDetailPanel::~GuildDetailPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

GuildDetailPanel* GuildDetailPanel::create(int tag)
{
	GuildDetailPanel* pPanel = new GuildDetailPanel();
	if(pPanel && pPanel->init(tag))
	{
		pPanel->autorelease();
		return pPanel;
	}
	CC_SAFE_DELETE(pPanel);
	return NULL; 
}

bool GuildDetailPanel::init( int tag)
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_selIndex = tag;
	m_nHeight = SystemData::size_y+1000;
	m_nWidth = SystemData::size_x+1000;
	initUI();
	setZOrder(999);
	dataRequest();

	return true;
}

void GuildDetailPanel::initUI()
{
	addCover(ccp(-1000,-1000));

	initFrame();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	m_background->addChild(m_pMainMenu);

	initLabels();
	initButtons();

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void GuildDetailPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case Button_Close:
			{
				closeSelf();
			}
			break;
		case Button_Combat:
			{
				//
			}
			break;
		case Button_Friend:
			{
				//
			}
			break;
		case Button_Apply:
			{
				if (m_selIndex<0)
				{
					return;
				}
				MsgApplicationToGuildRequest* req = new MsgApplicationToGuildRequest();
				req->GuildID = GuildData::getGuildID(GuildData::getRankByIndex(m_selIndex));
				HandleMessage::sendMessage(req);
			}
			break;
		default:
			break;
		}
	}
}

void GuildDetailPanel::closeSelf()
{
	this->removeFromParentAndCleanup(true);
}

void GuildDetailPanel::initFrame()
{
	m_background = SystemData::getSpriteByPlist("openactivity.alert.frame.background");
	m_background->setAnchorPoint(ccp(0.5,0.5));  
	addChild(m_background);
	
	CCSize bgSize1 = CCSizeMake(540,90);
	CCPoint bgPoint1 = ccp(281.5,233);
	CCScale9Sprite *bg1=SystemData::getScale9SpriteByPlist("openactivity.alert.frame.scalebg",bgSize1.width,bgSize1.height);
	bg1->setAnchorPoint(ccp(0.5,0));
	bg1->setPosition(bgPoint1); 
	m_background->addChild(bg1);

	CCSize bgSize2 = CCSizeMake(540,160);
	CCPoint bgPoint2 = ccp(281.5,68);
	CCScale9Sprite *bg2=SystemData::getScale9SpriteByPlist("openactivity.alert.frame.scalebg",bgSize2.width,bgSize2.height);
	bg2->setAnchorPoint(ccp(0.5,0));
	bg2->setPosition(bgPoint2); 
	m_background->addChild(bg2);
}

void GuildDetailPanel::initLabels()
{
	CCLabelTTF* m_Title =  SystemData::getLabelTTF("popalert.normal.label.title"); 
	m_Title->setColor(ccYELLOW);
	m_Title->setFontSize(22);    
	m_Title->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_Title->setDimensions(CCSizeMake(SystemData::getLayoutValue("popalert.normal.label.title.w"),SystemData::getLayoutValue("popalert.normal.label.title.h")));
	m_Title->setAnchorPoint(ccp(0.5,1));
	m_Title->setPosition(ccp(m_background->getContentSize().width/2,m_background->getContentSize().height-10));
	m_background->addChild(m_Title);
	m_Title->setString(SystemData::getLayoutString("popalert.browse.detail.title").c_str()); 
	
	float spaceWidth = 100.0f;
	CCLabelTTF* tName = SystemData::getLabelTTF("guild.browse.alert.label.name");
	tName->setColor(ccWHITE);
	tName->setFontSize(20);     
	tName->setAnchorPoint(CCPointZero);
	tName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tName);
	m_GuildName = SystemData::getLabelTTF("guild.browse.alert.label.name");
	m_GuildName->setColor(ccGREEN);
	m_GuildName->setFontSize(20);     
	m_GuildName->setAnchorPoint(CCPointZero);
	m_GuildName->setPositionX(m_GuildName->getPositionX()+spaceWidth);
	m_GuildName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_GuildName);
	m_GuildName->setString(GuildData::getGuildName(GuildData::getRankByIndex(m_selIndex)).c_str());

	CCLabelTTF* tCount = SystemData::getLabelTTF("guild.browse.alert.label.count");
	tCount->setColor(ccWHITE);
	tCount->setFontSize(20);     
	tCount->setAnchorPoint(CCPointZero);
	tCount->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tCount);
	m_GuildCount = SystemData::getLabelTTF("guild.browse.alert.label.count");
	m_GuildCount->setColor(ccGREEN);
	m_GuildCount->setFontSize(20);     
	m_GuildCount->setAnchorPoint(CCPointZero);
	m_GuildCount->setPositionX(m_GuildCount->getPositionX()+spaceWidth);
	m_GuildCount->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_GuildCount);

	int curCnt = GuildData::getGuildMemberCount(GuildData::getRankByIndex(m_selIndex));
	int curLvl = GuildData::getGuildLevel(GuildData::getRankByIndex(m_selIndex));
	int maxCnt = GuildData::getGuildMaxMember(curLvl);
	if (maxCnt < 1)
	{
		maxCnt = 1;
	}

	if (curCnt < 1)
	{
		curCnt = 1;
	}
	else if (curCnt > maxCnt)
	{
		curCnt = maxCnt;
	}
	m_GuildCount->setString((StringUtils::toString(curCnt)+"/"+StringUtils::toString(maxCnt)).c_str());

	CCLabelTTF* tMaster = SystemData::getLabelTTF("guild.browse.alert.label.master");
	tMaster->setColor(ccWHITE);
	tMaster->setFontSize(20);     
	tMaster->setAnchorPoint(CCPointZero);
	tMaster->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tMaster);
	m_GuildMaster = SystemData::getLabelTTF("guild.browse.alert.label.master");
	m_GuildMaster->setColor(ccGREEN);
	m_GuildMaster->setFontSize(20);     
	m_GuildMaster->setAnchorPoint(CCPointZero);
	m_GuildMaster->setPositionX(m_GuildMaster->getPositionX()+spaceWidth);
	m_GuildMaster->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_GuildMaster);
	m_GuildMaster->setString(GuildData::getGuildMasterName(GuildData::getRankByIndex(m_selIndex)).c_str());

	CCLabelTTF* tStatus = SystemData::getLabelTTF("guild.browse.alert.label.status");
	tStatus->setColor(ccWHITE);
	tStatus->setFontSize(20);     
	tStatus->setAnchorPoint(CCPointZero);
	tStatus->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tStatus);
	m_GuildStatus = SystemData::getLabelTTF("guild.browse.alert.label.status");
	m_GuildStatus->setColor(ccGREEN);
	m_GuildStatus->setFontSize(20);     
	m_GuildStatus->setAnchorPoint(CCPointZero);
	m_GuildStatus->setPositionX(m_GuildStatus->getPositionX()+spaceWidth);
	m_GuildStatus->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_GuildStatus);
	m_GuildStatus->setString(SystemData::getLayoutString("guild.browse.status.normal").c_str());

	CCLabelTTF* tPlacardTitle = SystemData::getLabelTTF("guild.browse.alert.label.placardtitle");
	tPlacardTitle->setColor(ccWHITE);
	tPlacardTitle->setFontSize(20);     
	tPlacardTitle->setAnchorPoint(ccp(0.5,0.5));
	tPlacardTitle->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(tPlacardTitle);
	
	m_GuildPlacard = SystemData::getLabelTTF("guild.browse.alert.label.placard");
	m_GuildPlacard->setColor(ccGREEN);
	m_GuildPlacard->setFontSize(20);     
	m_GuildPlacard->setAnchorPoint(ccp(0.5,0.5));
	m_GuildPlacard->setHorizontalAlignment(kCCTextAlignmentCenter); 
	m_GuildPlacard->setDimensions(CCSizeMake(550,200));
	addChild(m_GuildPlacard);
}

void GuildDetailPanel::initButtons()
{
	CCMenuItemImage* button1 = SystemData::getMenuItemImageByPlist("openactivity.alert.button.close");
	button1->setTarget(this,menu_selector(GuildDetailPanel::MenuCallBack));
	button1->setTag(Button_Close);
	button1->setAnchorPoint(ccp(1, 1));
	button1->setPosition(m_background->getContentSize().width,m_background->getContentSize().height);
	m_pMainMenu->addChild(button1);

	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("activity.button.frame",100,45);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",100,45); 
	CCMenuItemSprite *button2 =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(GuildDetailPanel::MenuCallBack));
	if(button2)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.alert.button.combat.text"); 
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		button2->setTag(Button_Combat);        
		button2->setPosition(SystemData::getLayoutPoint("guild.browse.alert.button.combat"));
		pLabel->setPosition(button2->getPosition()); 
		m_pMainMenu->addChild(button2); 
		m_pMainMenu->addChild(pLabel); 
	}

	CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("activity.button.frame",100,45);
	CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",100,45); 
	CCMenuItemSprite *button3 =CCMenuItemSprite::create(p3,pSel3,NULL,this,menu_selector(GuildDetailPanel::MenuCallBack));
	if(button3)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.alert.button.friend.text"); 
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		button3->setTag(Button_Friend);        
		button3->setPosition(SystemData::getLayoutPoint("guild.browse.alert.button.friend"));
		pLabel->setPosition(button3->getPosition());  
		m_pMainMenu->addChild(button3);  
		m_pMainMenu->addChild(pLabel); 
	}

	CCScale9Sprite* p4=SystemData::getScale9SpriteByPlist("activity.button.frame",100,45);
	CCScale9Sprite* pSel4=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",100,45); 
	CCMenuItemSprite *button4 =CCMenuItemSprite::create(p4,pSel4,NULL,this,menu_selector(GuildDetailPanel::MenuCallBack));
	if(button4)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.alert.button.apply.text"); 
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		button4->setTag(Button_Apply);        
		button4->setPosition(SystemData::getLayoutPoint("guild.browse.alert.button.apply"));
		pLabel->setPosition(button4->getPosition());  
		m_pMainMenu->addChild(button4); 
		m_pMainMenu->addChild(pLabel); 
	}
}

void GuildDetailPanel::dataRequest()
{
	mChecker->start();
	MsgGuildGetStringDataRequest *msg = new MsgGuildGetStringDataRequest;
	msg->guildID = GuildData::getGuildID(GuildData::getRankByIndex(m_selIndex));
	msg->key = GuildType::guild_public_notice;
	HandleMessage::sendMessage(msg);
}

void GuildDetailPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageGuildGetStringDataResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				const int guildID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				const int key = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				if (guildID == GuildData::getGuildID(GuildData::getRankByIndex(m_selIndex))
					&& key == GuildType::guild_public_notice
					&& m_GuildPlacard)
				{
					const std::string &data = CPEventHelper::getEventStringData(CPEventData::VALUE_4);
					if (!data.empty())
					{
						m_GuildPlacard->setString(data.c_str());
					}
				}
			}
		}
	}
}
