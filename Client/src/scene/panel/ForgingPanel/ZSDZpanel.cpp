#include "ZSDZpanel.h"
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
#include "userdata/luadata/LuaData.h"
#include "CommonFunction.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventHelper.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "utils/RichTextUtils.h"
#include "controls/CPRichText.h"
#include "controls/CPCheckBox.h"
#include "res/AudioLoader.h"


ZSDZpanel::ZSDZpanel( void ):
	m_pSecondItem(NULL),
	m_pExtraMoney(NULL),
	m_plock(NULL),
	m_Vcoin(0)
{

}

ZSDZpanel::~ZSDZpanel( void )
{

}

ZSDZpanel* ZSDZpanel::create()
{
	ZSDZpanel* pPanel = new ZSDZpanel();
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
void ZSDZpanel::updateTimer(float dt)
{
	// 冷却时间更新
	if (m_iTimeSpan > 0)
	{
		m_iTimeSpan--;
		
		// 当冷却时间为0时，可以再次点击
		if (m_iTimeSpan <= 0)
		{
			m_iTimeSpan = 0;
		}
	}
}
bool ZSDZpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	// 添加：初始化冷却时间
	m_iTimeSpan = 0;
	
	// 添加：启动冷却时间更新计时器
	this->schedule(schedule_selector(ZSDZpanel::updateTimer), 1.0f);

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
	CCSprite *pButton1n=SystemData::getSpriteByPlist("forging_base");
	CCSprite *pButton2n=SystemData::getSpriteByPlist("forging_base");
	pButton1n->setPosition(SystemData::getLayoutPoint("ZSDZ_button1_pos"));
	pButton2n->setPosition(SystemData::getLayoutPoint("ZSDZ_button2_pos"));
	addChild(pButton1n);
	addChild(pButton2n);
	CCSprite *pButton3n=SystemData::getSpriteByPlist("forging_base");
	pButton3n->setPosition(SystemData::getLayoutPoint("ZSDZ_FZB_pos"));
//	addChild(pButton3n);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("ZSDZ_DZDZB");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1n->getPositionX(),pButton1n->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("ZSDZ_ZSCL");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2n->getPositionX(),pButton2n->getPositionY()+50));
	CCLabelTTF* pFZB=SystemData::getLabelTTF("ZSDZ_FZB");
	pFZB->setColor(ccc3(3,223,204));
	pFZB->setFontSize(18);
	pFZB->setPosition(ccp(pButton3n->getPositionX(),pButton3n->getPositionY()+50));


	addChild(pSJWPK);
	addChild(pSJCLK);
//	addChild(pFZB);

	CCScale9Sprite* psmallBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBSJ_smallborder_size.w"),SystemData::getLayoutValue("ZBSJ_smallborder_size.h"));
	psmallBorder->setPosition(SystemData::getLayoutPoint("ZSDZ_smallborder_pos"));
	m_pTopList->addChild(psmallBorder);
	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("ZSDZ_DZXGYL");
	pSJXGYL->setPosition(ccp(psmallBorder->getPositionX(),psmallBorder->getPositionY()+35));
	pSJXGYL->setFontSize(18);
	pSJXGYL->setColor(ccWHITE);
	m_pTopList->addChild(pSJXGYL);
	CCSprite *pButton3=SystemData::getSpriteByPlist("forging_result");
	pButton3->setPosition(ccp(psmallBorder->getPositionX(),psmallBorder->getPositionY()-20));
	m_pTopList->addChild(pButton3);


	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_DZ);
	pUpLevel->setTarget(this,menu_selector(ZSDZpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("ZSDZ_button3_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("ZSDZ_DZ");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);

	
	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBSJ_XYJB");//需要金币
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("ZBSJ_label1_pos"));
	m_pMoney=SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);	
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));

	/*CCLabelTTF* pEWJB = SystemData::getLabelTTF("ZSDZ_XYEWJB");//需要额外金币
	pEWJB->setFontSize(12);
	pEWJB->setColor(ccYELLOW);
	pEWJB->setPosition(SystemData::getLayoutPoint("ZSDZ_EWJB_label_pos"));
	
	m_pExtraMoney = SystemData::getLabelTTF("XXXXX");
	m_pExtraMoney->setFontSize(14);	
	m_pExtraMoney->setColor(ccYELLOW);
	m_pExtraMoney->setPosition(ccp(pEWJB->getPositionX()+50,pEWJB->getPositionY())); */ 

	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要元宝
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("ZSDZ_YBDT_label_pos"));
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+75,m_pYuanBao->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);
	 
	m_plock=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	m_plock->setTag(TAG_LOCK);
	m_plock->setHandler(this,menu_selector(ZSDZpanel::menuCallBack));
	m_plock->setPosition(SystemData::getLayoutPoint("ZBSJ_label3_pos"));
	m_plock->setVisible(false);
	m_pTopList->addChild(m_plock);

	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
