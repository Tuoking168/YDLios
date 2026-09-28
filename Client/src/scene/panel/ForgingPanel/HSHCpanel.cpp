#include "HSHCpanel.h"
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
#include "userdata/luadata/LuaData.h"
#include "MergeMainPanel.h"
#include "ForgingMainPanel.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventHelper.h"
#include "scene/panel/ForgingPanel/ForgingMainPanel.h"
#include "scene/panel/MainPanel.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "controls/CPCheckBox.h"
#include "res/AudioLoader.h"
#include "ErrorDefinition.h"

HSHC_HSHCpanel::HSHC_HSHCpanel( void ):
	m_pMoney(NULL),
	m_pUserItem(NULL),
	m_pTgtItem(NULL),
	m_pYuanBaoMoney(NULL),
	m_pYuanBao(NULL),
	m_bLock(false)
{

}

HSHC_HSHCpanel::~HSHC_HSHCpanel( void )
{

}

HSHC_HSHCpanel* HSHC_HSHCpanel::create()
{
	HSHC_HSHCpanel* pPanel = new HSHC_HSHCpanel();
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

bool HSHC_HSHCpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}

	//装备升级界面背景
	CCScale9Sprite* bkgSprite = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("HSHC_HSHC_size.w"),SystemData::getLayoutValue("HSHC_HSHC_size.h"));
	m_nWidth = bkgSprite->getContentSize().width;
	m_nHeight = bkgSprite->getContentSize().height;
	bkgSprite->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_pos"));
	bkgSprite->setAnchorPoint(CCPointZero);
	addChild(bkgSprite);
	
	addCover();//保证点击事件

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);


	CCMenuItemImage* pLeftButton=SystemData::getMenuItemImageByPlist("forging_button3");
	pLeftButton->setPosition(SystemData::getLayoutPoint("HSHC_leftbutton_pos"));
	pLeftButton->setTag(TAG_HC);
	pLeftButton->setTarget(this,menu_selector(HSHC_HSHCpanel::menuCallBack));
	m_pTopList->addChild(pLeftButton);
	CCLabelTTF* pLeftLabel=SystemData::getLabelTTF("HSHC_HSHC");
	pLeftLabel->setFontSize(18);
	pLeftLabel->setColor(ccWHITE);
	pLeftLabel->setPosition(SystemData::getLayoutPoint("HSHC_leftbutton_pos"));
	m_pTopList->addChild(pLeftLabel);
	 
	CCMenuItemImage* pRightButton=SystemData::getMenuItemImageByPlist("forging_unselect");
	pRightButton->setPosition(SystemData::getLayoutPoint("HSHC_rightbutton_pos"));
	pRightButton->setTarget(this,menu_selector(HSHC_HSHCpanel::menuCallBack));
	pRightButton->setTag(TAG_ZH);
	m_pTopList->addChild(pRightButton);
	CCLabelTTF* pRightLabel=SystemData::getLabelTTF("HSHC_HSZH");
	pRightLabel->setFontSize(18);
	pRightLabel->setColor(ccWHITE);
	pRightLabel->setPosition(SystemData::getLayoutPoint("HSHC_rightbutton_pos"));
	m_pTopList->addChild(pRightLabel);

	//放标题背景
	CCLabelTTF* pFRXYHCDHS=SystemData::getLabelTTF("HSHC_HSHC_FRXYHCDHS");
	pFRXYHCDHS->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_title_pos"));
	pFRXYHCDHS->setColor(ccWHITE); 
	pFRXYHCDHS->setFontSize(16);
	m_pTopList->addChild(pFRXYHCDHS);


	for (int i=0;i<3;i++)
	{
		CCSprite *pButton1n=SystemData::getSpriteByPlist("forging_base");
		pButton1n->setPosition(ccp(SystemData::getLayoutPoint("HSHC_HSHC_button_pos").x+i*111,SystemData::getLayoutPoint("HSHC_HSHC_button_pos").y));
		m_pTopList->addChild(pButton1n);
	}

	//向下箭头
	CCSprite *pDown=SystemData::getSpriteByPlist("forging_up");
	pDown->runAction(CCFlipY::create(true));
	pDown->setScale(1.5);
	pDown->setScaleX(2);
	pDown->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_Down_pos"));
	m_pTopList->addChild(pDown);


	//中间框体
	CCScale9Sprite* pCenterborder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBSJ_smallborder_size.w"),SystemData::getLayoutValue("ZBSJ_smallborder_size.h"));
	pCenterborder->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_Center_pos"));
	addChild(pCenterborder);

	CCSprite *pItemborder=SystemData::getSpriteByPlist("forging_result");
	pItemborder->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_Center_pos"));
	addChild(pItemborder);
		
	// 合成按钮
	CCScale9Sprite *pZHButton1=SystemData::getScale9SpriteByPlist("forging_button3",78,40);
	CCScale9Sprite *pZHButton2=SystemData::getScale9SpriteByPlist("forging_button3.sel",78,40);
	CCMenuItemImage* pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTarget(this,menu_selector(HSHC_HSHCpanel::menuCallBack));
	pUpLevel->setTag(TAG_Upgrade);
	pUpLevel->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_HCbutton_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("HSHC_HSHC_HC");
	pUpLevelLabel->setFontSize(20);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);

	//跳转魂石镶嵌界面
	CCMenuItemImage* pBackButton=SystemData::getMenuItemImageByPlist("forging_button3");
	pBackButton->setPosition(SystemData::getLayoutPoint("HSHC_backbutton_pos"));
	pBackButton->setTarget(this,menu_selector(HSHC_HSHCpanel::menuCallBack));
	pBackButton->setTag(TAG_SoulStonePanel);
	m_pTopList->addChild(pBackButton);
	CCLabelTTF* pBackLabel=SystemData::getLabelTTF("HSHC_HSXQ");
	pBackLabel->setFontSize(18);
	pBackLabel->setColor(ccWHITE);
	pBackLabel->setPosition(SystemData::getLayoutPoint("HSHC_backbutton_pos"));
	m_pTopList->addChild(pBackLabel);


	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBSJ_XYJB");//需要金币
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_label1_pos"));
	m_pMoney=SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);	
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(ccp(pXYJB->getPositionX()+50,pXYJB->getPositionY()));

	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要金币
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_label2_pos"));
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+80,m_pYuanBao->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);


	CPCheckBox* plock=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock->setTag(TAG_LOCK);
	plock->setHandler(this,menu_selector(HSHC_HSHCpanel::menuCallBack));
	plock->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_label3_pos"));
	m_pTopList->addChild(plock);
	
	// 修改：将复选框设为不可见
	plock->setVisible(false);
	// 如果复选框有label，也需要隐藏
	if (pTHYB) {
		pTHYB->setVisible(false);
	}

	//pTHYB->setAnchorPoint(CCPointZero);
	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	//addChild(pTHYB);
	addChild(m_pYuanBao);
	addChild(m_pMoney);
	addChild(m_pYuanBaoMoney);
	addChild(pXYJB);

	m_pYuanBaoMoney->setVisible(false);
	m_pYuanBao->setVisible(false);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	return true;
}

