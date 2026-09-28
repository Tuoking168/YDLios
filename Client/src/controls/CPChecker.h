#ifndef __CPChecker_h__
#define __CPChecker_h__

#include "CCLayer.h"
#include "CCLabelTTF.h"
#include <string>

class CPChecker : public cocos2d::CCLayer
{
public:
	CPChecker();
	~CPChecker();

public:
	static CPChecker *create();

	void start(float dt, const std::string &note);
	void start(const std::string &note);
	void start(float dt);
	void start();
	void stop();

	void setTimeOutHandler(cocos2d::CCObject *target, cocos2d::SEL_CallFunc func);

private:
	bool initWithData();
	void initUI();
	void onEnter();
	void onExit();

	void endCheck(float dt);

	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void registerWithTouchDispatcher();

private:
	cocos2d::CCNode *mAnim;
	cocos2d::CCLabelTTF *mNote;
	cocos2d::CCObject *mHandler;
	cocos2d::SEL_CallFunc mHandleFunc;
};
#endif //__CPChecker_h__