#include "MainPanel.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "ext/CCMenuItemFontEx.h"
#include "ext/GeneralMenu.h"

#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "ext/TouchCover.h"

#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"

#include "scene/panel/functionPanel/DesignationPanel.h"
#include "TaskPanel.h"
#include "ForgingPanel/ForgingMainPanel.h"
#include "ForgingPanel/MergeMainPanel.h"
#include "functionPanel/CommonPanel.h"
#include "scene/panel/functionPanel/BoothPanel.h"
#include "scene/panel/guild/GuildPanel.h"
#include "scene/panel/functionPanel/ActivityPanel.h"
#include "scene/panel/HonorPanel.h"
#include "scene/panel/setting/SettingMainPanel.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/functionPanel/BagCellPanel.h"
#include "scene/panel/functionPanel/BagPanel.h"
#include "scene/panel/guide/GuideHelper.h"
#include "controls/CPNodeHelper.h"
#include "event/CPEventDispatcher.h"
#include "userdata/HeroData.h"
#include "FloatPanel.h"
#include "scene/panel/ForgingPanel/WPHCpanel.h"
#include "scene/panel/vip/VipPanel.h"


MainPanel::MainPanel():
	m_pMainMenu(NULL),
	m_pCurrentItem(NULL),
	m_pRightMenu(NULL),
	m_pTabelViewEx(NULL),
	m_iCurItemTag(0),
	m_MaxCellCount(0)
{

	CPEvtDispatcher.addEventListener(CPEventName::UI_OPEN, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_CLOSE, this);
}

MainPanel::~MainPanel()
{

	CPEvtDispatcher.removeEventListener(CPEventName::UI_OPEN, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_CLOSE, this);
}

MainPanel* MainPanel::create(int tag)
{
	MainPanel* pPanel = new MainPanel();
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
		CCLog("MainPanel create failed!");
	}
	return NULL;
}


bool MainPanel::init( const char* filename )
{	
	if (!CCLayer::init())
	{
		return false;
	}

	const CCSize &WinSize=CCDirector::sharedDirector()->getWinSize();	

	setAnchorPoint(ccp(0.5,0.5));
	m_nWidth = WinSize.width;
	m_nHeight = WinSize.height;
	addCover();//保证点击事件

	checkPanel();

	//背景
	CCScale9Sprite* bkg = SystemData::getScale9SpriteByPlist("ui_func.zuidiceng");
	bkg->setAnchorPoint(CCPointZero);
	bkg->setPosition(CCPointZero);
	addChild(bkg);

	//右侧顶部背景
	CCSprite* rightTopbkg = SystemData::getSpriteByPlist("ui_func.biaotilanmu");
	rightTopbkg->setAnchorPoint(ccp(0,1));
	rightTopbkg->setPosition(ccp(-3,475));
	addChild(rightTopbkg);

	//左侧功能框底层
	
	CCSprite* leftbkg = SystemData::getSpriteByPlist("ui_func.gongnengdibang");
	leftbkg->setAnchorPoint(CCPointZero);
	leftbkg->setPosition(CCPointZero);
	addChild(leftbkg);

	//----------------------按钮加载-----------------------------//
	m_pRightMenu=CCLayer::create();
	m_pRightMenu->setPosition(SystemData::getLayoutPoint("ui_func.rightmenu.pos"));
	addChild(m_pRightMenu);
	

	m_pTabelViewEx=CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("ui_func.bkg.size").width,SystemData::getLayoutSize("ui_func.bkg.size").height),kCCScrollViewDirectionVertical,this,NULL);
	m_pTabelViewEx->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTabelViewEx->setAnchorPoint(CCPointZero);
	m_pTabelViewEx->setPosition(ccp(8,25));
	m_pTabelViewEx->setIsadjust(true);
	addChild(m_pTabelViewEx);		

	//addPanel(TAG_Role_Panel);

	std::string panelname=CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (panelname=="MainPanel")
	{
		int data1=CPEventHelper::getEventIntData(CPEventData::VALUE_2);		
		if ((data1>=TAG_Role_Panel && data1<TAG_Max_Panel) || data1==TAG_Booth_Panel || data1==TAG_TreasureDepot_Panel)
		{
			addPanel(data1);
		}
	}
	else
	{
		MenuCallBack(m_pCurrentItem);
	}
	m_pTabelViewEx->reloadData(); 


	m_pMainMenu=CCMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setTouchPriority(kCCMenuHandlerPriority);
	addChild(m_pMainMenu);

	//关闭按钮
	CCMenuItemImage* pClose=SystemData::getMenuItemImageByPlist("ui_func.tuichu");
	pClose->setPosition(SystemData::getLayoutPoint("ui_func.tuichu.pos"));
	pClose->setTag(ClosePanel);
	pClose->setTarget(this,menu_selector(MainPanel::CloseCallBack));
	m_pMainMenu->addChild(pClose);		
	return true;
}

