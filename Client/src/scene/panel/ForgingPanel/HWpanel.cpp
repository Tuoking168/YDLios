#include "HWpanel.h"
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
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventHelper.h"
#include "controls/CPCheckBox.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/guide/GuideHelper.h"
#include "userdata/HeroData.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "scene/panel/ForgingPanel/HSHCpanel.h"
#include "res/AudioLoader.h"
#include "scene/panel/ForgingPanel/ForgingMainPanel.h"
#include "scene/panel/ForgingPanel/HSHCpanel.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"

HWpanel::HWpanel( void ):
	m_iCurSubType(0),
	m_pTableView(NULL),
	m_pTopList(NULL),
	m_pUserItem(NULL),
	m_iHeight(0)
{
	//	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

HWpanel::~HWpanel( void )
{

}

HWpanel* HWpanel::create(int tag)
{
	HWpanel* pPanel = new HWpanel();
	if(pPanel && pPanel->init(tag))
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

bool HWpanel::init(int tag)
{
	if (!CCLayer::init())
	{
		return false;
	}

	m_iCurSubType = tag;
	std::string panelName = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (panelName == "MainPanel")
	{
		int data3 = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
		if (data3 == TAG_HWTH || data3 == TAG_HWQL || data3 == TAG_ZJTH || data3 == TAG_ZJSJ)
		{
			m_iCurSubType = data3;
		}
	}
	//装备升级界面背景
	CCScale9Sprite* bkgSprite = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_mainpanel_size.w"),SystemData::getLayoutValue("forging_mainpanel_size.h")+40);
	m_nWidth = bkgSprite->getContentSize().width;
	m_nHeight = bkgSprite->getContentSize().height+40;
	bkgSprite->setPosition(ccp(SystemData::getLayoutPoint("forging_mainpanel_pos").x,SystemData::getLayoutPoint("forging_mainpanel_pos").y-40));
	bkgSprite->setAnchorPoint(CCPointZero);
	addChild(bkgSprite);

	addCover();//保证点击事件


	CCScale9Sprite* pbottombkg = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_bottompanel_size.w"),SystemData::getLayoutValue("forging_bottompanel_size.h")-40);
	pbottombkg->setAnchorPoint(CCPointZero);
	pbottombkg->setPosition(ccp(SystemData::getLayoutPoint("forging_bottompanel_pos").x,SystemData::getLayoutPoint("forging_bottompanel_pos").y));		
	addChild(pbottombkg);


	m_pMenu = GeneralMenu::create();
	m_pMenu->setAnchorPoint(CCPointZero);
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setAnchorPoint(CCPointZero);
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	//4个按钮
	int btnType[4]={TAG_HWTH,TAG_HWQL,TAG_ZJTH,TAG_ZJSJ};
	std::string btnName[4]={"HWTH_TH","HWTH_QL","HWTH_ZJTH","HWTH_ZJSJ"};
	for (int i=0;i<4;i++)
	{
		CCMenuItemImage* pItem=SystemData::getScale9MenuItemImageByPlist("forging_button3");
		pItem->setPosition(ccp(SystemData::getLayoutPoint("SXZY_btn_image").x+95*i,SystemData::getLayoutPoint("SXZY_btn_image").y));
		pItem->setTarget(this,menu_selector(HWpanel::menuCallBack));
		pItem->setTag(btnType[i]);
		if (btnType[i]==m_iCurSubType)
		{
			pItem->selected();
		}
//		m_pTopList->addChild(pItem);
		CCLabelTTF* pLabel=SystemData::getLabelTTF(btnName[i].c_str());
		pLabel->setFontSize(16);
		pLabel->setColor(ccWHITE);
		pLabel->setPosition(pItem->getPosition());
		m_pTopList->addChild(pItem);
		m_pTopList->addChild(pLabel);
		
		
	}

	return true;
}






void HWpanel::menuCallBack(CCObject *pSender)
{
	CCMenuItemImage* pNode = dynamic_cast<CCMenuItemImage*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		if (tag == m_iCurSubType)
		{
			return;
		}
		pNode->selected();
		if (m_pTopList->getChildByTag(m_iCurSubType))
		{
			((CCMenuItemImage*)(m_pTopList->getChildByTag(m_iCurSubType)))->unselected();
		}
		m_iCurSubType = tag;
		addSubPanel(m_iCurSubType);
	}
}

void HWpanel::addSubPanel( int tag )
{
	m_pMenu->removeAllChildren();
	BasePanel* panel = NULL;
	switch (tag)
	{
	case  TAG_HWTH:
		panel = HW_THpanel::create();
		((ForgingMainPanel*)this->getParent())->updateBag(TYPE_HWTH);
		break;

	case  TAG_HWQL:
		panel = HW_QLpanel::create();
		((ForgingMainPanel*)this->getParent())->updateBag(TYPE_HWTH);
		break;

	case  TAG_ZJTH:
		panel = ZJ_THpanel::create();
		((ForgingMainPanel*)this->getParent())->updateBag(TYPE_ZJTH);
		break;

	case TAG_ZJSJ:
		panel = ZJ_SJpanel::create();
		((ForgingMainPanel*)this->getParent())->updateBag(TYPE_ZJTH);
		break;

	default:
		break;
	}

	if (panel)
	{
		panel->setTag(tag);
		panel->setAnchorPoint(CCPointZero);
		panel->setPosition(CCPointZero);
		m_pMenu->addChild(panel);
	}

	//this->runAction(CCSequence::create(CCDelayTime::create()))
}


void HWpanel::addItem(UserItem* pUserItem)
{
	m_pUserItem = pUserItem;
	if (m_iCurSubType == TAG_HWTH)
	{
		((HW_THpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
	}
	if (m_iCurSubType == TAG_HWQL)
	{
		((HW_QLpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
	}
	if (m_iCurSubType == TAG_ZJSJ)
	{
		((ZJ_SJpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
	}
	if (m_iCurSubType == TAG_ZJTH)
	{
		((ZJ_THpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
	}
}



void HWpanel::removeItem()
{
	
	if (m_iCurSubType == TAG_HWTH)
	{
		((HW_THpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
	}
	if (m_iCurSubType == TAG_HWQL)
	{
		((HW_QLpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
	}
	if (m_iCurSubType == TAG_ZJSJ)
	{
		((ZJ_SJpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
	}
	if (m_iCurSubType == TAG_ZJTH)
	{
		((ZJ_THpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
	}
}

void HWpanel::handleEvent(int channel)
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		addItem(m_pUserItem);
	}
}

void HWpanel::onEnter()
{
	BasePanel::onEnter();
	addSubPanel(m_iCurSubType);
}






//----------------------------------------------------------------------------------------------------------------------//
HW_THpanel::HW_THpanel( void ):
	m_pTopList(NULL),
	m_pbottomList(NULL),
	m_iIsProtect(0),
	m_iCurSubType(0),
	m_pUserItem(NULL),
	m_pProbability(NULL),
	m_pMoney(NULL),
	m_pBaoHuFuCount(NULL),
	m_pLeftUserItem(NULL),
	m_pRightUserItem(NULL),
	m_pTableView(NULL),
	icon01(NULL),
	icon02(NULL)
{
	
}

HW_THpanel::~HW_THpanel( void )
{

}


bool HW_THpanel::init()
{


	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	//物品说明
	m_pbottomList = GeneralMenu::create();
	m_pbottomList->setPosition(CCPointZero);
	addChild(m_pbottomList);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCMenuItemImage* pUpLevel = SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_Upgrade);
	pUpLevel->setTarget(this,menu_selector(HW_THpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("HWQL_button_pos"));
	m_pTopList->addChild(pUpLevel);

	CCLabelTTF* pUpLevelLabel = SystemData::getLabelTTF("HWTH_TH_TH");
	pUpLevelLabel->setFontSize(18);
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(SystemData::getLayoutPoint("HWQL_button_pos"));
	m_pTopList->addChild(pUpLevelLabel);

	CCLabelTTF* pQFRXYHXTHDHW=SystemData::getLabelTTF("HWTH_QFRXYHXTHDHW");//请放入需要互相替换的幻武
	pQFRXYHXTHDHW->setAnchorPoint(ccp(0.5,0.5));
	pQFRXYHXTHDHW->setPosition(ccp(pUpLevel->getPositionX(),380));
	pQFRXYHXTHDHW->setFontSize(18);
	pQFRXYHXTHDHW->setColor(ccYELLOW);
	m_pTopList->addChild(pQFRXYHXTHDHW);

	
	CCSprite* pButton1 = SystemData::getSpriteByPlist("forging_base");
	pButton1->setPosition(SystemData::getLayoutPoint("HWTH_left_pos"));
	m_pTopList->addChild(pButton1);

	CCSprite* pButton2 = SystemData::getSpriteByPlist("forging_base");
	pButton2->setPosition(SystemData::getLayoutPoint("HWTH_right_pos"));
	m_pTopList->addChild(pButton2);

	CCLabelTTF* pYSHW=SystemData::getLabelTTF("HWTH_YSHW");
	pYSHW->setColor(ccc3(3,223,204));
	pYSHW->setFontSize(18);
	pYSHW->setPosition(ccp(pButton1->getPositionX(),pButton1->getPositionY()+50));
	CCLabelTTF* pCLHW=SystemData::getLabelTTF("HWTH_CLHW");
	pCLHW->setColor(ccc3(3,223,204));
	pCLHW->setFontSize(18);
	pCLHW->setPosition(ccp(pButton2->getPositionX(),pButton2->getPositionY()+50));
	m_pTopList->addChild(pYSHW);
	m_pTopList->addChild(pCLHW);

	CCLabelTTF* pXYJB = SystemData::getLabelTTF("ZBSJ_XYJB");
	pXYJB->setFontSize(12);
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("HWQL_CLSXYB_pos"));  
	m_pMoney = SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));

	m_pMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);

	addChild(m_pMoney);
	addChild(pXYJB);

	return true;
	
}


void HW_THpanel::menuCallBack(CCObject* pSender)
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{

		int rvt = 0;
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_Upgrade:
			if (m_pLeftUserItem && m_pRightUserItem)
			{
				CommonFunction::sendmsgChangeMagicWeapon(m_pLeftUserItem->iid,m_pRightUserItem->iid);
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::NotEquip);
			}
			break;
		/*case TAG_LOCK:
			if (m_bLock)
			{
				m_bLock = false;m_pYuanBao->setVisible(false);
				m_pYuanBaoMoney->setVisible(false);
			}
			else
			{
				m_bLock = true;
				m_pYuanBao->setVisible(true);
				m_pYuanBaoMoney->setVisible(true);

			}
			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pUserItem,TAG_Ehance,m_iIsProtect)).c_str());
			break;*/
		default:
			break;
		}
//		((ForgingMainPanel* )(this->getParent()))->addTopFunc(TAG_HWTH);
		
	}
}

void HW_THpanel::initContent()
{

	if (m_pTableView)
	{
		m_pTableView->removeFromParent();
		m_iHeight = 0;
	}
	m_pTableView = CCTableViewEx::create(this,
		SystemData::getLayoutSize("forging_bottommenu_size"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(SystemData::getLayoutPoint("forging_bottommenu_pos").x,SystemData::getLayoutPoint("forging_bottommenu_pos").y-40));
	m_pTableView->reloadData();  
	addChild(m_pTableView);	
}

void HW_THpanel::addItem( UserItem* pUserItem )
{
//	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		removeItem();
		return;
	}
	if (m_pLeftUserItem)
	{
		if (m_pLeftUserItem->iid == pUserItem->iid)
		{
			CPEventHelper::uiNotify("","",Error::CanNotSameItem);
		}
		else
		{
			addItem2(pUserItem);
		}
	}
	else
	{
		m_pLeftUserItem=pUserItem;
		CCMenuItemImage* pItem=CommonFunction::getItemIcon(m_pLeftUserItem,false);
		pItem->setTarget(this,menu_selector(HW_THpanel::ItemCallBack));
		pItem->setPosition(SystemData::getLayoutPoint("HWTH_left_pos"));
		pItem->setTag(1);
		m_pMenu->addChild(pItem);
	}

}

void HW_THpanel::addItem2(UserItem* pUserItem)
{
	
	if (pUserItem->type != m_pLeftUserItem->type)
	{
		return;
	}
	int tag = 0;
	if (m_pRightUserItem)
	{
		m_pMenu->removeChildByTag(tag);
	}
	m_pRightUserItem = pUserItem;
		
		icon02= CommonFunction::getItemIcon(m_pRightUserItem,false);
		icon02->setPosition(SystemData::getLayoutPoint("HWTH_right_pos"));
		icon02->setTarget(this,menu_selector(HW_THpanel::ItemCallBack));
		icon02->setTag(tag);
		m_pMenu->addChild(icon02);
	

	


	if (m_pMoney)
	{
		int money;
		money = SystemData::getLayoutValue("HWTH_reqCoin");
		CCString* p = CCString::createWithFormat("%d",money);
		m_pMoney->setString(p->getCString());
		if (HeroData::getProp(Entity::attr_money)<money)
		{
			m_pMoney->setColor(ccRED);
		}
		else
		{
			m_pMoney->setColor(ccWHITE);
		}


	}
		
}

void HW_THpanel::removeItem()
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
	if (icon01)
	{
		icon01 = NULL;
	}
	if (icon02)
	{
		icon02 = NULL;
	}
	if (m_pLeftUserItem)
	{
		m_pLeftUserItem = NULL;
	}
	if (m_pRightUserItem)
	{
		m_pRightUserItem = NULL;
	}
}

void HW_THpanel::onEnter()
{
	setContentID(4);
	EquipBasepanel::onEnter();
}

void HW_THpanel::handleEvent( int channel )
{
	if (channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		EffectSprite* p = EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("HWTH_left_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::tihuan);	
	}
	if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		
	}
}




//----------------------------------------------------------------------------------------------------------------------------------------//

HW_QLpanel::HW_QLpanel( void ):
	m_pTopList(NULL),
	m_pUserItem(NULL),
	m_plock(NULL),
	m_bLock(false),
	m_pMoney(NULL),
	m_pYuanBao(NULL),
	m_pYuanBaoMoney(NULL),
	m_pProLabel(NULL),
	m_pRebornReq(NULL),
    m_pRebornName(NULL),
	m_pTableView(NULL),
	m_iCurNum(0),
    m_iMaxNum(0)
{
	
}
HW_QLpanel::~HW_QLpanel( void )
{
	
}

bool HW_QLpanel::init()
{
	
	CCSprite *pButton1n=SystemData::getSpriteByPlist("forging_base"); 
	CCSprite *pButton2n=SystemData::getSpriteByPlist("forging_base");
	pButton1n->setPosition(SystemData::getLayoutPoint("HWQL_left_pos"));
	pButton2n->setPosition(SystemData::getLayoutPoint("HWQL_right_pos"));
	addChild(pButton1n);
	addChild(pButton2n);

	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("HWQL_QFRXYQLDHW");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1n->getPositionX(),pButton1n->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("HWQL_QLCL");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2n->getPositionX(),pButton2n->getPositionY()+50));
	addChild(pSJWPK);
	addChild(pSJCLK);

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBQH_QHDM_smallborder_size.w"),SystemData::getLayoutValue("ZBQH_QHDM_smallborder_size.h"));
	pBorder->setPosition(SystemData::getLayoutPoint("HWQL_smallborder_pos"));
	m_pTopList->addChild(pBorder);
	CCSprite *pButton3=SystemData::getSpriteByPlist("forging_result");
	pButton3->setPosition(SystemData::getLayoutPoint("HWQL_SJXGYL_pos"));
	m_pTopList->addChild(pButton3);
	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("HWTH_QLXGYL");
	pSJXGYL->setAnchorPoint(CCPointZero);
	pSJXGYL->setPosition(ccp(pButton3->getPositionX()+pButton3->getContentSize().width,pButton3->getPositionY()));
	pSJXGYL->setFontSize(18);
	pSJXGYL->setColor(ccWHITE);
	m_pTopList->addChild(pSJXGYL);

	//打磨条
	CCScale9Sprite* pProgressBkg=SystemData::getScale9SpriteByPlist("ZBQH_QHDM_jindutiao_bkg",SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.w"),SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.h"));
	pProgressBkg->setAnchorPoint(CCPointZero);
	pProgressBkg->setPosition(SystemData::getLayoutPoint("HWQL_QLDS_jindutiao_bkg"));
	m_pTopList->addChild(pProgressBkg);
	m_pProgress=SystemData::getScale9SpriteByPlist("ZBQH_QHDM_jindutiao",SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.w"),SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.h"));
	m_pProgress->setAnchorPoint(CCPointZero);
	m_pProgress->setPosition(SystemData::getLayoutPoint("HWQL_QLDS_jindutiao_bkg"));
	m_pProgress->setScaleX(0);
	m_pTopList->addChild(m_pProgress);

	initLabelNum();

	CCLabelTTF* pDMDS=SystemData::getLabelTTF("HWQL_QLDS_text");
	pDMDS->setAnchorPoint(CCPointZero);
	pDMDS->setPosition(ccp(pProgressBkg->getPositionX()+pProgressBkg->getContentSize().width+5,pProgressBkg->getPositionY()));
	pDMDS->setFontSize(16);
	pDMDS->setColor(ccWHITE);
	m_pTopList->addChild(pDMDS);

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(HW_QLpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_button3_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("HWQL_QL_QL");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);


	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBSJ_XYJB");//需要金币
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("HWQL_label1_pos"));
//	CCLabelTTF* m_pMoney = NULL;
	m_pMoney=SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);	
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));
//	CCLabelTTF* m_pYuanBao = NULL;
	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("HWQL_CLSXYB_pos"));
