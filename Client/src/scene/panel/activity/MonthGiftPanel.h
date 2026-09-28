#ifndef _MonthGiftPanel_
#define _MonthGiftPanel_	

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
USING_NS_CC;
USING_NS_CC_EXT;

class CCMenuEx;
class CPItemComponents;
class MonthGiftPanel :public BasePanel
{
public:
	MonthGiftPanel();
	~MonthGiftPanel();
	bool init();
	CREATE_FUNC(MonthGiftPanel);
	virtual void onCPEvent(const std::string &eventName);
public:

protected:
	void initLabels();
	void initButtons();
	void initFrame();
	void initSprite();
	void MenuCallBack(CCObject* pSender);
	void initRewards();
	void showTooltip(CCMenuItem* pImage);
	void itemCallBack(CCObject* pSender);
private:
	GeneralMenu* m_pMainMenu;
	//CCTableViewEx * m_pTableView;
	CPItemComponents *m_SwitchMenu;

	CPUpdater *	m_updater;

	OptionsList m_OptionsList;


	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_GoCharge,
		Button_GetReward,
	};
};

#endif//_MonthGiftPanel_