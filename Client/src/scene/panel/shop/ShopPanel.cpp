#include "ShopPanel.h"
#include "EntityDefinition.h"
#include "EffectDefinition.h"
#include "ModuleData.h"
#include "VIPModule.h"

#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/netdata/GameRole.h"


#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"
#include "ext/CCActionDestroy.h"
#include "ext/CCMenuEx.h"

#include "controls/CPNodeHelper.h"

#include "network/HandleMessage.h"

#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/SlideTable.h"
#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/EffectSprite.h"
#include "scene/panel/FloatPanelType.h"

#include "utils/StringUtils.h"

ShopPanel::ShopPanel()
	: m_pTopMenuView(NULL)
	, m_pCurCell(NULL)
	, m_nCurType(TAG_SHOP_BEST_SELLER)
	, m_nFinalBuyCount(0)
	, m_pSlideItems(NULL)
	, m_pGold(NULL)
	, m_pIntegration(NULL)
	, m_pCoupon(NULL)
	, m_nCurIndex(0)
	,m_updater(NULL)
	,m_consumeAlertEnable(false)
	,m_pTick(NULL)
	,pAlertBg(NULL)
	,m_Tab(0)
	,m_ItemID(0)
	,m_Page(0)
	,m_isLoading(true)
	,m_SelectItem(NULL)
{
}

ShopPanel::~ShopPanel()
{
	
}

bool ShopPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	const std::string &openPanel = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (openPanel == "ShopPanel")
	{
		m_Tab = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
		m_ItemID = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
	}
	if (m_ItemID<=0)
	{
		m_Tab=0;//getShopTab();
	}
	if (m_Tab<=0)
	{
		m_Tab=TAG_SHOP_BEST_SELLER;
	}
	
	//load the background
	CCSprite* bkgSprite=SystemData::getSprite("shop.background");
	addChild(bkgSprite);

	m_nWidth = bkgSprite->getContentSize().width;
	m_nHeight = bkgSprite->getContentSize().height;

	addCover();//swallow the touch event in case of leaking to the map layer

	CCPoint beginPos = SystemData::getLayoutPoint("shop.item.begin");
	m_pSlideItems = SlideTable::create(beginPos.x,beginPos.y,674,330,3,3,SystemData::getLayoutValue("shop.item.span.w"),SystemData::getLayoutValue("shop.item.span.h"));
	m_pSlideItems->setPosition(ccp(118,91));
	addChild(m_pSlideItems);
	m_pSlideItems->setPageChangeTarget(this,menu_selector(ShopPanel::pageChangeCallBack));

	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("shop.close");
	pClose->setTarget(this,menu_selector(ShopPanel::closeCallBack));
	CCMenuItemImage* pRecharge = SystemData::getMenuItemImageByPlist("shop.recharge");
	pRecharge->setTarget(this,menu_selector(ShopPanel::rechargeCallback));
	CCMenu* pMenu = CCMenu::create(pClose,pRecharge,NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	//cut line 
	CCScale9Sprite* pCutLine=SystemData::getScale9SpriteByPlist("shop.cutline",710,3);
	addChild(pCutLine);

	m_pTopMenuView = CCTableViewEx::create(this,SystemData::getLayoutSize("shop.top.view"),
		kCCScrollViewDirectionHorizontal,this,NULL);
	m_pTopMenuView->setPosition(SystemData::getLayoutPoint("shop.top.view"));
	addChild(m_pTopMenuView );

	//add the bottom money icon: vcoin,coupon,integration
	std::string bottomIcon[3] = {"vcoin","coupon","integration"};
	for (int i=0; i<3; i++)
	{
		CCPoint boardPos = SystemData::getLayoutPoint("shop.frame.labelboard"+StringUtils::toString(i));
		CCSprite* borad = SystemData::getSpriteByPlist("shop.frame.labelboard");
		borad->setPosition(boardPos); 
		borad->setAnchorPoint(ccp(0,0.5));
		addChild(borad);

		CCSprite* pIcon = SystemData::getSpriteByPlist("shop.sprite."+bottomIcon[i]); 
		pIcon->setPosition(SystemData::getLayoutPoint("shop.point.bottom"+bottomIcon[i]));
		pIcon->setScale(0.8); 
		addChild(pIcon); 
	}
	//add the bottom money statistics of the player
	m_pGold = SystemData::getLabelTTF("shop.lbl.yuanbao");
	addChild(m_pGold);
	m_pGold->setString((SystemData::getLayoutString("shop.lbl.yuanbao")+SystemData::intToString(HeroData::getProp(Entity::attr_gold))).c_str());
	m_pCoupon = SystemData::getLabelTTF("shop.lbl.coupon");
	addChild(m_pCoupon);
	m_pCoupon->setString((SystemData::getLayoutString("shop.lbl.coupon")+SystemData::intToString(HeroData::getProp(Entity::attr_diamond))).c_str());
	m_pIntegration = SystemData::getLabelTTF("shop.lbl.integration");
	addChild(m_pIntegration);
	m_pIntegration->setString((SystemData::getLayoutString("shop.lbl.integration")+SystemData::intToString(HeroData::getProp(Entity::attr_intergration))).c_str());
	
	CCMenuItemImage* m_pFrame = SystemData::getMenuItemImageByPlist("shop.consumealert.frame");
	m_pFrame->setTarget(this,menu_selector(ShopPanel::tickCallBack));
	pMenu->addChild(m_pFrame);
	m_pTick = SystemData::getSpriteByPlist("shop.consumealert.tick");
	addChild(m_pTick);
	CCLabelTTF* m_pText = SystemData::getLabelTTF("shop.consumealert.text");
	m_pText->setColor(ccc3(0,186,255));
	m_pText->setFontName("Arial");
	m_pText->setFontSize(14); 
	addChild(m_pText);
	
	pAlertBg=SystemData::getScale9SpriteByPlist("shop.alert",540,30);
	addChild(pAlertBg);

	consumeAlertEnable(true);
	setSelectTab(m_Tab);

	m_nWidth = 118;
	m_nHeight = bkgSprite->getContentSize().height;

	addCover(CCPointZero,kCCMenuHandlerPriority-1);

	return true;
}

