#ifndef __IEventListener_h__
#define __IEventListener_h__

#include <string>

class IEventListener
{
public:
	virtual void onCPEvent(const std::string &eventName) = 0;
};
#endif //__IEventListener_h__