void HSHC_HSHCpanel::menuCallBack( CCObject *pSender )
{
	CCLog("HSHC_HSZHpanel press down");	
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int rvt=0;
		int tag = pNode->getTag();
		HSHC_HSZHpanel* p=NULL;
		switch (tag)
		{	
		case TAG_ZH:
			((MergeMainPanel* )this->getParent())->addTopFunc(TAG_HSZH);
			break;
		case TAG_HC:
			return;					
			break;
		case TAG_SoulStonePanel:
			//EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TURNTO_HSXQ);
			CPEventHelper::openPanel("MainPanel",0,11,0,0);
			break;
		case TAG_Upgrade:
			rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pTgtItem,TAG_Merge,m_bLock,0,0,0);
			if (rvt==Error::Success)
			{
				if (m_bLock)
				{
					CommonFunction::sendmsgMerge(m_pTgtItem->sid,1);
				}
				else
				{
					CommonFunction::sendmsgMerge(m_pTgtItem->sid);
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
			//m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pTgtItem,TAG_Merge,0)).c_str());
			break;
		default:
			break;
		}
	}
}

void HSHC_HSHCpanel::addItem( UserItem* useritem )
{
	m_pMenu->removeAllChildren();
	if (useritem==NULL)
	{
		return;
	}
	m_pUserItem=useritem;
	CCArray* pArray=CommonFunction::getReqStoneItem(useritem);
	CCObject* pObject;
	int i=0;
	CCARRAY_FOREACH(pArray,pObject)
	{
		CCMenuItemImage* pItem=(CCMenuItemImage*)pObject;
		pItem->setPosition(ccp(SystemData::getLayoutPoint("HSHC_HSHC_button_pos").x+i*111,SystemData::getLayoutPoint("HSHC_HSHC_button_pos").y));
		pItem->setTarget(this,menu_selector(HSHC_HSHCpanel::ItemCallBack));
		m_pMenu->addChild(pItem);
		i++;
	}

	//加载目标物品
	CCMenuItemImage* pStone=CommonFunction::getTgtStoneItem(useritem);
	pStone->setTarget(this,menu_selector(HSHC_HSHCpanel::ItemCallBack));
	m_pMenu->addChild(pStone);
	m_pTgtItem=(UserItem*)(pStone->getUserData());


	int money=0;
	LuaData::getProp("gdItemMerge",m_pTgtItem->sid,"reqGold",money);
	m_pMoney->setString(SystemData::intToString(money).c_str());
	if (HeroData::getProp(Entity::attr_money)<money)
	{
		m_pMoney->setColor(ccRED);
	}
	else
	{
		m_pMoney->setColor(ccWHITE);
	}

	int vcoin=CommonFunction::getReqVcoin(m_pTgtItem,TAG_Merge,0);
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

void HSHC_HSHCpanel::ItemCallBack( CCObject* pSender )
{
	if (getChildByTag(100))
	{
		removeChildByTag(100);
	}
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	ItemTooltip* pTip=CommonFunction::getItemTips(pItem,TAG_Tips);
	pTip->setAnchorPoint(CCPointZero);
	pTip->setPosition(ccp(100,30));
	pTip->setTag(100);
	addChild(pTip);
	CCLOG("Item Call Back!");
}

void HSHC_HSHCpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		addItem(NULL);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_Center_pos"));
		addChild(p);
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_Center_pos"));
		addChild(p);

		AudioLoader::play(Sound::Effect::hecheng);
	}
}

