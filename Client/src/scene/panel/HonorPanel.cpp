#include "HonorPanel.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "ext/CCMenuItemFontEx.h"
#include "ext/GeneralMenu.h"
#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "ext/CCMenuEx.h"
#include "ext/TouchCover.h"
#include "script/LuaWrapper.h"
#include "MsgPlayer.h"

#include "event/EventProtocol.h"
#include "controls/CPNodeHelper.h"
#include "event/CPEventHelper.h"
#include "event/CPEvent.h"
#include "EntityDefinition.h"
#include "userdata/HeroData.h"

#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventDispatcher.h"
#include "logic/TimeManager.h"
#include "utils/StringUtils.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "functionPanel/BuffExPanel.h"
#include "UserData/ActivityData.h"

HonorPanel::HonorPanel():
	m_iCurHonorlvl(0),
	m_pLeftMenu(NULL),
	m_pRightMenu(NULL),
	m_pHonorLabel(NULL),
	m_pTabelView(NULL),
	m_pCurItemSprite(NULL),
	m_pCurHonorTime(NULL),
	m_bLeftOver(true),
	m_bRightOver(true),
	m_pMainMenu(NULL),
	m_iCurSelectRange(-1),
	m_bUpgrade(false),
	m_iTime(0),
	m_iTimeSpan(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
}

HonorPanel::~HonorPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
}

bool HonorPanel::init( const char* filename ) 
{
	m_iCurHonorlvl=HeroData::getProp(Entity::attr_honor_curmax);
	//顶上标题
	//CCLabelTTF* pBigLabel=CCLabelTTF::create(AToU8("荣    誉"),"微软雅黑",22);
	CCSprite* pBigLabel=SystemData::getSpriteByPlist("Honor_title");
	pBigLabel->setPosition(SystemData::getLayoutPoint("Honor_bigtitle_pos"));
	addChild(pBigLabel);

	//2个花纹
	CCSprite* phuawen1=SystemData::getSpriteByPlist("Honor_flower");
	phuawen1->setPosition(SystemData::getLayoutPoint("Honor_flower1"));
	addChild(phuawen1);
	CCSprite* phuawen2=SystemData::getSpriteByPlist("Honor_flower");
	phuawen2->runAction(CCFlipX::create(true));
	phuawen2->setPosition(SystemData::getLayoutPoint("Honor_flower2"));
	addChild(phuawen2);

	//最外层框
	CCScale9Sprite* pBigBorder=SystemData::getScale9SpriteByPlist("Honor_border",SystemData::getLayoutValue("Honor_bigborder_size.w"),SystemData::getLayoutValue("Honor_bigborder_size.h"));
	pBigBorder->setAnchorPoint(CCPointZero);
	pBigBorder->setPosition(ccp(5,5));
	addChild(pBigBorder);

	//内层层框
	CCScale9Sprite* pSmallBorder=SystemData::getScale9SpriteByPlist("Honor_smallborder",SystemData::getLayoutValue("Honor_smallborder_size.w"),SystemData::getLayoutValue("Honor_smallborder_size.h"));
	pSmallBorder->setAnchorPoint(CCPointZero);
	pSmallBorder->setPosition(ccp(10,55));
	addChild(pSmallBorder);

	//分隔条
	CCSprite* pline=SystemData::getSpriteByPlist("Honor_fengetiao");
	pline->setScaleX(1.4f);
	pline->runAction(CCRotateBy::create(0,90));
	pline->setPosition(SystemData::getLayoutPoint("Honor_fengetiao_pos"));
	addChild(pline);

	//左右箭头
	CCSprite* pItemLeft=SystemData::getSpriteByPlist("Honor_jiantou");
	pItemLeft->setScale(0.8f);
	pItemLeft->setPosition(SystemData::getLayoutPoint("Honor_zuojiantou_pos"));
	addChild(pItemLeft);
	CCSprite* pItemRight=SystemData::getSpriteByPlist("Honor_jiantou");
	pItemRight->setScale(0.8f);
	pItemRight->runAction(CCFlipX::create(true));
	pItemRight->setPosition(SystemData::getLayoutPoint("Honor_youjiantou_pos"));
	addChild(pItemRight);

	// 顶部按钮
	m_pTabelView=CCTableViewEx::create(this,SystemData::getLayoutSize("Honor_tabelview_size"),kCCScrollViewDirectionHorizontal,this,NULL);
	m_pTabelView->setVerticalFillOrder(kCCTableViewFillBottomUp);
	m_pTabelView->setAnchorPoint(CCPointZero);
	m_pTabelView->setIsadjust(true);
	m_pTabelView->setShouldAddSpeed(true);
	m_pTabelView->setPosition(SystemData::getLayoutPoint("Honor_tabelview_pos"));
	m_pTabelView->reloadData();  
	addChild(m_pTabelView);

	m_pMainMenu=GeneralMenu::create();
	m_pMainMenu->setAnchorPoint(CCPointZero);
	m_pMainMenu->setPosition(CCPointZero);
	addChild(m_pMainMenu);
	initButton();

	//m_iTime=HeroData::getProp(Entity::attr_honor_cur);
	getSubLeftPanel(HeroData::getProp(Entity::attr_honor_curmax));
	int size=0;
	LuaData::getProp_size("gdHonor",0,"",size);
	if (HeroData::getProp(Entity::attr_honor_curmax)==size)
	{
		getSubRightPanel(size);
	}
	else
	{
		getSubRightPanel(HeroData::getProp(Entity::attr_honor_curmax)+1);
	}
	//当前荣誉
	CCLabelTTF* pCorner=SystemData::getLabelTTF("Honor_text4");
	pCorner->setFontSize(18);
	pCorner->setColor(ccORANGE);
	pCorner->setAnchorPoint(ccp(0,0.5));
	pCorner->setPosition(ccp(300,362));
	addChild(pCorner);

	m_pHonorLabel=CCLabelTTF::create(SystemData::intToString(GameData::s_user->m_pMainRole->Honour).c_str(),"微软雅黑",18);
	m_pHonorLabel->setAnchorPoint(ccp(0,0.5));
	m_pHonorLabel->setColor(ccORANGE);
	m_pHonorLabel->setPosition(ccp(pCorner->getPositionX()+pCorner->getContentSize().width,pCorner->getPositionY()));
	addChild(m_pHonorLabel);


	//当前元宝
	CCLabelTTF* pCurGold=SystemData::getLabelTTF("Honor_text5");
	pCurGold->setFontSize(18);
	pCurGold->setColor(ccORANGE);
	pCurGold->setAnchorPoint(ccp(0,0.5));
	pCurGold->setPosition(ccp(500,362));
	addChild(pCurGold);

	m_pGoldLabel=CCLabelTTF::create(SystemData::intToString(HeroData::getProp(Entity::attr_gold)).c_str(),"微软雅黑",18);
	m_pGoldLabel->setAnchorPoint(ccp(0,0.5));
	m_pGoldLabel->setColor(ccORANGE);
	m_pGoldLabel->setPosition(ccp(pCurGold->getPositionX()+pCurGold->getContentSize().width,pCurGold->getPositionY()));
	addChild(m_pGoldLabel);	

	if (m_iCurHonorlvl+4>=size)
	{
		m_pTabelView->setCurPageWithInit(m_iCurHonorlvl-8); 
	}
	else
	{
		m_pTabelView->setCurPageWithInit(m_iCurHonorlvl-4);
	}
	return true; 
}

