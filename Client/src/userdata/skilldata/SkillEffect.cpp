#include "SkillEffect.h"
#include "SkillModel.h"
#include "SkillZhanShi.h"
#include "SkillFaShi.h"
#include "SkillDaoShi.h"
#include "EffectDefinition.h"

#include "userdata/UserData.h"
#include "userdata/GameData.h"
#include "userdata/HeroData.h"
#include "userdata/StaticData.h"
#include "userdata/netdata/AliveGhost.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/mapdata/PixesMap.h"

#include "utils/MacroUtils.h"


SkillEffect::SkillEffect(AliveGhost* hero)
: m_pHero(hero)
, m_bLock(false)
{
	m_skillCount.clear();
}

SkillEffect::~SkillEffect()
{
	removeAllSkills();
}

SkillEffect* SkillEffect::create(AliveGhost* hero)
{
	SkillEffect* pSkill = new SkillEffect(hero);
	return pSkill;
}

cSkillModel* SkillEffect::createSkill( int skillID )
{
	const int skillEnum = skillID/10;
	switch(skillEnum)
	{
	case SKILL_TYPE_YiBanGongJi:
		return new cSkillYiBanGongJi(m_pHero,skillID);

	//ZS skills
	case  SKILL_TYPE_JiChuJianShu:
		return new cSkillJiChuJianFa(m_pHero,skillID);
	case  SKILL_TYPE_CiShaJianShu:
		return new cSkillCiShaJianShu(m_pHero,skillID);
	case  SKILL_TYPE_BanYueWanDao:
		return new cSkillBanYueWanDao(m_pHero,skillID);
	case  SKILL_TYPE_YeManChongZhuang:
		return new cSkillYeManChongZhuang(m_pHero,skillID);
	case  SKILL_TYPE_LieHuoJianFa:
		return new cSkillLieHuoJianFa(m_pHero,skillID);
	case SKILL_TYPE_LieYanChongSheng:
		return NULL;

	//FS skills
	case  SKILL_TYPE_KangJuHuoHuan:
		return new cSkillKangJuHuoHuan(m_pHero,skillID);
	case  SKILL_TYPE_LeiDianShu:
		return new cSkillLeiDianShu(m_pHero,skillID);
	case  SKILL_TYPE_HuoQiuShu:
		return new cSkillHuoQiuShu(m_pHero,skillID);
	case  SKILL_TYPE_HuoQiang:
		return new cSkillHuoQiangShu(m_pHero, skillID);
	case  SKILL_TYPE_MoFaDun:
		return new cSkillMoFaDun(m_pHero,skillID);
	case  SKILL_TYPE_BingPaoXiao:
		return new cSkillBingPaoXiao(m_pHero,skillID);
	case SKILL_TYPE_ChuanTouShanDian:
		return new cSkillChuanTouShanDian(m_pHero,skillID);
	case SKILL_TYPE_ShunYi:
		return new cSkillShunYi(m_pHero, skillID);

	//DS Skills
	case  SKILL_TYPE_ShiDuShu:
		return new cSkillShiDuShu(m_pHero,skillID);
	case  SKILL_TYPE_LingHunHuoFu:
		return new cSkillLingHunHuoFu(m_pHero,skillID);
	case  SKILL_TYPE_JiTiYinShenShu:
		return new cSkillJiTiYinShenShu(m_pHero,skillID);
	case  SKILL_TYPE_QunTiZhiLiao:
		return new cSkillQunTiZhiLiao(m_pHero,skillID);
 	case  SKILL_TYPE_ZhaoHuanShenShou:
 		return new cSkillZhaoHuanShenShou(m_pHero,skillID);
	case SKILL_TYPE_DaYinYuShi:
		return NULL;

	//NPC Skills
	case  SKILL_TYPE_MonArrow:
		return new cSkillMonArrow(m_pHero,skillID);
	//Level up skill
	case  SKILL_TYPE_LevelUp:
		return new cSkillLevelUp(m_pHero,skillID);
	case  SKILL_TYPE_Relive:
		return new cSkillRelive(m_pHero,skillID);
	default:
		break;
	}
	switch (skillID)
	{
	case 5064:
	case 5082:
		return new cSkillBanYueWanDao(m_pHero, skillID);
	case 5065:
		return new cSkillYunShi(m_pHero, skillID);
	default:
		break;
	}
	CCLog(">>>Error: SkillEffect::createSkill, unknown skillID = %d", skillID);
	return NULL;
}

void SkillEffect::runSkill(int skillID, int tx, int ty, AliveGhost* aim)
{
	cSkillModel* pSkill = createSkill(skillID);
	if (!pSkill)
	{
		return;
	}

	if (m_pHero->mType == GHOST_TYPE_THIS)
	{
		const int skillEnum = skillID/10;
		if (skillEnum != SKILL_TYPE_LieHuoJianFa
			|| !m_pHero->hasEffectBuff(Effect::effect_firereborn))
		{
			setSkillCD(skillID);
		}		
	}
	addSkill(skillID, pSkill);
	CCPoint pt = PixesMap::getPixelPoint(tx, ty);
	int aimID = -1;
	if (aim)
	{
		pt = aim->getMapPosition();
		aimID = aim->mID;
	}
	pSkill->castSkill(pt.x, pt.y, aimID);
}

