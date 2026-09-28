#include "ActivityStatePanel.h"
#include "EntityDefinition.h"
#include "ActivityModule.h"
#include "EvtDataDefinition.h"

#include "scene/SceneHelper.h"
#include "scene/panel/FloatPanel.h"

#include "controls/CPItemComponents.h"
#include "controls/CPRichText.h"
#include "controls/CPScrollbar.h"
#include "controls/CPDelayRefresh.h"
#include "controls/CPChecker.h"

#include "userdata/LayoutData.h"
#include "userdata/HeroData.h"
#include "userdata/StaticData.h"
#include "userdata/ActivityData.h"
#include "userdata/SceneData.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "script/LuaWrapper.h"
#include "utils/StringUtils.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"


namespace ActivityStateBuilder
{
	enum
	{
		start = 1,
		doing = 2,
		stop = 3,
	};
}

static void addActivityState()
{
	const int activityID = HeroData::getProp(Entity::attr_event_in);
	int dataX = 0, dataY = 0, dataZ = 0;
	ActivityData::getExData(activityID, dataX, dataY, dataZ);

	Lua::instance()->push(activityID);
	Lua::instance()->push(dataX);
	Lua::instance()->push(dataY);
	Lua::instance()->push(dataZ);
	Lua::instance()->call("activity_build_activity_state", 4, 0);
}

//////////ActivityStatePanel//////////////////////////////////////////////
ActivityStatePanel::ActivityStatePanel()
	:mStateList(NULL)
	,mCurrentText(NULL)
	,mTimeLabel(NULL)
	,mStateRefresh(NULL)
	,mExitBtn(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::LUA_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
}

ActivityStatePanel::~ActivityStatePanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LUA_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
	if (mTimeLabel)
	{
		mTimeLabel->release();
	}
}

bool ActivityStatePanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initUI();
	onRefresh();

	return true;
}

void ActivityStatePanel::onEnter()
{
	CCLayer::onEnter();
	const int curJoinedActivity = HeroData::getProp(Entity::attr_event_in);
	if (curJoinedActivity != EvtData::evt_mnhs)
	{
		if (mExitBtn)
		{
			mExitBtn->setVisible(curJoinedActivity > 0);
		}
	}
}

void ActivityStatePanel::initUI()
{
	// board
	CCScale9Sprite *stateBoard = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "statePanelBoard");
	addChild(stateBoard);

	// title
	CCScale9Sprite *titleBoard = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "statePanelTitleBoard");
	addChild(titleBoard);

	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "statePanelTitle");
	titleBoard->addChild(titleLabel);

	const int nMapID= GameData::getCurrentMap()->mID;
	if (7!= nMapID)//攻城战活动中，玩家是无法通过退出按钮退出活动的。modify by sunbing
	{
		// exit menu
		CCMenu *menu = CCMenu::create();
		menu->setPosition(CCPointZero);
		addChild(menu);
		mExitBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "statePanelExit");
		mExitBtn->setTarget(this, menu_selector(ActivityStatePanel::onExitActivity));
		mExitBtn->setVisible(false);
		menu->addChild(mExitBtn);
	}
	

	// state list
	const CCSize &stateSize = LayoutData::getSize(CPModuleName::ACTIVITY, "statePanelList");
	const CCPoint &statePoint = LayoutData::getPoint(CPModuleName::ACTIVITY, "statePanelList");
	mStateList = CPItemComponents::create(stateSize, new CPLayoutList);
	mStateList->setClickHandler(this, callfunc_selector(ActivityStatePanel::onAutoMove));
	mStateList->setPosition(statePoint);
	addChild(mStateList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "statePanelScrollBar");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mStateList->setScrollbar(scrollBar);

	// state refresh
	mStateRefresh = CPDelayRefresh::create(this, callfunc_selector(ActivityStatePanel::onRefresh));
	addChild(mStateRefresh);

	// time label
	mTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "statePanelTime");
	mTimeLabel->retain();

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void ActivityStatePanel::onRefresh()
{
	mStateList->removeAllItems();
	addActivityState();
}

