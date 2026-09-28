#ifndef _TopWelfarePanel_H_
#define _TopWelfarePanel_H_	


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

class TopWelfarePanel :public MenuListPanel
{
public:
	TopWelfarePanel();
	~TopWelfarePanel();
	virtual const std::string dataTableName();
	virtual void onSwitch(int tag);
	bool init();
	void hide();
	CREATE_FUNC(TopWelfarePanel);
public:
	enum Panel_Tag
	{
		//panel
		Panel_FirstCharge = 0,
		Panel_EveryDayFirstCharge = 1,
		Panel_AddUpCharge = 2,
		Panel_MonthGift = 3,
		Panel_TimeLimitGift = 4,
		Panel_OnlineGift = 5,
		Panel_ConsumeDraw = 6,
		Panel_SingleRecharge = 7,
	};
protected:
	void showGirl(int girlID);
private:
	
	
	enum Child_Tag
	{
		Tag_NULL=0,
		
		//button
		Button_Close,

		//Cell
		Cell_Start = 100,
		Cell_End = 200,
	};
};

#endif//_TopWelfarePanel_H_