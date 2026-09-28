#include "TradePanel.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/SystemData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/NetItem.h"

#include "network/HandleMessage.h"
#include "MsgItem.h"
#include "scene/GameUI.h"
#include "event/EventProtocol.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/panel/functionPanel/BagPanel.h"
#include "script/LuaWrapper.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "userdata/UserPetData.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "EntityDefinition.h"
#include "MsgScene.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/FloatPanelType.h"
#include "userdata/netdata/GhostManager.h"
#include "MsgTrade.h"
#include "userdata/LayoutData.h"
#include "userdata/BoothData.h"
#include "event/CPEventHelper.h"
#include "TradeDefinition.h"

const short PAGE_ONE = 0;
const short PAGE_NUM = 12;

const int ItemOneLine = 6;
const int ItemSize = 74;
const int RectSize = 76;

const int TAG_PUTOFF_PACK = 1003;
const int TAG_SPLIT_PACK = 1004;

const int TAG_NEXT_PAGE = 1005;
const int TAG_PRE_PAGE = 1006;

static const float DOUBLE_CLICK_TIME = 0.2f;


#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

TradePanel::TradePanel()
{

}


TradePanel::~TradePanel()
{
}
/*

TradePanel* TradePanel::create()
{
	TradePanel* bagPanel = new TradePanel();
	if(bagPanel && bagPanel->init())
	{
		return bagPanel;
	}

	if (bagPanel)
	{
		delete bagPanel;
	}
	return NULL;
}*/

/**
 * TradePanel 初始化函数
 * 创建并布局交易界面的所有UI元素
 * 返回: bool - 初始化是否成功
 */
bool TradePanel::init()
{
	// 1. 首先调用父类CCLayer的初始化
	if(!CCLayer::init())
	{
		return false; // 父类初始化失败，直接返回false
	}

	// 2. 设置面板的宽度和高度（基于1200x520的设计分辨率）
	m_nWidth = 800;  // 对应800全屏的换算值（根据注释）
	m_nHeight = 480;  // 对应480的换算值（根据注释）  676545075

	// 3. 创建并添加背景
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::COMMON, "bkg");
	addChild(bkg);

	// 4. 创建并添加标题栏背景
	CCScale9Sprite *titleBoard = LayoutData::getScale9Sprite(CPModuleName::COMMON, "titleBoard");
	addChild(titleBoard);

	// 5. 创建并添加标题栏左右装饰元素
	CCSprite *titleBoardDecorationL = LayoutData::getSprite(CPModuleName::COMMON, "titleBoardDecorationL");
	addChild(titleBoardDecorationL);

	CCSprite *titleBoardDecorationR = LayoutData::getSprite(CPModuleName::COMMON, "titleBoardDecorationR");
	addChild(titleBoardDecorationR);

	// 6. 创建并添加标题左右装饰元素
	CCSprite *titleDecorationL = LayoutData::getSprite(CPModuleName::COMMON, "titleDecorationL");
	addChild(titleDecorationL);

	CCSprite *titleDecorationR = LayoutData::getSprite(CPModuleName::COMMON, "titleDecorationR");
	addChild(titleDecorationR);

	// 7. 添加覆盖层（可能是半透明遮罩）
	addCover();

	// 8. 创建并添加标题区域背景（使用plist资源）
	// 注释掉的原代码使用SystemData::getScale9Sprite，现使用带plist的版本
	CCScale9Sprite* pborderbkg = SystemData::getScale9SpriteByPlist(
		"Trade_titlebkg",
		SystemData::getLayoutValue("Trade_titlebkg_size.w"),
		SystemData::getLayoutValue("Trade_titlebkg_size.h")
	);
	pborderbkg->setAnchorPoint(CCPointZero); // 设置锚点为左下角
	pborderbkg->setPosition(SystemData::getLayoutPoint("Trade_titlebkg_pos")); // 从布局数据获取位置
	addChild(pborderbkg);

	// 9. 创建并添加左侧标题标签
	// 创建左侧标题背景精灵
	CCSprite* pleftSprite = SystemData::getSpriteByPlist("Trade_title"); 
	pleftSprite->setAnchorPoint(CCPointZero);
	pleftSprite->setPosition(SystemData::getLayoutPoint("Trade_title1_pos"));
	addChild(pleftSprite);
	
	// 创建并添加左侧标题文字
	CCLabelTTF* plabel1 = SystemData::getLabelTTF("Trade_title1");
	plabel1->setColor(ccWHITE); // 设置文字颜色为白色
	plabel1->setPosition(ccp(pleftSprite->getContentSize().width/2, pleftSprite->getContentSize().height/2)); // 居中显示
	pleftSprite->addChild(plabel1);

	// 10. 创建并添加右侧标题标签
	// 创建右侧标题背景精灵
	CCSprite* prightSprite = SystemData::getSpriteByPlist("Trade_title");
	prightSprite->setAnchorPoint(CCPointZero);
	prightSprite->setPosition(SystemData::getLayoutPoint("Trade_title2_pos"));
	addChild(prightSprite);
	
	// 创建并添加右侧标题文字
	CCLabelTTF* plabel2 = SystemData::getLabelTTF("Trade_title2");
	plabel2->setColor(ccWHITE);
	plabel2->setPosition(ccp(prightSprite->getContentSize().width/2, prightSprite->getContentSize().height/2));
	prightSprite->addChild(plabel2);

	// 11. 创建菜单容器（用于放置按钮）
	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);
	addChild(pMenu);

	// 12. 创建并添加关闭按钮
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("Trade_close");
	pClose->setTarget(this, menu_selector(TradePanel::closeCallBack)); // 设置点击回调函数
	pClose->setPosition(SystemData::getLayoutPoint("Trade_close_pos")); // 从布局数据获取位置
	pMenu->addChild(pClose);

	// 13. 创建并添加右侧背包面板
	// 参数说明: 5列, 4行, 最大背包格子数, 背包所有者, 背包类型
	BagPanel* bagPanel = BagPanel::create(
		5, 
		4, 
		SystemData::getLayoutValue("MaxPlayerBagSlot"), 
		Self_Bag, 
		Bag_Type_Trade
	);
	bagPanel->setPosition(ccp(487, 8)); // 固定位置
	bagPanel->setAnchorPoint(CCPointZero);
	// 注释掉的原代码：bagPanel->setPosition(SystemData::getLayoutPoint("ui_func.rightmenu.pos"));
	addChild(bagPanel);

	// 14. 创建并添加交易单元格面板
	// 左侧：自己的交易面板
	TradeCellPanel* pPanel1 = TradeCellPanel::create(Type_Self);
	pPanel1->setAnchorPoint(CCPointZero);
	pPanel1->setPosition(SystemData::getLayoutPoint("Trade_Cell1_pos"));
	addChild(pPanel1);
	
	// 右侧：其他人的交易面板
	TradeCellPanel* pPanel2 = TradeCellPanel::create(Type_Other);
	pPanel2->setAnchorPoint(CCPointZero);
	pPanel2->setPosition(SystemData::getLayoutPoint("Trade_Cell2_pos"));
	addChild(pPanel2);

	// 15. 初始化成功，返回true
	return true;
}

