#ifndef __ActivityPanel_h__
#define __ActivityPanel_h__

#include "cocos2d.h"
#include "event/IEventListener.h"
#include <map>

using namespace cocos2d;

class CPItemComponents;
class ActivityPanel : public CCLayer
{
public:
	ActivityPanel();
	~ActivityPanel();

	bool init();
	void onEnter();
	CREATE_FUNC(ActivityPanel);

private:
	void initUI();
	void switchView();
	void hideView();

	void onSwitch(CCObject *target);

private:
	CPItemComponents *mSwitchMenu;
	CCNode *mSubContainer;

	int mCurrentIndex;
};

///////TimeActivity////////////////////////////////////////////////////
class CPChecker;
class CPUpdater;
class TimeActivity : public CCLayer, public IEventListener
{
public:
	TimeActivity();
	~TimeActivity();

	bool init();
	void onEnter();
	CREATE_FUNC(TimeActivity);

private:
	void initUI();

	void refresh();
	void refreshDesc();
	void refreshReward();
	void refreshState();

	void refreshStateList();

	void onList(CCObject *target);
	void onAutoMove(CCObject *target);
	void onTeleport(CCObject *target);
	void onReward(CCObject *target);
	void onDone(CCObject *target);

	void addListItem(int index);
	void addListFinish();
	void setStartIndexSel();

	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mActivityList;
	CPItemComponents *mRewardList;
	CCNode *mDescContainer;
	CCNode *mStateContainer;
	CPChecker *mChecker;
	CPUpdater *mUpdater;

	typedef std::map<int, CCLabelTTF *> LabelMap;
	LabelMap mStateLabelMap;

	int mCurrentIndex;
	int mStartIndexInView;
	bool mHasFindStartIndex;
	bool mIsFinishPart;
};

///////DailyDungeon////////////////////////////////////////////////////
class DailyDungeon : public CCLayer
{
public:
	DailyDungeon();
	~DailyDungeon();

	bool init();
	void onEnter();
	CREATE_FUNC(DailyDungeon);

private:
	void initUI();

	void refresh();
	void refreshDesc();
	void refreshReward();
	void refreshState();

	void onList(CCObject *target);
	void onAutoMove(CCObject *target);
	void onTeleport(CCObject *target);
	void onReward(CCObject *target);

	void addListItem(int index);
	void addListFinish();

private:
	CPItemComponents *mActivityList;
	CPItemComponents *mRewardList;
	CCNode *mDescContainer;
	CCNode *mStateContainer;
	CPChecker *mChecker;

	int mCurrentIndex;
};

///////DayActivity////////////////////////////////////////////////////
class DayActivity : public CCLayer
{
public:
	DayActivity();
	~DayActivity();

	bool init();
	void onEnter();
	CREATE_FUNC(DayActivity);

private:
	void initUI();

	void refresh();
	void refreshDesc();
	void refreshReward();
	void refreshState();

	void onList(CCObject *target);
	void onAutoMove(CCObject *target);
	void onTeleport(CCObject *target);
	void onReward(CCObject *target);

	void addListItem(int index);
	void addListFinish();

private:
	CPItemComponents *mActivityList;
	CPItemComponents *mRewardList;
	CCNode *mDescContainer;
	CCNode *mStateContainer;
	CPChecker *mChecker;

	int mCurrentIndex;
};

///////WorldBoss////////////////////////////////////////////////////
class WorldBoss : public CCLayer, public IEventListener
{
public:
	WorldBoss();
	~WorldBoss();

	bool init();
	void onEnter();
	CREATE_FUNC(WorldBoss);

private:
	void initUI();

	void refresh();
	void refreshDesc();
	void refreshReward();
	void refreshState();

	void refreshStateList();
	void refreshKillerList();

	void onList(CCObject *target);
	void onKiller(CCObject *target);
	void onAutoMove(CCObject *target);
	void onTeleport(CCObject *target);
	void onReward(CCObject *target);

