#include "NpcShopPanel.h"

#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"

#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"

#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/repodata/RepoData.h"
#include "userdata/luadata/LuaData.h"

#include "event/EventProtocol.h"

#include "ext/CCMenuEx.h"
#include "ext/RadioGroup.h"
#include "ext/RadioGroupEx.h"
#include "ext/CCMenuEx.h"

#include "network/HandleMessage.h"

#include "NpcShopComp.h"
#include "userdata/ItemOperationDef.h"
#include "ext/GeneralMenu.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "EntityDefinition.h"
#include "userdata/HeroData.h"
#include "event/CPEventHelper.h"



////////NpcShopPanel////////////////////////////////////////////////
NpcShopPanel::NpcShopPanel()
	: m_nCurType(TAG_NPCSHOP_MEDICINE)
	, m_nFinalBuyCount(0)
	, m_pMenu(NULL)
	, mItemList(NULL)
	, m_bIsRepo(false)
	, m_updater(NULL)
	, m_pCurSelectItem(NULL)
	, m_repoNone(NULL)
	, m_iRefreshCnt(0)
{
}

NpcShopPanel::~NpcShopPanel()
{
	
}

NpcShopPanel* NpcShopPanel::create( int shopid )
{
	NpcShopPanel* pNpcShopPanel = new NpcShopPanel;
	if(pNpcShopPanel && pNpcShopPanel->init(shopid))
	{
		pNpcShopPanel->autorelease();
		return pNpcShopPanel;
	}
	CC_SAFE_DELETE(pNpcShopPanel);
	pNpcShopPanel = NULL;
	return NULL;
}

