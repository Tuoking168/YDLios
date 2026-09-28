
#include "CCActionDestroy.h"


//
// Place
//

CCActionInstantRemoveFromParent::~CCActionInstantRemoveFromParent()
{

}

CCActionInstantRemoveFromParent * CCActionInstantRemoveFromParent::create()
{
	CCActionInstantRemoveFromParent *pRet = new CCActionInstantRemoveFromParent();
	pRet->autorelease();
	return pRet;
}

void CCActionInstantRemoveFromParent::startWithTarget(CCNode *pTarget)
{
	CCActionInstant::startWithTarget(pTarget);
	CCNode* parent = pTarget->getParent();
	if (parent)
	{
		parent->removeChild(pTarget, true);
	}
}



CCActionInstantRemoveFromParentEx * CCActionInstantRemoveFromParentEx::create(CCNode* pTarget)
{
	CCActionInstantRemoveFromParentEx *pRet = new CCActionInstantRemoveFromParentEx();
	pRet->initWithTarget(pTarget);
	pRet->autorelease();
	return pRet;
}
bool CCActionInstantRemoveFromParentEx::initWithTarget(CCNode* pTarget)
{
	m_pTargetTarget = pTarget;
	return true;
}


void CCActionInstantRemoveFromParentEx::startWithTarget(CCNode *pTarget)
{
	CCActionInstant::startWithTarget(pTarget);
	CCNode* parent = m_pTargetTarget->getParent();
	if (parent)
	{
		parent->removeChild(m_pTargetTarget, true);
	}
}