//--------------------------------------------------------------------------------------------------------//



HSHC_HSZHpanel::HSHC_HSZHpanel( void ):
	m_pMoney(NULL),
	m_bLock(false),
	m_pUserItem(NULL),
	m_iSelectSid(0),
	m_pLabel1(NULL),
	m_pLabel2(NULL)

{
	
}

HSHC_HSZHpanel::~HSHC_HSZHpanel( void )
{

}

HSHC_HSZHpanel* HSHC_HSZHpanel::create()
{
	HSHC_HSZHpanel* pPanel = new HSHC_HSZHpanel();
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

bool HSHC_HSZHpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_iCurrentCount=1;

	//装备升级界面背景
	CCScale9Sprite* bkgSprite = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_mainpanel_size.w"),SystemData::getLayoutValue("forging_mainpanel_size.h"));
	m_nWidth = bkgSprite->getContentSize().width;
	m_nHeight = bkgSprite->getContentSize().height;
	bkgSprite->setPosition(SystemData::getLayoutPoint("forging_mainpanel_pos"));
	bkgSprite->setAnchorPoint(CCPointZero);
	addChild(bkgSprite);

	addCover();//保证点击事件
	
	//放标题背景
	CCLabelTTF* pFRXYHCDHS=SystemData::getLabelTTF("HSHC_HSZH_FRXYZHDHS");
	pFRXYHCDHS->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_title_pos"));
	pFRXYHCDHS->setAnchorPoint(CCPointZero);
	pFRXYHCDHS->setColor(ccc3(3,223,204));
	pFRXYHCDHS->setFontSize(14);
	addChild(pFRXYHCDHS);

	CCSprite *pItemSpriteborder=SystemData::getSpriteByPlist("forging_base");
	pItemSpriteborder->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_button_pos"));
	addChild(pItemSpriteborder);
	
	
	//向下箭头
	CCSprite *pDown1=SystemData::getSpriteByPlist("forging_up");
	pDown1->runAction(CCFlipY::create(true));
	pDown1->setScale(1.5);
	pDown1->setScaleX(2);
	pDown1->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_Down_pos"));
	addChild(pDown1);

	//中间框体
	CCScale9Sprite* pCenterborder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("HSHC_ZH_smallborder_size.w"),SystemData::getLayoutValue("HSHC_ZH_smallborder_size.h"));
	pCenterborder->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_Center_pos"));
	addChild(pCenterborder);

	CCSprite *pItemborder1=SystemData::getSpriteByPlist("forging_result");
	pItemborder1->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_center_Item1_pos"));
	addChild(pItemborder1);

	m_pLabel1=SystemData::getLabelTTF("");
	m_pLabel1->setPosition(ccp(pItemborder1->getPositionX(),pItemborder1->getPositionY()-39));
	m_pLabel1->setColor(ccYELLOW);
	addChild(m_pLabel1);
	

	CCSprite *pItemborder2=SystemData::getSpriteByPlist("forging_result");
	pItemborder2->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_center_Item2_pos"));
	addChild(pItemborder2);

	m_pLabel2=SystemData::getLabelTTF("");
	m_pLabel2->setPosition(ccp(pItemborder2->getPositionX(),pItemborder2->getPositionY()-39));
	m_pLabel2->setColor(ccYELLOW);
	addChild(m_pLabel2);
	
	CCLabelTTF *pTitleLabel=SystemData::getLabelTTF("HSHC_HSZH_XZZHZHDHS");
	pTitleLabel->setFontSize(18);
	pTitleLabel->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_center_title_pos"));
	pTitleLabel->setColor(ccc3(3,223,204));
	addChild(pTitleLabel);
		

	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setAnchorPoint(CCPointZero);
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);


	CCMenuItemImage* pLeftButton=SystemData::getMenuItemImageByPlist("forging_unselect");
	pLeftButton->setPosition(SystemData::getLayoutPoint("HSHC_leftbutton_pos"));
	pLeftButton->setTag(TAG_HC);
	pLeftButton->setTarget(this,menu_selector(HSHC_HSZHpanel::menuCallBack));
	m_pTopList->addChild(pLeftButton);
	CCLabelTTF* pLeftLabel=SystemData::getLabelTTF("HSHC_HSHC");
	pLeftLabel->setFontSize(18);
	pLeftLabel->setColor(ccWHITE);
	pLeftLabel->setPosition(SystemData::getLayoutPoint("HSHC_leftbutton_pos"));
	m_pTopList->addChild(pLeftLabel);

	CCMenuItemImage* pRightButton=SystemData::getMenuItemImageByPlist("forging_button3");
	pRightButton->setPosition(SystemData::getLayoutPoint("HSHC_rightbutton_pos"));
	pRightButton->setTarget(this,menu_selector(HSHC_HSZHpanel::menuCallBack));
	pRightButton->setTag(TAG_ZH);
	m_pTopList->addChild(pRightButton);
	CCLabelTTF* pRightLabel=SystemData::getLabelTTF("HSHC_HSZH");
	pRightLabel->setFontSize(18);
	pRightLabel->setColor(ccWHITE);
	pRightLabel->setPosition(SystemData::getLayoutPoint("HSHC_rightbutton_pos"));
	m_pTopList->addChild(pRightLabel);

	CCMenuItemImage* pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTarget(this,menu_selector(HSHC_HSZHpanel::menuCallBack));
	pUpLevel->setTag(TAG_HSZH);
	pUpLevel->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_ZHbutton_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("HSHC_HSZH");
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

	m_pMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	addChild(m_pMoney);
	addChild(pXYJB);

	//物品说明menu
	m_pBottomList=GeneralMenu::create();
	m_pBottomList->setPosition(CCPointZero);
	addChild(m_pBottomList);	

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
	
	m_pSprite=SystemData::getSpriteByPlist("ui_soulstone_select"); 
	m_pSprite->setVisible(false);
	addChild(m_pSprite);
	return true;
}