void MainPanel::onEnter()
{
	BasePanel::onEnter();
	setScale(0.0f);
	CPEventHelper::dispatcher(CPEventName::UI_FINISH, "MainPanel|onEnter", "");
	runAction(CPNodeHelper::getScaleToBig());	
}

void MainPanel::onExit()
{
	CPEventHelper::dispatcher(CPEventName::UI_FINISH, "MainPanel|onExit", "");
	BasePanel::onExit();
}

void MainPanel::initLeftFunc(CCMenuItemImage* pItem )
{		
	if (m_pCurrentItem)
	{
		std::string strNormalImage=func[m_pCurrentItem->getTag()];
		CCSprite* pNormalImage = pNormalImage=SystemData::getSpriteByPlist(strNormalImage.c_str());
		m_pCurrentItem->setNormalImage(pNormalImage);
		//m_pCurrentItem->unselected();
	}
	m_pCurrentItem=pItem;
	//m_pCurrentItem->selected();
	std::string strSelectImage=func[pItem->getTag()]+".sel";
	CCSprite* pSelectImage = SystemData::getSpriteByPlist(strSelectImage.c_str());
	m_pCurrentItem->setNormalImage(pSelectImage);	
	m_iCurItemTag=pItem->getTag();
}


void MainPanel::MenuCallBack( CCObject* pSender )
{
	//m_pRightMenu->removeAllChildren();
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		initLeftFunc((CCMenuItemImage*)pNode);
		addPanel(topTag[tag]);
	}
}


cocos2d::CCSize MainPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(85, 57);
}

cocos2d::extension::CCTableViewCell* MainPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		/*

		if (!GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA) && topTag[idx]==TAG_Enhance_Panel)
		{
		return cell;
		}*/

		CCMenuEx* pMenu = CCMenuEx::create(NULL,NULL);
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(ccp(0,2));
		pMenu->setTag(0);
		cell->addChild(pMenu);
				
		CCMenuItemImage* pFuncItem=SystemData::getMenuItemImageByPlist(func[idx]);		
		pFuncItem->setSelectedImage(NULL);
		pFuncItem->setAnchorPoint(CCPointZero);
		pFuncItem->setTag(idx);
		pFuncItem->setTarget(this,menu_selector(MainPanel::MenuCallBack));
		pMenu->addChild(pFuncItem);	

		if (m_iCurItemTag==topTag[idx])
		{
			std::string strSelectImage=func[idx]+".sel";
			CCSprite* pSelectImage = SystemData::getSpriteByPlist(strSelectImage.c_str());
			pFuncItem->setNormalImage(pSelectImage);	

			m_pCurrentItem=pFuncItem;
		}

	}
	return cell;
}

unsigned int MainPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return m_MaxCellCount;
}

