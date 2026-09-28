#include "SocialDelConfirmDialog.h"
#include "../SocialHelper.h"
#include "RelationshipDefinition.h"

#include "SocialModule.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/socialdata/SocialData.h"

#include "ModuleData.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

SocialDelConfirmDialog::SocialDelConfirmDialog()
	:m_iCurrentType(-1)
{
	CCLog("___SocialMsgConfirmDialog construct...");
	//CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}


SocialDelConfirmDialog::~SocialDelConfirmDialog()
{
	CCLog("___SocialMsgConfirmDialog destroy...");
	//CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool SocialDelConfirmDialog::onInitDialog()
{
	CCLog("___SocialMsgConfirmDialog onInitDialog...");

	// 添加背景
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogBkg");
	addChild(bkg);

	// 添加顶部Bar
	/*CCScale9Sprite *topbar = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogTopbar");
	addChild(topbar);*/

	// 添加关闭按钮
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::SOCIAL, "close");
	closeBtn->setTarget(this, menu_selector(SocialDelConfirmDialog::menuCallBack));
	closeBtn->setTag(SOCIAL_DEL_BUTTON_TAG_CLOSE);
	pushMenu(closeBtn);

	// 添加描述文本
	CCLog("___SocialDelConfirmDialog delname:%s", SocialData::delName.c_str());
	CCLog("___SocialDelConfirmDialog delpid:%d", SocialData::delPid);
	CCLog("___SocialDelConfirmDialog delptype:%d", SocialData::delType);

	char delCh[20];
	sprintf(delCh, "delRelationType%d", SocialData::delType);
	std::string delKey = delCh;
	CCLabelTTF *delDes = LayoutData::getLabelTTF(CPModuleName::SOCIAL, delKey);
	char ch[100];
	sprintf(ch, delDes->getString(), SocialData::delName.c_str());
	delDes->setString(ch);
	addChild(delDes);

	// 添加底部按钮
	// 确定
	CCMenuItemImage *confirmBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "confirm");
	confirmBtn->setTarget(this, menu_selector(SocialDelConfirmDialog::menuCallBack));
	confirmBtn->setTag(SOCIAL_DEL_BUTTON_TAG_CONFIRM);
	pushMenu(confirmBtn);

	// 取消
	CCMenuItemImage *cancelBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "cancel");
	cancelBtn->setTarget(this, menu_selector(SocialDelConfirmDialog::menuCallBack));
	cancelBtn->setTag(SOCIAL_DEL_BUTTON_TAG_CANCEL);
	pushMenu(cancelBtn);


	return true;
}

void SocialDelConfirmDialog::menuCallBack( CCObject* pSender )
{
	CCLog("___SocialDelConfirmDialog menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);

	if(pMenu)
	{
		int tag = pMenu->getTag();
		CCLog("___SocialDelConfirmDialog menuCallBack,tag:%d", tag);
		switch(tag)
		{
		case SOCIAL_DEL_BUTTON_TAG_CLOSE:
			{
				CCLog("___SocialDelConfirmDialog SOCIAL_DEL_BUTTON_TAG_CLOSE...");
				this->removeFromParentAndCleanup(true);
			}
			break;
		case SOCIAL_DEL_BUTTON_TAG_CONFIRM:
			{
				CCLog("___SocialDelConfirmDialog SOCIAL_DEL_BUTTON_TAG_CONFIRM...");
				int errorCode = SocialHelper::deleteRelation(SocialData::delPid, SocialData::delType);
				//if(errorCode != Error::Success)
				//{
				//	//showErrorMessage(errorCode);
				//}
				SocialData::delPid = -1;
				SocialData::delName = "";
				this->removeFromParentAndCleanup(true);
			}
			break;
		case SOCIAL_DEL_BUTTON_TAG_CANCEL:
			{
				CCLog("___SocialDelConfirmDialog SOCIAL_DEL_BUTTON_TAG_CANCEL...");
				this->removeFromParentAndCleanup(true);
			}
			break;
		default:
			break;
		}
	}
}

void SocialDelConfirmDialog::onCPEvent( const std::string &eventName )
{
	CCLog("___SocialDelConfirmDialog onCPEvent...");
	if (eventName == CPEventName::MSG_CHANGE)
	{
	}
}