#ifndef __LuckyCircle_H__
#define __LuckyCircle_H__

#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "ext/PartPanel.h"
#include "userdata/UserItemData.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "event/IEventListener.h"
#include "CCObject.h"
USING_NS_CC_EXT;

class LuckyCircle : public PartPanel , public IEventListener
{
public:
	LuckyCircle();
	~LuckyCircle();
	virtual bool init();
	CREATE_FUNC(LuckyCircle);

private:
	void initUI();
	void initButton();
	void initLabel();
	void initItems();

	void closecallback(CCObject* target);
	void menuCallBack(CCObject* target);
	void itemClickCallBack(CCObject* target);
	void startCircle();
	void Update(float dt);
	void showGetTip();
	bool checkIfCanStart();
	void func_locate();
	void showStop();

	virtual void onCPEvent(const std::string &eventName);

	GeneralMenu* menu;
	CCSprite* circlezhizhen;
	CCNode*	  m_pRotateNode;//用来存放所有可以旋转的内容
	CCMenuItemImage* startBtn;
	CCLabelTTF *goldLab;
	CCLabelTTF *timesLab;
	CCActionInterval* actionBy;

	int lotteryTimes;
	int yuanBao;
	int m_iTimeSpan;
	int m_id_pos;
	int circlespendGold;
	int circleEctraspendGold;
};

class LuckyCircleHelper
{

};

#endif