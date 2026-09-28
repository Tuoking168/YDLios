#include "ZBJDpanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "event/EventProtocol.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"

#include "userdata/netdata/GameRole.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/FloatPanelType.h"

#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"
#include "ext/CCTabelViewEx.h"

#include "CommonFunction.h"
#include "userdata/luadata/LuaData.h"
#include "script/LuaWrapper.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventHelper.h"
#include "userdata/HeroData.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "controls/CPCheckBox.h"
#include "res/AudioLoader.h"

ZBJDpanel::ZBJDpanel( void ):
	m_bflag(false),
	m_pMoney(NULL),
	m_pUserItem(NULL),
	m_pYuanBao(NULL),
	m_pYuanBaoMoney(NULL),
	m_pRoleItemCount(NULL),
	m_bLock(false),
	m_pScore(NULL),
	m_pTotalScore(NULL),
	m_iSuoCnt(0),
	m_pSuoItem(NULL),
	m_iHasSuoCnt(0),
	m_pSuoBkg(NULL),
	m_iLastSuoCnt(0),
	pSJWPK(NULL)
{
	for (int i=0;i<3;i++)
	{
		m_pblock[i]=NULL;
	}

}

ZBJDpanel::~ZBJDpanel( void )
{

}

ZBJDpanel* ZBJDpanel::create()
{
	ZBJDpanel* pPanel = new ZBJDpanel();
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

bool ZBJDpanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}

	m_block1=false;
	m_block2=false;
	m_block3=false;

	//装备升级界面背景
	CCScale9Sprite* bkgSprite = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_mainpanel_size.w"),SystemData::getLayoutValue("forging_mainpanel_size.h")+17);
	m_nWidth = bkgSprite->getContentSize().width;
	m_nHeight = bkgSprite->getContentSize().height;
	bkgSprite->setPosition(ccp(SystemData::getLayoutPoint("forging_mainpanel_pos").x,SystemData::getLayoutPoint("forging_mainpanel_pos").y-17));
	bkgSprite->setAnchorPoint(CCPointZero);
	addChild(bkgSprite);

	addCover();//保证点击事件


	//装备升级3个框

	CCSprite *pButton1n=SystemData::getSpriteByPlist("forging_base");
	CCSprite *pButton2n=SystemData::getSpriteByPlist("forging_base");
	pButton1n->setPosition(SystemData::getLayoutPoint("ZBJD_button1_pos"));
	pButton2n->setPosition(SystemData::getLayoutPoint("ZBJD_button2_pos"));
	addChild(pButton1n);
	addChild(pButton2n);

	pSJWPK=SystemData::getLabelTTF("ZBJD_QFRXYJDXZB");
	pSJWPK->setColor(ccc3(3,223,204));
	pSJWPK->setFontSize(18);
	pSJWPK->setPosition(ccp(pButton1n->getPositionX(),pButton1n->getPositionY()+50));
	CCLabelTTF* pSJCLK=SystemData::getLabelTTF("ZBJD_CLQX");
	pSJCLK->setColor(ccc3(3,223,204));
	pSJCLK->setFontSize(18);
	pSJCLK->setPosition(ccp(pButton2n->getPositionX(),pButton2n->getPositionY()+50));
	addChild(pSJWPK);
	addChild(pSJCLK);


	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("ZBJD_smallborder_size.w"),SystemData::getLayoutValue("ZBJD_smallborder_size.h"));
	pBorder->setPosition(SystemData::getLayoutPoint("ZBJD_smallborder_pos"));
	addChild(pBorder);

	// 标题背景
	CCPoint titlepos=SystemData::getLayoutPoint("ZBJD_title_pos");
	//初始化menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);


	m_pSuoBkg=SystemData::getSpriteByPlist("forging_base");
	m_pSuoBkg->setPosition(SystemData::getLayoutPoint("ZBJD_JDS_pos"));
	int suoid=SystemData::getLayoutValue("鉴定锁");
	m_pSuoItem=CommonFunction::getItemIconButDelete(CommonFunction::createNewItem(suoid),false);
	m_pSuoItem->setTarget(this,menu_selector(ZBJDpanel::ItemCallBack));
	m_iHasSuoCnt=getSuoCount();
	CCString *pStr=CCString::createWithFormat("%d/%d" , m_iHasSuoCnt, m_iSuoCnt);
	m_pRoleItemCount=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (m_iHasSuoCnt<m_iSuoCnt)
	{
		m_pRoleItemCount->setColor(ccRED);
	}
	m_pRoleItemCount->setPosition(ccp(m_pSuoItem->getContentSize().width/2,m_pSuoItem->getContentSize().height/2));
	m_pSuoItem->addChild(m_pRoleItemCount);
	m_pSuoItem->setPosition(SystemData::getLayoutPoint("ZBJD_JDS_pos"));
	m_pSuoItem->setVisible(false);
	m_pSuoBkg->setVisible(false);
	m_pTopList->addChild(m_pSuoBkg);
	m_pTopList->addChild(m_pSuoItem);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCLabelTTF* pSJXGYL=SystemData::getLabelTTF("ZBJD_JDQK");
	pSJXGYL->setAnchorPoint(ccp(0,0.5));
	pSJXGYL->setPosition(ccp(titlepos.x-70,titlepos.y));
	pSJXGYL->setFontSize(18);
	pSJXGYL->setColor(ccWHITE);
	m_pTopList->addChild(pSJXGYL);

	for (int i=1;i<=3;i++)
	{
		CCPoint pos=ccp(titlepos.x-10,titlepos.y-i*35);
		m_pblock[i-1]=SystemData::getLabelTTF("XXXXX");
		m_pblock[i-1]->setAnchorPoint(ccp(0.5,0.5));
		m_pblock[i-1]->setPosition(pos); 
		m_pblock[i-1]->setFontSize(16);
		m_pblock[i-1]->setColor(ccWHITE);
		m_pTopList->addChild(m_pblock[i-1]);

		//锁定框
		CCMenuItemImage *plock=SystemData::getMenuItemImageByPlist("forging_unlock");
		plock->setTarget(this,menu_selector(ZBJDpanel::menuCallBack));
		plock->setTag(100+i);
		plock->setPosition(ccp(m_pblock[i-1]->getPositionX()+110,m_pblock[i-1]->getPositionY()));
		m_pTopList->addChild(plock);
		plock->setVisible(false);
		plock->setSelectedImage(SystemData::getSpriteByPlist("forging_lock"));
	}

	// 升级按钮
	CCMenuItemImage *pUpLevel=SystemData::getMenuItemImageByPlist("forging_button3");
	pUpLevel->setTag(TAG_UPGRADE);
	pUpLevel->setTarget(this,menu_selector(ZBJDpanel::menuCallBack));
	pUpLevel->setPosition(SystemData::getLayoutPoint("ZBJD_button3_pos"));
	m_pTopList->addChild(pUpLevel);
	m_pButtonLabel=SystemData::getLabelTTF("ZBJD_JD");
	m_pButtonLabel->setFontSize(18);	
	m_pButtonLabel->setColor(ccWHITE);
	m_pButtonLabel->setPosition(pUpLevel->getPosition());
	m_pTopList->addChild(m_pButtonLabel);



	CCLabelTTF *pXYJB=SystemData::getLabelTTF("ZBSJ_XYJB");//需要金币
	pXYJB->setFontSize(12);	
	pXYJB->setColor(ccYELLOW);
	pXYJB->setPosition(ccp(SystemData::getLayoutPoint("ZBSJ_label1_pos").x,SystemData::getLayoutPoint("ZBSJ_label1_pos").y));
	pXYJB->setAnchorPoint(CCPointZero);
	addChild(pXYJB);
	m_pMoney=SystemData::getLabelTTF("XXXXX");
	m_pMoney->setFontSize(14);	
	m_pMoney->setColor(ccYELLOW);
	m_pMoney->setPosition(ccp(pXYJB->getPositionX()+100,pXYJB->getPositionY()));
	m_pMoney->setAnchorPoint(CCPointZero);
	addChild(m_pMoney);


	m_pYuanBao=SystemData::getLabelTTF("ZBSJ_CLJB");//需要元宝
	m_pYuanBao->setFontSize(12);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(ccp(SystemData::getLayoutPoint("ZBSJ_label1_pos").x,SystemData::getLayoutPoint("ZBSJ_label1_pos").y-15));
	m_pYuanBao->setAnchorPoint(CCPointZero);
	addChild(m_pYuanBao);
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setFontSize(14);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+100,m_pYuanBao->getPositionY()));
	m_pYuanBaoMoney->setAnchorPoint(CCPointZero);
	addChild(m_pYuanBaoMoney);

	CCLabelTTF *plabel=SystemData::getLabelTTF("ZBJD_ZBJDJF");//装备鉴定积分
	plabel->setFontSize(12);	
	plabel->setColor(ccYELLOW);
	plabel->setPosition(ccp(SystemData::getLayoutPoint("ZBSJ_label1_pos").x,SystemData::getLayoutPoint("ZBSJ_label1_pos").y-30));
	plabel->setAnchorPoint(CCPointZero);
	addChild(plabel);
	m_pScore=CCLabelTTF::create(SystemData::intToString(HeroData::getProp(Entity::attr_evaluate_grade)).c_str(),"",14);
	m_pScore->setFontSize(14);	
	m_pScore->setColor(ccYELLOW);
	m_pScore->setPosition(ccp(plabel->getPositionX()+100,plabel->getPositionY()));
	m_pScore->setAnchorPoint(CCPointZero);
	addChild(m_pScore);

	CCLabelTTF *pTotallabel=SystemData::getLabelTTF("ZBJD_NDJDJF");//玩家鉴定积分
	pTotallabel->setFontSize(12);	
	pTotallabel->setColor(ccYELLOW);
	pTotallabel->setPosition(ccp(SystemData::getLayoutPoint("ZBSJ_label1_pos").x,SystemData::getLayoutPoint("ZBSJ_label1_pos").y-45));
	pTotallabel->setAnchorPoint(CCPointZero);
	addChild(pTotallabel);
	m_pTotalScore=CCLabelTTF::create(SystemData::intToString(HeroData::getProp(Entity::attr_evaluate_grade)).c_str(),"",14);
	m_pTotalScore->setFontSize(14);	
	m_pTotalScore->setColor(ccYELLOW);
	m_pTotalScore->setPosition(ccp(pTotallabel->getPositionX()+100,pTotallabel->getPositionY()));
	m_pTotalScore->setAnchorPoint(CCPointZero);
	addChild(m_pTotalScore);

	CCLabelTTF *pTHYB=SystemData::getLabelTTF("ZBSJ_CLBZYBDT");//换元宝
	pTHYB->setFontSize(12);	
	pTHYB->setColor(ccYELLOW);


	CPCheckBox* plock=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pTHYB);;
	plock->setTag(TAG_LOCK);
	plock->setHandler(this,menu_selector(ZBJDpanel::menuCallBack));
	plock->setPosition(SystemData::getLayoutPoint("ZBSJ_label3_pos"));
	m_pTopList->addChild(plock);
	

	//pTHYB->setAnchorPoint(CCPointZero);

	//addChild(pTHYB);

	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);
		
	//物品说明menu
	m_pBottomList=GeneralMenu::create();
	m_pBottomList->setPosition(CCPointZero);
	addChild(m_pBottomList);	

	CCScale9Sprite* pbottombkg = SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_bottompanel_size.w"),SystemData::getLayoutValue("forging_bottompanel_size.h")-17);
	pbottombkg->setAnchorPoint(CCPointZero);
	pbottombkg->setPosition(SystemData::getLayoutPoint("forging_bottompanel_pos"));		
	addChild(pbottombkg);
	

	return true;
}

