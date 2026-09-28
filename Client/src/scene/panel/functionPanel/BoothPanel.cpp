#include "BoothPanel.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/HeroData.h"
#include "userdata/LayoutData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/NetItem.h"
#include "MsgPet.h"
#include "network/HandleMessage.h"
#include "MsgItem.h"
#include "scene/GameUI.h"
#include "event/EventProtocol.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "BagPanel.h"
#include "script/LuaWrapper.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "userdata/UserPetData.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "EntityDefinition.h"
#include "MsgScene.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/BoothData.h"

#include "event/CPEventHelper.h"
#include "scene/panel/ChatPanel.h"
#include "event/CPEventDispatcher.h"

#include "BoothSellBook.h"

const short PAGE_ONE = 0;
const short PAGE_NUM = 15;

const int ItemOneLine = 5;
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

BoothPanel::BoothPanel():
	m_iBoothType(0),
	m_ItemMenu(NULL),
	m_icurrentPrice(0),
	m_pBoothTitle(NULL),
	m_pEditBox(NULL),
	m_padLabel(NULL),
	i_time(0),
	m_pDownMenu(NULL),
	m_bclickOtherItem(false),
	m_iTimeSpan(0)
{
	for (int i=0;i<15;i++)
	{
		isItem[i]=false;
	}
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}


BoothPanel::~BoothPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

BoothPanel* BoothPanel::create(int type,bool isHighBooth)
{
	BoothPanel* bagPanel = new BoothPanel();
	if(bagPanel && bagPanel->init(type,isHighBooth))
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

bool BoothPanel::init(int type,bool isHighBooth)
{
	if(!CCLayer::init())
	{
		return false;
	}
	m_iBoothType=type;
	
	if (m_iBoothType==-1)
	{
		int data2=CPEventHelper::getEventIntData(CPEventData::VALUE_3);	
		m_iBoothType=data2;
	}
	BoothData::setIsHigh(isHighBooth);

	int count = 0;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		if (it->first >= ItemPos::Market_Bag_Start && it->first < ItemPos::Market_Bag_End)
		{
			count++;
		}
	}
	if (count > 5 && m_iBoothType==Booth_Sell)
	{
		BoothData::setIsHigh(true);
	}

	/*if (GameData::s_user->m_pMainRole->m_bMyBooth)
	{
		m_iBoothType=Booth_Sell;
	}
	else
	{
		m_iBoothType = Booth_Buy;
	}*/

	CCScale9Sprite* m_pBkgSprite = SystemData::getScale9SpriteByPlist("ui.bag.small_bkg", 390, 429);

	if(!m_pBkgSprite)
	{
		return false;
	}
	m_pBkgSprite->setAnchorPoint(CCPointZero);
	m_pBkgSprite->setPosition(ccp(8,8));
	addChild(m_pBkgSprite);

	CCSprite* ptitle=SystemData::getSpriteByPlist("ui_booth_title");
	ptitle->setPosition(SystemData::getLayoutPoint("ui_booth_title"));
	addChild(ptitle);

	std::string boothname=GameData::s_user->m_pMainRole->m_sBoothTargetName+SystemData::getLayoutString("Booth_text");
	if (GameData::s_user->m_pMainRole->m_bMyBooth)
	{
		boothname = SystemData::getLayoutString("Booth_text_my");
	}
	m_pBoothTitle=CCLabelTTF::create(boothname.c_str(),"",20);
	m_pBoothTitle->setColor(ccWHITE);
	if (GameData::s_user->m_pMainRole->m_bMyBooth)
	{
		m_pBoothTitle->setColor(ccc3(0,128,255));
	}
	m_pBoothTitle->setPosition(ptitle->getPosition());
	addChild(m_pBoothTitle);
	
	initBag();
	initBagSlot();

	GeneralMenu* pMenu = GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
	

	initButton();

	//广告 或 留言
	CCScale9Sprite* pborder=SystemData::getScale9SpriteByPlist("ui_booth_text",SystemData::getLayoutValue("ui_booth_text_size.w"),SystemData::getLayoutValue("ui_booth_text_size.h"));
	m_pEditBox = CCEditBox::create(SystemData::getLayoutSize("ui_booth_text_size"),pborder);
	m_pEditBox->setAnchorPoint(CCPointZero);
	m_pEditBox->setDelegate(this);
	m_pEditBox->setInputMode(kEditBoxInputModeAny);
	m_pEditBox->setInputFlag(kEditBoxInputFlagSensitive);
	m_pEditBox->setTouchPriority(kCCMenuHandlerPriority);
	m_pEditBox->setFontSize(16);
	m_pEditBox->setFontColor(ccWHITE);
	m_pEditBox->setPlaceholderFontSize(16);
	m_pEditBox->setMaxLength(30);
	m_pEditBox->setPlaceholderFontColor(ccWHITE);
	m_pEditBox->setPosition(SystemData::getLayoutPoint("ui_booth_text_pos"));
	addChild(m_pEditBox);

	m_padLabel = CCLabelTTF::create(BoothData::getBoothAD().c_str(),"",22,CCSizeMake(SystemData::getLayoutSize("ui_booth_text_size").width-15,SystemData::getLayoutSize("ui_booth_text_size").height),kCCTextAlignmentLeft); 
	m_padLabel->setAnchorPoint(ccp(0,1));
	m_padLabel->setPosition(ccp(SystemData::getLayoutPoint("ui_booth_text_pos").x+5,SystemData::getLayoutPoint("ui_booth_text_pos").y+SystemData::getLayoutValue("ui_booth_text_size.h")-5));
	addChild(m_padLabel);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu,999);


	m_ItemMenu=GeneralMenu::create();
	m_ItemMenu->setPosition(CCPointZero);
	m_ItemMenu->setAnchorPoint(CCPointZero);
	addChild(m_ItemMenu);

	//CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BoothPanel::openSetPrice),NOTIFICATION_ADDITEMMARKET,NULL);																									  
	return true;
}

