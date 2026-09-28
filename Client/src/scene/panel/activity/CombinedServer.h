#ifndef _CombinedServer_H_
#define _CombinedServer_H_	


#include <string>
#include <vector>
#include <map>
#include "ext/Basepanel.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
#include "scene/panel/MenuListPanel.h"
#include "event/EventListener.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CCMenuEx;
class SlideTable;
class CPChecker;

/////////CombinedServer////////////////////////////////////////////
class CombinedServer :public MenuListPanel
{
public:
	CombinedServer();
	~CombinedServer();
	virtual const std::string dataTableName();
	virtual void onCPEvent(const std::string& name);
	virtual void onSwitch(int tag);
	void doSwitch(int tag);
	bool init();
	void hide();
	CREATE_FUNC(CombinedServer);
public:
	enum Panel_Tag
	{
		//panel
		Panel_huodongshouchong = 1,
		Panel_leijichongzhi = 2,
		Panel_chongfuchongzhi = 3,
		Panel_danbichongzhi = 4,
		Panel_huodongshangdian = 5,
		Panel_duihuanshangdian = 6,
		Panel_meirihuikui = 7,
		Panel_yuanbaohuikui = 8,
		Panel_chongwuhuikui = 9,
		Panel_hunshihuikui = 10,
		Panel_chibanghuikui = 11,
		Panel_xunbaohuikui = 12,
		Panel_shizhuanghuikui = 13,
		Panel_huanwuhuikui = 14,
		Panel_qianghuahuikui = 15,
		panel_mashangqianggou = 16,
		panel_fengkuangqianggou = 17,
	};
	std::map<int, int> MakePanelTagScriptMap() const
	{
		std::map<int, int> map;
		map.insert(std::make_pair(Panel_huodongshouchong, 20416));
		map.insert(std::make_pair(Panel_leijichongzhi, 20413));
		map.insert(std::make_pair(Panel_chongfuchongzhi, 20414));
		map.insert(std::make_pair(Panel_danbichongzhi, 20415));
		// map.insert(std::make_pair(Panel_huodongshangdian, ));
		// map.insert(std::make_pair(Panel_duihuanshangdian, ));
		map.insert(std::make_pair(Panel_meirihuikui, 20404));
		map.insert(std::make_pair(Panel_yuanbaohuikui, 20412));
		map.insert(std::make_pair(Panel_chongwuhuikui, 20406));
		map.insert(std::make_pair(Panel_hunshihuikui, 20407));
		map.insert(std::make_pair(Panel_chibanghuikui, 20408));
		map.insert(std::make_pair(Panel_xunbaohuikui, 20409));
		map.insert(std::make_pair(Panel_shizhuanghuikui, 20410));
		map.insert(std::make_pair(Panel_huanwuhuikui, 20411));
		map.insert(std::make_pair(Panel_qianghuahuikui, 20405));
		map.insert(std::make_pair(panel_mashangqianggou,20418));
		map.insert(std::make_pair(panel_fengkuangqianggou,20419));
		return map;
	}
	int PanelTag2ScriptId(int tag) const
	{
		static std::map<int, int> map(MakePanelTagScriptMap());
		std::map<int, int>::const_iterator pos = map.find(tag);
		return pos == map.end() ? tag : pos->second;
	}
	int ScriptId2PanelTag(int nScriptId) const
	{
		static std::map<int, int> map(MakePanelTagScriptMap());
		for (std::map<int, int>::const_iterator iter = map.begin(), end = map.end();
			iter != end; ++ iter)
		{
			if (iter->second == nScriptId)
			{
				return iter->first;
			}
		}
		return nScriptId;
	}
protected:

private:
	enum Child_Tag
	{
		Tag_NULL=0,

		//button
		Button_Close,

		//Cell
		Cell_Start = 100,
		Cell_End = 200,
	};
	CCMenuItem* m_DefaultSelected;
};

///////////////////////////////////////////////////////////////
//----------------------------------活动商店------------------------
class CPItemComponents;
class CPChecker;
class ActivityShop :public BasePanel,public IEventListener
{
public:
	ActivityShop();
	~ActivityShop();

	bool init();

	CREATE_FUNC(ActivityShop);	
private:
	void initUI();	
	void refreshList();
	void itemClicked( CCObject* pSender );
	CCNode *getListItem(int index);
	void handleEvent( int channel );
	void onCPEvent(const std::string &eventName);

	enum ShopPanelOtherTag
	{
		TAG_ITEM_TIPS=-10000,
		TAG_KEYBOARD=-20000,
		TAG_MONEY_NOT_ENOUGH=-30000,
	};
private:
	UserItem  m_clickedItem;
	CPItemComponents *mItemList;
	CCLayer *mStateLayer;

