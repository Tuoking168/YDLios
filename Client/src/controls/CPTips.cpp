#include "CPTips.h"
#include "cocos2d.h"


using namespace cocos2d;


CPTips::CPTips()
	:mSubNode(NULL)
	,mType(CPTipsType::autoHide)
{

}

CPTips::~CPTips()
{

}

CPTips * CPTips::create( CPTipsSub *subNode )
{
	return create(subNode, CPTipsType::autoHide);
}

CPTips * CPTips::create( CPTipsSub *subNode, int type )
{
	CPTips *ret = new CPTips;
	if (ret && ret->initWithData(subNode, type))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return ret;
}

bool CPTips::initWithData( CPTipsSub *subNode, int type )
{
	if (!subNode)
	{
		return false;
	}

	mSubNode = subNode;
	mType = type;
	mSubNode->setCloseHandler(this);
	mSubNode->setAnchorPoint(CCPointZero);
	mSubNode->setPosition(CCPointZero);
	addChild(mSubNode);

	setContentSize(mSubNode->getContentSize());
	setAnchorPoint(ccp(0.5f, 0.5f));
	return true;
}

void CPTips::close()
{
	removeFromParent();
}

void CPTips::onEnter()
{
	registerWithTouchDispatcher();
	CCNode::onEnter();
}

void CPTips::onExit()
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}

void CPTips::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher *pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool CPTips::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	const CCPoint &pt = convertTouchToNodeSpace(pTouch);
	const CCSize &size = mSubNode->getContentSize();
	const CCRect &rect = CCRectMake(0, 0, size.width, size.height);
	if (rect.containsPoint(pt))
	{
		return true;
	}

	if (mType == CPTipsType::autoHide)
	{
		close();
	}
	return (mType == CPTipsType::modal);
}

///////CPTipsSub/////////////////////////////////////////////////////
CPTipsSub::CPTipsSub()
	:mCloseHandler(NULL)
{

}

CPTipsSub::~CPTipsSub()
{

}

void CPTipsSub::setCloseHandler( ICloseHandler *handler )
{
	mCloseHandler = handler;
}

void CPTipsSub::close()
{
	if (mCloseHandler)
	{
		mCloseHandler->close();
	}
	else
	{
		removeFromParent();
	}
}
