#ifndef __WelcomeScene_h__
#define __WelcomeScene_h__

#include "cocos2d.h"


using namespace cocos2d;

class WelcomeScene : public cocos2d::CCLayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	virtual void onEnter();

    // implement the "static node()" method manually
    CREATE_FUNC(WelcomeScene);

private:
	void initUI();
	void doLoad();
	void loadingOut();
};

#endif  // __WelcomeScene_h__