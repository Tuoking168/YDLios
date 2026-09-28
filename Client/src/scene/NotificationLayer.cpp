#include "NotificationLayer.h"
#include "cocos2d.h"
#include "NotificationModule.h"
#include "Event.h"
#include "EffectDefinition.h"
#include "NetworkService.h"
#include "SceneManager.h"
#include "LoginHelper.h"

#include "panel/EffectSprite.h"
#include "panel/guide/GuidePanel.h"

#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/SceneData.h"

#include "ext/CCActionDestroy.h"

#include "controls/CPChecker.h"
#include "controls/CPNodeHelper.h"

#include "logic/TimeManager.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "res/Path.h"
#include "res/CPAnimationManager.h"


#define		TAG_LAST_NOTE_START	1

#define		TAG_MOVE_ACTION		7
#define		TAG_RESET_DELAY_ACTION 127
#define		TAG_DELAY_RUN_ACTION 3

#define		NET_CONNECT_TIME_OUT 30
#define		HIGHT	25
#define		LINE	4


static void showRightNote( CCNode *noteNode, CCNode *containerLayer)
{
	if (!noteNode)
	{
		return;
	}

	int lastTag = 1;

	CCNode *lastNote = NULL;
	if (containerLayer->getChildren())
	{
		lastNote = dynamic_cast<CCNode*>(containerLayer->getChildren()->lastObject());
	}
	if (lastNote)
	{
		lastTag = lastNote->getTag()+1;
		containerLayer->stopActionByTag(TAG_MOVE_ACTION);
		int x = 0, y = 0;
		if (containerLayer->getChildrenCount()>=LINE)
		{
			y = HIGHT*(lastTag-LINE-1);
		}
		else
		{
			y = HIGHT*(lastTag-containerLayer->getChildrenCount()-1);
		}
		CCAction* action = CCMoveTo::create(0.2f, ccp(x, y));
		if (action)
		{
			action->setTag(TAG_MOVE_ACTION);
			containerLayer->runAction(action);
		}
	}
	else
	{
		containerLayer->setPosition(ccp(0, 0));
	}

	noteNode->setScaleX(1.5f);
	noteNode->setAnchorPoint(ccp(0, 0));
	noteNode->setPosition(ccp(0, HIGHT*(LINE+1-lastTag)));
	noteNode->runAction(CCSequence::create(
		CCSpawn::createWithTwoActions(CCFadeIn::create(0.2f), CCScaleTo::create(0.2f, 1.0f)), 
		CCDelayTime::create(3.0f),
		CCFadeOut::create(0.2f),
		CCActionInstantRemoveFromParent::create(),
		NULL));

	containerLayer->addChild(noteNode, 0, lastTag);
}

static void setAllChildrenTag( CCNode *parent, int tag )
{
	if(!parent)
	{
		CCLog(">>>Error: setAllChildrenTag, parent = NULL!");
		return;
	}

	CCArray *children = parent->getChildren();
	if(children && children->count() > 0)
	{
		CCObject *child = NULL;
		CCARRAY_FOREACH(children, child)
		{
			CCNode *node = dynamic_cast<CCNode *>(child);
			if (node)
			{
				node->setTag(tag);
			}
		}
	}
}

//////////NotificationLayer///////////////////////////////////////////
NotificationLayer::NotificationLayer()
	:mContainerTop(NULL)
	,mContainerMidRight(NULL)
	,mChecker(NULL)
	,mTouchAnim(NULL)
	,mRightCornerNote(NULL)
	,mDelayFunc(NULL)
	,mContainerTopFirstChildTag(0)
	,mContainerTopLastChildTag(0)
	,mReconnectGameServerCount(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::NET_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

NotificationLayer::~NotificationLayer()
{
	CPEvtDispatcher.removeEventListener(CPEventName::NET_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool NotificationLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);

	initUI();
	schedule(schedule_selector(NotificationLayer::doUpdate), 1.0f);

	return true;
}

void NotificationLayer::onEnter()
{
	CCLayer::onEnter();
}

void NotificationLayer::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, 3 * kCCMenuHandlerPriority, true);
}

bool NotificationLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pEvent);

