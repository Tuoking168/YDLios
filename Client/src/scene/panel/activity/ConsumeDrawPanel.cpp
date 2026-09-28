#include "ConsumeDrawPanel.h"
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
#include "utils/StringUtils.h"
#include "ActivityDataHelper.h"

#include "module/ModuleData.h"
#include "userdata/LayoutData.h"
#include "res/CPAnimationManager.h"
#include "controls/CPRichText.h"
#include "userdata/NPCFunctionData.h"


ConsumeDrawPanel::ConsumeDrawPanel()
	: m_updater(NULL)
{
	m_OptionsList.clear();
}

ConsumeDrawPanel::~ConsumeDrawPanel()
{
	
}

bool ConsumeDrawPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	switchView(true);
	
	return true;
}

void ConsumeDrawPanel::onCPEvent(const std::string &eventName)
{

}

void ConsumeDrawPanel::initFrame()
{
	
}
void ConsumeDrawPanel::initSprite()
{
	CCSprite* sprite1 = SystemData::getSpriteByPlist("consumedraw.sprite.activityname");
	sprite1->setAnchorPoint(CCPointZero);
	addChild(sprite1); 
	for (int i=0;i<8;i++)
	{
		CCSprite* sprite = SystemData::getSpriteByPlist("consumedraw.sprite.reward.frame");
		CCPoint point = SystemData::getLayoutPoint("consumedraw.sprite.reward"+StringUtils::toString(i));
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(point);
		addChild(sprite);
		CCLabelTTF* label = SystemData::getLabelTTF("consumedraw.label.reward.date");
		label->setHorizontalAlignment(kCCTextAlignmentCenter); 
		label->setPosition(ccp(point.x+67,point.y+108)); 
		addChild(label);

		CCSprite* doubt = SystemData::getSpriteByPlist("consumedraw.sprite.reward.doubt");
		doubt->setAnchorPoint(ccp(0.5,0));
		doubt->setPosition(ccp(point.x+67,point.y+2));
		addChild(doubt);
	}
}
void ConsumeDrawPanel::MenuCallBack(CCObject* pSender)
{
	CCLog("______________%s",__FUNCTION__);
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==Button_Detail)
		{
			switchView(false);
		}
		else if (tag==Button_Main)
		{
			switchView(true); 
		}
	}
}

void ConsumeDrawPanel::initLabels()
{
	CCLabelTTF* label1 = SystemData::getLabelTTF("consumedraw.label.rewardinfo");
	label1->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label1);
	/*
	CCLabelTTF* tRank = SystemData::getLabelTTF("guild.browse.title.rank");
	tRank->setColor(ccWHITE);
	tRank->setFontSize(18);
	tRank->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tRank); 
	*/  
}

void ConsumeDrawPanel::initButtons()
{
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("activity.button.frame",110,50); 
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",110,50);
	CCMenuItemSprite *button1 =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(ConsumeDrawPanel::MenuCallBack));
	if(button1)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("consumedraw.button.lookdetail.label");  
		pLabel->setFontSize(20);
		pLabel->setColor(ccWHITE);
		button1->setTag(Button_Detail);
		button1->setPosition(SystemData::getLayoutPoint("consumedraw.button.lookdetail"));
		pLabel->setPosition(button1->getPosition());
		m_pMainMenu->addChild(button1);
		m_pMainMenu->addChild(pLabel);
	}
}

void ConsumeDrawPanel::switchView(bool isMainView)
{
	this->removeAllChildrenWithCleanup(true);
	if (isMainView)
	{
		initFrame();
		initSprite();
		//主要menu
		m_pMainMenu = GeneralMenu::create();
		m_pMainMenu->setPosition(CCPointZero);
		m_pMainMenu->setAnchorPoint(CCPointZero);
		addChild(m_pMainMenu);
		initLabels();
		initButtons();
	}
	else
	{
		//主要menu
		m_pMainMenu = GeneralMenu::create();
		m_pMainMenu->setPosition(CCPointZero);
		m_pMainMenu->setAnchorPoint(CCPointZero);
		addChild(m_pMainMenu);
		initSubLabels();
		initSubButtons();
	}
}

void ConsumeDrawPanel::initSubLabels()
{
	CCLabelTTF* label1 = SystemData::getLabelTTF("consumedraw.detail.label.title");
	label1->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(label1);

	CCSize size1 = SystemData::getLayoutSize("consumedraw.detail.label.rule");
	CPRichText* pText1=NPCFunctionData::getBigContent(SystemData::getLayoutValue("consumedraw.detail.label.rule.tag"),size1.width,size1.height); 
	pText1->setAnchorPoint(ccp(0.5,0.5));
	pText1->setPosition(SystemData::getLayoutPoint("consumedraw.detail.label.rule"));  
	addChild(pText1);      

	CCSize size2 = SystemData::getLayoutSize("consumedraw.detail.label.multiplying");
	CPRichText* pText2=NPCFunctionData::getBigContent(SystemData::getLayoutValue("consumedraw.detail.label.multiplying.tag"),size2.width,size2.height); 
	pText2->setAnchorPoint(ccp(0.5,0.5));
	pText2->setPosition(SystemData::getLayoutPoint("consumedraw.detail.label.multiplying")); 
	addChild(pText2);
}
void ConsumeDrawPanel::initSubButtons()
{
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("activity.button.frame",110,50); 
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",110,50);
	CCMenuItemSprite *button1 =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(ConsumeDrawPanel::MenuCallBack));
	if(button1)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("consumedraw.detail.button.ok.label");  
		pLabel->setFontSize(20);
		pLabel->setColor(ccWHITE);
		button1->setTag(Button_Main);
		button1->setPosition(SystemData::getLayoutPoint("consumedraw.detail.button.ok"));
		pLabel->setPosition(button1->getPosition());
		m_pMainMenu->addChild(button1);
		m_pMainMenu->addChild(pLabel);
	}
}