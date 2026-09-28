#include "SXZYpanel.h"
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
#include "script/LuaWrapper.h"

#include "scene/panel/functionPanel/ItemTooltip.h"
#include "userdata/luadata/LuaData.h"
#include "CommonFunction.h"
#include "ForgingMainPanel.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventHelper.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "controls/CPCheckBox.h"
#include "res/AudioLoader.h"
#include "event/CPEventDispatcher.h"



SXZYPanel::SXZYPanel( void ):
	m_iCurSubType(0),
	m_pTabelView(NULL),
	m_pTopList(NULL),
	m_pUserItem(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);

}

SXZYPanel::~SXZYPanel( void )
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);

}

SXZYPanel* SXZYPanel::create(int tag)
{
	SXZYPanel* pPanel = new SXZYPanel();
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

bool SXZYPanel::init( int tag )
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
		if (data3==TAG_QHZY ||data3==TAG_JDZY || data3==TAG_JPZY || data3==TAG_JPQX)
		{
			m_iCurSubType=data3;
		}

	}

	//装备升级界面背景
	CCScale9Sprite* bkgSprite = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_mainpanel_size.w"),SystemData::getLayoutValue("forging_mainpanel_size.h"));
	m_nWidth = bkgSprite->getContentSize().width;
	m_nHeight = bkgSprite->getContentSize().height;
	bkgSprite->setPosition(SystemData::getLayoutPoint("forging_mainpanel_pos"));
	bkgSprite->setAnchorPoint(CCPointZero);
	addChild(bkgSprite);

	addCover();//保证点击事件

	m_pMenu=GeneralMenu::create();
	m_pMenu->setAnchorPoint(CCPointZero);
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	m_pTopList=GeneralMenu::create();
	m_pTopList->setAnchorPoint(CCPointZero);
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	int btnType[4]={TAG_JPZY,TAG_QHZY,TAG_JDZY,TAG_JPQX};
	std::string btnName[4]={"SXZY_JPZY","SXZY_QHZY","SXZY_JDZY","SXZY_JPQX"};
	for (int i=0;i<4;i++) 
	{
		CCMenuItemImage* pItem=SystemData::getScale9MenuItemImageByPlist("SXZY_btn_image");
		pItem->setPosition(ccp(SystemData::getLayoutPoint("SXZY_btn_image").x+95*i,SystemData::getLayoutPoint("SXZY_btn_image").y));
		pItem->setTarget(this,menu_selector(SXZYPanel::menuCallBack));
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

	//物品说明menu

	CCScale9Sprite* pbottombkg = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_bottompanel_size.w"),SystemData::getLayoutValue("forging_bottompanel_size.h"));
	pbottombkg->setAnchorPoint(CCPointZero);
	pbottombkg->setPosition(SystemData::getLayoutPoint("forging_bottompanel_pos"));		
	addChild(pbottombkg);
	
	addSubPanel(m_iCurSubType);
	return true;
}

void SXZYPanel::menuCallBack( CCObject *pSender )
{
	CCMenuItemImage* pNode = dynamic_cast<CCMenuItemImage*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==m_iCurSubType)
		{
			return;
		}
		pNode->selected();
		if (m_pTopList->getChildByTag(m_iCurSubType))
		{
			((CCMenuItemImage*)(m_pTopList->getChildByTag(m_iCurSubType)))->unselected();
		}
		m_iCurSubType=tag;
		//改变界面 并且改变背包物品
		addSubPanel(m_iCurSubType);
		int bagtype=0;
		if (m_iCurSubType==TAG_JPZY)
		{
			bagtype=TYPE_JPZY;
		}
		else if (m_iCurSubType==TAG_JPQX)
		{
			bagtype=TYPE_JPQX;
		}
		else if (m_iCurSubType==TAG_QHZY)
		{
			bagtype=TYPE_QHZY;
		}
		else if (m_iCurSubType==TAG_JDZY)
		{
			bagtype=TYPE_JDZY;
		}
		((ForgingMainPanel*)(this->getParent()))->updateBag(bagtype);
	}
}

cocos2d::CCSize SXZYPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(420, m_iHeight);
}

cocos2d::extension::CCTableViewCell* SXZYPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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

		int id=0;
		switch (m_iCurSubType)
		{
		case TAG_JPZY:
			id=5;
			break;
		case TAG_JDZY:
			id=7;
			break;
		case TAG_QHZY:
			id=6;
			break;
		case TAG_JPQX:
			id=8;
			break;
		default:
			id=5;
			break;
		}

		std::string content;
		LuaData::getProp("gddescription",id,"content",content);
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

