#ifndef __FullScreenPanel_h__
#define __FullScreenPanel_h__

#include "cocos2d.h"
#include "event/IEventListener.h"

using namespace cocos2d;

class FullScreenPanel : public CCLayer, public IEventListener
{
public:
	FullScreenPanel();
	~FullScreenPanel();
	virtual bool init();
	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
protected:
	void close();
	virtual void onCPEvent(const std::string &eventName) = 0;

private:
	void initUI();
	void onClose(CCObject *target);
};

#endif //__FullScreenPanel_h__