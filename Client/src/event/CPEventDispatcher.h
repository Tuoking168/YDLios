#ifndef __CPEventDispatcher_h__
#define __CPEventDispatcher_h__

#include <map>
#include <list>
#include <vector>
#include "CPEvent.h"

class IEventListener;
class CPEventDispatcher
{
public:
	static CPEventDispatcher &instance();

public:
	void addEventListener(const std::string &eventName, IEventListener *listener);
	// Remove all listeners regardless event name
	void removeEventListener(IEventListener* listener);
	void removeEventListener(const std::string &eventName, IEventListener *listener);
	void dispatcherEvent(const std::string &eventName);
	bool hasEventListener(const std::string &eventName);
	std::string getCurrentEvent() const;

private:
	CPEventDispatcher();
	CPEventDispatcher(const CPEventDispatcher &);
	CPEventDispatcher &operator=(const CPEventDispatcher &);
	~CPEventDispatcher();

private:
	typedef std::list<IEventListener *> ListEventListener;
	typedef ListEventListener::iterator ItList;
	typedef std::map<std::string, ListEventListener> MapListEventListener;
	typedef MapListEventListener::iterator ItMapList;
	MapListEventListener mMapListener;
	MapListEventListener mMapTemp;

	typedef std::vector<std::string> EventNameVect;
	EventNameVect mEventNames;
};
#define CPEvtDispatcher CPEventDispatcher::instance()
#endif //__CPEventDispatcher_h__