bool BoothPanel::initBagSlot()
{
	m_startPoint = ccp(41, 305);
	
	// 初始化6个背包页的背景，设置第一页为可见
	for (int i = 0; i<MAX_PACKET_PAGE_COUNT; i++)
	{
		CCSprite* bkgSprite = CCSprite::create();
		if (!bkgSprite)
			break;
		bkgSprite->setAnchorPoint(CCPointZero);
		bkgSprite->setPosition(ccp(0, 0));

		m_packPage[i] = CCLayer::create();
		m_packPage[i]->setTag(i);
		m_packPage[i]->setPosition(ccp(18,93));
		addChild(m_packPage[i]);
		m_packPage[i]->addChild(bkgSprite);
		if (i == 0)
			m_packPage[i]->setVisible(true);
		else
			m_packPage[i]->setVisible(false);
	}

	current_layer = m_packPage[0];
	current_layer_idx = 0;

	// 每页添加CCMenu 

	for (int i=0; i<MAX_PACKET_PAGE_COUNT; i++)
	{
		m_menus[i] = GeneralMenu::create();
		m_menus[i]->setPosition(CCPointZero);
		m_menusItem[i] = GeneralMenu::create();
		m_menusItem[i]->setPosition(CCPointZero);
		m_packPage[i]->addChild(m_menus[i]);
		m_packPage[i]->addChild(m_menusItem[i]);
	}

	// 添加未锁定的包裹格子
	int count=5;
	if (BoothData::getIsHigh())
	{
		count=10;
	}
	if (m_iBoothType==Booth_Buy)
	{
		count=ITEM_BAG_END;
	}
	for (int i = 0;i < ITEM_BAG_END;i++)
	{
		CCSprite* unlockSel = SystemData::getSpriteByPlist("ui.bag.slot.unlock");
		if (unlockSel)
		{
			unlockSel->setPosition(getItemPosition(i));
			unlockSel->setTag(200+i);
			short pos = backLayer(i);
			m_menus[pos]->addChild(unlockSel);
		}
	}
	// 添加锁定的包裹格子
	for(short index = count; index < ITEM_BAG_END; index++)
	{
		CCMenuItemImage* lock = SystemData::getMenuItemImageByPlist("ui.bag.slot.lock");
		if (lock)
		{
			lock->setPosition(getItemPosition(index));
			lock->setTag(200+index);
			short pos = backLayer(index);
			m_menusItem[pos]->addChild(lock);
		}
	}
	if (m_iBoothType==Booth_Sell)
	{
		UserItems items = GameData::s_user->getUserItemData()->userItems;

		for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
		{
			if (isPosInThisPanel(it->first))
			{
				insertItem(it->second,it->first);
			}
		}
	}
	else if (m_iBoothType==Booth_Buy)
	{
		for (std::vector< UserItem* >::iterator it=GameData::s_user->m_pMainRole->m_pMarketItemList.begin();it!=GameData::s_user->m_pMainRole->m_pMarketItemList.end();it++)
		{
			UserItem* p = *it;
			if (isPosInThisPanel(p->position))
			{
				insertItem(p,p->position);
			}
		}
	}
	
	return true;
}


bool BoothPanel::initButton() 
{
	if (m_pDownMenu)
	{
		m_pDownMenu->removeAllChildren();
	}
	else
	{
		m_pDownMenu = GeneralMenu::create();
		m_pDownMenu->setAnchorPoint(CCPointZero);
		m_pDownMenu->setPosition(CCPointZero);
		addChild(m_pDownMenu);
	}
	if (m_iBoothType==Booth_Buy)
	{
		CCMenuItemImage* pButton=SystemData::getMenuItemImageByPlist("ui_booth_button"); 
		pButton->setPosition(SystemData::getLayoutPoint("ui_booth_button1_pos"));
		pButton->setTarget(this,menu_selector(BoothPanel::buttonCallBack));
		pButton->setTag(Button_Message);
		CCLabelTTF* pLabel=SystemData::getLabelTTF("ui_booth_button1_text");
		pLabel->setFontSize(16);
		pLabel->setPosition(ccp(pButton->getContentSize().width/2,pButton->getContentSize().height/2));
		pLabel->setColor(ccWHITE);
		pButton->addChild(pLabel);
		m_pDownMenu->addChild(pButton);

		CCLabelTTF* p=SystemData::getLabelTTF("ui_booth_label1_text");
		p->setFontSize(16);
		p->setPosition(SystemData::getLayoutPoint("ui_booth_label_text_pos"));
		p->setColor(ccWHITE);
		m_pDownMenu->addChild(p);
	}
	else if (m_iBoothType==Booth_Sell)
	{
		CCMenuItemImage* pButton1=SystemData::getMenuItemImageByPlist("ui_booth_button");
		pButton1->setPosition(SystemData::getLayoutPoint("ui_booth_button2_pos"));
		pButton1->setTarget(this,menu_selector(BoothPanel::buttonCallBack));
		pButton1->setTag(Button_Book);
		CCLabelTTF* pLabel1=SystemData::getLabelTTF("ui_booth_button2_text");
		pLabel1->setFontSize(16);
		pLabel1->setPosition(ccp(pButton1->getContentSize().width/2,pButton1->getContentSize().height/2));
		pLabel1->setColor(ccWHITE);
		pButton1->addChild(pLabel1);
		m_pDownMenu->addChild(pButton1);

		CCLabelTTF* p=SystemData::getLabelTTF("ui_booth_label2_text");
		p->setColor(ccWHITE);
		p->setFontSize(16);
		p->setPosition(SystemData::getLayoutPoint("ui_booth_label_text_pos"));
		m_pDownMenu->addChild(p);

		//摆摊叫卖
		CCMenuItemImage* pButton5=SystemData::getMenuItemImageByPlist("ui_booth_button");
		pButton5->setPosition(SystemData::getLayoutPoint("ui_booth_button5_pos"));
		pButton5->setTarget(this,menu_selector(BoothPanel::buttonCallBack));
		pButton5->setTag(Button_TalkWorld);
		CCLabelTTF* pLabel5=SystemData::getLabelTTF("ui_booth_button5_text");
		pLabel5->setFontSize(16);
		pLabel5->setPosition(ccp(pButton5->getContentSize().width/2,pButton5->getContentSize().height/2));
		pLabel5->setColor(ccWHITE);
		pButton5->addChild(pLabel5);
		m_pDownMenu->addChild(pButton5);	
	}
	if (m_iBoothType==Booth_Sell)
	{
		CCMenuItemImage* pButton2=SystemData::getMenuItemImageByPlist("ui_booth_button");
		pButton2->setPosition(SystemData::getLayoutPoint("ui_booth_button3_pos"));
		pButton2->setTarget(this,menu_selector(BoothPanel::buttonCallBack));
		//判断如果处于摆摊状态
		CCLabelTTF* pLabel2=NULL;
		if (HeroData::getProp(Entity::attr_market_state) == 1)
		{
			pButton2->setTag(Button_Over);
			pLabel2=SystemData::getLabelTTF("ui_booth_button4_text");
		}
		else 
		{
			pButton2->setTag(Button_Start);
			pLabel2=SystemData::getLabelTTF("ui_booth_button3_text");
		}
		pLabel2->setFontSize(16);
		pLabel2->setColor(ccWHITE);
		pLabel2->setPosition(ccp(pButton2->getContentSize().width/2,pButton2->getContentSize().height/2));
		pButton2->addChild(pLabel2);
		m_pDownMenu->addChild(pButton2);
	}
	
	return true;
}

