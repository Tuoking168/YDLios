#ifndef _HWTHpanel_H_
#define _HWTHpanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
USING_NS_CC_EXT;



class HWTHpanel :
	public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	HWTHpanel(void);
	~HWTHpanel(void);
	static HWTHpanel* create();
	virtual bool init(const char* filename);
	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void addItem2(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	virtual void menuCallBack(CCObject *pSender);
private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pBottomList;//底部menu
	UserItem* m_pLeftUserItem;
	UserItem* m_pRightUserItem;
	int m_iHeight;

	enum HWTHTAG
	{
		TAG_UP=0,
		TAG_DOWN,
		TAG_UPGRADE,
		TAG_CHANGEHW,
		TAG_TH,
		TAG_QL,
	};
};


class HWQLpanel :
	public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	HWQLpanel(void);
	~HWQLpanel(void);
	static HWQLpanel* create();
	virtual bool init(const char* filename);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	virtual void menuCallBack(CCObject *pSender);
	void initContent();
private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pBottomList;//底部menu
	int m_iHeight;

	enum HWTHTAG
	{
		TAG_UP=0,
		TAG_DOWN,
		TAG_UPGRADE,
		TAG_CHANGEHW,
		TAG_TH,
		TAG_QL,
	};
};
#endif//_HWTHpanel_H_