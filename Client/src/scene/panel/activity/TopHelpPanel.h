#ifndef _TopHelpPanel_H_
#define _TopHelpPanel_H_	

/*
功能：显示商城信息界面
*/
#include <string>
#include <vector>
#include "ext/Basepanel.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
#include "scene/panel/MenuListPanel.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CCMenuEx;
class SlideTable;

class TopHelpPanel :public FullScreenPanel, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
	TopHelpPanel();
	~TopHelpPanel();
	CREATE_FUNC(TopHelpPanel);
	//static TopHelpPanel* create();
	virtual void onSwitch(int tag);
	bool init();
	void onEnter();
	void hide();
	virtual void onCPEvent(const std::string &eventName);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	
protected:
	void initLeftMenu();
	void initRightMenu();
	void menucallback(CCObject* pSender);
	void ShoesClick(CCObject* pSender);
	void BtnClick(CCObject* pSender);
	void OpenPanelClick(CCObject* pSender);
private:
	enum MyEnum
	{
		i_want_Upgrade	=1,
		i_want_Stronger	,
		i_want_equip	,
		i_want_money	,
		i_so_boring	,
	};
	int m_iCurListType;
	CCTableViewEx* m_pTableView;
	CCMenuItemImage* m_pSelectItem;
	int m_iCurListSubCount;

	struct HelpList
	{
		int id;
		int starnum;
		std::string name;
		std::string openpanelstr;
		int tgtid;
	};
	std::map<int ,HelpList> m_mHelpList;
};

#endif//_TopHelpPanel_H_