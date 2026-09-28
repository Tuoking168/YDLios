#include "BagCellPanel.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/NetItem.h"

#include "MsgItem.h"
#include "network/HandleMessage.h"
#include "scene/GameUI.h"
#include "event/EventProtocol.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "ext/CCActionDestroy.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "scene/panel/shop/NpcShopComp.h"
#include "BagPanel.h"
#include "controls/CPNodeHelper.h"
#include "userdata/ItemOperationDef.h"
#include "script/LuaWrapper.h"
#include "MsgPlayer.h"
#include "event/CPEventHelper.h"
#include "userdata/HeroData.h"
#include "EntityDefinition.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"
#include "controls/CPDelayRefresh.h"
#include "utils/TestUtils.h"
#include "utils/StringUtils.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/ForgingPanel/ForgingMainPanel.h"
#include "scene/panel/ForgingPanel/MergeMainPanel.h"
#include "scene/panel/functionPanel/SoulStonePanel.h"
#include "userdata/activitydata/SpiderData.h"
#include "module/UserDataModule.h"
#include "scene/panel/EffectSprite.h"
#include "EffectDefinition.h"

const int ItemSize = 74;
const int RectSize = 76;

const int TAG_PUTOFF_PACK = 1003;
const int TAG_SPLIT_PACK = 1004;

const int TAG_NEXT_PAGE = 1005;
const int TAG_PRE_PAGE = 1006;

static const int ITEM_UNUSE_POS = -1000;
static const int ITEM_BAG_BEGIN = 0;
static const int ITEM_BAG_SIZE = 20;

static const float DOUBLE_CLICK_TIME = 0.2f;



#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

BagCellPanel::BagCellPanel():
	m_pMainLayer(NULL),
	m_bisOver(true),
	m_bSpiltOp(false),
	m_iSpiltCnt(0),
	m_pCurrentPage(NULL),
	m_iposition(0),
	m_clickpos(CCPointZero),
	m_iCurPosition(0),
	m_iCurUnlockCount(1),
	m_iCountItem(0),
	m_updater(NULL),
	m_bInit(false)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}


BagCellPanel::~BagCellPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

BagCellPanel* BagCellPanel::create(int line,int row,int count,int type1,int type2,int position)
{
	BagCellPanel* bagcellpanel = new BagCellPanel;
	if(bagcellpanel && bagcellpanel->init(line,row,count,type1,type2,position))
	{
		bagcellpanel->autorelease();
		return bagcellpanel;
	}

	if (bagcellpanel)
	{
		delete bagcellpanel;
	}
	return NULL;
}

bool BagCellPanel::init(int line,int row,int count,int type1,int type2,int position)
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
	m_iWidth=m_iRow*RectSize;
	m_iHeight=m_iLine*RectSize;
	m_iCurrentPage=0;


	m_iHasSolt=HeroData::getProp(Entity::attr_bagslot);
	switch (m_iType1)
	{
	case Self_Bag:
		m_iStart = ItemPos::Player_Bag_Start;
		m_iEnd =  ItemPos::Player_Bag_End;
		break;
	case Role_Bag:
		m_iStart = ItemPos::Role_Bag_Start;
		m_iEnd =  ItemPos::Role_Bag_End;
		break;
	case Pet_Bag:
		m_iStart = ItemPos::Pet_Bag_Start;
		m_iEnd =  ItemPos::Pet_Bag_End;
		m_iHasSolt = HeroData::getProp(Entity::attr_petbagslot);
		break;
	case House_Bag:
		m_iStart = ItemPos::Treasure_Warehouse_Start;
		m_iEnd =  ItemPos::Treasure_Warehouse_End;
		m_iHasSolt = m_iCount;
		break;
	case Booth_Bag:
		m_iStart = ItemPos::Market_Bag_Start;
		m_iEnd =  ItemPos::Market_Bag_End;
		break;
	case Pet_Bag_Shop:
		m_iStart = ItemPos::Pet_Bag_Start;
		m_iEnd =  ItemPos::Pet_Bag_End;
		m_iHasSolt = HeroData::getProp(Entity::attr_petbagslot);
		break;
	case Stone_Bag:
		m_iStart = ItemPos::Player_Bag_Start;
		m_iEnd =  ItemPos::Player_Bag_End;
		break;
	case Spider_Bag:
		m_iStart = ItemPos::Player_Bag_Start;
		m_iEnd =  ItemPos::Player_Bag_End;
		break;
	case Setting_Bag:
		m_iStart = ItemPos::Player_Bag_Start;
		m_iEnd =  ItemPos::Player_Bag_End;
		break;
	case NPC_Bag:
		m_iStart = ItemPos::NPC_Bag_Start;
		m_iEnd =  ItemPos::NPC_Bag_End;
		m_iCount = count;
		m_iPage = m_iCount/m_iPageCount;
		m_iHasSolt = HeroData::getProp(Entity::attr_npcbagslot);
		break;
	case Sell_Bag:
		m_iStart = ItemPos::Player_Bag_Start;
		m_iEnd =  ItemPos::Player_Bag_End;
		break;
	default:
		m_iStart = 0;
		m_iEnd =  0;
		break;
	}

	if (m_iType2==Bag_Type_ItemEx2 || m_iType2==Bag_Type_ItemEx1 || m_iType2==Bag_Type_Spider || m_iType2==Bag_Type_Setting )
	{
		m_iHasSolt=m_iCount;
	}

	initBagSlot();

	m_pMenu=GeneralMenu::create();
	m_pMenu->setAnchorPoint(CCPointZero);
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu,999);

	m_pDelay=CPDelayRefresh::create(this,callfunc_selector(BagCellPanel::updateAllItem));
	m_pDelay->setDelayTime(0.02f);
	addChild(m_pDelay);

	CCString* pstr=CCString::createWithFormat("%d/%d",m_iCurrentPage+1,m_iPage);
	m_pCurrentPage = CCLabelTTF::create(pstr->getCString(),"微软雅黑", 20);
	if(m_pCurrentPage)
		//m_pCurrentPage->setPosition(SystemData::getLayoutPoint("forging_rightmenu_page_pos"));
			m_pCurrentPage->setPosition(ccp(m_iWidth/2,45));
	m_pMenu->addChild(m_pCurrentPage);

	if (m_iType2==Bag_Type_ItemEx1 || m_iType2==Bag_Type_ItemEx2|| m_iType2==Bag_Type_Spider || m_iType2==Bag_Type_Setting)
	{
		m_pCurrentPage->setPosition(ccp(m_iWidth/2,80));
	}

	CCMenuItemImage* turnLeft = SystemData::getMenuItemImageByPlist("ui.turn_jiantou");
	turnLeft->runAction(CCRotateBy::create(0,-90));
	turnLeft->setTarget(this,menu_selector(BagPanel::buttonCallBack));
	turnLeft->setPosition(ccp(m_pCurrentPage->getPositionX()-35,m_pCurrentPage->getPositionY()));
	m_pMenu->addChild(turnLeft);

	CCMenuItemImage* turnRight = SystemData::getMenuItemImageByPlist("ui.turn_jiantou");
	turnRight->runAction(CCRotateBy::create(0,90));
	turnRight->setTarget(this,menu_selector(BagPanel::buttonCallBack));
	turnRight->setPosition(ccp(m_pCurrentPage->getPositionX()+35,m_pCurrentPage->getPositionY()));
	m_pMenu->addChild(turnRight);


	return true;
}

