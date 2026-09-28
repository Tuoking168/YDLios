#ifndef __GUILD_INFO_PANEL_H__
#define __GUILD_INFO_PANEL_H__

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
class GuildInfoPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate, public IEventListener 
{
public:
	GuildInfoPanel();
	~GuildInfoPanel();
	virtual bool init(const char* filename);
	static GuildInfoPanel* create();
	virtual void handleEvent(int channel);
	void onCPEvent(const std::string &eventName);
protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	void initFrame();
	void initLabels();
	void initActivity();
	void initButtons();
	void loadGuildInfo();
	void loadPlacard(int tag);
	void loadMyInfo();
	void updateSwitchButtons(int tag);
	void changePlacardView();
	void showConvoy(bool isShow);
public:
	virtual void MenuCallBack(CCObject* pSender);
	void CloseSelf(CCObject* pSender);
protected:
	GeneralMenu* m_pMainMenu;
	CCTableViewEx * m_pTableView;
	int mHeight;
	int m_iCurrentQuestID;
	QuestInfo* m_pInfo;
	CCMenuItemSprite* m_pCurrentQuestSprite;

	CCLabelTTF* m_LabelGuildName;
	CCLabelTTF* m_LabelGuildMaster;
	CCLabelTTF* m_LabelGuildRank;
	CCLabelTTF* m_LabelGuildNum;
	CCLabelTTF* m_LabelGuildMoney;
	CCLabelTTF* m_LabelGuildJob;
	CCLabelTTF* m_LabelGuildNickname;
	CCLabelTTF* m_LabelGuildContribution;
	CCLabelTTF* m_LabelGuildPlacardCount;
	CCLabelTTF* m_LabelGuildPlacard;
	CCSprite* m_SpriteGuildWelfare;
	CCLabelTTF* m_LabelGuildWelfare;

	CCMenuItemImage* m_ConvoyGo;

	int m_PlacardSel;

	enum Child_Tag
	{
		Tag_Null=0,
		Activity_Chat,
		Activity_Event,
		Activity_Building,
		Activity_Convoy,
		Activity_Askforcombat,
		Activity_Querycombat,
		Activity_ConvoyGo,
		Button_Donate,
		Button_Leave,
		Button_GetReward,
		Placard_Private, 
		Placard_Public,
		Alert_Leave_Confirm,   
		Alert_Askforcombat,
		Alert_Change_Placard=565,
	};
};
  
class GuildDonatePanel : public BasePanel
{
public:
	GuildDonatePanel();
	~GuildDonatePanel();
	virtual bool init();
	static GuildDonatePanel* create();

protected:
	void initFrame();
	void initLabels();
	void initButtons();

	void initItems();
	void itemCallBack(CCObject* pSender);
	void keyBoardChangedCallBack(CCObject* pSender);
	int getGold(int sid,int cnt);
	void updateTotalGold();
public:
	virtual void MenuCallBack(CCObject* pSender);
	void closeSelf();
protected:
	GeneralMenu* m_pMainMenu;
	int m_selIndex;
	CCSprite *m_background;
	std::map<int,   int>   m_DonateCnt; 
	CCLabelTTF* m_GuildGold;
	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_Close,
		Button_DonateItem,
		Button_Donate50,
		Button_Donate500,

		//Item
		Item_Cnt_Button_Start = 100,
		Item_Cnt_Button_End = 105,
		Item_Cnt_Label_Start = 106,
		Item_Cnt_Label_End = 110,
	};
};
#endif//__GUILD_INFO_PANEL_H__