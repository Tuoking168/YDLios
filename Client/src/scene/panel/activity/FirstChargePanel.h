#ifndef _FirstChargePanel_
#define _FirstChargePanel_	

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
class FirstChargePanel :public BasePanel
{
public:
	FirstChargePanel();
	~FirstChargePanel();
	bool init();
	CREATE_FUNC(FirstChargePanel);
	virtual void onCPEvent(const std::string &eventName);
public:

protected:
	void initLabels();
	void initButtons();
	void initFrame();
	void initSprite();
	void initRewards();
	void MenuCallBack(CCObject* pSender);
	void itemCallBack(CCObject* pSender);
	void showTooltip(CCMenuItem* pImage);
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

		//item
		Item_Start = 1000,
	};
};

#endif//_FirstChargePanel_