#include "NumberKeyboard.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "event/EventDispatcher.h"
#include "event/EventProtocol.h"
#include "script/LuaWrapper.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/UserItemData.h"
#include "scene/Game.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "controls/CPItemComponents.h"
#include "ext/GeneralMenu.h"
#include "utils/StringUtils.h"
#include "userdata/HeroData.h"
#include "EntityDefinition.h"
#include "ShopPanel.h"
#include "NpcShopPanel.h"
#include "MsgShop.h"
#include "network/HandleMessage.h"
#include "MsgItem.h"

NumberBoard::NumberBoard()
	: m_nMaxValue(0)
	,mValue(1)
	, m_pValue(NULL)
	, m_pShowNum(NULL)
	, m_nCurPrice(0)
	,m_nEventType(0)
	, m_pShowMoney(NULL)
	, m_pCurLabel(NULL)
	,mTarget(NULL)
	,mHandleFunc(NULL)
{
}

NumberBoard::~NumberBoard()
{

}

NumberBoard* NumberBoard::create( int* pValue, int MaxValue, int eventtype, int price )
{
	NumberBoard* pNumberBoard = new NumberBoard;
	if(pNumberBoard && pNumberBoard->init(pValue,MaxValue,eventtype,price))
	{
		pNumberBoard->autorelease();
		return pNumberBoard;
	}
	if(pNumberBoard)
	{
		delete pNumberBoard;
	}
	return NULL;
}

