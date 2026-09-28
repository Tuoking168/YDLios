#include "EmigratedPanel.h"
#include "userdata/SystemData.h"
#include "ext/GeneralMenu.h"
#include "script/LuaWrapper.h"
#include "MsgActivity.h"
#include "network/HandleMessage.h"
#include "event/EventProtocol.h"
#include "userdata/ActivityData.h"
#include "EvtDataDefinition.h"
#include "userdata/netdata/HeroModel.h"
#include "userdata/GameData.h"
#include "scene/GameUI.h"
#include "userdata/UserData.h"
#include "userdata/StaticData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/activitydata/EmigratedData.h"
#include "userdata/luadata/LuaData.h"
#include "ext/CCTabelViewEx.h"
#include "utils/StringUtils.h"
#include "controls/CPUpdater.h"
#include "logic/TimeManager.h"
#include "logic/ItemOperator.h"
#include "event/CPEventHelper.h"

#include "MsgPlayer.h"
#include "userdata/HeroData.h"
#include "userdata/LayoutData.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "controls/CPNodeHelper.h"
#include "scene/panel/FloatPanelType.h"
#include "scene/panel/FloatPanel.h"
#include "ErrorDefinition.h"
#include "EntityDefinition.h"
#include "scene/panel/TaskPanel.h"
#include "userdata/TaskData.h"
#include "QuestDefinition.h"
#include "userdata/NPCFunctionData.h"
#include "ext/CCMenuItemFontColor.h"
#include "event/CPEventDispatcher.h"

int cscg_cnt;
int cscg_pos;

EmigratedPanel::EmigratedPanel()
	:rightTopPanel(NULL)
	,pLayer(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

EmigratedPanel::~EmigratedPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE,this);
}

bool EmigratedPanel::init()
{
	int k;
	ActivityData::getExData(EvtData::evt_cscg,cscg_cnt,k,cscg_pos);
	initInterFace();
	initRightTop();
	initRightDown();
	initMap();

	MsgCaiShenChuangGuanDataRequest* msg=new MsgCaiShenChuangGuanDataRequest;
	HandleMessage::sendMessage(msg);
	return true;
}

/**
 * EmigratedPanel::initInterFace() 初始化界面函数
 * 功能：初始化移民活动面板的UI界面，包括背景、标题栏、装饰元素和关闭按钮
 * 注意：函数名"initInterFace"可能是"initInterface"的拼写错误
 */
void EmigratedPanel::initInterFace()//财神ui
{
	// 1. 设置面板的宽度和高度（基于1200x520的设计分辨率）
	m_nWidth = 800;  // 注释：对应800全屏的换算值
	m_nHeight = 480;  // 注释：对应480的换算值

	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	// 2. 添加覆盖层（半透明黑色遮罩，用于突出显示当前面板）
	addCover();
	
	// 3. 设置面板的内容尺寸
	setContentSize(CCSizeMake(m_nWidth, m_nHeight));
	
	// 4. 创建并添加主背景
	// 从plist资源获取九宫格精灵作为主背景
	// 参数说明：
	// "activity_emigrated_mainbkg" - 移民活动主背景资源名称
	// m_nWidth, m_nHeight - 使用前面定义的宽度和高度
	CCScale9Sprite *bkg = SystemData::getScale9SpriteByPlist("activity_emigrated_mainbkg", m_nWidth, m_nHeight);
	bkg->setAnchorPoint(CCPointZero);  // 设置锚点为左下角
	bkg->setPosition(CCPointZero);      // 设置位置为(0,0)
	addChild(bkg);                       // 添加到当前面板
	
	// 5. 创建并添加通用标题栏背景
	// 从COMMON模块获取九宫格精灵作为标题栏背景
	CCScale9Sprite *titleBoard = LayoutData::getScale9Sprite(CPModuleName::COMMON, "titleBoard");
	addChild(titleBoard);
	
	// 6. 创建并添加标题栏左右装饰元素
	// 左侧标题栏装饰
	CCSprite *titleBoardDecorationL = LayoutData::getSprite(CPModuleName::COMMON, "titleBoardDecorationL");
	addChild(titleBoardDecorationL);
	
	// 右侧标题栏装饰
	CCSprite *titleBoardDecorationR = LayoutData::getSprite(CPModuleName::COMMON, "titleBoardDecorationR");
	addChild(titleBoardDecorationR);
	
	// 7. 创建并添加标题左右装饰元素
	// 左侧标题装饰
	CCSprite *titleDecorationL = LayoutData::getSprite(CPModuleName::COMMON, "titleDecorationL");
	addChild(titleDecorationL);
	
	// 右侧标题装饰
	CCSprite *titleDecorationR = LayoutData::getSprite(CPModuleName::COMMON, "titleDecorationR");
	addChild(titleDecorationR);
	
	// 8. 创建关闭按钮菜单容器
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);  // 设置位置为(0,0)
	addChild(menu);                   // 添加到当前面板
	
	// 9. 创建并添加关闭按钮
	// 从COMMON模块获取关闭按钮图片
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "close");
	closeBtn->setTarget(this, menu_selector(EmigratedPanel::menucallback));  // 设置点击回调函数
	closeBtn->setTag(button_close);  // 设置按钮标签为关闭按钮标识
	menu->addChild(closeBtn);         // 添加到菜单容器
	
	// 10. 创建并添加移民活动顶部标题图片
	// 从plist资源获取顶部标题精灵
	CCSprite* ptitle = SystemData::getSpriteByPlist("activity_emigrated_Toptitile");
	addChild(ptitle);
	
	// 注意：函数中缺少以下常见UI元素的设置：
	// 1. 标题栏和各装饰元素的位置设置
	// 2. 顶部标题图片的位置设置
	// 3. 关闭按钮的位置设置
	// 这些元素的位置可能在布局数据中定义，但此处未显式设置
}

void EmigratedPanel::menucallback( CCObject* pObject )
{
	CCNode* pNode=dynamic_cast<CCNode*>(pObject);
	if (pNode)
	{
		int tag=pNode->getTag();
		switch (tag)
		{
		case  button_close:
			this->removeFromParent();
			break;			
		default:
			break;
		}
	}
}

void EmigratedPanel::initMap()
{
	EmigratedLeftMapPanel* pPanel=EmigratedLeftMapPanel::create();
	pPanel->setPosition(CCPointZero);
	pPanel->setAnchorPoint(CCPointZero);
	addChild(pPanel);
}

void EmigratedPanel::initRightTop()
{
	pLayer = CCLayer::create();
	//rightTopPanel = BasePanel::create("");
	if (TaskData::getFirstTask(Quest::line_Emigrated))
	{
		rightTopPanel = EmigratedRightTopPanelTask::create();
	}
	else
	{
		rightTopPanel = EmigratedRightTopPanel::create();		
	}
	
	if (rightTopPanel && pLayer)
	{
		rightTopPanel->setPosition(CCPointZero);
		rightTopPanel->setAnchorPoint(CCPointZero);
		pLayer->addChild(rightTopPanel);
		addChild(pLayer);
	}
}

void EmigratedPanel::initRightDown()
{
	EmigratedRightDownPanel* pPanel=EmigratedRightDownPanel::create();
	pPanel->setPosition(CCPointZero);
	pPanel->setAnchorPoint(CCPointZero);
	addChild(pPanel);
}

void EmigratedPanel::onEnter()
{
	BasePanel::onEnter();
	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}

void EmigratedPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (source == "HandleMessageQuestUpdateList" ||
		source == "HandleMessageQuestUpdate")
	{
		if (TaskData::getFirstTask(Quest::line_Emigrated))
		{
			rightTopPanel = EmigratedRightTopPanelTask::create();
		}
		else
		{
			rightTopPanel = EmigratedRightTopPanel::create();	
		}


		rightTopPanel->setPosition(CCPointZero);
		rightTopPanel->setAnchorPoint(CCPointZero);
		pLayer->addChild(rightTopPanel);
	}
}

