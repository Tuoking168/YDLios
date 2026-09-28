#ifndef _MountSportsPanel_
#define _MountSportsPanel_	


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
class MountSportsInfoPanel :public BasePanel
{
public:
	MountSportsInfoPanel();
	~MountSportsInfoPanel();
	bool init();
	CREATE_FUNC(MountSportsInfoPanel);
protected:
	void initSprite();
	void MenuCallBack(CCObject* pSender);
	void initLabels();
	void initButtons();
private:
	GeneralMenu* m_pMainMenu;
	CPUpdater *	m_updater;
};

/////////MountSportsPanel///////////////////////////////////////////////
class CPDelayRefresh;
class MountSportsPanel :public FullScreenPanel
{
public:
	MountSportsPanel();
	~MountSportsPanel();
	bool init();
	CREATE_FUNC(MountSportsPanel);
	
private:
	void initFrame();
	void initSprite();
	void initLabels();
	void initRewards();
	void refreshLabel();

	void showTooltip(CCMenuItem* pImage);
	void itemCallBack(CCObject* pSender);

	void dataRequest();
	bool hasGet(int index);
	
	void onCPEvent(const std::string &eventName);

private:
	GeneralMenu* m_pMainMenu;
	CPUpdater *	m_updater;
	CCLayer *mLabelContainer;
	CPDelayRefresh *mRefresher;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_Close,

		//Cell
		Cell_Start = 100,
		Cell_End = 199,

		//Calendar
		Calendar_Start = 200,
		Calendar_End = 235,
	};
};

#endif//_MountSportsPanel_