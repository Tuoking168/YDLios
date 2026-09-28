#ifndef	___SKILL_FASHI_____
#define ___SKILL_FASHI_____

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

class cSkillHuoQiuShu : public cSkillCastModel
{
public:
	cSkillHuoQiuShu(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
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

class cSkillHuoQiangShu : public cSkillCastModel
{
public:
	cSkillHuoQiangShu(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
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

class cSkillKangJuHuoHuan: public cSkillCastModel
{
public:
	cSkillKangJuHuoHuan(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{
		std::string skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_src",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_cast = SystemData::getAnimationOneDir(skill_anim);
		}			
	}
	void castSkill(int x=0, int y=0, int id=-1);
};

class cSkillLeiDianShu: public cSkillCastModel
{
public:
	cSkillLeiDianShu(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
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

class cSkillMoFaDun: public cSkillCastModel
{
public:
	cSkillMoFaDun(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{
		std::string skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type,"effect_src",skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_cast = SystemData::getAnimationOneDir(skill_anim);
		}			
	}
	
	virtual void castOut();
};

class cSkillBingPaoXiao: public cSkillCastModel
{
public:
	cSkillBingPaoXiao(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
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
};

class cSkillChuanTouShanDian : public cSkillCastModel
{
public:
	cSkillChuanTouShanDian(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
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

class cSkillShunYi: public cSkillCastModel
{
public:
	cSkillShunYi(AliveGhost* hero,short type) : cSkillCastModel(hero,type)
	{
		std::string skill_anim = "";
		LuaData::getProp(LuaData::SKILL,type, "effect_src", skill_anim);
		if(!skill_anim.empty())
		{
			skill_anim = "effect/" + skill_anim;
			m_cast = SystemData::getAnimationOneDir(skill_anim);
		}			
	}
};


#endif // ___SKILL_FASHI_____