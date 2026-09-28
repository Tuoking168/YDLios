#ifndef _SettingBasePanel_H_
#define _SettingBasePanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
USING_NS_CC_EXT;


class SettingBasePanel :
	public BasePanel
{
public:
	SettingBasePanel(void);
	~SettingBasePanel(void);
	CREATE_FUNC(SettingBasePanel);
	virtual bool init();
	void onEnter();
	void onExit();


private:
	void menucallback(CCObject* pSender);
	void initLeftPanel();
	void initrightPanel();
	void initHideSetting();

	GeneralMenu* m_pLeftMenu;
};

#endif//_SettingBasePanel_H_