#ifndef __GUILD_BROWSE_PANEL_H__
#define __GUILD_BROWSE_PANEL_H__

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

class GuildBrowsePanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate, public IEventListener
{
public:
	GuildBrowsePanel();
	~GuildBrowsePanel();
	virtual bool init(const char* filename);
	static GuildBrowsePanel* create();
	virtual void handleEvent(int channel);
	void onCPEvent(const std::string &eventName);

private:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	void initFrame();
	void initLabels();
	void initButtons();
	void initCell(CCTableViewCell *cell);
	void loadCell(CCTableViewCell *cell,unsigned int idx);

	void loadGuildsRequest(int vPage);
	void loadGuildsPageUp();
	void loadGuildsPageDown();
	void loadGuildsHomePage();
	void loadGuildsEndPage();
	void createGuild();
	void loadGuildDetailView();

	void showTooltip(CCMenuItem* pImage);
	void itemCallBack(CCObject* pSender);

public:
	virtual void MenuCallBack(CCObject* pSender);
	void CloseSelf(CCObject* pSender);

private:
	GeneralMenu* m_pMainMenu;
	GeneralMenu* m_pRightMenu;
	GeneralMenu* m_pLeftMenu;
	int m_iCurrentType;
	CCTableViewEx * m_pTableView;
	int mHeight;
	int m_iCurrentQuestID;
	QuestInfo* m_pInfo;
	CCMenuItemSprite* m_pCurrentQuestSprite;

	CCLabelTTF* m_LabelInfo;
	CCLabelTTF* m_LabelPage;
	int m_selIndex;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Tag_Detail,
		Tag_Alliance,
		Tag_Combat,
		Tag_Filter,
		Tag_Apply,
		Tag_Add,
		Tag_Cancel_Apply,
		Tag_Page_Home,
		Tag_Page_End,
		Tag_Page_Up,
		Tag_Page_Down,
		//label
		Tag_Rank,
		Tag_Name,
		Tag_Master,
		Tag_Num,
		Tag_Level,
		Tag_Status,
		//Alert
		Alert_Create_Guild=5585,
	};
};

////////GuildDetailPanel/////////////////////////////////////////
class CPChecker;
class GuildDetailPanel : public BasePanel, public IEventListener
{
public:
	GuildDetailPanel();
	~GuildDetailPanel();
	virtual bool init(int tag);
	static GuildDetailPanel* create(int tag);
	virtual void MenuCallBack(CCObject* pSender);
	void closeSelf();

private:
	void initUI();
	void initFrame();
	void initLabels();
	void initButtons();
	void dataRequest();

	void onCPEvent(const std::string &eventName);

protected:
	GeneralMenu* m_pMainMenu;
	int m_selIndex;
	CCSprite *m_background;
	CPChecker *mChecker;

	CCLabelTTF* m_GuildName;
	CCLabelTTF* m_GuildCount;
	CCLabelTTF* m_GuildMaster;
	CCLabelTTF* m_GuildStatus;
	CCLabelTTF* m_GuildPlacard;
	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_Close,
		Button_Combat,
		Button_Friend,
		Button_Apply,
	};
};
#endif//__GUILD_BROWSE_PANEL_H__