HonorPanel* HonorPanel::create()
{
	HonorPanel* pPanel = new HonorPanel();
	if(pPanel && pPanel->init(""))
	{
		pPanel->autorelease();
		return pPanel;
	}
	else
	{

		if (pPanel)
		{
			delete pPanel;
		}
		CCLog("HonorPanel create failed!");
	}
	return NULL;
}

void HonorPanel::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (CPEventHelper::getEventSource() == "HandleMessageUpdPlayerPropsDataNotify")
		{
			if (CPEventHelper::getEventIntData(CPEventData::VALUE_2)==Entity::attr_honor_curmax)
			{
				m_iTime=HeroData::getProp(Entity::attr_honor_cur);
				m_bUpgrade=true;
				m_iCurHonorlvl=HeroData::getProp(Entity::attr_honor_curmax);
				getSubLeftPanel(m_iCurHonorlvl);
				int size=0;
				LuaData::getProp_size("gdHonor",0,"",size);
				if (m_iCurHonorlvl==size)
				{
					getSubRightPanel(size);
				}
				else
				{
					getSubRightPanel(m_iCurHonorlvl+1);
				}
				m_pTabelView->reloadData();  
				if (m_iCurHonorlvl+4>=size)
				{
					m_pTabelView->setCurPageWithInit(m_iCurHonorlvl-8); 
				}
				else
				{
					m_pTabelView->setCurPageWithInit(m_iCurHonorlvl-4);
				}
				/*EffectSprite* p=EffectSprite::create(Effect::effect_honorupgrade);
				p->setPosition(ccp(m_pCurItemSprite->getContentSize().width/2,m_pCurItemSprite->getContentSize().height/2));
				m_pCurItemSprite->addChild(p);*/
			}
			else if(CPEventHelper::getEventIntData(CPEventData::VALUE_2)==Entity::attr_honor_cur)
			{
				//HeroData::setProp(Entity::attr_honor_cur,7200+m_iTime);
				m_iTime=HeroData::getProp(Entity::attr_honor_cur);
				getSubLeftPanel(m_iCurHonorlvl);
				EffectSprite* p=EffectSprite::create(Effect::effect_honoropen,1);
				p->setAnchorPoint(CCPointZero);
				p->setPosition(ccp(SystemData::getLayoutPoint("Honor_border1_pos").x-14,SystemData::getLayoutPoint("Honor_border1_pos").y-12));
				m_pLeftMenu->addChild(p);
			}
			m_pHonorLabel->setString(SystemData::intToString(GameData::s_user->m_pMainRole->Honour).c_str());
			m_pGoldLabel->setString(SystemData::intToString(HeroData::getProp(Entity::attr_gold)).c_str());
		}
	}
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			updatetime(1);
			Update();
		}
	}
}

void HonorPanel::handleEvent( int channel )
{
	if (channel==EventProtocol::EVENT_MAXHONOR_UPDDATA)
	{
		m_iCurHonorlvl=HeroData::getProp(Entity::attr_honor_curmax);
		getSubLeftPanel(m_iCurHonorlvl);
		int size=0;
		LuaData::getProp_size("gdHonor",0,"",size);
		if (m_iCurHonorlvl==size)
		{
			getSubRightPanel(size);
		}
		else
		{
			getSubRightPanel(m_iCurHonorlvl+1);
		}
		m_pTabelView->reloadData();  
		EffectSprite* p=EffectSprite::create(Effect::effect_honorupgrade,5);
		p->setPosition(ccp(400,240));
		addChild(p);
		m_iTime=HeroData::getProp(Entity::attr_honor_cur);
	}
	if (channel==EventProtocol::EVENT_CURHONOR_UPDDATA)
	{
		//HeroData::setProp(Entity::attr_honor_cur,7200+m_iTime);
		m_iTime=HeroData::getProp(Entity::attr_honor_cur);
		getSubLeftPanel(HeroData::getProp(Entity::attr_honor_cur));
		//getSubRightPanel(HeroData::getProp(Entity::attr_honor_curmax)+1);
		m_pTabelView->reloadData();  
	}

	m_pHonorLabel->setString(SystemData::intToString(GameData::s_user->m_pMainRole->Honour).c_str());
}