bool NpcShopPanel::init(int shopid)
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_nCurType = shopid;
	m_iCurType = shopid;
	initUI();
	openShopRequest();

	return true;
}
std::string NpcShopPanel::getShopCategory()
{
	std::string cateStr="";
	switch (m_nCurType)
	{
	case TAG_NPCSHOP_MEDICINE:
		{
			cateStr = "medicine";
			break;
		}
	case TAG_NPSHOP_GROCERY:
		{
			cateStr = "grocery";
			break;
		}
	case TAG_NPCSHOP_BLACKSMITH:
		{
			cateStr = "weapon";
			break;
		}
	case TAG_NPCSHOP_JEWELERY:
		{
			cateStr = "decorator";
			break;
		}
	case TAG_NPCSHOP_ARMOR:
		{
			cateStr = "armor";
			break;
		}
	case TAG_NPCSHOP_BOOK:
		{
			cateStr = "book";
			break;
		}
	case TAG_NPCSHOP_CARRY:
		{
			cateStr = "carry";
			break;
		}
	default:
		break;
	}
	return cateStr;
}
void NpcShopPanel::initUI()
{
	if (m_nCurType!=TAG_NPCSHOP_CARRY)
	{
		m_nWidth = SystemData::getLayoutSize("npcshop.view").width+5;
		m_nHeight = 80;
		addCover(CCPointZero,kCCMenuHandlerPriority-1);
	}


	m_nWidth = 450;
	m_nHeight = 50;
	addCover(ccp(0,SystemData::getLayoutPoint("npcshop.top.btn").y),kCCMenuHandlerPriority-1);

	m_pMenu = CCMenu::create();
	m_pMenu->setPosition(CCPointZero);
	m_pMenu->setTouchPriority(kCCMenuHandlerPriority-1);
	addChild(m_pMenu);
	//add the top buttons
	CCMenuItemImage* pFirstBtn = SystemData::getMenuItemImageByPlist("npcshop.top.btn"); 
	pFirstBtn->setTag(m_nCurType);
	pFirstBtn->setPositionY(pFirstBtn->getPositionY()-3);
	pFirstBtn->setTarget(this,menu_selector(NpcShopPanel::selectTabCallback));
	m_pMenu->addChild(pFirstBtn);

	CCLabelTTF* pFirstLabel = SystemData::getLabelTTF("npcshop.lbl.medicine");
	pFirstLabel->setPosition(ccp(pFirstBtn->getContentSize().width/2,pFirstBtn->getContentSize().height/3));
	pFirstBtn->addChild(pFirstLabel);
	pFirstLabel->setString(SystemData::getLayoutString("npcshop.lbl."+getShopCategory()).c_str());

	if (m_nCurType!=TAG_NPCSHOP_CARRY)
	{
		CCMenuItemImage* pSecondBtn = SystemData::getMenuItemImageByPlist("npcshop.top.btn2");
		pSecondBtn->setTag(TAG_NPCSHOP_RECYCLE);
		pSecondBtn->setPositionY(pSecondBtn->getPositionY()-3);
		pSecondBtn->setTarget(this,menu_selector(NpcShopPanel::selectTabCallback));
		m_pMenu->addChild(pSecondBtn);

		CCLabelTTF* pSecondLabel = SystemData::getLabelTTF("npcshop.lbl.repo");
		pSecondLabel->setPosition(ccp(pSecondBtn->getContentSize().width/2,pSecondBtn->getContentSize().height/3));
		pSecondBtn->addChild(pSecondLabel);
	}

	

	//m_pMenu->setInitItem(m_nCurType);

	//add the border on the outside
	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("npcshop.border");  
	addChild(pBorder);  

	// item list
	const int cntPerLine = 2;
	CCSize listSize = SystemData::getLayoutSize("npcshop.view");
	CCPoint listPt = SystemData::getLayoutPoint("npcshop.view");
	if (m_nCurType==TAG_NPCSHOP_CARRY)
	{
		listSize = CCSizeMake(listSize.width,listSize.height+75);
		listPt=ccp(listPt.x,listPt.y-75);
	}
	
	mItemList = CPItemComponents::create(listSize,new CPLayoutGrid(cntPerLine));
	mItemList->setClickSensitive(true); 
	mItemList->setContentSize(listSize);
	mItemList->setAnchorPoint(CCPointZero);
	mItemList->setPosition(listPt);
	addChild(mItemList);

	if (m_nCurType!=TAG_NPCSHOP_CARRY)
	{
		CCSprite* pline=SystemData::getSpriteByPlist("shop.cutlinelarge"); 
		pline->setScaleX(0.9f);
		pline->setPosition(ccp(240,85));
		addChild(pline);
	}
	const CCSize &barSize = CCSizeMake(6, listSize.height);
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mItemList->setScrollbar(scrollBar);

	m_repoNone = SystemData::getLabelTTF("npcshop.lbl.repo.none");
	addChild(m_repoNone);
	m_repoNone->setVisible(false);

}

void NpcShopPanel::addListItem(int i )
{
	mItemList->addItem(getItem(i));
}

void NpcShopPanel::addListFinish()
{
	//mActivityList->setCurrentIndex(mCurrentIndex);
}

void NpcShopPanel::refreshList()
{
	if (m_bIsRepo && m_iCurType==TAG_NPCSHOP_CARRY)
	{
		m_bIsRepo=false;
		//return;
	}
	mItemList->removeAllItems();

	int num = 0;
	if(m_bIsRepo)
	{
		num = RepoData::mRepoItemList.size();
		if (num<=0)
		{
			m_repoNone->setVisible(true); 
		}
		else
		{
			m_repoNone->setVisible(false);
		}
	}
	else
	{
		num = GameData::s_user->mShopItems.size();
		m_repoNone->setVisible(false);
	}

	if (m_updater)
	{
		m_updater->removeFromParentAndCleanup(true);
		m_updater = NULL;
	}

	if (m_iRefreshCnt>0)
	{
		for (int i = 0;i<num;i++)
		{
			mItemList->addItem(getItem(i));
		}
	}
	else
	{
		m_updater = CPUpdater::create(this, cpupdater_selector(NpcShopPanel::addListItem));
		m_updater->setUpdateTimes(num);
		m_updater->setFinishHandler(this, callfunc_selector(NpcShopPanel::addListFinish));
		addChild(m_updater);
		m_updater->start();
	}

	m_iRefreshCnt++;
}

