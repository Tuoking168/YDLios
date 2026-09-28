#ifndef _TimeLimitGiftPanel_
#define _TimeLimitGiftPanel_	


#include <string>
#include <vector>
#include "scene/panel/FullScreenPanel.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
#include "scene/panel/OptionsHelper.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CCMenuEx;
class CPItemComponents;
class TimeLimitGiftPanel :public BasePanel
{
public:
	TimeLimitGiftPanel();
	~TimeLimitGiftPanel();
	bool init();
	CREATE_FUNC(TimeLimitGiftPanel);

	
private:
	void initLabels();
	void initButtons();
	void initSprite();
	void initRewards();

	void MenuCallBack(CCObject* pSender);
	void showTooltip(CCMenuItem* pImage);
	void itemCallBack(CCObject* pSender);

	int getRemainTime();
	void refreshLimitTimeString();

	void updateTime(float dt);

private:
	GeneralMenu* m_pMainMenu;
	CPItemComponents *m_SwitchMenu;

	CPUpdater *	m_updater;

	OptionsList m_OptionsList;

	CCLabelTTF* m_TimeLimit;
	std::string m_Prefix;
	std::string m_Day;
	std::string m_Hour;
	std::string m_Min;
	std::string m_Sec;
	float m_limitTime;


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

#endif//_TimeLimitGiftPanel_