#ifndef __Emigrated_PANEL_H__
#define __Emigrated_PANEL_H__

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "userdata/activitydata/EmigratedData.h"
#include "ext/CCTabelViewEx.h"
#include "event/IEventListener.h"
#include "scene/panel/FullScreenPanel.h"
USING_NS_CC_EXT;


class HeroModel;

struct emigratedmap
{
	int stepcount;
	std::string direction;
};

class EmigratedPanel : public BasePanel,public IEventListener
{
public:
	CREATE_FUNC(EmigratedPanel);
	//static EmigratedPanel* create();
	EmigratedPanel();
	~EmigratedPanel();
	bool init();

	void onEnter();
private:
	void initInterFace();
	void initMap();
	void initRightTop();
	void initRightDown();
	void menucallback(CCObject* pObject);
	void onCPEvent(const std::string &eventName);

	BasePanel* rightTopPanel;
	CCLayer* pLayer;

	enum buttontype
	{
		button_close	=0,
	};
};

//-------------------------------------------------------------------------------//
class EmigratedLeftMapPanel : public BasePanel, public IEventListener
{
public:
	static EmigratedLeftMapPanel* create();
	EmigratedLeftMapPanel();
	~EmigratedLeftMapPanel();
	bool init();

private:
	void initInterFace();
	void initMap();
	void initButton();
	void menucallback(CCObject* pObject);
	void itemcallback(CCObject* pObject);
	void onAddCount(int buttonType);
	void floatpanelCallback(int tag);
	void floatpanelCallback2(int tag);
	void addRollPanel();
	void addCase();
	virtual void handleEvent(int channel);
	void onCPEvent(const std::string &eventName);

	void updateRolePos();
	CCPoint getRolePos(int pos);
	int getRoleIndex(int pos);
	void getCrossPos(int startindex,int endindex);
	void updatetime(int index);
	void finishtime();

	void postrandomroll();
	void postfreshtime();
	void postaddcount();
	void postwalkover();

	void restartRequest();

	enum buttontype
	{
		button_randomroll	=0,
		button_selectroll	=1,
		button_chongzhiroll = 2,
		button_addtime		,
		button_addcount	,
		sprite_dice,
	};

	CCLabelTTF* m_pTitleLabel;
	CCLabelTTF* m_pCntLabel;
	HeroModel*	 m_heroModel;
	GeneralMenu* m_pCaseMenu;
	CCNode* m_pHeroPanel;
	std::map<int,CCPoint> m_mAllMapPos;
	std::vector<CCPoint> m_vCrossPos;
	int m_iCurPos;
	bool m_bIsActionOver;
	bool m_bIsCreateOver;
	CCSprite* m_pDiceSprite;
	CCLabelTTF* m_pTimeLabel;
	int m_iTime;
};

//-----------------------------------------------------------------------------------------//
class EmigratedRightTopPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	static EmigratedRightTopPanel* create();
	EmigratedRightTopPanel();
	~EmigratedRightTopPanel();
	bool init();

private:
	void initInterFace();
	void initTaskPanel();

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	int m_iHeight;
};

//----------------------------------------------------------------------------------------------//
class EmigratedRightDownPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	static EmigratedRightDownPanel* create();
	EmigratedRightDownPanel();
	~EmigratedRightDownPanel();
	bool init(); 

private:
	void initInterFace();
	virtual void handleEvent(int channel);
	CCLayer* getCaseList();
	CCSprite* getCaseSprite(stepcase caseinfo);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	int m_iHeight;
	CCTableViewEx* m_pTabelView;
};

//----------------------------------------------------------------------------------------------------//
class EmigratedRollPanel : public BasePanel
{
public:
	static EmigratedRollPanel* create();
	EmigratedRollPanel();
	~EmigratedRollPanel();
	bool init();

private:
	void initInterFace();
	void menucallback(CCObject* pSender);
	void initrollPanel();
	void initrollborder();

	void postselectnum();
	int m_iCurSelect;
	GeneralMenu* m_pRollMenu;
	enum buttontype
	{
		button_close	=0,
		button_ok,
		button_cancel,

		button_num1	=11,
		button_num2	=12,
		button_num3	=13,
		button_num4	=14,
		button_num5	=15,
		button_num6	=16,

		border_num1 =21,
	};
};

//------------------------------------------------------------------------------------------------------------//
class EmigratedContentPanel : public BasePanel
{
public:
	static EmigratedContentPanel* create();
	EmigratedContentPanel();
	~EmigratedContentPanel();
	bool init();

	void setContent(int num);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
	void menucallback(CCObject* pSender);

	enum MyEnum
	{
		button_close	=	0,
	};

};

//-------------------------------------------------------------------------------------------------------------------------------------------------//
class EmigratedRightTopPanelTask : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	static EmigratedRightTopPanelTask* create();
	EmigratedRightTopPanelTask();
	~EmigratedRightTopPanelTask();
	bool init();
	void initBtn(CCLayer* pLayer);
//	void MenuCallBack(CCObject* pSender);
	void quickFinishQuest( CCObject* pSender );
	void quickFinishCB2(CCObject* pSender);
	void quickFinishCB(int tag);
	void gotoNPC(CCObject* pSender);
private:
	void initTaskPanel();

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	int m_iHeight;
	int m_iCurrentQuestID;
	static EmigratedRightTopPanelTask* refresh();
};





#endif//__Emigrated_PANEL_H__