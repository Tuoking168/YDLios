#ifndef __ArenaPanel_h__
#define __ArenaPanel_h__

#include "FullScreenPanel.h"
#include "controls/CPTips.h"
#include "utils/MacroUtils.h"


class CPChecker;
class CPItemComponents;
class ArenaPanel : public FullScreenPanel
{
public:
	ArenaPanel();
	~ArenaPanel();
	CREATE_FUNC(ArenaPanel);

	bool init();
	void onEnter();
	void onExit();

	void setState(int state);

private:
	void initUI();
	void refreshState();
	void refreshTime();
	void refreshList();
	void showRecord();

	void onRank(CCObject *target);
	void onRecord(CCObject *target);
	void onAddCount(CCObject *target);
	void onAddCount(int btnType);
	void onCleanCD(CCObject *target);
	void onCleanCD(int btnType);
	void onRefreshBuff(CCObject *target);
	void onGoldRefresh(int btnType);
	void onSuperRefresh(int btnType);
	void onChallenge(CCObject *target);
	void onRankReward(CCObject *target);

	void dataRequest();
	CCMenuItem *getListItem(int rank);
	CCNode *getListNormNode(int rank);
	CCNode *getListSelNode(int rank);

	void onCPEvent(const std::string &eventName);

private:
	CPChecker *mChecker;
	CCLayer *mStateLayer;
	CCLabelTTF *mRewardTimeLabel;
	CCLabelTTF *mCDLabel;
	CPItemComponents *mCompetitorList;

	int mState;
};

/////////ArenaRewardPanel/////////////////////////////////////////////
class ArenaRewardPanel : public CPTipsSub, public IEventListener
{
public:
	ArenaRewardPanel();
	~ArenaRewardPanel();

	static ArenaRewardPanel *create(int rank);

private:
	bool initWithData(int rank);
	void initUI();
	void refresh();

	void onClose(CCObject *target);

	void dataRequest();

	void onCPEvent(const std::string &eventName);

private:
	CPChecker *mChecker;
	CCLayer *mDataLayer;

	int mRank;
};

////////ArenaRankPanel////////////////////////////////////////////////
class ArenaRankPanel : public CPTipsSub, public IEventListener
{
public:
	ArenaRankPanel();
	~ArenaRankPanel();
	CREATE_FUNC(ArenaRankPanel);
	bool init();

private:
	void initUI();
	void refreshList();
	void refreshMenu();

	void onPlayer(CCObject *target);
	void onPrePage(CCObject *target);
	void onNextPage(CCObject *target);
	void onClose(CCObject *target);

	CCMenuItem *getItem(int rank);
	void testPage();

	void onCPEvent(const std::string &eventName);

private:
	CPChecker *mChecker;
	CPItemComponents *mRankList;
	CCMenuItemImage *mPreBtn;
	CCMenuItemImage *mNextBtn;
	CCLabelTTF *mPageLabel;

	int mCurrentPage;
	int mMaxPage;
};

/////////ArenaRecordPanel///////////////////////////////////////////////////
class ArenaRecordPanel : public CPTipsSub
{
public:
	ArenaRecordPanel();
	~ArenaRecordPanel();
	CREATE_FUNC(ArenaRecordPanel);
	bool init();

private:
	void initUI();

	void onPlayer(CCObject *target);
	void onClose(CCObject *target);

private:
	CPItemComponents *mRecordList;
};

///////ArenaFightPanel/////////////////////////////////////////////////
class AnimElement;
class HeadPanel;
class ArenaFightPanel : public CCLayer, public IEventListener
{
public:
	ArenaFightPanel();
	~ArenaFightPanel();
	
	static ArenaFightPanel *create();
	static ArenaFightPanel *createWithData(ArenaPanel *arenaPanel, int targetRank);

	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	bool initWithData(ArenaPanel *arenaPanel, int targetRank);
	void initUI();
	void initAnimAndHead();
	void fightRequest();
	void showDamage(float dt);
	void showDamage(int id, int damage);

	void playBegin();
	void playMove();
	void playFight();
	void playEnd();

	void onClose(CCObject *target);

	void onCPEvent(const std::string &eventName);

private:
	CPChecker *mChecker;
	ArenaPanel *mArenaPanel;
	AnimElement *mMyRole;
	AnimElement *mOtherRole;
	HeadPanel *mMyHead;
	HeadPanel *mOtherHead;

	int mTargetRank;
	int mTargetPID;
	int mCurrentAction;
	int mMaxAction;
};

/////////ArenaHelper//////////////////////////////////////////////////
class ArenaHelper
{
public:
	static std::string getReward();
	static bool getRankReward(int level, int rank, int &exp, int &honor);
	static std::string getPlayCnt();
	static std::string getFightAdd();
	static std::string getRecord(int index);
	static int getMyMaxHP();
	static int getOtherMaxHP();

	static void dataRequest();
	static void challengeRequest(int rank);
	static void challengeRequest(int rank, int pid);
	static void cleanCoolDownRequest();
	static void addCountRequest();
	static void refreshBuffRequest(int refreshType);
	static void recordRequest();
	static void rankRequest(int page);
	static void heighThreeRequest();

private:
	CP_MAKE_STATIC_CLASS(ArenaHelper);
};

#endif //__ArenaPanel_h__