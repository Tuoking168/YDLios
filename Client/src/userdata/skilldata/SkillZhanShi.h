#ifndef	___SKILL_ZHANSHI_____
#define ___SKILL_ZHANSHI_____

#include "SkillModel.h"
#include "cocos2d.h"

#include "ext/CCActionDestroy.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/netdata/HeroAvatar.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/luadata/LuaData.h"

using namespace cocos2d;

class cZSBaseSkill : public cSkillJinShenGongJi
{
public:
	cZSBaseSkill(AliveGhost* hero,short type) : cSkillJinShenGongJi(hero,type)
	{
		std::string skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_src",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_cast = SystemData::getAnimation(skill_anim);
		}			
	}
	virtual void castSkill(int x, int y, int id);
};

class cSkillJiChuJianFa: public cZSBaseSkill
{
public:
	cSkillJiChuJianFa(AliveGhost* hero,short type) : cZSBaseSkill(hero,type)
	{}
};

class cSkillCiShaJianShu: public cZSBaseSkill
{
public:
	cSkillCiShaJianShu(AliveGhost* hero,short type) : cZSBaseSkill(hero,type)
	{}
};

class cSkillLieHuoJianFa: public cZSBaseSkill
{
public:
	cSkillLieHuoJianFa(AliveGhost* hero,short type) : cZSBaseSkill(hero,type)
	{}
};

class cSkillBanYueWanDao: public cZSBaseSkill
{
public:
	cSkillBanYueWanDao(AliveGhost* hero,short type) : cZSBaseSkill(hero,type)
	{}
};

class cSkillYeManChongZhuang: public cZSBaseSkill
{
public:
	cSkillYeManChongZhuang(AliveGhost* hero,short type) : cZSBaseSkill(hero,type)
	{}
};

class cSkillMonArrow: public cSkillCastModel
{
public:
	cSkillMonArrow(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{}
	virtual void castOut();
};

class cSkillYunShi: public cSkillCastModel
{
public:
	cSkillYunShi(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{
		std::string skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_src",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_cast = SystemData::getAnimationOneDir(skill_anim);
		}

		skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_tgt",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_explode = SystemData::getAnimationOneDir(skill_anim);
		}
	}
	virtual void castOut();
	virtual void castEnd();
};

class cSkillLevelUp: public cSkillCastModel
{
public:
	cSkillLevelUp(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{
		m_cast = SystemData::getAnimationOneDir(LayoutData::getString(CPModuleName::COMMON, "levelupAnim"));
	}
	virtual void castSkill(int x=0, int y=0, int id=-1);
};

class cSkillRelive: public cSkillCastModel
{
public:
	cSkillRelive(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{
		m_cast = SystemData::getAnimationOneDir(LayoutData::getString(CPModuleName::COMMON, "reliveAnim"));
	}
	virtual void castSkill(int x=0, int y=0, int id=-1);
};


#endif // ___SKILL_ZHANSHI_____