cocos2d::CCSize HonorPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(83,55);
}

cocos2d::extension::CCTableViewCell* HonorPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		CCMenuEx* pMenu = CCMenuEx::create(NULL,NULL);
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		std::string name;
		LuaData::getProp("gdHonor",idx+1,"name",name);
		CCLabelTTF* pLabel=CCLabelTTF::create(name.c_str(),"微软雅黑",18);
		pLabel->setDimensions(CCSizeMake(40,0));
		pLabel->setAnchorPoint(ccp(0.5,0.5));
		CCMenuItemSprite* pItem=NULL;
		if (HeroData::getProp(Entity::attr_honor_curmax)<idx+1)
		{
			CCScale9Sprite* pSprite1=SystemData::getScale9SpriteByPlist("Honor_button2_huise",75,55);
			CCScale9Sprite* pSprite2=SystemData::getScale9SpriteByPlist("Honor_button2_huise",75,55);
			pItem=CCMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(HonorPanel::buttonCallBack));
		}
		else
		{
			CCScale9Sprite* pSprite1=SystemData::getScale9SpriteByPlist("Honor_button2",75,55);
			CCScale9Sprite* pSprite2=SystemData::getScale9SpriteByPlist("Honor_button2.sel",75,55);
			pItem=CCMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(HonorPanel::buttonCallBack));
		}
		pItem->setPosition(CCPointZero);
		pItem->setAnchorPoint(CCPointZero);
		pItem->setTag(idx+1);
		pLabel->setPosition(ccp(pItem->getContentSize().width/2,pItem->getContentSize().height/2));
		pItem->addChild(pLabel);
		pMenu->addChild(pItem);

		CCScale9Sprite* pbuttonborder=SystemData::getScale9SpriteByPlist("Honor_buttonborder",80,58);
		//CCSprite* pbuttonborder=SystemData::getSprite("Honor_buttonborder"); 
		pbuttonborder->setPosition(ccp(pItem->getContentSize().width/2,pItem->getContentSize().height/2));
		pbuttonborder->setTag(100);
		pbuttonborder->setVisible(false);
		pItem->addChild(pbuttonborder);
		if (HeroData::getProp(Entity::attr_honor_curmax)==idx && m_iCurSelectRange==-1 )
		{
			pbuttonborder->setVisible(true);
			m_pCurItemSprite=pItem;
		}
		else if((m_iCurSelectRange-1)==idx && m_iCurSelectRange!=-1)
		{
			pbuttonborder->setVisible(true);
			m_pCurItemSprite=pItem;
		}	

		if (HeroData::getProp(Entity::attr_honor_curmax)==(idx+1) && m_bUpgrade)
		{
			EffectSprite* p=EffectSprite::create(Effect::effect_honorupgrade,1);
			p->setPosition(ccp(pItem->getContentSize().width/2,pItem->getContentSize().height/2));
			pItem->addChild(p);
			m_bUpgrade=false;
		}
	}
	return cell;
}

unsigned int HonorPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	int count;
	LuaData::getProp_size("gdHonor",0,"",count); 
	return count;
}

std::string strtitle[8]={
	"Honor_content_text1","Honor_content_text2","Honor_content_text3","Honor_content_text4","Honor_content_text5","Honor_content_text6","Honor_content_text7","Honor_content_text8"
};

