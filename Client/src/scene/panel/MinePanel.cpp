#include "MinePanel.h"
#include "userdata/SystemData.h"
#include "controls/CPNodeHelper.h"
#include "event/CPEventHelper.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/MineData.h"
#include "scene/panel/shop/NpcShopPanel.h"
#include "scene/panel/MainPanel.h"
#include "scene/panel/ForgingPanel/ForgingMainPanel.h"
#include "userdata/UserItemData.h"
#include "userdata/HeroData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "EntityDefinition.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

MinePanel::MinePanel():
	m_pBagSoltEmpty(NULL)
{
	m_pLabelMap.clear();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

MinePanel::~MinePanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

void MinePanel::onEnter()
{
	BasePanel::onEnter();
	setScale(0.0f);
	setAnchorPoint(ccp(0.5,0.5));
	runAction(CPNodeHelper::getScaleToBig());

}

void MinePanel::onExit()
{
	runAction(CPNodeHelper::getScaleToSmall());
	BasePanel::onExit();
}

MinePanel* MinePanel::create()
{
	MinePanel* pPanel = new MinePanel();
	if(pPanel && pPanel->init())
	{
		pPanel->autorelease();
		return pPanel;
	}

	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

bool MinePanel::init()
{
	CCSprite* pbkg = SystemData::getSpriteByPlist("Mine_panel_bkg");
	pbkg->setAnchorPoint(CCPointZero);
	pbkg->setPosition(CCPointZero);
	addChild(pbkg);

	m_nWidth = pbkg->getContentSize().width;
	m_nHeight = pbkg->getContentSize().height;
	addCover();

	setContentSize(CCSizeMake(m_nWidth,m_nHeight));

	CCScale9Sprite* pborder = SystemData::getScale9SpriteByPlist("Mine_panel_smallborder",SystemData::getLayoutValue("Mine_panel_smallborder.w"),SystemData::getLayoutValue("Mine_panel_smallborder.h"));
	pborder->setAnchorPoint(CCPointZero);
	pborder->setPosition(ccp(pbkg->getContentSize().width/2-pborder->getContentSize().width/2,15));
	pbkg->addChild(pborder);

	CCLabelTTF* pTitle = SystemData::getLabelTTF("Mine_panel_titletext");
	pTitle->setColor(ccYELLOW);
	pTitle->setFontSize(22);
	pTitle->setPosition(ccp(m_nWidth/2,m_nHeight-30));
	addChild(pTitle);

	CCSprite* pline = SystemData::getSpriteByPlist("Mine_panel_line");
	pline->setPosition(SystemData::getLayoutPoint("Mine_panel_line"));
	addChild(pline);

	GeneralMenu* pMenu = GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCMenuItemImage* pclose = SystemData::getMenuItemImageByPlist("selectRolePanel_close");
	pclose->setTarget(this,menu_selector(MinePanel::hideCB));
	pclose->setPosition(ccp(m_nWidth-pclose->getContentSize().width/2,m_nHeight-pclose->getContentSize().height/2));
	pMenu->addChild(pclose);

	//进行强化  打开随身商店2个按钮
	CCMenuItemImage* pLeftBtn = SystemData::getScale9MenuItemImageByPlist("Mine_panel_btn");
	pLeftBtn->setTarget(this,menu_selector(MinePanel::gotoEnhanceItem));
	pLeftBtn->setPosition(SystemData::getLayoutPoint("Mine_panel_leftbtn"));
	pMenu->addChild(pLeftBtn);

	CCLabelTTF* pLefttext = SystemData::getLabelTTF("Mine_panel_leftbtn_text");
	pLefttext->setColor(ccWHITE);
	pLefttext->setFontSize(16);
	pLefttext->setPosition(ccp(pLeftBtn->getContentSize().width/2,pLeftBtn->getContentSize().height/2));
	pLeftBtn->addChild(pLefttext);

	CCMenuItemImage* pRightBtn = SystemData::getScale9MenuItemImageByPlist("Mine_panel_btn");
	pRightBtn->setTarget(this,menu_selector(MinePanel::openShop));
	pRightBtn->setPosition(SystemData::getLayoutPoint("Mine_panel_rightbtn"));
	pMenu->addChild(pRightBtn);

	CCLabelTTF* pRighttext = SystemData::getLabelTTF("Mine_panel_rightbtn_text");
	pRighttext->setColor(ccWHITE);
	pRighttext->setFontSize(16);
	pRighttext->setPosition(ccp(pRightBtn->getContentSize().width/2,pRightBtn->getContentSize().height/2));
	pRightBtn->addChild(pRighttext);


	CCLabelTTF* p= SystemData::getLabelTTF("Mine_panel_downtext");
	p->setColor(ccGREEN);
	p->setFontSize(18);
	p->setPosition(ccp(pline->getPositionX(),pline->getPositionY()/2+3));
	addChild(p);

	m_pBagSoltEmpty = CCLabelTTF::create("0/0","",18);
	m_pBagSoltEmpty->setAnchorPoint(ccp(0,0.5));
	m_pBagSoltEmpty->setPosition(ccp(p->getPositionX()+p->getContentSize().width/2,p->getPositionY()));
	addChild(m_pBagSoltEmpty);

	addMineInterface();//数据统计,背包空格

	CCMenuItemImage* pHide = SystemData::getMenuItemImageByPlist("Mine_panel_hide"); 
	pHide->setPosition(ccp(m_nWidth-60,p->getPositionY()));
	pHide->setTarget(this,menu_selector(MinePanel::hideCB));
	pMenu->addChild(pHide);
	return true;
}

void MinePanel::closeCB( CCObject* pSender )
{
	MineData::clear();
	this->removeFromParent();
	//this->setVisible(false);
}

bool MinePanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void MinePanel::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void MinePanel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos=pTouch->getLocation();
	CCRect rect=CCRectMake(0,0,m_nWidth,m_nHeight);
	if (!rect.containsPoint( this->convertToNodeSpace(pos)))
	{
		hideCB(NULL);
	}
}

void MinePanel::addMineInterface()
{
	 for (int i =1;i<=3;i++)
	 {
		 CCString* pStr = CCString::createWithFormat(SystemData::getLayoutString("Mine_panel_text_").c_str(),i);
		 CCLabelTTF* pTitle = SystemData::getLabelTTF(pStr->getCString());
		 pTitle->setColor(ccORANGE);
		 pTitle->setFontSize(18);
		 pTitle->setPosition(ccp(90+180*(i-1),300));
		 addChild(pTitle);

		 CCString* pStrSize = CCString::createWithFormat(SystemData::getLayoutString("Mine_panel_text_size_").c_str(),i);
		 for (int j =1;j<=SystemData::getLayoutValue(pStrSize->getCString());j++)
		 {
			 CCString* pStrSub = CCString::createWithFormat(SystemData::getLayoutString("Mine_panel_text_sub_").c_str(),i,j);
			 int sid = SystemData::getLayoutValue(pStrSub->getCString());
			 std::string MineName ;
			 LuaData::getProp(LuaData::ITEM,sid,"name",MineName);
			 CCLabelTTF* pSubTitle =  CCLabelTTF::create(MineName.c_str(),"",18);
			 pSubTitle->setAnchorPoint(ccp(0,0.5));
			 pSubTitle->setPosition(ccp(pTitle->getPositionX()-pTitle->getContentSize().width,pTitle->getPositionY()-j*35));
			 addChild(pSubTitle);

			 CCLabelTTF* pNewMineCount = CCLabelTTF::create("0","",18);
			 pNewMineCount->setColor(ccGREEN);
			 pNewMineCount->setPosition(ccp(pTitle->getPositionX(),pTitle->getPositionY()-j*35));
			 addChild(pNewMineCount);

			 m_pLabelMap[sid] = pNewMineCount;

			 std::string allcount = "("+SystemData::intToString(MineData::getAllMineCount(sid))+")";
			 CCLabelTTF* pAllMineCount = CCLabelTTF::create(allcount.c_str(),"",18);
			 pAllMineCount->setColor(ccWHITE);
			 pAllMineCount->setPosition(ccp(pTitle->getPositionX()+pTitle->getContentSize().width/2,pTitle->getPositionY()-j*35));
			 addChild(pAllMineCount);
		 }
	 }
	 updateMineCount();
}

void MinePanel::gotoEnhanceItem( CCObject* pSender )
{
	CPEventHelper::openPanel("MainPanel",TAG_Enhance_Panel,TAG_ZBQH,0,0);
}

void MinePanel::openShop( CCObject* pSender )
{
	CPEventHelper::openPanel("NpcShopComp",TAG_NPCSHOP_CARRY,0,0,0); 
}

void MinePanel::updateMineCount()
{
	std::map<int,CCLabelTTF*>::iterator it = m_pLabelMap.begin();
	for (it;it!=m_pLabelMap.end();it++)
	{
		int count = MineData::getNewMineCount(it->first);
		it->second->setString(SystemData::intToString(count).c_str());
	}

	int allbagsolt = HeroData::getProp(Entity::attr_bagslot);
	int nowbagsolt = GameData::s_user->getUserItemData()->getItemSoltCnt(ItemPos::Player_Bag_Start);
	if (m_pBagSoltEmpty)
	{
		CCString* p = CCString::createWithFormat("%d/%d",nowbagsolt,allbagsolt);
		m_pBagSoltEmpty->setString(p->getCString());
		if (allbagsolt<=nowbagsolt)
		{
			m_pBagSoltEmpty->setColor(ccRED);
		}
		else
		{
			m_pBagSoltEmpty->setColor(ccWHITE);
		}
	}
}

void MinePanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageItemAddNotifyEx" || source == "HandleMessageItemUpdCountNotify")
		{
			CCLog("add new mine");
			int sid=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			int count=CPEventHelper::getEventIntData(CPEventData::VALUE_3); 
			MineData::addMine(sid,count);
			updateMineCount();
		}
	}
}

void MinePanel::hideCB( CCObject* pSender )
{
	this->setVisible(false);
}