void BoothPanel::insertItem( UserItem* userItem, int position )
{
	if (!userItem)
		return;
	
	short pos = backLayer(position-ItemPos::Market_Bag_Start);
	CCMenuItemImage* icon = CommonFunction::getItemIcon(userItem);
	//CCMenuItemImage* icon = CCMenuItemImage::create();
	/*icon->setNormalImage(LayoutData::getItemIcon(userItem->sid));
	icon->setSelectedImage(LayoutData::getItemIcon(userItem->sid));*/
	icon->setTarget(this,menu_selector(BoothPanel::itemClickCallBack));
	icon->setPosition(getItemPosition(position-ItemPos::Market_Bag_Start));
	icon->setTag(position-ItemPos::Market_Bag_Start);
	icon->setVisible(getItemVisible(position-ItemPos::Market_Bag_Start));
	m_menusItem[pos]->addChild(icon);	
}

void BoothPanel::removeItem( int position )
{
	short pos = backLayer(position-ItemPos::Market_Bag_Start);
	m_menus[pos]->removeChildByTag(position-ItemPos::Market_Bag_Start,true);
}

void BoothPanel::updateItemCount( int iid, short count )
{
	UserItem* userItem = GameData::s_user->getUserItemData()->getItemByIid(iid);
	userItem->count = count;
	short position = userItem->position;
	short pos = backLayer(position-ItemPos::Market_Bag_Start);
	CCMenuItemImage* icon = dynamic_cast<CCMenuItemImage*>(m_menus[pos]->getChildByTag(position-ItemPos::Market_Bag_Start));
	CCNode* ccNode = icon->getChildByTag(position);
	CCLabelTTF* countLabel = dynamic_cast<CCLabelTTF*>(icon->getChildByTag(position));
	if(!countLabel)
	{
		countLabel = CCLabelTTF::create("1","Times New Roman",10);
		countLabel->setPosition(ccp(5,5));
		countLabel->setTag(position);
		icon->addChild(countLabel);
	}
	char c_count[5];
	sprintf(c_count, "%d", count);
	countLabel->setString(c_count);
}

cocos2d::CCPoint BoothPanel::getItemPosition( int pos )
{
	pos %= PAGE_NUM;
	return ccpAdd(m_startPoint,ccp(pos%ItemOneLine*ItemSize,-(pos/ItemOneLine*(ItemSize-6)+36)));
}

short BoothPanel::backLayer(int pos)
{
	return (pos/PAGE_NUM);
}

void BoothPanel::buttonCallBack( CCObject* pSender )
{
 	CCMenuItemImage* pMenu = dynamic_cast<CCMenuItemImage*>(pSender);
 	if(pMenu)
 	{
		MsgOpenMarketRequest* req=NULL;
		MsgCloseMarketRequest* msg=NULL;
 		int tag = pMenu->getTag();
		switch(tag)
		{		
		case Button_Start:
			sendStartBooth();
			break;
		case Button_Over:
			msg=new MsgCloseMarketRequest;
			HandleMessage::sendMessage(msg);
			break;
		case Button_TalkWorld:
			if (i_time == 0)
			{
				ChatPanelHelper::sendChatRequest(ChatDefinition::type_world, 0, BoothData::getBoothAD());
				i_time = 30;
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::Sale30sinterval);
			}

			break;
		case Button_Book:
			{

				MsggetMarketWordsRequest* request = new MsggetMarketWordsRequest;
				HandleMessage::sendMessage(request);
				if (!getChildByTag(10))
				{
					BoothSellBook* bspanel = BoothSellBook::create();
					bspanel->setTag(10);
					addChild(bspanel); 
				}
			}
			break;
		case Button_Message:
			{
				if (m_iTimeSpan == 0)
				{
					leaveWord();
					m_iTimeSpan = SystemData::getLayoutValue("leaveword_timespan");
				}
				else
				{
					CPEventHelper::uiNotify("","",Error::time30sspan);
				}  
			}
			break;
 		default: 			
 			break;
 		}
 	}
}


void BoothPanel::leaveWord()
{
	MsgaddMarketWordsRequest* leavewords = new MsgaddMarketWordsRequest;
	std::string str = m_padLabel->getString();
	leavewords->marketid = GameData::s_user->m_pMainRole->m_iTargetpid;
	leavewords->content = str;
	HandleMessage::sendMessage(leavewords);
}

void BoothPanel::Update(float dt)
{
	if (i_time>0)
	{
		i_time--;
	}
	if (m_iTimeSpan > 0)
	{
		m_iTimeSpan--;
	}
}

void BoothPanel::itemClickCallBack( CCObject* pSender )
{
	CCMenuItemImage* pItem = dynamic_cast<CCMenuItemImage*>(pSender);
	if(pItem)
	{
		UserItem* item=(UserItem*)(pItem->getUserData());
		showTooltip(item);
	}
}

void BoothPanel::slotClickCallBack( CCObject* pSender )
{
	CCNode* pItem = dynamic_cast<CCNode*>(pSender);
	if(pItem)
	{
	}
}