void NpcShopPanel::selectTabCallback( CCObject* pSender )
{
	CCNode* pNode = (CCNode*)pSender;
	if(pNode)
	{
		int tag = pNode->getTag();
		if(m_nCurType == tag)
		{
			return;
		}
		m_nCurType = tag;
		if(tag == TAG_NPCSHOP_RECYCLE)
		{
			m_bIsRepo = true;
			NpcShopComp::_s_state = ItemOperationDefine::item_op_sell;
			if (m_pCurSelectItem)
			{
				m_pCurSelectItem->unselected();
			}
			m_pCurSelectItem=NULL;
		}
		else
		{
			m_bIsRepo = false;
			NpcShopComp::_s_state = ItemOperationDefine::item_op_buy;
			if (m_pCurSelectItem)
			{
				m_pCurSelectItem->unselected();
			}
			m_pCurSelectItem=NULL;
		}
		initTopTab();
		refreshList();
	}
}

void NpcShopPanel::itemClicked( CCObject* pSender )
{
	if (m_iCurType==TAG_NPCSHOP_CARRY)
	{
		m_bIsRepo=false;
	}
	//show tips for the clicked item
	CCNode* pNode = (CCNode*)pSender;
	if(pNode)
	{
		if(pNode->getPositionX()>400)
			return;

		
		if (m_pCurSelectItem)
		{
			m_pCurSelectItem->unselected();
		}
		m_pCurSelectItem=NULL;
		CCMenuItemImage* pItem=(CCMenuItemImage*)(pNode->getParent()->getParent());
		m_pCurSelectItem=pItem;
		m_pCurSelectItem->selected();

		int tag = pNode->getTag();
		//build the item data
		if(!m_bIsRepo)
		{
			ShopData& item = GameData::s_user->mShopItems[tag];
			m_clickedItem=(*CommonFunction::createNewItem(item.itemid));
			m_clickedItem.sid = item.itemid;
			m_curPrice = item.newprice;
			LuaData::getProp(LuaData::ITEM,item.itemid,"name",m_clickedItem.name);
			LuaData::getProp(LuaData::ITEM,item.itemid,"icon",m_clickedItem.icon);
			LuaData::getProp(LuaData::ITEM,item.itemid,"desc",m_clickedItem.desc);
			m_clickedItem.iid=0;
		}
		else
		{
			ShopBuyBackData& item = RepoData::mRepoItemList[tag];
			m_clickedItem=(*CommonFunction::createNewItem(item.itemsid));
			m_clickedItem.sid = item.itemsid;
			m_clickedItem.iid = item.itemiid;
			m_curPrice = item.price;
			m_clickedItem.count = item.count;
			LuaData::getProp(LuaData::ITEM,item.itemsid,"name",m_clickedItem.name);
			LuaData::getProp(LuaData::ITEM,item.itemsid,"icon",m_clickedItem.icon);
			LuaData::getProp(LuaData::ITEM,item.itemsid,"desc",m_clickedItem.desc);
		}
		//show the item tips
		CCPoint tipsPos = pNode->convertToWorldSpace(ccp(pNode->getContentSize().width,pNode->getContentSize().height-258));
		if(tipsPos.x+245>SystemData::size_x)
		{
			tipsPos.x -= 245+pNode->getContentSize().width;
		}
		if(tipsPos.y<0)
		{
			tipsPos.y = 0;
		}
		if (m_clickedItem.category==ItemCate_Equip)
		{
			tipsPos.y = 10;
		}
		if(!m_bIsRepo)
		{
			Game::getGameUI()->showTipsPanel(&m_clickedItem,TAG_Tips_GM,tipsPos);
		}
		else
		{
			Game::getGameUI()->showTipsPanel(&m_clickedItem,TAG_Tips_HG,tipsPos);
		}
	}
}

void NpcShopPanel::rechargeCallback( CCObject* pSender )
{
	///TODO: implement the recharge facility
}

void NpcShopPanel::openShopRequest()
{
	//send message to server
	MsgOpenShopRequest* msg = new MsgOpenShopRequest;
	msg->shopId = m_nCurType;
	HandleMessage::sendMessage(msg);
}

