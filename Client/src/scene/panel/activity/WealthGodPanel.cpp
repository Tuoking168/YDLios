#include "WealthGodPanel.h"
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

#include "utils/StringUtils.h"
#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "controls/CPItemComponents.h"
#include "event/CPEventHelper.h"
#include "ActivityDataHelper.h"

#include "module/ModuleData.h"
#include "userdata/LayoutData.h"
#include "res/CPAnimationManager.h"

ControlDiceAlert::ControlDiceAlert():
	m_pMainMenu(NULL),
	m_LabelInfo(NULL),
	m_LabelPage(NULL),
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
	m_PressConfirm(false),
	m_selIndex(-1)
{

}

ControlDiceAlert::~ControlDiceAlert()
{

}

ControlDiceAlert* ControlDiceAlert::create(CCSize alertSize)
{
	ControlDiceAlert* pPanel = new ControlDiceAlert();
	if(pPanel && pPanel->init("",alertSize))
	{
		pPanel->autorelease();
		return pPanel;
	}
	else
	{
		CCLog("ControlDiceAlert create failed!");
	}
	return NULL;
}


bool ControlDiceAlert::init( const char* filename ,CCSize alertSize)
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_Size = alertSize;

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
	
	this->setTouchEnabled(true);

	return true;
}



void ControlDiceAlert::MenuCallBack( CCObject* pSender )
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

void ControlDiceAlert::closeSelf()
{
	//Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);	
	this->removeFromParentAndCleanup(true);
}

void ControlDiceAlert::initFrame()
{
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
}

void ControlDiceAlert::initLabels()
{
	/*
	m_Title =  SystemData::getLabelTTF("popalert.normal.label.title"); 
	m_Title->setColor(ccYELLOW);
	m_Title->setFontSize(22);    
	m_Title->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_Title->setDimensions(CCSizeMake(SystemData::getLayoutValue("popalert.normal.label.title.w"),SystemData::getLayoutValue("popalert.normal.label.title.h")));
	//addChild(m_Title); 
	m_Title->setAnchorPoint(ccp(0,1));
	m_Title->setPosition(ccp(0,m_Size.height));
	m_AlertBg->addChild(m_Title);

	m_LabelInfo =  SystemData::getLabelTTF("popalert.normal.label.alert"); 
	m_LabelInfo->setColor(ccWHITE);
	m_LabelInfo->setFontSize(18);    
	m_LabelInfo->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_LabelInfo->setDimensions(CCSizeMake(SystemData::getLayoutValue("popalert.normal.label.alert.w"),SystemData::getLayoutValue("popalert.normal.label.alert.h")));
	addChild(m_LabelInfo); 
	*/
}

void ControlDiceAlert::initButtons()
{
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("popalert.normal.button.close");
	pClose->setTag(Tag_Close);
	pClose->setTarget(this,menu_selector(ControlDiceAlert::MenuCallBack));
	pClose->setAnchorPoint(ccp(1,1));
	pClose->setPosition(ccp(m_Size.width,m_Size.height));
	m_pMainMenu->addChild(pClose);

	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("guild.info.placard.button",100,45);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",100,45);
	m_MenuConfirm =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(ControlDiceAlert::MenuCallBack));
	if(m_MenuConfirm)
	{
		m_ConfirmTitle=SystemData::getLabelTTF("popalert.normal.button.confirm.text");
		m_ConfirmTitle->setFontSize(18);
		m_ConfirmTitle->setColor(ccWHITE);
		m_MenuConfirm->setTag(Tag_Confirm);
		m_MenuConfirm->setPosition(/*SystemData::getLayoutPoint("popalert.normal.button.confirm")*/ccp(m_Size.width/4,m_Size.height/9));
		m_ConfirmTitle->setPosition(m_MenuConfirm->getPosition());
		m_pMainMenu->addChild(m_MenuConfirm);
		m_pMainMenu->addChild(m_ConfirmTitle);
	}

	CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("guild.info.placard.button",100,45);
	CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",100,45);
	m_MenuCancel =CCMenuItemSprite::create(p3,pSel3,NULL,this,menu_selector(ControlDiceAlert::MenuCallBack));
	if(m_MenuCancel)
	{
		m_CancelTitle=SystemData::getLabelTTF("popalert.normal.button.cancel.text");
		m_CancelTitle->setFontSize(18);
		m_CancelTitle->setColor(ccWHITE);
		m_MenuCancel->setTag(Tag_Cancel);
		m_MenuCancel->setPosition(/*SystemData::getLayoutPoint("popalert.normal.button.cancel")*/ccp(m_Size.width/4*3,m_Size.height/9));
		m_CancelTitle->setPosition(m_MenuCancel->getPosition());
		m_pMainMenu->addChild(m_MenuCancel);
		m_pMainMenu->addChild(m_CancelTitle);
	}

}