unsigned int SXZYPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void SXZYPanel::addItem( UserItem* pUserItem )
{
	m_pUserItem = pUserItem;
	int equiptype=0;
	if (m_iCurSubType==TAG_JPZY)
	{
		((JPZYpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
		if (pUserItem)
		{
			equiptype=pUserItem->type+Type_special;
		}
		else
		{
			equiptype=TYPE_JPZY;
		}
	}
	if (m_iCurSubType==TAG_QHZY)
	{
		((QHZYpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
		if (pUserItem)
		{
			equiptype=pUserItem->type+Type_enhance;
		}
		else
		{
			equiptype=TYPE_QHZY;
		}
	}
	if (m_iCurSubType==TAG_JDZY)
	{
		((JDZYpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);
		if (pUserItem)
		{
			equiptype=pUserItem->type+Type_evaluate;
		}
		else
		{
			equiptype=TYPE_JDZY;
		}
	}
	if (m_iCurSubType==TAG_JPQX)
	{
		((JPQXpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->addItem(pUserItem);		
	}
	if (equiptype!=0)
	{
		((ForgingMainPanel*)this->getParent())->updateBag(equiptype);
	}
}


void SXZYPanel::removeItem()
{
	if (m_iCurSubType==TAG_JPZY)
	{
		((JPZYpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
		((ForgingMainPanel*)this->getParent())->updateBag(TYPE_JPZY);
	}
	else if (m_iCurSubType==TAG_QHZY)
	{
		((QHZYpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
		((ForgingMainPanel*)this->getParent())->updateBag(TYPE_QHZY);
	}
	else if (m_iCurSubType==TAG_JDZY)
	{
		((JDZYpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
		((ForgingMainPanel*)this->getParent())->updateBag(TYPE_JDZY);
	}
	else if (m_iCurSubType==TAG_JPQX)
	{
		((JPQXpanel*)(m_pMenu->getChildByTag(m_iCurSubType)))->removeItem();
		((ForgingMainPanel*)this->getParent())->updateBag(TYPE_JPQX);
	}
}

void SXZYPanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void SXZYPanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//addItem(m_pUserItem);
		//this->runAction(CCSequence::create(CCDelayTime::create(0.08f),CCCallFunc::create(this,callfunc_selector(SXZYPanel::initContent)),NULL));
	}
}

void SXZYPanel::initContent()
{
	if (m_pTabelView)
	{
		m_pTabelView->reloadData();
	}
	else
	{
		m_pTabelView=CCTableViewEx::create(this,SystemData::getLayoutSize("forging_bottommenu_size"),kCCScrollViewDirectionVertical,this,NULL);
		m_pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
		m_pTabelView->setAnchorPoint(CCPointZero);
		m_pTabelView->setPosition(SystemData::getLayoutPoint("forging_bottommenu_pos"));
		m_pTabelView->reloadData();  
		addChild(m_pTabelView);
	}
}

void SXZYPanel::addSubPanel( int tag )
{
	m_pMenu->removeAllChildren();
	BasePanel* panel=NULL;
	switch (tag)
	{
	case TAG_JPZY:
		panel=JPZYpanel::create();
		break;
	case TAG_QHZY:
		panel=QHZYpanel::create();
		break;
	case TAG_JDZY:
		panel=JDZYpanel::create();
		break;
	case TAG_JPQX:
		panel=JPQXpanel::create();
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

	this->runAction(CCSequence::create(CCDelayTime::create(0.08f),CCCallFunc::create(this,callfunc_selector(SXZYPanel::initContent)),NULL));
}

void SXZYPanel::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (CPEventHelper::getEventSource() == "HandlemessageItemUpdExDataNotify" || CPEventHelper::getEventSource() == "HandleMessageItemUpdData")
		{
			addItem(m_pUserItem);
		}
	}
}


//----------------------------------------------------------------------------------------------------------//


JPZYpanel::JPZYpanel( void ):
	m_pLeftUserItem(NULL),
	m_pRightUserItem(NULL),
	m_pYuanBaoMoney(NULL),
	m_pYuanBao(NULL),
	m_pMoney(NULL),
	m_bLock(false)
{

}

JPZYpanel::~JPZYpanel( void )
{

}

JPZYpanel* JPZYpanel::create()
{
	JPZYpanel* pPanel = new JPZYpanel();
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

bool JPZYpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBSJ_smallborder_size.w")+20,SystemData::getLayoutValue("ZBSJ_smallborder_size.h")-10);
	pBorder->setPosition(ccp(SystemData::getLayoutPoint("JPZY_button3_pos").x,SystemData::getLayoutPoint("JPZY_button3_pos").y+15));
	addChild(pBorder); 

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);


	//装备升级3个框
	CCSprite *pButton1=SystemData::getSpriteByPlist("forging_base");//升级物品框
	pButton1->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
	CCSprite *pButton2=SystemData::getSpriteByPlist("forging_base");//升级材料框
	pButton2->setPosition(SystemData::getLayoutPoint("JPZY_right_pos"));
	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("JPZY_MBZB");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1->getPositionX(),pButton1->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("JPZY_CLZB");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2->getPositionX(),pButton2->getPositionY()+50));
	addChild(pSJWPK);
	addChild(pSJCLK);
	addChild(pButton1);
	addChild(pButton2);


	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("JPZY_CLZBZZYHHXS");
	pSJXGYL->setPosition(SystemData::getLayoutPoint("JPZY_title_pos"));
	pSJXGYL->setFontSize(16);
	pSJXGYL->setColor(ccYELLOW);
	m_pTopList->addChild(pSJXGYL);


	CCSprite *pButton3=SystemData::getSpriteByPlist("forging_base");
	pButton3->setPosition(SystemData::getLayoutPoint("JPZY_button3_pos"));
	m_pTopList->addChild(pButton3);


	CCSprite *pButton4=SystemData::getSpriteByPlist("forging_base");//升级物品框
	pButton4->setPosition(ccp(SystemData::getLayoutPoint("JPZY_button1_pos").x,SystemData::getLayoutPoint("JPZY_button1_pos").y+6));
	m_pTopList->addChild(pButton4);
	CCLabelTTF* pZYCL=SystemData::getLabelTTF("JPZY_ZYCL");
	pZYCL->setPosition(ccp(pButton4->getPositionX(),pButton4->getPositionY()+50));
	pZYCL->setColor(ccc3(3,223,204));
	pZYCL->setFontSize(18);
	m_pTopList->addChild(pZYCL);

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(JPZYpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("JPZY_center_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("JPZY_ZY");
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

	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("ZBSJ_label2_pos"));
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+m_pYuanBao->getContentSize().width+5,m_pYuanBao->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);


	CPCheckBox* plock=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock->setTag(TAG_LOCK);
	plock->setHandler(this,menu_selector(JPZYpanel::menuCallBack));
	plock->setPosition(SystemData::getLayoutPoint("ZBSJ_label3_pos"));
	m_pTopList->addChild(plock);


	//pTHYB->setAnchorPoint(CCPointZero);
	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	//m_pTopList->addChild(pTHYB);
	m_pTopList->addChild(m_pYuanBao);
	m_pTopList->addChild(m_pMoney);
	m_pTopList->addChild(m_pYuanBaoMoney);
	m_pTopList->addChild(pXYJB);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);

	//物品说明menu
	m_pBottomList=GeneralMenu::create();
	m_pBottomList->setPosition(CCPointZero);
	addChild(m_pBottomList);	


	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);	

	return true;
}

void JPZYpanel::menuCallBack( CCObject *pSender )
{
	CCLOG("JPZYpanel Press");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_UPGRADE:
			if (m_pLeftUserItem && m_pRightUserItem)
			{
				int rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pRightUserItem,TAG_MoveAttr,m_bLock,0,0,0);
				if (rvt==Error::Success)
				{
					if (m_bLock)
					{
						CommonFunction::sendmsgChangeSpecialAttr(m_pLeftUserItem->iid,m_pRightUserItem->iid,1);
					}
					else
					{
						CommonFunction::sendmsgChangeSpecialAttr(m_pLeftUserItem->iid,m_pRightUserItem->iid);
					}
				}
				else
				{
					CPEventHelper::uiNotify("","",rvt);
				}
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::NotEquip);
			}
			AudioLoader::play(Sound::Effect::jipinzhuanyi);
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
			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pLeftUserItem,TAG_MoveAttr,0)).c_str());
			break;
		default:
			break;
		}

	}
}