void HSHC_HSZHpanel::menuCallBack( CCObject *pSender )
{
	CCLog("HSHC_HSZHpanel press down");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		HSHC_HSHCpanel* p=NULL;
		switch (tag)
		{	
		case TAG_ZH:
			return;				
			break;
		case TAG_HC:
			((MergeMainPanel* )this->getParent())->addTopFunc(TAG_HSHC);
			break;
		case TAG_HSZH:
			if (m_pUserItem && m_iSelectSid!=0 && m_iSelectSid!=m_pUserItem->sid)
			{
				if (!CommonFunction::IsEnoughMoney(m_pUserItem,TAG_StoneTrans))
				{
 					CPEventHelper::uiNotify("","",Error::NotEnoughMoney);
				}
				else
				{
					CommonFunction::sendmsgStoneTrans(m_pUserItem->iid,m_iSelectSid);
				}
			}
			else
			{
// 				NotificationLua& nLua=NotificationLuaManager::Instance();
// 				nLua.showLog("no Right Equip",Notification_RED);
			}
			break;
		default:
// 			NotificationLua& nLua=NotificationLuaManager::Instance();
// 			nLua.showLog("no implement",Notification_RED);
			break;
		}
	}
}


cocos2d::CCSize HSHC_HSZHpanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(420, m_iHeight);
}