//	CCLabelTTF* m_pYuanBaoMoney = NULL;
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+75,m_pYuanBao->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝 
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);

	CPCheckBox* plock1=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock1->setTag(TAG_LOCK);
	plock1->setHandler(this,menu_selector(HW_QLpanel::menuCallBack));
	plock1->setPosition(SystemData::getLayoutPoint("HWQL_label5_pos"));
	m_pTopList->addChild(plock1);

	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);

	addChild(m_pYuanBao);
	addChild(m_pMoney);
	addChild(m_pYuanBaoMoney);
	addChild(pXYJB);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);
	return true;



}

void HW_QLpanel::menuCallBack(CCObject* pSender)
{
//	CCLog("dwpanel press");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int rvt = 0;
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_UPGRADE:
			if (m_pUserItem)
			{
				if (m_pUserItem->data[ItemEquip::Item_EnhanceLevel]>=50)//以前15器灵
				{
					CPEventHelper::uiNotify("","",Error::Item_MaxLvl);	
					return;
				}	
			}
			rvt = CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_QiLing,m_bLock,0,0,0);
			if (rvt == Error::Success)
			{
				if (m_bLock)
				{
					CommonFunction::sendmsgQiling(m_pUserItem->iid,1);
				}
				else
				{
					CommonFunction::sendmsgQiling(m_pUserItem->iid);
				}
			}
			else
			{
				CPEventHelper::uiNotify("","",rvt);
			}
			break;

		case TAG_LOCK:
			if (m_bLock)
			{
				m_bLock = false;
				m_pYuanBao->setVisible(false);
				m_pYuanBaoMoney->setVisible(false);
			} 
			else
			{
				m_bLock = true;
				m_pYuanBao->setVisible(true);
				m_pYuanBaoMoney->setVisible(true);
			}
