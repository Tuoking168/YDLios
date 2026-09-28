#ifndef _HSHCpanel_H_
#define _HSHCpanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

#include "userdata/UserItemData.h"


class HSHC_HSHCpanel :
	public BasePanel
{
public:
	HSHC_HSHCpanel(void);
	~HSHC_HSHCpanel(void);
	static HSHC_HSHCpanel* create();
	virtual bool init(const char* filename);

public:
	virtual void menuCallBack(CCObject *pSender);
	virtual void addItem(UserItem* useritem);
	virtual void ItemCallBack(CCObject* pSender);
	virtual void handleEvent(int channel);

private:
	GeneralMenu* m_pTopList;//顶部menu
	CCLabelTTF* m_pMoney;
	UserItem* m_pUserItem;
	UserItem* m_pTgtItem;

	CCLabelTTF* m_pYuanBaoMoney;
	CCLabelTTF* m_pYuanBao;
	bool m_bLock;

	enum TAG1
	{
		TAG_HC=0,
		TAG_ZH,
		TAG_LOCK,
		TAG_Upgrade,
		TAG_SoulStonePanel,
	};
};






class HSHC_HSZHpanel :
	public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	HSHC_HSZHpanel(void);
	~HSHC_HSZHpanel(void);
	static HSHC_HSZHpanel* create();
	virtual bool init(const char* filename);

public:
	virtual void menuCallBack(CCObject *pSender);
	virtual void ItemCallBack(CCObject* pSender);
	virtual void addItem(UserItem* useritem);
	virtual void handleEvent(int channel);

protected:
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
	CCLabelTTF* m_pMoney;
	bool m_bLock;
	UserItem* m_pUserItem;
	int m_iSelectSid;
	CCSprite* m_pSprite;
	CCLabelTTF* m_pLabel1;
	CCLabelTTF* m_pLabel2;
	int m_iHeight;

	enum TAG2
	{
		TAG_HSZH=0,
		TAG_UP,
		TAG_DOWN,
		TAG_LOCK,
		TAG_HC,
		TAG_ZH,
	};
};

#endif//_HSHCpanel_H_