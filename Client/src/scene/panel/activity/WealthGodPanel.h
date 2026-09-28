#ifndef _WealthGodPanel_
#define _WealthGodPanel_	

/*
功能：显示商城信息界面
*/
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

class CCMenuEx;
class CPItemComponents;

class ControlDiceAlert : public BasePanel
{
public:
	ControlDiceAlert();
	~ControlDiceAlert();
	virtual bool init(const char* filename,CCSize alertSize);
	static ControlDiceAlert* create(CCSize alertSize);

protected:
	void initFrame();
	void initLabels();
	void initButtons();
	void initCell(CCTableViewCell *cell);
public:
	virtual void MenuCallBack(CCObject* pSender);

	void closeSelf();
	void setConfirmTarget(CCObject *rec, SEL_MenuHandler selector);
	void handleConfirmPressed();
	void setString(std::string alert);
	void setConfirmTitle(std::string cTitle);
	void setCancelTitle(std::string cTitle);
	void setCancelTarget(CCObject *rec, SEL_MenuHandler selector);
	void handleCancelPressed();
	void setTitle(std::string cTitle);

	bool isPressConfirm();
protected:
	GeneralMenu* m_pMainMenu;

	CCLabelTTF* m_LabelInfo;
	CCLabelTTF* m_LabelPage;
	int m_selIndex;
	CCObject *m_pListener;
	SEL_MenuHandler m_pfnSelector;
	CCObject *m_CancelListener;
	SEL_MenuHandler m_CancelSelector;

	CCSize m_Size;
	CCScale9Sprite* m_AlertBg;
	CCLabelTTF* m_ConfirmTitle;
	CCLabelTTF* m_CancelTitle;
	CCLabelTTF* m_Title;
	CCMenuItemSprite *m_MenuConfirm;
	CCMenuItemSprite *m_MenuCancel;

	bool m_PressConfirm;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Tag_Close,
		Tag_Confirm,
		Tag_Cancel,
	};
};

class WealthGodPanel :public FullScreenPanel
{
public:
	WealthGodPanel();
	~WealthGodPanel();
	bool init();
	CREATE_FUNC(WealthGodPanel);
	virtual void onCPEvent(const std::string &eventName);
public:
	
protected:
	void initFrame();
	void initSprite();
	void MenuCallBack(CCObject* pSender);
	void initLabels();
	void initButtons();
private:
	GeneralMenu* m_pMainMenu;
	//CCTableViewEx * m_pTableView;
	CPUpdater *	m_updater;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_Close,
		Button_Control_Dice,
		//Grid
		Grid_Start = 100,
		Grid_End = 199,
	};
};

#endif//_WealthGodPanel_