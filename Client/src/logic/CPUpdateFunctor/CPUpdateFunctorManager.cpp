#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "module/UserDataModule.h"
#include "userdata/HeroData.h"

#include "CPUpdateFunctorDefination.h"
#include "CPUpdateFunctorManager.h"
#include "CPUpdateFunctorPotionUse.h"
#include "CPUpdateFunctorSkillUse.h"


CPUpdateFunctorManager::CPUpdateFunctorManager():
	update_time(1.0f)
	,mHasInited(false)
{

}

CPUpdateFunctorManager::~CPUpdateFunctorManager()
{
	onClear();
}

void CPUpdateFunctorManager::onUpdate(float dt)
{
	initIfNeeded();
	update_time -= dt;
	if (update_time <= 0)
	{
		update_time += 1.0f;
		CPForeach(it, CPUpdateFunctorMap, m_Functors)
		{
			it->second->onUpdate();
		}
	}
}

bool CPUpdateFunctorManager::addFunctor( int tagid )
{
	CPUpdateFunctorMap::iterator it = m_Functors.find(tagid);
	if (it != m_Functors.end())
	{
		delete it->second;
		it->second = NULL;
	}

	if (tagid < CPUFDefination::PotionTagEnd && tagid >= CPUFDefination::PotionTagBegin)
	{
		const std::string &strsr = CPUserData::UPDATE_FUNCTOR_ID + SystemData::intToString(tagid) + "_";	
		const int time = UserData::getIntData(HeroData::getPID(), strsr, 2) * 1000;
		
		CPUpdateFunctorPotionUse* potionuse = new CPUpdateFunctorPotionUse(tagid, time);
		m_Functors[tagid] = potionuse;
	}
	else if (CPUFDefination::SkillTagBegin <= tagid
		&& tagid < CPUFDefination::SkillTagEnd)
	{
		ICPUpdateFunctor* skillUse = NULL;
		if (tagid==CPUFDefination::Skill_DS_Hui_Fu_Shu)
		{
			const std::string &strsr = CPUserData::UPDATE_FUNCTOR_ID + SystemData::intToString(tagid) + "_";	
			const int time = UserData::getIntData(HeroData::getPID(), strsr, 2) * 1000;

			skillUse = new CPUpdateFunctorSkillUse(tagid, time);
		}
		else if (tagid==CPUFDefination::Skill_DS_ZhaoHuan)
		{
			 skillUse = new CPUpdateFunctorSummonDog(tagid, 3000);
		}
		m_Functors[tagid] = skillUse;
	}
	return true;
}

bool CPUpdateFunctorManager::rmvFunctor( int tagid )
{
	CPUpdateFunctorMap::iterator it = m_Functors.find(tagid);
	if (it != m_Functors.end())
	{
		delete it->second;
		m_Functors.erase(it);
	}
	return true;
}

bool CPUpdateFunctorManager::hasFunctor( int tagid )
{
	return (m_Functors.find(tagid) != m_Functors.end());
}

ICPUpdateFunctor * CPUpdateFunctorManager::getFunctor( int tagid )
{
	CPUpdateFunctorMap::iterator it = m_Functors.find(tagid);
	if (it != m_Functors.end())
	{
		return it->second;
	}
	return NULL;
}

void CPUpdateFunctorManager::initIfNeeded()
{
	if (mHasInited)
	{
		return;
	}

	const int pid = HeroData::getPID();
	if (pid <= 0)
	{
		return;
	}

	const int taglist[] = 
	{
		CPUFDefination::HpLow_Potion1,
		CPUFDefination::HpLow_Potion2,
		CPUFDefination::HpLow_Scroll,
		CPUFDefination::MpLow_Potion1,
		CPUFDefination::MpLow_Potion2,
		CPUFDefination::EquipDuration,
		CPUFDefination::Skill_DS_Hui_Fu_Shu,
	};

	for (int i = 0; i < sizeof(taglist)/sizeof(int); i++)
	{
		if (taglist[i] == CPUFDefination::Skill_DS_Hui_Fu_Shu
			&& HeroData::getJob() == UserData::CARRER_OMNI)
		{
			continue;
		}
		const std::string &strsr = CPUserData::UPDATE_FUNCTOR_ID + SystemData::intToString(taglist[i]) + "_";
		const bool isopen = (UserData::getIntData(pid, strsr, 1) != 0);
		if (isopen)
		{
			addFunctor(taglist[i]);
		}
	}
	if (HeroData::getJob() != UserData::CARRER_OMNI)
	{
		addFunctor(CPUFDefination::Skill_DS_ZhaoHuan);
	}

	mHasInited = true;
}

void CPUpdateFunctorManager::onClear()
{
	CPForeach(it, CPUpdateFunctorMap, m_Functors)
	{
		delete it->second;
	}
	m_Functors.clear();
	mHasInited = false;
}

CPUpdateFunctorManager * CPUpdateFunctorManager::instance()
{
	static CPUpdateFunctorManager s_instance;
	return &s_instance;
}


