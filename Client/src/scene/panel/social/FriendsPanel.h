#ifndef __FRIENDS_PANEL_H__
#define __FRIENDS_PANEL_H__

/*
	好友界面
	@auth shixing
*/
#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum FRIENDS_BUTTON_TAG
{
	FRIENDS_BUTTON_TAG_NULL=0,
	FRIENDS_BUTTON_TAG_ADD,
	FRIENDS_BUTTON_TAG_CHAT,
	//FRIENDS_BUTTON_TAG_PICHAT,
	FRIENDS_BUTTON_TAG_DEL,
	FRIENDS_BUTTON_TAG_TRACK,
};

class FriendsPanel : public CCLayer, public IEventListener
{
public:
	FriendsPanel();
	~FriendsPanel();

	bool init();
	CREATE_FUNC(FriendsPanel);

protected:
	GeneralMenu* m_pMainMenu;
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

	GeneralMenu* m_pDialogMenu;// 弹出页面

private:
	static CCMenuItem *getRightBtn(int index);
	
	void refresh();
	void onClickListItem(CCObject *target);
	void addListUI();
	void addListItem(const std::string &name, const char gender, const char clazz, const int level);
	void addListFinish();
	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *mRightBtnMenu;
	CPItemComponents *mFriendList;

	int mCurrentIndex;
	int mFriendListOffset;
};

#endif
