#include "ApprenticeListDialog.h"
#include "../SocialHelper.h"
#include "RelationshipDefinition.h"

#include "SocialModule.h"
#include "ModuleData.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/socialdata/SocialData.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"

#include "ext/GeneralMenu.h"
#include "controls/CPChecker.h"
#include "controls/CPUpdater.h"
#include "controls/CPItemComponents.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

ApprenticeListDialog::ApprenticeListDialog()
	:mApprenticeListOffset(0)
	,mCurrentIndex(-1)
	,mApprenticeList(NULL)
{
	CCLog("___ApprenticeListDialog construct...");
	CPEvtDispatcher.addEventListener(CPEventName::UI_NOTIFY, this);
}


ApprenticeListDialog::~ApprenticeListDialog()
{
	CCLog("___ApprenticeListDialog destroy...");
	CPEvtDispatcher.removeEventListener(CPEventName::UI_NOTIFY, this);
}

bool ApprenticeListDialog::onInitDialog()
{
	CCLog("___ApprenticeListDialog onInitDialog...");

	// 添加背景
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "listDialogBkg");
	addChild(bkg);

	// 添加顶部Bar
	CCScale9Sprite *topbar = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "listDialogTopbar");
	addChild(topbar);

	// 添加关闭按钮
	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::SOCIAL, "listDialogClose");
	closeBtn->setTarget(this, menu_selector(ApprenticeListDialog::menuCallBack));
	closeBtn->setTag(APPRENTICE_LIST_BUTTON_TAG_CLOSE);
	pushMenu(closeBtn);

	// 添加线框
	char ch[16];
	const int subBoardCnt = LayoutData::getInt(CPModuleName::SOCIAL, "listSubBoardCnt");
	for (int i = 0; i < subBoardCnt; i++)
	{
		sprintf(ch, "listSubBoard1%d", i);
		CCScale9Sprite *subBoard = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, ch);
		subBoard->setAnchorPoint(CCPointZero);
		addChild(subBoard);
		if(i == 1) // 获取列表框的坐标位移
		{
			mApprenticeListOffset = subBoard->getPositionX();
		}
	}

	// 添加列表框表头标题
	char ch1[32];
	const int headLabelCnt = LayoutData::getInt(CPModuleName::SOCIAL, "listHeadLabelCnt");
	for (int i = 0; i < headLabelCnt; i++)
	{
		sprintf(ch1, "listDialogHeadLabel%d", i);
		CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, ch1);
		addChild(titleLabel);
	}

	// 添加底部按钮
	// 确定
	CCMenuItemImage *confirmBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "listDialogConfirm1");
	confirmBtn->setTarget(this, menu_selector(ApprenticeListDialog::menuCallBack));
	confirmBtn->setTag(APPRENTICE_LIST_BUTTON_TAG_CONFIRM);
	pushMenu(confirmBtn);

	// 取消
	CCMenuItemImage *cancelBtn = LayoutData::getMenuItemLabelImage(CPModuleName::SOCIAL, "listDialogCancel1");
	cancelBtn->setTarget(this, menu_selector(ApprenticeListDialog::menuCallBack));
	cancelBtn->setTag(APPRENTICE_LIST_BUTTON_TAG_CANCEL);
	pushMenu(cancelBtn);

	// 添加师傅列表数据
	addListUI();

	// 请求拜师列表数据
	SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_APPRENTICE_LIST);

	return true;
}

