//////////////////////////////////////////////////////////////////////////
// Threading.h
// 
// W.Y-J
// 2011.11.21
//////////////////////////////////////////////////////////////////////////

#ifndef __THREADING_H__
#define __THREADING_H__

#include "AtomicOp.h"
#include "pthread.h"
#include "Message/MsgIf.h"

//class MsgPacket;
class IMsg;
class Service;
namespace WOE
{

class Runnable
{
public:
	virtual ~Runnable() {}

	virtual void run() = 0;
	virtual void stop() = 0;

	virtual bool Send(IMsg *msg) = 0;

	void incReference() { ++m_refs; }
	void decReference()
	{
		if (!--m_refs)
			delete this;
	}
private:
	AtomicOp m_refs;
};

class Thread
{
public:
	Thread();
	Thread(Runnable *instance);
	~Thread();

	bool start(Runnable* instance=NULL);
	void stop();
	bool wait();
	void destroy();

	static void Sleep(unsigned long msecs);

	static unsigned long ThreadTask(void * param);
private:
	Thread(const Thread&);
	Thread& operator=(const Thread&);

	//static DWORD WINAPI ThreadTask(void * param);

private:
	Runnable* m_task;
	bool				_runningTask;
	pthread_t			_task_thread;
	pthread_mutex_t		_task_thread_mutex;
};
}

#endif // __THREADING_H__