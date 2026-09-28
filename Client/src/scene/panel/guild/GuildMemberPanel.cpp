#include <algorithm>
#include "GuildMemberPanel.h"
#include "GuildPanel.h"
#include "GuildModule.h"
#include "PopApplicationPanel.h"
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
#include "userdata/netdata/GhostManager.h"
#include "MsgScene.h"
#include "userdata/NPCFunctionData.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "ModuleData.h"
#include "userdata/GuildData.h"
#include "PopAlertPanel.h"
#include "ext/TextField.h"
#include "utils/StringUtils.h"
#include "controls/CPComboBox.h"
#include "userdata/LayoutData.h"
#include "MsgPlayer.h"
#include "userdata/teamdata/TeamData.h"
#include "MsgTeam.h"
#include "userdata/PlayerInfoData.h"
#include "userdata/teamdata/TeamMsgSender.h"
#include "scene/panel/social/SocialHelper.h"
#include "scene/panel/ChatPanel.h"
#include "GuildDefinition.h"
#include "userdata/HeroData.h"
//-----------------------------------------------------------------------------------------------------------//

static bool guildMemberComp(const GuildMemberInfo& v1, const GuildMemberInfo& v2);

const int alertZorder = INT_MAX;

GuildMemberPanel::GuildMemberPanel():
	m_pMainMenu(NULL),
	m_LabelPage(NULL),
	m_filterNickname(NULL),
	m_kNumOfEachPage(6),
	m_selIndex(-1),
	m_curPage(0),
	m_filterValue(0)
{
	m_NicknameList.clear();
	m_MemberList.clear();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

GuildMemberPanel::~GuildMemberPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

GuildMemberPanel* GuildMemberPanel::create()
{
	GuildMemberPanel* pPanel = new GuildMemberPanel();
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


bool GuildMemberPanel::init( const char* filename )
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
	
	CCSize pPlacardSize = CCSizeMake(SystemData::getLayoutValue("guild.member.tablebg.w"),SystemData::getLayoutValue("guild.member.tablebg.h"));
	CCPoint pPlacardPoint = SystemData::getLayoutPoint("guild.member.tablebg");
	m_pTableView = CCTableViewEx::create(this,CCSizeMake(pPlacardSize.width/*-15*/,pPlacardSize.height-60),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setAnchorPoint(CCPointZero);	
	m_pTableView->setPosition(ccp(pPlacardPoint.x/*+5*/,pPlacardPoint.y+60));
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setBounceable(false);
	/*m_pLeftMenu->*/addChild(m_pTableView); 
	//m_pTableView->setVisible(false);       

	initLabels();
	initButtons();

	filterPost();
	reloadTableView();

	return true;
}
void GuildMemberPanel::filterPost()
{
	m_MemberList.clear();

	int size = GuildData::getGuildMemberCnt();
	for (int i = 0; i < size; ++i)
	{
		int tmpPost = GuildData::getGuildMemberNickname(i);
		if (tmpPost < 0 ||
			(m_filterValue != 0 && (m_filterValue - 1) != tmpPost))
		{
			continue;
		}

		GuildMemberInfo tmp;
 		tmp.pid = GuildData::getGuildMemberPID(i);
 		tmp.name = GuildData::getGuildMemberName(i);
 		tmp.level = GuildData::getGuildMemberLevel(i);
 		tmp.job = GuildData::getGuildMemberJob(i);
 		tmp.post = GuildData::getGuildMemberNickname(i);
 		tmp.contribution = GuildData::getGuildMemberContribution(i);
 		tmp.todaycontribution = GuildData::getGuildMemberTodayContribution(i);
 		m_MemberList.push_back(tmp);
	}

	std::sort(m_MemberList.begin(), m_MemberList.end(), guildMemberComp);
}

int GuildMemberPanel::getMaxPage()
{
	if (m_MemberList.empty())
		return 1;

	return (m_MemberList.size() - 1) / m_kNumOfEachPage + 1;
}

int GuildMemberPanel::getMemberListIndex()
{
	if (!isSelectIndexValid())
	{
		return -1;
	}

	return m_selIndex + m_curPage * m_kNumOfEachPage;
}

bool GuildMemberPanel::isSelectIndexValid()
{
	return m_selIndex >= 0 && m_selIndex < m_kNumOfEachPage;
}

void GuildMemberPanel::changeNicknameCancelCallBack(CCObject* pSender)
{
	CCLog("%s",__FUNCTION__);
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		for (int i=0;i<GuildData::getGuildNicknameCnt();i++)
		{
			CCEditBox* m_pInputTextField = (CCEditBox*)pNode->getChildByTag(i+1);
			if (m_pInputTextField)
			{
				std::string nickname;
				if (LuaData::getProp(LuaData::GUILD_JOB_REWARD,i,"nickname",nickname))
				{
					if (nickname.empty()||nickname.length()<=0||nickname=="0")
					{
						LuaData::getProp(LuaData::GUILD_JOB_REWARD,GuildType::post_normal,"nickname",nickname);
					}
				}
				if (m_pInputTextField->getText()!=nickname)
				{
					m_pInputTextField->setText(nickname.c_str());

					MsgGuildNicknameUpdateRequest* req = new MsgGuildNicknameUpdateRequest();
					req->job = i;
					req->nickname = nickname;
					HandleMessage::sendMessage(req);
				}
			}
		}
	}
	
}
void GuildMemberPanel::comboCallBack(CCNode* pSender)
{
	CCLog("%s",__FUNCTION__);
	CPComboBox* mCombo = dynamic_cast<CPComboBox*>(pSender);
	if (!mCombo)
		return;
	int idx = mCombo->getTag()-Combo_Nickname_Start;
	if (idx < 0 || idx >= m_kNumOfEachPage)
		return;

	idx += m_curPage * m_kNumOfEachPage;
	if (idx < 0 || idx >= GuildData::getGuildMemberCnt())
		return;

	MsgGuildMemberNicknameChangeRequestEx* req = new MsgGuildMemberNicknameChangeRequestEx;
	req->pid = m_MemberList[idx].pid;
	req->nickname = mCombo->getCurrentIndex();
	HandleMessage::sendMessage(req);
}
void GuildMemberPanel::filterCallBack(CCNode* pSender)
{
	CCLog("%s",__FUNCTION__);
	CPComboBox* mCombo = dynamic_cast<CPComboBox*>(pSender);
	if (!mCombo)
		return;
	m_filterValue = mCombo->getCurrentIndex();
	//loadGuildMemberRequest(1);
	filterPost();
	reloadTableView();
	m_curPage = 0;

}
void GuildMemberPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==Button_Detail)
		{
			int index = getMemberListIndex();
			if (index < 0)
			{
				return;
			}

			MsgGetOtherPlayerDataRequest* msg=new MsgGetOtherPlayerDataRequest;
			msg->pid = m_MemberList[index].pid;//GuildData::getGuildMemberPID(m_selIndex);
			HandleMessage::sendMessage(msg);
		}
		else if (tag==Button_Chat)
		{
			int index = getMemberListIndex();
			if (index < 0)
			{
				return;
			}

			if (m_MemberList[index].pid == HeroData::getPID())
				return;

			ChatPanelHelper::openChatWithPartner(m_MemberList[index].pid, m_MemberList[index].name);
		}
		else if (tag==Button_Friend)
		{
			int index = getMemberListIndex();
			if (index < 0)
			{
				return;
			}
			SocialHelper::requestAddFriend(m_MemberList[index].pid, "");
		}
		else if (tag==Button_Invite)
		{
			int index = getMemberListIndex();
			if (index < 0)
			{
				return;
			}
			TeamMsgSender::Invite(m_MemberList[index].pid);
		}
		else if (tag==Button_AppList)
		{
			PopApplicationPanel* m_pApplicationPanel = dynamic_cast<PopApplicationPanel *>(getChildByTag(789));
			if (m_pApplicationPanel)
			{
				m_pApplicationPanel->removeFromParentAndCleanup(true);
				m_pApplicationPanel = NULL;
			}
			int cnt = GuildData::getGuildApplicationCnt();
			m_pApplicationPanel = PopApplicationPanel::create();
			addChild(m_pApplicationPanel, 3, 789);
		}
		else if (tag==Button_Call)
		{
			
		}
		else if (tag==Button_Editnickname)
		{
			editNicknameView();
		}
		else if (tag==Button_Pageup)
		{
			loadGuildMemberPageUp();
		}
		else if (tag==Button_Pagedown)
		{
			loadGuildMemberPageDown();
		}
		else if (tag==Button_ChangeMaster)
		{
			int index = getMemberListIndex();
			if (index < 0)
			{
				return;
			}
			PopAlertPanel* alert = PopAlertPanel::create();
			CCString* str = CCString::createWithFormat(
				SystemData::getLayoutString("popalert.member.updatemaster.alert").c_str(),
				m_MemberList[index].name.c_str());
			alert->setString(str->getCString());
			alert->setConfirmTarget(this,menu_selector(GuildMemberPanel::MenuCallBack));
			alert->setTag(Alert_ChangeMaster_Confirm);
			addChild(alert);
		}
		else if (tag==Button_Delete)
		{
			int index = getMemberListIndex();
			if (index < 0)
			{
				return;
			}
			PopAlertPanel* alert = PopAlertPanel::create();
			CCString* str = CCString::createWithFormat(
				SystemData::getLayoutString("popalert.member.delete.alert").c_str(),
				m_MemberList[index].name.c_str());
			alert->setString(str->getCString());
			alert->setConfirmTarget(this,menu_selector(GuildMemberPanel::MenuCallBack));
			alert->setTag(Alert_Delete_Confirm);
			addChild(alert);
		}
		else if (tag==Alert_ChangeMaster_Confirm)
		{
			int index = getMemberListIndex();
			if (index < 0)
			{
				return;
			}
			MsgGuildMasterResetRequest* req = new MsgGuildMasterResetRequest();
			req->ResetPid = m_MemberList[index].pid;//GuildData::getGuildMemberPID(m_selIndex);
			HandleMessage::sendMessage(req);
		}
		else if (tag==Alert_Delete_Confirm)
		{
			int index = getMemberListIndex();
			if (index < 0)
			{
				return;
			}
			MsgDeleteGuildMemberRequest* req = new MsgDeleteGuildMemberRequest();
			req->pid = m_MemberList[index].pid;//GuildData::getGuildMemberPID(m_selIndex);
			HandleMessage::sendMessage(req);
		}
		else if(tag == Alert_ChangeNickname_Confirm)
		{
			for (int i=0;i<GuildData::getGuildNicknameCnt();i++)
			{
// 				PopAlertPanel* pPanel = dynamic_cast<PopAlertPanel*>(pNode);
// 				if (!pPanel)
// 				{
// 					return;
// 				}
				CCEditBox* m_pInputTextField = (CCEditBox*)pNode->getChildByTag(i+1);
				if (m_pInputTextField)
				{
					std::string input = m_pInputTextField->getText();
					if (input.length()>0)
					{
						if (input!=GuildData::getGuildNickname(i))  
						{
							MsgGuildNicknameUpdateRequest* req = new MsgGuildNicknameUpdateRequest();
							req->job = i;
							req->nickname = input;
							HandleMessage::sendMessage(req);
						}
					}
					else
					{
						CCLog("_____%s________Error: input length error <%d>",__FUNCTION__,i);
					}
				}
			}
		}
	}
}


