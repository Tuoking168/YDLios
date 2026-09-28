#include "ActivityPanel.h"
#include "MsgActivity.h"
#include "ModuleData.h"
#include "ActivityModule.h"
#include "ActivityDefinition.h"
#include "ActivityPanelDefinition.h"
#include "ItemTooltip.h"

#include "scene/SceneHelper.h"

#include "element/ElementDefinition.h"
#include "element/AnimElement.h"

#include "controls/CPChecker.h"
#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"
#include "controls/CPUpdater.h"
#include "controls/CPRichText.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "userdata/LayoutData.h"
#include "userdata/ActivityData.h"
#include "userdata/StaticData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"

#include "utils/StringUtils.h"
#include "utils/RichTextUtils.h"

#include "script/LuaWrapper.h"

#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/HeroData.h"
#include "ErrorDefinition.h"
#include "scene/panel/activity/ActivityDataHelper.h"


////////////ActivityPanel//////////////////////////////////////////////
ActivityPanel::ActivityPanel()
	:mSwitchMenu(NULL)
	,mSubContainer(NULL)
	,mCurrentIndex(ActivityView::time_activity)
{

}

ActivityPanel::~ActivityPanel()
{

}

bool ActivityPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	const std::string &openPanel = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (openPanel == "MainPanel")
	{
		const int index = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
		if (ActivityView::begin <= index &&
			index < ActivityView::max)
		{
			mCurrentIndex = index;
		}
		else if (index == -1)
		{
			const int activityID = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
			if (activityID > 0)
			{
				mCurrentIndex = ActivityPanelHelper::getActivityType(activityID);
			}
		}
	}

	HandleMessage::sendMessage(new MsgGetInstanceCntRequest);
	initUI();
	mSwitchMenu->setCurrentIndex(mCurrentIndex);
	switchView();

	return true;
}

void ActivityPanel::onEnter()
{
	CCLayer::onEnter();
}

void ActivityPanel::initUI()
{	
	// sub board
	char ch[16];
	CCScale9Sprite *subBoard = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "subBoard");
	addChild(subBoard);

	const int subBoardCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "subBoardCnt");
	for (int i = 0; i < subBoardCnt; i++)
	{
		sprintf(ch, "subBoard%d", i);
		CCScale9Sprite *subBoard = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, ch);
		addChild(subBoard);
	}

	CCLabelTTF *descTitle = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "descTitle");
	addChild(descTitle);
	CCLabelTTF *rewardTitle = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "rewardTitle");
	addChild(rewardTitle);

	// switch menu
	const CCSize &switchSize = LayoutData::getSize(CPModuleName::ACTIVITY, "switch");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "switchItem");
	mSwitchMenu = CPItemComponents::create(switchSize, new CPLayoutList(itemSize, false));
	mSwitchMenu->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "switch"));
	addChild(mSwitchMenu);

	const int switchCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "switchCnt");
	for (int i = 0; i < switchCnt; i++)
	{
		sprintf(ch, "switch%d", i);
		CCMenuItem *btn = ActivityPanelHelper::getSwitchItem(i);
		btn->setTarget(this, menu_selector(ActivityPanel::onSwitch));
		mSwitchMenu->addItem(btn);
	}

	// sub container
	mSubContainer = CCNode::create();
	addChild(mSubContainer);
}

void ActivityPanel::switchView()
{
	hideView();
	CCNode *subPanel = mSubContainer->getChildByTag(mCurrentIndex);
	if (subPanel)
	{
		subPanel->setVisible(true);
		return;
	}

	subPanel = ActivityPanelHelper::getSubPanel(mCurrentIndex);
	if (subPanel)
	{
		mSubContainer->addChild(subPanel, 0, mCurrentIndex);
	}
}

void ActivityPanel::hideView()
{
	CCArray *children = mSubContainer->getChildren();
	if (children && children->count() > 0)
	{
		CCObject *object = NULL;
		CCARRAY_FOREACH(children, object)
		{
			CCNode *child = dynamic_cast<CCNode *>(object);
			if (child)
			{
				child->setVisible(false);
			}
		}
	}
}

void ActivityPanel::onSwitch( CCObject *target )
{
	const int index = mSwitchMenu->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
		switchView();
	}
}

///////TimeActivity////////////////////////////////////////////////////
TimeActivity::TimeActivity()
	:mActivityList(NULL)
	,mRewardList(NULL)
	,mDescContainer(NULL)
	,mStateContainer(NULL)
	,mChecker(NULL)
	,mUpdater(NULL)
	,mCurrentIndex(-1)
	,mStartIndexInView(0)
	,mHasFindStartIndex(false)
	,mIsFinishPart(false)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

TimeActivity::~TimeActivity()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool TimeActivity::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	const std::string &openPanel = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (openPanel == "MainPanel")
	{
		const int activityID = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
		if (activityID > 0)
		{
			mCurrentIndex = ActivityPanelHelper::getActivityIndex(ActivityView::time_activity, activityID);
		}
	}
	initUI();

	return true;
}

void TimeActivity::onEnter()
{
	CCLayer::onEnter();
}

void TimeActivity::initUI()
{
	// title label
	char ch[32];
	const int titleCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "timeActivityTitleCnt");
	for (int i = 0; i < titleCnt; i++)
	{
		sprintf(ch, "timeActivityTitle%d", i);
		CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, ch);
		addChild(titleLabel);
	}

	// activity list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemList");
	mActivityList = CPItemComponents::create(listSize, new CPLayoutList());
	mActivityList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemList"));
	addChild(mActivityList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mActivityList->setScrollbar(scrollBar);

	mUpdater = CPUpdater::create(this, cpupdater_selector(TimeActivity::addListItem));
	mUpdater->setUpdateTimes(ActivityPanelHelper::getActivityCount(ActivityView::time_activity));
	mUpdater->setFinishHandler(this, callfunc_selector(TimeActivity::addListFinish));
	addChild(mUpdater);
	mUpdater->start();

	// desc
	mDescContainer = CCNode::create();
	addChild(mDescContainer);

	// reward list
	const int cntPerLine = LayoutData::getInt(CPModuleName::ACTIVITY, "rewardPerLine");
	const CCSize &rewardListSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardList");
	const CCSize &rewardItemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardItem");
	mRewardList = CPItemComponents::create(rewardListSize, new CPLayoutGrid(cntPerLine, rewardItemSize, true));
	mRewardList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "rewardList"));
	addChild(mRewardList);

	const CCSize &rewardBarSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardScroll");
	CPScrollbar *rewardBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), rewardBarSize);
	mRewardList->setScrollbar(rewardBar);

	// state
	mStateContainer = CCNode::create();
	addChild(mStateContainer);
}

void TimeActivity::refresh()
{
	refreshDesc();
	refreshReward();
	refreshState();
}

void TimeActivity::refreshDesc()
{
	mDescContainer->removeAllChildrenWithCleanup(true);

	//
	int npcID = 0;
	const std::string &npcName = ActivityPanelHelper::getActivityNPC(ActivityView::time_activity, mCurrentIndex, npcID);
	
	CCSprite *npcBoard = LayoutData::getSprite(CPModuleName::ACTIVITY, "npcBoard");
	npcBoard->setScale(0.5f);
	mDescContainer->addChild(npcBoard);

	CCLabelTTF *npcNameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityNPC");
	mDescContainer->addChild(npcNameLabel);

	CCMenu *npcMenu = CCMenu::create();
	npcMenu->setPosition(CCPointZero);
	mDescContainer->addChild(npcMenu);

	CCMenuItemFont *npcNameBtn = LayoutData::getMenuItemFont(CPModuleName::ACTIVITY, "npcName");
	npcNameBtn->setTarget(this, menu_selector(TimeActivity::onAutoMove));
	npcNameBtn->setString(npcName.c_str());
	npcMenu->addChild(npcNameBtn, 0, npcID);

	CCMenuItemImage *teleportBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "teleport");
	teleportBtn->setTarget(this, menu_selector(TimeActivity::onTeleport));
	teleportBtn->setScale(0.6f);
	npcMenu->addChild(teleportBtn, 0, npcID);

	// desc list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "descList");
	CPItemComponents *descList = CPItemComponents::create(listSize, new CPLayoutList());
	descList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "descList"));
	mDescContainer->addChild(descList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "descScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	descList->setScrollbar(scrollBar);

	const std::string &desc = ActivityPanelHelper::getActivityDesc(ActivityView::time_activity, mCurrentIndex);
	const int fontSize = LayoutData::getInt(CPModuleName::ACTIVITY, "activityDescFontSize");
	const int descWidth = LayoutData::getInt(CPModuleName::ACTIVITY, "activityDescWidth");
	CPRichText *descNode = RichTextUtils::getRichText(desc, fontSize, descWidth, 0);
	descList->addItem(descNode);
}

void TimeActivity::refreshReward()
{
	mRewardList->removeAllItems();

	int sid = 0;
	const int rewardCnt = ActivityPanelHelper::getActivityRewardCnt(ActivityView::time_activity, mCurrentIndex);
	for (int i = 0; i < rewardCnt; i++)
	{
		CCSprite *icon = ActivityPanelHelper::getActivityRewardIcon(ActivityView::time_activity, mCurrentIndex, i, sid);
		if (icon)
		{
			CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid");
			item->setTarget(this, menu_selector(TimeActivity::onReward));
			mRewardList->addItem(item);
			item->setTag(sid);

			const CCSize &size = item->getContentSize();
			icon->setPosition(ccp(size.width/2, size.height/2));
			item->addChild(icon);
		}
	}
}