void ControlDiceAlert::setConfirmTarget(CCObject *rec, SEL_MenuHandler selector)
{
	m_pListener = rec;
    m_pfnSelector = selector;
}
void ControlDiceAlert::handleConfirmPressed()
{
	if (m_pListener && m_pfnSelector)
    {
		 (m_pListener->*m_pfnSelector)(this);
	}
}
void ControlDiceAlert::setCancelTarget(CCObject *rec, SEL_MenuHandler selector)
{
	m_CancelListener = rec;
	m_CancelSelector = selector;
}
void ControlDiceAlert::handleCancelPressed()
{
	if (m_CancelListener && m_CancelSelector)
	{
		(m_CancelListener->*m_CancelSelector)(this);
	}
}
void ControlDiceAlert::setString(std::string alert)
{
	if (m_LabelInfo)
	{
		m_LabelInfo->setString(alert.c_str());
	}
}
void ControlDiceAlert::setConfirmTitle(std::string cTitle)
{
	if (m_ConfirmTitle)
	{
		m_ConfirmTitle->setString(cTitle.c_str());
		if (m_MenuConfirm)
		{
			float pWidth = m_ConfirmTitle->getContentSize().width;
			pWidth=(pWidth<80)?100:(pWidth+20);
			CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("guild.info.placard.button",pWidth,45);
			CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",pWidth,45);
			m_MenuConfirm->setNormalImage(p3);     
			m_MenuConfirm->setSelectedImage(pSel3);     
		} 
	}
}
void ControlDiceAlert::setCancelTitle(std::string cTitle)
{
	if (m_CancelTitle)
	{
		m_CancelTitle->setString(cTitle.c_str());
		if (m_MenuCancel)
		{
			float pWidth = m_CancelTitle->getContentSize().width;
			pWidth=(pWidth<80)?100:(pWidth+20);
			CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("guild.info.placard.button",pWidth,45);
			CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",pWidth,45);
			m_MenuCancel->setNormalImage(p3);
			m_MenuCancel->setSelectedImage(pSel3);
		}
	}
}
void ControlDiceAlert::setTitle(std::string cTitle)
{
	if (m_Title)
	{
		m_Title->setString(cTitle.c_str());
	}
}
bool ControlDiceAlert::isPressConfirm()
{
	return m_PressConfirm;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WealthGodPanel::WealthGodPanel()
	: m_updater(NULL)
{
	
}

WealthGodPanel::~WealthGodPanel()
{
	
}

bool WealthGodPanel::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}
	
	initFrame();
	initSprite();
	
	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	initLabels();
	initButtons();
	
	return true;
}

void WealthGodPanel::onCPEvent(const std::string &eventName)
{

}

