#ifndef _WPHCpanel_H_
#define _WPHCpanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
USING_NS_CC_EXT;

enum ListType//合成分类
{
	TAG_PerfectEnhance	= -100,
	TAG_LingZhu	= 0,
	TAG_WuPin,
	TAG_ChiBang,
	TAG_MoJingShi,
	TAG_ZhuangBei,
	TAG_JiNengShu,
};

class WPHCpanel :
	public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	WPHCpanel(void);
	~WPHCpanel(void);
	static WPHCpanel* create( int tag=0);
	virtual bool init( int tag=0);

public:
	virtual void menuCallBack(CCObject *pSender);
	virtual void ItemCallBack(CCObject* pSender);
	virtual void handleEvent(int channel);

	void addItem(UserItem* useritem);
	void addtgtItem(UserItem* useritem);

protected:
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pBottomList;
	int m_iCurrentCount;//当前个数
	bool m_bLock;
	CCLabelTTF* m_pMoney;
	CCLabelTTF* m_pYuanBaoMoney;
	CCLabelTTF* m_pYuanBao;
	UserItem* m_pUseritem;
	CCLabelTTF* m_pCurrentItem;
	int m_iTag;
	int m_iHeight;
	CCLabelTTF* m_pJL;

	enum TAG2
	{
		TAG_HSZH=0,
		TAG_UP,
		TAG_DOWN,
		TAG_LEFT,
		TAG_RIGHT,
		TAG_COUNT,
		TAG_LOCK,
		TAG_LIST,
		TAG_LISTPANEL,
	};
};

class HCListpanel :
	public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	HCListpanel(void);
	~HCListpanel(void);
	static HCListpanel* create( int tag=0);
	virtual bool init( int tag=0);

public:
	virtual void menuCallBack(CCObject *pSender);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	int m_iType[20];
	int m_iSize;
	int m_iCurType;
};


#endif//_WPHCpanel_H_