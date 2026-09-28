#include "CPComboBox.h"
#include "cocos2d.h"

using namespace cocos2d;


#define ITEM_CHILD_TAG 7


static CCSprite *getSpriteByFrameName( const std::string &frameName )
{
	if (frameName.empty())
	{
		return NULL;
	}

	CCSprite *ret = CCSprite::create();
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
	if(frame)
	{
		ret->initWithSpriteFrame(frame);
		return ret;
	}
	CCLog(">>>Error: getSpriteByFrameName failed, frameName = %s", frameName.c_str());
	return ret;
}

static CCMenuItemSprite *getMenuItemSprite( const std::string &normFrame, const std::string &selFrame )
{
	CCSprite *norm = getSpriteByFrameName(normFrame);
	CCSprite *sel = getSpriteByFrameName(selFrame);
	return CCMenuItemSprite::create(norm, sel);
}

//////////CPComboBox//////////////////////////////////////////////////
CPComboBox::CPComboBox()
	:mLabel(NULL)
	,mCurrentItem(NULL)
	,mItemContainer(NULL)
	,mChangeHandler(NULL)
	,mChangeHandleFunc(NULL)
	,mChangeHandler_(NULL)
	,mChangeHandleFunc_(NULL)
	,mCurrentIndex(-1)
	,mIsOpen(false)
	,mIsItemContainerTouched(false)
	,m_zOrder(0)
	,m_iOpenDir(0)
{

}

CPComboBox::~CPComboBox()
{

}

CPComboBox * CPComboBox::create( const std::string &normFrame, const std::string &selFrame, const std::string &flagFrame )
{
	CPComboBox *ret = new CPComboBox;
	if (ret && ret->initWithData(normFrame, selFrame, flagFrame))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool CPComboBox::initWithData( const std::string &normFrame, const std::string &selFrame, const std::string &flagFrame )//下拉ui
{
	if (!CCNode::init())
	{
		return false;
	}

	if (!normFrame.empty() && !selFrame.empty())
	{
		mNormFrame = normFrame;
		mSelFrame = selFrame;
		mFlagFrame = flagFrame;

		initUI();
		setAnchorPoint(ccp(0.5f, 0.5f));
		setContentSize(mItemSize);

		return true;
	}
	return false;
}

void CPComboBox::onEnter()
{
	registerWithTouchDispatcher();
	CCNode::onEnter();	
}

void CPComboBox::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}

void CPComboBox::initUI()//下拉
{
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemSprite *btn = getMenuItemSprite(mNormFrame, mSelFrame);
	btn->setTarget(this, menu_selector(CPComboBox::onClick));
	menu->addChild(btn);

	mItemSize = btn->getContentSize();
	btn->setPosition(ccp(mItemSize.width/2, mItemSize.height/2));

	mCurrentItem = CCSprite::create();
	mCurrentItem->setPosition(ccp(mItemSize.width/2, mItemSize.height/2));
	addChild(mCurrentItem);

	mLabel = CCLabelTTF::create();
	mLabel->setPosition(ccp(mItemSize.width/2, mItemSize.height/2));
	addChild(mLabel, 1);

	CCSprite *flag = getSpriteByFrameName(mFlagFrame);
	if (flag)
	{
		flag->setAnchorPoint(ccp(1, 0.5f));
		flag->setPosition(ccp(mItemSize.width, mItemSize.height/2));
		addChild(flag, 1);
	}

	CCMenu *container = CCMenu::create();
	container->setVisible(false);
	container->setPosition(CCPointZero);
	addChild(container, 1);
	mItemContainer = container;
}

void CPComboBox::refresh()
{
	CCNode *item = mItemContainer->getChildByTag(mCurrentIndex);
	if (item)
	{
		CCLabelTTF *label = dynamic_cast<CCLabelTTF *>(item->getChildByTag(ITEM_CHILD_TAG));
		if (label)
		{
			mLabel->setString(label->getString());
		}
	}

	ItemFrameMap::iterator it = mItemFrames.find(mCurrentIndex);
	if (it != mItemFrames.end())
	{
		CCSprite *sprite = getSpriteByFrameName(it->second);
		if (sprite)
		{
			mCurrentItem->setDisplayFrame(sprite->displayFrame());
		}
	}
}

void CPComboBox::setLabelStyle( const std::string &fontName, float fontSize, const ccColor3B &color )
{
	mLabel->setFontName(fontName.c_str());
	mLabel->setFontSize(fontSize);
	mLabel->setColor(color);
}

void CPComboBox::setChangeHandler( CCObject *target, SEL_CallFuncN func )
{
	mChangeHandler = target;
	mChangeHandleFunc = func;
}

void CPComboBox::addLabelItem( const std::string &text )
{
	addLabelItem(text, getItemCount());
}

void CPComboBox::addLabelItem( const std::string &text, int index )
{
	CCLabelTTF *label = CCLabelTTF::create();
	label->setString(text.c_str());
	label->setFontName(mLabel->getFontName());
	label->setFontSize(mLabel->getFontSize());
	label->setColor(mLabel->getColor());
	addItem(label, index);	
}

void CPComboBox::addSpriteItem( const std::string &frame )
{
	addSpriteItem(frame, getItemCount());
}

void CPComboBox::addSpriteItem( const std::string &frame, int index )
{
	CCSprite *sprite = getSpriteByFrameName(frame);
	if (sprite)
	{
		mItemFrames[index] = frame;
		addItem(sprite, index);
	}
}

