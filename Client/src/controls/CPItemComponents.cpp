#include "CPItemComponents.h"
#include "CPScrollbar.h"
#include "CPNodeHelper.h"
#include "utils/MacroUtils.h"

#define MOVE_FACTOR 0.3f
#define SPEED_FACTOR 7
#define MAX_PERCENT 100

#define CLICK_D 24.0f
#define CLICK_D_HIGH 2.0f

////////////CPItemComponents/////////////////////////////////////////
CPItemComponents::CPItemComponents()
	:mItemContainer(NULL)
	,mClickedItem(NULL)
	,mSelectedItem(NULL)
	,mScrollbar(NULL)
	,mClickHandler(NULL)
	,mClickHandleFunc(NULL)
	,mLayout(NULL)
	,mArea(CCSizeZero)
	,mCurrentPt(CCPointZero)
	,mOffset(CCPointZero)
	,mTouchEnabled(true)
	,mClicked(false)
	,mHighClickSensitive(true)
	,mState(kCCMenuStateWaiting)
	,mMenuItemCount(0)
	,mSpeed(0)
{

}

CPItemComponents::~CPItemComponents()
{
	CC_SAFE_DELETE(mLayout);
}

CPItemComponents * CPItemComponents::create( const cocos2d::CCSize &size, ICPLayout *layout )
{
	CPItemComponents *ret = new CPItemComponents;
	if (ret && ret->initWithData(size, layout))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool CPItemComponents::initWithData( const cocos2d::CCSize &size, ICPLayout *layout )
{
	if (!CCNode::init())
	{
		return false;
	}

	if (!layout)
	{
		return false;
	}

	mArea = size;
	mCurrentPt = CCPointZero;
	mOffset = CCPointZero;

	mLayout = layout;

	mTouchEnabled = true;
	mClicked = false;
	mState = kCCMenuStateWaiting;
	mMenuItemCount = 0;
	mSpeed = 0;

	initUI();

	setContentSize(size);
	setAnchorPoint(ccp(0.5, 0.5));
	setPosition(CCPointZero);

	return true;
}

void CPItemComponents::initUI()
{
	CCClippingNode *clipNode = CPNodeHelper::getClippingNode(mArea);
	addChild(clipNode);

	mItemContainer = CCNode::create();
	mItemContainer->setAnchorPoint(ccp(0, 1));
	mItemContainer->setPosition(ccp(0, mArea.height));
	clipNode->addChild(mItemContainer);

	DebugCode(
		addChild(CPNodeHelper::getBorderNode(mArea));
	);
}

void CPItemComponents::onEnter()
{
	if (mTouchEnabled)
	{
		registerWithTouchDispatcher();
	}
	CCNode::onEnter();
}

void CPItemComponents::onExit()
{
	if (mState == kCCMenuStateTrackingTouch)
	{
		if (mClickedItem)
		{
			mClickedItem->unselected();
			mClickedItem = NULL;
		}

		if (mSelectedItem)
		{
			mSelectedItem->unselected();
			mSelectedItem = NULL;
		}

		mState = kCCMenuStateWaiting;
	}

	CCDirector* pDirector = CCDirector::sharedDirector();
	if( mTouchEnabled )
	{
		pDirector->getTouchDispatcher()->removeDelegate(this);
	}

	CCNode::onExit();
}

void CPItemComponents::setLayout( cocos2d::CCNode *item )
{
	mLayout->setLayout(item, getItemCount());
}

void CPItemComponents::setCurrentClickedItem( cocos2d::CCMenuItem *item )
{
	if (isItemAvailable(item))
	{
		if (mClickedItem && mClickedItem->isEnabled())
		{
			mClickedItem->unselected();
		}
		mClickedItem = item;
		mClickedItem->selected();
	}
}

void CPItemComponents::registerWithTouchDispatcher( void )
{
	 CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	 pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void CPItemComponents::addItem( cocos2d::CCMenuItem *item )
{
	if (item)
	{
		setLayout(item);
		mItemContainer->addChild(item, 0, mMenuItemCount);
		mMenuItemCount++;
	}
}

void CPItemComponents::addItem( cocos2d::CCNode *item )
{
	if (item)
	{
		CCMenuItem *menuItem = dynamic_cast<CCMenuItem *>(item);
		if (menuItem)
		{
			addItem(menuItem);
		}
		else
		{
			setLayout(item);
			mItemContainer->addChild(item, 0, getItemCount());
		}
	}
}

cocos2d::CCNode * CPItemComponents::getItem( int index )
{
	return mItemContainer->getChildByTag(index);
}

void CPItemComponents::setScrollbar( CPScrollbar *bar )
{
	if (mScrollbar)
	{
		CCLog(">>>Error: CPItemComponents::setScrollbar, mScrollbar != NULL");
		return;
	}

	if (bar)
	{
		mScrollbar = bar;
		if (mLayout->isVertical())
		{
			mScrollbar->setAnchorPoint(ccp(1, 0.5f));
			mScrollbar->setPosition(ccp(mArea.width, mArea.height/2));
		}
		else
		{
			mScrollbar->setAnchorPoint(ccp(0.5f, 0));
			mScrollbar->setPosition(ccp(mArea.width/2, 0));
		}
		addChild(mScrollbar);
	}
}

void CPItemComponents::setClickHandler( cocos2d::CCObject *target, cocos2d::SEL_CallFunc func )
{
	mClickHandler = target;
	mClickHandleFunc = func;
}

void CPItemComponents::setCurrentIndex( int index )
{
	if (index == kCCNodeTagInvalid)
	{
		return;
	}

	CCMenuItem *item = dynamic_cast<CCMenuItem *>(getItem(index));
	setCurrentClickedItem(item);
}

int CPItemComponents::getCurrentIndex() const
{
	if (mClickedItem)
	{
		return mClickedItem->getTag();
	}
	return -1;
}

void CPItemComponents::setPercent( int percent )
{
	if (percent < 0)
	{
		percent = 0;
	}
	else if (percent > MAX_PERCENT)
	{
		percent = MAX_PERCENT;
	}

	if (mLayout->isVertical())
	{
		float totalOffset = mLayout->getContentSize().height - mArea.height;
		if (totalOffset > 0)
		{
			int y = mArea.height + percent * totalOffset/MAX_PERCENT;
			mItemContainer->setPositionY(y);
		}
	}
	else
	{
		float totalOffset = mLayout->getContentSize().width - mArea.width;
		if (totalOffset > 0)
		{
			int x = -percent * totalOffset/MAX_PERCENT;
			mItemContainer->setPositionX(x);
		}
	}
}

int CPItemComponents::getPercent()
{
	float totalOffset = 0;
	float offset = 0;
	if (mLayout->isVertical())
	{
		totalOffset = mLayout->getContentSize().height - mArea.height;
		if (totalOffset > 0)
		{
			offset = mItemContainer->getPositionY() - mArea.height;
		}
	}
	else
	{
		totalOffset = mLayout->getContentSize().width - mArea.width;
		if (offset > 0)
		{
			offset = -mItemContainer->getPositionX();
		}
	}

	if (totalOffset <= 0)
	{
		return MAX_PERCENT;
	}
	return offset * MAX_PERCENT/totalOffset;
}

int CPItemComponents::getItemCount() const
{
	CCArray *children = mItemContainer->getChildren();
	if (children)
	{
		return children->count();
	}
	return 0;
}

int CPItemComponents::getMenuItemCount() const
{
	return mMenuItemCount;
}

void CPItemComponents::setClickSensitive( bool high )
{
	mHighClickSensitive = high;
}

void CPItemComponents::removeAllItems()
{
	mItemContainer->removeAllChildrenWithCleanup(true);
	mItemContainer->setPosition(ccp(0, mArea.height));
	mClickedItem = NULL;
	mSelectedItem = NULL;
	mCurrentPt = CCPointZero;
	mOffset = CCPointZero;
	mClicked = false;
	mMenuItemCount = 0;
	mState = kCCMenuStateWaiting;
	mLayout->reset();
}

bool CPItemComponents::isTouchEnabled() const
{
	return mTouchEnabled;
}

void CPItemComponents::setTouchEnabled( bool enabled )
{
	if (mTouchEnabled != enabled)
	{
		mTouchEnabled = enabled;
		if (m_bRunning)
		{
			if (enabled)
			{
				registerWithTouchDispatcher();
			}
			else
			{
				// have problems?
				CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
			}
		}
	}
}

ICPLayout * CPItemComponents::getLayout() const
{
	return mLayout;
}

bool CPItemComponents::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pEvent);
	if (mState != kCCMenuStateWaiting || ! m_bVisible || !mTouchEnabled)
	{
		return false;
	}

	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}

	if (!isTouchInArea(pTouch))
	{
		return false;
	}

	mClicked = true;
	mCurrentPt = convertTouchToNodeSpace(pTouch);
	mOffset = CCPointZero;
	mSpeed = 0;

	mState = kCCMenuStateTrackingTouch;
	mSelectedItem = itemForTouch(pTouch);
	if (mSelectedItem)
	{
		mSelectedItem->selected();
	}
	return true;
}