//			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pUserItem,TAG_Ehance,m_iIsProtect)).c_str());
			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pUserItem,TAG_QiLing,0)).c_str());
		default:
			break;
		}
		
	}
	
}

void HW_QLpanel::initLabelNum()
{
	if (m_pUserItem)
	{
		m_iCurNum=m_pUserItem->data[ItemEquip::Item_QLPolish];
		LuaData::getProp("gdOpenMagicWeapon",m_pUserItem->data[ItemEquip::Item_EnhanceLevel],"lvlcnt",m_iMaxNum);
	}
	if (m_pProgress && m_iMaxNum != 0)
	{
		float n = (float)m_iCurNum/(float)m_iMaxNum;
		m_pProgress->setScaleX(n);
	}
	if (m_iMaxNum==0)
	{
		m_pProgress->setScaleX(1);
		m_iCurNum=m_iMaxNum;
	}
	if (m_pProLabel)
	{
		CCString* pStr = CCString::createWithFormat("%d/%d",m_iCurNum,m_iMaxNum);
		m_pProLabel->setString(pStr->getCString());
	}
	else
	{
		CCString* pStr=CCString::createWithFormat("%d/%d",m_iCurNum,m_iMaxNum);
		m_pProLabel=CCLabelTTF::create(pStr->getCString(),"",16);
		m_pProLabel->setAnchorPoint(ccp(0.5,0));
		m_pProLabel->setPosition(ccp(m_pProgress->getPositionX()+SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.w")/2,m_pProgress->getPositionY()));
		m_pTopList->addChild(m_pProLabel);
	}
}

void  HW_QLpanel::addItem(UserItem* pUserItem)
{
	m_pMenu->removeAllChildren();
	if (pUserItem == NULL)
	{
		return;
	}
	m_pUserItem = pUserItem;
	CCMenuItemImage* icon = CommonFunction::getItemIcon(pUserItem,false);
	icon->setPosition(ccp(SystemData::getLayoutPoint("ZBQH_QHDM_button1_pos").x,SystemData::getLayoutPoint("ZBQH_QHDM_button1_pos").y-40));
	icon->setTarget(this,menu_selector(HW_QLpanel::ItemCallBack));
	m_pMenu->addChild(icon);

	if (m_pUserItem->data[ItemEquip::Item_EnhanceLevel]>=50)//以前15
	{
		initLabelNum();
		return ;
	}

	CCMenuItemImage* req = CommonFunction::getReqMagicWeaponQLItem(pUserItem);
	req->setPosition(ccp(SystemData::getLayoutPoint("ZBQH_QHDM_button2_pos").x,SystemData::getLayoutPoint("ZBQH_QHDM_button2_pos").y-40));
	req->setTarget(this,menu_selector(HW_QLpanel::ItemCallBack));
	m_pMenu->addChild(req);

	CCMenuItemImage* QilingAft = CommonFunction::getTgtMagicWeaponQLItem(pUserItem);
	QilingAft->setTarget(this,menu_selector(HW_QLpanel::ItemCallBack));
	QilingAft->setPosition(SystemData::getLayoutPoint("HWQL_SJXGYL_pos"));
	m_pMenu->addChild(QilingAft);

	if (m_pMoney)
	{
		int money;
		LuaData::getProp("gdOpenMagicWeapon",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqGold",money);
		CCString* p = CCString::createWithFormat("%d",money);
		m_pMoney->setString(p->getCString());
		if (HeroData::getProp(Entity::attr_money)<money)
		{
			m_pMoney->setColor(ccRED);
		}
		else
		{
			m_pMoney->setColor(ccWHITE);
		}
	}

	if (m_pYuanBaoMoney)
	{
		int yuanBao;
		yuanBao = CommonFunction::getReqVcoin(m_pUserItem,TAG_QiLing,0);
		if (HeroData::getProp(Entity::attr_gold)<yuanBao)
		{
			m_pYuanBaoMoney->setColor(ccRED);
		}
		else
		{
			m_pYuanBaoMoney->setColor(ccWHITE);
		}
	}


	initLabelNum();
}

void HW_QLpanel::initContent()
{
	if (m_pTableView)
	{
		m_pTableView->removeFromParent();
		m_iHeight = 0;
	}
	m_pTableView = CCTableViewEx::create(this,
		SystemData::getLayoutSize("forging_bottommenu_size"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(SystemData::getLayoutPoint("forging_bottommenu_pos").x,SystemData::getLayoutPoint("forging_bottommenu_pos").y-40));
	m_pTableView->reloadData();  
	addChild(m_pTableView);	
}

void HW_QLpanel::handleEvent( int channel )
{
	if (channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
	//	addItem(m_pUserItem);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("HWQL_left_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::qilingshibai);
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		EffectSprite* p = EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("HWQL_left_pos"));
		addChild(p);
		EffectSprite* p2=EffectSprite::create(Effect::effect_zhishengyiji,1);
		p2->setPosition(ccp(m_pProgress->getPositionX()+m_pProgress->getContentSize().width/2,m_pProgress->getPositionY()));
		addChild(p2);
	}
}

void HW_QLpanel::onEnter()
{
	setContentID(17);
	EquipBasepanel::onEnter();
}




//--------------------------------------------------------------------------------------------------------------------------------------------//



ZJ_THpanel::ZJ_THpanel( void ):
	m_pTopList(NULL),
	m_pbottomList(NULL),
	m_iHeight(0),
	m_pLeftUserItem(NULL),
	m_pRightUserItem(NULL),
	m_pTableView(NULL),
	icon01(NULL),
	icon02(NULL)
{

}

ZJ_THpanel::~ZJ_THpanel( void )
{

}

bool ZJ_THpanel::init()
{
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	//物品说明
	m_pbottomList = GeneralMenu::create();
	m_pbottomList->setPosition(CCPointZero);
	addChild(m_pbottomList);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);


	CCMenuItemImage* pUpLevel = SystemData::getMenuItemImageByPlist("forging_button3");

	pUpLevel->setTag(TAG_02);
	pUpLevel->setTarget(this,menu_selector(ZJ_THpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("HWQL_button_pos"));
	m_pTopList->addChild(pUpLevel);

	CCLabelTTF* pUpLevelLabel = SystemData::getLabelTTF("HWTH_TH_TH");
	pUpLevelLabel->setFontSize(18);
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(SystemData::getLayoutPoint("HWQL_button_pos"));
	m_pTopList->addChild(pUpLevelLabel);

	CCLabelTTF* pQFRXYHXTHDHW=SystemData::getLabelTTF("HWTH_QFRXYTHDZJ");//请放入需要互相替换的足迹
	pQFRXYHXTHDHW->setAnchorPoint(ccp(0.5,0.5));
	pQFRXYHXTHDHW->setPosition(ccp(pUpLevel->getPositionX(),380));
	pQFRXYHXTHDHW->setFontSize(18);
	pQFRXYHXTHDHW->setColor(ccYELLOW);
	m_pTopList->addChild(pQFRXYHXTHDHW);


	CCSprite* pButton1 = SystemData::getSpriteByPlist("forging_base");
	pButton1->setPosition(SystemData::getLayoutPoint("HWTH_left_pos"));
	m_pTopList->addChild(pButton1);

	CCSprite* pButton2 = SystemData::getSpriteByPlist("forging_base");
	pButton2->setPosition(SystemData::getLayoutPoint("HWTH_right_pos"));
	m_pTopList->addChild(pButton2);

	CCLabelTTF* pYSHW=SystemData::getLabelTTF("HWTH_YSZJ");
	pYSHW->setColor(ccc3(3,223,204));
	pYSHW->setFontSize(18);
	pYSHW->setPosition(ccp(pButton1->getPositionX(),pButton1->getPositionY()+50));
	CCLabelTTF* pCLHW=SystemData::getLabelTTF("HWTH_CLZJ");  
	pCLHW->setColor(ccc3(3,223,204));
	pCLHW->setFontSize(18);
	pCLHW->setPosition(ccp(pButton2->getPositionX(),pButton2->getPositionY()+50));
	m_pTopList->addChild(pYSHW);
	m_pTopList->addChild(pCLHW);

	CCLabelTTF* pXYJB = SystemData::getLabelTTF("ZBSJ_XYJB");
	pXYJB->setFontSize(12);
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("HWQL_CLSXYB_pos"));  
	m_pMoney = SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));


	pXYJB->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);

	addChild(pXYJB);
	addChild(m_pMoney);

	//物品说明
	m_pbottomList = GeneralMenu::create();
	m_pbottomList->setPosition(CCPointZero);
	addChild(m_pbottomList);

	return true;

}

