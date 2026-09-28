#include "ConvoyBeautyPanel.h"
#include "ActivityModule.h"
#include "ActivityDefinition.h"
#include "EvtDataDefinition.h"
#include "EntityDefinition.h"
#include "MsgActivity.h"

#include "FloatPanel.h"

#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"
#include "controls/CPCheckBox.h"
#include "controls/CPChecker.h"
#include "controls/CPComboBox.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "userdata/LayoutData.h"
#include "userdata/ActivityData.h"
#include "userdata/HeroData.h"
#include "userdata/StaticData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"

#include "utils/StringUtils.h"

#include "logic/ItemOperator.h"

#include "network/HandleMessage.h"


///////////ConvoyBeautyPanel///////////////////////////////////////////
ConvoyBeautyPanel::ConvoyBeautyPanel()
	:mStateLayer(NULL)
	,mCheckBox(NULL)
	,mChecker(NULL)
	,mComboBox(NULL)
	,mSelFlag(NULL)
	,mLastBeauty(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

ConvoyBeautyPanel::~ConvoyBeautyPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool ConvoyBeautyPanel::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}

	initUI();
	dataRequest();
	
	return true;
}

void ConvoyBeautyPanel::initUI()
{
	// title
	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "convoyBeautyTitle");
	addChild(title);

	// frame
	CCScale9Sprite *frame = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "convoyBeautyFrame");
	addChild(frame);

	// beauty list
	CCSprite *beauty = LayoutData::getSprite(CPModuleName::ACTIVITY, "convoyBeautyBoard");
	addChild(beauty);

	// question mark
	CCSprite *questionMark = LayoutData::getSprite(CPModuleName::ACTIVITY, "convoyBeautyQMark");
	addChild(questionMark);

	// last beauty
	mLastBeauty = LayoutData::getSprite(CPModuleName::ACTIVITY, "convoyBeautyLast");
	mLastBeauty->setVisible(false);
	addChild(mLastBeauty);

	// sel flag
	mSelFlag = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "convoyBeautySelFlag");
	mSelFlag->setPosition(ConvoyBeautyHelper::getPosition());
	addChild(mSelFlag);

	// label
	const CCSize &descSize = LayoutData::getSize(CPModuleName::ACTIVITY, "convoyBeautyDesc");
	const CCPoint &descPt = LayoutData::getPoint(CPModuleName::ACTIVITY, "convoyBeautyDesc");
	CPItemComponents *descList = CPItemComponents::create(descSize, new CPLayoutList());
	descList->setPosition(descPt);
	addChild(descList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "convoyBeautyScrollBar");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	descList->setScrollbar(scrollBar);

	CCLabelTTF *descLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "convoyBeautyDesc");	
	descList->addItem(descLabel);
	
	const int itemCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "convoyBeautyItemCnt");
	for (int i = 0; i < itemCnt; i++)
	{
		const std::string &key = "convoyBeautyItem" + StringUtils::toString(i);
		CCLabelTTF *itemLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, key);
		addChild(itemLabel);
	}

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *refreshBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "convoyBeautyRefresh");
	refreshBtn->setTarget(this, menu_selector(ConvoyBeautyPanel::onRefresh));
	menu->addChild(refreshBtn);

	CCMenuItemImage *startBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "convoyBeautyStart");
	startBtn->setTarget(this, menu_selector(ConvoyBeautyPanel::onStart));
	menu->addChild(startBtn);

	// state layer
	mStateLayer = CCLayer::create();
	addChild(mStateLayer);

	// checkBox
	mCheckBox = LayoutData::getCheckBox(CPModuleName::ACTIVITY, "convoyBeauty");
	addChild(mCheckBox);

	// comboBox
	mComboBox = LayoutData::getComboBox(CPModuleName::COMMON, "normal");
	mComboBox->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "convoyBeautyComboBox"));
	addChild(mComboBox);
	for (int i = Activity::Meinvhusong_Type_1; i <= Activity::Meinvhusong_Type_5; i++)
	{
		const std::string &key = "convoyBeautyTarget" + StringUtils::toString(i);
		mComboBox->addLabelItem(LayoutData::getString(CPModuleName::ACTIVITY, key));
	}

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void ConvoyBeautyPanel::refresh()
{
	mStateLayer->removeAllChildrenWithCleanup(true);

	CCLabelTTF *playCntLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "convoyBeautyCnt");
	playCntLabel->setString(ConvoyBeautyHelper::getPlayCntString().c_str());
	mStateLayer->addChild(playCntLabel);

	CCLabelTTF *vipLabel1 = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "convoyBeautyVIP");
	vipLabel1->setPosition(playCntLabel->getPosition());
	mStateLayer->addChild(vipLabel1);

	const int targetID = HeroData::getProp(Entity::attr_meinvhusong_mid);
	const std::string &colorKey = "convoyBeautyTarget" + StringUtils::toString(targetID);
	CCLabelTTF *playTargetLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "conveyBeautyTarget");
	playTargetLabel->setString(ConvoyBeautyHelper::getPlayTargetName().c_str());
	playTargetLabel->setColor(LayoutData::getColor3(CPModuleName::ACTIVITY, colorKey));
	mStateLayer->addChild(playTargetLabel);

	CCLabelTTF *refreshCntLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "convoyBeautyRefreshCnt");
	refreshCntLabel->setString(ConvoyBeautyHelper::getRefreshCntString().c_str());
	mStateLayer->addChild(refreshCntLabel);

	CCLabelTTF *rewardLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "convoyBeautyReward");
	rewardLabel->setString(ConvoyBeautyHelper::getRewardString().c_str());
	mStateLayer->addChild(rewardLabel);

	const int vip = HeroData::getProp(Entity::attr_vip_level);
	if (vip > 0)
	{
		const ccColor3B &yellow = LayoutData::getColor3(CPModuleName::COMMON, "yellow");
		vipLabel1->setColor(yellow);
	}

	mSelFlag->setPosition(ConvoyBeautyHelper::getPosition());
	if (targetID == Activity::Meinvhusong_Type_5)
	{
		if (!mLastBeauty->isVisible())
		{
			mLastBeauty->setVisible(true);
			mLastBeauty->stopAllActions();
			mLastBeauty->runAction(CCOrbitCamera::create(0.3f, 1.0f, 0, 180, 180, 0, 0));
		}
	}
	else
	{
		mLastBeauty->setVisible(false);
	}
}