cocos2d::CCSize GuildMemberPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutSize("guild.member.tablebg").width, 45);
}

cocos2d::extension::CCTableViewCell* GuildMemberPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		
		initCell(cell,idx);
	}
	loadCell(cell,idx);
	return cell;
}

unsigned int GuildMemberPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	if (m_MemberList.empty())
	{
		return 0;
	}

	int maxPage = getMaxPage();
	if (m_curPage + 1 == maxPage)
	{
		int numOfCurPage = m_MemberList.size() % m_kNumOfEachPage;
		return numOfCurPage == 0 ? m_kNumOfEachPage : numOfCurPage;
	}

	return m_kNumOfEachPage;
}

void GuildMemberPanel::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
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

void GuildMemberPanel::CloseSelf(CCObject* pSender)
{
	Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);	
}

void GuildMemberPanel::handleEvent( int channel )
{	
	if(channel == EventProtocol::EVENT_TASK_RECEIVED)
	{
		//CCLog("Event Recieve");
	}
}
void GuildMemberPanel::editNicknameView()
{
	CCSize alertSize = SystemData::getLayoutSize("popalert.changenickname");
	PopAlertPanel* alert = PopAlertPanel::create();
	alert->setConfirmTarget(this,menu_selector(GuildBrowsePanel::MenuCallBack));
	alert->setCancelTarget(this,menu_selector(GuildMemberPanel::changeNicknameCancelCallBack));
	alert->setTag(Alert_ChangeNickname_Confirm);
	alert->setConfirmTitle(SystemData::getLayoutString("popalert.changenickname.left"));
	alert->setCancelTitle(SystemData::getLayoutString("popalert.changenickname.right"));
	alert->setTitle(SystemData::getLayoutString("popalert.changenickname.title"));
	for (int i=0;i<GuildData::getGuildNicknameCnt();i++)
	{
		CCEditBox *ret = NULL;
		CCScale9Sprite *scaleSprite = CCScale9Sprite::createWithSpriteFrameName(SystemData::getLayoutString("guild.info.label.placard.inputframe").c_str());
		if (!scaleSprite)
		{
			scaleSprite = CCScale9Sprite::create(SystemData::getLayoutString("guild.info.label.placard.inputframe").c_str());
		}
		if (scaleSprite)
		{
			ret = CCEditBox::create(SystemData::getLayoutSize("guild.info.label.placard.inputframe"), scaleSprite);
			ret->setMaxLength(SystemData::getLayoutValue("guild.info.label.nickname.input.maxlength"));
			ret->setFontName(SystemData::getLayoutString("guild.info.label.placard.inputframe.font").c_str());
			ret->setPlaceholderFontName(SystemData::getLayoutString("guild.info.label.placard.inputframe.font").c_str());
			ret->setFontSize(SystemData::getLayoutValue("guild.info.label.placard.inputframe.fontsize"));
			ret->setPlaceholderFontSize(SystemData::getLayoutValue("guild.info.label.placard.inputframe.fontsize"));
			ret->setAnchorPoint(ccp(0.5,0.5));
			ret->setPosition(ccp(400,320-47*i));
			ret->setTouchPriority(kCCMenuHandlerPriority);
			ret->setTag(i+1); 
			alert->addChild(ret);
			ret->setText(GuildData::getGuildNickname(i).c_str());
		}
	}
	addChild(alert);
}
void GuildMemberPanel::initFrame()
{
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",SystemData::getLayoutValue("guild.bg.w"),SystemData::getLayoutValue("guild.bg.h"));
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(SystemData::getLayoutPoint("guild.bg"));   
	addChild(bg); 
	//封号信息
	CCScale9Sprite *infoview=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.member.nicknameview.w"),SystemData::getLayoutValue("guild.member.nicknameview.h"));
	infoview->setAnchorPoint(CCPointZero);
	infoview->setPosition(SystemData::getLayoutPoint("guild.member.nicknameview")); 
	addChild(infoview);
	//表格头
	CCScale9Sprite *headerview=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.member.headerview.w"),SystemData::getLayoutValue("guild.member.headerview.h"));
	headerview->setAnchorPoint(CCPointZero);
	headerview->setPosition(SystemData::getLayoutPoint("guild.member.headerview"));
	addChild(headerview);
	//右侧框
	CCScale9Sprite *pRightborder=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.member.rightbg.w"),SystemData::getLayoutValue("guild.member.rightbg.h"));
	pRightborder->setAnchorPoint(CCPointZero);  
	pRightborder->setPosition(SystemData::getLayoutPoint("guild.member.rightbg")); 
	addChild(pRightborder);	
	//列表背景
	CCScale9Sprite *pTable=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.member.tablebg.w"),SystemData::getLayoutValue("guild.member.tablebg.h"));
	pTable->setAnchorPoint(CCPointZero);  
	pTable->setPosition(SystemData::getLayoutPoint("guild.member.tablebg")); 
	addChild(pTable);	
}

