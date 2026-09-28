#include "CBHCpanel.h"

CBHCpanel::CBHCpanel( void )
{

}

CBHCpanel::~CBHCpanel( void )
{

}

CBHCpanel* CBHCpanel::create()
{
	CBHCpanel* p=new CBHCpanel;
	if (p && p->init(""))
	{
		p->autorelease();
		return p;
	}
	if (p)
	{
		delete p;
	}
	return NULL;
}

bool CBHCpanel::init( const char* filename )
{
	return true;
}

void CBHCpanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool CBHCpanel::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void CBHCpanel::ccTouchMoved( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void CBHCpanel::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void CBHCpanel::ccTouchCancelled( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void CBHCpanel::visit()
{
	CCNode::visit();
}
