#include "ZBQHpanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/LayoutData.h"
#include "event/EventProtocol.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"

#include "userdata/netdata/GameRole.h"
#include "scene/panel/ForgingPanel/ForgingMainPanel.h"

#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"

#include "CommonFunction.h"
#include "userdata/luadata/LuaData.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventHelper.h"
#include "WPHCpanel.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "controls/CPCheckBox.h"
#include "res/AudioLoader.h"
#include "utils/StringUtils.h"

ZBQHpanel::ZBQHpanel( void ):
	m_pTopList(NULL),
	m_pBottomList(NULL),
	m_iHeight(0),
	m_pTabelView(NULL),
	m_iCurSubType(0),
	m_pUserItem(NULL)
{

}

ZBQHpanel::~ZBQHpanel( void )
{

}

ZBQHpanel* ZBQHpanel::create(int tag)
{
	ZBQHpanel* pPanel = new ZBQHpanel();
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

bool ZBQHpanel::init( int tag )
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_iCurSubType=tag;

	std::string panelname=CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (panelname=="MainPanel")
	{
		int data3=CPEventHelper::getEventIntData(CPEventData::VALUE_4);
		if (data3==TAG_PTQH || data3==TAG_WMQH || data3==TAG_QHDM || data3==TAG_CBYH)
		{
			m_iCurSubType=data3;
		}
	}

	//装备升级界面背景
	CCScale9Sprite* bkgSprite = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_mainpanel_size.w"),SystemData::getLayoutValue("forging_mainpanel_size.h")+40);
	m_nWidth = bkgSprite->getContentSize().width;
	m_nHeight = bkgSprite->getContentSize().height;
	bkgSprite->setPosition(SystemData::getLayoutPoint("forging_mainpanel_pos"));
	bkgSprite->setAnchorPoint(CCPointZero);
	addChild(bkgSprite);

	addCover();//保证点击事件

	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	//4 个切换按钮
	int btnType[4]={TAG_PTQH,TAG_WMQH,TAG_QHDM,TAG_CBYH};
	std::string btnName[4]={"ZBQH_PTQH","ZBQH_WMQH","ZBQH_QHDM","ZBQH_CBYH"};
	for (int i=0;i<4;i++) 
	{
		CCMenuItemImage* pItem=SystemData::getScale9MenuItemImageByPlist("SXZY_btn_image");
		pItem->setPosition(ccp(SystemData::getLayoutPoint("ZBQH_mainbtn_pos").x+95*i,SystemData::getLayoutPoint("ZBQH_mainbtn_pos").y));
		pItem->setTarget(this,menu_selector(ZBQHpanel::menuCallBack));
		pItem->setTag(btnType[i]);
		if (btnType[i]==m_iCurSubType)
		{
			pItem->selected(); 
		}
		m_pTopList->addChild(pItem);
		CCLabelTTF* pLabel=SystemData::getLabelTTF(btnName[i].c_str());
		pLabel->setFontSize(16);
		pLabel->setColor(ccWHITE);
		pLabel->setPosition(pItem->getPosition());
		m_pTopList->addChild(pLabel);
	}

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	//物品说明menu
	m_pBottomList=GeneralMenu::create();
	m_pBottomList->setPosition(CCPointZero);
	addChild(m_pBottomList);	

	CCScale9Sprite* pbottombkg = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_bottompanel_size.w"),SystemData::getLayoutValue("forging_bottompanel_size.h")-40);
	pbottombkg->setAnchorPoint(CCPointZero);
	pbottombkg->setPosition(ccp(SystemData::getLayoutPoint("forging_bottompanel_pos").x,SystemData::getLayoutPoint("forging_bottompanel_pos").y+40));		
	addChild(pbottombkg);


	return true;
}


cocos2d::CCSize ZBQHpanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(420, m_iHeight);
}

cocos2d::extension::CCTableViewCell* ZBQHpanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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

		int i=2;
		if (m_iCurSubType==TAG_PTQH)
		{
			i=2;
		}
		else if (m_iCurSubType==TAG_WMQH)
		{
			i = 19;
		}
		else if (m_iCurSubType==TAG_QHDM)
		{
			i = 18;
		}
		else if (m_iCurSubType==TAG_CBYH)
		{
			i = 20;
		}

		std::string content;
		LuaData::getProp("gddescription",i,"content",content);
		CPRichText* pLabel = RichTextUtils::getRichText(content.c_str(),16,SystemData::getLayoutValue("forging_bottommenu_size.w"),0);
		//CCLabelTTF* pLabel=CCLabelTTF::create(content.c_str(),"",16);
		pLabel->setPosition(CCPointZero);
		pLabel->setAnchorPoint(CCPointZero);
		//pLabel->setDimensions(CCSizeMake(SystemData::getLayoutValue("forging_bottommenu_size.w"),0));
		//pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLayer->addChild(pLabel);
		m_iHeight=pLabel->getContentSize().height;
	}
	return cell;
}

unsigned int ZBQHpanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}


void ZBQHpanel::menuCallBack( CCObject *pSender )
{
	CCMenuItemImage* pNode = dynamic_cast<CCMenuItemImage*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		pNode->selected();
		if (tag==m_iCurSubType)
		{
			return;
		}
		initTopBtn(tag);
		/*if (m_pTopList->getChildByTag(m_iCurSubType))
		{
			((CCMenuItemImage*)(m_pTopList->getChildByTag(m_iCurSubType)))->unselected();
		}
		m_iCurSubType=tag;
		addSubPanel(m_iCurSubType);*/
	}
}


void ZBQHpanel::initContent()
{
	if (m_pTabelView)
	{
		m_pTabelView->removeFromParent();
		m_iHeight= 0;
		//m_pTabelView->reloadData();
	}
	m_pTabelView=CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("forging_bottommenu_size").width,
		SystemData::getLayoutSize("forging_bottommenu_size").height-40),kCCScrollViewDirectionVertical,this,NULL);
	m_pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTabelView->setAnchorPoint(CCPointZero);
	m_pTabelView->setPosition(ccp(SystemData::getLayoutPoint("forging_bottommenu_pos").x,SystemData::getLayoutPoint("forging_bottommenu_pos").y+40));
	m_pTabelView->reloadData();  
	addChild(m_pTabelView);
}

void ZBQHpanel::onEnter()
{
	BasePanel::onEnter();
	//this->runAction(CCSequence::create(CCDelayTime::create(0.08f),CCCallFunc::create(this,callfunc_selector(ZBQHpanel::initContent)),NULL));
	addSubPanel(m_iCurSubType);
}

void ZBQHpanel::onExit()
{
	BasePanel::onExit();
}

