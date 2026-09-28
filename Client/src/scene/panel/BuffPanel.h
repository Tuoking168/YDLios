#ifndef __BuffPanel_h__
#define __BuffPanel_h__

#include "cocos2d.h"

#include "event/IEventListener.h"

using namespace cocos2d;

class BuffPanel : public CCLayer, public IEventListener
{
public:
	BuffPanel();
	~BuffPanel();
	CREATE_FUNC(BuffPanel);
	bool init();

private:
	void refresh();

	void onCPEvent(const std::string &eventName);
};

#endif //__BuffPanel_h__