#include "WPHCpanel.h"
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

#include "CommonFunction.h"
#include "MergeMainPanel.h"
#include "userdata/luadata/LuaData.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventHelper.h"
#include "ZBQHpanel.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "controls/CPCheckBox.h"
#include "res/AudioLoader.h"



WPHCpanel::WPHCpanel( void ):
	m_bLock(false),
	m_pMoney(NULL),
	m_pUseritem(NULL),
	m_pCurrentItem(NULL),
	m_pYuanBaoMoney(NULL),
	m_pYuanBao(NULL),
	m_pJL(NULL)
{

}

WPHCpanel::~WPHCpanel( void )
{

}

WPHCpanel* WPHCpanel::create( int tag)//根据不同的tag创建不同的界面
{
	WPHCpanel* pPanel = new WPHCpanel();
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

bool WPHCpanel::init( int tag)
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_iCurrentCount=1;
	m_iTag=tag;


	std::string panelname=CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (panelname=="MainPanel")
	{
		int data3=CPEventHelper::getEventIntData(CPEventData::VALUE_4);
		m_iTag=data3;
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

	//放标题背景
	//顶部选项 文字
	CCSprite *pList=SystemData::getSpriteByPlist("forging_up");//下拉框
	pList->runAction(CCFlipY::create(true));
	CCMenuItemImage *pListButton=SystemData::getMenuItemImageByPlist("forging_protect");
	pListButton->setPosition(SystemData::getLayoutPoint("CBHC_Listbutton_pos"));
	pListButton->setTarget(this,menu_selector(WPHCpanel::menuCallBack));
	pListButton->setTag(TAG_LIST);
	m_pTopList->addChild(pListButton);
	pList->setPosition(ccp(pListButton->getPositionX()+75,pListButton->getPositionY()));
	addChild(pList);

	m_pCurrentItem=SystemData::getLabelTTF("CBHC_KTZY1D");
	m_pCurrentItem->setPosition(ccp(pListButton->getPositionX()-20,pListButton->getPositionY()));
	m_pCurrentItem->setFontSize(16);
	m_pCurrentItem->setColor(ccYELLOW);
	addChild(m_pCurrentItem);

	CCLabelTTF* pXZYHCDCBDC=SystemData::getLabelTTF("WPHC_CLXQ");
	pXZYHCDCBDC->setPosition(SystemData::getLayoutPoint("CBHC_title_pos"));
	pXZYHCDCBDC->setFontSize(16);
	pXZYHCDCBDC->setColor(ccWHITE);
	addChild(pXZYHCDCBDC);

	for (int i=0;i<5;i++)
	{
		CCSprite *pItemSpriteborder=SystemData::getSpriteByPlist("forging_base");
		pItemSpriteborder->setPosition(ccp(SystemData::getLayoutPoint("WPHC_Item_pos").x+i*70,SystemData::getLayoutPoint("WPHC_Item_pos").y));
		addChild(pItemSpriteborder);
	}
	
	//成功率
	CCLabelTTF *pSuccess=SystemData::getLabelTTF("WPHC_HCCGL");
	pSuccess->setColor(ccYELLOW);
	pSuccess->setFontSize(14);
	pSuccess->setPosition(SystemData::getLayoutPoint("WPHC_CGLLabel_pos"));
	addChild(pSuccess);
	m_pJL=SystemData::getLabelTTF("XXXXX");
	CCString *pStr1=CCString::createWithFormat("%s %%",m_pJL->getString());
	m_pJL->setString(pStr1->getCString());
	m_pJL->setFontSize(14);	
	m_pJL->setColor(ccYELLOW);
	m_pJL->setPosition(ccp(pSuccess->getPositionX()+70,pSuccess->getPositionY()));
	addChild(m_pJL);

	//中间框体

	CCScale9Sprite* pCenterborder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("WPHC_smallborder_size.w"),SystemData::getLayoutValue("WPHC_smallborder_size.h"));
	pCenterborder->setPosition(SystemData::getLayoutPoint("WPHC_Center_pos"));
	addChild(pCenterborder);
	
	CCSprite *pItemborder=SystemData::getSpriteByPlist("forging_result");
	pItemborder->setPosition(pCenterborder->getPosition());
	addChild(pItemborder);

	
	// 合成按钮
	CCSprite *pZHButton=SystemData::getSpriteByPlist("forging_button3");
	CCMenuItemSprite *pUpLevel=CCMenuItemSprite::create(pZHButton,pZHButton,NULL,this,menu_selector(WPHCpanel::menuCallBack));
	pUpLevel->setTag(TAG_Upgrade);
	pUpLevel->setPosition(SystemData::getLayoutPoint("WPHC_HCButton_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("WPHC_HC");
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
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+80,m_pYuanBao->getPositionY()));

	CCLabelTTF* pCLJB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pCLJB->setFontSize(12);	
	pCLJB->setColor(ccYELLOW);


	CPCheckBox* plock=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pCLJB);;
	plock->setTag(TAG_LOCK);
	plock->setHandler(this,menu_selector(WPHCpanel::menuCallBack));
	plock->setPosition(SystemData::getLayoutPoint("ZBSJ_label3_pos"));
	m_pTopList->addChild(plock);
	
	// 添加隐藏复选框的代码----------------------------//隐藏屏蔽复选框
	plock->setVisible(false);
	if (pCLJB) {
		pCLJB->setVisible(false);
	}

	m_pYuanBao->setAnchorPoint(CCPointZero);
	//pCLJB->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	addChild(m_pYuanBao);
	//addChild(pCLJB);
	addChild(m_pMoney);
	addChild(m_pYuanBaoMoney);
	addChild(pXYJB);

	//m_pMoney->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);
	m_pYuanBao->setVisible(false);
	
	if (m_iTag==TAG_ChiBang)
	{
		plock->setVisible(false);
		//plock->setEnabled(false);
		pCLJB->setVisible(false);

	}

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

