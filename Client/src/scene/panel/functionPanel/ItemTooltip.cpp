#include "ItemTooltip.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/OtherRole.h"
#include "userdata/UserItemData.h"
#include "userdata/SystemData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/LayoutData.h"
#include "script/LuaWrapper.h"
#include "userdata/netdata/GameRole.h"
#include "ext/CCTabelViewEx.h"
#include "event/EventProtocol.h"
#include "MsgItem.h"
#include "network/HandleMessage.h"
#include "CommonPanel.h"
#include "SoulStonePanel.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "EntityDefinition.h"
#include "MsgTrade.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/FloatPanelType.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "ItemDefinition.h"
#include "scene/panel/shop/NpcShopComp.h"
#include "userdata/ItemOperationDef.h"
#include "userdata/HeroData.h"
#include "userdata/activitydata/SpiderData.h"
#include "module/UserDataModule.h"
#include "event/CPEventHelper.h"
#include "controls/CPNodeHelper.h"
#include "ext/CCActionDestroy.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "userdata/UserPetData.h"
#include "logic/ItemOperator.h"
#include "userdata/BoothData.h"
#include "TradeDefinition.h"
#include "userdata/ActivityData.h"
#include "utils/StringUtils.h"
USING_NS_CC;

ItemTooltip::ItemTooltip():
	mHeight(0),
	m_pBkg(NULL),
	m_iCurrentTipsType(0),
	m_bIscompare(false),
	m_iCurSkillID(0),
	m_isp1(0),
	m_iCombatNum(0),
	m_icntEx(0)
{
}


ItemTooltip::~ItemTooltip()
{
}

ItemTooltip* ItemTooltip::create()
{
	ItemTooltip* pPanel = new ItemTooltip();
	if(pPanel && pPanel->init())
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

bool ItemTooltip::init()
{
	if(!PartPanel::init())
	{
		return NULL;
	}
    return true;
}
std::string ItemCate[22]={
	"武器","头盔","项链","戒指","勋章","衣服","鞋子","腰带","手镯","宝石","翅膀","时装","幻武","法球","足迹","元神","法器","斗笠","肩铠","护手","法袍","护腿"
};

void ItemTooltip::setTooltipContent(UserItem* item,int type ,bool flag)
{
	m_iCurrentTipsType=ItemTips;  // 设置当前提示类型为物品提示
	userItem = item;  // 保存传入的用户物品对象
	m_iH=0;  // 初始化高度偏移量为0
	
	// 如果是TAG_Tips类型，设置高度偏移量为50
	if (type==TAG_Tips)
	{
		m_iH=50;
	}
	
	/*int  height=m_iH;
	if (!flag)
	{
		height=0;
	}*/  // 注释掉的代码：根据flag条件设置高度
	
	// 如果物品对象存在
	if(userItem)
	{
		// 根据物品分类初始化不同的提示内容
		
		// 如果是装备类物品
		if (GameData::s_user->getUserItemData()->getItemCate(userItem->sid)==ItemCate_Equip)
		{
			initEquipItem(type,flag);  // 初始化装备物品提示
		}
		// 如果是扩展类物品且类型为宠物
		else if (GameData::s_user->getUserItemData()->getItemCate(userItem->sid)==ItemCate_Extension && GameData::s_user->getUserItemData()->getItemType(userItem->sid)==ItemType_Pet)
		{
			initPetEggItem(type,flag);  // 初始化宠物蛋物品提示
		}
		// 其他普通物品
		else
		{
			initNormalItem(type,flag);  // 初始化普通物品提示			
		}	

// 调试模式下显示物品的sid和iid信息
#ifdef DEBUG
		std::string sidstr="sid="+SystemData::intToString(userItem->sid);
		CCLabelTTF* psid=CCLabelTTF::create(sidstr.c_str(),"",15);
		psid->setAnchorPoint(CCPointZero);
		psid->setPosition(ccp(SystemData::getLayoutPoint("Tips_label8_pos").x,SystemData::getLayoutPoint("Tips_label8_pos").y+10));
		addChild(psid);

		std::string iidstr="iid="+SystemData::intToString(userItem->iid);
		CCLabelTTF* piid=CCLabelTTF::create(iidstr.c_str(),"",15);
		piid->setAnchorPoint(CCPointZero);
		piid->setPosition(ccp(SystemData::getLayoutPoint("Tips_label9_pos").x+10,SystemData::getLayoutPoint("Tips_label9_pos").y+10));
		addChild(piid);
#endif // DEBUG
	}
}

void ItemTooltip::setToolTipPetBase( UserPet* pPet,int type /*=0*/,bool flag/*=true*/ )
{
	m_iCurrentTipsType=ItemTips; 
	m_iH=0;
	UserPet* m_pet = pPet;
	if (type==TAG_Tips)
	{
		m_iH=50;
	}
	/*int  height=m_iH;
	if (!flag)
	{
		height=0;
	}*/
	if(m_pet)
	{
		initPetHeadItem(m_pet);


#ifdef DEBUG
		std::string sidstr="sid="+SystemData::intToString(m_pet->sid);
		CCLabelTTF* psid=CCLabelTTF::create(sidstr.c_str(),"",15);
		psid->setAnchorPoint(CCPointZero);
		psid->setPosition(ccp(SystemData::getLayoutPoint("Tips_label8_pos").x,SystemData::getLayoutPoint("Tips_label8_pos").y+10-60));
		addChild(psid);

		std::string iidstr="iid="+SystemData::intToString(m_pet->iid);
		CCLabelTTF* piid=CCLabelTTF::create(iidstr.c_str(),"",15);
		piid->setAnchorPoint(CCPointZero);
		piid->setPosition(ccp(SystemData::getLayoutPoint("Tips_label9_pos").x+10,SystemData::getLayoutPoint("Tips_label9_pos").y+10-60));
		addChild(piid);
#endif // DEBUG
	}
}
void ItemTooltip::onEnter()
{
	PartPanel::onEnter();  
}

void ItemTooltip::onExit()
{
    PartPanel::onExit();
}

void ItemTooltip::setTargetAndSeletor(CCObject* target, SEL_MenuHandler selectorOk, SEL_MenuHandler selectorCancel)
{
    CCMenuItemImage* btnOk = CCMenuItemImage::create("btnOkDialog.png", "btnOkSelDialog.png", target,selectorOk);
    CCMenuItemImage* btnReject = CCMenuItemImage::create("btnCancelDialog.png", "btnCancelSelDialog.png", target, selectorCancel);
    btnReject->setPosition(ccp(200, 210));
    btnOk->setPosition(ccp(120, 210));
    m_pMenu = CCMenu::create(btnOk, btnReject, NULL);
    m_pMenu->setPosition(CCPointZero);
    
    addChild(m_pMenu, 1);    
}

void ItemTooltip::setTargetAndSeletor(CCObject* target, SEL_MenuHandler selectorOk)
{
    CCMenuItemImage* btnOk = CCMenuItemImage::create("btnOkDialog.png", "btnOkSelDialog.png", target,selectorOk);
    btnOk->setPosition(ccp(160, 210));
    m_pMenu = CCMenu::create(btnOk, NULL);
    m_pMenu->setPosition(CCPointZero);
    
    addChild(m_pMenu, 1);    
}

void ItemTooltip::setContentText(const char* txContent)
{

}

CCLayer* ItemTooltip::getEquipInfo( UserItem* item ,int cntEx)
{
	int h=cntEx*20;
	CCLayer *player=CCLayer::create();
	CCTableViewEx* pTabelView = CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("Tips_tabelview_size_e").width,SystemData::getLayoutSize("Tips_tabelview_size_e").height-h),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(CCPointZero);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	player->addChild(pTabelView);	
	return player;
}

void ItemTooltip::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		MsgItemOperationRequestUse* req=NULL;
		MsgItemMovePosition* p=NULL;
		int tag=pNode->getTag();
		switch (tag)
		{
		case TAG_UP:
			CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_POSTMSG,(CCObject *)userItem);
			break;
		case TAG_DOWN:	
			CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_POSTMSG,(CCObject *)userItem);
			break;
		case TAG_REMOVE:
			//丢弃物品
			Game::getGameUI()->showFloatPanel(FloatPanelType::ITEM_DROP);
			if (Game::getGameUI()->m_panels[TAG_FLOAT_PANEL])
			{
				((FloatPanel*)(Game::getGameUI()->m_panels[TAG_FLOAT_PANEL]))->setHandler(this,floatpanel_selector(ItemTooltip::postRemoveItem));
				this->setVisible(false);
				return;
			}
			break;
		case TAG_CANCEL:
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_CANCEL);
			break;
		case TAG_USE:
			if (CommonFunction::checkCanBatchedUsing(userItem->sid))
			{
				int cnt = GameData::s_user->getUserItemData()->getItemByIid(userItem->iid)->count;
				if (cnt > 1)
				{
					//弹出数字键盘
					openKeyBorad(cnt,userItem->iid);
					return;
				}
				else
				{
					CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_POSTMSG,(CCObject *)userItem);
					return;
				}
			}
			CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_POSTMSG,(CCObject *)userItem);
			break;
		case TAG_BUY:
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SHOW_KEYBOARD);
			break;
		case TAG_BUYBACK:
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SHOP_BUY_ITEM);
			break;
		case TAG_BOOTHUP:
			if(userItem->data[ItemEquip::Item_Bind]==ItemEquip::Item_No_Bind)
			{
				CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_ADDITEMMARKET,(CCObject *)userItem);
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::Item_CanNotBooth);
			}
			break;
		case TAG_BOOTHDOWN:
			postItemMoveMsg(ItemPos::Player_Bag_Start);
			break;
		case TAG_SAVE_PETBAG:
			postItemMoveMsg(ItemPos::Pet_Bag_Start);
			break;
		case TAG_SAVE_NPCBAG:
			postItemMoveMsg(ItemPos::NPC_Bag_Start);
			break;
		case TAG_TAKE_PET:
			postItemMoveMsg(ItemPos::Pet_Bag_Start);
			break;
		case TAG_TAKE:
			postItemMoveMsg(ItemPos::Player_Bag_Start);
			break;
		case TAG_BOOTHBUY:
			postBoothBuy();
			break;
		case TAG_TRADE:
			if(userItem->data[ItemEquip::Item_Bind]==ItemEquip::Item_No_Bind)
			{
				if (!BoothData::getTradeLockState())
				{
					postTradeItem();
				}
				else
				{
					CPEventHelper::uiNotify("","",Error::TradeHasLock);
				}
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::Item_CanNotTrade);
			}
			break;
		case TAG_CANCELTRADE:
			postCancelTradeItem();
			break;
		case TAG_SELL:
			postSellItem();			
			break;
		case TAG_THROW:
			spiderdata::addItem(userItem);
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SPIDER_ITEM_CHANGE);
			break;
		case TAG_SET:
			setfastkey();
			break;
		case TAG_WATCHOUT:
			CPEventHelper::setEventIntData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2, userItem->iid);
			CPEventHelper::uiNotify("ItemTooltip|ShowItem", "", 0);
			break;
		case TAG_TOUBAO:
			postToubao();
			return;
		default:
			break;
		}
		closeCallBack(NULL);
	}
}

void ItemTooltip::openKeyBorad(int maxCnt,int iid)
{
	/*if (getChildByTag(Panel_Price))
	{
		getChildByTag(Panel_Price)->setVisible(false);
	}*/
	this->removeFromParent();
	int tag = SystemData::getLayoutValue("ItembatchedUsing.tag");
	Game::getGameUI()->showNumberKeyBoard(2,maxCnt,tag,iid,0);
//	m_icurrentPrice = 0;
}

void ItemTooltip::closeCallBack( CCObject* pSender )
{
	PartPanel::close();
}

cocos2d::CCSize ItemTooltip::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutValue("Tips_tabelview_size_e.w"),mHeight);
}

cocos2d::extension::CCTableViewCell* ItemTooltip::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		if (m_iCurrentTipsType==ItemTips)
		{
			if (GameData::s_user->getUserItemData()->getItemCate(userItem->sid)==ItemCate_Equip)
			{
				CCLayer *pLayer=getEquipInfoLayer(userItem);
				pLayer->setAnchorPoint(CCPointZero);
				pLayer->setPosition(ccp(0,mHeight));
				cell->addChild(pLayer);
			}
			else if (GameData::s_user->getUserItemData()->getItemCate(userItem->sid)==ItemCate_Extension && GameData::s_user->getUserItemData()->getItemType(userItem->sid)==ItemType_Pet)
			{
				CCLayer *pLayer=getPetEggInfoLayer(userItem);
				pLayer->setAnchorPoint(CCPointZero);
				pLayer->setPosition(ccp(0,mHeight));
				cell->addChild(pLayer);
			}
			else
			{
				CCLayer *pLayer=getOtherInfoLayer(userItem);
				pLayer->setAnchorPoint(CCPointZero);
				pLayer->setPosition(ccp(0,mHeight));
				cell->addChild(pLayer);
			}
		}
		else if (m_iCurrentTipsType==SkillTips)
		{
			CCLayer *pLayer=getSkillInfoLayer(m_iCurSkillID);
			pLayer->setAnchorPoint(CCPointZero);
			pLayer->setPosition(ccp(0,mHeight));
			cell->addChild(pLayer);
		}
	}
	return cell;
}

unsigned int ItemTooltip::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}


CCLayer* ItemTooltip::getOtherInfo( UserItem* item,int cntEx )
{
	int h=cntEx*20;
	CCLayer *player=CCLayer::create();
	CCTableViewEx* pTabelView = CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("Tips_tabelview_size").width,SystemData::getLayoutSize("Tips_tabelview_size").height-h),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(CCPointZero);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	player->addChild(pTabelView);	
	return player;
}


