#ifndef __EVENT_DISPATCHER_H__
#define __EVENT_DISPATCHER_H__

#include "EventListener.h"
#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"

USING_NS_CC;

class EventHandler;

class EventDispatcher : public CCObject
{
public:
	static EventDispatcher* sharedEventDispather();
public:
    ~EventDispatcher();
    bool init(void);
    EventDispatcher() 
        : m_pHandlers(NULL)
        , m_pHandlersToAdd(NULL)
        , m_pHandlersToRemove(NULL)
    {}

public:
    /** Whether or not the events are going to be dispatched. Default: true */
    bool isDispatchEvents(void);
    void setDispatchEvents(bool bDispatchEvents); 
    void removeListener(EventListener *pListener);

    /** Removes all touch delegates, releasing all the delegates */
    void removeAllListeners(void);

    /** Changes the priority of a previously added delegate. The lower the number,
    the higher the priority */
    void setPriority(int nPriority, EventListener *pListener);

	void addListener(EventListener *pListener, int nPriority=0);

    void dispatchEvent(int channel);

public:
    EventHandler* findHandler(EventListener *pListener);
protected:
    void forceRemoveListener(EventListener *pListener);
    void forceAddHandler(EventHandler *pHandler, CCArray* pArray);
    void forceRemoveAllListeners(void);
    void rearrangeHandlers(CCArray* pArray);
    EventHandler* findHandler(CCArray* pArray, EventListener *pListener);

protected:
     CCArray* m_pHandlers;

    bool m_bLocked;
    bool m_bToAdd;
    bool m_bToRemove;
     CCArray* m_pHandlersToAdd;
    CCArray *m_pHandlersToRemove;
    bool m_bToQuit;
    bool m_bDispatchEvents;

	static EventDispatcher* s_event_dispather;
};

#endif // __EVENT_DISPATCHER_H__
