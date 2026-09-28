#ifndef __BAGCell_PANEL_H__
#define __BAGCell_PANEL_H__

// Show bag panel

#include "GeneralMenuListener.h"
#include "CommonPanel.h"
#include "userdata/UserItemData.h"
#include "cocos2d.h"
#include "ext/basepanel.h"
#include "ItemDefinition.h"
#include "event/IEventListener.h"
#include "controls/CPUpdater.h"
USING_NS_CC;

struct UserItem;
class PacketPage;
class NetItem;
class CCMenuEx;
class ItemTooltip;
class CPDelayRefresh;

//需要行line，列row，总数count，背包类型SelfBagType，对应界面类型BagType

/*
enum SelfBagType
{
	Self_Bag				=1, // 背包
	Pet_Bag					=2,
	House_Bag				=3, //  仓库
	Role_Bag				=4, //  身上装备
};

enum BagType
{
	Bag_Type_Role			=1,
	Bag_Type_Pet			=2,
	Bag_Type_House			=3,
	Bag_Type_Stone			=4,
	Bag_Type_Booth			=5,  // 摊位
	Bag_Type_Npcshop		=6,
};*/

class BagCellPanel : public BasePanel, public IEventListener
{
public:
	BagCellPanel();
	virtual ~BagCellPanel();
	static BagCellPanel* create(int line,int row,int count,int type1,int type2,int position=0);
	virtual bool init(int line,int row,int count,int type1,int type2,int position);
	bool initBagSlot();//初始化背包格子
	virtual bool    isPosInThisPanel(int pos);
	void		    insertItem( UserItem* userItem, int pos);
	void		    insertStone( UserItem* userItem, int pos );
	virtual CCPoint getItemPosition( int pos );
	virtual void	slotClickCallBack(CCObject* pSender);
	virtual void	itemClickCallBack(CCObject* pSender);
	virtual void	singleClickCallback( float dt );
	short			backLayer(int pos);
	virtual bool	getItemVisible(int pos){return true;}
	virtual void	showTooltip(int tag);
	bool			isDoubleClickItem(int pos);
	virtual void    handleEvent(int channel);

	void			updatePage(int page);
	void onCPEvent(const std::string &eventName);
	void			useItem(CCNode* pSender,void* pObject);

	void		setCurVisibleType(int type);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void			setPanelVisible(CCObject* pSender);

	void			openKeyBorad();
	void			setCurCount(int count);
	void			openUnlockPanel();

	void			insertAllItem();
	void			updateAllItem();
	void			spiltItemMsg( CCObject* pSender  );
	void			sendMsgSpiltItem();
	void			setspiltState(bool flag);
	void			sellItem(CCObject* pSender);
	void			setType2(int type);
	void            addListItem(int i);
	void			addListItemFinish();
	static const int MAX_PACKET_PAGE_COUNT	= 30;
public:
	CCLayer*	    m_packPage[MAX_PACKET_PAGE_COUNT];
	CCMenuEx*	m_menus[MAX_PACKET_PAGE_COUNT];
	CCMenuEx*	m_menusItem[MAX_PACKET_PAGE_COUNT];
		
private:
	bool m_bInit;
	CPUpdater *	m_updater;
	CCLayer* m_pMainLayer;
	int m_iposition;

	GeneralMenu* m_menu;
	ItemTooltip* tooltip;
	CCLabelTTF* m_pCurrentPage;

	short   m_nCurPage;
	std::string m_sCurrentPage;
	CCLayer*	current_layer;
	short		current_layer_idx;
	UserItem*   m_pUserItem;


	CCPoint			m_startPoint;
	int				m_nPrePos;
	float			m_nPreTime;
	bool			m_bDoubleClick;
	bool            m_bisOver;
	CCPoint			m_clickpos;
	int				m_iCurPosition;

	int m_iLine;
	int m_iRow;
	int m_iCount;			//格子总数
	int m_iType1;
	int m_iType2;
	int m_iPageCount;		//一页格子总数
	int m_iPage;			//页数
	int m_iStart;
	int m_iEnd;
	int m_iHasSolt;		//	 拥有格子数量

	int m_iCountItem;

	int m_iCurrentVisibleType; // 当前可见类型 

	int m_iCurrentPage;

	int m_iWidth;
	int m_iHeight;

	bool m_bSpiltOp;
	int m_iSpiltCnt;

private:

	CCPoint m_StartPos;
	CCPoint m_TouchPos;
	CCPoint m_Pos;
	CPDelayRefresh* m_pDelay;
	int m_iCurUnlockCount;
	enum MyEnum
	{
		Panel_Unlock
	};

	std::vector<UserItem*> m_vecAllItem;
	std::vector<UserItem*> m_vecItem;
};

//-------------------------------------------------------------------------------------------//

class BagUnlockPanel : public BasePanel
{
public:
	BagUnlockPanel();
	virtual ~BagUnlockPanel();
	static BagUnlockPanel* create(int pos,int type);
	virtual bool init(int pos,int type);

	void	 setUnlockCount(int count); 
	virtual void    handleEvent(int channel);
private:
	virtual void MenuCallBack(CCObject* pSender);
	void	postmsgUnlockBag();
	bool	check();

	int m_iCount;
	CCLabelTTF* m_pCurCount;
	CCLabelTTF* m_pCurText;
	int m_iStartPos;		//	开始位置
	int m_iMaxCnt;		//最大个数
	int m_iBagType;
	enum ButtonType
	{
		Left_Button,
		Right_Button,
		Button_OK,
		Button_Cancel,
		Text_PutIn,
	};
};

#endif
