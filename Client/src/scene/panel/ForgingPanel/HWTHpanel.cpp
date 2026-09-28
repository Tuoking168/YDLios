#include "HWTHpanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "event/EventProtocol.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"

#include "userdata/netdata/GameRole.h"

#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"

#include "scene/panel/functionPanel/ItemTooltip.h"
#include "CommonFunction.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventHelper.h"
#include "ForgingMainPanel.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/guide/GuideHelper.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "res/AudioLoader.h"

HWTHpanel::HWTHpanel( void ):
	m_pLeftUserItem(NULL),
	m_pRightUserItem(NULL)
{

}

HWTHpanel::~HWTHpanel( void )
{

}

HWTHpanel* HWTHpanel::create()
{
	HWTHpanel* pPanel = new HWTHpanel();
	if(pPanel && pPanel->init(""))
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

bool HWTHpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}

	//装备升级界面背景
	CCScale9Sprite* bkgSprite = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_mainpanel_size.w"),SystemData::getLayoutValue("forging_mainpanel_size.h"));
	m_nWidth = bkgSprite->getContentSize().width;
	m_nHeight = bkgSprite->getContentSize().height;
	bkgSprite->setPosition(SystemData::getLayoutPoint("forging_mainpanel_pos"));
	bkgSprite->setAnchorPoint(CCPointZero);
	addChild(bkgSprite);

	addCover();//保证点击事件

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);


	CCLabelTTF* pQFRXYHXTHDHW=SystemData::getLabelTTF("HWTH_QFRXYHXTHDHW");
	pQFRXYHXTHDHW->setPosition(SystemData::getLayoutPoint("HWTH_title_pos"));
	pQFRXYHXTHDHW->setFontSize(18);
	pQFRXYHXTHDHW->setColor(ccYELLOW);
	m_pTopList->addChild(pQFRXYHXTHDHW);

	//装备升级3个框
	CCSprite *pButton1=SystemData::getSpriteByPlist("forging_base");//升级物品框
	pButton1->setPosition(SystemData::getLayoutPoint("HWTH_left_pos"));
	CCSprite *pButton2=SystemData::getSpriteByPlist("forging_base");//升级材料框
	pButton2->setPosition(SystemData::getLayoutPoint("HWTH_right_pos"));

	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("HWTH_YSHW");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1->getPositionX(),pButton1->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("HWTH_CLHW");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2->getPositionX(),pButton2->getPositionY()+50));
	m_pTopList->addChild(pSJWPK);
	m_pTopList->addChild(pSJCLK);
	m_pTopList->addChild(pButton1);
	m_pTopList->addChild(pButton2);

	/*//选择幻武按钮
	CCMenuItemImage *pXZbutton=SystemData::getMenuItemImageByPlist("forging_button3");
	pXZbutton->setTag(TAG_CHANGEHW);
	pXZbutton->setTarget(this,menu_selector(HWTHpanel::menuCallBack));
	pXZbutton->setPosition(SystemData::getLayoutPoint("HWTH_HWbutton_pos"));
	m_pTopList->addChild(pXZbutton);
	CCLabelTTF* pXZHW=SystemData::getLabelTTF("HWTH_XZHW");
	pXZHW->setColor(ccWHITE);
	pXZHW->setFontSize(18);
	pXZHW->setPosition(pXZbutton->getPosition());
	m_pTopList->addChild(pXZHW);*/


	
	CCMenuItemImage* pLeftButton=SystemData::getMenuItemImageByPlist("forging_button3");
	pLeftButton->setPosition(SystemData::getLayoutPoint("HWTH_HW_pos"));
	pLeftButton->setTag(TAG_TH);
	pLeftButton->setTarget(this,menu_selector(HWTHpanel::menuCallBack));
	m_pTopList->addChild(pLeftButton);
	CCLabelTTF* pLeftLabel=SystemData::getLabelTTF("HWTH_TH");
	pLeftLabel->setColor(ccWHITE);
	pLeftLabel->setFontSize(18);
	pLeftLabel->setPosition(SystemData::getLayoutPoint("HWTH_HW_pos"));
	m_pTopList->addChild(pLeftLabel);

	/*if (GuideHelper::canOpenFunction(FunctionName::HUAN_WU_QI_LING))
	{
		CCMenuItemImage* pRightButton=SystemData::getMenuItemImage("forging_unselect");
		pRightButton->setPosition(SystemData::getLayoutPoint("HWTH_QL_pos"));
		pRightButton->setTarget(this,menu_selector(HWTHpanel::menuCallBack));
		pRightButton->setTag(TAG_QL);
		m_pTopList->addChild(pRightButton);
		CCLabelTTF* pRightLabel=SystemData::getLabelTTF("HWTH_QL");
		pRightLabel->setPosition(SystemData::getLayoutPoint("HWTH_QL_pos"));
		m_pTopList->addChild(pRightLabel);
	}*/
	CCMenuItemImage* pRightButton=SystemData::getMenuItemImageByPlist("forging_unselect");
	pRightButton->setPosition(SystemData::getLayoutPoint("HWTH_QL_pos"));
	pRightButton->setTarget(this,menu_selector(HWTHpanel::menuCallBack));
	pRightButton->setTag(TAG_QL);
	m_pTopList->addChild(pRightButton);
	CCLabelTTF* pRightLabel=SystemData::getLabelTTF("HWTH_QL");
	pRightLabel->setColor(ccWHITE);
	pRightLabel->setFontSize(18);
	pRightLabel->setPosition(SystemData::getLayoutPoint("HWTH_QL_pos"));
	m_pTopList->addChild(pRightLabel);



	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(HWTHpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("HWTH_button_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("HWTH_TH");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);

	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBSJ_XYJB");//需要金币
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("ZBSJ_label1_pos"));
	CCLabelTTF *pmoney1=SystemData::getLabelTTF("XXXXX");
	pmoney1->setFontSize(14);	
	pmoney1->setColor(ccYELLOW);
	pmoney1->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));

	/*CCLabelTTF *pCLJB=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	pCLJB->setFontSize(12);	
	pCLJB->setColor(ccYELLOW);
	pCLJB->setPosition(SystemData::getLayoutPoint("ZBSJ_label2_pos"));
	CCLabelTTF *pmoney2=SystemData::getLabelTTF("XXXXX");
	pmoney2->setFontSize(14);	
	pmoney2->setColor(ccYELLOW);
	pmoney2->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);
	pTHYB->setPosition(SystemData::getLayoutPoint("ZBSJ_label3_pos"));
	pTHYB->setAnchorPoint(CCPointZero);*/
	//pCLJB->setAnchorPoint(CCPointZero);
	pmoney1->setAnchorPoint(CCPointZero);
	//pmoney2->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	//m_pTopList->addChild(pTHYB);