bool BagCellPanel::initBagSlot()
{
	m_startPoint = ccp(41, 305);

	CCClippingNode* clipper = CPNodeHelper::getClippingNode(CCSizeMake(m_iWidth-5,m_iHeight+85));
	clipper->setPosition(CCPointZero);
	addChild(clipper);

#ifdef DEBUG
	CCDrawNode* pStencil = CPNodeHelper::getBorderNode(CCSizeMake(m_iWidth-5,m_iHeight+85));
	addChild(pStencil);
#endif // DEBUG


	m_pMainLayer=CCLayer::create();
	m_pMainLayer->setAnchorPoint(CCPointZero);
	m_pMainLayer->setPosition(CCPointZero);
	clipper->addChild(m_pMainLayer);

	if (!CCLayer::init())
			return false;

	// 初始化6个背包页的背景，设置第一页为可见
	for (int i = 0; i<m_iPage; i++)
	{
		CCSprite* bkgSprite = CCSprite::create();
		if (!bkgSprite)
			break;
		bkgSprite->setAnchorPoint(CCPointZero);
		bkgSprite->setPosition(ccp(0, 0));

		m_packPage[i] = CCLayer::create();
		m_packPage[i]->setTag(i);
		m_packPage[i]->setPosition(ccp(i*m_iWidth,93));
		m_pMainLayer->addChild(m_packPage[i]);
		m_packPage[i]->addChild(bkgSprite);
		m_packPage[i]->setVisible(true);
		if (i == 0)
			m_packPage[i]->setVisible(true);
		else
			m_packPage[i]->setVisible(false);
	}

	current_layer = m_packPage[0];
	current_layer_idx = 0;
	int vipLv = HeroData::getProp(Entity::attr_vip_level);

	// 每页添加CCMenu
	for (int i=0; i<m_iPage; i++)
	{
		m_menus[i] = CCMenuEx::create();
		m_menus[i]->setPosition(CCPointZero);
		m_menusItem[i] = CCMenuEx::create();
		m_menusItem[i]->setPosition(CCPointZero);
		m_packPage[i]->addChild(m_menus[i]);
		m_packPage[i]->addChild(m_menusItem[i]);

		std::string vip = "";
		if (m_iType1 == NPC_Bag)
		{
			if (vipLv<=6)
			{
				if (i ==0)
				{
					continue;
				}
			}else if (vipLv<=8)
			{
				if (i<2)
				{
					continue;
				}
			}else if (vipLv == 9)
			{
				if (i<3)
				{
					continue;
				}
			}else
			{
				continue;
			}

			if (i == m_iPage-3)
			{
				vip += "VIP"+StringUtils::toString(SystemData::getLayoutValue("VIP7"));
			}
			if (i == m_iPage-2)
			{
				vip += "VIP"+StringUtils::toString(SystemData::getLayoutValue("VIP9"));
			}
			if (i == m_iPage-1)
			{
				vip += "VIP"+StringUtils::toString(SystemData::getLayoutValue("VIP10"));
			}
			CCLabelTTF* pW1 = CCLabelTTF::create(vip.c_str(),"",20);
			pW1->setColor(ccORANGE);
			CCLabelTTF* pWarm=SystemData::getLabelTTF("ui_NPCbag_notEnough_vip_text");
			pWarm->setFontSize(20);
			pWarm->setColor(ccORANGE);

			CCScale9Sprite* psbkg = SystemData::getScale9SpriteByPlist("taskcontent_sbkg",pWarm->getContentSize().width+100,pWarm->getContentSize().height+80);
			psbkg->setPosition(ccp(m_packPage[i]->getContentSize().width/2-170,m_packPage[i]->getContentSize().height/2-80));
			m_packPage[i]->addChild(psbkg);

			pWarm->setAnchorPoint(ccp(0,0.5));
			pWarm->setPosition(ccp(psbkg->getContentSize().width/2-80,psbkg->getContentSize().height/2));
			pW1->setPosition(ccp(pWarm->getPositionX()-30,pWarm->getPositionY()));
			psbkg->addChild(pWarm);
			psbkg->addChild(pW1);

			m_nWidth=m_packPage[i]->getContentSize().width;
			m_nHeight=m_packPage[i]->getContentSize().height;
		}
	}

	// 添加未锁定的包裹格子
	for (int i = 0;i < m_iCount;i++)
	{
		CCMenuItemImage* unlockSel = SystemData::getMenuItemImageByPlist("ui.bag.slot.unlock");
		if (unlockSel)
		{
			unlockSel->setPosition(getItemPosition(i));
			unlockSel->setTag(200+i);
			short pos = backLayer(i);
			m_menus[pos]->addChild(unlockSel);
		}
	}
	// 添加锁定的包裹格子
	for(short index = m_iHasSolt; index < m_iCount; index++)
	{
		CCMenuItemImage* lock = SystemData::getMenuItemImageByPlist("ui.bag.slot.lock");
		if (m_iType1 != NPC_Bag)
		{
			lock->setTarget(this,menu_selector(BagCellPanel::slotClickCallBack));
		}
		
		if (lock)
		{
			lock->setPosition(getItemPosition(index));
			lock->setTag(200+index);
			short pos = backLayer(index);
			m_menusItem[pos]->addChild(lock);
		}
	}

	if (m_iType2!=Bag_Type_ItemEx1 && m_iType2!=Bag_Type_ItemEx2)
	{
		this->runAction(CCSequence::create(CCDelayTime::create(0.02f),CCCallFunc::create(this,callfunc_selector(BagCellPanel::insertAllItem)),NULL));
	}

	m_Pos=m_pMainLayer->getPosition();

	return true;
}

void BagCellPanel::insertItem( UserItem* userItem, int position )
{
	if (!userItem)
		return;
	
	if (m_iType1==Self_Bag)
	{
		if (position<ItemPos::Player_Bag_Start || position>(ItemPos::Player_Bag_Start+m_iHasSolt))
		{
			return ;
		}
	}
	else if (m_iType1==Pet_Bag)
	{
		if (position<ItemPos::Pet_Bag_Start || position>(ItemPos::Pet_Bag_Start+m_iHasSolt))
		{
			return ;
		}
	}
	else if (m_iType1==House_Bag)
	{
		if (position<ItemPos::Treasure_Warehouse_Start || position>(ItemPos::Treasure_Warehouse_Start+m_iHasSolt))
		{
			return ;
		}
	}
	else if (m_iType1==NPC_Bag)
	{
		if (position<ItemPos::NPC_Bag_Start || position>(ItemPos::NPC_Bag_Start+m_iHasSolt))
		{
			return ;
		}
	}
	short pos = backLayer(position-m_iStart);
	CCMenuItemImage* icon=CommonFunction::getItemIcon(userItem);
	if (icon==NULL)
	{
		return;
	}
	icon->setTarget(this,menu_selector(BagCellPanel::itemClickCallBack));
	icon->setPosition(getItemPosition(position-m_iStart));
	icon->setTag(position-m_iStart);
	icon->setVisible(getItemVisible(position-m_iStart));
	icon->setZOrder(position-m_iStart);
	if (pos>=m_iPage)
	{
		CCLog(">>>Error: BagCellPanel::insertItem, pos = %d(to big), iid = %d, sid = %d", pos, userItem->iid, userItem->sid);
		return;
	}
	if (userItem->category==ItemCate_Stone && CommonFunction::getStoneLvl(userItem->name)>=7 )
	{
		EffectSprite* p=EffectSprite::create(Effect::effect_stoneputon);
		p->setPosition(ccp(icon->getContentSize().width/2,icon->getContentSize().height/2));
		icon->addChild(p);
	}

	m_menusItem[pos]->addChild(icon);

	if (m_bSpiltOp && ((UserItem*)(icon->getUserData()))->count>1)
	{
		CCMenu* pMenu=CCMenu::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		icon->addChild(pMenu);

		CCMenuItemImage* pSell=SystemData::getMenuItemImageByPlist("ui.btn.splititem");
		pSell->setTarget(this,menu_selector(BagCellPanel::spiltItemMsg));
		pSell->setTag(icon->getTag());
		pSell->setAnchorPoint(ccp(1,1));
		pSell->setPosition(ccp(icon->getContentSize().width+13,icon->getContentSize().height+10));
		pMenu->addChild(pSell);
	}

	if (m_iType2==Bag_Type_Npcshop ||m_iType2==Bag_Type_Null)
	{
		int price=0;
		LuaData::getProp("gdItems",userItem->sid,"price",price); 
		if (price==0)
		{
			return;
		}
		CCMenu* pMenu=CCMenu::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		icon->addChild(pMenu);

		CCMenuItemImage* pSell=SystemData::getMenuItemImageByPlist("ui.btn.sellitem");
		pSell->setTarget(this,menu_selector(BagCellPanel::sellItem));
		pSell->setTag(icon->getTag());
		pSell->setAnchorPoint(ccp(1,1));
		pSell->setPosition(ccp(icon->getContentSize().width+3,icon->getContentSize().height+3));
		pMenu->addChild(pSell);
	} 
}


