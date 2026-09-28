#ifndef _TopSportsPanel_H_
#define _TopSportsPanel_H_	

/*
功能：显示商城信息界面
*/
#include <string>
#include <vector>
#include "ext/Basepanel.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
#include "scene/panel/MenuListPanel.h"
#include "ext/GeneralMenu.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CCMenuEx;
class SlideTable;

class TopSportsPanel :public MenuListPanel
{
public:
	TopSportsPanel();
	~TopSportsPanel();
	virtual const std::string dataTableName();
	virtual void onSwitch(int tag);
	bool init();
	void hide();
	CREATE_FUNC(TopSportsPanel);
public:
	enum Panel_Tag
	{
		Panel_OpenSports,
	};

private:
	GeneralMenu* m_pRightMenu;
};
#endif//_TopSportsPanel_H_