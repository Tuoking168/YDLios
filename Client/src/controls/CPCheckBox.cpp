#include "CPCheckBox.h"
#include "cocos2d.h"

using namespace cocos2d;

CPCheckBox::CPCheckBox()
	:mSelFlag(NULL)
	,mLabel(NULL)
	,mTarget(NULL)
	,mHandleFunc(NULL)
	,m_bEnable(true)
{
	
}

CPCheckBox::~CPCheckBox()
{

}

CPCheckBox * CPCheckBox::create( CCMenuItem *item, CCNode *selFlag )
{
	return create(item, selFlag, NULL);
}

CPCheckBox * CPCheckBox::create( CCMenuItem *item, CCNode *selFlag, CCLabelTTF *label )
{
	CPCheckBox *ret = new CPCheckBox;
	if (ret && ret->initWithData(item, selFlag, label))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool CPCheckBox::initWithData( CCMenuItem *item, CCNode *selFlag, CCLabelTTF *label )
{
	if (item && selFlag)
	{
		if (CCNode::init())
		{
			const CCSize &itemSize = item->getContentSize();
			item->setTarget(this, menu_selector(CPCheckBox::onClick));
			item->setAnchorPoint(ccp(0, 0.5f));
			CCMenu *menu = CCMenu::create(item, NULL);
			menu->setPosition(CCPointZero);
			addChild(menu);

			//
			selFlag->setVisible(false);
			selFlag->setAnchorPoint(ccp(0, 0.5f));
			addChild(selFlag, 1);
			mSelFlag = selFlag;

			//
			CCSize contentSize = itemSize;
			if (label)
			{
				label->setAnchorPoint(ccp(0, 0.5f));
				addChild(label);
				mLabel = label;

				const CCSize &labelSize = label->getContentSize();
				contentSize.width += labelSize.width;
				if (labelSize.height > contentSize.height)
				{
					contentSize.height = labelSize.height;
				}
				label->setPosition(ccp(itemSize.width/2+contentSize.height/2, contentSize.height/2));
			}

			item->setPosition(ccp(0, contentSize.height/2));
			selFlag->setPosition(item->getPosition());
			
			item->setContentSize(contentSize);

			setContentSize(contentSize);
			setAnchorPoint(ccp(0.5f, 0.5f));

			return true;
		}
	}
	return false;
}

void CPCheckBox::setHandler( CCObject *target, SEL_MenuHandler func )
{
	mTarget = target;
	mHandleFunc = func;
}

void CPCheckBox::setChecked( bool checked )
{
	if (mSelFlag)
	{
		mSelFlag->setVisible(checked);
	}
}

bool CPCheckBox::isChecked() const
{
	if (mSelFlag)
	{
		return mSelFlag->isVisible();
	}
	return false;
}

void CPCheckBox::onClick( CCObject *target )
{
	if (!m_bEnable)
	{
		return;
	}
	if (mSelFlag)
	{
		mSelFlag->setVisible(!mSelFlag->isVisible());
	}

	if (mTarget && mHandleFunc)
	{
		(mTarget->*mHandleFunc)(this);
	}
}

cocos2d::CCLabelTTF * CPCheckBox::getLabel() const
{
	return mLabel;
}

void CPCheckBox::setEnable( bool flag )
{
	m_bEnable = flag;
}

