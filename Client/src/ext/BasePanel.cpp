#include "BasePanel.h"
#include "userdata/SystemData.h"
#include "scene/GameUI.h"
#include "userdata/netdata/NetItem.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"

#include "ext/CCActionDestroy.h"
#include "ext/TouchCover.h"
#include "ext/GeneralMenu.h"
#include "controls/CPNodeHelper.h"

int BasePanel::s_PanelZorder = BasePanel::TOP_ZORDER - 1;

BasePanel::BasePanel()
: m_nWidth(0)
, m_nHeight(0)
, m_nPosX(0)
, m_nPosY(0)
, m_isNeedShow(true)
, m_itemPoints(NULL)
, m_items(NULL)
, m_size(0)
, m_pBkgSprite(NULL)
, m_pMovingItem(NULL)
, m_pTargetPanel(NULL)
, m_bMoveTwoFar(false)
, m_bTouchDown(false)
, m_bIsDragging(false)
, m_pMenu(NULL)
{

}

BasePanel::~BasePanel()
{
	if (m_itemPoints)
		delete[] m_itemPoints;
	if (m_items)
		delete[] m_items;
}

BasePanel* BasePanel::create( const char *filename )
{
	BasePanel* pPanel = new BasePanel();
	if(pPanel && pPanel->init(filename))
	{
		pPanel->autorelease();
		return pPanel;
	}
	return NULL;
}

bool BasePanel::init(const char *filename, bool isshow, bool bconfigString)
{
	if (!CCLayer::init())
	{
		return false;
	}

	if (bconfigString && strlen(filename) > 0)
	{
		m_pBkgSprite = SystemData::getSprite(filename);
	}
	else
	{
		m_pBkgSprite = CCSprite::create();
	}
	
	if(!m_pBkgSprite)
	{
		return false;
	}

	m_isNeedShow = isshow;
	m_nWidth = m_pBkgSprite->getContentSize().width;
	m_nHeight = m_pBkgSprite->getContentSize().height;
	setPosition(ccp((SystemData::size_x-m_nWidth)/2, (SystemData::size_y-m_nHeight)/2));

	addCover();

 	m_pBkgSprite->setAnchorPoint(CCPointZero);
 	m_pBkgSprite->setPosition(CCPointZero);
	addChild(m_pBkgSprite,-2,-1);

	m_pMenu = GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu,2);

	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("close");
	pClose->setTarget(this,menu_selector(BasePanel::closeCallBack));
	pClose->setAnchorPoint(ccp(1,1));
	pClose->setPosition(ccp(m_nWidth, m_nHeight));
	m_pMenu->addChild(pClose);

	return true;
}

BasePanel* BasePanel::createWithSpriteFrameName( const char *filename )
{
	BasePanel* pPanel = new BasePanel();
	if(pPanel && pPanel->initWithSpriteFrameName(filename))
	{
		pPanel->autorelease();
		return pPanel;
	}
	return NULL;
}

bool BasePanel::initWithSpriteFrameName( const char *filename, bool isshow /*= true */ )
{
	if(!CCLayer::init())
	{
		return false;
	}

	m_pBkgSprite = CCSprite::createWithSpriteFrameName(filename);

	if(!m_pBkgSprite)
	{
		return false;
	}
	m_isNeedShow = isshow;
	m_nWidth = m_pBkgSprite->getContentSize().width;
	m_nHeight = m_pBkgSprite->getContentSize().height;
	setPosition(ccp((SystemData::size_x-m_nWidth)/2, (SystemData::size_y-m_nHeight)/2));

	addCover();

	m_pBkgSprite->setAnchorPoint(CCPointZero);
	m_pBkgSprite->setPosition(CCPointZero);
	addChild(m_pBkgSprite,-2,-1);

	m_pMenu = GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu,2);

	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("close");
	pClose->setTarget(this,menu_selector(BasePanel::closeCallBack));
	CCSize size = pClose->getContentSize();
	pClose->setContentSize(CCSizeMake(size.width*3, size.height*3));
	pClose->setAnchorPoint(ccp(0.5, 0.5));
	pClose->setPosition(ccp(m_nWidth, m_nHeight));
	m_pMenu->addChild(pClose);

	return true;
}

bool BasePanel::isInRange( CCTouch* pTouch )
{
	CCPoint touchLocation = getParent()->convertTouchToNodeSpace(pTouch);
	if(touchLocation.x>=getPosition().x && touchLocation.y>=getPosition().y && touchLocation.x<getPosition().x+m_nWidth && touchLocation.y<getPosition().y+m_nHeight)
	{
		return true;
	}
	return false;
}

void BasePanel::closeCallBack( CCObject* pSender )
{
	hide();
}

void BasePanel::show()
{
	if (m_isNeedShow)
	{
		update(0);
		CCLog("show panel ok!");
	}
}

void BasePanel::hide()
{
	//GameUI* pGameUI = dynamic_cast<GameUI*>(getParent()->getParent());
	GameUI* pGameUI=Game::getGameUI();
	if (!pGameUI)
	{
		this->removeFromParent();
		return;
	}
	int index = this->getTag();
	if (0 <= index && index < (int)pGameUI->m_panels.size())
	{
		pGameUI->hidePanel(index);
		pGameUI->m_panels[index] = NULL;
	}
	//this->runAction();
	this->runAction(CCSequence::create(CCFadeOut::create(0.2f),CPNodeHelper::getScaleToSmall(),CCActionInstantRemoveFromParentEx::create(this),NULL));
}

