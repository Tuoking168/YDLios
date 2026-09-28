#include "BaseElement.h"
#include "cocos2d.h"
#include "ElementDefinition.h"

using namespace cocos2d;


BaseElement::BaseElement()
	:mContainer(NULL)
	,mID(0)
	,mType(CPElement::Type::null)
{

}

BaseElement::~BaseElement()
{

}

bool BaseElement::initWithData( int id, int type )
{
	if (!CCNodeRGBA::init())
	{
		return false;
	}
	mID = id;
	mType = type;

	initUI();

	return true;
}

void BaseElement::initUI()
{
	mContainer = CCNode::create();
	addChild(mContainer);
}

void BaseElement::setColor( const cocos2d::ccColor3B &color )
{
	CCNodeRGBA::setColor(color);

	CCArray *children = mContainer->getChildren();
	if (children && children->count() > 0)
	{
		CCObject *object = NULL;
		CCARRAY_FOREACH(children, object)
		{
			CCSprite *sprite = dynamic_cast<CCSprite *>(object);
			if (sprite)
			{
				sprite->setColor(color);
			}
		}
	}
}

void BaseElement::setOpacity( GLubyte opacity )
{
	CCNodeRGBA::setOpacity(opacity);

	CCArray *children = mContainer->getChildren();
	if (children && children->count() > 0)
	{
		CCObject *object = NULL;
		CCARRAY_FOREACH(children, object)
		{
			CCSprite *sprite = dynamic_cast<CCSprite *>(object);
			if (sprite)
			{
				sprite->setOpacity(opacity);
			}
		}
	}
}

cocos2d::CCNode * BaseElement::getContainer()
{
	return mContainer;
}

int BaseElement::getID() const
{
	return mID;
}

int BaseElement::getType() const
{
	return mType;
}
