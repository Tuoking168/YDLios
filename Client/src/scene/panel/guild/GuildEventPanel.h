#ifndef __GUILD_EVENT_PANEL_H__
#define __GUILD_EVENT_PANEL_H__

/*
功能：行会
*/

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "MsgQuest.h"
#include "event/IEventListener.h"

USING_NS_CC_EXT;

//-----------------------------------------------------------------------------------------------------------------------------------------------//
/*
功能：任务栏，显示当前的任务或者可接，并可响应点击任务自动寻路到目标NPC
*/

class GuildEventPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate, public IEventListener
{
public:
	GuildEventPanel();
	~GuildEventPanel();
	virtual bool init(const char* filename);
	void hide();
	static GuildEventPanel* create();
	virtual void handleEvent(int channel);
	void onCPEvent(const std::string &eventName);
protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);


	void initFrame();
	void initLabels();
	void initButtons();
public:
	virtual void MenuCallBack(CCObject* pSender);

	void CloseSelf(CCObject* pSender);

protected:
	GeneralMenu* m_pMainMenu;
	int m_iCurrentType;
	CCTableViewEx * m_pTableView;
	int mHeight;
	int m_iCurrentQuestID;
	QuestInfo* m_pInfo;
	CCMenuItemSprite* m_pCurrentQuestSprite;

	CCLabelTTF* m_LabelPage;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_Close,
	};
};

#endif//__GUILD_EVENT_PANEL_H__