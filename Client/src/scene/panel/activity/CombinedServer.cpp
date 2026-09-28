#include "ActivityModule.h"
#include "ActivityDataHelper.h"
#include "CombinedServer.h"
#include "controls/CPItemComponents.h"
#include "controls/CPChecker.h"
#include "patchdata/ScriptPatchManager.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "event/EventProtocol.h"
#include "event/CPEvent.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"
#include "EvtDataDefinition.h"

#include "MsgShop.h"
#include "network/HandleMessage.h"

#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "scene/panel/EffectSprite.h"

#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/SystemData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/FuncData.h"
#include "userdata/ActivityData.h"
#include "userdata/WorldData.h"

#include "utils/StringUtils.h"
#include "controls/CPChecker.h"

/////////CombinedServer////////////////////////////////////////////
CombinedServer::CombinedServer()
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_DATA_READY, this);
}

CombinedServer::~CombinedServer()
{
	CPEvtDispatcher.removeEventListener(this);
}

bool CombinedServer::init()
{
	if (!MenuListPanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));
	
	// ========== 位置设置结束 ==========

	// 原有代码保持不变
	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "combinedServerTitle2");
	addChild(title);

	return true;
}

void CombinedServer::hide()
{
	this->removeFromParent();
}

const std::string CombinedServer::dataTableName()
{
	return "gdCombinedSvrOptions2";
}

void CombinedServer::onSwitch( int tag )
{
	int nScriptId = PanelTag2ScriptId(tag);
	if (nScriptId != tag && ScriptPatchManager::instance()->ScriptNeedUpdate(nScriptId))
	{
		ScriptPatchManager::instance()->UpdateScript(nScriptId);
	}
	else
	{
		doSwitch(tag);
	}
}

void CombinedServer::onCPEvent(const std::string& name)
{
	if (name == CPEventName::MSG_DATA_READY)
	{
		const std::string &source = CPEventHelper::getEventSource();
		if (source == "ScriptPatchManager")
		{
			int nScriptId = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
			ScriptPatchManager::instance()->UpdateLastFetchTime(nScriptId);
			ScriptPatchManager::instance()->EnableScript(nScriptId);
			doSwitch(ScriptId2PanelTag(nScriptId));
		}
	}
}

void CombinedServer::doSwitch(int tag)
{
	switch (tag)
	{
	case panel_fengkuangqianggou:
		{
			BuyCrazyFeedBack* panel = BuyCrazyFeedBack::create();
			addPanel(panel);
			break;
		}
	case panel_mashangqianggou:
		{
			BuyImmediatelyFeedBack* panel = BuyImmediatelyFeedBack::create();
			addPanel(panel);
			break;
		}
	case Panel_huodongshangdian:
		{
			MsgOpenShopRequest* msg = new MsgOpenShopRequest;
			msg->shopId = 18;
			//msg->clientDataVer = 1;
			HandleMessage::sendMessage(msg);
			ActivityShop* panel = ActivityShop::create();
			addPanel(panel);
			break;
		}
	case Panel_duihuanshangdian:		
		{
			MsgOpenShopRequest* msg = new MsgOpenShopRequest;
			msg->shopId = 19;
			//msg->clientDataVer = 1;
			HandleMessage::sendMessage(msg);
			ExchangeShop *panel = ExchangeShop::create();
			addPanel(panel);
			break;
	    }
	case Panel_yuanbaohuikui:
		{	
			YuanbiaoFeedBack *panel = YuanbiaoFeedBack::create();
			addPanel(panel);
			break;
		}		
	case Panel_qianghuahuikui:
		{
			QianghuaFeedBack *panel = QianghuaFeedBack::create();
			addPanel(panel);
			break;
		}
	case Panel_chongwuhuikui:
		{
			PetFeedBack *panel = PetFeedBack::create();
			addPanel(panel);
			break;
		}		
	case Panel_hunshihuikui:
		{
			HunshiFeedBack *panel = HunshiFeedBack::create();
			addPanel(panel);
			break;
		}	
	case Panel_chibanghuikui:
		{
			ChibangFeedBack *panel = ChibangFeedBack::create();
			addPanel(panel);
			break;
		}
	case Panel_xunbaohuikui:
		{
			XunbaoFeedBack *panel = XunbaoFeedBack::create();
			addPanel(panel);
			break;
		}
	case Panel_shizhuanghuikui:
		{
			ShizhuangFeedBack *panel = ShizhuangFeedBack::create();
			addPanel(panel);
			break;
		}
	case Panel_huanwuhuikui:
		{
			HuanwuFeedBack *panel = HuanwuFeedBack::create();
			addPanel(panel);
			break;
		}
	case Panel_meirihuikui:
		{
			DailyFeedBack *panel = DailyFeedBack::create();
			addPanel(panel);
			break;
		}
	case Panel_leijichongzhi:
		{
			TotalRechargeFeedBack *panel = TotalRechargeFeedBack::create();
			addPanel(panel);
			break;
		}
	case Panel_chongfuchongzhi:
		{
			RepeatRechargeFeedBack *panel = RepeatRechargeFeedBack::create();
			addPanel(panel);
			break;
		}
	case Panel_huodongshouchong:
		{
			FirstRechargeFeedBack *panel = FirstRechargeFeedBack::create();
			addPanel(panel);
			break;
		}
	case Panel_danbichongzhi:
		{
			SingleRechargeFeedBack *panel = SingleRechargeFeedBack::create();
			addPanel(panel);
			break;
		}
	default:
		break;
	}
}

//----------------------------------活动商店------------------------

ActivityShop::ActivityShop()
	:m_curPrice(0)
	,mStateLayer(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

ActivityShop::~ActivityShop()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool ActivityShop::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initUI();
	//	refreshList();

	return true;
}

