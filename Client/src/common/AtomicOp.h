//////////////////////////////////////////////////////////////////////////
// AtomicOp.h
// 
// W.Y-J
// 2011.11.21
//////////////////////////////////////////////////////////////////////////


#ifndef __ATOMICOP_H__
#define __ATOMICOP_H__

#ifdef WIN32
#include <atlsimpstr.h>
#else
#include <ext/atomicity.h>
inline long _InterlockedIncrement( volatile long *val )
{
	__gnu_cxx::__exchange_and_add((volatile int *)val,1);
	return *val;
}
inline long _InterlockedDecrement( volatile long *val )
{
	__gnu_cxx::__exchange_and_add((volatile int *)val,-1);
	return *val;
}
#endif

namespace WOE
{

class AtomicOp
{
public:
	AtomicOp();
	~AtomicOp();

	inline long operator++ (void)
	{
		return _InterlockedIncrement (const_cast<long *> (&this->value_));
	}

	inline long operator++ (int)
	{
		return ++*this - 1;
	}

	inline long operator-- (void)
	{
		return _InterlockedDecrement (const_cast<long *> (&this->value_));
	}

	long operator-- (int)
	{
		return --*this + 1;
	}
private:
	volatile long value_;
};

} // WOE

#endif // __ATOMICOP_H__