cocos2d::CCPoint BagCellPanel::getItemPosition( int pos )
{
	pos %= m_iPageCount;
	return ccpAdd(m_startPoint,ccp(pos%m_iRow*ItemSize,-(pos/m_iRow*(ItemSize-6))));
}

short BagCellPanel::backLayer(int pos)
{
	return (pos/m_iPageCount);
}

void BagCellPanel::itemClickCallBack( CCObject* pSender )
{
	CCNode* pItem = dynamic_cast<CCNode*>(pSender);
	if(pItem)
	{
		/*if (m_bSpiltOp)
		{
			spiltItemMsg((UserItem*)pItem->getUserData());
			return;
		}*/
		int tag = pItem->getTag();
		m_clickpos=pItem->getPosition();
		m_iCurPosition=pItem->getZOrder();
		if (m_bisOver)
		{
			if (m_iType2 == Bag_Type_ItemEx2)
			{
				UserItem* pUserItem=(UserItem*)pItem->getUserData();
				((MergeMainPanel*)(this->getParent()->getParent()))->PostNotic(pUserItem);
			}
			else if (m_iType2 == Bag_Type_ItemEx1)
			{
				UserItem* pUserItem=(UserItem*)pItem->getUserData();
				((ForgingMainPanel*)(this->getParent()->getParent()))->PostNotic(pUserItem);
			}
			else
			{
				if(isDoubleClickItem(tag))
				{
					m_bisOver=true;
					if (m_iType1 == Self_Bag && m_iType2==Bag_Type_Pet)
					{
						UserItem* pUserItem=(UserItem*)pItem->getUserData();
						MsgItemOperationRequestSetPosition* req=new MsgItemOperationRequestSetPosition;
						req->iid=pUserItem->iid;
						req->position=GameData::s_user->getUserItemData()->getEmptyPosition(ItemPos::Pet_Bag_Start);
						HandleMessage::sendMessage(req);
						return;
					}
					if (m_iType1 == House_Bag && m_iType2==Bag_Type_Self)
					{
						UserItem* pUserItem=(UserItem*)pItem->getUserData();
						MsgItemOperationRequestSetPosition* req=new MsgItemOperationRequestSetPosition;
						req->iid=pUserItem->iid;
						req->position=GameData::s_user->getUserItemData()->getEmptyPosition(ItemPos::Player_Bag_Start);
						HandleMessage::sendMessage(req);
						return;
					}
					if (m_iType1 == Pet_Bag && m_iType2==Bag_Type_Self)
					{
						UserItem* pUserItem=(UserItem*)pItem->getUserData();
						MsgItemOperationRequestSetPosition* req=new MsgItemOperationRequestSetPosition;
						req->iid=pUserItem->iid;
						req->position=GameData::s_user->getUserItemData()->getEmptyPosition(ItemPos::Player_Bag_Start);
						HandleMessage::sendMessage(req);
						return;
					}
					if (m_iType2 == Bag_Type_NPCBag && m_iType1 == Self_Bag)
					{
						UserItem* pUserItem=(UserItem*)pItem->getUserData();
						MsgItemOperationRequestSetPosition* req=new MsgItemOperationRequestSetPosition;
						req->iid=pUserItem->iid;
						req->position=GameData::s_user->getUserItemData()->getEmptyPosition(ItemPos::NPC_Bag_Start);
						HandleMessage::sendMessage(req);
						return;
					}
					if (m_iType2 == Bag_Type_NPCBag && m_iType1 == Pet_Bag)
					{
						UserItem* pUserItem=(UserItem*)pItem->getUserData();
						MsgItemOperationRequestSetPosition* req=new MsgItemOperationRequestSetPosition;
						req->iid=pUserItem->iid;
						req->position=GameData::s_user->getUserItemData()->getEmptyPosition(ItemPos::NPC_Bag_Start);
						HandleMessage::sendMessage(req);
						return;
					}
					if (m_iType2 == Bag_Type_Pet && m_iType1 ==NPC_Bag)
					{
						UserItem* pUserItem=(UserItem*)pItem->getUserData();
						MsgItemOperationRequestSetPosition* req=new MsgItemOperationRequestSetPosition;
						req->iid=pUserItem->iid;
						req->position=GameData::s_user->getUserItemData()->getEmptyPosition(ItemPos::Pet_Bag_Start);
						HandleMessage::sendMessage(req);
						return;
					}
					if (m_iType2 == Bag_Type_Self && m_iType1 == NPC_Bag)
					{
						UserItem* pUserItem=(UserItem*)pItem->getUserData();
						MsgItemOperationRequestSetPosition* req=new MsgItemOperationRequestSetPosition;
						req->iid=pUserItem->iid;
						req->position=GameData::s_user->getUserItemData()->getEmptyPosition(ItemPos::Player_Bag_Start);
						HandleMessage::sendMessage(req);
						return;
					}
					if (m_iType2 == Bag_Type_ItemEx2 || m_iType2 == Bag_Type_ItemEx1)
					{
						return;
					}
					if (m_iType2 == Bag_Type_Spider)
					{
						UserItem* pUserItem=(UserItem*)pItem->getUserData();
						spiderdata::addItem(pUserItem);
						EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SPIDER_ITEM_CHANGE);
						return;
					}
					if ( m_iType2==Bag_Type_Setting)
					{
						UserItem* pUserItem=(UserItem*)pItem->getUserData();
						CPEventHelper::setEventIntData(CPEventName::DATA_CHANGE, CPEventData::VALUE_2, 2);
						CPEventHelper::setEventIntData(CPEventName::DATA_CHANGE, CPEventData::VALUE_3, pUserItem->sid);
						CPEventHelper::dispatcher(CPEventName::DATA_CHANGE, "", "SettingFastPanel");
						/*int id=UserData::getemptyFast();
						if (id==0)
						{
							CPEventHelper::msgResponse("","",Error::Max_FastKey);
						}
						else
						{
							UserItem* pUserItem=(UserItem*)pItem->getUserData();
							UserData::setIntData(HeroData::getPID(),CPUserData::FAST_TYPE_,id,2);
							UserData::setIntData(HeroData::getPID(),CPUserData::FAST_NUM_,id,pUserItem->sid);
							EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_FAST_KEY);
						}*/
						return;
					}
					// Send Message			
					UserItem* item = GameData::s_user->getUserItemData()->getItemByPosition(tag+m_iStart);
					this->runAction(CCSequence::create(CCDelayTime::create(0.1f),CCCallFuncND::create(this,callfuncND_selector(BagCellPanel::useItem),item),NULL));

				}
				else
				{
					scheduleOnce(schedule_selector(BagCellPanel::singleClickCallback),DOUBLE_CLICK_TIME);
				}
			}
		}
		
	}
} 

