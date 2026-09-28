#include "ZBSJpanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/HeroData.h"
#include "userdata/UserData.h"
#include "event/EventProtocol.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"

#include "userdata/netdata/GameRole.h"

#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"
#include "ext/CCTabelViewEx.h"

#include "CommonFunction.h"
#include "userdata/luadata/LuaData.h"
#include "script/LuaWrapper.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventHelper.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "controls/CPCheckBox.h"
#include "res/AudioLoader.h"

ZBSJpanel::ZBSJpanel( void ):
	m_pUserItem(NULL),
	m_pMoney(NULL),
	m_bLock(false),
	m_bEnoughCL(false),
	m_pYuanBao(NULL),
	m_pYuanBaoMoney(NULL),
	m_pRebornReq(NULL),
	m_pRebornName(NULL),
	m_plock(NULL)
{

}

ZBSJpanel::~ZBSJpanel( void )
{

}

ZBSJpanel* ZBSJpanel::create()
{
	ZBSJpanel* pPanel = new ZBSJpanel();
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
void ZBSJpanel::updateTimer(float dt)
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

bool ZBSJpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	// 添加：初始化冷却时间
	m_iTimeSpan = 0;
	
	// 添加：启动冷却时间更新计时器
	this->schedule(schedule_selector(ZBSJpanel::updateTimer), 1.0f);

	//装备升级界面背景
	CCScale9Sprite* bkgSprite = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_mainpanel_size.w"),SystemData::getLayoutValue("forging_mainpanel_size.h"));
	m_nWidth = bkgSprite->getContentSize().width;
	m_nHeight = bkgSprite->getContentSize().height;
	bkgSprite->setPosition(SystemData::getLayoutPoint("forging_mainpanel_pos"));
	bkgSprite->setAnchorPoint(CCPointZero);
	addChild(bkgSprite);

	addCover();//保证点击事件

	//装备升级3个框
	CCSprite *pButton1n=SystemData::getSpriteByPlist("forging_base");
	CCSprite *pButton2n=SystemData::getSpriteByPlist("forging_base");
	pButton1n->setPosition(SystemData::getLayoutPoint("ZBSJ_button1_pos"));
	pButton2n->setPosition(SystemData::getLayoutPoint("ZBSJ_button2_pos"));
	addChild(pButton1n);
	addChild(pButton2n);

	CCLabelTTF* pSJWPK=SystemData::getLabelTTF("ZBSJ_QFRXYSJDZB");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1n->getPositionX(),pButton1n->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("ZBSJ_SJCL");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2n->getPositionX(),pButton2n->getPositionY()+50));
	addChild(pSJWPK);
	addChild(pSJCLK);

//	m_pRebornReq=SystemData::getSpriteByPlist("forging_base");
//	m_pRebornReq->setPosition(SystemData::getLayoutPoint("ZBSJ_button5_pos"));
//	addChild(m_pRebornReq,0);

