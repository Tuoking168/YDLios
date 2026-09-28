#include "CPUpdateFunctorPotionUse.h"
#include "UserDataModule.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/UserItemData.h"
#include "userdata/HeroData.h"

#include "logic/ItemOperator.h"

CPUpdateFunctorPotionUse::CPUpdateFunctorPotionUse()
{

}

CPUpdateFunctorPotionUse::CPUpdateFunctorPotionUse( int tag,int time ):
	CPUpdateFunctorImp(tag,time)
{

}


bool CPUpdateFunctorPotionUse::onUpdate()
{
	if (!CPUpdateFunctorImp::onUpdate())
	{
		return false;
	}

	const std::string &strsr= CPUserData::UPDATE_FUNCTOR_ID+SystemData::intToString(m_nTag) + "_";
	const float percent = UserData::getIntData(HeroData::getPID(),strsr,3) / 100.0f;
	float nowPercent = 100.0f;
	if (m_nTag > CPUFDefination::PotionHpBegin && m_nTag <CPUFDefination::PotionHpEnd)
	{
		if (m_nTag == CPUFDefination::HpLow_Scroll)
		{
			return false;
		}

		// TODO get now player hp percent
		int maxhp = GameData::s_user->m_pMainRole->mMaxHp;
		int hp = GameData::s_user->m_pMainRole->mHp;
		nowPercent = (float)hp / (float)maxhp;
	}
	else if (m_nTag > CPUFDefination::PotionMpBegin && m_nTag <CPUFDefination::PotionMpEnd)
	{
		// TODO get now player mp percent
		int maxmp = GameData::s_user->m_pMainRole->mMaxMp;
		int mp = GameData::s_user->m_pMainRole->mMp;
		nowPercent = (float)mp / (float)maxmp;
	}
	else if (m_nTag == CPUFDefination::EquipDuration)
	{
		nowPercent = ItemOperator::getCurEquipEndure()/100.0f;
	}
	GameRole* myRole = GameData::getMyRole();
	if (myRole && !myRole->isDead())
	{
		if (nowPercent < percent)
		{
			const int useitemid = UserData::getIntData(HeroData::getPID(), strsr, 4);
			// TODO if get tag target item use tag target Item
			if (useitemid)
			{
				UserItemData *userItems = GameData::getUserItemData();
				if (userItems)
				{
					const int iid = userItems->getItemBySid(useitemid);
					if (iid > 0)
					{
						ItemOperator::useItem(iid);
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

