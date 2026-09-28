#include "AccelerationAction.h"

AccelerationAction::AccelerationAction( void )
:m_acceleration(5)
,m_startSpeed(ccp(0,0))
{

}

AccelerationAction* AccelerationAction::create( const CCPoint& speed, float acceleration )
{
	AccelerationAction *pRet = new AccelerationAction(); 
	if (pRet && pRet->initWithProp(speed,acceleration)) 
	{ 
		pRet->autorelease();
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}
bool AccelerationAction::initWithProp(const CCPoint& speed,float acceleration)
{
	m_startSpeed=speed;
	m_acceleration=acceleration;
	float vx=m_startSpeed.x;
	float vy=m_startSpeed.y;
	float tx=fabs(vx/m_acceleration);
	float ty=fabs(vy/m_acceleration);
	float d=(tx > ty ? tx : ty);
	CCActionInterval::initWithDuration(d);
	return true;
}

void AccelerationAction::startWithTarget( CCNode *pTarget )
{
	CCActionInterval::startWithTarget(pTarget);
	m_startPosition = pTarget->getPosition();
}

void AccelerationAction::update( float time )
{
	if (m_pTarget)
	{
		float svx=m_startSpeed.x;
		float svy=m_startSpeed.y;
		short sign=svx==0?(svy>0?1:-1):(svx>0?1:-1);
		float xy=sign*m_acceleration*m_elapsed*m_elapsed/2;
		float dx=svx==0?0:xy;
		float dy=svy==0?0:xy;
		float sx=svx*m_elapsed-dx;
		float sy=svy*m_elapsed-dy;
		CCPoint dp=ccpAdd(ccp(sx,sy),m_startPosition);
		m_pTarget->setPosition(dp);
	}
}
