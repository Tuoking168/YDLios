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
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "userdata/netdata/GhostManager.h"
#include "MsgScene.h"
#include "userdata/NPCFunctionData.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "ModuleData.h"
#include "userdata/GuildData.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "GuildDefinition.h"


GuildPanel::GuildPanel():
	/*
	m_pMainMenu(NULL),
	m_pCurrentMenu(NULL),
	m_pTableView(NULL),
	m_iGuildCount(0),
	m_iCurrentType(0),
	m_pInfo(NULL)
	*/
	m_iCurrentType(-1),
	m_pTipTable(NULL)
	, m_showPanel(NULL)
{
	//CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_NOTIFY, this);
}

GuildPanel::~GuildPanel()
{
	//CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_NOTIFY, this);
}

bool GuildPanel::init( const char* filename )
{
	
	if (!CCLayer::init())
	{
		return false;
	}
	m_showPanel = CCNode::create();
	addChild(m_showPanel);

	updateSwitchButtons(-1);

	selectPanel(TAG_GUILDINFO);
	
	return true;
}

GuildPanel* GuildPanel::create()
{
	GuildPanel* pPanel = new GuildPanel();
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
void GuildPanel::selectPanel(int tag,bool guildLimit)
{
	/*
	CCNode* testNode = CCNode::create();
	testNode->setTag(tag);
	MenuCallBack(testNode);
	*/
	if (!GuildData::hasGuild()&&guildLimit)
	{
		CCLog("%s ___error: invalid Guild",__FUNCTION__);
		if (TAG_GUILDBROWSE!=tag)
		{
			//CPEventHelper::msgNotify("","",Opcode::GUILD_OP_NO_GUILD,0,0,0);
			CPEventHelper::msgNotify("","",2000,0,0,0);
			if (tag!=kCCNodeTagInvalid)
			{
				CCMenuItem* selButton = (CCMenuItem*)m_pMainMenu->getChildByTag(tag);
				if (selButton)selButton->unselected();
			}
		}
		tag = TAG_GUILDBROWSE;
	}
	if (m_iCurrentType==tag)
	{
		return;
	}
	if (m_iCurrentType!=kCCNodeTagInvalid)
	{
		CCMenuItem* selButton = (CCMenuItem*)m_pMainMenu->getChildByTag(m_iCurrentType);
		if (selButton)
		{
			selButton->unselected();
			m_showPanel->removeAllChildrenWithCleanup(true); 
		}
	}

	m_iCurrentType=tag;
	BasePanel* panel = NULL;
	if (tag==TAG_GUILDINFO)
	{
		panel = GuildInfoPanel::create();	
	}
	else if (tag==TAG_GUILDCOMBAT)
	{
		panel = GuildCombatPanel::create();
	}
	else if(tag==TAG_GUILDMEMBER)
	{	
		panel = GuildMemberPanel::create();
	}
	else if(tag==TAG_GUILDBROWSE)
	{		
		panel = GuildBrowsePanel::create();
	}
	if (panel)
	{
		
		//hideTipTable();
		//m_showPanel->removeAllChildrenWithCleanup(true); 
		//updateSwitchButtons(tag);
		m_showPanel->addChild(panel);
		
		if (m_iCurrentType!=kCCNodeTagInvalid)
		{
			CCMenuItem* button = (CCMenuItem*)m_pMainMenu->getChildByTag(tag);
			if (button)
			{
				button->selected();
			}
		}
	}
}
void GuildPanel::updateSwitchButtons(int tag)
{
	//主要menu  
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero); 
	addChild(m_pMainMenu);
	//加载顶部按钮
	CCScale9Sprite* p1;
	if (tag==TAG_GUILDINFO)
		p1=SystemData::getScale9SpriteByPlist("guild.switch.button.sel",105,45);
	else
		p1=SystemData::getScale9SpriteByPlist("guild.switch.button",105,45);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.switch.button.sel",105,45);
	CCMenuItemSprite *pinfo =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(GuildPanel::MenuCallBack));//行会信息按钮
	if(pinfo)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.switch.info");
		pLabel->setFontSize(20);
		pLabel->setColor(ccWHITE);
		pinfo->setTag(TAG_GUILDINFO);
		pinfo->setPosition(SystemData::getLayoutPoint("guild.switch.info"));
		pLabel->setPosition(pinfo->getPosition());
		m_pMainMenu->addChild(pinfo);
		m_pMainMenu->addChild(pLabel);
	}

	//CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("guild.switch.button",105,45);
	CCScale9Sprite* p2;
	if (tag==TAG_GUILDCOMBAT)
		p2=SystemData::getScale9SpriteByPlist("guild.switch.button.sel",105,45);
	else
		p2=SystemData::getScale9SpriteByPlist("guild.switch.button",105,45);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("guild.switch.button.sel",105,45);
	CCMenuItemSprite *pcombat =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(GuildPanel::MenuCallBack));//攻城战按钮
	if(pcombat)  
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.switch.combat");
		pLabel->setFontSize(20);
		pLabel->setColor(ccWHITE);
		pcombat->setTag(TAG_GUILDCOMBAT);
		pcombat->setPosition(SystemData::getLayoutPoint("guild.switch.combat"));
		pLabel->setPosition(pcombat->getPosition());
		m_pMainMenu->addChild(pcombat);
		m_pMainMenu->addChild(pLabel);
	}

	//CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("guild.switch.button",105,45);
	CCScale9Sprite* p3;
	if (tag==TAG_GUILDMEMBER)
		p3=SystemData::getScale9SpriteByPlist("guild.switch.button.sel",105,45);
	else
		p3=SystemData::getScale9SpriteByPlist("guild.switch.button",105,45);
	CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("guild.switch.button.sel",105,45);
	CCMenuItemSprite *pmember =CCMenuItemSprite::create(p3,pSel3,NULL,this,menu_selector(GuildPanel::MenuCallBack));//成员管理按钮
	if(pmember)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.switch.member");
		pLabel->setFontSize(20);
		pLabel->setColor(ccWHITE);
		pmember->setTag(TAG_GUILDMEMBER);
		pmember->setPosition(SystemData::getLayoutPoint("guild.switch.member"));
		pLabel->setPosition(pmember->getPosition());
		m_pMainMenu->addChild(pmember);
		m_pMainMenu->addChild(pLabel);
	}
	
	//CCScale9Sprite* p4=SystemData::getScale9SpriteByPlist("guild.switch.button",105,45);
	CCScale9Sprite* p4;
	if (tag==TAG_GUILDBROWSE)
		p4=SystemData::getScale9SpriteByPlist("guild.switch.button.sel",105,45);
	else
		p4=SystemData::getScale9SpriteByPlist("guild.switch.button",105,45);
	CCScale9Sprite* pSel4=SystemData::getScale9SpriteByPlist("guild.switch.button.sel",105,45);
	CCMenuItemSprite *pbrowse =CCMenuItemSprite::create(p4,pSel4,NULL,this,menu_selector(GuildPanel::MenuCallBack));//行会一览按钮
	if(pbrowse)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.switch.browse");
		pLabel->setFontSize(20);
		pLabel->setColor(ccWHITE);
		pbrowse->setTag(TAG_GUILDBROWSE);
		pbrowse->setPosition(SystemData::getLayoutPoint("guild.switch.browse"));
		pLabel->setPosition(pbrowse->getPosition());
		m_pMainMenu->addChild(pbrowse);
		m_pMainMenu->addChild(pLabel);
	}
}
void GuildPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		CCMenuItem* button = (CCMenuItem*)pNode;
		if (button)
		{
			button->selected();
		}

		int tag = pNode->getTag();
		selectPanel(tag);
	}
	
}

void GuildPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	/*
	if (eventName == CPEventName::MSG_FINISH)
	{
		if(source == "HandleMessageGuildMemberInfoResponse")
		{
			
		}
		else if(source == "HandleMessageCreateGuildResponse")
		{
			selectPanel(TAG_GUILDINFO,false); 
		}
		else if(source == "HandleMessageLeaveGuildResponse")
		{
			selectPanel(TAG_GUILDBROWSE);  
		}
	}
	*/
	if (eventName == CPEventName::UI_NOTIFY)
	{
		if(source == "SwitchGuildInfo")
		{
			selectPanel(TAG_GUILDINFO,false); 
		}
		else if(source == "SwitchGuildBrowse")
		{
			selectPanel(TAG_GUILDBROWSE); 
		}
		else if(source == "SwitchGuildCombat")
		{
			selectPanel(TAG_GUILDCOMBAT); 
		}
	}
}

void GuildPanel::onEnter()
{
	CPEventHelper::dispatcher(CPEventName::UI_OPEN, "GuildPanel|onEnter", "");
	BasePanel::onEnter();
}

void GuildPanel::onExit()
{
	CPEventHelper::dispatcher(CPEventName::UI_FINISH, "GuildPanel|onExit", "");
	BasePanel::onExit();
}