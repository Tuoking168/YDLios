#ifndef _EveryDayFirstChargePanel_
#define _EveryDayFirstChargePanel_	

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
class EveryDayFirstChargePanel :public BasePanel
{
public:
	EveryDayFirstChargePanel();
	~EveryDayFirstChargePanel();
	bool init();
	CREATE_FUNC(EveryDayFirstChargePanel);
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

		//Cell
		Cell_Start = 100,
		Cell_End = 200,
	};
};

#endif//_EveryDayFirstChargePanel_