void WealthGodPanel::initFrame()
{
	CCSize bgSize = SystemData::getLayoutSize("wealthgod.frame.bigbg");
	CCPoint bgPoint = SystemData::getLayoutPoint("wealthgod.frame.bigbg");
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",bgSize.width,bgSize.height);
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(bgPoint);
	addChild(bg);

	for (int i=0;i<6;i++)
	{
		CCSize size = SystemData::getLayoutSize("wealthgod.frame.bg"+StringUtils::toString(i));
		CCPoint point = SystemData::getLayoutPoint("wealthgod.frame.bg"+StringUtils::toString(i));
		CCScale9Sprite *frame=SystemData::getScale9SpriteByPlist("guild.menuback",size.width,size.height);
		frame->setAnchorPoint(CCPointZero);  
		frame->setPosition(point); 
		addChild(frame);	
	}
}
void WealthGodPanel::initSprite()
{
	int gridCnt = SystemData::getLayoutValue("wealthgod.sprite.grid.count");
	int direction=0;		//1:上 2:下 3:左 4:右
	CCPoint point = SystemData::getLayoutPoint("wealthgod.sprite.grid");
	for (int i=0;i<gridCnt;i++)
	{
		std::string gridColor = "green";
		if (i==0)
			gridColor = "blue";
		if (i==gridCnt-1)
			gridColor = "red";
		CCSprite* sprite = SystemData::getSpriteByPlist("wealthgod.sprite.grid."+gridColor);
		sprite->setAnchorPoint(CCPointZero);
		sprite->setTag(Grid_Start+i);
		addChild(sprite);
		CCSize pSize = sprite->getContentSize();
		switch (direction) 
		{
		case 1:
			{
				point=ccp(point.x,point.y+pSize.height);
				break;
			}
		case 2:
			{
				point=ccp(point.x,point.y-pSize.height);
				break;
			}
		case 3:
			{
				point=ccp(point.x-pSize.width,point.y);
				break;
			}
		case 4:
			{
				point=ccp(point.x+pSize.width,point.y);
				break;
			}
		default:
			break;
		}
		CCLog("_____%d_____<%f,%f>,%d",i,point.x,point.y,direction);
		sprite->setPosition(point); 

		int nextDir = SystemData::getLayoutValue("wealthgod.sprite.grid"+StringUtils::toString(i)+".direction");
		if (nextDir>0)
		{
			direction = nextDir;
		}
	}

	CCSprite* sprite1 = SystemData::getSpriteByPlist("wealthgod.sprite.arrowright");
	sprite1->setAnchorPoint(CCPointZero);
	addChild(sprite1); 
	CCSprite* sprite2 = SystemData::getSpriteByPlist("wealthgod.sprite.arrowleft");
	sprite2->setAnchorPoint(CCPointZero);
	sprite2->setFlipX(true);
	addChild(sprite2); 
	CCSprite* sprite3 = SystemData::getSpriteByPlist("wealthgod.sprite.start");
	sprite3->setAnchorPoint(CCPointZero);
	addChild(sprite3); 
	CCSprite* sprite4 = SystemData::getSpriteByPlist("wealthgod.sprite.end");
	sprite4->setAnchorPoint(CCPointZero);
	addChild(sprite4); 
	CCSprite* sprite5 = SystemData::getSpriteByPlist("wealthgod.sprite.questiongrid");
	sprite5->setAnchorPoint(CCPointZero);
	addChild(sprite5); 
	CCSprite* sprite6 = SystemData::getSpriteByPlist("wealthgod.sprite.questionmark");
	sprite6->setAnchorPoint(CCPointZero);
	addChild(sprite6); 
	CCSprite* sprite7 = SystemData::getSpriteByPlist("wealthgod.sprite.dice1");
	sprite7->setPosition(SystemData::getLayoutPoint("wealthgod.sprite.dice"));
	sprite7->setAnchorPoint(CCPointZero);
	addChild(sprite7); 
}

void WealthGodPanel::MenuCallBack(CCObject* pSender)
{
	CCLog("______________%s",__FUNCTION__);
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag(); 
		switch (tag)
		{
		case Button_Control_Dice:
			{
				ControlDiceAlert* panel = ControlDiceAlert::create(ccp(625,260));
				addChild(panel);
				break;
			}
		default:
			break;
		}
	}
}