NumberBoard* NumberBoard::create( int defaultValue, int maxValue, int price)
{
	NumberBoard* ret = new NumberBoard;
	if(ret && ret->init(defaultValue, maxValue, price))
	{
		ret->autorelease();
		return ret;
	}
	
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

void NumberBoard::onEnter()
{
	registerWithTouchDispatcher();
	CCNode::onEnter();	
}

void NumberBoard::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}
bool NumberBoard::init( int* pValue, int MaxValue, int eventtype, int price )
{
	m_nMaxValue = MaxValue;
	m_nEventType = eventtype;
	m_nCurPrice = price;
	if (pValue)
	{
		m_pValue = pValue;
		if (*m_pValue==0)
		{
			*m_pValue=0;
		}
		mValue = *m_pValue;
	}
	 
	CCScale9Sprite* pBkg = SystemData::getScale9SpriteByPlist("keyboard.sprite.bkg");
	addChild(pBkg);
	CCScale9Sprite* pBkg1 = SystemData::getScale9SpriteByPlist("keyboard.sprite.bkg");
	addChild(pBkg1);
	 
	m_nWidth = pBkg->getContentSize().width;
	m_nHeight = pBkg->getContentSize().height;
	addCover();

	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	//add the close button on the top right corner
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("keyboard.btn.close");
	pClose->setTarget(this,menu_selector(NumberBoard::closeCallback));
	pMenu->addChild(pClose);

	//add the increase and decrease arrow
	CCMenuItemImage* pIncrease = SystemData::getMenuItemImageByPlist("keyboard.btn.increase");
	pIncrease->setTarget(this,menu_selector(NumberBoard::increaseCallback));
	pMenu->addChild(pIncrease);
	CCMenuItemImage* pDecrease = SystemData::getMenuItemImageByPlist("keyboard.btn.decrease");
	pDecrease->setTarget(this,menu_selector(NumberBoard::decreaseCallback));
	pMenu->addChild(pDecrease);
	CCSprite *childSprite = dynamic_cast<CCSprite *>(pDecrease->getChildByTag(0x1));
	if (childSprite)
	{
		childSprite->setFlipX(true);
	}
	childSprite = dynamic_cast<CCSprite *>(pDecrease->getChildByTag(0x2));
	if (childSprite)
	{
		childSprite->setFlipX(true);
	}

	//add the confirm button
	CCMenuItemImage* pConfirm = SystemData::getMenuItemImageByPlist("keyboard.btn.confirm");
	pConfirm->setTarget(this,menu_selector(NumberBoard::confirmCallback));
	pMenu->addChild(pConfirm);
	CCLabelTTF* pConfirmLabel = SystemData::getLabelTTF("keyboard.lbl.confirm");
	pConfirmLabel->setFontSize(18);
	addChild(pConfirmLabel);

	//add the number keys
	CCPoint numbegin = SystemData::getLayoutPoint("keyboard.point.numbegin");
	CCSize  numberSize = SystemData::getLayoutSize("keyboard.size.keyspan");
	std::string numKey[12] = {"btn_1_","btn_2_","btn_3_","btn_10_shanchu_","btn_4_","btn_5_","btn_6_","btn_11_zuida","btn_7_","btn_8_","btn_9_","btn_0_"};
	for(int i=0; i<12; i++)	
	{
		const std::string &key = numKey[i] + ".png";
		const std::string &key_sel = numKey[i] + (i == 7 ? "_sel.png" : "sel.png");
		CCMenuItemImage* pItem = CCMenuItemImage::create();
		pItem->setNormalImage(LayoutData::getSpriteByFrameName(key));
		pItem->setSelectedImage(LayoutData::getSpriteByFrameName(key_sel));
		pItem->setAnchorPoint(CCPointZero);
		pItem->setPosition(ccpAdd(numbegin,ccp(i%4*numberSize.width,-i/4*numberSize.height)));
		if('0' <=numKey[i][4] && numKey[i][4] <= '9'
			&& numKey[i][5] == '_')	
		{
			pItem->setTag(numKey[i][4]-'0');
			pItem->setTarget(this,menu_selector(NumberBoard::touchCallback));
		}
		else
		{
			if(numKey[i][5] == '0')
			{
				pItem->setTarget(this,menu_selector(NumberBoard::deleteCallback));
			}
			else
			{
				pItem->setTarget(this,menu_selector(NumberBoard::maxCallback));
			}
		}
		pMenu->addChild(pItem);
	}
	CCScale9Sprite* pNumBkg = SystemData::getScale9SpriteByPlist("keyboard.sprite.numbkg");	
	addChild(pNumBkg);
	m_pCurLabel = SystemData::getLabelTTF("keyboard.lbl.totalcost");
	addChild(m_pCurLabel);
	m_pShowMoney = SystemData::getLabelTTF("keyboard.lbl.totalmoney");
	addChild(m_pShowMoney);
	m_pShowNum = SystemData::getLabelTTF("keyboard.lbl.curnum");
	addChild(m_pShowNum);

	CCSprite* pLine=SystemData::getSpriteByPlist("keyboard.lbl.line");
	pLine->setPosition(SystemData::getLayoutPoint("keyboard.lbl.line"));
	addChild(pLine);
	 
	showInput();
	return true;
}

bool NumberBoard::init( int defaultValue, int maxValue, int price)
{
	if (init(NULL, maxValue, 0, price))
	{
		mValue = defaultValue;
		if (mValue < 0)
		{
			mValue = 0;
		}
		return true;
	}
	return false;
}

void NumberBoard::touchCallback( CCObject* pSender )
{
	CCNode* pNode = (CCNode*)pSender;
	if(pNode)
	{
		int tag = pNode->getTag();
		int curValue = mValue * 10 + tag;
		if(curValue > m_nMaxValue)
		{
			curValue = m_nMaxValue;
		}
		mValue = curValue;
		showInput();
	}
}

void NumberBoard::confirmCallback( CCObject* pSender )
{
	if (mTarget && mHandleFunc)
	{
		(mTarget->*mHandleFunc)(mValue);
	}

	if (m_nEventType > 0)
	{
		if (m_pValue)
		{
			*m_pValue = mValue;
		}
		EventDispatcher::sharedEventDispather()->dispatchEvent(m_nEventType);
	}
	
	this->removeFromParent();
}

void NumberBoard::closeCallback( CCObject* pSender )
{
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PUTIN_OVER);
	this->removeFromParent();
}

void NumberBoard::deleteCallback( CCObject* pSender )
{
	mValue /= 10;	
	showInput();
}

