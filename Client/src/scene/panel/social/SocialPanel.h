#ifndef __SOCIAL_PANEL_H__
#define __SOCIAL_PANEL_H__

/*
	社交功能界面(好友、师徒、伴侣、仇人)
	@auth shixing
	*/
#include "../FullScreenPanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum SOCIAL_BUTTON_TAG
{
	SOCIAL_TAG_NULL=0,
	SOCIAL_TAG_FRIENDS,
	SOCIAL_TAG_MENTORSHIP,
	SOCIAL_TAG_COUPLE,
	SOCIAL_TAG_ENEMY,
};

class SocialPanel : public FullScreenPanel
{
public:
	SocialPanel();
	~SocialPanel();

	bool init();
	void onEnter();
	CREATE_FUNC(SocialPanel);

protected:
	GeneralMenu* m_pMainMenu;
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

	GeneralMenu* m_pSubContainMenu;// 功能页面

private:
	CPItemComponents *mSwitchMenu;

	static CCMenuItem *getSwitchItem(int index);
	void onCPEvent(const std::string &eventName);
};

#endif
