#ifndef _CombinedServerRankPanel_H_
#define _CombinedServerRankPanel_H_	

#include <string>
#include <vector>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "scene/panel/FullScreenPanel.h"
#include "ext/basepanel.h"
#include "ext/CCTabelViewEx.h"
USING_NS_CC_EXT;
class CombinedServerRankRightPanel;

class CombinedServerRankPanel :public FullScreenPanel
{
public:
	CombinedServerRankPanel();
	~CombinedServerRankPanel();
	CREATE_FUNC(CombinedServerRankPanel);
	//static CombinedServerRankPanel* create();
	virtual void onSwitch(int tag);
	bool init();
	void onEnter();
	void hide();
	void chongzhi( CCObject* pSender );
	virtual void onCPEvent(const std::string &eventName);

protected:

private:
	void onMove(float i);
	void refreshTime();
	void BtnCB(CCObject* pSender);
	int m_iCurType;
	GeneralMenu* m_pMenu;
	CCLabelTTF *m_TimeLabel;
	CCLabelTTF *pDownTitle;
	CombinedServerRankRightPanel* m_pRightMenu;
};

///-----------------------------------------------------------------------------------------------------------//

class CombinedServerRankRightPanel :public BasePanel,public IEventListener
{
public:
	CombinedServerRankRightPanel();
	~CombinedServerRankRightPanel();
	CREATE_FUNC(CombinedServerRankRightPanel);
	//static CombinedServerRankRightPanel* create();
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
	void libaoCB(CCObject* pSender);

	void updateMaxPage();
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

#endif//_CombinedServerRankPanel_H_