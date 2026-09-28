#ifndef _SXZYpanel_H_
#define _SXZYpanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
#include "scene/panel/ForgingPanel/ForgingMainPanel.h"
#include "ext/CCTabelViewEx.h"
#include "event/IEventListener.h"
USING_NS_CC_EXT;

//属性转移（主界面）
class SXZYPanel :
	public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate,public IEventListener
{
public:
	SXZYPanel(void);
	~SXZYPanel(void);
	static SXZYPanel* create(int tag=TAG_JPZY);
	virtual bool init(int tag);
	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);

	void onCPEvent(const std::string &eventName);
	void addSubPanel(int tag);

	void initContent();
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
	int m_iHeight;
	int m_iCurSubType;
	CCTableViewEx* m_pTabelView;
	UserItem* m_pUserItem;

	enum ZBSJTAG
	{
		TAG_UPGRADE,
	};


};

//------------------------------------------------------------------------------------------------------------------------//

//极品属性转移
class JPZYpanel :
	public BasePanel
{
public:
	JPZYpanel(void);
	~JPZYpanel(void);
	static JPZYpanel* create();
	virtual bool init(const char* filename);
	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void addItem2(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);
public:
	virtual void menuCallBack(CCObject *pSender);
private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pBottomList;//底部menu
	UserItem* m_pLeftUserItem;
	UserItem* m_pRightUserItem;
	int m_iHeight;
	bool m_bLock;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;
	CCLabelTTF *m_pMoney;

	enum ZBSJTAG
	{
		TAG_UPGRADE,
		TAG_LOCK,
	};
};

//------------------------------------------------------------------------------------------------------------------------//

//强化属性转移
class QHZYpanel :
	public BasePanel
{
public:
	QHZYpanel(void);
	~QHZYpanel(void);
	static QHZYpanel* create();
	virtual bool init(const char* filename);
	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void addItem2(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);
public:
	virtual void menuCallBack(CCObject *pSender);

private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pBottomList;//底部menu
	UserItem* m_pLeftUserItem;
	UserItem* m_pRightUserItem;
	int m_iHeight;
	bool m_bLock;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;
	CCLabelTTF *m_pMoney;

	enum ZBSJTAG
	{
		TAG_UPGRADE,
		TAG_LOCK,
	};
};

//------------------------------------------------------------------------------------------------------------------------//

//鉴定属性转移
class JDZYpanel :
	public BasePanel
{
public:
	JDZYpanel(void);
	~JDZYpanel(void);
	static JDZYpanel* create();
	virtual bool init(const char* filename);
	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void addItem2(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);
public:
	virtual void menuCallBack(CCObject *pSender);

private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pBottomList;//底部menu
	UserItem* m_pLeftUserItem;
	UserItem* m_pRightUserItem;
	int m_iHeight;
	bool m_bLock;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;
	CCLabelTTF *m_pMoney;

	CCLabelTTF *m_pleftblock[3];
	CCLabelTTF *m_prightblock[3];
	enum ZBSJTAG
	{
		TAG_UPGRADE,
		TAG_LOCK,
	};
};

//------------------------------------------------------------------------------------------------------------------------//

//极品属性清洗
class JPQXpanel :
	public BasePanel
{
public:
	JPQXpanel(void);
	~JPQXpanel(void);
	static JPQXpanel* create();
	virtual bool init(const char* filename);
	virtual void handleEvent(int channel);

	virtual void addItem(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);
public:
	virtual void menuCallBack(CCObject *pSender);

private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pBottomList;//底部menu
	UserItem* m_pUserItem;
	int m_iHeight;
	bool m_bLock;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;
	CCLabelTTF *m_pMoney;

	enum ZBSJTAG
	{
		TAG_UPGRADE,
		TAG_LOCK,
	};
};

#endif//_SXZYpanel_H_