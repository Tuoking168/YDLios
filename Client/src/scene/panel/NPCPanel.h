#ifndef __NPC_PANEL_H__
#define __NPC_PANEL_H__


#include "ext/PartPanel.h"
#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "QuestDefinition.h"
#include "MsgQuest.h"
#include "ext/GeneralMenu.h"
#include "ext/CCTabelViewEx.h"
#include "controls/CPRichText.h"
#include "event/IEventListener.h"
#include "controls/CPChecker.h"
#include "controls/CPUpdater.h"
USING_NS_CC_EXT;

class NPCTalkPanel : public PartPanel, public CCTableViewDataSource, public CCTableViewDelegate, public IEventListener
{
public:
	NPCTalkPanel();
	~NPCTalkPanel();
	virtual bool init();
	static NPCTalkPanel* create();
	void onEnter();
	void onExit();

	void sendMsgToupdateInterface();
	void updateAll();
	void initBaseInterface();
	void setShowQuest(bool flag);
	void addPortalStonePanel();

	void close(CCObject* pSender);
	void onCPEvent(const std::string &eventName);
private:
	void initAll();
	void initTaskTitle();
	void addNPCSubContent(int id);
	void addNPCSubContentFinish();

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	int m_iTalkLabelHeight;
	GeneralMenu* m_pMainMenu;
	CCLayer* m_pNPCcontent;
	CCScale9Sprite* m_pbkgSprite;
	CCScale9Sprite* m_pTalkBkg;
	bool m_bisShowQuest;
	CCTableViewEx* m_pTabelView;
	CPChecker *mChecker;
	CPRichText* m_pRichText;
	CPUpdater* m_pTime;
};
//-----------------------------------------------------------------------------//


class NPCTaskTitle : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	NPCTaskTitle();
	~NPCTaskTitle();
	virtual bool init(bool flag);
	static NPCTaskTitle* create(bool flag);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	void initInterFace();//当前NPC说话内容
	void initNPCFunction();//当前NPC说话内容
	void addTaskInterFace();//当前NPC任务
	void addTaskContent(int qid);//当前NPC任务详细内容
	void MenuCallBack(CCObject * pSender);
	void addSelectButton(int qid);
	void ChangeMap(int mapid);
	void initQuestList();
	void checkQuestOnlyOne();
	void setShowQuest(bool flag);

protected:
	GeneralMenu* m_pTaskMenu;

	typedef std::vector<int> IDVector;
	IDVector mQuestList;
	int mCurrentDefaultQuest;
	bool m_bHasTask;
	int m_iQuestHeight;
	int m_TaskHeight;
	int m_FuncHeight;
	bool m_bIsShowQuest;
	enum MyEnum
	{

		TAG_ACCEPTQUEST=1,
		TAG_FINISH,
		TAG_CLOSE,

		FlagNum	= 10000,
	};
};


//--------------------------------------------------------------------------------//.

class NPCTaskPanel : public PartPanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	NPCTaskPanel();
	~NPCTaskPanel();
	virtual bool init(int qid);
	static NPCTaskPanel* create(int qid);
	void onEnter();
	void onExit();

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	void addTaskContent();
	void addTaskButton();
	void MenuCallBack(CCObject * pSender);
	void BackCallBack(CCObject *pSender);
	void CloseCallBack(CCObject *pSender);
	void Close();
	void ItemCallBack(CCObject * pSender);

protected:
	GeneralMenu* m_pMainMenu;
	int mQuestID;
	int m_iTalkLabelHeight;

	enum MyEnum
	{
		TAG_FINISH=1,
		TAG_AVAILABE,
		TAG_NOTFINISH,


		TAG_SHOES=10,
	};
};

//------------------------------------------------------------------------------------------//

class NPCFunctionPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	NPCFunctionPanel();
	~NPCFunctionPanel();
	virtual bool init( int taskcount );
	static NPCFunctionPanel* create( int taskcount );


protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	CCMenuItemSprite* getFuncButton(int n);
	void MenuCallBack(CCObject * pSender);
	void ChangeMap(int mapid);
	void ChangeMapBack();
	void ChangeCrossServer();
private: 
	CCArray* m_pFuncList;
	int m_iFuncCount;
};

///////PortalPanel//////////////////////////////////////////////////////
class CPItemComponents;
class PortalStonePanel : public CCLayer
{
public:
	PortalStonePanel();
	~PortalStonePanel();
	CREATE_FUNC(PortalStonePanel);

	bool init();

private:
	void initUI();

	void onTeleport(CCObject *target);

private:
	CPItemComponents *mPortals;
};

#endif//__NPC_PANEL_H__