void TradePanel::closeCallBack( CCObject* pSender )
{
	//调用是否终止交易
	std::vector<std::string> strlist;
	std::string othername=GameData::s_user->m_pMainRole->m_iTargetname;
	strlist.push_back(othername);
	Game::getGameUI()->showFloatPanel(FloatPanelType::TradeTips_Over,strlist);
}

//---------------------------------------------------------------------------------------------------------//

TradeCellPanel::TradeCellPanel():
	m_pItemMenu(NULL),
	m_pLockButton(NULL),
	m_pLockSprite(NULL),
	m_pUserItem(NULL),
	m_bIsLock(false),
	m_pMoney1(NULL),
	m_pMoney2(NULL),
	m_iCurrentPrice(0),
	m_iCurrentPriceType(0)
{

}

TradeCellPanel::~TradeCellPanel()
{

}

TradeCellPanel* TradeCellPanel::create(int type)
{

	TradeCellPanel* bagPanel = new TradeCellPanel();
	if(bagPanel && bagPanel->init(type))
	{
		bagPanel->autorelease();
		return bagPanel;
	}


	if (bagPanel)
	{
		delete bagPanel;
	}
	return NULL;
}

bool TradeCellPanel::init(int type)
{
	m_iType=type;
	CCScale9Sprite* pborderdown=SystemData::getScale9SpriteByPlist("Trade_Cell",SystemData::getLayoutValue("Trade_CellDown_size.w"),SystemData::getLayoutValue("Trade_CellDown_size.h"));
	pborderdown->setAnchorPoint(CCPointZero);
	pborderdown->setPosition(CCPointZero);
	addChild(pborderdown);

	CCScale9Sprite* pborderup=SystemData::getScale9SpriteByPlist("Trade_Cell",SystemData::getLayoutValue("Trade_CellUp_size.w"),SystemData::getLayoutValue("Trade_CellUp_size.h"));
	pborderup->setAnchorPoint(CCPointZero);
	pborderup->setPosition(ccp(0,pborderdown->getContentSize().height));
	addChild(pborderup);


	CCMenu* pMenu=CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	//金钱图标
	CCSprite* pMoney1=SystemData::getSpriteByPlist("Trade_Money1");
	pMoney1->setPosition(SystemData::getLayoutPoint("Trade_Money1_pos"));
	addChild(pMoney1);


	CCSprite* pMoney2=SystemData::getSpriteByPlist("Trade_Money2");
	pMoney2->setPosition(SystemData::getLayoutPoint("Trade_Money2_pos"));
	addChild(pMoney2);

	if (m_iType==Type_Self)
	{
		//文本输入框
		CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("Trade_numbertext",90,30);
		CCMenuItemSprite* pText1=CCMenuItemSprite::create(p1,p1,NULL,this,menu_selector(TradeCellPanel::TextCallBack));
		pText1->setPosition(SystemData::getLayoutPoint("Trade_Text1_pos"));
		pText1->setTag(Text_Money1);
		pMenu->addChild(pText1);

		CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("Trade_numbertext",90,30);
		CCMenuItemSprite* pText2=CCMenuItemSprite::create(p2,p2,NULL,this,menu_selector(TradeCellPanel::TextCallBack));
		pText2->setPosition(SystemData::getLayoutPoint("Trade_Text2_pos"));
		pText2->setTag(Text_Money2);
		pMenu->addChild(pText2);
	}

	m_pMoney1=CCLabelTTF::create("0","微软雅黑",18);
	m_pMoney1->setPosition(SystemData::getLayoutPoint("Trade_Text1_pos"));
	addChild(m_pMoney1);

	m_pMoney2=CCLabelTTF::create("0","微软雅黑",18);
	m_pMoney2->setPosition(SystemData::getLayoutPoint("Trade_Text2_pos"));
	addChild(m_pMoney2);

	//格子初始化
	int x=0,y=0;
	for (int i=0;i<12;i++)
	{
		CCSprite* pitem=SystemData::getSpriteByPlist("Trade_item");
		pitem->setAnchorPoint(CCPointZero);
		pitem->setPosition(ccp(SystemData::getLayoutPoint("Trade_item_pos").x+x*72,SystemData::getLayoutPoint("Trade_item_pos").y-y*70));
		x++;
		if (x==6)
		{
			x=0;y++;
		}
		addChild(pitem);
	}

	initPlayerInfo();

	initButton();

	m_pItemMenu=GeneralMenu::create();
	m_pItemMenu->setAnchorPoint(CCPointZero);
	m_pItemMenu->setPosition(CCPointZero);
	addChild(m_pItemMenu);

	return true;
}

