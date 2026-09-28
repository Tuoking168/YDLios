#ifndef _LaunchedFocus_H_
#define _LaunchedFocus_H_	

#include <string>
#include <vector>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/PartPanel.h"
#include "ext/CCTabelViewEx.h"
#include "event/IEventListener.h"
#include "controls/CPItemComponents.h"
USING_NS_CC_EXT;

class LaunchedFocus : public BasePanel,public IEventListener
{
public:
	LaunchedFocus();
	~LaunchedFocus();
	CREATE_FUNC(LaunchedFocus);
	//static LoginRewardPanel* create();
	bool init();
	void initUI();
	void onEnter();
	virtual void onCPEvent(const std::string &eventName);

public:
	

protected:

private:
	void close(CCObject* pSender);
	void onChangeNum(CCObject* pSender);
	void onFindExp(CCObject* pSender);
	void addFlag();
	CCMenuItem *getChooseFindNum(int index);

	CCTableViewEx*		m_pTableView;
	CPItemComponents *mFindExpList;
	int m_sid;
	CCMenuItemSprite* findBtn;
	CCLabelTTF* pTextLabel3;
	CCString* pStr3;
	int mostExp;
};

#endif