#ifndef _GUILD_BUILDING_PANEL_H_
#define _GUILD_BUILDING_PANEL_H_	

#include "scene/panel/FullScreenPanel.h"
#include "scene/panel/MidScreenPanel.h"

class GuildBuildingPanel : public FullScreenPanel
{
public:
	GuildBuildingPanel();
	~GuildBuildingPanel();
	CREATE_FUNC(GuildBuildingPanel);
	bool init();

private:
	void initUI();

	void refresh();

	void onBuilding(CCObject *target);
	void openBuilding(int buildingID);

	void onCPEvent(const std::string &eventName);

private:
	CCLayer *mStateLayer;
	CCLayer *mContainerLayer;
};

/////////GuildBuildingGuangHuan//////////////////////////////////////////
class CPItemComponents;
class CPChecker;
class GuildBuildingGuangHuan:public FullScreenPanel
{
public:
	GuildBuildingGuangHuan();
	~GuildBuildingGuangHuan();
	CREATE_FUNC(GuildBuildingGuangHuan);
	bool init();
	void onEnter();
	void onExit();

private:
	void initUI();
	void refereshList();
	void refreshButtons();
	void refreshState();
	void refreshGuildMoney();

	void onItem(CCObject *target);	
	void onFirstPage(CCObject *target);
	void onLastPage(CCObject *target);
	void onPrePage(CCObject *target);
	void onNextPage(CCObject *target);	

 	int getFirstPage() const;
 	int getLastPage() const;
 	int getCurrentIndex() const;

	CCNode *getListItem(int index);

	void onCPEvent(const std::string &eventName);
	void onOpen( CCObject *target );	
	void onOpen(int btnType);
	
private:
	CPChecker *mChecker;
	CPItemComponents *mItemList;
	CPItemComponents *mBuildings;
	CCMenuItemImage *mUpgradeBtn;
	CCMenuItemImage *mOpenBtn;
	
	CCLabelTTF *mPageLabel;
	CCLabelTTF *mCDLabel;	 
	
	CCMenuItem *mFirstPageBtn;
	CCMenuItem *mLastPageBtn;
	CCMenuItem *mPrePageBtn;
	CCMenuItem *mNextPageBtn;
	CCLayer *mStateLayer;
	
	int mCurrentPage;
	int mCurrentIndex;
	int mSelectBuffID;
	bool mBtnState;
};

/////////GuildBuildingGongDian//////////////////////////////////////////
class CPItemComponents;
class CPChecker;
class GuildBuildingGongDian : public FullScreenPanel
{
public:
	GuildBuildingGongDian();
	~GuildBuildingGongDian();
	CREATE_FUNC(GuildBuildingGongDian);
	bool init();
	void onEnter();
	void onExit();

private:
	void initUI();
	void refreshMenu();
	void refreshList();
	void refreshGuildMoney();
	void refreshCD();

	void onList(CCObject *target);
	void onUpgrade(CCObject *target);
	void onOpen(CCObject *target);
	void onFinishBuilding(CCObject *target);
	void onFinishBuilding(int type);

	bool canUpgradeBuilding(int build_id);

	CCMenuItem *getListItem(int index);

	void onCPEvent(const std::string &eventName);

private:
	CPChecker *mChecker;
	CPItemComponents *mBuildings;
	CCMenuItemImage *mUpgradeBtn;
	CCMenuItemImage *mOpenBtn;
	CCMenuItemImage *mFinishBuildingBtn;
	CCLabelTTF *mGuildMoneyLabel;
	CCLabelTTF *mCDLabel;

	int mCurrentIndex;
};

////////////GuildBuildingTanXian/////////////////////////////////////////
class GeneralMenu;
class GuildBuildingTanXian: public MidScreenPanel
{
public:
	GuildBuildingTanXian();
	~GuildBuildingTanXian();
	CREATE_FUNC(GuildBuildingTanXian);
	bool init();

private:
	void initUI();
	void initLeft();
	void initRight();
	void refreshList();

