#include "EventDispatcher.h"
#include "EventHandler.h"
#include "cocoa/CCArray.h"
#include "support/data_support/ccCArray.h"
#include "ccMacros.h"
#include <algorithm>

static int less(const CCObject* p1, const CCObject* p2)
{
    return ((EventHandler*)p1)->getPriority() < ((EventHandler*)p2)->getPriority();
}

bool EventDispatcher::isDispatchEvents(void)
{
    return m_bDispatchEvents;
}

void EventDispatcher::setDispatchEvents(bool bDispatchEvents)
{
    m_bDispatchEvents = bDispatchEvents;
}

bool EventDispatcher::init(void)
{
    m_bDispatchEvents = true;
    m_pHandlers = CCArray::createWithCapacity(8);
    m_pHandlers->retain();
    m_pHandlersToAdd = CCArray::createWithCapacity(8);
    m_pHandlersToAdd->retain();
    m_pHandlersToRemove = CCArray::createWithCapacity(8);
	m_pHandlersToRemove->retain();

    m_bToRemove = false;
    m_bToAdd = false;
    m_bToQuit = false;
    m_bLocked = false;

    return true;
}

EventDispatcher::~EventDispatcher(void)
{
     CC_SAFE_RELEASE(m_pHandlers);
     CC_SAFE_RELEASE(m_pHandlersToAdd);
	 CC_SAFE_RELEASE(m_pHandlersToRemove);
}

//
// handlers management
//
void EventDispatcher::forceAddHandler(EventHandler *pHandler, CCArray *pArray)
{
//    unsigned int u = 0;

//    CCObject* pObj = NULL;
//    CCARRAY_FOREACH(pArray, pObj)
//     {
//         EventHandler *h = (EventHandler *)pObj;
//         if (h)
//         {
//             if (h->getPriority() < pHandler->getPriority())
//             {
//                 ++u;
//             }
// 
//             if (h->getListener() == pHandler->getListener())
//             {
//                 CCAssert(0, "");
//                 return;
//             }
//         }
//     }

//    pArray->insertObject(pHandler, u);
	pArray->addObject(pHandler);
}

void EventDispatcher::addListener(EventListener *pListener, int nPriority)
{    
    EventHandler *pHandler = EventHandler::handlerWithListener(pListener, nPriority);
    if (! m_bLocked)
    {
        forceAddHandler(pHandler, m_pHandlers);
    }
    else
    {
        /* If pHandler is contained in m_pHandlersToRemove, if so remove it from m_pHandlersToRemove and return.
         * Refer issue #752(cocos2d-x)
         */
//         if (ccCArrayContainsValue(m_pHandlersToRemove, pListener))
//         {
//             ccCArrayRemoveValue(m_pHandlersToRemove, pListener);
//             return;
//         }
		if(m_pHandlersToRemove->containsObject(pHandler))
		{
			m_pHandlersToRemove->removeObject(pHandler);
		}

        m_pHandlersToAdd->addObject(pHandler);
        m_bToAdd = true;
    }
}

void EventDispatcher::forceRemoveListener(EventListener *pListener)
{
    EventHandler *pHandler;

    CCObject* pObj = NULL;

    // remove handler from m_pHandlers
    CCARRAY_FOREACH(m_pHandlers, pObj)
    {
        pHandler = (EventHandler*)pObj;
        if (pHandler && pHandler->getListener() == pListener)
        {
            m_pHandlers->removeObject(pHandler);
            break;
        }
    }
}

void EventDispatcher::removeListener(EventListener *pListener)
{
    if (pListener == NULL)
    {
        return;
    }

    if (! m_bLocked)
    {
        forceRemoveListener(pListener);
    }
    else
    {
        /* If pHandler is contained in m_pHandlersToAdd, if so remove it from m_pHandlersToAdd and return.
         * Refer issue #752(cocos2d-x)
         */
        EventHandler *pHandler = findHandler(m_pHandlersToAdd, pListener);
        if (pHandler)
        {
            m_pHandlersToAdd->removeObject(pHandler);
            return;
        }

		pHandler = findHandler(pListener);
		if (pHandler)
		{
			m_pHandlersToRemove->addObject(pHandler);
		}
		
        m_bToRemove = true;
    }
}

