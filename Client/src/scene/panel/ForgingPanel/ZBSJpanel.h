#ifndef _ZBSJpanel_H_
#define _ZBSJpanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
#include "controls/CPCheckBox.h"

USING_NS_CC_EXT;

class ZBSJpanel :
	public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	ZBSJpanel(void);
	~ZBSJpanel(void);
	static ZBSJpanel* create();
	virtual bool init(const char* filename);
	virtual void handleEvent(int channel);
	virtual void onEnter();
	virtual void onExit();

	virtual void addItem(UserItem* pUserItem);
	virtual void removeItem();
	virtual void ItemCallBack(CCObject* pSender);
	virtual void addRebornItemReq(UserItem* pUserItem);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	virtual void menuCallBack(CCObject *pSender);
	virtual void SelectPos(CCObject *pObject);
	void initContent();
	
private:
	// 冷却时间相关方法
	void updateTimer(float dt);		// 计时器更新
	int m_iTimeSpan;				// 升级按钮冷却时间（秒）

private:
	GeneralMenu* m_pTopList;		// 顶部menu
	GeneralMenu* m_pBottomList;		// 底部menu
	CCLabelTTF *m_pMoney;			// 金币标签
	CCLabelTTF *m_pYuanBao;			// 元宝标签
	CCLabelTTF *m_pYuanBaoMoney;	// 元宝数量标签
	CCLabelTTF *m_pReqLevel;		// 需求等级标签
	UserItem * m_pUserItem;			// 用户物品
	CCSprite* m_pRebornReq;			// 重生需求图标
	CCLabelTTF *m_pRebornName;		// 重生名称标签
	CPCheckBox* m_plock;			// 锁定复选框
	bool m_bLock;					// 锁定状态
	bool m_bEnoughCL;				// 是否足够材料
	int m_iHeight;					// 高度

	enum ZBSJTAG
	{
		TAG_UP=0,		// 向上按钮
		TAG_DOWN,		// 向下按钮
		TAG_UPGRADE,	// 升级按钮
		TAG_LOCK,		// 锁定按钮
	};
};

#endif//_ZBSJpanel_H_