void ZJ_THpanel::menuCallBack(CCObject* pSender)
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	int rvt = 0;
	int tag = pNode->getTag();
	switch (tag)
	{
	case TAG_02:
		if (m_pLeftUserItem && m_pRightUserItem)
		{
			int leftLv = 0;
			int rightLv = 0;
			LuaData::getProp("gdItems",m_pLeftUserItem->sid,"lvl",leftLv);
			LuaData::getProp("gdItems",m_pRightUserItem->sid,"lvl",rightLv);
			if (leftLv == rightLv)
			{
				CPEventHelper::uiNotify("","",Error::CanNotSameFootLv);
				return;
			}
			CommonFunction::sendmsgChangeFoot(m_pLeftUserItem->iid,m_pRightUserItem->iid);
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

void ZJ_THpanel::initContent()
{
	if (m_pTableView)
	{
		m_pTableView->removeFromParent();
		m_iHeight = 0;
	}
	m_pTableView = CCTableViewEx::create(this,
		SystemData::getLayoutSize("forging_bottommenu_size"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(SystemData::getLayoutPoint("forging_bottommenu_pos").x,SystemData::getLayoutPoint("forging_bottommenu_pos").y-40));
	m_pTableView->reloadData();  
	addChild(m_pTableView);	
}

void ZJ_THpanel::addItem( UserItem* pUserItem )
{
	//	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		removeItem();
		return;
	}
	if (m_pLeftUserItem)
	{
		if (m_pLeftUserItem->iid == pUserItem->iid)
		{
			CPEventHelper::uiNotify("","",Error::CanNotSameItem);
		}
		else
		{
			addItem2(pUserItem);
		}
	}
	else
	{
		m_pLeftUserItem=pUserItem;
		CCMenuItemImage* pItem=CommonFunction::getItemIcon(m_pLeftUserItem,false);
		pItem->setTarget(this,menu_selector(HW_THpanel::ItemCallBack));
		pItem->setPosition(SystemData::getLayoutPoint("HWTH_left_pos"));
		pItem->setTag(1);
		m_pMenu->addChild(pItem);
	}

}

void ZJ_THpanel::addItem2(UserItem* pUserItem)
{

	if (pUserItem->type != m_pLeftUserItem->type)
	{
		return;
	}
	int tag = 0;
	if (m_pRightUserItem)
	{
		m_pMenu->removeChildByTag(tag);
	}
	m_pRightUserItem = pUserItem;

	icon02= CommonFunction::getItemIcon(m_pRightUserItem,false);
	icon02->setPosition(SystemData::getLayoutPoint("HWTH_right_pos"));
	icon02->setTarget(this,menu_selector(ZJ_THpanel::ItemCallBack));
	icon02->setTag(tag);
	m_pMenu->addChild(icon02);





	if (m_pMoney)
	{
		int money;
		money = SystemData::getLayoutValue("HWTH_reqCoin");
		CCString* p = CCString::createWithFormat("%d",money);
		m_pMoney->setString(p->getCString());
		if (HeroData::getProp(Entity::attr_money)<money)
		{
			m_pMoney->setColor(ccRED);
		}
		else
		{
			m_pMoney->setColor(ccWHITE);
		}


	}

}

void ZJ_THpanel::onEnter()
{
	setContentID(22);
	EquipBasepanel::onEnter();
}

void ZJ_THpanel::removeItem()
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
	if (icon01)
	{
		icon01 = NULL;
	}
	if (icon02)
	{
		icon02 = NULL;
	}
	if (m_pLeftUserItem)
	{
		m_pLeftUserItem = NULL;
	}
	if (m_pRightUserItem)
	{
		m_pRightUserItem = NULL;
	}
}

void ZJ_THpanel::handleEvent( int channel )
{
	if (channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		EffectSprite* p = EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("HWTH_left_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::tihuan);	
	}
	if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{

	}
}


//---------------------------------------------------------------------------------------------------------------------------------------------------//

ZJ_SJpanel::ZJ_SJpanel( void ):
	m_pTopList(NULL),
	m_iCurNum(0),
	m_iMaxNum(0),
	m_pProLabel(NULL),
	m_pTableView(NULL),
	m_pMoney(NULL),
	m_pYuanBao(NULL),
	m_pYuanBaoMoney(NULL),
	yuanBao(0)
{

}
ZJ_SJpanel::~ZJ_SJpanel( void )
{

}

bool ZJ_SJpanel::init()
{
	//界面背景
	CCSprite *pButton1n=SystemData::getSpriteByPlist("forging_base");
	CCSprite *pButton2n=SystemData::getSpriteByPlist("forging_base");
	pButton1n->setPosition(ccp(SystemData::getLayoutPoint("ZBQH_QHDM_button1_pos").x,SystemData::getLayoutPoint("ZBQH_QHDM_button1_pos").y-40));
	pButton2n->setPosition(ccp(SystemData::getLayoutPoint("ZBQH_QHDM_button2_pos").x,SystemData::getLayoutPoint("ZBQH_QHDM_button2_pos").y-40));
	addChild(pButton1n);
	addChild(pButton2n);

	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("HWQL_QFRXYSJDZJ");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1n->getPositionX(),pButton1n->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("HWQL_SJCL");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2n->getPositionX(),pButton2n->getPositionY()+50));
	addChild(pSJWPK);
	addChild(pSJCLK);

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBQH_QHDM_smallborder_size.w"),SystemData::getLayoutValue("ZBQH_QHDM_smallborder_size.h"));
	pBorder->setPosition(SystemData::getLayoutPoint("HWQL_smallborder_pos"));
	m_pTopList->addChild(pBorder);
	CCSprite *pButton3=SystemData::getSpriteByPlist("forging_result");
	pButton3->setPosition(SystemData::getLayoutPoint("HWQL_SJXGYL_pos"));
	m_pTopList->addChild(pButton3);
	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("ZJSJ_SJXGYL");
	pSJXGYL->setAnchorPoint(CCPointZero);
	pSJXGYL->setPosition(ccp(pButton3->getPositionX()+pButton3->getContentSize().width,pButton3->getPositionY()));
	pSJXGYL->setFontSize(18);
	pSJXGYL->setColor(ccWHITE);
	m_pTopList->addChild(pSJXGYL);

	//打磨条
	CCScale9Sprite* pProgressBkg=SystemData::getScale9SpriteByPlist("ZBQH_QHDM_jindutiao_bkg",SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.w"),SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.h"));
	pProgressBkg->setAnchorPoint(CCPointZero);
	pProgressBkg->setPosition(SystemData::getLayoutPoint("HWQL_QLDS_jindutiao_bkg"));
	m_pTopList->addChild(pProgressBkg);
	m_pProgress=SystemData::getScale9SpriteByPlist("ZBQH_QHDM_jindutiao",SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.w"),SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.h"));
	m_pProgress->setAnchorPoint(CCPointZero);
	m_pProgress->setPosition(SystemData::getLayoutPoint("HWQL_QLDS_jindutiao_bkg"));
	m_pProgress->setScaleX(0);
	m_pTopList->addChild(m_pProgress);

	initLabelNum();

	CCLabelTTF* pDMDS=SystemData::getLabelTTF("ZJSJ_SJDS_text");
	pDMDS->setAnchorPoint(CCPointZero);
	pDMDS->setPosition(ccp(pProgressBkg->getPositionX()+pProgressBkg->getContentSize().width+5,pProgressBkg->getPositionY()));
	pDMDS->setFontSize(16);
	pDMDS->setColor(ccWHITE);
	m_pTopList->addChild(pDMDS);

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(tag_up);
	pUpLevel->setTarget(this,menu_selector(HW_QLpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_button3_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("ZJSJ_SJ_SJ");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);


	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBSJ_XYJB");//需要金币
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("HWQL_label1_pos"));
	m_pMoney=SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);	
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));
	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("HWQL_CLSXYB_pos"));
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+75,m_pYuanBao->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝 
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);

	CPCheckBox* plock1=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock1->setTag(TAG_LOCK);
	plock1->setHandler(this,menu_selector(HW_QLpanel::menuCallBack));
	plock1->setPosition(SystemData::getLayoutPoint("HWQL_label5_pos"));
	m_pTopList->addChild(plock1);

	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	//pTHYB->setAnchorPoint(CCPointZero);

	//addChild(pTHYB);
	addChild(m_pYuanBao);
	addChild(m_pMoney);
	addChild(m_pYuanBaoMoney);
	addChild(pXYJB);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);
	return true;
}