void ZBQHpanel::addItem( UserItem* pUserItem )
{
	m_pUserItem=pUserItem;	
	if (m_iCurSubType==TAG_PTQH)
	{
		if (pUserItem && pUserItem->data[ItemEquip::Item_EnhanceLevel]>=10)
		{

			initTopBtn(TAG_QHDM);
			//addSubPanel(TAG_QHDM);
			((QHDMpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
		}
		else
		{
			((PTQHpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
		}
	}
	else if (m_iCurSubType==TAG_WMQH)
	{
		((WMQHpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
	}
	else if (m_iCurSubType==TAG_QHDM)
	{
		if (pUserItem && pUserItem->data[ItemEquip::Item_EnhanceLevel]<10)
		{
			initTopBtn(TAG_PTQH);
			//addSubPanel(TAG_PTQH);
			((PTQHpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
		}
		else
		{
			((QHDMpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
		}
	}
	else if (m_iCurSubType==TAG_CBYH)
	{
		((CBYHpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
	}
}

void ZBQHpanel::removeItem()
{
	if (m_iCurSubType==TAG_PTQH)
	{
		((PTQHpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
		//((ForgingMainPanel*)this->getParent())->updateBag(TYPE_JPZY);
	}
	else if (m_iCurSubType==TAG_WMQH)
	{
		((WMQHpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
	}
	else if (m_iCurSubType==TAG_QHDM)
	{
		((QHDMpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
	}
	else if (m_iCurSubType==TAG_CBYH)
	{
		((CBYHpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
	}
}

void ZBQHpanel::addSubPanel( int tag )
{
	m_pMenu->removeAllChildren();
	BasePanel* panel=NULL;
	switch (tag)
	{
	case TAG_PTQH:
		panel=PTQHpanel::create();
		break;
	case TAG_WMQH:
		panel=WMQHpanel::create();
		break;
	case TAG_QHDM:
		panel=QHDMpanel::create();
		break;
	case TAG_CBYH:
		panel=CBYHpanel::create();
		//更新背包
		((ForgingMainPanel*)this->getParent())->updateBag(Type_wing);
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

	this->runAction(CCSequence::create(CCDelayTime::create(0.08f),CCCallFunc::create(this,callfunc_selector(ZBQHpanel::initContent)),NULL));
}

void ZBQHpanel::initTopBtn( int tag )
{
	if (m_pTopList->getChildByTag(tag))
	{
		((CCMenuItemImage*)(m_pTopList->getChildByTag(tag)))->selected();
	}
	if (m_pTopList->getChildByTag(m_iCurSubType))
	{
		((CCMenuItemImage*)(m_pTopList->getChildByTag(m_iCurSubType)))->unselected();
	}
	if (m_iCurSubType==TAG_CBYH && m_iCurSubType!=tag)
	{
		((ForgingMainPanel*)this->getParent())->updateBag(TYPE_ZBQH);
	}
	m_iCurSubType=tag;
	addSubPanel(m_iCurSubType);
}

void ZBQHpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		addItem(m_pUserItem);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------//


WMQHpanel::WMQHpanel( void ):
	m_iEnhanceType(0),
	m_pUserItem(NULL),
	m_pMoney(NULL),
	m_bLock(false),
	m_pYuanBao(NULL),
	m_pYuanBaoMoney(NULL),
	m_pTopList(NULL),
	m_pCurrentItem(NULL),
	m_pReqMenu(NULL),
	m_iCurBHFType(0),
	m_icurReqItem(0)
{

}


WMQHpanel::~WMQHpanel( void )
{

}

WMQHpanel* WMQHpanel::create(int tag)
{
	WMQHpanel* pPanel = new WMQHpanel();
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

bool WMQHpanel::init( int tag )
{
	m_icurReqItem=tag;
	std::string panelname=CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (panelname=="MainPanel")
	{
		int data4=CPEventHelper::getEventIntData(CPEventData::VALUE_5);

		m_icurReqItem=data4;
	}

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	CCSprite *pList=SystemData::getSpriteByPlist("forging_up");//下拉框
	pList->runAction(CCFlipY::create(true));
	CCMenuItemImage *pListButton=SystemData::getMenuItemImageByPlist("forging_protect");
	pListButton->setPosition(SystemData::getLayoutPoint("CBHC_Listbutton_pos"));
	pListButton->setTarget(this,menu_selector(WMQHpanel::menuCallBack));
	pListButton->setTag(TAG_LIST);
	m_pTopList->addChild(pListButton);
	pList->setPosition(ccp(pListButton->getPositionX()+75,pListButton->getPositionY()));
	addChild(pList);

	m_pCurrentItem=SystemData::getLabelTTF("ZBQH_WMQH_text3");
	m_pCurrentItem->setPosition(ccp(pListButton->getPositionX()-20,pListButton->getPositionY()));
	m_pCurrentItem->setFontSize(16);
	m_pCurrentItem->setColor(ccYELLOW);
	addChild(m_pCurrentItem);

	//装备强化4个框
	CCSprite *pButton1n=SystemData::getSpriteByPlist("forging_base");
	CCSprite *pButton2n=SystemData::getSpriteByPlist("forging_base");
	pButton1n->setPosition(SystemData::getLayoutPoint("ZBQH_WMQH_button1_pos"));
	pButton2n->setPosition(SystemData::getLayoutPoint("ZBQH_WMQH_button2_pos"));
	addChild(pButton1n);
	addChild(pButton2n);

	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("ZBQH_WMQH_text1");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setAnchorPoint(ccp(1,0.5));
	pSJWPK->setPosition(ccp(pButton1n->getPositionX()-50,pButton1n->getPositionY()));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("ZBQH_WMQH_text2");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setAnchorPoint(ccp(1,0.5));
	pSJCLK->setPosition(ccp(pButton2n->getPositionX()-50,pButton2n->getPositionY()));
	addChild(pSJWPK);
	addChild(pSJCLK);

	//材料框
	CCSprite *pButton4=SystemData::getSpriteByPlist("forging_base");//物品框
	pButton4->setPosition(SystemData::getLayoutPoint("ZBQH_WMQH_button3_pos"));
	CCLabelTTF* pBHCL=SystemData::getLabelTTF("ZBQH_SJCL");
	pBHCL->setColor(ccc3(3,223,204));
	pBHCL->setFontSize(18);
	pBHCL->setPosition(ccp(pButton4->getPositionX(),pButton4->getPositionY()-50));
	addChild(pButton4);
	addChild(pBHCL);


	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	m_pReqMenu=GeneralMenu::create();
	m_pReqMenu->setPosition(CCPointZero);
	addChild(m_pReqMenu);

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(WMQHpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("ZBSJ_button3_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("ZBQH_upLevel");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);


	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBSJ_XYJB");//需要金币
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("ZBQH_label1_pos"));
	m_pMoney=SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);	
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));

	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("ZBQH_label2_pos"));
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+75,m_pYuanBao->getPositionY()));


	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);
	pTHYB->setPosition(SystemData::getLayoutPoint("ZBQH_label5_pos"));


	CPCheckBox* plock1=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock1->setTag(TAG_LOCK);
	plock1->setHandler(this,menu_selector(WMQHpanel::menuCallBack));
	plock1->setPosition(SystemData::getLayoutPoint("ZBQH_label5_pos"));
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

	addReqItem(m_icurReqItem);
	return true;
}

void WMQHpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		//addItem(m_pUserItem);
		addReqItem(m_icurReqItem);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		//CCSprite* p=CommonFunction::getEffect(0);
		p->setPosition(SystemData::getLayoutPoint("ZBQH_WMQH_button1_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::qianghuashibai);	
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("ZBQH_WMQH_button1_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::qianghua);	
	}
}

void WMQHpanel::addItem( UserItem* pUserItem )
{
	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		return;
	}
	m_pUserItem=pUserItem;
	CCMenuItemImage* icon=CommonFunction::getItemIcon(pUserItem,false);	
	icon->setPosition(SystemData::getLayoutPoint("ZBQH_WMQH_button1_pos"));	
	icon->setTarget(this,menu_selector(WMQHpanel::ItemCallBack));
	m_pMenu->addChild(icon);

	if (m_pUserItem->data[ItemEquip::Item_EnhanceLevel]>=15)
	{
		return ; 
	}
	
	CCMenuItemImage* EnhanceAft=CommonFunction::getTgtPerfectEnhanceItem(pUserItem,m_iCurBHFType);
	EnhanceAft->setPosition(SystemData::getLayoutPoint("ZBQH_WMQH_button2_pos"));
	EnhanceAft->setTarget(this,menu_selector(WMQHpanel::ItemCallBack));
	m_pMenu->addChild(EnhanceAft);
	

	int vcoin=CommonFunction::getReqVcoin(m_pUserItem,TAG_PerfectQH,m_iCurBHFType);
	if (vcoin==-1)
	{
		m_pYuanBaoMoney->setString("?");
		m_pYuanBaoMoney->setColor(ccRED);
	}
	else
	{
		m_pYuanBaoMoney->setString(SystemData::intToString(vcoin).c_str());
		if (HeroData::getProp(Entity::attr_gold)<vcoin)
		{
			m_pYuanBaoMoney->setColor(ccRED);
		}
		else
		{
			m_pYuanBaoMoney->setColor(ccWHITE);
		}
	}
}

void WMQHpanel::removeItem()
{
	m_pMenu->removeAllChildren();
	m_pUserItem=NULL;
	m_pMoney->setString("");
	m_pYuanBaoMoney->setString("");
}

void WMQHpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void WMQHpanel::menuCallBack( CCObject *pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int rvt=0;
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_UPGRADE:
			if (m_pUserItem )
			{
				if (m_pUserItem->data[ItemEquip::Item_EnhanceLevel]>14)
				{
					CPEventHelper::uiNotify("","",Error::Item_MaxLvl);	
					return;
				}				
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::NotEquip);	
				return ;
			}
			if (m_iCurBHFType==0)
			{
				CPEventHelper::uiNotify("","",Error::NotEnoughReq);
				return;
			}
			if ( m_pUserItem->data[ItemEquip::Item_EnhanceLevel]>=m_iCurBHFType)
			{
				CPEventHelper::uiNotify("","",Error::Item_CantDoIt);
				return;
			}
			rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_PerfectQH,m_bLock,m_iCurBHFType,0,0);

			if (rvt==Error::Success)
			{
				CommonFunction::sendmsgPerfectEnhance(m_pUserItem->iid,m_iCurBHFType,m_bLock);
			}
			else
			{
				CPEventHelper::uiNotify("","",rvt);	
			}			
			break;
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
			break;				
		}		
		if (tag==TAG_LIST)
		{
			HCListpanel* pPanel=HCListpanel::create(TAG_PerfectEnhance);
			pPanel->setTag(TAG_LISTPANEL);
			addChild(pPanel);
		}
	}
}

void WMQHpanel::addReqItem( UserItem* pUserItem )
{
	m_icurReqItem = pUserItem->sid;
	m_pReqMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		m_iCurBHFType=0;
		m_pCurrentItem->setString(SystemData::getLayoutString("ZBQH_WMQH_text3").c_str());
		return;
	}

	//加载相对应的item（材料，保护符，效果图）
	CCMenuItemImage* req =CommonFunction::getReqPerfectEhanceItem(pUserItem);
	req->setPosition(SystemData::getLayoutPoint("ZBQH_WMQH_button3_pos"));
	req->setTarget(this,menu_selector(WMQHpanel::ItemCallBack));
	m_pReqMenu->addChild(req);

	switch (pUserItem->sid)
	{
	case 40125:
		m_iCurBHFType=5;
		break;
	case 40126:
		m_iCurBHFType=8;
		break;
	case 40127:
		m_iCurBHFType=10;
		break;
	default:
		break;
	}

	m_pCurrentItem->setString(pUserItem->name.c_str());
	addItem(m_pUserItem);
}

void WMQHpanel::addReqItem( int sid )
{
	addReqItem(CommonFunction::createNewItem(sid));
}

bool WMQHpanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void WMQHpanel::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void WMQHpanel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (getChildByTag(TAG_LISTPANEL))
	{
		removeChildByTag(TAG_LISTPANEL);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------//

PTQHpanel::PTQHpanel( void ):
	m_iIsProtect(0),
	m_iEnhanceType(0),
	m_pUserItem(NULL),
	m_pMoney(NULL),
	m_bLock1(false),
	m_bLock2(false),
	m_pYuanBao(NULL),
	m_pYuanBaoMoney(NULL),
	m_pBaoHuFu(NULL),
	m_pBaoHuFuCount(NULL),
	m_pBaoHuIcon(NULL),
	m_pProbability(NULL),
	m_pTopList(NULL)
{

}

PTQHpanel::~PTQHpanel( void )
{

}

PTQHpanel* PTQHpanel::create()
{
	PTQHpanel* pPanel = new PTQHpanel();
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

bool PTQHpanel::init( const char* filename )
{
	//装备强化4个框
	CCSprite *pButton1n=SystemData::getSpriteByPlist("forging_base");
	CCSprite *pButton2n=SystemData::getSpriteByPlist("forging_base");
	pButton1n->setPosition(SystemData::getLayoutPoint("ZBSJ_button1_pos"));
	pButton2n->setPosition(SystemData::getLayoutPoint("ZBSJ_button2_pos"));
	addChild(pButton1n);
	addChild(pButton2n);

	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("ZBQH_QFRXYSJDZB");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1n->getPositionX(),pButton1n->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("ZBQH_SJCL");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2n->getPositionX(),pButton2n->getPositionY()+50));
	addChild(pSJWPK);
	addChild(pSJCLK);

	CCSprite *pButton4=SystemData::getSpriteByPlist("forging_result");//升级物品框
	pButton4->setPosition(SystemData::getLayoutPoint("ZBQH_BHborder_pos"));
	CCLabelTTF* pBHCL=SystemData::getLabelTTF("ZBQH_BHCL");
	pBHCL->setColor(ccc3(3,223,204));
	pBHCL->setFontSize(18);
	pBHCL->setPosition(ccp(pButton4->getPositionX(),pButton4->getPositionY()+50));
	addChild(pButton4);
	addChild(pBHCL);

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBSJ_smallborder_size.w"),SystemData::getLayoutValue("ZBSJ_smallborder_size.h"));
	pBorder->setPosition(SystemData::getLayoutPoint("ZBSJ_smallborder_pos"));
	m_pTopList->addChild(pBorder);
	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("ZBQH_SJXGYL");
	pSJXGYL->setPosition(ccp(pBorder->getPositionX(),pBorder->getPositionY()+35));
	pSJXGYL->setFontSize(18);
	pSJXGYL->setColor(ccWHITE);
	m_pTopList->addChild(pSJXGYL);
	CCSprite *pButton3=SystemData::getSpriteByPlist("forging_result");
	pButton3->setPosition(SystemData::getLayoutPoint("ZBSJ_button4_pos"));
	m_pTopList->addChild(pButton3);

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(PTQHpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("ZBSJ_button3_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("ZBQH_upLevel");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);

	CCLabelTTF *pCGL=SystemData::getLabelTTF("ZBQH_CGL");//成功率
	pCGL->setFontSize(12);	
	pCGL->setColor(ccYELLOW);
	pCGL->setPosition(SystemData::getLayoutPoint("ZBQH_label4_pos"));
	m_pProbability=SystemData::getLabelTTF("XXXXX");
	m_pProbability->setFontSize(14);	
	m_pProbability->setColor(ccYELLOW);
	m_pProbability->setPosition(ccp(pCGL->getPositionX()+50,pCGL->getPositionY()));

	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBSJ_XYJB");//需要金币
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("ZBQH_label1_pos"));
	m_pMoney=SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);	
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));

	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("ZBQH_label2_pos"));
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+75,m_pYuanBao->getPositionY()));

	m_pBaoHuFu=SystemData::getLabelTTF("ZBQH_XYBHF");//需要金币
	m_pBaoHuFu->setFontSize(12);	
	m_pBaoHuFu->setColor(ccYELLOW);
	m_pBaoHuFu->setPosition(SystemData::getLayoutPoint("ZBQH_label3_pos"));
	m_pBaoHuFuCount=SystemData::getLabelTTF("XXXXX");
	m_pBaoHuFuCount->setFontSize(14);	
	m_pBaoHuFuCount->setColor(ccYELLOW);
	m_pBaoHuFuCount->setPosition(ccp(m_pBaoHuFu->getPositionX()+70,m_pBaoHuFu->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);
	CPCheckBox* plock1=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock1->setTag(TAG_LOCK1);
	plock1->setHandler(this,menu_selector(PTQHpanel::menuCallBack));
	plock1->setPosition(SystemData::getLayoutPoint("ZBQH_label5_pos"));
	m_pTopList->addChild(plock1);

	CCLabelTTF *pSYQHFW=SystemData::getLabelTTF("ZBQH_SYQHBHF");//换元宝
	pSYQHFW->setFontSize(12);	 
	pSYQHFW->setColor(ccYELLOW);
	CPCheckBox* plock2=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pSYQHFW);;
	plock2->setTag(TAG_LOCK2);
	plock2->setAnchorPoint(CCPointZero);
	plock2->setHandler(this,menu_selector(PTQHpanel::menuCallBack));
	plock2->setPosition(ccp(SystemData::getLayoutPoint("ZBQH_label5_pos").x-plock1->getContentSize().width/2,SystemData::getLayoutPoint("ZBQH_label5_pos").y+plock1->getContentSize().height/2-2));
	m_pTopList->addChild(plock2);

	pCGL->setAnchorPoint(CCPointZero);
	m_pProbability->setAnchorPoint(CCPointZero);
	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	//pSYQHFW->setAnchorPoint(CCPointZero);
	//pTHYB->setAnchorPoint(CCPointZero);
	m_pBaoHuFu->setAnchorPoint(CCPointZero);
	m_pBaoHuFuCount->setAnchorPoint(CCPointZero);

	addChild(pCGL);
	addChild(m_pProbability);
	//addChild(pTHYB);
	addChild(m_pYuanBao);
	addChild(m_pMoney);
	addChild(m_pYuanBaoMoney);
	addChild(pXYJB);
	//addChild(pSYQHFW);
	addChild(m_pBaoHuFu);
	addChild(m_pBaoHuFuCount);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);
	m_pBaoHuFu->setVisible(false);
	m_pBaoHuFuCount->setVisible(false);

	return true;
}

void PTQHpanel::menuCallBack( CCObject *pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int rvt=0;
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_UPGRADE:
			if (m_pUserItem)
			{
				if (m_pUserItem->data[ItemEquip::Item_EnhanceLevel]>=10)
				{
					CPEventHelper::uiNotify("","",Error::Item_MaxLvl);	
					return;
				}				
			}
			rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_Ehance,m_bLock1,m_iIsProtect,0,0);
			if (rvt==Error::Success)
			{
				if (m_bLock1)
				{
					CommonFunction::sendmsgEnhance(m_pUserItem->iid, m_iEnhanceType, m_iIsProtect,1);
				}
				else
				{
					CommonFunction::sendmsgEnhance(m_pUserItem->iid, m_iEnhanceType, m_iIsProtect);
				}
			}
			else
			{
				CPEventHelper::uiNotify("","",rvt);	
			}			
			break;
		case TAG_LOCK1:
			if (m_bLock1)
			{
				m_bLock1=false;
				m_pYuanBao->setVisible(false);
				m_pYuanBaoMoney->setVisible(false);
			}
			else
			{
				m_bLock1=true;
				m_pYuanBao->setVisible(true);
				m_pYuanBaoMoney->setVisible(true);
			}
			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pUserItem,TAG_Ehance,m_iIsProtect)).c_str());
			break;
		case TAG_LOCK2:                                        //保护符勾选
			if (m_pUserItem==NULL)
			{
				CPEventHelper::uiNotify("","",Error::NotEquip);
				return;
			}
			if (m_bLock2)
			{
// 				if (getChildByTag(tag+100))
// 				{
// 					removeChildByTag(tag+100);
// 				}
				m_bLock2=false;
				m_pBaoHuFu->setVisible(false);
				m_pBaoHuFuCount->setVisible(false);
				if (m_pMenu->getChildByTag(TAG_BHF))
				{
					m_pMenu->removeChildByTag(TAG_BHF);
				}
				m_iIsProtect=0;

			}
			else
			{
				m_bLock2=true;
				m_pBaoHuFu->setVisible(true);
				m_pBaoHuFuCount->setVisible(true);

				if (!m_pMenu->getChildByTag(TAG_BHF))
				{
					CCMenuItemImage* pBHIcon=getBaoHuIcon();
					pBHIcon->setTag(TAG_BHF);
					pBHIcon->setTarget(this,menu_selector(PTQHpanel::ItemCallBack));
					pBHIcon->setPosition(SystemData::getLayoutPoint("ZBQH_BHborder_pos"));
					m_pMenu->addChild(pBHIcon);	
				}				
				m_iIsProtect=1;
			}

			if (m_pUserItem )
			{
				int propbability=0;
				LuaData::getProp("gdEquipEnhance",m_pUserItem->data[ItemEquip::Item_EnhanceLevel],"successRate",propbability);
				if (propbability==0 || m_iIsProtect==1)
				{
					propbability=100;
				}
				CCString* p=CCString::createWithFormat("%d %%",propbability);
				m_pProbability->setString(p->getCString());
			}
			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pUserItem,TAG_Ehance,m_iIsProtect)).c_str());
			break;
		}		
	}
}