void ShopPanel::hide()
{
	MsgCloseShopRequest* msg = new MsgCloseShopRequest;
	HandleMessage::sendMessage(msg);
	Game::getGameUI()->hidePanel(this->getTag());
}
void ShopPanel::addListItem(int i )
{
	CCMenuItemImage* pItem= SystemData::getMenuItemImageByPlist("shop.item.bkg");	
	pItem->setEnabled(false);
	//CCMenuItemImage* pItem= SystemData::getMenuItemImageByPlist("shop.item.bkg");	
	m_pSlideItems->addElement(pItem);
	CCMenuEx* pMenu = CCMenuEx::create();
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);
	CCMenuItemImage* pIconBkg = SystemData::getMenuItemImageByPlist("shop.icon.bkg");	
	pIconBkg->setTag(i);
	pIconBkg->setTarget(this,menu_selector(ShopPanel::itemClicked)); 
	pMenu->addChild(pIconBkg);  
	pItem->addChild(pMenu);  


	CCMenuItemImage* pMenuItem=CCMenuItemImage::create();
	pMenuItem->setTag(10000+i);
	pMenuItem->setAnchorPoint(CCPointZero);
	pMenuItem->setTarget(this,menu_selector(ShopPanel::itemClicked));
	pMenuItem->setContentSize(CCSizeMake(pItem->getContentSize().width-pIconBkg->getContentSize().width,pItem->getContentSize().height));
	pMenuItem->setPosition(ccp(pIconBkg->getContentSize().width,0));
	pMenu->addChild(pMenuItem);
	pItem->setTag(pMenuItem->getTag());

	//add the labels: name, price
	std::string name;
	ShopData& item = GameData::s_user->mShopItems[i];
	LuaData::getProp(LuaData::ITEM,item.itemid,"name",name);

	std::string strLabel[5] = {"itemname","item_original_price","item_current_price","original_price","current_price"};
	std::string strContent[5] = {name.c_str(),"","",SystemData::intToString(item.oldprice),SystemData::intToString(item.newprice)};
	for(int p=0; p<5; p++)
	{
		std::string key = "shop.lbl."+strLabel[p];
		CCLabelTTF* pLabel=SystemData::getLabelTTF(key);
		pLabel->setFontName("Arial");
		pLabel->setFontSize(16);
		pItem->addChild(pLabel);
		if(p==0||p==3||p==4)
		{
			pLabel->setString(strContent[p].c_str());
			if (strContent[p].size()>=27)
			{
				pLabel->setFontSize(14);
			}
		}
	}
	
	if (item.itemid == m_ItemID)
	{
		EffectSprite* p=EffectSprite::create(Effect::effect_stoneputon,1);
		p->setPosition(ccp(pIconBkg->getContentSize().width/2,pIconBkg->getContentSize().height/2));
		pIconBkg->addChild(p);
	}

	//add the money icon
	std::string moneyIcon = "vcoin";
	if(m_nCurType == TAG_SHOP_COUPON)
	{
		moneyIcon = "coupon";
	}
	else if(m_nCurType == TAG_SHOP_INTERGRATION)
	{ 
		moneyIcon = "integration"; 
	}
	CCSprite* pMoneyIconOri = SystemData::getSpriteByPlist("shop.sprite."+moneyIcon);
	pMoneyIconOri->setPosition(SystemData::getLayoutPoint("shop.point.itemvcoinori"));
	pMoneyIconOri->setScale(0.8);
	pItem->addChild(pMoneyIconOri);  
	CCSprite* pMoneyIconCur = SystemData::getSpriteByPlist("shop.sprite."+moneyIcon);
	pMoneyIconCur->setPosition(SystemData::getLayoutPoint("shop.point.itemvcoincur"));
	pMoneyIconCur->setScale(0.8);
	pItem->addChild(pMoneyIconCur);

	//add the item icon
	CCSprite* pIcon = LayoutData::getItemIcon(item.itemid);
	if(pIcon)
	{
		pIcon->setPosition(SystemData::getLayoutPoint("shop.point.itemicon"));
		pIconBkg->addChild(pIcon);

		// unfinished
		if (false)
		{
			CCSprite *anim = EffectSprite::create(Effect::effect_xiyou_libao);
			anim->setPosition(ccp(pIcon->getContentSize().width/2, pIcon->getContentSize().height/2));
			pIcon->addChild(anim);
		}
	}

	if (item.itemid==m_ItemID&&m_Tab==m_nCurType)
	{
		m_Page=m_pSlideItems->getTotalPage()-1;
		m_SelectItem=pItem;
	}
}
void ShopPanel::addListFinish()
{
	m_isLoading=false;
	if (m_ItemID<=0)
	{
		m_Page=0;
	}
	if (m_Page<=0)
	{
		m_Page=0;
	}
	m_pSlideItems->setCurPage(m_Page);

	if (m_ItemID>0&&m_SelectItem)
	{
		itemClicked(m_SelectItem);
	}

	m_SelectItem=NULL;
	m_ItemID=0;
	m_Page=0;
}