void TimeActivity::refreshState()
{
	mStateContainer->removeAllChildrenWithCleanup(true);

	const int activityID = ActivityPanelHelper::getActivityID(ActivityView::time_activity, mCurrentIndex);
	const int notFinishCnt = ActivityData::getNotFinishCnt(activityID);
	if (notFinishCnt > 0)
	{
		CCLabelTTF *curActivityLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "curActivity");
		mStateContainer->addChild(curActivityLabel);

		CCLabelTTF *curActivityNameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "bottomStateData");
		curActivityNameLabel->setString(ActivityPanelHelper::getActivityName(ActivityView::time_activity, mCurrentIndex).c_str());
		curActivityNameLabel->setPosition(curActivityLabel->getPosition());
		mStateContainer->addChild(curActivityNameLabel);

		CCLabelTTF *notFinishLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "notFinish");
		mStateContainer->addChild(notFinishLabel);

		CCLabelTTF *notFinishCntLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "bottomStateData");
		notFinishCntLabel->setString(StringUtils::toString(notFinishCnt).c_str());
		notFinishCntLabel->setPosition(notFinishLabel->getPosition());
		mStateContainer->addChild(notFinishCntLabel);

		CCLabelTTF *totalRewardLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "totalReward");
		mStateContainer->addChild(totalRewardLabel);

		const std::string rewardData = StringUtils::toString(notFinishCnt * 100) + "%";
		CCLabelTTF *totalRewardDataLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "bottomStateData");
		totalRewardDataLabel->setString(rewardData.c_str());
		totalRewardDataLabel->setPosition(totalRewardLabel->getPosition());
		mStateContainer->addChild(totalRewardDataLabel);

		CCLabelTTF *canDoneLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "canDone");
		mStateContainer->addChild(canDoneLabel);

		CCMenu *menu = CCMenu::create();
		menu->setPosition(CCPointZero);
		mStateContainer->addChild(menu);

		CCMenuItemImage *doneBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "done");
		doneBtn->setTarget(this, menu_selector(TimeActivity::onDone));
		menu->addChild(doneBtn);
	}
	else
	{
		CCLabelTTF *canNotDoneLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "canNotDone");
		mStateContainer->addChild(canNotDoneLabel);
	}
}

void TimeActivity::refreshStateList()
{
	ccColor3B color;
	LabelMap::iterator it = mStateLabelMap.begin();
	LabelMap::iterator itEnd = mStateLabelMap.end();
	while (it != itEnd)
	{
		CCLabelTTF *label = it->second;
		if (label)
		{
			const std::string &str = ActivityPanelHelper::getActivityState(ActivityView::time_activity, it->first, color);
			label->setString(str.c_str());
			label->setColor(color);
		}
		it++;
	}
}

void TimeActivity::onList( CCObject *target )
{
	const int index = mActivityList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
		refresh();
	}
}

void TimeActivity::onAutoMove( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int npcID = node->getTag();
		if (npcID > 0)
		{
			SceneHelper::autoMoveToNPC(npcID);
		}
	}
}

void TimeActivity::onTeleport( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int npcID = node->getTag();
		if (npcID > 0)
		{
			SceneHelper::teleportToNPCRequest(npcID);
		}
	}
}

void TimeActivity::onReward( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		ItemTooltip *tips = ItemTooltip::create();
		tips->setTooltipContentbysid(node->getTag());
		tips->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemTips"));
		addChild(tips);
	}
}

void TimeActivity::onDone( CCObject *target )
{

}

void TimeActivity::addListItem( int index )
{
	if (!ActivityPanelHelper::isTimeActivityVisible(index))
	{
		return;
	}

	ccColor3B stateColor;
	const std::string &stateString = ActivityPanelHelper::getActivityState(ActivityView::time_activity, index, stateColor);
	const std::string &endString = LayoutData::getString(CPModuleName::ACTIVITY, "stateEnd");
	if ((!mIsFinishPart && stateString == endString) ||
		(mIsFinishPart && stateString != endString))
	{
		return;
	}

	//
	if (mCurrentIndex < 0)
	{
		mCurrentIndex = index;
		refresh();
	}

	if (index == mCurrentIndex)
	{
		mHasFindStartIndex = true;
	}
	else if (!mHasFindStartIndex)
	{
		mStartIndexInView++;
	}

	CCNode *norm = CCNode::create();
	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "listSel");
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
	item->setTarget(this, menu_selector(TimeActivity::onList));
	mActivityList->addItem(item);
	item->setTag(index);

	const int ox = LayoutData::getInt(CPModuleName::ACTIVITY, "listTextOx");
	const int y = sel->getContentSize().height/2;
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle0");
	nameLabel->setString(ActivityPanelHelper::getActivityName(ActivityView::time_activity, index).c_str());
	nameLabel->setPositionX(nameLabel->getPositionX() + ox);
	nameLabel->setPositionY(y);
	item->addChild(nameLabel);

	CCLabelTTF *timeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle1");
	timeLabel->setString(ActivityPanelHelper::getActivityTime(ActivityView::time_activity, index).c_str());
	timeLabel->setPositionX(timeLabel->getPositionX() + ox);
	timeLabel->setPositionY(y);
	item->addChild(timeLabel);

	CCLabelTTF *rewardLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle2");
	rewardLabel->setString(ActivityPanelHelper::getActivityReward(ActivityView::time_activity, index).c_str());
	rewardLabel->setPositionX(rewardLabel->getPositionX() + ox);
	rewardLabel->setPositionY(y);
	item->addChild(rewardLabel);

	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle3");
	levelLabel->setString(ActivityPanelHelper::getActivityLevel(ActivityView::time_activity, index).c_str());
	levelLabel->setPositionX(levelLabel->getPositionX() + ox);
	levelLabel->setPositionY(y);
	item->addChild(levelLabel);

	CCLabelTTF *stateLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle4");
	stateLabel->setString(stateString.c_str());
	stateLabel->setColor(stateColor);
	stateLabel->setPositionX(stateLabel->getPositionX() + ox);
	stateLabel->setPositionY(y);
	item->addChild(stateLabel);
	mStateLabelMap[index] = stateLabel;
}

void TimeActivity::addListFinish()
{
	refresh();
	mActivityList->setCurrentIndex(mCurrentIndex);
	if (!mIsFinishPart)
	{
		mIsFinishPart = true;
		mUpdater->setUpdateTimes(ActivityPanelHelper::getActivityCount(ActivityView::time_activity));
		mUpdater->start();
	}
	else
	{
		const int count = ActivityPanelHelper::getTimeActivityVisibleCnt();
		if (count > 0)
		{
			mActivityList->setPercent(mStartIndexInView * 100 / count);
			runAction(CCSequence::create(
				CCDelayTime::create(0.1f),
				CCCallFunc::create(this, callfunc_selector(TimeActivity::setStartIndexSel)),
				NULL));
		}
	}
}

void TimeActivity::setStartIndexSel()
{
	mActivityList->setCurrentIndex(mCurrentIndex);
}

void TimeActivity::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_CHANGE)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageSyncEventStateNotify")
		{
			refreshStateList();
		}
		else if (source == "HandleMessageSyncEventNotFinishCountNotify")
		{
			refreshState();
		}
	}
}

////////DailyDungeon////////////////////////////////////////////////
DailyDungeon::DailyDungeon()
	:mActivityList(NULL)
	,mRewardList(NULL)
	,mDescContainer(NULL)
	,mStateContainer(NULL)
	,mChecker(NULL)
	,mCurrentIndex(0)
{

}

DailyDungeon::~DailyDungeon()
{

}

bool DailyDungeon::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initUI();
	refresh();

	return true;
}

void DailyDungeon::onEnter()
{
	CCLayer::onEnter();
}

void DailyDungeon::initUI()
{
	// title label
	char ch[32];
	const int titleCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "dailyDungeonTitleCnt");
	for (int i = 0; i < titleCnt; i++)
	{
		sprintf(ch, "dailyDungeonTitle%d", i);
		CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, ch);
		addChild(titleLabel);
	}

	// activity list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemList");
	mActivityList = CPItemComponents::create(listSize, new CPLayoutList());
	mActivityList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemList"));
	addChild(mActivityList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mActivityList->setScrollbar(scrollBar);

	CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(DailyDungeon::addListItem));
	updater->setUpdateTimes(ActivityPanelHelper::getActivityCount(ActivityView::daily_dungeon));
	updater->setFinishHandler(this, callfunc_selector(DailyDungeon::addListFinish));
	addChild(updater);
	updater->start();

	// desc
	mDescContainer = CCNode::create();
	addChild(mDescContainer);

	// reward list
	const int cntPerLine = LayoutData::getInt(CPModuleName::ACTIVITY, "rewardPerLine");
	const CCSize &rewardListSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardList");
	const CCSize &rewardItemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardItem");
	mRewardList = CPItemComponents::create(rewardListSize, new CPLayoutGrid(cntPerLine, rewardItemSize, true));
	mRewardList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "rewardList"));
	addChild(mRewardList);

	const CCSize &rewardBarSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardScroll");
	CPScrollbar *rewardBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), rewardBarSize);
	mRewardList->setScrollbar(rewardBar);

	// state
	mStateContainer = CCNode::create();
	addChild(mStateContainer);
}

