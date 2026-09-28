#ifndef __CPUpdateFunctorSkillUse_h__
#define __CPUpdateFunctorSkillUse_h__

#include "CPUpdateFunctorImp.h"

class CPUpdateFunctorSkillUse : public CPUpdateFunctorImp
{
public:
	CPUpdateFunctorSkillUse();
	CPUpdateFunctorSkillUse(int tag, int time);
	virtual ~CPUpdateFunctorSkillUse(){;}

	virtual bool onUpdate();
};

////////////CPUpdateFunctorSummonDog/////////////////////////////////////////////
class CPUpdateFunctorSummonDog : public CPUpdateFunctorImp
{
public:
	CPUpdateFunctorSummonDog();
	CPUpdateFunctorSummonDog(int tag, int time);
	virtual ~CPUpdateFunctorSummonDog(){;}

	virtual bool onUpdate();
};
#endif //__CPUpdateFunctorSkillUse_h__