CCLayer* ItemTooltip::getEquipInfoLayer( UserItem* item )
{
	CCLayer* pLayer=CCLayer::create();

	//基础属性
	int size;
	LuaData::getProp_size(LuaData::ITEM,item->sid,"attr",size);
	CCPoint pos=ccp(25,-15);
	mHeight=15;
	CCLabelTTF* ptitle1=CCLabelTTF::create(SystemData::getLayoutString("ItemTips_JCSX").c_str(),"",15);
	ptitle1->setAnchorPoint(CCPointZero);
	ptitle1->setPosition(ccp(pos.x-15,pos.y));
	ptitle1->setColor(ccORANGE);
	pLayer->addChild(ptitle1);
	mHeight+=ptitle1->getContentSize().height;

	bool hasluck=false;
	for (int i=1;i<=size;i++) 
	{
		int min,max,type;
		LuaData::getProp_ItemInfo(LuaData::ITEM,item->sid,"attr",i,"max","min","type",type,min,max);   
		std::string strtype;
		std::string strEnhance;	
		std::string strQiling;
		ccColor3B color=ccc3(0,204,255);

		LuaData::getProp("attr_type_to_name",type,strtype);
		
		// 新增：为暴击和防爆设置特殊颜色
		if (type==Combat::prop_Critical_Damage_Bonus)       // 暴击
		{
			color = ccc3(220, 20, 60)  ;  // 猩红色
		}
		else if (type==Combat::prop_Anti_Critical)          // 防爆
		{
			color = ccc3(147, 112, 219)   ;          // 中紫罗兰250, 128, 114
		}
		else if (type==Combat::prop_Damage_Reflect_Rate)   //       反弹
		{
			color = ccc3(250, 128, 114)   ;          // 鲑鱼色
		}
		else if (type==Combat::prop_Life_Steal_Rate)   //       吸血
		{
			color = ccc3(255, 0, 0)   ;              //红色
		}
		else if (type==Combat::prop_Mana_Steal_Rate)   //       吸蓝
		{
			color = ccc3(135, 206, 235)   ;              //天空蓝
		}
		// 原有的攻击类属性颜色判断
		else if (type==Combat::prop_Attack_Speed)
		{
			color = ccc3(255, 105, 180);               //热粉
		}
		else if (type==Combat::prop_Move_Speed)
		{
			color = ccc3(130, 206, 209);               //蓝绿(青)
		}
		else if (type==Combat::prop_Physical_Attack || 
			type==Combat::prop_Magical_Attack || 
			type==Combat::prop_Taoism_Attack)
		{
			color=ccYELLOW;
		}
		
		
		// 修改后的强化显示逻辑 - 包含防御属性
		int enhanceLevel = item->data[ItemEquip::Item_EnhanceLevel];
		if (enhanceLevel != 0)
		{
			int value = 0;
			int defValue = 0;  // 防御强化值
			
			if (item->type == ItemType_Equip_Magic_Weapon)
			{
				// 魔器强化
				LuaData::getProp("gdOpenMagicWeapon", enhanceLevel-1, "qilingValue", value);
				
				// 判断当前属性类型
				if (type == Combat::prop_Physical_Attack || 
					type == Combat::prop_Magical_Attack || 
					type == Combat::prop_Taoism_Attack)
				{
					strQiling = "(" + SystemData::getLayoutString("ItemTips_QL") + "+" + SystemData::intToString(value) + ")";
				}
			}
			else
			{
				// 普通装备强化
				LuaData::getProp("gdEquipEnhance", enhanceLevel-1, "enhanceValue", value);
				
				// 判断当前属性类型
				if (type == Combat::prop_Physical_Attack || 
					type == Combat::prop_Magical_Attack || 
					type == Combat::prop_Taoism_Attack)
				{
					// 攻击属性强化
					strEnhance = "(" + SystemData::getLayoutString("ItemTips_QH") + "+" + SystemData::intToString(value) + ")";
				}
				else if (type == Combat::prop_Physical_Defense || 
						 type == Combat::prop_Magical_Defense)
				{
					// 防御属性强化（设为攻击的70%）
					defValue = value * 8 / 10;
					if (defValue > 0) {
						strEnhance = "(" + SystemData::getLayoutString("ItemTips_QH") + "+" + SystemData::intToString(defValue) + ")";
					}
				}
			}
		}
		
		if(userItem->data[ItemEquip::Item_RebornLvl]!=0)
		{
			if (type==Combat::prop_Physical_Attack||
				type==Combat::prop_Magical_Attack||
				type==Combat::prop_Taoism_Attack||
				type==Combat::prop_Physical_Defense||
				type==Combat::prop_Magical_Defense)
			{
				int minvalue = min/5*userItem->data[ItemEquip::Item_RebornLvl];
				if (minvalue<1)
				{
					minvalue = 1;
				}
				min+=minvalue;
				int maxvalue = max/5*userItem->data[ItemEquip::Item_RebornLvl];
				if (maxvalue<1)
				{
					maxvalue = 1;
				}
				max+=maxvalue;
			}
		}
		CCString* pStr=NULL;
		CCString* pStrQL=NULL;
		if (type==Combat::prop_Physical_Attack||
			type==Combat::prop_Magical_Attack||
			type==Combat::prop_Taoism_Attack||
			type==Combat::prop_Physical_Defense||
			type==Combat::prop_Magical_Defense)
		{
			pStr=CCString::createWithFormat("%s:%d-%d%s",strtype.c_str(),min,max,strEnhance.c_str());
			pStrQL = CCString::createWithFormat("%s:%d-%d%s",strtype.c_str(),min,max,strQiling.c_str());
		}
		else if (type==Combat::prop_Luck )
		{
			hasluck=true;
			//幸运值
			if (userItem->data[ItemEquip::Item_Lucky]!=0)
			{				
				min+=userItem->data[ItemEquip::Item_Lucky];
			}
			if (min<0)
			{
				//strtype="诅咒"; 
				LuaData::getProp("attr_type_to_name",Combat::prop_Curse,strtype);
				min = -min;
			}
			else
			{
				LuaData::getProp("attr_type_to_name",Combat::prop_Luck,strtype);
			}
			pStr=CCString::createWithFormat("%s:%d",strtype.c_str(),min);
		}
		else if (type==Combat::prop_Hit || 
			type==Combat::prop_Dodge ||
			type==Combat::prop_Palsy || 
			type==Combat::prop_HPMax || 
			type==Combat::prop_MPMax ||
			type==Combat::prop_Critical_Damage_Bonus ||//暴击
			type==Combat::prop_Anti_Critical||//防爆
			type==Combat::prop_Damage_Reflect_Rate||//反弹
			type==Combat::prop_Life_Steal_Rate||//吸血
			type==Combat::prop_Mana_Steal_Rate)//吸蓝
		{
			// 暴击和防爆显示为百分比（百分之一转百分比）
	if (type==Combat::prop_Critical_Damage_Bonus ||
		type==Combat::prop_Anti_Critical||
		type==Combat::prop_Damage_Reflect_Rate||
		type==Combat::prop_Life_Steal_Rate||//吸血
		type==Combat::prop_Mana_Steal_Rate)//吸蓝
	{
		float percentValue = (float)min / 100.0f;
		pStr=CCString::createWithFormat("%s:%.2f%%",strtype.c_str(),percentValue);
	}
	else
	{
		pStr=CCString::createWithFormat("%s:%d",strtype.c_str(),min);
	}
}
		else
		{
			if (type==Entity::attr_gene_loot_exp)
			{
				pStr=CCString::createWithFormat("%s:%d%%",strtype.c_str(),min);
			}
			else if (type==Combat::prop_Attack_Speed || type==Combat::prop_Move_Speed)
			{
				pStr=CCString::createWithFormat("%s:%.1f%%",strtype.c_str(),min/100.0f);
			}
			else
			{
				pStr=CCString::createWithFormat("%s:%d%%",strtype.c_str(),min/100);
			}
		}

		if ( strEnhance != "")
		{
			CCLabelTTF* pLabel=CCLabelTTF::create((pStr->getCString()),"",15);
			pLabel->setAnchorPoint(CCPointZero);
			pLabel->setPosition(ccp(pos.x,pos.y-20));
			pLabel->setColor(color);
			pos=pLabel->getPosition();
			pLayer->addChild(pLabel);
			mHeight+=pLabel->getContentSize().height;
		}
		else if (strQiling != "")
		{
			CCLabelTTF* pLabel2=CCLabelTTF::create((pStrQL->getCString()),"",15);
			pLabel2->setAnchorPoint(CCPointZero);
			pLabel2->setPosition(ccp(pos.x,pos.y-20));
			pLabel2->setColor(color);
			pos=pLabel2->getPosition();
			pLayer->addChild(pLabel2);
			mHeight+=pLabel2->getContentSize().height;
		}
		else
		{
			CCLabelTTF* pLabel=CCLabelTTF::create((pStr->getCString()),"",15);
			pLabel->setAnchorPoint(CCPointZero);
			pLabel->setPosition(ccp(pos.x,pos.y-20));
			pLabel->setColor(color);
			pos=pLabel->getPosition();
			pLayer->addChild(pLabel);
			mHeight+=pLabel->getContentSize().height;
		}
		
	} 
	//幸运值


	if (!hasluck)
	{
		if (userItem->data[ItemEquip::Item_Lucky]!=0)
		{
			std::string luckystr ;
			int value = userItem->data[ItemEquip::Item_Lucky];
			if (value<0)
			{
				LuaData::getProp("attr_type_to_name",Combat::prop_Curse,luckystr);
				value = -value;
			}
			else
			{
				LuaData::getProp("attr_type_to_name",Combat::prop_Luck,luckystr);
			}
			CCString* pStr=CCString::createWithFormat("%s:%d",luckystr.c_str(),value);
			CCLabelTTF* pLabel=CCLabelTTF::create((pStr->getCString()),"",15);
			pLabel->setAnchorPoint(CCPointZero);
			pLabel->setPosition(ccp(pos.x,pos.y-20));
			pLabel->setColor(ccYELLOW);
			pos=pLabel->getPosition();
			pLayer->addChild(pLabel);
			mHeight+=pLabel->getContentSize().height;
		}
	}

	//鉴定属性
int reqlvl, type;
LuaData::getProp(LuaData::ITEM, userItem->sid, "type", type);        // 获取物品类型
LuaData::getProp(LuaData::ITEM, userItem->sid, "req_level", reqlvl);  // 获取需求等级

// 检查是否为可分解的装备类型（排除特殊装备）
if (type != ItemType_Equip_Foot &&           // 排除足迹装备
    type != ItemType_Equip_Wings &&          // 排除翅膀装备
    type != ItemType_Equip_Magic_Weapon &&   // 排除魔器装备
    type != ItemType_Equip_Material &&       // 排除材料装备
    type != ItemType_Equip_Fashion &&        // 排除时装装备
    type != ItemType_Equip_Yuanshen &&       // 排除元神装备
    type != ItemType_Equip_Shenqi1 &&        // 排除神器1
    type != ItemType_Equip_Shenqi2 &&        // 排除神器2
    type != ItemType_Equip_Shenqi3 &&        // 排除神器3
    type != ItemType_Equip_Shenqi4 &&        // 排除神器4
    type != ItemType_Equip_Shenqi5 &&        // 排除神器5
    type != ItemType_Equip_Shenqi6)          // 排除神器6
{
    
}
	{
		if (reqlvl>=20)
		{
			ccColor3B color=ccc3(0,204,255);
			CCLabelTTF* ptitle2=CCLabelTTF::create(SystemData::getLayoutString("ItemTips_JDSX").c_str(),"",15);
			ptitle2->setAnchorPoint(CCPointZero);
			//ptitle2->setPosition(ccp(pos.x,pos.y-20));
			ptitle2->setPosition(ccp(pos.x-15,pos.y-20));
			ptitle2->setColor(ccORANGE);
			pos=ccp(pos.x,pos.y-20);
			pLayer->addChild(ptitle2);
			mHeight+=ptitle2->getContentSize().height;

			int combo=item->data[ItemEquip::Item_DataCombo];
			int number=0;
			for (int b=0;b<3;b++)
			{
				int c=(int)((int)combo >> (8*b) & 255);
				if(c!=0)
				{
					number++;
				}
			}	
			int n=0;
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
					combovalue=(float)item->data[ItemEquip::Item_DataX+n];
					combovalue=combovalue/100;
					pStr=CCString::createWithFormat("%s : + %.2f%% ",name.c_str(),combovalue);
				}
				else
				{
					pStr=CCString::createWithFormat("%s : + %d ",name.c_str(),item->data[ItemEquip::Item_DataX+n]);
				}
				CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"",15);		
				if (n==0)
				{
					pLabel->setPosition(ccp(pos.x,pos.y-number*20));
					pos=pLabel->getPosition();
				}
				else
				{
					pLabel->setPosition(ccp(pos.x,pos.y+20*n));
				}
				pLabel->setAnchorPoint(CCPointZero);
				pLabel->setColor(color);
				pLayer->addChild(pLabel);
				mHeight+=pLabel->getContentSize().height;
			}

			int m=0;
			for (n;n<3;n++)
			{
				CCLabelTTF* pLabel=CCLabelTTF::create(SystemData::getLayoutString("ItemTips_WJD").c_str(),"",15);
				pLabel->setAnchorPoint(CCPointZero);
				pLabel->setPosition(ccp(pos.x,pos.y-(m+1)*20));
				pLabel->setColor(ccWHITE);
				pos=pLabel->getPosition();
				pLayer->addChild(pLabel);
				mHeight+=pLabel->getContentSize().height;
			}
		}
	}
	// 附魔属性
	int fmAttrid=item->data[ItemEquip::Item_FuMoPropID];
	int fmAttrdata=item->data[ItemEquip::Item_FuMoPropValue];
	int fmAttrCount=item->data[ItemEquip::Item_FuMoEnhanceCount];
	if (fmAttrid!=0)
	{
		ccColor3B color=ccc3(180, 0, 255);
		CCLabelTTF* ptitle3=CCLabelTTF::create(SystemData::getLayoutString("ItemTips_FMSX").c_str(),"",15);
		ptitle3->setAnchorPoint(CCPointZero);
		//ptitle3->setPosition(ccp(pos.x,pos.y-20));
		ptitle3->setPosition(ccp(pos.x-15,pos.y-20));
		ptitle3->setColor(ccORANGE);
		pos=ccp(pos.x,pos.y-20);
		pLayer->addChild(ptitle3);
		std::string name;
		LuaData::getProp("fm_attr_type_to_name",fmAttrid,name);
		CCString* pStr=NULL;
		if (fmAttrid == 15 || fmAttrid == 16 || fmAttrid == 22)
		{
			float spdata=(float)fmAttrdata/100;
			pStr=CCString::createWithFormat("%s : + %.2f%% (%d/10)",name.c_str(), spdata, fmAttrCount);
		}
		else
		{
			pStr=CCString::createWithFormat("%s : + %d (%d/10)",name.c_str(), fmAttrdata, fmAttrCount);
		}
		CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"",15);
		pLabel->setPosition(ccp(pos.x,pos.y-20));
		pLabel->setColor(color);
		pos=pLabel->getPosition();
		pLabel->setAnchorPoint(CCPointZero);
		pLayer->addChild(pLabel);
		mHeight+=pLabel->getContentSize().height;
	}
	// 极品属性

	int spAttrid=item->data[ItemEquip::Item_SpecialIdx];
	int spAttrdata=item->data[ItemEquip::Item_SpecialData];
	if (spAttrid!=0)
	{
		ccColor3B color=ccc3(0,204,255);
		CCLabelTTF* ptitle3=CCLabelTTF::create(SystemData::getLayoutString("ItemTips_JPSX").c_str(),"",15);
		ptitle3->setAnchorPoint(CCPointZero);
		//ptitle3->setPosition(ccp(pos.x,pos.y-20));
		ptitle3->setPosition(ccp(pos.x-15,pos.y-20));
		ptitle3->setColor(ccORANGE);
		pos=ccp(pos.x,pos.y-20);
		pLayer->addChild(ptitle3);
		std::string name;
		LuaData::getProp("gdBestEvaluate",spAttrid,"name",name);
		int attrid = 0;
		LuaData::getProp("gdBestEvaluate",spAttrid,"attrtype",attrid);
		CCString* pStr=NULL;
		if (attrid==1 || attrid==2)
		{
			float spdata=(float)spAttrdata/100;
			pStr=CCString::createWithFormat("%s : + %.2f%% ",name.c_str(),spdata);
		}
		else
		{
			pStr=CCString::createWithFormat("%s : + %d ",name.c_str(),spAttrdata);
		}
		CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"",15);
		pLabel->setPosition(ccp(pos.x,pos.y-20));
		pLabel->setColor(color);
		pos=pLabel->getPosition();
		pLabel->setAnchorPoint(CCPointZero);
		pLayer->addChild(pLabel);
		mHeight+=pLabel->getContentSize().height;
	}
	

	//套装属性
	int suitid = 0;
	LuaData::getProp(LuaData::ITEM,userItem->sid,"suite_id",suitid);
	if (suitid!=0)
	{
		CCLabelTTF* ptitle4=CCLabelTTF::create(SystemData::getLayoutString("ItemTips_TZSX").c_str(),"",15);
		ptitle4->setAnchorPoint(CCPointZero);
		//ptitle5->setPosition(ccp(pos.x,pos.y-20));
		ptitle4->setPosition(ccp(pos.x-15,pos.y-20));
		ptitle4->setColor(ccORANGE);
		pos=ccp(pos.x,pos.y-20);
		pLayer->addChild(ptitle4);
		mHeight+=ptitle4->getContentSize().height;
		
		int suitcnt = 0;//GameData::s_user->getUserItemData()->getItemSuitCnt(suitid);
		if (userItem->pid==HeroData::getPID() || userItem->pid==0)
		{
			suitcnt = GameData::s_user->getUserItemData()->getItemSuitCnt(suitid);
		}
		else
		{
			suitcnt = GameData::s_user->m_pOtherRole->getSuitCnt(suitid);
		}
		int suitallcnt = 0;
		LuaData::getProp("gdSuitAttribute",suitid,"suitcnt",suitallcnt);
		CCString* pLabel = CCString::createWithFormat("(%d/%d)",suitcnt,suitallcnt);
		CCLabelTTF* pcnt = CCLabelTTF::create(pLabel->getCString(),"",15);
		pcnt->setAnchorPoint(CCPointZero);
		pcnt->setColor(ccORANGE);
		pcnt->setPosition(ccp(ptitle4->getContentSize().width+ptitle4->getPositionX(),ptitle4->getPositionY()));
		pLayer->addChild(pcnt);

		int size = 0;
		LuaData::getProp_size("gdSuitAttribute",suitid,0,size);
		for (int i = 1;i<=size;i++)
		{
			int t_suitcnt = 0;
			LuaData::getProp("gdSuitAttribute",suitid,i,"cnt",t_suitcnt);
			if (t_suitcnt!=0)
			{
				CCString* pStr = CCString::createWithFormat("%d件:",t_suitcnt);
				int t_suitsize = 0;
				LuaData::getProp_size("gdSuitAttribute",suitid,i,t_suitsize);
				for (int j = 1;j<=t_suitsize;j++)
				{
					std::string suitstr = "";
					LuaData::getProp("gdSuitAttribute",suitid,i,j,"attrstring",suitstr);
					if (suitstr!="")
					{
						CCString* p = CCString::createWithFormat("%s%s",pStr->getCString(),suitstr.c_str());
						CCLabelTTF* psuit = CCLabelTTF::create(AToU8(p->getCString()),"",15);
						psuit->setAnchorPoint(CCPointZero);
						psuit->setPosition(ccp(pos.x-15,pos.y-20));
						if (suitcnt>=t_suitcnt)
						{
							psuit->setColor(ccGREEN);
						}
						else
						{
							psuit->setColor(ccGRAY);
						}
						pos=ccp(pos.x,pos.y-20);
						pLayer->addChild(psuit);
						mHeight+=psuit->getContentSize().height;
					}
				}
			}			
		}
	}


	//物品描述
	CCLabelTTF* ptitle5=CCLabelTTF::create(SystemData::getLayoutString("ItemTips_WPMS").c_str(),"",15);
	ptitle5->setAnchorPoint(CCPointZero);
	//ptitle5->setPosition(ccp(pos.x,pos.y-20));
	ptitle5->setPosition(ccp(pos.x-15,pos.y-20));
	ptitle5->setColor(ccORANGE);
	pos=ccp(pos.x,pos.y-20);
	pLayer->addChild(ptitle5);
	mHeight+=ptitle5->getContentSize().height;



	std::string desc;
	LuaData::getProp(LuaData::ITEM,item->sid,"desc",desc);
	CPRichText* pLabel5=RichTextUtils::getRichText(desc.c_str(),15,210,0);
	//CCLabelTTF* pLabel5=CCLabelTTF::create(desc.c_str(),"",15);
	pLabel5->setAnchorPoint(ccp(0,1));
	//pLabel5->setHorizontalAlignment(kCCTextAlignmentLeft);
	//pLabel5->setDimensions(CCSizeMake(210,0));
	pLabel5->setPosition(ccp(pos.x-15,pos.y-5));
	//pLabel5->setColor(ccGREEN);
	pos=pLabel5->getPosition();
	pLayer->addChild(pLabel5);
	mHeight+=pLabel5->getContentSize().height;
	mHeight+=60;

	return pLayer;
}