void MainPanel::addPanel( int tag, int type,bool isHighBooth)
{
	if (m_pRightMenu->getChildByTag(tag) && type==-1  && tag!=TAG_Friend_Panel)
	{
		return;
	}
	CCLayer* pPanel=NULL;
	bool isFriendPanel = false;
	m_iCurItemTag=tag;
	switch (tag)
	{
	case  TAG_Role_Panel:
		if(type==-1)
		{
			type=AVATAR;
		}
		pPanel=CommonPanel::create(type);
		break;
	case  TAG_Task_Panel:
		pPanel=TaskContentPanel::create();
		break;
	case  TAG_Activity_Panel:
		pPanel = ActivityPanel::create();
		break;
	case  TAG_Enhance_Panel:
		if(type==-1)
		{
			type=TAG_ZBQH;
		}
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA)) 
		{
			pPanel=ForgingMainPanel::create(type);
		}
		break;
	case  TAG_Merge_Panel:
		if(type==-1)
		{
			type=TAG_LZ;
		}
		if(GuideHelper::canOpenFunction(FunctionName::HE_CHENG))
		{
			pPanel=MergeMainPanel::create(type);
		}
		break;
	case  TAG_Honor_Panel:
		pPanel=HonorPanel::create();		
		break;
	case  TAG_Society_Panel:
		pPanel=GuildPanel::create();		
		break;
	case  TAG_Friend_Panel:
		if(type==-1)
		{
			type=AVATAR;
		}
		pPanel=CommonPanel::create(type);
		isFriendPanel=true;		
		break;
	case  TAG_Setting_Panel:
		pPanel=SettingMainPanel::create();
		break;
	case  TAG_Booth_Panel:
		pPanel=BoothPanel::create(type,isHighBooth);
		break;
	case  TAG_TreasureDepot_Panel:
		pPanel=CommonPanel::create(AVATAR,WAREHOUSE);
		break;
	case TAG_VIP_Panel:
		pPanel=VipPanel::create();
		break;
	case TAG_Designation_Panel:
		pPanel=Design::create();
		break;
	}
	if (pPanel)
	{
		m_pRightMenu->removeAllChildren();
		pPanel->setTag(tag);
		pPanel->setPosition(CCPointZero);
		pPanel->setAnchorPoint(CCPointZero);
		m_pRightMenu->addChild(pPanel);

		if (isFriendPanel)
		{
			m_iCurItemTag=0;
			m_pTabelViewEx->reloadData();
			CPEventHelper::openPanel("SocialPanel");
		}
	}	
	else
	{
		CPEventHelper::uiNotify("","",Error::NotOpenNewFunc);	
	}
}

void MainPanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_TURNTO_HSHC)
	{
		//CCLog("Event Recieve");
		addPanel(TAG_Merge_Panel,TAG_HSHC); 
	}
	else if (channel == EventProtocol::EVENT_TURNTO_BTJM)
	{
		addPanel(TAG_Booth_Panel,Booth_Sell); 
	}
	else if (channel == EventProtocol::EVENT_TURNTO_BTJM_H)
	{
		addPanel(TAG_Booth_Panel,Booth_Sell,true); 
	}
	else if (channel == EventProtocol::EVENT_TURNTO_OTHERBTJM)
	{
		addPanel(TAG_Booth_Panel,Booth_Buy); 
	}
	else if (channel == EventProtocol::EVENT_TURNTO_HSXQ)
	{
		addPanel(TAG_Role_Panel,WRAITHSTONE); 
		//((CommonPanel* )(m_pRightMenu->getChildByTag(TAG_Role_Panel)))->initRightTop(WRAITHSTONE); 
	}
}

