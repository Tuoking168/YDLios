#ifndef __MINI_MAP_LAYER_H__
#define __MINI_MAP_LAYER_H__

#include "CCLayer.h"
#include "CCLabelTTF.h"

#include "event/IEventListener.h"

using namespace cocos2d;

class MiniMapLayer : public CCLayer, public IEventListener
{
public:
	MiniMapLayer();
	~MiniMapLayer();
	CREATE_FUNC(MiniMapLayer);

	bool init();
	void onEnter();

protected:
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

private:
	void initUI();
	void buildPortalSign();
	void refreshMap();

	void update(float dt);
	void refreshMapPosition();
	void refreshMySign();
	void refreshEntitySign();

	void onOpen(CCObject *target);
	void onClose(CCObject *target);

	CCPoint getLocalPt(const CCPoint &pt);

	void onCPEvent(const std::string &eventName);

private:
	CCNode* m_pHeroFlag;
	CCLayer* m_pMiniMapLayer;
	CCNode* m_pNodeContainer;
	CCLabelTTF* mCoordinateLabel;
	CCSprite* m_pMap;
	CCNode *mPortalContainer;
	CCNode *mEntityContainer;
	CCNode *mOpenBtn;
	CCNode *mCloseBtn;
	CCLabelTTF *mNameLabel;
	

	float		m_fMiniTileWidth;
	float		m_fMiniTileHeight;
};
#endif //__MINI_MAP_LAYER_H__