#include "ZBFMpanel.h"
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
#include "scene/panel/FloatPanel.h"
#include "scene/panel/FloatPanelType.h"


const int ZBFM_MAX_PANEL = 2;
const int MAX_FM_COUNT = 10;
ZBFMMainpanel::ZBFMMainpanel( void ):
	m_pTopList(NULL),
	m_pBottomList(NULL),
	m_iHeight(0),
	m_pTabelView(NULL),
	m_iCurSubType(0),
	m_pUserItem(NULL)
{

}

ZBFMMainpanel::~ZBFMMainpanel( void )
{

}

ZBFMMainpanel* ZBFMMainpanel::create(int tag)
{
	ZBFMMainpanel* pPanel = new ZBFMMainpanel();
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

bool ZBFMMainpanel::init( int tag )
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
		if (data3==TAG_ZBFM_FMQH || data3==TAG_ZBFM_ZBFM)
		{
			m_iCurSubType=data3;
		}
	}

	//装备升级界面背景
	CCScale9Sprite* bkgSprite = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_ZBFM_mainpanel_size.w"),SystemData::getLayoutValue("forging_ZBFM_mainpanel_size.h") + 40);
	m_nWidth = bkgSprite->getContentSize().width;
	m_nHeight = bkgSprite->getContentSize().height;
	const CCPoint &pos = SystemData::getLayoutPoint("forging_ZBFM_mainpanel_pos");
	bkgSprite->setPosition(pos.x, pos.y - 40);
	bkgSprite->setAnchorPoint(CCPointZero);
	addChild(bkgSprite);

	addCover();//保证点击事件

	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	//切换按钮
	int btnType[ZBFM_MAX_PANEL]={TAG_ZBFM_ZBFM,TAG_ZBFM_FMQH};
	std::string btnName[ZBFM_MAX_PANEL]={"forging_ZBFM_ZBFM","forging_ZBFM_FMQH"};

	for (int i = 0; i < ZBFM_MAX_PANEL; i++) 
	{
		CCMenuItemImage* pItem=SystemData::getScale9MenuItemImageByPlist("SXZY_btn_image");
		pItem->setPosition(ccp(SystemData::getLayoutPoint("forging_ZBFM_mainbtn_pos").x+95*i,SystemData::getLayoutPoint("forging_ZBFM_mainbtn_pos").y));
		pItem->setTarget(this,menu_selector(ZBFMMainpanel::menuCallBack));
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

	CCScale9Sprite* pbottombkg = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_ZBFM_bottompanel_size.w"),SystemData::getLayoutValue("forging_ZBFM_bottompanel_size.h"));
	pbottombkg->setAnchorPoint(CCPointZero);
	pbottombkg->setPosition(ccp(SystemData::getLayoutPoint("forging_ZBFM_bottompanel_pos").x,SystemData::getLayoutPoint("forging_ZBFM_bottompanel_pos").y));		
	addChild(pbottombkg);


	return true;
}


cocos2d::CCSize ZBFMMainpanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(420, m_iHeight);
}

cocos2d::extension::CCTableViewCell* ZBFMMainpanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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

		int i=25;
		if (m_iCurSubType==TAG_ZBFM_ZBFM)
		{
			i=25;
		}
		else if (m_iCurSubType==TAG_ZBFM_FMQH)
		{
			i = 26;
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

unsigned int ZBFMMainpanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}


void ZBFMMainpanel::menuCallBack( CCObject *pSender )
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


void ZBFMMainpanel::initContent()
{
	if (m_pTabelView)
	{
		m_pTabelView->removeFromParent();
		m_iHeight= 0;
		//m_pTabelView->reloadData();
	}
	m_pTabelView=CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("forging_ZBFM_bottomlabel_size").width,
		SystemData::getLayoutSize("forging_ZBFM_bottomlabel_size").height),kCCScrollViewDirectionVertical,this,NULL);
	m_pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTabelView->setAnchorPoint(CCPointZero);
	m_pTabelView->setPosition(SystemData::getLayoutPoint("forging_ZBFM_bottomlabel_pos"));
	m_pTabelView->reloadData();  
	addChild(m_pTabelView);
}