void JPZYpanel::addItem( UserItem* pUserItem )
{
	if (pUserItem==NULL)
	{
		removeItem();
		return;
	}
	if (m_pLeftUserItem)
	{
		if (m_pLeftUserItem->iid==pUserItem->iid)
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
		CCMenuItemImage* pItem=CommonFunction::getItemIcon(pUserItem,false);
		pItem->setTarget(this,menu_selector(JPZYpanel::ItemCallBack));
		pItem->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
		pItem->setTag(1);
		m_pMenu->addChild(pItem);

	}
}

void JPZYpanel::addItem2( UserItem* pUserItem )
{
	if (pUserItem->type!=m_pLeftUserItem->type)
	{
		return;
	}
	if (m_pRightUserItem)
	{
		m_pMenu->removeChildByTag(2);
	}
	m_pRightUserItem=pUserItem;
	CCMenuItemImage* pItem=CommonFunction::getItemIcon(pUserItem,false);
	pItem->setTarget(this,menu_selector(JPZYpanel::ItemCallBack));
	pItem->setPosition(SystemData::getLayoutPoint("JPZY_right_pos"));
	pItem->setTag(2);
	m_pMenu->addChild(pItem);

	//重新加载目标预览
	CCMenuItemImage* ptgtItem=CommonFunction::getTgtSpecialAttrItem(m_pLeftUserItem,m_pRightUserItem);
	ptgtItem->setTarget(this,menu_selector(JPZYpanel::ItemCallBack));
	m_pMenu->addChild(ptgtItem);

	//添加极品转移符
	CCMenuItemImage* pReqItem=CommonFunction::getReqChangeAttrItem(pUserItem);
	pReqItem->setTarget(this,menu_selector(JPZYpanel::ItemCallBack));
	pReqItem->setPosition(SystemData::getLayoutPoint("JPZY_button1_pos"));
	m_pMenu->addChild(pReqItem);
}