void GuildMemberPanel::initLabels()
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

void GuildMemberPanel::initButtons()
{
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.button",100,40);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,40);
	CCMenuItemSprite *pDetail =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));//行会信息按钮
	if(pDetail)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.detail.text");
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		pDetail->setTag(Button_Detail);
		pDetail->setPosition(SystemData::getLayoutPoint("guild.member.button.detail"));
		pLabel->setPosition(pDetail->getPosition());
		m_pMainMenu->addChild(pDetail);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("guild.info.button",100,40);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,40);
	CCMenuItemSprite *pChat =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));//行会信息按钮
	if(pChat)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.chat.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pChat->setTag(Button_Chat);
		pChat->setPosition(SystemData::getLayoutPoint("guild.member.button.chat"));
		pLabel->setPosition(pChat->getPosition());
		m_pMainMenu->addChild(pChat);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("guild.info.button",100,40);
	CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,40);
	CCMenuItemSprite *pFriend =CCMenuItemSprite::create(p3,pSel3,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));//行会信息按钮
	if(pFriend)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.friend.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pFriend->setTag(Button_Friend);
		pFriend->setPosition(SystemData::getLayoutPoint("guild.member.button.friend"));
		pLabel->setPosition(pFriend->getPosition());
		m_pMainMenu->addChild(pFriend);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p4=SystemData::getScale9SpriteByPlist("guild.info.button",100,40);
	CCScale9Sprite* pSel4=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,40);
	CCMenuItemSprite *pInvite =CCMenuItemSprite::create(p4,pSel4,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));//行会信息按钮
	if(pInvite)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.invite.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pInvite->setTag(Button_Invite);
		pInvite->setPosition(SystemData::getLayoutPoint("guild.member.button.invite"));
		pLabel->setPosition(pInvite->getPosition());
		m_pMainMenu->addChild(pInvite);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p6=SystemData::getScale9SpriteByPlist("guild.info.button",100,40);
	CCScale9Sprite* pSel6=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,40);
	CCMenuItemSprite *pEnemy =CCMenuItemSprite::create(p6,pSel6,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));
	if(pEnemy)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.enemy.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pEnemy->setTag(Button_AppList);
		pEnemy->setPosition(SystemData::getLayoutPoint("guild.member.button.enemy"));
		pLabel->setPosition(pEnemy->getPosition());
		m_pMainMenu->addChild(pEnemy);
		m_pMainMenu->addChild(pLabel);
	}
	
	CCScale9Sprite* p8=SystemData::getScale9SpriteByPlist("guild.info.placard.button",120,35);
	CCScale9Sprite* pSel8=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",120,35);
	CCMenuItemSprite *pEditnickname =CCMenuItemSprite::create(p8,pSel8,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));//编辑称号
	if(pEditnickname)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.editnickname.text");
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		pEditnickname->setTag(Button_Editnickname);
		pEditnickname->setPosition(SystemData::getLayoutPoint("guild.member.button.editnickname"));
		pLabel->setPosition(pEditnickname->getPosition());
		m_pMainMenu->addChild(pEditnickname);
		m_pMainMenu->addChild(pLabel);  
		pEditnickname->setVisible(HeroData::getProp(Entity::attr_guild_post)<=GuildType::post_second_master&&HeroData::getProp(Entity::attr_guild_post)>0);
		pLabel->setVisible(HeroData::getProp(Entity::attr_guild_post)<=GuildType::post_second_master&&HeroData::getProp(Entity::attr_guild_post)>0);
	}

	CCScale9Sprite* p9=SystemData::getScale9SpriteByPlist("guild.info.placard.button",80,35);
	CCScale9Sprite* pSel9=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",80,35);
	CCMenuItemSprite *pPageup =CCMenuItemSprite::create(p9,pSel9,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));//行会信息按钮
	if(pPageup)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.pageup.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pPageup->setTag(Button_Pageup);
		pPageup->setPosition(SystemData::getLayoutPoint("guild.member.button.pageup"));
		pLabel->setPosition(pPageup->getPosition());
		m_pMainMenu->addChild(pPageup);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p10=SystemData::getScale9SpriteByPlist("guild.info.placard.button",80,35);
	CCScale9Sprite* pSel10=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",80,35);
	CCMenuItemSprite *pPagedown =CCMenuItemSprite::create(p10,pSel10,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));//行会信息按钮
	if(pPagedown)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.pagedown.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pPagedown->setTag(Button_Pagedown);
		pPagedown->setPosition(SystemData::getLayoutPoint("guild.member.button.pagedown"));
		pLabel->setPosition(pPagedown->getPosition());
		m_pMainMenu->addChild(pPagedown);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p11=SystemData::getScale9SpriteByPlist("guild.info.placard.button",100,35);
	CCScale9Sprite* pSel11=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",100,35);
	CCMenuItemSprite *pChangeMaster =CCMenuItemSprite::create(p11,pSel11,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));//行会信息按钮
	if(pChangeMaster)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.updatemaster.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pChangeMaster->setTag(Button_ChangeMaster);
		pChangeMaster->setPosition(SystemData::getLayoutPoint("guild.member.button.updatemaster"));
		pLabel->setPosition(pChangeMaster->getPosition());
		m_pMainMenu->addChild(pChangeMaster);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p12=SystemData::getScale9SpriteByPlist("guild.info.placard.button",100,35);
	CCScale9Sprite* pSel12=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",100,35);
	CCMenuItemSprite *pDelete =CCMenuItemSprite::create(p12,pSel12,NULL,this,menu_selector(GuildMemberPanel::MenuCallBack));
	if(pDelete)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.member.button.delete.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pDelete->setTag(Button_Delete);
		pDelete->setPosition(SystemData::getLayoutPoint("guild.member.button.delete"));
		pLabel->setPosition(pDelete->getPosition());
		m_pMainMenu->addChild(pDelete);
		m_pMainMenu->addChild(pLabel);
	}
	
	m_filterNickname = LayoutData::getComboBox(CPModuleName::COMMON, "normal");
	m_filterNickname->setDirection(ComboBoxOpenType::open_Down);
	m_filterNickname->setChangeHandler(this,callfuncN_selector(GuildMemberPanel::filterCallBack));
	m_filterNickname->setPosition(SystemData::getLayoutPoint("guild.member.button.nicknamebutton"));
	addChild(m_filterNickname); 
	m_filterNickname->setScale(0.9);
	m_filterNickname->addLabelItem(SystemData::getLayoutString("guild.member.title.filter.default"));
	const int cnt = GuildData::getGuildNicknameCnt();
	for (int i=0;i<cnt;i++)
	{
		m_filterNickname->addLabelItem(GuildData::getGuildNickname(i));
	}
}