//	m_pRebornName=SystemData::getLabelTTF("ZBSJ_ZZJJ");
//	m_pRebornName->setColor(ccc3(3,223,204));
//	m_pRebornName->setFontSize(18);
//	m_pRebornName->setPosition(ccp(m_pRebornReq->getPositionX(),m_pRebornReq->getPositionY()+50));
//	addChild(m_pRebornName,0);

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBSJ_smallborder_size.w"),SystemData::getLayoutValue("ZBSJ_smallborder_size.h"));
	pBorder->setPosition(SystemData::getLayoutPoint("ZBSJ_smallborder_pos"));
	addChild(pBorder); 
	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("ZBSJ_SJXGYL");
	pSJXGYL->setPosition(ccp(pBorder->getPositionX(),pBorder->getPositionY()+35));
	pSJXGYL->setFontSize(14);
	pSJXGYL->setColor(ccYELLOW);
	addChild(pSJXGYL);
	CCSprite *pButton3=SystemData::getSpriteByPlist("forging_result");
	pButton3->setPosition(SystemData::getLayoutPoint("ZBSJ_button4_pos"));
	addChild(pButton3);

	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(ZBSJpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("ZBSJ_button3_pos"));
	m_pTopList->addChild(pUpLevel);
	CCLabelTTF *pUpLevelLabel=SystemData::getLabelTTF("ZBSJ_upLevel");
	pUpLevelLabel->setFontSize(18);	
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(pUpLevelLabel);



	CCLabelTTF *pXYDJ=SystemData::getLabelTTF("ZBSJ_XYDJ");//需要金币
	pXYDJ->setFontSize(12);	
	pXYDJ->setColor(ccYELLOW);
	pXYDJ->setPosition(SystemData::getLayoutPoint("ZBSJ_label4_pos"));
	m_pReqLevel=SystemData::getLabelTTF("XXXXX");
	m_pReqLevel->setFontSize(14);	
	m_pReqLevel->setColor(ccRED);
	m_pReqLevel->setPosition(ccp(pXYDJ->getPositionX()+75,pXYDJ->getPositionY()));

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
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+75,m_pYuanBao->getPositionY()));

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);
	m_plock=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	m_plock->setTag(TAG_LOCK);
	m_plock->setHandler(this,menu_selector(ZBSJpanel::menuCallBack));
	m_plock->setPosition(SystemData::getLayoutPoint("ZBSJ_label3_pos"));
	m_pTopList->addChild(m_plock);

	m_pReqLevel->setAnchorPoint(CCPointZero);
	pXYDJ->setAnchorPoint(CCPointZero);
	//pTHYB->setAnchorPoint(CCPointZero);
	m_pYuanBao->setAnchorPoint(CCPointZero);
	m_pMoney->setAnchorPoint(CCPointZero);
	pXYJB->setAnchorPoint(CCPointZero);
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	addChild(pXYDJ);
	//addChild(pTHYB);
	addChild(m_pYuanBao);
	addChild(m_pMoney);
	addChild(pXYJB);
	addChild(m_pYuanBaoMoney);
	addChild(m_pReqLevel);
	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);
	m_pReqLevel->setVisible(false);

	//物品说明menu
	m_pBottomList=GeneralMenu::create();
	m_pBottomList->setPosition(CCPointZero);
	addChild(m_pBottomList);	

	CCScale9Sprite* pbottombkg = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_bottompanel_size.w"),SystemData::getLayoutValue("forging_bottompanel_size.h"));
	pbottombkg->setAnchorPoint(CCPointZero);
	pbottombkg->setPosition(SystemData::getLayoutPoint("forging_bottompanel_pos"));		
	addChild(pbottombkg);


	return true;
}


void ZBSJpanel::menuCallBack( CCObject *pSender )
{
	CCLOG("ZBSJpanel Press");
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
			
			rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_Upgrade,m_bLock,0,0,0);
			if (rvt==Error::Success)
			{
				if(!LuaData::checkIdExist("gdEquipUpgrade",m_pUserItem->sid))
				{
					CPEventHelper::uiNotify("","",Error::Item_MaxLvl);
					return;
				}
				
				// 设置冷却时间
				m_iTimeSpan = 3;
				
				if (m_bLock)
				{
					CommonFunction::sendmsgUpgrade(m_pUserItem->iid,1);		
				}
				else
				{
					CommonFunction::sendmsgUpgrade(m_pUserItem->iid);
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
			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pUserItem,TAG_Upgrade,0)).c_str());
			break;
			
		default:
// 			NotificationLua& nLua=NotificationLuaManager::Instance();
// 			nLua.showLog("no implement",Notification_RED);
			break;
		}
		
	}
}


cocos2d::CCSize ZBSJpanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(420, m_iHeight);
}

cocos2d::extension::CCTableViewCell* ZBSJpanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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
		LuaData::getProp("gddescription",1,"content",content);
		//CCLabelTTF* pLabel=CCLabelTTF::create(content.c_str(),"",16);
		CPRichText* pLabel = RichTextUtils::getRichText(content.c_str(),16,SystemData::getLayoutValue("forging_bottommenu_size.w"),0);
		pLabel->setPosition(CCPointZero);
		pLabel->setAnchorPoint(CCPointZero);
		//pLabel->setDimensions(CCSizeMake(SystemData::getLayoutValue("forging_bottommenu_size.w"),0));
		//pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLayer->addChild(pLabel);
		m_iHeight=pLabel->getContentSize().height;
	}
	return cell;
}

unsigned int ZBSJpanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void ZBSJpanel::SelectPos( CCObject *pObject )
{
	CCMenuItemImage *pItem=(CCMenuItemImage*)pObject;
	CCPoint Pos1=pItem->getPosition();
	CCPoint Pos=this->convertToNodeSpace(pItem->getPosition());
	CCLOG("x:%d,,,,y:%d",Pos.x,Pos.y);
}

void ZBSJpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		addItem(m_pUserItem);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		EffectSprite* pEffect=EffectSprite::create(Effect::effect_enhancefaild,1);
		//CCSprite* p=CommonFunction::getEffect(0);
		pEffect->setPosition(SystemData::getLayoutPoint("ZBSJ_button1_pos"));
		addChild(pEffect);
		AudioLoader::play(Sound::Effect::qianghuashibai);	
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		EffectSprite* pEffect=EffectSprite::create(Effect::effect_enhancesuccess,1);
		//CCSprite* p=CommonFunction::getEffect(1);
		pEffect->setPosition(SystemData::getLayoutPoint("ZBSJ_button1_pos"));
		addChild(pEffect);
		AudioLoader::play(Sound::Effect::qianghua);	
	}
}