void WPHCpanel::menuCallBack( CCObject *pSender )
{
	CCLog("HSHC_HSZHpanel press down");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int rvt=0;
		int tag = pNode->getTag();
		BasePanel *pPanel=NULL;
		switch (tag)
		{
		case TAG_LOCK:
			if (m_bLock)
			{
				m_bLock=false;
				m_pYuanBaoMoney->setVisible(false);
				m_pYuanBao->setVisible(false);
			}
			else
			{
				m_bLock=true;
				m_pYuanBaoMoney->setVisible(true);
				m_pYuanBao->setVisible(true);

			}

			//m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pUseritem,TAG_Merge,0)).c_str());
			break;
		case TAG_LIST:
			pPanel=HCListpanel::create(m_iTag);
			pPanel->setTag(TAG_LISTPANEL);
			addChild(pPanel); 
			break;
		case TAG_Upgrade:
			rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUseritem,TAG_Merge,m_bLock,0,0,0);
			if (rvt==Error::Success)
			{
				if (m_bLock)
				{
					CommonFunction::sendmsgMerge(m_pUseritem->sid,1);
				}
				else
				{
					CommonFunction::sendmsgMerge(m_pUseritem->sid);
				}
			}
			else
			{
				CPEventHelper::uiNotify("","",rvt);
			}
			break;
		default:
			break;
		}		
	}
}


cocos2d::CCSize WPHCpanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(420, m_iHeight);
}

cocos2d::extension::CCTableViewCell* WPHCpanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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

		int type=0;
		switch (m_iTag)
		{
		case  TAG_LingZhu://type=1
			type=10;
			break;
		case  TAG_ZhuangBei://type=2
			type=12;
			break;
		case  TAG_WuPin://type=3
			type=13;
			break;
		case  TAG_ChiBang://type=4
			type=14;
			break;
		case  TAG_MoJingShi://type=5
			type=15;
			break;
		case  TAG_JiNengShu://type=6
			type=11;
			break;
		}

		std::string content;
		LuaData::getProp("gddescription",type,"content",content);
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

