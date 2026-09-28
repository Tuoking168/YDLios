#include "SocialMsgNotifyDialog.h"
#include "../SocialHelper.h"
#include "RelationshipDefinition.h"

#include "SocialModule.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/socialdata/SocialData.h"

#include "ModuleData.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

SocialMsgNotifyDialog::SocialMsgNotifyDialog()
	:m_iCurrentType(-1)
{
	CCLog("___SocialMsgNotifyDialog construct...");
	//CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}


SocialMsgNotifyDialog::~SocialMsgNotifyDialog()
{
	CCLog("___SocialMsgNotifyDialog destroy...");
	//CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool SocialMsgNotifyDialog::onInitDialog()
{
	CCLog("___SocialMsgNotifyDialog onInitDialog...");

	// 添加背景
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogBkg");
	addChild(bkg);

	// 添加顶部Bar
	/*CCScale9Sprite *topbar = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogTopbar");
	addChild(topbar);*/

	// 添加关闭按钮
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::SOCIAL, "close");
	closeBtn->setTarget(this, menu_selector(SocialMsgNotifyDialog::menuCallBack));
	closeBtn->setTag(SOCIAL_MSG_NOTIFY_BUTTON_TAG_CLOSE);
	pushMenu(closeBtn);

	// 添加描述文本
	CCLabelTTF *delDes = LayoutData::getLabelTTF(CPModuleName::SOCIAL, SocialData::notifyMsgKey);
	char ch[256];
	sprintf(ch, delDes->getString(), SocialData::notifyMsgValue.c_str());
	delDes->setString(ch);
	addChild(delDes);

	// 添加底部按钮
	// 关闭按钮
	CCMenuItemImage *confirmBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "confirmClose");
	confirmBtn->setTarget(this, menu_selector(SocialMsgNotifyDialog::menuCallBack));
	confirmBtn->setTag(SOCIAL_MSG_NOTIFY_BUTTON_TAG_CLOSE);
	pushMenu(confirmBtn);

	return true;
}

void SocialMsgNotifyDialog::menuCallBack( CCObject* pSender )
{
	CCLog("___DelFriendConfirmDialog menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);

	if(pMenu)
	{
		int tag = pMenu->getTag();
		CCLog("___DelFriendConfirmDialog menuCallBack,tag:%d", tag);
		switch(tag)
		{
		case SOCIAL_MSG_NOTIFY_BUTTON_TAG_CLOSE:
			{
				CCLog("___DelFriendConfirmDialog ADD_FRIEND_BUTTON_TAG_CLOSE...");
				this->removeFromParentAndCleanup(true);
				SocialData::notifyMsgKey = "";
				SocialData::notifyMsgValue = "";
			}
			break;
		default:
			break;
		}
	}
}

void SocialMsgNotifyDialog::onCPEvent( const std::string &eventName )
{
	CCLog("___DelFriendConfirmDialog onCPEvent...");
	if (eventName == CPEventName::MSG_CHANGE)
	{
	}
}