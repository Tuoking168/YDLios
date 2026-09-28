#include "CPUpdateFunctorSkillUse.h"
#include "UserDataModule.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/StaticData.h"
#include "userdata/netdata/GameRole.h"

#include "utils/StringUtils.h"

CPUpdateFunctorSkillUse::CPUpdateFunctorSkillUse()
{

}

CPUpdateFunctorSkillUse::CPUpdateFunctorSkillUse( int tag, int time )
	:CPUpdateFunctorImp(tag, time)
{

}

bool CPUpdateFunctorSkillUse::onUpdate()
{
	if (!CPUpdateFunctorImp::onUpdate())
	{
		return false;
	}

	int saimachangFlag = 0;
	StaticData::getMapSaiMaChangFlag(GameData::getCurrentMap()->mID, saimachangFlag);
	if (saimachangFlag)
	{
		return false;
	}

	const std::string &strsr = CPUserData::UPDATE_FUNCTOR_ID + StringUtils::toString(m_nTag) + "_";
	const float percent = UserData::getIntData(HeroData::getPID(), strsr, 3) / 100.0f;
	GameRole* myRole = GameData::getMyRole();
	if (myRole && !myRole->isDead())
	{
		const int maxhp = myRole->mMaxHp;
		const int hp = myRole->mHp;
		const float nowPercent = hp / (maxhp + 0.1f);
		if (nowPercent < percent)
		{
			const int skillID = UserData::getIntData(HeroData::getPID(), strsr, 4);
			int currentSkillID = 0;
			if (myRole->isSkillLearned(skillID, currentSkillID))
			{
				myRole->startCastSkill(currentSkillID);
				return true;
			}
		}		
	}

	return false;
}

/////////////CPUpdateFunctorSummonDog////////////////////////////////
CPUpdateFunctorSummonDog::CPUpdateFunctorSummonDog()
{

}

CPUpdateFunctorSummonDog::CPUpdateFunctorSummonDog( int tag, int time )
	:CPUpdateFunctorImp(tag, time)
{

}

bool CPUpdateFunctorSummonDog::onUpdate()
{
	if (!GameData::s_user)
	{
		return false;
	}
	if (m_nUpdateTime + m_nInterval > GameData::s_user->millisecondNow())
	{
		return false;
	}
	m_nUpdateTime = GameData::s_user->millisecondNow();
	GameRole* myRole = GameData::getMyRole();
	if (myRole && !myRole->isDead())
	{
		myRole->checkSummonDog();
		return true;
	}

	return false;
}
