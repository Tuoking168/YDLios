#ifndef _SHOPPANEL_H_
#define _SHOPPANEL_H_	

/*
功能：显示商城信息界面
*/
#include <string>
#include <vector>
#include "ext/Basepanel.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CCMenuEx;
class SlideTable;

class ShopPanel :public BasePanel, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
	ShopPanel();
	~ShopPanel();
	bool init();
	void hide();
	CREATE_FUNC(ShopPanel);
	void onEnter();
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
protected:
	void initItemPages(int type);
	void rechargeCallback(CCObject* pSender);
	void itemClicked(CCObject* pSender);
	void handleEvent(int channel);
	void openShop(int type);
	void addListItem(int i );
	void addListFinish();
	void consumeAlertEnable(bool enable);
	void tickCallBack(CCObject* pSender);
	void pageChangeCallBack(CCObject* pSender);
	void setSelectTab(int pTab);
	
	enum ShopPanelOtherTag
	{
		TAG_ITEM_TIPS=-10000,
		TAG_KEYBOARD=-20000,
		TAG_MONEY_NOT_ENOUGH=-30000,
	};
public:
	enum ShopPanelTopTag
	{
		TAG_SHOP_BEST_SELLER=1,
		TAG_SHOP_EQUIP,
		TAG_SHOP_SKILL,
		TAG_SHOP_MEDICINE,
		TAG_SHOP_COMMONLY_USED,
		TAG_SHOP_RARE_TREASURES,
		TAG_SHOP_PERSONALISZED_DRESS,
		TAG_SHOP_COUPON,//liquan
		TAG_SHOP_INTERGRATION,
		TAG_SHOP_MAX,
	};
private:
	CCTableViewEx*	m_pTopMenuView;
	CCTableViewCell* m_pCurCell;
	int				m_nCurType;
	int				m_nFinalBuyCount;
	UserItem		m_clickedItem;
	int				m_curPrice;
	SlideTable*		m_pSlideItems;
	
	CCLabelTTF*		m_pGold;
	CCLabelTTF*		m_pIntegration;
	CCLabelTTF*		m_pCoupon;
	int				m_nCurIndex;

	CPUpdater *	m_updater;

	bool m_consumeAlertEnable;
	CCSprite* m_pTick;
	CCScale9Sprite* pAlertBg;

	int m_Tab;
	int m_ItemID;
	int m_Page;
	bool m_isLoading;
	CCMenuItem* m_SelectItem;
};

#endif//_SHOPPANEL_H_