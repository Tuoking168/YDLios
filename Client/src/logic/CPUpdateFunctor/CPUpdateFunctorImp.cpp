#include "CPUpdateFunctorImp.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "module/UserDataModule.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/HeroData.h"

CPUpdateFunctorImp::CPUpdateFunctorImp():
	m_nTag(0),
	m_nInterval(1000),
	m_nUpdateTime( GameData::s_user->millisecondNow())
{

}

CPUpdateFunctorImp::CPUpdateFunctorImp( int tag,int time ):
	m_nTag(tag),
	m_nInterval(time),
	m_nUpdateTime( GameData::s_user->millisecondNow())
{

}

void CPUpdateFunctorImp::setTag( int tag )
{
	m_nTag = tag;
}

bool CPUpdateFunctorImp::onUpdate()
{
	const std::string &strsr = CPUserData::UPDATE_FUNCTOR_ID+SystemData::intToString(m_nTag)+ "_";	
	m_nInterval = UserData::getIntData(HeroData::getPID(),strsr,2) * 1000;
	if (m_nUpdateTime + m_nInterval < GameData::s_user->millisecondNow())
	{
		m_nUpdateTime = GameData::s_user->millisecondNow();
		return true;
	}
	return false;
}

void CPUpdateFunctorImp::setInterval( int time )
{
	m_nInterval = time;
	if (m_nInterval <= 0)
	{
		m_nInterval = 1;
	}
}

int CPUpdateFunctorImp::getTag() const
{
	return m_nTag;
}

int CPUpdateFunctorImp::getInterval() const
{
	return m_nInterval;
}