//-------------------------------------------------------------------------------------------------------//

EmigratedLeftMapPanel* EmigratedLeftMapPanel::create()
{
	EmigratedLeftMapPanel* pPanel=new EmigratedLeftMapPanel;
	if (pPanel && pPanel->init())
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

EmigratedLeftMapPanel::EmigratedLeftMapPanel():
	m_heroModel(NULL),
	m_pCntLabel(NULL),
	m_pHeroPanel(NULL),
	m_pTitleLabel(NULL),
	m_bIsActionOver(true),
	m_pCaseMenu(NULL),
	m_bIsCreateOver(false),
	m_pDiceSprite(NULL),
	m_pTimeLabel(NULL),
	m_iTime(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);

}

EmigratedLeftMapPanel::~EmigratedLeftMapPanel()
{
	CC_SAFE_DELETE(m_heroModel);
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool EmigratedLeftMapPanel::init()
{
	initInterFace();
	initMap();
	m_pCaseMenu=GeneralMenu::create();
	m_pCaseMenu->setAnchorPoint(CCPointZero);
	m_pCaseMenu->setPosition(CCPointZero);
	addChild(m_pCaseMenu);
	initButton();
	updateRolePos();
	return true;
}

void EmigratedLeftMapPanel::initInterFace()
{
	CCScale9Sprite* pborder1=SystemData::getScale9SpriteByPlist("activity_emigrated_border",SystemData::getLayoutValue("activity_emigrated_border1_size.w"),SystemData::getLayoutValue("activity_emigrated_border1_size.h"));
	pborder1->setAnchorPoint(CCPointZero);
	pborder1->setPosition(SystemData::getLayoutPoint("activity_emigrated_border1_pos"));
	addChild(pborder1);

	CCSprite* ptitlebkg=SystemData::getSpriteByPlist("activity_emigrated_namebkg");
	ptitlebkg->setPosition(ccp(pborder1->getContentSize().width/2,pborder1->getContentSize().height/2));
	pborder1->addChild(ptitlebkg);

	CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("activity_emigrated_name").c_str(),1);
	m_pTitleLabel=SystemData::getLabelTTF(pStr->getCString());
	m_pTitleLabel->setColor(ccORANGE);
	m_pTitleLabel->setFontSize(20);
	m_pTitleLabel->setPosition(ptitlebkg->getPosition());
	pborder1->addChild(m_pTitleLabel);


	CCScale9Sprite* pborder2=SystemData::getScale9SpriteByPlist("activity_emigrated_border",SystemData::getLayoutValue("activity_emigrated_border2_size.w"),SystemData::getLayoutValue("activity_emigrated_border2_size.h"));
	pborder2->setAnchorPoint(CCPointZero);
	pborder2->setPosition(SystemData::getLayoutPoint("activity_emigrated_border2_pos"));
	addChild(pborder2);

	CCSprite* pMap=SystemData::getSprite("activity_emigrated_mapbkg");
	pMap->setAnchorPoint(CCPointZero);
	pMap->setPosition(SystemData::getLayoutPoint("activity_emigrated_border2_pos"));
	addChild(pMap);

	CCMenu* pMenu = CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCMenuItem* pRollItem = CCMenuItem::create();
	CCSprite* pSprite=SystemData::getSpriteByPlist("activity_emigrated_roll1");
	pSprite->setTag(sprite_dice);
	pSprite->setPosition(SystemData::getLayoutPoint("activity_emigrated_roll_mianpos"));
	addChild(pSprite); 
	pRollItem->setTarget(this,menu_selector(EmigratedLeftMapPanel::menucallback));
	pRollItem->setContentSize(pSprite->getContentSize());
	pRollItem->setTag(button_randomroll);
	pRollItem->setPosition(pSprite->getPosition());
	pMenu->addChild(pRollItem);
}
 
void EmigratedLeftMapPanel::menucallback( CCObject* pObject )
{
	if (!m_bIsActionOver)
	{
		return;
	}
	CCNode* pNode=dynamic_cast<CCNode*>(pObject);
	if (pNode)
	{
		int tag=pNode->getTag();
		switch (tag)
		{		
		case  button_selectroll:
			addRollPanel();
			break;
		case button_randomroll:
			//发送roll点消息
			postrandomroll();
			break;
		case button_chongzhiroll:
			{
				int vipLv = HeroData::getProp(Entity::attr_vip_level);
				if (vipLv>=6)
				{
					int cnt = ActivityData::getExDataX(EvtData::evt_freerestartcscg);
					int cnt2 = ActivityData::getExDataY(EvtData::evt_freerestartcscg);
					if (cnt2-cnt>0)
					{
						Game::getGameUI()->showFloatPanel(FloatPanelType::Refresh_Cahshenchuangguan);
						((FloatPanel*)(Game::getGameUI()->m_panels[TAG_FLOAT_PANEL]))->setHandler(this,floatpanel_selector(EmigratedLeftMapPanel::floatpanelCallback2));
					}
					else
					{
						CPEventHelper::uiNotify("","",Error::NotEnoughCnt);
						return;
					}
					
				}
				else
				{
					CPEventHelper::uiNotify("","",Error::NotEnoughVipLevel);
					return;
				}

			}
			break;
		case button_addtime:
			//发送加速时间
			if (HeroData::getCommonCD(EvtData::cd_cdcscg) != 0)
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::Time_QuickCoolDown);
				((FloatPanel*)(Game::getGameUI()->m_panels[TAG_FLOAT_PANEL]))->setHandler(this,floatpanel_selector(EmigratedLeftMapPanel::floatpanelCallback));
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::NoNeedCleanCD);   

			}
			
			break;
		case button_addcount:
			{
				//发送添加次数
				int cost = 0;
				StaticData::getGlobalData("emigrateAddCountCost", cost);
				int liquan = HeroData::getProp(Entity::attr_diamond);
				bool couponFirst = false;
				if (liquan>0)
				{
					couponFirst = true;
				}
				if (ItemOperator::testGoldEnough(cost,couponFirst))
				{
					StrVector vect;
					vect.push_back(StringUtils::toString(cost));
					FloatPanel::show(FloatPanelType::Emigrate_add_count, vect, this, floatpanel_selector(EmigratedLeftMapPanel::onAddCount));
				}
				break;
			}			
		default:
			break;
		}
	}
}

