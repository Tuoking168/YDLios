#ifndef	___SKILL_MODEL_____
#define ___SKILL_MODEL_____


#include "cocos2d.h"
#include "userdata/netdata/AliveGhost.h"
#include "ext/CCActionDestroy.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/SystemData.h"

using namespace cocos2d;


class cSkillModel : public CCObject
{
public:
	cSkillModel(AliveGhost* hero,short type)
		:m_Animstab(NULL)
		,m_ghost(NULL)
	{
		m_pHero = hero;
		m_nType = type;
	}
	virtual void castSkill(int x=0, int y=0, int id=-1) = 0;

public:
	// 技能飞行动画
	CCFlashAnimation*	m_Animstab;

	// 施法英雄
	AliveGhost*			m_pHero;

	// 技能Ghost
	Ghost*				m_ghost;
	short				m_nType;
};

class cSkillCastModel : public cSkillModel
{
public:
	cSkillCastModel(AliveGhost* hero,short type): cSkillModel(hero,type),m_cast(NULL),m_explode(NULL)
	{}
	~cSkillCastModel();
	virtual void castSkill(int x=0, int y=0, int id=-1);
	virtual void castOut();
	virtual void castEnd();
	virtual CCPoint getOffsetPosition(float angle);
	virtual void sendMessage();
	virtual void explode();

	//differet cast modes
	// A/s: source, B: mid, C: target
	virtual void AC();
	virtual void sBC();

private:
	void beginUpdate();
	void uiEnd();
	void logicEnd();

	void update(float dt);

public:
	// 起手动画
	CCFlashAnimation* m_cast;

	// 目标爆炸动画
	CCFlashAnimation* m_explode;
	int	m_destx;
	int m_desty;
	int m_aimID;
};


class cSkillJinShenGongJi : public cSkillModel
{
public:
	cSkillJinShenGongJi(AliveGhost* hero,short type)
	:cSkillModel(hero,type)
	,m_cast(NULL)
	{}
	virtual void castSkill(int x, int y, int id);
	virtual void castEnd();

public:
	CCFlashAnimation* m_cast;
};

class cSkillYiBanGongJi : public cSkillModel
{
public:
	cSkillYiBanGongJi(AliveGhost* hero,short type): cSkillModel(hero,type)
	{}
	virtual void castSkill(int x/* =0 */, int y/* =0 */, int id)
	{
	}
};

#endif // ___SKILL_MODEL_____