bool BoothPanel::isDoubleClickItem( int pos )
{
	float curTime = SystemData::getSystemTime();
	CCLog("prepos: %d, curPos: %d.",m_nPrePos,pos);
	CCLog("pretime: %f, curTime: %f.",m_nPreTime,curTime);
	if(m_nPrePos==pos && curTime-m_nPreTime < DOUBLE_CLICK_TIME)
	{
		m_nPrePos = ITEM_UNUSE_POS;
		m_nPreTime = curTime;
		m_bDoubleClick = true;
		return true;
	}
	m_nPrePos = pos;
	m_nPreTime = curTime;
	m_bDoubleClick = false;
	return false;
}

void BoothPanel::singleClickCallback( float dt )
{
	if(!m_bDoubleClick)
	{
		m_nPrePos = ITEM_UNUSE_POS;
		m_nPreTime = SystemData::getSystemTime();
	}
}

void BoothPanel::showTooltip(UserItem* userItem )
{
	if (userItem==NULL)
	{
		return;
	}
	m_pUserItem=userItem;
	int type=TAG_Tips;
	if(m_iBoothType==Booth_Buy)
	{
		type=TAG_Tips_GMQX;
		//发送请求物品详细信息数据
		MsgItemInfoDataGetRequest* msg=new MsgItemInfoDataGetRequest;
		msg->eid=GameData::s_user->m_pMainRole->m_iTargeteid;
		msg->iid=userItem->iid;
		msg->pid=GameData::s_user->m_pMainRole->m_iTargetpid;
		HandleMessage::sendMessage(msg);
		m_bclickOtherItem = true;
	}
	else
	{
		type=TAG_Tips_XJQX;
		CCPoint pos = ccp(490,180);
		if (userItem->category==ItemCate_Equip || (userItem->category==ItemCate_Extension && userItem->type==ItemType_Pet))
		{
			 pos = ccp(490,10);
		}
		Game::getGameUI()->showTipsPanel(userItem,type,pos);
	}

}

void BoothPanel::handleEvent( int channel )
{
	if (channel == EventProtocol::EVENT_PUTIN_OVER)
	{
		setpricetoSellPanel(m_icurrentPrice);
		m_icurrentPrice = 0;
	}
	else if (channel == EventProtocol::EVENT_MARKETITEM_UPDATA)
	{
		//Game::getGameUI()->showTipsPanel(m_pUserItem,TAG_Tips_GMQX);
	}
}

void BoothPanel::openSetPrice( CCObject* pSender )
{
	if (getChildByTag(Panel_Price))
	{
		getChildByTag(Panel_Price)->setVisible(true);
		return;
	}

	if (pSender==NULL)
	{
		return;
	}
	UserItem* pUserItem=(UserItem*)pSender;
	SellPanel* pPanel=SellPanel::create(pUserItem);
	if (pPanel)
	{
		pPanel->setAnchorPoint(CCPointZero);
		pPanel->setPosition(SystemData::getLayoutPoint("ui_sellpanel_pos"));
		pPanel->setTag(Panel_Price);
		addChild(pPanel);
	}
}

void BoothPanel::openKeyBorad()
{
	if (getChildByTag(Panel_Price))
	{
		getChildByTag(Panel_Price)->setVisible(false);
	}
	//打开计算器
	/*NumberBoard* pKeyBoard=NumberBoard::create(&m_icurrentPrice,1000,EventProtocol::EVENT_PUTIN_OVER,1);
	pKeyBoard->setPosition(SystemData::getLayoutPoint("ui_sellpanel_pos"));
	addChild(pKeyBoard);*/

	Game::getGameUI()->showNumberBoard(&m_icurrentPrice,99999999,EventProtocol::EVENT_PUTIN_OVER,1);
	m_icurrentPrice = 0;
}

void BoothPanel::setpricetoSellPanel( int price )
{
	if (getChildByTag(Panel_Price))
	{
		getChildByTag(Panel_Price)->setVisible(true);
	}
	((SellPanel*)getChildByTag(Panel_Price))->setPrice(price);
}

void BoothPanel::insertOtherItem()
{
	std::vector< UserItem* >::iterator it;
	for (it=GameData::s_user->m_pMainRole->m_pMarketItemList.begin();it!=GameData::s_user->m_pMainRole->m_pMarketItemList.end();it++)
	{
		UserItem* userItem=(UserItem*)*it;
		int position=userItem->position;
		short pos = backLayer(position-ItemPos::Market_Bag_Start);

		CCMenuItemImage* icon = CommonFunction::getItemIcon(userItem);

		icon->setTarget(this,menu_selector(BoothPanel::itemClickCallBack));
		icon->setPosition(getItemPosition(position-ItemPos::Market_Bag_Start));
		icon->setTag(position-ItemPos::Market_Bag_Start);
		//icon->setVisible(getItemVisible(position-ItemPos::Market_Bag_Start));
		m_menusItem[pos]->addChild(icon);
	}
}

void BoothPanel::initBag()
{
	if (GameData::s_user->m_pMainRole->m_bMyBooth)
	{
		m_iBoothType=Booth_Sell;
	}
	else
	{
		m_iBoothType=Booth_Buy;
	}
	if (getChildByTag(98))
	{
		removeChildByTag(98);
	}
	//加载背包
	if (m_iBoothType==Booth_Buy)
	{
		BagPanel* bagPanel = BagPanel::create(5,4,SystemData::getLayoutValue("MaxPlayerBagSlot"),Self_Bag,Bag_Type_Booth_Buy);
		bagPanel->setPosition(ccp(403,8));
		bagPanel->setTag(98);
		addChild(bagPanel);
	}
	else if (m_iBoothType==Booth_Sell)
	{
		BagPanel* bagPanel = BagPanel::create(5,4,SystemData::getLayoutValue("MaxPlayerBagSlot"),Self_Bag,Bag_Type_Booth_Cell);
		bagPanel->setPosition(ccp(403,8));
		bagPanel->setTag(98);
		addChild(bagPanel);
	}
}

void BoothPanel::editBoxEditingDidBegin( extension::CCEditBox *editBox )
{
	//adStr = m_pEditBox->getText();
	m_pEditBox->setText(m_padLabel->getString());
}

