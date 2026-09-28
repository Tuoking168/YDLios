#include "BagPanel.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/SystemData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/NetItem.h"

#include "MsgItem.h"
#include "network/HandleMessage.h"
#include "scene/GameUI.h"
#include "event/EventProtocol.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "scene/panel/shop/NpcShopComp.h"
#include "BagCellPanel.h"
#include "controls/CPUpdater.h"
#include "logic/TimeManager.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"
#include "logic/BagOperator.h"
#include <algorithm>

#include <algorithm>

const short PAGE_NUM = 20;

const int ItemSize = 74;
const int RectSize = 76;


const int TAG_NEXT_PAGE = 1005;
const int TAG_PRE_PAGE = 1006;


const int TAG_BAGCELL = 2000;

static const int ITEM_UNUSE_POS = -1000;
static const int ITEM_BAG_BEGIN = 0;
static const int ITEM_BAG_SIZE = 20;
static const int ITEM_BAG_END = 120;

static const float DOUBLE_CLICK_TIME = 0.2f;


#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

BagPanel::BagPanel():
	m_MoneyMenu(NULL)
	,m_iCurrentBagType(0)
	,m_bSpilt(false)
	,m_iSortTime(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
}


BagPanel::~BagPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
}

BagPanel* BagPanel::create(int line,int row,int count,int type1,int type2,int position)
{
	BagPanel* bagPanel = new BagPanel();
	if(bagPanel && bagPanel->init(line,row,count,type1,type2,position))
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

bool BagPanel::init(int line,int row,int count,int type1,int type2,int position)
{
	if(!CCLayer::init())
	{
		return false;
	}
	m_iposition=position;
	m_iLine=line;
	m_iRow=row;
	m_iCount=count;
	m_iType1=type1;
	m_iType2=type2;
	m_iPageCount=line*row;
	m_iPage=m_iCount/m_iPageCount;
	if (m_iCount%m_iPageCount!=0)
	{
		m_iPage++;
	}

	m_iWidth=307+(m_iRow-4)*80; 

	CCScale9Sprite* m_pBkgSprite = SystemData::getScale9SpriteByPlist("ui.bag.small_bkg", m_iWidth, 429);

	if(!m_pBkgSprite)
	{
		return false;
	}
	m_pBkgSprite->setAnchorPoint(CCPointZero);
	//m_pBkgSprite->setPosition(SystemData::getLayoutPoint("ui.bagpanel"));
	m_pBkgSprite->setPosition(CCPointZero);
	addChild(m_pBkgSprite);
	/*if (m_iType1==Pet_Bag || m_iType1==NPC_Bag)
	{
		m_pBkgSprite->setPosition(CCPointZero);
	}*/

	m_MoneyMenu=GeneralMenu::create();
	m_MoneyMenu->setPosition(CCPointZero);
	addChild(m_MoneyMenu);

	initBagSlot(line,row,count,type1,type2,position);
	if (m_iType2==Bag_Type_NPCBag || m_iType1==Self_Bag || m_iType2==Bag_Type_Stone || m_iType1==House_Bag || m_iType2==Bag_Type_Npcshop)
	{
		initMoney(); 
	}
	if (m_iType1 != Sell_Bag)
	{
		initButton();
	}

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu,999);

	return true;
}

bool BagPanel::initBagSlot(int line,int row,int count,int type1,int type2,int position)
{
	current_layer_idx = 0;
	BagCellPanel* pPanel=BagCellPanel::create(line,row,count,type1,type2,position);
	//pPanel->setAnchorPoint(ccp(0.5,0));
	/*pPanel->setPosition(ccp(408,0));
	if (m_iType1==Pet_Bag || m_iType1==NPC_Bag)
	{
	}*/
	pPanel->setPosition(ccp((m_iWidth+5-m_iRow*RectSize)/2,-8));
	pPanel->setTag(TAG_BAGCELL);
	addChild(pPanel);
	//OpenSpilt(false);
	return true;
}

