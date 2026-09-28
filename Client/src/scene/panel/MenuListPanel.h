#ifndef _MENU_LIST_PANEL_H_
#define _MENU_LIST_PANEL_H_	

#include <string>
#include <vector>
#include "FullScreenPanel.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
#include "OptionsHelper.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CCMenuEx;
class GeneralMenu;
class CPItemComponents;
class MenuListPanel : public FullScreenPanel
{
public:
	MenuListPanel();
	~MenuListPanel();
	bool init();
	CREATE_FUNC(MenuListPanel);
	virtual void onCPEvent(const std::string &eventName);
	virtual const std::string dataTableName();
	virtual void onSwitch(int tag);
	void onEnter();
	void addPanel(CCNode* child);
	void reloadSwitchMenu(bool selectDefault=true);

protected:
	void initFrame();
	void initSwitchView();
	void MenuCallBack(CCObject* pSender);
	void addListItem(int i );
	void addListFinish();
	int defaultSwitch();

	void initCell(CCTableViewCell *cell);
private:
	GeneralMenu* m_pMainMenu;
	CPItemComponents *m_SwitchMenu;

	CPUpdater *	m_updater;

	OptionsList m_OptionsList;
	CCNode *m_pRightMgr;

	CCMenuItem* m_DefaultSelected;

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

#endif//_MENU_LIST_PANEL_H_