void NumberBoard::maxCallback( CCObject* pSender )
{
	mValue = m_nMaxValue;
	showInput();
}

void NumberBoard::increaseCallback( CCObject* pSender )
{
	mValue += 1;
	if (mValue > m_nMaxValue)
	{
		mValue = m_nMaxValue;
	}
	showInput();
}

void NumberBoard::decreaseCallback( CCObject* pSender )
{
	if (mValue > 0)
	{
		mValue -= 1;
	}
	showInput();
}

void NumberBoard::showInput()
{
	std::string num = SystemData::intToString(mValue);
	if (m_pShowNum)
	{
		m_pShowNum->setString(num.c_str());
	}
	std::string money = SystemData::intToString(mValue * m_nCurPrice);
	if (m_pShowMoney)
	{
		m_pShowMoney->setString(money.c_str());
	}
}

void NumberBoard::setCurLabelStr( std::string str )
{
	m_pCurLabel->setString(AToU8(str.c_str()));
}

void NumberBoard::setHandler( CCObject *target, SEL_NumberPanel func )
{
	mTarget = target;
	mHandleFunc = func;
}

void NumberBoard::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool NumberBoard::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void NumberBoard::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void NumberBoard::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos=pTouch->getLocation();
	CCRect rect=CCRectMake(0,0,m_nWidth,m_nHeight);
	if (!rect.containsPoint( this->convertToNodeSpace(pos)))
	{
		this->removeFromParent();
	}
}

void NumberBoard::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}


//////////////////////////////////////////////////////////////////////////

NumberKeyBoard::NumberKeyBoard()
	: m_nMaxValue(0)
	, m_pValue(0)
	, m_pShowNum(NULL)
	//, m_nCurPrice(0)
	, m_pShowMoney(NULL)
	, m_pCurLabel(NULL)
	, m_pListener(NULL)
	, m_pfnSelector(NULL)
	, m_nCurPrice(0)
	, m_nType(0)
	, m_nSid(0)
	,m_UserIid(0)
{
}

NumberKeyBoard::~NumberKeyBoard()
{

}

NumberKeyBoard* NumberKeyBoard::create(int curValue,int MaxValue)
{
	NumberKeyBoard* pNumberKeyBoard = new NumberKeyBoard;
	if(pNumberKeyBoard && pNumberKeyBoard->init(curValue,MaxValue))
	{
		pNumberKeyBoard->autorelease();
		return pNumberKeyBoard;
	}
	if(pNumberKeyBoard)
	{
		delete pNumberKeyBoard;
	}
	return NULL;
}

NumberKeyBoard* NumberKeyBoard::create(int curValue,int MaxValue,int tag,int iid,int str)
{
	NumberKeyBoard* pNumberKeyBoard = new NumberKeyBoard;
	if(pNumberKeyBoard && pNumberKeyBoard->init(curValue,MaxValue,iid))
	{
		pNumberKeyBoard->autorelease();
		return pNumberKeyBoard;
	}
	if(pNumberKeyBoard)
	{
		delete pNumberKeyBoard;
	}
	return NULL;
}

NumberKeyBoard* NumberKeyBoard::create( int defaultValue, int maxValue, int price, int sid)
{
	NumberKeyBoard* ret = new NumberKeyBoard;
	if(ret && ret->init(defaultValue, maxValue, price,sid))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}
void NumberKeyBoard::onEnter()
{
	registerWithTouchDispatcher();
	CCNode::onEnter();	
}

void NumberKeyBoard::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}

bool NumberKeyBoard::init(int curValue,int MaxValue,int iid)
{
	m_UserIid = iid;
	return init(curValue,MaxValue);
}

