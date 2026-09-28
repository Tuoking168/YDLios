#ifndef __RechargePanel_h__
#define __RechargePanel_h__

#include "scene/panel/FullScreenPanel.h"
#include "cocos2d.h"
#include "event/IEventListener.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include <map>
#include "controls/CPTips.h"
#include "ext/BasePanel.h"
#include "cocos-ext.h"
using namespace cocos2d;
USING_NS_CC_EXT;

class CPItemComponents;
class RechargePanel : public FullScreenPanel
{
public:
	RechargePanel();
	~RechargePanel();
	CREATE_FUNC(RechargePanel);
	bool init();
	void onEnter();

private:
	void initUI();
	void switchView();

	void onList(CCObject *target);

	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mSwitchList;

	int mCurrentView;
};

//////////NormalRechargePanel//////////////////////////////////////////////
class NormalRechargePanel : public CCLayer , public CCEditBoxDelegate
{
public:
	NormalRechargePanel();
	~NormalRechargePanel();
	CREATE_FUNC(NormalRechargePanel);
	bool init();
	void onEnter();

private:
	void initUI();
	void refreshGold();

	void onChangeNum(CCObject *target);
	void onRecharge(CCObject *target);
	void editBoxTextChanged(CCEditBox* editBox,  const std::string& text);
	void editBoxReturn(CCEditBox* editBox);

	CCMenuItem *getRechargeNum(int index);

private:
	CPItemComponents *mRechargeValueList;
	CCLabelTTF *mGoldLabel;
	extension::CCEditBox *goldBox;
};
#endif //__RechargePanel_h__