void EmigratedLeftMapPanel::initMap()
{
	m_mAllMapPos.clear();
	std::vector<emigratedmap> emigratedlist;
	int stepcount=SystemData::getLayoutValue("activity_emigrated_mapstep");
	for (int i=0;i<stepcount;i++)
	{
		CCString* countname=CCString::createWithFormat(SystemData::getLayoutString("activity_emigrated_mapcount").c_str(),i+1);
		CCString* dirctionname=CCString::createWithFormat(SystemData::getLayoutString("activity_emigrated_mapdirection").c_str(),i+1);
		emigratedmap step1;
		step1.stepcount=SystemData::getLayoutValue(countname->getCString());
		step1.direction=SystemData::getLayoutString(dirctionname->getCString()).c_str();
		emigratedlist.push_back(step1);
	}

	int x=48;
	int y=30;
	CCPoint pos=SystemData::getLayoutPoint("activity_emigrated_mapstart");
	std::vector<emigratedmap>::iterator it;
	std::string lastdirction;
	int ncnt=0;
	int ndirection=0;//1 2 3 4 上 右 下 左
	for (it=emigratedlist.begin();it!=emigratedlist.end();it++)
	{
		if (it->direction=="up")
		{
			x=0;
			y=30;
			ndirection=1;
		}
		else if (it->direction=="down")
		{
			x=0;
			y=-30;
			ndirection=3;
		}
		else if(it->direction=="left")
		{
			x=-48;
			y=0;
			ndirection=4;
		}
		else if (it->direction=="right")
		{
			x=48;
			y=0;
			ndirection=2;
		}
		for (int n=0;n<it->stepcount;n++)
		{
			ncnt++;		
			pos=ccp(pos.x+x,pos.y+y);
			CCSprite* pstep=NULL;
			CCSprite* ptext=NULL;
			CCSprite* pdirect=NULL;
			CCMenuItemImage* pbutton=NULL;
			if (it==emigratedlist.begin() && n==0)
			{
				pstep=SystemData::getSpriteByPlist("activity_emigrated_bluefloor");
				ptext=SystemData::getSpriteByPlist("activity_emigrated_starttext");
				ptext->setPosition(pos);
			}
			else if ((it+1)==emigratedlist.end() && n+1==it->stepcount)
			{
				pstep=SystemData::getSpriteByPlist("activity_emigrated_redfloor");
				ptext=SystemData::getSpriteByPlist("activity_emigrated_endtext");
				ptext->setPosition(ccp(pos.x,pos.y+30));
				pdirect=SystemData::getSpriteByPlist("activity_emigrated_direct");
				pdirect->setPosition(ccp(pos.x+x,pos.y));
				if (it->direction=="left")
				{
					pdirect->runAction(CCFlipX::create(true));
				}

				pbutton=SystemData::getMenuItemImageByPlist("activity_emigrated_case10");
				pbutton->setPosition(pos);
				pbutton->setTag(10);
				pbutton->setTarget(this,menu_selector(EmigratedLeftMapPanel::menucallback));

				CCSprite* pstepEx=SystemData::getSpriteByPlist("activity_emigrated_bluefloor");
				pstepEx->setPosition(ccp(pos.x+x*2,pos.y));
				addChild(pstepEx);

				CCSprite* pstepExtext=SystemData::getSpriteByPlist("activity_emigrated_wenhao");
				pstepExtext->setPosition(ccp(pos.x+x*2,pos.y));
				addChild(pstepExtext);
			}
			else
			{
				if (it==emigratedlist.begin() && n==1)
				{
					pdirect=SystemData::getSpriteByPlist("activity_emigrated_direct");
					pdirect->setPosition(pos);
				}
				pstep=SystemData::getSpriteByPlist("activity_emigrated_greenfloor");
			}
			pstep->setPosition(pos);
			addChild(pstep);
			m_mAllMapPos[ncnt*10+ndirection]=pos;
			if (ptext)
			{
				addChild(ptext);
			}
			if (pdirect)
			{
				addChild(pdirect);
			}
			if (pbutton)
			{
				addChild(pbutton);
			}
		}
	}
	m_iCurPos=m_mAllMapPos.begin()->first;
	
}

void EmigratedLeftMapPanel::initButton()
{
	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);
	addChild(pMenu);

	CCScale9Sprite* pbutton1spr1=SystemData::getScale9SpriteByPlist("activity_emigrated_button",96,42);
	CCScale9Sprite* pbutton1spr2=SystemData::getScale9SpriteByPlist("activity_emigrated_button.sel",96,42);
	CCMenuItemSprite* pbutton1=CCMenuItemSprite::create(pbutton1spr1,pbutton1spr2,NULL,this,menu_selector(EmigratedLeftMapPanel::menucallback));
	pbutton1->setAnchorPoint(CCPointZero);
	pbutton1->setTag(button_selectroll);
	pbutton1->setPosition(SystemData::getLayoutPoint("activity_emigrated_buttontext1_pos"));
	pMenu->addChild(pbutton1);
	CCLabelTTF* pbuttontext1=SystemData::getLabelTTF("activity_emigrated_buttontext1");
	pbuttontext1->setColor(ccYELLOW);
	pbuttontext1->setFontSize(18);
	pbuttontext1->setPosition(ccp(pbutton1->getPositionX()+pbutton1->getContentSize().width/2,pbutton1->getPositionY()+pbutton1->getContentSize().height/2));
	pMenu->addChild(pbuttontext1);

	CCScale9Sprite* pbutton2spr1=SystemData::getScale9SpriteByPlist("activity_emigrated_button",96,42);
	CCScale9Sprite* pbutton2spr2=SystemData::getScale9SpriteByPlist("activity_emigrated_button.sel",96,42);
	CCMenuItemSprite* pbutton2=CCMenuItemSprite::create(pbutton2spr1,pbutton2spr2,NULL,this,menu_selector(EmigratedLeftMapPanel::menucallback));
	pbutton2->setAnchorPoint(CCPointZero);
	pbutton2->setTag(button_randomroll);
	pbutton2->setPosition(SystemData::getLayoutPoint("activity_emigrated_buttontext2_pos"));
	pMenu->addChild(pbutton2);
	CCLabelTTF* pbuttontext2=SystemData::getLabelTTF("activity_emigrated_buttontext2");
	pbuttontext2->setColor(ccYELLOW);
	pbuttontext2->setFontSize(18);
	pbuttontext2->setPosition(ccp(pbutton2->getPositionX()+pbutton2->getContentSize().width/2,pbutton2->getPositionY()+pbutton2->getContentSize().height/2));
	pMenu->addChild(pbuttontext2);

	//重置闯关按钮
	CCScale9Sprite* pbutton3spr1=SystemData::getScale9SpriteByPlist("activity_emigrated_button",96,42);
	CCScale9Sprite* pbutton3spr2=SystemData::getScale9SpriteByPlist("activity_emigrated_button.sel",96,42);
	CCMenuItemSprite* pbuttonCZ=CCMenuItemSprite::create(pbutton3spr1,pbutton3spr2,NULL,this,menu_selector(EmigratedLeftMapPanel::menucallback));
	pbuttonCZ->setAnchorPoint(CCPointZero);
	pbuttonCZ->setTag(button_chongzhiroll);
	pbuttonCZ->setPosition(SystemData::getLayoutPoint("activity_emigrated_buttontext3_pos"));
	pMenu->addChild(pbuttonCZ);
	CCLabelTTF* pbuttontextCZ=SystemData::getLabelTTF("activity_emigrated_buttontext3");
	pbuttontextCZ->setColor(ccYELLOW);
	pbuttontextCZ->setFontSize(18);
	pbuttontextCZ->setPosition(ccp(pbuttonCZ->getPositionX()+pbuttonCZ->getContentSize().width/2,pbuttonCZ->getPositionY()+pbuttonCZ->getContentSize().height/2));
	pMenu->addChild(pbuttontextCZ);

	CCLabelTTF* p2=SystemData::getLabelTTF("activity_emigrated_button1_text");
	p2->setPosition(ccp(SystemData::getLayoutValue("activity_emigrated_buttontext1_pos.x"),SystemData::getLayoutValue("activity_emigrated_button1_pos.y")));
	p2->setAnchorPoint(ccp(0,0.5));
	p2->setColor(ccWHITE);
	p2->setFontSize(16);
	pMenu->addChild(p2);

	m_pCntLabel=CCLabelTTF::create("0/0","",18);
	m_pCntLabel->setPosition(ccp(SystemData::getLayoutValue("activity_emigrated_buttontext1_pos.x")+p2->getContentSize().width+5,SystemData::getLayoutValue("activity_emigrated_button1_pos.y")));
	m_pCntLabel->setColor(ccYELLOW);
	m_pCntLabel->setAnchorPoint(ccp(0,0.5));
	pMenu->addChild(m_pCntLabel);

	CCMenuItemImage* pbutton4=SystemData::getMenuItemImageByPlist("activity_emigrated_button1");
	pbutton4->setPosition(SystemData::getLayoutPoint("activity_emigrated_button1_pos"));
	pbutton4->setTarget(this,menu_selector(EmigratedLeftMapPanel::menucallback));
	pbutton4->setTag(button_addcount);
	pMenu->addChild(pbutton4);

	CCLabelTTF* p1=SystemData::getLabelTTF("activity_emigrated_button2_text");
	p1->setPosition(ccp(SystemData::getLayoutValue("activity_emigrated_buttontext1_pos.x"),SystemData::getLayoutValue("activity_emigrated_button2_pos.y")));
	p1->setAnchorPoint(ccp(0,0.5));
	p1->setColor(ccWHITE);
	p1->setFontSize(16);
	pMenu->addChild(p1);

	m_pTimeLabel=CCLabelTTF::create(StringUtils::timeToString(HeroData::getCommonCD(EvtData::cd_cdcscg),TimeType::ms).c_str(),"",18);
	m_pTimeLabel->setPosition(ccp(SystemData::getLayoutValue("activity_emigrated_buttontext1_pos.x")+p2->getContentSize().width+5,SystemData::getLayoutValue("activity_emigrated_button2_pos.y")));
	m_pTimeLabel->setColor(ccYELLOW);
	m_pTimeLabel->setAnchorPoint(ccp(0,0.5));
	pMenu->addChild(m_pTimeLabel);

	CCMenuItemImage* pbutton3=SystemData::getMenuItemImageByPlist("activity_emigrated_button2");
	pbutton3->setPosition(SystemData::getLayoutPoint("activity_emigrated_button2_pos"));
	pbutton3->setTarget(this,menu_selector(EmigratedLeftMapPanel::menucallback));
	pbutton3->setTag(button_addtime);
	pMenu->addChild(pbutton3);
}