void MainPanel::showOtherPanel( int openpanel )
{
	bool flag = false;
	switch (openpanel)
	{
	case 1://灵珠合成界面
		if(GuideHelper::canOpenFunction(FunctionName::HE_CHENG))
		{
			CPEventHelper::openPanel("MainPanel",TAG_Merge_Panel,TAG_LZ,TAG_LingZhu,0);
			flag=true;
		}
		//addPanel(TAG_Merge_Panel,TAG_LZ); 
		break;
	case 2://物品合成界面
		if(GuideHelper::canOpenFunction(FunctionName::HE_CHENG))
		{
			CPEventHelper::openPanel("MainPanel",TAG_Merge_Panel,TAG_WP,TAG_WuPin,0);
			flag=true;
		}
		//addPanel(TAG_Merge_Panel,TAG_WP); 
		break;
	case 3://翅膀合成界面
		if(GuideHelper::canOpenFunction(FunctionName::HE_CHENG))
		{
			CPEventHelper::openPanel("MainPanel",TAG_Merge_Panel,TAG_CB,TAG_ChiBang,0);
			flag=true;
		}
		//addPanel(TAG_Merge_Panel,TAG_CB); 
		break;
	case 4://装备强化界面
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA))
		{
			CPEventHelper::openPanel("MainPanel",TAG_Enhance_Panel,TAG_ZBQH,0,0);
			flag=true;
		}
		//addPanel(TAG_Enhance_Panel,TAG_ZBQH); 
		break;
	case 5://转生锻造界面
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA))
		{
			if(GuideHelper::canOpenFunction(FunctionName::ZHUAN_SHENG_DUAN_ZAO))
			{
				CPEventHelper::openPanel("MainPanel",TAG_Enhance_Panel,TAG_ZSDZ,0,0);
				flag=true;
			}
		}
		//addPanel(TAG_Enhance_Panel,TAG_ZSDZ); 
		break;
	case 6://装备升级界面
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA))
		{
			if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_SHENG_JI))
			{
				CPEventHelper::openPanel("MainPanel",TAG_Enhance_Panel,TAG_ZBSJ,0,0);
				flag=true;
			}
		}
		//addPanel(TAG_Enhance_Panel,TAG_ZBSJ); 
		break;
	case 7://宠物界面
		//((CommonPanel* )(m_pRightMenu->getChildByTag(TAG_Role_Panel)))->initRightTop(PET); 
		if(GuideHelper::canOpenFunction(FunctionName::CHONG_WU))
		{
			CPEventHelper::openPanel("MainPanel",TAG_Role_Panel,PET,0,0);
			flag=true;
		}
		//addPanel(TAG_Role_Panel,PET); 
		break;
	case 8://装备鉴定界面
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA))
		{
			if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_JIAN_DING))
			{
				CPEventHelper::openPanel("MainPanel",TAG_Enhance_Panel,TAG_ZBJD,0,0);
				flag=true;
			}
		}
		//addPanel(TAG_Enhance_Panel,TAG_ZBJD); 
		break;
	case 9://属性转移界面
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA))
		{
			if(GuideHelper::canOpenFunction(FunctionName::SHU_XING_ZHUAN_YI))
			{
				CPEventHelper::openPanel("MainPanel",TAG_Enhance_Panel,TAG_SXZY,0,0);
				flag=true;
			}
		}
		//addPanel(TAG_Enhance_Panel,TAG_JPZY); 
		break;
	case 10://解锁背包界面
		if (HeroData::getProp(Entity::attr_bagslot)>=SystemData::getLayoutValue("MaxPlayerBagSlot"))
		{
			CPEventHelper::uiNotify("","",Error::MaxBagSolt);
			flag=true;
			break;
		}
		Game::getGameUI()->showUnlockPanel(1,Self_Bag);
		flag=true;
		/*if (Game::getGameUI()->getPanel(TAG_UNLOCKBAG_PANEL))
		{
		((BagUnlockPanel*)(Game::getGameUI()->getPanel(TAG_UNLOCKBAG_PANEL)))->setUnlockCount(1);
		}*/
		break;
	case 11://商城界面
		CPEventHelper::openPanel("ShopPanel");
		flag=true;
		//addPanel(TAG_Shop_Panel); 
		break;
	case 12://寻宝界面
		if(GuideHelper::canOpenFunction(FunctionName::XUN_BAO))
		{
			CPEventHelper::openPanel("TreasureHuntPanel");
			flag=true;
		}
		break;
	case 13://5级完美强化
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA))
		{
			CPEventHelper::openPanel("MainPanel",TAG_Enhance_Panel,TAG_ZBQH,TAG_WMQH,SystemData::getLayoutValue("5级完美强化符"));
			flag=true;
		}
		break;
	case 14://8级完美强化
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA))
		{
			CPEventHelper::openPanel("MainPanel",TAG_Enhance_Panel,TAG_ZBQH,TAG_WMQH,SystemData::getLayoutValue("8级完美强化符"));
			flag=true;
		}
		//addPanel(TAG_Enhance_Panel,TAG_ZBQH);  
		break;
	case 15://10级完美强化
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA))
		{
			CPEventHelper::openPanel("MainPanel",TAG_Enhance_Panel,TAG_ZBQH,TAG_WMQH,SystemData::getLayoutValue("10级完美强化符"));
			flag=true;
		}
		//addPanel(TAG_Enhance_Panel,TAG_ZBQH); 
		break;
	case 16://强化转移
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA))
		{
			if(GuideHelper::canOpenFunction(FunctionName::SHU_XING_ZHUAN_YI))
			{
				CPEventHelper::openPanel("MainPanel",TAG_Enhance_Panel,TAG_SXZY,TAG_QHZY,0);
				flag=true;
			}
		}
		//addPanel(TAG_Enhance_Panel,TAG_JPZY); 
		break;
	case 17://极品清洗
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA))
		{
			if(GuideHelper::canOpenFunction(FunctionName::SHU_XING_ZHUAN_YI))
			{
				CPEventHelper::openPanel("MainPanel",TAG_Enhance_Panel,TAG_SXZY,TAG_JPQX,0);
				flag=true;
			}
		}
		//addPanel(TAG_Enhance_Panel,TAG_JPZY); 
		break;
	default:
		CCLOG("openpanel = %d 尚未设置该Panel",openpanel);
		break;
	}
	if (!flag)
	{
		CPEventHelper::uiNotify("","",Error::NotOpenNewFunc);	
	}
}

