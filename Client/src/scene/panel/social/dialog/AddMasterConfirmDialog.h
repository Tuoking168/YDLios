#ifndef __ADD_MASTER_CONFIRM_DIALOG_H__
#define __ADD_MASTER_CONFIRM_DIALOG_H__

/*
	添加师傅确认对话框
	@auth shixing
*/
#include "DialogLayer.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum ADD_MASTER_BUTTON_TAG
{
	ADD_MASTER_BUTTON_TAG_CLOSE=0,
	ADD_MASTER_BUTTON_TAG_AGREE,
	ADD_MASTER_BUTTON_TAG_REFUSE,
};

class AddMasterConfirmDialog : public DialogLayer, public IEventListener
{
public:
	AddMasterConfirmDialog();
	~AddMasterConfirmDialog();

	virtual bool onInitDialog();
	CREATE_FUNC(AddMasterConfirmDialog);

protected:
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

private:
	void onCPEvent(const std::string &eventName);
};

#endif