CCLayer* ItemTooltip::getOtherInfoLayer( UserItem* item )
{
	CCLayer *pLayer=CCLayer::create();
	//物品描述
	CCPoint pos=ccp(15,0);
	CCLabelTTF* ptitle5=CCLabelTTF::create(SystemData::getLayoutString("ItemTips_WPMS").c_str(),"",15);
	ptitle5->setAnchorPoint(CCPointZero);
	//ptitle5->setPosition(ccp(pos.x,pos.y-20));  
	ptitle5->setPosition(ccp(pos.x-15,pos.y-20));
	pos=ptitle5->getPosition();
	pLayer->addChild(ptitle5);
	mHeight+=ptitle5->getContentSize().height;


	std::string desc;
	LuaData::getProp(LuaData::ITEM,item->sid,"desc",desc);
	CPRichText* pLabel5=RichTextUtils::getRichText(desc.c_str(),15,190,0);
	//CCLabelTTF* pLabel5=CCLabelTTF::create(desc.c_str(),"",15);
	pLabel5->setAnchorPoint(ccp(0,1));
	//pLabel5->setHorizontalAlignment(kCCTextAlignmentLeft);
	//pLabel5->setDimensions(CCSizeMake(190,0));
	pLabel5->setPosition(ccp(pos.x,pos.y-5));
	//pLabel5->setColor(ccGREEN);
	pos=pLabel5->getPosition(); 
	pLayer->addChild(pLabel5);
	mHeight+=pLabel5->getContentSize().height;
	mHeight+=10;
	return pLayer; 
}

void ItemTooltip::settingButton(CCMenu* pMenu, int type )
{
	CCLabelTTF* plabel1=NULL;
	CCMenuItemImage* pItem1=SystemData::getScale9MenuItemImageByPlist("forging_bag_button");
	//pItem1->setContentSize(CCSizeMake(SystemData::getLayoutValue("forging_bag_button.w"),SystemData::getLayoutValue("forging_bag_button.h")));
	//CCMenuItemImage* pItem1=SystemData::getMenuItemImageByPlist("forging_bag_button");//第一个按钮	
	pItem1->setTarget(this,menu_selector(ItemTooltip::MenuCallBack));

	CCLabelTTF* plabel2=NULL;
	CCMenuItemImage* pItem2=SystemData::getScale9MenuItemImageByPlist("forging_bag_button"); 
	//pItem2->setContentSize(CCSizeMake(SystemData::getLayoutValue("forging_bag_button.w"),SystemData::getLayoutValue("forging_bag_button.h")));
	//CCMenuItemImage* pItem2=SystemData::getMenuItemImageByPlist("forging_bag_button");//第二个按钮 
	pItem2->setTarget(this,menu_selector(ItemTooltip::MenuCallBack));
	switch (type)
	{
	case TAG_Tips:
		break;
	case TAG_Tips_ZBDQ://装备和丢弃
		plabel1=CCLabelTTF::create(AToU8("装备"),"",20);
		pItem1->setTag(TAG_UP);
		pItem1->setPosition(SystemData::getLayoutPoint("Tips_button1_pos_e"));

		plabel2=CCLabelTTF::create(AToU8("丢弃"),"",20);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button2_pos_e"));
		pItem2->setTag(TAG_REMOVE);

		pMenu->addChild(pItem1);
		plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
		pItem1->addChild(plabel1);
		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_XX://卸下
		plabel2=CCLabelTTF::create(AToU8("卸下"),"",20);
		pItem2->setTag(TAG_DOWN);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button3_pos"));

		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_DQ://丢弃
		plabel2=CCLabelTTF::create(AToU8("丢弃"),"",20);
		pItem2->setTag(TAG_REMOVE);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button3_pos"));

		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_SYDQ://使用和丢弃
		plabel1=CCLabelTTF::create(AToU8("使用"),"",20);
		pItem1->setTag(TAG_USE);
		pItem1->setPosition(SystemData::getLayoutPoint("Tips_button1_pos_e"));
		plabel2=CCLabelTTF::create(AToU8("丢弃"),"",20);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button2_pos_e"));
		pItem2->setTag(TAG_REMOVE);

		pMenu->addChild(pItem1);
		plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
		pItem1->addChild(plabel1);
		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_QX://取消
		plabel2=CCLabelTTF::create(AToU8("取消"),"",20);
		pItem2->setTag(TAG_CANCEL);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button3_pos"));

		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;	
	case TAG_Tips_GM://购买
		plabel2=CCLabelTTF::create(AToU8("购买"),"",20);
		pItem2->setTag(TAG_BUY);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button3_pos"));

		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_HG://回购
		plabel2=CCLabelTTF::create(AToU8("回购"),"",20);
		pItem2->setTag(TAG_BUYBACK);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button3_pos"));

		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_BTQX://摆摊和取消 
		plabel1=CCLabelTTF::create(AToU8("摆摊"),"",20);
		pItem1->setTag(TAG_BOOTHUP);
		pItem1->setPosition(SystemData::getLayoutPoint("Tips_button1_pos_e"));
		plabel2=CCLabelTTF::create(AToU8("取消"),"",20);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button2_pos_e"));
		pItem2->setTag(TAG_CANCEL);

		pMenu->addChild(pItem1);
		plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
		pItem1->addChild(plabel1);
		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_CFQX1://存放和取消
		plabel1=CCLabelTTF::create(AToU8("存放"),"",20);
		pItem1->setTag(TAG_SAVE_PETBAG);
		plabel2=CCLabelTTF::create(AToU8("取消"),"",20);
		pItem2->setTag(TAG_CANCEL);		
		pItem1->setPosition(SystemData::getLayoutPoint("Tips_button1_pos_e"));
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button2_pos_e"));


		pMenu->addChild(pItem1);
		plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
		pItem1->addChild(plabel1);
		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_CFQX2://存放和取消
		plabel1=CCLabelTTF::create(AToU8("存放"),"",20);
		pItem1->setTag(TAG_SAVE_NPCBAG);
		plabel2=CCLabelTTF::create(AToU8("取消"),"",20);
		pItem2->setTag(TAG_CANCEL);		
		pItem1->setPosition(SystemData::getLayoutPoint("Tips_button1_pos_e"));
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button2_pos_e"));
		

		pMenu->addChild(pItem1);
		plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
		pItem1->addChild(plabel1);
		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_XJQX://下架和取消
		plabel1=CCLabelTTF::create(AToU8("下架"),"",20);
		pItem1->setTag(TAG_BOOTHDOWN);
		plabel2=CCLabelTTF::create(AToU8("取消"),"",20);
		pItem2->setTag(TAG_CANCEL);		
		pItem1->setPosition(SystemData::getLayoutPoint("Tips_button1_pos_e"));
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button2_pos_e"));


		pMenu->addChild(pItem1);
		plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
		pItem1->addChild(plabel1);
		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_QCQX2:
		plabel1=CCLabelTTF::create(AToU8("取出"),"",20);
		pItem1->setTag(TAG_TAKE_PET);
		plabel2=CCLabelTTF::create(AToU8("取消"),"",20);
		pItem2->setTag(TAG_CANCEL);		
		pItem1->setPosition(SystemData::getLayoutPoint("Tips_button1_pos_e"));
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button2_pos_e"));


		pMenu->addChild(pItem1);
		plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
		pItem1->addChild(plabel1);
		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_QCQX:
		plabel1=CCLabelTTF::create(AToU8("取出"),"",20);
		pItem1->setTag(TAG_TAKE);
		plabel2=CCLabelTTF::create(AToU8("取消"),"",20);
		pItem2->setTag(TAG_CANCEL);		
		pItem1->setPosition(SystemData::getLayoutPoint("Tips_button1_pos_e"));
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button2_pos_e"));


		pMenu->addChild(pItem1);
		plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
		pItem1->addChild(plabel1);
		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_GMQX:
		plabel1=CCLabelTTF::create(AToU8("购买"),"",20);
		pItem1->setTag(TAG_BOOTHBUY);
		plabel2=CCLabelTTF::create(AToU8("取消"),"",20);
		pItem2->setTag(TAG_CANCEL);		
		pItem1->setPosition(SystemData::getLayoutPoint("Tips_button1_pos_e"));
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button2_pos_e"));


		pMenu->addChild(pItem1);
		plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
		pItem1->addChild(plabel1);
		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_JY:
		plabel2=CCLabelTTF::create(AToU8("交易"),"",20);
		pItem2->setTag(TAG_TRADE);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button3_pos"));

		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_QXJY:
		plabel2=CCLabelTTF::create(AToU8("取消"),"",20);
		pItem2->setTag(TAG_CANCELTRADE);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button3_pos"));

		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_MC:
		plabel2=CCLabelTTF::create(AToU8("卖出"),"",20);
		pItem2->setTag(TAG_SELL);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button3_pos"));

		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;

	case TAG_Tips_TR:
		plabel2=CCLabelTTF::create(AToU8("投入"),"",20);
		pItem2->setTag(TAG_THROW);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button3_pos"));

		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_JRKJJ:
		plabel2=CCLabelTTF::create(AToU8("加入"),"",20);
		pItem2->setTag(TAG_SET);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button3_pos"));

		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_ZSQX:
		plabel1=CCLabelTTF::create(AToU8("展示"),"",20);
		pItem1->setTag(TAG_WATCHOUT);
		plabel2=CCLabelTTF::create(AToU8("取消"),"",20);
		pItem2->setTag(TAG_CANCEL);		
		pItem1->setPosition(SystemData::getLayoutPoint("Tips_button1_pos_e"));
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button2_pos_e"));


		pMenu->addChild(pItem1);
		plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
		pItem1->addChild(plabel1);
		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	case TAG_Tips_XXTB://卸下和投保
		plabel1=CCLabelTTF::create(AToU8("卸下"),"",20);
		pItem1->setTag(TAG_DOWN);
		pItem1->setPosition(SystemData::getLayoutPoint("Tips_button1_pos_e"));
		pItem2->setTag(TAG_TOUBAO);
		pItem2->setPosition(SystemData::getLayoutPoint("Tips_button2_pos_e"));
		{
			int toubaoState = 0;
			std::map<int,int>::iterator itTB = userItem->data.find(ItemEquip::Item_Toubao);
			if(itTB != userItem->data.end()) toubaoState = itTB->second;
			if(toubaoState >= 1)
			{
				plabel2 = CCLabelTTF::create(AToU8("已投保"),"",20);
				pItem2->setEnabled(false);
			}
			else
			{
				plabel2 = CCLabelTTF::create(AToU8("投保"),"",20);
				pItem2->setEnabled(true);
			}
		}

		pMenu->addChild(pItem1);
		plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
		pItem1->addChild(plabel1);
		pMenu->addChild(pItem2);
		plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pItem2->addChild(plabel2);
		break;
	}
}

void ItemTooltip::postItemMoveMsg( int startIndex )
{
	MsgItemOperationRequestSetPosition* req=new MsgItemOperationRequestSetPosition;
	req->iid=userItem->iid;
	req->position=GameData::s_user->getUserItemData()->getEmptyPosition(startIndex);
	HandleMessage::sendMessage(req);
}

void ItemTooltip::setTooltipSkill( int skillID )
{
	m_iCurrentTipsType=SkillTips;
	m_iCurSkillID=skillID;

	m_pBkg=SystemData::getScale9SpriteByPlist("Tips_skillwaikuang",SystemData::getLayoutValue("Tips_skill_size.w"),SystemData::getLayoutValue("Tips_skill_size.h"));
	m_pBkg->setAnchorPoint(CCPointZero);
	m_pBkg->setPosition(ccp(0,0));
	addChild(m_pBkg, 0);

	m_nWidth=m_pBkg->getContentSize().width;
	m_nHeight=m_pBkg->getContentSize().height;
	addCover();

	CCScale9Sprite* pBkg=SystemData::getScale9SpriteByPlist("Tips_waikuang1",SystemData::getLayoutValue("Tips_skill_size.w")-14,SystemData::getLayoutValue("Tips_skill_size.h")-60);
	pBkg->setAnchorPoint(CCPointZero);
	pBkg->setPosition(ccp(7,14));
	addChild(pBkg, 0);

	CCLayer *pLayer=getSkillInfo(); 
	pLayer->setPosition(SystemData::getLayoutPoint("Tips_skill_pos"));
	addChild(pLayer);
	
}

void ItemTooltip::postBoothBuy()
{
	MsgBuyEntityMarketThingRequestEx* msg=new MsgBuyEntityMarketThingRequestEx;
	//msg->position=userItem->position;
	msg->iid=userItem->iid;
	msg->cnt=userItem->count;
	msg->MoneyType=userItem->data[ItemEquip::Item_Market_Type];
	msg->Price=userItem->data[ItemEquip::Item_Market_Price];	msg->pid=GameData::s_user->m_pMainRole->m_iTargetpid;
	HandleMessage::sendMessage(msg);
}

void ItemTooltip::postTradeItem()
{
	MsgItemTradeChangeItem* req=new MsgItemTradeChangeItem;
	req->iid=userItem->iid;
	req->cnt=userItem->count;
	req->position=GameData::s_user->getUserItemData()->getEmptyPosition(ItemPos::Trade_Bag_Start);
	HandleMessage::sendMessage(req);
}

void ItemTooltip::postCancelTradeItem()
{
	MsgItemTradeChangeItem* req=new MsgItemTradeChangeItem;
	req->iid=userItem->iid;
	req->cnt=userItem->count;
	req->position=GameData::s_user->getUserItemData()->getEmptyPosition(ItemPos::Player_Bag_Start);
	HandleMessage::sendMessage(req);
}

void ItemTooltip::postRemoveItem(int tag)
{
	if (tag==0)
	{
		GameData::s_user->m_pMainRole->abandonItem(userItem->iid,userItem->count);
	}
	this->removeFromParent();
}

void ItemTooltip::compareItem()
{
	UserItems items = GameData::s_user->getUserItemData()->userItems;

	int n=1;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		//判断身上是否有此类型装备
		if (it->first<ItemPosition_Null && it->first>=ItemPosition_Equip_Material && it->second->type==GameData::s_user->getUserItemData()->getItemType(userItem->sid))
		{
			ItemTooltip* p1=ItemTooltip::create();
			p1->setTooltipContent(it->second, TAG_Tips,false);
			p1->setAnchorPoint(CCPointZero);
			p1->setPosition(ccp(-250*n,0));
			p1->setIscompare(true);
			p1->setCompareCombatNum(GameData::s_user->getUserItemData()->getCombatNum(userItem));
			p1->setIsCheckInPanel(false);
			addChild(p1);
			n++;
		}
	}
	if (n==3)
	{
		this->setPosition(ccp(-1,-1));
	}
}

void ItemTooltip::setTooltipContentbysid( int sid ,int type /*=0 */ )
{
	UserItem* pItem=CommonFunction::createNewItem(sid);
	setTooltipContent(pItem,type);
}

void ItemTooltip::postSellItem()
{
	MsgItemOperationRequestSell* msgSell = new MsgItemOperationRequestSell;
	msgSell->iid = userItem->iid;
	msgSell->count = userItem->count;
	HandleMessage::sendMessage(msgSell);

	NpcShopComp::_s_state = ItemOperationDefine::item_op_sell;
}

void ItemTooltip::postToubao()
{
	MsgItemOperationRequestUse* req = new MsgItemOperationRequestUse;
	req->iid = userItem->iid;
	req->eid = -1;
	req->cnt = 1;
	HandleMessage::sendMessage(req);
	closeCallBack(NULL);
}

void ItemTooltip::setIscompare( bool flag )
{
	m_bIscompare=flag;
}
 
CCLayer* ItemTooltip::getSkillInfo()
{
	CCLayer *player=CCLayer::create();
	CCTableViewEx* pTabelView = CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("Tips_tabelview_skill_size").width,SystemData::getLayoutSize("Tips_tabelview_skill_size").height),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(ccp(0,5));
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	player->addChild(pTabelView);	
	return player; 
}

/**
 * 创建技能信息显示层
 * @param skillid 技能ID
 * @return 包含技能信息的CCLayer
 */