void BagCellPanel::slotClickCallBack( CCObject* pSender )
{
	//解锁点击
	CCNode* pItem = dynamic_cast<CCNode*>(pSender);
	if(pItem)
	{
		if (m_iType2==Bag_Type_Role || m_iType2==Bag_Type_Pet || m_iType2==Bag_Type_House || m_iType2==Bag_Type_Stone || m_iType2==Bag_Type_Self)
		{
			int tag=pItem->getTag()-200;
			int num=abs(tag-m_iHasSolt+1);
			m_iCurUnlockCount=num;
			openUnlockPanel();
		}
		else
		{

		}
	}
}

bool BagCellPanel::isDoubleClickItem( int pos )
{
	float curTime = SystemData::getSystemTime();
	CCLog("prepos: %d, curPos: %d.",m_nPrePos,pos);
	CCLog("pretime: %f, curTime: %f.",m_nPreTime,curTime);
	if(m_nPrePos==pos && curTime-m_nPreTime < DOUBLE_CLICK_TIME)
	{
		m_nPrePos = ITEM_UNUSE_POS;
		m_nPreTime = curTime;
		m_bDoubleClick = true;
		m_bisOver=false;
		return true;
	}
	m_nPrePos = pos;
	m_nPreTime = curTime;
	m_bDoubleClick = false;
	return false;
}

void BagCellPanel::singleClickCallback( float dt )
{
	if(!m_bDoubleClick)
	{
		if(m_iType2 == Bag_Type_Npcshop)
		{
			if(NpcShopComp::_s_state == ItemOperationDefine::item_op_fix)
			{
				///TODO: send the fix message
			}			
			else
			{
				showTooltip(m_nPrePos);
			}
		}
		else
		{
			showTooltip(m_nPrePos);
		}
		m_nPrePos = ITEM_UNUSE_POS;
		m_nPreTime = SystemData::getSystemTime();
	}
}

void BagCellPanel::showTooltip( int tag )
{
	UserItem* userItem = GameData::s_user->getUserItemData()->getItemByPosition(tag+m_iStart);
	if (userItem==NULL)
	{
		return;
	}
	m_pUserItem=userItem;
	int type=TAG_Tips;
	
	if (m_iType2==Bag_Type_Booth_Cell)//如果处于摊位出售
	{
		type=TAG_Tips_BTQX;
	}
	else if (m_iType2==Bag_Type_Booth_Buy)//如果处于摊位购买
	{
		type=TAG_Tips;
	}
	else if (m_iType2==Bag_Type_Trade)//如果处于交易
	{
		type=TAG_Tips_JY;
	}
	else if (m_iType1==NPC_Bag && m_iType2==Bag_Type_Pet)//如果处于跟Pet交互
	{
		type=TAG_Tips_QCQX2;
	}
	else if (m_iType2 == Bag_Type_Chart)//物品展示
	{
		type = TAG_Tips_ZSQX;
	}
	else if (m_iType2==Bag_Type_Pet)//如果处于跟宠物交互
	{
		type=TAG_Tips_CFQX1;
	}
	else if (m_iType2==Bag_Type_House)//如果处于跟仓库交互
	{
		//type=TAG_Tips_CFQX2;
	}
	else if (m_iType2==Bag_Type_Self)//如果处于跟背包交互
	{
		type=TAG_Tips_QCQX;
	}
	else if (m_iType2 == Bag_Type_Npcshop)
	{
		type=TAG_Tips_MC;
	}
	else if ( m_iType2==Bag_Type_Spider)
	{
		type=TAG_Tips_TR;
	}
	else if ( m_iType2==Bag_Type_Setting)
	{
		type=TAG_Tips_JRKJJ;
	}
	else if (m_iType2==Bag_Type_NPCBag)//如果处于跟NPC仓库交互
	{
		type=TAG_Tips_CFQX2;
	}
	else if (m_iType2==Bag_Type_Role || m_iType2==Bag_Type_Stone)//如果处于跟人物和魂石交互
	{
		if (m_pUserItem->category==ItemCate_Equip && m_pUserItem->position<0)
		{
			type=TAG_Tips_XX;
		}
		else if (m_pUserItem->category==ItemCate_Equip && m_pUserItem->position>0)
		{
			type=TAG_Tips_ZBDQ;
		}
		else 
		{
			int canuse=0;
			LuaData::getProp("gdItems",m_pUserItem->sid,"canuse",canuse);
			if (m_pUserItem->category==ItemCate_Material && canuse==0)
			{
				type=TAG_Tips_DQ;
			}
			else
			{
				type=TAG_Tips_SYDQ;
			}
		}
	}

	CCPoint anpos=CCPointZero;
	CCPoint pos=ccp(300,10);
	CCPoint itempos=m_clickpos;//getItemPosition(tag); 
	int realtag=m_iCurPosition%m_iPageCount;
	CCPoint pos1=ccp(itempos.x-ItemSize/2,itempos.y+(ItemSize/2)+94);
	CCPoint pos2=ccp(itempos.x+ItemSize/2,itempos.y+(ItemSize/2)+94);
	CCPoint pos3=ccp(itempos.x+ItemSize/2,itempos.y+(-ItemSize/2)+94);
	CCPoint pos4=ccp(itempos.x-ItemSize/2,itempos.y+(-ItemSize/2)+94);
	// 判断tips显示的位置
	if (userItem->category==ItemCate_Equip || (userItem->category==ItemCate_Extension && userItem->type==ItemType_Pet))// 是否是装备(目前一律右边显示)
	{
		if (m_iposition==1)//当前属于界面的左边还是右边(左边)
		{
			pos=ccp(pos2.x+100,pos.y);
		}
		else
		{
			pos=ccp(pos1.x+100+2*ItemSize,pos.y);
		}
	}
	else
	{
		if (m_iposition==1)//当前属于界面的左边还是右边(左边)
		{
			if (realtag<3*m_iRow)//判断属于上面还是下面(上面)
			{
				pos=ccp(pos2.x+100,pos2.y-258);
				anpos=ccp(0,1);
			}
			else
			{
				pos=ccp(pos3.x+100,pos3.y);
				anpos=ccp(0,0);
			}
		}
		else// 右边
		{
			if (realtag<3*m_iRow)//判断属于上面还是下面(上面)
			{
				pos=ccp(pos1.x+100+2*ItemSize,pos1.y-258);
				anpos=ccp(1,1);
			}
			else
			{
				pos=ccp(pos4.x+100+2*ItemSize,pos4.y);
				anpos=ccp(1,0);
			}
		}
	}
	if (m_iType1==NPC_Bag)
	{
		pos=ccp(pos.x-85,pos.y);
	}
	CCLog("__________showTipsPanel");
	Game::getGameUI()->showTipsPanel(userItem,type,pos,anpos);
}

void BagCellPanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA ||channel == EventProtocol::EVENT_SPIDER_ITEM_CHANGE )
	{
		m_pDelay->refresh();
	}	
	if (channel==EventProtocol::EVENT_PUTIN_UNLOCK)
	{
		//openUnlockPanel();
	}
	if (channel==EventProtocol::EVENT_ITEM_SPILT)
	{
		sendMsgSpiltItem();
	}
}

bool BagCellPanel::isPosInThisPanel( int pos )
{	
	return (pos >= m_iStart && pos<=m_iEnd );
}

void BagCellPanel::updatePage( int page )
{
	
	for (int i = 0; i<m_iPage; i++)
	{
		m_packPage[i]->setVisible(true);
	}

	m_iCurrentPage=page;
	m_pMainLayer->runAction(CCSequence::create( CCMoveTo::create(0.2,ccp(m_Pos.x-m_iWidth*page,0)),CCCallFuncO::create(this,callfuncO_selector(BagCellPanel::setPanelVisible),NULL),NULL));	
	if (m_pCurrentPage)
	{
		CCString* pstr=CCString::createWithFormat("%d/%d",m_iCurrentPage+1,m_iPage);
		m_pCurrentPage->setString(pstr->getCString());
	}
}

