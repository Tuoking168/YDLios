#ifndef _OnlineGiftPanel_
#define _OnlineGiftPanel_	

/*
功能：显示商城信息界面
*/
#include <string>
#include <vector>
#include "scene/panel/FullScreenPanel.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
#include "scene/panel/OptionsHelper.h"
#include "event/IEventListener.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCMenuEx;
class CPItemComponents;
class OnlineGiftPanel :public BasePanel, public IEventListener
{
public:
	OnlineGiftPanel();
	~OnlineGiftPanel();
	bool init();
	CREATE_FUNC(OnlineGiftPanel);

private:
	void initLabels();
	void initButtons();
	void initSprite();
	void MenuCallBack(CCObject* pSender);
	void initRewards();
	void refreshReward();

	void showTooltip(CCMenuItem* pImage);
	void itemCallBack(CCObject* pSender);

	void setTotalTime(int pSec);
	void setTimeString(int pSec);
	void updateTime(float dt);

	void onCPEvent(const std::string &eventName);

private:
	GeneralMenu* m_pMainMenu;
	CPItemComponents *m_SwitchMenu;
	GeneralMenu *mRewardContainer;

	CPUpdater *	m_updater;

	OptionsList m_OptionsList;

	CCLabelTTF* m_TimeLabel;
	float m_Time;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_GetReward,

		//Cell
		Cell_Start = 100,
		Cell_End = 200,
	};
};

#endif//_OnlineGiftPanel_