void PTQHpanel::addItem(UserItem* pUserItem)
{
	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		return;
	}
	m_pUserItem=pUserItem;
	CCMenuItemImage* icon=CommonFunction::getItemIcon(pUserItem,false);	
	icon->setPosition(SystemData::getLayoutPoint("ZBSJ_button1_pos"));	
	icon->setTarget(this,menu_selector(PTQHpanel::ItemCallBack));
	m_pMenu->addChild(icon);

	if (m_pUserItem->data[ItemEquip::Item_EnhanceLevel]>=15)
	{
		return ;
	}

	//加载相对应的item（材料，保护符，效果图）
	CCMenuItemImage* req =CommonFunction::getReqEnhanceItem(pUserItem);
	req->setPosition(SystemData::getLayoutPoint("ZBSJ_button2_pos"));
	req->setTarget(this,menu_selector(PTQHpanel::ItemCallBack));
	m_pMenu->addChild(req);

	CCMenuItemImage* EnhanceAft=CommonFunction::getTgtEnhanceItem(pUserItem);
	EnhanceAft->setTarget(this,menu_selector(PTQHpanel::ItemCallBack));
	m_pMenu->addChild(EnhanceAft);

	//------------------------几率---------------------//
	if (m_pProbability )
	{
		int propbability=0;
		LuaData::getProp("gdEquipEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"successRate",propbability);
		if (propbability==0 || m_iIsProtect==1)
		{
			propbability=100;
		}
		CCString* p=CCString::createWithFormat("%d %%",propbability);
		m_pProbability->setString(p->getCString());
	}

	if (m_pMoney)
	{
		int money;
		LuaData::getProp("gdEquipEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqGold",money);
		CCString* p=CCString::createWithFormat("%d",money);
		m_pMoney->setString(p->getCString());
		if (HeroData::getProp(Entity::attr_money)<money)
		{
			m_pMoney->setColor(ccRED);
		}
		else
		{
			m_pMoney->setColor(ccWHITE);
		}

		int protectcount=0;
		LuaData::getProp("gdEquipEnhance",m_pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqProtect",protectcount);
		m_pBaoHuFuCount->setString(SystemData::intToString(protectcount).c_str());


		int vcoin=CommonFunction::getReqVcoin(pUserItem,TAG_Ehance,m_iIsProtect);
		if (vcoin==-1)
		{
			m_pYuanBaoMoney->setString("?");
			m_pYuanBaoMoney->setColor(ccRED);
		}
		else
		{
			m_pYuanBaoMoney->setString(SystemData::intToString(vcoin).c_str());
			if (HeroData::getProp(Entity::attr_gold)<vcoin)
			{
				m_pYuanBaoMoney->setColor(ccRED);
			}
			else
			{
				m_pYuanBaoMoney->setColor(ccWHITE);
			}
		}
	}

	if (m_bLock2)
	{
		CCMenuItemImage* pBHIcon=getBaoHuIcon();
		pBHIcon->setTag(TAG_BHF);
		pBHIcon->setTarget(this,menu_selector(PTQHpanel::ItemCallBack));
		pBHIcon->setPosition(SystemData::getLayoutPoint("ZBQH_BHborder_pos"));
		m_pMenu->addChild(pBHIcon);
	}
}

void PTQHpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		//addItem(m_pUserItem);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("ZBSJ_button1_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::qianghuashibai);	
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("ZBSJ_button1_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::qianghua);	
	}
}

void PTQHpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void PTQHpanel::removeItem()
{
	m_pMenu->removeAllChildren();
	m_pUserItem=NULL;
	m_pMoney->setString("");
	m_pYuanBaoMoney->setString("");
	m_pBaoHuFuCount->setString("");
	m_pProbability->setString("");
}

CCMenuItemImage* PTQHpanel::getBaoHuIcon()
{
	int reqid=40012;
	int reqcnt=0;
	if (m_pUserItem==NULL)
	{
		return NULL;
	}
	LuaData::getProp("gdEquipEnhance",m_pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqProtect",reqcnt);
	CCMenuItemImage* reqItem = CCMenuItemImage::create();
	reqItem->setNormalImage(LayoutData::getItemIcon(reqid));
	reqItem->setSelectedImage(LayoutData::getItemIcon(reqid));

	int count=0;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->sid==reqid)
		{
			count+=pItem->count;
		}
	}
	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
		reqItem->setColor(ccGRAY);
	}
	else
	{
		pLable->setColor(ccGREEN);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);

	UserItem* pItem=CommonFunction::createNewItem(reqid);
	reqItem->setUserData(pItem);

	return reqItem;
}

//---------------------------------------------------------------------------------------------------------------------//


QHDMpanel::QHDMpanel( void ):
	m_iEnhanceType(0),
	m_pUserItem(NULL),
	m_pMoney(NULL),
	m_bLock(false),
	m_pYuanBao(NULL),
	m_pYuanBaoMoney(NULL),
	m_pTopList(NULL),
	m_pProgress(NULL),
	m_pProLabel(NULL),
	m_iCurNum(0),
	m_iMaxNum(0)
{

}