void ActivityShop::initUI()
{
	//board
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "activityShopBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "activityShopBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "activityShopList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "activityShopItemSize");
	const int perLine = LayoutData::getInt(CPModuleName::ACTIVITY, "activityShopPerLine");
	mItemList = CPItemComponents::create(listSize, new CPLayoutGrid(perLine, itemSize, true));
	mItemList->setClickSensitive(true);
	mItemList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "activityShopList"));
	addChild(mItemList);

	// state layer
	mStateLayer = CCLayer::create();
	addChild(mStateLayer);

	//活动时间
	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY, "activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText", CombinedServer::Panel_huodongshangdian, "activitystarttime", startTime);
	LuaData::getProp("gdActivityText", CombinedServer::Panel_huodongshangdian, "activityendtime", endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	int dhqNeedGold = 0;
	dhqNeedGold = WorldData::getWorldDataX(10100);//需要消耗多少元宝获得一张兑换券
	if (dhqNeedGold == 0) dhqNeedGold = 100;
	LuaData::getProp("gdActivityText",CombinedServer::Panel_huodongshangdian,"textintroduce",textInfo);
	CCString* textStr = CCString::createWithFormat(textInfo.c_str(),dhqNeedGold);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textStr->getCString());
	addChild(topTextInfo);

}

void ActivityShop::refreshList()
{
	mItemList->removeAllItems();
	mStateLayer->removeAllChildren();

	const int itemCnt = GameData::s_user->mShopItems.size();

	for (int i = 0; i < itemCnt; i++)
	{
		CCNode *item = getListItem(i);
		mItemList->addItem(item);	
	}	

	std::string goldStr = SystemData::intToString(HeroData::getProp(Entity::attr_gold));
	CCLabelTTF *goldLab = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityShopHaveGold");
	goldLab->setString((goldLab->getString() + goldStr).c_str());
	mStateLayer->addChild(goldLab);
}

CCNode *ActivityShop::getListItem(int index)
{
	CCNode *ret = CCNode::create();
	ret->setContentSize(LayoutData::getSize(CPModuleName::ACTIVITY, "activityShopImage"));

	CCMenuEx *pMenu = CCMenuEx::create();
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);

	CCMenuItemImage* pItem= SystemData::getMenuItemImageByPlist("shop.item.bkg");	
	pItem->setEnabled(false);
	pItem->setAnchorPoint(ccp(0, 1));
	pItem->setPosition(ccp(0, ret->getContentSize().height));

	CCMenuItemImage* pIconBkg = SystemData::getMenuItemImageByPlist("shop.icon.bkg");
	pIconBkg->setTag(index);
	pIconBkg->setTarget(this, menu_selector(ActivityShop::itemClicked)); 
	pMenu->addChild(pIconBkg);  
	pItem->addChild(pMenu);

	CCMenuItemImage* pMenuItem=CCMenuItemImage::create();	
	pMenuItem->setTag(10000 + index);
	pMenuItem->setAnchorPoint(CCPointZero);	
	pMenuItem->setTarget(this, menu_selector(ActivityShop::itemClicked));
	pMenuItem->setContentSize(CCSizeMake(pItem->getContentSize().width-pIconBkg->getContentSize().width, pItem->getContentSize().height));
	pMenuItem->setPosition(ccp(pIconBkg->getContentSize().width, 0));
	pMenu->addChild(pMenuItem);
	pItem->setTag(pMenuItem->getTag());	
	ret->addChild(pItem);

	//add the labels: name, price
	std::string name = "";	
	ShopData& item = GameData::s_user->mShopItems[index];
	LuaData::getProp(LuaData::ITEM, item.itemid, "name", name);
	std::string strLabel[5] = {"itemname", "item_original_price", "item_current_price", "original_price", "current_price"};
	std::string strContent[5] = {name.c_str(), "", "", SystemData::intToString(item.oldprice), SystemData::intToString(item.newprice)};
	for(int p = 0; p < 5; p++)
	{
		std::string key = "shop.lbl." + strLabel[p];
		CCLabelTTF* pLabel=SystemData::getLabelTTF(key);
		pLabel->setFontName("Arial");
		pLabel->setFontSize(16);
		pItem->addChild(pLabel);
		if(p==0 || p==3 || p==4)
		{
			pLabel->setString(strContent[p].c_str());
			if (strContent[p].size()>=27)
			{
				pLabel->setFontSize(14);
			}
		}
	}//显示pItem上的汉字的

	std::string moneyIcon = "vcoin";
	CCSprite* pMoneyIconOri = SystemData::getSpriteByPlist("shop.sprite." + moneyIcon);
	pMoneyIconOri->setPosition(SystemData::getLayoutPoint("shop.point.itemvcoinori"));
	pMoneyIconOri->setScale(0.8f);
	pItem->addChild(pMoneyIconOri);  
	CCSprite* pMoneyIconCur = SystemData::getSpriteByPlist("shop.sprite." + moneyIcon);
	pMoneyIconCur->setPosition(SystemData::getLayoutPoint("shop.point.itemvcoincur"));
	pMoneyIconCur->setScale(0.8f);
	pItem->addChild(pMoneyIconCur);

	//add the item icon
	CCSprite* pIcon = LayoutData::getItemIcon(item.itemid);
	if(pIcon)
	{
		pIcon->setPosition(SystemData::getLayoutPoint("shop.point.itemicon"));
		pIconBkg->addChild(pIcon);	
	}
	return ret;
}

void ActivityShop::itemClicked(CCObject *pSender)
{
	CCNode* pNode = (CCNode*)pSender;
	if(pNode)
	{
		int tag = pNode->getTag();
		bool isicon = false;
		if(tag >= 10000)
		{
			tag -= 10000;
			isicon = true;
		}
		//build the item data
		ShopData& item = GameData::s_user->mShopItems[tag];
		UserItem* pi = CommonFunction::createNewItem(item.itemid);
		m_clickedItem = *pi;
		m_clickedItem.sid = item.itemid;
		m_curPrice = item.newprice;
		LuaData::getProp(LuaData::ITEM, item.itemid, "name", m_clickedItem.name);
		LuaData::getProp(LuaData::ITEM, item.itemid, "icon", m_clickedItem.icon);
		LuaData::getProp(LuaData::ITEM, item.itemid, "desc", m_clickedItem.desc);

		if(!isicon)	
		{
			//show the item tips
			if(getChildByTag(TAG_KEYBOARD))
			{
				removeChildByTag(TAG_KEYBOARD);
			}
			const int row = 2;
			const int col = 2;
			int c = tag % (row * col);
			if (tag <=0 ) c = 0;
			int b = c % col;
			if(c <= 0) b = 0;
			int a = c/row;
			a = col - ( a + 1 );
			CCPoint tipsPos = ccp(196 + b*225, -70 + a*105);

			if(tipsPos.x+245 > SystemData::size_x)
			{
				tipsPos.x -= 245+pNode->getContentSize().width;
			}
			if(tipsPos.y<0)
			{
				tipsPos.y = 0;
			} 

			if (pi->category == ItemCate_Equip || pi->type == ItemType_Pet)
			{
				tipsPos.y = 0;
			}
			if (tipsPos.y > 200)
			{
				tipsPos.y = 200;
			}

			Game::getGameUI()->showTipsPanel(&m_clickedItem, TAG_Tips_GM, tipsPos);
		}
		else
		{
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SHOW_KEYBOARD);
		}
	}
}

