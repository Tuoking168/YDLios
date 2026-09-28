#ifndef _SKILLEFFECT_H_
#define _SKILLEFFECT_H_

#include <map>
#include <vector>

class cSkillModel;
class AliveGhost;

enum SKILL_ALL
{
	SKILL_TYPE_YiBanGongJi = 100,
	SKILL_TYPE_WaKuang	   = 200,
	SKILL_TYPE_CAIJI	   = 300,

	SKILL_TYPE_JiChuJianShu = 10,
	SKILL_TYPE_LieHuoJianFa = 11,
	SKILL_TYPE_BanYueWanDao = 12,
	SKILL_TYPE_CiShaJianShu = 13,
	SKILL_TYPE_YeManChongZhuang = 14,
	SKILL_TYPE_LieYanChongSheng = 15,

	SKILL_TYPE_HuoQiang = 20,
	SKILL_TYPE_HuoQiuShu = 21,
	SKILL_TYPE_LeiDianShu = 22,
	SKILL_TYPE_KangJuHuoHuan = 23,
	SKILL_TYPE_ChuanTouShanDian = 24,
	SKILL_TYPE_BingPaoXiao = 26,
	SKILL_TYPE_MoFaDun = 27,
	SKILL_TYPE_ShunYi = 28,

	SKILL_TYPE_QunTiZhiLiao = 30,
	SKILL_TYPE_LingHunHuoFu = 31,
	SKILL_TYPE_ShiDuShu = 32,
	SKILL_TYPE_JiTiYinShenShu = 33,
	SKILL_TYPE_ZhaoHuanShenShou = 36,
	SKILL_TYPE_DaYinYuShi = 37,

	SKILL_TYPE_YunShi = 506,

	SKILL_TYPE_MonArrow = 601,
	SKILL_TYPE_LevelUp = 602,
	SKILL_TYPE_Relive = 603
};

class SkillEffect
{
public:
	SkillEffect(AliveGhost* hero);
	~SkillEffect();

	static SkillEffect* create(AliveGhost*);
	
	void    runSkill(int skillID, int tx, int ty, AliveGhost* aim);
	
	void    removeSkill(int skillID);
	bool	hasSkill(int skillID);
	bool	overLimit(int skillID);
	void	removeAllSkills();

	static bool isSkillNeedTarget(int skillID);
	static bool needTurnToTarget(int skillID);
	static bool isShortRange(int skillID);

private:
	typedef std::vector<cSkillModel *> SkillVect;

	cSkillModel *createSkill(int skillID);
	void addSkill(int skillID, cSkillModel *skill);
	void releaseSkillVect(SkillVect &vect);
	void setSkillCD(int skillID);

private:
	struct SkillCount
	{
		SkillCount()
			:count(0)
		{}
		int count;
		SkillVect skills;
	};
	typedef std::map<short, SkillCount> SkillMap;
	SkillMap	m_skillCount;
	AliveGhost*	m_pHero;
	bool		m_bLock;
};

#endif