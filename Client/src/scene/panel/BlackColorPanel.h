#ifndef __BlackColorPanel_H__
#define __BlackColorPanel_H__


#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
USING_NS_CC_EXT;

class GeneralMenu;

class BlackColorPanel : public BasePanel
{
public:
	BlackColorPanel();
	~BlackColorPanel();
	virtual bool init();
	static BlackColorPanel* create();

	void menucallback(CCObject* pSender);
};



#endif//__Target_PANEL_H__