void JPZYpanel::removeItem()
{
	m_pMenu->removeAllChildren();
	m_pRightUserItem=NULL;
	m_pLeftUserItem=NULL;
	m_pYuanBaoMoney->setString("");
	m_pMoney->setString("");
}

void JPZYpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void JPZYpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		addItem(NULL);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
		addChild(p);
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
		addChild(p);
	}
}



//-------------------------------------------------------------------------------------------------------------------------//

QHZYpanel::QHZYpanel( void ):
	m_pLeftUserItem(NULL),
	m_pRightUserItem(NULL),
	m_pYuanBaoMoney(NULL),
	m_pYuanBao(NULL),
	m_pMoney(NULL),
	m_bLock(false)
{

}

QHZYpanel::~QHZYpanel( void )
{

}

QHZYpanel* QHZYpanel::create()
{
	QHZYpanel* pPanel = new QHZYpanel();
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

bool QHZYpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBSJ_smallborder_size.w")+20,SystemData::getLayoutValue("ZBSJ_smallborder_size.h")-10);
	pBorder->setPosition(ccp(SystemData::getLayoutPoint("JPZY_button3_pos").x,SystemData::getLayoutPoint("JPZY_button3_pos").y+15));
	addChild(pBorder); 

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);


	//装备升级3个框
	CCSprite *pButton1=SystemData::getSpriteByPlist("forging_base");//升级物品框
	pButton1->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
	CCSprite *pButton2=SystemData::getSpriteByPlist("forging_base");//升级材料框
	pButton2->setPosition(SystemData::getLayoutPoint("JPZY_right_pos"));
	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("JPZY_MBZB");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1->getPositionX(),pButton1->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("JPZY_CLZB");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2->getPositionX(),pButton2->getPositionY()+50));
	addChild(pSJWPK);
	addChild(pSJCLK);
	addChild(pButton1);
	addChild(pButton2);



	CCSprite *pButton3=SystemData::getSpriteByPlist("forging_base");
	pButton3->setPosition(SystemData::getLayoutPoint("JPZY_button3_pos"));
	m_pTopList->addChild(pButton3);
	 

	CCSprite *pButton4=SystemData::getSpriteByPlist("forging_base");//升级物品框
	pButton4->setPosition(ccp(SystemData::getLayoutPoint("JPZY_button1_pos").x,SystemData::getLayoutPoint("JPZY_button1_pos").y+6));
	m_pTopList->addChild(pButton4);
	CCLabelTTF* pZYCL=SystemData::getLabelTTF("JPZY_ZYCL");
	pZYCL->setPosition(ccp(pButton4->getPositionX(),pButton4->getPositionY()+50));
	pZYCL->setColor(ccc3(3,223,204));
	pZYCL->setFontSize(18);
	m_pTopList->addChild(pZYCL);

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(QHZYpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("JPZY_center_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("JPZY_ZY");
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

	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("ZBSJ_label2_pos"));
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+m_pYuanBao->getContentSize().width+5,m_pYuanBao->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);


	CPCheckBox* plock=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock->setTag(TAG_LOCK);
	plock->setHandler(this,menu_selector(QHZYpanel::menuCallBack));
	plock->setPosition(SystemData::getLayoutPoint("ZBSJ_label3_pos"));
	m_pTopList->addChild(plock);

	//pTHYB->setAnchorPoint(CCPointZero);
	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	//m_pTopList->addChild(pTHYB);
	m_pTopList->addChild(m_pYuanBao);
	m_pTopList->addChild(m_pMoney);
	m_pTopList->addChild(m_pYuanBaoMoney);
	m_pTopList->addChild(pXYJB);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);

	//物品说明menu
	m_pBottomList=GeneralMenu::create();
	m_pBottomList->setPosition(CCPointZero);
	addChild(m_pBottomList);	


	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);	

	return true;
}

void QHZYpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		addItem(NULL);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
		addChild(p);
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
		addChild(p);
	}
}

void QHZYpanel::addItem( UserItem* pUserItem )
{
	if (pUserItem==NULL)
	{
		removeItem();
		return;
	}
	if (m_pLeftUserItem)
	{
		if (m_pLeftUserItem->iid==pUserItem->iid)
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
		CCMenuItemImage* pItem=CommonFunction::getItemIcon(pUserItem,false);
		pItem->setTarget(this,menu_selector(QHZYpanel::ItemCallBack));
		pItem->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
		pItem->setTag(1);
		m_pMenu->addChild(pItem);
	}
}