bool BagCellPanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{	
	CCPoint pos = convertToNodeSpace(pTouch->getLocation());
	int iwidth=0;
	if(pos.x>=0-iwidth && pos.x<=0+m_iWidth-iwidth && pos.y>=m_startPoint.y-m_iHeight+130 && pos.y<=m_startPoint.y+130 )
	{
		for (int i = 0; i<m_iPage; i++)
		{
			m_packPage[i]->setVisible(true);
		}
		m_TouchPos.x = pos.x;
		m_TouchPos.y = pos.y;
		m_StartPos=m_pMainLayer->getPosition();
		return true;
	}
	return false;
}

void BagCellPanel::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	Game::getGameUI()->hidePanel(TAG_Tips_PANEL);
	
	CCPoint pos = convertToNodeSpace(pTouch->getLocation());
	int iwidth=0;
	
	if(pos.x>=0-iwidth && pos.x<=0+m_iWidth-iwidth && pos.y>=m_startPoint.y-m_iHeight+130 && pos.y<=m_startPoint.y+130 )
	{
		m_pMainLayer->setPosition(ccpAdd(m_pMainLayer->getPosition(),ccp(-(m_TouchPos.x-pos.x),0)));
		m_TouchPos=pos;
	}
}

void BagCellPanel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos = convertToNodeSpace(pTouch->getLocation());
	if (abs((int)(m_StartPos.x-m_pMainLayer->getPositionX()))>=35)
	{
		int n=abs((int)(m_StartPos.x-m_pMainLayer->getPositionX()))/m_iWidth+1;
		if (m_StartPos.x-m_pMainLayer->getPositionX()>0)//左移
		{
			if ((m_iCurrentPage+n)>= m_iPage)
			{
				updatePage(m_iPage-1);
			}
			else
			{
				updatePage(m_iCurrentPage+n);
			}
			//发送消息，改变page+1
			/*for (int i=0;i<n;i++)
			{
				if (m_iType1==Pet_Bag)
				{
					EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PETBAGCELL_LEFT);
				}
				else
				{
					EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_BAGCELL_LEFT);
				}
			}*/

		}
		else
		{
			if ((m_iCurrentPage-n)<0)
			{
				updatePage(0);
			}
			else
			{
				updatePage(m_iCurrentPage-n);
			}
			
			//发送消息，改变page-1
			/*for (int i=0;i<n;i++)
			{
				if (m_iType1==Pet_Bag )
				{
					EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PETBAGCELL_RIGHT);
				}
				else
				{
					EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_BAGCELL_RIGHT);
				}
			}*/
		}

	}
	else
	{
		updatePage(m_iCurrentPage);
	}
}

void BagCellPanel::setPanelVisible(CCObject* pSender)
{
	for (int i = 0; i<m_iPage; i++)
	{
		if(m_iCurrentPage==i)
		{
			m_packPage[i]->setVisible(true);
			m_packPage[i]->setTouchEnabled(true);
			m_menusItem[i]->setTouchEnabled(true);
			m_menus[i]->setTouchEnabled(true);
		}
		else
		{
			m_packPage[i]->setVisible(false);
			m_packPage[i]->setTouchEnabled(false);
			m_menusItem[i]->setTouchEnabled(false);
			m_menus[i]->setTouchEnabled(false);
		}
	}
}

void BagCellPanel::insertStone(UserItem* userItem, int position)
{
    if (!userItem)
        return;
    
    int pos = backLayer(position);
    
    // 修复：使用 >= 而不是 >
    if (pos < 0 || pos >= m_iPage)  // 关键修复点增加页数闪退
    {
        return;
    }
    
    CCMenuItemImage* icon = CommonFunction::getItemIcon(userItem);
    if (icon == NULL)
    {
        return;
    }
    
    icon->setTarget(this, menu_selector(BagCellPanel::itemClickCallBack));
    icon->setPosition(getItemPosition(position));
    icon->setTag(userItem->position - m_iStart);
    icon->setVisible(getItemVisible(position));
    icon->setZOrder(position);
    
    if (userItem->category == ItemCate_Stone && CommonFunction::getStoneLvl(userItem->name) >= 7)
    {
        EffectSprite* p = EffectSprite::create(Effect::effect_stoneputon);
        p->setPosition(ccp(icon->getContentSize().width/2, icon->getContentSize().height/2));
        icon->addChild(p);
    }
    
    // 现在可以安全调用
    m_menusItem[pos]->addChild(icon);

    if (m_iType2 == Bag_Type_Npcshop || m_iType2 == Bag_Type_Null)
    {
        int price = 0;
        LuaData::getProp("gdItems", userItem->sid, "price", price); 
        if (price == 0)
        {
            return;
        }
        CCMenu* pMenu = CCMenu::create();
        pMenu->setAnchorPoint(CCPointZero);
        pMenu->setPosition(CCPointZero);
        icon->addChild(pMenu);

        CCMenuItemImage* pSell = SystemData::getMenuItemImageByPlist("ui.btn.sellitem");
        pSell->setTarget(this, menu_selector(BagCellPanel::sellItem));
        pSell->setTag(icon->getTag());
        pSell->setAnchorPoint(ccp(1,1));
        pSell->setPosition(ccp(icon->getContentSize().width+13, icon->getContentSize().height+10));
        pMenu->addChild(pSell);
    } 
}

void BagCellPanel::openKeyBorad()
{
	if (getChildByTag(Panel_Unlock))
	{
		getChildByTag(Panel_Unlock)->setVisible(false);
	}
	//Game::getGameUI()->showNumberBoard(&m_iCurUnlockCount,m_iCount-HeroData::getProp(Entity::attr_bagslot),EventProtocol::EVENT_PUTIN_UNLOCK,1);
}

void BagCellPanel::setCurCount( int count )
{
	if (Game::getGameUI()->getPanel(TAG_UNLOCKBAG_PANEL))
	{
		((BagUnlockPanel*)(Game::getGameUI()->getPanel(TAG_UNLOCKBAG_PANEL)))->setUnlockCount(count);
	}
}

void BagCellPanel::openUnlockPanel()
{
	Game::getGameUI()->showUnlockPanel(m_iCurUnlockCount,m_iType1);
	setCurCount(m_iCurUnlockCount);
}

void BagCellPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			int type=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (type==Entity::attr_petbagslot && m_iType1==Pet_Bag)
			{
				handleEvent(EventProtocol::EVENT_ITEM_UPDDATA);
			}
			else if (type==Entity::attr_bagslot && m_iType1==Self_Bag)
			{
				handleEvent(EventProtocol::EVENT_ITEM_UPDDATA);
			}
			else if (type==Entity::attr_warehouseslot && m_iType1==House_Bag)
			{
				handleEvent(EventProtocol::EVENT_ITEM_UPDDATA);
			}
		}
	}
}

