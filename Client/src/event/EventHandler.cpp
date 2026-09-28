#include "EventHandler.h"
#include "ccMacros.h"

EventListener* EventHandler::getListener(void)
{
    return m_pListener;
}

void EventHandler::setListener(EventListener *pListener)
{
    if (pListener)
    {
        dynamic_cast<CCObject*>(pListener)->retain();
    }

    if (m_pListener)
    {
        dynamic_cast<CCObject*>(m_pListener)->release();
    }

    m_pListener = pListener;
}

int EventHandler::getPriority(void)
{
    return m_nPriority;
}

void EventHandler::setPriority(int nPriority)
{
    m_nPriority = nPriority;
}

EventHandler* EventHandler::handlerWithListener(EventListener *pListener, int nPriority)
{
    EventHandler *pHandler = new EventHandler();

    if (pHandler)
    {
        if (pHandler->initWithListener(pListener, nPriority))
        {
            pHandler->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pHandler);
        }
    }
    
    return pHandler;
}

bool EventHandler::initWithListener(EventListener *pListener, int nPriority)
{
    CCAssert(pListener != NULL, "touch delegate should not be null");

    m_pListener = pListener; 

    dynamic_cast<CCObject*>(pListener)->retain();

    m_nPriority = nPriority;

    return true;
}

EventHandler::~EventHandler(void)
{
    if (m_pListener)
    {
        dynamic_cast<CCObject*>(m_pListener)->release();
    }   
}
