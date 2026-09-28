#ifndef _AddUpChargePanel_
#define _AddUpChargePanel_	


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
class AddUpChargePanel :public BasePanel, public IEventListener
{
public:
	AddUpChargePanel();
	~AddUpChargePanel();
	bool init();
	CREATE_FUNC(AddUpChargePanel);

	static int getGiftRewardMinIndex();
	static int getGiftRewardCurrentIndex();

private:
	void refreshInfo(int vPhase);
	void initLabels();
	void initButtons();
	void initFrame();
	void initPanLongReward();
	void refreshRewards();

	void MenuCallBack(CCObject* pSender);
	void showTooltip(CCMenuItem* pImage);
	void itemCallBack(CCObject* pSender);
	void onBoxItem(CCObject *target);

	void onCPEvent(const std::string &eventName);

private:
	GeneralMenu* m_pMainMenu;
	CPItemComponents *m_SwitchMenu;

	CPUpdater *	m_updater;

	OptionsList m_OptionsList;

	CCNode* m_InfoMainNode;
	GeneralMenu* m_InfoMainMenu;

	CCLabelTTF *mPanLongNeedGoldLabel;

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

#endif//_AddUpChargePanel_