QHDMpanel::~QHDMpanel( void )
{

}

QHDMpanel* QHDMpanel::create()
{
	QHDMpanel* pPanel = new QHDMpanel();
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
// 在QHDMpanel.cpp文件中添加updateTimer方法的实现
void QHDMpanel::updateTimer(float dt)
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


bool QHDMpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	// 添加：初始化冷却时间
	m_iTimeSpan = 0;
	
	// 添加：启动冷却时间更新计时器
	this->schedule(schedule_selector(QHDMpanel::updateTimer), 1.0f);
	
	//装备强化4个框
	CCSprite *pButton1n=SystemData::getSpriteByPlist("forging_base");
	CCSprite *pButton2n=SystemData::getSpriteByPlist("forging_base");
	pButton1n->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_button1_pos"));
	pButton2n->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_button2_pos"));
	addChild(pButton1n);
	addChild(pButton2n);

	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("ZBQH_QFRXYSJDZB");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1n->getPositionX(),pButton1n->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("ZBQH_SJCL");
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
	pBorder->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_smallborder_pos"));
	m_pTopList->addChild(pBorder);
	CCSprite *pButton3=SystemData::getSpriteByPlist("forging_result");
	pButton3->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_btn_pos"));
	m_pTopList->addChild(pButton3);
	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("ZBQH_SJXGYL");
	pSJXGYL->setAnchorPoint(CCPointZero);
	pSJXGYL->setPosition(ccp(pButton3->getPositionX()+pButton3->getContentSize().width,pButton3->getPositionY()));
	pSJXGYL->setFontSize(18);
	pSJXGYL->setColor(ccWHITE);
	m_pTopList->addChild(pSJXGYL);

	//打磨条
	CCScale9Sprite* pProgressBkg=SystemData::getScale9SpriteByPlist("ZBQH_QHDM_jindutiao_bkg",SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.w"),SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.h"));
	pProgressBkg->setAnchorPoint(CCPointZero);
	pProgressBkg->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_jindutiao_bkg"));
	m_pTopList->addChild(pProgressBkg);
	m_pProgress=SystemData::getScale9SpriteByPlist("ZBQH_QHDM_jindutiao",SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.w"),SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.h"));
	m_pProgress->setAnchorPoint(CCPointZero);
	m_pProgress->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_jindutiao_bkg"));
	m_pProgress->setScaleX(0);
	m_pTopList->addChild(m_pProgress);

	initLabelNum();

	CCLabelTTF* pDMDS=SystemData::getLabelTTF("ZBQH_QHDM_text");
	pDMDS->setAnchorPoint(CCPointZero);
	pDMDS->setPosition(ccp(pProgressBkg->getPositionX()+pProgressBkg->getContentSize().width+5,pProgressBkg->getPositionY()));
	pDMDS->setFontSize(16);
	pDMDS->setColor(ccWHITE);
	m_pTopList->addChild(pDMDS);

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(QHDMpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_button3_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("ZBQH_QHDM_upLevel");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);


	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBSJ_XYJB");//需要金币
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("ZBQH_label1_pos"));
	m_pMoney=SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);	
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));

	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(ccp(SystemData::getLayoutPoint("ZBSJ_label2_pos").x,SystemData::getLayoutPoint("ZBSJ_label2_pos").y));
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+75,m_pYuanBao->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝 
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);

	CPCheckBox* plock1=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock1->setTag(TAG_LOCK1);
	plock1->setHandler(this,menu_selector(QHDMpanel::menuCallBack));
	plock1->setPosition(SystemData::getLayoutPoint("ZBQH_label5_pos"));
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


void QHDMpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		//addItem(m_pUserItem);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_button1_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::qianghuashibai);	
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_button1_pos"));
		addChild(p);

		EffectSprite* p2=EffectSprite::create(Effect::effect_zhishengyiji,1);
		p2->setPosition(ccp(m_pProgress->getPositionX()+m_pProgress->getContentSize().width/2,m_pProgress->getPositionY()));
		addChild(p2);
	}
}

void QHDMpanel::addItem( UserItem* pUserItem )
{
	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		return;
	}
	m_pUserItem=pUserItem;
	CCMenuItemImage* icon=CommonFunction::getItemIcon(pUserItem,false);	
	icon->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_button1_pos"));	
	icon->setTarget(this,menu_selector(QHDMpanel::ItemCallBack));
	m_pMenu->addChild(icon);


	if (m_pUserItem->data[ItemEquip::Item_EnhanceLevel]>=50)//20强化图材料
	{
		initLabelNum();
		return ;
	}

	//加载相对应的item（材料，保护符，效果图）
	CCMenuItemImage* req =CommonFunction::getReqEnhanceItem(pUserItem);
	req->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_button2_pos"));
	req->setTarget(this,menu_selector(QHDMpanel::ItemCallBack));
	m_pMenu->addChild(req);

	CCMenuItemImage* EnhanceAft=CommonFunction::getTgtEnhanceItem(pUserItem);
	EnhanceAft->setTarget(this,menu_selector(QHDMpanel::ItemCallBack));
	EnhanceAft->setPosition(SystemData::getLayoutPoint("ZBQH_QHDM_btn_pos"));
	m_pMenu->addChild(EnhanceAft);
		
	if (m_pMoney)
	{
		int money;
		LuaData::getProp("gdEquipEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqGold",money);
		CCString* p=CCString::createWithFormat("%d",money);
		m_pMoney->setString(p->getCString());
		if (HeroData::getProp(Entity::attr_money)<money)
		{
			m_pMoney->setColor(ccRED);
		}
		else
		{
			m_pMoney->setColor(ccWHITE);
		}

		int vcoin=CommonFunction::getReqVcoin(pUserItem,TAG_Ehance,0);
		if (vcoin==-1)
		{
			m_pYuanBaoMoney->setString("?");
			m_pYuanBaoMoney->setColor(ccRED);
		}
		else
		{
			m_pYuanBaoMoney->setString(SystemData::intToString(vcoin).c_str());
			if (HeroData::getProp(Entity::attr_gold)<vcoin)
			{
				m_pYuanBaoMoney->setColor(ccRED);
			}
			else
			{
				m_pYuanBaoMoney->setColor(ccWHITE);
			}
		}
	}
	initLabelNum();
}

void QHDMpanel::removeItem()
{
	m_pMenu->removeAllChildren();
	m_pUserItem=NULL;
	m_pMoney->setString("");
	m_pYuanBaoMoney->setString("");
	m_iCurNum=0;
	m_iMaxNum=0;
	initLabelNum();
}

void QHDMpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void QHDMpanel::menuCallBack( CCObject *pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int rvt=0;
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_UPGRADE:
			// 添加冷却时间检查
			if (m_iTimeSpan != 0)
			{
				CPEventHelper::uiNotify("", "", Error::time3sspan);
				return;
			}
			
			if (m_pUserItem)
			{
				if (m_pUserItem->data[ItemEquip::Item_EnhanceLevel]>=50)//最大装备强化次数
				{
					CPEventHelper::uiNotify("","",Error::Item_MaxLvl);	
					return;
				}				
			}
			rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_Ehance,m_bLock,0,0,0);
			if (rvt==Error::Success)
			{
				// 设置冷却时间
				m_iTimeSpan = 3;
				
				if (m_bLock)
				{
					CommonFunction::sendmsgPolish(m_pUserItem->iid, 1);
				}
				else
				{
					CommonFunction::sendmsgPolish(m_pUserItem->iid);
				}
			}
			else
			{
				CPEventHelper::uiNotify("","",rvt);	
			}			
			break;
			
		case TAG_LOCK1:
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
			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pUserItem,TAG_Ehance,0)).c_str());
			break;		
		}		
	}
}

void QHDMpanel::initLabelNum()
{
	if (m_pUserItem)
	{
		m_iCurNum=m_pUserItem->data[ItemEquip::Item_Polish];
		LuaData::getProp("gdEquipEnhance",m_pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqPoints",m_iMaxNum);
	}
	/*if (m_iCurNum!=0)
	{
		int width=SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.w")*m_iCurNum/m_iMaxNum;
		m_pProgress->setContentSize(CCSizeMake(width, SystemData::getLayoutValue("ZBQH_QHDM_jindutiao_bkg.h")));
	}*/
	if (m_pProgress && m_iMaxNum!=0)
	{
		float n=(float)m_iCurNum/(float)m_iMaxNum;
		m_pProgress->setScaleX(n);
	}

	if (m_iMaxNum==0)
	{
		m_pProgress->setScaleX(1);
		m_iCurNum=m_iMaxNum;
	}
	//CCLog("da mo jin du = %d",width);
	
	if (m_pProLabel)
	{
		CCString* pStr=CCString::createWithFormat("%d/%d",m_iCurNum,m_iMaxNum);
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

//---------------------------------------------------------------------------------------------------------------------//

CBYHpanel::CBYHpanel( void ):
	m_iEnhanceType(0),
	m_pUserItem(NULL),
	m_pMoney(NULL),
	m_pYuanBao(NULL),
	m_pYuanBaoMoney(NULL),
	m_pProbability(NULL),
	m_pTopList(NULL),
	m_bLock(false),
	pShouldBeSucceed(NULL),
	pBDCG(NULL)
{

}

CBYHpanel::~CBYHpanel( void )
{

}

CBYHpanel* CBYHpanel::create()
{
	CBYHpanel* pPanel = new CBYHpanel();
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

bool CBYHpanel::init( const char* filename )
{
	//装备强化4个框
	CCSprite *pButton1n=SystemData::getSpriteByPlist("forging_base");
	CCSprite *pButton2n=SystemData::getSpriteByPlist("forging_base");
	CCSprite *pButton3n=SystemData::getSpriteByPlist("forging_base");
	pButton1n->setPosition(SystemData::getLayoutPoint("ZBQH_CBYH_button1_pos"));
	pButton2n->setPosition(SystemData::getLayoutPoint("ZBQH_CBYH_button2_pos"));
	pButton3n->setPosition(SystemData::getLayoutPoint("ZBQH_CBYH_button3_pos"));
	addChild(pButton1n);
	addChild(pButton2n);
	addChild(pButton3n); 

	CCLabelTTF* pXYYHDCB=SystemData::getLabelTTF("ZBQH_XYYHDCB");
	pXYYHDCB->setColor(ccc3(3,223,204));
	pXYYHDCB->setFontSize(18);
	pXYYHDCB->setPosition(ccp(pButton1n->getPositionX(),pButton1n->getPositionY()+50));
	CCLabelTTF* pCL1=SystemData::getLabelTTF("ZBQH_CBYH_CL1");
	pCL1->setColor(ccc3(3,223,204));
	pCL1->setFontSize(18);
	pCL1->setPosition(ccp(pButton2n->getPositionX(),pButton2n->getPositionY()+50));
	CCLabelTTF* pCL2=SystemData::getLabelTTF("ZBQH_CBYH_CL2");
	pCL2->setColor(ccc3(3,223,204));
	pCL2->setFontSize(18);
	pCL2->setPosition(ccp(pButton3n->getPositionX(),pButton3n->getPositionY()+50));
	addChild(pXYYHDCB);
	addChild(pCL1);
	addChild(pCL2);

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBSJ_smallborder_size.w"),SystemData::getLayoutValue("ZBSJ_smallborder_size.h"));
	pBorder->setPosition(SystemData::getLayoutPoint("ZBSJ_smallborder_pos"));
	m_pTopList->addChild(pBorder);
	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("ZBQH_SJXGYL");
	pSJXGYL->setPosition(ccp(pBorder->getPositionX(),pBorder->getPositionY()+35));
	pSJXGYL->setFontSize(18);
	pSJXGYL->setColor(ccWHITE);
	m_pTopList->addChild(pSJXGYL);
	CCSprite *pButton3=SystemData::getSpriteByPlist("forging_result");
	pButton3->setPosition(SystemData::getLayoutPoint("ZBSJ_button4_pos"));
	m_pTopList->addChild(pButton3);

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(CBYHpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("ZBSJ_button3_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("ZBQH_CBYH_upLevel");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);

	CCLabelTTF *pCGL=SystemData::getLabelTTF("ZBQH_CGL");//成功率
	pCGL->setFontSize(12);	
	pCGL->setColor(ccYELLOW);
	pCGL->setPosition(SystemData::getLayoutPoint("ZBQH_label4_pos"));
	pCGL->setPositionY(pCGL->getPositionY()-15);
	m_pProbability=SystemData::getLabelTTF("XXXXX");
	m_pProbability->setFontSize(14);	
	m_pProbability->setColor(ccYELLOW);
	m_pProbability->setPosition(ccp(pCGL->getPositionX()+50,pCGL->getPositionY()));

	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBSJ_XYJB");//需要金币
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("ZBQH_label1_pos"));
	pXYJB->setPositionY(pXYJB->getPositionY()-15);
	m_pMoney=SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);	
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));


	pBDCG=SystemData::getLabelTTF("ZBSJ_BDCG");//必定成功
	pBDCG->setFontSize(12);	
	pBDCG->setColor(ccYELLOW);
	pBDCG->setPosition(SystemData::getLayoutPoint("ZBQH_label6_pos"));
	pBDCG->setPositionY(pBDCG->getPositionY()-15);	
	string sCnt = StringUtils::toString(0);
	pShouldBeSucceed=CCLabelTTF::create(sCnt.c_str(),"微软雅黑",14);	
	pShouldBeSucceed->setFontSize(14);	
	pShouldBeSucceed->setColor(ccRED);
	pShouldBeSucceed->setPosition(ccp(44,7));


	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//材料所需元宝
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("ZBQH_label2_pos"));
	m_pYuanBao->setPositionY(m_pYuanBao->getPositionY()-15);
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+75,m_pYuanBao->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);
	 
	CPCheckBox* plock1=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock1->setTag(TAG_LOCK1);
	plock1->setHandler(this,menu_selector(CBYHpanel::menuCallBack));
	plock1->setPosition(SystemData::getLayoutPoint("ZBQH_label5_pos"));
	m_pTopList->addChild(plock1);

	pCGL->setAnchorPoint(CCPointZero);
	m_pProbability->setAnchorPoint(CCPointZero);
	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	//pTHYB->setAnchorPoint(CCPointZero);

	addChild(pCGL);
	addChild(m_pProbability);
	//addChild(pTHYB);
	addChild(m_pYuanBao);
	addChild(m_pMoney);
	addChild(m_pYuanBaoMoney);
	addChild(pXYJB);
	//加载保底标签
	addChild(pBDCG);
	pBDCG->addChild(pShouldBeSucceed);

	//首次隐藏
	pBDCG->setVisible(false);
	pShouldBeSucceed->setVisible(false);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);

	return true;
}

void CBYHpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		//addItem(m_pUserItem);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("ZBSJ_button4_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::qianghuashibai);	
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("ZBSJ_button4_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::qianghua);	
	}
	Refresh();
}

void CBYHpanel::addItem( UserItem* pUserItem )
{
	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		return;
	}
	m_pUserItem=pUserItem;
	CCMenuItemImage* icon=CommonFunction::getItemIcon(pUserItem,false);	
	icon->setPosition(SystemData::getLayoutPoint("ZBQH_CBYH_button1_pos"));	
	icon->setTarget(this,menu_selector(CBYHpanel::ItemCallBack));
	m_pMenu->addChild(icon);

	if (m_pUserItem->data[ItemEquip::Item_EnhanceLevel]>=15)
	{
		return ;
	}

	//加载相对应的item（材料，保护符，效果图）
	CCMenuItemImage* req1 =CommonFunction::getReqWingEnhanceItem1(pUserItem);
	if (req1)
	{
		req1->setPosition(SystemData::getLayoutPoint("ZBQH_CBYH_button2_pos"));
		req1->setTarget(this,menu_selector(CBYHpanel::ItemCallBack));
		m_pMenu->addChild(req1);
	}

	CCMenuItemImage* req2 =CommonFunction::getReqWingEnhanceItem2(pUserItem);
	if (req2)
	{
		req2->setPosition(SystemData::getLayoutPoint("ZBQH_CBYH_button3_pos"));
		req2->setTarget(this,menu_selector(CBYHpanel::ItemCallBack));
		m_pMenu->addChild(req2);
	}

	CCMenuItemImage* EnhanceAft=CommonFunction::getTgtWingEnhanceItem(pUserItem);
	if (EnhanceAft)
	{
		EnhanceAft->setTarget(this,menu_selector(CBYHpanel::ItemCallBack));
		m_pMenu->addChild(EnhanceAft);
	}

	if (m_pProbability )
	{
		int propbability=0;
		LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"probability",propbability);		
		CCString* p=CCString::createWithFormat("%d %%",propbability);
		m_pProbability->setString(p->getCString());
	}

	if (m_pMoney)
	{
		int money;
		LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqGold",money);
		CCString* p=CCString::createWithFormat("%d",money);
		m_pMoney->setString(p->getCString());
		if (HeroData::getProp(Entity::attr_money)<money)
		{
			m_pMoney->setColor(ccRED);
		}
		else
		{
			m_pMoney->setColor(ccWHITE);
		}

		int vcoin=CommonFunction::getReqVcoin(pUserItem,TAG_Wing,0);
		if (vcoin==-1)
		{
			m_pYuanBaoMoney->setString("?");
			m_pYuanBaoMoney->setColor(ccRED);
		}
		else
		{
			m_pYuanBaoMoney->setString(SystemData::intToString(vcoin).c_str());
			if (HeroData::getProp(Entity::attr_gold)<vcoin)
			{
				m_pYuanBaoMoney->setColor(ccRED);
			}
			else
			{
				m_pYuanBaoMoney->setColor(ccWHITE);
			}
		}
	}
	pBDCG->setVisible(true);
	pShouldBeSucceed->setVisible(true);
	Refresh();
}

void CBYHpanel::Refresh()
{
	if (pShouldBeSucceed)
	{
		int nCnt1=0;
		int nCnt2=0;
		if (m_pUserItem)
		{
			if (m_pUserItem->data[ItemEquip::Item_EnhanceLevel] == 15)
			{
				pShouldBeSucceed->setVisible(false);
				pBDCG->setVisible(false);
			}
			else
			{
				LuaData::getProp("gdWingEnhance",m_pUserItem->data[ItemEquip::Item_EnhanceLevel],"shouldbesucceed",nCnt1);
				nCnt2 = m_pUserItem->data[ItemEquip::Item_EnhanceFailCount];
				string sCnt = StringUtils::toString(nCnt1 - nCnt2 + 1);	
				pShouldBeSucceed->setString(sCnt.c_str());
			}
		}
	}
}

void CBYHpanel::removeItem()
{
	m_pMenu->removeAllChildren();
	m_pUserItem=NULL;
	m_pMoney->setString("");
	m_pYuanBaoMoney->setString("");
	m_pProbability->setString("");
	//清除
	pShouldBeSucceed->setString("");
	pBDCG->setString("");
}

void CBYHpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void CBYHpanel::menuCallBack( CCObject *pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int rvt=0;
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_UPGRADE:
			if (m_pUserItem)
			{
				if (m_pUserItem->data[ItemEquip::Item_EnhanceLevel]>=15)
				{
					CPEventHelper::uiNotify("","",Error::Item_MaxLvl);	
					return;
				}				
			}
			rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_Wing,m_bLock,0,0,0);
			if (rvt==Error::Success)
			{
				if (m_bLock)
				{
					CommonFunction::sendmsgWingEnhance(m_pUserItem->iid, 1);
				}
				else
				{
					CommonFunction::sendmsgWingEnhance(m_pUserItem->iid);
				}
			}
			else
			{
				CPEventHelper::uiNotify("","",rvt);	
			}			
			break;
		case TAG_LOCK1:
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
			break;		
		}		
	}
}
