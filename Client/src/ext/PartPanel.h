#ifndef __PartPanel_h__
#define __PartPanel_h__

#include "cocos2d.h"

USING_NS_CC;

/*
对象：专为当前项目非全屏界面设计。
特点：点击周围非自己区域会自动关闭。
注意：需要手动调用addCover设置吞掉点击层的大小以及position
*/

class PartPanel : public CCLayer
{
public:
	PartPanel();
	virtual ~PartPanel();
	virtual void onEnter();
	virtual void onExit();
	static PartPanel* create();
	virtual bool init();
	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void setIsCheckInPanel(bool flag);
public:
	virtual void addCover(CCPoint Pos = CCPointZero);
	virtual void close();

private:
	virtual bool isPointInThisPanel(CCPoint& point);

protected:
	int m_nWidth;
	int m_nHeight;
	CCPoint m_pPos;
	bool m_bIsCheck;
};
#endif //__PartPanel_h__