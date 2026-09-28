#ifndef __POP_PULLDOWN_PANEL_H__
#define __POP_PULLDOWN_PANEL_H__

/*
功能：行会
*/

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "MsgQuest.h"

USING_NS_CC_EXT;

//-----------------------------------------------------------------------------------------------------------------------------------------------//
/*
功能：
*/
typedef std::vector< std::string > StringVector;
class PopPullDownTable : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	PopPullDownTable();
	~PopPullDownTable();
	virtual bool init(const char* filename);
	static PopPullDownTable* create();

	void setData(std::string vkey);
protected:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	void initFrame();
	void initLabels();
	void initButtons();
	void initCell(CCTableViewCell *cell);
	void loadCell(CCTableViewCell *cell,unsigned int idx);

public:
	virtual void MenuCallBack(CCObject* pSender);
	void setTitlePanel(BasePanel* mPanel);
protected:
	CCTableViewEx * m_pTableView;
	int m_selIndex;
	CCSprite* m_Arrow;
	CCSize m_Size;
	bool m_Show;
	StringVector m_data;

	BasePanel* m_TitlePanel;

	enum Child_Tag
	{
		Tag_NULL=0,
		Cell_Nickname,
	};
};

class PopPullDownPanel : public BasePanel//, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	PopPullDownPanel();
	~PopPullDownPanel();
	virtual bool init(const char* filename);
	static PopPullDownPanel* create();

protected:
	/*
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	*/

	void initFrame();
	void initLabels();
	void initButtons();
	void initCell(CCTableViewCell *cell);
	void showTipTable(CCPoint curPoint);
	void hideTipTable();
	
public:
	virtual void MenuCallBack(CCObject* pSender);
	void PullDown();
	void PullUp();
	void setNickname(int job);
	void setShowMode(bool mShow);
	void setOwnerPID(int mPid);
protected:
	//CCTableViewEx * m_pTableView;
	CCLabelTTF *m_pLabel;
	CCLabelTTF* m_LabelInfo;
	CCLabelTTF* m_LabelPage;
	int m_selIndex;
	CCSprite* m_Arrow;
	CCSize m_Size;
	bool m_Show;
	int m_Pid;

	PopPullDownTable* m_pTipTable;
};

#endif//__POP_PULLDOWN_PANEL_H__