void ApprenticeListDialog::menuCallBack( CCObject* pSender )
{
	CCLog("___ApprenticeListDialog menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);

	if(pMenu)
	{
		int tag = pMenu->getTag();
		CCLog("___ApprenticeListDialog menuCallBack,tag:%d", tag);
		switch(tag)
		{
		case APPRENTICE_LIST_BUTTON_TAG_CLOSE:
			{
				CCLog("___ApprenticeListDialog APPRENTICE_LIST_BUTTON_TAG_CLOSE...");
				this->removeFromParentAndCleanup(true);
			}
			break;
		case APPRENTICE_LIST_BUTTON_TAG_CONFIRM:
			{
				CCLog("___ApprenticeListDialog APPRENTICE_LIST_BUTTON_TAG_CONFIRM...");
				if (mCurrentIndex < 0 || mCurrentIndex >= (int)SocialData::mApprenticeList.size())
						{
							break;
						}
						SocialData::RelationData data = SocialData::mApprenticeList[mCurrentIndex];

				int errorCode = SocialHelper::requestAddApprentice(data.pid);
				if(errorCode != Error::Success)
				{
					showErrorMessage(errorCode);
				}
				this->removeFromParentAndCleanup(true);
			}
			break;
		case APPRENTICE_LIST_BUTTON_TAG_CANCEL:
			{
				CCLog("___ApprenticeListDialog APPRENTICE_LIST_BUTTON_TAG_CANCEL...");
				this->removeFromParentAndCleanup(true);
			}
			break;
		default:
			break;
		}
	}
}

void ApprenticeListDialog::addListUI()
{
	const CCSize &listSize = LayoutData::getSize(CPModuleName::SOCIAL, "mentorshipDialogList");
	mApprenticeList = CPItemComponents::create(listSize, new CPLayoutList());
	mApprenticeList->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "mentorshipDialogList"));
	addCompMenu(mApprenticeList);
}

void ApprenticeListDialog::addListItem(const std::string &name, const char gender, const char clazz, const int level)
{
	CCNode *norm = CCNode::create();
	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "listSel");
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
	item->setTarget(this, menu_selector(ApprenticeListDialog::onClickListItem));
	mApprenticeList->addItem(item);

	// 姓名
	const int y = sel->getContentSize().height/2;
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listDialogHeadLabel0");
	nameLabel->setString(name.c_str());
	nameLabel->setFontSize(18);
	nameLabel->setPositionX(nameLabel->getPositionX()-mApprenticeListOffset);
	nameLabel->setPositionY(y);
	item->addChild(nameLabel);

	// 性别
	char ch1[18];
	sprintf(ch1, "gender%d", (int)(gender));
	CCLabelTTF *genderLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listDialogHeadLabel1");
	genderLabel->setString(LayoutData::getString(CPModuleName::SOCIAL, ch1).c_str());
	genderLabel->setFontSize(18);
	genderLabel->setPositionX(genderLabel->getPositionX()-mApprenticeListOffset);
	genderLabel->setPositionY(y);
	item->addChild(genderLabel);

	// 职业
	char ch2[18];
	sprintf(ch2, "class%d", (int)(clazz));
	CCLabelTTF *classLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listDialogHeadLabel2");
	classLabel->setString(LayoutData::getString(CPModuleName::SOCIAL, ch2).c_str());
	classLabel->setFontSize(18);
	classLabel->setPositionX(classLabel->getPositionX()-mApprenticeListOffset);
	classLabel->setPositionY(y);
	item->addChild(classLabel);

	// 等级
	char ch3[18];
	sprintf(ch3, "%d", level);
	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listDialogHeadLabel3");
	levelLabel->setString(ch3);
	levelLabel->setFontSize(18);
	levelLabel->setPositionX(levelLabel->getPositionX()-mApprenticeListOffset);
	levelLabel->setPositionY(y);
	item->addChild(levelLabel);
}

void ApprenticeListDialog::addListFinish()
{
	//mMentorshipList->setCurrentIndex(mCurrentIndex);
}

void ApprenticeListDialog::onClickListItem( CCObject *target )
{
	const int index = mApprenticeList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
	}
}

void ApprenticeListDialog::showErrorMessage(int errorCode)
{

}

void ApprenticeListDialog::onCPEvent( const std::string &eventName )
{
	CCLog("___ApprenticeListDialog onCPEvent...");
	if (eventName == CPEventName::UI_NOTIFY)
	{
		const std::string &source = CPEventHelper::getEventSource();
		if (source == "HandleMessageRelationListResponse")
		{
			CCLog("ApprenticeListDialog::onCPEvent HandleMessageRelationListResponse...");
			if(CPEventHelper::isRequestSuccess())
			{
				for (SocialData::RelationList::iterator it = SocialData::mApprenticeList.begin();it!=SocialData::mApprenticeList.end();it++)
				{
					SocialData::RelationData data = *it;
					addListItem(data.name, data.gender, data.clazz, data.level);
				}
				mCurrentIndex = -1;
			}
		}
	}
}