void HonorPanel::getSubLeftPanel( int curHonorlvl)
{
	m_bLeftOver=false;
	if (m_pLeftMenu)
	{
		m_pLeftMenu->removeAllChildren();
	}
	else
	{
		m_pLeftMenu=GeneralMenu::create();
		m_pLeftMenu->setPosition(CCPointZero);
		m_pLeftMenu->setAnchorPoint(CCPointZero);
		addChild(m_pLeftMenu);
	}
	//标题
	CCSprite* pTitle=SystemData::getSpriteByPlist("Honor_titlebkg");
	pTitle->setPosition(SystemData::getLayoutPoint("Honor_title1_pos"));	
	m_pLeftMenu->addChild(pTitle);

	CCLabelTTF* pTitletext=SystemData::getLabelTTF("Honor_title_text1");
	pTitletext->setFontSize(16);
	pTitletext->setColor(ccWHITE);
	pTitletext->setPosition(SystemData::getLayoutPoint("Honor_title1_pos"));
	m_pLeftMenu->addChild(pTitletext);

	//荣誉状态
	CCLabelTTF* ptext1=SystemData::getLabelTTF("Honor_text1");
	ptext1->setFontSize(16);
	ptext1->setColor(ccORANGE);
	ptext1->setAnchorPoint(ccp(0,0.5));
	ptext1->setPosition(SystemData::getLayoutPoint("Honor_text1_left_pos"));
	m_pLeftMenu->addChild(ptext1);

	//需要荣誉
	int reqHonor=0;
	LuaData::getProp("gdHonor",curHonorlvl,"openreq",reqHonor);
	CCLabelAtlas* pReq=CCLabelAtlas::create(SystemData::intToString(reqHonor).c_str(), SystemData::getLayoutString("ui.attribute_panel.num").c_str(), 17, 20, '0');
	pReq->setAnchorPoint(ccp(0,0.5));
	pReq->setScale(0.8);
	pReq->setPosition(ccp(ptext1->getPositionX()+ptext1->getContentSize().width,ptext1->getPositionY()));
	m_pLeftMenu->addChild(pReq);

	CCLabelTTF* phonor=SystemData::getLabelTTF("Honor_text");
	phonor->setFontSize(16);
	phonor->setColor(ccORANGE);
	phonor->setAnchorPoint(ccp(0,0.5));
	phonor->setPosition(ccp(ptext1->getPositionX()+ptext1->getContentSize().width+pReq->getContentSize().width*pReq->getScale(),ptext1->getPositionY()));
	m_pLeftMenu->addChild(phonor);

	//需要元宝
	int reqGold=0;
	LuaData::getProp("gdHonor",curHonorlvl,"openreqgold",reqGold);
	CCLabelAtlas* pReqGold=CCLabelAtlas::create(SystemData::intToString(reqGold).c_str(), SystemData::getLayoutString("ui.attribute_panel.num").c_str(), 17, 20, '0');
	pReqGold->setAnchorPoint(ccp(0,0.5));
	pReqGold->setScale(0.8);
	pReqGold->setPosition(ccp(phonor->getPositionX()+phonor->getContentSize().width,phonor->getPositionY()));
	m_pLeftMenu->addChild(pReqGold);

	CCLabelTTF* pgold=SystemData::getLabelTTF("Honor_text_gold");
	pgold->setFontSize(16);
	pgold->setColor(ccORANGE);
	pgold->setAnchorPoint(ccp(0,0.5));
	pgold->setPosition(ccp(phonor->getPositionX()+phonor->getContentSize().width+pReqGold->getContentSize().width*pReqGold->getScale(),phonor->getPositionY()));
	m_pLeftMenu->addChild(pgold);

	CCLabelTTF* ptext2=SystemData::getLabelTTF("Honor_text2");
	ptext2->setFontSize(16);
	ptext2->setColor(ccORANGE);
	ptext2->setAnchorPoint(ccp(0,0.5));
	ptext2->setPosition(SystemData::getLayoutPoint("Honor_text2_left_pos"));
	m_pLeftMenu->addChild(ptext2);

	CCLabelTTF* p1=CCLabelTTF::create(AToU8("2小时"),"",16);
	p1->setFontSize(16);
	p1->setColor(ccORANGE);
	p1->setAnchorPoint(ccp(0,0.5));
	p1->setPosition(ccp(ptext2->getPositionX()+ptext2->getContentSize().width+10,ptext2->getPositionY()));
	m_pLeftMenu->addChild(p1);

	CCLabelTTF* ptext3=SystemData::getLabelTTF("Honor_text3");
	ptext3->setFontSize(16);
	ptext3->setColor(ccORANGE);
	ptext3->setAnchorPoint(ccp(0,0.5));
	ptext3->setPosition(SystemData::getLayoutPoint("Honor_text3_left_pos"));
	m_pLeftMenu->addChild(ptext3);

	if (HeroData::getProp(Entity::attr_honor_cur)==0)
	{
		m_pCurHonorTime=CCLabelTTF::create(AToU8("未开启"),"",16);
		m_pCurHonorTime->setFontSize(16);
		m_pCurHonorTime->setColor(ccORANGE);
		m_pCurHonorTime->setAnchorPoint(ccp(0,0.5));
		m_pCurHonorTime->setPosition(ccp(ptext3->getPositionX()+ptext3->getContentSize().width+10,ptext3->getPositionY()));
		m_pLeftMenu->addChild(m_pCurHonorTime);
	}
	else
	{
		int curtime = ActivityData::getWorldTime();
		int starttime = HeroData::getBuffStartTime(10000+curHonorlvl);
		m_iTime=HeroData::getBuffTime(10000+curHonorlvl) - (curtime - starttime);
		m_pCurHonorTime=CCLabelTTF::create(StringUtils::timeToString(m_iTime,TimeType::hms).c_str(),"",16);
		m_pCurHonorTime->setFontSize(16);
		m_pCurHonorTime->setColor(ccORANGE);
		m_pCurHonorTime->setAnchorPoint(ccp(0,0.5));
		m_pCurHonorTime->setPosition(ccp(ptext3->getPositionX()+ptext3->getContentSize().width+10,ptext3->getPositionY()));
		m_pLeftMenu->addChild(m_pCurHonorTime);
	}
	
	 
	//内框内容
	CCScale9Sprite* pborder=SystemData::getScale9SpriteByPlist("Honor_smallborder",SystemData::getLayoutValue("Honor_border_size.w"),SystemData::getLayoutValue("Honor_border_size.h"));
	pborder->setAnchorPoint(CCPointZero);
	pborder->setPosition(SystemData::getLayoutPoint("Honor_border1_pos"));
	m_pLeftMenu->addChild(pborder);

	for (int i=0;i<8;i++)
	{
		CCLabelTTF* ptext=SystemData::getLabelTTF(strtitle[i].c_str());
		ptext->setFontSize(14);
		ptext->setColor(ccWHITE);
		ptext->setAnchorPoint(ccp(0,0.5));
		ptext->setPosition(ccp(SystemData::getLayoutPoint("Honor_bordertext_leftpos").x,SystemData::getLayoutPoint("Honor_bordertext_leftpos").y-20*i));
		m_pLeftMenu->addChild(ptext);

		int type,data;
		LuaData::getProp("gdHonor",curHonorlvl,"attr",i+1,"data","type",type,data);
		std::string datastr;
		datastr="+ "+SystemData::intToString(data);
		if (i==0 || i==1 )
		{
			datastr="+ "+SystemData::intToString(data/100)+" %";
		}
		else if(i==7)
		{
			datastr="+ "+SystemData::intToString(data)+" %";
		}
		CCLabelTTF* pValue=CCLabelTTF::create(datastr.c_str(),"",14);
		pValue->setAnchorPoint(ccp(0,0.5));
		pValue->setColor(ccGREEN);
		if (i==7)
		{
			pValue->setColor(ccYELLOW);
		}
		pValue->setPosition(ccp(ptext->getPositionX()+ptext->getContentSize().width+10,ptext->getPositionY()));
		m_pLeftMenu->addChild(pValue);

	}

	if (reqHonor>GameData::s_user->m_pMainRole->Honour)
	{
		((CCMenuItemImage*)(m_pMainMenu->getChildByTag(Honor_Left1)))->setEnabled(false);
	}

	if (reqGold>HeroData::getProp(Entity::attr_gold))
	{
		((CCMenuItemImage*)(m_pMainMenu->getChildByTag(Honor_Left2)))->setEnabled(false);
	}
	
	m_bLeftOver=true;
}

