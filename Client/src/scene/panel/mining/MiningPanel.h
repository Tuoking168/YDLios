#ifndef __MINING_PANEL_H__
#define __MINING_PANEL_H__

/*
功能：行会
*/

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "event/IEventListener.h"

USING_NS_CC_EXT;

//-----------------------------------------------------------------------------------------------------------------------------------------------//
/*
功能：
*/
 typedef std::map<int,int> RewardList;
class MiningPanel : public BasePanel, public IEventListener
{
public:
	MiningPanel();
	~MiningPanel();
	virtual bool init(const char* filename);
	static MiningPanel* create();
	void onCPEvent(const std::string &eventName);
protected:

	void initFrame();
	void initLabels();
	void initButtons();
	void reloadData();
public:
	virtual void MenuCallBack(CCObject* pSender);

	void closeSelf();
	void setConfirmTarget(CCObject *rec, SEL_MenuHandler selector);
	void handleConfirmPressed();
	void setString(std::string alert);
protected:
	GeneralMenu* m_pMainMenu;

	CCLabelTTF* m_LabelInfo;
	CCLabelTTF* m_LabelPage;
	int m_selIndex;
	CCSprite* m_Arrow;
	CCObject *m_pListener;
	SEL_MenuHandler m_pfnSelector;
	RewardList m_reward;
	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Tag_Close,
		Tag_BackToCity,
		Tag_BackToCityGo,
		Tag_Strengthen,
		Tag_BackToMine,
		Tag_BackToMineGo,
		//label
		Label_Money_Start,
		Label_Ore_Cu,
		Label_Ore_Fe,
		Label_Ore_Ag,
		Label_Ore_Au,
		Label_Ingot_Cu,
		Label_Ingot_Fe,
		Label_Ingot_Ag,
		Label_Ingot_Au,
		Label_Money_End,

		Label_Material_Start,
		Label_Stone_Fe,
		Label_Stone_Green,
		Label_Stone_Diamond,
		Label_Stone_Purple,
		Label_Stone_Soul,
		Label_Material_End,

		Label_Rare_Start,
		Label_Hoe_Ag,
		Label_Hoe_Au,
		Label_bottle_dust,
		Label_Rare_End,
	};
};

#endif//__MINING_PANEL_H__