void TradeCellPanel::handleEvent( int channel )
{
	if (channel==EventProtocol::EVENT_TRADE_SELF || channel==EventProtocol::EVENT_TRADE_OTHER)
	{
		if (m_iType==Type_Self)
		{
			addSelfItem();
		}
		else if (m_iType==Type_Other)
		{
			addOtherItem();
		}
	}
	if (channel==EventProtocol::EVENT_TRADE_SELFLOCK)
	{
		m_bIsLock=true;
		if (m_pLockButton)
		{
			m_pLockButton->setTag(Button_isLock);
			CCSprite* p1=SystemData::getSpriteByPlist("Trade_button_lock");
			CCSprite* p2=SystemData::getSpriteByPlist("Trade_button_lock");
			m_pLockButton->setNormalImage(p1);
			m_pLockButton->setSelectedImage(p2);
		}
	}
	if (channel==EventProtocol::EVENT_TRADE_SELFUNLOCK)
	{
		m_bIsLock=false;
		if (m_pLockButton)
		{
			m_pLockButton->setTag(Button_Lock);
			CCSprite* p1=SystemData::getSpriteByPlist("Trade_button");
			CCSprite* p2=SystemData::getSpriteByPlist("Trade_button.sel");
			m_pLockButton->setNormalImage(p1);
			m_pLockButton->setSelectedImage(p2);
		}
	}
	if (channel==EventProtocol::EVENT_TRADE_OTHERLOCK)
	{
		if (m_pLockSprite)
		{
			CCSprite* p1=SystemData::getSpriteByPlist("Trade_lock");
			CCSprite* p2=SystemData::getSpriteByPlist("Trade_lock");
			m_pLockSprite->setNormalImage(p1);
			m_pLockSprite->setSelectedImage(p2);
		}
	}
	if (channel==EventProtocol::EVENT_TRADE_OTHERUNLOCK)
	{
		if (m_pLockSprite)
		{
			CCSprite* p1=SystemData::getSpriteByPlist("Trade_unlock");
			CCSprite* p2=SystemData::getSpriteByPlist("Trade_unlock");
			m_pLockSprite->setNormalImage(p1);
			m_pLockSprite->setSelectedImage(p2);
		}
	}
	if (channel==EventProtocol::EVENT_TRADEITEM_UPDATA)
	{
		if (m_iType==Type_Other)
		{
			addOtherItem();
		}
		else if (m_iType==Type_Self)
		{
			addSelfItem();
		}
	}
	if (channel==EventProtocol::EVENT_TRADEITEM_INFO)
	{
		if (m_pUserItem)
		{
			Game::getGameUI()->showTipsPanel(m_pUserItem,TAG_Tips);
		}
	}
	if (channel==EventProtocol::EVENT_PUTIN_OVER)
	{
		if (m_iCurrentPriceType==Text_Money1)
		{
			m_pMoney1->setString(SystemData::intToString(m_iCurrentPrice).c_str());
			MsgItemTradeChangeMoney* msg=new MsgItemTradeChangeMoney;
			msg->cnt=m_iCurrentPrice;
			msg->moneytype=Entity::attr_money;
			HandleMessage::sendMessage(msg);
		}
		if (m_iCurrentPriceType==Text_Money2)
		{
			m_pMoney2->setString(SystemData::intToString(m_iCurrentPrice).c_str());
			MsgItemTradeChangeMoney* msg=new MsgItemTradeChangeMoney;
			msg->cnt=m_iCurrentPrice;
			msg->moneytype=Entity::attr_gold;
			HandleMessage::sendMessage(msg);
		}
	}
}

