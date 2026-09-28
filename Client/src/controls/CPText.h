#ifndef __CPText_h__
#define __CPText_h__

#include "CCNode.h"
#include "CCMenuItem.h"
#include "CCLabelTTF.h"
#include <string>

class CPText : public cocos2d::CCNode
{
public:
	CPText();
	~CPText();

public:
	static CPText *create(int width, int height,int defaultnum=0);

	void setHandler(cocos2d::CCObject *target, cocos2d::SEL_MenuHandler func);
	void setLabelStyle(const std::string &fontName, float fontSize, const cocos2d::ccColor3B &color);
	void setDefaultNum(int num);
	int  getDefaultNum();
private:
	bool initWithData(int width, int height,int defaultnum);

	void onClick(cocos2d::CCObject *target);
private:
	int m_iWidth;
	int m_iHeight;
	int m_DefaultNum;
	cocos2d::CCObject *mTarget;
	cocos2d::SEL_MenuHandler mHandleFunc;
	cocos2d::CCLabelTTF* m_pLabel;
	cocos2d::CCMenuItemImage* m_pMenuItem;
};

#endif //__CPText_h__