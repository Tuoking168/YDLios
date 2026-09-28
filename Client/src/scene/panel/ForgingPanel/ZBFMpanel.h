#ifndef __ZBFMpanel_H__
#define __ZBFMpanel_H__	

#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
#include "controls/CPCheckBox.h"
#include "ext/CCTabelViewEx.h"
#include "scene/panel/ForgingPanel/ForgingMainPanel.h"
USING_NS_CC_EXT;


// Modify By Tony. 2014/12/3 14:37
// 装备附魔主界面;
class ZBFMMainpanel :
	public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	ZBFMMainpanel(void);
	~ZBFMMainpanel(void);
	static ZBFMMainpanel* create(int tag=TAG_PTQH);
	virtual bool init(int tag);
	virtual void onEnter();
	virtual void onExit();

	virtual void addItem(UserItem* pUserItem);
	virtual void removeItem();
	void addSubPanel( int tag );

	virtual void handleEvent(int channel);

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
	void initTopBtn(int tag);
private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pBottomList;//底部menu
	int m_iHeight;
	CCTableViewEx* m_pTabelView;
	int m_iCurSubType;
	UserItem * m_pUserItem;
};

// Modify By Tony. 2014/12/3 14:41
// 装备附魔
class ZBFMpanel :
	public BasePanel
{
public:
	ZBFMpanel(void);
	~ZBFMpanel(void);
	static ZBFMpanel* create();
	virtual bool init(const char* filename);

	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);

	virtual void menuCallBack(CCObject *pSender);
	void postFumoMsg(int i);
private:
	GeneralMenu* m_pTopList;//顶部menu
	UserItem * m_pUserItem;
	int m_iEnhanceType;
	CCLabelTTF *m_pMoney;
	bool m_bLock1;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;

	enum ZBFMTAG
	{
		TAG_UP=0,
		TAG_DOWN,
		TAG_FUMO,
		TAG_YULAN,
		TAG_YBDT,
	};
};


// Modify By Tony. 2014/12/3 14:47
// 附魔强化
class FMQHpanel :
	public BasePanel
{
public:
	FMQHpanel(void);
	~FMQHpanel(void);
	static FMQHpanel* create();
	virtual bool init(const char* filename);

	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);

	virtual void menuCallBack(CCObject *pSender);
	CCMenuItemImage* getFMFIcon();
private:
	void initLabelNum();

	GeneralMenu* m_pTopList;//顶部menu
	UserItem * m_pUserItem;
	int m_iEnhanceType;
	CCLabelTTF *m_pMoney;
	bool m_bLock;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;
	CCLabelTTF *m_pLabelXYJPFMFSL;
	CCLabelTTF *m_pLabelFMFCount;
	CCScale9Sprite* m_pProgress;

	int m_iCurNum;
	int m_iMaxNum;
	CCLabelTTF* m_pProLabel;

	CPCheckBox *m_pCheckJPFM;
	CPCheckBox *m_pCheckYBDT;

	enum FMQHTAG
	{
		TAG_UP=0,
		TAG_DOWN,
		TAG_FMQH,
		TAG_JPFM,
		TAG_YBDT,
		TAG_FMF,
		TAG_YULAN,
	};
};


#endif//__ZBFMpanel_H__