void CPComboBox::setCurrentIndex( int index )
{
	if (index != mCurrentIndex)
	{
		CCNode *item = mItemContainer->getChildByTag(index);
		if (item)
		{
			mCurrentIndex = index;
		}
		else if (mItemContainer->getChildrenCount() > 0)
		{
			mCurrentIndex = 0;
		}
		else
		{
			mCurrentIndex = -1;
			return;
		}
		refresh();
	}
}

int CPComboBox::getCurrentIndex() const
{
	return mCurrentIndex;
}

int CPComboBox::getItemCount() const
{
	CCArray *children = mItemContainer->getChildren();
	if (children)
	{
		return children->count();
	}
	return 0;
}

void CPComboBox::addItem( CCNode *item, int tag )
{
	if (!item)
	{
		return;
	}

	const int cnt = getItemCount();
	CCMenuItemSprite *btn = getMenuItemSprite(mNormFrame, mSelFrame);
	btn->setTarget(this, menu_selector(CPComboBox::onItem));
	btn->setAnchorPoint(ccp(0, 1));
	btn->setPosition(ccp(0, -mItemSize.height * cnt));
	mItemContainer->addChild(btn, 0, tag);
	mItemContainer->setContentSize(CCSizeMake(mItemSize.width, mItemSize.height * (cnt + 1)));

	item->setPosition(ccp(mItemSize.width/2, mItemSize.height/2));
	btn->addChild(item, 0, ITEM_CHILD_TAG);

	if (mCurrentIndex < 0)
	{
		setCurrentIndex(tag);
	}
}

void CPComboBox::open()
{
	if (!mIsOpen)
	{
		mIsOpen = true;
		CCNode *parent = getParent();
		if (parent)
		{
			m_zOrder = getZOrder();
			setZOrder(INT_MAX);

			const CCSize &size = CCEGLView::sharedOpenGLView()->getFrameSize();
			const CCPoint &pt = parent->convertToWorldSpace(getPosition());
			switch (m_iOpenDir)
			{
			case ComboBoxOpenType::open_Unsettled:
				if (pt.y >= size.height/2)
				{
					mItemContainer->setAnchorPoint(ccp(0.5f, 0));
					mItemContainer->setPositionY(0);
				}
				else
				{
					mItemContainer->setAnchorPoint(ccp(0.5f, -1));
					mItemContainer->setPositionY(mItemSize.height * (getItemCount() + 1));
				}
				break;
			case ComboBoxOpenType::open_Up:
				mItemContainer->setAnchorPoint(ccp(0.5f, -1));
				mItemContainer->setPositionY(mItemSize.height * (getItemCount() + 1));
				break;
			case ComboBoxOpenType::open_Down:
				mItemContainer->setAnchorPoint(ccp(0.5f, 0));
				mItemContainer->setPositionY(0);
				break;
			default:
				if (pt.y >= size.height/2)
				{
					mItemContainer->setAnchorPoint(ccp(0.5f, 0));
					mItemContainer->setPositionY(0);
				}
				else
				{
					mItemContainer->setAnchorPoint(ccp(0.5f, -1));
					mItemContainer->setPositionY(mItemSize.height * (getItemCount() + 1));
				}
				break;
			}
			mItemContainer->stopAllActions();
			mItemContainer->setScaleY(0);
			mItemContainer->setScaleX(1);
			mItemContainer->runAction(CCSequence::createWithTwoActions(
				CCShow::create(),
				CCEaseBackOut::create(CCScaleTo::create(0.3f, 1.0f))
				));
		}
	}
}

void CPComboBox::close()
{
	if (mIsOpen)
	{
		mIsOpen = false;
		
		setZOrder(m_zOrder);

		mItemContainer->stopAllActions();
		mItemContainer->runAction(CCSequence::createWithTwoActions(
			CCEaseBackIn::create(CCScaleTo::create(0.3f, 1.0f, 0.0f)),
			CCHide::create()
			));
	}
}

void CPComboBox::onClick( CCObject *target )
{
	if (mIsOpen)
	{
		close();
	}
	else
	{
		open();
	}

	if (mChangeHandler_ && mChangeHandleFunc_)
	{
		(mChangeHandler_->*mChangeHandleFunc_)(this);
	}
}

void CPComboBox::onItem( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int index = node->getTag();
		if (index != mCurrentIndex)
		{
			setCurrentIndex(index);
			if (mChangeHandler && mChangeHandleFunc)
			{
				(mChangeHandler->*mChangeHandleFunc)(this);
			}
		}
		close();
	}
}

void CPComboBox::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
}

bool CPComboBox::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	mIsItemContainerTouched = false;
	if (mIsOpen)
	{
		mIsItemContainerTouched = mItemContainer->ccTouchBegan(pTouch, pEvent);
		close();
		return true;
	}
	return false;
}

void CPComboBox::ccTouchMoved( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (mIsItemContainerTouched)
	{
		mItemContainer->ccTouchMoved(pTouch, pEvent);
	}
}

void CPComboBox::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (mIsItemContainerTouched)
	{
		mItemContainer->ccTouchEnded(pTouch, pEvent);
	}
}

void CPComboBox::ccTouchCancelled( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (mIsItemContainerTouched)
	{
		mItemContainer->ccTouchCancelled(pTouch, pEvent);
	}
}

void CPComboBox::cleanItems()
{
	CCArray *children = mItemContainer->getChildren();
	if (children)
	{
		children->removeAllObjects();
		refresh();
	}
}

void CPComboBox::setDirection( int dir )
{
	m_iOpenDir = dir;
}

void CPComboBox::setChangeHandler_( cocos2d::CCObject *target, cocos2d::SEL_CallFuncN func )
{
	mChangeHandler_ = target;
	mChangeHandleFunc_ = func;
}