bool BagPanel::initMoney()
{
	m_MoneyMenu->removeAllChildren();
	std::string money[3] = {"wx.bag.gold","wx.bag.coupon","wx.bag.vcoin"};
	for(int i = 0;i < 3;i++)
	{
		CCSprite* sprite = SystemData::getSpriteByPlist(money[i]);
		sprite->setPosition(SystemData::getLayoutPoint(money[i]));
		m_MoneyMenu->addChild(sprite); 
	}

	m_pVcoin = CCLabelTTF::create(" ","Times New Roman",15);
	m_pCoupon = CCLabelTTF::create(" ","Times New Roman",15);
	m_pGold = CCLabelTTF::create(" ","Times New Roman",15);

	m_pVcoin->setAnchorPoint(ccp(0,0.5));
	m_pCoupon->setAnchorPoint(ccp(0,0.5));
	m_pGold->setAnchorPoint(ccp(0,0.5));

	m_pVcoin->setPosition(ccp(SystemData::getLayoutPoint("wx.bag.vcoin").x+17,SystemData::getLayoutPoint("wx.bag.vcoin").y));
	m_pCoupon->setPosition(ccp(SystemData::getLayoutPoint("wx.bag.coupon").x+17,SystemData::getLayoutPoint("wx.bag.coupon").y));
	m_pGold->setPosition(ccp(SystemData::getLayoutPoint("wx.bag.gold").x+17,SystemData::getLayoutPoint("wx.bag.gold").y));

	m_MoneyMenu->addChild(m_pVcoin);
	m_MoneyMenu->addChild(m_pCoupon);
	m_MoneyMenu->addChild(m_pGold);

	// 获取原始数值
	int goldValue = HeroData::getProp(Entity::attr_gold);
	int diamondValue = HeroData::getProp(Entity::attr_diamond);
	int moneyValue = HeroData::getProp(Entity::attr_money);
    
    // 从lua配置中读取单位字符串
    std::string unitWan = SystemData::getLayoutString("wx.bag.unit.wan");
    std::string unitYi = SystemData::getLayoutString("wx.bag.unit.yi");
    
    // 如果lua中没有配置，使用默认值
    if (unitWan.empty()) unitWan = "W";
    if (unitYi.empty()) unitYi = "E";
    
    char buffer[32];
    
    // 格式化元宝
    if (goldValue < 10000) {
        // 小于1万，直接显示
        sprintf(buffer, "%d", goldValue);
    }
    else if (goldValue < 100000000) {
        // 1万-1亿之间
        float wanValue = goldValue / 10000.0f;
        
        if (goldValue % 10000 == 0) {
            // 整万数
            sprintf(buffer, "%d%s", goldValue / 10000, unitWan.c_str());
        } 
        else if (wanValue < 10) {
            // 1.0万-9.9万
            sprintf(buffer, "%.1f%s", wanValue, unitWan.c_str());
        }
        else if (wanValue < 100) {
            // 10.0万-99.9万
            sprintf(buffer, "%.1f%s", wanValue, unitWan.c_str());
        }
        else if (wanValue < 1000) {
            // 100.0万-999.9万
            sprintf(buffer, "%.1f%s", wanValue, unitWan.c_str());
        }
        else {
            // 1000万以上
            sprintf(buffer, "%d%s", (int)wanValue, unitWan.c_str());
        }
    } 
    else {
        // 1亿以上
        float yiValue = goldValue / 100000000.0f;
        
        if (goldValue % 100000000 == 0) {
            // 整亿数
            sprintf(buffer, "%d%s", goldValue / 100000000, unitYi.c_str());
        } 
        else if (yiValue < 10) {
            // 1.0亿-9.9亿
            sprintf(buffer, "%.1f%s", yiValue, unitYi.c_str());
        }
        else if (yiValue < 100) {
            // 10.0亿-99.9亿
            sprintf(buffer, "%.1f%s", yiValue, unitYi.c_str());
        }
        else {
            // 100亿以上
            sprintf(buffer, "%d%s", (int)yiValue, unitYi.c_str());
        }
    }
    m_pVcoin->setString(buffer);
    
    // 格式化仙玉
    if (diamondValue < 10000) {
        sprintf(buffer, "%d", diamondValue);
    }
    else if (diamondValue < 100000000) {
        float wanValue = diamondValue / 10000.0f;
        
        if (diamondValue % 10000 == 0) {
            sprintf(buffer, "%d%s", diamondValue / 10000, unitWan.c_str());
        } 
        else if (wanValue < 10) {
            sprintf(buffer, "%.1f%s", wanValue, unitWan.c_str());
        }
        else if (wanValue < 100) {
            sprintf(buffer, "%.1f%s", wanValue, unitWan.c_str());
        }
        else if (wanValue < 1000) {
            sprintf(buffer, "%.1f%s", wanValue, unitWan.c_str());
        }
        else {
            sprintf(buffer, "%d%s", (int)wanValue, unitWan.c_str());
        }
    } 
    else {
        float yiValue = diamondValue / 100000000.0f;
        
        if (diamondValue % 100000000 == 0) {
            sprintf(buffer, "%d%s", diamondValue / 100000000, unitYi.c_str());
        } 
        else if (yiValue < 10) {
            sprintf(buffer, "%.1f%s", yiValue, unitYi.c_str());
        }
        else if (yiValue < 100) {
            sprintf(buffer, "%.1f%s", yiValue, unitYi.c_str());
        }
        else {
            sprintf(buffer, "%d%s", (int)yiValue, unitYi.c_str());
        }
    }
    m_pCoupon->setString(buffer);
    
    // 格式化金币
    if (moneyValue < 10000) {
        sprintf(buffer, "%d", moneyValue);
    }
    else if (moneyValue < 100000000) {
        float wanValue = moneyValue / 10000.0f;
        
        if (moneyValue % 10000 == 0) {
            sprintf(buffer, "%d%s", moneyValue / 10000, unitWan.c_str());
        } 
        else if (wanValue < 10) {
            sprintf(buffer, "%.1f%s", wanValue, unitWan.c_str());
        }
        else if (wanValue < 100) {
            sprintf(buffer, "%.1f%s", wanValue, unitWan.c_str());
        }
        else if (wanValue < 1000) {
            sprintf(buffer, "%.1f%s", wanValue, unitWan.c_str());
        }
        else {
            sprintf(buffer, "%d%s", (int)wanValue, unitWan.c_str());
        }
    } 
    else {
        float yiValue = moneyValue / 100000000.0f;
        
        if (moneyValue % 100000000 == 0) {
            sprintf(buffer, "%d%s", moneyValue / 100000000, unitYi.c_str());
        } 
        else if (yiValue < 10) {
            sprintf(buffer, "%.1f%s", yiValue, unitYi.c_str());
        }
        else if (yiValue < 100) {
            sprintf(buffer, "%.1f%s", yiValue, unitYi.c_str());
        }
        else {
            sprintf(buffer, "%d%s", (int)yiValue, unitYi.c_str());
        }
    }
    m_pGold->setString(buffer);
	
	return true;
}