void CPItemComponents::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pEvent);
	if (mState != kCCMenuStateTrackingTouch)
	{
		return;
	}

	if (isTouchInArea(pTouch))
	{
		const CCPoint &pt = convertTouchToNodeSpace(pTouch);
		if (mLayout->isVertical())
		{
			mSpeed = pt.y - mCurrentPt.y;
			mOffset.y += mSpeed;
		}
		else
		{
			mSpeed = pt.x - mCurrentPt.x;
			mOffset.x += mSpeed;
		}
		mCurrentPt = pt;
		const float STANDARD = (mHighClickSensitive ? CLICK_D_HIGH : CLICK_D);
		if (mSpeed < -STANDARD || STANDARD < mSpeed )
		{
			mClicked = false;
		}

		//
		CCMenuItem *currentItem = itemForTouch(pTouch);
		if (currentItem != mSelectedItem) 
		{
			if (mSelectedItem)
			{
				if (mSelectedItem != mClickedItem)
				{
					mSelectedItem->unselected();
				}
			}

			if (mClicked)
			{
				mSelectedItem = currentItem;
				if (mSelectedItem)
				{
					mSelectedItem->selected();
				}
			}
			else
			{
				mSelectedItem = NULL;
			}			
		}
	}
	else
	{
		ccTouchEnded(pTouch, pEvent);
	}
}

