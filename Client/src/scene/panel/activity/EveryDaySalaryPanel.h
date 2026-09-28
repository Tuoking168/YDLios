#ifndef _EveryDaySalaryPanel_
#define _EveryDaySalaryPanel_	

#include <string>
#include <vector>
#include "scene/panel/FullScreenPanel.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
#include "scene/panel/OptionsHelper.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CPItemComponents;
class EveryDaySalaryPanel :public FullScreenPanel
{
public:
	EveryDaySalaryPanel();
	~EveryDaySalaryPanel();
	bool init();
	CREATE_FUNC(EveryDaySalaryPanel);
	virtual void onCPEvent(const std::string &eventName);

private:
	void setCurMonth(int pMonth);
	void setAddupSign(int pCnt);
	void setPatchSign(int pCnt);

	void setOpenDays(int pDays);
	void setAddupOnline(int pTime);
	void setOnline(int pType);

	void setCurTicket(int pCnt);
	void setCurHonor(int pCnt);
	void setLastTicket(int pCnt);
	void setLastHonor(int pCnt);

private:
	void initFrame();
	void initSprite();
	void initMenu();
	void initLabels();
	void initButtons();
	void initCell(CCTableViewCell *cell);
	void loadCell(CCTableViewCell *cell);

	void selectButtonWithIndex(int idx);
	void loadRewards(int idx);
	void showTooltip(CCMenuItem* pImage);
	void MenuCallBack(CCObject* pSender);
	void itemCallBack(CCObject* pSender);
	
	//»’¿˙
	struct CalendarInfo {
		int year;
		int month;
		int day;
		bool isSigned;
		int row;
		int column;
	}; 
	typedef std::vector<CalendarInfo> CalendarList;
	CalendarList m_CalendarList;
	void initCalendar();
	int getMaxDay(int month,int year);
	int getDayIndex(int day,int week);
	int getLastMonth(int month,int& year);
	int getNextMonth(int month,int& year);
	void initCalendarData();
	void addListItem(int idx );
	void clickCalendar(CCObject* pSender);

	void refreshmrqd();

private:
	GeneralMenu* m_pMainMenu;
	CPUpdater *	m_updater;
	GeneralMenu* m_RewardMgr;

	int m_CurYear;
	int m_CurMonth;
	int m_CurDay;
	int m_CurWeek;

	int m_indexSelected;

	CCLabelTTF* m_LabelCurMonth;
	CCLabelTTF* m_LabelAddupSign;
	CCLabelTTF* m_LabelPatchSign;
	CCLabelTTF* m_LabelOpenDays;
	CCLabelTTF* m_LabelAddupOnline;
	CCLabelTTF* m_LabelOnline;
	CCLabelTTF* m_LabelCurTicket;
	CCLabelTTF* m_LabelCurHonor;
	CCLabelTTF* m_LabelLastTicket;
	CCLabelTTF* m_LabelLastHonor;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_Get,
		Button_GetReward,

		//Cell
		Cell_Start = 100,
		Cell_End = 199,

		//Calendar
		Calendar_Start = 200,
		Calendar_End = 235,

		//Button_Sign
		Button_Sign_Start = 250,
		Button_Sign_End = 260,
	};
};

#endif//_EveryDaySalaryPanel_