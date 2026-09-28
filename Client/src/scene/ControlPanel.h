#ifndef __CONTROL_PANEL_H__
#define __CONTROL_PANEL_H__

#include "ext/CCLayerEx.h"

class ControlPanel : public CCLayerEx
{
public:
	bool init();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void registerWithTouchDispatcher();
	CREATE_FUNC(ControlPanel);

private:
	void refreshControlCenterPostion(CCTouch *touch);

	void onTouchBegin();
	CCPoint getScreenPosition(CCTouch* pTouch);
	bool    isInRange(CCTouch* pTouch);
	void	update(float delta);

	void	inTouch();
	void	outTouch();

private:
	CCSprite* m_pNormalSprite;
	CCSprite* m_pControCenter;
	CCSprite* m_pDimlySprite;
	CCPoint m_center;
	CCPoint m_controlcenter;
	CCPoint mCurrentPt;

public:
	static float m_distance;
	static float m_timetouchkeep;
};
#endif//__CONTROL_PANEL_H__