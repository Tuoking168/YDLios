#include "DonateKeyboard.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "event/EventDispatcher.h"
#include "event/EventProtocol.h"
#include "script/LuaWrapper.h"

DonateKeyBoard::DonateKeyBoard()
	: m_nMaxValue(0)
	, m_pValue(0)
	, m_pShowNum(NULL)
	//, m_nCurPrice(0)
	, m_pShowMoney(NULL)
	, m_pCurLabel(NULL)
	, m_pListener(NULL)
	, m_pfnSelector(NULL)
{
}

DonateKeyBoard::~DonateKeyBoard()
{

}

DonateKeyBoard* DonateKeyBoard::create(int curValue,int MaxValue)
{
	DonateKeyBoard* pDonateKeyBoard = new DonateKeyBoard;
	if(pDonateKeyBoard && pDonateKeyBoard->init(curValue,MaxValue))
	{
		pDonateKeyBoard->autorelease();
		return pDonateKeyBoard;
	}
	if(pDonateKeyBoard)
	{
		delete pDonateKeyBoard;
	}
	return NULL;
}
void DonateKeyBoard::onEnter()
{
	registerWithTouchDispatcher();
	CCNode::onEnter();	
}

void DonateKeyBoard::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}
bool DonateKeyBoard::init(int curValue,int MaxValue)
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
	pClose->setTarget(this,menu_selector(DonateKeyBoard::closeCallback));
	pMenu->addChild(pClose);

	//add the increase and decrease arrow
	CCMenuItemImage* pIncrease = SystemData::getMenuItemImageByPlist("keyboard.btn.increase");
	pIncrease->setTarget(this,menu_selector(DonateKeyBoard::increaseCallback));
	pMenu->addChild(pIncrease);
	CCMenuItemImage* pDecrease = SystemData::getMenuItemImageByPlist("keyboard.btn.decrease");
	pDecrease->setTarget(this,menu_selector(DonateKeyBoard::decreaseCallback));
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
	pConfirm->setTarget(this,menu_selector(DonateKeyBoard::confirmCallback));
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
			pItem->setTarget(this,menu_selector(DonateKeyBoard::touchCallback));
		}
		else
		{
			if(numKey[i][5] == '0')
			{
				pItem->setTarget(this,menu_selector(DonateKeyBoard::deleteCallback));
			}
			else
			{
				pItem->setTarget(this,menu_selector(DonateKeyBoard::maxCallback));
			}
		}
		pMenu->addChild(pItem);
	}
	CCScale9Sprite* pNumBkg = SystemData::getScale9SpriteByPlist("keyboard.sprite.numbkg");	
	addChild(pNumBkg);
	m_pCurLabel = SystemData::getLabelTTF("keyboard.lbl.donatecount");
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

void DonateKeyBoard::touchCallback( CCObject* pSender )
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

void DonateKeyBoard::confirmCallback( CCObject* pSender )
{
	//EventDispatcher::sharedEventDispather()->dispatchEvent(m_nEventType);
	this->removeFromParent();
}

void DonateKeyBoard::closeCallback( CCObject* pSender )
{
	//EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_PUTIN_OVER);
	this->removeFromParent();
}

void DonateKeyBoard::deleteCallback( CCObject* pSender )
{
	(m_pValue)/=10;	
	showInput();
}

void DonateKeyBoard::maxCallback( CCObject* pSender )
{
	m_pValue = m_nMaxValue;
	showInput();
}

void DonateKeyBoard::increaseCallback( CCObject* pSender )
{
	m_pValue += 1;
	if (m_pValue>m_nMaxValue)
	{
		m_pValue = m_nMaxValue;
	}
	showInput();
}

void DonateKeyBoard::decreaseCallback( CCObject* pSender )
{
	if (m_pValue>0)
	{
		m_pValue -= 1;
	}
	showInput();
}

void DonateKeyBoard::showInput()
{
	std::string num = SystemData::intToString(m_pValue);
	if (m_pShowNum)
	{
		m_pShowNum->setString(num.c_str());
	}
	//std::string money = SystemData::intToString((*m_pValue)*m_nCurPrice);
	std::string money = SystemData::intToString((m_pValue)*1);
	if (m_pShowMoney)
	{
		m_pShowMoney->setString(money.c_str());
	}
	handleChanged();
}

void DonateKeyBoard::setCurLabelStr( std::string str )
{
	m_pCurLabel->setString(AToU8(str.c_str()));
}

void DonateKeyBoard::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool DonateKeyBoard::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void DonateKeyBoard::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void DonateKeyBoard::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos=pTouch->getLocation();
	CCRect rect=CCRectMake(0,0,m_nWidth,m_nHeight);
	if (!rect.containsPoint( this->convertToNodeSpace(pos)))
	{
		this->removeFromParent();
	}
}

void DonateKeyBoard::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}
void DonateKeyBoard::setChangeHandler(CCObject *rec, SEL_MenuHandler selector)
{
	m_pListener = rec;
	m_pfnSelector = selector;
}
void DonateKeyBoard::handleChanged()
{
	if (m_pListener && m_pfnSelector)
	{
		(m_pListener->*m_pfnSelector)(this);
	}
}
int DonateKeyBoard::getCurNum()
{
	return m_pValue;
}