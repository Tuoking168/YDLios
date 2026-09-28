#ifndef __ConvoyBeautyPanel_h__
#define __ConvoyBeautyPanel_h__

#include "FullScreenPanel.h"
#include "utils/MacroUtils.h"

class CPCheckBox;
class CPChecker;
class CPComboBox;
class ConvoyBeautyPanel : public FullScreenPanel
{
public:
	ConvoyBeautyPanel();
	~ConvoyBeautyPanel();
	CREATE_FUNC(ConvoyBeautyPanel);
	bool init();

private:
	void initUI();
	void refresh();

	void onRefresh(CCObject *target);
	void onRefresh(int btnType);
	void onStart(CCObject *target);

	void dataRequest();
	void refreshRequest();

	void onCPEvent(const std::string &eventName);

private:
	CCLayer *mStateLayer;
	CPCheckBox *mCheckBox;
	CPChecker *mChecker;
	CPComboBox *mComboBox;
	CCNode *mSelFlag;
	CCNode *mLastBeauty;
};

/////////ConvoyBeautyHelper//////////////////////////////////////////////
class ConvoyBeautyHelper
{
public:
	static std::string getPlayCntString();
	static std::string getRefreshCntString();
	static std::string getPlayTargetName();
	static std::string getRewardString();
	static int getRefreshRemainCnt();

	static CCPoint getPosition();

private:
	CP_MAKE_STATIC_CLASS(ConvoyBeautyHelper);
};

#endif //__ConvoyBeautyPanel_h__