void EmigratedLeftMapPanel::addRollPanel()
{
	EmigratedRollPanel* pPanel=EmigratedRollPanel::create();
	pPanel->setPosition(ccp(82,79));
	pPanel->setAnchorPoint(CCPointZero);
	addChild(pPanel);
}

void EmigratedLeftMapPanel::postrandomroll()
{
	MsgCaiShenChuangGuanRandomRequest* msg=new MsgCaiShenChuangGuanRandomRequest;
	HandleMessage::sendMessage(msg);
}

void EmigratedLeftMapPanel::postfreshtime()
{
	MsgCleanCoolDownRequest* msg=new MsgCleanCoolDownRequest;
	msg->cdtype=EvtData::cd_cdcscg;
	HandleMessage::sendMessage(msg);
}

void EmigratedLeftMapPanel::postaddcount()
{
	MsgCaiShenChuangGuanfreshtimeRequest* msg=new MsgCaiShenChuangGuanfreshtimeRequest;
	HandleMessage::sendMessage(msg);
}

void EmigratedLeftMapPanel::handleEvent( int channel )
{
	if (channel==EventProtocol::EVENT_UPDATE_EMIGRATED_DATA)
	{
		int k,newpos;
		ActivityData::getExData(EvtData::evt_cscg,cscg_cnt,k,newpos);
		bool flag=false;
		int a=newpos-cscg_pos;
		if (newpos==cscg_pos)
		{
			flag=true;
		}
		cscg_pos=newpos;
		CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("activity_emigrated_name").c_str(),cscg_pos/100);
		m_pTitleLabel->setString(SystemData::getLayoutString(pStr->getCString()).c_str());

		const int maxCount = cscg_cnt/100;
		const int remainCount = maxCount - cscg_cnt%100;
		CCString* pStrCnt=CCString::createWithFormat("%d/%d", remainCount, maxCount);
		m_pCntLabel->setString(pStrCnt->getCString());
		
		if (a>0 && a<=6)
		{
			if (getChildByTag(sprite_dice))
			{
				this->removeChildByTag(sprite_dice);	
			}	

			CCString* p=CCString::createWithFormat(SystemData::getLayoutString("activity_emigrated_roll").c_str(),a);
			CCSprite* pSprite=SystemData::getSpriteByPlist(p->getCString());
			pSprite->setTag(sprite_dice);
			pSprite->setPosition(SystemData::getLayoutPoint("activity_emigrated_roll_mianpos"));
			addChild(pSprite);
		}

		if (!m_bIsCreateOver && !flag)
		{
			updateRolePos();
		}
		else
		{
			m_pHeroPanel->setPosition(getRolePos(cscg_pos%100));
			m_iCurPos=getRoleIndex(cscg_pos%100);
			m_bIsCreateOver=false;
		}
	}
	if (channel==EventProtocol::EVENT_UPDATE_EMIGRATED_MISSIONUP)
	{
		if (m_pHeroPanel)
		{
			int k;
			ActivityData::getExData(EvtData::evt_cscg,cscg_cnt,k,cscg_pos);
			m_pHeroPanel->stopAllActions();
			CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("activity_emigrated_name").c_str(),cscg_pos/100);
			m_pTitleLabel->setString(SystemData::getLayoutString(pStr->getCString()).c_str());
			m_pHeroPanel->setPosition(getRolePos(cscg_pos%100));

			m_iCurPos=m_mAllMapPos.begin()->first;
		}		
	}
	if (channel==EventProtocol::EVENT_UPDATE_EMIGRATED_ROUNDOVER)
	{
		m_bIsActionOver=true;
	}
	if (channel==EventProtocol::EVENT_UPDATE_EMIGRATED_DATALIST)
	{
		addCase();
	}
}

void EmigratedLeftMapPanel::updateRolePos()
{
	if (m_heroModel==NULL || m_pHeroPanel==NULL)
	{
		GeneralMenu* menu=GeneralMenu::create();
		menu->setAnchorPoint(CCPointZero);
		menu->setPosition(CCPointZero);
		addChild(menu);
		m_pHeroPanel = CCNode::create();
		m_pHeroPanel->setAnchorPoint(CCPointZero);
		m_pHeroPanel->setPosition(getRolePos(cscg_pos%100));
		menu->addChild(m_pHeroPanel,999);

		m_heroModel = HeroModel::create();
		if(!m_heroModel)
		{ 
			return ;
		}
		m_heroModel->update(GameData::s_user->m_pMainRole);
		m_heroModel->setPosition(CCPointZero);
		m_heroModel->attach(m_pHeroPanel);
		m_pHeroPanel->setScale(0.8f);

		m_bIsCreateOver=true;
	}
	else
	{		
		m_bIsCreateOver=false;
		m_bIsActionOver=false;
		//m_pHeroPanel->stopAllActions();
		getCrossPos(m_iCurPos,getRoleIndex(cscg_pos%100));
		std::vector<CCPoint>::iterator it=m_vCrossPos.begin();
		CCArray* pArray=CCArray::create();
		for (it;it!=m_vCrossPos.end();it++)
		{
			CCAction* p=CCMoveTo::create(0.2f,*it);
			pArray->addObject(p);
		}
		m_pHeroPanel->runAction(CCSequence::create(CCSequence::create(pArray),CCCallFunc::create(this,callfunc_selector(EmigratedLeftMapPanel::postwalkover)),NULL));
	}
	
}

int EmigratedLeftMapPanel::getRoleIndex( int pos )
{
	int n=0;
	std::map<int,CCPoint>::iterator it=m_mAllMapPos.begin();
	for (it;it!=m_mAllMapPos.end();it++)
	{
		if (pos==n)
		{
			return it->first;
		}
		n++;
	}
	return 0;
}