cocos2d::CCSize ZBJDpanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(420, m_iHeight);
}

cocos2d::extension::CCTableViewCell* ZBJDpanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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
		LuaData::getProp("gddescription",3,"content",content);
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

unsigned int ZBJDpanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}


void ZBJDpanel::menuCallBack( CCObject *pSender )
{
	CCLOG("ZBJDpanel Press");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		CCMenuItemImage* pItem=NULL;
		int tag = pNode->getTag();
		if (tag>100 && tag<200)//点击的锁定框
		{
			pItem=(CCMenuItemImage*)m_pTopList->getChildByTag(tag);
			int j=tag%100;
			switch (j)
			{
			case 1:
				if (m_block1)
				{
					m_block1=false;
					pItem->unselected();
				}
				else
				{
					m_block1=true;
					pItem->selected();
				}
				break;
			case 2:
				if (m_block2)
				{
					m_block2=false;
					pItem->unselected();
				}
				else
				{
					m_block2=true;
					pItem->selected();
				}
				break;
			case 3:
				if (m_block3)
				{
					m_block3=false;
					pItem->unselected();
				}
				else
				{
					m_block3=true;
					pItem->selected();
				}
				break;			
			default:
				break;
			}
		}
		int rvt=0;
		updateSuoCount();
		switch (tag)
		{		
		case TAG_UPGRADE:			
			rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(m_pUserItem,TAG_Evaluate,m_bLock,m_iSuoCnt,0,0);
			if (rvt==Error::Success)
			{
				if (m_bflag)
				{
					if (m_bLock)
					{
						CommonFunction::sendmsgEvaluate(m_pUserItem->iid,1);
					}
					else
					{
						CommonFunction::sendmsgEvaluate(m_pUserItem->iid);
					}
				}
				else
				{
					FloatPanel* panel=FloatPanel::create(FloatPanelType::Item_ZBQX);
					panel->setPosition(ccp(200,150));
					panel->setHandler(this,floatpanel_selector(ZBJDpanel::postClearMsg));
					addChild(panel);					
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
			break;
		default:
			break;
		}
	}
	if (!m_bflag)
	{
		int i=0;
		if (m_block1)	
			i++;
		if (m_block2)	
			i++;
		if (m_block3)	
			i++;

		int vcoin=CommonFunction::getReqVcoin(m_pUserItem,TAG_Evaluate,i);
		if (i > 0)
		{
			int suoID = SystemData::getLayoutValue("鉴定锁");
			int suoCnt = GameData::s_user->getUserItemData()->getItemCntBySid(suoID,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);
			if (suoCnt < i)
			{
				int shopprice = 0;
				LuaData::getProp("gdItems",suoID,"shopprice",shopprice);
				vcoin = vcoin + (i - suoCnt) * shopprice ;
			}

		}
		m_pYuanBaoMoney->setString(SystemData::intToString(vcoin).c_str());
	}
	
}


void ZBJDpanel::addItem(UserItem* pUserItem)
{
	for(int i=1;i<=3;i++)
	{
		m_pTopList->getChildByTag(100+i)->setVisible(false);
	}
	if (m_pUserItem)
	{
		if (pUserItem->iid!=m_pUserItem->iid)
		{
			m_iLastSuoCnt = 0;
		}
	}
	
	m_pSuoItem->setVisible(false);
	m_pSuoBkg->setVisible(false);
	m_bflag=false;
	m_pMenu->removeAllChildren();
	if (pUserItem==NULL)
	{
		return;
	}
	m_pUserItem=pUserItem;
	CCMenuItemImage* icon=CommonFunction::getItemIcon(pUserItem,false);	
	icon->setPosition(SystemData::getLayoutPoint("ZBJD_button1_pos"));	
	icon->setTarget(this,menu_selector(ZBJDpanel::ItemCallBack));
	m_pMenu->addChild(icon);

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
	if (number!=3)
	{
		m_bflag=true;
		pSJWPK->setString(SystemData::getLayoutString("ZBJD_QFRXYJDXZB").c_str());
	}
	else
	{
		pSJWPK->setString(SystemData::getLayoutString("ZBJD_QFRXYSQXZB").c_str());
	}
	for (n;(int)((int)combo>>(n*8) & 255)!=0;n++)
	{
		int x=(int)((int)combo>>(n*8) & 255);
		std::string name;
		int type=0;
		LuaData::getProp("gdEquipEvaluate",x,"name",name);
		LuaData::getProp("gdEquipEvaluate",x,"attrtype",type);
		float combovalue;
		CCString* pStr;
		if (type==Combat::prop_Death_Recovery_Percent || type==Combat::prop_Health_Recovery_Point || type==Combat::prop_Magic_Recovery_Point || type==Combat::prop_Posion_Recovery_Point || type==Combat::prop_Magic_Hit|| type==Combat::prop_Magic_Dodge || type==Combat::prop_Posion_Dodge)
		{
			combovalue=(float)pUserItem->data[ItemEquip::Item_DataX+n];
			combovalue=combovalue/100;
			pStr=CCString::createWithFormat("%s:+%.2f%%",name.c_str(),combovalue);
		}
		else
		{
			pStr=CCString::createWithFormat("%s:+%d",name.c_str(),pUserItem->data[ItemEquip::Item_DataX+n]);
		}if (n<3)
		{
			m_pblock[n]->setString(pStr->getCString());
		}
	}
	if (n==3)
	{
		for(int i=1;i<=3;i++)
		{
			m_pTopList->getChildByTag(100+i)->setVisible(true);
		}
	}
	for (n;n<3;n++)
	{
		m_pblock[n]->setString(SystemData::getLayoutString("ItemTips_WJD").c_str());
	}
	
	//加载相对应的item（材料，保护符，效果图）
	CCMenuItemImage* req =CommonFunction::getReqEvaluateItem(pUserItem);
	req->setPosition(SystemData::getLayoutPoint("ZBJD_button2_pos"));
	req->setTarget(this,menu_selector(ZBJDpanel::ItemCallBack));
	m_pMenu->addChild(req);

	if (m_bflag)
	{
		m_pButtonLabel->setString(SystemData::getLayoutString("ZBJD_JD").c_str());
	}
	else
	{
		m_pButtonLabel->setString(SystemData::getLayoutString("ZBJD_QX").c_str());
	}
	InitBlock();

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

	int i=0;
	if (!m_bflag)
	{				
		if (m_block1)	
			i++;
		if (m_block2)	
			i++;
		if (m_block3)	
			i++;
	}

	int vcoin=CommonFunction::getReqVcoin(pUserItem,TAG_Evaluate,i);
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
	m_pMoney->setString("1000");
	m_pTotalScore->setString(SystemData::intToString(HeroData::getProp(Entity::attr_evaluate_grade)).c_str());
	if (m_pUserItem)
	{
		m_pScore->setString(SystemData::intToString(m_pUserItem->data[ItemEquip::Item_EvaluateCount]).c_str());
	}
	else
	{
		m_pScore->setString("0");
	}
}

void ZBJDpanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		addItem(m_pUserItem);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		//CCSprite* p=CommonFunction::getEffect(0);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancefaild,1);
		p->setPosition(SystemData::getLayoutPoint("ZBJD_button1_pos"));
		addChild(p);
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		//CCSprite* p=CommonFunction::getEffect(1);
		EffectSprite* p=EffectSprite::create(Effect::effect_enhancesuccess,1);
		p->setPosition(SystemData::getLayoutPoint("ZBJD_button1_pos"));
		addChild(p);
		AudioLoader::play(Sound::Effect::jianding);	
	}

	updateSuoCount();

	m_pTotalScore->setString(SystemData::intToString(HeroData::getProp(Entity::attr_evaluate_grade)).c_str());
	if (m_pUserItem)
	{
		m_pScore->setString(SystemData::intToString(m_pUserItem->data[ItemEquip::Item_EvaluateCount]).c_str());
	}
	else
	{
		m_pScore->setString("0");
	}
}

void ZBJDpanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void ZBJDpanel::InitBlock()
{
	m_block1=false;
	m_block2=false;
	m_block3=false;
	switch (m_iLastSuoCnt)
	{
	case 1:
		m_block1 = true;
		break;
	case 2:
		m_block1=true;
		m_block2=true;
		break;
	case 3:
		m_block1=true;
		m_block2=true;
		m_block3=true;
		break;
	default:
		break;
	}
	for (int i=101;i<=103;i++)
	{
		CCMenuItemImage* pItem=(CCMenuItemImage*)m_pTopList->getChildByTag(i);
		if ((m_block1 && i==101) || (m_block2 && i==102) || (m_block3 && i==103))
		{
			pItem->selected();	
		}
		else
		{
			pItem->unselected();
		}
	}
}

void ZBJDpanel::removeItem()
{
	m_pMenu->removeAllChildren();
	m_pUserItem=NULL;
	m_pMoney->setString("");
	m_pYuanBaoMoney->setString("");
	m_iLastSuoCnt = 0;
	InitBlock();

	pSJWPK->setString(SystemData::getLayoutString("ZBJD_QFRXYJDXZB").c_str());
}

void ZBJDpanel::initContent()
{
	CCTableViewEx *pTabelView=CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("forging_bottommenu_size").width,SystemData::getLayoutSize("forging_bottommenu_size").height-17),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(SystemData::getLayoutPoint("forging_bottommenu_pos"));
	pTabelView->reloadData();  
	addChild(pTabelView);
}