void TradeCellPanel::addOtherItem()
{
	m_pItemMenu->removeAllChildren();

	m_pMoney1->setString(SystemData::intToString(GameData::s_user->m_pMainRole->m_iTargetMoney1).c_str());
	m_pMoney2->setString(SystemData::intToString(GameData::s_user->m_pMainRole->m_iTargetMoney2).c_str());

	std::vector< UserItem* >::iterator it;
	for (it=GameData::s_user->m_pMainRole->m_pTradeItemList.begin();it!=GameData::s_user->m_pMainRole->m_pTradeItemList.end();it++)
	{
		UserItem* userItem=(UserItem*)*it;
		int position=userItem->position;
		CCMenuItemImage* icon = CommonFunction::getItemIcon(userItem);
		/*CCMenuItemImage* icon = CCMenuItemImage::create();
		icon->setNormalImage(LayoutData::getItemIcon(userItem->sid));
		icon->setSelectedImage(LayoutData::getItemIcon(userItem->sid));*/
		icon->setTarget(this,menu_selector(TradeCellPanel::ItemCallBack));
		icon->setPosition(getItemPosition(position-ItemPos::Trade_Bag_Start));	
		icon->setAnchorPoint(CCPointZero);	
		m_pItemMenu->addChild(icon);
	}
}

void TradeCellPanel::addSelfItem()
{
	m_pItemMenu->removeAllChildren();
	UserItems items = GameData::s_user->getUserItemData()->userItems;

	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		if (isPosInThisPanel(it->first))
		{
			UserItem* userItem=it->second;
			int position=userItem->position;
			CCMenuItemImage* icon = CommonFunction::getItemIcon(userItem);
			/*CCMenuItemImage* icon = CCMenuItemImage::create();
			icon->setNormalImage(LayoutData::getItemIcon(userItem->sid));
			icon->setSelectedImage(LayoutData::getItemIcon(userItem->sid));*/
			icon->setTarget(this,menu_selector(TradeCellPanel::ItemCallBack));
			icon->setPosition(getItemPosition(position-ItemPos::Trade_Bag_Start));	
			icon->setAnchorPoint(CCPointZero);
			m_pItemMenu->addChild(icon);
		}
	}
}

