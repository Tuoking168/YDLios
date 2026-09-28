#ifndef __SOCIAL_MSG_NOTIFY_DIALOG_H__
#define __SOCIAL_MSG_NOTIFY_DIALOG_H__

/*
	社交消息通知提示框
	@auth shixing
*/
#include "DialogLayer.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum SOCIAL_MSG_NOTIFY_BUTTON_TAG
{
	SOCIAL_MSG_NOTIFY_BUTTON_TAG_CLOSE=0
};

class SocialMsgNotifyDialog : public DialogLayer, public IEventListener
{
public:
	SocialMsgNotifyDialog();
	~SocialMsgNotifyDialog();

	virtual bool onInitDialog();
	CREATE_FUNC(SocialMsgNotifyDialog);

protected:
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

private:
	void onCPEvent(const std::string &eventName);
};

#endif
