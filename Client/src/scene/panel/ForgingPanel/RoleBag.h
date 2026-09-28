#ifndef _RoleBag_H_
#define _RoleBag_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
USING_NS_CC_EXT;


#define POST_MOVE_POS "postmovepos"

class RoleBag :
	public BasePanel
{
public:
	RoleBag(void);
	~RoleBag(void);
	static RoleBag* create(int type=TAG_SSZB,int itemtype = 0);
	virtual bool init(int type,int itemtype = 0);
	virtual void onEnter();
	virtual void onExit();
	virtual void handleEvent(int channel);

public:
	virtual void menuCallBack(CCObject *pSender);
	virtual void ItemCallBack(CCObject *pSender);
	virtual void updateBag(int Page);
	virtual void updatePage(int tag);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	CC_PROPERTY(CCArray* ,m_pItemArray,ItemArray);//存放物品数组
	CC_PROPERTY(CCMenuItemImage* ,m_pCurrentItem,CurrentItem);//当前选中的装备
	virtual void update(float dt);
	virtual void ItemIsSelect(CCObject *pSender);
	virtual void initItem();
	virtual void addItem(int Page);

	virtual void addAllItem();
private:
	int m_iCurrentPage;//当前页数
	int m_iAllPage;//总页数
	GeneralMenu* m_pMainMenu;//主要Menu
	GeneralMenu* m_pBagMenu;//主要Menu
	CCPoint m_OldPoint;
	bool m_bIsSelectItem;//是否选择中物品
	int m_izOrder;
	int m_iCurrentTypeBag;
	int m_iCurrentVisibleType;//当前背包筛选的类型

	enum TAGBAG
	{
		TAG_LEFT=0,
		TAG_RIGHT,
		TAG_PAGE,

		TAG_SSZB=300,
		TAG_BBWP,
		TAG_CWWP,
	};
};

#endif//_RoleBag_H_