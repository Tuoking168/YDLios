#include "TopHelpPanel.h"
#include "EntityDefinition.h"
#include "userdata/netdata/GhostManager.h"
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
#include "ext/GeneralMenu.h"
#include "SceneDefinition.h"
#include "event/CPEventHelper.h"
#include "controls/CPNodeHelper.h"
#include "userdata/NPCFunctionData.h"


TopHelpPanel::TopHelpPanel():
	m_pTableView(NULL),
	m_pSelectItem(NULL),
	m_iCurListSubCount(0)
{
}

TopHelpPanel::~TopHelpPanel()
{
	
}
/*

TopHelpPanel* TopHelpPanel::create()
{

	TopHelpPanel* bagPanel = new TopHelpPanel();
	if(bagPanel && bagPanel->init())
	{
		bagPanel->autorelease();
		return bagPanel;
	}
	if (bagPanel)
	{
		delete bagPanel;
	}
	return NULL;
}*/

bool TopHelpPanel::init()//小秘书ui
{
	if (!FullScreenPanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	CCSprite* pTitle=SystemData::getSpriteByPlist("help_title");
	addChild(pTitle);

	CCScale9Sprite* pBorderbkg=SystemData::getScale9SpriteByPlist("help_borderbkg",SystemData::getLayoutValue("help_borderbkg.w"),SystemData::getLayoutValue("help_borderbkg.h"));
	pBorderbkg->setPosition(ccp(6,6));
	pBorderbkg->setAnchorPoint(CCPointZero);
	addChild(pBorderbkg);

	CCSprite* pMM=SystemData::getSpriteByPlist("help_MM");
	pMM->setAnchorPoint(CCPointZero);
	pMM->setPosition(CCPointZero);
	addChild(pMM);

	CCScale9Sprite* pBorder1=SystemData::getScale9SpriteByPlist("help_border",SystemData::getLayoutValue("help_border1.w"),SystemData::getLayoutValue("help_border1.h"));
	pBorder1->setPosition(SystemData::getLayoutPoint("help_border"));
	pBorder1->setOpacity(200);
	pBorder1->setAnchorPoint(CCPointZero);
	addChild(pBorder1);

	CCScale9Sprite* pBorder2=SystemData::getScale9SpriteByPlist("help_border",SystemData::getLayoutValue("help_border2.w"),SystemData::getLayoutValue("help_border2.h"));
	pBorder2->setPosition(ccp(pBorder1->getPositionX()+pBorder1->getContentSize().width,pBorder1->getPositionY()));
	pBorder2->setOpacity(200);
	pBorder2->setAnchorPoint(CCPointZero);
	addChild(pBorder2);

	onSwitch(1);
	//m_iCurListType=1;
	initLeftMenu();
	//initRightMenu();
	return true;
}

void TopHelpPanel::hide()
{
	this->removeFromParent();
}

void TopHelpPanel::onSwitch(int tag)
{
	m_iCurListType = tag;
	initRightMenu();
}


void TopHelpPanel::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}

cocos2d::CCSize TopHelpPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("help_tableviewcell");
}

