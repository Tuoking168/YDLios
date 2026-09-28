#include "AddMasterConfirmDialog.h"
#include "../SocialHelper.h"
#include "RelationshipDefinition.h"

#include "SocialModule.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/socialdata/SocialData.h"

#include "ModuleData.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "userdata/IconTipsData.h"

AddMasterConfirmDialog::AddMasterConfirmDialog()
	:m_iCurrentType(-1)
{
	CCLog("___AddMasterConfirmDialog construct...");
	SocialData::apprenticePid = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
	SocialData::apprenticeName = SocialData::getApprenticeName(SocialData::apprenticePid);
}


AddMasterConfirmDialog::~AddMasterConfirmDialog()
{
	CCLog("___AddMasterConfirmDialog destroy...");
}

bool AddMasterConfirmDialog::onInitDialog()
{
	CCLog("___AddMasterConfirmDialog onInitDialog...");

	// 添加背景
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogBkg");
	addChild(bkg);

	// 添加顶部Bar
	/*CCScale9Sprite *topbar = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogTopbar");
	addChild(topbar);*/

	// 添加关闭按钮
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::SOCIAL, "close");
	closeBtn->setTarget(this, menu_selector(AddMasterConfirmDialog::menuCallBack));
	closeBtn->setTag(ADD_MASTER_BUTTON_TAG_CLOSE);
	pushMenu(closeBtn);

	// 添加描述文本
	CCLog("___AddMasterConfirmDialog master name:%s", SocialData::masterName.c_str());
	CCLog("___AddMasterConfirmDialog master pid:%d", SocialData::masterPid);

	CCLabelTTF *textDes = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "addMasterConfirm");
	char ch[256];
	sprintf(ch, textDes->getString(), SocialData::apprenticeName.c_str());
	textDes->setString(ch);
	addChild(textDes);

	// 添加底部按钮
	// 同意
	CCMenuItemImage *agreeBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "agree");
	agreeBtn->setTarget(this, menu_selector(AddMasterConfirmDialog::menuCallBack));
	agreeBtn->setTag(ADD_MASTER_BUTTON_TAG_AGREE);
	pushMenu(agreeBtn);

	// 拒绝
	CCMenuItemImage *refuseBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "refuse");
	refuseBtn->setTarget(this, menu_selector(AddMasterConfirmDialog::menuCallBack));
	refuseBtn->setTag(ADD_MASTER_BUTTON_TAG_REFUSE);
	pushMenu(refuseBtn);


	return true;
}

void AddMasterConfirmDialog::menuCallBack( CCObject* pSender )
{
	CCLog("___AddMasterConfirmDialog menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);

	if(pMenu)
	{
		int tag = pMenu->getTag();
		CPEventHelper::setEventIntData("closeTip", CPEventData::VALUE_3, SocialData::apprenticePid);
		CCLog("___AddMasterConfirmDialog menuCallBack,tag:%d", tag);
		switch(tag)
		{
		case ADD_MASTER_BUTTON_TAG_CLOSE:
			{
				CCLog("___AddMasterConfirmDialog ADD_MASTER_BUTTON_TAG_CLOSE...");
				//this->removeFromParentAndCleanup(true);
			}
			break;
		case ADD_MASTER_BUTTON_TAG_AGREE:
			{
				CCLog("___AddMasterConfirmDialog ADD_MASTER_BUTTON_TAG_AGREE...");
				int errorCode = SocialHelper::agreeAddMaster();
				//this->removeFromParentAndCleanup(true);
			}
			break;
		case ADD_MASTER_BUTTON_TAG_REFUSE:
			{
				CCLog("___AddMasterConfirmDialog ADD_MASTER_BUTTON_TAG_REFUSE...");
				int errorCode = SocialHelper::refuseAddMaster();
				//this->removeFromParentAndCleanup(true);
			}
			break;
		default:
			break;
		}

		CPEventHelper::setEventIntData("closeTip", CPEventData::VALUE_2, T_findmaster);
		CPEventHelper::dispatcher("closeTip","","");
		this->removeFromParentAndCleanup(true);
	}
}

void AddMasterConfirmDialog::onCPEvent( const std::string &eventName )
{
	CCLog("___AddMasterConfirmDialog onCPEvent...");
}