bool NumberKeyBoard::init(int curValue,int MaxValue)
{
	m_pValue = curValue;
	m_nMaxValue = MaxValue;
	if (m_pValue>m_nMaxValue)
	{
		m_pValue=m_nMaxValue;
	}
	
	CCScale9Sprite* pBkg = SystemData::getScale9SpriteByPlist("keyboard.sprite.bkg");
	addChild(pBkg);
	CCScale9Sprite* pBkg1 = SystemData::getScale9SpriteByPlist("keyboard.sprite.bkg");
	addChild(pBkg1);
	 
	m_nWidth = pBkg->getContentSize().width;
	m_nHeight = pBkg->getContentSize().height;
	addCover();

	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	//add the close button on the top right corner
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("keyboard.btn.close");
	pClose->setTarget(this,menu_selector(NumberKeyBoard::closeCallback));
	pMenu->addChild(pClose);

	//add the increase and decrease arrow
	CCMenuItemImage* pIncrease = SystemData::getMenuItemImageByPlist("keyboard.btn.increase");
	pIncrease->setTarget(this,menu_selector(NumberKeyBoard::increaseCallback));
	pMenu->addChild(pIncrease);
	CCMenuItemImage* pDecrease = SystemData::getMenuItemImageByPlist("keyboard.btn.decrease");
	pDecrease->setTarget(this,menu_selector(NumberKeyBoard::decreaseCallback));
	pMenu->addChild(pDecrease);
	CCSprite *childSprite = dynamic_cast<CCSprite *>(pDecrease->getChildByTag(0x1));
	if (childSprite)
	{
		childSprite->setFlipX(true);
	}
	childSprite = dynamic_cast<CCSprite *>(pDecrease->getChildByTag(0x2));
	if (childSprite)
	{
		childSprite->setFlipX(true);
	}

	//add the confirm button
	CCMenuItemImage* pConfirm = SystemData::getMenuItemImageByPlist("keyboard.btn.confirm");
	pConfirm->setTarget(this,menu_selector(NumberKeyBoard::confirmCallback));
	pMenu->addChild(pConfirm);
	CCLabelTTF* pConfirmLabel = SystemData::getLabelTTF("keyboard.lbl.confirm");
	pConfirmLabel->setFontSize(18);
	addChild(pConfirmLabel);

	//add the number keys
	CCPoint numbegin = SystemData::getLayoutPoint("keyboard.point.numbegin");
	CCSize  numberSize = SystemData::getLayoutSize("keyboard.size.keyspan");
	std::string numKey[12] = {"btn_1_","btn_2_","btn_3_","btn_10_shanchu_","btn_4_","btn_5_","btn_6_","btn_11_zuida","btn_7_","btn_8_","btn_9_","btn_0_"};
	for(int i=0; i<12; i++)	
	{
		const std::string &key = numKey[i] + ".png";
		const std::string &key_sel = numKey[i] + (i == 7 ? "_sel.png" : "sel.png");
		CCMenuItemImage* pItem = CCMenuItemImage::create();
		pItem->setNormalImage(LayoutData::getSpriteByFrameName(key));
		pItem->setSelectedImage(LayoutData::getSpriteByFrameName(key_sel));
		pItem->setAnchorPoint(CCPointZero);
		pItem->setPosition(ccpAdd(numbegin,ccp(i%4*numberSize.width,-i/4*numberSize.height)));
		if('0' <=numKey[i][4] && numKey[i][4] <= '9'
			&& numKey[i][5] == '_')	
		{
			pItem->setTag(numKey[i][4]-'0');
			pItem->setTarget(this,menu_selector(NumberKeyBoard::touchCallback));
		}
		else
		{
			if(numKey[i][5] == '0')
			{
				pItem->setTarget(this,menu_selector(NumberKeyBoard::deleteCallback));
			}
			else
			{
				pItem->setTarget(this,menu_selector(NumberKeyBoard::maxCallback));
			}
		}
		pMenu->addChild(pItem);
	}
	CCScale9Sprite* pNumBkg = SystemData::getScale9SpriteByPlist("keyboard.sprite.numbkg");	
	addChild(pNumBkg);
	if (!(m_UserIid))
	{
		m_pCurLabel = SystemData::getLabelTTF("keyboard.lbl.donatecount");
		addChild(m_pCurLabel);
		m_pShowMoney = SystemData::getLabelTTF("keyboard.lbl.totalmoney");
		addChild(m_pShowMoney);
	}
	m_pShowNum = SystemData::getLabelTTF("keyboard.lbl.curnum"); 
	addChild(m_pShowNum);

	CCSprite* pLine=SystemData::getSpriteByPlist("keyboard.lbl.line");
	pLine->setPosition(SystemData::getLayoutPoint("keyboard.lbl.line"));
	addChild(pLine);
	 
	showInput();
	return true;
}
bool NumberKeyBoard::init(int defaultValue, int vType, int price ,int sid)
{
	m_nType = vType;
	m_nSid = sid;
	int buyType = Entity::attr_gold;
	if (vType==ShopPanel::TAG_SHOP_COUPON)
	{
		buyType=Entity::attr_diamond;
	}
	else if (vType==ShopPanel::TAG_SHOP_INTERGRATION)
	{
		buyType=Entity::attr_intergration;
	}
	else if (vType>=TAG_NPCSHOP_MEDICINE&&vType<=TAG_NPCSHOP_RECYCLE)
	{
		buyType = Entity::attr_money;
	}
	m_pValue = defaultValue;
	m_nMaxValue = HeroData::getProp(buyType)/price;//maxValue;
	if (m_pValue>m_nMaxValue)
	{
		m_pValue=m_nMaxValue;
	}
	m_nCurPrice = price;

	CCScale9Sprite* pBkg = SystemData::getScale9SpriteByPlist("keyboard.sprite.newbkg");
	addChild(pBkg); 
	CCScale9Sprite* pBkg1 = SystemData::getScale9SpriteByPlist("keyboard.sprite.newbkg");
	addChild(pBkg1);
	 
	m_nWidth = pBkg->getContentSize().width;
	m_nHeight = pBkg->getContentSize().height;
	addCover();

	CCMenu* pMenu = CCMenu::create();
	pMenu->setTouchPriority(kCCMenuHandlerPriority-1);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	//add the close button on the top right corner
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("keyboard.btn.newclose");
	pClose->setTarget(this,menu_selector(NumberKeyBoard::closeCallback));
	pMenu->addChild(pClose);

	//add the increase and decrease arrow
	CCMenuItemImage* pIncrease = SystemData::getMenuItemImageByPlist("keyboard.btn.increase");
	pIncrease->setTarget(this,menu_selector(NumberKeyBoard::increaseCallback));
	pMenu->addChild(pIncrease);
	CCMenuItemImage* pDecrease = SystemData::getMenuItemImageByPlist("keyboard.btn.decrease");
	pDecrease->setTarget(this,menu_selector(NumberKeyBoard::decreaseCallback));
	pMenu->addChild(pDecrease);
	CCSprite *childSprite = dynamic_cast<CCSprite *>(pDecrease->getChildByTag(0x1));
	if (childSprite)
	{
		childSprite->setFlipX(true);
	}
	childSprite = dynamic_cast<CCSprite *>(pDecrease->getChildByTag(0x2));
	if (childSprite)
	{
		childSprite->setFlipX(true);
	}

	//add the confirm button
	CCMenuItemImage* pConfirm = SystemData::getMenuItemImageByPlist("keyboard.btn.confirm");
	pConfirm->setTarget(this,menu_selector(NumberKeyBoard::confirmCallback));
	pMenu->addChild(pConfirm);
	CCLabelTTF* pConfirmLabel = SystemData::getLabelTTF("keyboard.lbl.confirm");
	pConfirmLabel->setFontSize(18);
	addChild(pConfirmLabel);

	//add the number keys
	CCPoint numbegin = SystemData::getLayoutPoint("keyboard.point.numbegin");
	CCSize  numberSize = SystemData::getLayoutSize("keyboard.size.keyspan");
	std::string numKey[12] = {"btn_1_","btn_2_","btn_3_","btn_10_shanchu_","btn_4_","btn_5_","btn_6_","btn_11_zuida","btn_7_","btn_8_","btn_9_","btn_0_"};
	for(int i=0; i<12; i++)	
	{
		const std::string &key = numKey[i] + ".png";
		const std::string &key_sel = numKey[i] + (i == 7 ? "_sel.png" : "sel.png");
		CCMenuItemImage* pItem = CCMenuItemImage::create();
		pItem->setNormalImage(LayoutData::getSpriteByFrameName(key));
		pItem->setSelectedImage(LayoutData::getSpriteByFrameName(key_sel));
		pItem->setAnchorPoint(CCPointZero);
		pItem->setPosition(ccpAdd(numbegin,ccp(i%4*numberSize.width,-i/4*numberSize.height)));
		if('0' <=numKey[i][4] && numKey[i][4] <= '9'
			&& numKey[i][5] == '_')	
		{
			pItem->setTag(numKey[i][4]-'0');
			pItem->setTarget(this,menu_selector(NumberKeyBoard::touchCallback));
		}
		else
		{
			if(numKey[i][5] == '0')
			{
				pItem->setTarget(this,menu_selector(NumberKeyBoard::deleteCallback));
			}
			else
			{
				pItem->setTarget(this,menu_selector(NumberKeyBoard::maxCallback));
			}
		}
		pMenu->addChild(pItem);
	}
	CCScale9Sprite* pNumBkg = SystemData::getScale9SpriteByPlist("keyboard.sprite.numbkg");	
	addChild(pNumBkg);
	m_pCurLabel = SystemData::getLabelTTF("keyboard.lbl.newtotalcost"); 
	addChild(m_pCurLabel); 
	m_pShowMoney = SystemData::getLabelTTF("keyboard.lbl.newtotalmoney");
	addChild(m_pShowMoney);
	m_pShowNum = SystemData::getLabelTTF("keyboard.lbl.curnum");
	addChild(m_pShowNum);

	CCLabelTTF* m_pPriceLabel = SystemData::getLabelTTF("keyboard.lbl.itemcost");
	addChild(m_pPriceLabel);
	CCLabelTTF* m_pPriceShowLabel = SystemData::getLabelTTF("keyboard.lbl.itemmoney");
	addChild(m_pPriceShowLabel);
	m_pPriceShowLabel->setString(StringUtils::toString(price).c_str());

	CCSprite* pLine=SystemData::getSpriteByPlist("keyboard.lbl.line");
	pLine->setPosition(SystemData::getLayoutPoint("keyboard.lbl.line"));
	addChild(pLine);

	loadItemIcon(sid);

	showInput();
	return true;
}
void NumberKeyBoard::touchCallback( CCObject* pSender )
{
	CCNode* pNode = (CCNode*)pSender;
	if(pNode)
	{
		int tag = pNode->getTag();
		int curValue = (m_pValue)*10+tag;
		if(curValue>m_nMaxValue)
		{
			curValue = m_nMaxValue;
		}
		m_pValue = curValue;
		showInput();
	}
}

