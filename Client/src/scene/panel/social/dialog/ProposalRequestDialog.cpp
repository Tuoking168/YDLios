#include "ProposalRequestDialog.h"
#include "../SocialHelper.h"
#include "RelationshipDefinition.h"

#include "SocialModule.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/socialdata/SocialData.h"

#include "ModuleData.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

ProposalRequestDialog::ProposalRequestDialog()
	:m_iCurrentType(-1)
	,mInputText(NULL)
{
	CCLog("___ProposalRequestDialog construct...");
	//CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}


ProposalRequestDialog::~ProposalRequestDialog()
{
	CCLog("___ProposalRequestDialog destroy...");
	//CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool ProposalRequestDialog::onInitDialog()
{
	CCLog("___ProposalRequestDialog onInitDialog...");

	// ???????
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogBkg");
	addChild(bkg);

	// ???????Bar
	CCScale9Sprite *topbar = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogTopbar");
	addChild(topbar);

	// ????????
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::SOCIAL, "close");
	closeBtn->setTarget(this, menu_selector(ProposalRequestDialog::menuCallBack));
	closeBtn->setTag(PROPOSAL_REQUEST_BUTTON_TAG_CLOSE);
	pushMenu(closeBtn);

	// ???????????
	CCLabelTTF *des1 = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "proposalRequestDes1");
	addChild(des1);
	CCLabelTTF *des2 = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "proposalRequestDes2");
	addChild(des2);

	// ????????????????????
	mInputText = LayoutData::getEditBox(CPModuleName::SOCIAL, "addFriendInput");
	mInputText->setTouchPriority(kCCMenuHandlerPriority-2);
	addChild(mInputText);

	// ?????????
	// ???
	CCMenuItemImage *confirmBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "confirmP");
	confirmBtn->setTarget(this, menu_selector(ProposalRequestDialog::menuCallBack));
	confirmBtn->setTag(PROPOSAL_REQUEST_BUTTON_TAG_CONFIRM);
	pushMenu(confirmBtn);

	// ???
	CCMenuItemImage *cancelBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "cancel");
	cancelBtn->setTarget(this, menu_selector(ProposalRequestDialog::menuCallBack));
	cancelBtn->setTag(PROPOSAL_REQUEST_BUTTON_TAG_CANCEL);
	pushMenu(cancelBtn);


	return true;
}

void ProposalRequestDialog::menuCallBack( CCObject* pSender )
{
	CCLog("___ProposalRequestDialog menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);

	if(pMenu)
	{
		int tag = pMenu->getTag();
		CCLog("___ProposalRequestDialog menuCallBack,tag:%d", tag);
		switch(tag)
		{
		case PROPOSAL_REQUEST_BUTTON_TAG_CLOSE:
			{
				CCLog("___ProposalRequestDialog PROPOSAL_REQUEST_BUTTON_TAG_CLOSE...");
				this->removeFromParentAndCleanup(true);
			}
			break;
		case PROPOSAL_REQUEST_BUTTON_TAG_CONFIRM:
			{
				CCLog("___ProposalRequestDialog PROPOSAL_REQUEST_BUTTON_TAG_CONFIRM...");
				std::string name = "";
				if (mInputText)
				{
					name = mInputText->getText();
				}
				if (!name.empty())
			{
				SocialHelper::requestAddCouple(0, name);
				CPEventHelper::uiNotify("ProposalRequestSent", "", 0);
			}
				this->removeFromParentAndCleanup(true);
			}
			break;
		case PROPOSAL_REQUEST_BUTTON_TAG_CANCEL:
			{
				CCLog("___ProposalRequestDialog PROPOSAL_REQUEST_BUTTON_TAG_CANCEL...");
				this->removeFromParentAndCleanup(true);
			}
			break;
		default:
			break;
		}
	}
}

void ProposalRequestDialog::onCPEvent( const std::string &eventName )
{
	CCLog("___ProposalRequestDialog onCPEvent...");
	if (eventName == CPEventName::MSG_CHANGE)
	{
	}
}