void MainPanel::CloseCallBack( CCObject* pSender )
{
	if (Game::getGameUI()->getPanel(TAG_Tips_PANEL))
	{
		Game::getGameUI()->hidePanel(TAG_Tips_PANEL);
	}
	/*CCShow *sh = CCShow::create();
	CCAction* ac=CPNodeHelper::getScaleToSmall();
	CCAction* rm=CCActionInstantRemoveFromParentEx::create(this);
	this->runAction(CCSequence::create(sh, ac,rm,NULL));*/
	//BasePanel::closeCallBack(pSender);  
	Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);
	//this->Game::getGameUI()->hidePanel(TAG_Tips_PANEL);removeFromParent();
}

void MainPanel::checkPanel()
{
	topTag[0]=TAG_Role_Panel;
	topTag[1]=TAG_Task_Panel;
	topTag[2]=TAG_Activity_Panel;
	//topTag[3]=TAG_Shop_Panel;
	topTag[3]=TAG_Merge_Panel;
	topTag[4]=TAG_Enhance_Panel;
	topTag[5]=TAG_Honor_Panel;
	topTag[6]=TAG_Friend_Panel;
	topTag[7]=TAG_Society_Panel;
	topTag[8]=TAG_Setting_Panel;
	topTag[9]=TAG_VIP_Panel;
	topTag[10]=TAG_Designation_Panel;
	/*topTag[TAG_Max_Panel]={
		TAG_Role_Panel,TAG_Task_Panel	,TAG_Activity_Panel ,TAG_Shop_Panel ,TAG_Merge_Panel ,TAG_Enhance_Panel ,TAG_Honor_Panel ,TAG_Friend_Panel ,TAG_Society_Panel ,TAG_Setting_Panel 
	};*/ 
	   
	func[0]="ui_func.juese";
	func[1]="ui_func.renwu";
	func[2]="ui_func.huodong";
	//func[3]="ui_func.shangcheng";
	func[3]="ui_func.hecheng";
	func[4]="ui_func.qianghua";
	func[5]="ui_func.rongyu";
	func[6]="ui_func.shejiao";
	func[7]="ui_func.hanghui";
	func[8]="ui_func.shezhi";
	func[9]="ui_func.vip";
	func[10]="ui_func.designation";
	/*func[TAG_Max_Panel]={
		"ui_func.juese","ui_func.renwu","ui_func.huodong","ui_func.qianghua","ui_func.hecheng","ui_func.rongyu","ui_func.shangcheng","ui_func.hanghui","ui_func.shejiao","ui_func.shezhi"
	};*/
	m_MaxCellCount=TAG_Max_Panel;
	if (!GuideHelper::canOpenFunction(FunctionName::HANG_HUI))
	{
		int n=0;
		for (int i=0;i<TAG_Max_Panel;i++)
		{
			if (topTag[i]==TAG_Society_Panel)
			{
				n=i;
				break;
			}
		}
		int temp=topTag[n];
		for (int i=n;i<TAG_Max_Panel-1;i++)
		{
			topTag[i]=topTag[i+1];
		}
		topTag[TAG_Max_Panel-1]=temp;

		std::string tempstr=func[n];
		for (int i=n;i<TAG_Max_Panel-1;i++)
		{
			func[i]=func[i+1];
		}
		func[TAG_Max_Panel-1]=tempstr;

		m_MaxCellCount--;
	}
	if (!GuideHelper::canOpenFunction(FunctionName::RONG_YV))
	{
		int n=0;
		for (int i=0;i<TAG_Max_Panel;i++)
		{
			if (topTag[i]==TAG_Honor_Panel)
			{
				n=i;
				break;
			}
		}
		int temp=topTag[n];
		for (int i=n;i<TAG_Max_Panel-1;i++)
		{
			topTag[i]=topTag[i+1];
		}
		topTag[TAG_Max_Panel-1]=temp;

		std::string tempstr=func[n];
		for (int i=n;i<TAG_Max_Panel-1;i++)
		{
			func[i]=func[i+1];
		}
		func[TAG_Max_Panel-1]=tempstr;

		m_MaxCellCount--;
	}
	if (!GuideHelper::canOpenFunction(FunctionName::HE_CHENG))
	{
		int n=0;
		for (int i=0;i<TAG_Max_Panel;i++)
		{
			if (topTag[i]==TAG_Merge_Panel)
			{
				n=i;
				break;
			}
		}
		int temp=topTag[n];
		for (int i=n;i<TAG_Max_Panel-1;i++)
		{
			topTag[i]=topTag[i+1];
		}
		topTag[TAG_Max_Panel-1]=temp;

		std::string tempstr=func[n];
		for (int i=n;i<TAG_Max_Panel-1;i++)
		{
			func[i]=func[i+1];
		}
		func[TAG_Max_Panel-1]=tempstr;

		m_MaxCellCount--;
	}
	if (!GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_QIANG_HUA))
	{
		int n=0;
		for (int i=0;i<TAG_Max_Panel;i++)
		{
			if (topTag[i]==TAG_Enhance_Panel)
			{
				n=i;
				break;
			}
		}
		int temp=topTag[n];
		for (int i=n;i<TAG_Max_Panel-1;i++)
		{
			topTag[i]=topTag[i+1];
		}
		topTag[TAG_Max_Panel-1]=temp;

		std::string tempstr=func[n];
		for (int i=n;i<TAG_Max_Panel-1;i++)
		{
			func[i]=func[i+1];
		}
		func[TAG_Max_Panel-1]=tempstr;

		m_MaxCellCount--;
	}
}

void MainPanel::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::UI_OPEN)
	{
		const std::string &target = CPEventHelper::getEventTarget();
		if (target == "GameUI")
		{
			const std::string &panelName = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
			if (panelName == "MainPanel")
			{
				//showPanel(TAG_MAIN_PANEL);
				int data1=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				int data2=CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				int data3=CPEventHelper::getEventIntData(CPEventData::VALUE_4);
				if (data1>=TAG_Role_Panel && data1<TAG_Max_Panel)
				{
					addPanel(data1,data2);
					m_pTabelViewEx->reloadData(); 
				}
				if (data1 == TAG_Booth_Panel)
				{
					addPanel(data1,data2,data3);
					m_pTabelViewEx->reloadData(); 
				}
			}
		}
	}
	if (eventName == CPEventName::UI_CLOSE)
	{
		const std::string &source = CPEventHelper::getEventSource();
		if (source == "NoticePanel::onGet")
		{
			this->removeFromParent();
		}
	}
}

