#include "SkillDaoShi.h"
#include "ext/CCFlashAnimation.h"

void cSkillShiDuShu::castSkill( int x/*=0*/, int y/*=0*/, int id/*=-1*/ )
{
	m_destx = x;
	m_desty = y;
	m_aimID = id;

	if (m_cast)
	{
		CCSprite* pSprite = CCSprite::create();
		m_pHero->attachMe(pSprite);
		pSprite->_setZOrder(4);
		pSprite->runAction(CCSequence::create(
			m_cast->getAnimate(0)
			,CCActionInstantRemoveFromParentEx::create(pSprite)
			,NULL
			));
	}
	castOut();
}

void cSkillShiDuShu::castOut()
{
	sBC();
}

////////cSkillLingHunHuoFu/////////////////////////////////////////////
void cSkillLingHunHuoFu::castSkill( int x/*=0*/, int y/*=0*/, int id/*=-1*/ )
{
	m_destx = x;
	m_desty = y;
	m_aimID = id;

	if (m_cast)
	{
		CCSprite* pSprite = CCSprite::create();
		m_pHero->attachMe(pSprite);
		pSprite->_setZOrder(4);
		pSprite->runAction(CCSequence::create(
			m_cast->getAnimate(0)
			,CCActionInstantRemoveFromParentEx::create(pSprite)
			,NULL
			));
	}
	castOut();
}

void cSkillLingHunHuoFu::castOut()
{
	sBC();
}