void ZJ_SJpanel::menuCallBack(CCObject* pSender)
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int rvt = 0;
		int tag = pNode->getTag();
		switch (tag)
		{
		case tag_up:
			if (m_pUserItem)
			{
				int lvl = 0;
				LuaData::getProp("gdItems",m_pUserItem->sid,"lvl",lvl);
				if (lvl>=20)
				{
					CPEventHelper::uiNotify("","",Error::Item_MaxLvl);	
					return;
				}	
			}
			rvt = CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_FootShengjie,m_bLock,0,0,0);
			if (rvt == Error::Success)
			{
				if (m_bLock)
				{
					CommonFunction::sendmsgFootUp(m_pUserItem->iid,1);
				}
				else
				{
					CommonFunction::sendmsgFootUp(m_pUserItem->iid);
				}
			}
			else
			{
				CPEventHelper::uiNotify("","",rvt);
			}
			break;
		case TAG_LOCK:
			if (m_bLock)
			{
				m_bLock = false;
				m_pYuanBao->setVisible(false);
				m_pYuanBaoMoney->setVisible(false);
			} 
			else
			{
				m_bLock = true;
				m_pYuanBao->setVisible(true);
				m_pYuanBaoMoney->setVisible(true);
			}
			m_pYuanBaoMoney->setString(SystemData::intToString(yuanBao).c_str());
		default:
			break;
		}
		//	HW_THpanel* p = NULL;
		//((ForgingMainPanel* )(this->getParent()))->addTopFunc(TAG_ZJSJ);

	}

}

