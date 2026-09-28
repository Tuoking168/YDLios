#include "MentorshipPanel.h"
#include "RelationshipDefinition.h"
#include "dialog/MasterListDialog.h"
#include "dialog/ApprenticeListDialog.h"
#include "dialog/SocialDelConfirmDialog.h"

#include "SocialModule.h"
#include "ModuleData.h"
#include "userdata/socialdata/SocialData.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "SocialHelper.h"

#include "ext/GeneralMenu.h"
#include "controls/CPChecker.h"
#include "controls/CPUpdater.h"
#include "controls/CPItemComponents.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"

#include "scene/panel/ChatPanel.h"

MentorshipPanel::MentorshipPanel()
	:m_iCurrentType(-1)
	,mMentorshipList(NULL)
	,mCurrentIndex(-1)
	,mMentorshipListOffset(0)
	,mCurrentListType(-1)
	,m_pDialogMenu(NULL)
{
	CCLog("___MentorshipPanel construct...");

	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_NOTIFY, this);
}


MentorshipPanel::~MentorshipPanel()
{
	CCLog("___MentorshipPanel destroy...");
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_NOTIFY, this);
}

bool MentorshipPanel::init()
{
	CCLog("___MentorshipPanel init...");
	
	if (!CCLayer::init())
	{
		return false;
	}
	
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	addChild(m_pMainMenu);

	// ???????
	char ch[16];
	const int subBoardCnt = LayoutData::getInt(CPModuleName::SOCIAL, "subBoardCnt");
	for (int i = 0; i < subBoardCnt; i++)
	{
		sprintf(ch, "subBoard2%d", i);
		CCScale9Sprite *subBoard = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, ch);
		subBoard->setAnchorPoint(CCPointZero);
		addChild(subBoard);
		if(i == 1) // ????งา????????ฆห??
		{
			mMentorshipListOffset = subBoard->getPositionX();
		}
	}

	// ?????งา?????????
	char ch1[32];
	const int headLabelCnt = LayoutData::getInt(CPModuleName::SOCIAL, "listHeadLabelCnt");
	for (int i = 0; i < headLabelCnt; i++)
	{
		sprintf(ch1, "listHeadLabel%d", i);
		CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, ch1);
		addChild(titleLabel);
	}

	// ????????
	const CCSize &switchSize = LayoutData::getSize(CPModuleName::SOCIAL, "rightBtn");
	mRightBtnMenu = CPItemComponents::create(switchSize, new CPLayoutList(CCSizeMake(87,72), true));
	mRightBtnMenu->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "rightBtn"));
	addChild(mRightBtnMenu);

	const int switchCnt = LayoutData::getInt(CPModuleName::SOCIAL, "rightBtnMentorshipCnt");
	for (int i = 0; i < switchCnt; i++)
	{
		CCMenuItem *btn = getRightBtn(i);
		btn->setTarget(this, menu_selector(MentorshipPanel::menuCallBack));
		mRightBtnMenu->addItem(btn);
	}

	// ?????????
	addMBottomButton();

	// ???????งา?????
	addListUI();

	/*CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(MentorshipPanel::addListItem));
	updater->setUpdateTimes(30);
	updater->setFinishHandler(this, callfunc_selector(MentorshipPanel::addListFinish));
	addChild(updater);
	updater->start();*/

	// ????????งา?????
	SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_MASTER);
	return true;
}

void MentorshipPanel::onEnter()
{
	CCLayer::onEnter();
	CCLog("___MentorshipPanel onEnter...");

}

