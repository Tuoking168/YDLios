#include "ReliveAlertPanel.h"
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
#include "utils/StringUtils.h"
#include "controls/CPNodeHelper.h"
#include "event/CPEventHelper.h"

//-----------------------------------------------------------------------------------------------------------//


ReliveAlertPanel::ReliveAlertPanel():
	m_pMainMenu(NULL),
	m_pListener(NULL),
	m_pfnSelector(NULL),
	m_CancelListener(NULL),
	m_CancelSelector(NULL)
	, m_ReasonLabel(NULL)
	, m_TimeLabel(NULL)
	, m_ReliveTime(120.0f)
	, m_ReliveType(0)
	, m_Reason("")
{

}

ReliveAlertPanel::~ReliveAlertPanel()
{

}

ReliveAlertPanel* ReliveAlertPanel::create(std::string pReason,int pType)
{
	ReliveAlertPanel* pPanel = new ReliveAlertPanel();
	if(pPanel && pPanel->init(pReason,pType))
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

void ReliveAlertPanel::onEnter()
{
	BasePanel::onEnter();
	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}

bool ReliveAlertPanel::init(std::string pReason,int pType)
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_Reason = pReason;
	m_ReliveType = pType;



	initFrame();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	m_pborder->addChild(m_pMainMenu);

	initLabels();
	initButtons();

	this->schedule(schedule_selector(ReliveAlertPanel::update));

	return true;
}



void ReliveAlertPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==Button_By_Gold)
		{
			reliveByType(Button_By_Gold);
		}
		else if (tag==Button_Free)
		{
			reliveByType(Button_Free);
		}
	}
}
void ReliveAlertPanel::reliveByType(int pType)
{
	if (pType==Button_By_Gold)
	{
		MsgReviveEntityRequest* req = new MsgReviveEntityRequest;	
		req->eid=GameData::s_user->m_pMainRole->mID;
		req->type=Entity::revive_dead;
		HandleMessage::sendMessage(req);
	}
	else if (pType==Button_Free)
	{
		MsgReviveEntityRequest* req = new MsgReviveEntityRequest;
		req->eid=GameData::s_user->m_pMainRole->mID;
		req->type=Entity::revive_safe;
		HandleMessage::sendMessage(req);	
		//closeSelf();
	}	
}
void ReliveAlertPanel::closeSelf()
{
	//Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);	
	this->removeFromParentAndCleanup(true);
}

/**
 * ReliveAlertPanel::initFrame() 初始化函数
 * 初始化复活提示面板的框架布局和UI元素
 * 功能：设置面板尺寸，添加背景遮罩，创建边框面板
 */
void ReliveAlertPanel::initFrame()
{
	// 1. 设置面板的宽度和高度（基于1200x520的设计分辨率）
	m_nWidth = 800;  // 注释说明：对应800全屏的换算值
	m_nHeight = 480;  // 注释说明：对应480的换算值
	
	// 2. 添加覆盖层（通常为半透明黑色遮罩，用于突出显示当前面板）
	addCover();
	
	// 3. 创建并添加边框面板
	// 从plist资源获取九宫格精灵，用作对话框边框背景
	// 参数说明：
	// "ui_float_menu_border" - 资源名称
	// SystemData::getLayoutValue("ui_float_menu_size.w") - 从布局配置获取宽度
	// SystemData::getLayoutValue("ui_float_menu_size.h") - 从布局配置获取高度
	m_pborder = SystemData::getScale9SpriteByPlist(
		"ui_float_menu_border",
		SystemData::getLayoutValue("ui_float_menu_size.w"),//复活ui布局
		SystemData::getLayoutValue("ui_float_menu_size.h")
	);
	
	// 4. 设置边框面板的锚点为居中（0.5, 0.5）
	m_pborder->setAnchorPoint(ccp(0.5, 0.5));
	
	// 5. 设置边框面板的位置（从布局配置获取）
	m_pborder->setPosition(SystemData::getLayoutPoint("relive.frame.bigbg"));
	
	// 6. 将边框面板添加到当前面板中
	addChild(m_pborder);
}
void ReliveAlertPanel::initLabels()
{
	CCLabelTTF* title = SystemData::getLabelTTF("relive.label.title");
	title->setHorizontalAlignment(kCCTextAlignmentCenter); 
	m_pborder->addChild(title); 

	CCSize size1 = SystemData::getLayoutSize("relive.label.reason.range"); 
	m_ReasonLabel=CPRichText::create(size1.width,size1.height); 
	CCPoint labelPoint1=SystemData::getLayoutPoint("relive.label.reason");
	m_ReasonLabel->setAnchorPoint(ccp(0,0.5));
	m_ReasonLabel->setPosition(labelPoint1); 
	m_pborder->addChild(m_ReasonLabel);
	setReason(m_Reason);
// 	std::string pRichStr1 = SystemData::getLayoutString("relive.label.reason");
// 	CPRichTextItemLabel* pText1=new CPRichTextItemLabel(pRichStr1,"",18,ccYELLOW);
// 	pRichText1->addItem(pText1);

	if (m_ReliveType != Relive_Orientation)
	{
	  CCSize size2 = SystemData::getLayoutSize("relive.label.relivebygold.range"); 
	  CPRichText* pRichText2=CPRichText::create(size2.width,size2.height); 
	  CCPoint labelPoint2=SystemData::getLayoutPoint("relive.label.relivebygold");
	  pRichText2->setAnchorPoint(ccp(0,0.5));
	  pRichText2->setPosition(labelPoint2); 
	  m_pborder->addChild(pRichText2);
	
		for (int i = 0; i < 5; i++)
		{
			std::string pRichStr = SystemData::getLayoutString("relive.label.relivebygold"+StringUtils::toString(i+1));
			CPRichTextItemLabel* pText=new CPRichTextItemLabel(pRichStr,"",18,i%2?ccYELLOW:ccWHITE);
			pRichText2->addItem(pText);
		}
	}
	
	m_TimeLabel = SystemData::getLabelTTF("relive.label.relivesafe");
	m_TimeLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
	if (m_ReliveType == Relive_Orientation)
	{
		m_TimeLabel->setPosition(SystemData::getLayoutPoint("relive.label.notusegold.pos"));
	}
	m_pborder->addChild(m_TimeLabel);
	setTime(m_ReliveTime);

	CCLabelTTF* label1 = SystemData::getLabelTTF("relive.label.notice");
	label1->setHorizontalAlignment(kCCTextAlignmentCenter); 
	m_pborder->addChild(label1);
}

