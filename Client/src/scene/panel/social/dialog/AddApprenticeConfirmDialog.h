#ifndef __ADD_APPRENTICE_CONFIRM_DIALOG_H__
#define __ADD_APPRENTICE_CONFIRM_DIALOG_H__

/*
	添加徒弟确认对话框
	@auth shixing
*/
#include "DialogLayer.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum ADD_APPRENTICE_BUTTON_TAG
{
	ADD_APPRENTICE_BUTTON_TAG_CLOSE=0,
	ADD_APPRENTICE_BUTTON_TAG_AGREE,
	ADD_APPRENTICE_BUTTON_TAG_REFUSE,
};

class AddApprenticeConfirmDialog : public DialogLayer, public IEventListener
{
public:
	AddApprenticeConfirmDialog();
	~AddApprenticeConfirmDialog();

	virtual bool onInitDialog();
	CREATE_FUNC(AddApprenticeConfirmDialog);

protected:
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

private:
	void onCPEvent(const std::string &eventName);
};

#endif
