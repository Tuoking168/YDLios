//////////////////////////////////////////////////////////////////////////
// LockedQueue.h
// 
// W.Y-J
// 2011.11.21
//////////////////////////////////////////////////////////////////////////

#ifndef __LOCKEDQUEUE_H__
#define __LOCKEDQUEUE_H__

// #include <WinSock2.h>
// #include <windows.h>

#include <deque>
#include "pthread.h"

namespace WOE
{

template <class T, typename StorageType=std::deque<T> >
class LockedQueue
{
public:

	//! Create a LockedQueue.
	LockedQueue()
		: _canceled(false)
	{
		pthread_mutex_init(&_lock, NULL);
	}

	//! Destroy a LockedQueue.
	virtual ~LockedQueue()
	{
		pthread_mutex_destroy(&_lock);
	}

	//! Adds an item to the queue.
	void add_back(const T& item)
	{
		lock();

		//ASSERT(!this->_canceled);
		// throw Cancellation_Exception();

		_queue.push_back(item);

		unlock();
	}

	void add_front(const T& item)
	{
		lock();

		//ASSERT(!this->_canceled);
		// throw Cancellation_Exception();

		_queue.push_front(item);

		unlock();
	}

	//! Gets the next result in the queue, if any.
	bool next(T& result)
	{
		lock();

		if (_queue.empty())
		{
			unlock();
			return false;
		}
		//ASSERT (!_queue.empty() || !this->_canceled);
		// throw Cancellation_Exception();
		result = _queue.front();
		_queue.pop_front();

		unlock();
		return true;
	}

	template<class Checker>
	bool next(T& result, Checker& check)
	{
		lock();

		if (_queue.empty())
		{
			unlock();
			return false;
		}

		result = _queue.front();
		if (!check.Process(result))
		{
			unlock();
			return false;
		}

		_queue.pop_front();

		unlock();
		return true;
	}

	//! Peeks at the top of the queue. Remember to unlock after use.
	T& peek()
	{
		lock();

		T& result = _queue.front();

		return result;
	}

	//! Cancels the queue.
	void cancel()
	{
		lock();

		_canceled = true;

		unlock();
	}

	//! Checks if the queue is cancelled.
	bool cancelled()
	{
		bool ret = false;

		lock();

		ret = _canceled;

		unlock();

		return ret;
	}

	//! Locks the queue for access.
	void lock()
	{
		pthread_mutex_lock(&_lock);
	}

	//! Unlocks the queue.
	void unlock()
	{
		pthread_mutex_unlock(&_lock);
	}

	///! Calls pop_front of the queue
	void pop_front()
	{
		lock();

		_queue.pop_front();

		unlock();
	}

	///! Checks if we're empty or not with locks held
	bool empty()
	{
		bool ret = false;

		lock();

		ret = _queue.empty();

		unlock();

		return ret;
	}

	int size()
	{
		return int(_queue.size());
	}
private:
	//! Lock access to the queue.
	pthread_mutex_t _lock;

	//! Storage backing the queue.
	StorageType _queue;

	//! Cancellation flag.
	volatile bool _canceled;
};

}
#endif // __LOCKEDQUEUE_H__