void WealthGodPanel::initLabels()
{
	for (int i=0;i<4;i++)
	{
		CCLabelTTF* label = SystemData::getLabelTTF("wealthgod.label.label"+StringUtils::toString(i));
		label->setHorizontalAlignment(kCCTextAlignmentCenter);      
		addChild(label);
	}
	 
	CCLabelTTF* label1 = SystemData::getLabelTTF("wealthgod.label.round");
	label1->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(label1);
	CCLabelTTF* label2 = SystemData::getLabelTTF("wealthgod.label.cooldown");
	label2->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(label2);
	CCLabelTTF* label3 = SystemData::getLabelTTF("wealthgod.label.remain");
	label3->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(label3);
}

void WealthGodPanel::initButtons()
{
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("activity.button.frame",100,45);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",100,45);
	CCMenuItemSprite *button1 =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(WealthGodPanel::MenuCallBack));
	if(button1)
	{   
		CCLabelTTF *pLabel=SystemData::getLabelTTF("wealthgod.button.controldice.label");  
		pLabel->setFontSize(16);
		pLabel->setColor(ccWHITE);
		button1->setTag(Button_Control_Dice);    
		button1->setPosition(SystemData::getLayoutPoint("wealthgod.button.controldice"));
		pLabel->setPosition(button1->getPosition());
		m_pMainMenu->addChild(button1);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("activity.button.frame",100,45);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",100,45);
	CCMenuItemSprite *button2 =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(WealthGodPanel::MenuCallBack));
	if(button2)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("wealthgod.button.randdice.label");
		pLabel->setFontSize(16);
		pLabel->setColor(ccWHITE);
		//button->setTag(Tag_Detail);    
		button2->setPosition(SystemData::getLayoutPoint("wealthgod.button.randdice"));
		pLabel->setPosition(button2->getPosition());
		m_pMainMenu->addChild(button2);
		m_pMainMenu->addChild(pLabel);
	}

	CCMenuItemImage* button3 = SystemData::getMenuItemImageByPlist("wealthgod.button.next");
	button3->setTarget(this,menu_selector(WealthGodPanel::MenuCallBack));
	button3->setAnchorPoint(CCPointZero);
	m_pMainMenu->addChild(button3); 

	CCMenuItemImage* button4 = SystemData::getMenuItemImageByPlist("wealthgod.button.add");
	button4->setTarget(this,menu_selector(WealthGodPanel::MenuCallBack));
	button4->setAnchorPoint(CCPointZero);
	m_pMainMenu->addChild(button4); 
	/*
	for (int i=0;i<5;i++)
	{
		CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.placard.button",80,35);
		CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",80,35);
		CCMenuItemSprite *button =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(WealthGodPanel::MenuCallBack));
		if(button)
		{ 
			CCLabelTTF *pLabel=SystemData::getLabelTTF("everydaysalary.button.sign"+StringUtils::toString(i)+".label");
			pLabel->setFontSize(16);
			pLabel->setColor(ccWHITE);
			//button->setTag(Tag_Detail);    
			button->setPosition(SystemData::getLayoutPoint("everydaysalary.button.sign"+StringUtils::toString(i)));
			pLabel->setPosition(button->getPosition());
			m_pMainMenu->addChild(button);
			m_pMainMenu->addChild(pLabel);
		}
	}
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.button",80,35);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.button.sel",80,35);
	CCMenuItemSprite *button1 =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(WealthGodPanel::MenuCallBack));
	if(button1)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("everydaysalary.button.signreward.label");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		//button1->setTag(Tag_Detail);
		button1->setPosition(SystemData::getLayoutPoint("everydaysalary.button.signreward"));
		pLabel->setPosition(button1->getPosition());
		m_pMainMenu->addChild(button1);
		m_pMainMenu->addChild(pLabel);
	}
	CCMenuItemImage* button2 = SystemData::getMenuItemImageByPlist("everydaysalary.button.getreward");
	button2->setTarget(this,menu_selector(WealthGodPanel::MenuCallBack));
	button2->setAnchorPoint(CCPointZero);
	m_pMainMenu->addChild(button2);
	*/
}
