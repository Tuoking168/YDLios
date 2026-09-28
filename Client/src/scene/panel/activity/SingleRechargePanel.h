#ifndef __SingleRechargePanel_h__
#define __SingleRechargePanel_h__

#include "cocos2d.h"
#include "event/IEventListener.h"

using namespace cocos2d;

class CPChecker;
class CPItemComponents;
class SingleRechargePanel : public CCLayer, public IEventListener
{
public:
	SingleRechargePanel();
	~SingleRechargePanel();
	CREATE_FUNC(SingleRechargePanel);
	bool init();

private:
	void initUI();
	void refreshDesc();
	void refreshBtnState();	

	void onItem(CCObject *target);
	void onGetReward(CCObject *target);

	CCMenuItem *getRewardItem(int index);

	void onCPEvent(const std::string &eventName);

private:
	CPChecker *mChecker;
	CPItemComponents *mRewards;
	CCLayer *mRefreshLayer;
	CCMenuItemImage *mGetBtn;

	int mCurrentIndex;
};

#endif //SingleRechargePanel