void BoothPanel::editBoxReturn( extension::CCEditBox *editBox )
{
	const std::string &str = m_pEditBox->getText();
	m_padLabel->setString(str.substr(0,SystemData::getLayoutValue("singal_leaveword_countOfwords")).c_str());
	BoothData::setBoothAD(str);
	m_pEditBox->setText("");
}

void BoothPanel::sendStartBooth()
{
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	int count = 0;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		if (isPosInThisPanel(it->first))
		{
			count++;
		}
	}
	if (count!=0)
	{
		MsgOpenMarketRequest* req=new MsgOpenMarketRequest;
		req->posx= BoothData::getIsHigh();
		req->posy=BoothData::getIsHigh();		
		HandleMessage::sendMessage(req);
	}
	else
	{
		CPEventHelper::uiNotify("","",Error::MarketCantNone);
	}
}

void BoothPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			Update(1);
		}
	}
	else if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "MsgItemInfoDataGetResponse" )
		{
			if (m_bclickOtherItem)
			{
				Game::getGameUI()->showTipsPanel(m_pUserItem,TAG_Tips_GMQX);
			}
			else
			{
				updateAll();
			}
			m_bclickOtherItem = false;
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageItemRmvNotify" ||
			source == "HandleMessageItemUpdCountNotify" ||
			source == "MsgItemUpdPositionNotify" ||
			source == "HandleMessageItemUpdData" ||
			source == "HandlemessageItemUpdExDataNotify")
		{
			updateAll();
		}

		if (source == "MsgEntityMarketInfoNotify")
		{
			int ishigh =  CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (ishigh==1)
			{
				BoothData::setIsHigh(true);
			}
			else
			{
				BoothData::setIsHigh(false);
			}
			updateAll();
		}
	}
}

void BoothPanel::onEnter()
{
	BasePanel::onEnter();
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BoothPanel::openSetPrice),NOTIFICATION_ADDITEMMARKET,NULL);
}

void BoothPanel::onExit()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,NOTIFICATION_ADDITEMMARKET);
	BasePanel::onExit();
}

void BoothPanel::updateAll()
{
	if (GameData::s_user->m_pMainRole->m_bMyBooth)
	{
		m_iBoothType=Booth_Sell;
	}
	else
	{
		m_iBoothType = Booth_Buy;
	}

	if (m_iBoothType==Booth_Sell)
	{
		UserItems items = GameData::s_user->getUserItemData()->userItems;

		for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
		{
			if (it->first>=(ItemPos::Market_Bag_Start+5))
			{
				BoothData::setIsHigh(true);
			}
		}
	}
	else if (m_iBoothType==Booth_Buy)
	{
		for (std::vector< UserItem* >::iterator it=GameData::s_user->m_pMainRole->m_pMarketItemList.begin();it!=GameData::s_user->m_pMainRole->m_pMarketItemList.end();it++)
		{
			UserItem* p = *it;
			if (p->position>=(ItemPos::Market_Bag_Start+5))
			{
				BoothData::setIsHigh(true); 
			}
		}
		//insertOtherItem();
	}
	initBag();
	initButton();

	std::string boothname=GameData::s_user->m_pMainRole->m_sBoothTargetName+SystemData::getLayoutString("Booth_text");
	if (GameData::s_user->m_pMainRole->m_bMyBooth)
	{
		boothname = SystemData::getLayoutString("Booth_text_my");
	}
	if (GameData::s_user->m_pMainRole->m_bMyBooth)
	{
		m_pBoothTitle->setColor(ccc3(0,128,255));
	}
	else
	{
		m_pBoothTitle->setColor(ccWHITE);
	}
	m_pBoothTitle->setString(boothname.c_str());
	for (int i=0;i<MAX_PACKET_PAGE_COUNT;i++)
	{
		m_menusItem[i]->removeAllChildren();
	}

	// 添加未锁定的包裹格子
	int count=5;
	if (BoothData::getIsHigh())
	{
		count=10;
	}

	for (int i = 0;i < ITEM_BAG_END;i++)
	{
		CCSprite* unlockSel = SystemData::getSpriteByPlist("ui.bag.slot.unlock");
		if (unlockSel)
		{
			unlockSel->setPosition(getItemPosition(i));
			unlockSel->setTag(200+i);
			short pos = backLayer(i);
			m_menus[pos]->addChild(unlockSel);
		}
	}
	// 添加锁定的包裹格子
	for(short index = count; index < ITEM_BAG_END; index++)
	{
		CCMenuItemImage* lock = SystemData::getMenuItemImageByPlist("ui.bag.slot.lock");
		if (lock)
		{
			lock->setPosition(getItemPosition(index));
			lock->setTag(200+index);
			short pos = backLayer(index);
			m_menusItem[pos]->addChild(lock);
		}
	}

	if (m_iBoothType==Booth_Sell)
	{
		UserItems items = GameData::s_user->getUserItemData()->userItems;

		for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
		{
			if (isPosInThisPanel(it->first))
			{
				insertItem(it->second,it->first);
			}
		}
	}
	else if (m_iBoothType==Booth_Buy)
	{
		for (std::vector< UserItem* >::iterator it=GameData::s_user->m_pMainRole->m_pMarketItemList.begin();it!=GameData::s_user->m_pMainRole->m_pMarketItemList.end();it++)
		{
			UserItem* p = *it;
			if (isPosInThisPanel(p->position))
			{
				insertItem(p,p->position);
			}
		}
		//insertOtherItem();
	}

}

//------------------------------------------------------------------------------------------------------------------------//


SellPanel::SellPanel():
	m_pSellTypeLabel(NULL),
	m_pSelectSprite(NULL),
	m_pSellPrice(NULL),
	m_pUserItem(NULL),
	m_iCurrentSellType(0),
	m_iPrice(0)
{

}

SellPanel::~SellPanel()
{

}

SellPanel* SellPanel::create(UserItem* pUserItem)
{
	SellPanel* bagPanel = new SellPanel();
	if(bagPanel && bagPanel->init(pUserItem))
	{
		bagPanel->autorelease();
		return bagPanel;
	}

	delete bagPanel;
	return NULL;
}