void HonorPanel::getSubRightPanel( int curHonorlvl )
{
	m_iCurSelectRange=curHonorlvl;
	m_bRightOver=false;
	if (m_pRightMenu)
	{
		m_pRightMenu->removeAllChildren();
	}
	else
	{
		m_pRightMenu=GeneralMenu::create();
		m_pRightMenu->setPosition(CCPointZero);
		m_pRightMenu->setAnchorPoint(CCPointZero);
		addChild(m_pRightMenu);
	}
	//标题
	CCSprite* pTitle=SystemData::getSpriteByPlist("Honor_titlebkg");
	pTitle->setPosition(SystemData::getLayoutPoint("Honor_title2_pos"));	
	m_pRightMenu->addChild(pTitle);

	CCLabelTTF* pTitletext=NULL;
	if (curHonorlvl==(HeroData::getProp(Entity::attr_honor_curmax)+1))
	{
		pTitletext =SystemData::getLabelTTF("Honor_title_text2");
	}
	else
	{
		CCString *pStr=CCString::createWithFormat(SystemData::getLayoutString("Honor_title_text3").c_str(),curHonorlvl);
		pTitletext = CCLabelTTF::create(pStr->getCString(),"",16);
	}
	pTitletext->setFontSize(16);
	pTitletext->setColor(ccWHITE);
	pTitletext->setPosition(SystemData::getLayoutPoint("Honor_title2_pos"));
	m_pRightMenu->addChild(pTitletext);

	//荣誉状态
	CCLabelTTF* ptext1=SystemData::getLabelTTF("Honor_text1_");
	ptext1->setFontSize(16);
	ptext1->setColor(ccORANGE);
	ptext1->setAnchorPoint(ccp(0,0.5));
	ptext1->setPosition(SystemData::getLayoutPoint("Honor_text1_right_pos"));
	m_pRightMenu->addChild(ptext1);

	//需要荣誉
	int reqHonor=0;
	LuaData::getProp("gdHonor",curHonorlvl,"upgradereq",reqHonor);
	CCLabelAtlas* pReq=CCLabelAtlas::create(SystemData::intToString(reqHonor).c_str(), SystemData::getLayoutString("ui.attribute_panel.num").c_str(), 17, 20, '0');
	pReq->setAnchorPoint(ccp(0,0.5));
	pReq->setScale(0.8);
	pReq->setPosition(ccp(ptext1->getPositionX()+ptext1->getContentSize().width,ptext1->getPositionY()));
	m_pRightMenu->addChild(pReq);

	CCLabelTTF* phonor=SystemData::getLabelTTF("Honor_text");
	phonor->setFontSize(16);
	phonor->setColor(ccORANGE);
	phonor->setAnchorPoint(ccp(0,0.5));
	phonor->setPosition(ccp(ptext1->getPositionX()+ptext1->getContentSize().width+pReq->getScale()*pReq->getContentSize().width,ptext1->getPositionY()));
	m_pRightMenu->addChild(phonor);

	//需要元宝
	int reqGold=0;
	LuaData::getProp("gdHonor",curHonorlvl,"upgradereqgold",reqGold);
	CCLabelAtlas* pReqGold=CCLabelAtlas::create(SystemData::intToString(reqGold).c_str(), SystemData::getLayoutString("ui.attribute_panel.num").c_str(), 17, 20, '0');
	pReqGold->setAnchorPoint(ccp(0,0.5));
	pReqGold->setScale(0.8);
	pReqGold->setPosition(ccp(phonor->getPositionX()+phonor->getContentSize().width,phonor->getPositionY()));
	m_pRightMenu->addChild(pReqGold);

	CCLabelTTF* pgold=SystemData::getLabelTTF("Honor_text_gold");
	pgold->setFontSize(16);
	pgold->setColor(ccORANGE);
	pgold->setAnchorPoint(ccp(0,0.5));
	pgold->setPosition(ccp(phonor->getPositionX()+phonor->getContentSize().width+pReqGold->getContentSize().width*pReqGold->getScale(),phonor->getPositionY()));
	m_pRightMenu->addChild(pgold);

	CCLabelTTF* ptext2=SystemData::getLabelTTF("Honor_text2");
	ptext2->setFontSize(16);
	ptext2->setColor(ccORANGE);
	ptext2->setAnchorPoint(ccp(0,0.5));
	ptext2->setPosition(SystemData::getLayoutPoint("Honor_text2_right_pos"));
	m_pRightMenu->addChild(ptext2);
	
	CCLabelTTF* p1=CCLabelTTF::create(AToU8("2小时"),"",16);
	p1->setFontSize(16);
	p1->setColor(ccORANGE);
	p1->setAnchorPoint(ccp(0,0.5));
	p1->setPosition(ccp(ptext2->getPositionX()+ptext2->getContentSize().width+10,ptext2->getPositionY()));
	m_pRightMenu->addChild(p1);

	CCLabelTTF* ptext3=SystemData::getLabelTTF("Honor_text3_");
	ptext3->setFontSize(16);
	ptext3->setColor(ccORANGE);
	ptext3->setAnchorPoint(ccp(0,0.5));
	ptext3->setPosition(SystemData::getLayoutPoint("Honor_text3_right_pos"));
	m_pRightMenu->addChild(ptext3);
	
	int reqLvl=0;
	LuaData::getProp("gdHonor",curHonorlvl,"reqlvl",reqLvl);
	CCLabelTTF* p2=CCLabelTTF::create(SystemData::intToString(reqLvl).c_str(),"",16);
	p2->setFontSize(16);
	p2->setColor(ccORANGE);
	if (GameData::s_user->m_pMainRole->mLevel<reqLvl)
	{
		p2->setColor(ccRED);
	}
	p2->setAnchorPoint(ccp(0,0.5));
	p2->setPosition(ccp(ptext3->getPositionX()+ptext3->getContentSize().width+10,ptext3->getPositionY())); 
	m_pRightMenu->addChild(p2);
	  
	//内框内容
	CCScale9Sprite* pborder=SystemData::getScale9SpriteByPlist("Honor_smallborder",SystemData::getLayoutValue("Honor_border_size.w"),SystemData::getLayoutValue("Honor_border_size.h"));
	pborder->setAnchorPoint(CCPointZero);
	pborder->setPosition(SystemData::getLayoutPoint("Honor_border2_pos"));
	m_pRightMenu->addChild(pborder);

	for (int i=0;i<8;i++)
	{
		CCLabelTTF* ptext=SystemData::getLabelTTF(strtitle[i].c_str());
		ptext->setFontSize(14);
		ptext->setColor(ccWHITE);
		ptext->setAnchorPoint(ccp(0,0.5));
		ptext->setPosition(ccp(SystemData::getLayoutPoint("Honor_bordertext_rightpos").x,SystemData::getLayoutPoint("Honor_bordertext_rightpos").y-20*i));
		m_pRightMenu->addChild(ptext);

		int type,data;
		LuaData::getProp("gdHonor",curHonorlvl,"attr",i+1,"data","type",type,data);
		std::string datastr;
		datastr="+ "+SystemData::intToString(data);
		if (i==0 || i==1 )
		{
			datastr="+ "+SystemData::intToString(data/100)+" %";
		}
		else if(i==7)
		{
			datastr="+ "+SystemData::intToString(data)+" %";
		}
		CCLabelTTF* pValue=CCLabelTTF::create(datastr.c_str(),"",14);
		pValue->setAnchorPoint(ccp(0,0.5));
		pValue->setColor(ccGREEN);
		if (i==7) 
		{
			pValue->setColor(ccYELLOW);
		}
		pValue->setPosition(ccp(ptext->getPositionX()+ptext->getContentSize().width+10,ptext->getPositionY()));
		m_pRightMenu->addChild(pValue);
	}

	int reqlvl;
	LuaData::getProp("gdHonor",curHonorlvl,"reqlvl",reqlvl); 
	if (reqHonor<=GameData::s_user->m_pMainRole->Honour && HeroData::getProp(Entity::attr_honor_curmax)+1==curHonorlvl  && reqlvl<=GameData::s_user->m_pMainRole->mLevel)
	{
		((CCMenuItemImage*)(m_pMainMenu->getChildByTag(Honor_Right1)))->setEnabled(true);
	}
	else
	{
		((CCMenuItemImage*)(m_pMainMenu->getChildByTag(Honor_Right1)))->setEnabled(false);
	}

	if (reqGold<=HeroData::getProp(Entity::attr_gold) && HeroData::getProp(Entity::attr_honor_curmax)+1==curHonorlvl  && reqlvl<=GameData::s_user->m_pMainRole->mLevel)
	{
		((CCMenuItemImage*)(m_pMainMenu->getChildByTag(Honor_Right2)))->setEnabled(true);
	}
	else
	{
		((CCMenuItemImage*)(m_pMainMenu->getChildByTag(Honor_Right2)))->setEnabled(false);
	}
	
	m_bRightOver=true;
}