void DailyDungeon::refresh()
{
	refreshDesc();
	refreshReward();
	refreshState();
}

void DailyDungeon::refreshDesc()
{
	mDescContainer->removeAllChildrenWithCleanup(true);

	//
	int npcID = 0;
	const std::string &npcName = ActivityPanelHelper::getActivityNPC(ActivityView::daily_dungeon, mCurrentIndex, npcID);

	CCSprite *npcBoard = LayoutData::getSprite(CPModuleName::ACTIVITY, "npcBoard");
	npcBoard->setScale(0.5f);
	mDescContainer->addChild(npcBoard);

	CCLabelTTF *npcNameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityNPC");
	mDescContainer->addChild(npcNameLabel);

	CCMenu *npcMenu = CCMenu::create();
	npcMenu->setPosition(CCPointZero);
	mDescContainer->addChild(npcMenu);

	CCMenuItemFont *npcNameBtn = LayoutData::getMenuItemFont(CPModuleName::ACTIVITY, "npcName");
	npcNameBtn->setTarget(this, menu_selector(DailyDungeon::onAutoMove));
	npcNameBtn->setString(npcName.c_str());
	npcMenu->addChild(npcNameBtn, 0, npcID);

	CCMenuItemImage *teleportBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "teleport");
	teleportBtn->setTarget(this, menu_selector(DailyDungeon::onTeleport));
	teleportBtn->setScale(0.6f);
	npcMenu->addChild(teleportBtn, 0, npcID);

	// desc list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "descList");
	CPItemComponents *descList = CPItemComponents::create(listSize, new CPLayoutList());
	descList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "descList"));
	mDescContainer->addChild(descList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "descScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	descList->setScrollbar(scrollBar);

	const std::string &desc = ActivityPanelHelper::getActivityDesc(ActivityView::daily_dungeon, mCurrentIndex);
	const int fontSize = LayoutData::getInt(CPModuleName::ACTIVITY, "activityDescFontSize");
	const int descWidth = LayoutData::getInt(CPModuleName::ACTIVITY, "activityDescWidth");
	CPRichText *descNode = RichTextUtils::getRichText(desc, fontSize, descWidth, 0);
	descList->addItem(descNode);
}

void DailyDungeon::refreshReward()
{
	mRewardList->removeAllItems();

	int sid = 0;
	const int rewardCnt = ActivityPanelHelper::getActivityRewardCnt(ActivityView::daily_dungeon, mCurrentIndex);
	for (int i = 0; i < rewardCnt; i++)
	{
		CCSprite *icon = ActivityPanelHelper::getActivityRewardIcon(ActivityView::daily_dungeon, mCurrentIndex, i, sid);
		if (icon)
		{
			CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid");
			item->setTarget(this, menu_selector(DailyDungeon::onReward));
			mRewardList->addItem(item);
			item->setTag(sid);

			const CCSize &size = item->getContentSize();
			icon->setPosition(ccp(size.width/2, size.height/2));
			item->addChild(icon);
		}
	}
}

void DailyDungeon::refreshState()
{
	mStateContainer->removeAllChildrenWithCleanup(true);
	CCLabelTTF *canNotDoneLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "canNotDone");
	mStateContainer->addChild(canNotDoneLabel);
}

void DailyDungeon::onList( CCObject *target )
{
	const int index = mActivityList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
		refresh();
	}
}

void DailyDungeon::onAutoMove( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int npcID = node->getTag();
		if (npcID > 0)
		{
			SceneHelper::autoMoveToNPC(npcID);
		}
	}
}

void DailyDungeon::onTeleport( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int npcID = node->getTag();
		if (npcID > 0)
		{
			SceneHelper::teleportToNPCRequest(npcID);
		}
	}
}

void DailyDungeon::onReward( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		ItemTooltip *tips = ItemTooltip::create();
		tips->setTooltipContentbysid(node->getTag());
		tips->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemTips"));
		addChild(tips);
	}
}

void DailyDungeon::addListItem( int index )
{
	CCNode *norm = CCNode::create();
	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "listSel");
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
	item->setTarget(this, menu_selector(DailyDungeon::onList));
	mActivityList->addItem(item);

	const int ox = LayoutData::getInt(CPModuleName::ACTIVITY, "listTextOx");
	const int y = sel->getContentSize().height/2;
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "dailyDungeonTitle0");
	nameLabel->setString(ActivityPanelHelper::getActivityName(ActivityView::daily_dungeon, index).c_str());
	nameLabel->setPositionX(nameLabel->getPositionX() + ox);
	nameLabel->setPositionY(y);
	item->addChild(nameLabel);
	if (nameLabel->getPositionX() < nameLabel->getContentSize().width/2)
	{
		nameLabel->setPositionX(nameLabel->getContentSize().width/2);
	}

	CCLabelTTF *rewardLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "dailyDungeonTitle1");
	rewardLabel->setString(ActivityPanelHelper::getActivityReward(ActivityView::daily_dungeon, index).c_str());
	rewardLabel->setPositionX(rewardLabel->getPositionX() + ox);
	rewardLabel->setPositionY(y);
	item->addChild(rewardLabel);

	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "dailyDungeonTitle2");
	levelLabel->setString(ActivityPanelHelper::getActivityLevel(ActivityView::daily_dungeon, index).c_str());
	levelLabel->setPositionX(levelLabel->getPositionX() + ox);
	levelLabel->setPositionY(y);
	item->addChild(levelLabel);

	ccColor3B timesColor;
	const std::string &timesStr = ActivityPanelHelper::getActivityState(ActivityView::daily_dungeon, index, timesColor);
	CCLabelTTF *timesLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "dailyDungeonTitle3");
	timesLabel->setString(timesStr.c_str());
	timesLabel->setColor(timesColor);
	timesLabel->setPositionX(timesLabel->getPositionX() + ox);
	timesLabel->setPositionY(y);
	item->addChild(timesLabel);
}

void DailyDungeon::addListFinish()
{
	mActivityList->setCurrentIndex(mCurrentIndex);
}

//////////DayActivity//////////////////////////////////////////////////
DayActivity::DayActivity()
	:mActivityList(NULL)
	,mRewardList(NULL)
	,mDescContainer(NULL)
	,mStateContainer(NULL)
	,mChecker(NULL)
	,mCurrentIndex(0)
{

}

DayActivity::~DayActivity()
{

}

bool DayActivity::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initUI();
	refresh();

	return true;
}

void DayActivity::onEnter()
{
	CCLayer::onEnter();
}

void DayActivity::initUI()
{
	// title label
	char ch[32];
	const int titleCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "timeActivityTitleCnt");
	for (int i = 0; i < titleCnt; i++)
	{
		sprintf(ch, "timeActivityTitle%d", i);
		CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, ch);
		addChild(titleLabel);
	}

	// activity list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemList");
	mActivityList = CPItemComponents::create(listSize, new CPLayoutList());
	mActivityList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemList"));
	addChild(mActivityList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mActivityList->setScrollbar(scrollBar);

	CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(DayActivity::addListItem));
	updater->setUpdateTimes(ActivityPanelHelper::getActivityCount(ActivityView::day_activity));
	updater->setFinishHandler(this, callfunc_selector(DayActivity::addListFinish));
	addChild(updater);
	updater->start();

	// desc
	mDescContainer = CCNode::create();
	addChild(mDescContainer);

	// reward list
	const int cntPerLine = LayoutData::getInt(CPModuleName::ACTIVITY, "rewardPerLine");
	const CCSize &rewardListSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardList");
	const CCSize &rewardItemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardItem");
	mRewardList = CPItemComponents::create(rewardListSize, new CPLayoutGrid(cntPerLine, rewardItemSize, true));
	mRewardList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "rewardList"));
	addChild(mRewardList);

	const CCSize &rewardBarSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardScroll");
	CPScrollbar *rewardBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), rewardBarSize);
	mRewardList->setScrollbar(rewardBar);

	// state
	mStateContainer = CCNode::create();
	addChild(mStateContainer);
}

void DayActivity::refresh()
{
	refreshDesc();
	refreshReward();
	refreshState();
}

void DayActivity::refreshDesc()
{
	mDescContainer->removeAllChildrenWithCleanup(true);

	//
	int npcID = 0;
	const std::string &npcName = ActivityPanelHelper::getActivityNPC(ActivityView::day_activity, mCurrentIndex, npcID);

	CCSprite *npcBoard = LayoutData::getSprite(CPModuleName::ACTIVITY, "npcBoard");
	npcBoard->setScale(0.5f);
	mDescContainer->addChild(npcBoard);

	CCLabelTTF *npcNameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityNPC");
	mDescContainer->addChild(npcNameLabel);

	CCMenu *npcMenu = CCMenu::create();
	npcMenu->setPosition(CCPointZero);
	mDescContainer->addChild(npcMenu);

	CCMenuItemFont *npcNameBtn = LayoutData::getMenuItemFont(CPModuleName::ACTIVITY, "npcName");
	npcNameBtn->setTarget(this, menu_selector(DayActivity::onAutoMove));
	npcNameBtn->setString(npcName.c_str());
	npcMenu->addChild(npcNameBtn, 0, npcID);

	CCMenuItemImage *teleportBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "teleport");
	teleportBtn->setTarget(this, menu_selector(DayActivity::onTeleport));
	teleportBtn->setScale(0.6f);
	npcMenu->addChild(teleportBtn, 0, npcID);

	// desc list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "descList");
	CPItemComponents *descList = CPItemComponents::create(listSize, new CPLayoutList());
	descList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "descList"));
	mDescContainer->addChild(descList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "descScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	descList->setScrollbar(scrollBar);

	const std::string &desc = ActivityPanelHelper::getActivityDesc(ActivityView::day_activity, mCurrentIndex);
	const int fontSize = LayoutData::getInt(CPModuleName::ACTIVITY, "activityDescFontSize");
	const int descWidth = LayoutData::getInt(CPModuleName::ACTIVITY, "activityDescWidth");
	CPRichText *descNode = RichTextUtils::getRichText(desc, fontSize, descWidth, 0);
	descList->addItem(descNode);
}

