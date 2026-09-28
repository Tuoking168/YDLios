#ifndef __TASK_PANEL_H__
#define __TASK_PANEL_H__

/*
功能：任务栏，显示当前的任务或者可接，并可响应点击任务自动寻路到目标NPC
*/

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "event/IEventListener.h"
#include "MsgQuest.h"

USING_NS_CC_EXT;


class CPItemComponents;
class CPRichText;
class TaskTipsPanel : public CCLayer, public IEventListener
{
public:
	TaskTipsPanel();
	~TaskTipsPanel();
	CREATE_FUNC(TaskTipsPanel);
	bool init();

private:
	void initUI();
	void refresh();
	void autoRefresh();
	
	void onSwitch(CCObject *target);
	void onAutoMove(CCObject *target);

	void buildDesc();

	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mSwitchMenu;
	CPItemComponents *mDescList;
	CPRichText *mCurrentText;
	CCMenuItemSprite *mCurrentTaskBoard;
	
	int mCurrentType;
};

//-----------------------------------------------------------------------------------------------------------------------------------------------//
/*
功能：任务栏，显示当前的任务或者可接，并可响应点击任务自动寻路到目标NPC
*/

class TaskContentPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	TaskContentPanel();
	~TaskContentPanel();
	virtual bool init(const char* filename);
	static TaskContentPanel* create();
	virtual void handleEvent(int channel);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	virtual void MenuCallBack(CCObject* pSender);
	void ItemCallBack(CCObject* pSender);

	void updateLeftList(int tag);//更新左边列表
	void CloseSelf(CCObject* pSender);
	void updateRightMenu();
	void initButton( int tag);

	void FirstPart();//任务内容
	void SecondPart();//任务奖励

	void initQuestList(CCMenuEx* pMenu);
	CCArray * getTypeQuest(int type );

	void QuestCallBack(CCObject* pSender);

	void initUpdateLeft();
	void quickFinishQuest(CCObject* pSender);
	void quickFinishCB(int tag);


protected:
	GeneralMenu* m_pMainMenu;
	GeneralMenu* m_pRightMenu;
	GeneralMenu* m_pLeftMenu;
	GeneralMenu* m_pRightBtnMenu;
	int m_iCurrentType;
	CCTableViewEx * m_pTableView;
	int mHeight;
	int m_iCurrentQuestID;
	CCMenuItemSprite* m_pCurrentQuestSprite;

	enum Button_TAG
	{
		TAG_CURRENTQUEST=0,
		TAG_ACCESSQUEST,
		TAG_SEARCHTASK,
		TAG_DOINGTASK,
		TAG_GIVEUPTASK,
		TAG_SpeedShoes,
		TAG_QuickFinish,
	};
};

//-----------------------------------------------------------------------------------------------------------------------------------------------//
class TaskContentSubPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	TaskContentSubPanel();
	~TaskContentSubPanel();
	virtual bool init(int qid);
	static TaskContentSubPanel* create(int qid);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	void addContent(CCLayer* pLayer, CCMenuEx* pMenu);
protected:
	CCTableViewEx * m_pTableView;
	int mHeight;
	int mQuestID;
	enum MyEnum
	{
		TAG_Shoes=1,
	};
};

#endif//__TASK_PANEL_H__