bool BagPanel::initButton()
{
	GeneralMenu* menu = GeneralMenu::create();
	if (menu)
	{
		menu->setAnchorPoint(CCPointZero);
		menu->setPosition(CCPointZero);
		addChild(menu);
	}
	else
		return false;

	//整理按钮
	CCMenuItemTextImage *pPutOff =  SystemData::getMenuItemTextImage("ui.button",SystemData::getLayoutString("wx.bag.sort").c_str(),"微软雅黑",20,ccWHITE);
		/*CCMenuItemTextImage::create(
		SystemData::getLayoutString("ui.button").c_str(),
		SystemData::getLayoutString("ui.button_sel").c_str(),
		this,
		menu_selector(BagPanel::buttonCallBack),
		SystemData::getLayoutString("wx.bag.sort").c_str(),
		"微软雅黑",
		20,
		ccWHITE
		);*/
	if(pPutOff)
	{
		pPutOff->setTarget(this,menu_selector(BagPanel::buttonCallBack));
		pPutOff->setTag(TAG_PUTOFF_PACK);
		pPutOff->setPosition(ccp(m_iWidth/5,35));
		/*if (m_iType1==Pet_Bag || m_iType1==NPC_Bag)
		{
			pPutOff->setPosition(SystemData::getLayoutPoint("ui_housebag_button1_pos"));
		}*/
		menu->addChild(pPutOff);
	}
	CCMenuItemTextImage *pSplit=NULL;
	if (m_iType2==Bag_Type_NPCBag || m_iType1==Self_Bag || m_iType2==Bag_Type_Stone)
	{
		//拆分按钮
		pSplit =  SystemData::getMenuItemTextImage("ui.button",SystemData::getLayoutString("wx.bag.split").c_str(),"微软雅黑",20,ccWHITE);
			/*CCMenuItemTextImage::create(
			SystemData::getLayoutString("ui.button").c_str(),
			SystemData::getLayoutString("ui.button_sel").c_str(),
			SystemData::getLayoutString("ui.button_unable").c_str(),
			this,
			menu_selector(BagPanel::buttonCallBack),
			SystemData::getLayoutString("wx.bag.split").c_str(),
			"微软雅黑",
			20,
			ccWHITE
			);*/
		if(pSplit)
		{
			pSplit->setTarget(this,menu_selector(BagPanel::buttonCallBack));
			pSplit->setTag(TAG_SPLIT_PACK);
			pSplit->setPosition(ccp(m_iWidth/5*4,35));
			/*if (m_iType1==Pet_Bag || m_iType1==NPC_Bag)
			{
				pSplit->setPosition(SystemData::getLayoutPoint("ui_housebag_button2_pos"));
			}*/
			menu->addChild(pSplit);
			//
			if (m_iType2==Bag_Type_Npcshop)
			{
				pSplit->setEnabled(false);
			}
		}
	}
	else
	{
		//取出按钮（包括交易界面和摆摊界面）
		pSplit = SystemData::getMenuItemTextImage("ui.button",SystemData::getLayoutString("wx.bag.takeout").c_str(),"微软雅黑",20,ccWHITE);
			/*CCMenuItemTextImage::create(
			SystemData::getLayoutString("ui.button").c_str(),
			SystemData::getLayoutString("ui.button_sel").c_str(),
			this,
			menu_selector(BagPanel::buttonCallBack),
			SystemData::getLayoutString("wx.bag.takeout").c_str(),
			"微软雅黑",
			20,
			ccWHITE
			);*/
		if(pSplit)
		{
			pSplit->setTarget(this,menu_selector(BagPanel::buttonCallBack));
			pSplit->setTag(TAG_TAKE_PACK);
			pSplit->setPosition(ccp(m_iWidth/5 * 4,35));
			menu->addChild(pSplit);
		}
	}
	

	return true;
}