CCLayer* ItemTooltip::getSkillInfoLayer(int skillid)
{
    CCLayer* pLayer = CCLayer::create();  // 创建技能信息图层

    // 1. 显示技能图标
    const CCPoint& iconPos = ccp(47, -40);  // 图标位置
    std::string strIconUrl;
    std::string strKey = "icon";
    // 从Lua配置表获取技能图标资源名
    LuaData::getProp(LuaData::SKILL, skillid, strKey, strIconUrl);
    strIconUrl = "skill_" + strIconUrl;  // 添加前缀
    
    // 创建图标背景
    CCSprite* pIconbkg = SystemData::getSpriteByPlist("skillpanel.iconbkg");
    pIconbkg->setPosition(iconPos);
    pLayer->addChild(pIconbkg);
    
    // 创建技能图标
    CCSprite* pIcon = LayoutData::getSpriteByFrameName(strIconUrl + ".png");
    pIcon->setPosition(iconPos);
    pLayer->addChild(pIcon);

    mHeight = 15;  // 初始化高度偏移
    CCPoint pos = ccp(15, 0);  // 文本起始位置

    // 2. 显示技能名称
    std::string name;
    LuaData::getProp(LuaData::SKILL, skillid, "name", name);  // 获取技能名称
    CCLabelTTF* p1 = CCLabelTTF::create(name.c_str(), "", 18);
    p1->setAnchorPoint(ccp(0, 1));  // 左上角锚点
    p1->setPosition(ccp(pos.x + pIconbkg->getContentSize().width + 5, 
                        pos.y - pIconbkg->getContentSize().height / 2));  // 图标右侧
    p1->setHorizontalAlignment(kCCTextAlignmentLeft);  // 左对齐
    pLayer->addChild(p1);
    pos = ccp(pos.x, pos.y - pIconbkg->getContentSize().height);  // 更新位置
    mHeight += pIconbkg->getContentSize().height;  // 累加高度

    // 3. 检查技能是否已学习
    int learned = 0;
    int tgtexp = 0;
    LuaData::getProp(LuaData::SKILL, skillid, "tgtexp", tgtexp);  // 获取目标经验值
    GameRole* myRole = GameData::getMyRole();  // 获取玩家角色
    
    // 如果技能未学习，显示学习前描述
    if (!GameData::getMyRole()->isSkillLearned(skillid, learned))
    {
        std::string strDesp;
        LuaData::getProp(LuaData::SKILL, skillid, "desc_before_learn", strDesp);  // 获取未学习描述
        CCLabelTTF* p2 = CCLabelTTF::create(strDesp.c_str(), "", 18);
        p2->setHorizontalAlignment(kCCTextAlignmentLeft);
        p2->setDimensions(CCSizeMake(SystemData::getLayoutValue("Tips_tabelview_skill_size.w") - 15, 0));
        p2->setAnchorPoint(ccp(0, 1));
        p2->setPosition(ccp(pos.x, pos.y));
        p2->setColor(ccc3(6, 95, 110));  // 深蓝色
        pLayer->addChild(p2);
        pos = ccp(pos.x, pos.y - p2->getContentSize().height);
        mHeight += p2->getContentSize().height;
    }

    // 4. 显示技能等级
    int level = 0;
    LuaData::getProp(LuaData::SKILL, skillid, "lvl", level);  // 获取技能等级
    std::string strLevel = SystemData::getLayoutString("skillpanel.level") + SystemData::intToString(level);
    CCLabelTTF* p2 = CCLabelTTF::create(strLevel.c_str(), "", 18);
    p2->setHorizontalAlignment(kCCTextAlignmentLeft);
    p2->setDimensions(CCSizeMake(SystemData::getLayoutValue("Tips_tabelview_skill_size.w") - 15, 0));
    p2->setAnchorPoint(ccp(0, 1));
    p2->setPosition(ccp(pos.x, pos.y - 15));
    pLayer->addChild(p2);
    
    // 5. 显示技能魔法消耗
    int magic_cost = 0;
    LuaData::getProp(LuaData::SKILL, skillid, "mana", magic_cost);  // 获取魔法消耗
    std::string strMagicCost = SystemData::getLayoutString("skillpanel.magiccost") + SystemData::intToString(magic_cost);
    CCLabelTTF* p3 = CCLabelTTF::create(strMagicCost.c_str(), "", 18);
    p3->setHorizontalAlignment(kCCTextAlignmentLeft);
    p3->setDimensions(CCSizeMake(SystemData::getLayoutValue("Tips_tabelview_skill_size.w") - 15, 0));
    p3->setAnchorPoint(ccp(0, 1));
    p3->setPosition(ccp(pos.x + 150, p2->getPositionY()));  // 与等级信息并排
    pLayer->addChild(p3);
    
    pos = ccp(pos.x, pos.y - p2->getContentSize().height);
    mHeight += p2->getContentSize().height;

    // 6. 如果技能已学习，显示经验进度条
    if (learned >= 0)
    {
        int curexp = HeroData::getSkillExp(skillid);  // 获取当前技能经验
        
        if (tgtexp != 0)  // 如果有目标经验值
        {
            // 经验标签
            std::string strExp1 = SystemData::getLayoutString("skillpanel.experience.desc");
            CCLabelTTF* p4 = CCLabelTTF::create(strExp1.c_str(), "", 18);
            p4->setHorizontalAlignment(kCCTextAlignmentLeft);
            p4->setAnchorPoint(ccp(0, 1));
            p4->setPosition(ccp(pos.x, pos.y - 15));
            p4->setColor(ccc3(15, 255, 240));  // 浅蓝色
            pLayer->addChild(p4);

            // 经验条背景
            CCScale9Sprite* pExperienceBkg = SystemData::getScale9SpriteByPlist("skillpanel.experience.bkg", 110, 10);
            pExperienceBkg->setAnchorPoint(ccp(0, 0.5));
            pExperienceBkg->setPosition(ccp(p4->getPositionX() + p4->getContentSize().width + 5, 
                                           pos.y - 15 - p4->getContentSize().height / 2));
            pLayer->addChild(pExperienceBkg);

            // 经验进度条
            CCScale9Sprite* pExperienceBar = SystemData::getScale9SpriteByPlist("skillpanel.experience", 110, 10);
            pExperienceBar->setAnchorPoint(ccp(0, 0.5));
            pExperienceBar->setPosition(pExperienceBkg->getPosition());
            float percent = (float)curexp / (float)tgtexp;  // 计算百分比
            if (percent > 1.0f) percent = 1.0f;  // 限制最大100%
            if (percent < 0.0f) percent = 0.0f;  // 限制最小0%
            pExperienceBar->setScaleX(percent);  // 缩放X轴表示进度
            pLayer->addChild(pExperienceBar);

            // 经验数值文本
            std::string strExp2 = SystemData::intToString(curexp) + "/" + SystemData::intToString(tgtexp);
            CCLabelTTF* p5 = CCLabelTTF::create(strExp2.c_str(), "", 14);
            p5->setHorizontalAlignment(kCCTextAlignmentLeft);
            p5->setPosition(ccp(pExperienceBkg->getPositionX() + pExperienceBkg->getContentSize().width / 2, 
                               pExperienceBkg->getPositionY()));
            p5->setColor(ccWHITE);
            pLayer->addChild(p5);
            
            pos = ccp(pos.x, pos.y - p4->getContentSize().height);
            mHeight += p4->getContentSize().height;
        }
    }

    // 7. 显示技能效果描述
    std::string skillEffect;
    LuaData::getProp(LuaData::SKILL, skillid, "desc", skillEffect);  // 获取技能描述
    skillEffect = SystemData::getLayoutString("skillpanel.description") + skillEffect;
    CCLabelTTF* p4 = CCLabelTTF::create(skillEffect.c_str(), "", 18);
    p4->setHorizontalAlignment(kCCTextAlignmentLeft);
    p4->setDimensions(CCSizeMake(SystemData::getLayoutValue("Tips_tabelview_skill_size.w") - 15, 0));
    p4->setAnchorPoint(ccp(0, 1));
    p4->setPosition(ccp(pos.x, pos.y - 15));
    p4->setColor(ccc3(15, 255, 240));  // 浅蓝色
    pLayer->addChild(p4);
    pos = ccp(pos.x, pos.y - p4->getContentSize().height);
    mHeight += p4->getContentSize().height;

    // 8. 如果技能有下一级，显示下一级信息
    if (learned != 0)
    {
        learned = skillid + 1;  // 下一级技能ID
        
        if (LuaData::checkIdExist(LuaData::SKILL, learned))  // 检查下一级技能是否存在
        {
            // 8.1 显示下一级等级
            int level = 0;
            LuaData::getProp(LuaData::SKILL, learned, "lvl", level);
            std::string strLevel = SystemData::getLayoutString("skillpanel.nextlevel") + SystemData::intToString(level);
            CCLabelTTF* p5 = CCLabelTTF::create(strLevel.c_str(), "", 18);
            p5->setHorizontalAlignment(kCCTextAlignmentLeft);
            p5->setDimensions(CCSizeMake(SystemData::getLayoutValue("Tips_tabelview_skill_size.w") - 15, 0));
            p5->setAnchorPoint(ccp(0, 1));
            p5->setPosition(ccp(pos.x, pos.y - 15));
            p5->setColor(ccc3(15, 240, 0));  // 浅绿色
            pLayer->addChild(p5);
            pos = ccp(pos.x, pos.y - p5->getContentSize().height);
            mHeight += p5->getContentSize().height;

            // 8.2 显示下一级学习条件
            int tgtexp = 1;
            int skillidup = 0;
            strKey = "tgtexp";
            std::string id = "id";
            LuaData::getProp(LuaData::SKILL, skillid, strKey, tgtexp);
            LuaData::getProp(LuaData::SKILL, learned, id, skillidup);
            
            if (skillidup != 0 && tgtexp == 0)  // 如果下一级存在且需要条件
            {
                int reqlv = 0;
                int reborn = 0;
                std::string strReqLv = "";
                std::string strdesc = "";
                CCLabelTTF* pReqLv = CCLabelTTF::create();
                
                strKey = "reqlvl";
                LuaData::getProp(LuaData::SKILL, learned, strKey, reqlv);  // 需求等级
                LuaData::getProp(LuaData::SKILL, learned, "reborn", reborn);  // 转生需求
                LuaData::getProp(LuaData::SKILL, learned, "desc_before_learn", strdesc);  // 学习前描述
                
                // 构建需求文本
                if (reborn)  // 有转生需求
                {
                    strReqLv = SystemData::intToString(reborn) + SystemData::getLayoutString("skillpanel.reborn");
                }
                if (reqlv)  // 有等级需求
                {
                    strReqLv = SystemData::intToString(reqlv) + SystemData::getLayoutString("skillpanel.reqlvl");
                }
                
                pReqLv = CCLabelTTF::create(strReqLv.c_str(), "", 16);
                pReqLv->setColor(ccYELLOW);  // 黄色强调
                pReqLv->setPosition(ccp(p5->getPositionX() + 100, p5->getPositionY() - 10));
                pReqLv->setAnchorPoint(ccp(0, 0.5));
                pLayer->addChild(pReqLv);
            }

            // 8.3 显示下一级技能效果
            std::string skillEffect;
            LuaData::getProp(LuaData::SKILL, learned, "desc", skillEffect);
            skillEffect = SystemData::getLayoutString("skillpanel.description") + skillEffect;
            
            // 使用富文本显示技能效果（支持颜色、样式等）
            CPRichText* p6 = RichTextUtils::getRichText(skillEffect.c_str(), 18, 
                                                       SystemData::getLayoutValue("Tips_tabelview_skill_size.w") - 15, 0);
            p6->setAnchorPoint(ccp(0, 1));
            p6->setPosition(ccp(pos.x, pos.y - 15));
            pLayer->addChild(p6);
            
            pos = ccp(pos.x, pos.y - p6->getContentSize().height);
            mHeight += p6->getContentSize().height;
        }
    }
    
    return pLayer;  // 返回完整的技能信息层
}

void ItemTooltip::setfastkey()
{
	//UserItem* pUserItem=(UserItem*)pItem->getUserData();
	CPEventHelper::setEventIntData(CPEventName::DATA_CHANGE, CPEventData::VALUE_2, 2);
	CPEventHelper::setEventIntData(CPEventName::DATA_CHANGE, CPEventData::VALUE_3, userItem->sid);
	CPEventHelper::dispatcher(CPEventName::DATA_CHANGE, "", "SettingFastPanel");
	/*int id=UserData::getemptyFast();
	if (id==0)
	{
		CPEventHelper::msgResponse("","",Error::Max_FastKey);
	}
	else
	{
		UserData::setIntData(HeroData::getPID(),CPUserData::FAST_TYPE_,id,2);
		UserData::setIntData(HeroData::getPID(),CPUserData::FAST_NUM_,id,userItem->sid);
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_FAST_KEY);
	}*/
}

int ItemTooltip::getCombatNum( UserItem* item )
{
	int CombatNum=0;
	int size;
	LuaData::getProp_size(LuaData::ITEM,item->sid,"attr",size);

	bool hasluck=false;
	//基础属性加成
	for (int i=1;i<=size;i++) 
	{
		int min,max,type;
		LuaData::getProp_ItemInfo(LuaData::ITEM,item->sid,"attr",i,"max","min","type",type,min,max);

		if(userItem->data[ItemEquip::Item_RebornLvl]!=0)
		{
			if (type==Combat::prop_Physical_Attack||
				type==Combat::prop_Magical_Attack||
				type==Combat::prop_Taoism_Attack||type==Combat::prop_Physical_Defense||type==Combat::prop_Magical_Defense)
			{
				min+=min/5*userItem->data[ItemEquip::Item_RebornLvl];
				max+=max/5*userItem->data[ItemEquip::Item_RebornLvl];
			}
		}

		if (item->data[ItemEquip::Item_EnhanceLevel]!=0 && (type==Combat::prop_Physical_Attack||type==Combat::prop_Magical_Attack||type==Combat::prop_Taoism_Attack))
		{
			int value;
			LuaData::getProp("gdEquipEnhance",item->data[ItemEquip::Item_EnhanceLevel]-1,"enhanceValue",value);
			min+=value;
			max+=value;
		}

		CombatNum+=getCombatTypeNum(type,min);
		if (type==Combat::prop_Physical_Attack||type==Combat::prop_Magical_Attack||type==Combat::prop_Taoism_Attack||type==Combat::prop_Physical_Defense||type==Combat::prop_Magical_Defense)
		{
			CombatNum+=getCombatTypeNum(type+1,max);
		}
		if (type==Combat::prop_Luck)
		{
			hasluck=true;
			CombatNum+=getCombatTypeNum(type,userItem->data[ItemEquip::Item_Lucky]+min);
		}
	}
	if (!hasluck)
	{
		if (userItem->data[ItemEquip::Item_Lucky]!=0)
		{
			CombatNum+=getCombatTypeNum(Combat::prop_Luck,userItem->data[ItemEquip::Item_Lucky]);
		}
	}

	//鉴定属性
	int reqlvl;
	LuaData::getProp(LuaData::ITEM,userItem->sid,"req_level",reqlvl);
	int combo=item->data[ItemEquip::Item_DataCombo];
	if (reqlvl>=20 && combo!=0)
	{
		int number=0;
		for (int b=0;b<3;b++)
		{
			int c=(int)((int)combo >> (8*b) & 255);
			if(c!=0)
			{
				number++;
			}
		}	
		int n=0;
		for (n;(int)((int)combo>>(n*8) & 255)!=0;n++)
		{
			int x=(int)((int)combo>>(n*8) & 255);
			float combovalue;
			if (x==11 || x==12 || x==13 || x==15 || x==17|| x==18)
			{
				combovalue=(float)item->data[ItemEquip::Item_DataX+n];
				combovalue=combovalue/100;
			}
			else
			{
				combovalue=item->data[ItemEquip::Item_DataX+n];
			}
			CombatNum+=getCombatTypeNum(x,combovalue,2);
		}
	}

	// 极品属性
	int spAttrid=item->data[ItemEquip::Item_SpecialIdx];
	int spAttrdata=item->data[ItemEquip::Item_SpecialData];
	if (spAttrid!=0)
	{
		CombatNum+=getCombatTypeNum(spAttrid,spAttrdata,2);
	}

	return CombatNum;
}