void ShopPanel::initItemPages( int type )
{
	m_pSlideItems->clear();
	
	int itemNum = GameData::s_user->mShopItems.size();
	
	if (m_updater)
	{
		m_updater->removeFromParentAndCleanup(true);
		m_updater = NULL;
	}
	m_updater = CPUpdater::create(this, cpupdater_selector(ShopPanel::addListItem));
	m_updater->setUpdateTimes(itemNum);
	m_updater->setFinishHandler(this, callfunc_selector(ShopPanel::addListFinish));
	addChild(m_updater);
	m_updater->start();
}

void ShopPanel::rechargeCallback( CCObject* pSender )
{
	CPEventHelper::openPanel("RechargePanel");
}

cocos2d::CCSize ShopPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	static CCSize cellSize = SystemData::getLayoutSize("shop.top.view.cell");   
	return cellSize;
}

cocos2d::extension::CCTableViewCell* ShopPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell* cell = NULL;
	if (!cell)
	{
		cell = new CCTableViewCell;
		cell->autorelease();

		CCMenuItemImage* pItem = SystemData::getMenuItemImageByPlist("shop.top.btn");
		pItem->setTag(-10);  
		cell->addChild(pItem);
		pItem->setScaleX(0.65f);

		if(m_nCurIndex == idx)
		{
			pItem->selected();
			m_pCurCell = cell;
		}
		if (m_pCurCell == NULL && idx == 0)
		{
			m_pCurCell = cell;
		}

		static std::string keyList[TAG_SHOP_MAX]={"bestseller","equip","skill","medicine","commonly.used","rare.treasures","personalized.dress","coupon","integration"};
		std::string key = "shop.catalog."+keyList[idx];
		CCLabelTTF* pLabel = CCLabelTTF::create(SystemData::getLayoutString(key).c_str(),"Consolas",18);
		pLabel->setPosition(ccp((cellSizeForTable(table).width-7)/2,cellSizeForTable(table).height/3));
		cell->addChild(pLabel);
	}
	return cell;
}