void EventDispatcher::forceRemoveAllListeners(void)
{
     m_pHandlers->removeAllObjects();
}

void EventDispatcher::removeAllListeners(void)
{
    if (! m_bLocked)
    {
        forceRemoveAllListeners();
    }
    else
    {
        m_bToQuit = true;
    }
}

EventHandler* EventDispatcher::findHandler(EventListener *pListener)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pHandlers, pObj)
    {
        EventHandler* pHandler = (EventHandler*)pObj;
        if (pHandler->getListener() == pListener)
        {
            return pHandler;
        }
    }

    return NULL;
}

EventHandler* EventDispatcher::findHandler(CCArray* pArray, EventListener *pListener)
{
    CCAssert(pArray != NULL && pListener != NULL, "");

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pArray, pObj)
    {
        EventHandler* pHandle = (EventHandler*)pObj;
        if (pHandle->getListener() == pListener)
        {
            return pHandle;
        }
    }

    return NULL;
}

void EventDispatcher::rearrangeHandlers(CCArray *pArray)
{
    std::sort(pArray->data->arr, pArray->data->arr + pArray->data->num, less);
}

void EventDispatcher::setPriority(int nPriority, EventListener *pListener)
{
    CCAssert(pListener != NULL, "");

    EventHandler *handler = NULL;

    handler = this->findHandler(pListener);

    CCAssert(handler != NULL, "");
	
    if (handler->getPriority() != nPriority)
    {
        handler->setPriority(nPriority);
        this->rearrangeHandlers(m_pHandlers);
    }
}

//
// dispatch events
//
void EventDispatcher::dispatchEvent( int channel )
{
    m_bLocked = true;

     unsigned int uHandlersCount = m_pHandlers->count();
    //
    // process handlers
    //
    if (uHandlersCount > 0)
    {
        EventHandler *pHandler = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pHandlers, pObj)
        {
            pHandler = (EventHandler*)(pObj);

            if (! pHandler)
            {
                break;
            }
            pHandler->getListener()->handleEvent(channel);
        }
    }
    //
    // Optimization. To prevent a [handlers copy] which is expensive
    // the add/removes/quit is done after the iterations
    //
    m_bLocked = false;
    if (m_bToRemove)
    {
        m_bToRemove = false;
		EventHandler* pHandler = NULL;
		CCObject* pObj = NULL;
		CCARRAY_FOREACH(m_pHandlersToRemove, pObj)
		{
			pHandler = (EventHandler*)pObj;
			if (! pHandler)
			{
				break;
			}           
			m_pHandlers->removeObject(pHandler);
		}
       m_pHandlersToRemove->removeAllObjects();
    }

    if (m_bToAdd)
    {
        m_bToAdd = false;
        EventHandler* pHandler = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pHandlersToAdd, pObj)
         {
             pHandler = (EventHandler*)pObj;
            if (! pHandler)
            {
                break;
            }           
            forceAddHandler(pHandler, m_pHandlers);
         }
 
         m_pHandlersToAdd->removeAllObjects();    
    }

    if (m_bToQuit)
    {
        m_bToQuit = false;
        forceRemoveAllListeners();
    }
}

EventDispatcher* EventDispatcher::sharedEventDispather()
{
	if(s_event_dispather==NULL)
	{
		//here have memory leak
		static EventDispatcher _data;
		//s_event_dispather = new EventDispatcher();
		s_event_dispather=&_data;
		s_event_dispather->init();
	}
	return s_event_dispather;
}

EventDispatcher* EventDispatcher::s_event_dispather=NULL;
