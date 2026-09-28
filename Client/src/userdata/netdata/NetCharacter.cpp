#include "NetCharacter.h"


NetCharacter::NetCharacter()
	: mExperience(0)
	, mCombatNum(0)
	, mExperienceNext(100)
	, Honour(0)
	, PK_NUM(0)
{
	for (short idx = 0; idx<Combat::prop_Normal_End; idx++)
	{
		CombatData[idx] = 0;
	}
}