void ActivityShop::handleEvent( int channel )
{	
	if(channel == EventProtocol::EVENT_SHOW_KEYBOARD)
	{
		if(getChildByTag(TAG_KEYBOARD))
		{
			removeChildByTag(TAG_KEYBOARD);
		}

		int totalCount = HeroData::getProp(Entity::attr_gold);
		totalCount /= m_curPrice;

		if (totalCount>0)
		{
			int typeId = 0;
			LuaData::getProp("gdShopname","回馈商店",typeId);
			NumberKeyBoard *pNumberBoard = NumberKeyBoard::create(1, typeId, m_curPrice, m_clickedItem.sid);
			pNumberBoard->setPosition(SystemData::getLayoutPoint("activity.shop.point.keyboard"));
			pNumberBoard->setTag(TAG_KEYBOARD);
			addChild(pNumberBoard);
		}
	}

}

void ActivityShop::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_CHANGE)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageShopItemListNotify")
		{
			refreshList();			
		}
	}
	else if (eventName == CPEventName::MSG_FINISH)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageOpenShopResponseEx")
		{
			if (CPEventHelper::isRequestSuccess())
			{

			}
		}		
	}
}


//----------------------------------兑换商店------------------------
ExchangeShop::ExchangeShop():
	mTimeStateLayer(NULL)
	,mStateLayer(NULL)
	,mItemList(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

ExchangeShop::~ExchangeShop()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool ExchangeShop::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();
	if (GameData::s_user->mShopItems.size())
	{
		GameData::s_user->mShopItems.clear();
	}
	refreshList();

	return true;
}

void ExchangeShop::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "activityShopBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "activityShopBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "ExchangeShopList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "ExchangeShopItemSize");
	const int perLine = LayoutData::getInt(CPModuleName::ACTIVITY, "exchangeShopPerLine");
	mItemList = CPItemComponents::create(listSize, new CPLayoutGrid(perLine, itemSize, true));
	mItemList->setClickSensitive(true);
	mItemList->setAnchorPoint(CCPointZero);
	mItemList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "ExchangeShopListpos"));
	addChild(mItemList); 

	mStateLayer = CCLayer::create();
	addChild(mStateLayer);

	//活动时间
	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::Panel_duihuanshangdian,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::Panel_duihuanshangdian,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	int dhqNeedGold = 0;
	dhqNeedGold = WorldData::getWorldDataX(10100);//需要消耗多少元宝获得一张兑换券
	if (dhqNeedGold == 0) dhqNeedGold = 100;
	LuaData::getProp("gdActivityText",CombinedServer::Panel_duihuanshangdian,"textintroduce",textInfo);
	CCString* textStr = CCString::createWithFormat(textInfo.c_str(),dhqNeedGold);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textStr->getCString());
	addChild(topTextInfo);

}

void ExchangeShop::refreshList()
{
	mItemList->removeAllItems();
	mStateLayer->removeAllChildren();

	const int itemCnt = GameData::s_user->mShopItems.size();//temp	
	for (int i = 0; i < itemCnt; i++)
	{
		CCNode *item = getListItem(i);	
		item->setTag(i);
		mItemList->addItem(item);
	}

	int dhq = HeroData::getProp(2000);//获得兑换券的数
	std::string dhqStr = SystemData::intToString(dhq);
	CCLabelTTF *dhqLab = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityShopHaveDuiHuanQuan");
	dhqLab->setString((dhqLab->getString() + dhqStr).c_str());
	mStateLayer->addChild(dhqLab);
}

CCNode * ExchangeShop::getListItem( int index )
{
	CCNode* ret = CCNode::create();
	ret->setContentSize(LayoutData::getSize(CPModuleName::ACTIVITY,"ExchangeShopItemSize"));

	CCScale9Sprite* itemBg = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY,"exchangeShopItemBg");
	itemBg->setPosition(ccp(15,57));
	ret->addChild(itemBg); 

	CCSprite* itemBg0 = LayoutData::getSprite(CPModuleName::ACTIVITY,"exchangeShopItemBg0");
	itemBg0->setAnchorPoint(CCPointZero);
	itemBg0->setPosition(ccp(27,36)); 
	itemBg->addChild(itemBg0);


	CCScale9Sprite * normalsprite = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY,"exchangeNorm");
	CCScale9Sprite * selectsprite = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY,"exchangeSel"); 
	CCMenuItemSprite* btnsprite=CCMenuItemSprite::create(normalsprite,selectsprite);
	btnsprite->setPosition(ccp(itemBg->getPositionX()+60,itemBg->getPositionY()-25));
	btnsprite->setTarget(this,menu_selector(ExchangeShop::onGetReward));
	btnsprite->setTag(GameData::s_user->mShopItems[index].itemid);

	CCMenu* menu = CCMenu::create();
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	ret->addChild(menu);
	menu->addChild(btnsprite);

	//-----------------------------------------------------------------------------------------------
	std::string name = "";	
	ShopData& item = GameData::s_user->mShopItems[index];
	LuaData::getProp(LuaData::ITEM,item.itemid,"name",name);

	//add the item icon
	UserItem* pUserItem = CommonFunction::createNewItem(item.itemid);
	CCMenuItemImage* pIcon = CommonFunction::getItemIconButDelete(pUserItem);
	if(pIcon)
	{
		pIcon->setTarget(this,menu_selector(ExchangeShop::onItem));
		pIcon->setPosition(ccp(itemBg->getPositionX()+59,itemBg->getPositionY()+70));
		menu->addChild(pIcon);	
	}

	//----------------------------------------------------------------------------------------------
	CCLabelTTF* itemName = CCLabelTTF::create();
	itemName->setString(name.c_str());
	itemName->setColor(ccYELLOW);
	itemName->setFontSize(16);
	itemName->setPosition(ccp(itemBg0->getPositionX()+32,itemName->getPositionY()+114));
	itemBg->addChild(itemName);

	
	CCString* dhqstr = CCString::createWithFormat(SystemData::getLayoutString("duihuanquan").c_str(),item.newprice);
	CCLabelTTF* duihuanquan = CCLabelTTF::create();
	duihuanquan->setString(dhqstr->getCString());
	duihuanquan->setColor(ccGREEN);
	duihuanquan->setFontSize(18);
	duihuanquan->setPosition(ccp(itemBg0->getPositionX()+32,itemBg0->getPositionY()-15));
	itemBg->addChild(duihuanquan);

	return ret;
}