cocos2d::CCPoint EmigratedLeftMapPanel::getRolePos( int pos )
{
	int n=0;
	std::map<int,CCPoint>::iterator it=m_mAllMapPos.begin();
	for (it;it!=m_mAllMapPos.end();it++)
	{
		if (pos==n)
		{
			return it->second;
		}
		n++;
	}
	return CCPointZero;
}

void EmigratedLeftMapPanel::getCrossPos( int startindex,int endindex )
{
	m_vCrossPos.clear();
	if (startindex<endindex)
	{
		std::map<int,CCPoint>::iterator it=m_mAllMapPos.begin();
		for (it;it!=m_mAllMapPos.end();it++)
		{
			if (startindex<=it->first && endindex>=it->first)
			{
				m_vCrossPos.push_back(it->second);
			}
		}
	}
	else
	{
		std::map<int,CCPoint>::iterator it=m_mAllMapPos.end();
		std::map<int,CCPoint>::iterator it1=m_mAllMapPos.begin();
		it1--;
		it--;
		for (it;it!=it1;it--)
		{
			if (startindex>=it->first && endindex<=it->first)
			{
				m_vCrossPos.push_back(it->second);
			}
		}
	}
	m_iCurPos=endindex;
	
}

void EmigratedLeftMapPanel::postwalkover()
{
	MsgCaiShenChuangGuanWalkOverRequest* msg=new MsgCaiShenChuangGuanWalkOverRequest;
	HandleMessage::sendMessage(msg);
}

void EmigratedLeftMapPanel::addCase()
{
	if (m_pCaseMenu)
	{
		m_pCaseMenu->removeAllChildren();
	}
	else
	{
		return;
	}
	
	int num=0;
	std::vector<int>::iterator it=Emigrateddata::cscg_list.begin();
	for (it;it!=Emigrateddata::cscg_list.end();it++)
	{
		CCPoint pos=getRolePos(num+1);
		if (*it!=0)
		{
			CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("activity_emigrated_case").c_str(),*it);
			CCMenuItemImage* psprite=SystemData::getMenuItemImageByPlist(pStr->getCString());
			psprite->setPosition(pos);
			psprite->setTarget(this,menu_selector( EmigratedLeftMapPanel::itemcallback));
			psprite->setTag(*it);
			m_pCaseMenu->addChild(psprite);
		}		
		num++;
	}
}

void EmigratedLeftMapPanel::itemcallback( CCObject* pObject )
{
	CCNode* pNode=dynamic_cast<CCNode*>(pObject);
	if (pNode)
	{
		int tag=pNode->getTag();
		EmigratedContentPanel* pPanel=EmigratedContentPanel::create();
		pPanel->setContent(tag);
		pPanel->setAnchorPoint(CCPointZero);
		pPanel->setPosition(SystemData::getLayoutPoint("activity_emigrated_content_pos"));
		addChild(pPanel);
	}
}

void EmigratedLeftMapPanel::onAddCount( int buttonType )
{
	if (buttonType == Button_QD)
	{
		postaddcount();
	}
}

void EmigratedLeftMapPanel::updatetime(int index)
{
	if (m_iTime!=0)
	{
		m_iTime=m_iTime-index;
	}
	//HeroData::setCommonCD(EvtData::cd_cdcscg, m_iTime, 0);
	m_pTimeLabel->setString(StringUtils::timeToString(m_iTime,TimeType::ms).c_str());
}

void EmigratedLeftMapPanel::finishtime()
{
	m_iTime=0;
	m_pTimeLabel->setString(StringUtils::timeToString(m_iTime,TimeType::ms).c_str());
}

void EmigratedLeftMapPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			updatetime(1);
		}
	}
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdBaseCoolDownNotify")
		{
			m_iTime=HeroData::getCommonCD(EvtData::cd_cdcscg);
		}
	}
}

void EmigratedLeftMapPanel::floatpanelCallback(int tag )
{
	switch (tag)
	{
    	case 0:
		    postfreshtime();
			break;
		default:
			break;

	}
	
}

void EmigratedLeftMapPanel::floatpanelCallback2(int tag )
{
	switch (tag)
	{
	case 0:
		restartRequest();
		break;
	default:
		break;

	}

}

void EmigratedLeftMapPanel::restartRequest()
{
	MsgCaiShenChuangGuanReStartRequest* msg=new MsgCaiShenChuangGuanReStartRequest;
	HandleMessage::sendMessage(msg);
}

//-------------------------------------------------------------------------------------//

EmigratedRightTopPanel::EmigratedRightTopPanel()
{

}

EmigratedRightTopPanel* EmigratedRightTopPanel::create()
{
	EmigratedRightTopPanel* pPanel=new EmigratedRightTopPanel;
	if (pPanel && pPanel->init())
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

EmigratedRightTopPanel::~EmigratedRightTopPanel()
{

}

bool EmigratedRightTopPanel::init()
{
	initInterFace();
	return true;
}

void EmigratedRightTopPanel::initInterFace()
{
	CCScale9Sprite* pborder1=SystemData::getScale9SpriteByPlist("activity_emigrated_border",SystemData::getLayoutValue("activity_emigrated_border3_size.w"),SystemData::getLayoutValue("activity_emigrated_border3_size.h"));
	pborder1->setAnchorPoint(CCPointZero);
	pborder1->setPosition(SystemData::getLayoutPoint("activity_emigrated_border3_pos"));
	addChild(pborder1);

	CCSprite* ptitlebkg=SystemData::getSpriteByPlist("activity_emigrated_smallbkg");
	ptitlebkg->setPosition(ccp(pborder1->getContentSize().width/2,pborder1->getContentSize().height/2-1));
	pborder1->addChild(ptitlebkg);

	CCLabelTTF* ptext=SystemData::getLabelTTF("activity_emigrated_Righttext1");
	ptext->setFontSize(20);
	ptext->setColor(ccORANGE);
	ptext->setPosition(ptitlebkg->getPosition());
	pborder1->addChild(ptext);

	CCScale9Sprite* pborder2=SystemData::getScale9SpriteByPlist("activity_emigrated_border",SystemData::getLayoutValue("activity_emigrated_border4_size.w"),SystemData::getLayoutValue("activity_emigrated_border4_size.h"));
	pborder2->setAnchorPoint(CCPointZero);
	pborder2->setPosition(SystemData::getLayoutPoint("activity_emigrated_border4_pos"));
	addChild(pborder2);

	CCTableViewEx* pTabelView=CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("activity_emigrated_border4_size").width-10,SystemData::getLayoutSize("activity_emigrated_border4_size").height-5),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(ccp(SystemData::getLayoutPoint("activity_emigrated_border4_pos").x+5,SystemData::getLayoutPoint("activity_emigrated_border4_pos").y+2));
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	//pTabelView->showBottom();
	addChild(pTabelView);
}

cocos2d::CCSize EmigratedRightTopPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutValue("activity_emigrated_border4_size.w")-10,m_iHeight);
}

cocos2d::extension::CCTableViewCell* EmigratedRightTopPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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

		CPRichText* ptext=RichTextUtils::getRichText(SystemData::getLayoutString("Emigrated_ReadMe"),18,SystemData::getLayoutValue("activity_emigrated_border4_size.w")-10,0);
		ptext->setPosition(CCPointZero);
		ptext->setAnchorPoint(CCPointZero);
		pLayer->addChild(ptext);
		m_iHeight=ptext->getContentSize().height;
	}
	return cell;
}

unsigned int EmigratedRightTopPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

//---------------------------------------------------------------------------------------------------//