void BagPanel::buttonCallBack( CCObject* pSender )
{
 	CCMenuItemImage* pMenu = dynamic_cast<CCMenuItemImage*>(pSender);
 	if(pMenu)
 	{
 		int tag = pMenu->getTag();
		OpenSpilt(false);
 		switch(tag)
 		{
		case TAG_PUTOFF_PACK://整理
			SortBag();
			break;
		case TAG_TAKE_PACK://取出所有物品
			TakeOutBag();
			break;
		case TAG_SPLIT_PACK://分解模式开启
			m_bSpilt=!m_bSpilt;
			OpenSpilt(m_bSpilt);
			break;
 		/*case TAG_NEXT_PAGE:
 			{
 				current_layer_idx += 1;
				if(current_layer_idx > (m_iPage-1))
				{
					current_layer_idx = 0;
				}
				char c_page[5];
				sprintf(c_page, "%d/%d", current_layer_idx+1, m_iPage);
				m_pCurrentPage->setString(c_page);
				((BagCellPanel*)getChildByTag(TAG_BAGCELL))->updatePage(current_layer_idx);
 			}
 			break;
 		case TAG_PRE_PAGE:
 			{
 				current_layer_idx -= 1;
				if(current_layer_idx < 0)
				{
					current_layer_idx = m_iPage -1;
				}
				char c_page[5];
				sprintf(c_page, "%d/%d", current_layer_idx+1, m_iPage);
				m_pCurrentPage->setString(c_page);
				((BagCellPanel*)getChildByTag(TAG_BAGCELL))->updatePage(current_layer_idx);
 			}
 			break;*/
 		default:
 			break;
 		}
 	}
}

void BagPanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA )
	{

		if (m_iType2==Bag_Type_NPCBag || m_iType1==Self_Bag || m_iType2==Bag_Type_Stone || m_iType1==House_Bag)
		{
			initMoney();
		}	
	}
}
/*

bool BagSort(UserItem* v1, UserItem* v2){	
	return v1->sid < v2->sid;	
}*/

void BagPanel::SortBag()
{
	BagOperator::SetBagType(m_iType1);
	BagOperator::StartDoSortBag();
	//return;
	//PileItem();
	//return;
	/*if (m_iSortTime!=0)
	{
		//CPEventHelper::uiNotify("","",Error::CanNotClickQuick);
		return;
	}
	m_iSortTime=1;
	int start,end;
	switch (m_iType1)
	{
	case Self_Bag:
		start = ItemPos::Player_Bag_Start;
		end =  ItemPos::Player_Bag_End;
		break;
	case Role_Bag:
		start = ItemPos::Player_Bag_Start;
		end =  ItemPos::Player_Bag_End;
		break;
	case Pet_Bag:
		start = ItemPos::Pet_Bag_Start;
		end =  ItemPos::Pet_Bag_End;
		break;
	case House_Bag:
		start = ItemPos::Treasure_Warehouse_Start;
		end =  ItemPos::Treasure_Warehouse_End;
		break;
	case Booth_Bag:
		start = ItemPos::Market_Bag_Start;
		end =  ItemPos::Market_Bag_End;
		break;
	case Pet_Bag_Shop:
		start = ItemPos::Pet_Bag_Start;
		end =  ItemPos::Pet_Bag_End;
		break;
	case Stone_Bag:
		start = ItemPos::Player_Bag_Start;
		end =  ItemPos::Player_Bag_End;
		break;
	case NPC_Bag:
		start = ItemPos::NPC_Bag_Start;
		end =  ItemPos::NPC_Bag_End;
		break;
	default:
		start = 0;
		end =  0;
		break;
	}
	int n=0;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	std::vector<UserItem*> ItemList;
	ItemList.clear();
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		int pos=it->first;
		if ((pos >= start && pos<end ))
		{
			UserItem* item=it->second;
			ItemList.push_back(item);
			n++;				
		}
	}

	std::sort(ItemList.begin(),ItemList.end(),BagSort);

	n=0;
	
	for (std::vector<UserItem*>::iterator it1 = ItemList.begin();it1!=ItemList.end();it1++ )
	{
		UserItem* item=(UserItem*)*it1;
		if ((start+n)!=item->position)
		{
			MsgItemOperationRequestSetPosition* req1=new MsgItemOperationRequestSetPosition;
			req1->iid=item->iid;
			req1->position=start+n;
			HandleMessage::sendMessage(req1);
		}
		n++;
	}*/
}

void BagPanel::TakeOutBag()
{
	int start = 0;
	int end =  0;
	if (m_iType1==Pet_Bag)
	{
		start = ItemPos::Pet_Bag_Start;
		end =  ItemPos::Pet_Bag_End;
	}
	else if (m_iType1==House_Bag)
	{
		start = ItemPos::Treasure_Warehouse_Start;
		end =  ItemPos::Treasure_Warehouse_End;
	}
	else if (m_iType1==NPC_Bag)
	{
		start = ItemPos::NPC_Bag_Start;
		end =  ItemPos::NPC_Bag_End;
	}
	if (start==0 && end==0)
	{
		return;
	}
	int tgt = ItemPos::Player_Bag_Start;
	if (m_iType2==Bag_Type_Pet)
	{
		tgt = ItemPos::Pet_Bag_Start;
	}
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	int n=1;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		int pos=it->first;
		if ((pos >= start && pos<end ))
		{
			MsgItemOperationRequestSetPosition* req=new MsgItemOperationRequestSetPosition;
			req->iid=it->second->iid;
			int newpos=GameData::s_user->getUserItemData()->getEmptyPosition(tgt,n);
			req->position=newpos;
			if (newpos=0)
			{
				break;
			}
			n++;
			HandleMessage::sendMessage(req);
		}
	}
}

