#ifndef _ZSDZpanel_H_
#define _ZSDZpanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "scene/panel/ForgingPanel/EquipBasepanel.h"

USING_NS_CC_EXT;

class CPCheckBox;

class ZSDZpanel :
	public EquipBasepanel
{
public:
	ZSDZpanel(void);
	~ZSDZpanel(void);
	static ZSDZpanel* create();
	virtual bool init(const char* filename);
	virtual void onEnter();
	void removeItem();

public:
	virtual void menuCallBack(CCObject *pSender);
	void initContent();

	virtual void addItem(UserItem* pUserItem);
	
private:
	// 冷却时间相关方法
	void updateTimer(float dt);		// 计时器更新
	int m_iTimeSpan;				// 升级按钮冷却时间（秒）

private:
	GeneralMenu* m_pTopList;		// 顶部menu
	GeneralMenu* m_pBottomList;		// 底部menu
	UserItem * m_pSecondItem;		// 第二个物品
	CCLabelTTF* m_pExtraMoney;		// 额外金钱标签
	CPCheckBox* m_plock;			// 锁定复选框
	int m_Vcoin;					// 虚拟币数量

	enum ZSDZTAG
	{
		TAG_UP=0,		// 向上按钮
		TAG_DOWN,		// 向下按钮
		TAG_DZ,			// 升级按钮
	};
};

#endif//_ZSDZpanel_H_