void BasePanel::update( float dt )
{
	//just overwrite me
}

bool BasePanel::isPointInThisPanel(CCPoint& point)
{
	CCPoint p0 = getPosition();
	if (point.x >= p0.x
		&& point.x <= p0.x + m_nWidth
		&& point.y >= p0.y
		&& point.y <= p0.y + m_nHeight)
		return true;
	return false;
}

bool BasePanel::dragIn(CCPoint& point, CCNode* itemsrc)
{
// 	point.x -= getPosition().x;
// 	point.y -= getPosition().y;
// 	for (int i=0; i<m_size; i++)
// 	{
// 		if (point.x >= m_itemPoints[i].x - 12
// 			&& point.x <= m_itemPoints[i].x + 12
// 			&& point.y >= m_itemPoints[i].y - 12
// 			&& point.y <= m_itemPoints[i].y + 12)
// 		{
// 			return moveItemInPanel(i, itemsrc->getTag());
// 		}
// 	}
	return false;
}

void BasePanel::dragOut( CCPoint& point )
{
	m_bTouchDown = false;
	if(m_bIsDragging)
	{
		dragEndInScroll();
		m_bIsDragging = false;
		if(m_pTargetPanel && m_pMovingItem)
		{
			m_pTargetPanel->dragIn(point,m_pMovingItem);
		}
		if(m_pMovingItem)
		{
			m_pMovingItem->removeFromParentAndCleanup(true);
			m_pMovingItem = NULL;
		}
	}
}

void BasePanel::setTargetPanel( BasePanel* targetPanel )
{
	m_pTargetPanel = targetPanel;
}

void BasePanel::startDrag(CCPoint& pos)
{
	m_bTouchDown = true;
	m_bIsDragging = false;
	if(checkSelectOneItem(pos))
	{
		m_bIsDragging = true;
		dragBeginInScroll();
	}
}

void BasePanel::startDragInScroll( CCPoint &pos )
{
	m_bTouchDown = true;
	m_nStartDragPeriod = 0;
	m_ptStartDragPos = pos;
	m_bMoveTwoFar = false;
	m_bIsDragging = false;
	schedule(schedule_selector(BasePanel::checkStartDragInScroll),0.1f);
}

void BasePanel::checkStartDragInScroll( float dt )
{
	if (!m_bTouchDown)
	{
		unschedule(schedule_selector(BasePanel::checkStartDragInScroll));
		return;
	}

	m_nStartDragPeriod++;
	if(m_nStartDragPeriod >= DragPeriod)
	{
		if (!m_bMoveTwoFar)
			startDrag(m_ptStartDragPos);
		unschedule(schedule_selector(BasePanel::checkStartDragInScroll));
	}
}

bool BasePanel::checkSelectOneItem(CCPoint &pos)
{
	//子类自己去写
	return false;
}

void BasePanel::dragging(CCPoint& pos)
{
	if(ccpDistance(m_ptStartDragPos,pos) > SelectDistance)
	{
		m_bMoveTwoFar = true;
	}
	if(m_bIsDragging && m_pMovingItem)
	{
		m_pMovingItem->setPosition(pos);
	}
}

void BasePanel::dragEndInScroll()
{

}

void BasePanel::dragBeginInScroll()
{

}

void BasePanel::setItemType( int type )
{
	m_nItemType = type;
}

int BasePanel::getItemType()
{
	return m_nItemType;
}

void BasePanel::setMeTopOrder()
{
	if (m_pTargetPanel)
		m_pTargetPanel->_setZOrder(TOP_ZORDER-1);
	_setZOrder(TOP_ZORDER);
	if (m_pParent)
	{
		m_pParent->reorderChild(this, TOP_ZORDER);
	}
}

void BasePanel::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	EventDispatcher::sharedEventDispather()->addListener(this);
}

void BasePanel::onExit()
{
	EventDispatcher::sharedEventDispather()->removeListener(this);
	CCLayer::onExit();
}

void BasePanel::addCover()
{
	CCRect inner = CCRectZero;
	CCRect outer = CCRectMake(0,0,m_nWidth,m_nHeight);
	TouchCover* pCover = TouchCover::create(inner,outer);
	pCover->setAnchorPoint(CCPointZero);
	pCover->setPosition(ccp(m_nPosX,m_nPosY));
	addChild(pCover);
}

void BasePanel::addCover(CCPoint Pos,int priority)
{	
	CCRect inner = CCRectZero;
	CCRect outer = CCRectMake(Pos.x,Pos.y,m_nWidth,m_nHeight);
	TouchCover* pCover = TouchCover::create(inner,outer);
	pCover->setTag(-100);
	pCover->setAnchorPoint(CCPointZero);
	pCover->setPosition(Pos);
	pCover->setTouchPriority(priority);
	addChild(pCover);
}

void BasePanel::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, false);
}

bool BasePanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(!isVisible() || !isInRange(pTouch))
	{
		return false;
	}
	return true;
}