//	m_pTopList->addChild(pCLJB);
	m_pTopList->addChild(pmoney1);
	//m_pTopList->addChild(pmoney2);
	m_pTopList->addChild(pXYJB);

	//物品说明menu
	m_pBottomList=GeneralMenu::create();
	m_pBottomList->setPosition(CCPointZero);
	addChild(m_pBottomList);	

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);	

	CCScale9Sprite* pbottombkg = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_bottompanel_size.w"),SystemData::getLayoutValue("forging_bottompanel_size.h"));
	pbottombkg->setAnchorPoint(CCPointZero);
	pbottombkg->setPosition(SystemData::getLayoutPoint("forging_bottompanel_pos"));		
	addChild(pbottombkg);

	CCTableViewEx *pTabelView=CCTableViewEx::create(this,SystemData::getLayoutSize("forging_bottommenu_size"),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(SystemData::getLayoutPoint("forging_bottommenu_pos"));
	pTabelView->reloadData();  
	addChild(pTabelView);
	return true;
}

void HWTHpanel::menuCallBack( CCObject *pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		HWQLpanel* p=NULL;
		switch (tag)
		{	
		case TAG_QL:
			((ForgingMainPanel* )(this->getParent()))->addTopFunc(TAG_HWQL);
			break;
		case TAG_UPGRADE:
			if (m_pLeftUserItem && m_pRightUserItem)
			{
				 CommonFunction::sendmsgChangeMagicWeapon(m_pLeftUserItem->iid,m_pRightUserItem->iid);
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::NotEquip);
			}
			break;
		default:
			break;
		}
	}
}

cocos2d::CCSize HWTHpanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(420, m_iHeight);
}

cocos2d::extension::CCTableViewCell* HWTHpanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer=CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		std::string content;
		LuaData::getProp("gddescription",4,"content",content);
		CCLabelTTF* pLabel=CCLabelTTF::create(content.c_str(),"",16);
		pLabel->setPosition(CCPointZero);
		pLabel->setAnchorPoint(CCPointZero);
		pLabel->setDimensions(CCSizeMake(SystemData::getLayoutValue("forging_bottommenu_size.w"),0));
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLayer->addChild(pLabel);
		m_iHeight=pLabel->getContentSize().height;
	}
	return cell;
}

