#ifndef _EveryDayActivePanel_
#define _EveryDayActivePanel_	

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
class GameData;
class CPItemComponents;
class EveryDayActivePanel :public FullScreenPanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	EveryDayActivePanel();
	~EveryDayActivePanel();
	bool init();
	CREATE_FUNC(EveryDayActivePanel);
	virtual void onCPEvent(const std::string &eventName);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	
protected:
	void initFrame();
	void MenuCallBack(CCObject* pSender);

	void initLabels();
	void initButtons();
	void initCell(CCTableViewCell *cell);
	void loadCell(CCTableViewCell *cell);

	void selectButtonWithIndex(int idx);
	void loadRewards(int idx);
	void showTooltip(CCMenuItem* pImage);

	void getReward(CCObject* pSender);
	void itemClickCallBack(CCObject* pSender);
	void onEnter();

	void initHappinessBar();
	void loadHappiness();
	void refreshHappinessBar();
private:
	void updateLeft();
	int getSignDays();

	CCLayer* m_LeftLayer;
	GeneralMenu* m_pMainMenu;
	CPUpdater *	m_updater;
	GeneralMenu* m_RewardMgr;
	CCTableViewEx*		m_pTableView;

	int m_indexSelected;
	int m_Height;

	CCScale9Sprite* m_pHappiness;


	CCLabelTTF* m_hasSinged;
	CCLabelTTF* m_hasHappness;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_Get,//

		//Cell
		Cell_Start = 100,
		Cell_End = 199,

		//Calendar
		Calendar_Start = 200,
		Calendar_End = 235,

		//Button_Sign
		Button_Sign_Start = 250,
		Button_Sign_End = 260,
	};
};

//------------------------------------------left part----------------------------------------------------------------------------
class EveryDayActivePanelLeftPart :public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate,public IEventListener
{
public:
	EveryDayActivePanelLeftPart();
	~EveryDayActivePanelLeftPart();
	bool init();
	CREATE_FUNC(EveryDayActivePanelLeftPart);
protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	void onEnter();
	virtual void onCPEvent(const std::string &eventName);
	void updateView();

	GeneralMenu* m_pTopMenu;
	CCTableViewEx *m_pTabelView;
	CCLayer* m_pLeftLayer;

	int m_Height;
};

//--------------------------------------------------------------------------------------------------------------------------

class LeftPartBaseMenu:public CCLayer,public IEventListener
{
public:
	LeftPartBaseMenu();
	~LeftPartBaseMenu();
	CREATE_FUNC(LeftPartBaseMenu);
	bool init();
	void initFirstPart();
	void initSecondPart();
	virtual void onCPEvent(const std::string &eventName);

protected:

private:

	void gotoNPC(CCObject* pSender);
	void useShoes(CCObject* pSender);
	void miaoDoActivite(CCObject* pSender);

	int m_iFirstHeight;
	int m_iSecondHeight;

	int everydayActive_id_begin;
	int everydayActive_id_end;

};


#endif//_EveryDayActivePanel_