#include "AutoAttack.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"

bool AutoAttack::m_bAutoAttack = false;

void AutoAttack::openAutoAttack()
{
	if (!AutoAttack::checkAutoAttack())
	{
		CPEventHelper::setEventIntData(CPEventName::UI_CHANGE,CPEventData::VALUE_1,1);
		CPEventHelper::dispatcher(CPEventName::UI_CHANGE,"AutoAttack","TopActivity");
	}
	AutoAttack::m_bAutoAttack = true;
	GameData::s_user->m_pMainRole->autoAttack();
}

void AutoAttack::closeAutoAttack()
{
	if (AutoAttack::checkAutoAttack())
	{
		CPEventHelper::setEventIntData(CPEventName::UI_CHANGE,CPEventData::VALUE_1,0);
		CPEventHelper::dispatcher(CPEventName::UI_CHANGE,"AutoAttack","TopActivity");
	}
	AutoAttack::m_bAutoAttack = false;
	//GameData::s_user->m_pMainRole->setEasyAI(false);
	GameData::s_user->m_pMainRole->stopAutoMoving();
}

bool AutoAttack::checkAutoAttack()
{
	return  AutoAttack::m_bAutoAttack;
}

