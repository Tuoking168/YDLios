#include "AddApprenticeConfirmDialog.h"
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

AddApprenticeConfirmDialog::AddApprenticeConfirmDialog()
	:m_iCurrentType(-1)
{
	CCLog("___AddApprenticeConfirmDialog construct...");
	SocialData::masterPid = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
	SocialData::masterName = SocialData::getMasterName(SocialData::masterPid);
}


AddApprenticeConfirmDialog::~AddApprenticeConfirmDialog()
{
	CCLog("___AddApprenticeConfirmDialog destroy...");
}

bool AddApprenticeConfirmDialog::onInitDialog()
{
	CCLog("___AddApprenticeConfirmDialog onInitDialog...");

	// 添加背景
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogBkg");
	addChild(bkg);

	// 添加顶部Bar
	/*CCScale9Sprite *topbar = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogTopbar");
	addChild(topbar);*/

	// 添加关闭按钮
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::SOCIAL, "close");
	closeBtn->setTarget(this, menu_selector(AddApprenticeConfirmDialog::menuCallBack));
	closeBtn->setTag(ADD_APPRENTICE_BUTTON_TAG_CLOSE);
	pushMenu(closeBtn);

	// 添加描述文本
	CCLog("___AddMasterConfirmDialog master name:%s", SocialData::masterName.c_str());
	CCLog("___AddMasterConfirmDialog master pid:%d", SocialData::masterPid);

	CCLabelTTF *textDes = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "addApprenticeConfirm");
	char ch[256];
	sprintf(ch, textDes->getString(), SocialData::masterName.c_str());
	textDes->setString(ch);
	addChild(textDes);

	// 添加底部按钮
	// 同意
	CCMenuItemImage *agreeBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "agree");
	agreeBtn->setTarget(this, menu_selector(AddApprenticeConfirmDialog::menuCallBack));
	agreeBtn->setTag(ADD_APPRENTICE_BUTTON_TAG_AGREE);
	pushMenu(agreeBtn);

	// 拒绝
	CCMenuItemImage *refuseBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "refuse");
	refuseBtn->setTarget(this, menu_selector(AddApprenticeConfirmDialog::menuCallBack));
	refuseBtn->setTag(ADD_APPRENTICE_BUTTON_TAG_REFUSE);
	pushMenu(refuseBtn);


	return true;
}

void AddApprenticeConfirmDialog::menuCallBack( CCObject* pSender )
{
	CCLog("___AddApprenticeConfirmDialog menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);

	if(pMenu)
	{
		int tag = pMenu->getTag();


		CPEventHelper::setEventIntData("closeTip", CPEventData::VALUE_3, SocialData::masterPid);
		CCLog("___AddApprenticeConfirmDialog menuCallBack,tag:%d", tag);
		switch(tag)
		{
		case ADD_APPRENTICE_BUTTON_TAG_CLOSE:
			{
				CCLog("___AddApprenticeConfirmDialog ADD_APPRENTICE_BUTTON_TAG_CLOSE...");
				//this->removeFromParentAndCleanup(true);
			}
			break;
		case ADD_APPRENTICE_BUTTON_TAG_AGREE:
			{
				CCLog("___AddApprenticeConfirmDialog ADD_APPRENTICE_BUTTON_TAG_AGREE...");
				int errorCode = SocialHelper::agreeAddApprentice();
				//this->removeFromParentAndCleanup(true);
			}
			break;
		case ADD_APPRENTICE_BUTTON_TAG_REFUSE:
			{
				CCLog("___AddApprenticeConfirmDialog ADD_APPRENTICE_BUTTON_TAG_REFUSE...");
				int errorCode = SocialHelper::refuseAddApprentice();
				//this->removeFromParentAndCleanup(true);
			}
			break;
		default:
			break;
		}

		CPEventHelper::setEventIntData("closeTip", CPEventData::VALUE_2, T_findapprentice);
		CPEventHelper::dispatcher("closeTip","","");
		this->removeFromParentAndCleanup(true);
	}
}

void AddApprenticeConfirmDialog::onCPEvent( const std::string &eventName )
{
	CCLog("___AddApprenticeConfirmDialog onCPEvent...");
}