void DayActivity::refreshReward()
{
	mRewardList->removeAllItems();

	int sid = 0;
	const int rewardCnt = ActivityPanelHelper::getActivityRewardCnt(ActivityView::day_activity, mCurrentIndex);
	for (int i = 0; i < rewardCnt; i++)
	{
		CCSprite *icon = ActivityPanelHelper::getActivityRewardIcon(ActivityView::day_activity, mCurrentIndex, i, sid);
		if (icon)
		{
			CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid");
			item->setTarget(this, menu_selector(DayActivity::onReward));
			mRewardList->addItem(item);
			item->setTag(sid);

			const CCSize &size = item->getContentSize();
			icon->setPosition(ccp(size.width/2, size.height/2));
			item->addChild(icon);
		}
	}
}

void DayActivity::refreshState()
{
	mStateContainer->removeAllChildrenWithCleanup(true);
	CCLabelTTF *canNotDoneLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "canNotDone");
	mStateContainer->addChild(canNotDoneLabel);
}

void DayActivity::onList( CCObject *target )
{
	const int index = mActivityList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
		refresh();
	}
}

void DayActivity::onAutoMove( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int npcID = node->getTag();
		if (npcID > 0)
		{
			SceneHelper::autoMoveToNPC(npcID);
		}
	}
}

void DayActivity::onTeleport( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int npcID = node->getTag();
		if (npcID > 0)
		{
			SceneHelper::teleportToNPCRequest(npcID);
		}
	}
}

void DayActivity::onReward( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		ItemTooltip *tips = ItemTooltip::create();
		tips->setTooltipContentbysid(node->getTag());
		tips->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemTips"));
		addChild(tips);
	}
}

void DayActivity::addListItem( int index )
{
	CCNode *norm = CCNode::create();
	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "listSel");
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
	item->setTarget(this, menu_selector(DayActivity::onList));
	mActivityList->addItem(item);

	const int ox = LayoutData::getInt(CPModuleName::ACTIVITY, "listTextOx");
	const int y = sel->getContentSize().height/2;
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle0");
	nameLabel->setString(ActivityPanelHelper::getActivityName(ActivityView::day_activity, index).c_str());
	nameLabel->setPositionX(nameLabel->getPositionX() + ox);
	nameLabel->setPositionY(y);
	item->addChild(nameLabel);

	CCLabelTTF *timeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle1");
	timeLabel->setString(ActivityPanelHelper::getActivityTime(ActivityView::day_activity, index).c_str());
	timeLabel->setPositionX(timeLabel->getPositionX() + ox);
	timeLabel->setPositionY(y);
	item->addChild(timeLabel);

	CCLabelTTF *rewardLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle2");
	rewardLabel->setString(ActivityPanelHelper::getActivityReward(ActivityView::day_activity, index).c_str());
	rewardLabel->setPositionX(rewardLabel->getPositionX() + ox);
	rewardLabel->setPositionY(y);
	item->addChild(rewardLabel);

	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle3");
	levelLabel->setString(ActivityPanelHelper::getActivityLevel(ActivityView::day_activity, index).c_str());
	levelLabel->setPositionX(levelLabel->getPositionX() + ox);
	levelLabel->setPositionY(y);
	item->addChild(levelLabel);

	ccColor3B stateColor;
	const std::string &stateStr = ActivityPanelHelper::getActivityState(ActivityView::day_activity, index, stateColor);
	CCLabelTTF *stateLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle4");
	stateLabel->setString(stateStr.c_str());
	stateLabel->setColor(stateColor);
	stateLabel->setPositionX(stateLabel->getPositionX() + ox);
	stateLabel->setPositionY(y);
	item->addChild(stateLabel);
}

void DayActivity::addListFinish()
{
	mActivityList->setCurrentIndex(mCurrentIndex);
}

/////////WorldBoss///////////////////////////////////////////////////
WorldBoss::WorldBoss()
	:mBossList(NULL)
	,mRewardList(NULL)
	,mDescContainer(NULL)
	,mStateContainer(NULL)
	,mChecker(NULL)
	,mCurrentIndex(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

WorldBoss::~WorldBoss()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool WorldBoss::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	const std::string &openPanel = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (openPanel == "MainPanel")
	{
		const int activityID = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
		if (activityID > 0)
		{
			mCurrentIndex = ActivityPanelHelper::getActivityIndex(ActivityView::world_boss, activityID);
		}
	}
	initUI();

	return true;
}

void WorldBoss::onEnter()
{
	CCLayer::onEnter();
}

void WorldBoss::initUI()
{
	// title label
	char ch[32];
	const int titleCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "timeActivityTitleCnt");
	for (int i = 0; i < titleCnt; i++)
	{
		sprintf(ch, "worldBossTitle%d", i);
		CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, ch);
		addChild(titleLabel);
	}

	// activity list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemList");
	mBossList = CPItemComponents::create(listSize, new CPLayoutList());
	mBossList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemList"));
	addChild(mBossList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mBossList->setScrollbar(scrollBar);

	CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(WorldBoss::addListItem));
	updater->setUpdateTimes(ActivityPanelHelper::getActivityCount(ActivityView::world_boss));
	updater->setFinishHandler(this, callfunc_selector(WorldBoss::addListFinish));
	addChild(updater);
	updater->start();

	// desc
	mDescContainer = CCNode::create();
	addChild(mDescContainer);

	// reward list
	const int cntPerLine = LayoutData::getInt(CPModuleName::ACTIVITY, "rewardPerLine");
	const CCSize &rewardListSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardList");
	const CCSize &rewardItemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardItem");
	mRewardList = CPItemComponents::create(rewardListSize, new CPLayoutGrid(cntPerLine, rewardItemSize, true));
	mRewardList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "rewardList"));
	addChild(mRewardList);

	const CCSize &rewardBarSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardScroll");
	CPScrollbar *rewardBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), rewardBarSize);
	mRewardList->setScrollbar(rewardBar);

	// state
	mStateContainer = CCNode::create();
	addChild(mStateContainer);
}

void WorldBoss::refresh()
{
	refreshDesc();
	refreshReward();
	refreshState();
}

void WorldBoss::refreshDesc()
{
	mDescContainer->removeAllChildrenWithCleanup(true);

	//
	int mapID = 0, x = 0, y = 0;
	const std::string &mapName = ActivityPanelHelper::getBossMap(ActivityView::world_boss, mCurrentIndex, mapID, x, y);

	CCSprite *npcBoard = LayoutData::getSprite(CPModuleName::ACTIVITY, "npcBoard");
	npcBoard->setScale(0.5f);
	mDescContainer->addChild(npcBoard);

	CCLabelTTF *bossMapLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityBossMap");
	mDescContainer->addChild(bossMapLabel);

	CCMenu *mapNameMenu = CCMenu::create();
	mapNameMenu->setPosition(CCPointZero);
	mDescContainer->addChild(mapNameMenu);

	CCMenuItemFont *mapNameBtn = LayoutData::getMenuItemFont(CPModuleName::ACTIVITY, "npcName");
	mapNameBtn->setTarget(this, menu_selector(WorldBoss::onAutoMove));
	mapNameBtn->setString(mapName.c_str());
	mapNameMenu->addChild(mapNameBtn);

	CCMenuItemImage *teleportBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "teleport");
	teleportBtn->setTarget(this, menu_selector(WorldBoss::onTeleport));
	teleportBtn->setScale(0.6f);
	mapNameMenu->addChild(teleportBtn);

	// anim
	const int activityID = ActivityPanelHelper::getActivityID(ActivityView::world_boss, mCurrentIndex);
	const int monsterID = ActivityData::getWorldBossSID(activityID);
	AnimElement *anim = AnimElement::create(monsterID, CPElement::Type::monster);
	anim->setCloth(monsterID);
	anim->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "monsterAnim"));
	mDescContainer->addChild(anim);
}

void WorldBoss::refreshReward()
{
	mRewardList->removeAllItems();

	int sid = 0;
	const int rewardCnt = ActivityPanelHelper::getActivityRewardCnt(ActivityView::world_boss, mCurrentIndex);
	for (int i = 0; i < rewardCnt; i++)
	{
		CCSprite *icon = ActivityPanelHelper::getActivityRewardIcon(ActivityView::world_boss, mCurrentIndex, i, sid);
		if (icon)
		{
			CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid");
			item->setTarget(this, menu_selector(WorldBoss::onReward));
			mRewardList->addItem(item);
			item->setTag(sid);

			const CCSize &size = item->getContentSize();
			icon->setPosition(ccp(size.width/2, size.height/2));
			item->addChild(icon);
		}
	}
}

