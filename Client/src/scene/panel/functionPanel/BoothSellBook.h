#ifndef __BoothsSellBook_H__
#define __BoothsSellBook_H__


#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
#include "ext/CCTabelViewEx.h"
#include "event/IEventListener.h"
#include "userdata/BoothData.h"
USING_NS_CC_EXT;

class BoothSellBook : public BasePanel
{
public:
	BoothSellBook();
	~BoothSellBook();
	CREATE_FUNC(BoothSellBook);

private:
	bool init();
	void initUI();

	void bottonCallBack(CCObject* pSender);
}; 

class SellBook : public CCLayer , public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	SellBook();
	~SellBook();
	CREATE_FUNC(SellBook);
	bool init();
	int getGold();
	int getVcoin();

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	int d_value;
	int m_gold;//jinbi
	int m_vcoin;//yuanbao
	CCTableViewEx*		m_pTableView;
	CCLabelTTF*			m_pBookdesc;
	std::map<int,sellData> sellMap;

	int initMostCnt();

//	void setTimes(int time);
//	void setGold(int gold);
//	void setVcoin(int vcoin);
};

class LeavewordBook : public CCLayer , public CCTableViewDataSource, public CCTableViewDelegate,public IEventListener
{
public:
	LeavewordBook();
	~LeavewordBook();
	CREATE_FUNC(LeavewordBook);
	virtual void    onCPEvent( const std::string &eventName );
	bool init();
	virtual void onEnter();

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	CCTableViewEx*		m_pTableView;
	std::vector<MarketWords> words;

};

#endif