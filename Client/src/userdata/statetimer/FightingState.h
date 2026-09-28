#ifndef __FIGHTING_STATE_H__
#define __FIGHTING_STATE_H__


class FightingState
{
public:
	const static int FIGHT_TIME_INTEVAL = 3;
	static bool isFighting;
	static int	stateTimeLeft;
	static void update();
	static void start();
};


#endif//__FIGHTING_STATE_H__