#ifndef __CCTABLE_VIEW_EX__
#define __CCTABLE_VIEW_EX__

#include "cocos-ext.h"
#include "ext/BasePanel.h"
USING_NS_CC_EXT;

class CCTableViewEx : public CCTableView
{
public:
	CCTableViewEx();
	static CCTableViewEx* create(CCTableViewDataSource* dataSource, CCSize size, CCScrollViewDirection direction, CCTableViewDelegate* tableDelegate);
	static CCTableViewEx* create(CCTableViewDataSource* dataSource, CCSize size, CCScrollViewDirection direction, CCTableViewDelegate* tableDelegate, CCNode *container);
	virtual bool initWithViewSize(CCSize size, CCNode* container = NULL);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void setScrollBar(CCScale9Sprite* scrollbar);
	virtual void setScrollBarBackground(CCScale9Sprite* scrollbarbkg);

public:
	virtual bool isNodeVisibleInView(CCNode * node);
	virtual void showTop();
	virtual void showBottom();
	virtual void setIsadjust(bool flag);
	virtual int  getCurPage();
	virtual void setCurPage(int page);
	virtual void setCurPageWithInit(int page);
	virtual void setShouldAddSpeed(bool flag);

protected:
	void	adjustScroll();
	void	adjustScrollBar();
	CCScale9Sprite* m_pScrollBar;
	bool			m_bShowScrollBar;
	int				m_iCurPage;

	bool    m_bAdjust;
	int  m_iSpeed;
	CCPoint m_CurPoint;
	bool	m_bAddSpeed;
};


#endif//__CCTABLE_VIEW_EX__