CCMenuItemImage* NpcShopPanel::getItem( int id )
{
	CCMenuItemImage* pItem= SystemData::getMenuItemImageByPlist("npcshop.item.bkg");	
	pItem->setEnabled(false);
	CCMenuEx* pMenu=CCMenuEx::create();
	CCMenuItemImage* pIconBkg = SystemData::getMenuItemImageByPlist("npcshop.icon.bkg");	
	pIconBkg->setTarget(this,menu_selector(NpcShopPanel::itemClicked));
	pMenu->setPosition(pIconBkg->getPosition());
	pIconBkg->setPosition(CCPointZero);
	pIconBkg->setTag(id);
	pMenu->addChild(pIconBkg);
	pItem->addChild(pMenu);

	//add the labels: name, price
	CCMenuItemImage* pMenuItem=CCMenuItemImage::create();
	pMenuItem->setTag(id);
	pMenuItem->setTarget(this,menu_selector(NpcShopPanel::buyClick));
	//pMenuItem->setTarget(this,menu_selector(NpcShopPanel::itemClicked));
	pMenuItem->setAnchorPoint(CCPointZero);
	pMenuItem->setContentSize(CCSizeMake(pItem->getContentSize().width-pIconBkg->getContentSize().width,pItem->getContentSize().height));
	pMenuItem->setPosition(ccp(pIconBkg->getContentSize().width,0));
	pMenu->addChild(pMenuItem);
	std::string name;
	int sid,price,cnt,isbind;
	bool cntFlag = false;
	if(!m_bIsRepo)
	{
		ShopData& item = GameData::s_user->mShopItems[id];
		sid = item.itemid;
		price = item.newprice;
	}
	else
	{
		ShopBuyBackData& item = RepoData::mRepoItemList[id];
		sid = item.itemsid;
		price = item.price;
		cnt = item.count;
		isbind = item.isbind;
		cntFlag = true;
	}
	LuaData::getProp(LuaData::ITEM,sid,"name",name);
	std::string strLabel[2] = {"itemname","current_price"};
	std::string strContent[2] = {name.c_str(),SystemData::intToString(price)};
	for(int p=0; p<2; p++)
	{
		std::string key = "npcshop.lbl."+strLabel[p];
		CCLabelTTF* pLabel=SystemData::getLabelTTF(key);
		pLabel->setFontName("Consolas");
		pLabel->setFontSize(16);
		pItem->addChild(pLabel);
		pLabel->setString(strContent[p].c_str());
	}
	//add the item icon
	std::string icon;
	LuaData::getProp(LuaData::ITEM,sid,"icon",icon);
	UserItem* pUserItem = CommonFunction::createNewItem(sid);
	pUserItem->count = cnt;
	pUserItem->data[ItemEquip::Item_Bind] = isbind;
	CCMenuItemImage* pIcon = CommonFunction::getItemIcon(pUserItem,cntFlag);
	if(pIcon)
	{
		pIcon->setPosition(SystemData::getLayoutPoint("npcshop.point.itemicon"));
		pIconBkg->addChild(pIcon);
	}
	//add the gold icon
	CCSprite* pGold = SystemData::getSpriteByPlist("npcshop.sprite.gold");
	pItem->addChild(pGold);

	return pItem;
}

/**
 * NPC商店面板事件处理函数
 * 处理商店相关的事件消息，包括数据刷新、键盘显示、购买物品等
 * 
 * @param channel 事件频道/事件类型标识
 */