void ActivityStatePanel::onExitActivity( CCObject *target )
{
	StrVector vect;
	FloatPanel::show(FloatPanelType::Exit_activity_scene, vect, this, floatpanel_selector(ActivityStatePanel::onExitActivity));
}

void ActivityStatePanel::onExitActivity( int btnType )
{
	if (btnType == Button_QD)
	{
		mChecker->start();
		SceneHelper::backToNormalMapRequest();
	}
}

void ActivityStatePanel::refreshTime()
{
	int time = 0;
	if (HeroData::getProp(Entity::attr_event_in) == EvtData::evt_mnhs)
	{
		time = HeroData::getProp(Entity::attr_meinvhusong_remain);
	}
	else
	{
		time = SceneData::getProp("scene_time_remain");
	}
	const std::string &timeString = StringUtils::timeToString(time, TimeType::hms);
	mTimeLabel->setString(timeString.c_str());
}

void ActivityStatePanel::buildDesc()
{
	const int buildType = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
	switch (buildType)
	{
	case ActivityStateBuilder::start:
		{
			const CCSize &stateSize = LayoutData::getSize(CPModuleName::ACTIVITY, "statePanelList");
			mCurrentText = CPRichText::create(stateSize.width, 0);
			break;
		}
	case ActivityStateBuilder::doing:
		{
			if (mCurrentText)
			{
				const std::string &text = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
				const std::string &fontName = "Arial";
				int fontSize = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				int colorID = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
				const ccColor3B &color = LayoutData::getColor3(CPModuleName::ACTIVITY, "statePanelDesc" + StringUtils::toString(colorID));
				mCurrentText->addItem(new CPRichTextItemLabel(text, fontName, fontSize, color));
			}
			break;
		}
	case ActivityStateBuilder::stop:
		{
			if (mStateList && mCurrentText)
			{
				const int isTimeLabel = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				if (isTimeLabel)
				{
					mTimeLabel->removeFromParentAndCleanup(true);
					mCurrentText->addItem(new CPRichTextItemNode(mTimeLabel));
					refreshTime();
				}
				mStateList->addItem(mCurrentText);
			}
			mCurrentText = NULL;
			break;
		}
	default:
		{
			CCLog(">>>Error: ActivityStatePanel::buildDesc, unknown buildType = %d", buildType);
			break;
		}
	}
}

void ActivityStatePanel::onAutoMove()
{
	if (HeroData::getProp(Entity::attr_event_in) == EvtData::evt_mnhs)
	{
		int npcID = 0;
		StaticData::getGlobalData("girlSubmitNPC", npcID);
		SceneHelper::autoMoveToNPC(npcID);
	}
}

void ActivityStatePanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::LUA_CHANGE)
	{
		if (source == "activity_build_activity_state")
		{
			buildDesc();
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if ((Entity::attr_script_start <= type && type <= Entity::attr_script_end) ||
				type == Entity::attr_event_in)
			{
				mStateRefresh->refresh();
				const int curJoinedActivity = HeroData::getProp(Entity::attr_event_in);
				if (curJoinedActivity != EvtData::evt_mnhs)
				{
					if (mExitBtn)
					{
						mExitBtn->setVisible(curJoinedActivity > 0);
					}
				}
			}
		}
		else if(source == "HandleMessageSyncPlayerEventDataNotify")
		{
			const int activityID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (activityID == HeroData::getProp(Entity::attr_event_in))
			{
				mStateRefresh->refresh();
			}
		}
		else if (source == "HandleMessageUpdScenePropsNotify")
		{
			mStateRefresh->refresh();
		}
	}
	else if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageEnterSceneResponse")
		{
			mChecker->stop();
		}
	}
	else if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			refreshTime();
		}
	}
}
