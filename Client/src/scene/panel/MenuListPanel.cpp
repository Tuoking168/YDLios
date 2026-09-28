#include "MenuListPanel.h"
#include "EntityDefinition.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "event/EventProtocol.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"

#include "userdata/netdata/GameRole.h"

#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"
#include "ext/CCMenuEx.h"
#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/SlideTable.h"

#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "controls/CPItemComponents.h"
#include "event/CPEventHelper.h"
#include "controls/CPNodeHelper.h"

#include "utils/MacroUtils.h"


MenuListPanel::MenuListPanel()
	: m_updater(NULL)
	,m_pRightMgr(NULL)
	,m_DefaultSelected(NULL)
	,m_SwitchMenu(NULL)
{
	m_OptionsList.clear();
}

MenuListPanel::~MenuListPanel()
{
	
}

bool MenuListPanel::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}

	OptionsHelper::initAllOptionsList(m_OptionsList,dataTableName());
	
	initFrame();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	initSwitchView();
	
	return true;
}

void MenuListPanel::onCPEvent(const std::string &eventName)
{

}
void MenuListPanel::initSwitchView()
{
	reloadSwitchMenu();
}

void MenuListPanel::initFrame()
{
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",796,436);
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(ccp(2,2));	
	addChild(bg);
	//右侧框
	CCScale9Sprite *pRightborder=SystemData::getScale9SpriteByPlist("guild.menuback",595,420);
	pRightborder->setAnchorPoint(CCPointZero);  
	pRightborder->setPosition(ccp(195,10)); 
	addChild(pRightborder);	
	//列表背景
	CCScale9Sprite *pTable=SystemData::getScale9SpriteByPlist("guild.menuback",175,420);
	pTable->setAnchorPoint(CCPointZero);  
	pTable->setPosition(ccp(10,10)); 
	addChild(pTable);	
	//右侧panel管理
	m_pRightMgr=CCNode::create();
	m_pRightMgr->setAnchorPoint(CCPointZero);  
	m_pRightMgr->setPosition(ccp(195,10)); 
	addChild(m_pRightMgr);	
}

void MenuListPanel::MenuCallBack(CCObject* pSender)
{
	CCLog("______________%s",__FUNCTION__);
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		if (m_pRightMgr)
		{
			m_pRightMgr->removeAllChildrenWithCleanup(true);
		}
		int tag = pNode->getTag();
	
		if (m_DefaultSelected)
		{
			if (defaultSwitch()!=tag)
			{
				m_DefaultSelected->unselected();
				m_DefaultSelected = NULL;
			}
		}
	
		onSwitch(tag);
	}
}
const std::string MenuListPanel::dataTableName()
{
	return "";
}
void MenuListPanel::onSwitch(int tag)
{
	CCLog("______________%s__%d",__FUNCTION__,tag);
}
void MenuListPanel::addPanel(CCNode* child)
{
	if (m_pRightMgr && child)
	{
		m_pRightMgr->addChild(child);
	}
}