void WorldBoss::refreshState()
{
	mStateContainer->removeAllChildrenWithCleanup(true);
	CCLabelTTF *canNotDoneLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "canNotDone");
	mStateContainer->addChild(canNotDoneLabel);
}

void WorldBoss::refreshStateList()
{
	ccColor3B color;
	LabelMap::iterator it = mStateLabelMap.begin();
	LabelMap::iterator itEnd = mStateLabelMap.end();
	while (it != itEnd)
	{
		CCLabelTTF *label = it->second;
		if (label)
		{
			const std::string str = ActivityPanelHelper::getActivityState(ActivityView::world_boss, it->first, color);
			label->setString(str.c_str());
			label->setColor(color);
		}
		it++;
	}
}

void WorldBoss::refreshKillerList()
{

}

void WorldBoss::onList( CCObject *target )
{
	const int index = mBossList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
		refresh();
	}
}

void WorldBoss::onKiller( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int pid = node->getTag();
	}
}

void WorldBoss::onAutoMove( CCObject *target )
{
	int mapID = 0, x = 0, y = 0;
	ActivityPanelHelper::getBossMap(ActivityView::world_boss, mCurrentIndex, mapID, x, y);
	if (mapID > 0 &&
		x > 0 &&
		y > 0)
	{
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->startAutoMoveToCrossMap(mapID, x, y, GHOST_TYPE_MONSTER);
	}
}

void WorldBoss::onTeleport( CCObject *target )
{
	const int activityID = ActivityPanelHelper::getActivityID(ActivityView::world_boss, mCurrentIndex);
	int playerLv = 0;
	int bossLv = 0;
	playerLv = HeroData::getLevel();
	std::string bossname;
	LuaData::getProp("gdWorldMonEvent",activityID,"name",bossname);
	bossLv = ActivityPanelHelper::getBossLvl(bossname);
	if (playerLv < bossLv && HeroData::getProp(Entity::attr_reborn) < 1)
	{
		CPEventHelper::uiNotify("","",Error::Not_enough_lvl_for_boss);
		return;
	}
	SceneHelper::teleportToActivityBoss(activityID);
}

void WorldBoss::onReward( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		ItemTooltip *tips = ItemTooltip::create();
		tips->setTooltipContentbysid(node->getTag());
		tips->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemTips"));
		addChild(tips);
	}
}

void WorldBoss::addListItem( int index )
{
	CCNode *norm = CCNode::create();
	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "listSel");
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
	item->setTarget(this, menu_selector(WorldBoss::onList));
	mBossList->addItem(item);

	const int ox = LayoutData::getInt(CPModuleName::ACTIVITY, "listTextOx");
	const int y = sel->getContentSize().height/2;
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "worldBossTitle0");
	nameLabel->setString(ActivityPanelHelper::getActivityName(ActivityView::world_boss, index).c_str());
	nameLabel->setPositionX(nameLabel->getPositionX() + ox);
	nameLabel->setPositionY(y);
	item->addChild(nameLabel);

	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "worldBossTitle1");
	levelLabel->setString(ActivityPanelHelper::getBossLevelAndGrow(ActivityView::world_boss, index).c_str());
	levelLabel->setPositionX(levelLabel->getPositionX() + ox);
	levelLabel->setPositionY(y);
	item->addChild(levelLabel);

	CCLabelTTF *growExpLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "worldBossTitle2");
	growExpLabel->setString(ActivityPanelHelper::getBossGrowExp(ActivityView::world_boss, index).c_str());
	growExpLabel->setPositionX(growExpLabel->getPositionX() + ox);
	growExpLabel->setPositionY(y);
	item->addChild(growExpLabel);

	ccColor3B stateColor;
	const std::string &stateStr = ActivityPanelHelper::getActivityState(ActivityView::world_boss, index, stateColor);
	CCLabelTTF *stateLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "worldBossTitle3");
	stateLabel->setString(stateStr.c_str());
	stateLabel->setColor(stateColor);
	stateLabel->setPositionX(stateLabel->getPositionX() + ox);
	stateLabel->setPositionY(y);
	item->addChild(stateLabel);
	mStateLabelMap[index] = stateLabel;

	int pid = 0;
	const std::string &killerName = ActivityPanelHelper::getKillerName(ActivityView::world_boss, index, pid);
	CCMenu *killNameMenu = CCMenu::create();
	killNameMenu->setPosition(CCPointZero);
	item->addChild(killNameMenu);

	CCLabelTTF *killerNameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "worldBossTitle4");
	killerNameLabel->setString(killerName.c_str());

	CCMenuItem *killNameBtn = CCMenuItem::create();
	killNameBtn->setContentSize(killerNameLabel->getContentSize());
	killNameBtn->setTarget(this, menu_selector(WorldBoss::onKiller));
	killNameBtn->setPositionX(killerNameLabel->getPositionX() + ox);
	killNameBtn->setPositionY(y);
	killNameMenu->addChild(killNameBtn, 0, pid);

	killerNameLabel->setAnchorPoint(CCPointZero);
	killerNameLabel->setPosition(CCPointZero);
	killNameBtn->addChild(killerNameLabel);
	mKillerNameMap[index] = killerNameLabel;
}

void WorldBoss::addListFinish()
{
	refresh();
	const int count = ActivityPanelHelper::getActivityCount(ActivityView::world_boss);
	if (count > 0)
	{
		mBossList->setPercent(mCurrentIndex * 100 / count);
		runAction(CCSequence::create(
			CCDelayTime::create(0.1f),
			CCCallFunc::create(this, callfunc_selector(WorldBoss::setStartIndexSel)),
			NULL));
	}
}

void WorldBoss::setStartIndexSel()
{
	mBossList->setCurrentIndex(mCurrentIndex);
}

void WorldBoss::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_CHANGE)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageSyncEventStateNotify")
		{
			refreshStateList();
		}
	}
}

/////////SceneBoss//////////////////////////////////////////////////
SceneBoss::SceneBoss()
	:mBossList(NULL)
	,mRewardList(NULL)
	,mDescContainer(NULL)
	,mStateContainer(NULL)
	,mChecker(NULL)
	,mCurrentIndex(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

SceneBoss::~SceneBoss()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool SceneBoss::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	const std::string &openPanel = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (openPanel == "MainPanel")
	{
		const int activityID = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
		if (activityID > 0)
		{
			mCurrentIndex = ActivityPanelHelper::getActivityIndex(ActivityView::scene_boss, activityID);
		}
	}
	initUI();

	return true;
}

void SceneBoss::onEnter()
{
	CCLayer::onEnter();
}

void SceneBoss::initUI()
{
	// title label
	char ch[32];
	const int titleCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "timeActivityTitleCnt");
	for (int i = 0; i < titleCnt; i++)
	{
		sprintf(ch, "worldBossTitle%d", i);
		CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, ch);
		addChild(titleLabel);
	}

	// activity list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemList");
	mBossList = CPItemComponents::create(listSize, new CPLayoutList());
	mBossList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemList"));
	addChild(mBossList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mBossList->setScrollbar(scrollBar);

	CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(SceneBoss::addListItem));
	updater->setUpdateTimes(ActivityPanelHelper::getActivityCount(ActivityView::scene_boss));
	updater->setFinishHandler(this, callfunc_selector(SceneBoss::addListFinish));
	addChild(updater);
	updater->start();

	// desc
	mDescContainer = CCNode::create();
	addChild(mDescContainer);

	// reward list
	const int cntPerLine = LayoutData::getInt(CPModuleName::ACTIVITY, "rewardPerLine");
	const CCSize &rewardListSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardList");
	const CCSize &rewardItemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardItem");
	mRewardList = CPItemComponents::create(rewardListSize, new CPLayoutGrid(cntPerLine, rewardItemSize, true));
	mRewardList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "rewardList"));
	addChild(mRewardList);

	const CCSize &rewardBarSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardScroll");
	CPScrollbar *rewardBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), rewardBarSize);
	mRewardList->setScrollbar(rewardBar);

	// state
	mStateContainer = CCNode::create();
	addChild(mStateContainer);
}

void SceneBoss::refresh()
{
	refreshDesc();
	refreshReward();
	refreshState();
}

void SceneBoss::refreshDesc()
{
	mDescContainer->removeAllChildrenWithCleanup(true);

	//
	int mapID = 0, x = 0, y = 0;
	const std::string &mapName = ActivityPanelHelper::getBossMap(ActivityView::scene_boss, mCurrentIndex, mapID, x, y);

	CCSprite *npcBoard = LayoutData::getSprite(CPModuleName::ACTIVITY, "npcBoard");
	npcBoard->setScale(0.5f);
	mDescContainer->addChild(npcBoard);

	CCLabelTTF *bossMapLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityBossMap");
	mDescContainer->addChild(bossMapLabel);

	CCMenu *mapNameMenu = CCMenu::create();
	mapNameMenu->setPosition(CCPointZero);
	mDescContainer->addChild(mapNameMenu);

	CCMenuItemFont *mapNameBtn = LayoutData::getMenuItemFont(CPModuleName::ACTIVITY, "npcName");
	mapNameBtn->setTarget(this, menu_selector(SceneBoss::onAutoMove));
	mapNameBtn->setString(mapName.c_str());
	mapNameMenu->addChild(mapNameBtn);

	CCMenuItemImage *teleportBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "teleport");
	teleportBtn->setTarget(this, menu_selector(SceneBoss::onTeleport));
	teleportBtn->setScale(0.6f);
	mapNameMenu->addChild(teleportBtn);

	// anim
	const int activityID = ActivityPanelHelper::getActivityID(ActivityView::scene_boss, mCurrentIndex);
	const int monsterID = ActivityData::getWorldBossSID(activityID);
	AnimElement *anim = AnimElement::create(monsterID, CPElement::Type::monster);
	anim->setCloth(monsterID);
	anim->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "monsterAnim"));
	mDescContainer->addChild(anim);
}

