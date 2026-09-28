#ifndef __CPUPUDATEFUNCTOR_MANAGER__
#define __CPUPUDATEFUNCTOR_MANAGER__

#include "CPUpdateFunctorIf.h"
#include <map>

class CPUpdateFunctorManager 
{
public:
	
	CPUpdateFunctorManager();
	virtual ~CPUpdateFunctorManager();
	static CPUpdateFunctorManager *	instance();
	
	void onClear();

	void onUpdate(float dt);

	bool addFunctor(int tagid);

	bool rmvFunctor(int tagid);

	bool hasFunctor(int tagid);

	ICPUpdateFunctor *getFunctor(int tagid);

private:
	void initIfNeeded();

private:
	typedef std::map<int, ICPUpdateFunctor*> CPUpdateFunctorMap;
	CPUpdateFunctorMap	m_Functors;
	float update_time;
	bool mHasInited;
};
#endif //__CPUPUDATEFUNCTOR_MANAGER__