void HonorPanel::buttonCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (m_pCurItemSprite)
		{
			m_pCurItemSprite->getChildByTag(100)->setVisible(false);
		}
		m_pCurItemSprite=(CCMenuItemSprite*)pNode;
		m_pCurItemSprite->getChildByTag(100)->setVisible(true);
		getSubRightPanel(tag);
	}
}

void HonorPanel::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case Honor_Left1:
			if (m_bLeftOver)
			{
				postopenhonor();
			}
			break;
		case Honor_Left2:
			if (m_bLeftOver)
			{
				postopenhonorbygold();
			}
			break;
		case Honor_Right1:
			if (m_bRightOver)
			{
				if (m_iTimeSpan == 0)
				{
					postupgradehonor();
					m_iTimeSpan = 3;
				}
				else
				{
					CPEventHelper::uiNotify("","",Error::time3sspan);
				}  
				
			}
			break;
		case Honor_Right2:
			if (m_bRightOver)
			{
				if (m_iTimeSpan == 0)
				{
					postupgradehonorbygold();
					m_iTimeSpan = 3;
				}
				else
				{
					CPEventHelper::uiNotify("","",Error::time3sspan);
				}  
				
			}
			break;
		default:
			break;
		}
	}
}
 
void HonorPanel::Update()
{
	if (m_iTimeSpan > 0)
	{
		m_iTimeSpan--;
	}
}