void MentorshipPanel::menuCallBack( CCObject* pSender )
{
	CCLog("___MentorshipPanel menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);
	
	if(pMenu)
	{
		int tag = pMenu->getTag() + 1;
		CCLog("___MentorshipPanel menuCallBack,tag:%d", tag);
		if(!m_pDialogMenu)
		{
			// ??????????
			m_pDialogMenu = GeneralMenu::create();
			m_pDialogMenu->setPosition(CCPointZero);
			addChild(m_pDialogMenu);
		}
		BasePanel* panel = NULL;
		switch(tag)
		{
			case MENTORSHIP_BUTTON_TAG_MASTER:
				{
					CCLog("___MentorshipPanel MENTORSHIP_BUTTON_TAG_MASTER...");
					if(mCurrentListType != RelationshipDefinition::SOCIAL_TYPE_MASTER)
					{
						// ????????งา?????
						SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_MASTER);
						// ????????????
						if(mCurrentListType == RelationshipDefinition::SOCIAL_TYPE_APPRENTICE){
							m_pMainMenu->removeChildByTag(MENTORSHIP_BUTTON_TAG_AQUIT-1);
							m_pMainMenu->removeChildByTag(MENTORSHIP_BUTTON_TAG_ALIST-1);
						}
						addMBottomButton();
					}
				}
				break;
			case MENTORSHIP_BUTTON_TAG_APPRENTICE:
				{
					CCLog("___MentorshipPanel MENTORSHIP_BUTTON_TAG_APPRENTICE...");
					if(mCurrentListType != RelationshipDefinition::SOCIAL_TYPE_APPRENTICE)
					{
						// ????????งา?????
						SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_APPRENTICE);
						// ????????????
						if(mCurrentListType == RelationshipDefinition::SOCIAL_TYPE_MASTER){
							m_pMainMenu->removeChildByTag(MENTORSHIP_BUTTON_TAG_MQUIT-1);
							m_pMainMenu->removeChildByTag(MENTORSHIP_BUTTON_TAG_MLIST-1);
						}
						addABottomButton();
					}
				}
				break;
			/*case MENTORSHIP_BUTTON_TAG_PICHAT:
				{
					CCLog("___MentorshipPanel MENTORSHIP_BUTTON_TAG_PICHAT...");
				}
				break;*/
			case MENTORSHIP_BUTTON_TAG_CHAT:
				{
					CCLog("___MentorshipPanel MENTORSHIP_BUTTON_TAG_CHAT...");
					// ??????Tab???????????????????งา???????งา???????????????????งา?
					SocialData::RelationList *list = NULL;
					if (mCurrentListType == RelationshipDefinition::SOCIAL_TYPE_MASTER)
					{
						list = &SocialData::mMasters;
					}
					else if (mCurrentListType == RelationshipDefinition::SOCIAL_TYPE_APPRENTICE)
					{
						list = &SocialData::mApprentices;
					}
					if (list && mCurrentIndex >= 0 && mCurrentIndex < (int)list->size())
					{
						SocialData::RelationData data = (*list)[mCurrentIndex];
						ChatPanelHelper::openChatWithPartner(data.pid, data.name);
					}
				}
				break;
			case MENTORSHIP_BUTTON_TAG_CALL:
				{
					CCLog("___MentorshipPanel MENTORSHIP_BUTTON_TAG_CALL...");
					// ???????????ฆห?จฐ????????จฒ??????TRACK?????????
					SocialData::RelationList *list = NULL;
					if (mCurrentListType == RelationshipDefinition::SOCIAL_TYPE_MASTER)
					{
						list = &SocialData::mMasters;
					}
					else if (mCurrentListType == RelationshipDefinition::SOCIAL_TYPE_APPRENTICE)
					{
						list = &SocialData::mApprentices;
					}
					if (list && mCurrentIndex >= 0 && mCurrentIndex < (int)list->size())
					{
						SocialData::RelationData data = (*list)[mCurrentIndex];
						SocialHelper::findPlayer(data.pid);
					}
				}
				break;
			case MENTORSHIP_BUTTON_TAG_MQUIT:
				{
					CCLog("___MentorshipPanel MENTORSHIP_BUTTON_TAG_QUIT...");
					if(mCurrentIndex>=0 && mCurrentIndex<(int)SocialData::mMasters.size())
					{
						SocialData::RelationData data = SocialData::mMasters[mCurrentIndex];
						SocialData::delPid = data.pid;
						SocialData::delName = data.name;
						SocialData::delType = RelationshipDefinition::SOCIAL_TYPE_MASTER;
						panel = SocialDelConfirmDialog::create();
					}
				}
				break;
			case MENTORSHIP_BUTTON_TAG_MLIST:
				{
					CCLog("___MentorshipPanel MENTORSHIP_BUTTON_TAG_MLIST...");
					panel = MasterListDialog::create();
				}
				break;
			case MENTORSHIP_BUTTON_TAG_AQUIT:
				{
					CCLog("___MentorshipPanel MENTORSHIP_BUTTON_TAG_AQUIT...");
					if(mCurrentIndex>=0 && mCurrentIndex<(int)SocialData::mApprentices.size())
					{
						SocialData::RelationData data = SocialData::mApprentices[mCurrentIndex];
						SocialData::delPid = data.pid;
						SocialData::delName = data.name;
						SocialData::delType = RelationshipDefinition::SOCIAL_TYPE_APPRENTICE;
						panel = SocialDelConfirmDialog::create();
					}
				}
				break;
			case MENTORSHIP_BUTTON_TAG_ALIST:
				{
					CCLog("___MentorshipPanel MENTORSHIP_BUTTON_TAG_ALIST...");
					panel = ApprenticeListDialog::create();
				}
				break;
			default:
 				break;
		}
		pMenu->unselected();
		if (panel)
		{
			panel->setPosition(CCPointZero);
			panel->setAnchorPoint(CCPointZero);
			m_pDialogMenu->addChild(panel);
		}
	}
}