	void addListItem(int index);
	void addListFinish();
	void setStartIndexSel();

	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mBossList;
	CPItemComponents *mRewardList;
	CCNode *mDescContainer;
	CCNode *mStateContainer;
	CPChecker *mChecker;

	typedef std::map<int, CCLabelTTF *> LabelMap;
	LabelMap mStateLabelMap;
	LabelMap mKillerNameMap;

	int mCurrentIndex;
};

///////SceneBoss////////////////////////////////////////////////////
class SceneBoss : public CCLayer, public IEventListener
{
public:
	SceneBoss();
	~SceneBoss();

	bool init();
	void onEnter();
	CREATE_FUNC(SceneBoss);

private:
	void initUI();

	void refresh();
	void refreshDesc();
	void refreshReward();
	void refreshState();

	void refreshStateList();
	void refreshKillerList();

	void onList(CCObject *target);
	void onKiller(CCObject *target);
	void onAutoMove(CCObject *target);
	void onTeleport(CCObject *target);
	void onReward(CCObject *target);

	void addListItem(int index);
	void addListFinish();
	void setStartIndexSel();

	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mBossList;
	CPItemComponents *mRewardList;
	CCNode *mDescContainer;
	CCNode *mStateContainer;
	CPChecker *mChecker;

	typedef std::map<int, CCLabelTTF *> LabelMap;
	LabelMap mStateLabelMap;
	LabelMap mKillerNameMap;

	int mCurrentIndex;
};

///////WeekActivity////////////////////////////////////////////////////
class WeekActivity : public CCLayer, public IEventListener
{
public:
	WeekActivity();
	~WeekActivity();

	bool init();
	void onEnter();
	CREATE_FUNC(WeekActivity);

private:
	void initUI();

	void refresh();
	void refreshDesc();
	void refreshReward();
	void refreshState();

	void refreshStateList();

	void onList(CCObject *target);
	void onAutoMove(CCObject *target);
	void onTeleport(CCObject *target);
	void onReward(CCObject *target);

	void addListItem(int index);
	void addListFinish();

	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mActivityList;
	CPItemComponents *mRewardList;
	CCNode *mDescContainer;
	CCNode *mStateContainer;
	CPChecker *mChecker;

	typedef std::map<int, CCLabelTTF *> LabelMap;
	LabelMap mStateLabelMap;

	int mCurrentIndex;
};

////////ActivityPanelHelper////////////////////////////////////////////////
class ActivityPanelHelper
{
public:
	static CCMenuItem *getSwitchItem(int index);
	static CCNode *getSubPanel(int type);

	static int getActivityCount(int type);
	static int getActivityID(int type, int index);
	static int getActivityIndex(int type, int activityID);
	static int getActivityType(int activityID);
	static std::string getActivityName(int type, int index);
	static std::string getActivityTime(int type, int index);
	static std::string getActivityReward(int type, int index);
	static std::string getActivityLevel(int type, int index);
	static std::string getActivityState(int type, int index, ccColor3B &color);
	static std::string getActivityEnterCount(int type, int index);
	static std::string getBossLevelAndGrow(int type, int index);
	static int  getBossLvl(std::string &bossname);
	static std::string getBossGrowExp(int type, int index);
	static std::string getKillerName(int type, int index, int &pid);
	static std::string getActivityNPC(int type, int index, int &npcID);
	static std::string getBossMap(int type, int index, int &mapID, int &x, int &y);
	static std::string getActivityDesc(int type, int index);
	static int getActivityRewardCnt(int type, int index);
	static CCSprite *getActivityRewardIcon(int type, int index, int rewardIndex, int &sid);

	static bool isTimeActivityVisible(int index);
	static int getTimeActivityVisibleCnt();
	static std::string getBossPos(int eventid, int &mapID, int &x, int &y);

private:
	ActivityPanelHelper();
	ActivityPanelHelper(const ActivityPanelHelper &);
	ActivityPanelHelper &operator=(const ActivityPanelHelper &);
	~ActivityPanelHelper();
};
#endif //__ActivityPanel_h__