#ifndef __POP_ALERT_PANEL_H__
#define __POP_ALERT_PANEL_H__

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
 
class PopAlertPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate//,public CCTouchDelegate
{
public:
	enum Alert_Type
	{
		Type_Null	=0,
		Type_Small	=1,
		Type_Big	=2,
	};
public:
	PopAlertPanel();
	~PopAlertPanel();
	virtual bool init(int pType,int optionCnt);
	static PopAlertPanel* create(int pType=Type_Small,int optionCnt=2);
	void onEnter();
protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	/*
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	*/
	void initFrame();
	void initLabels();
	void initButtons();
	void initCell(CCTableViewCell *cell);

	void addSubView(CCNode* pChild);
	CCNode* getSubViewByTag(int tag);
public:
	virtual void MenuCallBack(CCObject* pSender);

	void closeSelf();
	void setConfirmTarget(CCObject *rec, SEL_MenuHandler selector);
	void handleConfirmPressed();
	void setString(std::string alert);
	void setConfirmTitle(std::string cTitle);
	void setCancelTitle(std::string cTitle);
	void setCancelTarget(CCObject *rec, SEL_MenuHandler selector);
	void handleCancelPressed();
	void setTitle(std::string cTitle);

	bool isPressConfirm();
	
	void showLine(bool lineVisible);
protected:
	GeneralMenu* m_pMainMenu;
	CCTableViewEx * m_pTableView;

	CCLabelTTF* m_LabelInfo;
	CCLabelTTF* m_LabelPage;
	int m_selIndex;
	CCSprite* m_Arrow;
	CCObject *m_pListener;
	SEL_MenuHandler m_pfnSelector;
	CCObject *m_CancelListener;
	SEL_MenuHandler m_CancelSelector;

	//CCSize m_Size;
	//CCScale9Sprite* m_AlertBg;
	CCSprite* m_AlertBg;
	CCLabelTTF* m_ConfirmTitle;
	CCLabelTTF* m_CancelTitle;
	CCLabelTTF* m_Title;
	CCMenuItemSprite *m_MenuConfirm;
	CCMenuItemSprite *m_MenuCancel;
	CCScale9Sprite* m_Line;

	bool m_PressConfirm;

	int m_Type;
	int m_OptionCount;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Tag_Close,
		Tag_Confirm,
		Tag_Cancel,
		//label
	};
};

#endif//__POP_ALERT_PANEL_H__