cocos2d::extension::CCTableViewCell* TopHelpPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell* cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell;
		cell->autorelease();

		GeneralMenu* pMenu=GeneralMenu::create();
		pMenu->setPosition(CCPointZero);
		pMenu->setAnchorPoint(CCPointZero);
		cell->addChild(pMenu);

		HelpList helplist = m_mHelpList[idx];

		int id = helplist.id;
		int starnum=helplist.starnum;
		int tgtid=helplist.tgtid;
		std::string openpanelstr=helplist.openpanelstr;
		std::string name=helplist.name;
		//LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",idx+1,"starnum",starnum);
		for (int i=0;i<starnum;i++)
		{
			CCSprite* pStar=SystemData::getSpriteByPlist("help_star");
			pStar->setPosition(ccp(SystemData::getLayoutPoint("help_star").x+i*pStar->getContentSize().width,SystemData::getLayoutPoint("help_star").y));
			pMenu->addChild(pStar);
		}

		//LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",idx+1,"title",name);
		CCLabelTTF* pLabel=CCLabelTTF::create(name.c_str(),"",18);
		pLabel->setPosition(SystemData::getLayoutPoint("help_subtitle"));
		pLabel->setAnchorPoint(CCPointZero);
		pMenu->addChild(pLabel);

		//LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",idx+1,"tgtid",tgtid);
		//LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",idx+1,"openpanel",openpanelstr);
		if (tgtid!=0)
		{
			CCMenuItemImage* pItem=SystemData::getScale9MenuItemImageByPlist("help_Btn");
			pItem->setPosition(SystemData::getLayoutPoint("help_Btn"));
			pItem->setTarget(this,menu_selector(TopHelpPanel::BtnClick));
			pItem->setTag(id);
			pMenu->addChild(pItem);

			CCLabelTTF* pItemLabel=SystemData::getLabelTTF("help_btn_text1");
			pItemLabel->setPosition(pItem->getPosition());
			pItemLabel->setFontSize(20);
			pItemLabel->setColor(ccWHITE);
			pMenu->addChild(pItemLabel);

			CCMenuItemImage* pShoes=SystemData::getMenuItemImageByPlist("help_Shoes");
			pShoes->setPosition(SystemData::getLayoutPoint("help_Shoes"));
			pShoes->setTarget(this,menu_selector(TopHelpPanel::ShoesClick));
			pShoes->setTag(id);
			pMenu->addChild(pShoes);
		}
		else if(openpanelstr!="") 
		{
			CCMenuItemImage* pItem=SystemData::getScale9MenuItemImageByPlist("help_Btn");
			pItem->setPosition(SystemData::getLayoutPoint("help_Btn"));
			pItem->setTarget(this,menu_selector(TopHelpPanel::OpenPanelClick));
			pItem->setTag(id);
			pMenu->addChild(pItem);

			CCLabelTTF* pItemLabel=SystemData::getLabelTTF("help_btn_text2");
			pItemLabel->setPosition(pItem->getPosition());
			pItemLabel->setFontSize(20);
			pItemLabel->setColor(ccWHITE);
			pMenu->addChild(pItemLabel);
		}
		  
		CCSprite* pLine=SystemData::getSpriteByPlist("help_line");
		pLine->setScaleX(SystemData::getLayoutSize("help_tableviewcell").width/pLine->getContentSize().width);
		pLine->setAnchorPoint(CCPointZero);
		pLine->setPosition(CCPointZero);
		pMenu->addChild(pLine);
	}
	return cell;
}

unsigned int TopHelpPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return m_iCurListSubCount;
}

void TopHelpPanel::onCPEvent( const std::string &eventName )
{

}

void TopHelpPanel::initLeftMenu()
{
	CCMenu* pMenu=CCMenu::create();
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);
	addChild(pMenu);
	int size=SystemData::getLayoutValue("help_smalltitle_size");
	CCPoint pos= SystemData::getLayoutPoint("help_smalltitle");
	for (int i=1;i<=size;i++)
	{
		CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("help_smalltitle").c_str(),i);
		CCMenuItemImage* pItem=SystemData::getMenuItemImageByPlist(pStr->getCString());
		pItem->setTarget(this,menu_selector(TopHelpPanel::menucallback));
		pItem->setTag(i);
		pItem->setPosition(ccp(pos.x,pos.y-(i-1)*55));
		pMenu->addChild(pItem);
		if (m_iCurListType==i)
		{
			pItem->selected();
			m_pSelectItem=pItem;
		}
	}
}

void TopHelpPanel::menucallback( CCObject* pSender )
{
	CCNode* pNode=dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		if (m_pSelectItem)
		{
			m_pSelectItem->unselected();
		}
		int tag=pNode->getTag();
		onSwitch(tag);
		CCMenuItemImage* p=(CCMenuItemImage*)pSender;
		p->selected();
		m_pSelectItem=p;
	}
}

