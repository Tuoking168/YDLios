#include "FightingState.h"

bool FightingState::isFighting = false;
int FightingState::stateTimeLeft = 0;

void FightingState::update()
{
	if(stateTimeLeft>0)
	{
		stateTimeLeft--;
		if(stateTimeLeft == 0)
		{
			isFighting = false;
		}
	}
}

void FightingState::start()
{
	stateTimeLeft = FIGHT_TIME_INTEVAL;
	isFighting = true;
}
