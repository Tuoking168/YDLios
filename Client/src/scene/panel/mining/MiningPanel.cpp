#include "MiningPanel.h"
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
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "ModuleData.h"


//-----------------------------------------------------------------------------------------------------------//


MiningPanel::MiningPanel():
	m_pMainMenu(NULL),
	m_LabelInfo(NULL),
	m_LabelPage(NULL),
	m_selIndex(-1),
	m_pListener(NULL),
	m_pfnSelector(NULL)
{
	m_reward.clear();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

MiningPanel::~MiningPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

MiningPanel* MiningPanel::create()
{
	MiningPanel* pPanel = new MiningPanel();
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


bool MiningPanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}

	initFrame();

	//Ö÷Òªmenu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	initLabels();
	initButtons();
	
	this->setTouchEnabled(true);

	return true;
}



void MiningPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==Tag_Close)
		{
			closeSelf();	
		}
	}
}

void MiningPanel::closeSelf()
{
	//Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);	
	this->removeFromParentAndCleanup(true);
}

void MiningPanel::initFrame()
{
	CCSize bigBgSize = SystemData::getLayoutSize("mining.bigbg");
	CCScale9Sprite* bigBg=SystemData::getScale9SpriteByPlist("mining.bigbg",bigBgSize.width,bigBgSize.height);
	addChild(bigBg);

	CCSize bigMainSize = SystemData::getLayoutSize("mining.mainbg");
	CCScale9Sprite* mainBg=SystemData::getScale9SpriteByPlist("mining.mainbg",bigMainSize.width,bigMainSize.height);
	addChild(mainBg); 
	 
	CCSize titleSize = SystemData::getLayoutSize("mining.titlebg");
	CCScale9Sprite* titleBg=SystemData::getScale9SpriteByPlist("mining.titlebg",titleSize.width,titleSize.height);
	addChild(titleBg);
	 
	CCSize separateSize = SystemData::getLayoutSize("mining.sprite.separate");
	CCScale9Sprite* fSeparate=SystemData::getScale9SpriteByPlist("mining.sprite.separate",separateSize.width,separateSize.height);
	addChild(fSeparate);    
	
}

void MiningPanel::initLabels()
{
	CCLabelTTF* tTitle = SystemData::getLabelTTF("mining.title");
	tTitle->setColor(ccYELLOW);
	tTitle->setFontSize(28);     
	tTitle->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tTitle); 

	CCLabelTTF* tMoney = SystemData::getLabelTTF("mining.label.money");
	tMoney->setColor(ccORANGE);
	tMoney->setFontSize(18);     
	tMoney->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tMoney);

	CCLabelTTF* tMaterial = SystemData::getLabelTTF("mining.label.material");
	tMaterial->setColor(ccORANGE);
	tMaterial->setFontSize(18);     
	tMaterial->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tMaterial);

	CCLabelTTF* tRare = SystemData::getLabelTTF("mining.label.rare");
	tRare->setColor(ccORANGE);
	tRare->setFontSize(18);     
	tRare->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tRare);

	CCLabelTTF* tBagsurplus = SystemData::getLabelTTF("mining.label.bagsurplus");
	tBagsurplus->setColor(ccGREEN);
	tBagsurplus->setFontSize(18);     
	//tBagsurplus->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tBagsurplus);

	CCLabelTTF* tBagcount = SystemData::getLabelTTF("mining.label.bagcount");
	tBagcount->setColor(ccGREEN);
	tBagcount->setFontSize(18);     
	//tBagcount->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tBagcount);

	CCLabelTTF* tPredicttime = SystemData::getLabelTTF("mining.label.predicttime");
	tPredicttime->setColor(ccGREEN);
	tPredicttime->setFontSize(18);     
	//tPredicttime->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tPredicttime);
	 
	CCLabelTTF* tTime = SystemData::getLabelTTF("mining.label.time");
	tTime->setColor(ccGREEN);
	tTime->setFontSize(18);     
	//tTime->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tTime);

	CCPoint moneyPoint = SystemData::getLayoutPoint("mining.label.money");
	for (int i=Label_Money_Start+1;i<Label_Money_End;i++)
	{
		CCLabelTTF* title = CCLabelTTF::create("ABCDEFG","Arial",18);
		title->setPosition(ccp(moneyPoint.x,moneyPoint.y-(i-Label_Money_Start)*20));
		addChild(title);
		CCLabelTTF* count = CCLabelTTF::create("0","Arial",18);
		count->setTag(i);
		count->setPosition(ccp(title->getPositionX()+50,title->getPositionY()));
		addChild(count);
	}
	CCPoint materialPoint = SystemData::getLayoutPoint("mining.label.material");
	for (int i=Label_Material_Start+1;i<Label_Material_End;i++)
	{
		CCLabelTTF* title = CCLabelTTF::create("ABCDEFG","Arial",18);
		title->setPosition(ccp(materialPoint.x,materialPoint.y-(i-Label_Material_Start)*20));
		addChild(title);
		CCLabelTTF* count = CCLabelTTF::create("0","Arial",18);
		count->setTag(i);
		count->setPosition(ccp(title->getPositionX()+50,title->getPositionY()));
		addChild(count);
	}
	CCPoint rarePoint = SystemData::getLayoutPoint("mining.label.rare");
	for (int i=Label_Rare_Start+1;i<Label_Rare_End;i++)
	{
		CCLabelTTF* title = CCLabelTTF::create("ABCDEFG","Arial",18);
		title->setPosition(ccp(rarePoint.x,rarePoint.y-(i-Label_Rare_Start)*20));
		addChild(title);
		CCLabelTTF* count = CCLabelTTF::create("0","Arial",18); 
		count->setTag(i);
		count->setPosition(ccp(title->getPositionX()+50,title->getPositionY()));
		addChild(count);
	}
}

