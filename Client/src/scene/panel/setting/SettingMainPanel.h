#ifndef _SettingMainPanel_H_
#define _SettingMainPanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
USING_NS_CC_EXT;


class SettingMainPanel :
	public BasePanel
{
public:
	SettingMainPanel(void);
	~SettingMainPanel(void);
	static SettingMainPanel* create();
	virtual bool init();

private:
	void menucallback(CCObject* pSender);
	int m_icurTop;
	GeneralMenu* m_pMainPanel;
	CCMenuItemSprite* m_pcurBtn;

	void addPanel(int tag);

	enum MyEnum
	{
		Base_Panel	= 0,
		Take_Panel	= 1,
		Protect_Panel	= 2,
		Fast_Panel	= 3,
	};
};

#endif//_SettingMainPanel_H_