unsigned int WPHCpanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void WPHCpanel::addItem(UserItem* useritem)
{	
	//根据材料筛选目标
	int tgtSid=0;
	int type=0;
	switch (m_iTag)
	{
	case  TAG_LingZhu://type=1
		type=1;
		break;
	case  TAG_ZhuangBei://type=2
		type=2;
		break;
	case  TAG_WuPin://type=3
		type=3;
		break;
	case  TAG_ChiBang://type=4
		type=4;
		break;
	case  TAG_MoJingShi://type=5
		type=5;
		break;
	case  TAG_JiNengShu://type=6
		type=6;
		break;
	}
	if (useritem==NULL)
	{
		return ;
	}
	LuaData::getProp_mergefindtgt("gdtgtItemMergeType",type,"gdItemMerge",useritem->sid,tgtSid); 

	if (tgtSid==0)
	{
		return;
	}

	UserItem* pUserItem=new UserItem;
	pUserItem->sid=tgtSid;
	std::string icon;
	LuaData::getProp(LuaData::ITEM,tgtSid,"icon",icon);
	pUserItem->icon=icon;
	std::string name;
	LuaData::getProp(LuaData::ITEM,tgtSid,"name",name);
	pUserItem->name=name;

	//调用addtgtItem显示
	addtgtItem(pUserItem);


}

void WPHCpanel::ItemCallBack( CCObject* pSender )
{

	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

bool WPHCpanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void WPHCpanel::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void WPHCpanel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (getChildByTag(TAG_LISTPANEL))
	{
		removeChildByTag(TAG_LISTPANEL);
	}
}

void WPHCpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		addtgtItem(m_pUseritem);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("WPHC_Center_pos"));
		addChild(p);
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("WPHC_Center_pos"));
		addChild(p);
		if (m_iTag==TAG_ChiBang)
		{
			AudioLoader::play(Sound::Effect::chibanghecheng);	
		}
		else
		{
			AudioLoader::play(Sound::Effect::hecheng);
		}
	}
}

void WPHCpanel::addtgtItem( UserItem* useritem )
{
	m_pMenu->removeAllChildren();
	if (useritem==NULL)
	{
		return;
	}
	m_pUseritem=useritem;
	//加载需要材料
	CCArray* pArray=CommonFunction::getReqMergeItem(m_pUseritem);
	CCObject* pObject;
	int i=0;
	CCARRAY_FOREACH(pArray,pObject)
	{
		CCMenuItemImage* pItem=(CCMenuItemImage*)pObject;
		pItem->setPosition(ccp(SystemData::getLayoutPoint("WPHC_Item_pos").x+i*70,SystemData::getLayoutPoint("WPHC_Item_pos").y));
		pItem->setTarget(this,menu_selector(WPHCpanel::ItemCallBack));
		m_pMenu->addChild(pItem);
		i++;
	}
	//更换名字
	m_pCurrentItem->setString(m_pUseritem->name.c_str());

	CCMenuItemImage* MergeAft=CommonFunction::getTgtMergeItem(m_pUseritem);
	MergeAft->setTarget(this,menu_selector(WPHCpanel::ItemCallBack));
	m_pMenu->addChild(MergeAft);

	int money=0;
	LuaData::getProp("gdItemMerge",m_pUseritem->sid,"reqGold",money);
	m_pMoney->setString(SystemData::intToString(money).c_str());
	if (HeroData::getProp(Entity::attr_money)<money)
	{
		m_pMoney->setColor(ccRED);
	}
	else
	{
		m_pMoney->setColor(ccWHITE);
	}

	int vcoin=CommonFunction::getReqVcoin(m_pUseritem,TAG_Merge,0);
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

	int pro=0;
	LuaData::getProp("gdItemMerge",m_pUseritem->sid,"probability",pro);
	CCString* p=CCString::createWithFormat("%d %%",pro);
	m_pJL->setString(p->getCString());
}



//----------------------------------------------------------------------------------------------------------------------------------//

HCListpanel::HCListpanel( void ):
	m_iSize(0),
	m_iCurType(0)
{

}

HCListpanel::~HCListpanel( void )
{

}