void MiningPanel::initButtons()
{
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("mining.button.close");
	pClose->setTag(Tag_Close);
	pClose->setTarget(this,menu_selector(MiningPanel::MenuCallBack));
	m_pMainMenu->addChild(pClose);
	
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.button",120,40);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.button.sel",120,40);
	CCMenuItemSprite *pBackToCity =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(MiningPanel::MenuCallBack));
	if(pBackToCity)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("mining.button.backtocity");
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		pBackToCity->setTag(Tag_BackToCity);
		pBackToCity->setPosition(SystemData::getLayoutPoint("mining.button.backtocity"));
		pLabel->setPosition(pBackToCity->getPosition());
		m_pMainMenu->addChild(pBackToCity);
		m_pMainMenu->addChild(pLabel);
	}

	CCMenuItemImage* pBackToCityGo = SystemData::getMenuItemImageByPlist("mining.button.backtocity.go");
	pBackToCityGo->setTag(Tag_BackToCityGo);
	pBackToCityGo->setTarget(this,menu_selector(MiningPanel::MenuCallBack));
	m_pMainMenu->addChild(pBackToCityGo);
	
	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("guild.info.button",100,40);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,40);
	CCMenuItemSprite *pStrengthen =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(MiningPanel::MenuCallBack));
	if(pStrengthen)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("mining.button.strengthen");
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		pStrengthen->setTag(Tag_Strengthen);
		pStrengthen->setPosition(SystemData::getLayoutPoint("mining.button.strengthen"));
		pLabel->setPosition(pStrengthen->getPosition());
		m_pMainMenu->addChild(pStrengthen);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("guild.info.button",120,40);
	CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("guild.info.button.sel",120,40);
	CCMenuItemSprite *pBackToMine =CCMenuItemSprite::create(p3,pSel3,NULL,this,menu_selector(MiningPanel::MenuCallBack));
	if(pBackToMine)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("mining.button.backtomine");    
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		pBackToMine->setTag(Tag_BackToMine); 
		pBackToMine->setPosition(SystemData::getLayoutPoint("mining.button.backtomine"));
		pLabel->setPosition(pBackToMine->getPosition());
		m_pMainMenu->addChild(pBackToMine);
		m_pMainMenu->addChild(pLabel);
	}

	CCMenuItemImage* pBackToMineGo = SystemData::getMenuItemImageByPlist("mining.button.backtomine.go");
	pBackToMineGo->setTag(Tag_BackToMineGo);
	pBackToMineGo->setTarget(this,menu_selector(MiningPanel::MenuCallBack));
	m_pMainMenu->addChild(pBackToMineGo);
}

void MiningPanel::setConfirmTarget(CCObject *rec, SEL_MenuHandler selector)
{
	m_pListener = rec;
    m_pfnSelector = selector;
}
void MiningPanel::handleConfirmPressed()
{
	if (m_pListener && m_pfnSelector)
    {
		 (m_pListener->*m_pfnSelector)(this);
	}
}
void MiningPanel::setString(std::string alert)
{
	m_LabelInfo->setString(alert.c_str());
}

void MiningPanel::reloadData()
{
	//reward map
	//m_reward
	//bag

}

void MiningPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if(source == "HandleMessageGuildMemberInfoResponse")
		{
			
		}
	}
	if (eventName == CPEventName::UI_NOTIFY)
	{
	
	}
}