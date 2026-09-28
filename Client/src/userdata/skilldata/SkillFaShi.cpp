#include "SkillFaShi.h"
#include "SkillEffect.h"
#include "ext/CCFlashAnimation.h"
#include "scene/Game.h"

void cSkillHuoQiuShu::castSkill( int x/*=0*/, int y/*=0*/, int id/*=-1*/ )
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

void cSkillHuoQiuShu::castOut()
{
	sBC();
}

void cSkillKangJuHuoHuan::castSkill( int x/*=0*/, int y/*=0*/, int id/*=-1*/ )
{
	m_destx = x;
	m_desty = y;
	m_aimID = id;

	if (m_cast)
	{
		CCSprite* pSprite = CCSprite::create();
		m_pHero->attachMe(pSprite);
		pSprite->_setZOrder(-1);
		pSprite->runAction(CCSequence::create(
			m_cast->getAnimate(0)
			,CCActionInstantRemoveFromParentEx::create(pSprite)
			,CCCallFunc::create(this, callfunc_selector(cSkillCastModel::castOut))
			,NULL
			));
	}
	else
	{
		castOut();
	}
}

void cSkillLeiDianShu::castOut()
{
	AC();
}

void cSkillLeiDianShu::castEnd()
{
	cSkillCastModel::castEnd();
}

void cSkillBingPaoXiao::castOut()
{
	AC();
}

void cSkillMoFaDun::castOut()
{
	//
}

void cSkillChuanTouShanDian::castSkill( int x, int y, int id )
{
	if (m_cast)
	{
		CCSprite* pSprite = CCSprite::create();
		m_pHero->attachMe(pSprite);
		if(m_pHero->getDirection()==0)
		{
			pSprite->_setZOrder(-1);
		}
		else
		{
			pSprite->_setZOrder(4);
		}
		pSprite->setPosition(ccp(0,40));
		pSprite->runAction(CCSequence::create(
			m_cast->getAnimate(m_pHero->getDirection())
			,CCActionInstantRemoveFromParentEx::create(pSprite)
			,CCCallFunc::create(this,callfunc_selector(cSkillCastModel::castEnd))
			,NULL
			));
	}	
}