void QHZYpanel::addItem2( UserItem* pUserItem )
{
	if (pUserItem->type!=m_pLeftUserItem->type)
	{
		return;
	}
	if (m_pRightUserItem)
	{
		m_pMenu->removeChildByTag(2);
	}
	m_pRightUserItem=pUserItem;
	CCMenuItemImage* pItem=CommonFunction::getItemIcon(pUserItem,false);
	pItem->setTarget(this,menu_selector(QHZYpanel::ItemCallBack));
	pItem->setPosition(SystemData::getLayoutPoint("JPZY_right_pos"));
	pItem->setTag(2);
	m_pMenu->addChild(pItem);

	//重新加载目标预览
	CCMenuItemImage* ptgtItem=CommonFunction::getTgtEnhanceAttrItem(m_pLeftUserItem,m_pRightUserItem);
	ptgtItem->setTarget(this,menu_selector(QHZYpanel::ItemCallBack));
	m_pMenu->addChild(ptgtItem);

	//添加强化转移符
	CCMenuItemImage* pReqItem=CommonFunction::getReqEnhanceAttrItem(pUserItem);
	pReqItem->setTarget(this,menu_selector(QHZYpanel::ItemCallBack));
	pReqItem->setPosition(SystemData::getLayoutPoint("JPZY_button1_pos"));
	m_pMenu->addChild(pReqItem);


	int money=0;
	//LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqGold",money);
	m_pMoney->setString(SystemData::intToString(money).c_str());
	if (HeroData::getProp(Entity::attr_money)<money)
	{
		m_pMoney->setColor(ccRED);
	}
	else
	{
		m_pMoney->setColor(ccWHITE);
	}

	int vcoin=CommonFunction::getReqVcoin(pUserItem,TAG_MoveOther,m_bLock);
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

void QHZYpanel::removeItem()
{
	m_pMenu->removeAllChildren();
	m_pRightUserItem=NULL;
	m_pLeftUserItem=NULL;
	m_pYuanBaoMoney->setString("");
	m_pMoney->setString("");
}

void QHZYpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void QHZYpanel::menuCallBack( CCObject *pSender )
{
	CCLOG("QHZYpanel Press");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_UPGRADE:
			if (m_pLeftUserItem && m_pRightUserItem)
			{
				int rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pRightUserItem,TAG_MoveOther,m_bLock,0,0,0);
				if (rvt==Error::Success)
				{
					if (m_bLock)
					{
						CommonFunction::sendmsgChangeEnhance(m_pLeftUserItem->iid,m_pRightUserItem->iid,1);
					}
					else
					{
						CommonFunction::sendmsgChangeEnhance(m_pLeftUserItem->iid,m_pRightUserItem->iid);
					}
				}
				else
				{
					CPEventHelper::uiNotify("","",rvt);
				}
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::NotEquip);
			}
			AudioLoader::play(Sound::Effect::jipinzhuanyi);
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
			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pLeftUserItem,TAG_MoveOther,0)).c_str());
			break;
		default:
			break;
		}

	}
}

//--------------------------------------------------------------------------------------------------------------------//

JDZYpanel::JDZYpanel( void ):
	m_pLeftUserItem(NULL),
	m_pRightUserItem(NULL),
	m_pYuanBaoMoney(NULL),
	m_pYuanBao(NULL),
	m_pMoney(NULL),
	m_bLock(false)
{
	for (int i=0;i<3;i++)
	{
		m_pleftblock[i]=NULL;
	}
	for (int i=0;i<3;i++)
	{
		m_prightblock[i]=NULL;
	}
}

JDZYpanel::~JDZYpanel( void )
{

}

