#ifndef __Mine_PANEL_H__
#define __Mine_PANEL_H__


#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
#include "event/IEventListener.h"
USING_NS_CC_EXT;

class MinePanel : public BasePanel, public IEventListener
{
public:
	MinePanel();
	~MinePanel();
	virtual bool init();
	static MinePanel* create();

	void onEnter();
	void onExit();
	
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void updateMineCount();

	void onCPEvent(const std::string &eventName);

private:
	void closeCB(CCObject* pSender);
	void addMineInterface();
	void gotoEnhanceItem(CCObject* pSender);
	void openShop(CCObject* pSender);
	void hideCB(CCObject* pSender);
	

	std::map<int ,CCLabelTTF*> m_pLabelMap;
	CCLabelTTF* m_pBagSoltEmpty;
};

#endif//__Float_PANEL_H__