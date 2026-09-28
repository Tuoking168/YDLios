#include "CouplePanel.h"
#include "RelationshipDefinition.h"
#include "dialog/SocialDelConfirmDialog.h"
#include "event/CPEventDispatcher.h"

#include "SocialModule.h"
#include "ModuleData.h"
#include "userdata/socialdata/SocialData.h"
#include "SocialHelper.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"

#include "ext/GeneralMenu.h"
#include "controls/CPChecker.h"
#include "controls/CPUpdater.h"
#include "controls/CPItemComponents.h"
#include "event/CPEventHelper.h"

#include "scene/panel/ChatPanel.h"


CouplePanel::CouplePanel()
	:m_iCurrentType(-1)
	,mCoupleList(NULL)
	,mCurrentIndex(0)
	,mCoupleListOffset(0)
	,m_pMainMenu(NULL)
{
	CCLog("___CouplePanel construct...");

	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_NOTIFY, this);
}


CouplePanel::~CouplePanel()
{
	CCLog("___CouplePanel destroy...");
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_NOTIFY, this);
}

bool CouplePanel::init()
{
	CCLog("___CouplePanel init...");
	
	if (!CCLayer::init())
	{
		return false;
	}

	// ???????
	char ch[16];
	const int subBoardCnt = LayoutData::getInt(CPModuleName::SOCIAL, "subBoardCnt");
	for (int i = 0; i < subBoardCnt; i++)
	{
		sprintf(ch, "subBoard2%d", i);
		CCScale9Sprite *subBoard = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, ch);
		subBoard->setAnchorPoint(CCPointZero);
		addChild(subBoard);
		if(i == 1) // ????§Ò????????¦Ë??
		{
			mCoupleListOffset = subBoard->getPositionX();
		}
	}

	// ?????§Ò?????????
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
	mRightBtnMenu = CPItemComponents::create(switchSize, new CPLayoutList(CCSizeMake(87,82), true));
	mRightBtnMenu->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "rightBtn"));
	addChild(mRightBtnMenu);

	const int switchCnt = LayoutData::getInt(CPModuleName::SOCIAL, "rightBtnCoupleCnt");
	for (int i = 0; i < switchCnt; i++)
	{
		CCMenuItem *btn = getRightBtn(i);
		btn->setTarget(this, menu_selector(CouplePanel::menuCallBack));
		mRightBtnMenu->addItem(btn);
	}

	// ????????§Ò?
	addListUI();

	/*CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(CouplePanel::addListItem));
	updater->setUpdateTimes(30);
	updater->setFinishHandler(this, callfunc_selector(CouplePanel::addListFinish));
	addChild(updater);
	updater->start();*/

	// ????????§Ò?????
	SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_COUPLE);

	return true;
}

void CouplePanel::onEnter()
{
	CCLayer::onEnter();
	CCLog("___CouplePanel onEnter...");

}

void CouplePanel::menuCallBack( CCObject* pSender )
{
	CCLog("___CouplePanel menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);
	
	if(pMenu)
	{
		int tag = pMenu->getTag() + 1;
		CCLog("___CouplePanel menuCallBack,tag:%d", tag);
		if(!m_pMainMenu)
		{
			// ??????????
			m_pMainMenu = GeneralMenu::create();
			m_pMainMenu->setPosition(CCPointZero);
			addChild(m_pMainMenu);
		}
		BasePanel* panel = NULL;
		switch(tag)
		{
			case COUPLE_BUTTON_TAG_CHAT:
				{
					CCLog("___CouplePanel COUPLE_BUTTON_TAG_CHAT (???)...");
					// ??ï“??????????????? ProposalRequestDialog
					CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"ProposalRequestDialog");
					CPEventHelper::uiNotify("UIShowSocialDialog","",0);
				}
				break;
			/*case COUPLE_BUTTON_TAG_PICHAT:
				{
					CCLog("___CouplePanel COUPLE_BUTTON_TAG_PICHAT...");
				}
				break;*/
			case COUPLE_BUTTON_TAG_CALL:
				{
					CCLog("___CouplePanel COUPLE_BUTTON_TAG_CALL...");
					// ??????????????¦Ë?¨°????????¨²??????TRACK???????
					if (mCurrentIndex >= 0 && mCurrentIndex < (int)SocialData::mCouples.size())
					{
						SocialData::RelationData data = SocialData::mCouples[mCurrentIndex];
						SocialHelper::findPlayer(data.pid);
					}
				}
				break;
			case COUPLE_BUTTON_TAG_DIVORCE:
				{
					CCLog("___CouplePanel COUPLE_BUTTON_TAG_DIVORCE...");
					if(mCurrentIndex>=0)
					{
						SocialData::RelationData data = SocialData::mCouples[mCurrentIndex];
						SocialData::delPid = data.pid;
						SocialData::delName = data.name;
						SocialData::delType = RelationshipDefinition::SOCIAL_TYPE_COUPLE;
						panel = SocialDelConfirmDialog::create();
					}
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
			m_pMainMenu->addChild(panel);
		}
	}
}

CCMenuItem * CouplePanel::getRightBtn( int index )
{
	CCScale9Sprite *norm = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnNorm");
	CCScale9Sprite *sel = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnSel");
	CCMenuItemSprite *ret = CCMenuItemSprite::create(norm, sel);
	
	char ch[20];
	sprintf(ch, "rightBtnCouple%d", index);
	const CCSize &itemSize = norm->getContentSize();
	CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "rightBtn");
	label->setString(LayoutData::getString(CPModuleName::SOCIAL, ch).c_str());
	label->setPosition(ccp(itemSize.width/2, itemSize.height/2));
	ret->addChild(label);
	return ret;
}