void TopHelpPanel::initRightMenu()
{
	m_iCurListSubCount=0;
	LuaData::getProp_size("gdSmallsecretary",m_iCurListType,"attr",m_iCurListSubCount);

	int nowlvl= HeroData::getLevel();
	int n = 0;
	for(int i = 0;i<m_iCurListSubCount;i++)
	{
		int minlvl = 0;
		int maxlvl = 0;
		LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",i+1,"minlvl",minlvl);
		LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",i+1,"maxlvl",maxlvl);
		if (nowlvl<minlvl || (nowlvl>maxlvl && maxlvl!=-1))
		{
			n++;
		}
		else
		{
			int tgtid=0;
			LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",i+1,"tgtid",tgtid);
			std::string openpanelstr="";
			LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",i+1,"openpanel",openpanelstr);
			std::string name;
			LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",i+1,"title",name);
			int starnum=0;
			LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",i+1,"starnum",starnum);
			HelpList helplist;
			helplist.id = i+1;
			helplist.name = name;
			helplist.tgtid = tgtid;
			helplist.openpanelstr = openpanelstr;
			helplist.starnum = starnum;
			m_mHelpList[i-n] = helplist;
		}
	}
	m_iCurListSubCount = m_iCurListSubCount-n;

	if (m_pTableView)
	{
		m_pTableView->reloadData();
	}
	else
	{
		m_pTableView=CCTableViewEx::create(this,SystemData::getLayoutSize("help_tableview"),kCCScrollViewDirectionVertical,this,NULL);
		m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
		m_pTableView->setAnchorPoint(CCPointZero);
		m_pTableView->setIsadjust(true);
		m_pTableView->setPosition(SystemData::getLayoutPoint("help_tableview"));
		m_pTableView->reloadData(); 
		addChild(m_pTableView);	
	}	
}

void TopHelpPanel::ShoesClick( CCObject* pSender )
{
	CCNode* pNode=dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag=pNode->getTag();
		int tgtid=0,tgttype=0;
		LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",tag,"tgtid",tgtid);
		LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",tag,"tgttype",tgttype);
		/*MsgEnterSceneRequest* sceneMsg=NULL;*/
		switch (tgttype)
		{
		case 1://NPC
			/*sceneMsg = new MsgEnterSceneRequest;
			sceneMsg->sid = tgtid;
			sceneMsg->reason = Scene::seNpc;*/
			NPCFunctionData::useShoes(tgtid,Scene::seNpc);
			break;
		case 2://MAP
			/*sceneMsg = new MsgEnterSceneRequest;
			sceneMsg->sid = tgtid;
			sceneMsg->reason = Scene::seInstance;*/
			NPCFunctionData::useShoes(tgtid,Scene::seInstance);
			break;
		case 3://Monster
			/*sceneMsg = new MsgEnterSceneRequest;
			sceneMsg->sid = tgtid;
			sceneMsg->reason = Scene::seMonster;*/
			NPCFunctionData::useShoes(tgtid,Scene::seMonster);
			break;
		default:
			break;
		}
		this->removeFromParent();
		/*if (sceneMsg)
		{
			HandleMessage::sendMessage(sceneMsg);
		}*/
	}
}

void TopHelpPanel::BtnClick( CCObject* pSender )
{
	CCNode* pNode=dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag=pNode->getTag();
		int tgtid=0,tgttype=0;
		LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",tag,"tgtid",tgtid);
		LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",tag,"tgttype",tgttype);
		switch (tgttype)
		{
		case 1://NPC
			GameData::s_user->m_pGhostManager->gotoGhostPos(tgtid,"npcs",GHOST_TYPE_NPC);
			break;
		case 2://MAP
			GameData::s_user->m_pGhostManager->gotoMap(tgtid,GHOST_TYPE_MONSTER);
			break;
		case 3://Monster
			GameData::s_user->m_pGhostManager->gotoGhostPos(tgtid,"monsters",GHOST_TYPE_MONSTER);
			break;
		default:
			break;
		}
	}
	this->removeFromParent();
}

void TopHelpPanel::OpenPanelClick( CCObject* pSender )
{
	CCNode* pNode=dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag=pNode->getTag();
		int tgttype=0;
		int sub1=0;
		int sub2=0;
		std::string openpanel="";
		LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",tag,"openpanel",openpanel);
		LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",tag,"tgttype",tgttype);
		LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",tag,"sub1",sub1);
		LuaData::getProp("gdSmallsecretary",m_iCurListType,"attr",tag,"sub2",sub2);
		if (tgttype==0)
		{
			if (sub1!=-1 && sub2!=-1)
			{
				CPEventHelper::openPanel(openpanel,sub1,sub2,0,1);  
			}
			else
			{
				CPEventHelper::openPanel(openpanel); 
			}
		}
	}
	this->removeFromParent();
}

void TopHelpPanel::onEnter()
{
	FullScreenPanel::onEnter();
	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}