void ConvoyBeautyPanel::onRefresh( CCObject *target )
{
	if (mCheckBox->isChecked())
	{
		const int targetID = HeroData::getProp(Entity::attr_meinvhusong_mid);
		if (targetID == mComboBox->getCurrentIndex())
		{
			return;
		}
	}

	if (ConvoyBeautyHelper::getRefreshRemainCnt() <= 0)
	{
		int cost = 0;
		StaticData::getGlobalData("girlRefreshCost", cost);
		if (!ItemOperator::testGoldEnough(cost, true))
		{
			return;
		}

		StrVector vect;
		vect.push_back(StringUtils::toString(cost));
		FloatPanel::show(FloatPanelType::Refresh_Meinvhusong, vect, this, floatpanel_selector(ConvoyBeautyPanel::onRefresh));
		return;
	}
	refreshRequest();
}

void ConvoyBeautyPanel::onRefresh( int btnType )
{
	if (btnType == Button_QD)
	{
		refreshRequest();
	}
}

void ConvoyBeautyPanel::onStart( CCObject *target )
{
	mChecker->start();
	HandleMessage::sendMessage(new MsgMeiNvHuSongStartRequest);
}

void ConvoyBeautyPanel::dataRequest()
{
	mChecker->start();
	HandleMessage::sendMessage(new MsgMeiNvHuSongEnterRequest);
}

void ConvoyBeautyPanel::refreshRequest()
{
	mChecker->start();
	HandleMessage::sendMessage(new MsgMeiNvHuSongRefreshRequest);
}

void ConvoyBeautyPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdMeiNvHuSongDataNotify")
		{
			refresh();
		}
		else if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (type == Entity::attr_meinvhusong_mid)
			{
				refresh();
			}
		}
		else if(source == "HandleMessageSyncPlayerEventDataNotify")
		{
			const int activityID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (activityID == ActivityData::getActivityID("mnhs"))
			{
				refresh();
			}
		}
	}
	else if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageMeiNvHuSongEnterResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				refresh();
			}
			else
			{
				close();
			}
		}
		else if (source == "HandleMessageMeiNvHuSongStartResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				close();
			}
		}
		else if (source == "HandleMessageMeiNvHuSongRefreshResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				if (mCheckBox->isChecked())
				{
					const int targetID = HeroData::getProp(Entity::attr_meinvhusong_mid);
					if (targetID != mComboBox->getCurrentIndex())
					{
						CCDelayTime *dt = CCDelayTime::create(1.0f);
						CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(ConvoyBeautyPanel::refreshRequest));
						runAction(CCSequence::create(dt, func, NULL));
					}
				}
			}
		}
	}
}

///////////ConvoyBeautyHelper//////////////////////////////////////////
std::string ConvoyBeautyHelper::getPlayCntString()
{
	int cntAdd = 0;
	const int vipLevel = HeroData::getProp(Entity::attr_vip_level);
	if (vipLevel > 0)
	{
		StaticData::getVIPData(vipLevel, "escortbelle", cntAdd);
	}
	
	int data1, playCnt = 0, data3;
	ActivityData::getExData(ActivityData::getActivityID("mnhs"), data1, playCnt, data3);
	const int playMax = ActivityData::getMeiNvHuSongData(Activity::Meinvhusong_round_max) + cntAdd;
	int remainCnt = playMax - playCnt;
	if (remainCnt < 0)
	{
		remainCnt = 0;
	}
	const std::string &ret = StringUtils::toString(remainCnt) + "/" + StringUtils::toString(playMax);
	return ret;
}

std::string ConvoyBeautyHelper::getRefreshCntString()
{
	const int refreshMax = ActivityData::getMeiNvHuSongData(Activity::Meinvhusong_refresh_max);
	const int remainCnt = getRefreshRemainCnt();
	const std::string &ret = StringUtils::toString(remainCnt) + "/" + StringUtils::toString(refreshMax);
	return ret;
}

std::string ConvoyBeautyHelper::getPlayTargetName()
{
	const int targetID = HeroData::getProp(Entity::attr_meinvhusong_mid);
	return LayoutData::getString(CPModuleName::ACTIVITY, "convoyBeautyTarget" + StringUtils::toString(targetID));
}

std::string ConvoyBeautyHelper::getRewardString()
{
	const int targetID = HeroData::getProp(Entity::attr_meinvhusong_mid);
	int exp = 0;
	int money = 0;
	StaticData::getConvoyBeautyExp(targetID, HeroData::getLevel(), exp);
	StaticData::getGlobalData("girlMoneyReward", money);
	std::string ret = LayoutData::getString(CPModuleName::COMMON, "exp") + ": " + StringUtils::toString(exp);
	ret += "  " + LayoutData::getString(CPModuleName::COMMON, "money") + ": " + StringUtils::toString(money);
	return ret;
}

int ConvoyBeautyHelper::getRefreshRemainCnt()
{
	int refreshCnt = 0, data2, data3;
	ActivityData::getExData(EvtData::evt_mnhs, refreshCnt, data2, data3);
	const int refreshMax = ActivityData::getMeiNvHuSongData(Activity::Meinvhusong_refresh_max);
	int remainCnt = refreshMax - refreshCnt;
	if (remainCnt < 0)
	{
		remainCnt = 0;
	}
	return remainCnt;
}

cocos2d::CCPoint ConvoyBeautyHelper::getPosition()
{
	const CCPoint &firstPt = LayoutData::getPoint(CPModuleName::ACTIVITY, "convoyBeautyFirstBeauty");
	const int width = LayoutData::getInt(CPModuleName::ACTIVITY, "convoyBeautyItemWidth");
	const int targetID = HeroData::getProp(Entity::attr_meinvhusong_mid);
	return ccp(firstPt.x + targetID * width, firstPt.y);
}
