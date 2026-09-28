#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "EventListener.h"
#include "cocoa/CCObject.h"

USING_NS_CC;

class EventHandler : public CCObject
{
public:
    virtual ~EventHandler(void);

    /** delegate */
    EventListener* getListener();
    void setListener(EventListener *pListener);

    /** priority */
    int getPriority(void);
    void setPriority(int nPriority);

    /** initializes a TouchHandler with a delegate and a priority */
    virtual bool initWithListener(EventListener *pListener, int nPriority);

public:
    /** allocates a TouchHandler with a delegate and a priority */
    static EventHandler* handlerWithListener(EventListener *pListener, int nPriority);

protected:
    EventListener *m_pListener;
    int m_nPriority;
};

#endif // __EVENT_HANDLER_H__
