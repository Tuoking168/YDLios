#ifndef __CPUPUDATEFUNCTOR_IMP__
#define __CPUPUDATEFUNCTOR_IMP__

#include "CPUpdateFunctorIf.h"

class CPUpdateFunctorImp : public ICPUpdateFunctor
{
public:
	CPUpdateFunctorImp();
	CPUpdateFunctorImp(int tag,int time);
	virtual ~CPUpdateFunctorImp(){;}

	virtual bool onUpdate();

	virtual void setTag(int tag);

	virtual int	 getTag() const;

	virtual void setInterval(int time);

	virtual int	 getInterval() const;

protected:
	int m_nTag;
	int m_nInterval;
	int m_nUpdateTime;
};
#endif //__CPUPUDATEFUNCTOR_IMP__