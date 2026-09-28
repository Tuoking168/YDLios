#include "EnemyPanel.h"
#include "RelationshipDefinition.h"
#include "event/CPEventDispatcher.h"

#include "SocialModule.h"
#include "ModuleData.h"
#include "userdata/socialdata/SocialData.h"
#include "SocialHelper.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "controls/CPChecker.h"
#include "controls/CPUpdater.h"
#include "controls/CPItemComponents.h"
#include "event/CPEventHelper.h"


EnemyPanel::EnemyPanel()
	:m_iCurrentType(-1)
	,mEnemyList(NULL)
	,mCurrentIndex(0)
	,mEnemyListOffset(0)
{
	CCLog("___EnemyPanel construct...");

	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_NOTIFY, this);
}


EnemyPanel::~EnemyPanel()
{
	CCLog("___EnemyPanel destory...");
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_NOTIFY, this);
}

bool EnemyPanel::init()
{
	CCLog("___EnemyPanel init...");
	
	if (!CCLayer::init())
	{
		return false;
	}

	std::string panelname=CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (panelname=="SocialPanel")
	{
		int data3=CPEventHelper::getEventIntData(CPEventData::VALUE_4);
		int g = 0;
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
			mEnemyListOffset = subBoard->getPositionX();
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

	const int switchCnt = LayoutData::getInt(CPModuleName::SOCIAL, "rightBtnEnemyCnt");
	for (int i = 0; i < switchCnt; i++)
	{
		CCMenuItem *btn = getRightBtn(i);
		btn->setTarget(this, menu_selector(EnemyPanel::menuCallBack));
		mRightBtnMenu->addItem(btn);
	}

	// 添加好友列表数据
	const CCSize &listSize = LayoutData::getSize(CPModuleName::SOCIAL, "enemyList");
	mEnemyList = CPItemComponents::create(listSize, new CPLayoutList());
	mEnemyList->setPosition(LayoutData::getPoint(CPModuleName::SOCIAL, "enemyList"));
	addChild(mEnemyList);

	//CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(EnemyPanel::addListItem));
	//updater->setUpdateTimes(30);
	//updater->setFinishHandler(this, callfunc_selector(EnemyPanel::addListFinish));
	//addChild(updater);
	//updater->start();

	// 请求仇人列表数据
	SocialHelper::requestRelationsData(RelationshipDefinition::SOCIAL_TYPE_ENEMY);

	return true;
}

void EnemyPanel::onEnter()
{
	CCLayer::onEnter();
	CCLog("___EnemyPanel onEnter...");

}

void EnemyPanel::menuCallBack( CCObject* pSender )
{
	CCLog("___EnemyPanel menuCallBack...");
	CCMenuItem* pMenu = dynamic_cast<CCMenuItem*>(pSender);
	
	if(pMenu)
	{
		int tag = pMenu->getTag() + 1;
		CCLog("___EnemyPanel menuCallBack,tag:%d", tag);
		BasePanel* panel = NULL;
		switch(tag)
		{
			case ENEMY_BUTTON_TAG_TRACK:
				{
					CCLog("___EnemyPanel FRIENDS_BUTTON_TAG_TRACK...");
					if (!SocialData::mEnemies.empty() && mCurrentIndex<SocialData::mEnemies.size() && mCurrentIndex>=0)
					{
						if (CommonFunction::checkZhuiZonglingCount()!=Error::Success)
						{
							return;
						}
						SocialData::RelationData data = SocialData::mEnemies[mCurrentIndex];
						SocialHelper::findPlayer(data.pid);
					}
				}
				break;
			default:
 				break;
		}
		pMenu->unselected();
	}
}

CCMenuItem * EnemyPanel::getRightBtn( int index )
{
	CCScale9Sprite *norm = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnNorm");
	CCScale9Sprite *sel = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "rightBtnSel");
	CCMenuItemSprite *ret = CCMenuItemSprite::create(norm, sel);
	
	char ch[18];
	sprintf(ch, "rightBtnEnemy%d", index);
	const CCSize &itemSize = norm->getContentSize();
	CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "rightBtn");
	label->setString(LayoutData::getString(CPModuleName::SOCIAL, ch).c_str());
	label->setPosition(ccp(itemSize.width/2, itemSize.height/2));
	ret->addChild(label);
	return ret;
}

void EnemyPanel::addListItem(const std::string &name, const char gender, const char clazz, const int level)
{
	CCNode *norm = CCNode::create();
	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::SOCIAL, "listSel");
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
	item->setTarget(this, menu_selector(EnemyPanel::onClickListItem));
	mEnemyList->addItem(item);

	// 姓名
	const int y = sel->getContentSize().height/2;
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel0");
	nameLabel->setString(name.c_str());
	nameLabel->setFontSize(18);
	nameLabel->setPositionX(nameLabel->getPositionX()-mEnemyListOffset);
	nameLabel->setPositionY(y);
	item->addChild(nameLabel);

	// 性别
	char ch1[18];
	sprintf(ch1, "gender%d", (int)(gender));
	CCLabelTTF *genderLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel1");
	genderLabel->setString(LayoutData::getString(CPModuleName::SOCIAL, ch1).c_str());
	genderLabel->setFontSize(18);
	genderLabel->setPositionX(genderLabel->getPositionX()-mEnemyListOffset);
	genderLabel->setPositionY(y);
	item->addChild(genderLabel);

	// 职业
	char ch2[18];
	sprintf(ch2, "class%d", (int)(clazz));
	CCLabelTTF *classLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel2");
	classLabel->setString(LayoutData::getString(CPModuleName::SOCIAL, ch2).c_str());
	classLabel->setFontSize(18);
	classLabel->setPositionX(classLabel->getPositionX()-mEnemyListOffset);
	classLabel->setPositionY(y);
	item->addChild(classLabel);

	// 等级
	char ch3[18];
	sprintf(ch3, "%d", level);
	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::SOCIAL, "listHeadLabel3");
	levelLabel->setString(ch3);
	levelLabel->setFontSize(18);
	levelLabel->setPositionX(levelLabel->getPositionX()-mEnemyListOffset);
	levelLabel->setPositionY(y);
	item->addChild(levelLabel);
}

void EnemyPanel::onClickListItem( CCObject *target )
{
	const int index = mEnemyList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
	}
}

void EnemyPanel::addListFinish()
{
	//mFriendList->setCurrentIndex(mCurrentIndex);
}

void EnemyPanel::onCPEvent( const std::string &eventName )
{
	CCLog("___EnemyPanel onCPEvent...");
	if (eventName == CPEventName::UI_NOTIFY)
	{
		const std::string &source = CPEventHelper::getEventSource();
		if (source == "HandleMessageRelationListResponse")
		{
			CCLog("EnemyPanel::onCPEvent HandleMessageRelationListResponse...");
			if(CPEventHelper::isRequestSuccess())
			{
				for (SocialData::RelationList::iterator it = SocialData::mEnemies.begin();it!=SocialData::mEnemies.end();it++)
				{
					SocialData::RelationData data = *it;
					addListItem(data.name, data.gender, data.clazz, data.level);
				}
			}
		}
	}
}