void ZBFMMainpanel::onEnter()
{
	BasePanel::onEnter();
	//this->runAction(CCSequence::create(CCDelayTime::create(0.08f),CCCallFunc::create(this,callfunc_selector(ZBFMMainpanel::initContent)),NULL));
	addSubPanel(m_iCurSubType);
}

void ZBFMMainpanel::onExit()
{
	BasePanel::onExit();
}

void ZBFMMainpanel::addItem( UserItem* pUserItem )
{
	m_pUserItem=pUserItem;	
	if (m_iCurSubType == TAG_ZBFM_ZBFM)
	{
		((ZBFMpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
	}
	else if (m_iCurSubType==TAG_ZBFM_FMQH)
	{
		if (pUserItem && pUserItem->data[ItemEquip::Item_FuMoPropID] == 0)
		{

			initTopBtn(TAG_ZBFM_ZBFM);
			((ZBFMpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
		}
		else
		{
			((FMQHpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
		}
	}
}

void ZBFMMainpanel::removeItem()
{
	if (m_iCurSubType==TAG_ZBFM_ZBFM)
	{
		((ZBFMpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
		//((ForgingMainPanel*)this->getParent())->updateBag(TYPE_JPZY);
	}
	else if (m_iCurSubType==TAG_ZBFM_FMQH)
	{
		((FMQHpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
	}
}

void ZBFMMainpanel::addSubPanel( int tag )
{
	m_pMenu->removeAllChildren();
	BasePanel* panel=NULL;
	switch (tag)
	{
	case TAG_ZBFM_ZBFM:
		panel=ZBFMpanel::create();
		break;
	case TAG_ZBFM_FMQH:
		panel=FMQHpanel::create();
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

	this->runAction(CCSequence::create(CCDelayTime::create(0.08f),CCCallFunc::create(this,callfunc_selector(ZBFMMainpanel::initContent)),NULL));
}

void ZBFMMainpanel::initTopBtn( int tag )
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

void ZBFMMainpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		addItem(m_pUserItem);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------//

ZBFMpanel::ZBFMpanel( void ):
	m_iEnhanceType(0),
	m_pUserItem(NULL),
	m_pMoney(NULL),
	m_bLock1(false),
	m_pYuanBao(NULL),
	m_pYuanBaoMoney(NULL),
	m_pTopList(NULL)
{

}

ZBFMpanel::~ZBFMpanel( void )
{

}

ZBFMpanel* ZBFMpanel::create()
{
	ZBFMpanel* pPanel = new ZBFMpanel();
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

bool ZBFMpanel::init( const char* filename )
{
	// 装备框
	CCSprite *pEquip=SystemData::getSpriteByPlist("forging_base");
	pEquip->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_equip_pos"));
	addChild(pEquip);

	// 材料框
	CCSprite *pMaterial=SystemData::getSpriteByPlist("forging_base");
	pMaterial->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_material_pos"));
	addChild(pMaterial);

	// 装备文字
	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("ZBFM_ZBFM_STR_QFRXYFMDZB");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_label_qfrxyfmdzb_pos"));
	addChild(pSJWPK);

	// 材料文字
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("ZBFM_ZBFM_STR_SXCL");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_label_sxcl_pos"));
	addChild(pSJCLK);


	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBFM_ZBFM_smallborder_size.w"),SystemData::getLayoutValue("ZBFM_ZBFM_smallborder_size.h"));
	pBorder->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_smallborder_pos"));
	m_pTopList->addChild(pBorder);
	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("ZBFM_FMQH_QHXGYL");
	pSJXGYL->setPosition(ccp(pBorder->getPositionX(),pBorder->getPositionY()+35));
	pSJXGYL->setFontSize(18);
	pSJXGYL->setColor(ccWHITE);
	m_pTopList->addChild(pSJXGYL);

	CCLabelTTF* pQHXG=SystemData::getLabelTTF("XXXX");
	pQHXG->setTag(TAG_YULAN);
	pQHXG->setPosition(ccp(pBorder->getPositionX(),pBorder->getPositionY()));
	pQHXG->setFontSize(18);
	pQHXG->setColor(ccWHITE);
	m_pTopList->addChild(pQHXG);


	// 附魔按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_FUMO);
	pUpLevel->setTarget(this,menu_selector(ZBFMpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_btn_fumo_pos"));
	m_pTopList->addChild(pUpLevel);

	// 附魔按钮文字
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("ZBFM_ZBFM_STR_FM");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);

	// 需要金币文字
	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBFM_ZBFM_XYJB");
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_label_xyjb_pos"));
	pXYJB->setAnchorPoint(CCPointZero);
	addChild(pXYJB);

	// 金币数值
	m_pMoney=SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);	
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_label_jb_pos"));
	m_pMoney->setAnchorPoint(CCPointZero);
	addChild(m_pMoney);

	// 需要元宝
	m_pYuanBao=SystemData::getLabelTTF("ZBFM_ZBFM_CLSXYB");
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_label_xyyb_pos"));
	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pYuanBao->setVisible(false);
	addChild(m_pYuanBao);

	// 元宝数值
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_label_yb_pos"));
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setVisible(false);
	addChild(m_pYuanBaoMoney);


	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBFM_ZBFM_CLSXYB");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);
	CPCheckBox* plock1=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock1->setTag(TAG_YBDT);
	plock1->setHandler(this,menu_selector(ZBFMpanel::menuCallBack));
	plock1->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_check_ybdt_pos"));
	m_pTopList->addChild(plock1);




	return true;
}

void ZBFMpanel::postFumoMsg(int i)
{
	if (i != Button_QD)
	{
		return;
	}

	CPCheckBox *pCheck = (CPCheckBox *)m_pTopList->getChildByTag(TAG_YBDT);
	bool bLock = pCheck->isChecked();
	int rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_ZHUANGBEIFUMO,bLock,0,0,0);
	if (rvt != Error::Success)
	{
		CPEventHelper::uiNotify("","",rvt);	
		return;
	}

	CommonFunction::sendmsgFuMo(m_pUserItem->iid, (int)bLock);
}

void ZBFMpanel::menuCallBack( CCObject *pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int rvt=0;
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_FUMO:
			if (!m_pUserItem)
			{
				return;
			}
			if (m_pUserItem->data[ItemEquip::Item_FuMoPropID] != 0)
			{
// 				FloatPanel* panel=FloatPanel::create(FloatPanelType::Fumo_Reset);
// 				panel->setPosition(ccp(200,150));
// 				panel->setHandler(this,floatpanel_selector(ZBFMpanel::postFumoMsg));
// 				addChild(panel);			

				StrVector vect;
				FloatPanel::show(FloatPanelType::Fumo_Reset, vect, this, floatpanel_selector(ZBFMpanel::postFumoMsg));
			}
			else
			{
				CPCheckBox *pCheck = (CPCheckBox *)m_pTopList->getChildByTag(TAG_YBDT);
				bool bLock = pCheck->isChecked();
				rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_ZHUANGBEIFUMO,bLock,0,0,0);
				if (rvt != Error::Success)
				{
					CPEventHelper::uiNotify("","",rvt);	
					break;
				}

				CommonFunction::sendmsgFuMo(m_pUserItem->iid, (int)bLock);
			}
			break;
		case TAG_YBDT:
			{
				CPCheckBox *pCheck = (CPCheckBox *)m_pTopList->getChildByTag(TAG_YBDT);
				bool bLock = pCheck->isChecked();
				if (!m_pUserItem)
				{
					CPEventHelper::uiNotify("","",Error::NotEquip);
					pCheck->setChecked(false);
					m_pYuanBao->setVisible(false);
					m_pYuanBaoMoney->setVisible(false);
					return;
				}

				m_pYuanBao->setVisible(bLock);
				m_pYuanBaoMoney->setVisible(bLock);
				int needYB = CommonFunction::getReqVcoin(m_pUserItem, TAG_ZHUANGBEIFUMO, 0);
				m_pYuanBaoMoney->setString(SystemData::intToString(needYB).c_str());
				m_pYuanBaoMoney->setColor((HeroData::getProp(Entity::attr_gold) < needYB) ? ccRED : ccWHITE);

			}
			break;
		}		
	}
}

void ZBFMpanel::addItem(UserItem* pUserItem)
{
	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		return;
	}
	m_pUserItem=pUserItem;
	CCMenuItemImage* icon=CommonFunction::getItemIcon(pUserItem,false);	
	icon->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_equip_pos"));	
	icon->setTarget(this,menu_selector(ZBFMpanel::ItemCallBack));
	m_pMenu->addChild(icon);

	if (m_pUserItem->data[ItemEquip::Item_FuMoPropID] != 0)
	{
		CCLabelTTF * pLabel = (CCLabelTTF *)m_pTopList->getChildByTag(TAG_YULAN);
		int fmAttrid=m_pUserItem->data[ItemEquip::Item_FuMoPropID];
		int fmAttrdata=m_pUserItem->data[ItemEquip::Item_FuMoPropValue];
		int fmAttrCount=m_pUserItem->data[ItemEquip::Item_FuMoEnhanceCount];
		std::string name;
		LuaData::getProp("fm_attr_type_to_name",fmAttrid,name);
		CCString* pStr=NULL;
		if (fmAttrid == 15 || fmAttrid == 16 || fmAttrid == 22)
		{
			float spdata=(float)fmAttrdata/100;
			pStr=CCString::createWithFormat("%s : + %.2f%% (%d/10)",name.c_str(), spdata, fmAttrCount);
		}
		else
		{
			pStr=CCString::createWithFormat("%s : + %d (%d/10)",name.c_str(), fmAttrdata, fmAttrCount);
		}
		pLabel->setString(pStr->getCString());
	}
	else
	{
		CCLabelTTF * pLabel = (CCLabelTTF *)m_pTopList->getChildByTag(TAG_YULAN);
		pLabel->setString("");
	}

	//加载相对应的item（材料，保护符，效果图）
	CCMenuItemImage* req =CommonFunction::getReqFMCLItem(pUserItem);
	req->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_material_pos"));
	req->setTarget(this,menu_selector(ZBFMpanel::ItemCallBack));
	m_pMenu->addChild(req);


	if (m_pMoney)
	{
		int money;
		LuaData::getProp("gdFuMo", "money",money);
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


		int vcoin=CommonFunction::getReqVcoin(pUserItem,TAG_ZHUANGBEIFUMO,0);
		if (vcoin==-1)
		{
			m_pYuanBaoMoney->setString("?");
			m_pYuanBaoMoney->setColor(ccRED);
		}
		else
		{
			m_pYuanBaoMoney->setString(SystemData::intToString(vcoin).c_str());
			m_pYuanBaoMoney->setColor((HeroData::getProp(Entity::attr_gold) < vcoin) ? ccRED : ccWHITE);
		}
	}


}

void ZBFMpanel::handleEvent( int channel )
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
		p->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_equip_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::qianghuashibai);	
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("ZBFM_ZBFM_equip_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::qianghua);	
	}
}

void ZBFMpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void ZBFMpanel::removeItem()
{
	m_pMenu->removeAllChildren();

	CPCheckBox *pYBCheck = (CPCheckBox *)m_pTopList->getChildByTag(TAG_YBDT);
	pYBCheck->setChecked(false);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);

	m_pUserItem=NULL;
	m_pMoney->setString("");
	m_pYuanBaoMoney->setString("");
}

//---------------------------------------------------------------------------------------------------------------------//


FMQHpanel::FMQHpanel( void ):
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
	m_iMaxNum(0),
	m_pCheckJPFM(NULL),
	m_pCheckYBDT(NULL)
{

}

FMQHpanel::~FMQHpanel( void )
{

}

FMQHpanel* FMQHpanel::create()
{
	FMQHpanel* pPanel = new FMQHpanel();
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

bool FMQHpanel::init( const char* filename )
{
	// 装备框
	CCSprite *pEquip=SystemData::getSpriteByPlist("forging_base");
	pEquip->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_equip_pos"));
	addChild(pEquip);

	// 材料框
	CCSprite *pMaterial=SystemData::getSpriteByPlist("forging_base");
	pMaterial->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_material_pos"));
	addChild(pMaterial);

	// 装备文字
	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("ZBFM_FMQH_STR_QFRXYQHDZB");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_label_qfrxyqhdzb_pos"));
	addChild(pSJWPK);

	// 材料文字
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("ZBFM_FMQH_STR_FMCL");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_label_fmcl_pos"));
	addChild(pSJCLK);

	// 强化显示框
	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBFM_FMQH_smallborder_size.w"),SystemData::getLayoutValue("ZBFM_FMQH_smallborder_size.h"));
	pBorder->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_smallborder_pos"));
	addChild(pBorder);

	// 极品附魔符
	CCSprite *pJPFMF=SystemData::getSpriteByPlist("forging_result");//升级物品框
	pJPFMF->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_jpfmf_pos"));
	addChild(pJPFMF);

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	// 强化效果预览文字
	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("ZBFM_FMQH_QHXGYL");
	pSJXGYL->setAnchorPoint(CCPointZero);
	pSJXGYL->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_label_qhxgyl_pos"));
	pSJXGYL->setFontSize(18);
	pSJXGYL->setColor(ccWHITE);
	m_pTopList->addChild(pSJXGYL);

	// 预览
	CCLabelTTF* pQHXG=SystemData::getLabelTTF("XXXX");
	pQHXG->setTag(TAG_YULAN);
	pQHXG->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_smallborder_pos"));
	pQHXG->setFontSize(18);
	pQHXG->setColor(ccWHITE);
	m_pTopList->addChild(pQHXG);

	// 打磨条背景框
	CCScale9Sprite* pProgressBkg=SystemData::getScale9SpriteByPlist("ZBFM_FMQH_jindutiao_bkg",SystemData::getLayoutValue("ZBFM_FMQH_jindutiao.w"),SystemData::getLayoutValue("ZBFM_FMQH_jindutiao.h"));
	pProgressBkg->setAnchorPoint(CCPointZero);
	pProgressBkg->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_jindutiao"));
	m_pTopList->addChild(pProgressBkg);

	// 打磨条
	m_pProgress=SystemData::getScale9SpriteByPlist("ZBQH_QHDM_jindutiao",SystemData::getLayoutValue("ZBFM_FMQH_jindutiao.w"),SystemData::getLayoutValue("ZBFM_FMQH_jindutiao.h"));
	m_pProgress->setAnchorPoint(CCPointZero);
	m_pProgress->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_jindutiao"));
	m_pProgress->setScaleX(0);
	m_pTopList->addChild(m_pProgress);

	CCLabelTTF* pLBLJPFMF=SystemData::getLabelTTF("ZBFM_FMQH_STR_JPFM");
	pLBLJPFMF->setColor(ccc3(3,223,204));
	pLBLJPFMF->setFontSize(18);
	pLBLJPFMF->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_label_jpfm_pos"));
	addChild(pLBLJPFMF);

	initLabelNum();

	// 附魔点数
	CCLabelTTF* pFMDS=SystemData::getLabelTTF("ZBFM_FMQH_FMDS");
	pFMDS->setAnchorPoint(CCPointZero);
	pFMDS->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_label_fmds_pos"));
	pFMDS->setFontSize(16);
	pFMDS->setColor(ccWHITE);
	m_pTopList->addChild(pFMDS);

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_FMQH);
	pUpLevel->setTarget(this,menu_selector(FMQHpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_btn_fmqh_pos"));
	m_pTopList->addChild(pUpLevel);

	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("ZBFM_FMQH_STR_FM");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);

	// 使用极品附魔符复选框
	CCLabelTTF *pSYJPFMF=SystemData::getLabelTTF("ZBFM_ZBFM_SYJPFMF");
	pSYJPFMF->setFontSize(12);	
	pSYJPFMF->setColor(ccYELLOW);
	m_pCheckJPFM = CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"), SystemData::getSpriteByPlist("ui_setting_isSelectBtn"), pSYJPFMF);
	m_pCheckJPFM->setTag(TAG_JPFM);
	m_pCheckJPFM->setHandler(this,menu_selector(FMQHpanel::menuCallBack));
	m_pCheckJPFM->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_check_jpfm_pos"));
	m_pTopList->addChild(m_pCheckJPFM);

	// 元宝代替复选框
	CCLabelTTF *pSYYB=SystemData::getLabelTTF("ZBFM_FMQH_CLBZYBDT");
	pSYYB->setFontSize(12);	 
	pSYYB->setColor(ccYELLOW);
	m_pCheckYBDT=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"), SystemData::getSpriteByPlist("ui_setting_isSelectBtn"), pSYYB);
	m_pCheckYBDT->setTag(TAG_YBDT);
	m_pCheckYBDT->setAnchorPoint(CCPointZero);
	m_pCheckYBDT->setHandler(this,menu_selector(FMQHpanel::menuCallBack));
	m_pCheckYBDT->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_check_ybdt_pos"));
	m_pTopList->addChild(m_pCheckYBDT);

	// 需要金币
	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBFM_FMQH_XYJB");
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setAnchorPoint(CCPointZero);
	pXYJB->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_label_xyjb_pos"));
	addChild(pXYJB);
	m_pMoney=SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);	
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setAnchorPoint(CCPointZero);
	m_pMoney->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_label_jb_pos"));
	addChild(m_pMoney);

	// 需要元宝
	m_pYuanBao=SystemData::getLabelTTF("ZBFM_FMQH_CLSXYB");
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_label_xyyb_pos"));
	m_pYuanBao->setVisible(false);
	addChild(m_pYuanBao);
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_label_yb_pos"));
	m_pYuanBaoMoney->setVisible(false);
	addChild(m_pYuanBaoMoney);

	// 需要极品附魔符数量
	m_pLabelXYJPFMFSL=SystemData::getLabelTTF("ZBFM_FMQH_XYJPFMFSL");
	m_pLabelXYJPFMFSL->setFontSize(12);	
	m_pLabelXYJPFMFSL->setColor(ccYELLOW);
	m_pLabelXYJPFMFSL->setAnchorPoint(CCPointZero);
	m_pLabelXYJPFMFSL->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_label_xyfmf_pos"));
	m_pLabelXYJPFMFSL->setVisible(false);
	addChild(m_pLabelXYJPFMFSL);
	m_pLabelFMFCount=SystemData::getLabelTTF("XXXXX");
	m_pLabelFMFCount->setFontSize(14);	
	m_pLabelFMFCount->setColor(ccYELLOW);
	m_pLabelFMFCount->setAnchorPoint(CCPointZero);
	m_pLabelFMFCount->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_label_fmf_pos"));
	m_pLabelFMFCount->setVisible(false);
	addChild(m_pLabelFMFCount);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	return true;
}

void FMQHpanel::handleEvent( int channel )
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
		p->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_equip_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::qianghuashibai);	
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_equip_pos"));
		addChild(p);
	}
}

void FMQHpanel::addItem( UserItem* pUserItem )
{
	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		return;
	}

	m_pUserItem=pUserItem;

	CCMenuItemImage* icon=CommonFunction::getItemIcon(m_pUserItem,false);	
	icon->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_equip_pos"));	
	icon->setTarget(this,menu_selector(FMQHpanel::ItemCallBack));
	m_pMenu->addChild(icon);

	initLabelNum();


	CCLabelTTF * pLabel = (CCLabelTTF *)m_pTopList->getChildByTag(TAG_YULAN);
	int fmAttrid=m_pUserItem->data[ItemEquip::Item_FuMoPropID];
	int fmAttrdata=m_pUserItem->data[ItemEquip::Item_FuMoPropValue];
	int fmAttrCount=m_pUserItem->data[ItemEquip::Item_FuMoEnhanceCount];
	std::string name;
	LuaData::getProp("fm_attr_type_to_name",fmAttrid,name);
	CCString* pStr=NULL;
	if (fmAttrid == 15 || fmAttrid == 16 || fmAttrid == 22)
	{
		float spdata=(float)fmAttrdata/100;
		pStr=CCString::createWithFormat("%s : + %.2f%%",name.c_str(), spdata, fmAttrCount);
	}
	else
	{
		pStr=CCString::createWithFormat("%s : + %d",name.c_str(), fmAttrdata, fmAttrCount);
	}
	pLabel->setString(pStr->getCString());


	if (m_pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] >= MAX_FM_COUNT)
	{
		return;
	}

	//加载相对应的item（材料，保护符，效果图）
	CCMenuItemImage* req =CommonFunction::getReqFMFItem(pUserItem);
	req->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_material_pos"));
	req->setTarget(this,menu_selector(FMQHpanel::ItemCallBack));
	m_pMenu->addChild(req);

	if (m_pMoney)
	{
		int money;
		LuaData::getProp("gdFuMoEnhance", pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] + 1, "money", money);
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
		CPCheckBox *pJPCheck = (CPCheckBox *)m_pTopList->getChildByTag(TAG_JPFM);
		bool bJPLock = pJPCheck->isChecked();
		int vcoin = CommonFunction::getReqVcoin(m_pUserItem, TAG_FUMOQIANGHUA, (int)bJPLock);
		if (vcoin==-1)
		{
			m_pYuanBaoMoney->setString("?");
			m_pYuanBaoMoney->setColor(ccRED);
		}
		else
		{
			m_pYuanBaoMoney->setString(SystemData::intToString(vcoin).c_str());
			m_pYuanBaoMoney->setColor((HeroData::getProp(Entity::attr_gold) < vcoin) ? ccRED : ccWHITE);
		}
	}

	if (m_pCheckJPFM->isChecked())
	{
		if (!m_pMenu->getChildByTag(TAG_FMF))
		{
			CCMenuItemImage* pBHIcon = CommonFunction::getReqJPFMFItem(m_pUserItem);
			//CCMenuItemImage* pBHIcon = getFMFIcon();
			pBHIcon->setTag(TAG_FMF);
			pBHIcon->setTarget(this,menu_selector(FMQHpanel::ItemCallBack));
			pBHIcon->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_jpfmf_pos"));
			pBHIcon->setVisible(true);
			m_pMenu->addChild(pBHIcon);	
		}				
	}

	int jpfmfcount = 0;
	LuaData::getProp("gdFuMoEnhance", m_pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] + 1, "perfectItemCount",jpfmfcount);
	m_pLabelFMFCount->setString(SystemData::intToString(jpfmfcount).c_str());

	initLabelNum();
}

