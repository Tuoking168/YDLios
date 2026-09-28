#ifndef _ConsumeDrawPanel_
#define _ConsumeDrawPanel_	

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
class ConsumeDrawPanel :public BasePanel
{
public:
	ConsumeDrawPanel();
	~ConsumeDrawPanel();
	bool init();
	CREATE_FUNC(ConsumeDrawPanel);
	virtual void onCPEvent(const std::string &eventName);
public:

protected:
	void initLabels();
	void initButtons();
	void initFrame();
	void initSprite();
	void MenuCallBack(CCObject* pSender);

	void switchView(bool isMainView);

	void initSubLabels();
	void initSubButtons();
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
		Button_Detail,
		Button_Main,

		//Cell
		Cell_Start = 100,
		Cell_End = 200,
	};
};

#endif//_ConsumeDrawPanel_