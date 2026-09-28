#ifndef __LowerRightNotificationPanel_h__
#define __LowerRightNotificationPanel_h__

#include "cocos2d.h"

using namespace cocos2d;

class LowerRightNotificationPanel : public CCLayer
{
public:
	LowerRightNotificationPanel();
	~LowerRightNotificationPanel();
	CREATE_FUNC(LowerRightNotificationPanel);
	bool init();
	void onEnter();
	void onExit();

public:
	void showLowerRightNote(CCNode *noteNode);

private:
	void initUI();

private:
	CCLayer *mContainer;
};
#endif //__LowerRightNotificationPanel_h__