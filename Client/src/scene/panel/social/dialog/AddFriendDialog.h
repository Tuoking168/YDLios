#ifndef __ADD_FRIEND_DIALOG_H__
#define __ADD_FRIEND_DIALOG_H__

/*
	添加好友对话框
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
	ADD_FRIEND_BUTTON_TAG_CONFIRM,
	ADD_FRIEND_BUTTON_TAG_CANCEL,
};

class AddFriendDialog : public DialogLayer, public IEventListener
{
public:
	AddFriendDialog();
	~AddFriendDialog();

	virtual bool onInitDialog();
	CREATE_FUNC(AddFriendDialog);

protected:
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

	void showErrorMessage(int errorCode);
private:
	extension::CCEditBox *mInputText;

	void onCPEvent(const std::string &eventName);
};

#endif
