#ifndef _LeftTipsPanel_H_
#define _LeftTipsPanel_H_	

#include "cocos2d.h"
#include "event/IEventListener.h"

using namespace cocos2d;

class CPItemComponents;
class CPDelayRefresh;
class LeftTipsPanel : public CCLayer, public IEventListener
{
public:
	LeftTipsPanel();
	~LeftTipsPanel();
	CREATE_FUNC(LeftTipsPanel);

	bool init();
	void onEnter();

private:
	void initUI();
	void switchPanel();
	void switchPanel(int index);
	void autoSwitch();

	void onSwitch(CCObject *target);
	void onShow(CCObject *target);
	void onHide(CCObject *target);

	void show();
	void hide();

	CCMenuItemSprite *getSwitchButton(int index);
	CCMenuItemSprite *getArrowButton(bool isClose);

	void onCPEvent(const std::string &eventName);

private:
	CCNode *mContainer;
	CPItemComponents *mSwitchMenu;
	CCMenuItemSprite *mShowButton;
	CPDelayRefresh *mDelayRefresh;

	int mCurrentIndex;
	bool mIsShow;
};

#endif//_LeftTipsPanel_H_