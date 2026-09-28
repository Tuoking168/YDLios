#ifndef __ActivityStatePanel_h__
#define __ActivityStatePanel_h__

#include "cocos2d.h"
#include "event/IEventListener.h"

using namespace cocos2d;

class CPItemComponents;
class CPRichText;
class CPDelayRefresh;
class CPChecker;
class ActivityStatePanel : public CCLayer, public IEventListener
{
public:
	ActivityStatePanel();
	~ActivityStatePanel();
	CREATE_FUNC(ActivityStatePanel);
	
	bool init();
	void onEnter();
	
private:
	void initUI();
	void refreshTime();

	void onRefresh();
	void onExitActivity(CCObject *target);
	void onExitActivity(int btnType);

	void buildDesc();

	void onAutoMove();

	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mStateList;
	CPRichText *mCurrentText;
	CCLabelTTF *mTimeLabel;
	CPDelayRefresh *mStateRefresh;
	CCMenuItemImage *mExitBtn;
	CPChecker *mChecker;
};
#endif //__ActivityStatePanel_h__