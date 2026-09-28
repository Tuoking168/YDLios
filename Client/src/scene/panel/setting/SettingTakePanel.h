#ifndef _SettingTakePanel_H_
#define _SettingTakePanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
USING_NS_CC_EXT;


class SettingTakePanel :
	public BasePanel
{
public:
	SettingTakePanel(void);
	~SettingTakePanel(void);
	static SettingTakePanel* create();
	virtual bool init();
	void onEnter();
	void onExit();


private:
	void menucallback(CCObject* pSender);
	void initLeftPanel();
	void initright1Panel();
	void initright2Panel();
	void sendmsgToServer();
};

#endif//_SettingTakePanel_H_