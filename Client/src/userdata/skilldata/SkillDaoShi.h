#ifndef	___SKILL_DAOSHI_____
#define ___SKILL_DAOSHI_____

#include "SkillModel.h"
#include "cocos2d.h"
#include "userdata/netdata/HeroAvatar.h"
#include "ext/CCActionDestroy.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/SystemData.h"
#include "userdata/luadata/LuaData.h"
using namespace cocos2d;

class cSkillShiDuShu: public cSkillCastModel
{
public:
	cSkillShiDuShu(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{
		std::string skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_src",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_cast = SystemData::getAnimationOneDir(skill_anim);
		}

		skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_mid",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_Animstab = SystemData::getAnimationOneDir(skill_anim);
		}			
		LuaData::getProp(LuaData::SKILL,type,"effect_tgt",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_explode = SystemData::getAnimationOneDir(skill_anim);
		}			
	}
	virtual void castSkill(int x=0, int y=0, int id=-1);
	virtual void castOut();
};

class cSkillLingHunHuoFu: public cSkillCastModel
{
public:
	cSkillLingHunHuoFu(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{
		std::string skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_src",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_cast = SystemData::getAnimationOneDir(skill_anim);
		}

		skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_mid",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_Animstab = SystemData::getAnimationOneDir(skill_anim);
		}			
		LuaData::getProp(LuaData::SKILL,type,"effect_tgt",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_explode = SystemData::getAnimationOneDir(skill_anim);
		}			
	}
	virtual void castSkill(int x=0, int y=0, int id=-1);
	virtual void castOut();
};

class cSkillJiTiYinShenShu: public cSkillCastModel
{
public:
	cSkillJiTiYinShenShu(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{
		std::string skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_src",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_cast = SystemData::getAnimationOneDir(skill_anim);
		}			
	}
};

class cSkillQunTiZhiLiao: public cSkillCastModel
{
public:
	cSkillQunTiZhiLiao(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{
		std::string skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_src",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_cast = SystemData::getAnimationOneDir(skill_anim);
		}			
	}
};

class cSkillZhaoHuanShenShou: public cSkillCastModel
{
public:
	cSkillZhaoHuanShenShou(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{
		std::string skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_src",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_cast = SystemData::getAnimationOneDir(skill_anim);
		}			
	}
};


#endif // ___SKILL_DAOSHI_____