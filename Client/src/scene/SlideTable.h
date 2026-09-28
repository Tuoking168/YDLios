/********************************************************************
	created:	2013/09/09 17:56 
	filename: 	D:\work\fire\trunk\Client\src\scene\SlideTable.h
	file path:	D:\work\fire\trunk\Client\src\scene
	file base:	SlideTable
	file ext:	h
	author:		Tom
	
	purpose:	1.create two dimension array to display some elements
				2.implement the turn page function	
*********************************************************************/

#ifndef __SLIDE_TABLE_H__
#define __SLIDE_TABLE_H__

#include "cocos2d.h"
USING_NS_CC;

class CCMenuEx;
class SlideTable : public CCLayer
{
public:
	//create one table
	//param: width,height are the size of the view
	//param: row and collomn are numbers of row and collomn of the elements
	//param: spanW and spanH are the distance between tow adjacent elements
	static SlideTable* create(int beginx, int beginy, int width, int height, int row, int collomn, int spanW, int spanH);
	SlideTable();
	~SlideTable();
	void onEnter();
	void registerWithTouchDispatcher();
	bool init(int beginx, int beginy, int width, int height, int row, int collomn, int spanW, int spanH);
	//add one element
	void addElement(CCNode* pElement);
	//remove all the elements
	void clear();
	//add touch cover
	void addCover();
	//get the current page number
	int getCurPage();

	bool isScrolling();

	void setPageFlagVisible(bool pVisibility);
	void setPageChangeTarget(CCObject *rec, SEL_MenuHandler selector);
	int getTotalPage();
	void handlePageChanged();
	void setCurPage(int pPage);
public:
	//implement the sliding page effect
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

protected:
	void updatePageFlag(int curPage);
	void adjustPagePosition();

private:
	int				m_nCurPage;
	CCNode*			m_pMovingNode;
	int				m_prePosX;
	int				m_nStartX;
	int				m_nTotalNum;
	int				m_nPageSize;
	int				m_nLineSize;
	int				m_nViewLeft;
	int				m_nViewRight;
	int				m_nViewBottom;
	int				m_nViewTop;
	int				m_nSpanW;
	int				m_nSpanH;
	int				m_nPageNum;
	CCPoint			m_beginPos;
	CCMenuEx*		m_pMenu;
	CCNode*			m_pNodeContainer;
	std::vector<CCMenuItem*> m_pPageFlags;

	CCObject *m_pListener;
	SEL_MenuHandler m_pfnSelector;
	bool m_PageFlagVisible;

#define EXACT_X 10
#define EXACT_Y 10
	CCPoint		m_ScrollStartPos;
	bool		m_isScrolling;
};


#endif//__SLIDE_TABLE_H__