#include "FriendsPanel.h"
#include "RelationshipDefinition.h"
#include "dialog/AddFriendDialog.h"
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

FriendsPanel::FriendsPanel()
	:m_iCurrentType(-1)
	,mFriendList(NULL)
	,mCurrentIndex(-1)
	,mFriendListOffset(0)
	,m_pDialogMenu(NULL)
{
	CCLog("___FriendsPanel construct...");

	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_NOTIFY, this);
}


FriendsPanel::~FriendsPanel()
{
	CCLog("___FriendsPanel destroy...");
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_NOTIFY, this);
}

bool FriendsPanel::init()
{
	CCLog("___FriendsPanel init...");
	
	if (!CCLayer::init())
	{
		return false;
	}

	// 添加线框
	char ch[16];
	const int subBoardCnt = LayoutData::getInt(CPModuleName::SOCIAL, "subBoardCnt");
	for (int i = 0; i < subBoardCnt; i++)
	{
		sprintf(ch, "subBoard1%d", i);
		CCScale9Sprite *subBoard = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, ch);
		subBoard->setAnchorPoint(CCPointZero);
		addChild(subBoard);
		if(i == 1) // 获取列表框的坐标位移
		{
			mFriendListOffset = subBoard->getPositionX(); 
		}
	}

	// 添加列表框表头标题
	char ch1[32];
	const int headLabelCnt = LayoutData::getInt(CPModuleName::SOCIAL, "listHeadLabelCnt");
	for (int i = 0; i < headLabelCnt; i++)
	{
		sprintf(ch1, "listHeadLabel%d", i);
		CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, ch1);
		addChild(titleLabel);
	}

	// 添加右侧按钮
	const CCSize &switchSize = LayoutData::getSize(CPModuleName::SOCIAL, "rightBtn");
	mRightBtnMenu = CPItemComponents::create(switchSize, new CPLayoutList(CCSizeMake(87,72), true));
	mRightBtnMenu->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "rightBtn"));
	addChild(mRightBtnMenu);

	const int switchCnt = LayoutData::getInt(CPModuleName::SOCIAL, "rightBtnFriendsCnt");
	for (int i = 0; i < switchCnt; i++)
	{
		CCMenuItem *btn = getRightBtn(i);
		btn->setTarget(this, menu_selector(FriendsPanel::menuCallBack));
		mRightBtnMenu->addItem(btn);
	}

	// 添加好友列表数据
	addListUI();
	 
	//CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(FriendsPanel::addListItem));
	//updater->setUpdateTimes(30);
	//updater->setFinishHandler(this, callfunc_selector(FriendsPanel::addListFinish));
	//addChild(updater);
	//updater->start();

	// 请求好友列表数据
	SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_FRIEND);
	return true;
}

void FriendsPanel::menuCallBack( CCObject* pSender )
{
	CCLog("___FriendsPanel menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);
	
	if(pMenu)
	{
		int tag = pMenu->getTag() + 1;
		CCLog("___FriendsPanel menuCallBack,tag:%d", tag);
		if(!m_pDialogMenu)
		{
			// 弹出框添加
			m_pDialogMenu = GeneralMenu::create();
			m_pDialogMenu->setPosition(CCPointZero);
			addChild(m_pDialogMenu);
		}
		BasePanel* panel = NULL;
		switch(tag)
		{
			case FRIENDS_BUTTON_TAG_ADD:
				{
					CCLog("___FriendsPanel FRIENDS_BUTTON_TAG_ADD...");
					panel = AddFriendDialog::create();
				}
				break;
			case FRIENDS_BUTTON_TAG_CHAT:
				{
					CCLog("___FriendsPanel FRIENDS_BUTTON_TAG_CHAT...");
					if (mCurrentIndex >= 0 && mCurrentIndex < SocialData::mFriends.size())
					{
						SocialData::RelationData data = SocialData::mFriends[mCurrentIndex];
						ChatPanelHelper::openChatWithPartner(data.pid, data.name);
					}
				}
				break;
			/*case FRIENDS_BUTTON_TAG_PICHAT:
				{
					CCLog("___FriendsPanel FRIENDS_BUTTON_TAG_PICHAT...");
					if (mCurrentIndex >= 0 && mCurrentIndex < SocialData::mFriends.size())
					{
						SocialData::RelationData data = SocialData::mFriends[mCurrentIndex];
						ChatPanelHelper::openChatWithPartner(data.pid, data.name);
					}
				}
				break;*/
			case FRIENDS_BUTTON_TAG_DEL:
				{
					CCLog("___FriendsPanel FRIENDS_BUTTON_TAG_DEL...");
					if(!SocialData::mFriends.empty() && mCurrentIndex<SocialData::mFriends.size() && mCurrentIndex>=0)
					{
						SocialData::RelationData data = SocialData::mFriends[mCurrentIndex];
						SocialData::delPid = data.pid;
						SocialData::delName = data.name;
						SocialData::delType = RelationshipDefinition::SOCIAL_TYPE_FRIEND;
						panel = SocialDelConfirmDialog::create();
					}
				}
				break;
			case FRIENDS_BUTTON_TAG_TRACK:
				{
					CCLog("___FriendsPanel FRIENDS_BUTTON_TAG_TRACK...");
					if (!SocialData::mFriends.empty() && mCurrentIndex<SocialData::mFriends.size() && mCurrentIndex>=0)
					{
						SocialData::RelationData data = SocialData::mFriends[mCurrentIndex];
						SocialHelper::findPlayer(data.pid);
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
			m_pDialogMenu->addChild(panel);
		}
	}
}

CCMenuItem * FriendsPanel::getRightBtn( int index )
{
	CCScale9Sprite *norm = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnNorm");
	CCScale9Sprite *sel = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnSel");
	CCMenuItemSprite *ret = CCMenuItemSprite::create(norm, sel);
	
	char ch[18];
	sprintf(ch, "rightBtnFriends%d", index);
	const CCSize &itemSize = norm->getContentSize();
	CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "rightBtn");
	label->setString(LayoutData::getString(CPModuleName::SOCIAL, ch).c_str());
	label->setPosition(ccp(itemSize.width/2, itemSize.height/2));
	ret->addChild(label);
	return ret;
}

void FriendsPanel::addListUI()
{
	const CCSize &listSize = LayoutData::getSize(CPModuleName::SOCIAL, "friendList");
	mFriendList = CPItemComponents::create(listSize, new CPLayoutList());
	mFriendList->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "friendList"));
	addChild(mFriendList);
}

