#ifndef __CPRichText_h__
#define __CPRichText_h__

#include "CCNode.h"
#include <string>

class ICPRichTextItem;
class CPRichText : public cocos2d::CCNode
{
public:
	enum
	{
		AlignLeft = 0,
		AlignCenter = 1,
		AlignRight = 2,
	};
	
public:
	CPRichText();
	~CPRichText();

public:
	static CPRichText *create();
	static CPRichText *create(int width, int height);
	static CPRichText *create(int width, int height, int align);

	void addItem(ICPRichTextItem *item);

private:
	bool initWithData(int width, int height, int align);
	void initUI();

	void addSingleLine(ICPRichTextItem *item);
	void addMultiLine(ICPRichTextItem *item);
	void addToCurrentLine(CCNode *node);

	void adjustCurrentSpaceWidth();
	void makeNewLine();

private:
	CCNode *mContainer;
	CCNode *mCurrentLine;

	int mWidth;
	int mHeight;
	int mAlign;
	int mCurrentSpaceWith;
	int mCurrentHeight;
};

///////////ICPRichTextItem////////////////////////////////////////////////
class ICPRichTextItem
{
public:
	virtual ~ICPRichTextItem(){}
	virtual cocos2d::CCNode *getNextNode(int width) = 0;
};

/////////CPRichTextLabel//////////////////////////////////////////////////
class CPRichTextItemLabel : public ICPRichTextItem
{
public:
	CPRichTextItemLabel(const std::string &text, const std::string &fontName, int fontSize, const cocos2d::ccColor3B &color);
	~CPRichTextItemLabel();

public:
	cocos2d::CCNode *getNextNode(int width);

private:
	std::string mText;
	std::string mFontName;
	int mFontSize;
	cocos2d::ccColor3B mColor;
	bool mHasReturnSpaceNode;
};

//////////CPRichTextItemNode/////////////////////////////////////////////////
class CPRichTextItemNode : public ICPRichTextItem
{
public:
	CPRichTextItemNode(cocos2d::CCNode *node);
	~CPRichTextItemNode();

public:
	cocos2d::CCNode *getNextNode(int width);

private:
	cocos2d::CCNode *mNode;
	bool mHasFinish;
	int mReturnCnt;
};

#endif //__CPRichText_h__