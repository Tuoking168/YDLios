#ifndef __ACCELERATION_ACTION__
#define __ACCELERATION_ACTION__

#include "cocos2d.h"
using namespace cocos2d;
class AccelerationAction : public CCActionInterval
{
public:
	AccelerationAction(void);
	static AccelerationAction* create(const CCPoint& speed, float acceleration);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void update(float time);
protected:
	bool initWithProp(const CCPoint& speed, float acceleration);
private:
	CCPoint m_startPosition;
	CCPoint m_startSpeed;
	float m_acceleration;
};
#endif//__ACCELERATION_ACTION__