void FriendsPanel::addListItem(const std::string &name, const char gender, const char clazz, const int level)
{
	CCNode *norm = CCNode::create();
	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "listSel");
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
	item->setTarget(this, menu_selector(FriendsPanel::onClickListItem));
	mFriendList->addItem(item);

	// 姓名
	const int y = sel->getContentSize().height/2;
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel0");
	nameLabel->setString(name.c_str());
	nameLabel->setFontSize(18);
	nameLabel->setPositionX(nameLabel->getPositionX()-mFriendListOffset);
	nameLabel->setPositionY(y);
	item->addChild(nameLabel);

	// 性别
	char ch1[18];
	sprintf(ch1, "gender%d", (int)(gender));
	CCLabelTTF *genderLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel1");
	genderLabel->setString(LayoutData::getString(CPModuleName::SOCIAL, ch1).c_str());
	genderLabel->setFontSize(18);
	genderLabel->setPositionX(genderLabel->getPositionX()-mFriendListOffset);
	genderLabel->setPositionY(y);
	item->addChild(genderLabel);

	// 职业
	char ch2[18];
	sprintf(ch2, "class%d", (int)(clazz));
	CCLabelTTF *classLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel2");
	classLabel->setString(LayoutData::getString(CPModuleName::SOCIAL, ch2).c_str());
	classLabel->setFontSize(18);
	classLabel->setPositionX(classLabel->getPositionX()-mFriendListOffset);
	classLabel->setPositionY(y);
	item->addChild(classLabel);

	// 等级
	char ch3[18];
	sprintf(ch3, "%d", level);
	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel3");
	levelLabel->setString(ch3);
	levelLabel->setFontSize(18);
	levelLabel->setPositionX(levelLabel->getPositionX()-mFriendListOffset);
	levelLabel->setPositionY(y);
	item->addChild(levelLabel);
}

void FriendsPanel::onClickListItem( CCObject *target )
{
	const int index = mFriendList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
	}
}

void FriendsPanel::addListFinish()
{
	//mFriendList->setCurrentIndex(mCurrentIndex);
}

void FriendsPanel::onCPEvent( const std::string &eventName )
{
	CCLog("___FriendsPanel onCPEvent...");
	if (eventName == CPEventName::UI_NOTIFY)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageRelationListResponse")
		{
			CCLog("FriendsPanel::onCPEvent HandleMessageRelationListResponse...");
			if(CPEventHelper::isRequestSuccess())
			{
				// 清除列表控件并重新绘制
				mFriendList->removeFromParentAndCleanup(true);
				if(m_pDialogMenu){
					m_pDialogMenu->removeFromParentAndCleanup(true);
					m_pDialogMenu = NULL;
				}
				addListUI();
				for (SocialData::RelationList::iterator it = SocialData::mFriends.begin();it!=SocialData::mFriends.end();it++)
				{
					SocialData::RelationData data = *it;
					addListItem(data.name, data.gender, data.clazz, data.level);
				}
				mCurrentIndex = -1;
			}
		}
	}
	else if(eventName == CPEventName::MSG_CHANGE)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageRefreshFriendList")
		{
			CCLog("FriendsPanel::onCPEvent HandleMessageRefreshFriendList...");
			// 清除列表控件并重新绘制
			mFriendList->removeFromParentAndCleanup(true);
			m_pDialogMenu->removeFromParentAndCleanup(true);
			m_pDialogMenu = NULL;
			addListUI();
			mCurrentIndex = -1;
			// 请求好友列表数据
			SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_FRIEND);
		}
		else if(source == "HandleMessageDeleteFriendResponse")
		{
			CCLog("FriendsPanel::onCPEvent HandleMessageDeleteFriendResponse...");
			// 清除列表控件并重新绘制
			mFriendList->removeFromParentAndCleanup(true);
			m_pDialogMenu->removeFromParentAndCleanup(true);
			m_pDialogMenu = NULL;
			addListUI();
			mCurrentIndex = -1;
			// 请求好友列表数据
			SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_FRIEND);
		}
	}
}