void CPItemComponents::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);
	if (mState != kCCMenuStateTrackingTouch)
	{
		return;
	}

	if (mSelectedItem)
	{
		if (mClicked)
		{
			setCurrentClickedItem(mSelectedItem);
			if (mClickedItem)
			{
				mClickedItem->activate();
			}
		}
		else
		{
			if (mSelectedItem != mClickedItem)
			{
				mSelectedItem->unselected();
			}
		}
		mSelectedItem = NULL;
	}

	if (mClicked)
	{
		mClicked = false;
		if (mClickHandler && mClickHandleFunc)
		{
			(mClickHandler->*mClickHandleFunc)();
		}
	}

	int offset = mSpeed * SPEED_FACTOR;
	if (mLayout->isVertical())
	{
		mOffset.y += offset;
	}
	else
	{
		mOffset.x += offset;
	}
	mCurrentPt = CCPointZero;
	mSpeed = 0;
	mState = kCCMenuStateWaiting;
}

void CPItemComponents::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);
	if (mState != kCCMenuStateWaiting)
	{
		if (mSelectedItem)
		{
			mSelectedItem->unselected();
		}
		mState = kCCMenuStateWaiting;
	}
}

void CPItemComponents::visit()
{
	updateContainerPosition();
	updateItemVisible();
	updateScrollbar();
	CCNode::visit();
}

CCMenuItem* CPItemComponents::itemForTouch( CCTouch * touch )
{
	CCPoint touchLocation = touch->getLocation();
	CCArray *children = mItemContainer->getChildren();
	if (children && children->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(children, pObject)
		{
			CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
			if (pChild && pChild->isVisible() && pChild->isEnabled())
			{
				CCPoint local = pChild->convertToNodeSpace(touchLocation);
				CCRect r = pChild->rect();
				r.origin = CCPointZero;

				if (r.containsPoint(local))
				{
					return pChild;
				}
			}
		}
	}

	return NULL;
}