void NpcShopPanel::handleEvent(int channel)
{
	// 事件：获取商店数据
	if (channel == EventProtocol::EVENT_GET_SHOP_DATA)
	{
		// 如果当前状态是出售物品操作，并且当前标签不是携带物品标签
		if (NpcShopComp::_s_state == ItemOperationDefine::item_op_sell && m_iCurType != TAG_NPCSHOP_CARRY)
		{
			// 设置为回购状态
			m_bIsRepo = true;
			m_nCurType = TAG_NPCSHOP_RECYCLE;  // 切换到回收/回购标签
			
			// 取消当前选中物品
			if (m_pCurSelectItem)
			{
				m_pCurSelectItem->unselected();
			}
			m_pCurSelectItem = NULL;
		}
		else
		{
			// 正常购买状态
			m_bIsRepo = false;
			m_nCurType = m_iCurType;  // 使用当前标签
			
			// 取消当前选中物品
			if (m_pCurSelectItem)
			{
				m_pCurSelectItem->unselected();
			}
			m_pCurSelectItem = NULL;
		}
		
		// 初始化顶部标签
		initTopTab();
		// 刷新列表显示
		refreshList();
	}
	// 事件：获取回购数据
	else if (channel == EventProtocol::EVENT_GET_REPO_DATA)
	{
		// 处理逻辑与EVENT_GET_SHOP_DATA基本相同
		if (NpcShopComp::_s_state == ItemOperationDefine::item_op_sell && m_iCurType != TAG_NPCSHOP_CARRY)
		{
			m_bIsRepo = true;
			m_nCurType = TAG_NPCSHOP_RECYCLE;
			
			if (m_pCurSelectItem)
			{
				m_pCurSelectItem->unselected();
			}
			m_pCurSelectItem = NULL;
		}
		else
		{
			m_bIsRepo = false;
			m_nCurType = m_iCurType;
			
			if (m_pCurSelectItem)
			{
				m_pCurSelectItem->unselected();
			}
			m_pCurSelectItem = NULL;
		}
		
		// 初始化顶部标签
		initTopTab();
		// 如果是回购状态，才刷新列表
		if (m_bIsRepo)
		{
			refreshList();
		}
	}
	// 事件：显示购买键盘（输入购买数量）
	else if (channel == EventProtocol::EVENT_SHOW_KEYBOARD)
	{
		// 检查是否有足够的金币购买至少1个物品
		if (m_curPrice == 0)  // 如果单价为0，设为1防止除零错误
		{
			m_curPrice = 1;
		}
		
		// 检查金币是否足够购买1个物品
		if (m_curPrice > HeroData::getProp(Entity::attr_money))
		{
			// 金币不足，显示错误提示
			CPEventHelper::uiNotify("", "", Error::NotEnoughMoney);
			return;
		}
		
		// 计算最大可购买数量：总金币 / 单价
		int maxCount = HeroData::getProp(Entity::attr_money) / m_curPrice;
		
		// 如果是回购状态，有额外的限制
		if (m_bIsRepo)
		{
			// 在回购状态下，不能购买超过之前出售的数量
			if (maxCount > m_clickedItem.count)
			{
				maxCount = m_clickedItem.count;
			}
		}
		
		// 设置初始购买数量为1
		m_nFinalBuyCount = 1;
		
		// 显示数字键盘，用于输入购买数量
		Game::getGameUI()->showNumberKeyBoard(
			1,                    // 初始数量
			m_nCurType,           // 商店类型
			m_curPrice,           // 物品单价
			m_clickedItem.sid     // 物品ID
		);
	}
	// 事件：确认购买物品
	else if (channel == EventProtocol::EVENT_SHOP_BUY_ITEM)
	{
		// 发送购买请求消息
		if (!m_bIsRepo)  // 正常购买
		{
			MsgBuyItemInShopRequest* msg = new MsgBuyItemInShopRequest;
			msg->shopid = m_nCurType;           // 商店ID
			msg->itemcnt = m_nFinalBuyCount;    // 购买数量
			msg->itemid = m_clickedItem.sid;    // 物品ID
			HandleMessage::sendMessage(msg);
		}
		else  // 回购
		{
			MsgShopBackBuyItemRequest* msg = new MsgShopBackBuyItemRequest;
			msg->itemiid = m_clickedItem.iid;  // 回购使用实例ID
			HandleMessage::sendMessage(msg);
		}
	}
}

/**
 * NPC商店面板购买按钮点击事件处理
 * 处理玩家点击购买按钮的逻辑，包括物品选择、信息获取、价格验证和购买触发
 * 
 * @param pSender 被点击的按钮对象
 */