unsigned int ShopPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 9;
}

void ShopPanel::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{
	if(cell == m_pCurCell)
	{
		return;
	}
	if(m_pCurCell)
	{
		CCMenuItemImage* pNormal = (CCMenuItemImage*)(m_pCurCell->getChildByTag(-10));
		pNormal->unselected();
	}
	m_pCurCell = cell;
	if(m_pCurCell)
	{
		CCMenuItemImage* pNormal = (CCMenuItemImage*)(m_pCurCell->getChildByTag(-10));
		pNormal->selected();
	}
	if(m_pCurCell)
	{
		m_nCurType = m_pCurCell->getIdx()+1;
		openShop(m_nCurType);
	}
	m_nCurIndex = cell->getIdx();
}

void ShopPanel::itemClicked( CCObject* pSender )
{
	//show tips for the clicked item
	CCNode* pNode = (CCNode*)pSender;
	if(pNode)
	{
		int tag = pNode->getTag();
		bool isicon = false;
		if(tag>=10000)
		{
			tag -= 10000;
			isicon = true;
		}
		//build the item data
		ShopData& item = GameData::s_user->mShopItems[tag];
		UserItem* pi=CommonFunction::createNewItem(item.itemid);
		m_clickedItem=*pi;
		m_clickedItem.sid = item.itemid;
		m_curPrice = item.newprice;
		LuaData::getProp(LuaData::ITEM,item.itemid,"name",m_clickedItem.name);
		LuaData::getProp(LuaData::ITEM,item.itemid,"icon",m_clickedItem.icon);
		LuaData::getProp(LuaData::ITEM,item.itemid,"desc",m_clickedItem.desc);

		if(isicon)
		{
			if (!m_pSlideItems->isScrolling())
			{
				EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SHOW_KEYBOARD);
			}
		}
		else
		{
			//show the item tips
			if(getChildByTag(TAG_KEYBOARD))
			{
				removeChildByTag(TAG_KEYBOARD);
			}
			const int row = 3;
			const int col = 3;
			int c = tag%(row*col);
			if (tag<=0)c=0;
			int b=c%col;
			if(c<=0)b=0;
			int a=c/row;
			a=col-(a+1);
			CCPoint tipsPos = ccp(196+b*225,-70+a*105);

			if(tipsPos.x+245>SystemData::size_x)
			{
				tipsPos.x -= 245+pNode->getContentSize().width;
			}
			if(tipsPos.y<0)
			{
				tipsPos.y = 0;
			} 

			if (pi->category==ItemCate_Equip || pi->type == ItemType_Pet)
			{
				tipsPos.y=0;
			}
			if (tipsPos.y>200)
			{
				tipsPos.y=200;
			}

			Game::getGameUI()->showTipsPanel(&m_clickedItem,TAG_Tips_GM,tipsPos);
		}
	}
}

void ShopPanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_GET_SHOP_DATA)
	{
		initItemPages(m_nCurType);
	}
	else if(channel == EventProtocol::EVENT_SHOW_KEYBOARD)
	{
		if(getChildByTag(TAG_KEYBOARD))
		{
			removeChildByTag(TAG_KEYBOARD);
		}
		int totalCount = HeroData::getProp(Entity::attr_gold);
		if(m_nCurType == TAG_SHOP_COUPON)
		{
			totalCount = HeroData::getProp(Entity::attr_diamond);
		}
		else if(m_nCurType == TAG_SHOP_INTERGRATION)
		{
			totalCount = HeroData::getProp(Entity::attr_intergration);
		}
		totalCount /= m_curPrice;
		if (totalCount<=0)
		{
			if(m_nCurType == TAG_SHOP_COUPON)
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::Coupon_NotEnough);			
			}
			else if(m_nCurType == TAG_SHOP_INTERGRATION)
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::Score_NotEnough);			
			}
			else 
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::Gold_NotEnough);
			}
			
		}
		else
		{
			NumberKeyBoard* pNumberBoard = NumberKeyBoard::create(1,m_nCurType,m_curPrice,m_clickedItem.sid);
			pNumberBoard->setPosition(SystemData::getLayoutPoint("shop.point.keyboard"));
			pNumberBoard->setTag(TAG_KEYBOARD);
			addChild(pNumberBoard);
		}
	}
	else if(channel == EventProtocol::EVENT_SHOP_BUY_ITEM)
	{
		//send the buy message
		if(m_nFinalBuyCount>0)
		{
			MsgBuyItemInShopRequest* msg = new MsgBuyItemInShopRequest;
			msg->shopid = m_nCurType;
			msg->itemcnt = m_nFinalBuyCount;
			msg->itemid = m_clickedItem.sid;
			HandleMessage::sendMessage(msg);
		}
	}
	else if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{ 
		m_pGold->setString((SystemData::getLayoutString("shop.lbl.yuanbao")+SystemData::intToString(HeroData::getProp(Entity::attr_gold))).c_str());
		m_pCoupon->setString((SystemData::getLayoutString("shop.lbl.coupon")+SystemData::intToString(HeroData::getProp(Entity::attr_diamond))).c_str());
		m_pIntegration->setString((SystemData::getLayoutString("shop.lbl.integration")+SystemData::intToString(HeroData::getProp(Entity::attr_intergration))).c_str());
	}
	else if(channel == TAG_MONEY_NOT_ENOUGH)
	{
		rechargeCallback(NULL);
	}
}

void ShopPanel::openShop( int type )
{
	//send message to server
	MsgOpenShopRequest* msg = new MsgOpenShopRequest;
	msg->shopId = type;
	HandleMessage::sendMessage(msg);
}

void ShopPanel::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
	CCLog("_______%s",__FUNCTION__);
}

void ShopPanel::consumeAlertEnable(bool enable)
{
	if (!m_pTick||!pAlertBg)
		return;
	m_pTick->setVisible(enable);
	pAlertBg->setVisible(enable);
	m_consumeAlertEnable = enable;
}
void ShopPanel::tickCallBack(CCObject* pSender)
{
	consumeAlertEnable(!m_consumeAlertEnable);
}

void ShopPanel::onEnter()
{

	BasePanel::onEnter();
	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}

void ShopPanel::pageChangeCallBack(CCObject* pSender)
{
	if (!m_pSlideItems)
		return;
	if (!m_isLoading)
	{
		//setShopPage(m_pSlideItems->getCurPage());
	}
}

void ShopPanel::setSelectTab(int pTab)
{
	if (!m_pTopMenuView)
		return;
	cocos2d::extension::CCTableViewCell* cell = m_pTopMenuView->cellAtIndex(pTab-1);
	if(m_pCurCell)
	{
		CCMenuItemImage* pNormal = (CCMenuItemImage*)(m_pCurCell->getChildByTag(-10));
		pNormal->unselected();
	}
	m_pCurCell = cell;
	if(m_pCurCell)
	{
		CCMenuItemImage* pNormal = (CCMenuItemImage*)(m_pCurCell->getChildByTag(-10));
		pNormal->selected();
	}
	if(m_pCurCell)
	{
		m_nCurType = m_pCurCell->getIdx()+1;
		openShop(m_nCurType);
	}
	m_nCurIndex = cell->getIdx();
}