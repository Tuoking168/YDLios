#include "PartPanel.h"
#include "ext/TouchCover.h"
#include "ext/CCActionDestroy.h"
#include "controls/CPNodeHelper.h"

PartPanel::PartPanel():
	m_nHeight(0),
	m_nWidth(0),
	m_pPos(CCPointZero),
	m_bIsCheck(true)
{

}

PartPanel::~PartPanel()
{

}

void PartPanel::onEnter()
{
	CCLayer::onEnter();
	setScale(0.0f);
	setAnchorPoint(ccp(0.5,0.5));
	runAction(CPNodeHelper::getScaleToBig());
}

void PartPanel::onExit()
{
	CCLayer::onExit();
}

PartPanel* PartPanel::create()
{
	PartPanel* pPanel = new PartPanel();
	if(pPanel && pPanel->init())
	{
		pPanel->autorelease();
		return pPanel;
	}
	return NULL;
}

bool PartPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);
	
	return true;
}

bool PartPanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos=pTouch->getLocation();
	if (!isPointInThisPanel(pos) && m_bIsCheck)
	{
		return true;
	}

	return false;
}

void PartPanel::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void PartPanel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos=pTouch->getLocation();
	if (!isPointInThisPanel(pos) && m_bIsCheck)
	{
		close();
	}	
}

void PartPanel::addCover( CCPoint Pos )
{
	m_pPos = Pos;
	CCRect inner = CCRectZero;
	CCRect outer = CCRectMake(m_pPos.x,m_pPos.y,m_nWidth,m_nHeight);
	TouchCover* pCover = TouchCover::create(inner,outer);
	pCover->setAnchorPoint(CCPointZero);
	pCover->setPosition(m_pPos);
	addChild(pCover);
}

void PartPanel::close()
{
	//this->removeFromParent();
	this->runAction(CCSequence::create(CCShow::create(),CCActionInstantRemoveFromParentEx::create(this),NULL));
}

bool PartPanel::isPointInThisPanel( CCPoint& point )
{
	CCRect rect=CCRectMake(m_pPos.x,m_pPos.y,m_nWidth,m_nHeight);
	if (!rect.containsPoint( this->convertToNodeSpace(point)))
	{
		return false;
	}
	return true;
}

void PartPanel::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void PartPanel::setIsCheckInPanel( bool flag )
{
	m_bIsCheck = flag;
}