	void onCPEvent(const std::string &eventName);
	void onLeft( CCObject *target );
	void onRight( CCObject *target );
	void onExplore( CCObject *target);
	void onItem( CCObject *target);
	void getTanXianItem(int i, int &j);		
	CCPoint getPos(int i ,int &j);

private:
	CCLayer *mStateLayer;
	CPChecker *mChecker;
	CPItemComponents *mPilgrimageList;
	CPItemComponents *mItemList;
	GeneralMenu *mTanXianMenu;

	int mUseCount;
	int mRandSid;
	std::vector<int> vec;
};

////////GuildBuildingShenShou////////////////////////////////////////////////
class GuildBuildingShenShou: public MidScreenPanel
{
public:
	GuildBuildingShenShou() ;
	~GuildBuildingShenShou();
	CREATE_FUNC(GuildBuildingShenShou);
	bool init();

private:
	void initUI();
	void initLeft();
	void initRight();
	void refreshList();

	void onCPEvent(const std::string &eventName);
	void onLeft( CCObject *target );
	void onRight( CCObject *target );
	void personalChallenge( CCObject *target );
	void guildChallenge( CCObject *target );
	void enterChallenge( CCObject *target );
	void addTarget( CCObject *target );

private:
	CCLayer *mStateLayer;
	CPChecker *mChecker;
	CPItemComponents *mPilgrimageList;
	CPItemComponents *mItemList;

};

////////GuildBuildingGuanGong////////////////////////////////////////////////
class GuildBuildingGuanGong : public MidScreenPanel
{
public:
	GuildBuildingGuanGong();
	~GuildBuildingGuanGong();
	CREATE_FUNC(GuildBuildingGuanGong);
	bool init();

private:
	void initUI();
	void initLeft();
	void initRight();
	void refreshList();
	void refreshState();

	void onItem(CCObject *target);
	void onPilgrimage(CCObject *target);
	void onVIP(CCObject *target);
	void onAdd(CCObject *target);
	void onAdd(int type);
	void onReward(CCObject *target);

	CCNode *getPilgrimageNode(int index);

	void onCPEvent(const std::string &eventName);

private:
	CCLayer *mStateLayer;
	CPChecker *mChecker;
	CPItemComponents *mPilgrimageList;
};

////////GuildBuildingFuli/////////////////////////////////////////////
class GuildBuildingFuli : public MidScreenPanel
{
public:
	GuildBuildingFuli();
	~GuildBuildingFuli();
	CREATE_FUNC(GuildBuildingFuli);
	bool init();

private:
	void initUI();

	void refreshState();
	void onItem(CCObject *target);
	void onOpen(CCObject *target);
	void onReward(CCObject *target);

	CCNode *getListItemNode(int index);	
	CPItemComponents *components;
	void onCPEvent(const std::string &eventName);

private:
	int mStatus;
};

/////////GuildBuildingShangDian////////////////////////////////////////////////
class GuildBuildingShangDian : public MidScreenPanel
{
public:
	GuildBuildingShangDian();
	~GuildBuildingShangDian();
	CREATE_FUNC(GuildBuildingShangDian);
	bool init();

private:
	void initUI();
	void refereshList();
	void refreshButtons();
	void refreshState();

	void onItem(CCObject *target);
	void onList(CCObject *target);
	void onFirstPage(CCObject *target);
	void onLastPage(CCObject *target);
	void onPrePage(CCObject *target);
	void onNextPage(CCObject *target);
	void onBuyItem(int count);

	CCMenuItem *getListItem(int index);
	int getFirstPage() const;
	int getLastPage() const;
	int getCurrentIndex() const;

	void onCPEvent(const std::string &eventName);

private:
	CCMenuItem *mFirstPageBtn;
	CCMenuItem *mLastPageBtn;
	CCMenuItem *mPrePageBtn;
	CCMenuItem *mNextPageBtn;
	CPItemComponents *mItemList;
	CCLabelTTF *mPageLabel;
	CCLayer *mStateLayer;
	CPChecker *mChecker;

	int mCurrentPage;
};
#endif//_GUILD_BUILDING_PANEL_H_