void GuildMemberPanel::initCell(CCTableViewCell *cell,int idx)
{
	CCLabelTTF* tName = SystemData::getLabelTTF("guild.member.title.name");
	tName->setTag(Tag_Name);
	tName->setPosition(ccp(tName->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tName->setColor(ccWHITE);
	tName->setFontSize(18);     
	tName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tName);
	
	CCLabelTTF* tJob = SystemData::getLabelTTF("guild.member.title.job");
	tJob->setTag(Tag_Job);
	tJob->setPosition(ccp(tJob->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tJob->setColor(ccWHITE);
	tJob->setFontSize(18);   
	tJob->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tJob);

	CCLabelTTF* tLevel = SystemData::getLabelTTF("guild.member.title.level");
	tLevel->setTag(Tag_Level);
	tLevel->setPosition(ccp(tLevel->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tLevel->setColor(ccWHITE);
	tLevel->setFontSize(18);
	tLevel->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tLevel); 

	CCLabelTTF* tContribution = SystemData::getLabelTTF("guild.member.title.contribution");
	tContribution->setTag(Tag_Contribution);
	tContribution->setPosition(ccp(tContribution->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tContribution->setColor(ccWHITE); 
	tContribution->setFontSize(18);   
	tContribution->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tContribution);

	CCLabelTTF* tNickname = SystemData::getLabelTTF("guild.member.title.nickname");
	tNickname->setTag(Tag_Nickname);
	tNickname->setPosition(ccp(tNickname->getPositionX(),cellSizeForTable(m_pTableView).height/2));
	tNickname->setColor(ccWHITE); 
	tNickname->setFontSize(18);   
	tNickname->setHorizontalAlignment(kCCTextAlignmentLeft); 
	cell->addChild(tNickname);

	CCPoint nicknamePoint =  SystemData::getLayoutPoint("guild.member.title.nickname");
	float posy = SystemData::getLayoutPoint("guild.member.tablebg").y+SystemData::getLayoutSize("guild.member.tablebg").height-25;
	nicknamePoint = ccp(nicknamePoint.x,posy-idx*cellSizeForTable(m_pTableView).height);
	CPComboBox* mComboBox = LayoutData::getComboBox(CPModuleName::COMMON, "normal");
	mComboBox->setTag(Combo_Nickname_Start + idx);
	mComboBox->setChangeHandler(this,callfuncN_selector(GuildMemberPanel::comboCallBack));
	mComboBox->setPosition(nicknamePoint);
	mComboBox->setScale(0.9);
	addChild(mComboBox, 1);

	m_NicknameList.push_back(mComboBox);
	int cnt = GuildData::getGuildNicknameCnt();
	for (int i=0;i<cnt;i++)
	{
		mComboBox->addLabelItem(GuildData::getGuildNickname(i));
	}
	mComboBox->setVisible(false);
}
void GuildMemberPanel::loadCell(CCTableViewCell *cell,unsigned int idx)
{
	int realIndex = idx + m_curPage * m_kNumOfEachPage;

	std::string s_Level = StringUtils::toString(m_MemberList[realIndex].level);
	std::string s_Contribution = StringUtils::toString(m_MemberList[realIndex].contribution);
	
	CCLabelTTF* tName = (CCLabelTTF*)cell->getChildByTag(Tag_Name);
	tName->setString(m_MemberList[realIndex].name.c_str());

	CCLabelTTF* tJob = (CCLabelTTF*)cell->getChildByTag(Tag_Job);
	std::string sJob = GuildData::getDefaultNickname(m_MemberList[realIndex].post);
	tJob->setString(sJob.c_str());

	CCLabelTTF* tLevel = (CCLabelTTF*)cell->getChildByTag(Tag_Level);
	tLevel->setString(s_Level.c_str());

	CCLabelTTF* tContribution = (CCLabelTTF*)cell->getChildByTag(Tag_Contribution);
	tContribution->setString(s_Contribution.c_str());

	CCLabelTTF* tNickname = (CCLabelTTF*)cell->getChildByTag(Tag_Nickname);
	int job = m_MemberList[realIndex].post;
	tNickname->setString(GuildData::getGuildNickname(job).c_str());
	
	CPComboBox* pNickname = (CPComboBox*)getChildByTag(Combo_Nickname_Start + idx);
	if (pNickname)
	{
		pNickname->setCurrentIndex(job);
	}

	bool isVisible = (HeroData::getProp(Entity::attr_guild_post) < job
		|| job == GuildType::post_normal)
		&& HeroData::getProp(Entity::attr_guild_post) > 0;
	pNickname->setVisible(isVisible); 
	tNickname->setVisible(!isVisible);
}

void GuildMemberPanel::loadGuildMemberPageUp()
{
	if (m_curPage <= 0)
	{
		CCLog("Error____________Page invalid");
		return;
	}
	--m_curPage;
	reloadTableView();
}
void GuildMemberPanel::loadGuildMemberPageDown()
{
	int maxPage = getMaxPage();
	if (m_curPage + 1 >= maxPage)
	{
		CCLog("Error____________Page invalid");
		return;
	}

	++m_curPage;
	reloadTableView();
}
void GuildMemberPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if(source == "HandleMessageGuildMemberInfoResponse")
		{
			if (m_LabelPage)
			{
				CCString* sPage = CCString::createWithFormat("%d/%d",GuildData::getGuildMemberPage(),GuildData::getGuildMemberMaxPage());
				m_LabelPage->setString(sPage->getCString());
			}
			reloadTableView();
		}
		else if(source == "HandleMessageGuildNicknameLoadNotify")
		{
			reloadTableView();
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if(source == "HandleMessageSyncGuildExStringDataNotify")
		{
			int dataType = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			CCLog("_droid_____________type = %d",dataType);
			if (dataType==GuildType::guild_nick_normal
				||dataType==GuildType::guild_nick_master
				||dataType==GuildType::guild_nick_second
				||dataType==GuildType::guild_nick_elite)
			{
				reloadTableView();
			}
		}
		else if (source == "HandleMessageGuildMemberChangeNotify")
		{
			filterPost();
			reloadTableView();
		}
		else if (source == "HandleMessageDeleteGuildMemberResponse")
		{
			filterPost();
			reloadTableView();
		}
	}
}
void GuildMemberPanel::reloadTableView()
{
	if (m_filterNickname)
	{
		m_filterNickname->removeFromParentAndCleanup(true);
		m_filterNickname=NULL;
	}
	m_filterNickname = LayoutData::getComboBox(CPModuleName::COMMON, "normal");
	m_filterNickname->setChangeHandler(this,callfuncN_selector(GuildMemberPanel::filterCallBack));
	//CCPoint pos = SystemData::getLayoutPoint("guild.combat.label.combobox" + StringUtils::toString(i));
	m_filterNickname->setPosition(SystemData::getLayoutPoint("guild.member.button.nicknamebutton"));
	addChild(m_filterNickname); 
	m_filterNickname->setScale(0.9);
	m_filterNickname->addLabelItem(SystemData::getLayoutString("guild.member.title.filter.default"));
	int cnt = GuildData::getGuildNicknameCnt();
	for (int i=0;i<cnt;i++)
	{
// 		int job = GuildData::getGuildNicknameJob(i);
// 		m_filterNickname->addLabelItem(GuildData::getGuildNickname(job));
		m_filterNickname->addLabelItem(GuildData::getGuildNickname(i));
	}
	m_filterNickname->setCurrentIndex(m_filterValue);

	for ( std::vector<CPComboBox*>::iterator iter = m_NicknameList.begin() ; iter != m_NicknameList.end() ; iter++ )
	{
		CPComboBox* box = *iter;
		box->removeFromParentAndCleanup(true);
		box=NULL;
	}
	m_NicknameList.clear();

	if (m_LabelPage)
	{
		int maxPage = getMaxPage();
		if (m_curPage + 1 > maxPage)
		{
			m_curPage = maxPage - 1;
		}
		else if (m_curPage < 0)
		{
			m_curPage = 0;
		}

		CCString* sPage = CCString::createWithFormat("%d/%d", m_curPage + 1, maxPage);
		m_LabelPage->setString(sPage->getCString());
	}

	m_pTableView->reloadData();
	
	if (numberOfCellsInTableView(m_pTableView) > 0)
		tableCellTouched(m_pTableView, m_pTableView->cellAtIndex(0));
}







////////////////////////////////////////////////////////////////////////////////
NickNameEditPanel::NickNameEditPanel()
	:m_pMainMenu(NULL)
	,m_selIndex(-1)
{

}

NickNameEditPanel::~NickNameEditPanel()
{

}

NickNameEditPanel* NickNameEditPanel::create(int tag)
{
	NickNameEditPanel* pPanel = new NickNameEditPanel();
	if(pPanel && pPanel->init(tag))
	{
		pPanel->autorelease();
		return pPanel;
	}
	else
	{
		CCLog("NickNameEditPanel create failed!");
	}
	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}


bool NickNameEditPanel::init( int tag)
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_selIndex = tag;

	m_nHeight = SystemData::size_y+1000;
	m_nWidth = SystemData::size_x+1000;

	addCover(ccp(-1000,-1000));

	initFrame();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	initLabels();
	initButtons();

	return true;
}

void NickNameEditPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		closeSelf();		
	}
}

