#ifndef __CPItemComponents_h__
#define __CPItemComponents_h__

#include "CCMenuItem.h"
#include "CCTouchDelegateProtocol.h"

class ICPLayout;
class CPScrollbar;
class CPItemComponents : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
public:
	CPItemComponents();
	~CPItemComponents();

public:
	static CPItemComponents *create(const cocos2d::CCSize &size, ICPLayout *layout);

	void addItem(cocos2d::CCNode *item);
	void addItem(cocos2d::CCMenuItem *item);

	cocos2d::CCNode *getItem(int index);

	void setScrollbar(CPScrollbar *bar);
	void setClickHandler(cocos2d::CCObject *target, cocos2d::SEL_CallFunc func);

	void setCurrentIndex(int index);
	int getCurrentIndex() const;

	void setPercent(int percent);
	int getPercent();

	int getItemCount() const;
	int getMenuItemCount() const;

	void removeAllItems();

	void setClickSensitive(bool high);

	bool isTouchEnabled() const;
	void setTouchEnabled(bool enabled);

	ICPLayout *getLayout() const;

private:
	bool initWithData(const cocos2d::CCSize &size, ICPLayout *layout);
	void initUI();
	void onEnter();
	void onExit();

	void setLayout(cocos2d::CCNode *item);
	void setCurrentClickedItem(cocos2d::CCMenuItem *item);

	bool isTouchInArea(cocos2d::CCTouch *pTouch);
	bool isItemInArea(cocos2d::CCNode *item);
	cocos2d::CCMenuItem *itemForTouch(cocos2d::CCTouch * touch);
	bool isItemAvailable(cocos2d::CCMenuItem *item);
	void updateContainerPosition();
	void updateItemVisible();
	void updateScrollbar();
	
	float getMyX(float x);
	float getMyY(float y);

	//
	void visit();

public:
	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

private:
	cocos2d::CCNode *mItemContainer;
	cocos2d::CCMenuItem *mClickedItem;
	cocos2d::CCMenuItem *mSelectedItem;
	CPScrollbar *mScrollbar;
	cocos2d::CCObject *mClickHandler;
	cocos2d::SEL_CallFunc mClickHandleFunc;

	cocos2d::CCSize mArea;
	cocos2d::CCPoint mCurrentPt;
	cocos2d::CCPoint mOffset;

	ICPLayout *mLayout;

	bool mTouchEnabled;
	bool mClicked;
	bool mHighClickSensitive;
	short mState;
	int mMenuItemCount;
	float mSpeed;
};

/////////ICPLayout///////////////////////////////////////////////////////
class ICPLayout
{
public:
	virtual ~ICPLayout(){}
	bool isVertical() const;
	cocos2d::CCSize getContentSize();
	void reset();

	virtual void setLayout(cocos2d::CCNode *node, int index) = 0;

protected:
	ICPLayout(const cocos2d::CCSize &itemSize, bool vertical);

	void setIsVertical(bool vertical);
	void setContentSize(const cocos2d::CCSize &size);
	void setItemSize(const cocos2d::CCSize &size);

	cocos2d::CCSize getItemSize() const;

private:
	bool mIsVertical;
	cocos2d::CCSize mItemSize;
	cocos2d::CCSize mContentSize;
};

//////////CPLayoutList//////////////////////////////////////////////////
/**
 * size can be different for each item
 */
class CPLayoutList : public ICPLayout
{
public:
	CPLayoutList();
	CPLayoutList(const cocos2d::CCSize &itemSize, bool vertical);
	~CPLayoutList();

public:
	void setLayout(cocos2d::CCNode *node, int index);
};

////////////CPLayoutGrid/////////////////////////////////////////////////
/**
 * size must be equal for each item
 */
class CPLayoutGrid : public ICPLayout
{
public:
	CPLayoutGrid(int countPerLine);
	CPLayoutGrid(int countPerLine, const cocos2d::CCSize &itemSize, bool vertical);
	~CPLayoutGrid();

public:
	void setLayout(cocos2d::CCNode *node, int index);

private:
	int mCountPerLine;
};

#endif //__CPItemComponents_h__