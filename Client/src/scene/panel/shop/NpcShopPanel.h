#ifndef _NPC_SHOPPANEL_H_
#define _NPC_SHOPPANEL_H_	

/*
功能：显示NPC商店信息界面
*/
#include "ext/Basepanel.h"
#include "cocos2d.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"

using namespace cocos2d;

class GeneralMenu;
class CCMenuEx;
class RadioGroup;
class CPItemComponents;

enum NpcShopPanelTag
{
	TAG_NPCSHOP_MEDICINE=10,
	TAG_NPSHOP_GROCERY=11,
	TAG_NPCSHOP_BLACKSMITH=12,
	TAG_NPCSHOP_JEWELERY=13,
	TAG_NPCSHOP_ARMOR=14,
	TAG_NPCSHOP_BOOK=15,
	TAG_NPCSHOP_CARRY=16,
	TAG_NPCSHOP_RECYCLE,
};

enum NpcShopPanelOtherTag
{
	TAG_ITEM_TIPS=-10000,
	TAG_KEYBOARD=-20000,
};

class NpcShopPanel :public BasePanel
{
public:
	NpcShopPanel();
	~NpcShopPanel();

	static	NpcShopPanel* create(int shopid);

private:
	bool init(int shopid);
	void initUI();
	void refreshList();

	void selectTabCallback(CCObject* pSender);
	void itemClicked(CCObject* pSender);
	void rechargeCallback(CCObject* pSender);
	
	void openShopRequest();
	CCMenuItemImage* getItem(int id);

	void addListItem(int i );
	void addListFinish();

	void buyClick(CCObject* pSender);

	void handleEvent(int channel);

	void initTopTab();

	std::string getShopCategory();
private:
	CCMenu*		m_pMenu;
	CPItemComponents *mItemList;

	int				m_nCurType;
	int				m_iCurType;
	int				m_nFinalBuyCount;
	UserItem		m_clickedItem;
	int				m_curPrice;
	bool			m_bIsRepo;

	CPUpdater *	m_updater;
	CCMenuItemImage* m_pCurSelectItem;
	int m_iCurSelectID;

	CCLabelTTF* m_repoNone;
	int		m_iRefreshCnt;
};

#endif//_NPC_SHOPPANEL_H_