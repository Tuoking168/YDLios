#include "ProposalConfirmDialog.h"
#include "../SocialHelper.h"
#include "RelationshipDefinition.h"

#include "SocialModule.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/socialdata/SocialData.h"

#include "ModuleData.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

ProposalConfirmDialog::ProposalConfirmDialog()
	:m_iCurrentType(-1)
{
	CCLog("___ProposalConfirmDialog construct...");
}


ProposalConfirmDialog::~ProposalConfirmDialog()
{
	CCLog("___ProposalConfirmDialog destroy...");
}

bool ProposalConfirmDialog::onInitDialog()
{
	CCLog("___ProposalConfirmDialog onInitDialog...");

	// ????????????????????????????????
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogBkg");
	addChild(bkg);

	// ????????
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::SOCIAL, "close");
	closeBtn->setTarget(this, menu_selector(ProposalConfirmDialog::menuCallBack));
	closeBtn->setTag(PROPOSAL_CONFIRM_BUTTON_TAG_CLOSE);
	pushMenu(closeBtn);

	// ???????????
	CCLog("___ProposalConfirmDialog bridegroom name:%s", SocialData::bridegroomName.c_str());
	CCLog("___ProposalConfirmDialog bridegroom pid:%d", SocialData::bridegroomPid);

	CCLabelTTF *textDes = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "addCoupleConfirm1");
	char ch[256];
	sprintf(ch, textDes->getString(), SocialData::bridegroomName.c_str());
	textDes->setString(ch);
	addChild(textDes);

	// ?????????
	// ????
	CCMenuItemImage *agreeBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "agree");
	agreeBtn->setTarget(this, menu_selector(ProposalConfirmDialog::menuCallBack));
	agreeBtn->setTag(PROPOSAL_CONFIRM_BUTTON_TAG_AGREE);
	pushMenu(agreeBtn);

	// ???
	CCMenuItemImage *refuseBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "refuse");
	refuseBtn->setTarget(this, menu_selector(ProposalConfirmDialog::menuCallBack));
	refuseBtn->setTag(PROPOSAL_CONFIRM_BUTTON_TAG_REFUSE);
	pushMenu(refuseBtn);


	return true;
}

void ProposalConfirmDialog::menuCallBack( CCObject* pSender )
{
	CCLog("___ProposalConfirmDialog menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);

	if(pMenu)
	{
		int tag = pMenu->getTag();
		CCLog("___ProposalConfirmDialog menuCallBack,tag:%d", tag);
		switch(tag)
		{
		case PROPOSAL_CONFIRM_BUTTON_TAG_CLOSE:
			{
				CCLog("___ProposalConfirmDialog PROPOSAL_CONFIRM_BUTTON_TAG_CLOSE...");
			}
			break;
		case PROPOSAL_CONFIRM_BUTTON_TAG_AGREE:
			{
				CCLog("___ProposalConfirmDialog PROPOSAL_CONFIRM_BUTTON_TAG_AGREE...");
				int errorCode = SocialHelper::agreeAddCouple();
			}
			break;
		case PROPOSAL_CONFIRM_BUTTON_TAG_REFUSE:
			{
				CCLog("___ProposalConfirmDialog PROPOSAL_CONFIRM_BUTTON_TAG_REFUSE...");
				int errorCode = SocialHelper::refuseAddCouple();
			}
			break;
		default:
			break;
		}

		this->removeFromParentAndCleanup(true);
	}
}

void ProposalConfirmDialog::onCPEvent( const std::string &eventName )
{
	CCLog("___ProposalConfirmDialog onCPEvent...");
}
