#ifndef __TOUCH_COVER_H__
#define __TOUCH_COVER_H__

#include "cocos2d.h"
using namespace cocos2d;

/**
 * 全局窗口矩形定义
 * 描述：定义一个静态的窗口矩形，用于表示全屏显示区域
 * 坐标和尺寸说明：
 *  - CCRectMake(x, y, width, height) 创建矩形
 *  - x=0: 矩形左上角X坐标为0（屏幕左边缘）
 *  - y=0: 矩形左上角Y坐标为0（屏幕下边缘，Cocos2d-x坐标系原点在左下角）
 *  - width=520: 矩形宽度为520像素
 *  - height=1200: 矩形高度为1200像素
 * 
 * 注释分析：
 *  - 注释"全屏 480 800"表示原始设计分辨率为480×800
 *  - 实际设置的宽度600和高度1200可能是经过换算后的分辨率
 *  - 注意：宽高比600:1200 ≈ 1:2.307，而480:800 = 1:1.667
 *  - 这可能是为了适应不同屏幕比例做的调整
 * 
 * 使用场景：
 *  - 可能用于全屏窗口的裁剪区域
 *  - 可能用于视口设置或屏幕适配
 */
static CCRect WindowRect = CCRectMake(0, 0, 480, 800); // 全屏 480×800（原设计分辨率）改

class TouchCover : public CCLayer
{
public:
	TouchCover();
	static TouchCover* create(CCRect& innerRect,CCRect& outlineRect = WindowRect);
	bool	initWithRect(CCRect& innerRect,CCRect& outlineRect);
	virtual void onEnter();
	void setoutlineRect(const CCRect& outlineRect);

	void setTouchPriority(int priority);
protected:
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void registerWithTouchDispatcher();
	virtual bool isTouchInInnerRect(CCPoint touchpos);
	virtual bool isTouchInOutlineRect(CCPoint touchpos);
	virtual bool isSwallowTouch(CCPoint touchpos);

private:
	CCRect m_innnerRect;
	CCRect m_outlineRect;
	int m_nPriority;
};
	

#endif  // __TOUCH_COVER_H__