EmigratedRightDownPanel* EmigratedRightDownPanel::create()
{
	EmigratedRightDownPanel* pPanel=new EmigratedRightDownPanel;
	if (pPanel && pPanel->init())
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

EmigratedRightDownPanel::EmigratedRightDownPanel():
	m_pTabelView(NULL)
{

}

EmigratedRightDownPanel::~EmigratedRightDownPanel()
{

}

bool EmigratedRightDownPanel::init()
{
	initInterFace();
	return true;
}

void EmigratedRightDownPanel::initInterFace()
{
	CCScale9Sprite* pborder1=SystemData::getScale9SpriteByPlist("activity_emigrated_border",SystemData::getLayoutValue("activity_emigrated_border5_size.w"),SystemData::getLayoutValue("activity_emigrated_border5_size.h"));
	pborder1->setAnchorPoint(CCPointZero);
	pborder1->setPosition(SystemData::getLayoutPoint("activity_emigrated_border5_pos"));
	addChild(pborder1);

	CCSprite* ptitlebkg=SystemData::getSpriteByPlist("activity_emigrated_smallbkg");
	ptitlebkg->setPosition(ccp(pborder1->getContentSize().width/2,pborder1->getContentSize().height/2-1));
	pborder1->addChild(ptitlebkg);

	CCLabelTTF* ptext=SystemData::getLabelTTF("activity_emigrated_Righttext2");
	ptext->setFontSize(20);
	ptext->setColor(ccORANGE);
	ptext->setPosition(ptitlebkg->getPosition());
	pborder1->addChild(ptext);

	CCScale9Sprite* pborder2=SystemData::getScale9SpriteByPlist("activity_emigrated_border",SystemData::getLayoutValue("activity_emigrated_border6_size.w"),SystemData::getLayoutValue("activity_emigrated_border6_size.h"));
	pborder2->setAnchorPoint(CCPointZero);
	pborder2->setPosition(SystemData::getLayoutPoint("activity_emigrated_border6_pos"));
	addChild(pborder2); 


	m_pTabelView=CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("activity_emigrated_border6_size").width-10,SystemData::getLayoutSize("activity_emigrated_border6_size").height-5),kCCScrollViewDirectionVertical,this,NULL);
	m_pTabelView->setAnchorPoint(CCPointZero);
	m_pTabelView->setPosition(ccp(SystemData::getLayoutPoint("activity_emigrated_border6_pos").x+5,SystemData::getLayoutPoint("activity_emigrated_border6_pos").y+2));
	m_pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	//pTabelView->showBottom();
	addChild(m_pTabelView);

}

void EmigratedRightDownPanel::handleEvent( int channel )
{
	if (channel==EventProtocol::EVENT_UPDATE_EMIGRATED_ROUNDOVER)
	{
		//m_vCaseList.clear();
		if (m_pTabelView)
		{
			m_pTabelView->reloadData();
			if (m_iHeight>SystemData::getLayoutValue("activity_emigrated_border6_size.h")-10)
			{
				m_pTabelView->showBottom();
				//m_pTabelView->setContentOffset(ccp(0,20));
			}
		}
	}
}

cocos2d::CCSize EmigratedRightDownPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutValue("activity_emigrated_border6_size.w")-10,m_iHeight+20);
}

cocos2d::extension::CCTableViewCell* EmigratedRightDownPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer=getCaseList();
		pLayer->setPosition(ccp(0,20));
		pLayer->setAnchorPoint(CCPointZero);
		cell->addChild(pLayer);
	}
	return cell;
}

unsigned int EmigratedRightDownPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

CCLayer* EmigratedRightDownPanel::getCaseList()
{
	m_iHeight=0;
	CCLayer* pLayer=CCLayer::create();
	std::vector<stepcase>::iterator it=Emigrateddata::cscg_caselist.end();
	CCPoint pos=CCPointZero;
	if (Emigrateddata::cscg_caselist.size()!=0)
	{
		do
		{
			it--;
			CCSprite* p=getCaseSprite(*it);
			p->setAnchorPoint(CCPointZero);
			p->setPosition(ccp(pos.x,pos.y));
			pLayer->addChild(p);
			pos=ccp(pos.x,pos.y+p->getContentSize().height);
			m_iHeight+=p->getContentSize().height;
		}while(it!=Emigrateddata::cscg_caselist.begin());
	}	
	return pLayer;
}

CCSprite* EmigratedRightDownPanel::getCaseSprite(stepcase caseinfo)
{
	CCSprite* pSprite=CCSprite::create();
	std::string str=AToU8("您触发");
	std::string name;
	LuaData::getProp("gdEmigrated",caseinfo.type,"name",name);
	str=str+"["+name+"]";
	CCLabelTTF* pLabel=CCLabelTTF::create(str.c_str(),"",18);
	pLabel->setAnchorPoint(CCPointZero);
	pLabel->setPosition(CCPointZero);
	pSprite->addChild(pLabel);
	pSprite->setContentSize(pLabel->getContentSize());
	return pSprite;
}

//----------------------------------------------------------------------------------------------------------------------//

EmigratedRollPanel* EmigratedRollPanel::create()
{
	EmigratedRollPanel* pPanel=new EmigratedRollPanel;
	if (pPanel && pPanel->init())
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

EmigratedRollPanel::EmigratedRollPanel():
	m_iCurSelect(0),
	m_pRollMenu(NULL)
{

}

EmigratedRollPanel::~EmigratedRollPanel()
{

}

/**
 * EmigratedRollPanel::init() 初始化函数
 * 功能：初始化移民抽奖/转盘面板的基本参数和界面
 * 返回: bool - 初始化是否成功
 */
bool EmigratedRollPanel::init()
{
	// 1. 设置面板的高度和宽度（基于520x1200的设计分辨率）
	// 注意：这里先设置高度，再设置宽度，顺序与之前的代码示例相反
	m_nHeight = 480;  // 注释：对应480的换算值      这改了
	m_nWidth = 800;  // 注释：对应800全屏的换算值
	
	// 2. 添加带偏移的覆盖层（半透明黑色遮罩）
	// 参数说明：偏移量为(-82, -79)，可能是为了视觉对齐或特殊布局需求
	// 偏移量负值表示向左和向下偏移
	addCover(ccp(-82, -79));
	
	// 3. 初始化基础界面元素
	// 调用initInterFace()函数创建背景、标题栏、装饰元素和关闭按钮等
	initInterFace();
	
	// 4. 初始化抽奖/转盘面板
	// 调用initrollPanel()函数创建抽奖转盘的具体UI元素
	initrollPanel();
	
	// 5. 初始化成功，返回true
	return true;
}

void EmigratedRollPanel::initInterFace()
{
	CCScale9Sprite* pborder=SystemData::getScale9SpriteByPlist("activity_emigrated_rollborder",SystemData::getLayoutValue("activity_emigrated_rollpanel_size.w"),SystemData::getLayoutValue("activity_emigrated_rollpanel_size.h"));
	pborder->setAnchorPoint(CCPointZero);
	pborder->setPosition(CCPointZero);
	addChild(pborder);

	CCLabelTTF* needYuanBao = SystemData::getLabelTTF("activity_emigrated_yaokongNeedyuanbao");
	needYuanBao->setColor(ccYELLOW);
	needYuanBao->setFontSize(18);
	needYuanBao->setAnchorPoint(CCPointZero);
	needYuanBao->setPosition(SystemData::getLayoutPoint("yaokongNeedyuanbao_pos"));
	addChild(needYuanBao);
	  
	CCMenu* pMenu=CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCMenuItemImage* pClose=SystemData::getMenuItemImageByPlist("activity_emigrated_close");
	pClose->setTarget(this,menu_selector(EmigratedRollPanel::menucallback));
	pClose->setPosition(SystemData::getLayoutPoint("activity_emigrated_close_pos"));
	pClose->setTag(button_close);
	pMenu->addChild(pClose);
}

void EmigratedRollPanel::menucallback( CCObject* pSender )
{
	CCNode* pNode=dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag=pNode->getTag();
		switch (tag)
		{		
		case button_close:
			this->removeFromParent();
			break;
		case button_ok:
			if (m_iCurSelect<=6 && m_iCurSelect>=1)
			{
				//发送遥控roll点消息
				postselectnum();
				this->removeFromParent();
			}
			else
			{
				//提示需要选择点数
			}
			break;
		case button_cancel:
			this->removeFromParent();
			break;
		case button_num1:
			initrollborder();
			m_iCurSelect=button_num1-10;
			m_pRollMenu->getChildByTag(tag+10)->setVisible(true);
			break;
		case button_num2:
			initrollborder();
			m_iCurSelect=button_num2-10;
			m_pRollMenu->getChildByTag(tag+10)->setVisible(true);
			break;
		case button_num3:
			initrollborder();
			m_iCurSelect=button_num3-10;
			m_pRollMenu->getChildByTag(tag+10)->setVisible(true);
			break;
		case button_num4:
			initrollborder();
			m_iCurSelect=button_num4-10;
			m_pRollMenu->getChildByTag(tag+10)->setVisible(true);
			break;
		case button_num5:
			initrollborder();
			m_iCurSelect=button_num5-10;
			m_pRollMenu->getChildByTag(tag+10)->setVisible(true);
			break;
		case button_num6:
			initrollborder();
			m_iCurSelect=button_num6-10;
			m_pRollMenu->getChildByTag(tag+10)->setVisible(true);
			break;
		default:
			break;
		}
	}
}

