#ifndef _TopActivityPanel_H_
#define _TopActivityPanel_H_	


#include <string>
#include <vector>
#include "ext/Basepanel.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
#include "scene/panel/MenuListPanel.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CCMenuEx;
class SlideTable;

class TopActivityPanel :public MenuListPanel
{
public:
	TopActivityPanel();
	~TopActivityPanel();
	virtual const std::string dataTableName();
	virtual void onSwitch(int tag);
	bool init();
	void hide();
	CREATE_FUNC(TopActivityPanel);
public:
	enum Panel_Tag
	{
		Panel_InvestPlan,
	};
};

#endif//_TopActivityPanel_H_