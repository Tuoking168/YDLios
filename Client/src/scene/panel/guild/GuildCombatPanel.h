#ifndef __GUILD_COMBAT_PANEL_H__
#define __GUILD_COMBAT_PANEL_H__

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
class CPComboBox;
class CPItemComponents;
struct GuildMemberInfo;

//-----------------------------------------------------------------------------------------------------------------------------------------------//
/*
功能：任务栏，显示当前的任务或者可接，并可响应点击任务自动寻路到目标NPC
*/

class GuildCombatPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate, public IEventListener
{
public:
	GuildCombatPanel();
	~GuildCombatPanel();
	virtual bool init(const char* filename);
	static GuildCombatPanel* create();
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
	//void initSprites();
	void initMasterInfo();
	void setReward(bool isReward);
	void comboCallBack(CCNode* pSender);

	void loadRuleView();
	void loadQueryView();
	void initRewards();
	void showTooltip(CCMenuItem* pImage);
	void itemCallBack(CCObject* pSender);
	void refreshMasterInfo();

	virtual void MenuCallBack(CCObject* pSender);
	void applyGCZ( CCObject* pSender );
	bool isSandCityMaster();
	bool canGetSandCityReward();
protected:
	GeneralMenu* m_pMainMenu;

	int m_iCurrentType;
	CCTableViewEx * m_pTableView;
	int mHeight;
	
	std::vector<CCLabelTTF*> m_MasterReward;
	std::vector<CPComboBox*> m_MasterList;
	CCLabelTTF* m_RewardGuild;
	CCLabelTTF* m_MasterGuild;
	CCLabelTTF* m_CombatTime;
	CCLabelTTF* m_DefGuild;
	CCLabelTTF* m_AtkGuild;
	CCLabelTTF* m_RewardItem;
	CCMenuItem* m_EditJob;
	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_Preview,
		Button_Rule,
		Button_Reward,
		Button_Query,
		Button_Edit_Job,
		Button_Occupy_Reward,
		//alert
		Alert_Askforcombat,
		//Label

		//combo
		Combo_Start = 100,
		Combo_End = 104,
		//master info
		Job_Start = 200,
		Job_ChengZhu = 201,
		Job_FuChengZhu = 202,
		Job_DaJiangJun = 203,
		Job_DaZhengLing = 204,
		Job_DaZongGuan = 205,
		Job_end = 210,
	};
};

class GuildClothesPreviewPanel : public BasePanel
{
public:
	GuildClothesPreviewPanel();
	~GuildClothesPreviewPanel();
	virtual bool init(int tag);
	static GuildClothesPreviewPanel* create(int tag);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
protected:
	void initFrame();
	void initLabels();
	void initButtons();
public:
	virtual void MenuCallBack(CCObject* pSender);
	void closeSelf();
protected:
	GeneralMenu* m_pMainMenu;
	int m_selIndex;
	CCScale9Sprite *m_background;
};

class GuildJobSettingPanel : public BasePanel, public IEventListener
{
public:
	GuildJobSettingPanel();
	~GuildJobSettingPanel();
	virtual bool init(int tag);
	static GuildJobSettingPanel* create(int tag);

	virtual void onCPEvent(const std::string &eventName);
protected:
	void initFrame();
	void initLabels();
	void initButtons();
	void onSelectjob(CCObject *target);
	CCMenuItem * getJobView( int index );
	void onSelectMember(CCObject *target);
	void refreshMemberList();
	void refreshMemberPanel();

	void keepOnly(int index);
public:
	virtual void MenuCallBack(CCObject* pSender);
	void closeSelf();
protected:
	GeneralMenu* m_pMainMenu;
	int m_selIndex;
	CCSprite *m_background;
	CPItemComponents *m_SwitchMenu;
	CPItemComponents *m_SwitchJob;
	std::vector<CCLabelTTF*> m_JobList;
	
	std::vector<GuildMemberInfo> m_MemberList;
	std::vector<int> m_JobsPid;

	enum Tag
	{
		// Button
		Button_Confirm,
		Button_Close,
	};
};
#endif//__GUILD_COMBAT_PANEL_H__