void HonorPanel::postopenhonor()
{
	MsgOpenHonorRequest* msg=new MsgOpenHonorRequest;
	msg->honorid=m_iCurHonorlvl;
	HandleMessage::sendMessage(msg);
}

void HonorPanel::postopenhonorbygold()
{
	MsgOpenHonorByGoldRequest* msg=new MsgOpenHonorByGoldRequest;
	msg->honorid=m_iCurHonorlvl;
	HandleMessage::sendMessage(msg);
}

void HonorPanel::postupgradehonorbygold()
{
	MsgUpgradeHonorByGoldRequest* msg=new MsgUpgradeHonorByGoldRequest;
	msg->honorid=m_iCurHonorlvl+1;
	HandleMessage::sendMessage(msg);
}

void HonorPanel::postupgradehonor()
{
	MsgUpgradeHonorRequest* msg=new MsgUpgradeHonorRequest;
	msg->honorid=m_iCurHonorlvl+1;
	HandleMessage::sendMessage(msg);
}

void HonorPanel::updatetime(int index)
{
	if (m_iTime==0)
	{
		//finishtime();
		return;
	}
	m_iTime=m_iTime-index;
	if (m_pCurHonorTime)
	{
		m_pCurHonorTime->setString(StringUtils::timeToString(m_iTime,TimeType::hms).c_str());
		HeroData::setProp(Entity::attr_honor_cur,m_iTime);
		if (m_iTime==0)
		{
			finishtime();
		}
	}
	
}

void HonorPanel::finishtime()
{
	m_iTime=0;
	m_pCurHonorTime->setString(AToU8("未开启"));
}