bool CPItemComponents::isTouchInArea( cocos2d::CCTouch *pTouch )
{
	CCPoint pt = convertTouchToNodeSpace(pTouch);
	const CCRect &rect = CCRectMake(0, 0, mArea.width, mArea.height);
	return rect.containsPoint(pt);
}

bool CPItemComponents::isItemInArea( cocos2d::CCNode *item )
{
	if (item)
	{
		const CCPoint &itemAnPt = item->getAnchorPoint();
		const CCPoint &itemPt = item->getPosition();
		const CCSize &itemSize = item->getContentSize();
		const CCPoint &itemOriginPt = ccp(itemPt.x - itemSize.width * itemAnPt.x, itemPt.y - itemSize.height * itemAnPt.y);

		CCPoint temp = CCPointZero;
		CCPoint ptArray[4];
		temp = mItemContainer->convertToWorldSpace(itemOriginPt);
		ptArray[0] = convertToNodeSpace(temp);
		temp = mItemContainer->convertToWorldSpace(ccp(itemOriginPt.x + itemSize.width, itemOriginPt.y));
		ptArray[1] = convertToNodeSpace(temp);
		temp = mItemContainer->convertToWorldSpace(ccp(itemOriginPt.x + itemSize.width, itemOriginPt.y + itemSize.height));
		ptArray[2] = convertToNodeSpace(temp);
		temp = mItemContainer->convertToWorldSpace(ccp(itemOriginPt.x, itemOriginPt.y + itemSize.height));
		ptArray[3] = convertToNodeSpace(temp);

		CCRect rect = CCRectMake(0, 0, mArea.width, mArea.height);
		for (int i = 0; i < 4; i++)
		{
			if (rect.containsPoint(ptArray[i]))
			{
				return true;
			}
		}

		rect = CCRectMake(ptArray[0].x, ptArray[0].y, itemSize.width, itemSize.height);
		ptArray[0] = ccp(0, 0);
		ptArray[1] = ccp(mArea.width, 0);
		ptArray[2] = ccp(mArea.width, mArea.height);
		ptArray[3] = ccp(0, mArea.height);
		for (int i = 0; i < 4; i++)
		{
			if (rect.containsPoint(ptArray[i]))
			{
				return true;
			}
		}
	}
	return false;
}

bool CPItemComponents::isItemAvailable( cocos2d::CCMenuItem *item )
{
	return (item && item->isVisible() && item->isEnabled());
}

void CPItemComponents::updateContainerPosition()
{
	if (mOffset.equals(CCPointZero))
	{
		return;
	}

	if (mLayout->isVertical())
	{
		const float containerY = mItemContainer->getPositionY();
		const float dy = mOffset.y * MOVE_FACTOR;
		const float y = getMyY(containerY + dy);
		if (y != containerY)
		{
			mItemContainer->setPositionY(y);
			mOffset.y -= dy;
		}
		else
		{
			mOffset.y = 0;
		}
	}
	else
	{
		const float containerX = mItemContainer->getPositionX();
		const float dx = mOffset.x * MOVE_FACTOR;
		const float x = getMyX(containerX + dx);
		if (x != containerX)
		{
			mItemContainer->setPositionX(x);
			mOffset.x -= dx;
		}
		else
		{
			mOffset.x = 0;
		}
	}
}

void CPItemComponents::updateItemVisible()
{
	CCArray *children = mItemContainer->getChildren();
	if (children && children->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(children, pObject)
		{
			CCNode *pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				pChild->setVisible(isItemInArea(pChild));
			}
		}
	}

}

void CPItemComponents::updateScrollbar()
{
	if (mScrollbar)
	{
		float maxPosition = 0;
		float curPosition = 0;
		if (mLayout->isVertical())
		{
			maxPosition = mLayout->getContentSize().height - mArea.height;
			curPosition = mItemContainer->getPositionY() - mArea.height;
		}
		else
		{
			maxPosition = mLayout->getContentSize().width - mArea.width;
			curPosition = -mItemContainer->getPositionX();
		}
		mScrollbar->setMaxPosition(maxPosition);
		mScrollbar->setCurrentPosition(curPosition);
	}
}

float CPItemComponents::getMyX( float x )
{
	float d = mLayout->getContentSize().width - mArea.width;
	if(d > 0)
	{
		if(x > 0)
		{
			x = 0;
		}
		else if(x < - d)
		{
			x = - d;
		}
	}
	else
	{
		x = 0;
	}
	return x;
}