void NumberKeyBoard::confirmCallback( CCObject* pSender )
{
	//EventDispatcher::sharedEventDispather()->dispatchEvent(m_nEventType);
	if (m_UserIid)
	{
		UserItem* userItem = GameData::s_user->getUserItemData()->getItemByIid(m_UserIid);
		int cnt = userItem->count;
		UserItems items = GameData::s_user->getUserItemData()->userItems;
		if (m_pValue<=cnt && m_pValue>0)
		{
			MsgItemOperationRequestUse* req = new MsgItemOperationRequestUse;
			req->cnt = m_pValue;
			req->iid = m_UserIid;
			HandleMessage::sendMessage(req);
		}
		this->removeFromParent();
		return;
	}
	if(m_pValue>0)
	{
		MsgBuyItemInShopRequest* msg = new MsgBuyItemInShopRequest;
		msg->shopid = m_nType;
		msg->itemcnt = m_pValue;
		msg->itemid = m_nSid;
		HandleMessage::sendMessage(msg);
	}
	this->removeFromParent();
}

void NumberKeyBoard::closeCallback( CCObject* pSender )
{
	//EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PUTIN_OVER);
	this->removeFromParent();
}

void NumberKeyBoard::deleteCallback( CCObject* pSender )
{
	(m_pValue)/=10;	
	showInput();
}

