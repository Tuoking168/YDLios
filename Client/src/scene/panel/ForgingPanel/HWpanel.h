#ifndef _HWpanel_H_
#define _HWpanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "CCObject.h"
#include "ForgingMainPanel.h"
#include "CCTabelViewEx.h"
#include "scene/panel/ForgingPanel/EquipBasepanel.h"
#include "controls/CPCheckBox.h"
USING_NS_CC_EXT;


class HWpanel :
	public BasePanel
{
public:
	HWpanel(void);
	~HWpanel(void);
	static HWpanel* create(int tag=TAG_HWTH);
	virtual bool init(int tag);
	virtual void handleEvent(int channel);


	void addItem(UserItem* pUserItem);

	void removeItem();
	void onEnter();

	void onCPEvent(const std::string &eventName);
	void addSubPanel(int tag);


	void initTopBtn(int tag);

protected:
	
public:
	virtual void menuCallBack(CCObject *pSender);
private:
	GeneralMenu* m_pTopList;//¶¥²¿menu
	int m_iHeight;
	int m_iCurSubType;
	CCTableViewEx* m_pTableView;
	UserItem* m_pUserItem;

	enum HWTAG
	{

		
		TAG_UPGRADE,
		

	};
};

//-------------------------------------------------------------------------------------------------------------------------------------------//

class HW_THpanel:
	public EquipBasepanel
{
public:
	HW_THpanel(void);
	~HW_THpanel(void);
	CREATE_FUNC(HW_THpanel);
	virtual bool init();

protected:

public:
	virtual void menuCallBack(CCObject* pSender);
	virtual void initContent();
	virtual void addItem(UserItem* pUserItem);
	virtual void removeItem();
	virtual void onEnter();
	void addItem2(UserItem* pUserItem);
	virtual void handleEvent(int channel);

private:
	GeneralMenu* m_pTopList;
	GeneralMenu* m_pbottomList;
	UserItem * m_pUserItem;
	UserItem* m_pLeftUserItem;
	UserItem* m_pRightUserItem;
	int m_iHeight;
	int m_iIsProtect;
	int m_iCurSubType;
	CCLabelTTF *m_pProbability;
	CCLabelTTF *m_pMoney;
	CCLabelTTF *m_pBaoHuFuCount;
	CCMenuItemImage* icon01;
	CCMenuItemImage* icon02;
	CCTableViewEx* m_pTableView;
	

	enum DWTAG
	{
		TAG_UP=0,
		TAG_UPGRADE,
		TAG_LOCK1,
		TAG_LOCK2,
		TAG_BHF,
		TAG_DOWN,
	};

};

//--------------------------------------------------------------------------------------------------------------------------------------------//

class HW_QLpanel:
	public EquipBasepanel
{
public:
	HW_QLpanel(void);
	~HW_QLpanel(void);
	CREATE_FUNC(HW_QLpanel);
	virtual bool init();

	virtual void handleEvent(int channel);


public:
	virtual void menuCallBack(CCObject* pSender);
	virtual void addItem(UserItem* pUserItem);
	virtual void onEnter();
	virtual void initContent();


protected:
	

private:
	void initLabelNum();
	GeneralMenu* m_pTopList;
	GeneralMenu* m_pbottomList;
	int m_iHeight;
	CCScale9Sprite* m_pProgress;
	UserItem* m_pUserItem;
	CPCheckBox* m_plock;
	bool m_bLock;
	CCLabelTTF *m_pMoney;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;
	CCSprite* m_pRebornReq;
	CCLabelTTF* m_pRebornName;
	CCTableViewEx* m_pTableView;

	int m_iCurNum;
	int m_iMaxNum;
	CCLabelTTF* m_pProLabel;

	enum QLTAG
	{
		TAG_UP=0,
		TAG_DOWN,
		TAG_UPGRADE,
		TAG_LOCK,
		TAG_04,
		TAG_05,
	};

};


class ZJ_THpanel:
	public EquipBasepanel
{
public:
	ZJ_THpanel(void);
	~ZJ_THpanel(void);
	CREATE_FUNC(ZJ_THpanel);
	virtual bool init();

protected:

public:
	virtual void menuCallBack(CCObject* pSender);
	virtual void initContent();
	virtual void addItem(UserItem * pUserItem);
	virtual void handleEvent(int channel);
	void addItem2(UserItem* pUserItem);
	void removeItem();

	void onEnter();

private:
	GeneralMenu* m_pTopList;
	GeneralMenu* m_pbottomList;
	UserItem* m_pLeftUserItem;
	UserItem* m_pRightUserItem;
	int m_iHeight;
	CCMenuItemImage* icon01;
	CCMenuItemImage* icon02;
	CCTableViewEx* m_pTableView;

	enum DWTAG
	{
		TAG_00=0,
		TAG_01,
		TAG_02,
		TAG_03,
		TAG_04,
		TAG_05,
	};

};

class ZJ_SJpanel:
	public EquipBasepanel
{
public:
	ZJ_SJpanel(void);
	~ZJ_SJpanel(void);
	CREATE_FUNC(ZJ_SJpanel);
	virtual bool init();


public:
	virtual void menuCallBack(CCObject* pSender);
	virtual	void initContent();
	virtual void addItem(UserItem * pUserItem);
	virtual void onEnter();
	virtual void handleEvent(int channel);

	void initLabelNum();
	void onCPEvent();

protected:

private:
	GeneralMenu* m_pTopList;
	GeneralMenu* m_pbottomList;
	CCScale9Sprite* m_pProgress;
	int m_iHeight;
	int m_iCurNum;
	int m_iMaxNum;
	int yuanBao;
	CCLabelTTF* m_pProLabel;
	CCTableViewEx* m_pTableView;

	CCLabelTTF* m_pMoney;
	CCLabelTTF* m_pYuanBao;
	CCLabelTTF* m_pYuanBaoMoney;

	enum FootSJ
	{
		tag_up = 1 ,
	};
};

#endif