unsigned int HWTHpanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void HWTHpanel::addItem( UserItem* pUserItem )
{
	//如果1中已经有物品，则进入add2
	if (m_pLeftUserItem)
	{
		addItem2(pUserItem);
	}
	else
	{
		removeItem();
		m_pLeftUserItem=pUserItem;
		//载入1号物品的icon
		CCMenuItemImage* pItem=CommonFunction::getItemIcon(pUserItem,false);
		pItem->setTarget(this,menu_selector(HWTHpanel::ItemCallBack));
		pItem->setPosition(SystemData::getLayoutPoint("HWTH_left_pos"));
		pItem->setTag(1);
		m_pMenu->addChild(pItem);
	}	
}

void HWTHpanel::addItem2( UserItem* pUserItem )
{
	if (m_pRightUserItem)
	{
		m_pMenu->removeChildByTag(2);
	}
	if (pUserItem->iid==m_pLeftUserItem->iid)
	{
		CPEventHelper::uiNotify("","",Error::CanNotSameItem);
		return ;
	}
	m_pRightUserItem = pUserItem;
	//载入2号物品的icon
	CCMenuItemImage* pItem=CommonFunction::getItemIcon(pUserItem,false);
	pItem->setTarget(this,menu_selector(HWTHpanel::ItemCallBack));
	pItem->setPosition(SystemData::getLayoutPoint("HWTH_right_pos"));
	pItem->setTag(2);
	m_pMenu->addChild(pItem);
}

void HWTHpanel::removeItem()
{
	m_pMenu->removeAllChildren();
	m_pLeftUserItem=NULL;
	m_pRightUserItem=NULL;
}

void HWTHpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void HWTHpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		removeItem();
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("HWTH_left_pos"));
		addChild(p);
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("HWTH_left_pos"));
		addChild(p);
	}
}






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



HWQLpanel::HWQLpanel( void )
{

}

HWQLpanel::~HWQLpanel( void )
{

}