//bool SellPanel::init(UserItem* pUserItem)
//{
//	m_pUserItem=pUserItem;
//	if (m_pUserItem==NULL)
//	{
//		return false;
//	}
//
//	m_nHeight=640;
//	m_nWidth=800;
//	addCover();  
//
//	CCSprite*  pborder=SystemData::getSpriteByPlist("ui_sellpanel_border");
//	pborder->setAnchorPoint(CCPointZero);
//	addChild(pborder);
//
//	CCSprite* pItem=SystemData::getSpriteByPlist("ui_sellpanel_item");
//	pItem->setPosition(SystemData::getLayoutPoint("ui_sellpanel_item_pos"));
//	addChild(pItem);
//
//
//	CCScale9Sprite* ptext1=SystemData::getScale9SpriteByPlist("ui_sellpanel_text",SystemData::getLayoutValue("ui_sellpanel_text_size.w"),SystemData::getLayoutValue("ui_sellpanel_text_size.h"));
//	ptext1->setPosition(SystemData::getLayoutPoint("ui_sellpanel_text1_pos"));
//	//addChild(ptext1);
//
//
//	CCLabelTTF* pitemcount=CCLabelTTF::create(SystemData::intToString(pUserItem->count).c_str(),"微软雅黑",20);
//	pitemcount->setPosition(SystemData::getLayoutPoint("ui_sellpanel_text1_pos"));
//	addChild(pitemcount);
//	 
//	CCLabelTTF* p1=SystemData::getLabelTTF("ui_sellpanel_SL");
//	p1->setColor(ccWHITE);
//	p1->setAnchorPoint(ccp(1,0.5));
//	p1->setFontSize(20);
//	p1->setPosition(ccp(ptext1->getPositionX()-ptext1->getContentSize().width/2,ptext1->getPositionY()));
//	addChild(p1);
//
//	CCMenu* pMenu=CCMenu::create();
//	pMenu->setPosition(CCPointZero);
//	pMenu->setAnchorPoint(CCPointZero);
//	addChild(pMenu);
//
//	CCScale9Sprite* ptext2=SystemData::getScale9SpriteByPlist("ui_sellpanel_text",SystemData::getLayoutValue("ui_sellpanel_text_size.w"),SystemData::getLayoutValue("ui_sellpanel_text_size.h"));
//	CCMenuItemSprite* ptext=CCMenuItemSprite::create(ptext2,ptext2,NULL,this,menu_selector(SellPanel::MenuCallBack));
//	ptext->setPosition(SystemData::getLayoutPoint("ui_sellpanel_text2_pos"));
//	ptext->setTag(Text_PutIn);
//	pMenu->addChild(ptext); 
//	 
//	 
//	CCLabelTTF* p2=SystemData::getLabelTTF("ui_sellpanel_SJ");
//	p2->setColor(ccWHITE);
//	p2->setFontSize(20);
//	p2->setAnchorPoint(ccp(1,0.5));
//	p2->setPosition(ccp(ptext->getPositionX()-ptext->getContentSize().width/2,ptext->getPositionY()));
//	addChild(p2); 
//
//	CCMenuItemImage* pbutton=SystemData::getMenuItemImageByPlist("ui_sellpanel_button");
//	pbutton->setTarget(this,menu_selector(SellPanel::MenuCallBack));
//	pbutton->setTag(Button_OK);
//	pbutton->setPosition(SystemData::getLayoutPoint("ui_sellpanel_button_pos"));
//	pMenu->addChild(pbutton);
//
//
//	CCLabelTTF* p3=SystemData::getLabelTTF("ui_sellpanel_QD");
//	p3->setPosition(SystemData::getLayoutPoint("ui_sellpanel_button_pos"));
//	p3->setColor(ccWHITE);
//	p3->setFontSize(18);
//	addChild(p3);
//
//	CCMenuItemImage* pclose=SystemData::getMenuItemImageByPlist("ui_sellpanel_close");
//	pclose->setTarget(this,menu_selector(SellPanel::close));
//	pclose->setPosition(SystemData::getLayoutPoint("ui_sellpanel_close_pos"));
//	pMenu->addChild(pclose);
//
//	CCMenuItemImage* pleftblock=SystemData::getMenuItemImageByPlist("ui_sellpanel_block");
//	pleftblock->setPosition(SystemData::getLayoutPoint("ui_sellpanel_leftblock_pos"));
//	pleftblock->setTarget(this,menu_selector(SellPanel::MenuCallBack));
//	pleftblock->setTag(Left_Block);
//	pMenu->addChild(pleftblock);
//	CCLabelTTF* plefttext=SystemData::getLabelTTF("ui_sellpanel_YJBCS");
//	plefttext->setPosition(ccp(pleftblock->getContentSize().width,pleftblock->getContentSize().height/2));
//	plefttext->setColor(ccYELLOW);
//	plefttext->setFontSize(18);
//	plefttext->setAnchorPoint(ccp(0,0.5));
//	pleftblock->addChild(plefttext);
//
//	CCMenuItemImage* prightblock=SystemData::getMenuItemImageByPlist("ui_sellpanel_block");
//	prightblock->setPosition(SystemData::getLayoutPoint("ui_sellpanel_rightblock_pos"));
//	prightblock->setTarget(this,menu_selector(SellPanel::MenuCallBack));
//	prightblock->setTag(Right_Block);
//	pMenu->addChild(prightblock);
//	CCLabelTTF* prighttext=SystemData::getLabelTTF("ui_sellpanel_YYBCS");
//	prighttext->setPosition(ccp(prightblock->getContentSize().width,pleftblock->getContentSize().height/2));
//	prighttext->setColor(ccYELLOW); 
//	prighttext->setFontSize(18);
//	prighttext->setAnchorPoint(ccp(0,0.5));
//	prightblock->addChild(prighttext);
//	 
//	//默认金币出售
//	m_pSelectSprite=SystemData::getSpriteByPlist("ui_sellpanel_isblock");
//	m_pSelectSprite->setPosition(SystemData::getLayoutPoint("ui_sellpanel_leftblock_pos"));
//	addChild(m_pSelectSprite);
//
//	m_pSellTypeLabel=SystemData::getLabelTTF("ui_sellpanel_JB");
//	m_pSellTypeLabel->setColor(ccWHITE);
//	m_pSellTypeLabel->setAnchorPoint(ccp(0,0.5));
//	m_pSellTypeLabel->setFontSize(20);
//	m_pSellTypeLabel->setPosition(ccp(ptext->getPositionX()+ptext->getContentSize().width/2+20,ptext->getPositionY()));
//	addChild(m_pSellTypeLabel);
//
//	m_iCurrentSellType=Left_Block;
//
//	//出售价格
//	m_pSellPrice=CCLabelTTF::create("0","微软雅黑",18);
//	m_pSellPrice->setPosition(SystemData::getLayoutPoint("ui_sellpanel_text2_pos"));
//	m_pSellPrice->setColor(ccWHITE);
//	addChild(m_pSellPrice);
//
//
//	CCMenuItemImage* icon=CommonFunction::getItemIcon(pUserItem);
//	icon->setPosition(SystemData::getLayoutPoint("ui_sellpanel_item_pos"));
//	pMenu->addChild(icon);
//
//	CCLabelTTF* pname=CCLabelTTF::create(pUserItem->name.c_str(),"微软雅黑",20);
//	pname->setAnchorPoint(CCPointZero);
//	pname->setPosition(SystemData::getLayoutPoint("ui_sellpanel_itemname_pos"));
//	addChild(pname);
//
//	return true;
//}
bool SellPanel::init(UserItem* pUserItem)
{
	m_pUserItem = pUserItem;
	if (m_pUserItem == NULL) return false;

	m_nHeight = 640;
	m_nWidth = 800;
    
    // === 1. 先设置面板位置（在添加任何子节点之前）===
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(CCSize(m_nWidth, m_nHeight));
    this->setAnchorPoint(ccp(0.5f, 0.5f));
    this->setPosition(ccp(winSize.width/2 - 100, winSize.height/2));
   
    
	addCover();
    
    // === 2. 创建容器节点 ===
    CCNode* container = CCNode::create();
    container->setPosition(CCPointZero);
    container->setAnchorPoint(ccp(0.5f, 0.5f));
    
    // === 3. 将所有子节点添加到容器（保持原始坐标）===
	CCSprite* pborder = SystemData::getSpriteByPlist("ui_sellpanel_border");
	pborder->setAnchorPoint(CCPointZero);
	container->addChild(pborder);

	CCSprite* pItem = SystemData::getSpriteByPlist("ui_sellpanel_item");
	pItem->setPosition(SystemData::getLayoutPoint("ui_sellpanel_item_pos"));
	container->addChild(pItem);

	CCScale9Sprite* ptext1 = SystemData::getScale9SpriteByPlist("ui_sellpanel_text",
		SystemData::getLayoutValue("ui_sellpanel_text_size.w"),
		SystemData::getLayoutValue("ui_sellpanel_text_size.h"));
	ptext1->setPosition(SystemData::getLayoutPoint("ui_sellpanel_text1_pos"));
	// container->addChild(ptext1);

	CCLabelTTF* pitemcount = CCLabelTTF::create(SystemData::intToString(pUserItem->count).c_str(), "微软雅黑", 20);
	pitemcount->setPosition(SystemData::getLayoutPoint("ui_sellpanel_text1_pos"));
	container->addChild(pitemcount);
	 
	CCLabelTTF* p1 = SystemData::getLabelTTF("ui_sellpanel_SL");
	p1->setColor(ccWHITE);
	p1->setAnchorPoint(ccp(1, 0.5));
	p1->setFontSize(20);
	p1->setPosition(ccp(ptext1->getPositionX() - ptext1->getContentSize().width/2, ptext1->getPositionY()));
	container->addChild(p1);

	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);
	container->addChild(pMenu);

	CCScale9Sprite* ptext2 = SystemData::getScale9SpriteByPlist("ui_sellpanel_text",
		SystemData::getLayoutValue("ui_sellpanel_text_size.w"),
		SystemData::getLayoutValue("ui_sellpanel_text_size.h"));
	CCMenuItemSprite* ptext = CCMenuItemSprite::create(ptext2, ptext2, NULL, this, menu_selector(SellPanel::MenuCallBack));
	ptext->setPosition(SystemData::getLayoutPoint("ui_sellpanel_text2_pos"));
	ptext->setTag(Text_PutIn);
	pMenu->addChild(ptext);
	 
	CCLabelTTF* p2 = SystemData::getLabelTTF("ui_sellpanel_SJ");
	p2->setColor(ccWHITE);
	p2->setFontSize(20);
	p2->setAnchorPoint(ccp(1, 0.5));
	p2->setPosition(ccp(ptext->getPositionX() - ptext->getContentSize().width/2, ptext->getPositionY()));
	container->addChild(p2);

	CCMenuItemImage* pbutton = SystemData::getMenuItemImageByPlist("ui_sellpanel_button");
	pbutton->setTarget(this, menu_selector(SellPanel::MenuCallBack));
	pbutton->setTag(Button_OK);
	pbutton->setPosition(SystemData::getLayoutPoint("ui_sellpanel_button_pos"));
	pMenu->addChild(pbutton);

	CCLabelTTF* p3 = SystemData::getLabelTTF("ui_sellpanel_QD");
	p3->setPosition(SystemData::getLayoutPoint("ui_sellpanel_button_pos"));
	p3->setColor(ccWHITE);
	p3->setFontSize(18);
	container->addChild(p3);

	CCMenuItemImage* pclose = SystemData::getMenuItemImageByPlist("ui_sellpanel_close");
	pclose->setTarget(this, menu_selector(SellPanel::close));
	pclose->setPosition(SystemData::getLayoutPoint("ui_sellpanel_close_pos"));
	pMenu->addChild(pclose);

	CCMenuItemImage* pleftblock = SystemData::getMenuItemImageByPlist("ui_sellpanel_block");
	pleftblock->setPosition(SystemData::getLayoutPoint("ui_sellpanel_leftblock_pos"));
	pleftblock->setTarget(this, menu_selector(SellPanel::MenuCallBack));
	pleftblock->setTag(Left_Block);
	pMenu->addChild(pleftblock);
	
	CCLabelTTF* plefttext = SystemData::getLabelTTF("ui_sellpanel_YJBCS");
	plefttext->setPosition(ccp(pleftblock->getContentSize().width, pleftblock->getContentSize().height/2));
	plefttext->setColor(ccYELLOW);
	plefttext->setFontSize(18);
	plefttext->setAnchorPoint(ccp(0, 0.5));
	pleftblock->addChild(plefttext);

	CCMenuItemImage* prightblock = SystemData::getMenuItemImageByPlist("ui_sellpanel_block");
	prightblock->setPosition(SystemData::getLayoutPoint("ui_sellpanel_rightblock_pos"));
	prightblock->setTarget(this, menu_selector(SellPanel::MenuCallBack));
	prightblock->setTag(Right_Block);
	pMenu->addChild(prightblock);
	
	CCLabelTTF* prighttext = SystemData::getLabelTTF("ui_sellpanel_YYBCS");
	prighttext->setPosition(ccp(prightblock->getContentSize().width, pleftblock->getContentSize().height/2));
	prighttext->setColor(ccYELLOW);
	prighttext->setFontSize(18);
	prighttext->setAnchorPoint(ccp(0, 0.5));
	prightblock->addChild(prighttext);
	 
	m_pSelectSprite = SystemData::getSpriteByPlist("ui_sellpanel_isblock");
	m_pSelectSprite->setPosition(SystemData::getLayoutPoint("ui_sellpanel_leftblock_pos"));
	container->addChild(m_pSelectSprite);

	m_pSellTypeLabel = SystemData::getLabelTTF("ui_sellpanel_JB");
	m_pSellTypeLabel->setColor(ccWHITE);
	m_pSellTypeLabel->setAnchorPoint(ccp(0, 0.5));
	m_pSellTypeLabel->setFontSize(20);
	m_pSellTypeLabel->setPosition(ccp(ptext->getPositionX() + ptext->getContentSize().width/2 + 20, ptext->getPositionY()));
	container->addChild(m_pSellTypeLabel);

	m_iCurrentSellType = Left_Block;

	m_pSellPrice = CCLabelTTF::create("0", "微软雅黑", 18);
	m_pSellPrice->setPosition(SystemData::getLayoutPoint("ui_sellpanel_text2_pos"));
	m_pSellPrice->setColor(ccWHITE);
	container->addChild(m_pSellPrice);

	CCMenuItemImage* icon = CommonFunction::getItemIcon(pUserItem);
	icon->setPosition(SystemData::getLayoutPoint("ui_sellpanel_item_pos"));
	pMenu->addChild(icon);

	CCLabelTTF* pname = CCLabelTTF::create(pUserItem->name.c_str(), "微软雅黑", 20);
	pname->setAnchorPoint(CCPointZero);
	pname->setPosition(SystemData::getLayoutPoint("ui_sellpanel_itemname_pos"));
	container->addChild(pname);
    
    // === 4. 将容器添加到面板 ===
    this->addChild(container);
    
    // === 5. 移动容器而不是面板 ===
    // 计算需要移动的距离
    CCPoint containerWorldPos = container->convertToWorldSpace(CCPointZero);
   
    
    // 如果想向左移动470，直接移动容器
    container->setPositionX(container->getPositionX() - 470);
    
	return true;
}
void SellPanel::MenuCallBack( CCObject* pSender )
{
	CCLog("SellPanel Click");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag=pNode->getTag();
		switch (tag)
		{
		case Left_Block:
			m_pSelectSprite->setPosition(SystemData::getLayoutPoint("ui_sellpanel_leftblock_pos"));
			m_iCurrentSellType=Left_Block;
			m_pSellTypeLabel->setString(SystemData::getLayoutString("ui_sellpanel_JB").c_str());
			break;
		case Right_Block:
			m_pSelectSprite->setPosition(SystemData::getLayoutPoint("ui_sellpanel_rightblock_pos"));
			m_iCurrentSellType=Right_Block;
			m_pSellTypeLabel->setString(SystemData::getLayoutString("ui_sellpanel_YB").c_str());
			break;
		case Button_OK:
			if (m_iPrice==0)
			{
				//提示不能出售0元
			}
			else
			{
				postBoothUP();
			}
			break;
		case Text_PutIn:
			((BoothPanel*)(this->getParent()))->openKeyBorad();
			break;
		default:
			break;
		}
	}
}
// 函数名：postBoothUP - 发布/上架摊位
// 功能：处理玩家摆摊上架物品的逻辑
// 注释：这是摆摊系统的上架功能，玩家可以在此函数中设置物品售价并上架
void SellPanel::postBoothUP()
{
	if (checkIfCanpostUp())
	{
		MsgMarketSetItemRequest* req=new MsgMarketSetItemRequest;
		req->iid=m_pUserItem->iid;
		if (m_iCurrentSellType==Left_Block)
		{
			req->selltype=Entity::attr_diamond;//金币改仙玉
		}
		else
		{
			req->selltype=Entity::attr_gold;
		}
		req->sellprice=m_iPrice;
		req->sellcnt=m_pUserItem->count;
		req->position=GameData::s_user->getUserItemData()->getEmptyPosition(ItemPos::Market_Bag_Start);
		HandleMessage::sendMessage(req);
	}
	else
	{
		CPEventHelper::uiNotify("","",Error::BoothUpTypeLimit);
	}
	this->removeFromParent();
}

void SellPanel::setPrice( int price )
{
	m_pSellPrice->setString(SystemData::intToString(price).c_str());
	m_iPrice=price;
}

void SellPanel::close( CCObject* pSender )
{
	this->removeFromParent();
}

bool SellPanel::checkIfCanpostUp()
{
	int count = 0;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		if (it->first >= ItemPos::Market_Bag_Start && it->first < ItemPos::Market_Bag_End)
		{
			count++;
		}
	}
	bool isHigh = BoothData::getIsHigh();
	if (!isHigh)
	{
		if (count<5)
		{
			return true;
		}
		else
		{
			return false;
		}
	}else
	{
		if (count >= 10)
		{
			return false;
		}
		return true;
	}
}