void ExchangeShop::onItem( CCObject *target )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)target;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void ExchangeShop::onGetReward(CCObject *target)
{
	CCNode* pNode = dynamic_cast<CCNode*>(target);
	if (pNode)
	{
		int tag = pNode->getTag();
		int id = SystemData::getLayoutValue("duihuanquan_id");
		int cnt = HeroData::getProp(2000);
		FuncData::setCurFuncID(16);
		FuncData::sendFuncMsg(id,tag);
	}
}

void ExchangeShop::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_CHANGE)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageShopItemListNotify")
		{
			refreshList();
		}
	}
}

//----------------------------------元宝回馈------------------------
YuanbiaoFeedBack::YuanbiaoFeedBack()
{
}

YuanbiaoFeedBack::~YuanbiaoFeedBack()
{
}

bool YuanbiaoFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void YuanbiaoFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY, "activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText", CombinedServer::Panel_yuanbaohuikui, "activitystarttime", startTime);
	LuaData::getProp("gdActivityText", CombinedServer::Panel_yuanbaohuikui, "activityendtime", endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	int dhqNeedGold = 0;
	dhqNeedGold = WorldData::getWorldDataX(10100);//需要消耗多少元宝获得一张兑换券
	if (dhqNeedGold == 0) dhqNeedGold = 100;
	LuaData::getProp("gdActivityText",CombinedServer::Panel_yuanbaohuikui,"textintroduce",textInfo);
	CCString* textStr = CCString::createWithFormat(textInfo.c_str(),dhqNeedGold);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textStr->getCString());
	CCSize size = CCSizeMake(LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "feedBackBoard0")->getContentSize().width-10,
		LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "feedBackBoard0")->getContentSize().height);
	topTextInfo->setDimensions(size);
	addChild(topTextInfo);

	int totalYuanBao = 0;//获得活动时间内总消耗的元宝数
	totalYuanBao = ActivityData::getExDataZ(5040);
	std::string ybStr = SystemData::intToString(totalYuanBao);
	CCLabelTTF *dhqLab = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"totalFeedBackYuanBao");
	dhqLab->setString((dhqLab->getString() + ybStr).c_str());
	addChild(dhqLab);

	m_pTableView = CCTableViewEx::create(this, SystemData::getLayoutSize("feedBack.frame.bg"), kCCScrollViewDirectionVertical, this, NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20, 25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize YuanbiaoFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* YuanbiaoFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("YB_feedback_id_begin") + idx + 1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item", SystemData::getLayoutValue("feedback_Item.w"), SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 80*i, SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward", index, "reward", i + 1, "itemID", reqsid);
			LuaData::getProp("gdRepayReward", index, "reward", i + 1, "itemcnt", reqcnt);
			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this, menu_selector(YuanbiaoFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward", index, "text", notify);		
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "feedBackDescLab");	
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30, SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");	
		pButton->setTarget(this, menu_selector(YuanbiaoFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);
	}
	return cell;
}

unsigned int YuanbiaoFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("YB_feedback_id_begin"));
}

void YuanbiaoFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage = (CCMenuItemImage*)target;
	UserItem* pItem = (UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem, TAG_Tips);
}

void YuanbiaoFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void YuanbiaoFeedBack::onCPEvent( const std::string &eventName )
{

}

//----------------------------------强化回馈------------------------
QianghuaFeedBack::QianghuaFeedBack()
{
}

QianghuaFeedBack::~QianghuaFeedBack()
{
}

bool QianghuaFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void QianghuaFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY, "activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText", CombinedServer::Panel_qianghuahuikui, "activitystarttime", startTime);
	LuaData::getProp("gdActivityText", CombinedServer::Panel_qianghuahuikui, "activityendtime", endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText", CombinedServer::Panel_qianghuahuikui, "textintroduce", textInfo);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityFeedBackTextLabel");
	topTextInfo->setString(textInfo.c_str());
	CCSize size = CCSizeMake(LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "feedBackBoard0")->getContentSize().width-10,
		LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "feedBackBoard0")->getContentSize().height);
	topTextInfo->setDimensions(size);
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this, SystemData::getLayoutSize("feedBack.frame.bg"), kCCScrollViewDirectionVertical, this, NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20, 25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize QianghuaFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* QianghuaFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("QH_feedback_id_begin") + idx + 1;
		LuaData::getProp_size("gdRepayReward", index, "reward", size);
		for (int i = 0; i < size; i++)
		{
			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward", index, "reward", i + 1, "itemID", reqsid);
			LuaData::getProp("gdRepayReward", index, "reward", i + 1, "itemcnt", reqcnt);
			if (reqcnt == 0)
			{
				continue;
			}
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item", SystemData::getLayoutValue("feedback_Item.w"), SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i, SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this, menu_selector(QianghuaFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward", index, "text", notify);		
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "feedBackDescLab");	
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30, SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");	
		pButton->setTarget(this, menu_selector(QianghuaFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);
	}
	return cell;
}

unsigned int QianghuaFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("QH_feedback_id_begin"));
}

void QianghuaFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage = (CCMenuItemImage*)target;
	UserItem* pItem = (UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem, TAG_Tips);
}

void QianghuaFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void QianghuaFeedBack::onCPEvent( const std::string &eventName )
{

}

//----------------------------------宠物回馈------------------------
PetFeedBack::PetFeedBack()
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

