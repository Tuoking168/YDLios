#include "TimeManager.h"
#include "EntityDefinition.h"
#include "ModuleData.h"
#include "SceneModule.h"
#include "HeroModule.h"
#include "ActivityModule.h"

#include "userdata/SceneData.h"
#include "event/CPEventHelper.h"
#include "utils/StringUtils.h"

/////////TimeManager///////////////////////////////////////////////////
TimeManager::TimeManager()
{
	init();
}

TimeManager & TimeManager::instance()
{
	static TimeManager mng;
	return mng;
}

TimeManager::~TimeManager()
{

}

void TimeManager::init()
{
	addKey(CPModuleName::SCENE, CPSceneData::PROP_, SceneData::getPropKey("scene_time_remain"));
	addKey(CPModuleName::HERO, CPHeroData::SKILL_LIST, CPHeroData::SKILL_CD);
	addKey(CPModuleName::HERO, CPHeroData::COMMON_CD_LIST, CPHeroData::COMMON_CD);
	addKey(CPModuleName::HERO, CPHeroData::REWARD_TIME_LIST, CPHeroData::REWARD_TIME);
	addKey(CPModuleName::HERO, CPHeroData::PROP_, Entity::attr_meinvhusong_remain);
	addKey(CPModuleName::ACTIVITY, "", CPActivityData::WORLD_TIME, true);
}

void TimeManager::update()
{
	for (int i = 0; i < (int)mTimeVect.size(); i++)
	{
		if (mTimeVect[i].subModule.empty())
		{
			updateNormModule(i);
		}
		else
		{
			updateSubModule(i);
		}
	}
	CPEventHelper::dispatcher(CPEventName::LGC_TIMER, "TimeManager", "");
}

void TimeManager::clear()
{
	mTimeVect.clear();
}

void TimeManager::addKey( const std::string &module, const std::string &key )
{
	addKey(module, "", key);
}

void TimeManager::addKey( const std::string &module, const std::string &keyHead, int key )
{
	const std::string &fullKey = keyHead + StringUtils::toString(key);
	addKey(module, fullKey);
}

void TimeManager::addKey( const std::string &module, const std::string &subModule, const std::string &key )
{
	addKey(module, subModule, key, false);
}

void TimeManager::addKey( const std::string &module, const std::string &subModule, const std::string &key, bool toAdd )
{
	TimeKey timeKey;
	timeKey.module = module;
	timeKey.subModule = subModule;
	timeKey.key = key;
	timeKey.toAdd = toAdd;
	mTimeVect.push_back(timeKey);
}

void TimeManager::updateNormModule( int index )
{
	const bool toAdd = mTimeVect[index].toAdd;
	int time = 0;
	ModuleData::getInt(mTimeVect[index].module, mTimeVect[index].key, time);
	toNextTime(time, toAdd);
	ModuleData::setInt(mTimeVect[index].module, mTimeVect[index].key, time);
}

void TimeManager::updateSubModule( int index )
{
	const bool toAdd = mTimeVect[index].toAdd;
	SubModuleData::init(mTimeVect[index].module, mTimeVect[index].subModule);
	int time = 0;
	IDVector vect;
	SubModuleData::getIDVector(vect);
	for (int i = 0; (int)i < vect.size(); i++)
	{
		time = 0;
		SubModuleData::getInt(vect[i], mTimeVect[index].key, time);
		toNextTime(time, toAdd);
		SubModuleData::setInt(vect[i], mTimeVect[index].key, time);
	}
}

void TimeManager::toNextTime( int &time, bool toAdd )
{
	if (toAdd)
	{
		time++;
	}
	else
	{
		time--;
		if (time < 0)
		{
			time = 0;
		}
	}
}
