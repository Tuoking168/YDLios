#include "ControlPanel.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/netdata/GameRole.h"

#include "ext/CCMenuEx.h"


#define  TOUCH_DELAY_ACTION_TAG 19


float ControlPanel::m_timetouchkeep = 0;
float ControlPanel::m_distance = 0;
bool ControlPanel::init()
{
	if(!CCLayerEx::init())
	{
		return false;
	}

	m_pNormalSprite = SystemData::getSpriteByPlist("main_ui.control_bkg");
	addChild(m_pNormalSprite);

	m_center = m_pNormalSprite->getPosition();
	m_controlcenter = LayoutData::getCenter(m_pNormalSprite->getContentSize());
	mCurrentPt = CCPointZero;

	m_pDimlySprite = SystemData::getSpriteByPlist("main_ui.control_circle");
	m_pDimlySprite->setPosition(m_controlcenter);
	m_pNormalSprite->addChild(m_pDimlySprite);

	m_pControCenter = SystemData::getSpriteByPlist("main_ui.control_button");
	m_pControCenter->setPosition(m_controlcenter);
	m_pNormalSprite->addChild(m_pControCenter);

	schedule(schedule_selector(ControlPanel::update), 0.1f);
	outTouch();

	return true;
}

bool ControlPanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(!pTouch)
	{ 
		return false;
	}

	if(!isInRange(pTouch))
	{
		return false;
	}

	inTouch();
	m_timetouchkeep = 0;
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->m_bIsInControlPanel = true;

	refreshControlCenterPostion(pTouch);
	mCurrentPt = getScreenPosition(pTouch);

	stopActionByTag(TOUCH_DELAY_ACTION_TAG);
	CCAction *touchDelay = CCSequence::create(CCDelayTime::create(0.1f)
		, CCCallFunc::create(this, callfunc_selector(ControlPanel::onTouchBegin))
		, NULL);
	touchDelay->setTag(TOUCH_DELAY_ACTION_TAG);
	runAction(touchDelay);

	return true;
}

void ControlPanel::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if(!pTouch)
	{
		return;
	}
	GameRole* myRole = GameData::getMyRole();
	if(!myRole || !myRole->m_bIsInControlPanel)
	{
		return;
	}

	refreshControlCenterPostion(pTouch);
	mCurrentPt = getScreenPosition(pTouch);
	myRole->touchScreenMoved(mCurrentPt);
}

void ControlPanel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	outTouch();
	refreshControlCenterPostion(NULL);

	CCAction *touchDelay = getActionByTag(TOUCH_DELAY_ACTION_TAG);
	if (touchDelay)
	{
		stopAction(touchDelay);
		onTouchBegin();
	}
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->touchScreenEnded();
}

void ControlPanel::onTouchBegin()
{
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->touchScreenBegin(mCurrentPt);
}

void ControlPanel::refreshControlCenterPostion( CCTouch *touch )
{
	if (!touch)
	{
		m_pControCenter->setPosition(m_controlcenter);
		return;
	}

	const CCPoint &pos = m_pNormalSprite->convertToNodeSpace(touch->getLocation());
	const float radius = m_controlcenter.x;
	const float dis = ccpDistance(pos, m_controlcenter);
	CCPoint finalPos = m_controlcenter;
	if (dis <= radius)
	{
		finalPos = pos;
	}
	else
	{
		float ratio = radius/dis;
		finalPos = ccpAdd(m_controlcenter, ccp((pos.x - m_controlcenter.x) * ratio, (pos.y - m_controlcenter.y) * ratio));
	}
	m_pControCenter->setPosition(finalPos);
}

cocos2d::CCPoint ControlPanel::getScreenPosition( CCTouch* pTouch )
{
	const float scalex = SystemData::size_x/m_pNormalSprite->getContentSize().width;
	const float scaley = SystemData::size_y/m_pNormalSprite->getContentSize().height;
	CCPoint touchpos = pTouch->getLocation();
	touchpos = m_pNormalSprite->convertToNodeSpace(touchpos);
	return ccp(touchpos.x * scalex, touchpos.y * scaley);
}

bool ControlPanel::isInRange( CCTouch* pTouch )
{
	CCPoint touchpos = pTouch->getLocation();
	touchpos = convertToNodeSpace(touchpos);
	m_distance = ccpDistance(touchpos, m_center);
	if(m_distance > m_center.x * 2)
	{
		return false;
	}
	return true;
}

void ControlPanel::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void ControlPanel::update( float delta )
{
	GameRole* myRole = GameData::getMyRole();
	if(myRole && myRole->m_bIsInControlPanel)
	{
		m_timetouchkeep += delta;
	}
}

void	ControlPanel::inTouch()
{
	m_pNormalSprite->setOpacity(255);
	m_pControCenter->setOpacity(255);
	m_pDimlySprite->setVisible(true);
}

void	ControlPanel::outTouch()
{
	m_pNormalSprite->setOpacity(204);
	m_pControCenter->setOpacity(204);
	m_pDimlySprite->setVisible(false);
}
