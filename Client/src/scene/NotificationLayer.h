#ifndef __NotificationLayer_h__
#define __NotificationLayer_h__

#include "cocos2d.h"
#include <string>
#include "event/IEventListener.h"
#include "GUI/CCControlExtension/CCScale9Sprite.h"

using namespace cocos2d;

typedef void (*VoidCallBack)();

class CPChecker;
class EffectSprite;
class NotificationLayer : public CCLayer, public IEventListener
{
public:
	NotificationLayer();
	~NotificationLayer();
	CREATE_FUNC(NotificationLayer);

	bool init();
	void onEnter();
	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

public:
	void showTopNote(CCNode *noteNode);
	void showMidRightNote(CCNode *noteNode);
	void showRightCornerNote(const std::string &note);

	void checkNetState();

	void delayRun(float dt, VoidCallBack func);

private:
	void initUI();
	void initChecker();
	void doUpdate(float dt);

	void showTopNext();
	CCAction* getTopAction();
	void adjustTopBoard(const CCSize &targetSize);

	void handleNetChange(int changeType);
	void onCheckNetStateTimeOut();

	void reenterGameServer();
	void backToLogin();

	void resetReconnectCount();

	void onExecuteRun();

	void onCPEvent(const std::string &eventName);

private:
	extension::CCScale9Sprite *mContainerTop;
	short			mContainerTopFirstChildTag;
	short			mContainerTopLastChildTag;
	CCLayer	*mContainerMidRight;
	CPChecker *mChecker;
	CCSprite *mTouchAnim;
	CCLabelTTF *mRightCornerNote;
	VoidCallBack mDelayFunc;

	int mReconnectGameServerCount;
};

#endif  //__NotificationLayer_h__