void NickNameEditPanel::closeSelf()
{
	this->removeFromParentAndCleanup(true);
}

void NickNameEditPanel::initFrame()
{
	CCSprite* frame = SystemData::getSpriteByPlist("openactivity.alert.frame.background");
	frame->setAnchorPoint(ccp(0.5,0.5));  
	addChild(frame);

	CCSize bgSize = SystemData::getLayoutSize("openactivity.alert.frame.scalebg");
	CCPoint bgPoint = SystemData::getLayoutPoint("openactivity.alert.frame.scalebg");
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("openactivity.alert.frame.scalebg",bgSize.width,bgSize.height);
	bg->setAnchorPoint(ccp(0.5,0.5));
	bg->setPosition(bgPoint); 
	addChild(bg);
}

void NickNameEditPanel::initLabels()
{
	/*
	CCSize size = SystemData::getLayoutSize("openactivity.alert.label.content"); 
	CPRichText* pText=NPCFunctionData::getBigContent(ActivityDataHelper::getOpenActivityInfo(m_selIndex+1),size.width,size.height); 
	pText->setAnchorPoint(ccp(0.5,0.5));
	pText->setPosition(SystemData::getLayoutPoint("openactivity.alert.label.content")); 
	addChild(pText);

	CCLabelTTF* label1 = SystemData::getLabelTTF("openactivity.alert.label.page");
	label1->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(label1);
	label1->setString(ActivityDataHelper::getOpenActivityTitle(m_selIndex+1).c_str());
	*/
}

