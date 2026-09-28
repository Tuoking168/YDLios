#ifndef __ATTRIBUTE_PANEL_H__
#define ___ATTRIBUTE_PANEL_H__

// avatar attrubute panel

#include "CommonPanel.h"
#include "event/EventListener.h"
#include "ext/GeneralMenuListener.h"
#include "ext/GeneralMenu.h"
#include "ext/CCTabelViewEx.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

class CCTableViewEx;
class HeroAvatar;
class AttributePanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	AttributePanel();
	virtual ~AttributePanel();
	virtual bool init(bool isSelf);
	static AttributePanel* create(bool isSelf=true);
	virtual void handleEvent(int channel);

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	
	virtual void callBack(CCObject* pSender); 
	
	
public:
	CC_PROPERTY(CCLayer*, m_pMainMenu,MainMenu);
	virtual void updateList(int tag);


protected:
	GeneralMenu* m_pTopMenu;
	GeneralMenu* m_pBottomMenu;
	CCTableViewEx *pTabelView;
	int m_iCurrentTag;//当前tag
	int m_Height;
	bool m_bIsSelf;
	CCLabelAtlas* m_pCombatNum;

public:
	enum TAG_CLICK_BUTTON
	{
		TAG_PROP_SWITCH_BASE = 10,
		TAG_PROP_SWITCH_ADDITION
	};

private:
	static AttributePanel* attributePanel;
};

//----------------------------------------------------------------------------------//


class BaseMenu:public CCLayer
{
public:
	BaseMenu();
	virtual ~BaseMenu();
	static BaseMenu* create(bool isSelf);
	virtual bool init(bool isSelf);
	virtual void initFirstPart();
	virtual void initSecondPart();
	virtual void initThirdPart();
	virtual void handleEvent(int channel);

	virtual void initBuffPart();

protected:
	bool m_bIsSelf;

	int m_iFirstHeight;
	int m_iBuffHeight;
	int m_iSecondHeight;
	int m_iThirdHeight;

};

//------------------------------------------------------------------------------------//

class AdditonMenu:public CCLayer
{
public:
	AdditonMenu();
	virtual ~AdditonMenu();
	static AdditonMenu* create(bool isSelf);
	virtual bool init(bool isSelf);
	virtual void initFirstPart();
	virtual void initSecondPart();
	virtual void initThirdPart();
	virtual void initFourthPart();

private:
	CCLabelTTF* getSingleLabel(int type,int value,std::string name,bool flag=true);

	std::vector<int> checkFirst(int lvl);//判断身上装备哪些符合条件
	int checkSecond(int lvl);//判断几个魂石符合条件
	int checkEnhanceSize();

protected:
	int m_iFirstHeight;
	int m_iSecondHeight;
	int m_iThirdHeight;
	int m_iFourthHeight;

	bool m_bIsSelf;
};

#endif