int ItemTooltip::getCombatTypeNum( int type,int num ,int tag)
{
	int combatnum=0;
	if (tag==1)
	{
		switch (type)
		{
		case Combat::prop_HPMax	:
			combatnum=num/1*20;
			break;
		case Combat::prop_MPMax	:
			combatnum=num/1*20;
			break;
		case Combat::prop_HP	:
			break;
		case Combat::prop_MP	:
			break;
		case Combat::prop_Physical_Attack	:
			if (HeroData::getJob()==UserData::CARRER_ZS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case Combat::prop_PATK_Max	:
			if (HeroData::getJob()==UserData::CARRER_ZS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case Combat::prop_Magical_Attack	:
			if (HeroData::getJob()==UserData::CARRER_FS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case Combat::prop_MATK_Max	:
			if (HeroData::getJob()==UserData::CARRER_FS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case Combat::prop_Taoism_Attack	:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case Combat::prop_TATK_Max	:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case Combat::prop_PDEF_Min	:
			combatnum=num/2*1;
			break;
		case Combat::prop_PDEF_Max	:
			combatnum=num/2*1;
			break;
		case Combat::prop_MDEF_Min	:
			combatnum=num/2*1;
			break;
		case Combat::prop_MDEF_Max	:
			combatnum=num/2*1;
			break;
		case Combat::prop_Health_Recovery_Point	:
			combatnum=num/50*1;
			break;
		case Combat::prop_Magic_Recovery_Point	:
			combatnum=num/50*1;
			break;	
		case Combat::prop_Hit	:
			combatnum=num/1*10;
			break;	
		case Combat::prop_Dodge	:
			combatnum=num/1*20;
			break;	
		case Combat::prop_Magic_Hit	:
			combatnum=num/0.5*1;
			break;	
		case Combat::prop_Magic_Dodge	:
			combatnum=num/0.5*1;
			break;	
		case Combat::prop_Posion_Dodge	:
			break;	
		case Combat::prop_Posion_Recovery_Point	:
			combatnum=num/50*1;
			break;	
		case Combat::prop_Palsy	:
			combatnum=num/1*50;
			break;	
		case Combat::prop_Death_Recovery_Percent	:
			combatnum=num/1*7;
			break;	
		case Combat::prop_Luck	:
			combatnum=num/1*25;
			break;	
		case Combat::prop_Curse	:
			break;	
		case Combat::prop_Holy_Damage	:
			combatnum=num/25*1;
			break;	
		case Combat::prop_Damage_to_Magic	:
			combatnum=num/1*7;
			break;	
		case Combat::prop_Critical_Damage_Bonus	://暴击
			combatnum=num/1 * 10;
			break;
		case Combat::prop_Anti_Critical	://防爆
			combatnum=num/1 * 10;
			break;
		case Combat::prop_Damage_Reflect_Rate ://反弹
	        combatnum=num/1 * 10;
	        break;
		case Combat::prop_Life_Steal_Rate ://吸血
	        combatnum=num/1 * 1;
	        break;
		case Combat::prop_Mana_Steal_Rate ://吸蓝
	        combatnum=num/1 * 1;
	        break;
		default:
			break;
		}
	}
	else if (tag==2)
	{
		switch (tag)
		{
		case 1:
			if (HeroData::getJob()==UserData::CARRER_ZS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case 2:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case 3:
			if (HeroData::getJob()==UserData::CARRER_FS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case 4:
			if (HeroData::getJob()==UserData::CARRER_ZS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case 5:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case 6:
			if (HeroData::getJob()==UserData::CARRER_FS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case 7:
			combatnum=num/2*1;
			break;
		case 8:
			combatnum=num/2*1;
			break;
		case 9:
			combatnum=num/2*1;
			break;
		case 10:
			combatnum=num/2*1;
			break;
		case 11:
			combatnum=num/50*1;
			break;
		case 12:
			combatnum=num/50*1;
			break;
		case 13:
			combatnum=num/0.5*1;
			break;
		case 14:
			combatnum=num/25*1;
			break;
		case 15:
			combatnum=num/50*1;
			break;
		case 16:
			combatnum=num/1*10;
			break;
		case 17:
			combatnum=num/0.5*1;
			break;
		case 18:
			break;
		case 19:
			combatnum=num/1*20;
			break;
		default:
			break;
		}
	}
	return combatnum;
}

void ItemTooltip::setCompareCombatNum( int num )
{
	m_iCombatNum=num;
}

/**
 * @brief 初始化装备物品的工具提示界面
 * 
 * 创建装备的详细信息展示界面，包括装备图标、属性、强化等级、耐久度等信息
 * @param type 工具提示类型（如TAG_Tips_ZBDQ、TAG_Tips_GMQX等）
 * @param flag 是否显示关闭按钮
 */
void ItemTooltip::initEquipItem(int type,bool flag)
{
	// 如果是装备对比或购买类型的提示，先进行装备比较
	if (type==TAG_Tips_ZBDQ || type==TAG_Tips_GMQX)
	{
		compareItem();
	}

	// 创建背景框
	m_pBkg=SystemData::getScale9SpriteByPlist("Tips_waikuang",SystemData::getLayoutValue("Tips_size_e.w"),SystemData::getLayoutValue("Tips_size_e.h")-m_iH);
	m_pBkg->setAnchorPoint(CCPointZero);
	m_pBkg->setPosition(ccp(0,m_iH));
	addChild(m_pBkg, 0);

	// 设置内容尺寸
	m_nWidth=m_pBkg->getContentSize().width;
	m_nHeight=m_pBkg->getContentSize().height;
	addCover(m_pBkg->getPosition());
	this->setContentSize(CCSizeMake(m_nWidth,m_nHeight));

	// 创建内层背景
	CCScale9Sprite* pBkg=SystemData::getScale9SpriteByPlist("Tips_waikuang1",SystemData::getLayoutValue("Tips_size_e.w")-14,SystemData::getLayoutValue("Tips_size_e.h")-62);
	pBkg->setPosition(ccp(7,57));
	pBkg->setAnchorPoint(CCPointZero);
	addChild(pBkg, 0);

	// 检查装备是否已绑定并显示标识
	if(userItem->position<ItemPosition_Null && userItem->position>ItemPosition_Equip_Max)
	{
		CCSprite* pHasEquip=SystemData::getSpriteByPlist("Tips_yibangding");
		pHasEquip->setPosition(SystemData::getLayoutPoint("Tips_yibangding"));
		addChild(pHasEquip);
	}
	
	// 创建装备名称标签
	CCLabelTTF* nameLabel = CCLabelTTF::create(GameData::s_user->getUserItemData()->getItemName(userItem->sid).c_str(),"",17);
	nameLabel->setAnchorPoint(CCPointZero);
	nameLabel->setPosition(SystemData::getLayoutPoint("Tips_e_label1_pos"));
	
	// 根据装备品质设置颜色
	int EquipColor = (GameData::s_user->getUserItemData()->getEquipColor(userItem->sid));
	switch(EquipColor)
	{
	case ItemQuality_Null:
		nameLabel->setColor(ccGRAY);
		break;
	case ItemQuality_Green:
		nameLabel->setColor(ccGREEN);
		break;
	case ItemQuality_Blue:
		nameLabel->setColor(ccBLUE);
		break;
	case ItemQuality_Magenta:
		nameLabel->setColor(ccMAGENTA);
		break;
	case ItemQuality_Yellow:
		nameLabel->setColor(ccYELLOW);
		break;
	case ItemQuality_Hose:
		nameLabel->setColor(ccRED);
		break;
	case ItemQuality_Tuo:
		nameLabel->setColor(ccMAGENTA);
		break;
	case ItemQuality_King:
		nameLabel->setColor(ccBLACK);
		break;
	default:
		nameLabel->setColor(ccGRAY);
		break;
	}
	addChild(nameLabel);

// 显示强化等级
if (userItem->data[ItemEquip::Item_EnhanceLevel] != 0)
{
	// 只在名称后面显示一次强化等级
	CCString *pStrEnhancelvl = CCString::createWithFormat("+%d", userItem->data[ItemEquip::Item_EnhanceLevel]);
	CCLabelTTF* lvlLabel = CCLabelTTF::create(pStrEnhancelvl->getCString(), "", 15);
	lvlLabel->setAnchorPoint(CCPointZero);
	lvlLabel->setColor(ccGREEN);
	lvlLabel->setPosition(ccp(nameLabel->getPositionX() + nameLabel->getContentSize().width + 1, nameLabel->getPositionY()));
	addChild(lvlLabel);
	
	// 显示强化星级/月亮/太阳图标
	int i = userItem->data[ItemEquip::Item_EnhanceLevel];
	CCPoint pos = ccp(SystemData::getLayoutPoint("Tips_e_label3_pos").x, SystemData::getLayoutPoint("Tips_e_label3_pos").y);
	
	// 根据强化等级显示不同的图标
	if (i <= 15)
	{
		// 1-15级显示星星
		for (int n = 0; n < i; n++)
		{
			CCSprite* pStar = SystemData::getSpriteByPlist("Tips_star");
			pStar->setAnchorPoint(CCPointZero);
			pStar->setScale(0.5f);
			pStar->setPosition(ccp(pos.x + n * 15 - 5, pos.y));
			addChild(pStar);
		}
	}
	else if (i < 20)
	{
		// 16-19级：先显示3个月亮
		for (int n = 0; n < 3; n++)
		{
			CCSprite* pmoon = SystemData::getSpriteByPlist("Tips_moon");
			pmoon->setAnchorPoint(CCPointZero);
			pmoon->setScale(0.5f);
			pmoon->setPosition(ccp(pos.x + n * 15 - 5, pos.y));
			addChild(pmoon);
		}
		
		// 然后显示剩余的星星（第4个位置开始）
		for (int n = 16; n <= i; n++)  // 从16级开始计数
		{
			CCSprite* pStar = SystemData::getSpriteByPlist("Tips_star");
			pStar->setAnchorPoint(CCPointZero);
			pStar->setScale(0.5f);
			// 从第4个位置开始，即3个月亮之后的位置
			pStar->setPosition(ccp(pos.x + 3 * 15 - 5 + (n - 16) * 15, pos.y));
			addChild(pStar);
		}
	}
	else if (i < 25)
	{
		// 20-24级：先显示4个月亮
		for (int n = 0; n < 4; n++)
		{
			CCSprite* pmoon = SystemData::getSpriteByPlist("Tips_moon");
			pmoon->setAnchorPoint(CCPointZero);
			pmoon->setScale(0.5f);
			pmoon->setPosition(ccp(pos.x + n * 15 - 5, pos.y));
			addChild(pmoon);
		}
		
		// 然后显示剩余的星星（第5个位置开始）
		for (int n = 20; n <= i; n++)  // 从20级开始计数
		{
			CCSprite* pStar = SystemData::getSpriteByPlist("Tips_star");
			pStar->setAnchorPoint(CCPointZero);
			pStar->setScale(0.5f);
			// 从第5个位置开始，即4个月亮之后的位置
			pStar->setPosition(ccp(pos.x + 4 * 15 - 5 + (n - 20) * 15, pos.y));
			addChild(pStar);
		}
	}
	else if (i < 30)
	{
		// 25-29级：先显示1个太阳
		CCSprite* pSun = SystemData::getSpriteByPlist("Tips_sun");
		pSun->setAnchorPoint(CCPointZero);
		pSun->setScale(0.5f);
		pSun->setPosition(ccp(pos.x, pos.y));
		addChild(pSun);
		
		// 然后显示剩余的星星（太阳之后的位置）
		for (int n = 25; n <= i; n++)  // 从25级开始计数
		{
			CCSprite* pStar = SystemData::getSpriteByPlist("Tips_star");
			pStar->setAnchorPoint(CCPointZero);
			pStar->setScale(0.5f);
			// 在太阳之后显示星星
			pStar->setPosition(ccp(pos.x + 15 - 5 + (n - 25) * 15, pos.y));
			addChild(pStar);
		}
	}
	else if (i < 40)
	{
		// 30-39级显示3个太阳
		for (int n = 0; n < 3; n++)
		{
			CCSprite* pSun = SystemData::getSpriteByPlist("Tips_sun");
			pSun->setAnchorPoint(CCPointZero);
			pSun->setScale(0.5f);
			pSun->setPosition(ccp(pos.x + n * 15 - 5, pos.y));
			addChild(pSun);
		}
	}
	else if (i < 50)
	{
		// 40-49级显示4个太阳
		for (int n = 0; n < 4; n++)
		{
			CCSprite* pSun = SystemData::getSpriteByPlist("Tips_sun");
			pSun->setAnchorPoint(CCPointZero);
			pSun->setScale(0.5f);
			pSun->setPosition(ccp(pos.x + n * 15 - 5, pos.y));
			addChild(pSun);
		}
	}
	else
	{
		// 50级及以上显示5个太阳
		for (int n = 0; n < 5; n++)
		{
			CCSprite* pSun = SystemData::getSpriteByPlist("Tips_sun");
			pSun->setAnchorPoint(CCPointZero);
			pSun->setScale(0.5f);
			pSun->setPosition(ccp(pos.x + n * 15 - 5, pos.y));
			addChild(pSun);
		}
	
	}
//--------------------------------------------------------------------------------------------------------

	m_icntEx++;  // 增加额外信息计数器
}

	// 显示绑定状态
	int bindtype=userItem->data[ItemEquip::Item_Bind]; 
	std::string str; 
	if (bindtype==ItemEquip::Item_Has_bind)
	{
		str="[已绑定]"; 
	}
	CCLabelTTF* bangdingLabel=CCLabelTTF::create(AToU8(str.c_str()),"",15);
	bangdingLabel->setAnchorPoint(CCPointZero);
	bangdingLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label2_pos").x,SystemData::getLayoutPoint("Tips_e_label2_pos").y-m_icntEx*20));
	bangdingLabel->setColor(ccRED);
	addChild(bangdingLabel);

	// 显示装备类型
	int itemtype;
	LuaData::getProp(LuaData::ITEM,userItem->sid,"type",itemtype);
	CCString* p1=CCString::createWithFormat("%s",ItemCate[itemtype-1].c_str());
	std::string strp1 = "类型：";
	strp1 += p1->getCString();
	CCLabelTTF* leixingLabel = CCLabelTTF::create(AToU8(strp1.c_str()), "", 15);
	leixingLabel->setAnchorPoint(CCPointZero);
	leixingLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label3_pos").x,SystemData::getLayoutPoint("Tips_e_label3_pos").y-m_icntEx*20));
	leixingLabel->setColor(ccBLUE);
	addChild(leixingLabel);

	// 显示装备战力
	int mCombatNum=ItemOperator::getItemCombatNum(userItem);
	CCString* p2=CCString::createWithFormat("%d",mCombatNum);
	std::string strp2 = "战力：";
	strp2 += p2->getCString();
	CCLabelTTF* zhanliLabel = CCLabelTTF::create(AToU8(strp2.c_str()), "", 15);
	zhanliLabel->setAnchorPoint(CCPointZero);
	zhanliLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label4_pos").x,SystemData::getLayoutPoint("Tips_e_label4_pos").y-m_icntEx*20));
	zhanliLabel->setColor(ccRED);
	addChild(zhanliLabel);

	// 装备对比逻辑（装备对比界面专用）
	bool hasdurable=true;
	if (type==TAG_Tips_ZBDQ && userItem->position>0)
	{
		int pos=0;
		// 根据装备类型获取对应位置的装备
		switch(GameData::s_user->getUserItemData()->getItemType(userItem->sid))
		{
		case ItemType_Equip_Weapon:
			pos = -2;
			break;
		case ItemType_Equip_Helmet:
			pos = -15;
			break;
		case ItemType_Equip_Neckless:
			pos = -1;
			break;
		case ItemType_Equip_Ring:
			pos = -11; // or -5
			break;
		case ItemType_Equip_Medal:
			pos = -14;
			break;
		case ItemType_Equip_Cloth:
			pos = -13;
			break;
		case ItemType_Equip_Shoes:
			pos = -10;
			break;
		case ItemType_Equip_Belt:
			pos = -9;
			break;
		case ItemType_Equip_Bangle:
			pos = -12; // or -4
			break;
		case ItemType_Equip_Stone:
			pos = -6;
			break;
		case ItemType_Equip_Wings:
			pos = -8;
			hasdurable=false;
			break;
		case ItemType_Equip_Fashion:
			pos = -7;
			hasdurable=false;
			break;
		case ItemType_Equip_Magic_Weapon:
			pos = -3;
			hasdurable=false;
			break;
		case ItemType_Equip_Material:
			pos = -16;
			hasdurable=false;
			break;
		case ItemType_Equip_Foot:
			pos = -17;
			hasdurable=false;
			break;
		case ItemType_Equip_Yuanshen:
			pos = -18;
			hasdurable=false;
			break;
		    case ItemType_Equip_Shenqi1:
			pos = -19;
			hasdurable=false;
			break;
			case ItemType_Equip_Shenqi2:
			pos = -20;
			hasdurable=false;
			break;
			case ItemType_Equip_Shenqi3:
			pos = -21;
			hasdurable=false;
			break;
			case ItemType_Equip_Shenqi4:
			pos = -22;
			hasdurable=false;
			break;
			case ItemType_Equip_Shenqi5:
			pos = -23;
			hasdurable=false;
			break;
			case ItemType_Equip_Shenqi6:
			pos = -24;
			hasdurable=false;
			break;
		default:
			break;
		}
		
		// 获取当前位置的装备进行战力对比
		UserItem* p=GameData::s_user->getUserItemData()->getItemByPosition(pos);
		if (p)
		{
			m_iCombatNum=GameData::s_user->getUserItemData()->getCombatNum(p);
		}
		int num=mCombatNum-m_iCombatNum;
		
		// 显示战力对比结果
		if (num>0)
		{
			CCSprite* pFlag=SystemData::getSpriteByPlist("Tips_zengqiang");
			pFlag->setScale(0.7f);
			pFlag->setAnchorPoint(CCPointZero);
			pFlag->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label4_pos").x+75,SystemData::getLayoutPoint("Tips_e_label4_pos").y-m_icntEx*20));
			addChild(pFlag);

			CCLabelTTF* p=CCLabelTTF::create(SystemData::intToString(num).c_str(),"",16);
			p->setAnchorPoint(CCPointZero);
			p->setPosition(ccp(pFlag->getPositionX()+pFlag->getContentSize().width,pFlag->getPositionY()));
			p->setColor(ccGREEN);
			addChild(p);
		}
		else if (num<0)
		{
			CCSprite* pFlag=SystemData::getSpriteByPlist("Tips_jianruo");
			pFlag->setScale(0.7f);
			pFlag->setAnchorPoint(CCPointZero);
			pFlag->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label4_pos").x+75,SystemData::getLayoutPoint("Tips_e_label4_pos").y-m_icntEx*20));
			addChild(pFlag);

			CCLabelTTF* p=CCLabelTTF::create(SystemData::intToString(-num).c_str(),"",16);
			p->setAnchorPoint(CCPointZero);
			p->setPosition(ccp(pFlag->getPositionX()+pFlag->getContentSize().width,pFlag->getPositionY()));
			p->setColor(ccRED);
			addChild(p);
		}				
	}

	// 显示装备重量
	int itemweight;
	LuaData::getProp(LuaData::ITEM,userItem->sid,"weight",itemweight);
	CCString* p3=CCString::createWithFormat("重量：%d",itemweight);
	CCLabelTTF* zhongliangLabel=CCLabelTTF::create(AToU8(p3->getCString()),"",15);
	zhongliangLabel->setAnchorPoint(CCPointZero);
	zhongliangLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label5_pos").x,SystemData::getLayoutPoint("Tips_e_label5_pos").y-m_icntEx*20));
	addChild(zhongliangLabel);

	// 显示耐久度（如果装备有耐久）
	if (hasdurable)
	{
		int itemdurable;
		LuaData::getProp(LuaData::ITEM,userItem->sid,"durable",itemdurable);
		if (itemdurable!=0)
		{
			CCString* p4=CCString::createWithFormat("%d/%d",itemdurable-userItem->data[ItemEquip::Item_Durable],itemdurable);
			std::string strp4 = "耐久：";
			strp4 += p4->getCString();
			CCLabelTTF* naijiuLabel = CCLabelTTF::create(AToU8(strp4.c_str()), "", 15);
			naijiuLabel->setAnchorPoint(CCPointZero);
			naijiuLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label6_pos").x,SystemData::getLayoutPoint("Tips_e_label6_pos").y-m_icntEx*20));
			naijiuLabel->setColor(ccc3(0,204,255));
			// 耐久度为0时显示红色
			if (itemdurable-userItem->data[ItemEquip::Item_Durable]==0)
			{
				naijiuLabel->setColor(ccRED);
			}
			addChild(naijiuLabel);
		}
	}

	// 显示装备需求等级
	int itemreq_lvl;
	LuaData::getProp(LuaData::ITEM,userItem->sid,"req_level",itemreq_lvl);
	CCString* p5=CCString::createWithFormat("%d",itemreq_lvl);
	std::string strp5 = "等级：";
	strp5 += p5->getCString();
	CCLabelTTF* dengjiLabel = CCLabelTTF::create(AToU8(strp5.c_str()), "", 15);
	// 等级不足显示红色
	if (itemreq_lvl>GameData::s_user->m_pMainRole->mLevel && HeroData::getProp(Entity::attr_reborn)==0)
	{
		dengjiLabel->setColor(ccRED);
	}
	else
	{
		dengjiLabel->setColor(ccGREEN);
	}
	dengjiLabel->setAnchorPoint(CCPointZero);
	dengjiLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label7_pos").x,SystemData::getLayoutPoint("Tips_e_label7_pos").y-m_icntEx*20));
	addChild(dengjiLabel);
	dengjiLabel->setFontName("Arial");

	// 显示职业限制
	if (userItem->profession!=0)
	{
		std::string strname="";
		switch (userItem->profession)
		{
		case 1:
			strname="战士";
			break;
		case 2:
			strname="法师";
			break;
		case 3:
			strname="道士";
			break;
		case 4:
			strname="天机";
			break;
		default:
			break;
		}
		CCString* p6=CCString::createWithFormat("%s",strname.c_str());
		std::string strp6 = "职业限制：";
		strp6 += p6->getCString();
		CCLabelTTF* zhuanshengLabel = CCLabelTTF::create(AToU8(strp6.c_str()), "", 15);
		CCPoint pos=ccp(SystemData::getLayoutPoint("Tips_e_label8_pos").x,SystemData::getLayoutPoint("Tips_e_label8_pos").y-m_icntEx*20);
		// 职业不匹配显示红色
		if (userItem->profession!=GameData::s_user->m_pMainRole->mGhostJob)
		{
			zhuanshengLabel->setColor(ccRED);
		}
		else
		{
			zhuanshengLabel->setColor(ccGREEN); 
		}
		zhuanshengLabel->setAnchorPoint(CCPointZero);
		zhuanshengLabel->setPosition(pos);
		addChild(zhuanshengLabel);
		m_icntEx++;
	}

	// 显示转生需求
	if (userItem->data[ItemEquip::Item_RebornLvl]!=0)
	{
		CCString* p6=CCString::createWithFormat("%d",userItem->data[ItemEquip::Item_RebornLvl]);
		std::string strp6 = "需要转生次数：";
		strp6 += p6->getCString();
		CCPoint pos=ccp(SystemData::getLayoutPoint("Tips_e_label8_pos").x,SystemData::getLayoutPoint("Tips_e_label8_pos").y-m_icntEx*20);
		CCLabelTTF* zhuanshengLabel = CCLabelTTF::create(AToU8(strp6.c_str()), "", 15);
		// 转生次数不足显示红色
		if (userItem->data[ItemEquip::Item_RebornLvl]>HeroData::getProp(Entity::attr_reborn))
		{
			zhuanshengLabel->setColor(ccRED);
		}
		else
		{
			zhuanshengLabel->setColor(ccGREEN);
		}
		zhuanshengLabel->setAnchorPoint(CCPointZero);
		zhuanshengLabel->setPosition(pos);
		addChild(zhuanshengLabel);
		m_icntEx++;
	}

	// 显示价格（商店界面专用）//摆摊界面
	if (type == TAG_Tips_XJQX || type == TAG_Tips_GMQX)
	{
		std::string moneytype;
		if ( userItem->data[ItemEquip::Item_Market_Type]==Entity::attr_gold)
		{
			moneytype="元宝";
		}
		else if ( userItem->data[ItemEquip::Item_Market_Type]==Entity::attr_diamond)//仙玉
		{
			moneytype="仙玉";
		}
		CCString* ppricestr=CCString::createWithFormat("%d %s",userItem->data[ItemEquip::Item_Market_Price],moneytype.c_str());
		std::string strppricestr = "价格：";
		strppricestr += ppricestr->getCString();
		CCLabelTTF* pPriceLabel = CCLabelTTF::create(AToU8(strppricestr.c_str()), "", 15);
		pPriceLabel->setAnchorPoint(CCPointZero);
		pPriceLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label8_pos").x,SystemData::getLayoutPoint("Tips_e_label8_pos").y-m_icntEx*20));
		pPriceLabel->setColor(ccRED);
		addChild(pPriceLabel);
		m_icntEx++;
	}

	// 显示装备时限
	int a = userItem->data[ItemEquip::Item_GetTime];
	if (a != 0)
	{
		int curtime = ActivityData::getWorldTime();
		int b = a - curtime;
		CCLabelTTF* l_timelabel0 = SystemData::getLabelTTF("timelimitgift.label.timelimit");
		CCLabelTTF* l_timelabel=CCLabelTTF::create(StringUtils::timeToString(b,TimeType::dh).c_str(),"",15);
		l_timelabel0->setColor(ccYELLOW);
		l_timelabel0->setAnchorPoint(CCPointZero);
		l_timelabel->setAnchorPoint(CCPointZero);
		l_timelabel0->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label8_pos").x,SystemData::getLayoutPoint("Tips_e_label8_pos").y-m_icntEx*20));
		l_timelabel->setPosition(ccp(l_timelabel0->getPositionX()+l_timelabel0->getContentSize().width+10,l_timelabel0->getPositionY()));
		addChild(l_timelabel0);
		addChild(l_timelabel);
		m_icntEx++;
	}
	
	// 添加分割线
	CCSprite* pLine=SystemData::getSpriteByPlist("Tips_xinxigetiao");
	pLine->setPosition(ccp(SystemData::getLayoutPoint("Tips_line_pos_e").x,SystemData::getLayoutPoint("Tips_line_pos_e").y-m_icntEx*20));
	addChild(pLine);

	// 添加装备属性信息
	CCLayer *pLayer=getEquipInfo(userItem,m_icntEx);
	pLayer->setPosition(SystemData::getLayoutPoint("Tips_info_pos_e"));
	addChild(pLayer);

	// 添加装备图标背景
	CCSprite* psprite=SystemData::getSpriteByPlist("ui.bag.slot.unlock");
	psprite->setPosition(SystemData::getLayoutPoint("Tips_icon_pos_e"));
	psprite->setScale(0.7f);
	addChild(psprite);

	// 创建菜单和按钮
	CCMenu* pMenu=CCMenu::create();
	pMenu->setTouchPriority(kCCMenuHandlerPriority-2);
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);
	addChild(pMenu);

	// 显示转生钻石图标
	int i=userItem->data[ItemEquip::Item_RebornLvl];
	if(i>=5)//5
	{
		i = 5;//5
	}
	CCPoint pos=ccp(SystemData::getLayoutPoint("pMenu").x,SystemData::getLayoutPoint("Tips_e_label3_pos").y);
	for (int n=0;n<i;n++)
	{
		CCSprite* pDiamond=SystemData::getSpriteByPlist("Tips_diamond2");
		pDiamond->setAnchorPoint(CCPointZero);
		pDiamond->setScale(0.7f);
		pDiamond->setPosition(ccp(pos.x+n*8 +20, pos.y+25));
		addChild(pDiamond);
	}

	// 添加装备图标
	CCMenuItemImage* icon=CommonFunction::getItemIconButDelete(CommonFunction::createNewItem(userItem->sid),false);	
	icon->setPosition(SystemData::getLayoutPoint("Tips_icon_pos_e"));	
	icon->setScale(0.7f);
	pMenu->addChild(icon);

	// 添加关闭按钮（如果需要）
	if (flag)
	{
		CCMenuItemImage* pClose=SystemData::getMenuItemImageByPlist("forging_close");
		pClose->setTarget(this,menu_selector(ItemTooltip::closeCallBack));
		pClose->setPosition(SystemData::getLayoutPoint("Tips_close_pos_e"));
		pClose->setScale(0.7f);
		pMenu->addChild(pClose);
	}

	// 设置其他功能按钮
	settingButton(pMenu,type);
}

/**
 * 初始化普通物品的提示框
 * 
 * @param type 提示框类型（用于区分不同界面调用）
 * @param flag 是否显示关闭按钮
 */
void ItemTooltip::initNormalItem(int type, bool flag)
{
    // 1. 创建主背景框
    m_pBkg = SystemData::getScale9SpriteByPlist(
        "Tips_waikuang",                                       // 背景图片资源名
        SystemData::getLayoutValue("Tips_size.w"),            // 宽度
        SystemData::getLayoutValue("Tips_size.h") - m_iH      // 高度（扣除偏移量）
    );
    m_pBkg->setAnchorPoint(CCPointZero);                     // 锚点设为左下角
    m_pBkg->setPosition(ccp(0, m_iH));                       // 设置位置
    addChild(m_pBkg, 0);                                      // 添加到当前节点，层级0
    
    // 记录背景框尺寸
    m_nWidth = m_pBkg->getContentSize().width;
    m_nHeight = m_pBkg->getContentSize().height;
    
    addCover(m_pBkg->getPosition());                         // 添加遮罩（可能用于触摸处理）
    this->setContentSize(CCSizeMake(m_nWidth, m_nHeight));   // 设置当前节点尺寸
    
    // 2. 创建内层背景框
    CCScale9Sprite* pBkg = SystemData::getScale9SpriteByPlist(
        "Tips_waikuang1",                                     // 内层背景图片
        SystemData::getLayoutValue("Tips_size.w") - 14,      // 宽度略小于外层
        SystemData::getLayoutValue("Tips_size.h") - 62       // 高度略小于外层
    );
    pBkg->setAnchorPoint(CCPointZero);
    pBkg->setPosition(ccp(7, 57));                           // 相对位置偏移
    addChild(pBkg, 0);
    
    // 3. 显示物品名称
    CCLabelTTF* nameLabel = CCLabelTTF::create(
        GameData::s_user->getUserItemData()->getItemName(userItem->sid).c_str(),  // 物品名称
        "",                                                                       // 字体文件（为空使用默认）
        17                                                                        // 字号
    );
    nameLabel->setAnchorPoint(CCPointZero);
    nameLabel->setPosition(SystemData::getLayoutPoint("Tips_label1_pos"));  // 预设位置
    addChild(nameLabel);
    
    // 4. 显示绑定状态
    int bindtype = userItem->data[ItemEquip::Item_Bind];  // 获取绑定类型
    std::string str;
    if (bindtype == ItemEquip::Item_Has_bind)            // 已绑定
    {
        str = "[已绑定]";
    }
    CCLabelTTF* bangdingLabel = CCLabelTTF::create(AToU8(str.c_str()), "", 15);  // UTF8转换
    bangdingLabel->setAnchorPoint(CCPointZero);
    bangdingLabel->setPosition(SystemData::getLayoutPoint("Tips_label2_pos"));
    addChild(bangdingLabel);
    
    // 5. 显示物品重量
    int itemweight;
    LuaData::getProp(LuaData::ITEM, userItem->sid, "weight", itemweight);  // 从Lua获取重量
    CCString* p3 = CCString::createWithFormat("%d", itemweight);
    std::string strp3 = "重量：";
    strp3 += p3->getCString();
    CCLabelTTF* zhongliangLabel = CCLabelTTF::create(AToU8(strp3.c_str()), "", 15);
    zhongliangLabel->setAnchorPoint(CCPointZero);
    zhongliangLabel->setPosition(SystemData::getLayoutPoint("Tips_label3_pos"));
    addChild(zhongliangLabel);
    
    // 6. 动态条件显示（职业、转生、经验玉等）
    int cntEx = 0;  // 额外信息计数器（用于纵向排列）
    
    // 职业限制
    if (userItem->profession != 0)
    {
        std::string strname = "";
        switch (userItem->profession)
        {
        case 1: strname = "战士"; break;
        case 2: strname = "法师"; break;
        case 3: strname = "道士"; break;
        default: break;
        }
        CCString* p6 = CCString::createWithFormat("%s", strname.c_str());
        std::string strp6 = "职业限制：";
        strp6 += p6->getCString();
        CCLabelTTF* zhuanshengLabel = CCLabelTTF::create(AToU8(strp6.c_str()), "", 15);
        
        // 根据当前职业是否符合条件设置文字颜色
        if (userItem->profession != GameData::s_user->m_pMainRole->mGhostJob)
        {
            zhuanshengLabel->setColor(ccRED);     // 不符合条件显示红色
        }
        else
        {
            zhuanshengLabel->setColor(ccGREEN);   // 符合条件显示绿色
        }
        zhuanshengLabel->setAnchorPoint(CCPointZero);
        zhuanshengLabel->setPosition(SystemData::getLayoutPoint("Tips_label4_pos"));
        addChild(zhuanshengLabel);
        cntEx++;  // 计数器递增
    }
    
    // 转生等级限制
    if (userItem->data[ItemEquip::Item_RebornLvl] != 0)
    {
        CCString* p4 = CCString::createWithFormat("%d", userItem->data[ItemEquip::Item_RebornLvl]);
        std::string strp4 = "需要转生次数：";
        strp4 += p4->getCString();
        CCLabelTTF* zhuanshengLabel = CCLabelTTF::create(AToU8(strp4.c_str()), "", 15);
        
        // 判断玩家转生等级是否满足
        if (userItem->data[ItemEquip::Item_RebornLvl] > HeroData::getProp(Entity::attr_reborn))
        {
            zhuanshengLabel->setColor(ccRED);
        }
        else
        {
            zhuanshengLabel->setColor(ccGREEN);
        }
        zhuanshengLabel->setAnchorPoint(CCPointZero);
        
        // 动态计算Y坐标位置
        if (cntEx == 0)
        {
            zhuanshengLabel->setPosition(SystemData::getLayoutPoint("Tips_label4_pos"));
        }
        else
        {
            zhuanshengLabel->setPosition(SystemData::getLayoutPoint("Tips_label5_pos"));
        }
        addChild(zhuanshengLabel);
        cntEx++;
    }
    
    // 经验玉特殊处理
    if (GameData::s_user->getUserItemData()->getItemType(userItem->sid) == ItemType_ExpJade && 
        GameData::s_user->getUserItemData()->getItemCate(userItem->sid) == ItemCate_Extension)
    {
        // 获取经验玉的最大经验值配置
        CCString* pStr = CCString::createWithFormat(SystemData::getLayoutString("Jade_").c_str(), userItem->sid);
        int maxexp = SystemData::getLayoutValue(pStr->getCString());
        int nowexp = userItem->data[ItemEquip::Item_ExpStore];
        
        CCString* pStr1 = CCString::createWithFormat(" %d/%d", nowexp, maxexp);
        std::string strpStr1 = "储存经验：";
        strpStr1 += pStr1->getCString();
        CCLabelTTF* p = CCLabelTTF::create(AToU8(strpStr1.c_str()), "", 15);
        p->setAnchorPoint(CCPointZero);
        p->setPosition(ccp(SystemData::getLayoutPoint("Tips_label4_pos").x, 
                          SystemData::getLayoutPoint("Tips_label4_pos").y - cntEx * 20));  // 每项间隔20像素
        addChild(p);
        cntEx++;
    }
    
    // 等级限制
    int lvl = 0;
    LuaData::getProp(LuaData::ITEM, userItem->sid, "req_level", lvl);
    if (lvl != 0)
    {
        CCString* pStr = CCString::createWithFormat("%d", lvl);
        std::string strpStr = "等级：";
        strpStr += pStr->getCString();
        CCLabelTTF* p = CCLabelTTF::create(AToU8(strpStr.c_str()), "", 15);
        p->setAnchorPoint(CCPointZero);
        p->setPosition(ccp(SystemData::getLayoutPoint("Tips_label4_pos").x, 
                          SystemData::getLayoutPoint("Tips_label4_pos").y - cntEx * 20));
        addChild(p);
        
        // 判断等级是否满足
        if (lvl > GameData::s_user->m_pMainRole->mLevel && HeroData::getProp(Entity::attr_reborn) == 0)
        {
            p->setColor(ccRED);
        }
        else
        {
            p->setColor(ccGREEN);
        }
        cntEx++;
    }
    
    // 7. 特殊类型显示（商店、拍卖行等）摆摊界面
    if (type == TAG_Tips_XJQX || type == TAG_Tips_GMQX)  // 商店或拍卖行界面
    {
        // 显示数量
        CCString* pcountstr = CCString::createWithFormat("%d", userItem->count);
        std::string strpcountstr = "数量：";
        strpcountstr += pcountstr->getCString();
        CCLabelTTF* pCountLabel = CCLabelTTF::create(AToU8(strpcountstr.c_str()), "", 15);
        pCountLabel->setAnchorPoint(CCPointZero);
        pCountLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_label4_pos").x, 
                                    SystemData::getLayoutPoint("Tips_label4_pos").y - cntEx * 20));
        pCountLabel->setColor(ccYELLOW);
        addChild(pCountLabel);
        cntEx++;
        
        // 显示价格
        std::string moneytype;
        if (userItem->data[ItemEquip::Item_Market_Type] == Entity::attr_gold)
        {
            moneytype = "元宝";
        }
        else if (userItem->data[ItemEquip::Item_Market_Type] == Entity::attr_diamond)//金币改仙玉
        {
            moneytype = "仙玉";
        }
        CCString* ppricestr = CCString::createWithFormat("%d %s", 
            userItem->data[ItemEquip::Item_Market_Price], moneytype.c_str());
        std::string strppricestr = "价格：";
        strppricestr += ppricestr->getCString();
        CCLabelTTF* pPriceLabel = CCLabelTTF::create(AToU8(strppricestr.c_str()), "", 15);
        pPriceLabel->setAnchorPoint(CCPointZero);
        pPriceLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_label4_pos").x, 
                                    SystemData::getLayoutPoint("Tips_label4_pos").y - cntEx * 20));
        pPriceLabel->setColor(ccRED);
        addChild(pPriceLabel);
        cntEx++;
    }
    
    // 8. 添加分割线
    CCSprite* pLine = SystemData::getSpriteByPlist("Tips_xinxigetiao");
    pLine->setPosition(ccp(SystemData::getLayoutPoint("Tips_line_pos").x, 
                          SystemData::getLayoutPoint("Tips_line_pos").y - cntEx * 20));
    addChild(pLine);
    
    // 9. 添加其他属性信息
    CCLayer* pLayer = getOtherInfo(userItem, cntEx);
    pLayer->setPosition(SystemData::getLayoutPoint("Tips_info_pos"));
    addChild(pLayer);
    
    // 10. 添加物品图标背景
    CCSprite* psprite = SystemData::getSpriteByPlist("ui.bag.slot.unlock");
    psprite->setPosition(SystemData::getLayoutPoint("Tips_icon_pos"));
    psprite->setScale(0.7f);
    addChild(psprite);
    
    // 11. 创建菜单容器
    CCMenu* pMenu = CCMenu::create();
    pMenu->setTouchPriority(kCCMenuHandlerPriority - 2);  // 设置触摸优先级
    pMenu->setPosition(CCPointZero);
    pMenu->setAnchorPoint(CCPointZero);
    addChild(pMenu);
    
    // 添加物品图标按钮
    CCMenuItemImage* icon = CommonFunction::getItemIconButDelete(
        CommonFunction::createNewItem(userItem->sid), false);
    icon->setPosition(SystemData::getLayoutPoint("Tips_icon_pos"));
    icon->setScale(0.7f);
    pMenu->addChild(icon);
    
    // 12. 根据flag决定是否添加关闭按钮
    if (flag)
    {
        CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("forging_close");
        pClose->setTarget(this, menu_selector(ItemTooltip::closeCallBack));  // 设置关闭回调
        pClose->setPosition(SystemData::getLayoutPoint("Tips_close_pos"));
        pClose->setScale(0.7f);
        pMenu->addChild(pClose);
    }
    
    // 13. 根据类型设置其他功能按钮
    settingButton(pMenu, type);
}

void ItemTooltip::initPetEggItem( int type,bool flag )
{
	m_pBkg=SystemData::getScale9SpriteByPlist("Tips_waikuang",SystemData::getLayoutValue("Tips_size_e.w"),SystemData::getLayoutValue("Tips_size_e.h")-m_iH);
	m_pBkg->setAnchorPoint(CCPointZero);
	m_pBkg->setPosition(ccp(0,m_iH));
	addChild(m_pBkg, 0);


	m_nWidth=m_pBkg->getContentSize().width;
	m_nHeight=m_pBkg->getContentSize().height;
	addCover(m_pBkg->getPosition());

	this->setContentSize(CCSizeMake(m_nWidth,m_nHeight));

	CCScale9Sprite* pBkg=SystemData::getScale9SpriteByPlist("Tips_waikuang1",SystemData::getLayoutValue("Tips_size_e.w")-14,SystemData::getLayoutValue("Tips_size_e.h")-62);
	pBkg->setPosition(ccp(7,57));
	pBkg->setAnchorPoint(CCPointZero);
	addChild(pBkg, 0);

	int itemsid = userItem->sid;
	UserPet* pPetEgg = GameData::s_user->getUserPetData()->getPetEggInfo(userItem->data[ItemEquip::Item_Link_Pet]);
	if (pPetEgg == NULL)
	{	
		CCLabelTTF* nameLabel = CCLabelTTF::create(GameData::s_user->getUserItemData()->getItemName(userItem->sid).c_str(),"",17);
		nameLabel->setAnchorPoint(CCPointZero);
		nameLabel->setPosition(SystemData::getLayoutPoint("Tips_e_label1_pos"));
		addChild(nameLabel);	
	}
	else
	{	
		std::string petname;
		LuaData::getProp(LuaData::PET,pPetEgg->sid,"name",petname);
		CCString* pstrname = CCString::createWithFormat("%s%s",SystemData::getLayoutString("PetEgg_Name").c_str(),petname.c_str());
		CCLabelTTF* nameLabel = CCLabelTTF::create(pstrname->getCString(),"",17);
		nameLabel->setAnchorPoint(CCPointZero);
		nameLabel->setPosition(SystemData::getLayoutPoint("Tips_e_label1_pos"));
		addChild(nameLabel);

		int eggid = 0;
		LuaData::getProp(LuaData::PET,pPetEgg->sid,"eggid",eggid);
		if(eggid!=0)
		{
			itemsid = eggid;
		}
	}
	

	int bindtype=userItem->data[ItemEquip::Item_Bind]; 
	std::string str; 
	if (bindtype==ItemEquip::Item_Has_bind)
	{
		str="[已绑定]"; 
	}
	CCLabelTTF* bangdingLabel=CCLabelTTF::create(AToU8(str.c_str()),"",15);
	bangdingLabel->setAnchorPoint(CCPointZero);
	bangdingLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label2_pos").x,SystemData::getLayoutPoint("Tips_e_label2_pos").y-m_icntEx*20));
	addChild(bangdingLabel);


	int itemweight;
	LuaData::getProp(LuaData::ITEM,userItem->sid,"weight",itemweight);
	CCString* p3=CCString::createWithFormat("%d",itemweight);
	std::string strp3 = "重量：";
	strp3 += p3->getCString();
	CCLabelTTF* zhongliangLabel = CCLabelTTF::create(AToU8(strp3.c_str()), "", 15);
	zhongliangLabel->setAnchorPoint(CCPointZero);
	zhongliangLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label3_pos").x,SystemData::getLayoutPoint("Tips_e_label3_pos").y-m_icntEx*20));
	//zhongliangLabel->setPosition(SystemData::getLayoutPoint("Tips_e_label5_pos"));
	addChild(zhongliangLabel);

	int itemlvl = 0;
	if (pPetEgg)
	{
		itemlvl = pPetEgg->lvl;
	}
	CCString* p4=CCString::createWithFormat("%d",itemlvl);
	std::string strp4 = "当前宠物等级：";
	strp4 += p4->getCString();
	CCLabelTTF* petlvlLabel = CCLabelTTF::create(AToU8(strp4.c_str()), "", 15);
	if (itemlvl>GameData::s_user->m_pMainRole->mLevel)
	{
		petlvlLabel->setColor(ccRED);
	}
	else
	{
		petlvlLabel->setColor(ccGREEN);
	}
	petlvlLabel->setAnchorPoint(CCPointZero);
	petlvlLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label5_pos").x,SystemData::getLayoutPoint("Tips_e_label5_pos").y-m_icntEx*20));
	//dengjiLabel->setPosition(SystemData::getLayoutPoint("Tips_e_label7_pos"));
	addChild(petlvlLabel);

	int itemreq_lvl;
	LuaData::getProp(LuaData::ITEM,itemsid,"req_level",itemreq_lvl);
	CCString* p5=CCString::createWithFormat("%d",itemreq_lvl);
	std::string strp5 = "等级：";
	strp5 += p5->getCString();
	CCLabelTTF* dengjiLabel = CCLabelTTF::create(AToU8(strp5.c_str()), "", 15);
	if (itemreq_lvl>GameData::s_user->m_pMainRole->mLevel)
	{
		dengjiLabel->setColor(ccRED);
	}
	else
	{
		dengjiLabel->setColor(ccGREEN);
	}
	dengjiLabel->setAnchorPoint(CCPointZero);
	dengjiLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label7_pos").x,SystemData::getLayoutPoint("Tips_e_label7_pos").y-m_icntEx*20));
	//dengjiLabel->setPosition(SystemData::getLayoutPoint("Tips_e_label7_pos"));
	addChild(dengjiLabel);

	
	if (userItem->data[ItemEquip::Item_RebornLvl]!=0)
	{
		CCString* p6=CCString::createWithFormat("%d",userItem->data[ItemEquip::Item_RebornLvl]);
		std::string strp6 = "需要转生次数：";
		strp6 += p6->getCString();
		CCPoint pos=ccp(SystemData::getLayoutPoint("Tips_e_label8_pos").x,SystemData::getLayoutPoint("Tips_e_label8_pos").y-m_icntEx*20);
		CCLabelTTF* zhuanshengLabel = CCLabelTTF::create(AToU8(strp6.c_str()), "", 15);
		if (userItem->data[ItemEquip::Item_RebornLvl]>HeroData::getProp(Entity::attr_reborn))
		{
			zhuanshengLabel->setColor(ccRED);
		}
		else
		{
			zhuanshengLabel->setColor(ccGREEN);
		}
		zhuanshengLabel->setAnchorPoint(CCPointZero);
		zhuanshengLabel->setPosition(pos);

		addChild(zhuanshengLabel);
		m_icntEx++;
	}

	if (type == TAG_Tips_XJQX || type == TAG_Tips_GMQX)
	{
		std::string moneytype;
		if ( userItem->data[ItemEquip::Item_Market_Type]==Entity::attr_gold)
		{
			moneytype="元宝";
		}
		else if ( userItem->data[ItemEquip::Item_Market_Type]==Entity::attr_diamond)//金币改仙玉
		{
			moneytype="仙玉";
		}
		CCString* ppricestr=CCString::createWithFormat("%d %s",userItem->data[ItemEquip::Item_Market_Price],moneytype.c_str());
		std::string strppricestr = "价格：";
		strppricestr += ppricestr->getCString();
		CCLabelTTF* pPriceLabel = CCLabelTTF::create(AToU8(strppricestr.c_str()), "", 15);
		pPriceLabel->setAnchorPoint(CCPointZero);
		pPriceLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label8_pos").x,SystemData::getLayoutPoint("Tips_e_label8_pos").y-m_icntEx*20));
		pPriceLabel->setColor(ccYELLOW);
		addChild(pPriceLabel);
		m_icntEx++;
	}

	//分割线
	CCSprite* pLine=SystemData::getSpriteByPlist("Tips_xinxigetiao");
	pLine->setPosition(ccp(SystemData::getLayoutPoint("Tips_line_pos_e").x,SystemData::getLayoutPoint("Tips_line_pos_e").y-m_icntEx*20));
	addChild(pLine); 

	CCLayer *pLayer=getPetEggInfo(userItem,m_icntEx);
	pLayer->setPosition(SystemData::getLayoutPoint("Tips_info_pos_e"));
	addChild(pLayer);

	CCSprite* psprite=SystemData::getSpriteByPlist("ui.bag.slot.unlock");
	psprite->setPosition(SystemData::getLayoutPoint("Tips_icon_pos_e"));
	psprite->setScale(0.7f);
	addChild(psprite);

	//按钮加载 
	CCMenu* pMenu=CCMenu::create();
	pMenu->setTouchPriority(kCCMenuHandlerPriority-2);
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);
	addChild(pMenu);


	CCMenuItemImage* icon=CommonFunction::getItemIconButDelete(CommonFunction::createNewItem(itemsid),false);	
	icon->setPosition(SystemData::getLayoutPoint("Tips_icon_pos_e"));	
	icon->setScale(0.7f);
	pMenu->addChild(icon);

	if (flag)
	{
		CCMenuItemImage* pClose=SystemData::getMenuItemImageByPlist("forging_close"); 
		pClose->setTarget(this,menu_selector(ItemTooltip::closeCallBack));
		pClose->setPosition(SystemData::getLayoutPoint("Tips_close_pos_e"));
		pClose->setScale(0.7f);
		pMenu->addChild(pClose);
	}

	settingButton(pMenu,type);
}

CCLayer* ItemTooltip::getPetEggInfoLayer( UserItem* item )
{
	int linkid = 0;

	Lua::instance()->push(item->sid);		
	if(	Lua::instance()->call("ItemCheckPetDesc", 1, 1) &&  
		Lua::instance()->pop(linkid))
	if (linkid==0)
	{
		linkid = item->data[ItemEquip::Item_Link_Pet];
	}
	UserPet* pPetEgg = GameData::s_user->getUserPetData()->getPetEggInfo(linkid);
	if (pPetEgg == NULL)
	{
		CCLayer *pLayer=CCLayer::create();
		return pLayer;
	}
	return getPetEggInfoLayerbyPet(pPetEgg);
}

CCLayer* ItemTooltip::getPetEggInfo( UserItem* item,int cntEx/*=0*/ )
{
	int h=cntEx*20;
	CCLayer *player=CCLayer::create();
	CCTableViewEx* pTabelView = CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("Tips_tabelview_size_e").width,SystemData::getLayoutSize("Tips_tabelview_size_e").height-h),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(CCPointZero);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	player->addChild(pTabelView);	
	return player;
}

CCLayer* ItemTooltip::getPetHeadInfo( UserPet* pPet,int cntEx/*=0*/ )
{
	int h=cntEx*20;
	CCLayer *player=CCLayer::create();
	CCTableViewEx* pTabelView = CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("Tips_tabelview_size_e").width,SystemData::getLayoutSize("Tips_tabelview_size_e").height-h),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(CCPointZero);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	player->addChild(pTabelView);	
	return player;
}CCLayer* ItemTooltip::getPetEggInfoLayerbyPet( UserPet* pPetEgg )
{
	CCLayer *pLayer=CCLayer::create();
	//物品描述
	CCPoint pos=ccp(15,0);
	CCLabelTTF* ptitle1=CCLabelTTF::create(SystemData::getLayoutString("ItemTips_JCSX").c_str(),"",15);
	ptitle1->setAnchorPoint(CCPointZero);
	ptitle1->setPosition(ccp(pos.x-5,pos.y-20));
	ptitle1->setColor(ccORANGE);
	pos=ptitle1->getPosition();
	pLayer->addChild(ptitle1);
	mHeight+=ptitle1->getContentSize().height;

	std::string strtype[7] = {"生命值上限","魔法值上限","最大物理攻击","最大魔法攻击","最大道术攻击","最大物理防御","最大魔法防御"};
	int type[7] = {Combat::prop_Curse,Combat::prop_MPMax,Combat::prop_PATK_Max,Combat::prop_MATK_Max,Combat::prop_TATK_Max,Combat::prop_PDEF_Max,Combat::prop_MDEF_Max};	
	//ccColor3B color=ccRED;

	for (int i = 0;i<7;i++)
	{
		int data = pPetEgg->data[type[i]];
		CCString* pStr = CCString::createWithFormat("%s:%d",strtype[i].c_str(),data);
		CCLabelTTF* plabel=CCLabelTTF::create(AToU8(pStr->getCString()),"",15);
		plabel->setAnchorPoint(CCPointZero);
		plabel->setPosition(ccp(pos.x+10,pos.y-20));
		plabel->setColor(ccYELLOW);
		pos=ccp(pos.x,plabel->getPositionY());
		pLayer->addChild(plabel);
		mHeight+=plabel->getContentSize().height;
	}

	/*CCLabelTTF* ptitle0=CCLabelTTF::create(AToU8("特有属性:"),"",15);
	ptitle0->setAnchorPoint(CCPointZero);
	ptitle0->setPosition(ccp(pos.x,pos.y-20));
	ptitle0->setColor(ccORANGE);
	pos=ptitle0->getPosition();
	pLayer->addChild(ptitle0);
	mHeight+=ptitle0->getContentSize().height;

	//宠物特性
	int characterid = 0;
	int petsid = pPetEgg->sid;
	LuaData::getProp("gdPets",petsid,"character",characterid);
	int charactercount = 0;
	LuaData::getProp_size("gdPetCharacter",characterid,"",charactercount);
	for (int i = 1;i<=charactercount;i++)
	{
		int type=0;
		int data = 0;
		LuaData::getProp("gdPetCharacter",characterid,i,"type",type);
		LuaData::getProp("gdPetCharacter",characterid,i,"data",data); 
		std::string name;
		LuaData::getProp("attr_type_to_name",type,name); 
		CCString* pStr ;
		if (data==0)
		{
			data = pPetEgg->exdata[Entity::attr_pet_character_begin+i-1];
			if (data==0)
			{
				pStr = CCString::createWithFormat("%s:???",name.c_str());
			}
			else
			{
				if (type==Combat::prop_Death_Recovery_Percent || type==Combat::prop_Health_Recovery_Point || type==Combat::prop_Magic_Recovery_Point || type==Combat::prop_Posion_Recovery_Point || type==Combat::prop_Magic_Hit|| type==Combat::prop_Magic_Dodge || type==Combat::prop_Posion_Dodge)
				{
					float dataf=(float)data/100;
					pStr=CCString::createWithFormat("%s:%.2f%% ",name.c_str(),dataf);
				}
				else
				{
					pStr = CCString::createWithFormat("%s:%d",name.c_str(),data);
				}
			}
		}
		else
		{
			if (type==Combat::prop_Death_Recovery_Percent || type==Combat::prop_Health_Recovery_Point || type==Combat::prop_Magic_Recovery_Point || type==Combat::prop_Posion_Recovery_Point || type==Combat::prop_Magic_Hit|| type==Combat::prop_Magic_Dodge || type==Combat::prop_Posion_Dodge)
			{
				float dataf=(float)data/100;
				pStr=CCString::createWithFormat("%s:%.2f%% ",name.c_str(),dataf);
			}
			else
			{
				pStr = CCString::createWithFormat("%s:%d",name.c_str(),data);
			}
		}
			
		CCLabelTTF* plabel=CCLabelTTF::create(pStr->getCString(),"",15);
		plabel->setAnchorPoint(CCPointZero);
		plabel->setPosition(ccp(pos.x+10,pos.y-20));
		plabel->setColor(ccYELLOW);
		pos=ccp(pos.x,plabel->getPositionY());
		pLayer->addChild(plabel);
		mHeight+=plabel->getContentSize().height;
	}*/


	CCLabelTTF* ptitle2=CCLabelTTF::create(AToU8("进阶属性:"),"",15);
	ptitle2->setAnchorPoint(CCPointZero);
	ptitle2->setPosition(ccp(pos.x,pos.y-20));
	ptitle2->setColor(ccORANGE);
	pos=ptitle2->getPosition();
	pLayer->addChild(ptitle2);
	mHeight+=ptitle2->getContentSize().height;

	int attrcnt = GameData::s_user->getUserPetData()->getPetAdvanceCnt(pPetEgg);

	for (int i = 0;i<attrcnt;i++)
	{
		int advancetype = pPetEgg->exdata[Entity::attr_pet_ex_prop_type];

		int c=(int)((int)advancetype >> (8*i) & 255);
		if(c!=0)
		{
			int type=c;
			std::string name;
			LuaData::getProp("attr_type_to_name",c,name);
			int data = pPetEgg->exdata[Entity::attr_pet_ex_prop_type+attrcnt-i];
			float combovalue;
			CCString* pStr;
			if (type==Combat::prop_Death_Recovery_Percent || type==Combat::prop_Health_Recovery_Point || type==Combat::prop_Magic_Recovery_Point || type==Combat::prop_Posion_Recovery_Point || type==Combat::prop_Magic_Hit|| type==Combat::prop_Magic_Dodge || type==Combat::prop_Posion_Dodge)
			{
				combovalue=(float)data;
				combovalue=combovalue/100;
				pStr=CCString::createWithFormat("%s:+%.2f%%",name.c_str(),combovalue);
			}
			else
			{
				pStr=CCString::createWithFormat("%s:+%d",name.c_str(),data);
			}

			CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"",18);
			pLabel->setPosition(ccp(pos.x+10,pos.y-20));
			pos=ccp(pos.x,pLabel->getPositionY());
			pLabel->setAnchorPoint(CCPointZero);
			pLayer->addChild(pLabel);
			mHeight+=pLabel->getContentSize().height;
		}	
	}

	for (int i = attrcnt;i<3;i++)
	{
		CCLabelTTF* pLabel=SystemData::getLabelTTF("ui_petadvance_text4");
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLabel->setAnchorPoint(CCPointZero);
		pLabel->setColor(ccWHITE);
		pLabel->setPosition(ccp(pos.x+10,pos.y-20));
		pos=ccp(pos.x,pLabel->getPositionY());
		pLabel->setFontSize(18);
		pLayer->addChild(pLabel);
		mHeight+=pLabel->getContentSize().height;
	}

	CCLabelTTF* ptitle3=CCLabelTTF::create(SystemData::getLayoutString("ItemTips_JPSX").c_str(),"",15);
	ptitle3->setAnchorPoint(CCPointZero);
	//ptitle5->setPosition(ccp(pos.x,pos.y-20));
	ptitle3->setColor(ccORANGE);
	ptitle3->setPosition(ccp(pos.x,pos.y-20));
	pos=ptitle3->getPosition();
	pLayer->addChild(ptitle3);
	mHeight+=ptitle3->getContentSize().height;

	int specialattr = pPetEgg->exdata[Entity::attr_pet_top_prop_type];
	int specialdata = pPetEgg->exdata[Entity::attr_pet_top_prop];
	if (specialattr!=0)
	{
		std::string name;
		LuaData::getProp("attr_type_to_name",specialattr,name);
		CCString* pStr=CCString::createWithFormat("%s : + %d ",name.c_str(),specialdata);
		CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"",15);
		pLabel->setPosition(ccp(pos.x+10,pos.y-20));
		pos=ccp(pos.x,pLabel->getPositionY());
		pLabel->setAnchorPoint(CCPointZero);
		pLayer->addChild(pLabel);
		mHeight+=pLabel->getContentSize().height;
	}
	else
	{
		CCLabelTTF* pLabel=SystemData::getLabelTTF("ui_petadvance_text4");
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLabel->setAnchorPoint(CCPointZero);
		pLabel->setColor(ccWHITE);
		pLabel->setPosition(ccp(pos.x+10,pos.y-20));
		pos=ccp(pos.x,pLabel->getPositionY());
		pLabel->setFontSize(18);
		pLayer->addChild(pLabel);
		mHeight+=pLabel->getContentSize().height;
	}

	mHeight+=70;
	return pLayer; 
}


