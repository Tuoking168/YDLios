#ifndef __PROPOSAL_REQUEST_DIALOG_H__
#define __PROPOSAL_REQUEST_DIALOG_H__

/*
	???????????
	@auth shixing
*/
#include "DialogLayer.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"

#include "event/IEventListener.h"

USING_NS_CC_EXT;

class CPItemComponents;

enum PROPOSAL_REQUEST_BUTTON_TAG
{
	PROPOSAL_REQUEST_BUTTON_TAG_CLOSE=0,
	PROPOSAL_REQUEST_BUTTON_TAG_CONFIRM,
	PROPOSAL_REQUEST_BUTTON_TAG_CANCEL,
};

class ProposalRequestDialog : public DialogLayer, public IEventListener
{
public:
	ProposalRequestDialog();
	~ProposalRequestDialog();

	virtual bool onInitDialog();
	CREATE_FUNC(ProposalRequestDialog);

protected:
	int m_iCurrentType;
	void menuCallBack(CCObject* pSender);

private:
	extension::CCEditBox *mInputText;
	void onCPEvent(const std::string &eventName);
};

#endif
