#ifndef __SpiderPanel_PANEL_H__
#define __SpiderPanel_PANEL_H__

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "event/IEventListener.h"
#include "userdata/UserItemData.h"
USING_NS_CC_EXT;


class SpiderPanel : public BasePanel
{
public:
	CREATE_FUNC(SpiderPanel);
	SpiderPanel();
	~SpiderPanel();
	bool init();
	void removeItem();
private:
	void closecallback(CCObject* pSender);

};
//------------------------------------------------------------------------------------------//

class SpiderLeftPanel : public BasePanel
{
public:
	CREATE_FUNC(SpiderLeftPanel);
	SpiderLeftPanel();
	~SpiderLeftPanel();
	bool init();

private:
	void menucallback(CCObject* pSender);
	void updateItemMenu();
	void insertItem(UserItem* p, int n);
	virtual void handleEvent(int channel);
	void itemcallback(CCObject* pSender);

private:
	CCLabelTTF* m_pCurReq1;
	CCLabelTTF* m_pCurReq2;
	CCLabelTTF* m_pCurReqItemCnt;
	CCLabelTTF* m_pYuanBao;
	CCLabelTTF* m_pYuanBaoMoney;
	GeneralMenu* m_pItemMenu;
	bool m_bLock;
	enum MyEnum
	{
		Btn_Left,
		Btn_Right,
		TAG_LOCK,
	};
};

//------------------------------------------------------------------------------------------//


class SpiderRightPanel : public BasePanel
{
public:
	CREATE_FUNC(SpiderRightPanel);
	SpiderRightPanel();
	~SpiderRightPanel();
	bool init();

};
#endif//__SpiderPanel_PANEL_H__