void EmigratedRollPanel::initrollPanel()
{
	m_pRollMenu=GeneralMenu::create();
	m_pRollMenu->setPosition(CCPointZero);
	m_pRollMenu->setAnchorPoint(CCPointZero);
	addChild(m_pRollMenu);

	for (int i=0;i<6;i++)
	{
		CCString* pName=CCString::createWithFormat(SystemData::getLayoutString("activity_emigrated_roll").c_str(),i+1);
		CCMenuItemImage* pItem=SystemData::getMenuItemImageByPlist(pName->getCString());
		pItem->setPosition(ccp(SystemData::getLayoutPoint("activity_emigrated_roll_pos").x+i*100,SystemData::getLayoutPoint("activity_emigrated_roll_pos").y));
		pItem->setTarget(this,menu_selector(EmigratedRollPanel::menucallback));
		pItem->setTag(button_num1+i);
		m_pRollMenu->addChild(pItem);

		CCSprite* pborder=SystemData::getSpriteByPlist("activity_emigrated_rollbuttonborder");
		pborder->setPosition(pItem->getPosition());
		pborder->setTag(border_num1+i);
		pborder->setVisible(false);
		m_pRollMenu->addChild(pborder);
	}

	CCMenuItemImage* pLeftButton=SystemData::getScale9MenuItemImageByPlist("activity_emigrated_rollbutton");
	pLeftButton->setAnchorPoint(CCPointZero);
	pLeftButton->setTarget(this,menu_selector(EmigratedRollPanel::menucallback));
	pLeftButton->setPosition(SystemData::getLayoutPoint("activity_emigrated_rollbutton1_pos"));
	pLeftButton->setTag(button_ok);
	m_pRollMenu->addChild(pLeftButton);
	//CCLabelTTF::create(AToU8("确定"),"",18)
	CCLabelTTF* pLeftLabel= SystemData::getLabelTTF("panel_QueDing_label");
	pLeftLabel->setFontSize(18);
	pLeftLabel->setPosition(ccp(pLeftButton->getPositionX()+pLeftButton->getContentSize().width/2,pLeftButton->getPositionY()+pLeftButton->getContentSize().height/2));
	m_pRollMenu->addChild(pLeftLabel);

	CCMenuItemImage* pRightButton=SystemData::getScale9MenuItemImageByPlist("activity_emigrated_rollbutton");
	pRightButton->setAnchorPoint(CCPointZero);
	pRightButton->setTarget(this,menu_selector(EmigratedRollPanel::menucallback));
	pRightButton->setPosition(SystemData::getLayoutPoint("activity_emigrated_rollbutton2_pos"));
	pRightButton->setTag(button_cancel);
	m_pRollMenu->addChild(pRightButton);

	CCLabelTTF* prightLabel= SystemData::getLabelTTF("panel_QuXiao_label");
	prightLabel->setFontSize(18);
	prightLabel->setPosition(ccp(pRightButton->getPositionX()+pRightButton->getContentSize().width/2,pRightButton->getPositionY()+pRightButton->getContentSize().height/2));
	m_pRollMenu->addChild(prightLabel);
}

void EmigratedRollPanel::initrollborder()
{
	for (int i=0;i<6;i++)
	{
		m_pRollMenu->getChildByTag(border_num1+i)->setVisible(false);
	}
}

void EmigratedRollPanel::postselectnum()
{
	MsgCaiShenChuangGuanSelectRequest* msg=new MsgCaiShenChuangGuanSelectRequest;
	msg->rollnum=m_iCurSelect;
	HandleMessage::sendMessage(msg);
}

//----------------------------------------------------------------------------------------------------------------------------//

EmigratedContentPanel* EmigratedContentPanel::create()
{
	EmigratedContentPanel* pPanel=new EmigratedContentPanel;
	if (pPanel && pPanel->init())
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

EmigratedContentPanel::EmigratedContentPanel()
{

}

EmigratedContentPanel::~EmigratedContentPanel()
{

}

bool EmigratedContentPanel::init()
{
	m_nWidth=SystemData::getLayoutValue("activity_emigrated_content_size.w");
	m_nHeight=SystemData::getLayoutValue("activity_emigrated_content_size.h");
	addCover(CCPointZero);

	CCScale9Sprite* pborder=SystemData::getScale9SpriteByPlist("activity_emigrated_content",SystemData::getLayoutValue("activity_emigrated_content_size.w"),SystemData::getLayoutValue("activity_emigrated_content_size.h"));
	pborder->setPosition(CCPointZero);
	pborder->setAnchorPoint(CCPointZero);
	addChild(pborder);

	CCSprite* pSprite=SystemData::getSpriteByPlist("activity_emigrated_contentfengetiao");
	pSprite->setAnchorPoint(CCPointZero);
	pSprite->setPosition(SystemData::getLayoutPoint("activity_emigrated_contentfengetiao_pos"));
	addChild(pSprite);

	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCMenuItemImage* pClose=SystemData::getMenuItemImageByPlist("activity_emigrated_close");
	pClose->setPosition(SystemData::getLayoutPoint("activity_emigrated_contentclose_pos"));
	pClose->setTarget(this,menu_selector(EmigratedContentPanel::menucallback));
	pClose->setTag(button_close);
	pMenu->addChild(pClose);
	return true;
}

void EmigratedContentPanel::menucallback( CCObject* pSender )
{
	CCNode* pNode=dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag=pNode->getTag();
		switch (tag)
		{		
		case button_close:
			this->removeFromParent();
			break;
		default:
			break;
		}
	}
}