void ZBSJpanel::addItem( UserItem* pUserItem )
{
	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		m_plock->setVisible(true);
		return;
	}
	m_pUserItem=pUserItem;

	if (m_pUserItem->type == ItemType_Equip_Magic_Weapon)
	{
		m_plock->setVisible(false);
	}
	else
	{
		m_plock->setVisible(true);
	}

	CCMenuItemImage* icon=CommonFunction::getItemIcon(pUserItem,false);
	icon->setPosition(SystemData::getLayoutPoint("ZBSJ_button1_pos"));	
	icon->setTarget(this,menu_selector(ZBSJpanel::ItemCallBack));
	m_pMenu->addChild(icon);


	if(!LuaData::checkIdExist("gdEquipUpgrade",m_pUserItem->sid))
	{
		return;
	}

	//加载相对应的item（材料，保护符，效果图）
	CCMenuItemImage* req =CommonFunction::getReqUpgradeItem(pUserItem);
	req->setPosition(SystemData::getLayoutPoint("ZBSJ_button2_pos"));
	req->setTarget(this,menu_selector(ZBSJpanel::ItemCallBack));
	m_pMenu->addChild(req);

	UserItem* pReq=(UserItem*)req->getUserData();
	if (pReq)
	{
		if (pUserItem->sid == pReq->sid)
		{
			m_plock->setVisible(false);
		}
		else
		{
			m_plock->setVisible(true);
		}
	}

	//加载升级后的预览物品
	CCMenuItemImage* UpgradeAft=CommonFunction::getTgtUpgradeItem(pUserItem);
	UpgradeAft->setTarget(this,menu_selector(ZBSJpanel::ItemCallBack));
	m_pMenu->addChild(UpgradeAft);

	int money;
	LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqGold",money);
	m_pMoney->setString(SystemData::intToString(money).c_str());
	if (HeroData::getProp(Entity::attr_money)<money)
	{
		m_pMoney->setColor(ccRED);
	}
	else
	{
		m_pMoney->setColor(ccWHITE);
	}

	int vcoin=CommonFunction::getReqVcoin(pUserItem,TAG_Upgrade,0);
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

	int m=-1;
	m_pReqLevel->setVisible(true);
	LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqEhLevel",m);
	m_pReqLevel->setString(SystemData::intToString(m).c_str());
	if (m<=pUserItem->data[ItemEquip::Item_EnhanceLevel])
	{
		m_pReqLevel->setColor(ccWHITE);
	}
	else
	{
		m_pReqLevel->setColor(ccRED);
	}

//	addRebornItemReq(pUserItem);
}

void ZBSJpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void ZBSJpanel::removeItem()
{
	m_pMenu->removeAllChildren();
	m_pUserItem=NULL;
	m_pMoney->setString("");
	m_pYuanBaoMoney->setString("");
	m_pReqLevel->setString("");
	m_plock->setVisible(true);
}

void ZBSJpanel::initContent()
{
//	m_pRebornReq->setVisible(false);
//	m_pRebornName->setVisible(false);

	CCTableViewEx *pTabelView=CCTableViewEx::create(this,SystemData::getLayoutSize("forging_bottommenu_size"),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(SystemData::getLayoutPoint("forging_bottommenu_pos"));
	pTabelView->reloadData();  
	addChild(pTabelView);

}


void ZBSJpanel::onEnter()
{
	BasePanel::onEnter();
	//initContent();
	this->runAction(CCSequence::create(CCDelayTime::create(0.02f),CCCallFunc::create(this,callfunc_selector(ZBSJpanel::initContent)),NULL));
}

void ZBSJpanel::onExit()
{
	BasePanel::onExit();
}


void ZBSJpanel::addRebornItemReq( UserItem* pUserItem )
{
	int rebornlvl=pUserItem->data[ItemEquip::Item_RebornLvl];
	if (rebornlvl==0)
	{
		//隐藏战争结晶
		m_pRebornReq->setVisible(false);
		m_pRebornName->setVisible(false);
		return;
	}

	//显示并且摆放战争结晶
	m_pRebornReq->setVisible(true);
	m_pRebornName->setVisible(true);

	int reqid=0;
	int reqcnt=0;
	LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"rebornreq",reqid);
	LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reborncnt",reqcnt);
	reqcnt=rebornlvl*2*reqcnt;
	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(CommonFunction::createNewItem(reqid),false);
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
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);
	reqItem->setTarget(this,menu_selector(ZBSJpanel::ItemCallBack));
	reqItem->setPosition(SystemData::getLayoutPoint("ZBSJ_button5_pos"));
	m_pMenu->addChild(reqItem);
}
