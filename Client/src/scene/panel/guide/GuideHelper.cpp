#include "GuideHelper.h"
#include "EntityDefinition.h"

#include "userdata/ActivityData.h"
#include "userdata/HeroData.h"
#include "userdata/TaskData.h"
#include "userdata/StaticData.h"



/////////GuideHelper//////////////////////////////////////////////////
bool GuideHelper::canOpenFunction( const std::string &funcName )
{
	int needReborn = 0, needLevel = 0, needQuest = 0, hide = 0, openDays = 0;
	StaticData::getFunctionOpenNeed(funcName, needReborn, needLevel, needQuest, hide, openDays);
	if (hide)
	{
		return false;
	}

	if (0 < openDays && openDays < ActivityData::getWorldBeginDays())
	{
		return false;
	}

	const int level = HeroData::getLevel();
	const int qid = TaskData::getFirstMainLineTask();
	const int reborn = HeroData::getProp(Entity::attr_reborn);
	if (reborn > needReborn)
	{
		if (qid >= needQuest || qid==0)
		{
			return true;
		}		
	}
	else if(reborn==needReborn)
	{
		if (level >= needLevel)
		{
			if (qid >= needQuest || qid==0)
			{
				return true;
			}
		}
	}
	return false;
}

bool GuideHelper::canOpenFunction( const int funcID )
{
	return !ActivityData::isHide(funcID);
}