int MenuListPanel::defaultSwitch()
{
	int data1=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
	int data4=CPEventHelper::getEventIntData(CPEventData::VALUE_5);
	if (data4==1)
	{
		return data1-1;
	}
	
	return OptionsHelper::getDefaultTag();
}
void MenuListPanel::reloadSwitchMenu(bool selectDefault)
{
	if (m_SwitchMenu)
	{
		m_SwitchMenu->removeFromParentAndCleanup(true);
		m_SwitchMenu = NULL;
	}
	CCSize pPlacardSize = CCSizeMake(175,420);
	CCPoint pPlacardPoint = ccp(10,10);
	m_SwitchMenu = CPItemComponents::create(pPlacardSize, new CPLayoutList(CCSizeZero,true));
	m_SwitchMenu->setPosition(pPlacardPoint);
	m_SwitchMenu->setAnchorPoint(CCPointZero);
	addChild(m_SwitchMenu);
	
	CPForeach(iter, OptionsList, m_OptionsList)
	{
		OptionsInfo option = *iter;
		CCScale9Sprite* p1;
		CCScale9Sprite* pSel1;
		bool hasResource = false;
		if (option.resource.length()>0&&option.resource!="0")
		{
			std::string p1String = option.resource + ".png";
			std::string pSel1String = option.resource + "_sel.png";
			p1=CCScale9Sprite::createWithSpriteFrameName(p1String.c_str());
			pSel1=CCScale9Sprite::createWithSpriteFrameName(pSel1String.c_str());
			hasResource = true;
		}
		else
		{
			p1=SystemData::getScale9SpriteByPlist("option.normal.bkg",178,34);
			pSel1=SystemData::getScale9SpriteByPlist("option.normal.bkg.sel",178,34);
			hasResource = false;
		}
		CCMenuItemSprite *optionButton =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(MenuListPanel::MenuCallBack)); 
		if(optionButton)
		{ 
			CCLabelTTF *pLabel=SystemData::getLabelTTF("option.normal.label.text");
			pLabel->setFontSize(18);
			pLabel->setColor(ccc3(0,186,255));
			pLabel->setAnchorPoint(ccp(0.5,0.5));
			pLabel->setPosition(ccp(optionButton->getContentSize().width/2,optionButton->getContentSize().height/2));
			pLabel->setString(option.title.c_str());
			if (hasResource)
			{
				pLabel->setVisible(false);
			}
			else
			{
				pLabel->setVisible(true);
			}
			optionButton->addChild(pLabel);
			m_SwitchMenu->addItem(optionButton);
			optionButton->setTag(option.idx); 

			if (selectDefault&&option.idx==defaultSwitch()&&!optionButton->isSelected())
			{
				m_DefaultSelected = optionButton;
				m_DefaultSelected->selected();
				onSwitch(option.idx);
			}
		}
	}
}

void MenuListPanel::addListItem(int i )
{
	if (i>=m_OptionsList.size())
	{
		return;
	}
	OptionsInfo option = m_OptionsList[i];
	CCScale9Sprite* p1;
	CCScale9Sprite* pSel1;
	bool hasResource = false;
	if (option.resource.length()>0&&option.resource!="0")
	{
		std::string p1String = option.resource + ".png";
		std::string pSel1String = option.resource + "_sel.png";
		p1 = CCScale9Sprite::createWithSpriteFrameName(p1String.c_str());
		pSel1 = CCScale9Sprite::createWithSpriteFrameName(pSel1String.c_str());
		hasResource = true;
	}
	else
	{
		p1=SystemData::getScale9SpriteByPlist("option.normal.bkg",178,34);
		pSel1=SystemData::getScale9SpriteByPlist("option.normal.bkg.sel",178,34);
		hasResource = false;
	}
	CCMenuItemSprite *optionButton =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(MenuListPanel::MenuCallBack));
	if(optionButton)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("option.normal.label.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccc3(0,186,255));
		pLabel->setAnchorPoint(ccp(0.5,0.5));
		pLabel->setPosition(ccp(optionButton->getContentSize().width/2,optionButton->getContentSize().height/2));
		pLabel->setString(option.title.c_str());
		if (hasResource)
		{
			pLabel->setVisible(false);
		}
		else
		{
			pLabel->setVisible(true);
		}
		optionButton->addChild(pLabel);
		m_SwitchMenu->addItem(optionButton);
		optionButton->setTag(option.idx); 

		if (i==defaultSwitch())
		{
			m_DefaultSelected = optionButton;
		}

	}
}
void MenuListPanel::addListFinish()
{
	int data1=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
	int data4=CPEventHelper::getEventIntData(CPEventData::VALUE_5);
	if (data4==1)
	{
		onSwitch(data1-1);
	}
	else
	{
		if (m_DefaultSelected)
		{
			m_DefaultSelected->selected();
			onSwitch(defaultSwitch());
		}
	}
}

void MenuListPanel::initCell(CCTableViewCell *cell)
{
	int idx = cell->getIdx();

	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("option.normal.bkg",178,34);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("option.normal.bkg.sel",178,34);
	CCMenuItemSprite *optionButton =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(MenuListPanel::MenuCallBack));
	if(optionButton)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("option.normal.label.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccc3(0,186,255));
		pLabel->setAnchorPoint(ccp(0.5,0.5));
		optionButton->setAnchorPoint(ccp(0.5,0.5));
		optionButton->setPosition(ccp(89,17));
		pLabel->setPosition(optionButton->getPosition());
		optionButton->setTag(Cell_Start+idx);
		cell->addChild(optionButton);
		cell->addChild(pLabel); 
	}
}

void MenuListPanel::onEnter()
{
	FullScreenPanel::onEnter();
	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}