void NumberKeyBoard::maxCallback( CCObject* pSender )
{
	m_pValue = m_nMaxValue;
	showInput();
}

void NumberKeyBoard::increaseCallback( CCObject* pSender )
{
	m_pValue += 1;
	if (m_pValue>m_nMaxValue)
	{
		m_pValue = m_nMaxValue;
	}
	showInput();
}

void NumberKeyBoard::decreaseCallback( CCObject* pSender )
{
	if (m_pValue>0)
	{
		m_pValue -= 1;
	}
	showInput();
}

void NumberKeyBoard::showInput()
{
	std::string num = SystemData::intToString(m_pValue);
	if (m_pShowNum)
	{
		m_pShowNum->setString(num.c_str());
	}
	std::string money = SystemData::intToString((m_pValue)*m_nCurPrice);
	if (m_pShowMoney)
	{
		m_pShowMoney->setString(money.c_str());
	}
	handleChanged();
}

void NumberKeyBoard::setCurLabelStr( std::string str )
{
	if (m_pCurLabel)
	{
		m_pCurLabel->setString(AToU8(str.c_str()));
	}
}

void NumberKeyBoard::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool NumberKeyBoard::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void NumberKeyBoard::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void NumberKeyBoard::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos=pTouch->getLocation();
	CCRect rect=CCRectMake(0,0,m_nWidth,m_nHeight);
	if (!rect.containsPoint( this->convertToNodeSpace(pos)))
	{
		this->removeFromParent();
	}
}

