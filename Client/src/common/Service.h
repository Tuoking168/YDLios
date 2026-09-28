#ifndef __WOE_SERVICE____
#define __WOE_SERVICE____

//
//	Service Interface
//
//
class IMsg;
class Service
{
public:
	virtual ~Service(){}

	//
	//	start the service
	//	stop the service
	//	wait for the end of service
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void wait() = 0;

	//
	//	post an message to current thread
	//
	virtual void postMsg(IMsg* pMsg) = 0;
};

#endif

