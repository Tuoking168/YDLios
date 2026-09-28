#ifndef _InvestPlanPanel_
#define _InvestPlanPanel_	


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
class SlideTable;
class InvestPlanPanel : public BasePanel, public IEventListener
{
public:
	InvestPlanPanel();
	~InvestPlanPanel();
	bool init();
	CREATE_FUNC(InvestPlanPanel);

private:
	void initLabels();
	void initButtons();
	void initSprite();
	void refreshTimeLabel();
	
	void onOpen(CCObject *target);
	void onGet(CCObject *target);
	void showTooltip(CCMenuItem* pImage);
	void itemCallBack(CCObject* pSender);

	void initItemPages();
	void addListItem(int i );
	void pageChangeCallBack(CCObject* pSender);
	int getRemainTime();

	void onCPEvent(const std::string &eventName);

private:
	GeneralMenu* m_pMainMenu;
	CPItemComponents *m_SwitchMenu;

	SlideTable*		m_pSlideItems;
	CPUpdater *	m_updater;
	CCLabelTTF* m_PageInfo;
	CCLabelTTF *mTimeLabel;

	OptionsList m_OptionsList;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_Close,

		//Cell
		Cell_Start = 100,
		Cell_End = 200,
	};
};

#endif//_InvestPlanPanel_