HWQLpanel* HWQLpanel::create()
{
	HWQLpanel* pPanel = new HWQLpanel();
	if(pPanel && pPanel->init(""))
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

bool HWQLpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}

	//装备升级界面背景
	CCScale9Sprite* bkgSprite = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_mainpanel_size.w"),SystemData::getLayoutValue("forging_mainpanel_size.h"));
	m_nWidth = bkgSprite->getContentSize().width;
	m_nHeight = bkgSprite->getContentSize().height;
	bkgSprite->setPosition(SystemData::getLayoutPoint("forging_mainpanel_pos"));
	bkgSprite->setAnchorPoint(CCPointZero);
	addChild(bkgSprite);

	addCover();//保证点击事件

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);
	
	//装备升级3个框
	CCSprite *pButton1=SystemData::getSpriteByPlist("forging_base");//升级物品框
	pButton1->setPosition(SystemData::getLayoutPoint("HWQL_left_pos"));
	CCSprite *pButton2=SystemData::getSpriteByPlist("forging_base");//升级材料框
	pButton2->setPosition(SystemData::getLayoutPoint("HWQL_right_pos"));

	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("HWTH_HW");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1->getPositionX(),pButton1->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("HWTH_QLCL");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2->getPositionX(),pButton2->getPositionY()+50));
	m_pTopList->addChild(pSJWPK);
	m_pTopList->addChild(pSJCLK);
	m_pTopList->addChild(pButton1);
	m_pTopList->addChild(pButton2);

	//选择幻武按钮
	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("HWQL_smallborder_size.w"),SystemData::getLayoutValue("HWQL_smallborder_size.h"));
	pBorder->setPosition(SystemData::getLayoutPoint("HWQL_smallborder_pos"));
	m_pTopList->addChild(pBorder);
	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("HWTH_QLXGYL");
	pSJXGYL->setPosition(SystemData::getLayoutPoint("HWQL_title_pos"));
	pSJXGYL->setFontSize(18);
	pSJXGYL->setColor(ccWHITE);
	m_pTopList->addChild(pSJXGYL);
	CCSprite *pButton3=SystemData::getSpriteByPlist("forging_result");
	pButton3->setPosition(ccp(pSJXGYL->getPositionX(),pSJXGYL->getPositionY()-55));
	m_pTopList->addChild(pButton3);

	
	CCMenuItemImage* pLeftButton=SystemData::getMenuItemImageByPlist("forging_unselect");
	pLeftButton->setPosition(SystemData::getLayoutPoint("HWTH_HW_pos"));
	pLeftButton->setTag(TAG_TH);
	pLeftButton->setTarget(this,menu_selector(HWQLpanel::menuCallBack));
	m_pTopList->addChild(pLeftButton);
	CCLabelTTF* pLeftLabel=SystemData::getLabelTTF("HWTH_TH");
	pLeftLabel->setColor(ccWHITE);
	pLeftLabel->setFontSize(18);
	pLeftLabel->setPosition(SystemData::getLayoutPoint("HWTH_HW_pos"));
	m_pTopList->addChild(pLeftLabel);

	CCMenuItemImage* pRightButton=SystemData::getMenuItemImageByPlist("forging_button3");
	pRightButton->setPosition(SystemData::getLayoutPoint("HWTH_QL_pos"));
	pRightButton->setTag(TAG_QL);
	pRightButton->setTarget(this,menu_selector(HWQLpanel::menuCallBack)); 
	m_pTopList->addChild(pRightButton);
	CCLabelTTF* pRightLabel=SystemData::getLabelTTF("HWTH_QL");
	pRightLabel->setColor(ccWHITE);
	pRightLabel->setFontSize(18);
	pRightLabel->setPosition(SystemData::getLayoutPoint("HWTH_QL_pos"));
	m_pTopList->addChild(pRightLabel);


	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(HWQLpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("HWQL_button_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("HWTH_QL");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);

	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBSJ_XYJB");//需要金币
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("ZBSJ_label1_pos"));
	CCLabelTTF *pmoney1=SystemData::getLabelTTF("XXXXX");
	pmoney1->setFontSize(14);	
	pmoney1->setColor(ccYELLOW);
	pmoney1->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));

	CCLabelTTF *pCLJB=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	pCLJB->setFontSize(12);	
	pCLJB->setColor(ccYELLOW);
	pCLJB->setPosition(SystemData::getLayoutPoint("ZBSJ_label2_pos"));
	CCLabelTTF *pmoney2=SystemData::getLabelTTF("XXXXX");
	pmoney2->setFontSize(14);	
	pmoney2->setColor(ccYELLOW);
	pmoney2->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);
	pTHYB->setPosition(SystemData::getLayoutPoint("ZBSJ_label3_pos"));
	pTHYB->setAnchorPoint(CCPointZero);
	pCLJB->setAnchorPoint(CCPointZero);
	pmoney1->setAnchorPoint(CCPointZero);
	pmoney2->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	m_pTopList->addChild(pTHYB);
	m_pTopList->addChild(pCLJB);
	m_pTopList->addChild(pmoney1);
	m_pTopList->addChild(pmoney2);
	m_pTopList->addChild(pXYJB);

	//物品说明menu
	m_pBottomList=GeneralMenu::create();
	m_pBottomList->setPosition(CCPointZero);
	addChild(m_pBottomList);	

	CCScale9Sprite* pbottombkg = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_bottompanel_size.w"),SystemData::getLayoutValue("forging_bottompanel_size.h"));
	pbottombkg->setAnchorPoint(CCPointZero);
	pbottombkg->setPosition(SystemData::getLayoutPoint("forging_bottompanel_pos"));		
	addChild(pbottombkg);

	this->runAction(CCSequence::create(CCDelayTime::create(0.08f),CCCallFunc::create(this,callfunc_selector(HWQLpanel::initContent)),NULL));
	return true;
}

cocos2d::CCSize HWQLpanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(420, m_iHeight);
}

cocos2d::extension::CCTableViewCell* HWQLpanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer=CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		std::string content;
		LuaData::getProp("gddescription",17,"content",content);
		CCLabelTTF* pLabel=CCLabelTTF::create(content.c_str(),"",16);
		pLabel->setPosition(CCPointZero);
		pLabel->setAnchorPoint(CCPointZero);
		pLabel->setDimensions(CCSizeMake(SystemData::getLayoutValue("forging_bottommenu_size.w"),0));
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLayer->addChild(pLabel);
		m_iHeight=pLabel->getContentSize().height;
	}
	return cell;
}

unsigned int HWQLpanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void HWQLpanel::menuCallBack( CCObject *pSender )
{
	CCLOG("HWQLpanel Press");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		HWTHpanel* p=NULL;
		switch (tag)
		{	
		case TAG_TH:
			((ForgingMainPanel* )(this->getParent()))->addTopFunc(TAG_HWTH);
			break;
		default:
			break;
		}
	}
}

void HWQLpanel::initContent()
{
	CCTableViewEx *pTabelView=CCTableViewEx::create(this,SystemData::getLayoutSize("forging_bottommenu_size"),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(SystemData::getLayoutPoint("forging_bottommenu_pos"));
	pTabelView->reloadData();  
	addChild(pTabelView);
}