#define TOUCH_ANIM_TAG 2
	mTouchAnim->stopActionByTag(TOUCH_ANIM_TAG);
	const CCPoint &pt = convertTouchToNodeSpace(pTouch);
	mTouchAnim->setPosition(pt);

	mTouchAnim->setOpacity(255);
	CCDelayTime *dt = CCDelayTime::create(0.2f);
	CCFadeOut *fo = CCFadeOut::create(0.3f);
	CCAction *action = CCSequence::create(dt, fo, NULL);
	action->setTag(TOUCH_ANIM_TAG);
	mTouchAnim->runAction(action);

	return false;
}

void NotificationLayer::initUI()//通知ui
{
	// guide panel
	GuidePanel *guidePanel = GuidePanel::create();
	addChild(guidePanel);

	// top
	mContainerTop = LayoutData::getScale9Sprite(CPModuleName::NOTIFICATION, "topNoteBoard");
	mContainerTop->setOpacity(0);
	mContainerTop->setPosition(LayoutData::getPoint(CPModuleName::NOTIFICATION, "noteAreaTop"));
	addChild(mContainerTop);

	// mid right
	const CCSize &midRightSize = LayoutData::getSize(CPModuleName::NOTIFICATION, "noteAreaMidRight");
	CCNode *midRightClipping = CPNodeHelper::getClippingNode(midRightSize);
	midRightClipping->setPosition(LayoutData::getPoint(CPModuleName::NOTIFICATION, "noteAreaMidRight"));
	addChild(midRightClipping, 0, 1);

	mContainerMidRight = CCLayer::create();
	midRightClipping->addChild(mContainerMidRight);

	// touch anim
	const std::string &animPath = LayoutData::getString(CPModuleName::NOTIFICATION, "touchAnim");
	mTouchAnim = CCSprite::create();
	mTouchAnim->setVisible(false);
	addChild(mTouchAnim);

	//
	mRightCornerNote = LayoutData::getLabelTTF(CPModuleName::NOTIFICATION, "rightCornerNote");
    if(mRightCornerNote)
	{
        addChild(mRightCornerNote, 0, 1);
	}
}

void NotificationLayer::initChecker()
{
	if (!mChecker)
	{
		mChecker = CPChecker::create();
		mChecker->setTimeOutHandler(this, callfunc_selector(NotificationLayer::onCheckNetStateTimeOut));
		addChild(mChecker);
	}
}

void NotificationLayer::showTopNote( cocos2d::CCNode *noteNode )
{
	if (mContainerTopLastChildTag == mContainerTopFirstChildTag &&
		mContainerTopFirstChildTag == 0)
	{
		noteNode->setScale(1.5f);
		noteNode->setVisible(true);
		mContainerTopFirstChildTag++;
		noteNode->runAction(getTopAction());
		mContainerTop->runAction(CCFadeIn::create(0.5f));
		adjustTopBoard(noteNode->getContentSize());

		const CCSize &topSize = mContainerTop->getContentSize();
		noteNode->setPosition(ccp(topSize.width/2, topSize.height/2));
	}
	else
	{
		noteNode->setVisible(false);
	}
	mContainerTopLastChildTag++;
	noteNode->setTag(mContainerTopLastChildTag);
	mContainerTop->addChild(noteNode);
}

void NotificationLayer::showTopNext()
{
	mContainerTop->removeChildByTag(mContainerTopFirstChildTag++);

	if (mContainerTopFirstChildTag<=mContainerTopLastChildTag)
	{
		CCNode* note = mContainerTop->getChildByTag(mContainerTopFirstChildTag);
		if (note)
		{
			note->setScale(1.5f);
			note->setVisible(true);
			note->runAction(getTopAction());
			adjustTopBoard(note->getContentSize());

			const CCSize &topSize = mContainerTop->getContentSize();
			note->setPosition(ccp(topSize.width/2, topSize.height/2));
		}
	}
	else
	{
		mContainerTop->runAction(CCFadeOut::create(0.5f));
		mContainerTopLastChildTag = 0;
		mContainerTopFirstChildTag = 0;
	}
}

CCAction* NotificationLayer::getTopAction()
{
	float dt = 5.0f;
	if (mContainerTopLastChildTag>=8)
	{
		dt = 1.0f;
	}
	else if (mContainerTopLastChildTag>=4)
	{
		dt = 3.0f;
	}

	return	CCSequence::create(
		CCSpawn::createWithTwoActions(CCFadeIn::create(0.25f), CCScaleTo::create(0.25f, 1.0f)), 
		CCDelayTime::create(dt),
		CCFadeOut::create(0.5f),
		CCCallFunc::create(this, callfunc_selector(NotificationLayer::showTopNext)),
		NULL
		);
}

