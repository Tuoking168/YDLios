#include "CCLayerEx.h"
#include "userdata/SystemData.h"



CCLayerEx::CCLayerEx()
{

}


void CCLayerEx::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void CCLayerEx::onEnter()
{
	setTouchEnabled(true);
	CCLayer::onEnter();
}

void CCLayerEx::setHandlerPriority(int newPriority)
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->setPriority(newPriority, this);
}

CCLayerWithMask::CCLayerWithMask()
:m_theMask(NULL)
{

}

void CCLayerWithMask::onEnter()
{
	CCLayerEx::onEnter();

	m_theMask = SystemData::getSpriteByPlist("sprite.glassboard");
	if (m_theMask)
	{
		m_theMask->setOpacity(0);
		m_theMask->runAction(CCFadeIn::create(0.3f));
		addChild(m_theMask, -1);
	}
}