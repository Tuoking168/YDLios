#include "CPRichText.h"
#include "CPNodeHelper.h"

#include "utils/MacroUtils.h"
#include "utils/TestUtils.h"

////////CPRichText///////////////////////////////////////////////////////
CPRichText::CPRichText()
	:mContainer(NULL)
	,mCurrentLine(NULL)
	,mWidth(0)
	,mHeight(0)
	,mCurrentSpaceWith(0)
	,mCurrentHeight(0)
{

}

CPRichText::~CPRichText()
{

}

CPRichText * CPRichText::create()
{
	return create(0, 0);
}

CPRichText * CPRichText::create( int width, int height )
{
	return create(width, height, AlignLeft);
}

CPRichText * CPRichText::create( int width, int height, int align )
{
	CPRichText *ret = new CPRichText;
	if (ret && ret->initWithData(width, height, align))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool CPRichText::initWithData( int width, int height, int align )
{
	if (!CCNode::init())
	{
		return false;
	}

	mAlign = align;
	if (mAlign < AlignLeft)
	{
		mAlign = AlignLeft;
	}
	else if (mAlign > AlignRight)
	{
		mAlign = AlignRight;
	}

	if (width > 0)
	{
		mWidth = width;
		mCurrentSpaceWith = width;
	}

	if (height > 0)
	{
		mHeight = height;
	}

	initUI();

	setContentSize(CCSizeMake(mWidth, mHeight));
	setAnchorPoint(ccp(0.5f, 0.5f));

	return true;
}

void CPRichText::initUI()
{
	mContainer = CCNode::create();
	mContainer->setAnchorPoint(ccp(0, 1));
	mContainer->setPosition(ccp(0, mHeight));
	if (mWidth > 0)
	{
		mCurrentLine = CCNode::create();
		mCurrentLine->setContentSize(CCSizeMake(mWidth, 0));
		mCurrentLine->setAnchorPoint(ccp(0, 1));
		mCurrentLine->setPosition(CCPointZero);
		mContainer->addChild(mCurrentLine);
		if (mHeight > 0)
		{
			CCClippingNode *clippingNode = CPNodeHelper::getClippingNode(CCSizeMake(mWidth, mHeight));
			clippingNode->addChild(mContainer);
			addChild(clippingNode);

			DebugCode(
				addChild(CPNodeHelper::getBorderNode(CCSizeMake(mWidth, mHeight)));
			);
		}
		else
		{
			addChild(mContainer);
		}
	}
	else
	{
		addChild(mContainer);
	}
}

void CPRichText::addItem( ICPRichTextItem *item )
{
	if (!item)
	{
		CCLog(">>>Error, CPRichText::addItem, item = NULL!");
		return;
	}

	//
	if (mWidth > 0 && mHeight > 0)
	{
		if (mCurrentHeight > mHeight)
		{
			CC_SAFE_DELETE(item);
			return;
		}
	}

	//
	if (mWidth <= 0)
	{
		addSingleLine(item);
	}
	else
	{
		addMultiLine(item);
	}
	CC_SAFE_DELETE(item);

	//
	if (mHeight <= 0)
	{
		mContainer->setPosition(ccp(0, getContentSize().height));
	}
}

void CPRichText::addSingleLine( ICPRichTextItem *item )
{
	CCNode *node = item->getNextNode(0);
	if (node)
	{
		CCSize contentSize = getContentSize();
		const CCSize &nodeSize = CCSizeMake(node->getContentSize().width * node->getScaleX(), node->getContentSize().height * node->getScaleY());

		node->setAnchorPoint(CCPointZero);
		node->setPosition(contentSize.width, -nodeSize.height);
		mContainer->addChild(node);

		contentSize.width += nodeSize.width;
		if (nodeSize.height > contentSize.height)
		{
			contentSize.height = nodeSize.height;
		}
		setContentSize(contentSize);
		mCurrentHeight = contentSize.height;
	}
}

void CPRichText::addMultiLine( ICPRichTextItem *item )
{
	CCSize lineSize = CCSizeZero;
	adjustCurrentSpaceWidth();
	CCNode *node = item->getNextNode(mCurrentSpaceWith);
	while (node)
	{
		// add node
		addToCurrentLine(node);

		// content size and space width
		const CCSize &nodeSize = CCSizeMake(node->getContentSize().width * node->getScaleX(), node->getContentSize().height * node->getScaleY());
		lineSize = mCurrentLine->getContentSize();
		if (nodeSize.height > lineSize.height)
		{
			lineSize.height = nodeSize.height;
		}
		mCurrentLine->setContentSize(lineSize);
		mCurrentSpaceWith -= nodeSize.width;

		// next
		adjustCurrentSpaceWidth();
		node = item->getNextNode(mCurrentSpaceWith);
	}

	//
	if (mHeight <= 0 && (int)lineSize.height > 0)
	{
		setContentSize(CCSizeMake(mWidth, mCurrentHeight + lineSize.height));
	}
}

void CPRichText::addToCurrentLine( CCNode *node )
{
	if (mAlign == AlignLeft)
	{
		node->setAnchorPoint(CCPointZero);
		node->setPosition(ccp(mWidth - mCurrentSpaceWith, 0));
	}
	else if (mAlign == AlignCenter)
	{
		const int nodeWidth = node->getContentSize().width;
		float leftOx = (mCurrentSpaceWith - nodeWidth)/2;
		if (leftOx < 0)
		{
			leftOx = 0;
		}

		CCArray *children = mCurrentLine->getChildren();
		if (children && children->count() > 0)
		{
			CCObject *obj = NULL;
			CCARRAY_FOREACH(children, obj)
			{
				CCNode *child = dynamic_cast<CCNode *>(obj);
				if (child)
				{
					child->setPositionX(leftOx);
					leftOx += child->getContentSize().width;
				}
			}
		}
		node->setAnchorPoint(CCPointZero);
		node->setPosition(ccp(leftOx, 0));
	}
	else
	{
		CCArray *children = mCurrentLine->getChildren();
		if (children && children->count() > 0)
		{
			const float ox = node->getContentSize().width;
			CCObject *obj = NULL;
			CCARRAY_FOREACH(children, obj)
			{
				CCNode *child = dynamic_cast<CCNode *>(obj);
				if (child)
				{
					child->setPositionX(child->getPositionX() - ox);
				}
			}
		}
		node->setAnchorPoint(ccp(1, 0));
		node->setPosition(ccp(mWidth, 0));
	}
	mCurrentLine->addChild(node);
}

void CPRichText::adjustCurrentSpaceWidth()
{
	if (mWidth > 0)
	{
		if (mCurrentSpaceWith <= 0)
		{
			mCurrentSpaceWith = mWidth;
			makeNewLine();
		}
	}
}

void CPRichText::makeNewLine()
{
	mCurrentHeight += mCurrentLine->getContentSize().height;

	mCurrentLine = CCNode::create();
	mCurrentLine->setContentSize(CCSizeMake(mWidth, 0));
	mCurrentLine->setAnchorPoint(ccp(0, 1));
	mCurrentLine->setPosition(ccp(0, -mCurrentHeight));
	mContainer->addChild(mCurrentLine);
}

////////CPRichTextLabel///////////////////////////////////////////////
CPRichTextItemLabel::CPRichTextItemLabel( const std::string &text, const std::string &fontName, int fontSize, const cocos2d::ccColor3B &color )
	:mText(text)
	,mFontName(fontName)
	,mFontSize(fontSize)
	,mColor(color)
	,mHasReturnSpaceNode(false)
{

}

CPRichTextItemLabel::~CPRichTextItemLabel()
{

}

cocos2d::CCNode * CPRichTextItemLabel::getNextNode( int width )
{
	if (mText.empty())
	{
		return NULL;
	}

	//
	CCNode *ret = NULL;
	if (width <= 0)
	{
		CCLabelTTF *label = CCLabelTTF::create();
		label->setString(mText.c_str());
		label->setFontName(mFontName.c_str());
		label->setFontSize(mFontSize);
		label->setColor(mColor);
		ret = label;

		mText.clear();
	}
	else
	{
		const std::string &selectstr = "\n";
		const int &subpos = mText.find(selectstr);
		const std::string &newtext = mText.substr(0, subpos);
		CCLabelTTF *label = CPNodeHelper::getLabelByWidth(newtext, mFontName, mFontSize, width);
		const int &len = strlen(label->getString());
		if (len > 0)
		{
			label->setColor(mColor);
			ret = label;   
			mText = mText.substr(len);
			mHasReturnSpaceNode = false;
		}
		else
		{
			if (subpos == 0)
			{
				mText=mText.erase(0, selectstr.length());
			}

			if (!mHasReturnSpaceNode)
			{
				ret = CCNode::create();
				ret->setContentSize(CCSizeMake(width, 0));
				mHasReturnSpaceNode = true;
			}
		}
	}
	return ret;
}

///////////CPRichTextItemNode/////////////////////////////////////////////
CPRichTextItemNode::CPRichTextItemNode( cocos2d::CCNode *node )
	:mNode(node)
	,mHasFinish(false)
	,mReturnCnt(0)
{

}

CPRichTextItemNode::~CPRichTextItemNode()
{

}

cocos2d::CCNode * CPRichTextItemNode::getNextNode( int width )
{
	if (mHasFinish)
	{
		return NULL;
	}

	if (!mNode)
	{
		mHasFinish = true;
		return NULL;
	}

	//
	CCNode *ret = NULL;
	const CCSize &size = CCSizeMake(mNode->getContentSize().width * mNode->getScaleX(), mNode->getContentSize().height * mNode->getScaleY());
	if (mReturnCnt == 0)
	{
		if (width <= 0 || width >= size.width)
		{
			ret = mNode;
			mHasFinish = true;
		}
		else
		{
			ret = CCNode::create();
			ret->setContentSize(CCSizeMake(width, 0));
		}
	}
	else if (mReturnCnt == 1)
	{
		ret = mNode;
		mHasFinish = true;
	}

	mReturnCnt++;
	return ret;
}
