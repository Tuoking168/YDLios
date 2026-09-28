#ifndef __NET_CHARACTER_H__
#define __NET_CHARACTER_H__

#include "CommonType.h"
#include "CombatDefinition.h"

class NetCharacter
{
public:
	NetCharacter();
	virtual ~NetCharacter(){}

public:
	int64 mExperience;
	int64 mExperienceNext;
	int mCombatNum;
	int CombatData[Combat::prop_Normal_End];
	int Honour;
	int PK_NUM;
};

#endif//__NET_CHARACTER_H__