#include "AddFriendConfirmDialog.h"
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

AddFriendConfirmDialog::AddFriendConfirmDialog()
	:m_iCurrentType(-1)
{
	CCLog("___AddFriendConfirmDialog construct...");
	SocialData::apprenticePid = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
	SocialData::apprenticeName = SocialData::getFriendName(SocialData::apprenticePid);
}


AddFriendConfirmDialog::~AddFriendConfirmDialog()
{
	CCLog("___AddFriendConfirmDialog destroy...");
}

bool AddFriendConfirmDialog::onInitDialog()
{
	CCLog("___AddFriendConfirmDialog onInitDialog...");

	// 添加背景
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogBkg");
	addChild(bkg);

	// 添加顶部Bar
	/*CCScale9Sprite *topbar = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogTopbar");
	addChild(topbar);*/

	// 添加关闭按钮
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::SOCIAL, "close");
	closeBtn->setTarget(this, menu_selector(AddFriendConfirmDialog::menuCallBack));
	closeBtn->setTag(ADD_FRIEND_BUTTON_TAG_CLOSE);
	pushMenu(closeBtn);

	// 添加描述文本
	CCLog("___AddFriendConfirmDialog master name:%s", SocialData::masterName.c_str());
	CCLog("___AddFriendConfirmDialog master pid:%d", SocialData::masterPid);

	CCLabelTTF *textDes = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "addFriendConfirm");
	char ch[256];
	sprintf(ch, textDes->getString(), SocialData::apprenticeName.c_str());
	textDes->setString(ch);
	addChild(textDes);

	// 添加底部按钮
	// 同意
	CCMenuItemImage *agreeBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "agree");
	agreeBtn->setTarget(this, menu_selector(AddFriendConfirmDialog::menuCallBack));
	agreeBtn->setTag(ADD_FRIEND_BUTTON_TAG_AGREE);
	pushMenu(agreeBtn);

	// 拒绝
	CCMenuItemImage *refuseBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "refuse");
	refuseBtn->setTarget(this, menu_selector(AddFriendConfirmDialog::menuCallBack));
	refuseBtn->setTag(ADD_FRIEND_BUTTON_TAG_REFUSE);
	pushMenu(refuseBtn);


	return true;
}

void AddFriendConfirmDialog::menuCallBack( CCObject* pSender )
{
	CCLog("___AddFriendConfirmDialog menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);

	if(pMenu)
	{
		int tag = pMenu->getTag();
		CPEventHelper::setEventIntData("closeTip", CPEventData::VALUE_3, SocialData::apprenticePid);
		CCLog("___AddFriendConfirmDialog menuCallBack,tag:%d", tag);
		switch(tag)
		{
		case ADD_FRIEND_BUTTON_TAG_CLOSE:
			{
				CCLog("___AddFriendConfirmDialog ADD_FRIEND_BUTTON_TAG_CLOSE...");
				//this->removeFromParentAndCleanup(true);
			}
			break;
		case ADD_FRIEND_BUTTON_TAG_AGREE:
			{
				CCLog("___AddFriendConfirmDialog ADD_FRIEND_BUTTON_TAG_AGREE...");
				int errorCode = SocialHelper::agreeAddFriend();
				//this->removeFromParentAndCleanup(true);
			}
			break;
		case ADD_FRIEND_BUTTON_TAG_REFUSE:
			{
				CCLog("___AddFriendConfirmDialog ADD_FRIEND_BUTTON_TAG_REFUSE...");
				int errorCode = SocialHelper::refuseAddFriend();
				//this->removeFromParentAndCleanup(true);
			}
			break;
		default:
			break;
		}

		CPEventHelper::setEventIntData("closeTip", CPEventData::VALUE_2, T_addfriend);
		CPEventHelper::dispatcher("closeTip","","");
		this->removeFromParentAndCleanup(true);
	}
}

void AddFriendConfirmDialog::onCPEvent( const std::string &eventName )
{
	CCLog("___AddFriendConfirmDialog onCPEvent...");
}