float CPItemComponents::getMyY( float y )
{
	float d = mLayout->getContentSize().height - mArea.height;
	if(d > 0)
	{
		if(y < mArea.height)
		{
			y = mArea.height;
		}
		else if(y > mArea.height + d)
		{
			y = mArea.height + d;
		}
	}
	else
	{
		y = mArea.height;
	}	
	return y;
}

//////////ICPLayout///////////////////////////////////////////////
ICPLayout::ICPLayout( const cocos2d::CCSize &itemSize, bool vertical )
	:mIsVertical(vertical)
	,mContentSize(CCSizeZero)
	,mItemSize(itemSize)
{

}

bool ICPLayout::isVertical() const
{
	return mIsVertical;
}

cocos2d::CCSize ICPLayout::getContentSize()
{
	return mContentSize;
}

void ICPLayout::reset()
{
	mContentSize = CCSizeZero;
}

void ICPLayout::setIsVertical( bool vertical )
{
	mIsVertical = vertical;
}

void ICPLayout::setContentSize( const cocos2d::CCSize &size )
{
	mContentSize = size;
}

void ICPLayout::setItemSize( const cocos2d::CCSize &size )
{
	mItemSize = size;
}

cocos2d::CCSize ICPLayout::getItemSize() const
{
	return mItemSize;
}

////////CPLayoutList/////////////////////////////////////////////////
CPLayoutList::CPLayoutList()
	:ICPLayout(CCSizeZero, true)
{
}

CPLayoutList::CPLayoutList( const cocos2d::CCSize &itemSize, bool vertical )
	:ICPLayout(itemSize, vertical)
{
}

CPLayoutList::~CPLayoutList()
{

}

void CPLayoutList::setLayout( cocos2d::CCNode *node, int index )
{
	if (!node)
	{
		return;
	}

	//
	node->setAnchorPoint(ccp(0, 1));
	CCSize itemSize = getItemSize();
	if (itemSize.equals(CCSizeZero))
	{
		itemSize = node->getContentSize();
	}

	CCSize contentSize = getContentSize();
	if (isVertical())
	{
		node->setPosition(ccp(0, -contentSize.height));
		if (itemSize.height > 0)
		{
			contentSize.height += itemSize.height;
		}
	}
	else
	{
		node->setPosition(ccp(contentSize.width, 0));
		if (itemSize.width > 0)
		{
			contentSize.width += itemSize.width;
		}
	}
	setContentSize(contentSize);
}

///////////CPLayoutGrid/////////////////////////////////////////////
CPLayoutGrid::CPLayoutGrid( int countPerLine )
	:ICPLayout(CCSizeZero, true)
	,mCountPerLine(countPerLine)
{
	if (mCountPerLine <= 0)
	{
		mCountPerLine = 1;
	}
}

CPLayoutGrid::CPLayoutGrid( int countPerLine, const cocos2d::CCSize &itemSize, bool vertical )
	:ICPLayout(itemSize, vertical)
	,mCountPerLine(countPerLine)
{
	if (mCountPerLine <= 0)
	{
		mCountPerLine = 1;
	}
}

CPLayoutGrid::~CPLayoutGrid()
{
}

void CPLayoutGrid::setLayout( cocos2d::CCNode *node, int index )
{
	if (!node)
	{
		return;
	}

	if (index < 0)
	{
		index = 0;
	}

	//
	node->setAnchorPoint(ccp(0, 1));
	CCSize itemSize = getItemSize();
	if (itemSize.equals(CCSizeZero))
	{
		itemSize = node->getContentSize();
	}

	int indexM = index%mCountPerLine;
	int indexN = index/mCountPerLine;
	if (isVertical())
	{
		node->setPosition(ccp(itemSize.width * indexM, -itemSize.height * indexN));
		setContentSize(CCSizeMake(itemSize.width * mCountPerLine, itemSize.height * (indexN + 1)));
	}
	else
	{
		node->setPosition(ccp(itemSize.width * indexN, itemSize.height * indexM));
		setContentSize(CCSizeMake(itemSize.width * (indexN + 1), itemSize.height * mCountPerLine));
	}
}