void NotificationLayer::adjustTopBoard( const CCSize &targetSize )
{
	const CCSize &baseSize = LayoutData::getSize(CPModuleName::NOTIFICATION, "noteBaseAreaTop");
	mContainerTop->setContentSize(CCSizeMake(baseSize.width, baseSize.height + targetSize.height));
}

void NotificationLayer::showMidRightNote( cocos2d::CCNode *noteNode )
{
	showRightNote(noteNode, mContainerMidRight);
}

void NotificationLayer::showRightCornerNote( const std::string &note )
{
	mRightCornerNote->stopAllActions();
	mRightCornerNote->setString(note.c_str());
	CCShow *show = CCShow::create();
	CCDelayTime *dl = CCDelayTime::create(3.0f);
	CCHide *hide = CCHide::create();
	CCAction *action = CCSequence::create(show, dl, hide, NULL);
	mRightCornerNote->runAction(action);
}

void NotificationLayer::checkNetState()
{
	if (!mChecker)
	{
		initChecker();
	}
	const int state = NetworkService::getNetState();
	if (state != NS_Connected)
	{
		mChecker->start(NET_CONNECT_TIME_OUT, LayoutData::getString(CPModuleName::COMMON, "netConnect"));
	}
}

void NotificationLayer::doUpdate( float dt )
{
	TimeManager::instance().update();
}

void NotificationLayer::onCheckNetStateTimeOut()
{
	backToLogin();
}

void NotificationLayer::handleNetChange( int changeType )
{
	if (!mChecker)
	{
		initChecker();
	}

	switch (changeType)
	{
	case Event::NETWORKBORN:
		{
			mChecker->stop();
			if (GameData::s_game_state == GAME_STATE_RUNNING)
			{
				reenterGameServer();
			}
			break;
		}
	case Event::NETWORKBROKEN:
		{
			checkNetState();
			break;
		}
	case Event::NETWORKNOTREADY:
		{
			checkNetState();
			break;
		}
	case Event::NETWORKALIVE:
		{
			break;
		}
	}
}

void NotificationLayer::reenterGameServer()
{
	static const int RETRY_COUNT_MAX = 3;
	CCLog(">>>NotificationLayer::reenterGameServer: %d/%d", mReconnectGameServerCount, RETRY_COUNT_MAX);
	if (mReconnectGameServerCount >= RETRY_COUNT_MAX)
	{
		backToLogin();
		return;
	}

	LoginHelper::enterServerRequest();
	LoginHelper::enterCrossServerRequest();
	mReconnectGameServerCount++;

	stopActionByTag(TAG_RESET_DELAY_ACTION);
	CCAction *action = CCSequence::create(
		CCDelayTime::create(5.0f)
		, CCCallFunc::create(this, callfunc_selector(NotificationLayer::resetReconnectCount))
		, NULL);
	action->setTag(TAG_RESET_DELAY_ACTION);
	runAction(action);
}

void NotificationLayer::backToLogin()
{
	SceneManager::switchToLogin();
	resetReconnectCount();
}

void NotificationLayer::resetReconnectCount()
{
	stopActionByTag(TAG_RESET_DELAY_ACTION);
	mReconnectGameServerCount = 0;
}

void NotificationLayer::delayRun( float dt, VoidCallBack func )
{
	if (func)
	{
		mDelayFunc = func;
		
		stopActionByTag(TAG_DELAY_RUN_ACTION);
		CCAction *action = CCSequence::create(CCDelayTime::create(dt)
			, CCCallFunc::create(this, callfunc_selector(NotificationLayer::onExecuteRun))
			, NULL);
		action->setTag(TAG_DELAY_RUN_ACTION);
		runAction(action);
	}
}

void NotificationLayer::onExecuteRun()
{
	if (mDelayFunc)
	{
		mDelayFunc();
		mDelayFunc = NULL;
	}
}

void NotificationLayer::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::NET_CHANGE)
	{
		const int &changeType = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
		handleNetChange(changeType);
	}
	else if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageEnterServerResponse")
		{
			if (GameData::s_game_state == GAME_STATE_RUNNING)
			{
				if (CPEventHelper::isRequestSuccess())
				{
					GameData::s_user->enterGameRequest();
				}
				else
				{
					backToLogin();
				}
			}
		}
	}
}