void BagCellPanel::insertAllItem()
{
	if (m_updater)
	{
		removeChild(m_updater);
	}

	m_iCountItem = 0;
	m_vecItem.clear();
	m_vecAllItem.clear();
	if (m_iType2==Bag_Type_ItemEx1 ||m_iType2==Bag_Type_ItemEx2)
	{
		m_vecItem=CommonFunction::getBagItem(m_iCurrentVisibleType,m_iType1);
		m_iCountItem = m_vecItem.size();
	}
	else if (m_iType2==Bag_Type_Npcshop)
	{
		m_vecItem=CommonFunction::getBagItem(Type_Npcshop,m_iType1);
		m_iCountItem = m_vecItem.size();
	}
	else if (m_iType2==Bag_Type_Spider && m_iType1==Spider_Bag)
	{
		m_vecItem=CommonFunction::getBagItem(Type_Spider,Self_Bag);
		m_iCountItem = m_vecItem.size();
	}
	else if (m_iType2==Bag_Type_Chart )
	{
		m_vecItem=CommonFunction::getBagItem(Type_Chart,m_iType1);
		m_iCountItem = m_vecItem.size();
	}
	else if (m_iType2==Bag_Type_Setting && m_iType1==Setting_Bag)
	{
		m_vecItem=CommonFunction::getBagItem(Type_Setting,Self_Bag);
		m_iCountItem = m_vecItem.size();
	}
	else if (m_iType2==Bag_Type_Null && m_iType1==Sell_Bag)
	{
		m_vecItem=CommonFunction::getBagItem(Type_rubbish,Sell_Bag);
		m_iCountItem = m_vecItem.size();
	}
	else if (m_iType1==Stone_Bag)
	{
		m_vecItem=CommonFunction::getBagItem(Type_Stone,Sell_Bag);
		m_iCountItem = m_vecItem.size();
	}
	else 
	{
		//m_vecAllItem=CommonFunction::getBagItem(Type_NULL,Sell_Bag);

		UserItems items = GameData::s_user->getUserItemData()->userItems;
		int n=0;
		for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
		{
			if (isPosInThisPanel(it->first))
			{
				m_vecAllItem.push_back(it->second);
				//insertItem(it->second,it->first);
			}
		}
		m_iCountItem = m_vecAllItem.size();
	}

	if (m_bInit)
	{
		if (m_vecItem.size()>0)
		{
			int n = 0;
			for(std::vector<UserItem*>::iterator it = m_vecItem.begin(); it!=m_vecItem.end(); it++)
			{
				insertStone(*it,n);
				n++;
			}
		}

		if (m_vecAllItem.size()>0)
		{
			int n = 0;
			for(std::vector<UserItem*>::iterator it = m_vecAllItem.begin(); it!=m_vecAllItem.end(); it++)
			{
				insertItem(*it,(*it)->position);
				n++;
			}
		}
	}
	else
	{
		m_updater = CPUpdater::create(this, cpupdater_selector(BagCellPanel::addListItem));
		m_updater->setUpdateTimes(m_iCountItem);
		m_updater->setFinishHandler(this, callfunc_selector(BagCellPanel::addListItemFinish));
		addChild(m_updater);
		m_updater->start();
	}
}

void BagCellPanel::addListItemFinish()
{
	m_bInit = true;
}

void BagCellPanel::addListItem(int i)
{
	if (m_vecItem.size()>0)
	{
		int n = 0;
		for(std::vector<UserItem*>::iterator it = m_vecItem.begin(); it!=m_vecItem.end(); it++)
		{
			if (i==n)
			{
				insertStone(*it,i);
				break;
			}
			n++;
		}
	}

	if (m_vecAllItem.size()>0)
	{
		int n = 0;
		for(std::vector<UserItem*>::iterator it = m_vecAllItem.begin(); it!=m_vecAllItem.end(); it++)
		{
			if (i==n)
			{
				insertItem(*it,(*it)->position);
				break;
			}
			n++;
		}
	}
}

void BagCellPanel::updateAllItem()
{

	if (m_iType2==Bag_Type_ItemEx1 || m_iType2==Bag_Type_ItemEx2 || m_iType2==Bag_Type_Spider)
	{
		m_iHasSolt=m_iCount;
	}

	GameData::s_user->UpdStoneArray();
	m_iHasSolt=HeroData::getProp(Entity::attr_bagslot);
	switch (m_iType1)
	{
	case Self_Bag:
		m_iStart = ItemPos::Player_Bag_Start;
		m_iEnd =  ItemPos::Player_Bag_End;
		break;
	case Role_Bag:
		m_iStart = ItemPos::Player_Bag_Start;
		m_iEnd =  ItemPos::Player_Bag_End;
		break;
	case Pet_Bag:
		m_iStart = ItemPos::Pet_Bag_Start;
		m_iEnd =  ItemPos::Pet_Bag_End;
		m_iHasSolt = HeroData::getProp(Entity::attr_petbagslot);
		break;
	case House_Bag:
		m_iStart = ItemPos::Treasure_Warehouse_Start;
		m_iEnd =  ItemPos::Treasure_Warehouse_End;
		m_iHasSolt = m_iCount;
		break;
	case Booth_Bag:
		m_iStart = ItemPos::Market_Bag_Start;
		m_iEnd =  ItemPos::Market_Bag_End;
		break;
	case Pet_Bag_Shop:
		m_iStart = ItemPos::Pet_Bag_Start;
		m_iEnd =  ItemPos::Pet_Bag_End;
		break;
	case Stone_Bag:
		m_iStart = ItemPos::Player_Bag_Start;
		m_iEnd =  ItemPos::Player_Bag_End;
		break;
	case Spider_Bag:
		m_iStart = ItemPos::Player_Bag_Start;
		m_iEnd =  ItemPos::Player_Bag_End;
		break;
	case NPC_Bag:
		m_iStart = ItemPos::NPC_Bag_Start;
		m_iEnd =  ItemPos::NPC_Bag_End;
		m_iHasSolt=HeroData::getProp(Entity::attr_npcbagslot);
		break;
	case Sell_Bag:
		m_iStart = ItemPos::Player_Bag_Start;
		m_iEnd =  ItemPos::Player_Bag_End;
		break;
	default:
		m_iStart = 0;
		m_iEnd =  0;
		break;
	}
	
	for (int i=0;i<m_iPage;i++)
	{
		CCArray *children = m_menusItem[i]->getChildren();
		if (children && children->count() > 0)
		{
			//m_menusItem[i]->removeAllChildren();
			CCObject *obj = NULL;
			CCARRAY_FOREACH(children, obj)
			{
				CCNode *child = dynamic_cast<CCNode *>(obj);
				if (child)
				{
					CCHide *hi = CCHide::create();
					CCDelayTime *dl = CCDelayTime::create(0.5f);
					CCActionInstantRemoveFromParent *rmv = CCActionInstantRemoveFromParent::create();
					CCAction *action = CCSequence::create(hi, dl, rmv, NULL);
					child->runAction(action);
				}
			}
		}
	}

	// 添加锁定的包裹格子
	for(short index = m_iHasSolt; index < m_iCount; index++)
	{
		CCMenuItemImage* lock = SystemData::getMenuItemImageByPlist("ui.bag.slot.lock");
		lock->setTarget(this,menu_selector(BagCellPanel::slotClickCallBack));
		if (lock)
		{
			lock->setPosition(getItemPosition(index));
			lock->setTag(200+index);
			short pos = backLayer(index);
			m_menusItem[pos]->addChild(lock);
		}
	}
	//this->stopAllActions();
	insertAllItem();

	//this->runAction(CCSequence::create(CCDelayTime::create(0.02f),CCCallFunc::create(this,callfunc_selector(BagCellPanel::insertAllItem)),NULL));

	m_bisOver=true;
}

void BagCellPanel::useItem(CCNode* pSender, void* pObject )
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_POSTMSG,(CCObject *)pObject);
}

void BagCellPanel::setCurVisibleType( int type )
{
	m_iCurrentVisibleType=type;
	updateAllItem();
}

void BagCellPanel::spiltItemMsg( CCObject* pSender )
{
	CCNode* pNode=(CCNode*)pSender;	
	if (pNode)
	{
		int tag=pNode->getTag();
		UserItem* userItem = GameData::s_user->getUserItemData()->getItemByPosition(tag+m_iStart);
		if (userItem==NULL)
		{
			return;
		}
		m_pUserItem=userItem;
		Game::getGameUI()->showNumberBoard(&m_iSpiltCnt,userItem->count,EventProtocol::EVENT_ITEM_SPILT,1,"拆分数量:");
	}
}

