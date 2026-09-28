/********************************************************************
	created:	2013/10/23 14:59 
	filename: 	D:\work\fire\trunk\Client\src\scene\panel\TreasureHuntPanel.h
	file path:	D:\work\fire\trunk\Client\src\scene\panel
	file base:	TreasureHuntPanel
	file ext:	h
	author:		tom
	
	purpose:	1. Use YB to hunt for treasures like Equips, Weapons, Diamonds and so on.
				2. Deliver some the information of the player like YB left and happiness index.
*********************************************************************/
#ifndef __TREASURE_HUNT_PANEL_H__
#define __TREASURE_HUNT_PANEL_H__

#include "FullScreenPanel.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
#include "event/EventListener.h"
#include "utils/MacroUtils.h"
USING_NS_CC_EXT;

class GeneralMenu;
class CPItemComponents;
class TreasureHuntPanel : public FullScreenPanel, public EventListener 
{
public:
	TreasureHuntPanel();
	~TreasureHuntPanel();
	bool init();
	void onEnterTransitionDidFinish();
	CREATE_FUNC(TreasureHuntPanel);
	void onEnter();
	void onExit();
	 void recoverButtonColor(CCObject* pBtn);//恢复按钮颜色的函数
protected:
	void handleEvent(int channel);
	void onCPEvent(const std::string &eventName);
protected:
	enum TreasureHuntTag
	{
		TAG_TREASURE_HUNT_1,
		TAG_TREASURE_HUNT_10,
		TAG_TREASURE_HUNT_50,
		TAG_TREASURE_DEPOT,
	};

protected:
	void buildTitles();
	void buildBorders();
	void buildGrids();
	void buildLabels();
	void buildHuntButtons();
	void buildSprites();
	void buildHappinessIndex();
	void buildHuntHistory();
	void showTreasures();
	void updateGold();
	void updateCapacityOfDepot();
	void updateHappiness();
	void updateMyHuntHistory();
	void updateAllHuntHistory();
	void huntCallback(CCObject* pSender);
	void rechageCallback(CCObject* pSender);
	void openDepot();
	void huntTreasure(int type);
	void itemClickCallback(CCObject* pSender);

	void addListItem(int i );
	void addListFinish();
private:
	CCLabelTTF* m_pGold;
	CCLabelTTF* m_pDepotCapacity;
	CCScale9Sprite* m_pHappiness;
	CPItemComponents *mMyRecordList;
	CPItemComponents *mAllRecordList;
	GeneralMenu*	m_pTreasureListMenu;
	UserItem m_clickedItem;

	CPUpdater *	m_updater;
};

/////////TreasureHuntHelper//////////////////////////////////////////////
class TreasureHuntHelper
{
public:
	static std::string getRecord(int index, bool isMy);

private:
	CP_MAKE_STATIC_CLASS(TreasureHuntHelper);
};
#endif//__TREASURE_HUNT_PANEL_H__