void NpcShopPanel::buyClick(CCObject* pSender)
{
	// 如果是携带物品标签，强制设置为非回购状态
	if (m_iCurType == TAG_NPCSHOP_CARRY)
	{
		m_bIsRepo = false;
	}
	
	// 将发送者转换为节点对象
	CCNode* pNode = (CCNode*)pSender;
	
	if (pNode)
	{
		// 获取点击项的标签（索引）
		int tag = pNode->getTag();
		
		// 非回购状态下的物品选择处理
		if (!m_bIsRepo)
		{
			// 取消之前选中的物品
			if (m_pCurSelectItem)
			{
				m_pCurSelectItem->unselected();
			}
			
			// 获取并选中当前点击的物品按钮
			CCMenuItemImage* pItem = (CCMenuItemImage*)(pNode->getParent()->getParent());
			pItem->selected();
			m_pCurSelectItem = pItem;  // 更新当前选中物品
		}
		
		// 根据是否为回购状态，从不同数据源获取物品信息
		if (!m_bIsRepo)  // 正常购买
		{
			// 从商店数据中获取物品信息
			ShopData& item = GameData::s_user->mShopItems[tag];
			m_clickedItem.sid = item.itemid;    // 设置物品ID
			m_curPrice = item.newprice;         // 设置物品价格
			
			// 从Lua配置表中获取物品的详细信息
			LuaData::getProp(LuaData::ITEM, item.itemid, "name", m_clickedItem.name);  // 物品名称
			LuaData::getProp(LuaData::ITEM, item.itemid, "icon", m_clickedItem.icon);  // 物品图标
			LuaData::getProp(LuaData::ITEM, item.itemid, "desc", m_clickedItem.desc);  // 物品描述
			
			m_clickedItem.iid = 0;  // 实例ID，正常购买时为0
		}
		else  // 回购状态
		{
			// 从回购数据中获取物品信息
			ShopBuyBackData& item = RepoData::mRepoItemList[tag];
			m_clickedItem.sid = item.itemsid;  // 设置物品ID
			m_clickedItem.iid = item.itemiid;  // 设置物品实例ID（回购需要）
			m_curPrice = item.price;           // 设置回购价格
			m_clickedItem.count = item.count;  // 设置可回购数量
			
			// 从Lua配置表中获取物品的详细信息
			LuaData::getProp(LuaData::ITEM, item.itemsid, "name", m_clickedItem.name);
			LuaData::getProp(LuaData::ITEM, item.itemsid, "icon", m_clickedItem.icon);
			LuaData::getProp(LuaData::ITEM, item.itemsid, "desc", m_clickedItem.desc);
		}
		
		// 根据状态执行不同的后续操作
		if (!m_bIsRepo)  // 正常购买流程
		{
			// 检查玩家金币是否足够购买
			if (m_curPrice > HeroData::getProp(Entity::attr_money))
			{
				// 金币不足，显示错误提示
				CPEventHelper::uiNotify("", "", Error::NotEnoughMoney);
				return;
			}
			
			// 金币足够，触发显示键盘事件（用于输入购买数量）
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SHOW_KEYBOARD);
		}
		else  // 回购流程
		{
			// 直接触发购买事件（回购不需要输入数量，直接购买全部）
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SHOP_BUY_ITEM);
		}
	}
}

void NpcShopPanel::initTopTab()
{
	if (m_pMenu->getChildByTag(TAG_NPCSHOP_RECYCLE))
	{
		((CCMenuItemImage*)(m_pMenu->getChildByTag(TAG_NPCSHOP_RECYCLE)))->unselected();
	}
	if (m_pMenu->getChildByTag(m_iCurType))
	{
		((CCMenuItemImage*)(m_pMenu->getChildByTag(m_iCurType)))->unselected();
	}
	if(!m_bIsRepo)
	{
		if (m_pMenu->getChildByTag(m_iCurType))
		{
			((CCMenuItemImage*)(m_pMenu->getChildByTag(m_iCurType)))->selected();
		}
	}
	else
	{
		if (m_pMenu->getChildByTag(TAG_NPCSHOP_RECYCLE))
		{
			((CCMenuItemImage*)(m_pMenu->getChildByTag(TAG_NPCSHOP_RECYCLE)))->selected();
		}
	}
}