void FMQHpanel::removeItem()
{
	m_pMenu->removeAllChildren();

	CPCheckBox *pJPCheck = (CPCheckBox *)m_pTopList->getChildByTag(TAG_JPFM);
	pJPCheck->setChecked(false);
	CPCheckBox *pYBCheck = (CPCheckBox *)m_pTopList->getChildByTag(TAG_YBDT);
	pYBCheck->setChecked(false);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);
	m_pLabelXYJPFMFSL->setVisible(false);
	m_pLabelFMFCount->setVisible(false);

	m_pUserItem=NULL;
	m_pMoney->setString("");
	m_pYuanBaoMoney->setString("");
	m_iCurNum=0;
	m_iMaxNum=0;
	initLabelNum();
}

void FMQHpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void FMQHpanel::menuCallBack( CCObject *pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int rvt=0;
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_FMQH:
			{
				if (!m_pUserItem)
				{
					CPEventHelper::uiNotify("","",Error::NotEquip);
					return;
				}
				CPCheckBox *pYBCheck = (CPCheckBox *)m_pTopList->getChildByTag(TAG_YBDT);
				bool bYBLock = pYBCheck->isChecked();
				CPCheckBox *pJPCheck = (CPCheckBox *)m_pTopList->getChildByTag(TAG_JPFM);
				bool bJPLock = pJPCheck->isChecked();
				rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem, TAG_FUMOQIANGHUA, (int)bJPLock, (int)bYBLock, 0, 0);
				if (rvt != Error::Success)
				{
					CPEventHelper::uiNotify("","",rvt);	
					break;
				}

				CommonFunction::sendmsgFuMoEnhance(m_pUserItem->iid, (int)bJPLock, (int)bYBLock);	
			}
			break;
		case TAG_YBDT:
			{
				CPCheckBox *pYBCheck = (CPCheckBox *)m_pTopList->getChildByTag(TAG_YBDT);
				bool bYBLock = pYBCheck->isChecked();
				CPCheckBox *pJPCheck = (CPCheckBox *)m_pTopList->getChildByTag(TAG_JPFM);
				bool bJPLock = pJPCheck->isChecked();
				if (!m_pUserItem)
				{
					CPEventHelper::uiNotify("","",Error::NotEquip);
					pYBCheck->setChecked(false);
					m_pYuanBao->setVisible(false);
					m_pYuanBaoMoney->setVisible(false);
					return;
				}
				m_pYuanBao->setVisible(bYBLock);
				m_pYuanBaoMoney->setVisible(bYBLock);
				int needYB = CommonFunction::getReqVcoin(m_pUserItem, TAG_FUMOQIANGHUA, (int)bJPLock);
				m_pYuanBaoMoney->setString(SystemData::intToString(needYB).c_str());
				m_pYuanBaoMoney->setColor((HeroData::getProp(Entity::attr_gold) < needYB) ? ccRED : ccWHITE);
			}
			break;	
		case TAG_JPFM:                                        //保护符勾选
			if (!m_pUserItem)
			{
				CPEventHelper::uiNotify("","",Error::NotEquip);
				m_pCheckJPFM->setChecked(false);
				return;
			}

			m_pLabelXYJPFMFSL->setVisible(m_pCheckJPFM->isChecked());
			m_pLabelFMFCount->setVisible(m_pCheckJPFM->isChecked());
			int jpfmfcount = 0;
			LuaData::getProp("gdFuMoEnhance", m_pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] + 1, "perfectItemCount",jpfmfcount);
			m_pLabelFMFCount->setString(SystemData::intToString(jpfmfcount).c_str());

			if (!m_pCheckJPFM->isChecked())
			{
				if (m_pMenu->getChildByTag(TAG_FMF))
				{
					m_pMenu->removeChildByTag(TAG_FMF);
				}
			}
			else
			{
				if (!m_pMenu->getChildByTag(TAG_FMF))
				{
					if (m_pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] < MAX_FM_COUNT)
					{
						CCMenuItemImage* pBHIcon = CommonFunction::getReqJPFMFItem(m_pUserItem);
						//CCMenuItemImage* pBHIcon = getFMFIcon();
						pBHIcon->setTag(TAG_FMF);
						pBHIcon->setTarget(this,menu_selector(FMQHpanel::ItemCallBack));
						pBHIcon->setPosition(SystemData::getLayoutPoint("ZBFM_FMQH_jpfmf_pos"));
						pBHIcon->setVisible(true);
						m_pMenu->addChild(pBHIcon);	
					}
				}				
			}

			int needYB = CommonFunction::getReqVcoin(m_pUserItem, TAG_FUMOQIANGHUA, int(m_pCheckJPFM->isChecked()));
			m_pYuanBaoMoney->setString(SystemData::intToString(needYB).c_str());
			m_pYuanBaoMoney->setColor((HeroData::getProp(Entity::attr_gold) < needYB) ? ccRED : ccWHITE);

			break;

		}		
	}
}

// 显示进度条及文字
void FMQHpanel::initLabelNum()
{
	if (m_pUserItem)
	{
		m_iCurNum=m_pUserItem->data[ItemEquip::Item_FuMoEnhanceCount];
	}

	m_iMaxNum = MAX_FM_COUNT;

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

	if (!m_pProLabel)
	{
		m_pProLabel=CCLabelTTF::create("","",16);
		m_pProLabel->setAnchorPoint(ccp(0.5,0));
		m_pProLabel->setPosition(ccp(m_pProgress->getPositionX() + m_pProgress->getContentSize().width/2,m_pProgress->getPositionY()));
		m_pTopList->addChild(m_pProLabel);
	}

	CCString* pStr=CCString::createWithFormat("%d/%d",m_iCurNum,m_iMaxNum);
	m_pProLabel->setString(pStr->getCString());
}

// 附魔强化图标
CCMenuItemImage* FMQHpanel::getFMFIcon()
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
