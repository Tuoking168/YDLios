#ifndef _RankPanel_H_
#define _RankPanel_H_	

#include <string>
#include <vector>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "scene/panel/FullScreenPanel.h"
#include "ext/basepanel.h"
#include "ext/CCTabelViewEx.h"
USING_NS_CC_EXT;


class RankPanel :public FullScreenPanel
{
public:
	RankPanel();
	~RankPanel();
	CREATE_FUNC(RankPanel);
	//static RankPanel* create();
	virtual void onSwitch(int tag);
	bool init();
	void onEnter();
	void hide();
	virtual void onCPEvent(const std::string &eventName);
	
protected:

private:
	CCLabelTTF* m_pSelfRankLabel;
};

///-----------------------------------------------------------------------------------------------------------//

class RankLeftPanel :public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	RankLeftPanel();
	~RankLeftPanel();
	CREATE_FUNC(RankLeftPanel);
	//static RankLeftPanel* create();
	bool init();

private:
	void initBtn();
	void initLabel();
	void BtnCB(CCObject* pSender);
	void LabelCB(CCObject* pSender);
protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	int m_iCurType;
	GeneralMenu* m_pBtnMenu;
	CCTableViewEx* m_pTableView;

	enum MyEnum
	{
		r_combatnum,
		r_level,
		r_pet,
		r_money,
		r_guild,
		r_firework,
	};
};

///-----------------------------------------------------------------------------------------------------------//

class RankRightPanel :public BasePanel,public IEventListener
{
public:
	RankRightPanel();
	~RankRightPanel();
	CREATE_FUNC(RankRightPanel);
	//static RankRightPanel* create();
	bool init();
	void initTop();
	void onCPEvent(const std::string &eventName);
private:
	void shouyeCB(CCObject* pSender);
	void shangyiyeCB(CCObject* pSender);
	void xiayiyeCB(CCObject* pSender);
	void moyeCB(CCObject* pSender);
	CCMenuItemImage* getSingleInfo(int number);
	void addInfoByPage();
	void addSingleInfo(int number);
	void singleCB(CCObject* pSender);
	void updateMaxPage();

	CCMenuItemImage* getSingleInfoByCombatNum(int number);
	CCMenuItemImage* getSingleInfoByLevel(int number);
	CCMenuItemImage* getSingleInfoByPet(int number);
	CCMenuItemImage* getSingleInfoByMoney(int number);
	CCMenuItemImage* getSingleInfoByGuildLevel(int number);
	CCMenuItemImage* getSingleInfoByGuildYLT(int number);
	CCMenuItemImage* getSingleInfoByFireWork(int number);
	

private:
	CCLayer* m_pTopLabel;
	GeneralMenu* m_pInfoMenu;
	int m_iCurPage;
	int m_iMaxPage;
	int m_iMinPage;
	int m_iListSize;
	CCPoint pos[10];
	CCLabelTTF* m_pPage;
};

#endif//_RankPanel_H_