JDZYpanel* JDZYpanel::create()
{
	JDZYpanel* pPanel = new JDZYpanel();
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

bool JDZYpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	//装备升级3个框
	CCSprite *pButton1=SystemData::getSpriteByPlist("forging_base");//升级物品框
	pButton1->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
	CCSprite *pButton2=SystemData::getSpriteByPlist("forging_base");//升级材料框
	pButton2->setPosition(SystemData::getLayoutPoint("JPZY_right_pos"));
	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("JPZY_MBZB");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1->getPositionX(),pButton1->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("JPZY_CLZB");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2->getPositionX(),pButton2->getPositionY()+50));
	addChild(pSJWPK);
	addChild(pSJCLK);
	addChild(pButton1);
	addChild(pButton2);
	
	CCSprite *pButton4=SystemData::getSpriteByPlist("forging_base");//升级物品框
	pButton4->setPosition(SystemData::getLayoutPoint("JPZY_button1_pos"));
	m_pTopList->addChild(pButton4);
	CCLabelTTF* pZYCL=SystemData::getLabelTTF("JPZY_ZYCL");
	pZYCL->setPosition(ccp(pButton4->getPositionX(),pButton4->getPositionY()-50));
	pZYCL->setColor(ccc3(3,223,204));
	pZYCL->setFontSize(18);
	m_pTopList->addChild(pZYCL);

	for (int i=1;i<=3;i++)
	{
		CCPoint posleft=ccp(pButton1->getPositionX(),pButton1->getPositionY()-i*30-20);
		m_pleftblock[i-1]=SystemData::getLabelTTF("XXXXX");
		m_pleftblock[i-1]->setAnchorPoint(ccp(0.5,0.5));
		m_pleftblock[i-1]->setPosition(posleft); 
		m_pleftblock[i-1]->setFontSize(14);
		m_pleftblock[i-1]->setColor(ccWHITE);
		m_pTopList->addChild(m_pleftblock[i-1]);

		CCPoint posright=ccp(pButton2->getPositionX(),pButton2->getPositionY()-i*30-20);
		m_prightblock[i-1]=SystemData::getLabelTTF("XXXXX");
		m_prightblock[i-1]->setAnchorPoint(ccp(0.5,0.5));
		m_prightblock[i-1]->setPosition(posright); 
		m_prightblock[i-1]->setFontSize(14);
		m_prightblock[i-1]->setColor(ccWHITE);
		m_pTopList->addChild(m_prightblock[i-1]);
	}

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(JDZYpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("JPZY_center_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("JPZY_ZY");
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

	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("ZBSJ_label2_pos"));
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+m_pYuanBao->getContentSize().width+5,m_pYuanBao->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);


	CPCheckBox* plock=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock->setTag(TAG_LOCK);
	plock->setHandler(this,menu_selector(JDZYpanel::menuCallBack));
	plock->setPosition(SystemData::getLayoutPoint("ZBSJ_label3_pos"));
	m_pTopList->addChild(plock);


	//pTHYB->setAnchorPoint(CCPointZero);
	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	//m_pTopList->addChild(pTHYB);
	m_pTopList->addChild(m_pYuanBao);
	m_pTopList->addChild(m_pMoney);
	m_pTopList->addChild(m_pYuanBaoMoney);
	m_pTopList->addChild(pXYJB);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);

	//物品说明menu
	m_pBottomList=GeneralMenu::create();
	m_pBottomList->setPosition(CCPointZero);
	addChild(m_pBottomList);	


	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);	

	return true;
}

void JDZYpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		addItem(NULL);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
		addChild(p);
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
		addChild(p);
	}
}

void JDZYpanel::addItem( UserItem* pUserItem )
{
	if (pUserItem==NULL)
	{
		removeItem();
		return;
	}
	if (m_pLeftUserItem)
	{
		if (m_pLeftUserItem->iid==pUserItem->iid)
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
		CCMenuItemImage* pItem=CommonFunction::getItemIcon(pUserItem,false);
		pItem->setTarget(this,menu_selector(JDZYpanel::ItemCallBack));
		pItem->setPosition(SystemData::getLayoutPoint("JPZY_left_pos"));
		pItem->setTag(1);
		m_pMenu->addChild(pItem);

		//载入当前鉴定属性
		int combo=pUserItem->data[ItemEquip::Item_DataCombo];
		int number=0;
		int n=0;
		for (int b=0;b<3;b++)
		{
			int c=(int)((int)combo >> (8*b) & 255);
			if(c!=0)
			{
				number++;
			}
		}
		for (n;(int)((int)combo>>(n*8) & 255)!=0;n++)
		{
			int x=(int)((int)combo>>(n*8) & 255);
			std::string name;
			LuaData::getProp("gdEquipEvaluate",x,"name",name);
			float combovalue;
			CCString* pStr;
			if (x==11 || x==12 || x==13 || x==15 || x==17|| x==18)
			{
				combovalue=(float)pUserItem->data[ItemEquip::Item_DataX+n];
				combovalue=combovalue/100;
				pStr=CCString::createWithFormat("%s:+%.2f%%",name.c_str(),combovalue);
			}
			else
			{
				pStr=CCString::createWithFormat("%s:+%d",name.c_str(),pUserItem->data[ItemEquip::Item_DataX+n]);
			}
			m_pleftblock[n]->setString(pStr->getCString());
		}
		for (n;n<3;n++)
		{
			m_pleftblock[n]->setString(SystemData::getLayoutString("ItemTips_WJD").c_str());
		}
	}
}