	int	 m_curPrice;
	
};


//----------------------------------兑换商店------------------------
class ExchangeShop : public BasePanel,public IEventListener
{
public:
	 ExchangeShop();
	 ~ExchangeShop();

	 bool init();
	 CREATE_FUNC(ExchangeShop);

private:
	void initUI();
	void refreshList();
	CCNode *getListItem(int index);
	void onItem( CCObject *target );
	void onGetReward(CCObject *target);

	void onCPEvent(const std::string &eventName);

private:
	CCLayer *mTimeStateLayer;
	CCLayer *mStateLayer;
	CPItemComponents *mItemList;
	CPChecker *mChecker;
};

//----------------------------------元宝回馈------------------------
class CCMenuEx;
class YuanbiaoFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	YuanbiaoFeedBack();
	~YuanbiaoFeedBack();

	bool init();
	CREATE_FUNC(YuanbiaoFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};


//-----------------------------------强化回馈-----------------------
class CCMenuEx;
class QianghuaFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	QianghuaFeedBack();
	~QianghuaFeedBack();

	bool init();
	CREATE_FUNC(QianghuaFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};
//----------------------------------宠物回馈------------------------
class CCMenuEx;
class PetFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate,public IEventListener
{
public:
	PetFeedBack();
	~PetFeedBack();

	bool init();
	CREATE_FUNC(PetFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};
//----------------------------------魂石回馈------------------------
class CCMenuEx;
class HunshiFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	HunshiFeedBack();
	~HunshiFeedBack();

	bool init();
	CREATE_FUNC(HunshiFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};

//------------------------------------翅膀回馈----------------------
class CCMenuEx;
class ChibangFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate,public IEventListener
{
public:
	ChibangFeedBack();
	~ChibangFeedBack();

	bool init();
	CREATE_FUNC(ChibangFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};

//---------------------------------寻宝回馈-------------------------
class CCMenuEx;
class XunbaoFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	XunbaoFeedBack();
	~XunbaoFeedBack();

	bool init();
	CREATE_FUNC(XunbaoFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};

//--------------------------------时装回馈---------------------------
class CCMenuEx;
class ShizhuangFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	ShizhuangFeedBack();
	~ShizhuangFeedBack();

	bool init();
	CREATE_FUNC(ShizhuangFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};

//-------------------------------幻武回馈---------------------------
class CCMenuEx;
class HuanwuFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	HuanwuFeedBack();
	~HuanwuFeedBack();

	bool init();
	CREATE_FUNC(HuanwuFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};
//----------------------------------------每日回馈---------------------------------------------
class CCMenuEx;
class DailyFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	DailyFeedBack();
	~DailyFeedBack();

	bool init();
	CREATE_FUNC(DailyFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack(CCObject* pSender);
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};

//--------------------------------疯狂抢购------------------------

class BuyCrazyFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	BuyCrazyFeedBack();
	~BuyCrazyFeedBack();

	bool init();
	CREATE_FUNC(BuyCrazyFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};

//--------------------------------马上抢购------------------------

class BuyImmediatelyFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	BuyImmediatelyFeedBack();
	~BuyImmediatelyFeedBack();

	bool init();
	CREATE_FUNC(BuyImmediatelyFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};

//----------------------------------------------6 19新加活动-----------------------------------------
//------------------------------------------------累计充值-------------------------------------------

class TotalRechargeFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	TotalRechargeFeedBack();
	~TotalRechargeFeedBack();

	bool init();
	CREATE_FUNC(TotalRechargeFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};

//------------------------------------------------------重复充值----------------------------------------

class RepeatRechargeFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	RepeatRechargeFeedBack();
	~RepeatRechargeFeedBack();

	bool init();
	CREATE_FUNC(RepeatRechargeFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};

//--------------------------------------------------------单笔充值--------------------------------

class SingleRechargeFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	SingleRechargeFeedBack();
	~SingleRechargeFeedBack();

	bool init();
	CREATE_FUNC(SingleRechargeFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};

//--------------------------------------------------------活动首冲--------------------------------

class FirstRechargeFeedBack : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	FirstRechargeFeedBack();
	~FirstRechargeFeedBack();

	bool init();
	CREATE_FUNC(FirstRechargeFeedBack);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
	void initUI();
	void onItem( CCObject *target );
	void menuCallBack( CCObject* pSender );
	void onCPEvent(const std::string &eventName);
private:
	CCTableViewEx*	m_pTableView;

};

#endif