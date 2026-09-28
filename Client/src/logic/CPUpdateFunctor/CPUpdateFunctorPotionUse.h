#ifndef __CPUPUDATEFUNCTOR_POTIONUSE__
#define __CPUPUDATEFUNCTOR_POTIONUSE__

#include "CPUpdateFunctorImp.h"

class CPUpdateFunctorPotionUse : public CPUpdateFunctorImp
{
public:
	CPUpdateFunctorPotionUse();
	CPUpdateFunctorPotionUse(int tag,int time);
	virtual ~CPUpdateFunctorPotionUse(){;}

	virtual bool onUpdate();


};
#endif //__CPUPUDATEFUNCTOR_POTIONUSE__