#ifndef __PROPOSAL_CONFIRM_DIALOG_H__
#define __PROPOSAL_CONFIRM_DIALOG_H__

/*
	求婚确认对话框
	@auth shixing
*/
#include "DialogLayer.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum PROPOSAL_CONFIRM_BUTTON_TAG
{
	PROPOSAL_CONFIRM_BUTTON_TAG_CLOSE=0,
	PROPOSAL_CONFIRM_BUTTON_TAG_AGREE,
	PROPOSAL_CONFIRM_BUTTON_TAG_REFUSE,
};

class ProposalConfirmDialog : public DialogLayer, public IEventListener
{
public:
	ProposalConfirmDialog();
	~ProposalConfirmDialog();

	virtual bool onInitDialog();
	CREATE_FUNC(ProposalConfirmDialog);

protected:
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

private:
	void addButton();
	void onCPEvent(const std::string &eventName);
};

#endif