void JDZYpanel::addItem2( UserItem* pUserItem )
{
	if (pUserItem->type!=m_pLeftUserItem->type)
	{
		return;
	}
	if (m_pRightUserItem)
	{
		m_pMenu->removeChildByTag(2);
	}
	m_pRightUserItem=pUserItem;
	CCMenuItemImage* pItem=CommonFunction::getItemIcon(pUserItem,false);
	pItem->setTarget(this,menu_selector(JDZYpanel::ItemCallBack));
	pItem->setPosition(SystemData::getLayoutPoint("JPZY_right_pos"));
	pItem->setTag(2);
	m_pMenu->addChild(pItem);

	/*//重新加载目标预览
	CCMenuItemImage* ptgtItem=CommonFunction::getTgtEvaluateAttrItem(m_pLeftUserItem,m_pRightUserItem);
	ptgtItem->setTarget(this,menu_selector(JDZYpanel::ItemCallBack));
	m_pMenu->addChild(ptgtItem);*/

	//添加强化转移符
	CCMenuItemImage* pReqItem=CommonFunction::getReqEvaluateAttrItem(pUserItem);
	pReqItem->setTarget(this,menu_selector(JDZYpanel::ItemCallBack));
	pReqItem->setPosition(SystemData::getLayoutPoint("JPZY_button1_pos"));
	m_pMenu->addChild(pReqItem);

	//载入当前鉴定属性
	int combo=pUserItem->data[ItemEquip::Item_DataCombo];
	int number=0;
	int n=0;
	for (int b=0;b<3;b++)
	{
		int c=(int)((int)combo >> (8*b) & 255);
		if(c!=0)
		{
			number++;
		}
	}
	for (n;(int)((int)combo>>(n*8) & 255)!=0;n++)
	{
		int x=(int)((int)combo>>(n*8) & 255);
		std::string name;
		LuaData::getProp("gdEquipEvaluate",x,"name",name);
		float combovalue;
		CCString* pStr;
		if (x==11 || x==12 || x==13 || x==15 || x==17|| x==18)
		{
			combovalue=(float)pUserItem->data[ItemEquip::Item_DataX+n];
			combovalue=combovalue/100;
			pStr=CCString::createWithFormat("%s:+%.2f%%",name.c_str(),combovalue);
		}
		else
		{
			pStr=CCString::createWithFormat("%s:+%d",name.c_str(),pUserItem->data[ItemEquip::Item_DataX+n]);
		}
		m_prightblock[n]->setString(pStr->getCString());
	}
	for (n;n<3;n++)
	{
		m_prightblock[n]->setString(SystemData::getLayoutString("ItemTips_WJD").c_str());
	}

	int money=0;
	//LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqGold",money);
	m_pMoney->setString(SystemData::intToString(money).c_str());
	if (HeroData::getProp(Entity::attr_money)<money)
	{
		m_pMoney->setColor(ccRED);
	}
	else
	{
		m_pMoney->setColor(ccWHITE);
	}

	int vcoin=CommonFunction::getReqVcoin(pUserItem,TAG_MoveOther,m_bLock);
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

void JDZYpanel::removeItem()
{
	m_pMenu->removeAllChildren();
	m_pRightUserItem=NULL;
	m_pLeftUserItem=NULL;
	m_pYuanBaoMoney->setString("");
	m_pMoney->setString("");

	for (int n=0;n<3;n++)
	{
		m_prightblock[n]->setString("");
		m_pleftblock[n]->setString("");
	}
}

void JDZYpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void JDZYpanel::menuCallBack( CCObject *pSender )
{
	CCLOG("JDZYpanel Press");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_UPGRADE:
			if (m_pLeftUserItem && m_pRightUserItem)
			{
				int rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pRightUserItem,TAG_MoveOther,m_bLock,0,0,0);
				if (rvt==Error::Success)
				{
					if (m_bLock)
					{
						CommonFunction::sendmsgChangeEvaluate(m_pLeftUserItem->iid,m_pRightUserItem->iid,1);
					}
					else
					{
						CommonFunction::sendmsgChangeEvaluate(m_pLeftUserItem->iid,m_pRightUserItem->iid);
					}
				}
				else
				{
					CPEventHelper::uiNotify("","",rvt);
				}
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::NotEquip);
			}
			AudioLoader::play(Sound::Effect::jipinzhuanyi);
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
			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pLeftUserItem,TAG_MoveOther,0)).c_str());
			break;
		default:
			break;
		}

	}
}
//-------------------------------------------------------------------------------------------------------------------------------//

JPQXpanel::JPQXpanel( void ):
	m_pUserItem(NULL),
	m_pYuanBaoMoney(NULL),
	m_pYuanBao(NULL),
	m_pMoney(NULL),
	m_bLock(false)
{

}

JPQXpanel::~JPQXpanel( void )
{

}

