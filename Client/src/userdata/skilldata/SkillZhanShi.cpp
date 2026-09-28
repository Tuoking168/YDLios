#include "SkillZhanShi.h"
#include "userdata/netdata/GameRole.h"
#include "ext/CCFlashAnimation.h"

#include "res/AudioLoader.h"

void cZSBaseSkill::castSkill( int x, int y, int id )
{
	if (m_cast)
	{
		CCDelayTime *dt = CCDelayTime::create(CCFlashAnimation::FRAME_TIME * 5);
		CCActionInterval *anim = m_cast->getAnimate(m_pHero->getDirection());
		CCActionInstantRemoveFromParent *rmv = CCActionInstantRemoveFromParent::create();
		CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(cSkillJinShenGongJi::castEnd));
		CCAction *action = CCSequence::create(dt, anim, rmv, func, NULL);
		CCSprite *pSprite = CCSprite::create();
		m_pHero->attachMe(pSprite);
		pSprite->_setZOrder(4);
		pSprite->runAction(action);
	}	
}

void cSkillMonArrow::castOut()
{
	//
}

void cSkillYunShi::castOut()
{
	AC();
}

void cSkillYunShi::castEnd()
{
	cSkillCastModel::castEnd();
}

////////////cSkillLevelUp//////////////////////////////////////////////
void cSkillLevelUp::castSkill( int x/*=0*/, int y/*=0*/, int id/*=-1*/ )
{
	cSkillCastModel::castSkill(x, y, id);
	AudioLoader::play(Sound::Effect::shengji);
}

////////////cSkillLevelUp//////////////////////////////////////////////
void cSkillRelive::castSkill( int x/*=0*/, int y/*=0*/, int id/*=-1*/ )
{
	cSkillCastModel::castSkill(x, y, id);
	AudioLoader::play(Sound::Effect::shengji);
}
