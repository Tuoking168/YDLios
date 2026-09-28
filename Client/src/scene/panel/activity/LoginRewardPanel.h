#ifndef _LoginRewardPanel_H_
#define _LoginRewardPanel_H_	

#include <string>
#include <vector>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/PartPanel.h"
#include "ext/CCTabelViewEx.h"
#include "event/IEventListener.h"
USING_NS_CC_EXT;


class LoginRewardPanel :public PartPanel,public IEventListener, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	LoginRewardPanel();
	~LoginRewardPanel();
	CREATE_FUNC(LoginRewardPanel);
	//static LoginRewardPanel* create();
	bool init();
	virtual void onCPEvent(const std::string &eventName);
	
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

protected:

private:
	void getReward(CCObject* pSender);
	void close(CCObject* pSender);
	void itemClickCallBack(CCObject* pSender);

	CCTableViewEx*		m_pTableView;
};

#endif//_LoginRewardPanel_H_