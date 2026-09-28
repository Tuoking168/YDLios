#include "cocos2d.h"
#include "CCActionEx.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

//
// Place
//
CCActionVertex * CCActionVertex::actionWithVertex(float vertex)
{
	CCActionVertex *pRet = new CCActionVertex();
	pRet->initWithVertex(vertex);
	pRet->autorelease();
	return pRet;
}
bool CCActionVertex::initWithVertex(float vertex)
{
	_vertexZ = vertex;
	return true;
}

/*CCObject * CCActionVertex::copyWithZone(CCZone *pZone)
{
	CCZone *pNewZone = NULL;
	CCActionVertex *pRet = NULL;
	if (pZone && pZone->m_pCopyObject)
	{
		pRet = (CCActionVertex*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCActionVertex();
		pZone = pNewZone = new CCZone(pRet);
	}
	CCActionInstant::copyWithZone(pZone);
	pRet->initWithVertex(_vertexZ);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}*/

void CCActionVertex::startWithTarget(CCNode *pTarget)
{
	CCActionInstant::startWithTarget(pTarget);
	m_pTarget->setVertexZ(_vertexZ);
}



//
// CCActionMusicFadeTo
//
CCActionMusicFadeTo* CCActionMusicFadeTo::create(float duration)
{
	CCActionMusicFadeTo* pRotateTo = new CCActionMusicFadeTo();
	pRotateTo->initWithDuration(duration);
	pRotateTo->autorelease();

	return pRotateTo;
}

bool CCActionMusicFadeTo::initWithDuration(float duration)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		return true;
	}

	return false;
}

/*
CCObject* CCActionMusicFadeTo::copyWithZone(cocos2d::CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCActionMusicFadeTo* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject)
	{
		//in case of being called at sub class
		pCopy = (CCActionMusicFadeTo*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCActionMusicFadeTo();
		pZone = pNewZone = new CCZone(pCopy);
	}

	CCActionInterval::copyWithZone(pZone);

	pCopy->initWithDuration(m_fDuration, m_fVolumeDst);

	//Action *copy = [[[self class] allocWithZone: zone] initWithDuration:[self duration] angle: angle];
	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}*/

void CCActionMusicFadeTo::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);

	m_fVolumeSrc = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();

	m_fVolumeDiff = m_fVolumeDst - m_fVolumeSrc;

}

void CCActionMusicFadeTo::update(float time)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(m_fVolumeSrc + m_fVolumeDiff * time);
}


CCFollowOnTop *CCFollowOnTop::actionWithTarget(CCNode *pFollowedNode)
{
	CCFollowOnTop *pRet = new CCFollowOnTop();
	if (pRet && pRet->initWithTarget(pFollowedNode))
	{
		pRet->_time_accumulate = 0.0f;
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
		return NULL;
}

void CCFollowOnTop::step(float dt)
{
	_time_accumulate += dt;

	CCPoint pt = m_pobFollowedNode->getPosition();
	pt.y += (52 + 6 * sin(_time_accumulate*3)* sin(_time_accumulate*3));

	m_pTarget->setPosition(pt);
}