void BagPanel::OpenSpilt(bool flag)
{
	//m_bSpilt=flag;
	((BagCellPanel*)(this->getChildByTag(TAG_BAGCELL)))->setspiltState(flag);
}

void BagPanel::setType2( int type )
{
	m_iType2=type;
	((BagCellPanel*)(this->getChildByTag(TAG_BAGCELL)))->setType2(m_iType2);
}

void BagPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			updatetime(1);
		}
	}
}

void BagPanel::updatetime( int index )
{
	if (m_iSortTime!=0)
	{
		m_iSortTime=m_iSortTime-index;
	}
}

void BagPanel::PileItem()
{
	/*if (m_iSortTime!=0)
	{
		//CPEventHelper::uiNotify("","",Error::CanNotClickQuick);
		return;
	}
	m_iSortTime=1;
	int bagtype = 0;
	int start,end;
	switch (m_iType1)
	{
	case Self_Bag:
		start = ItemPos::Player_Bag_Start;
		end =  ItemPos::Player_Bag_End;
		bagtype =  ItemPos::Bag_Player;
		break;
	case Role_Bag:
		start = ItemPos::Player_Bag_Start;
		end =  ItemPos::Player_Bag_End;
		bagtype =  ItemPos::Bag_Player;
		break;
	case Pet_Bag:
		start = ItemPos::Pet_Bag_Start;
		end =  ItemPos::Pet_Bag_End;
		bagtype =  ItemPos::Bag_Pet;
		break;
	case House_Bag:
		start = ItemPos::Treasure_Warehouse_Start;
		end =  ItemPos::Treasure_Warehouse_End;
		bagtype =  ItemPos::Bag_Warehouse;
		break;
	case Booth_Bag:
		start = ItemPos::Market_Bag_Start;
		end =  ItemPos::Market_Bag_End;
		bagtype =  ItemPos::Bag_Market;
		break;
	case Pet_Bag_Shop:
		start = ItemPos::Pet_Bag_Start;
		end =  ItemPos::Pet_Bag_End;
		bagtype =  ItemPos::Bag_Pet;
		break;
	case Stone_Bag:
		start = ItemPos::Player_Bag_Start;
		end =  ItemPos::Player_Bag_End;
		bagtype =  ItemPos::Bag_Player;
		break;
	case NPC_Bag:
		start = ItemPos::NPC_Bag_Start;
		end =  ItemPos::NPC_Bag_End;
		bagtype =  ItemPos::Bag_NPC;
		break;
	default:
		start = 0;
		end =  0;
		bagtype =  ItemPos::Bag_All;
		break;
	}

	UserItems items = GameData::s_user->getUserItemData()->userItems;
	std::map<int,int> ItemList;
	ItemList.clear();
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		int pos=it->first;
		if ((pos >= start && pos<end ))
		{
			UserItem* item=it->second;
			if (item->count<item->maxStack)
			{
				int n = ItemList[item->sid];
				ItemList[item->sid] = ++n;
			}
		}
	}
	
	for (std::map<int,int>::iterator it1 = ItemList.begin();it1!=ItemList.end();it1++ )
	{
		int cnt = it1->second;
		if (cnt>1)
		{
			MsgItemOperationRequestPile* req=new MsgItemOperationRequestPile;
			req->sid=it1->first;
			CCLog("pile item sid = %d",req->sid);
			req->bagtype=bagtype;
			HandleMessage::sendMessage(req);
		}
	}*/
}
