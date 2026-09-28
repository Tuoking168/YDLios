#include "HeroData.h"
#include "ModuleData.h"
#include "HeroModule.h"
#include "EntityDefinition.h"
#include "StaticData.h"
#include "CCCommon.h"
#include <algorithm>

#include "utils/StringUtils.h"

using namespace cocos2d;


static bool compareHeadName( int id1, int id2 )
{
	int count1 = 0, count2 = 0;
	StaticData::getHeadNamesAddPropCnt(id1, count1);
	StaticData::getHeadNamesAddPropCnt(id2, count2);
	if (count1 > 0 && count2 <= 0)
	{
		return true;
	}
	else if (count1 <= 0 && count2 > 0)
	{
		return false;
	}
	else
	{
		int priority1 = 0, priority2 = 0;
		StaticData::getHeadNamesData(id1, "priority", priority1);
		StaticData::getHeadNamesData(id2, "priority", priority2);
		return (priority1 > priority2);
	}
}

/////////HeroData////////////////////////////////////////////////////////
void HeroData::setPID( int pid )
{
	ModuleData::setInt(CPModuleName::HERO, CPHeroData::PID, pid);
}

int HeroData::getPID()
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::HERO, CPHeroData::PID, ret);
	return ret;
}

void HeroData::setLevel( int level )
{
	ModuleData::setInt(CPModuleName::HERO, CPHeroData::LEVEL, level);
}

int HeroData::getLevel()
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::HERO, CPHeroData::LEVEL, ret);
	return ret;
}

std::string HeroData::getLevelString()
{
	return StringUtils::levelToString(getProp(Entity::attr_reborn), getLevel());
}

void HeroData::setJob( int job )
{
	ModuleData::setInt(CPModuleName::HERO, CPHeroData::JOB, job);
}

int HeroData::getJob()
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::HERO, CPHeroData::JOB, ret);
	return ret;
}

void HeroData::setGender( int gender )
{
	ModuleData::setInt(CPModuleName::HERO, CPHeroData::GENDER, gender);
}

int HeroData::getGender()
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::HERO, CPHeroData::GENDER, ret);
	return ret;
}

void HeroData::setProp( int key, int value )
{
	const std::string fullKey = CPHeroData::PROP_ + StringUtils::toString(key);
	ModuleData::setInt(CPModuleName::HERO, fullKey, value);
}

int HeroData::getProp( int key )
{
	int ret = 0;
	const std::string fullKey = CPHeroData::PROP_ + StringUtils::toString(key);
	ModuleData::getInt(CPModuleName::HERO, fullKey, ret);
	return ret;
}

void HeroData::updateBuff( int geneID, int duration ,int starttime)
{
	SubModuleData::init(CPModuleName::HERO, CPHeroData::BUFF_LIST);
	SubModuleData::setInt(geneID, CPHeroData::DURATION, duration);
	SubModuleData::setInt(geneID, CPHeroData::STARTTIME, starttime);
}

int HeroData::getBuffStartTime( int geneID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::HERO, CPHeroData::BUFF_LIST);
	SubModuleData::getInt(geneID, CPHeroData::STARTTIME, ret);
	return ret;
}

int HeroData::getBuffTime( int geneID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::HERO, CPHeroData::BUFF_LIST);
	SubModuleData::getInt(geneID, CPHeroData::DURATION, ret);
	return ret;
}

void HeroData::removeBuff( int geneID )
{
	SubModuleData::init(CPModuleName::HERO, CPHeroData::BUFF_LIST);
	SubModuleData::clearData(geneID);
}

bool HeroData::hasBuff( int geneID )
{
	SubModuleData::init(CPModuleName::HERO, CPHeroData::BUFF_LIST);
	int ret;
	return SubModuleData::getInt(geneID, CPHeroData::DURATION, ret);
}

IDVector HeroData::getBuffVect()
{
	IDVector ret;
	SubModuleData::init(CPModuleName::HERO, CPHeroData::BUFF_LIST);
	SubModuleData::getIDVector(ret);
	return ret;
}

void HeroData::resetGlobalCD()
{
	int time = 0;
	StaticData::getGlobalData("playerattackinterval", time);
	setGlobalCD(time/1000.0f);
}

void HeroData::setGlobalCD( float cd )
{
	ModuleData::setFloat(CPModuleName::HERO, CPHeroData::GLOBAL_CD, cd);
}

float HeroData::getGlobalCD()
{
	float ret = 0;
	ModuleData::getFloat(CPModuleName::HERO, CPHeroData::GLOBAL_CD, ret);
	return ret;
}

void HeroData::setCommonCD( int cdID, int cd, int ex )
{
	SubModuleData::init(CPModuleName::HERO, CPHeroData::COMMON_CD_LIST);
	SubModuleData::setInt(cdID, CPHeroData::COMMON_CD, cd);
	SubModuleData::setInt(cdID, CPHeroData::COMMON_CD_EX, ex);
}

int HeroData::getCommonCD( int cdID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::HERO, CPHeroData::COMMON_CD_LIST);
	SubModuleData::getInt(cdID, CPHeroData::COMMON_CD, ret);
	return ret;
}

