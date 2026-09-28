#ifndef __Booth_PANEL_H__
#define __Booth_PANEL_H__

// Show bag panel

#include "GeneralMenuListener.h"
#include "CommonPanel.h"
#include "userdata/UserItemData.h"
#include "cocos2d.h"
#include "ext/basepanel.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include "event/IEventListener.h"
USING_NS_CC_EXT;

enum BoothType
{
	Booth_Buy		=1,    //看其他人摊位
	Booth_Sell		=2,   //看自己摊位
};

struct UserItem;
class PacketPage;
class Scissor;
class NetItem;
class CCMenuEx;
class ItemTooltip;

class BoothPanel : public BasePanel,public CCEditBoxDelegate,public IEventListener
{
public:
	BoothPanel();
	virtual ~BoothPanel();

	static BoothPanel* create(int type=Booth_Sell,bool isHighBooth=false);
	virtual bool init(int type,bool isHighBooth);
	virtual void onEnter();
	virtual void onExit();
	bool initBagSlot();//初始化背包格子
	bool initButton();//初始化拆分和整理按钮
	virtual bool    isPosInThisPanel(int pos){  return (pos >= ItemPos::Market_Bag_Start && pos<=ItemPos::Market_Bag_End );}
	void		    insertItem( UserItem* userItem, int pos);
	void		    removeItem( int pos );
	void		    updateItemCount( int iid, short count );
	virtual CCPoint getItemPosition( int pos );
	virtual bool	getItemVisible(int pos){return true;}
	virtual void	slotClickCallBack(CCObject* pSender);
	virtual void	itemClickCallBack(CCObject* pSender);
	virtual void	singleClickCallback( float dt );
	virtual void    buttonCallBack(CCObject* pSender); 
	short			backLayer(int pos);

	virtual void    onCPEvent( const std::string &eventName );

	virtual void	showTooltip(UserItem* userItem);
	bool			isDoubleClickItem(int pos);
	virtual void    handleEvent(int channel);

	void			openSetPrice(CCObject* pSender);
	void			openKeyBorad();
	void			setpricetoSellPanel(int price);

	void			insertOtherItem();
	void			initBag();

	void editBoxEditingDidBegin(extension::CCEditBox *editBox);
	void editBoxReturn(extension::CCEditBox *editBox);

	void			sendStartBooth();
	void			Update(float);
	void			updateAll();
	void            leaveWord();
public:
	
	static const int MAX_PACKET_PAGE_COUNT	= 1;
	CCLayer*	    m_packPage[MAX_PACKET_PAGE_COUNT];
	GeneralMenu*	m_menusItem[MAX_PACKET_PAGE_COUNT];
	GeneralMenu*	m_menus[MAX_PACKET_PAGE_COUNT];
	CCPoint		_prePoint;
	CCLayer*	current_layer;
	short		current_layer_idx;
	bool		m_ballowMove;
	UserItem*  m_pUserItem;

	static const int ITEM_BAG_BEGIN = 0;
	static const int ITEM_BAG_SIZE = 15;
	static const int ITEM_BAG_END = 15;

	CCPoint			m_startPoint;
	CCSprite*		m_movingItem;
	bool			m_bMovingItem;

	int				m_nPrePos;
	float			m_nPreTime;
	bool			m_bDoubleClick;

	static const int ITEM_UNUSE_POS = -1000;
	GeneralMenu*	m_pConfirmDlg;

protected:
	short   m_nCurPage;
	static const int MAX_SLOT_ROW_COUNT = 5;

	//CCPoint m_startPoint;
	CCLabelTTF *m_pGold;
	CCLabelTTF *m_pVcoin;
	CCLabelTTF *m_pGoldBind;
	CCLabelTTF *m_pVcoinBind;
	CCLabelTTF *m_pCoupon;
	CCLabelTTF *m_pCurrentPage;

	bool m_isTouchMoved;
	CCMenuItem *m_dropItem;
	
	std::string     m_sCurrentPage;
	int				m_itemTag;
	CCSprite*		m_moveItem;
	CCSprite*		m_fiveDots[5];

private:
	int m_icurrentPrice;
	GeneralMenu* m_menu;
	ItemTooltip* tooltip;
	int m_iBoothType;
	bool isItem[15];
	GeneralMenu* m_ItemMenu;
	CCLabelTTF* m_pBoothTitle;

	std::string adStr;
	CCEditBox* m_pEditBox;
	CCLabelTTF* m_padLabel;
	int i_time;
	int m_iTimeSpan;
	GeneralMenu* m_pDownMenu;
	bool m_bclickOtherItem;

	enum ButtonType
	{
		Button_Message		=1, //留言
		Button_Book,			//日志
		Button_Start,			//摆摊
		Button_Over,			//收摊
		Button_TalkWorld,			//世界喊话

		Panel_Price,
	};
};




class SellPanel:
	public BasePanel
{
public:
	SellPanel();
	~SellPanel();

	static SellPanel* create(UserItem* pUserItem);
	virtual bool init(UserItem* pUserItem);
	void MenuCallBack(CCObject* pSender);

	void postBoothUP();
	void setPrice(int price);
private:
	void close(CCObject* pSender);
	bool checkIfCanpostUp();
	UserItem* m_pUserItem;
	CCLabelTTF* m_pSellTypeLabel;
	CCSprite* m_pSelectSprite;
	CCLabelTTF* m_pSellPrice;
	int m_iCurrentSellType;
	int m_iPrice;

	enum ButtonType
	{
		Left_Block,
		Right_Block,
		Button_OK,
		Text_PutIn,
	};
};



#endif
