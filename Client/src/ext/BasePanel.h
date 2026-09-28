#ifndef __BASE_PANEL_H__
#define __BASE_PANEL_H__

/*
功能：可以拖动的，需要一个sprite来初始化，氛围为sprite的contentsize，有关闭按钮。
注意：关闭默认是隐藏，可以在子类里面重写hide实现其他的功能。
*/

#include "event/EventListener.h"
#include "cocos2d.h"
USING_NS_CC;

class NetItem;
class GeneralMenu;

class BasePanel : public CCLayer, public EventListener
{
public:
	BasePanel();
	virtual ~BasePanel();
	virtual void onEnter();
	virtual void onExit();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	static BasePanel* create(const char *filename);
	virtual bool init(const char *filename, bool isshow = true , bool bconfigString = false);
	static BasePanel* createWithSpriteFrameName(const char *filename);
	virtual bool initWithSpriteFrameName(const char *filename, bool isshow = true );

public:
	virtual void setTargetPanel(BasePanel* targetPanel);
	virtual bool dragIn(CCPoint& point, CCNode* itemsrc);//receive item
	virtual void dragOut(CCPoint& point);//call at moving end, tell target
	virtual void startDrag(CCPoint &pos);//set dragging state
	virtual void dragging(CCPoint& pos);
	virtual bool checkSelectOneItem(CCPoint &pos);//check and create moving sprite
	
	virtual void dragEndInScroll();
	virtual void dragBeginInScroll();
	virtual void startDragInScroll(CCPoint &pos);
	virtual void checkStartDragInScroll(float dt);

	virtual void setItemType(int type);
	virtual int	 getItemType();
	
	virtual void addOneItem(std::map<int, NetItem*>::iterator it){};

public:
	virtual void show();
	virtual void hide();
	virtual void update(float dt);
	virtual bool isPointInThisPanel(CCPoint& point);
	virtual void closeCallBack(CCObject* pSender);
	virtual void setMeTopOrder();
	virtual void addCover();
	virtual void addCover(CCPoint Pos,int priority = kCCMenuHandlerPriority);

public:
	virtual bool isInRange(CCTouch* pTouch);

public:
	GeneralMenu*	m_pMenu;		
	CCSprite*		m_pBkgSprite;
	int				m_nWidth;
	int				m_nHeight;
	int				m_nPosX;
	int				m_nPosY;
	bool			m_isNeedShow;
	CCPoint*		m_itemPoints;
	CCPoint*		m_desitemPoints;
	CCMenuItemImage** m_items;
	CCMenuItemImage** m_desitems;
	int				m_size;
	static int		s_PanelZorder;
	const static int TOP_ZORDER = 28;

public:
	BasePanel*		m_pTargetPanel;
	CCSprite*		m_pMovingItem;
	bool			m_bIsDragging;
	int				m_nStartDragPeriod;
	bool			m_bTouchDown;
	bool			m_bMoveTwoFar;
	CCPoint			m_ptStartDragPos;
	int				m_nItemType;
	const static int DragPeriod = 5;
	const static int SelectDistance = 8; 
	enum ITEM_TYPE
	{
		ITEM_TYPE_BAG,
		ITEM_TYPE_SHOP,
		ITEM_TYPE_ROLE,
		ITEM_TYPE_DEPOT,
		ITEM_TYPE_TREASURE_DEPOT,
		ITEM_TYPE_FURNACE,
	};
};

#endif//__BASE_PANEL_H__