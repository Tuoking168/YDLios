#ifndef __PetAttribute_PANEL_H__
#define ___PetAttribute_PANEL_H__

// avatar PetAttribute panel

#include "CommonPanel.h"
#include "event/EventListener.h"
#include "ext/GeneralMenuListener.h"
#include "ext/GeneralMenu.h"
#include "ext/CCTabelViewEx.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "userdata/UserPetData.h"
#include "ext/PartPanel.h"
#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CCTableViewEx;
class HorseAttributePanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	HorseAttributePanel();
	virtual ~HorseAttributePanel();
	virtual bool init();
	CREATE_FUNC(HorseAttributePanel);

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
		
	
public:
	CC_PROPERTY(CCLayer*, m_pMainMenu,MainMenu);
	virtual void updateList();

	


protected:
	GeneralMenu* m_pTopMenu;
	GeneralMenu* m_pBottomMenu;
	CCTableViewEx *pTabelView;

	int mHeight;


};

//----------------------------------------------------------------------------------//


class HorseBasePanel: public CCLayer, public EventListener
{
public:
	HorseBasePanel();
	virtual ~HorseBasePanel();
	CREATE_FUNC(HorseBasePanel);
	virtual bool init();
	virtual void initHorseGene();
	virtual void initFirstPart();
	virtual void initSecondPart();

	virtual void handleEvent(int channel);
private:
	void menuCallBack(CCObject* pSender);

	enum MyEnum
	{
		tag_advance,
		tag_speattr,
	};
protected:
	GeneralMenu* m_pFirstMenu;
	GeneralMenu* m_pSecondMenu;
	GeneralMenu* m_pThirdMenu;	
	int mHeight;

	struct GeneLv 
	{
		int id;
		int lv;
		GeneLv(int lv, int id)
		{
			this->lv = lv;
			this->id = id;
		}
	};
	std::vector<GeneLv> m_vecGeneLv;
};
//////////////////////////////////////////////////////////////////////////


class HorseBuffTips : public PartPanel
{
public:
	HorseBuffTips();
	virtual ~HorseBuffTips();
	static HorseBuffTips* create(int tag);
	virtual bool init(int tag);

private:
	int m_iTag;
};


////////////////////////////////////////////////////////////////////////////////////////
//坐骑装备升级界面

class HorseEquipEnhancePanel : public PartPanel, public EventListener
{
public:
	HorseEquipEnhancePanel();
	virtual ~HorseEquipEnhancePanel();
	static HorseEquipEnhancePanel* create(int tag);
	virtual bool init(int tag);
private:
	void initEquip();
	void initExp();
	void blockCallBack(CCObject* pSender);
	void menuAddExpCallBack(CCObject* pSender);
	void menuLevelUpCallBack(CCObject* pSender);
	void menuCancelCallBack(CCObject* pSender);
	void initInfo();
	void equipAddExp(int tag);
	void equipLvlUp(int tag);
	void handleEvent( int channel );
	void addLevelUpEffect();

private:
	bool m_bBlock;
	bool m_bVcoin;
	CCLayer* m_pEquipLayer;
	CCScale9Sprite* m_pExppoint;
	CCMenu* m_pMenu;
	CCSprite* pSprite;
	CCSprite* m_pBkg;
	CCLabelTTF* m_pLabelVcoin;
	CCLabelTTF* m_pLabelPangu;
	CCLabelTTF* m_pLabelKaitian;
	enum tagSpe
	{
		tag_cancel = 0,
		tag_change,
		tag_vcoin,
	};
	int m_equipindex;
};

#endif