HCListpanel* HCListpanel::create( int tag/*=0*/ )//灵珠，物品，翅膀，等等分类
{
	HCListpanel* pPanel = new HCListpanel();
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

bool HCListpanel::init( int tag/*=0*/ )
{
	m_iCurType=tag;
	//根据tag取出相应的能够合成的列表
	switch (tag)
	{
	case TAG_PerfectEnhance:
		m_iType[0]=SystemData::getLayoutValue("5级完美强化符");
		m_iType[1]=SystemData::getLayoutValue("8级完美强化符");
		m_iType[2]=SystemData::getLayoutValue("10级完美强化符");
		m_iSize=3;
		break;
	case  TAG_LingZhu://type=1
		LuaData::getProp_size("gdtgtItemMergeType",1,"",m_iSize);
		for (int i=1;i<=m_iSize;i++)
		{
			LuaData::getProp("gdtgtItemMergeType",1,i,"sid",m_iType[i-1]);
		}
		break;
	case  TAG_MoJingShi://type=5
		LuaData::getProp_size("gdtgtItemMergeType",5,"",m_iSize);
		for (int i=1;i<=m_iSize;i++)
		{
			LuaData::getProp("gdtgtItemMergeType",5,i,"sid",m_iType[i-1]);
		}
		break;
	case  TAG_WuPin://type=3
		LuaData::getProp_size("gdtgtItemMergeType",3,"",m_iSize);
		for (int i=1;i<=m_iSize;i++)
		{
			LuaData::getProp("gdtgtItemMergeType",3,i,"sid",m_iType[i-1]);
		}
		break;
	case  TAG_ChiBang://type=4
		LuaData::getProp_size("gdtgtItemMergeType",4,"",m_iSize);
		for (int i=1;i<=m_iSize;i++)
		{
			LuaData::getProp("gdtgtItemMergeType",4,i,"sid",m_iType[i-1]);
		}
		break;
	case  TAG_ZhuangBei://type=2
		LuaData::getProp_size("gdtgtItemMergeType",2,"",m_iSize);
		for (int i=1;i<=m_iSize;i++)
		{
			LuaData::getProp("gdtgtItemMergeType",2,i,"sid",m_iType[i-1]);
		}
		break;
	case  TAG_JiNengShu://type=6
		LuaData::getProp_size("gdtgtItemMergeType",6,"",m_iSize);
		for (int i=1;i<=m_iSize;i++)
		{
			LuaData::getProp("gdtgtItemMergeType",6,i,"sid",m_iType[i-1]);
		}
		break;
	}

	int size=3;
	if (m_iSize<3)
	{
		size=m_iSize;
	}
	else if (m_iSize==0)
	{
		return false;
	}
	CCScale9Sprite* pborder=SystemData::getScale9SpriteByPlist("forging_protect",183,40*size);
	pborder->setAnchorPoint(ccp(0,1));
	pborder->setPosition(SystemData::getLayoutPoint("forging_list_pos"));
	addChild(pborder);

	m_nWidth = pborder->getContentSize().width;
	m_nHeight = pborder->getContentSize().height; 
	addCover(ccp(pborder->getPositionX(),pborder->getPositionY()-m_nHeight));	
	 
	//摆上列表
	CCTableViewEx *pTabelView=CCTableViewEx::create(this,CCSizeMake(178,35*size),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(ccp(pborder->getPositionX(),pborder->getPositionY()-m_nHeight+2.5*size));
	pTabelView->reloadData();  
	addChild(pTabelView);	

	return true;
}

void HCListpanel::menuCallBack( CCObject *pSender )
{
	CCMenuItemImage* icon=(CCMenuItemImage* )pSender;
	UserItem* pUserItem=(UserItem*)icon->getUserData();
	if (m_iCurType==TAG_PerfectEnhance)
	{
		((WMQHpanel*)(this->getParent()))->addReqItem(pUserItem);
	}
	else
	{		
		((WPHCpanel*)(this->getParent()))->addtgtItem(pUserItem);
	}
	this->removeFromParent();
}

cocos2d::CCSize HCListpanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(170,35);
}

cocos2d::extension::CCTableViewCell* HCListpanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		CCMenuEx* pMenu=CCMenuEx::create(NULL,NULL);
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		UserItem* pUserItem=CommonFunction::createNewItem(m_iType[idx]);

		CCScale9Sprite* p=SystemData::getScale9SpriteByPlist("forging_smallbkg",170,35);
		p->setOpacity(0);
		CCLabelTTF* pLabel=CCLabelTTF::create(pUserItem->name.c_str(),"微软雅黑",15);
		pLabel->setPosition(ccp(p->getContentSize().width/2,p->getContentSize().height/2));
		p->addChild(pLabel);
		CCMenuItemSprite* pItem=CCMenuItemSprite::create(p,p,NULL,this,menu_selector(HCListpanel::menuCallBack));
		pItem->setPosition(pLabel->getPosition());
		pItem->setUserData(pUserItem);
		pMenu->addChild(pItem);
	}
	return cell;
}

unsigned int HCListpanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return m_iSize;
}