CCMenuItem * MentorshipPanel::getRightBtn( int index )
{
	CCScale9Sprite *norm = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnNorm");
	CCScale9Sprite *sel = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnSel");
	CCMenuItemSprite *ret = CCMenuItemSprite::create(norm, sel);
	
	char ch[20];
	sprintf(ch, "rightBtnMentorship%d", index);
	const CCSize &itemSize = norm->getContentSize();
	CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "rightBtn");
	label->setString(LayoutData::getString(CPModuleName::SOCIAL, ch).c_str());
	label->setPosition(ccp(itemSize.width/2, itemSize.height/2));
	ret->addChild(label);
	return ret;
}

void MentorshipPanel::addMBottomButton()
{

	// ???????
	CCScale9Sprite *norm = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnNorm");
	CCScale9Sprite *sel = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnSel");
	CCMenuItemSprite *ret = CCMenuItemSprite::create(norm, sel);
	const CCSize &itemSize = norm->getContentSize();
	CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "rightBtn");
	label->setString(LayoutData::getString(CPModuleName::SOCIAL, "rightBtnMentorship5").c_str());
	label->setFontSize(16);
	label->setPosition(ccp(itemSize.width/2, itemSize.height/2));
	ret->addChild(label);
	ret->setTarget(this, menu_selector(MentorshipPanel::menuCallBack));
	ret->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "mentorshipQuitBtn"));
	ret->setTag(MENTORSHIP_BUTTON_TAG_MQUIT-1);
	m_pMainMenu->addChild(ret);
	// ????งา?
	CCScale9Sprite *norm2 = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnNorm");
	CCScale9Sprite *sel2 = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnSel");
	CCMenuItemSprite *ret2 = CCMenuItemSprite::create(norm2, sel2);
	const CCSize &itemSize2 = norm2->getContentSize();
	CCLabelTTF *label2 = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "rightBtn");
	label2->setString(LayoutData::getString(CPModuleName::SOCIAL, "rightBtnMentorship6").c_str());
	label2->setFontSize(16);
	label2->setPosition(ccp(itemSize.width/2, itemSize.height/2));
	ret2->addChild(label2);
	ret2->setTarget(this, menu_selector(MentorshipPanel::menuCallBack));
	ret2->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "mentorshipMListBtn"));
	ret2->setTag(MENTORSHIP_BUTTON_TAG_MLIST-1);
	m_pMainMenu->addChild(ret2);
}

void MentorshipPanel::addABottomButton()
{

	// ??????
	CCScale9Sprite *norm = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnNorm");
	CCScale9Sprite *sel = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnSel");
	CCMenuItemSprite *ret = CCMenuItemSprite::create(norm, sel);
	const CCSize &itemSize = norm->getContentSize();
	CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "rightBtn");
	label->setString(LayoutData::getString(CPModuleName::SOCIAL, "rightBtnMentorship7").c_str());
	label->setFontSize(16);
	label->setPosition(ccp(itemSize.width/2, itemSize.height/2));
	ret->addChild(label);
	ret->setTarget(this, menu_selector(MentorshipPanel::menuCallBack));
	ret->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "mentorshipQuitBtn"));
	ret->setTag(MENTORSHIP_BUTTON_TAG_AQUIT-1);
	m_pMainMenu->addChild(ret);
	// ????งา?
	CCScale9Sprite *norm2 = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnNorm");
	CCScale9Sprite *sel2 = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnSel");
	CCMenuItemSprite *ret2 = CCMenuItemSprite::create(norm2, sel2);
	const CCSize &itemSize2 = norm2->getContentSize();
	CCLabelTTF *label2 = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "rightBtn");
	label2->setString(LayoutData::getString(CPModuleName::SOCIAL, "rightBtnMentorship8").c_str());
	label2->setFontSize(16);
	label2->setPosition(ccp(itemSize.width/2, itemSize.height/2));
	ret2->addChild(label2);
	ret2->setTarget(this, menu_selector(MentorshipPanel::menuCallBack));
	ret2->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "mentorshipMListBtn"));
	ret2->setTag(MENTORSHIP_BUTTON_TAG_ALIST-1);
	m_pMainMenu->addChild(ret2);
}

void MentorshipPanel::addListUI()
{
	const CCSize &listSize = LayoutData::getSize(CPModuleName::SOCIAL, "mentorshipList");
	mMentorshipList = CPItemComponents::create(listSize, new CPLayoutList());
	mMentorshipList->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "mentorshipList"));
	addChild(mMentorshipList);
}

