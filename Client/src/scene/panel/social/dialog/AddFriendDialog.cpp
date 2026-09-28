#include "AddFriendDialog.h"
#include "../SocialHelper.h"
#include "RelationshipDefinition.h"

#include "SocialModule.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"

#include "ModuleData.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

AddFriendDialog::AddFriendDialog()
	:m_iCurrentType(-1)
	,mInputText(NULL)
{
	CCLog("___AddFriendDialog construct...");
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}


AddFriendDialog::~AddFriendDialog()
{
	CCLog("___AddFriendDialog destroy...");
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool AddFriendDialog::onInitDialog()
{
	CCLog("___AddFriendDialog onInitDialog...");

	// 添加背景
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogBkg");
	addChild(bkg);

	// 添加顶部Bar
	/*CCScale9Sprite *topbar = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "dialogTopbar");
	addChild(topbar);*/
	
	// 添加关闭按钮
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::SOCIAL, "close");
	closeBtn->setTarget(this, menu_selector(AddFriendDialog::menuCallBack));
	closeBtn->setTag(ADD_FRIEND_BUTTON_TAG_CLOSE);
	pushMenu(closeBtn);
	
	// 添加描述文本
	CCLabelTTF *inputDes = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "addFriendInput");
	addChild(inputDes);

	// 添加输入框
	// input edit box
	mInputText = LayoutData::getEditBox(CPModuleName::SOCIAL, "addFriendInput");
	mInputText->setTouchPriority(kCCMenuHandlerPriority-2);
	addChild(mInputText);
	
	// 添加底部按钮
	// 确定
	CCMenuItemImage *confirmBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "confirm");
	confirmBtn->setTarget(this, menu_selector(AddFriendDialog::menuCallBack));
	confirmBtn->setTag(ADD_FRIEND_BUTTON_TAG_CONFIRM);
	pushMenu(confirmBtn);

	// 取消
	CCMenuItemImage *cancelBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "cancel");
	cancelBtn->setTarget(this, menu_selector(AddFriendDialog::menuCallBack));
	cancelBtn->setTag(ADD_FRIEND_BUTTON_TAG_CANCEL);
	pushMenu(cancelBtn);


	return true;
}

void AddFriendDialog::menuCallBack( CCObject* pSender )
{
	CCLog("___AddFriendDialog menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);
	
	if(pMenu)
	{
		int tag = pMenu->getTag();
		CCLog("___AddFriendDialog menuCallBack,tag:%d", tag);
		switch(tag)
		{
			case ADD_FRIEND_BUTTON_TAG_CLOSE:
				{
					CCLog("___AddFriendDialog ADD_FRIEND_BUTTON_TAG_CLOSE...");
					this->removeFromParentAndCleanup(true);
				}
				break;
			case ADD_FRIEND_BUTTON_TAG_CONFIRM:
				{
					CCLog("___AddFriendDialog ADD_FRIEND_BUTTON_TAG_CONFIRM...");
					std::string name = mInputText->getText();
					
					int errorCode = SocialHelper::requestAddFriend(0, name);
					if(errorCode != Error::Success)
					{
						showErrorMessage(errorCode);
					}
				}
				break;
			case ADD_FRIEND_BUTTON_TAG_CANCEL:
				{
					CCLog("___AddFriendDialog ADD_FRIEND_BUTTON_TAG_CANCEL...");
					//this->removeFromParentAndCleanup(true);
				}
				break;
			default:
 				break;
		}
	}
	this->removeFromParentAndCleanup(true);
}

void AddFriendDialog::showErrorMessage(int errorCode)
{
	if(errorCode > Error::Success)
	{
		if(!this->getChildByTag(errorCode))
		{
			char buffer[80];
			sprintf(buffer, "addFriendError%d", errorCode);
			std::string errorKey = buffer;
			CCLabelTTF *errorDes = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "addFriendError");
			errorDes->setString(LayoutData::getString(CPModuleName::SOCIAL, errorKey).c_str());
			errorDes->setTag(errorCode);
			addChild(errorDes);
		}
	}
}

void AddFriendDialog::onCPEvent( const std::string &eventName )
{
	CCLog("___AddFriendDialog onCPEvent...");
	if (eventName == CPEventName::MSG_FINISH)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageAddFriendResponse")
		{
			CCLog("AddFriendDialog::onCPEvent HandleMessageAddFriendResponse...");
			if(CPEventHelper::isRequestSuccess())
			{
				this->removeFromParentAndCleanup(true);
				// 刷新好友列表
				CPEventHelper::msgNotify("HandleMessageRefreshFriendList", "", 0, 0, 0, 0);
			}
		}
	}
}