//	pEWJB->setAnchorPoint(CCPointZero);
//	m_pExtraMoney->setAnchorPoint(CCPointZero);
	addChild(m_pYuanBao);
	addChild(m_pMoney);

	addChild(pXYJB);
//	addChild(pEWJB);
	addChild(m_pYuanBaoMoney);   
//	addChild(m_pExtraMoney);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);

	//物品说明menu
	m_pBottomList=GeneralMenu::create();
	m_pBottomList->setPosition(CCPointZero);
	addChild(m_pBottomList);	

	CCScale9Sprite* pbottombkg = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_bottompanel_size.w"),SystemData::getLayoutValue("forging_bottompanel_size.h"));
	pbottombkg->setAnchorPoint(CCPointZero);
	pbottombkg->setPosition(SystemData::getLayoutPoint("forging_bottompanel_pos"));		
	addChild(pbottombkg);

	settgtPos(SystemData::getLayoutPoint("ZSDZ_button1_pos"));

	return true;
}


void ZSDZpanel::menuCallBack( CCObject *pSender )
{
	//	EquipBasepanel::MenuCallBack(pSender);
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		int rvt=0;
		
		switch (tag)
		{
		case TAG_DZ:
			// 添加冷却时间检查
			if (m_iTimeSpan != 0)
			{
				CPEventHelper::uiNotify("", "", Error::time3sspan);
				return;
			}
			
			if (m_pUserItem)
			{
				if (m_pUserItem->data[ItemEquip::Item_RebornLvl]>=25)
				{
					CPEventHelper::uiNotify("","",Error::Item_MaxBornLevel);	
					return;
				}				
			}
			
			rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_Reborn,m_bLock,0,0,0);
			if (rvt==Error::Success)
			{
				// 设置冷却时间
				m_iTimeSpan = 3;
				
				if (m_bLock)
				{
					if (m_pSecondItem)
					{
						CommonFunction::sendmsgReborn(m_pUserItem->iid,m_pSecondItem->iid,1);	
					}	
					else
					{
						CommonFunction::sendmsgReborn(m_pUserItem->iid,0,1);	
					}
				}
				else
				{
					if (m_pSecondItem)
					{
						CommonFunction::sendmsgReborn(m_pUserItem->iid,m_pSecondItem->iid);	
					}
					else
					{
						CommonFunction::sendmsgReborn(m_pUserItem->iid,0);	
					}
				}	
			}
			else
			{
				CPEventHelper::uiNotify("","",rvt);
			}			
			break;
			
		/*case TAG_UP:
			break;
		case TAG_DOWN:
			break;
			*/
			
		case TAG_LOCK:
			if (m_bLock)
			{
				m_bLock=false;
				m_pYuanBao->setVisible(false);
				m_pYuanBaoMoney->setVisible(false);
			}
			else
			{
				m_bLock=true;
				m_pYuanBao->setVisible(true);
				m_pYuanBaoMoney->setVisible(true);
			}
			m_pYuanBaoMoney->setString(SystemData::intToString(m_Vcoin).c_str());
			break;
			
		default:
			break;
		}
	}
}