int HeroData::getCommonCDEx( int cdID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::HERO, CPHeroData::COMMON_CD_LIST);
	SubModuleData::getInt(cdID, CPHeroData::COMMON_CD_EX, ret);
	return ret;
}

void HeroData::setSkillExp( int skillID, int exp )
{
	SubModuleData::init(CPModuleName::HERO, CPHeroData::SKILL_LIST);
	SubModuleData::setInt(skillID, CPHeroData::SKILL_EXP, exp);
}

int HeroData::getSkillExp( int skillID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::HERO, CPHeroData::SKILL_LIST);
	SubModuleData::getInt(skillID, CPHeroData::SKILL_EXP, ret);
	return ret;
}

void HeroData::setSkillCD( int skillID, int cd )
{	
	if (hasSkill(skillID))
	{
		SubModuleData::init(CPModuleName::HERO, CPHeroData::SKILL_LIST);
		SubModuleData::setInt(skillID, CPHeroData::SKILL_CD, cd);
	}
	else
	{
		CCLog(">>>Error: setSkillCD, unknown skillID = %d", skillID);
	}
}

int HeroData::getSkillCD( int skillID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::HERO, CPHeroData::SKILL_LIST);
	SubModuleData::getInt(skillID, CPHeroData::SKILL_CD, ret);
	return ret;
}

IDVector HeroData::getSkillVect()
{
	IDVector ret;
	SubModuleData::init(CPModuleName::HERO, CPHeroData::SKILL_LIST);
	SubModuleData::getIDVector(ret);
	return ret;
}

bool HeroData::hasSkill( int skillID )
{
	const IDVector &vect = getSkillVect();
	for (int i = 0; i < (int)vect.size(); i++)
	{
		if (vect[i] == skillID)
		{
			return true;
		}
	}
	return false;
}

void HeroData::clearSkill( int skillID )
{
	SubModuleData::init(CPModuleName::HERO, CPHeroData::SKILL_LIST);
	SubModuleData::clearData(skillID);
}

void HeroData::clearAllSkill()
{
	SubModuleData::init(CPModuleName::HERO, CPHeroData::SKILL_LIST);
	SubModuleData::clearAll();
}

void HeroData::setRewardTime( int timeID, int time, int data1, int data2, int data3 )
{
	SubModuleData::init(CPModuleName::HERO, CPHeroData::REWARD_TIME_LIST);
	SubModuleData::setInt(timeID, CPHeroData::REWARD_TIME, time);
	SubModuleData::setInt(timeID, CPHeroData::REWARD_TIME_EX_DATA_X, data1);
	SubModuleData::setInt(timeID, CPHeroData::REWARD_TIME_EX_DATA_Y, data2);
	SubModuleData::setInt(timeID, CPHeroData::REWARD_TIME_EX_DATA_Z, data3);
}

int HeroData::getRewardTime( int timeID )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::HERO, CPHeroData::REWARD_TIME_LIST);
	SubModuleData::getInt(timeID, CPHeroData::REWARD_TIME, ret);
	return ret;
}

void HeroData::getRewardTimeEx( int timeID, int &data1, int &data2, int &data3 )
{
	SubModuleData::init(CPModuleName::HERO, CPHeroData::REWARD_TIME_LIST);
	SubModuleData::getInt(timeID, CPHeroData::REWARD_TIME_EX_DATA_X, data1);
	SubModuleData::getInt(timeID, CPHeroData::REWARD_TIME_EX_DATA_Y, data2);
	SubModuleData::getInt(timeID, CPHeroData::REWARD_TIME_EX_DATA_Z, data3);
}

IDVector HeroData::getOwnedHeadNames()
{
	return getHeadNames(getProp(Entity::attr_has_headtitle));
}

IDVector HeroData::getWornHeadNames()
{
	return getHeadNames(getProp(Entity::attr_open_headtitle));
}

IDVector HeroData::getHeadNames( int base )
{
	if (base < 0)
	{
		base = 0;
	}

	IDVector ret;
	const int intLen = 32;
	int mark = 0;
	for (int i = 0; i < intLen; i++)
	{
		mark = 1 << i;
		if ((mark & base) != 0)
		{
			ret.push_back(i + 1);
		}
	}
	std::sort(ret.begin(), ret.end(), compareHeadName);
	return ret;
}

bool HeroData::getHeadNameIsOwned( int id )
{
	if (id < 0)
	{
		id = 0;
	}
	IDVector it = getOwnedHeadNames();
	for (IDVector::iterator it1 = it.begin();it1!=it.end();it1++)
	{
		int a = * it1;
		if (id == a)
		{
			return true;
		}
	}
	return false;
}

bool HeroData::getHeadNameIsWorn( int id )
{
	if (id < 0)
	{
		id = 0;
	}
	IDVector it = getWornHeadNames();
	for (IDVector::iterator it1 = it.begin();it1!=it.end();it1++)
	{
		int a = * it1;
		if (id == a)
		{
			return true;
		}
	}
	return false;
}

void HeroData::clear()
{
	ModuleData::clearModule(CPModuleName::HERO);
}

