//////////////////////////////////////////////////////////////////////////
// Threading.cpp
// 
// W.Y-J
// 2011.11.21
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Threading.h"
#include <assert.h>

#define ASSERT assert

namespace WOE
{

Thread::Thread()
: m_task(0),
_runningTask(false)
{
	pthread_mutex_init(&_task_thread_mutex, NULL);
}

Thread::Thread(Runnable* instance): m_task(instance)
{
	pthread_mutex_init(&_task_thread_mutex, NULL);
	if (m_task)
	{
		m_task->incReference();

		bool _start = start();
		ASSERT (_start);
	}
}

Thread::~Thread()
{
	wait();
	pthread_mutex_destroy(&_task_thread_mutex);
	if (m_task)
		m_task->decReference();
}

void* __static_task_thread(void* data)
{
	Thread::ThreadTask(data);
	return 0;
}
bool Thread::start(Runnable* instance/* =NULL */)
{
	if (instance!=NULL)
	{
		instance->incReference();
		if (m_task)
		{
			if (_runningTask)
			{
				m_task->stop();
				wait();
			}
			m_task->decReference();
		}
		m_task = instance;
	}

	_runningTask = true;
	int err = pthread_create(&_task_thread, NULL, __static_task_thread, (void*)m_task);
	if(err != 0)
	{
		return false;
	}

	m_task->incReference();


	return true;
}

void Thread::stop()
{
	if (m_task)
	{
		m_task->stop();
		m_task=NULL;

		wait();
	}
}

bool Thread::wait()
{
	if(_runningTask)
	{
		pthread_join(_task_thread, NULL);
		return true;
	}
	else
	{
		return false;
	}
}

void Thread::destroy()
{

	return;
}

unsigned long Thread::ThreadTask(void * param)
{
	Runnable* _task = (Runnable*)param;
	_task->run();

	// task execution complete, free reference added at
	_task->decReference();

	return (unsigned long)0;
}


void Thread::Sleep(unsigned long msecs)
{
#ifdef WIN32
	::Sleep (msecs);
#else
	sleep(msecs);
#endif
}


}