PetFeedBack::~PetFeedBack()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool PetFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void PetFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY, "activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText", CombinedServer::Panel_chongwuhuikui, "activitystarttime", startTime);
	LuaData::getProp("gdActivityText", CombinedServer::Panel_chongwuhuikui, "activityendtime", endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText", CombinedServer::Panel_chongwuhuikui, "textintroduce", textInfo);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityFeedBackTextLabel");
	topTextInfo->setString(textInfo.c_str());
	CCSize size = CCSizeMake(LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "feedBackBoard0")->getContentSize().width-10,
		LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "feedBackBoard0")->getContentSize().height);
	topTextInfo->setDimensions(size);
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this, SystemData::getLayoutSize("feedBack.frame.bg"), kCCScrollViewDirectionVertical, this, NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20, 25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize PetFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* PetFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("CW_feedback_id_begin") + idx + 1;
		LuaData::getProp_size("gdRepayReward", index, "reward", size);
		for (int i = 0; i < size; i++)
		{
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item", SystemData::getLayoutValue("feedback_Item.w"), SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i, SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward", index, "reward", i + 1, "itemID", reqsid);
			LuaData::getProp("gdRepayReward", index, "reward", i + 1, "itemcnt", reqcnt);
			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this, menu_selector(PetFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward", index, "text", notify);		
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30, SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");	
		pButton->setTarget(this, menu_selector(PetFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);

		if (ActivityData::getExDataX(index) == 0)
		{
//			pButton->setVisible(false);
//			CCSprite* pFlag = SystemData::getSpriteByPlist("Login_Reward_hasget");
//			pFlag->setPosition(pButton->getPosition());
//			pLayer->addChild(pFlag);
		}
	}
	return cell;
}

unsigned int PetFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("CW_feedback_id_begin"));
}

void PetFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage = (CCMenuItemImage*)target;
	UserItem* pItem = (UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem, TAG_Tips);
}

void PetFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void PetFeedBack::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();

	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source=="HandleMessageFuncDataNotify")
		{
			int funcid = FuncData::getCurFuncID();
			if (funcid == 19)
			{
				if (m_pTableView)
				{
					CCPoint point = m_pTableView->getContentOffset();
					m_pTableView->reloadData();
					m_pTableView->setContentOffset(point);
				}
			}
		}
	}
}

//----------------------------------魂石回馈------------------------
HunshiFeedBack::HunshiFeedBack()
{
}

HunshiFeedBack::~HunshiFeedBack()
{
}

bool HunshiFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void HunshiFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY, "activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText", CombinedServer::Panel_hunshihuikui, "activitystarttime", startTime);
	LuaData::getProp("gdActivityText", CombinedServer::Panel_hunshihuikui, "activityendtime", endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText", CombinedServer::Panel_hunshihuikui, "textintroduce", textInfo);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityFeedBackTextLabel");
	topTextInfo->setString(textInfo.c_str());
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this, SystemData::getLayoutSize("feedBack.frame.bg"), kCCScrollViewDirectionVertical, this, NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20, 25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize HunshiFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* HunshiFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("HS_feedback_id_begin") + idx + 1;
		LuaData::getProp_size("gdRepayReward", index, "reward", size);
		for (int i = 0; i < size; i++)
		{
			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward", index, "reward", i + 1, "itemID", reqsid);
			LuaData::getProp("gdRepayReward", index, "reward", i + 1, "itemcnt", reqcnt);
			if (reqcnt == 0)
			{
				continue;
			}
// 			std::string name;
// 
// 			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemname",name);
// 			LuaData::getProp("gdRewardEx",name,"reward",reqsid,"type",reqsid);
// 			LuaData::getProp("gdRewardEx",name,"reward",reqsid,"count",reqcnt);
			 
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item", SystemData::getLayoutValue("feedback_Item.w"), SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i, SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this, menu_selector(HunshiFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward", index, "text", notify);		
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "feedBackDescLab");	
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30, SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");	
		pButton->setTarget(this, menu_selector(HunshiFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);
	}
	return cell;
}

unsigned int HunshiFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("HS_feedback_id_begin"));
}

void HunshiFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage = (CCMenuItemImage*)target;
	UserItem* pItem = (UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void HunshiFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void HunshiFeedBack::onCPEvent( const std::string &eventName )
{

}

//----------------------------------翅膀回馈------------------------
ChibangFeedBack::ChibangFeedBack()
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

ChibangFeedBack::~ChibangFeedBack()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool ChibangFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void ChibangFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::Panel_chibanghuikui,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::Panel_chibanghuikui,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText",CombinedServer::Panel_chibanghuikui,"textintroduce",textInfo);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textInfo.c_str());
	CCSize size = CCSizeMake(LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "feedBackBoard0")->getContentSize().width-10,
		LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "feedBackBoard0")->getContentSize().height);
	topTextInfo->setDimensions(size);
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("feedBack.frame.bg"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20,25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize ChibangFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* ChibangFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("CB_feedback_id_begin")+idx+1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item",SystemData::getLayoutValue("feedback_Item.w"),SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i,SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemID",reqsid);
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemcnt",reqcnt);
			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this,menu_selector(ChibangFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward",index,"text",notify);
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30,SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");	
		pButton->setTarget(this,menu_selector(ChibangFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);

		int x = ActivityData::getExDataX(index);
		int y = ActivityData::getExDataY(index);
		if (x == y)
		{
//			pButton->setVisible(false);
//			CCSprite* pFlag = SystemData::getSpriteByPlist("Login_Reward_hasget");
//			pFlag->setPosition(pButton->getPosition());
//			pLayer->addChild(pFlag);
		}
	}
	return cell;
}

unsigned int ChibangFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("CB_feedback_id_begin"));
}

void ChibangFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)target;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void ChibangFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void ChibangFeedBack::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();

	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source=="HandleMessageFuncDataNotify")
		{
			int funcid = FuncData::getCurFuncID();
			if (funcid == 19)
			{
				if (m_pTableView)
				{
					CCPoint point = m_pTableView->getContentOffset();
					m_pTableView->reloadData();
					m_pTableView->setContentOffset(point);
				}
			}
		}
	}
}