void BagCellPanel::sendMsgSpiltItem()
{
	if (m_pUserItem)
	{
		int bagtype=0;
		switch (m_iType1)
		{
		case Self_Bag:
			bagtype=ItemPos::Bag_Player;
			break;
		case House_Bag:
			bagtype=ItemPos::Bag_Warehouse;
			break;
		default:
			break;
		}
		if (bagtype==0)
		{
			return;
		}
		MsgItemResolveRequest* msg=new MsgItemResolveRequest;
		msg->iid=m_pUserItem->iid;
		msg->count=m_iSpiltCnt;
		msg->bagtype=bagtype;
		HandleMessage::sendMessage(msg);

		m_iSpiltCnt=1;
		//setspiltState(false);
	}	
}

void BagCellPanel::setspiltState( bool flag )
{
	m_bSpiltOp=flag;
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_ITEM_UPDDATA);
}

void BagCellPanel::sellItem( CCObject* pSender )
{
	CCNode* pItem = dynamic_cast<CCNode*>(pSender);
	if(pItem)
	{
		int tag=pItem->getTag();
		UserItem* userItem = GameData::s_user->getUserItemData()->getItemByPosition(tag+m_iStart);
		if (userItem==NULL)
		{
			return;
		}
		m_pUserItem=userItem;
		MsgItemOperationRequestSell* msgSell = new MsgItemOperationRequestSell;
		msgSell->iid = m_pUserItem->iid;
		msgSell->count = m_pUserItem->count;
		HandleMessage::sendMessage(msgSell);

		NpcShopComp::_s_state = ItemOperationDefine::item_op_sell;
	}
}

void BagCellPanel::setType2( int type )
{
	m_iType2=type;
}


//-----------------------------------------------------------------------------------------------------------------------------//

BagUnlockPanel::BagUnlockPanel():
	m_iCount(0),
	m_pCurCount(NULL)
{

}

BagUnlockPanel::~BagUnlockPanel()
{

}

BagUnlockPanel* BagUnlockPanel::create(int pos,int type)
{
	BagUnlockPanel* bagcellpanel = new BagUnlockPanel;
	if(bagcellpanel && bagcellpanel->init(pos,type))
	{
		bagcellpanel->autorelease();
		return bagcellpanel;
	}

	if (bagcellpanel)
	{
		delete bagcellpanel;
	}
	return NULL;
}

/**
 * BagUnlockPanel::init() 初始化函数
 * 功能：初始化背包解锁界面，根据背包类型计算可解锁格子数量，创建UI元素
 * 参数: 
 *   int pos - 初始解锁数量
 *   int type - 背包类型（Self_Bag:角色背包, Pet_Bag:宠物背包, House_Bag:仓库背包）
 * 返回: bool - 初始化是否成功
 */