void EmigratedContentPanel::setContent( int num )
{
	std::string name;
	LuaData::getProp("gdEmigrated",num,"name",name);
	name="["+name+"]";
	CCLabelTTF* pName=CCLabelTTF::create(name.c_str(),"",20);
	pName->setColor(ccYELLOW);
	pName->setPosition(SystemData::getLayoutPoint("activity_emigrated_contenttitle_pos"));
	pName->setAnchorPoint(ccp(0,0.5));
	addChild(pName);

	std::string content;
	LuaData::getProp("gdEmigrated",num,"content",content);
	CCLabelTTF* pcontent=CCLabelTTF::create(content.c_str(),"",18);
	pcontent->setAnchorPoint(ccp(0,1));
	pcontent->setDimensions(CCSizeMake(280,180));
	pcontent->setHorizontalAlignment(kCCTextAlignmentLeft);
	pcontent->setPosition(SystemData::getLayoutPoint("activity_emigrated_contentsub_pos"));
	addChild(pcontent);
}

bool EmigratedContentPanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void EmigratedContentPanel::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void EmigratedContentPanel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos=pTouch->getLocation();
	CCRect rect=CCRectMake(0,0,SystemData::getLayoutValue("activity_emigrated_content_size.w"),SystemData::getLayoutValue("activity_emigrated_content_size.h"));
	if (!rect.containsPoint( this->convertToNodeSpace(pos)))
	{
		this->removeFromParent();
	}
}

void EmigratedContentPanel::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}


//----------------------------------------------------------------------------------------------------------------------------------------------//


EmigratedRightTopPanelTask::EmigratedRightTopPanelTask()
	:m_iCurrentQuestID(0)
{

}

EmigratedRightTopPanelTask* EmigratedRightTopPanelTask::create()
{
	EmigratedRightTopPanelTask* pPanel=new EmigratedRightTopPanelTask;
	if (pPanel && pPanel->init())
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

EmigratedRightTopPanelTask::~EmigratedRightTopPanelTask()
{

}

bool EmigratedRightTopPanelTask::init()
{
	m_iCurrentQuestID = TaskData::getFirstTask(Quest::line_Emigrated);//
	initTaskPanel();
	return true;
}

void EmigratedRightTopPanelTask::initTaskPanel()
{
	CCScale9Sprite* pborder1=SystemData::getScale9SpriteByPlist("activity_emigrated_border",SystemData::getLayoutValue("activity_emigrated_border3_size.w"),SystemData::getLayoutValue("activity_emigrated_border3_size.h"));
	pborder1->setAnchorPoint(CCPointZero);
	pborder1->setPosition(SystemData::getLayoutPoint("activity_emigrated_border3_pos"));
	addChild(pborder1);

	CCSprite* ptitlebkg=SystemData::getSpriteByPlist("activity_emigrated_smallbkg");
	ptitlebkg->setPosition(ccp(pborder1->getContentSize().width/2,pborder1->getContentSize().height/2-1));
	pborder1->addChild(ptitlebkg);

	CCLabelTTF* ptext=SystemData::getLabelTTF("activity_emigrated_Righttext_TaskMammon");
	ptext->setFontSize(20);
	ptext->setColor(ccORANGE);
	ptext->setPosition(ptitlebkg->getPosition());
	pborder1->addChild(ptext);

	CCScale9Sprite* pborder2=SystemData::getScale9SpriteByPlist("activity_emigrated_border",SystemData::getLayoutValue("activity_emigrated_border4_size.w"),SystemData::getLayoutValue("activity_emigrated_border4_size.h"));
	pborder2->setAnchorPoint(CCPointZero);
	pborder2->setPosition(SystemData::getLayoutPoint("activity_emigrated_border4_pos"));
	addChild(pborder2);

    CCTableViewEx* pTabelView=CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("activity_emigrated_border4_size").width-10,SystemData::getLayoutSize("activity_emigrated_border4_size").height-5),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(ccp(SystemData::getLayoutPoint("activity_emigrated_border4_pos").x+5,SystemData::getLayoutPoint("activity_emigrated_border4_pos").y+2));
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	addChild(pTabelView);
}

cocos2d::CCSize EmigratedRightTopPanelTask::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutValue("activity_emigrated_border4_size.w")-10,m_iHeight);
}

cocos2d::extension::CCTableViewCell* EmigratedRightTopPanelTask::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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

		m_iHeight = 0;
		std::string str;
		LuaData::getProp(LuaData::QUEST,m_iCurrentQuestID,"des",str);

		CPRichText* ptext=RichTextUtils::getRichText(str,18,SystemData::getLayoutValue("activity_emigrated_border4_size.w")-10,0);
		ptext->setPosition(CCPointZero);
		ptext->setAnchorPoint(ccp(0,1));
		pLayer->addChild(ptext);

		GeneralMenu *menuBack = GeneralMenu::create();
		menuBack->setPosition(CCPointZero);
		menuBack->setAnchorPoint(CCPointZero); 
		CCString *pStr=NPCFunctionData::getCString(m_iCurrentQuestID,12);			
		CCMenuItemFont *pLabel1=CCMenuItemFont::create(pStr->getCString(),this,menu_selector(EmigratedRightTopPanelTask::gotoNPC));
		pLabel1->setFontSizeObj(16);
		pLabel1->setAnchorPoint(ccp(0,1));
		menuBack->addChild(pLabel1);

    	//-----------------------------------------------------------------------------------------------//
		m_iHeight=ptext->getContentSize().height+pLabel1->getContentSize().height + 100;

		ptext->setPosition(ccp(0,m_iHeight));
		pLabel1->setPosition(ccp(0,m_iHeight-ptext->getContentSize().height-20));
		
		//------------------------------------------------------------------------------------------------//
		CCMenuItemImage *pShoes=SystemData::getMenuItemImageByPlist("tasktips_shoes");	
		pShoes->setTag(5);
		pShoes->setScale(0.5f);
		pShoes->setPosition(ccp(170,90));
		
		menuBack->addChild(pShoes);
		pShoes->setTarget(this,menu_selector(EmigratedRightTopPanelTask::quickFinishCB2));

		if (TaskData::getTaskState(m_iCurrentQuestID)==Quest::state_NotFinished)
		{
			const ccColor3B &color = LayoutData::getColor3(CPModuleName::COMMON, "yellow");
			std::string strQ = SystemData::getLayoutString("taskcontent_quickfinishquest");
			CCMenuItemFont *pQuickFinish=CCMenuItemFont::create(strQ.c_str(),this,menu_selector(EmigratedRightTopPanelTask::quickFinishQuest));
			pQuickFinish->setFontSizeObj(18);
			pQuickFinish->setColor(color);
			pQuickFinish->setPosition(ccp(40, 55));
			menuBack->addChild(pQuickFinish);
		}

		cell->addChild(menuBack);
	}
	return cell;
}

unsigned int EmigratedRightTopPanelTask::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void EmigratedRightTopPanelTask::quickFinishQuest( CCObject* pSender )
{
	Game::getGameUI()->showFloatPanel(FloatPanelType::Quest_QuickFinish);
	if (Game::getGameUI()->getPanel(TAG_FLOAT_PANEL))
	{
		FloatPanel* pPanel = dynamic_cast<FloatPanel*>(Game::getGameUI()->getPanel(TAG_FLOAT_PANEL));
		pPanel->setHandler(this,floatpanel_selector(EmigratedRightTopPanelTask::quickFinishCB));
	}
}

void EmigratedRightTopPanelTask::quickFinishCB2(CCObject* pSender)
{
	CCNode * pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		if (tag==5)
		{
			NPCFunctionData::getShoesFunc(m_iCurrentQuestID,TAG_GOTONPC);
		}
	}
}

void EmigratedRightTopPanelTask::quickFinishCB(int tag)
{
	if (tag==0)
	{
		NPCFunctionData::QuickQuest(m_iCurrentQuestID);
	}
}

void EmigratedRightTopPanelTask::gotoNPC(CCObject* pSender)
{
	this->getParent()->getParent()->removeFromParent();
	NPCFunctionData::dealwithQuest(m_iCurrentQuestID);
	
}