void CouplePanel::addListUI()
{
	const CCSize &listSize = LayoutData::getSize(CPModuleName::SOCIAL, "coupleList");
	mCoupleList = CPItemComponents::create(listSize, new CPLayoutList());
	mCoupleList->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "coupleList"));
	addChild(mCoupleList);
}

void CouplePanel::addListItem(const std::string &name, const char gender, const char clazz, const int level)
{
	CCNode *norm = CCNode::create();
	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "listSel");
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
	item->setTarget(this, menu_selector(CouplePanel::onClickListItem));
	mCoupleList->addItem(item);

	// ????
	const int y = sel->getContentSize().height/2;
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel0");
	nameLabel->setString(name.c_str());
	nameLabel->setFontSize(18);
	nameLabel->setPositionX(nameLabel->getPositionX()-mCoupleListOffset);
	nameLabel->setPositionY(y);
	item->addChild(nameLabel);

	// ???
	char ch1[18];
	sprintf(ch1, "gender%d", (int)(gender));
	CCLabelTTF *genderLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel1");
	genderLabel->setString(LayoutData::getString(CPModuleName::SOCIAL, ch1).c_str());
	genderLabel->setFontSize(18);
	genderLabel->setPositionX(genderLabel->getPositionX()-mCoupleListOffset);
	genderLabel->setPositionY(y);
	item->addChild(genderLabel);

	// ??
	char ch2[18];
	sprintf(ch2, "class%d", (int)(clazz));
	CCLabelTTF *classLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel2");
	classLabel->setString(LayoutData::getString(CPModuleName::SOCIAL, ch2).c_str());
	classLabel->setFontSize(18);
	classLabel->setPositionX(classLabel->getPositionX()-mCoupleListOffset);
	classLabel->setPositionY(y);
	item->addChild(classLabel);

	// ???
	char ch3[18];
	sprintf(ch3, "%d", level);
	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel3");
	levelLabel->setString(ch3);
	levelLabel->setFontSize(18);
	levelLabel->setPositionX(levelLabel->getPositionX()-mCoupleListOffset);
	levelLabel->setPositionY(y);
	item->addChild(levelLabel);
}

void CouplePanel::onClickListItem( CCObject *target )
{
	const int index = mCoupleList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
	}
}

void CouplePanel::addListFinish()
{
	//mMentorshipList->setCurrentIndex(mCurrentIndex);
}

void CouplePanel::onCPEvent( const std::string &eventName )
{
	CCLog("___CouplePanel onCPEvent...");
	if (eventName == CPEventName::UI_NOTIFY)
	{
		const std::string &source = CPEventHelper::getEventSource();
		if (source == "HandleMessageRelationListResponse")
		{
			CCLog("CouplePanel::onCPEvent HandleMessageRelationListResponse...");
			if(CPEventHelper::isRequestSuccess())
			{
				// ????§Ò?????????????
				mCoupleList->removeFromParentAndCleanup(true);
				addListUI();
				for (SocialData::RelationList::iterator it = SocialData::mCouples.begin();it!=SocialData::mCouples.end();it++)
				{
					SocialData::RelationData data = *it;
					addListItem(data.name, data.gender, data.clazz, data.level);
				}
				mCurrentIndex = -1;
			}
		}
	}
}