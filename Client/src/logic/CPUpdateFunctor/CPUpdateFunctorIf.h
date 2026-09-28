#ifndef __CPUPUDATEFUNCTOR_IF__
#define __CPUPUDATEFUNCTOR_IF__


class ICPUpdateFunctor
{
public:
	virtual ~ICPUpdateFunctor(){;}

	virtual bool onUpdate()		 = 0;

	virtual void setTag(int tag) = 0;

	virtual int	 getTag() const = 0;

	virtual void setInterval(int time) = 0;

	virtual int	 getInterval() const = 0;

};
#endif //__CPUPUDATEFUNCTOR_IF__