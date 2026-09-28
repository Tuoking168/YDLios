#ifndef __BAG_PANEL_H__
#define __BAG_PANEL_H__

// Show bag panel

#include "GeneralMenuListener.h"
#include "CommonPanel.h"
#include "cocos2d.h"
#include "ext/basepanel.h"
#include "event/IEventListener.h"
USING_NS_CC;

struct UserItem;
class PacketPage;
class NetItem;
class CCMenuEx;
class ItemTooltip;

//需要行line，列row，总数count，背包类型SelfBagType，对应界面类型BagType

enum SelfBagType
{
	Self_Bag				=1, // 背包
	Pet_Bag					=2,
	House_Bag				=3, //  仓库
	Role_Bag				=4, //  身上装备
	Booth_Bag				=5,	//	摊位
	Pet_Bag_Shop			=6,
	Stone_Bag				=7,
	Spider_Bag				=8, //	诛魔结阵
	Setting_Bag				=9, //   设置快捷键
	NPC_Bag					=10, //   NPC仓库
	Sell_Bag				=11, //   垃圾装备售卖
};

enum BagType
{
	Bag_Type_Role			=1,
	Bag_Type_Pet			=2,
	Bag_Type_House			=3,
	Bag_Type_Stone			=4,
	Bag_Type_Booth_Cell		=5,
	Bag_Type_Booth_Buy		=6,
	Bag_Type_Npcshop		=7,
	Bag_Type_Self			=8, // 自身背包
	Bag_Type_Trade			=9, // 交易界面
	Bag_Type_ItemEx1			=10, // 物品Ex--forging
	Bag_Type_ItemEx2			=11, // 物品Ex--merge
	Bag_Type_Spider			=12,
	Bag_Type_Setting			=13,
	Bag_Type_NPCBag			=14,
	Bag_Type_Chart			=15,//聊天界面

	Bag_Type_Null			=20,//没有其他界面
};


class BagPanel : public BasePanel, public IEventListener
{
public:
	BagPanel();
	virtual ~BagPanel();
	static BagPanel* create(int line,int row,int count,int type1,int type2,int position=0);
	virtual bool init(int line,int row,int count,int type1,int type2,int position);
	bool initBagSlot(int line,int row,int count,int type1,int type2,int position);//初始化背包格子
	bool initMoney();//初始化元宝仙玉金币
	bool initButton();//初始化拆分和整理按钮
	virtual void    buttonCallBack(CCObject* pSender); 
	virtual void    handleEvent(int channel);

	void onCPEvent(const std::string &eventName);
	void updatetime(int index);
	void  SortBag();
	void PileItem();
	void TakeOutBag();
	void OpenSpilt(bool flag);
	void setType2(int type);
	static const int MAX_PACKET_PAGE_COUNT	= 6;
public:
	CCLayer*	    m_packPage[MAX_PACKET_PAGE_COUNT];
	GeneralMenu*	m_menus[MAX_PACKET_PAGE_COUNT];
	GeneralMenu*	m_menusItem[MAX_PACKET_PAGE_COUNT];
		
private:
	GeneralMenu* m_menu;
	ItemTooltip* tooltip;
	GeneralMenu* m_MoneyMenu;
	int m_iCurrentBagType;
	bool m_bSpilt;

	CCLabelTTF *m_pGold;
	CCLabelTTF *m_pVcoin;
	CCLabelTTF *m_pGoldBind;
	CCLabelTTF *m_pVcoinBind;
	CCLabelTTF *m_pCoupon;
	CCLabelTTF *m_pCurrentPage;


	short   m_nCurPage;
	std::string m_sCurrentPage;
	CCLayer*	current_layer;
	short		current_layer_idx;
	UserItem*   m_pUserItem;


	CCPoint			m_startPoint;
	int				m_nPrePos;
	float			m_nPreTime;
	bool			m_bDoubleClick;

private:
	int m_iposition;
	int m_iLine;
	int m_iRow;
	int m_iCount;			//格子总数
	int m_iType1;
	int m_iType2;
	int m_iPageCount;		//一页格子总数
	int m_iPage;			//页数

	int m_iWidth;
	enum MyEnum
	{
		TAG_PUTOFF_PACK = 1,
		TAG_SPLIT_PACK ,
		TAG_TAKE_PACK ,
	};

	int m_iSortTime;
};

//-------------------------------------------------------------------------------------------------------------------------//

#endif
