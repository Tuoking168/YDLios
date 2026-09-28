#ifndef __ITEM_TOOLTIP_H__
#define __ITEM_TOOLTIP_H__

#include "cocos2d.h"
#include "ext/PartPanel.h"
#include "cocos-ext.h"
#include "event/EventListener.h"
USING_NS_CC_EXT;

enum TipsType
{
	TAG_Tips,					//无
	TAG_Tips_ZBDQ,				//装备和丢弃
	TAG_Tips_XX,				//卸下和丢弃
	TAG_Tips_DQ,				//丢弃
	TAG_Tips_SYDQ,				//使用和丢弃
	TAG_Tips_QX,				//取消
	TAG_Tips_GM,				//购买
	TAG_Tips_HG,				//回购
	TAG_Tips_BTQX,				//摆摊取消
	TAG_Tips_CFQX1,				//存放取消(宠物)
	TAG_Tips_CFQX2,				//存放取消(仓库)
	TAG_Tips_XJQX,				//下架取消
	TAG_Tips_QCQX,				//取出取消
	TAG_Tips_QCQX2,				//取出取消(宠物)
	TAG_Tips_GMQX,				//购买取消(摊位)
	TAG_Tips_JY,				//交易
	TAG_Tips_QXJY,				//取消交易
	TAG_Tips_MC,				//卖出(商店)
	TAG_Tips_TR,				//投入（诛魔结阵）
	TAG_Tips_JRKJJ,				//加入快捷键（诛魔结阵）
	TAG_Tips_ZSQX,				//聊天界面
	TAG_Tips_XXTB,				//卸下和投保
};

struct UserItem;
struct UserPet;

class ItemTooltip :
	public PartPanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	ItemTooltip();
	~ItemTooltip();
	static ItemTooltip* create();

	virtual bool init();
	void setTooltipSkill(int skillID);
	void setTooltipContentbysid(int sid ,int type =0 );
	void setTooltipContent(UserItem* item ,int type =0,bool flag=true);
	void setToolTipPetBase(UserPet* pPet,int type =0,bool flag=true);
	void setTargetAndSeletor(CCObject* target, SEL_MenuHandler selectorOk, SEL_MenuHandler selectorCancel);
    void setTargetAndSeletor(CCObject* target, SEL_MenuHandler selectorOk);
    void setContentText(const char* text);

	void settingButton(CCMenu* pMenu, int type);

	void onEnter();
    void onExit(); 


	void setIscompare(bool flag);
	void setCompareCombatNum(int num);
	/*virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);*/

	void setWaitTime(float time, CCCallFunc* callFun);

	int m_isp1;
private:
	void	initEquipItem(int type,bool flag);
	void	initNormalItem(int type,bool flag);
	void    initPetEggItem(int type,bool flag);
	CCLayer*    initPetHeadItem(UserPet* u_pet);

	int		getCombatNum(UserItem* item);
	int		getCombatTypeNum(int type,int num,int tag=1);

	CCLayer* getEquipInfoLayer(UserItem* item);
	CCLayer* getEquipInfo(UserItem* item,int cntEx=0);
	CCLayer* getOtherInfoLayer(UserItem* item);
	CCLayer* getOtherInfo(UserItem* item,int cntEx=0);
	CCLayer* getSkillInfo();
	CCLayer* getSkillInfoLayer(int skillid);
	CCLayer* getPetEggInfoLayer(UserItem* item);
	CCLayer* getPetEggInfoLayerbyPet(UserPet* Pet);
	CCLayer* getPetEggInfo(UserItem* item,int cntEx=0);
	CCLayer* getPetHeadInfo(UserPet* pPet,int cntEx=0);

	void compareItem();

	void MenuCallBack(CCObject* pSender);
	void closeCallBack(CCObject* pSender);
	void openKeyBorad(int maxCnt,int iid);

	void setfastkey();

	void postBoothDOWN();
	void postItemMoveMsg(int startIndex);
	void postBoothBuy();
	void postTradeItem();
	void postCancelTradeItem();
	void postRemoveItem(int tag);
	void postSellItem();
	void postToubao();
protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	int m_iCurrentTipsType;		//当前tips类型 （物品，技能）
	int m_iCurSkillID;
    CCMenu* m_pMenu;
    bool m_bTouchMenu;
    CCTouch* m_pTouch;
	UserItem* userItem;		//当前物品

	int mHeight;
	int m_iH;
	bool m_bIscompare;
	int m_iCombatNum;
	int m_icntEx;

	CCScale9Sprite* m_pBkg;
	enum TipsType
	{
		SkillTips,
		ItemTips,
		PetTips,
	};
	enum MyEnum
	{
		TAG_UP,
		TAG_DOWN,
		TAG_REMOVE,
		TAG_CANCEL,
		TAG_USE,
		TAG_BUY,
		TAG_BUYBACK,
		TAG_BOOTHUP,
		TAG_BOOTHDOWN,
		TAG_SAVE_PETBAG,
		TAG_TAKE,
		TAG_TAKE_PET,
		TAG_SAVE_NPCBAG,
		TAG_BOOTHBUY,
		TAG_TRADE,
		TAG_CANCELTRADE,
		TAG_SELL,
		TAG_THROW,
		TAG_SET,
		TAG_WATCHOUT,
		TAG_TOUBAO,
	};
};

#endif