//----------------------------------寻宝回馈------------------------
XunbaoFeedBack::XunbaoFeedBack()
{
}

XunbaoFeedBack::~XunbaoFeedBack()
{
}

bool XunbaoFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void XunbaoFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::Panel_xunbaohuikui,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::Panel_xunbaohuikui,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText",CombinedServer::Panel_xunbaohuikui,"textintroduce",textInfo);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textInfo.c_str());
	addChild(topTextInfo);

	int searchTimes = 0;//获得当日寻宝次数
	searchTimes = ActivityData::getExDataZ(5025);//ActivityData::getExDataX(EvtData::evt_xb);
	std::string ybStr = SystemData::intToString(searchTimes);
	CCLabelTTF *dhqLab = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"dailySearchBaoTimes");
	dhqLab->setString((dhqLab->getString() + ybStr).c_str());
	addChild(dhqLab);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("feedBack.frame.bg"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20,25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize XunbaoFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* XunbaoFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("XB_feedback_id_begin")+idx+1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item",SystemData::getLayoutValue("feedback_Item.w"),SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i,SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemID",reqsid);
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemcnt",reqcnt);
			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this,menu_selector(XunbaoFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward",index,"text",notify);
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30,SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");	
		pButton->setTarget(this,menu_selector(XunbaoFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);
	}
	return cell;
}

unsigned int XunbaoFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("XB_feedback_id_begin"));
}

void XunbaoFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)target;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void XunbaoFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void XunbaoFeedBack::onCPEvent( const std::string &eventName )
{

}

//----------------------------------时装回馈------------------------
ShizhuangFeedBack::ShizhuangFeedBack()
{
}

ShizhuangFeedBack::~ShizhuangFeedBack()
{
}

bool ShizhuangFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void ShizhuangFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::Panel_shizhuanghuikui,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::Panel_shizhuanghuikui,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText",CombinedServer::Panel_shizhuanghuikui,"textintroduce",textInfo);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textInfo.c_str());
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("feedBack.frame.bg"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20,25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize ShizhuangFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* ShizhuangFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("SZ_feedback_id_begin")+idx+1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item",SystemData::getLayoutValue("feedback_Item.w"),SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i,SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemID",reqsid);
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemcnt",reqcnt);
			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this,menu_selector(ShizhuangFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward",index,"text",notify);
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30,SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");	
		pButton->setTarget(this,menu_selector(ShizhuangFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);
	}
	return cell;
}

unsigned int ShizhuangFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("SZ_feedback_id_begin"));
}

void ShizhuangFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)target;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void ShizhuangFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void ShizhuangFeedBack::onCPEvent( const std::string &eventName )
{

}

//----------------------------------幻武回馈------------------------
HuanwuFeedBack::HuanwuFeedBack()
{
}

HuanwuFeedBack::~HuanwuFeedBack()
{
}

bool HuanwuFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void HuanwuFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::Panel_huanwuhuikui,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::Panel_huanwuhuikui,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText",CombinedServer::Panel_huanwuhuikui,"textintroduce",textInfo);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textInfo.c_str());
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("feedBack.frame.bg"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20,25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize HuanwuFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* HuanwuFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("HW_feedback_id_begin")+idx+1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item",SystemData::getLayoutValue("feedback_Item.w"),SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i,SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemID",reqsid);
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemcnt",reqcnt);
			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this,menu_selector(HuanwuFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward",index,"text",notify);
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());	
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30,SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");
		pButton->setTarget(this,menu_selector(HuanwuFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);
	}
	return cell;
}

unsigned int HuanwuFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("HW_feedback_id_begin"));
}

void HuanwuFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)target;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void HuanwuFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void HuanwuFeedBack::onCPEvent( const std::string &eventName )
{

}



//-------------------------------------------------------------------每日回馈----------------------

DailyFeedBack::DailyFeedBack()
{
}

DailyFeedBack::~DailyFeedBack()
{
}

bool DailyFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void DailyFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::Panel_meirihuikui,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::Panel_meirihuikui,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	int dhqNeedGold = 0;
	dhqNeedGold = WorldData::getWorldDataX(10100);//需要消耗多少元宝获得一张兑换券
	if (dhqNeedGold == 0) dhqNeedGold = 100;
	LuaData::getProp("gdActivityText",CombinedServer::Panel_meirihuikui,"textintroduce",textInfo);
	CCString* textStr = CCString::createWithFormat(textInfo.c_str(),dhqNeedGold);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textStr->getCString());
	addChild(topTextInfo);

	int dailyYuanBao = 0;//获得当日消耗的元宝数
	dailyYuanBao = ActivityData::getExDataZ(5000);
	std::string ybStr = SystemData::intToString(dailyYuanBao);
	CCLabelTTF *dhqLab = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"dailyFeedBackYuanBao");
	dhqLab->setString((dhqLab->getString() + ybStr).c_str());
	addChild(dhqLab);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("feedBack.frame.bg"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20,25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize DailyFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* DailyFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("MR_feedback_id_begin")+idx+1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item",SystemData::getLayoutValue("feedback_Item.w"),SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i,SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemID",reqsid);
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemcnt",reqcnt);
			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this,menu_selector(DailyFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward",index,"text",notify);
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30,SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");
		pButton->setTarget(this,menu_selector(DailyFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);
	}
	return cell;
}

unsigned int DailyFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("MR_feedback_id_begin"));
}

void DailyFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)target;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void DailyFeedBack::onCPEvent( const std::string &eventName )
{

}

void DailyFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

//----------------------------------疯狂抢购------------------------

BuyCrazyFeedBack::BuyCrazyFeedBack()
{

}

BuyCrazyFeedBack::~BuyCrazyFeedBack()
{

}