void ReliveAlertPanel::initButtons()
{
	bool goldEnable = true;
	std::string freeName = SystemData::getLayoutString("Label3");
	if (m_ReliveType==Relive_Normal ||
		m_ReliveType==Relive_Instance)
	{
		goldEnable = true;

		// right button
		if (m_ReliveType == Relive_Normal)
		{
			freeName = SystemData::getLayoutString("Label2");
		}
		else
		{
			freeName = SystemData::getLayoutString("Label3");
		}
	}	
	else if (m_ReliveType == Relive_Orientation)
	{
		goldEnable = false;
		freeName = SystemData::getLayoutString("Label4");
	}

	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("activity.button.frame",120,45);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",120,45); 
	CCMenuItemSprite *button1 =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(ReliveAlertPanel::MenuCallBack));
	if(button1 && goldEnable == true)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("Label1"); 
		pLabel->setFontSize(20); 
		pLabel->setColor(ccWHITE);
		button1->setTag(Button_By_Gold);        
		button1->setPosition(SystemData::getLayoutPoint("relive.button.relivebygold.pos"));
		pLabel->setPosition(button1->getPosition()); 
		m_pMainMenu->addChild(button1);  
		m_pMainMenu->addChild(pLabel);

		button1->setEnabled(goldEnable);
	}

	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("activity.button.frame",120,45);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",120,45); 
	CCMenuItemSprite *button2 =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(ReliveAlertPanel::MenuCallBack));
	if(button2)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("Label3"); 
		pLabel->setFontSize(20);  
		pLabel->setColor(ccWHITE);
		button2->setTag(Button_Free);
		if (goldEnable == false)
		{
			button2->setPosition(SystemData::getLayoutPoint("relive.button.notusegold.pos"));
		}
		else
		{
           button2->setPosition(SystemData::getLayoutPoint("relive.button.relivesafe.pos"));
		}		
		pLabel->setPosition(button2->getPosition()); 
		m_pMainMenu->addChild(button2); 
		m_pMainMenu->addChild(pLabel);

		pLabel->setString(freeName.c_str());
	}
}

void ReliveAlertPanel::setConfirmTarget(CCObject *rec, SEL_MenuHandler selector)
{
	m_pListener = rec;
    m_pfnSelector = selector;
}
void ReliveAlertPanel::handleConfirmPressed()
{
	if (m_pListener && m_pfnSelector)
    {
		 (m_pListener->*m_pfnSelector)(this);
	}
}
void ReliveAlertPanel::setCancelTarget(CCObject *rec, SEL_MenuHandler selector)
{
	m_CancelListener = rec;
	m_CancelSelector = selector;
}
void ReliveAlertPanel::handleCancelPressed()
{
	if (m_CancelListener && m_CancelSelector)
	{
		(m_CancelListener->*m_CancelSelector)(this);
	}
}

void ReliveAlertPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if(source == "ReliveSITU")
		{
			MsgReviveEntityRequest* req = new MsgReviveEntityRequest;	
			req->eid=GameData::s_user->m_pMainRole->mID;
			req->type=Entity::revive_dead;
			HandleMessage::sendMessage(req);
		}
	}
}


void ReliveAlertPanel::update(float dt)
{
	m_ReliveTime-=dt;
	if (m_ReliveTime<0)
	{
		m_ReliveTime=0;
		setTime((int)m_ReliveTime); 
		reliveByType(Button_Free);
		unschedule(schedule_selector(ReliveAlertPanel::update));
		return;
	}
	setTime((int)m_ReliveTime); 
}
void ReliveAlertPanel::setReason(std::string pReason)
{
	if (!m_ReasonLabel)
		return;
	m_ReasonLabel->cleanup();
	std::string pRichStr1 = SystemData::getLayoutString("relive.label.reason1");
	CPRichTextItemLabel* pText1=new CPRichTextItemLabel(pRichStr1,"",18,ccWHITE);
	m_ReasonLabel->addItem(pText1);
	CPRichTextItemLabel* pText2=new CPRichTextItemLabel(pReason,"",18,ccRED);
	m_ReasonLabel->addItem(pText2);
	std::string pRichStr3 = SystemData::getLayoutString("relive.label.reason3");
	CPRichTextItemLabel* pText3=new CPRichTextItemLabel(pRichStr3,"",18,ccWHITE);
	m_ReasonLabel->addItem(pText3);
}
void ReliveAlertPanel::setTime(int dt)
{
	if (!m_TimeLabel)
		return;
	std::string pStr1 = SystemData::getLayoutString("relive.label.relivesafe.min");
	std::string pStr2 = SystemData::getLayoutString("relive.label.relivesafe.sec");
	std::string pStr3 = SystemData::getLayoutString("relive.label.relivesafe");
	int min=dt/60;
	int sec=dt%60;
	std::string pStr = StringUtils::toString(min)+pStr1+StringUtils::toString(sec)+pStr2+pStr3;
	m_TimeLabel->setString(pStr.c_str());
}