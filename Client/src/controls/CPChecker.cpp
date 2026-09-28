#include "CPChecker.h"
#include "cocos2d.h"
#include "CommonModule.h"

#include "userdata/LayoutData.h"

using namespace cocos2d;

#define DT_DEFAULT	6


static CCAction *getCheckerAction()
{
	CCDelayTime *dt = CCDelayTime::create(0.1f);
	CCRotateBy *rb = CCRotateBy::create(0.0f, 30);
	return CCRepeatForever::create(CCSequence::create(dt, rb, NULL));
}

//////////////CPChecker/////////////////////////////////////////////////
CPChecker::CPChecker()
	:mAnim(NULL)
	,mNote(NULL)
	,mHandler(NULL)
	,mHandleFunc(NULL)
{
	
}

CPChecker::~CPChecker()
{

}

CPChecker * CPChecker::create()
{
	CPChecker *ret = new CPChecker;
	if(ret && ret->initWithData())
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool CPChecker::initWithData()
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(false);

	initUI();

	return true;
}

void CPChecker::initUI()
{
	// anim
	mAnim = LayoutData::getSprite(CPModuleName::COMMON, "wait");
	mAnim->setVisible(false);
	addChild(mAnim);

	// note
	mNote = LayoutData::getLabelTTF(CPModuleName::COMMON, "waitNote");
	mNote->setVisible(false);
	addChild(mNote);
}

void CPChecker::onEnter()
{
	CCLayer::onEnter();
	mAnim->runAction(getCheckerAction());
}

void CPChecker::onExit()
{
	stop();
	CCLayer::onExit();
}

void CPChecker::start( float dt, const std::string &note )
{
	if (!mAnim->isVisible())
	{
		setTouchEnabled(true);
		mAnim->stopAllActions();
		mAnim->runAction(getCheckerAction());
		mAnim->setVisible(true);
		mNote->setString(note.c_str());
		mNote->setVisible(true);
		scheduleOnce(schedule_selector(CPChecker::endCheck), dt);
	}
}

void CPChecker::start( const std::string &note )
{
	start(DT_DEFAULT, note);
}

void CPChecker::start( float dt )
{
	start(dt, "");
}

void CPChecker::start()
{
	start(DT_DEFAULT, "");
}

void CPChecker::stop()
{
	if (mAnim->isVisible())
	{
		unschedule(schedule_selector(CPChecker::endCheck));
		mAnim->stopAllActions();
		mAnim->setVisible(false);
		mNote->setVisible(false);
		setTouchEnabled(false);
	}
}

void CPChecker::setTimeOutHandler( cocos2d::CCObject *target, cocos2d::SEL_CallFunc func )
{
	mHandler = target;
	mHandleFunc = func;
}

void CPChecker::endCheck( float dt )
{
	CCLog(">>>CPChecker: time out !");
	stop();
	if (mHandler && mHandleFunc)
	{
		(mHandler->*mHandleFunc)();
	}
}

bool CPChecker::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);
	return true;
}

void CPChecker::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 2 * kCCMenuHandlerPriority, true);
}