bool BuyCrazyFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void BuyCrazyFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::panel_fengkuangqianggou,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::panel_fengkuangqianggou,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText",CombinedServer::panel_fengkuangqianggou,"textintroduce",textInfo);
	CCString* textStr = CCString::createWithFormat(textInfo.c_str());
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textStr->getCString());
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("feedBack.frame.bg"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20,25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize BuyCrazyFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* BuyCrazyFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("FK_feedback_id_begin")+idx+1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemID",reqsid);
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemcnt",reqcnt);
			std::string rewardname = "";
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemname",rewardname);
			if (reqcnt == 0)
			{
				continue;
			}
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item",SystemData::getLayoutValue("feedback_Item.w"),SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i,SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			if (reqsid==0)
			{
				int id=0;
				switch (HeroData::getJob())
				{
				case UserData::CARRER_ZS:
					id=1;
					break;
				case UserData::CARRER_FS:
					id=3;
					break;
				case UserData::CARRER_DS:
					id=5;
					break;
				default:
					break;
				}
				if (HeroData::getGender()==UserData::SEX_FEMALE)
				{
					id++;
				}
				// 				std::string rewardname = "";
				// 				LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemname",rewardname);
				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"type",reqsid);
				//				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"count",reqcnt);
				if (reqsid == 0)
				{
					continue;
				}
			}

			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this,menu_selector(BuyCrazyFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward",index,"text",notify);
// 		int i = 100;
// 		notify += StringUtils::toString(i);
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30,SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "fengkuangBtn");
		pButton->setTarget(this,menu_selector(BuyCrazyFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);
	}
	return cell;
}

unsigned int BuyCrazyFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("FK_feedback_id_begin"));
}

void BuyCrazyFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage = (CCMenuItemImage*)target;
	UserItem* pItem = (UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void BuyCrazyFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(23);
		FuncData::sendFuncMsg(tag);
	}
}

void BuyCrazyFeedBack::onCPEvent( const std::string &eventName )
{
	
}

//----------------------------------马上抢购------------------------

BuyImmediatelyFeedBack::BuyImmediatelyFeedBack()
{

}

BuyImmediatelyFeedBack::~BuyImmediatelyFeedBack()
{

}

bool BuyImmediatelyFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void BuyImmediatelyFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::panel_mashangqianggou,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::panel_mashangqianggou,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText",CombinedServer::panel_mashangqianggou,"textintroduce",textInfo);
	CCString* textStr = CCString::createWithFormat(textInfo.c_str());
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textStr->getCString());
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("feedBack.frame.bg"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20,25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize BuyImmediatelyFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* BuyImmediatelyFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("QG_feedback_id_begin")+idx+1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemID",reqsid);
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemcnt",reqcnt);
			std::string rewardname = "";
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemname",rewardname);
			if (reqcnt == 0)
			{
				continue;
			}
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item",SystemData::getLayoutValue("feedback_Item.w"),SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i,SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			if (reqsid==0)
			{
				int id=0;
				switch (HeroData::getJob())
				{
				case UserData::CARRER_ZS:
					id=1;
					break;
				case UserData::CARRER_FS:
					id=3;
					break;
				case UserData::CARRER_DS:
					id=5;
					break;
				default:
					break;
				}
				if (HeroData::getGender()==UserData::SEX_FEMALE)
				{
					id++;
				}
				// 				std::string rewardname = "";
				// 				LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemname",rewardname);
				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"type",reqsid);
				//				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"count",reqcnt);
				if (reqsid == 0)
				{
					continue;
				}
			}

			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this,menu_selector(BuyImmediatelyFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward",index,"text",notify);
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30,SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "qianggouBtn");
		pButton->setTarget(this,menu_selector(BuyImmediatelyFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);
	}
	return cell;
}

unsigned int BuyImmediatelyFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("QG_feedback_id_begin"));
}

void BuyImmediatelyFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage = (CCMenuItemImage*)target;
	UserItem* pItem = (UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void BuyImmediatelyFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(22);
		FuncData::sendFuncMsg(tag);
	}
}

void BuyImmediatelyFeedBack::onCPEvent( const std::string &eventName )
{

}


//----------------------------------------------6 19新加活动-----------------------------------------
//------------------------------------------------累计充值-------------------------------------------


TotalRechargeFeedBack::TotalRechargeFeedBack()
{

}

TotalRechargeFeedBack::~TotalRechargeFeedBack()
{

}

bool TotalRechargeFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void TotalRechargeFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::Panel_leijichongzhi,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::Panel_leijichongzhi,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText",CombinedServer::Panel_leijichongzhi,"textintroduce",textInfo);
	CCString* textStr = CCString::createWithFormat(textInfo.c_str());
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textStr->getCString());
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("feedBack.frame.bg"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20,25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}



cocos2d::CCSize TotalRechargeFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* TotalRechargeFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("LJ_feedback_id_begin")+idx+1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemID",reqsid);
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemcnt",reqcnt);
			std::string rewardname = "";
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemname",rewardname);
			if (reqcnt == 0)
			{
				continue;
			}
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item",SystemData::getLayoutValue("feedback_Item.w"),SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i,SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			if (reqsid==0)
			{
				int id=0;
				switch (HeroData::getJob())
				{
				case UserData::CARRER_ZS:
					id=1;
					break;
				case UserData::CARRER_FS:
					id=3;
					break;
				case UserData::CARRER_DS:
					id=5;
					break;
				default:
					break;
				}
				if (HeroData::getGender()==UserData::SEX_FEMALE)
				{
					id++;
				}
// 				std::string rewardname = "";
// 				LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemname",rewardname);
				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"type",reqsid);
//				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"count",reqcnt);
				if (reqsid == 0)
				{
					continue;
				}
			}

			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this,menu_selector(TotalRechargeFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward",index,"text",notify);
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30,SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");
		pButton->setTarget(this,menu_selector(TotalRechargeFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);
	}
	return cell;
}

unsigned int TotalRechargeFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("LJ_feedback_id_begin"));
}

void TotalRechargeFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage = (CCMenuItemImage*)target;
	UserItem* pItem = (UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void TotalRechargeFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void TotalRechargeFeedBack::onCPEvent( const std::string &eventName )
{

}



//------------------------------------------------------重复充值----------------------------------------



RepeatRechargeFeedBack::RepeatRechargeFeedBack()
{

}

RepeatRechargeFeedBack::~RepeatRechargeFeedBack()
{

}

bool RepeatRechargeFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void RepeatRechargeFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::Panel_chongfuchongzhi,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::Panel_chongfuchongzhi,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	int dhqNeedGold = 0;
	dhqNeedGold = WorldData::getWorldDataZ(SystemData::getLayoutValue("CF_NeedGold_WordID"));
	if (dhqNeedGold == 0) dhqNeedGold = 500;
	LuaData::getProp("gdActivityText",CombinedServer::Panel_chongfuchongzhi,"textintroduce",textInfo);
	CCString* textStr = CCString::createWithFormat(textInfo.c_str(),dhqNeedGold);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textStr->getCString());
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("feedBack.frame.bg"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20,25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}



