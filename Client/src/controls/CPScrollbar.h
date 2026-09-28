#ifndef __CPScrollbar_h__
#define __CPScrollbar_h__

#include "CCNode.h"
#include "GUI//CCControlExtension/CCScale9Sprite.h"

class CPScrollbar : public cocos2d::CCNode
{
public:
	CPScrollbar();
	~CPScrollbar();

public:
	static CPScrollbar *create(cocos2d::extension::CCScale9Sprite *bar, cocos2d::CCSize size);
	static CPScrollbar *create(cocos2d::extension::CCScale9Sprite *bar, cocos2d::CCSize size, bool vertical);

	void setMaxPosition(float pos);
	void setCurrentPosition(float pos);

private:
	bool initWithData(cocos2d::extension::CCScale9Sprite *bar, cocos2d::CCSize size, bool vertical);
	void initUI();
	void refreshUI();

	void visit();

private:
	cocos2d::extension::CCScale9Sprite *mBar;
	cocos2d::CCSize mArea;

	bool mVertical;
	float mMaxPosition;
	float mCurrentPosition;
};
#endif //__CPScrollbar_h__