void ZSDZpanel::initContent()
{
	CCTableViewEx *pTabelView=CCTableViewEx::create(this,SystemData::getLayoutSize("forging_bottommenu_size"),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(SystemData::getLayoutPoint("forging_bottommenu_pos"));
	pTabelView->reloadData();  
	addChild(pTabelView);
}

void ZSDZpanel::onEnter()
{	
	setContentID(9);
	EquipBasepanel::onEnter();
}

void ZSDZpanel::addItem( UserItem* pUserItem )
{
	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		return ;
	}
	m_pUserItem=pUserItem;
	CCMenuItemImage* icon=CommonFunction::getItemIcon(m_pUserItem,false); 
	icon->setPosition(SystemData::getLayoutPoint("ZSDZ_button1_pos"));	
	icon->setTarget(this,menu_selector(ZSDZpanel::ItemCallBack));
	m_pMenu->addChild(icon);

	//加载相对应的副装备
	m_pSecondItem=NULL;
	CCMenuItemImage* req1 =CommonFunction::getReqRebornItemSecond(m_pUserItem);
	if (req1)
	{
		req1->setPosition(SystemData::getLayoutPoint("ZSDZ_button2_pos"));
		req1->setTarget(this,menu_selector(ZSDZpanel::ItemCallBack));
		m_pMenu->addChild(req1);
		m_pSecondItem=(UserItem*)(req1->getUserData());
		m_plock->setVisible(false);
	}else
	{
		m_plock->setVisible(true);
	}

	//加载相对应的材料
	int tag=0;
	LuaData::getProp("gdItemReBorn",m_pUserItem->sid,"reqid",tag);
	CCMenuItemImage* req2 =CommonFunction::getReqRebornItem(m_pUserItem);
	if (tag != 0)
	{
		req2->setPosition(SystemData::getLayoutPoint("ZSDZ_button2_pos"));
		req2->setTarget(this,menu_selector(ZSDZpanel::ItemCallBack));
		m_pMenu->addChild(req2);
	}
	

	//加载升级后的预览物品
	CCMenuItemImage* RebornAft=CommonFunction::getTgtRebornItem(m_pUserItem);
	//RebornAft->setPosition(SystemData::getLayoutPoint("ZSDZ_smallborder_pos"));
	RebornAft->setTarget(this,menu_selector(ZSDZpanel::ItemCallBack));
	m_pMenu->addChild(RebornAft);


	int money;
	int d_value = 0;
//	int extraMoney;
	LuaData::getProp("gdItemReBorn",m_pUserItem->sid,"reqmoney",money);
//	LuaData::getProp("gdItemReBorn",pUserItem->sid,"reqExtramoney",extraMoney);      
	if ( LuaData::checkIdExist("gdSpecialRebornItem",m_pUserItem->sid))
	{
		d_value = 2;
	}
	money=money*(m_pUserItem->data[ItemEquip::Item_RebornLvl]+1+d_value);
//	extraMoney=extraMoney*(pUserItem->data[ItemEquip::Item_RebornLvl]+1);   
	m_pMoney->setString(SystemData::intToString(money).c_str());
//	m_pExtraMoney->setString(SystemData::intToString(extraMoney).c_str());
	if (HeroData::getProp(Entity::attr_money)<money)
	{
		m_pMoney->setColor(ccRED);
	}
	else
	{
		m_pMoney->setColor(ccWHITE);
	}

	/*if (HeroData::getProp(Entity::attr_money)<extraMoney)
	{
		m_pExtraMoney->setColor(ccRED);
	}
	else
	{
		m_pExtraMoney->setColor(ccWHITE);
	}*/

	m_Vcoin=CommonFunction::getReqVcoin(m_pUserItem,TAG_Reborn,m_bLock);
	if (m_Vcoin==-1)
	{
		m_pYuanBaoMoney->setString("?");
		m_pYuanBaoMoney->setColor(ccRED);
	}
	else
	{
		m_pYuanBaoMoney->setString(SystemData::intToString(m_Vcoin).c_str());
		if (HeroData::getProp(Entity::attr_gold)<m_Vcoin)
		{
			m_pYuanBaoMoney->setColor(ccRED);
		}
		else
		{
			m_pYuanBaoMoney->setColor(ccWHITE);
		}
	}
}

void ZSDZpanel::removeItem()
{
	if(m_pMenu)
	{
		m_pMenu->removeAllChildren();
	}
	if(m_pUserItem)
	{
		m_pUserItem=NULL;
	}
	if(m_pMoney)
	{
		m_pMoney->setString("");
	}
	if(m_pYuanBaoMoney)
	{
		m_pYuanBaoMoney->setString("");
	}

	m_plock->setVisible(false);
}