cocos2d::CCSize RepeatRechargeFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* RepeatRechargeFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("CF_feedback_id_begin")+idx+1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemID",reqsid);
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemcnt",reqcnt);
			if (reqcnt == 0)
			{
				continue;
			}
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item",SystemData::getLayoutValue("feedback_Item.w"),SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i,SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this,menu_selector(RepeatRechargeFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward",index,"text",notify);
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30,SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");
		pButton->setTarget(this,menu_selector(RepeatRechargeFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);
	}
	return cell;
}

unsigned int RepeatRechargeFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("CF_feedback_id_begin"));
}

void RepeatRechargeFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage = (CCMenuItemImage*)target;
	UserItem* pItem = (UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void RepeatRechargeFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void RepeatRechargeFeedBack::onCPEvent( const std::string &eventName )
{

}


//--------------------------------------------------------单笔充值--------------------------------


SingleRechargeFeedBack::SingleRechargeFeedBack()
{

}

SingleRechargeFeedBack::~SingleRechargeFeedBack()
{

}

bool SingleRechargeFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void SingleRechargeFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::Panel_danbichongzhi,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::Panel_danbichongzhi,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText",CombinedServer::Panel_danbichongzhi,"textintroduce",textInfo);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textInfo.c_str());
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("feedBack.frame.bg"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20,25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize SingleRechargeFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* SingleRechargeFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("DB_feedback_id_begin")+idx+1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item",SystemData::getLayoutValue("feedback_Item.w"),SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i,SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemID",reqsid);
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemcnt",reqcnt);
			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this,menu_selector(SingleRechargeFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward",index,"text",notify);
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30,SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");	
		pButton->setTarget(this,menu_selector(SingleRechargeFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);

//		int x = ActivityData::getExDataX(index);
//		int y = ActivityData::getExDataY(index);
//		int z = ActivityData::getExDataY(index);
	}
	return cell;
}

unsigned int SingleRechargeFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("DB_feedback_id_begin"));
}

void SingleRechargeFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)target;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void SingleRechargeFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void SingleRechargeFeedBack::onCPEvent( const std::string &eventName )
{

}







//--------------------------------------------------------活动首冲--------------------------------


FirstRechargeFeedBack::FirstRechargeFeedBack()
{

}

FirstRechargeFeedBack::~FirstRechargeFeedBack()
{

}

bool FirstRechargeFeedBack::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();

	return true;
}

void FirstRechargeFeedBack::initUI()
{
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "feedBackBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "feedBackBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, key);
		addChild(board);
	}

	std::string startTime = ""; 
	std::string endTime = "";
	std::string upTo = LayoutData::getString(CPModuleName::ACTIVITY,"activityFeedBackTimeUp");
	LuaData::getProp("gdActivityText",CombinedServer::Panel_huodongshouchong,"activitystarttime",startTime);
	LuaData::getProp("gdActivityText",CombinedServer::Panel_huodongshouchong,"activityendtime",endTime);
	CCLabelTTF *topTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTimeLabel");
	topTimeLabel->setString((topTimeLabel->getString() + startTime + upTo + endTime).c_str());
	addChild(topTimeLabel);

	std::string textInfo = "";
	LuaData::getProp("gdActivityText",CombinedServer::Panel_huodongshouchong,"textintroduce",textInfo);
	CCLabelTTF *topTextInfo = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"activityFeedBackTextLabel");
	topTextInfo->setString(textInfo.c_str());
	addChild(topTextInfo);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("feedBack.frame.bg"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(ccp(20,25));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
}

cocos2d::CCSize FirstRechargeFeedBack::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("feedback_cell");
}

cocos2d::extension::CCTableViewCell* FirstRechargeFeedBack::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		//--------------------------------------------------------------------------------------
		int size = 0;
		int index = SystemData::getLayoutValue("SC_feedback_id_begin")+idx+1;
		LuaData::getProp_size("gdRepayReward",index,"reward",size);
		for (int i = 0; i < size; i++)
		{
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("feedback_Item",SystemData::getLayoutValue("feedback_Item.w"),SystemData::getLayoutValue("feedback_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x+80*i,SystemData::getLayoutPoint("feedback_Item").y));
			pLayer->addChild(pItemborder);

			//每个Item里加载物品图片
			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemID",reqsid);
			LuaData::getProp("gdRepayReward",index,"reward",i+1,"itemcnt",reqcnt);
			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setPosition(pItemborder->getPosition());
			pItem->setTarget(this,menu_selector(FirstRechargeFeedBack::onItem));
			pMenu->addChild(pItem);
		}

		std::string notify = "";
		LuaData::getProp("gdRepayReward",index,"text",notify);
		CCLabelTTF *pLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"feedBackDescLab");
		pLabel->setString(notify.c_str());
		pLabel->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x - 30,SystemData::getLayoutPoint("feedback_Item").y + 50));
		pLayer->addChild(pLabel);

		CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "feedBackBtn");	
		pButton->setTarget(this,menu_selector(FirstRechargeFeedBack::menuCallBack));
		pButton->setTag(index);
		pButton->setPosition(ccp(SystemData::getLayoutPoint("feedback_Item").x + 89*5, SystemData::getLayoutPoint("feedback_Item").y));
		pMenu->addChild(pButton);

//		int x = ActivityData::getExDataX(index);
//		int y = ActivityData::getExDataY(index);
//		int z = ActivityData::getExDataY(index);
	}
	return cell;
}

unsigned int FirstRechargeFeedBack::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return ActivityDataHelper::getActivityGiftTableCellCount(SystemData::getLayoutValue("SC_feedback_id_begin"));
}

void FirstRechargeFeedBack::onItem( CCObject *target )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)target;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void FirstRechargeFeedBack::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		FuncData::setCurFuncID(19);
		FuncData::sendFuncMsg(tag);
	}
}

void FirstRechargeFeedBack::onCPEvent( const std::string &eventName )
{

}
