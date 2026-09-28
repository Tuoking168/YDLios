#ifndef __MINI_MAP_PANEL__
#define __MINI_MAP_PANEL__


#include "FullScreenPanel.h"

class CPItemComponents;
class MiniMapPanel : public FullScreenPanel
{
public:
	MiniMapPanel();
	CREATE_FUNC(MiniMapPanel);

	bool init();
	void onEnter();
	void onExit();

public:
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

private:
	void initUI();
	void showCurrentMap();
	void showWorldMap();
	void refreshCurrentMap();
	void refreshMySign(float dt);

	void buildPortalSign();
	void buildEntitySign();
	void buildBossSign(int monsterID, int posX, int posY);
	void buildMySign();

	void onCurrentMap(CCObject *target);
	void onWorldMap(CCObject *target);
	void onNPC(CCObject *target);
	void onWorldMapIcon(CCObject *target);
	void onWorldTeleport(CCObject *target);
	void onNPCTeleport(CCObject* pSender);

	bool isInMap(const CCPoint &pos);
	void moveTo(const CCPoint &pos);
	CCPoint getLocalPt(const CCPoint &pt);

	void onCPEvent(const std::string &eventName);

private:
	CCLayer *mCurrentMapLayer;
	CCLayer *mWorldMapLayer;
	CPItemComponents *mMapSwitch;
	CPItemComponents *mCurrentNPCList;
	CCLayer *mCurrentMapContainer;
	CCNode *mMySign;

	CCSize mMapShow;
	CCPoint mLeftTop;

	int mCurrentMapID;

	float m_fMapHeight;
	float m_fMapWidth;
	float m_fMiniTileHeight;
	float m_fMiniTileWidth;
};

#endif//__MINI_MAP_PANEL__