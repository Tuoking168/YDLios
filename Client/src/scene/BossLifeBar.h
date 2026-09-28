#ifndef __BossLifeBar_h__
#define __BossLifeBar_h__

#include "cocos2d.h"
#include "event/IEventListener.h"

using namespace cocos2d;

class CPProgressBar;
class BossLifeBar : public CCNode, public IEventListener
{
public:
	BossLifeBar();
	~BossLifeBar();
	CREATE_FUNC(BossLifeBar);

	void refresh();

private:
	bool init();
	void onEnter();
	void onExit();

	void initUI();

	void onCPEvent(const std::string &eventName);

private:
	CPProgressBar *mLifeBar;
	CCLabelTTF *mLifeLabel;
};
#endif //__BossLifeBar_h__