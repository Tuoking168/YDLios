#ifndef __ReliveAlertPanel__
#define __ReliveAlertPanel__

/*
功能：行会
*/

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "MsgQuest.h"
#include "controls/CPRichText.h"

USING_NS_CC_EXT;

//-----------------------------------------------------------------------------------------------------------------------------------------------//
/*
功能：
*/
 
class ReliveAlertPanel : public BasePanel
{
public:
	enum relive_type
	{
		Relive_Normal,
		Relive_Instance,
		Relive_Orientation,
	};
	enum Button_Type
	{
		Button_By_Gold=1,
		Button_Free=2,
	};
public:
	ReliveAlertPanel();
	~ReliveAlertPanel();
	virtual bool init(std::string pReason,int pType);
	static ReliveAlertPanel* create(std::string pReason,int pType=0);
	void onEnter();
	void onCPEvent(const std:: string &eventName);
protected:
	void initFrame();
	void initLabels();
	void initButtons();
	void update(float dt);
	void reliveByType(int pType);
public:
	virtual void MenuCallBack(CCObject* pSender);

	void setReason(std::string pReason);
	void setTime(int dt);

	void closeSelf();
	void setConfirmTarget(CCObject *rec, SEL_MenuHandler selector);
	void handleConfirmPressed();
	void setConfirmTitle(std::string cTitle);
	void setCancelTitle(std::string cTitle);
	void setCancelTarget(CCObject *rec, SEL_MenuHandler selector);
	void handleCancelPressed();
protected:
	GeneralMenu* m_pMainMenu;
	
	CCScale9Sprite* m_pborder;

	CPRichText* m_ReasonLabel;
	CCLabelTTF* m_TimeLabel;
	float m_ReliveTime;

	int m_ReliveType;
	std::string m_Reason;

	CCObject *m_pListener;
	SEL_MenuHandler m_pfnSelector;
	CCObject *m_CancelListener;
	SEL_MenuHandler m_CancelSelector;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Tag_Close,
		Tag_Confirm,
		Tag_Cancel,
		//label
	};
};

#endif//__ReliveAlertPanel__