/**
 * 初始化宠物头部信息工具提示界面
 * @param u_pet 用户宠物数据指针
 * @return 返回创建的图层
 */
CCLayer* ItemTooltip::initPetHeadItem(UserPet* u_pet)
{
    // 1. 创建背景框
    // 获取缩放九宫格背景精灵，使用指定尺寸
    m_pBkg = SystemData::getScale9SpriteByPlist("Tips_waikuang", 
              SystemData::getLayoutValue("Tips_size_e.w"), 
              SystemData::getLayoutValue("Tips_size_e.h") - m_iH + 60);
    m_pBkg->setAnchorPoint(CCPointZero);  // 设置锚点为左下角
    m_pBkg->setPosition(ccp(0, m_iH - 60));  // 设置位置
    addChild(m_pBkg, 0);  // 添加到当前节点

    // 记录背景框尺寸
    m_nWidth = m_pBkg->getContentSize().width;
    m_nHeight = m_pBkg->getContentSize().height;
    addCover(m_pBkg->getPosition());  // 添加遮罩
    this->setContentSize(CCSizeMake(m_nWidth, m_nHeight));  // 设置内容尺寸

    // 2. 创建内层背景
    CCScale9Sprite* pBkg = SystemData::getScale9SpriteByPlist("Tips_waikuang1", 
                          SystemData::getLayoutValue("Tips_size_e.w") - 14, 
                          SystemData::getLayoutValue("Tips_size_e.h") - 62 + 60);
    pBkg->setPosition(ccp(7, 57 - 60));  // 设置位置
    pBkg->setAnchorPoint(CCPointZero);  // 设置锚点
    addChild(pBkg, 0);  // 添加到当前节点

    // 3. 添加分割线
    CCSprite* pLine = SystemData::getSpriteByPlist("Tips_xinxigetiao");
    pLine->setPosition(ccp(SystemData::getLayoutPoint("Tips_line_pos_e").x, 
                          SystemData::getLayoutPoint("Tips_line_pos_e").y - m_icntEx * 20));
    addChild(pLine);

    // 4. 创建图标背景
    CCSprite* psprite = SystemData::getSpriteByPlist("ui.bag.slot.unlock");
    psprite->setPosition(SystemData::getLayoutPoint("Tips_icon_pos_e"));  // 设置位置
    psprite->setScale(0.7f);  // 缩放
    addChild(psprite);

    // 5. 创建菜单
    CCMenu* pMenu = CCMenu::create();
    pMenu->setTouchPriority(kCCMenuHandlerPriority - 2);  // 设置触摸优先级
    pMenu->setPosition(CCPointZero);  // 设置位置
    pMenu->setAnchorPoint(CCPointZero);  // 设置锚点
    addChild(pMenu);  // 添加到当前节点

    // 6. 获取宠物头像ID
    int headid = 0;
    LuaData::getProp("gdPets", u_pet->sid, "headImageID_n", headid);  // 默认头像ID
    
    // 根据转生等级使用特殊头像
    int rebornLV = 0;
    rebornLV = u_pet->exdata[Entity::attr_pet_reborn_cnt];  // 获取转生次数
    if (rebornLV > 0)  // 如果已转生
    {
        LuaData::getProp("gdPets", u_pet->sid, "headImageID_s", headid);  // 使用转生头像
    }
    
    // 创建宠物头像按钮
    CCMenuItemImage* icon = CommonFunction::getItemIconButDelete(CommonFunction::createNewItem(headid), false);
    icon->setPosition(SystemData::getLayoutPoint("Tips_icon_pos_e"));  // 设置位置
    icon->setScale(0.7f);  // 缩放
    pMenu->addChild(icon);  // 添加到菜单

    // 7. 创建关闭按钮
    CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("forging_close");
    pClose->setTarget(this, menu_selector(ItemTooltip::closeCallBack));  // 设置回调
    pClose->setPosition(SystemData::getLayoutPoint("Tips_close_pos_e"));  // 设置位置
    pClose->setScale(0.7f);  // 缩放
    pMenu->addChild(pClose);  // 添加到菜单

    // 8. 显示宠物名称
    std::string petName;
    LuaData::getProp("gdPets", u_pet->sid, "name", petName);  // 获取宠物名称
    CCLabelTTF* nameLabel = CCLabelTTF::create(petName.c_str(), "", 17);  // 创建标签
    nameLabel->setAnchorPoint(CCPointZero);  // 设置锚点
    nameLabel->setPosition(SystemData::getLayoutPoint("Tips_e_label1_pos"));  // 设置位置
    addChild(nameLabel);  // 添加到当前节点

    // 9. 显示宠物等级
    CCString* p4 = NULL;
    if (rebornLV > 0)  // 如果已转生
    {
        p4 = CCString::createWithFormat("当前宠物等级：%d转%d级", rebornLV, u_pet->lvl);
    }
    else
    {
        p4 = CCString::createWithFormat("当前宠物等级：%d", u_pet->lvl);
    }
    
    CCLabelTTF* petlvlLabel = CCLabelTTF::create(AToU8(p4->getCString()), "", 15);
    petlvlLabel->setColor(ccGREEN);  // 设置颜色为绿色
    petlvlLabel->setAnchorPoint(CCPointZero);  // 设置锚点
    petlvlLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label5_pos").x, 
                                SystemData::getLayoutPoint("Tips_e_label5_pos").y - m_icntEx * 20));
    addChild(petlvlLabel);  // 添加到当前节点

    // 10. 显示需求等级
    int itemreq_lvl;
    LuaData::getProp(LuaData::ITEM, u_pet->sid, "req_level", itemreq_lvl);  // 获取需求等级
    CCString* p5 = CCString::createWithFormat("等级：%d", itemreq_lvl);
    CCLabelTTF* dengjiLabel = CCLabelTTF::create(AToU8(p5->getCString()), "", 15);
    
    // 根据玩家等级设置颜色
    if (itemreq_lvl > GameData::s_user->m_pMainRole->mLevel)  // 需求等级高于玩家等级
    {
        dengjiLabel->setColor(ccRED);  // 红色表示未达到
    }
    else
    {
        dengjiLabel->setColor(ccGREEN);  // 绿色表示已达到
    }
    
    dengjiLabel->setAnchorPoint(CCPointZero);  // 设置锚点
    dengjiLabel->setPosition(ccp(SystemData::getLayoutPoint("Tips_e_label7_pos").x, 
                                 SystemData::getLayoutPoint("Tips_e_label7_pos").y - m_icntEx * 20));
    addChild(dengjiLabel);  // 添加到当前节点

    // 11. 创建属性显示层
    CCLayer* pLayer = CCLayer::create();  // 创建新图层
    addChild(pLayer);  // 添加到当前节点

    // 12. 显示基础属性标题
    CCPoint pos = ccp(15, 305);
    CCLabelTTF* ptitle1 = CCLabelTTF::create(SystemData::getLayoutString("ItemTips_JCSX").c_str(), "", 15);
    ptitle1->setAnchorPoint(CCPointZero);  // 设置锚点
    ptitle1->setPosition(ccp(pos.x - 5, pos.y - 20));  // 设置位置
    ptitle1->setColor(ccORANGE);  // 设置颜色为橙色
    pos = ptitle1->getPosition();  // 更新位置
    pLayer->addChild(ptitle1);  // 添加到图层
    mHeight += ptitle1->getContentSize().height;  // 累加高度

    // 13. 显示基础属性
    std::string strtype[7] = {"生命值上限", "魔法值上限", "最大物理攻击", "最大魔法攻击", 
                               "最大道术攻击", "最大物理防御", "最大魔法防御"};
    int type[7] = {Combat::prop_MPMax, Combat::prop_MPMax, Combat::prop_PATK_Max, 
                   Combat::prop_MATK_Max, Combat::prop_TATK_Max, Combat::prop_PDEF_Max, 
                   Combat::prop_MDEF_Max};
    
    for (int i = 0; i < 7; i++)
    {
        int data = u_pet->data[type[i]];  // 获取属性值
        CCString* pStr = CCString::createWithFormat("%s:%d", strtype[i].c_str(), data);
        CCLabelTTF* plabel = CCLabelTTF::create(AToU8(pStr->getCString()), "", 15);
        plabel->setAnchorPoint(CCPointZero);  // 设置锚点
        plabel->setPosition(ccp(pos.x + 10, pos.y - 20));  // 设置位置
        plabel->setColor(ccYELLOW);  // 设置颜色为黄色
        pos = ccp(pos.x, plabel->getPositionY());  // 更新位置
        addChild(plabel);  // 添加到当前节点
        mHeight += plabel->getContentSize().height;  // 累加高度
    }

    // 14. 显示进阶属性标题
    CCLabelTTF* ptitle2 = CCLabelTTF::create(AToU8("进阶属性:"), "", 15);
    ptitle2->setAnchorPoint(CCPointZero);  // 设置锚点
    ptitle2->setPosition(ccp(pos.x, pos.y - 20));  // 设置位置
    ptitle2->setColor(ccORANGE);  // 设置颜色为橙色
    pos = ptitle2->getPosition();  // 更新位置
    pLayer->addChild(ptitle2);  // 添加到图层
    mHeight += ptitle2->getContentSize().height;  // 累加高度

    // 15. 显示进阶属性
    int attrcnt = GameData::s_user->getUserPetData()->getPetAdvanceCnt(u_pet);  // 获取进阶属性数量
    
    for (int i = 0; i < attrcnt; i++)
    {
        int advancetype = u_pet->exdata[Entity::attr_pet_ex_prop_type];  // 获取进阶属性类型
        int c = (int)((int)advancetype >> (8 * i) & 255);  // 提取属性类型
        
        if (c != 0)  // 如果有该属性
        {
            int type = c;  // 属性类型
            std::string name;
            LuaData::getProp("attr_type_to_name", c, name);  // 获取属性名称
            int data = u_pet->exdata[Entity::attr_pet_ex_prop_type + attrcnt - i];  // 获取属性值
            
            float combovalue;
            CCString* pStr;
            
            // 根据属性类型格式化显示
            if (type == Combat::prop_Death_Recovery_Percent || 
                type == Combat::prop_Health_Recovery_Point || 
                type == Combat::prop_Magic_Recovery_Point || 
                type == Combat::prop_Posion_Recovery_Point || 
                type == Combat::prop_Magic_Hit || 
                type == Combat::prop_Magic_Dodge || 
                type == Combat::prop_Posion_Dodge)
            {
                // 百分比属性
                combovalue = (float)data;
                combovalue = combovalue / 100;
                pStr = CCString::createWithFormat("%s:+%.2f%%", name.c_str(), combovalue);
            }
            else
            {
                // 数值属性
                pStr = CCString::createWithFormat("%s:+%d", name.c_str(), data);
            }
            
            CCLabelTTF* pLabel = CCLabelTTF::create(pStr->getCString(), "", 18);
            pLabel->setPosition(ccp(pos.x + 10, pos.y - 20));  // 设置位置
            pos = ccp(pos.x, pLabel->getPositionY());  // 更新位置
            pLabel->setAnchorPoint(CCPointZero);  // 设置锚点
            pLayer->addChild(pLabel);  // 添加到图层
            mHeight += pLabel->getContentSize().height;  // 累加高度
        }
    }
    
    // 16. 显示未开启的进阶属性槽
    for (int i = attrcnt; i < 3; i++)
    {
        CCLabelTTF* pLabel = SystemData::getLabelTTF("ui_petadvance_text4");  // 获取默认文本
        pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);  // 设置左对齐
        pLabel->setAnchorPoint(CCPointZero);  // 设置锚点
        pLabel->setColor(ccWHITE);  // 设置颜色为白色
        pLabel->setPosition(ccp(pos.x + 10, pos.y - 20));  // 设置位置
        pos = ccp(pos.x, pLabel->getPositionY());  // 更新位置
        pLabel->setFontSize(18);  // 设置字体大小
        pLayer->addChild(pLabel);  // 添加到图层
        mHeight += pLabel->getContentSize().height;  // 累加高度
    }

    // 17. 显示极品属性标题
    CCLabelTTF* ptitle3 = CCLabelTTF::create(SystemData::getLayoutString("ItemTips_JPSX").c_str(), "", 15);
    ptitle3->setAnchorPoint(CCPointZero);  // 设置锚点
    ptitle3->setColor(ccORANGE);  // 设置颜色为橙色
    ptitle3->setPosition(ccp(pos.x, pos.y - 20));  // 设置位置
    pos = ptitle3->getPosition();  // 更新位置
    pLayer->addChild(ptitle3);  // 添加到图层
    mHeight += ptitle3->getContentSize().height;  // 累加高度

    // 18. 显示极品属性
    int specialattr = u_pet->exdata[Entity::attr_pet_top_prop_type];  // 获取极品属性类型
    int specialdata = u_pet->exdata[Entity::attr_pet_top_prop];  // 获取极品属性值
    
    if (specialattr != 0)  // 如果有极品属性
    {
        std::string name;
        LuaData::getProp("attr_type_to_name", specialattr, name);  // 获取属性名称
        CCString* pStr = CCString::createWithFormat("%s : + %d ", name.c_str(), specialdata);
        CCLabelTTF* pLabel = CCLabelTTF::create(pStr->getCString(), "", 15);
        pLabel->setPosition(ccp(pos.x + 10, pos.y - 20));  // 设置位置
        pos = ccp(pos.x, pLabel->getPositionY());  // 更新位置
        pLabel->setAnchorPoint(CCPointZero);  // 设置锚点
        pLayer->addChild(pLabel);  // 添加到图层
        mHeight += pLabel->getContentSize().height;  // 累加高度
    }
    else
    {
        // 显示未开启的极品属性槽
        CCLabelTTF* pLabel = SystemData::getLabelTTF("ui_petadvance_text4");  // 获取默认文本
        pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);  // 设置左对齐
        pLabel->setAnchorPoint(CCPointZero);  // 设置锚点
        pLabel->setColor(ccWHITE);  // 设置颜色为白色
        pLabel->setPosition(ccp(pos.x + 10, pos.y - 20));  // 设置位置
        pos = ccp(pos.x, pLabel->getPositionY());  // 更新位置
        pLabel->setFontSize(18);  // 设置字体大小
        pLayer->addChild(pLabel);  // 添加到图层
        mHeight += pLabel->getContentSize().height;  // 累加高度
    }
    
    // 19. 增加总高度
    mHeight += 70;
    
    return pLayer;  // 返回创建的图层
}

