#ifndef __Booth_PANEL_H__
#define __Booth_PANEL_H__

// Show bag panel

#include "GeneralMenuListener.h"
#include "userdata/UserItemData.h"
#include "cocos2d.h"
#include "ext/basepanel.h"
USING_NS_CC;

enum PanelType
{
	Type_Self,
	Type_Other,
};

class TradePanel : public BasePanel
{
public:
	TradePanel();
	virtual ~TradePanel();

	CREATE_FUNC(TradePanel);
	//static TradePanel* create();
	virtual bool init();

	virtual void closeCallBack(CCObject* pSender);
	
};


class TradeCellPanel : public BasePanel
{
public:
	TradeCellPanel();
	virtual ~TradeCellPanel();

	static TradeCellPanel* create(int type);
	virtual bool init(int type);
	virtual void    handleEvent(int channel);

	virtual void initPlayerInfo();
	virtual void TextCallBack(CCObject* pSender);
	virtual void addSelfItem();
	virtual void addOtherItem();
	virtual void ItemCallBack(CCObject* pSender);
	virtual void initButton();
	virtual void MenuCallBack(CCObject* pSender);
	virtual bool isPosInThisPanel(int pos){  return (pos >= ItemPos::Trade_Bag_Start && pos<=ItemPos::Trade_Bag_End );}

	CCPoint getItemPosition(int pos);
private:
	int m_iType;
	GeneralMenu* m_pItemMenu;
	CCMenuItemImage* m_pLockButton;
	CCMenuItemImage* m_pLockSprite;
	UserItem* m_pUserItem;
	bool m_bIsLock;

	int m_iCurrentPriceType;
	int m_iCurrentPrice;

	CCLabelTTF* m_pMoney1;
	CCLabelTTF* m_pMoney2;

	enum MyEnum
	{
		Button_Lock,
		Button_isLock,
		Text_Money1,
		Text_Money2,
	};
};




#endif