void MentorshipPanel::addListItem(const std::string &name, const char gender, const char clazz, const int level)
{
	CCNode *norm = CCNode::create();
	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "listSel");
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
	item->setTarget(this, menu_selector(MentorshipPanel::onClickListItem));
	mMentorshipList->addItem(item);

	// ????
	const int y = sel->getContentSize().height/2;
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel0");
	nameLabel->setString(name.c_str());
	nameLabel->setFontSize(18);
	nameLabel->setPositionX(nameLabel->getPositionX()-mMentorshipListOffset);
	nameLabel->setPositionY(y);
	item->addChild(nameLabel);

	// ???
	char ch1[18];
	sprintf(ch1, "gender%d", (int)(gender));
	CCLabelTTF *genderLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel1");
	genderLabel->setString(LayoutData::getString(CPModuleName::SOCIAL, ch1).c_str());
	genderLabel->setFontSize(18);
	genderLabel->setPositionX(genderLabel->getPositionX()-mMentorshipListOffset);
	genderLabel->setPositionY(y);
	item->addChild(genderLabel);

	// ??
	char ch2[18];
	sprintf(ch2, "class%d", (int)(clazz));
	CCLabelTTF *classLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel2");
	classLabel->setString(LayoutData::getString(CPModuleName::SOCIAL, ch2).c_str());
	classLabel->setFontSize(18);
	classLabel->setPositionX(classLabel->getPositionX()-mMentorshipListOffset);
	classLabel->setPositionY(y);
	item->addChild(classLabel);

	// ???
	char ch3[18];
	sprintf(ch3, "%d", level);
	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel3");
	levelLabel->setString(ch3);
	levelLabel->setFontSize(18);
	levelLabel->setPositionX(levelLabel->getPositionX()-mMentorshipListOffset);
	levelLabel->setPositionY(y);
	item->addChild(levelLabel);
}

void MentorshipPanel::onClickListItem( CCObject *target )
{
	const int index = mMentorshipList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
	}
}

void MentorshipPanel::addListFinish()
{
	//mMentorshipList->setCurrentIndex(mCurrentIndex);
}

void MentorshipPanel::onCPEvent( const std::string &eventName )
{
	CCLog("___MentorshipPanel onCPEvent...");
	if (eventName == CPEventName::UI_NOTIFY)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageMasterListResponse")
		{
			CCLog("MentorshipPanel::onCPEvent HandleMessageMasterListResponse...");
			if(CPEventHelper::isRequestSuccess())
			{
				// ????งา?????????????
				mMentorshipList->removeFromParentAndCleanup(true);
				if(m_pDialogMenu)
				{
					m_pDialogMenu->removeFromParentAndCleanup(true);
					m_pDialogMenu = NULL;
				}
				addListUI();
				for (SocialData::RelationList::iterator it = SocialData::mMasters.begin();it!=SocialData::mMasters.end();it++)
				{
					SocialData::RelationData data = *it;
					addListItem(data.name, data.gender, data.clazz, data.level);
				}
				mCurrentListType = RelationshipDefinition::SOCIAL_TYPE_MASTER;
			}
		}
		else if(source == "HandleMessageApprenticeListResponse")
		{
			CCLog("MentorshipPanel::onCPEvent HandleMessageApprenticeListResponse...");
			if(CPEventHelper::isRequestSuccess())
			{
				// ????งา?????????????
				mMentorshipList->removeFromParentAndCleanup(true);
				if(m_pDialogMenu)
				{
					m_pDialogMenu->removeFromParentAndCleanup(true);
					m_pDialogMenu = NULL;
				}
				addListUI();
				for (SocialData::RelationList::iterator it = SocialData::mApprentices.begin();it!=SocialData::mApprentices.end();it++)
				{
					SocialData::RelationData data = *it;
					addListItem(data.name, data.gender, data.clazz, data.level);
				}
				mCurrentListType = RelationshipDefinition::SOCIAL_TYPE_APPRENTICE;
			}
		}
	}
	else if(eventName == CPEventName::MSG_CHANGE)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageMasterListResponse")
		{
			CCLog("MentorshipPanel::onCPEvent HandleMessageMasterListResponse...");
			// ????????งา?????
			SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_MASTER);
		}
		else if(source == "HandleMessageApprenticeListResponse")
		{
			CCLog("MentorshipPanel::onCPEvent HandleMessageApprenticeListResponse...");
			// ????????งา?????
			SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_APPRENTICE);
		}
	}
}