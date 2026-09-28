#ifndef __ADD_FRIEND_CONFIRM_DIALOG_H__
#define __ADD_FRIEND_CONFIRM_DIALOG_H__

/*
	添加好友确认对话框
	@auth shixing
*/
#include "DialogLayer.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum ADD_FRIEND_BUTTON_TAG
{
	ADD_FRIEND_BUTTON_TAG_CLOSE=0,
	ADD_FRIEND_BUTTON_TAG_AGREE,
	ADD_FRIEND_BUTTON_TAG_REFUSE,
};

class AddFriendConfirmDialog : public DialogLayer, public IEventListener
{
public:
	AddFriendConfirmDialog();
	~AddFriendConfirmDialog();

	virtual bool onInitDialog();
	CREATE_FUNC(AddFriendConfirmDialog);

protected:
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

private:
	void onCPEvent(const std::string &eventName);
};

#endif