bool BagUnlockPanel::init(int pos, int type) // 解锁背包的界面
{
	// 1. 设置面板的宽度和高度（基于1200x520的设计分辨率）
	m_nWidth = 800;  // 注释：对应800全屏的换算值
	m_nHeight = 480;  // 注释：对应480的换算值
	
	// 2. 添加覆盖层（半透明黑色遮罩）
	addCover();
	
	// 3. 根据背包类型计算可解锁的最大数量和起始位置
	// 需要判断是什么类型的背包
	switch (type)
	{
	case Self_Bag: // 角色背包
		// 可解锁数量 = 最大背包格子数 - 当前已解锁格子数
		m_iMaxCnt = SystemData::getLayoutValue("MaxPlayerBagSlot") - HeroData::getProp(Entity::attr_bagslot);
		// 起始位置 = 当前已解锁格子数 - 基础背包格子数 + 1
		m_iStartPos = HeroData::getProp(Entity::attr_bagslot) - SystemData::getLayoutValue("PlayerBagSlotNum") + 1;
		// 背包类型属性标识
		m_iBagType = Entity::attr_bagslot;
		break;	
		
	case Pet_Bag: // 宠物背包
		// 可解锁数量 = 最大宠物背包格子数 - 当前已解锁格子数
		m_iMaxCnt = SystemData::getLayoutValue("MaxPetBagSlot") - HeroData::getProp(Entity::attr_petbagslot);
		// 起始位置 = 当前已解锁格子数 - 基础宠物背包格子数 + 1
		m_iStartPos = HeroData::getProp(Entity::attr_petbagslot) - SystemData::getLayoutValue("PetBagSlotNum") + 1;
		// 背包类型属性标识
		m_iBagType = Entity::attr_petbagslot;
		break;
		
	case House_Bag: // 仓库背包		
		// 可解锁数量 = 最大仓库格子数 - 当前已解锁格子数
		m_iMaxCnt = SystemData::getLayoutValue("MaxHouseBagSlot") - HeroData::getProp(Entity::attr_warehouseslot);
		// 起始位置 = 当前已解锁格子数 - 基础仓库格子数 + 1
		m_iStartPos = HeroData::getProp(Entity::attr_warehouseslot) - SystemData::getLayoutValue("HouseBagSlotNum") + 1;
		// 背包类型属性标识
		m_iBagType = Entity::attr_warehouseslot;
		break;
		
	default: // 默认使用角色背包配置
		m_iMaxCnt = SystemData::getLayoutValue("MaxPlayerBagSlot") - HeroData::getProp(Entity::attr_bagslot);
		m_iStartPos = HeroData::getProp(Entity::attr_bagslot) - SystemData::getLayoutValue("PlayerBagSlotNum") + 1;
		m_iBagType = Entity::attr_bagslot;
		break;
	}
	
	// 4. 保存初始解锁数量
	m_iCount = pos; // 传入的解锁数量参数

	// 5. 创建并添加对话框边框
	// 从plist资源获取九宫格精灵作为对话框边框
	CCScale9Sprite* pborder = SystemData::getScale9SpriteByPlist(
		"ui_float_menu_border",
		SystemData::getLayoutValue("ui_float_menu_size.w"),
		SystemData::getLayoutValue("ui_float_menu_size.h")
	);
	pborder->setAnchorPoint(CCPointZero);  // 设置锚点为左下角
	pborder->setPosition(CCPointZero);      // 设置位置为(0,0)
	addChild(pborder);                       // 添加到当前面板

	// 6. 重置面板尺寸并添加带偏移的覆盖层
	m_nWidth = 800;  // 重新设置宽度
	m_nHeight = 480;  // 重新设置高度
	addCover(ccp(-260, -100));  // 添加带偏移的覆盖层

	// 7. 创建关闭按钮菜单容器
	CCMenu* pMenu = CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);  // 设置锚点为左下角
	pMenu->setPosition(CCPointZero);      // 设置位置为(0,0)
	addChild(pMenu);                      // 添加到当前面板

	// 8. 创建并添加关闭按钮
	// 从plist资源获取关闭按钮图片
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("ui_float_menu_close");
	pClose->setPosition(SystemData::getLayoutPoint("ui_float_menu_close_pos"));  // 从布局获取位置
	pClose->setTarget(this, menu_selector(BagUnlockPanel::MenuCallBack));        // 设置点击回调函数
	pClose->setTag(Button_Cancel);  // 设置按钮标签为取消按钮
	pMenu->addChild(pClose);         // 添加到菜单容器

	// 9. 创建数量显示背景
	// 从plist资源获取数量显示框背景
	CCScale9Sprite* ptext2 = SystemData::getScale9SpriteByPlist(
		"ui_sellpanel_text",
		SystemData::getLayoutValue("ui_sellpanel_text_size.w"),
		SystemData::getLayoutValue("ui_sellpanel_text_size.h")
	);
	// 创建可点击的数量显示区域
	CCMenuItemSprite* ptext = CCMenuItemSprite::create(ptext2, ptext2, NULL, this, menu_selector(BagUnlockPanel::MenuCallBack));
	ptext->setPosition(ccp(170, 170));  // 设置位置
	ptext->setTag(Text_PutIn);           // 设置标签为文本输入区域
	pMenu->addChild(ptext);              // 添加到菜单容器

	// 10. 创建左右箭头按钮
	// 左箭头按钮
	CCMenuItemImage* pItemLeft = SystemData::getMenuItemImageByPlist("ui_pet_jiantou");
	pItemLeft->setPosition(ccp(90, 170));  // 设置位置
	pItemLeft->setTarget(this, menu_selector(BagUnlockPanel::MenuCallBack));  // 设置点击回调
	pItemLeft->setTag(Left_Button);  // 设置标签为左按钮
	pMenu->addChild(pItemLeft);       // 添加到菜单容器
	
	// 右箭头按钮（通过水平翻转左箭头创建）
	CCSprite* psprite = SystemData::getSpriteByPlist("ui_pet_jiantou");
	psprite->runAction(CCFlipX::create(true));  // 水平翻转精灵
	CCMenuItemSprite* pItemRight = CCMenuItemSprite::create(psprite, psprite, NULL, this, menu_selector(BagUnlockPanel::MenuCallBack));
	pItemRight->setPosition(ccp(250, 170));  // 设置位置
	pItemRight->setTag(Right_Button);         // 设置标签为右按钮
	pMenu->addChild(pItemRight);              // 添加到菜单容器

	// 11. 创建当前数量显示文本
	m_pCurCount = CCLabelTTF::create(SystemData::intToString(m_iCount).c_str(), "微软雅黑", 15);
	m_pCurCount->setPosition(ptext->getPosition());  // 位置与数量显示框相同
	addChild(m_pCurCount);  // 添加到当前面板

	// 12. 创建静态提示文本1
	CCLabelTTF* pStaticText1 = SystemData::getLabelTTF("BagCell_text1");
	pStaticText1->setPosition(ccp(170, 210));  // 设置位置
	pStaticText1->setColor(ccWHITE);           // 设置颜色为白色
	pStaticText1->setFontSize(18);              // 设置字体大小
	addChild(pStaticText1);                     // 添加到当前面板

	// 13. 创建静态提示文本2
	CCLabelTTF* pStaticText2 = SystemData::getLabelTTF("BagCell_text2");
	pStaticText2->setPosition(ccp(170, 90));   // 设置位置
	pStaticText2->setColor(ccGREEN);           // 设置颜色为绿色
	pStaticText2->setFontSize(18);              // 设置字体大小
	addChild(pStaticText2);                     // 添加到当前面板

	// 14. 创建动态费用文本（显示当前解锁数量和所需费用）
	// 使用格式化字符串创建文本，显示"解锁X个背包格子需要X金币"
	CCString* pStr = CCString::createWithFormat(
		SystemData::getLayoutString("BagCell_text3").c_str(),  // 格式化字符串
		m_iCount,      // 当前解锁数量
		m_iCount * 10  // 所需金币数量（每个格子10金币）
	);
	m_pCurText = CCLabelTTF::create(pStr->getCString(), "微软雅黑", 18);
	m_pCurText->setPosition(ccp(170, 115));  // 设置位置
	addChild(m_pCurText);                     // 添加到当前面板

	// 15. 创建"确定"和"取消"按钮
	std::string str[2] = {"确定", "取消"};  // 按钮文本
	
	// 循环创建两个按钮
	for (int i = 0; i < 2; i++)
	{
		// 获取按钮的正常和选中状态精灵
		CCSprite* p1 = SystemData::getSpriteByPlist("ui_float_button");
		CCSprite* p2 = SystemData::getSpriteByPlist("ui_float_button.sel");
		
		// 创建按钮菜单项
		CCMenuItemSprite* pButton = CCMenuItemSprite::create(p1, p2, NULL, this, menu_selector(BagUnlockPanel::MenuCallBack));
		
		// 设置按钮位置：基于布局位置，水平排列
		pButton->setPosition(ccp(
			SystemData::getLayoutPoint("ui_float_block1_pos").x + (i % 2) * 160,  // 水平间隔160像素
			SystemData::getLayoutPoint("ui_float_block1_pos").y - 60 - (i / 2) * 50  // 垂直间隔50像素
		));
		
		// 根据索引设置按钮标签
		if (i == 0)
		{
			pButton->setTag(Button_OK);  // 确定按钮
		}
		else if (i == 1)
		{
			pButton->setTag(Button_Cancel);  // 取消按钮
		}
		
		// 创建按钮文本（UTF-8编码转换）
		CCLabelTTF* pLabel = CCLabelTTF::create(AToU8(str[i].c_str()), "微软雅黑", 18);
		pLabel->setPosition(ccp(pButton->getContentSize().width / 2, pButton->getContentSize().height / 2));  // 居中
		pMenu->addChild(pButton);    // 添加按钮到菜单容器
		pButton->addChild(pLabel);   // 添加文本到按钮
	}
	
	// 16. 设置初始解锁数量显示
	setUnlockCount(m_iCount);
	
	// 17. 初始化成功，返回true
	return true;
}

void BagUnlockPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag=pNode->getTag();
		switch (tag)
		{
		case Left_Button:
			setUnlockCount(m_iCount-1);
			break;
		case Right_Button:
			setUnlockCount(m_iCount+1);			
			break;
		case Button_OK:
			postmsgUnlockBag();
			break;
		case Button_Cancel:
			this->removeFromParent();
			break;
		case Text_PutIn:
			Game::getGameUI()->showNumberBoard(&m_iCount,m_iMaxCnt,EventProtocol::EVENT_PUTIN_UNLOCK,1);
			this->setVisible(false);
			//((BagCellPanel*)(this->getParent()))->openKeyBorad();
			break;
		default:
			break;
		}
	}
}

void BagUnlockPanel::setUnlockCount( int count )
{
	m_iCount=count;
	if (m_iCount<1)
	{
		m_iCount=1;
	}
	else if (m_iCount>m_iMaxCnt)
	{
		m_iCount=m_iMaxCnt;
	}
	if (m_pCurCount)
	{
		m_pCurCount->setString(SystemData::intToString(m_iCount).c_str());
	}
	int n=m_iStartPos;
	int mcount=0;  
	for (int i=0;i<m_iCount;i++)
	{
		mcount+=n;
		n++;
	}
	if (m_pCurText)
	{
		CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("BagCell_text3").c_str(),mcount,mcount*10);
		m_pCurText->setString(pStr->getCString());
	}
}

void BagUnlockPanel::postmsgUnlockBag()
{
	if (check())
	{
		MsgUnlockBagSlotRequest* msg=new MsgUnlockBagSlotRequest;
		msg->count=m_iCount;
		msg->startpos=m_iStartPos;
		msg->bagtype=m_iBagType;
		HandleMessage::sendMessage(msg);
		this->removeFromParent();
	}
	
}

bool BagUnlockPanel::check()
{
	UserItems items = GameData::s_user->getUserItemData()->userItems;

	int n=0;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		int sid = SystemData::getLayoutValue("背包扩展符");
		if (it->second->sid==sid)
		{
			n+=it->second->count;
		}
	}

	if (n>=m_iCount)
	{
		return true;
	}
	else
	{
		if (HeroData::getProp(Entity::attr_gold)>=(m_iCount-n)*10)
		{
			return true;
		}
	}
	CPEventHelper::uiNotify("","",Error::Item_UnlockReqNotEnough);
	return false;
}

void BagUnlockPanel::handleEvent( int channel )
{
	if (channel==EventProtocol::EVENT_PUTIN_UNLOCK)
	{
		this->setVisible(true);
		setUnlockCount(m_iCount);
	}
}