cocos2d::extension::CCTableViewCell* HSHC_HSZHpanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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
		LuaData::getProp("gddescription",16,"content",content);
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

unsigned int HSHC_HSZHpanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}


void HSHC_HSZHpanel::addItem( UserItem* useritem )
{
	m_iSelectSid=0;
	m_pUserItem=NULL;
	m_pSprite->setVisible(false);
	m_pMenu->removeAllChildren();
	m_pLabel1->setString(" ");
	m_pLabel2->setString(" ");
	if (useritem==NULL)
	{
		return;
	}
	
	// 检查物品类型
	if (useritem->category != ItemCate_Stone && useritem->category != ItemCate_Equip)//增加装备转换
	{
		return;  // 不支持的类型
	}
	
	//需要转化的物品（魂石或装备）
	CCMenuItemImage* icon=CommonFunction::getItemIcon(useritem,false);
	icon->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_button_pos"));
	icon->setTarget(this,menu_selector(HSHC_HSZHpanel::ItemCallBack));
	m_pMenu->addChild(icon);

	CCArray* pArray=CommonFunction::getReqStoneTransItem(useritem);
	CCObject* pObject;
	int i=0;
	CCARRAY_FOREACH(pArray,pObject)
	{
		CCMenuItemImage* pItem=(CCMenuItemImage*)pObject;
		if (i==0)
		{
			pItem->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_center_Item1_pos"));
			UserItem* p=(UserItem*)pItem->getUserData();
			m_pLabel1->setString(p->name.c_str());
		}
		else
		{
			pItem->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_center_Item2_pos"));
			UserItem* p=(UserItem*)pItem->getUserData();
			m_pLabel2->setString(p->name.c_str());
		}
		pItem->setTarget(this,menu_selector(HSHC_HSZHpanel::ItemCallBack));
		m_pMenu->addChild(pItem);
		i++;
	}
	int reqmoney=0;
	LuaData::getProp("gdItemStoneTransform",useritem->sid,"reqGold",reqmoney);
	m_pMoney->setString(SystemData::intToString(reqmoney).c_str());
	if (m_pMoney)
	{
		if (HeroData::getProp(Entity::attr_money)<reqmoney)
		{
			m_pMoney->setColor(ccRED);
		}
		else
		{
			m_pMoney->setColor(ccWHITE);
		}
	}

	m_pUserItem=useritem;
}

void HSHC_HSZHpanel::ItemCallBack( CCObject* pSender )
{


	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);

	//加上外框
	m_pSprite->setVisible(true);
	m_pSprite->setPosition(pImage->getPosition());
	m_iSelectSid=pItem->sid;
}

void HSHC_HSZHpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		addItem(NULL);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_button_pos"));
		addChild(p);
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("HSHC_HSZH_button_pos"));
		addChild(p);
	}
}


//----------------------------------------------------------------------------------------------------------//

