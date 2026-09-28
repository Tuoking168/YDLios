#ifndef __Honor_PANEL_H__
#define __Honor_PANEL_H__

/*
功能：任务栏，显示当前的任务或者可接，并可响应点击任务自动寻路到目标NPC
*/

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "event/IEventListener.h"
#include "ext/GeneralMenu.h"

USING_NS_CC_EXT;



class HonorPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate, public IEventListener
{
public:
	HonorPanel();
	~HonorPanel();
	virtual bool init(const char* filename);
	static HonorPanel* create();
	virtual void handleEvent(int channel);

	void onCPEvent(const std::string &eventName);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	void getSubLeftPanel(int curHonorlvl);
	void getSubRightPanel(int curHonorlvl);
	void buttonCallBack(CCObject* pSender);
	void menuCallBack(CCObject* pSender);

	void initButton();

	void postopenhonor();
	void postopenhonorbygold();
	void postupgradehonor();
	void postupgradehonorbygold();
	void updatetime(int index);
	void finishtime();
	void Update();

	int m_iCurHonorlvl;
	GeneralMenu* m_pLeftMenu;
	GeneralMenu* m_pRightMenu;
	CCLabelTTF* m_pHonorLabel;
	CCLabelTTF* m_pGoldLabel;
	CCTableViewEx* m_pTabelView;
	CCMenuItemSprite* m_pCurItemSprite;

	GeneralMenu* m_pMainMenu;

	CCLabelTTF* m_pCurHonorTime;
	int m_iTime;
	bool m_bLeftOver;
	bool m_bRightOver;
	int m_iCurSelectRange;
	bool m_bUpgrade;
	int m_iTimeSpan;

	enum MyEnum
	{
		Honor_Left1,
		Honor_Left2,
		Honor_Right1,
		Honor_Right2,
	};
};


#endif//__Honor_PANEL_H__