void SceneBoss::refreshReward()
{
	mRewardList->removeAllItems();

	int sid = 0;
	const int rewardCnt = ActivityPanelHelper::getActivityRewardCnt(ActivityView::scene_boss, mCurrentIndex);
	for (int i = 0; i < rewardCnt; i++)
	{
		CCSprite *icon = ActivityPanelHelper::getActivityRewardIcon(ActivityView::scene_boss, mCurrentIndex, i, sid);
		if (icon)
		{
			CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid");
			item->setTarget(this, menu_selector(SceneBoss::onReward));
			mRewardList->addItem(item);
			item->setTag(sid);

			const CCSize &size = item->getContentSize();
			icon->setPosition(ccp(size.width/2, size.height/2));
			item->addChild(icon);
		}
	}
}

void SceneBoss::refreshState()
{
	mStateContainer->removeAllChildrenWithCleanup(true);
	CCLabelTTF *canNotDoneLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "canNotDone");
	mStateContainer->addChild(canNotDoneLabel);
}

void SceneBoss::refreshStateList()
{

}

void SceneBoss::refreshKillerList()
{

}

void SceneBoss::onList( CCObject *target )
{
	const int index = mBossList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
		refresh();
	}
}

void SceneBoss::onKiller( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int pid = node->getTag();
	}
}

void SceneBoss::onAutoMove( CCObject *target )
{
	int mapID = 0, x = 0, y = 0;
	ActivityPanelHelper::getBossMap(ActivityView::scene_boss, mCurrentIndex, mapID, x, y);
	if (mapID > 0 &&
		x > 0 &&
		y > 0)
	{
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->startAutoMoveToCrossMap(mapID, x, y, GHOST_TYPE_MONSTER);
	}
}

void SceneBoss::onTeleport( CCObject *target )
{
	const int activityID = ActivityPanelHelper::getActivityID(ActivityView::scene_boss, mCurrentIndex);
	SceneHelper::teleportToActivityBoss(activityID);
}

void SceneBoss::onReward( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		ItemTooltip *tips = ItemTooltip::create();
		tips->setTooltipContentbysid(node->getTag());
		tips->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemTips"));
		addChild(tips);
	}
}

void SceneBoss::addListItem( int index )
{
	CCNode *norm = CCNode::create();
	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "listSel");
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
	item->setTarget(this, menu_selector(SceneBoss::onList));
	mBossList->addItem(item);

	const int ox = LayoutData::getInt(CPModuleName::ACTIVITY, "listTextOx");
	const int y = sel->getContentSize().height/2;
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "worldBossTitle0");
	nameLabel->setString(ActivityPanelHelper::getActivityName(ActivityView::scene_boss, index).c_str());
	nameLabel->setPositionX(nameLabel->getPositionX() + ox);
	nameLabel->setPositionY(y);
	item->addChild(nameLabel);

	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "worldBossTitle1");
	levelLabel->setString(ActivityPanelHelper::getBossLevelAndGrow(ActivityView::scene_boss, index).c_str());
	levelLabel->setPositionX(levelLabel->getPositionX() + ox);
	levelLabel->setPositionY(y);
	item->addChild(levelLabel);

	CCLabelTTF *growExpLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "worldBossTitle2");
	growExpLabel->setString(ActivityPanelHelper::getBossGrowExp(ActivityView::scene_boss, index).c_str());
	growExpLabel->setPositionX(growExpLabel->getPositionX() + ox);
	growExpLabel->setPositionY(y);
	item->addChild(growExpLabel);

	ccColor3B stateColor;
	const std::string &stateStr = ActivityPanelHelper::getActivityState(ActivityView::scene_boss, index, stateColor);
	CCLabelTTF *stateLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "worldBossTitle3");
	stateLabel->setString(stateStr.c_str());
	stateLabel->setColor(stateColor);
	stateLabel->setPositionX(stateLabel->getPositionX() + ox);
	stateLabel->setPositionY(y);
	item->addChild(stateLabel);
	mStateLabelMap[index] = stateLabel;

	int pid = 0;
	const std::string &killerName = ActivityPanelHelper::getKillerName(ActivityView::scene_boss, index, pid);
	CCMenu *killNameMenu = CCMenu::create();
	killNameMenu->setPosition(CCPointZero);
	item->addChild(killNameMenu);

	CCLabelTTF *killerNameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "worldBossTitle4");
	killerNameLabel->setString(killerName.c_str());

	CCMenuItem *killNameBtn = CCMenuItem::create();
	killNameBtn->setContentSize(killerNameLabel->getContentSize());
	killNameBtn->setTarget(this, menu_selector(SceneBoss::onKiller));
	killNameBtn->setPositionX(killerNameLabel->getPositionX() + ox);
	killNameBtn->setPositionY(y);
	killNameMenu->addChild(killNameBtn, 0, pid);

	killerNameLabel->setAnchorPoint(CCPointZero);
	killerNameLabel->setPosition(CCPointZero);
	killNameBtn->addChild(killerNameLabel);
	mKillerNameMap[index] = killerNameLabel;
}

void SceneBoss::addListFinish()
{
	refresh();
	const int count = ActivityPanelHelper::getActivityCount(ActivityView::scene_boss);
	if (count > 0)
	{
		mBossList->setPercent(mCurrentIndex * 100 / count);
		runAction(CCSequence::create(
			CCDelayTime::create(0.1f),
			CCCallFunc::create(this, callfunc_selector(SceneBoss::setStartIndexSel)),
			NULL));
	}
}

void SceneBoss::setStartIndexSel()
{
	mBossList->setCurrentIndex(mCurrentIndex);
}

void SceneBoss::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_CHANGE)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageSyncEventStateNotify")
		{
			refreshStateList();
		}
	}
}

/////////WeekActivity///////////////////////////////////////////////////
WeekActivity::WeekActivity()
	:mActivityList(NULL)
	,mRewardList(NULL)
	,mDescContainer(NULL)
	,mStateContainer(NULL)
	,mChecker(NULL)
	,mCurrentIndex(0)
{

}

WeekActivity::~WeekActivity()
{

}

bool WeekActivity::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initUI();
	refresh();

	return true;
}

void WeekActivity::onEnter()
{
	CCLayer::onEnter();
}

void WeekActivity::initUI()
{
	// title label
	char ch[32];
	const int titleCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "timeActivityTitleCnt");
	for (int i = 0; i < titleCnt; i++)
	{
		sprintf(ch, "timeActivityTitle%d", i);
		CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, ch);
		addChild(titleLabel);
	}

	// activity list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemList");
	mActivityList = CPItemComponents::create(listSize, new CPLayoutList());
	mActivityList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemList"));
	addChild(mActivityList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "itemScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mActivityList->setScrollbar(scrollBar);

	CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(WeekActivity::addListItem));
	updater->setUpdateTimes(ActivityPanelHelper::getActivityCount(ActivityView::week_activity));
	updater->setFinishHandler(this, callfunc_selector(WeekActivity::addListFinish));
	addChild(updater);
	updater->start();

	// desc
	mDescContainer = CCNode::create();
	addChild(mDescContainer);

	// reward list
	const int cntPerLine = LayoutData::getInt(CPModuleName::ACTIVITY, "rewardPerLine");
	const CCSize &rewardListSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardList");
	const CCSize &rewardItemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardItem");
	mRewardList = CPItemComponents::create(rewardListSize, new CPLayoutGrid(cntPerLine, rewardItemSize, true));
	mRewardList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "rewardList"));
	addChild(mRewardList);

	const CCSize &rewardBarSize = LayoutData::getSize(CPModuleName::ACTIVITY, "rewardScroll");
	CPScrollbar *rewardBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), rewardBarSize);
	mRewardList->setScrollbar(rewardBar);

	// state
	mStateContainer = CCNode::create();
	addChild(mStateContainer);
}

void WeekActivity::refresh()
{
	refreshDesc();
	refreshReward();
	refreshState();
}