void TradeCellPanel::ItemCallBack( CCObject* pSender )
{
	CCNode* pNode=(CCNode*)pSender;
	UserItem* useritem=(UserItem*)(pNode->getUserData());
	if (useritem)
	{
		m_pUserItem=useritem;
		if (m_iType==Type_Other)
		{
			MsgItemInfoDataGetRequest* msg=new MsgItemInfoDataGetRequest;
			msg->eid=GameData::s_user->m_pMainRole->m_iTargeteid;
			msg->iid=useritem->iid;
			msg->pid=GameData::s_user->m_pMainRole->m_iTargetpid;
			HandleMessage::sendMessage(msg);
		}
		else if (!m_bIsLock && m_iType==Type_Self)
		{
			int type=TAG_Tips_QXJY;
			Game::getGameUI()->showTipsPanel(useritem,type);
		}
		else if (m_bIsLock && m_iType==Type_Self)
		{
			int type=TAG_Tips;
			Game::getGameUI()->showTipsPanel(useritem,type);
		}
	}
}

void TradeCellPanel::initPlayerInfo()
{
	std::string name;
	int degree;
	if (m_iType==Type_Self)
	{
		name=GameData::s_user->m_pMainRole->mName;
		degree=GameData::s_user->m_pMainRole->mLevel;
	}
	else if (m_iType==Type_Other)
	{
		AliveGhost* ghost=(AliveGhost*)(GameData::s_user->m_pGhostManager->getGhostById(GameData::s_user->m_pMainRole->m_iTargeteid));
		if (ghost)
		{
			name=ghost->mName;
			degree=ghost->mLevel;
		}
	}
	CCLabelTTF* pName=CCLabelTTF::create(name.c_str(),"微软雅黑",18);
	pName->setAnchorPoint(CCPointZero);
	pName->setPosition(SystemData::getLayoutPoint("Trade_name_pos"));
	addChild(pName);

	CCLabelTTF* pDegree=CCLabelTTF::create(SystemData::intToString(degree).c_str(),"微软雅黑",18);
	pDegree->setAnchorPoint(CCPointZero);
	pDegree->setPosition(SystemData::getLayoutPoint("Trade_dgree_pos"));
	addChild(pDegree);
}

void TradeCellPanel::initButton()
{
	CCMenu* pMenu=CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	if (m_iType==Type_Self)
	{
		m_pLockButton=SystemData::getMenuItemImageByPlist("Trade_button");
		m_pLockButton->setTarget(this,menu_selector(TradeCellPanel::MenuCallBack));
		m_pLockButton->setTag(Button_Lock);
		m_pLockButton->setPosition(SystemData::getLayoutPoint("Trade_button1_pos"));
		pMenu->addChild(m_pLockButton);


		CCLabelTTF* pLabel=SystemData::getLabelTTF("Trade_button_text");
		pLabel->setColor(ccWHITE);
		pLabel->setFontSize(16);
		pLabel->setPosition(SystemData::getLayoutPoint("Trade_button1_pos"));
		addChild(pLabel);


	}
	else if (m_iType==Type_Other)
	{
		m_pLockSprite=SystemData::getMenuItemImageByPlist("Trade_unlock");
		m_pLockSprite->setPosition(SystemData::getLayoutPoint("Trade_button1_pos"));
		pMenu->addChild(m_pLockSprite);
	}
}

void TradeCellPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode=(CCNode*)pSender;
	if (pNode)
	{
		int tag=pNode->getTag();
		if (tag==Button_Lock)
		{
			//发送锁定消息
			MsgItemTradeLockInfo* msg=new MsgItemTradeLockInfo;
			msg->lock=1;
			HandleMessage::sendMessage(msg);
		}
	}
}

cocos2d::CCPoint TradeCellPanel::getItemPosition( int pos )
{
	return ccp(SystemData::getLayoutPoint("Trade_item_pos").x+(pos%6)*72,SystemData::getLayoutPoint("Trade_item_pos").y-pos/6*70);
}

void TradeCellPanel::TextCallBack( CCObject* pSender )//输入金钱
{
	if (BoothData::getTradeLockState())
	{	
		CPEventHelper::uiNotify("","",Error::TradeHasLock);
		return;
	}
	CCNode* pNode=(CCNode*)pSender;
	if (pNode)
	{
		int tag=pNode->getTag();
		//打开计算器
		int countmax;
		if (tag==Text_Money1)
		{
			countmax=HeroData::getProp(Entity::attr_money);
		}
		if (tag==Text_Money2)
		{
			/*if (HeroData::getLevel()<SystemData::getLayoutValue("交易等级"))
			{
				CPEventHelper::uiNotify("","",Error::NotEnoughLevel);
				return;
			}*/
			countmax=HeroData::getProp(Entity::attr_gold);
		}
		m_iCurrentPriceType=tag;
		Game::getGameUI()->showNumberBoard(&m_iCurrentPrice,countmax,EventProtocol::EVENT_PUTIN_OVER,1);
	}
}
