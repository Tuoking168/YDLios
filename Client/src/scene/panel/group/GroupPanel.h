#ifndef __GROUP_PANEL_H__
#define __GROUP_PANEL_H__


#include "ext/BasePanel.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

class CCTableViewEx;

class GroupPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	GroupPanel();
	~GroupPanel();
	bool init();
	CREATE_FUNC(GroupPanel);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

protected:
	void callback(CCObject* pSender);

private:
	CCTableViewEx* m_pGroupTable;
};

#endif//__GROUP_PANEL_H__