void HonorPanel::initButton()
{
	//开启祝福按钮
	int reqHonor=0;
	LuaData::getProp("gdHonor",m_iCurHonorlvl,"openreq",reqHonor);
	CCMenuItemSprite* pItem1=NULL;
	if (reqHonor<=GameData::s_user->m_pMainRole->Honour)
	{
		CCSprite* pSprite1=SystemData::getSpriteByPlist("Honor_button1");
		CCSprite* pSprite2=SystemData::getSpriteByPlist("Honor_button1.sel");
		CCSprite* pSprite3=SystemData::getSpriteByPlist("Honor_button1_huise");
		pItem1=CCMenuItemSprite::create(pSprite1,pSprite2,pSprite3,this,NULL);
		//pItem1=SystemData::getMenuItemImage("Honor_button1");
		pItem1->setTarget(this,menu_selector(HonorPanel::menuCallBack));
	}
	else
	{
		CCSprite* pSprite1=SystemData::getSpriteByPlist("Honor_button1_huise");
		CCSprite* pSprite2=SystemData::getSpriteByPlist("Honor_button1_huise");
		CCSprite* pSprite3=SystemData::getSpriteByPlist("Honor_button1_huise");
		pItem1=CCMenuItemSprite::create(pSprite1,pSprite2,pSprite3,this,NULL);
		//pItem1=SystemData::getMenuItemImage("Honor_button1_huise");
		pItem1->setTarget(this,NULL);
	}
	pItem1->setScaleX(1.1);
	pItem1->setTag(Honor_Left1);
	pItem1->setPosition(SystemData::getLayoutPoint("Honor_button1_pos"));
	m_pMainMenu->addChild(pItem1);


	CCLabelTTF* pbuttonLabel1=SystemData::getLabelTTF("Honor_button_text1");
	pbuttonLabel1->setFontSize(16);
	pbuttonLabel1->setColor(ccWHITE);
	pbuttonLabel1->setPosition(SystemData::getLayoutPoint("Honor_button1_pos"));
	m_pMainMenu->addChild(pbuttonLabel1);
	
	//元宝开启按钮
	int reqGold=0;
	LuaData::getProp("gdHonor",m_iCurHonorlvl,"openreqgold",reqGold);
	CCMenuItemSprite* pItem3=NULL;
	if (reqGold<=HeroData::getProp(Entity::attr_gold))
	{
		CCSprite* pSprite1=SystemData::getSpriteByPlist("Honor_button1");
		CCSprite* pSprite2=SystemData::getSpriteByPlist("Honor_button1.sel");
		CCSprite* pSprite3=SystemData::getSpriteByPlist("Honor_button1_huise");
		pItem3=CCMenuItemSprite::create(pSprite1,pSprite2,pSprite3,this,NULL);
		pItem3->setTarget(this,menu_selector(HonorPanel::menuCallBack));
	}
	else
	{
		CCSprite* pSprite1=SystemData::getSpriteByPlist("Honor_button1_huise");
		CCSprite* pSprite2=SystemData::getSpriteByPlist("Honor_button1_huise");
		CCSprite* pSprite3=SystemData::getSpriteByPlist("Honor_button1_huise");
		pItem3=CCMenuItemSprite::create(pSprite1,pSprite2,pSprite3,this,NULL);
		pItem3->setTarget(this,NULL);
	}
	pItem3->setScaleX(1.1);
	pItem3->setTag(Honor_Left2);
	pItem3->setPosition(ccp(SystemData::getLayoutPoint("Honor_button1_pos").x + 150,SystemData::getLayoutPoint("Honor_button1_pos").y));
	m_pMainMenu->addChild(pItem3);


	CCLabelTTF* pbuttonLabel3=SystemData::getLabelTTF("Honor_button_text3");
	pbuttonLabel3->setFontSize(16);
	pbuttonLabel3->setColor(ccWHITE);
	pbuttonLabel3->setPosition(ccp(SystemData::getLayoutPoint("Honor_button1_pos").x + 150,SystemData::getLayoutPoint("Honor_button1_pos").y));
	m_pMainMenu->addChild(pbuttonLabel3);



	//升级祝福按钮
	int curHonorlvl=m_iCurHonorlvl+1;
	int count;
	LuaData::getProp_size("gdHonor",0,"",count); 
	LuaData::getProp("gdHonor",curHonorlvl,"upgradereq",reqHonor);
	int reqlvl;
	LuaData::getProp("gdHonor",curHonorlvl,"reqlvl",reqlvl); 
	CCMenuItemSprite* pItem2=NULL;
	if (reqHonor<=GameData::s_user->m_pMainRole->Honour && HeroData::getProp(Entity::attr_honor_curmax)+1==curHonorlvl && count>=curHonorlvl && reqlvl<=GameData::s_user->m_pMainRole->mLevel)
	{
		CCSprite* pSprite1=SystemData::getSpriteByPlist("Honor_button1");
		CCSprite* pSprite2=SystemData::getSpriteByPlist("Honor_button1.sel");
		CCSprite* pSprite3=SystemData::getSpriteByPlist("Honor_button1_huise");
		pItem2=CCMenuItemSprite::create(pSprite1,pSprite2,pSprite3,this,menu_selector(HonorPanel::menuCallBack));
		pItem2->setTarget(this,menu_selector(HonorPanel::menuCallBack));
	}
	else
	{
		CCSprite* pSprite1=SystemData::getSpriteByPlist("Honor_button1_huise");
		CCSprite* pSprite2=SystemData::getSpriteByPlist("Honor_button1_huise");
		CCSprite* pSprite3=SystemData::getSpriteByPlist("Honor_button1_huise");
		pItem2=CCMenuItemSprite::create(pSprite1,pSprite2,pSprite3,this,NULL);
		//pItem2=SystemData::getMenuItemImage("Honor_button1_huise");
		pItem2->setTarget(this,NULL);
	}
	pItem2->setScaleX(1.1);
	pItem2->setTag(Honor_Right1);
	pItem2->setPosition(SystemData::getLayoutPoint("Honor_button2_pos"));
	m_pMainMenu->addChild(pItem2);

	CCLabelTTF* pbuttonLabel2=SystemData::getLabelTTF("Honor_button_text2");
	pbuttonLabel2->setFontSize(16);
	pbuttonLabel2->setColor(ccWHITE);
	pbuttonLabel2->setPosition(SystemData::getLayoutPoint("Honor_button2_pos"));
	m_pMainMenu->addChild(pbuttonLabel2);

	//元宝升级按钮
	LuaData::getProp("gdHonor",curHonorlvl,"upgradereqgold",reqGold);
	CCMenuItemSprite* pItem4=NULL;
	if (reqGold<=HeroData::getProp(Entity::attr_gold) && HeroData::getProp(Entity::attr_honor_curmax)+1==curHonorlvl && count>=curHonorlvl && reqlvl<=GameData::s_user->m_pMainRole->mLevel)
	{
		CCSprite* pSprite1=SystemData::getSpriteByPlist("Honor_button1");
		CCSprite* pSprite2=SystemData::getSpriteByPlist("Honor_button1.sel");
		CCSprite* pSprite3=SystemData::getSpriteByPlist("Honor_button1_huise");
		pItem4=CCMenuItemSprite::create(pSprite1,pSprite2,pSprite3,this,menu_selector(HonorPanel::menuCallBack));
		pItem4->setTarget(this,menu_selector(HonorPanel::menuCallBack));
	}
	else
	{
		CCSprite* pSprite1=SystemData::getSpriteByPlist("Honor_button1_huise");
		CCSprite* pSprite2=SystemData::getSpriteByPlist("Honor_button1_huise");
		CCSprite* pSprite3=SystemData::getSpriteByPlist("Honor_button1_huise");
		pItem4=CCMenuItemSprite::create(pSprite1,pSprite2,pSprite3,this,NULL);
		pItem4->setTarget(this,NULL);
	}
	pItem4->setScaleX(1.1);
	pItem4->setTag(Honor_Right2);
	pItem4->setPosition(ccp(SystemData::getLayoutPoint("Honor_button2_pos").x + 150,SystemData::getLayoutPoint("Honor_button2_pos").y));
	m_pMainMenu->addChild(pItem4);

	CCLabelTTF* pbuttonLabel4=SystemData::getLabelTTF("Honor_button_text4");
	pbuttonLabel4->setFontSize(16);
	pbuttonLabel4->setColor(ccWHITE);
	pbuttonLabel4->setPosition(ccp(SystemData::getLayoutPoint("Honor_button2_pos").x + 150,SystemData::getLayoutPoint("Honor_button2_pos").y));
	m_pMainMenu->addChild(pbuttonLabel4);
}