void NumberKeyBoard::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}
void NumberKeyBoard::setChangeHandler(CCObject *rec, SEL_MenuHandler selector)
{
	m_pListener = rec;
	m_pfnSelector = selector;
}
void NumberKeyBoard::handleChanged()
{
	if (m_pListener && m_pfnSelector)
	{
		(m_pListener->*m_pfnSelector)(this);
	}
}
int NumberKeyBoard::getCurNum()
{
	return m_pValue;
}
void NumberKeyBoard::loadItemIcon(int sid)
{
	CCPoint point = SystemData::getLayoutPoint("keyboard.sprite.itemframe");

	CCSprite* itemBg = SystemData::getSpriteByPlist("activity.sprite.item.frame");
	itemBg->setAnchorPoint(CCPointZero);
	itemBg->setPosition(point);
	addChild(itemBg);

	GeneralMenu* m_pMenu = GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	m_pMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMenu);

	if (sid>0)
	{ 
		UserItem* item = CommonFunction::createNewItem(sid);
		item->count = 1;
		CCMenuItemImage* pItem=CommonFunction::getItemIcon(item);
		//pItem->setTag(i+1);
		//pItem->setAnchorPoint(CCPointZero);
		pItem->setPosition(ccp(point.x+33,point.y+33));
		pItem->setTarget(this,menu_selector(NumberKeyBoard::itemCallBack));
		m_pMenu->addChild(pItem);

		// 		CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
		// 		pSprite->setPosition(pItem->getPosition());
		// 		m_InfoMainMenu->addChild(pSprite);
	}
}
void NumberKeyBoard::showTooltip(CCMenuItem* pImage)
{
	// show tips
	CCPoint tipsPos = pImage->convertToWorldSpace(ccp(pImage->getContentSize().width,pImage->getContentSize().height-125));
	if(tipsPos.x+245>SystemData::size_x) 
	{
		tipsPos.x -= 245+pImage->getContentSize().width;
	}
	UserItem* userItem = (UserItem*)pImage->getUserData();
	if (userItem->category==ItemCate_Equip)
	{
		tipsPos.y=0;
	}
	if (tipsPos.y>200)
	{
		tipsPos.y=200;
	}
	Game::getGameUI()->showTipsPanel(userItem,TAG_Tips,tipsPos);
}
void NumberKeyBoard::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}