void ZBJDpanel::onEnter()
{
	BasePanel::onEnter();
	this->runAction(CCSequence::create(CCDelayTime::create(0.08f),CCCallFunc::create(this,callfunc_selector(ZBJDpanel::initContent)),NULL));
}

void ZBJDpanel::onExit()
{
	BasePanel::onExit();
}

void ZBJDpanel::postClearMsg(int i)
{
	m_iLastSuoCnt = m_iSuoCnt;
	if (i==0)
	{
		if (m_bLock)
		{
			CommonFunction::sendmsgClearItem(m_pUserItem->iid, (int)m_block1, (int)m_block2, (int)m_block3,1);
		}
		else
		{
			CommonFunction::sendmsgClearItem(m_pUserItem->iid, (int)m_block1, (int)m_block2, (int)m_block3);
		}
	}
	
}

int ZBJDpanel::getSuoCount()
{
	int count=0;
	int suoid=SystemData::getLayoutValue("鉴定锁");
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->sid==suoid)
		{
			count+=pItem->count;
		}
	}	
	return count;
}

void ZBJDpanel::updateSuoCount()
{
	int i=0;
	if (m_block1)	
		i++;
	if (m_block2)	
		i++;
	if (m_block3)	
		i++;

	m_iSuoCnt=i;
	m_iHasSuoCnt=getSuoCount();
	if (m_iSuoCnt!=0)
	{
		CCString *pStr=CCString::createWithFormat("%d/%d" , m_iHasSuoCnt, m_iSuoCnt);
		m_pRoleItemCount->setString(pStr->getCString());
		m_pSuoItem->setVisible(true);
		m_pSuoBkg->setVisible(true);
		if (m_iHasSuoCnt<m_iSuoCnt)
		{
			m_pRoleItemCount->setColor(ccRED);
		}
	}
	else
	{
		m_pSuoItem->setVisible(false);
		m_pSuoBkg->setVisible(false);
	}
}