void SkillEffect::addSkill( int skillID, cSkillModel *skill )
{
	if(m_bLock)
	{
		return;
	}
	m_bLock = true;
	const int typeEnum = skillID/10;
	SkillMap::iterator it = m_skillCount.find(typeEnum);
	if(it == m_skillCount.end())
	{
		SkillCount data;
		data.count = 1;
		data.skills.push_back(skill);
		m_skillCount[typeEnum] = data;
	}
	else
	{
		SkillCount &data = it->second;
		data.count++;
		data.skills.push_back(skill);
	}
	m_bLock = false;
}

void SkillEffect::removeSkill( int skillID )
{
	if (m_bLock)
	{
		return;
	}
	m_bLock = true;

	const int typeEnum = skillID/10;
	SkillMap::iterator it = m_skillCount.find(typeEnum);
	if(it != m_skillCount.end())
	{
		SkillCount &data = it->second;
		data.count--;
		if (data.count <= 0)
		{
			data.count = 0;
			releaseSkillVect(data.skills);
		}
	}
	else
	{
		CCLog("SkillEffect::removeSkill, undefined type %d.", typeEnum);
	}
	m_bLock = false;
}

bool SkillEffect::hasSkill( int skillID )
{
	const int typeEnum = skillID/10;
	SkillMap::iterator it = m_skillCount.find(typeEnum);
	return (it != m_skillCount.end());
}

bool SkillEffect::overLimit( int skillID )
{	
	if(m_bLock)
	{
		return true;
	}

	const int typeEnum = skillID/10;
	if (typeEnum == SKILL_TYPE_YiBanGongJi ||
		typeEnum == SKILL_TYPE_JiChuJianShu ||
		typeEnum == SKILL_TYPE_WaKuang)
	{
		return false;
	}

	m_bLock = true;

	int skill_num = 1;
	if(typeEnum == SKILL_TYPE_HuoQiang)
	{
		skill_num = 15;
	}

	int num = 0;
	SkillMap::iterator it = m_skillCount.find(typeEnum);
	if(it != m_skillCount.end())
	{
		num = it->second.count;
	}

	if((num + 1) > skill_num)
	{
		m_bLock = false;
		return true;
	}

	m_bLock = false;
	return false;
}

void SkillEffect::removeAllSkills()
{
	if(m_bLock)
	{
		return;
	}
	m_bLock = true;
	CPForeach(it, SkillMap, m_skillCount)
	{
		releaseSkillVect(it->second.skills);
	}
	m_skillCount.clear();
	m_bLock = false;
}

bool SkillEffect::isSkillNeedTarget( int skillID )
{
	const int typeEnum = skillID/10;
	if (typeEnum == SKILL_TYPE_HuoQiuShu ||
		typeEnum == SKILL_TYPE_LeiDianShu ||
		typeEnum == SKILL_TYPE_BingPaoXiao ||
		typeEnum == SKILL_TYPE_JiChuJianShu ||
		typeEnum == SKILL_TYPE_LieHuoJianFa ||
		typeEnum == SKILL_TYPE_BanYueWanDao ||
		typeEnum == SKILL_TYPE_CiShaJianShu ||
		typeEnum == SKILL_TYPE_LingHunHuoFu ||
		typeEnum == SKILL_TYPE_ShiDuShu ||
		typeEnum == SKILL_TYPE_YiBanGongJi ||
		typeEnum == SKILL_TYPE_CAIJI)
	{
		return true;
	}
	return false;
}

bool SkillEffect::needTurnToTarget( int skillID )
{
	const int typeEnum = skillID/10;
	if (typeEnum == SKILL_TYPE_CiShaJianShu ||
		typeEnum == SKILL_TYPE_ChuanTouShanDian)
	{
		return true;
	}
	return false;
}

bool SkillEffect::isShortRange( int skillID )
{
	const int typeEnum = skillID/10;
	if (typeEnum == SKILL_TYPE_JiChuJianShu ||
		typeEnum == SKILL_TYPE_LieHuoJianFa ||
		typeEnum == SKILL_TYPE_BanYueWanDao ||
		typeEnum == SKILL_TYPE_YiBanGongJi ||
		typeEnum == SKILL_TYPE_WaKuang ||
		typeEnum == SKILL_TYPE_CAIJI)
	{
		return true;
	}
	return false;
}

void SkillEffect::releaseSkillVect( SkillVect &vect )
{
	for (int i = 0; i < (int)vect.size(); i++)
	{
		vect[i]->release();
	}
	vect.clear();
}

void SkillEffect::setSkillCD( int skillID )
{
	int cd = 0;
	StaticData::getSkillCD(skillID, cd);
	if (cd > 0)
	{
		// 仅普攻类技能CD随攻速缩短, 其它技能保持原始CD
		// 规则: skillID/10==100(普通攻击) 或 10<=skillID/10<20(基础剑法系列)
		int typeEnum = skillID / 10;
		bool isNormalAttack = (typeEnum == 100) || (typeEnum >= 10 && typeEnum < 20);
		if (isNormalAttack)
		{
			GameRole* myRole = GameData::getMyRole();
			if (myRole)
			{
				float atkSpeedMul = 1.0f + myRole->CombatData[Combat::prop_Attack_Speed] / 100.0f;
				if (atkSpeedMul < 0.1f) atkSpeedMul = 0.1f;
				cd = (int)(cd / atkSpeedMul);
			}
		}
		HeroData::setSkillCD(skillID, cd / 1000);
	}
}
