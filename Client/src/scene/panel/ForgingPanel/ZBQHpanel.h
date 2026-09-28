#ifndef _ZBQHpanel_H_
#define _ZBQHpanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
#include "ext/CCTabelViewEx.h"
#include "scene/panel/ForgingPanel/ForgingMainPanel.h"

USING_NS_CC_EXT;

class ZBQHpanel :
	public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	ZBQHpanel(void);
	~ZBQHpanel(void);
	static ZBQHpanel* create(int tag=TAG_PTQH);
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

//-----------------------------------------------------------------------------------------------------------------------------//

class WMQHpanel :
	public BasePanel
{
public:
	WMQHpanel(void);
	~WMQHpanel(void);
	static WMQHpanel* create(int tag=40125);
	virtual bool init(int tag);
	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);

	virtual void menuCallBack(CCObject *pSender);
	virtual void addReqItem(UserItem* pUserItem);
	virtual void addReqItem(int sid);

protected:

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pReqMenu;//顶部menu
	UserItem * m_pUserItem;
	int m_iEnhanceType;
	CCLabelTTF *m_pMoney;
	bool m_bLock;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;
	CCLabelTTF* m_pCurrentItem;
	int m_iCurBHFType;
	int m_icurReqItem;
	enum ZBQHTAG
	{
		TAG_UPGRADE,
		TAG_LOCK,
		TAG_LIST,
		TAG_LISTPANEL,
	};
};

//-----------------------------------------------------------------------------------------------------------------------------//

class PTQHpanel :
	public BasePanel
{
public:
	PTQHpanel(void);
	~PTQHpanel(void);
	static PTQHpanel* create();
	virtual bool init(const char* filename);

	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);

	virtual void menuCallBack(CCObject *pSender);
	CCMenuItemImage* getBaoHuIcon();
private:
	GeneralMenu* m_pTopList;//顶部menu
	UserItem * m_pUserItem;
	int m_iEnhanceType;
	int m_iIsProtect;
	CCLabelTTF *m_pMoney;
	CCLabelTTF *m_pProbability;
	bool m_bLock1;
	bool m_bLock2;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;
	CCLabelTTF *m_pBaoHuFu;
	CCLabelTTF *m_pBaoHuFuCount;

	CCMenuItemImage * m_pBaoHuIcon;

	enum ZBQHTAG
	{
		TAG_UP=0,
		TAG_DOWN,
		TAG_UPGRADE,
		TAG_LOCK1,
		TAG_LOCK2,
		TAG_BHF,
	};
};


//-----------------------------------------------------------------------------------------------------------------------------//

class QHDMpanel :
	public BasePanel
{
public:
	QHDMpanel(void);
	~QHDMpanel(void);
	static QHDMpanel* create();
	virtual bool init(const char* filename);

	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);

	virtual void menuCallBack(CCObject *pSender);
	
private:
	// 冷却时间相关方法
	void updateTimer(float dt);		// 计时器更新
	int m_iTimeSpan;				// 升级按钮冷却时间（秒）
	
	void initLabelNum();

	GeneralMenu* m_pTopList;//顶部menu
	UserItem * m_pUserItem;
	int m_iEnhanceType;
	CCLabelTTF *m_pMoney;
	bool m_bLock;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;
	CCScale9Sprite* m_pProgress;

	int m_iCurNum;
	int m_iMaxNum;
	CCLabelTTF* m_pProLabel;

	enum ZBQHTAG
	{
		TAG_UP=0,
		TAG_DOWN,
		TAG_UPGRADE,
		TAG_LOCK1,
		TAG_LOCK2,
		TAG_BHF,
	};
};


//-----------------------------------------------------------------------------------------------------------------------------//

class CBYHpanel :
	public BasePanel
{
public:
	CBYHpanel(void);
	~CBYHpanel(void);
	static CBYHpanel* create();
	virtual bool init(const char* filename);

	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);

	virtual void menuCallBack(CCObject *pSender);
private:
	void  Refresh();
	GeneralMenu* m_pTopList;//顶部menu
	UserItem * m_pUserItem;
	int m_iEnhanceType;
	CCLabelTTF *m_pMoney;
	CCLabelTTF *m_pProbability;
	bool m_bLock;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;

	CCLabelTTF *pShouldBeSucceed;
	CCLabelTTF *pBDCG;

	enum ZBQHTAG
	{
		TAG_UP=0,
		TAG_DOWN,
		TAG_UPGRADE,
		TAG_LOCK1,
		TAG_LOCK2,
		TAG_BHF,
	};
};
#endif//_ZBQHpanel_H_