void WeekActivity::refreshDesc()
{
	mDescContainer->removeAllChildrenWithCleanup(true);

	//
	int npcID = 0;
	const std::string &npcName = ActivityPanelHelper::getActivityNPC(ActivityView::week_activity, mCurrentIndex, npcID);

	CCSprite *npcBoard = LayoutData::getSprite(CPModuleName::ACTIVITY, "npcBoard");
	npcBoard->setScale(0.5f);
	mDescContainer->addChild(npcBoard);

	CCLabelTTF *npcNameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "activityNPC");
	mDescContainer->addChild(npcNameLabel);

	CCMenu *npcMenu = CCMenu::create();
	npcMenu->setPosition(CCPointZero);
	mDescContainer->addChild(npcMenu);

	CCMenuItemFont *npcNameBtn = LayoutData::getMenuItemFont(CPModuleName::ACTIVITY, "npcName");
	npcNameBtn->setTarget(this, menu_selector(WeekActivity::onAutoMove));
	npcNameBtn->setString(npcName.c_str());
	npcMenu->addChild(npcNameBtn, 0, npcID);

	CCMenuItemImage *teleportBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "teleport");
	teleportBtn->setTarget(this, menu_selector(WeekActivity::onTeleport));
	teleportBtn->setScale(0.6f);
	npcMenu->addChild(teleportBtn, 0, npcID);

	// desc list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "descList");
	CPItemComponents *descList = CPItemComponents::create(listSize, new CPLayoutList());
	descList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "descList"));
	mDescContainer->addChild(descList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "descScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	descList->setScrollbar(scrollBar);

	const std::string &desc = ActivityPanelHelper::getActivityDesc(ActivityView::week_activity, mCurrentIndex);
	const int fontSize = LayoutData::getInt(CPModuleName::ACTIVITY, "activityDescFontSize");
	const int descWidth = LayoutData::getInt(CPModuleName::ACTIVITY, "activityDescWidth");
	CPRichText *descNode = RichTextUtils::getRichText(desc, fontSize, descWidth, 0);
	descList->addItem(descNode);
}

void WeekActivity::refreshReward()
{
	mRewardList->removeAllItems();

	int sid = 0;
	const int rewardCnt = ActivityPanelHelper::getActivityRewardCnt(ActivityView::week_activity, mCurrentIndex);
	for (int i = 0; i < rewardCnt; i++)
	{
		CCSprite *icon = ActivityPanelHelper::getActivityRewardIcon(ActivityView::week_activity, mCurrentIndex, i, sid);
		if (icon)
		{
			CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid");
			item->setTarget(this, menu_selector(WeekActivity::onReward));
			mRewardList->addItem(item);
			item->setTag(sid);

			const CCSize &size = item->getContentSize();
			icon->setPosition(ccp(size.width/2, size.height/2));
			item->addChild(icon);
		}
	}
}

void WeekActivity::refreshState()
{
	mStateContainer->removeAllChildrenWithCleanup(true);
	CCLabelTTF *canNotDoneLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "canNotDone");
	mStateContainer->addChild(canNotDoneLabel);
}

void WeekActivity::refreshStateList()
{
	ccColor3B color;
	LabelMap::iterator it = mStateLabelMap.begin();
	LabelMap::iterator itEnd = mStateLabelMap.end();
	while (it != itEnd)
	{
		CCLabelTTF *label = it->second;
		if (label)
		{
			const std::string &str = ActivityPanelHelper::getActivityState(ActivityView::week_activity, it->first, color);
			label->setString(str.c_str());
			label->setColor(color);
		}
		it++;
	}
}

void WeekActivity::onList( CCObject *target )
{
	const int index = mActivityList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
		refresh();
	}
}

void WeekActivity::onAutoMove( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int npcID = node->getTag();
		if (npcID > 0)
		{
			SceneHelper::autoMoveToNPC(npcID);
		}
	}
}

void WeekActivity::onTeleport( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int npcID = node->getTag();
		if (npcID > 0)
		{
			SceneHelper::teleportToNPCRequest(npcID);
		}
	}
}

void WeekActivity::onReward( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		ItemTooltip *tips = ItemTooltip::create();
		tips->setTooltipContentbysid(node->getTag());
		tips->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "itemTips"));
		addChild(tips);
	}
}

void WeekActivity::addListItem( int index )
{
	CCNode *norm = CCNode::create();
	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "listSel");
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
	item->setTarget(this, menu_selector(WeekActivity::onList));
	mActivityList->addItem(item);

	const int ox = LayoutData::getInt(CPModuleName::ACTIVITY, "listTextOx");
	const int y = sel->getContentSize().height/2;
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle0");
	nameLabel->setString(ActivityPanelHelper::getActivityName(ActivityView::week_activity, index).c_str());
	nameLabel->setPositionX(nameLabel->getPositionX() + ox);
	nameLabel->setPositionY(y);
	item->addChild(nameLabel);

	CCLabelTTF *timeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle1");
	timeLabel->setString(ActivityPanelHelper::getActivityTime(ActivityView::week_activity, index).c_str());
	timeLabel->setPositionX(timeLabel->getPositionX() + ox);
	timeLabel->setPositionY(y);
	item->addChild(timeLabel);

	CCLabelTTF *rewardLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle2");
	rewardLabel->setString(ActivityPanelHelper::getActivityReward(ActivityView::week_activity, index).c_str());
	rewardLabel->setPositionX(rewardLabel->getPositionX() + ox);
	rewardLabel->setPositionY(y);
	item->addChild(rewardLabel);

	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle3");
	levelLabel->setString(ActivityPanelHelper::getActivityLevel(ActivityView::week_activity, index).c_str());
	levelLabel->setPositionX(levelLabel->getPositionX() + ox);
	levelLabel->setPositionY(y);
	item->addChild(levelLabel);

	ccColor3B stateColor;
	const std::string &stateStr = ActivityPanelHelper::getActivityState(ActivityView::week_activity, index, stateColor);
	CCLabelTTF *stateLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "timeActivityTitle4");
	stateLabel->setString(stateStr.c_str());
	stateLabel->setColor(stateColor);
	stateLabel->setPositionX(stateLabel->getPositionX() + ox);
	stateLabel->setPositionY(y);
	item->addChild(stateLabel);
	mStateLabelMap[index] = stateLabel;
}

void WeekActivity::addListFinish()
{
	mActivityList->setCurrentIndex(mCurrentIndex);
}

void WeekActivity::onCPEvent( const std::string &eventName )
{

}

////////////ActivityPanelHelper///////////////////////////////////////////
CCMenuItem * ActivityPanelHelper::getSwitchItem( int index )
{
	CCScale9Sprite *norm = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "switchNorm");
	CCScale9Sprite *sel = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "switchSel");
	CCNode *normNode = CCNode::create();
	normNode->setContentSize(sel->getContentSize());
	norm->setAnchorPoint(ccp(0, 1));
	norm->setPositionY(sel->getContentSize().height);
	normNode->addChild(norm);
	CCMenuItemSprite *ret = CCMenuItemSprite::create(normNode, sel);

	char ch[16];
	sprintf(ch, "switch%d", index);
	const CCSize &itemSize = normNode->getContentSize();
	CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "switch");
	label->setString(LayoutData::getString(CPModuleName::ACTIVITY, ch).c_str());
	label->setPosition(ccp(itemSize.width/2, itemSize.height/2));
	ret->addChild(label);
	return ret;
}

CCNode * ActivityPanelHelper::getSubPanel( int type )
{
	switch (type)
	{
	case ActivityView::time_activity:
		return TimeActivity::create();
	case ActivityView::daily_dungeon:
		return DailyDungeon::create();
	case ActivityView::day_activity:
		return DayActivity::create();
	case ActivityView::world_boss:
		return WorldBoss::create();
	case ActivityView::scene_boss:
		return SceneBoss::create();
	case ActivityView::week_activity:
		return WeekActivity::create();
	}
	CCLog(">>>Error: ActivityPanelHelper::getSubPanel, unknown type = %d", type);
	return NULL;
}

