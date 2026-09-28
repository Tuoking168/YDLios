#include "SpecialBagPanel.h"
#include "userdata/SystemData.h"
#include "ext/GeneralMenu.h"
#include "scene/panel/functionPanel/BagPanel.h"
#include "scene/panel/functionPanel/BagCellPanel.h"
#include "userdata/activitydata/SpiderData.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "event/EventProtocol.h"
#include "event/EventDispatcher.h"
#include "ext/CCActionDestroy.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "event/CPEventHelper.h"
#include "scene/panel/ForgingPanel/ForgingMainPanel.h"


SpecialBagPanel::SpecialBagPanel():
	m_pMenu(NULL),
	m_iCurType(0),
	m_iInterFaceType(0)
{

}

SpecialBagPanel::~SpecialBagPanel()
{

}

SpecialBagPanel* SpecialBagPanel::create(int interfacetype)
{
	SpecialBagPanel* pPanel = new SpecialBagPanel();
	if(pPanel && pPanel->init(interfacetype))
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

bool SpecialBagPanel::init(int interfacetype)
{
	/*m_nWidth = CCDirector::sharedDirector()->getWinSize().width;
	m_nHeight = CCDirector::sharedDirector()->getWinSize().height;
	addCover();*/
	if (!PartPanel::init())
	{
		return false;
	}

	m_iInterFaceType = interfacetype;

	CCScale9Sprite* pbkg1=SystemData::getScale9SpriteByPlist("activity_spider_bkg",SystemData::getLayoutValue("activity_spider_bkg_right.w"),SystemData::getLayoutValue("activity_spider_bkg_right.h"));
	//pbkg1->setPosition(SystemData::getLayoutPoint("activity_spider_bkg_right"));
	pbkg1->setAnchorPoint(CCPointZero);
	addChild(pbkg1);

	CCScale9Sprite* pbkg=SystemData::getScale9SpriteByPlist("activity_spider_bkg",SystemData::getLayoutValue("activity_spider_bkg_right.w"),SystemData::getLayoutValue("activity_spider_bkg_right.h"));
	//pbkg->setPosition(SystemData::getLayoutPoint("activity_spider_bkg_right"));
	pbkg->setAnchorPoint(CCPointZero);
	addChild(pbkg);

	m_nWidth =pbkg->getContentSize().width;
	m_nHeight = pbkg->getContentSize().height;

	m_pMenu = GeneralMenu::create();
	m_pMenu->setAnchorPoint(CCPointZero);
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	std::string RightName[3]={
		"forging_SSZB","forging_BBWP","forging_CWWP"
	};
	for (int i=0;i<3;i++)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF(RightName[i]); 
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		CCMenuItemImage *pRightButton=SystemData::getMenuItemImageByPlist("forging_bag_button");
		pRightButton->setScaleX(1.1);
		pRightButton->setTarget(this,menu_selector(SpecialBagPanel::menucallback));
		pRightButton->setTag(i+300);
		//pRightButton->setPosition(ccp(SystemData::getLayoutPoint("forging_rightmenu_button_pos").x+i*103+52,SystemData::getLayoutPoint("forging_rightmenu_button_pos").y-15));
		pRightButton->setPosition(ccp(i*103+52,SystemData::getLayoutPoint("forging_rightmenu_button_pos").y-25));
		pLabel->setPosition(ccp(pRightButton->getPositionX(),pRightButton->getPositionY()));
		m_pMenu->addChild(pRightButton);
		m_pMenu->addChild(pLabel);
	}

	updateList(TAG_SSZB);


	/*CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "close");
	closeBtn->setTarget(this, menu_selector(SpecialBagPanel::closecallback));
	closeBtn->setPosition(ccp());
	m_pMenu->addChild(closeBtn);*/
	return true;
}

void SpecialBagPanel::closecallback( CCObject* pSender )
{
	this->removeFromParent();
}

void SpecialBagPanel::menucallback( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	int tag = pNode->getTag();
	updateList(tag);
}

void SpecialBagPanel::updateList( int tag )
{
	if (m_iCurType == tag )
	{
		return ;
	}

	m_iCurType=tag;


	//按钮变更
	reloadRightButton();

	CCMenuItemSprite *pItem=NULL;

	pItem=(CCMenuItemSprite *)m_pMenu->getChildByTag(m_iCurType);
	CCSprite* pSprite=SystemData::getSpriteByPlist("forging_bag_button.sel");
	pItem->setNormalImage(pSprite);

	updateBag(m_iCurType);

}

void SpecialBagPanel::reloadRightButton()
{
	for (int i=0;i<3;i++)
	{
		CCMenuItemSprite *pItem=(CCMenuItemSprite *)m_pMenu->getChildByTag(i+300);
		CCSprite* pSprite=SystemData::getSpriteByPlist("forging_bag_button");
		pItem->setNormalImage(pSprite);
	}
}

void SpecialBagPanel::updateBag( int type )
{
	if (m_pMenu->getChildByTag(bag_panel))
	{
		m_pMenu->removeChildByTag(bag_panel);
	}
	BagCellPanel* panel = NULL;

	int type1=Self_Bag;
	int x=5;
	int y=4;
	int count=80;
	switch (m_iCurType)
	{
	case TAG_SSZB:
		type1=Role_Bag;
		count=20;
		break;
	case TAG_BBWP:
		type1=Self_Bag;
		break;
	case TAG_CWWP:
		type1=Pet_Bag;
		break;
	default:
		break;
	}
	panel=BagCellPanel::create(x,y,count,type1,m_iInterFaceType);
	//panel->setPosition(ccp(SystemData::getLayoutPoint("forging_rightmenu_pos").x+55,SystemData::getLayoutPoint("forging_rightmenu_pos").y-70));
	panel->setPosition(ccp(5,SystemData::getLayoutPoint("forging_rightmenu_pos").y-85));
	//背包内容变更
	if (panel)
	{
		panel->setTag(bag_panel);
		panel->setAnchorPoint(CCPointZero);
		m_pMenu->addChild(panel);
		//panel->setCurVisibleType(type);
	}
}