void ZJ_SJpanel::initContent()
{
	if (m_pTableView)
	{
		m_pTableView->removeFromParent();
		m_iHeight = 0;
	}
	m_pTableView = CCTableViewEx::create(this,
		SystemData::getLayoutSize("forging_bottommenu_size"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(SystemData::getLayoutPoint("forging_bottommenu_pos").x,SystemData::getLayoutPoint("forging_bottommenu_pos").y-40));
	m_pTableView->reloadData();  
	addChild(m_pTableView);	
}

void ZJ_SJpanel::addItem(UserItem * pUserItem)
{
	m_pMenu->removeAllChildren();
	if (pUserItem == NULL)
	{
		return;
	}
	m_pUserItem = pUserItem;
	int lvl = 0;
	LuaData::getProp("gdItems",m_pUserItem->sid,"lvl",lvl);
	if (lvl>=20)
	{
		CPEventHelper::uiNotify("","",Error::Item_MaxLvl);
		return ;
	}

	CCMenuItemImage* icon = CommonFunction::getItemIcon(pUserItem,false);
	icon->setPosition(ccp(SystemData::getLayoutPoint("ZBQH_QHDM_button1_pos").x,SystemData::getLayoutPoint("ZBQH_QHDM_button1_pos").y-40));
	icon->setTarget(this,menu_selector(ZJ_SJpanel::ItemCallBack));
	m_pMenu->addChild(icon);

	CCMenuItemImage* req = CommonFunction::getReqFootUpItem(pUserItem);
	req->setPosition(ccp(SystemData::getLayoutPoint("ZBQH_QHDM_button2_pos").x,SystemData::getLayoutPoint("ZBQH_QHDM_button2_pos").y-40));
	req->setTarget(this,menu_selector(ZJ_SJpanel::ItemCallBack));
	m_pMenu->addChild(req);

	CCMenuItemImage* FootUpAft = CommonFunction::getTgtFootUpItem(pUserItem);
	FootUpAft->setTarget(this,menu_selector(ZJ_SJpanel::ItemCallBack));
	FootUpAft->setPosition(SystemData::getLayoutPoint("HWQL_SJXGYL_pos"));
	m_pMenu->addChild(FootUpAft);

	if (m_pMoney)
	{
		int money = 0;
		LuaData::getProp("gdFootUp",pUserItem->sid,"reqGold",money);
		CCString* p = CCString::createWithFormat("%d",money);
		m_pMoney->setString(p->getCString());
		if (HeroData::getProp(Entity::attr_money)<money)
		{
			m_pMoney->setColor(ccRED);
		}
		else
		{
			m_pMoney->setColor(ccWHITE);
		}
	}

	if (m_pYuanBaoMoney)
	{
		yuanBao = CommonFunction::getReqVcoin(m_pUserItem,TAG_FootShengjie,0);
		if (HeroData::getProp(Entity::attr_gold)<yuanBao)
		{
			m_pYuanBaoMoney->setColor(ccRED);
		}
		else
		{
			m_pYuanBaoMoney->setColor(ccWHITE);
		}
	}


	initLabelNum();
}

void ZJ_SJpanel::initLabelNum()
{
	if (m_pUserItem)
	{
		m_iCurNum=m_pUserItem->data[ItemEquip::Item_FootPolish];
		LuaData::getProp("gdFootUp",m_pUserItem->sid,"upValue",m_iMaxNum);
	}
	if (m_pProgress && m_iMaxNum != 0)
	{
		float n = (float)m_iCurNum/(float)m_iMaxNum;
		m_pProgress->setScaleX(n);
	}
	if (m_iMaxNum==0)
	{
		m_pProgress->setScaleX(1);
		m_iCurNum=m_iMaxNum;
	}
	if (m_pProLabel)
	{
		CCString* pStr = CCString::createWithFormat("%d/%d",m_iCurNum,m_iMaxNum);
		m_pProLabel->setString(pStr->getCString());
	}
	else
	{
		CCString* pStr=CCString::createWithFormat("%d/%d",m_iCurNum,m_iMaxNum);
		m_pProLabel=CCLabelTTF::create(pStr->getCString(),"",16);
		m_pProLabel->setAnchorPoint(ccp(0.5,0));
		m_pProLabel->setPosition(ccp(m_pProgress->getPositionX()+SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.w")/2,m_pProgress->getPositionY()));
		m_pTopList->addChild(m_pProLabel);
	}
}

void ZJ_SJpanel::onEnter()
{
	setContentID(21);
	EquipBasepanel::onEnter();
}

void ZJ_SJpanel::handleEvent( int channel )
{
	if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		EffectSprite* p = EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("HWQL_left_pos"));
		addChild(p);
	}
}

void ZJ_SJpanel::onCPEvent()
{
	yuanBao = CommonFunction::getReqVcoin(m_pUserItem,TAG_FootShengjie,0);
}
