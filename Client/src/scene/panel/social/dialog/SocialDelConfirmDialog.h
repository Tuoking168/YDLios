#ifndef __SOCIAL_DEL_CONFIRM_DIALOG_H__
#define __SOCIAL_DEL_CONFIRM_DIALOG_H__

/*
	确认对话框
	@auth shixing
*/
#include "DialogLayer.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum SOCIAL_DEL_BUTTON_TAG
{
	SOCIAL_DEL_BUTTON_TAG_CLOSE=0,
	SOCIAL_DEL_BUTTON_TAG_CONFIRM,
	SOCIAL_DEL_BUTTON_TAG_CANCEL,
};

class SocialDelConfirmDialog : public DialogLayer, public IEventListener
{
public:
	SocialDelConfirmDialog();
	~SocialDelConfirmDialog();

	virtual bool onInitDialog();
	CREATE_FUNC(SocialDelConfirmDialog);

protected:
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

private:
	void onCPEvent(const std::string &eventName);
};

#endif
