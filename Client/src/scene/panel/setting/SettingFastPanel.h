#ifndef _SettingFastPanel_H_
#define _SettingFastPanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
#include "event/IEventListener.h"
USING_NS_CC_EXT;


class SettingFastPanel :
	public BasePanel,public IEventListener
{
public:
	SettingFastPanel(void);
	~SettingFastPanel(void);
	static SettingFastPanel* create();
	virtual bool init();
	void onEnter();
	void onExit();
	virtual void handleEvent(int channel);

	void onCPEvent(const std::string &eventName);

private:
	void menucallback(CCObject* pSender);
	void initLeftPanel();
	void initrightPanel(int tag);
	void initBtn(int tag);

	void addSkillPanel();
	void addBagPanel();

	void fastclickback(CCObject* pSender);
	void insertLeftItem();
	void leftBtnCallBack(CCObject* pSender);
	enum MyEnum
	{
		setting_SkillPanel =1,
		setting_BagPanel,
	};

	CCMenu* m_pMainMenu;
	int m_CurSubPanel;
	GeneralMenu* m_pRightMenu;
	GeneralMenu* m_pLeftMenu;
	GeneralMenu* m_pBtnMenu;
	int m_iSelectTag;
	CCSprite* m_pEffect;
};

#endif//_SettingBasePanel_H_