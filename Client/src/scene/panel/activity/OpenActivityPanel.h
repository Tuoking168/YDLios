#ifndef _OpenActivityPanel_
#define _OpenActivityPanel_	


#include <string>
#include <vector>
#include "scene/panel/FullScreenPanel.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
#include "scene/panel/OptionsHelper.h"
#include "controls/CPRichText.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CCMenuEx;
class CPItemComponents;
class SlideTable;
class CPDelayRefresh;
class OpenActivityPanel :public FullScreenPanel
{
public:
	OpenActivityPanel();
	~OpenActivityPanel();
	bool init();
	CREATE_FUNC(OpenActivityPanel);
	virtual void onCPEvent(const std::string &eventName);

private:
	void initFrame();
	void initSprite();
	void MenuCallBack(CCObject* pSender);
	void initLabels();
	void initButtons();
	void refresh();
	void showTooltip(CCMenuItem* pImage);

	void itemCallBack(CCObject* pSender);

	void initItemPages();
	void addListItem(int i );
	void addListFinish();
	void pageChangeCallBack(CCObject* pSender);

	void dataRequest();

private:
	GeneralMenu* m_pMainMenu;
	SlideTable*		m_pSlideItems;
	CPUpdater *	m_updater;
	CCLabelTTF* m_PageInfo;
	CPDelayRefresh *mDelayRefresh;

	typedef std::vector<CCLabelTTF *> LabelVect;
	LabelVect mLabels;

	int mOpenDays;
	
	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_Close,
		//Cell
		Cell_Start = 100,
		Cell_End = 199,

		//Calendar
		Calendar_Start = 200,
		Calendar_End = 235,
	};
	enum Cell_Tag
	{
		Cell_Tag_NULL=0,
		//label
		Cell_Label_title = 1,
		Cell_Label_zhanshi = 2,
		Cell_Label_fashi = 3,
		Cell_Label_daoshi = 4,
		Cell_Label_rewardinfo = 5,
	};
};

////////////ActivityDetailPanel//////////////////////////////////////////
class ActivityDetailPanel : public BasePanel
{
public:
	ActivityDetailPanel();
	~ActivityDetailPanel();
	virtual bool init(int tag);
	static ActivityDetailPanel* create(int tag);

protected:
	void initFrame();
	void initLabels();
	void initButtons();
	void addSubContent(int id);
public:
	virtual void MenuCallBack(CCObject* pSender);
	void closeSelf();
protected:
	GeneralMenu* m_pMainMenu;
	int m_selIndex;
	CPRichText* m_pRichText;
};
#endif//_OpenActivityPanel_