int ActivityPanelHelper::getActivityCount( int type )
{
	int cnt = 0;
	Lua::instance()->push(type);
	if (Lua::instance()->call("activity_get_activity_cnt", 1, 1) &&
		Lua::instance()->pop(cnt))
	{
		return cnt;
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityCount failed, type = %d", type);
	return 0;
}

int ActivityPanelHelper::getActivityID( int type, int index )
{
	int ret = 0;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("activity_get_activity_id", 2, 1) &&
		Lua::instance()->pop(ret))
	{
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityID failed, type = %d, index = %d", type, index);
	return ret;
}

int ActivityPanelHelper::getActivityIndex( int type, int activityID )
{
	int ret = 0;
	Lua::instance()->push(type);
	Lua::instance()->push(activityID);
	if (Lua::instance()->call("activity_get_activity_index", 2, 1) &&
		Lua::instance()->pop(ret))
	{
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityIndex failed, type = %d, activityID = %d", type, activityID);
	return ret;
}

int ActivityPanelHelper::getActivityType( int activityID )
{
	int ret = 0;
	Lua::instance()->push(activityID);
	if (Lua::instance()->call("activity_get_activity_type", 1, 1) &&
		Lua::instance()->pop(ret))
	{
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityType failed, activityID", activityID);
	return ret;
}

std::string ActivityPanelHelper::getActivityName( int type, int index )
{
	std::string ret;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("activity_get_activity_name", 2, 1) &&
		Lua::instance()->pop_utf8(ret))
	{
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getItemName failed, type = %d, index = %d", type, index);
	return ret;
}

std::string ActivityPanelHelper::getActivityTime( int type, int index )
{
	if (type == ActivityView::day_activity)
	{
		return LayoutData::getString(CPModuleName::ACTIVITY, "allDay");
	}

	int startTime = 0;
	int stopTime = 0;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("activity_get_activity_time", 2, 2) &&
		Lua::instance()->pop(stopTime) &&
		Lua::instance()->pop(startTime))
	{
		std::string ret = StringUtils::timeToString(startTime, TimeType::hm);
		ret += "-" + StringUtils::timeToString(stopTime, TimeType::hm);
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityTime failed, type = %d, index = %d", type, index);
	return "0";
}

std::string ActivityPanelHelper::getActivityReward( int type, int index )
{
	std::string ret;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("activity_get_activity_reward", 2, 1) &&
		Lua::instance()->pop_utf8(ret))
	{
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityReward failed, type = %d, index = %d", type, index);
	return ret;
}

std::string ActivityPanelHelper::getActivityLevel( int type, int index )
{
	int reborn = 0, level = 0;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("activity_get_activity_level", 2, 2) &&
		Lua::instance()->pop(level) &&
		Lua::instance()->pop(reborn))
	{
		if (level < 0)
		{
			level = 0;
		}

		std::string ret;
		if (reborn > 0)
		{
			ret = StringUtils::toString(reborn) + LayoutData::getString(CPModuleName::COMMON, "reborn");
		}
		ret += StringUtils::toString(level);
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityLevel failed, type = %d, index = %d", type, index);
	return "0";
}

std::string ActivityPanelHelper::getActivityState( int type, int index, ccColor3B &color )
{
	switch (type)
	{
	case ActivityView::time_activity:
	case ActivityView::week_activity:
		{
			const int unstartID = ActivityData::getUnstartID();
			const int timeID = index + 1;
			if (timeID >= unstartID)
			{
				color = LayoutData::getColor3(CPModuleName::COMMON, "white");
				return LayoutData::getString(CPModuleName::ACTIVITY, "stateNotBegin");
			}
			else
			{
				const int state = ActivityData::getState(timeID);
				if (state == Activity::Activity_Begin)
				{
					color = LayoutData::getColor3(CPModuleName::COMMON, "green");
					return LayoutData::getString(CPModuleName::ACTIVITY, "stateDoing");
				}
				color = LayoutData::getColor3(CPModuleName::COMMON, "gray");
				return LayoutData::getString(CPModuleName::ACTIVITY, "stateEnd");
			}
		}
	case ActivityView::day_activity:
		{
			color = LayoutData::getColor3(CPModuleName::COMMON, "green");
			return LayoutData::getString(CPModuleName::ACTIVITY, "stateDoing");
		}
	case ActivityView::daily_dungeon:
		{
			color = LayoutData::getColor3(CPModuleName::COMMON, "white");
			return getActivityEnterCount(type, index);
		}
	case ActivityView::world_boss:
	case ActivityView::scene_boss:
		{
			const int activityID = getActivityID(type, index);
			const int state = ActivityData::getWorldBossState(activityID);
			if (state == Activity::boss_is_alive)
			{
				color = LayoutData::getColor3(CPModuleName::COMMON, "green");
				return LayoutData::getString(CPModuleName::ACTIVITY, "stateCome");
			}
			else if (state == Activity::boss_is_disappear)
			{
				color = LayoutData::getColor3(CPModuleName::COMMON, "gray");
				return LayoutData::getString(CPModuleName::ACTIVITY, "stateGone");
			}
			else
			{
				if (ActivityData::getWorldBossKillerPID(activityID) > 0)
				{
					color = LayoutData::getColor3(CPModuleName::COMMON, "gray");
					return LayoutData::getString(CPModuleName::ACTIVITY, "stateKilled");
				}
				color = LayoutData::getColor3(CPModuleName::COMMON, "white");
				return LayoutData::getString(CPModuleName::ACTIVITY, "stateNotCome");
			}
		}
	}
	CCLog(">>>Error: ActivityPanelHelper::getItemState, unknown type = %d", type);
	return "";
}

std::string ActivityPanelHelper::getActivityEnterCount( int type, int index )
{
	int maxCnt = 0;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("activity_get_activity_enter_max", 2, 1) &&
		Lua::instance()->pop(maxCnt))
	{
		const int activityID = getActivityID(type, index);
		const int cnt = ActivityData::getInstanceEnterCount(activityID);
		return StringUtils::toString(cnt) + "/" + StringUtils::toString(maxCnt);
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityEnterCount, unknown type = %d, index = %d", type, index);
	return "";
}

std::string ActivityPanelHelper::getBossLevelAndGrow( int type, int index )
{
	int mid = 0;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("activity_get_boss_id", 2, 1) &&
		Lua::instance()->pop(mid))
	{
		int lvlBase = 0;
		StaticData::getMonsterLevel(mid, lvlBase);
		const int activityID = getActivityID(type, index);
		int add = ActivityData::getWorldBossSID(activityID) - mid;
		if (add < 0)
		{
			add = 0;
		}
		return StringUtils::toString(lvlBase) + "+" + StringUtils::toString(add);
	}
	CCLog(">>>Error: ActivityPanelHelper::getBossLevelAndGrow, unknown type = %d, index", type, index);
	return "";
}

std::string ActivityPanelHelper::getBossGrowExp( int type, int index )
{
	int maxExp = 0;
	Lua::instance()->push(type);
	Lua::instance()->push(index);
	if (Lua::instance()->call("activity_get_boss_max_exp", 2, 1) &&
		Lua::instance()->pop(maxExp))
	{
		const int activityID = getActivityID(type, index);
		const int exp = ActivityData::getWorldBossEXP(activityID);
		return StringUtils::toString(exp) + "/" + StringUtils::toString(maxExp);
	}
	CCLog(">>>Error: ActivityPanelHelper::getBossGrowExp, unknown type = %d", type);
	return "";
}

std::string ActivityPanelHelper::getKillerName( int type, int index, int &pid )
{
	switch (type)
	{
	case ActivityView::world_boss:
	case ActivityView::scene_boss:
		{
			const int activityID = getActivityID(type, index);
			const int state = ActivityData::getWorldBossState(activityID);
			if (state == Activity::boss_is_dead)
			{
				pid = ActivityData::getWorldBossKillerPID(activityID);
				return ActivityData::getWorldBossKillerName(activityID);
			}
			pid = 0;
			return "";
		}
	}
	CCLog(">>>Error: ActivityPanelHelper::getKillerName, unknown type = %d", type);
	return "";
}

std::string ActivityPanelHelper::getActivityNPC( int type, int index, int &npcID )
{
	std::string ret;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("activity_get_activity_npc", 2, 2) &&
		Lua::instance()->pop_utf8(ret) &&
		Lua::instance()->pop(npcID))
	{
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityNPC failed, type = %d, index = %d", type, index);
	return ret;
}

std::string ActivityPanelHelper::getBossMap( int type, int index, int &mapID, int &x, int &y )
{
	std::string ret;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("activity_get_boss_map_id", 2, 4) &&
		Lua::instance()->pop(y) &&
		Lua::instance()->pop(x) &&
		Lua::instance()->pop_utf8(ret) &&
		Lua::instance()->pop(mapID))
	{
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getBossMap failed, type = %d, index = %d", type, index);
	return ret;
}

std::string ActivityPanelHelper::getBossPos( int eventid, int &mapID, int &x, int &y )
{
	std::string ret;
	Lua::instance()->push(eventid);
	if (Lua::instance()->call("activity_get_boss_pos", 1, 3) &&
		Lua::instance()->pop(y) &&
		Lua::instance()->pop(x) &&
		Lua::instance()->pop(mapID))
	{
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getBossPos failed, eventid = %d", eventid);
	return ret;
}

std::string ActivityPanelHelper::getActivityDesc( int type, int index )
{
	std::string ret;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("activity_get_activity_desc", 2, 1) &&
		Lua::instance()->pop_utf8(ret))
	{
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityDesc failed, type = %d, index = %d", type, index);
	return ret;
}

int ActivityPanelHelper::getActivityRewardCnt( int type, int index )
{
	int ret = 0;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("activity_get_activity_reward_cnt", 2, 1) &&
		Lua::instance()->pop(ret))
	{
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityRewardCnt failed, type = %d, index = %d", type, index);
	return ret;
}

CCSprite * ActivityPanelHelper::getActivityRewardIcon( int type, int index, int rewardIndex, int &sid )
{
	CCSprite *ret = NULL;
	Lua::instance()->push(type);
	Lua::instance()->push(index + 1);
	Lua::instance()->push(rewardIndex + 1);
	if (Lua::instance()->call("activity_get_activity_reward_icon", 3, 1) &&
		Lua::instance()->pop(sid))
	{
		return LayoutData::getItemIcon(sid);
	}
	CCLog(">>>Error: ActivityPanelHelper::getActivityRewardIcon failed, type = %d, index = %d, rewardIndex = %d", type, index, rewardIndex);
	return ret;
}

bool ActivityPanelHelper::isTimeActivityVisible( int index )
{
	int ret = 0;
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("get_time_activity_visible", 1, 1) &&
		Lua::instance()->pop(ret))
	{
		return (ret != 0);
	}
	CCLog(">>>Error: ActivityPanelHelper::isTimeActivityVisible failed, index = %d", index);
	return false;
}

int ActivityPanelHelper::getTimeActivityVisibleCnt()
{
	int ret = 0;
	if (Lua::instance()->call("get_time_activity_visible_cnt", 0, 1) &&
		Lua::instance()->pop(ret))
	{
		return ret;
	}
	CCLog(">>>Error: ActivityPanelHelper::getTimeActivityVisibleCnt failed!");
	return 0;
}

int ActivityPanelHelper::getBossLvl( std::string &bossname )
{
	int lvl = 0;
	CPLua->push(bossname);
	if (CPLua->call("g_get_bosslvl_byname", 1, 1)
		&& CPLua->pop(lvl))
	{
		return lvl;
	}
	return 50;
}