void NickNameEditPanel::initButtons()
{
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.placard.button",100,45);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",100,45); 
	CCMenuItemSprite *button =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(NickNameEditPanel::MenuCallBack));
	if(button)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("openactivity.alert.button.ok.label"); 
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		//button->setTag(Tag_Detail);        
		button->setPosition(SystemData::getLayoutPoint("openactivity.alert.button.ok"));
		pLabel->setPosition(button->getPosition()); 
		m_pMainMenu->addChild(button); 
		m_pMainMenu->addChild(pLabel);
	}

	CCMenuItemImage* button2 = SystemData::getMenuItemImageByPlist("openactivity.alert.button.close");
	button2->setTarget(this,menu_selector(NickNameEditPanel::MenuCallBack));
	button2->setAnchorPoint(ccp(1,1));
	m_pMainMenu->addChild(button2);
}

static bool guildMemberComp(const GuildMemberInfo& v1, const GuildMemberInfo& v2)
{
	// 先依据职位进行排序
	if (v1.post != v2.post)
	{
		/*
			注：由于GuildType中，帮众为0，帮主为1，副帮主为2，精英为3，
			排序要求为：帮主->副帮主->精英->帮众，
			所以此处的代码利用了该顺序
		*/
		if (v1.post == GuildType::post_normal)
			return false;

		if (v2.post == GuildType::post_normal)
			return true;

		return v1.post < v2.post;
	}

	// 随后依据人物的帮派贡献排序
	if (v1.contribution != v2.contribution)
		return v1.contribution > v2.contribution;

	// 最后依据人物的等级排序
	return v1.level > v2.level;
}