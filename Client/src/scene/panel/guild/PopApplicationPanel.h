#ifndef __POP_APPLICATION_H__
#define __POP_APPLICATION_H__

/*
功能：行会
*/

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "MsgQuest.h"
#include "event/IEventListener.h"

USING_NS_CC_EXT;

//-----------------------------------------------------------------------------------------------------------------------------------------------//
/*
功能：
*/

typedef std::vector< std::string > StringVector;
typedef std::vector< int > IntVector;
class PopApplicationPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate, public IEventListener
{
public:
	PopApplicationPanel();
	~PopApplicationPanel();
	virtual bool init(const char* filename);
	static PopApplicationPanel* create();
	void onCPEvent(const std::string &eventName);
protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent );
	virtual void ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent );

	void initFrame();
	void initLabels();
	void initButtons();
	void initCell(CCTableViewCell *cell);
	void setData(std::string vkey);
	void loadCell(CCTableViewCell *cell,unsigned int idx);
public:
	virtual void MenuCallBack(CCObject* pSender);

	void closeSelf();
	void setConfirmTarget(CCObject *rec, SEL_MenuHandler selector);
	void handleConfirmPressed();
	void setString(std::string alert);
protected:
	GeneralMenu* m_pMainMenu;
	CCTableViewEx * m_pTableView;
	CCSprite* m_AlertBg;

	CCLabelTTF* m_LabelInfo;
	CCLabelTTF* m_LabelPage;
	int m_selIndex;
	CCSprite* m_Arrow;
	CCObject *m_pListener;
	SEL_MenuHandler m_pfnSelector;

	StringVector m_Namedata;
	IntVector m_lvlData;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Tag_Close,
		Tag_Confirm,
		Tag_Cancel,
		Tag_Refuse_All,
		//label
		//cell
		Cell_Name,
		Cell_Level,
	};
};

#endif//__POP_APPLICATION_H__