JPQXpanel* JPQXpanel::create()
{
	JPQXpanel* pPanel = new JPQXpanel();
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

bool JPQXpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	//装备升级3个框
	CCSprite *pButton1=SystemData::getSpriteByPlist("forging_base");//升级物品框
	pButton1->setPosition(SystemData::getLayoutPoint("JPQX_up_pos"));
	CCSprite *pButton2=SystemData::getSpriteByPlist("forging_base");//升级材料框
	pButton2->setPosition(SystemData::getLayoutPoint("JPQX_down_pos"));
	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("JPZY_MBZB");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1->getPositionX()-70,pButton1->getPositionY()));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("JPZY_CLZB");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2->getPositionX()-70,pButton2->getPositionY()));
	addChild(pSJWPK);
	addChild(pSJCLK);
	addChild(pButton1);
	addChild(pButton2);

	CCSprite *pButton4=SystemData::getSpriteByPlist("forging_base");//升级物品框
	pButton4->setPosition(SystemData::getLayoutPoint("JPZY_button1_pos"));
	m_pTopList->addChild(pButton4);
	CCLabelTTF* pZYCL=SystemData::getLabelTTF("JPZY_ZYCL");
	pZYCL->setPosition(ccp(pButton4->getPositionX(),pButton4->getPositionY()-50));
	pZYCL->setColor(ccc3(3,223,204));
	pZYCL->setFontSize(18);
	m_pTopList->addChild(pZYCL);

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(JPQXpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("JPZY_center_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("JPQX_QX");
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

	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("ZBSJ_label2_pos"));
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+m_pYuanBao->getContentSize().width+5,m_pYuanBao->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);


	CPCheckBox* plock=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock->setTag(TAG_LOCK);
	plock->setHandler(this,menu_selector(JPQXpanel::menuCallBack));
	plock->setPosition(SystemData::getLayoutPoint("ZBSJ_label3_pos"));
	m_pTopList->addChild(plock);


	//pTHYB->setAnchorPoint(CCPointZero);
	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	//m_pTopList->addChild(pTHYB);
	m_pTopList->addChild(m_pYuanBao);
	m_pTopList->addChild(m_pMoney);
	m_pTopList->addChild(m_pYuanBaoMoney);
	m_pTopList->addChild(pXYJB);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);

	//物品说明menu
	m_pBottomList=GeneralMenu::create();
	m_pBottomList->setPosition(CCPointZero);
	addChild(m_pBottomList);	


	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);	

	return true;
}

void JPQXpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		addItem(NULL);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("JPQX_up_pos"));
		addChild(p);
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("JPQX_up_pos"));
		addChild(p);
	}
}

void JPQXpanel::addItem( UserItem* pUserItem )
{
	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		return;
	}
	m_pUserItem=pUserItem;
	CCMenuItemImage* icon=CommonFunction::getItemIcon(pUserItem,false);
	icon->setPosition(SystemData::getLayoutPoint("JPQX_up_pos"));	
	icon->setTarget(this,menu_selector(JPQXpanel::ItemCallBack));
	m_pMenu->addChild(icon);

	//加载相对应的item（材料，保护符，效果图）
	CCMenuItemImage* req =CommonFunction::getReqClearSpecialAttrItem(pUserItem);
	req->setPosition(SystemData::getLayoutPoint("JPZY_button1_pos"));
	req->setTarget(this,menu_selector(JPQXpanel::ItemCallBack));
	m_pMenu->addChild(req);

	//加载升级后的预览物品
	CCMenuItemImage* UpgradeAft=CommonFunction::getTgtClearSpecialAttrItem(pUserItem);
	UpgradeAft->setTarget(this,menu_selector(JPQXpanel::ItemCallBack));
	m_pMenu->addChild(UpgradeAft);


	int money=0;
	//LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqGold",money);
	m_pMoney->setString(SystemData::intToString(money).c_str());
	if (HeroData::getProp(Entity::attr_money)<money)
	{
		m_pMoney->setColor(ccRED);
	}
	else
	{
		m_pMoney->setColor(ccWHITE);
	}

	int vcoin=CommonFunction::getReqVcoin(pUserItem,TAG_ClearAttr,m_bLock);
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

void JPQXpanel::removeItem()
{
	m_pMenu->removeAllChildren();
	m_pUserItem=NULL;
	m_pYuanBaoMoney->setString("");
	m_pMoney->setString("");
}

void JPQXpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void JPQXpanel::menuCallBack( CCObject *pSender )
{
	CCLOG("JDZYpanel Press");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_UPGRADE:
			if (m_pUserItem)
			{
				int rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_ClearAttr,m_bLock,0,0,0);
				if (rvt==Error::Success)
				{
					if (m_bLock)
					{
						CommonFunction::sendmsgClearSpecialAttr(m_pUserItem->iid,1);
					}
					else
					{
						CommonFunction::sendmsgClearSpecialAttr(m_pUserItem->iid);
					}
				}
				else
				{
					CPEventHelper::uiNotify("","",rvt);
				}
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::NotEquip);
			}
			AudioLoader::play(Sound::Effect::jipinzhuanyi);
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
			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pUserItem,TAG_ClearAttr,0)).c_str());
			break;
		default:
			break;
		}

	}
}
