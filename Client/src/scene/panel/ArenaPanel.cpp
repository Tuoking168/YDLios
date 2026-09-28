#include "ArenaPanel.h"
#include "ActivityModule.h"
#include "ActivityDefinition.h"
#include "EvtDataDefinition.h"
#include "WorldDefinition.h"
#include "MsgActivity.h"
#include "MsgPlayer.h"
#include "MsgWorld.h"
#include "EntityDefinition.h"
#include "SceneDefinition.h"
#include "MainUIModule.h"

#include "ext/CCActionDestroy.h"

#include "logic/ItemOperator.h"

#include "scene/NotificationHelper.h"
#include "scene/panel/HeadPanel.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/OperateMenu.h"

#include "controls/CPChecker.h"
#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"
#include "controls/CPTips.h"
#include "controls/CPNodeHelper.h"
#include "controls/CPRichText.h"

#include "element/AnimElement.h"
#include "element/ElementDefinition.h"

#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/ActivityData.h"
#include "userdata/HeroData.h"
#include "userdata/StaticData.h"
#include "userdata/PlayerInfoData.h"
#include "userdata/netdata/GameRole.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "utils/StringUtils.h"
#include "utils/RichTextUtils.h"

#include "network/HandleMessage.h"

#include "script/LuaWrapper.h"



namespace ArenaState
{
	enum
	{
		ready = 0,
		fighting,
	};
}


////////ArenaPanel////////////////////////////////////////////////
ArenaPanel::ArenaPanel()
	:mChecker(NULL)
	,mStateLayer(NULL)
	,mRewardTimeLabel(NULL)
	,mCDLabel(NULL)
	,mCompetitorList(NULL)
	,mState(ArenaState::ready)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

ArenaPanel::~ArenaPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool ArenaPanel::init()//战力竞技ui
{
	if (!FullScreenPanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	initUI();
	dataRequest();

	return true;
}

void ArenaPanel::onEnter()
{
	FullScreenPanel::onEnter();
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);

	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}

void ArenaPanel::onExit()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
	FullScreenPanel::onExit();
}

void ArenaPanel::setState( int state )
{
	mState = state;
}

void ArenaPanel::initUI()
{
	// title
	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "arenaTitle");
	addChild(title);

	// board
	CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "arenaBoard");
	addChild(board);

	CCScale9Sprite *stateBoard = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "arenaStateBoard");
	addChild(stateBoard);

	// line
	CCSprite *line = LayoutData::getSprite(CPModuleName::ACTIVITY, "arenaLine");
	addChild(line);

	// my anim竞技场
	GameRole *myRole = GameData::getMyRole();
	if (myRole)
	{
		AnimElement *myAnim = AnimElement::create(0, CPElement::Type::player, HeroData::getGender());
		myAnim->setCloth(myRole->getDress(AVATAR_TYPE_CLOTH));
		myAnim->setWeapon(myRole->getDress(AVATAR_TYPE_WEAPON));
		myAnim->setWings(myRole->getDress(AVATAR_TYPE_WINGS));
		myAnim->setScale(LayoutData::getFloat(CPModuleName::ACTIVITY, "arenaAnimScale"));
		myAnim->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "arenaMyAnim"));
		addChild(myAnim);
	}

	// state layer
	mStateLayer = CCLayer::create();
	addChild(mStateLayer);

	// buff
	const int buffCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "arenaBuffItemCnt");
	for (int i = 0; i < buffCnt; i++)
	{
		const std::string &key = "arenaBuff" + StringUtils::toString(i);
		CCSprite *buff = LayoutData::getSprite(CPModuleName::ACTIVITY, key);
		mStateLayer->addChild(buff);

		const CCPoint &pt = buff->getPosition();
		const CCSize &size = buff->getContentSize();
		CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaBuff");
		label->setString(LayoutData::getString(CPModuleName::ACTIVITY, key).c_str());
		label->setAnchorPoint(ccp(0.5f, 0));
		label->setPosition(ccp(pt.x, pt.y + size.height/2));
		addChild(label);
	}

	// label
	const int itemCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "arenaLabelItemCnt");
	for (int i = 0; i < itemCnt; i++)
	{
		const std::string &key = "arenaItem" + StringUtils::toString(i);
		CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, key);
		addChild(label);
	}

	mRewardTimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRewardTime");
	addChild(mRewardTimeLabel);

	mCDLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaCD");
	addChild(mCDLabel);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *rankBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "arenaRank");
	rankBtn->setTarget(this, menu_selector(ArenaPanel::onRank));
	menu->addChild(rankBtn);

	CCMenuItemImage *recordBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "arenaRecord");
	recordBtn->setTarget(this, menu_selector(ArenaPanel::onRecord));
	menu->addChild(recordBtn);

	const int rewardShowCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "arenaRankRewardCnt");
	for (int i = 0; i < rewardShowCnt; i++)
	{
		const std::string &key = "arenaRankReward" + StringUtils::toString(i);
		CCMenuItemImage *rewardBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, key);
		rewardBtn->setTarget(this, menu_selector(ArenaPanel::onRankReward));
		menu->addChild(rewardBtn, 0, i + 1);
	}

	CCMenuItemImage *addCountBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "arenaAddCount");
	addCountBtn->setTarget(this, menu_selector(ArenaPanel::onAddCount));
	menu->addChild(addCountBtn);

	CCMenuItemImage *cleanCDBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "arenaCleanCD");
	cleanCDBtn->setTarget(this, menu_selector(ArenaPanel::onCleanCD));
	menu->addChild(cleanCDBtn);

	const int buffRefreshCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "arenaBuffRefreshCnt");
	for (int i = 0; i < buffRefreshCnt; i++)
	{
		if  (i == 1) continue;
		const std::string &key = "arenaBuffRefresh" + StringUtils::toString(i);
		CCMenuItemImage *btn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, key);
		btn->setTarget(this, menu_selector(ArenaPanel::onRefreshBuff));
		menu->addChild(btn, 0, i + 1);
	}

	// list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "arenaList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "arenaItem");
	const int perLine = LayoutData::getInt(CPModuleName::ACTIVITY, "arenaListPerLine");
	mCompetitorList = CPItemComponents::create(listSize, new CPLayoutGrid(perLine, itemSize, true));
	mCompetitorList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "arenaList"));
	addChild(mCompetitorList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "arenaScrollBar");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mCompetitorList->setScrollbar(scrollBar);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void ArenaPanel::refreshState()
{
	mStateLayer->removeAllChildrenWithCleanup(true);

	//
	CCLabelTTF *myRankLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaMyRank");
	myRankLabel->setString(StringUtils::toString(HeroData::getProp(Entity::attr_arena_rank)).c_str());
	mStateLayer->addChild(myRankLabel);

	CCLabelTTF *myWinLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaMyWin");
	myWinLabel->setString(StringUtils::toString(HeroData::getProp(Entity::attr_arena_wincount)).c_str());
	mStateLayer->addChild(myWinLabel);

	CCLabelTTF *myRewardLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaMyReward");
	myRewardLabel->setString(ArenaHelper::getReward().c_str());
	mStateLayer->addChild(myRewardLabel);

	CCLabelTTF *playCntLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaPlayCnt");
	playCntLabel->setString(ArenaHelper::getPlayCnt().c_str());
	mStateLayer->addChild(playCntLabel);

	CCLabelTTF *fightLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaFight");
	fightLabel->setString(StringUtils::toString(HeroData::getProp(Entity::attr_combat_data_num)).c_str());
	mStateLayer->addChild(fightLabel);

	const CCSize &fightLabelSize = fightLabel->getContentSize();
	const CCPoint &fightLabelPt = fightLabel->getPosition();
	CCLabelTTF *fightAddLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaFightAdd");
	fightAddLabel->setString(ArenaHelper::getFightAdd().c_str());
	fightAddLabel->setPosition(ccp(fightLabelPt.x + fightLabelSize.width, fightLabelPt.y));
	mStateLayer->addChild(fightAddLabel);

	// buff
	std::string buffKey;
	const int buffCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "arenaBuffItemCnt");
	for (int i = 0; i < buffCnt; i++)
	{
		if (i == HeroData::getProp(Entity::attr_arena_buff))
		{
			buffKey = "arenaBuffSel" + StringUtils::toString(i);
		}
		else
		{
			buffKey = "arenaBuff" + StringUtils::toString(i);
		}
		CCSprite *buff = LayoutData::getSprite(CPModuleName::ACTIVITY, buffKey);
		mStateLayer->addChild(buff);
	}
}

void ArenaPanel::refreshTime()
{
	int time = HeroData::getRewardTime(EvtData::rw_rwzljj);
	const ccColor3B &red = LayoutData::getColor3(CPModuleName::COMMON, "red");
	const ccColor3B &green = LayoutData::getColor3(CPModuleName::COMMON, "green");

	ccColor3B color = ((time > 0) ? red : green);
	mRewardTimeLabel->setString(StringUtils::timeToString(time, TimeType::hms).c_str());
	mRewardTimeLabel->setColor(color);

	time = HeroData::getCommonCD(EvtData::cd_cdzljj);
	color = ((time > 0) ? red : green);
	mCDLabel->setString(StringUtils::timeToString(time, TimeType::ms).c_str());
	mCDLabel->setColor(color);
}

void ArenaPanel::refreshList()
{
	mCompetitorList->removeAllItems();
	const IDVector &vect = ActivityData::getArenaCompetitorList();
	for (int i = 0; i < (int)vect.size(); i++)
	{
		CCNode *norm = getListNormNode(vect[i]);
		CCNode *sel = getListSelNode(vect[i]);
		CCMenuItemSprite *item = CCMenuItemSprite::create(norm, sel);
		mCompetitorList->addItem(item);
	}

	if (vect.size() > 0)
	{
		mCompetitorList->setCurrentIndex(0);
	}
}

void ArenaPanel::showRecord()
{
	CPTips *tips = CPTips::create(ArenaRecordPanel::create());
	tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
	addChild(tips);
}

void ArenaPanel::onRank( CCObject *target )
{
	CPTips *tips = CPTips::create(ArenaRankPanel::create());
	tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
	addChild(tips);
}

void ArenaPanel::onRecord( CCObject *target )
{
	mChecker->start();
	ArenaHelper::recordRequest();
}

void ArenaPanel::onAddCount( CCObject *target )
{
	int cost = 0;
	StaticData::getGlobalData("arenaAddCountCost", cost);
	if (!ItemOperator::testGoldEnough(cost))
	{
		return;
	}
	
	StrVector vect;
	vect.push_back(StringUtils::toString(cost));
	FloatPanel::show(FloatPanelType::Arena_add_count, vect, this, floatpanel_selector(ArenaPanel::onAddCount));
}

void ArenaPanel::onAddCount( int btnType )
{
	if (btnType == Button_QD)
	{
		mChecker->start();
		ArenaHelper::addCountRequest();
	}
}

void ArenaPanel::onCleanCD( CCObject *target )
{
	const int cd = HeroData::getCommonCD(EvtData::cd_cdzljj);
	if (cd <= 0)
	{
		return;
	}

	int cost = 0;
	StaticData::getClearCDCost(EvtData::cd_cdzljj, cost);
	if (!ItemOperator::testGoldEnough(cost))
	{
		return;
	}

	StrVector vect;
	vect.push_back(StringUtils::toString(cost));
	FloatPanel::show(FloatPanelType::Arena_clear_cd, vect, this, floatpanel_selector(ArenaPanel::onCleanCD));
}

void ArenaPanel::onCleanCD( int btnType )
{
	if (btnType == Button_QD)
	{
		mChecker->start();
		ArenaHelper::cleanCoolDownRequest();
	}
}

void ArenaPanel::onRefreshBuff( CCObject *target )
{
	const int buff = HeroData::getProp(Entity::attr_arena_buff);
	if (buff == Activity::ABuff_tianjun)
	{
		CPEventHelper::uiNotify("ArenaPanel", "", Error::Arena_buff_best);
		return;
	}

	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		int cost = 0;
		const int &refreshType = node->getTag();
		if (refreshType == Activity::AR_money)
		{
			StaticData::getGlobalData("arenaRefreshBuffByMoney", cost);
			if (!ItemOperator::testMoneyEnough(cost))
			{
				return;
			}

			mChecker->start();
			ArenaHelper::refreshBuffRequest(refreshType);
		}
		else if (refreshType == Activity::AR_gold)
		{
			StaticData::getGlobalData("arenaRefreshBuffByGold", cost);
			if (!ItemOperator::testGoldEnough(cost))
			{
				return;
			}

			StrVector vect;
			vect.push_back(StringUtils::toString(cost));
			FloatPanel::show(FloatPanelType::Arena_gold_refresh, vect, this, floatpanel_selector(ArenaPanel::onGoldRefresh));
		}
		else
		{
			StaticData::getGlobalData("arenaRefreshBuffByOneKey", cost);
			if (!ItemOperator::testGoldEnough(cost))
			{
				return;
			}

			StrVector vect;
			vect.push_back(StringUtils::toString(cost));
			FloatPanel::show(FloatPanelType::Arena_super_refresh, vect, this, floatpanel_selector(ArenaPanel::onSuperRefresh));
		}
	}
}

void ArenaPanel::onGoldRefresh( int btnType )
{
	if (btnType == Button_QD)
	{
		mChecker->start();
		ArenaHelper::refreshBuffRequest(Activity::AR_gold);
	}
}

void ArenaPanel::onSuperRefresh( int btnType )
{
	if (btnType == Button_QD)
	{
		mChecker->start();
		ArenaHelper::refreshBuffRequest(Activity::AR_maxdata);
	}
}

void ArenaPanel::onChallenge( CCObject *target )
{
	if (mState != ArenaState::ready)
	{
		return;
	}

	const int cd = HeroData::getCommonCD(EvtData::cd_cdzljj);
	if (cd > 0)
	{
		CPEventHelper::uiNotify("ArenaPanel", "", Error::CDhasLocked);
		return;
	}

	const IDVector &vect = ActivityData::getArenaCompetitorList();
	const int index = mCompetitorList->getCurrentIndex();
	if (0 <= index && index < (int)vect.size())
	{
		ArenaFightPanel *panel = ArenaFightPanel::createWithData(this, vect[index]);
		if (panel)
		{
			addChild(panel, 1);
		}
	}
}

void ArenaPanel::onRankReward( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int rank = node->getTag();
		CPTips *tips = CPTips::create(ArenaRewardPanel::create(rank));
		tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
		addChild(tips);
	}
}

void ArenaPanel::dataRequest()
{
	mChecker->start();
	ArenaHelper::dataRequest();
}
// 创建竞技场列表中的普通对手项节点
// 这个函数用于构建竞技场界面中每个对手的显示项
CCNode * ArenaPanel::getListNormNode( int rank )
{
	int pid = 0, level= 0, reborn = 0, job = 0, gender = 0;
	int cloth = 0, weapon = 0, wings = 0;
	std::string name, guildName;
	ActivityData::getArenaCompetitor(rank, pid, level, name, reborn, job, gender, cloth, weapon, wings, guildName);

	// anim
	CCScale9Sprite *ret = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "arenaListItemBoard");
	AnimElement *anim = AnimElement::create(0, CPElement::Type::player, gender);
	anim->setCloth(cloth);
	anim->setWeapon(weapon);
	anim->setWings(wings);
	anim->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "arenaPlayerAnim"));
	ret->addChild(anim);

	// name
	CCSprite *nameBoard = LayoutData::getSprite(CPModuleName::ACTIVITY, "arenaNameBoard");
	ret->addChild(nameBoard);

	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaPlayerName");
	nameLabel->setString(name.c_str());
	nameLabel->setPositionX(nameBoard->getContentSize().width/2);
	nameLabel->setPositionY(nameBoard->getContentSize().height/2);
	nameBoard->addChild(nameLabel);

	// level
	CCSprite *levelBoard = LayoutData::getSprite(CPModuleName::ACTIVITY, "arenaLevelBoard");
	ret->addChild(levelBoard);

	const std::string &lvlStr = "Lv." + StringUtils::toString(level);
	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaPlayerLevel");
	levelLabel->setString(lvlStr.c_str());
	levelLabel->setPositionX(levelBoard->getContentSize().width/2);
	levelLabel->setPositionY(levelBoard->getContentSize().height/2);
	levelBoard->addChild(levelLabel);

	// rank
	CCLabelTTF *rankLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaPlayerRank");
	ret->addChild(rankLabel);
	const std::string &rankStr = rankLabel->getString() + StringUtils::toString(rank);
	rankLabel->setString(rankStr.c_str());

	return ret;
}

CCNode * ArenaPanel::getListSelNode( int rank )
{
	CCNode *ret = getListNormNode(rank);

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	ret->addChild(menu);

	CCMenuItemImage *challengeBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "arenaChallenge");
	challengeBtn->setTarget(this, menu_selector(ArenaPanel::onChallenge));
	menu->addChild(challengeBtn);

	return ret;
}

void ArenaPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageArenaListNotify" ||
			source == "HandleMessageUpdPlayerPropsDataNotify" ||
			source == "HandleMessageSyncPlayerEventDataNotify")
		{
			refreshState();
			if (source == "HandleMessageArenaListNotify")
			{
				refreshList();
			}
		}
	}
	else if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageOpenArenaResponse" ||
			source == "HandleMessageRefreshArenaBuffResponse" ||
			source == "HandleMessageBuyArenaFightCntResponse" ||
			source == "HandleMessageCleanCoolDownResponse")
		{
			mChecker->stop();
		}
		else if (source == "HandleMessageArenaFightResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				ArenaHelper::dataRequest();
			}
		}
		else if (source == "HandleMessageGetPlayerArenaFightRecordResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				showRecord();
			}
		}
	}
	else if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			refreshTime();
		}
	}
}

//////////ArenaRewardPanel////////////////////////////////////////////
ArenaRewardPanel::ArenaRewardPanel()
	:mChecker(NULL)
	,mDataLayer(NULL)
	,mRank(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

ArenaRewardPanel::~ArenaRewardPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

ArenaRewardPanel * ArenaRewardPanel::create( int rank )
{
	ArenaRewardPanel *ret = new ArenaRewardPanel;
	if (ret && ret->initWithData(rank))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool ArenaRewardPanel::initWithData( int rank )
{
	if (!CPTipsSub::init())
	{
		return false;
	}

	mRank = rank;
	initUI();
	dataRequest();

	return true;
}

void ArenaRewardPanel::initUI()
{
	// board
	CCSprite *board = LayoutData::getSprite(CPModuleName::COMMON, "floatBoard");
	addChild(board);
	setContentSize(board->getContentSize());

	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRewardTitle");
	addChild(titleLabel);

	// data layer
	mDataLayer = CCLayer::create();
	addChild(mDataLayer);

	// desc
	CCLabelTTF *descLabel1 = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRewardDesc1");
	addChild(descLabel1);

	CCLabelTTF *descLabel2 = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRewardDesc2");
	addChild(descLabel2);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "floatClose");
	closeBtn->setTarget(this, menu_selector(ArenaRewardPanel::onClose));
	menu->addChild(closeBtn);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void ArenaRewardPanel::refresh()
{
	mDataLayer->removeAllChildren();

	int pid = 0, job = 0, fightPoint = 0;
	std::string name;
	ActivityData::getArenaRank(mRank, pid, name, job, fightPoint);

	// desc
	CCLabelTTF *rankLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRewardRank");
	mDataLayer->addChild(rankLabel);
	char ch[128];
	sprintf(ch, rankLabel->getString(), mRank);
	rankLabel->setString(ch);

	CCLabelTTF *rankNameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRewardRankPlayer");
	rankNameLabel->setString(name.c_str());
	rankNameLabel->setPositionX(rankLabel->getPositionX() + rankLabel->getContentSize().width);
	mDataLayer->addChild(rankNameLabel);

	CCLabelTTF *rewardLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRewardReward");
	mDataLayer->addChild(rewardLabel);

	const int level = ActivityData::getWorldIntProp(WorldDefination::prop_arena_first_lvl, mRank - 1);
	int exp = 0, honor = 0;
	ArenaHelper::getRankReward(level, mRank, exp, honor);
	std::string str = LayoutData::getString(CPModuleName::COMMON, "exp") + " " + StringUtils::toString(exp);
	CCLabelTTF *rewardItemLabel1 = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRewardItem1");
	rewardItemLabel1->setString(str.c_str());
	mDataLayer->addChild(rewardItemLabel1);

	str = LayoutData::getString(CPModuleName::COMMON, "honor") + " " + StringUtils::toString(honor);
	CCLabelTTF *rewardItemLabel2 = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRewardItem2");
	rewardItemLabel2->setString(str.c_str());
	mDataLayer->addChild(rewardItemLabel2);
}

void ArenaRewardPanel::onClose( CCObject *target )
{
	close();
}

void ArenaRewardPanel::dataRequest()
{
	mChecker->start();
	ArenaHelper::rankRequest(1);
	ArenaHelper::heighThreeRequest();
}

void ArenaRewardPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageGetArenaHeroResponse"
			|| source == "HandleMessageSyncWorldDataResponse")
		{
			mChecker->stop();
			refresh();
		}
	}
}

///////////ArenaRankPanel////////////////////////////////////////
ArenaRankPanel::ArenaRankPanel()
	:mChecker(NULL)
	,mRankList(NULL)
	,mPreBtn(NULL)
	,mNextBtn(NULL)
	,mPageLabel(NULL)
	,mCurrentPage(1)
	,mMaxPage(1)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

ArenaRankPanel::~ArenaRankPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool ArenaRankPanel::init()
{
	if (!CCNode::init())
	{
		return false;
	}

	initUI();

	mChecker->start();
	ArenaHelper::rankRequest(mCurrentPage);

	return true;
}

void ArenaRankPanel::initUI()
{
	// board
	CCSprite *board = LayoutData::getSprite(CPModuleName::COMMON, "floatBoard");
	addChild(board);
	setContentSize(board->getContentSize());

	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRankTitle");
	addChild(titleLabel);

	// item title
	const int itemCnt = LayoutData::getInt(CPModuleName::ACTIVITY, "arenaRankItemTitleCnt");
	for (int i = 0; i < itemCnt; i++)
	{
		const std::string &key = "arenaRankItemTitle" + StringUtils::toString(i);
		CCLabelTTF *itemTitleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, key);
		addChild(itemTitleLabel);
	}

	// record
	const CCSize &recordSize = LayoutData::getSize(CPModuleName::ACTIVITY, "arenaRankList");
	mRankList = CPItemComponents::create(recordSize, new CPLayoutList);
	mRankList->setClickSensitive(true);
	mRankList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "arenaRankList"));
	addChild(mRankList);

	// page label
	mPageLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRankPage");
	addChild(mPageLabel);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	mPreBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "arenaRankPrePage");
	mPreBtn->setTarget(this, menu_selector(ArenaRankPanel::onPrePage));
	menu->addChild(mPreBtn);

	mNextBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "arenaRankNextPage");
	mNextBtn->setTarget(this, menu_selector(ArenaRankPanel::onNextPage));
	menu->addChild(mNextBtn);

	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "floatClose");
	closeBtn->setTarget(this, menu_selector(ArenaRankPanel::onClose));
	menu->addChild(closeBtn);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void ArenaRankPanel::refreshList()
{
	mRankList->removeAllItems();

	const IDVector &rankVect = ActivityData::getArenaRankVect();
	for (int i = 0; i < (int)rankVect.size(); i++)
	{
		CCMenuItem *item = getItem(rankVect[i]);
		item->setTarget(this, menu_selector(ArenaRankPanel::onPlayer));
		mRankList->addItem(item);
		item->setTag(rankVect[i]);
	}
}

void ArenaRankPanel::refreshMenu()
{
	mPreBtn->setEnabled(mCurrentPage > 1);
	mNextBtn->setEnabled(mCurrentPage < mMaxPage);

	const std::string pageStr = StringUtils::toString(mCurrentPage) + "/" + StringUtils::toString(mMaxPage);
	mPageLabel->setString(pageStr.c_str());
}

void ArenaRankPanel::onPlayer( CCObject *target )
{
	const int rank = mRankList->getCurrentIndex();
	const int pid = ActivityData::getArenaRankPID(rank);
	if (pid > 0 && pid != HeroData::getPID())
	{
		OperateMenu  *opMenu = OperateMenu::create(OperateMenu::Operate_Type_Player);
		opMenu->setPlayerID(pid);
		opMenu->setPlayerName(ActivityData::getArenaRankName(rank));
		opMenu->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "arenaOperateMenu"));
		addChild(opMenu);
	}
}

void ArenaRankPanel::onPrePage( CCObject *target )
{
	mChecker->start();
	ArenaHelper::rankRequest(mCurrentPage - 1);
}

void ArenaRankPanel::onNextPage( CCObject *target )
{
	mChecker->start();
	ArenaHelper::rankRequest(mCurrentPage + 1);
}

void ArenaRankPanel::onClose( CCObject *target )
{
	close();
}

CCMenuItem * ArenaRankPanel::getItem( int rank )
{
	CCScale9Sprite *sel = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "arenaRankListSel");
	CCNode *norm = CCNode::create();
	norm->setContentSize(sel->getContentSize());
	CCMenuItemSprite *ret = CCMenuItemSprite::create(norm, sel);

	int pid = 0, job = 0, fightPoint = 0;
	std::string name;
	ActivityData::getArenaRank(rank, pid, name, job, fightPoint);

	ccColor3B color = ccWHITE;
	if (rank <= 3)
	{
		color = LayoutData::getColor3(CPModuleName::ACTIVITY, "arenaRank" + StringUtils::toString(rank));
	}

	const int y = sel->getContentSize().height/2;
	CCLabelTTF *rankLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRankItemRank");
	rankLabel->setString(StringUtils::toString(rank).c_str());
	rankLabel->setColor(color);
	rankLabel->setPositionY(y);
	ret->addChild(rankLabel);

	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRankItemName");
	nameLabel->setString(name.c_str());
	nameLabel->setColor(color);
	nameLabel->setPositionY(y);
	ret->addChild(nameLabel);

	const std::string &jobStr = LayoutData::getString(CPModuleName::COMMON, "job" + StringUtils::toString(job));
	CCLabelTTF *jobLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRankItemJob");
	jobLabel->setString(jobStr.c_str());
	jobLabel->setColor(color);
	jobLabel->setPositionY(y);
	ret->addChild(jobLabel);

	CCLabelTTF *fightLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRankItemFightPoint");
	fightLabel->setString(StringUtils::toString(fightPoint).c_str());
	fightLabel->setColor(color);
	fightLabel->setPositionY(y);
	ret->addChild(fightLabel);

	return ret;
}

void ArenaRankPanel::testPage()
{
	if (mMaxPage <= 0)
	{
		mMaxPage = 1;
	}

	if (mCurrentPage <= 0)
	{
		mCurrentPage = 1;
	}
	else if (mCurrentPage > mMaxPage)
	{
		mCurrentPage = mMaxPage;
	}
}

void ArenaRankPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageGetArenaHeroResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess())
			{
				mCurrentPage = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				mMaxPage = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				testPage();
				refreshList();
				refreshMenu();
			}
		}
	}
}

//////////ArenaRecordPanel//////////////////////////////////////////////
ArenaRecordPanel::ArenaRecordPanel()
	:mRecordList(NULL)
{

}

ArenaRecordPanel::~ArenaRecordPanel()
{

}

bool ArenaRecordPanel::init()
{
	if (!CCNode::init())
	{
		return false;
	}

	initUI();

	return true;
}

void ArenaRecordPanel::initUI()
{
	// board
	CCSprite *board = LayoutData::getSprite(CPModuleName::COMMON, "floatBoard");
	addChild(board);
	setContentSize(board->getContentSize());

	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "arenaRecordTitle");
	addChild(titleLabel);

	// record
	const CCSize &recordSize = LayoutData::getSize(CPModuleName::ACTIVITY, "arenaRecordList");
	mRecordList = CPItemComponents::create(recordSize, new CPLayoutList);
	mRecordList->setClickSensitive(true);
	mRecordList->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "arenaRecordList"));
	addChild(mRecordList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::ACTIVITY, "arenaRecordScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mRecordList->setScrollbar(scrollBar);
	const int fontSize = LayoutData::getInt(CPModuleName::ACTIVITY, "arenaRecordFontSize");
	const int recordCnt = ActivityData::getArenaRecordSize();
	for (int i = recordCnt - 1; i >= 0; i--)
	{
		CPRichText *text = RichTextUtils::getRichText(ArenaHelper::getRecord(i), fontSize, recordSize.width, 0);
		mRecordList->addItem(text);
	}

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "floatClose");
	closeBtn->setTarget(this, menu_selector(ArenaRecordPanel::onClose));
	menu->addChild(closeBtn);
}

void ArenaRecordPanel::onPlayer( CCObject *target )
{

}

void ArenaRecordPanel::onClose( CCObject *target )
{
	close();
}

/////////ArenaFightPanel////////////////////////////////////////////
#define PLAY_RATE 0.6f
ArenaFightPanel::ArenaFightPanel()
	:mChecker(NULL)
	,mArenaPanel(NULL)
	,mMyRole(NULL)
	,mOtherRole(NULL)
	,mMyHead(NULL)
	,mOtherHead(NULL)
	,mTargetRank(0)
	,mTargetPID(0)
	,mCurrentAction(0)
	,mMaxAction(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

ArenaFightPanel::~ArenaFightPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	if (mArenaPanel)
	{
		mArenaPanel->setState(ArenaState::ready);
	}
}

ArenaFightPanel * ArenaFightPanel::create()
{
	return createWithData(NULL, 0);
}

ArenaFightPanel * ArenaFightPanel::createWithData( ArenaPanel *arenaPanel, int targetRank )
{
	ArenaFightPanel *ret = new ArenaFightPanel;
	if (ret && ret->initWithData(arenaPanel, targetRank))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool ArenaFightPanel::initWithData( ArenaPanel *arenaPanel, int targetRank )
{
	if (!CCLayer::init())
	{
		return false;
	}

	setTouchEnabled(true);

	mArenaPanel = arenaPanel;
	if (mArenaPanel)
	{
		mArenaPanel->setState(ArenaState::fighting);
		mTargetRank = targetRank;
	}
	else
	{
		CPUnused(targetRank);
		mTargetPID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
		mTargetRank = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
	}

	initUI();
	fightRequest();

	return true;
}

void ArenaFightPanel::initUI()
{
	// bkg
	CCSprite *bkg = LayoutData::getSpriteByFile(CPModuleName::ACTIVITY, "arenaFightBkg");
	addChild(bkg);

	// close board
	CCScale9Sprite *closeBoard = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "arenaFightCloseBoard");
	addChild(closeBoard);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *closeBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "arenaFightClose");
	closeBtn->setTarget(this, menu_selector(ArenaFightPanel::onClose));
	menu->addChild(closeBtn);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}
// 初始化竞技场战斗动画和头像
// 功能：创建玩家和对手的角色动画模型，以及对应的头像面板
void ArenaFightPanel::initAnimAndHead()
{
	// my role
	GameRole *myRole = GameData::getMyRole();
	if (!mMyRole)
	{
		mMyRole = AnimElement::create(0, CPElement::Type::player, HeroData::getGender());
		mMyRole->setCloth(myRole->getDress(AVATAR_TYPE_CLOTH));
		mMyRole->setWeapon(myRole->getDress(AVATAR_TYPE_WEAPON));
		mMyRole->setWings(myRole->getDress(AVATAR_TYPE_WINGS));
		mMyRole->act(CPElement::State::idle, DIR_RIGHT);
		mMyRole->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "arenaFightMyStart"));
		addChild(mMyRole);
	}
	
	if (!mMyHead)
	{
		mMyHead = HeadPanel::create();
		mMyHead->setName(myRole->mName);
		mMyHead->setLevel(HeroData::getLevel());
		mMyHead->setJob(HeroData::getJob());
		mMyHead->setGender(HeroData::getGender());
		mMyHead->setHP(1, 1);
		mMyHead->setMP(1, 1);
		mMyHead->setAnchorPoint(ccp(0, 1));
		mMyHead->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "leftTop"));
		addChild(mMyHead);
	}
	
	// other role
	int pid = 0, level= 0, reborn = 0, job = 0, gender = 0;
	int cloth = 0, weapon = 0, wings = 0;
	int maxHP = 0;
	std::string name;
	ActivityData::getArenaFightBegin(2, level, name, reborn, job, gender, cloth, weapon, wings, maxHP);
	if (!mOtherRole)
	{
		mOtherRole = AnimElement::create(0, CPElement::Type::player, gender);
		mOtherRole->setCloth(cloth);
		mOtherRole->setWeapon(weapon);
		mOtherRole->setWings(wings);
		mOtherRole->act(CPElement::State::idle, DIR_LEFT);
		mOtherRole->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "arenaFightOtherStart"));
		addChild(mOtherRole);
	}
	
	if (!mOtherHead)
	{
		mOtherHead = HeadPanel::create();
		mOtherHead->setName(name);
		mOtherHead->setLevel(level);
		mOtherHead->setJob(job);
		mOtherHead->setGender(gender);
		mOtherHead->setHP(1, 1);
		mOtherHead->setMP(1, 1);
		mOtherHead->setAnchorPoint(ccp(1, 1));
		mOtherHead->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "rightTop"));
		addChild(mOtherHead);
	}
}

void ArenaFightPanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool ArenaFightPanel::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);

	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}
	return true;
}

void ArenaFightPanel::fightRequest()
{
	mChecker->start();
	if (mTargetPID == 0)
	{
		ArenaHelper::challengeRequest(mTargetRank);
	}
	else
	{
		ArenaHelper::challengeRequest(mTargetRank, mTargetPID);
	}
}

void ArenaFightPanel::showDamage( float dt )
{
	if (mCurrentAction >= mMaxAction)
	{
		unschedule(schedule_selector(ArenaFightPanel::showDamage));
		playEnd();
		return;
	}

	int id = 0, damage = 0;
	ActivityData::getArenaFightData(mCurrentAction, id, damage);
	showDamage(id, damage);

	mCurrentAction++;
}

void ArenaFightPanel::showDamage( int id, int damage )
{
	char strdhp[60];
	sprintf(strdhp, ":%d", damage);
	const std::string &path = LayoutData::getString(CPModuleName::COMMON, "combatNumber");
	const CCSize &size = LayoutData::getSize(CPModuleName::COMMON, "combatNumber");
	CCLabelAtlas *damageLabel = CCLabelAtlas::create(strdhp, path.c_str(), size.width, size.height, '0');
	damageLabel->setAnchorPoint(ccp(0.5f, 0.5f));
	damageLabel->setVisible(false);
	addChild(damageLabel);

	const int oy = LayoutData::getInt(CPModuleName::ACTIVITY, "arenaFightDamageOy");
	damageLabel->runAction(CCSequence::create(
		CCDelayTime::create(PLAY_RATE),
		CCShow::create(),
		CCMoveBy::create(PLAY_RATE, ccp(0, oy)),
		CCActionInstantRemoveFromParent::create(),
		NULL));

	//
	const int y = LayoutData::getInt(CPModuleName::ACTIVITY, "arenaFightDamageY");
	if (id == 1)
	{
		damageLabel->setPosition(ccp(mOtherRole->getPositionX(), y));
		mOtherHead->setHP(mOtherHead->getCurrentHP() - damage, mOtherHead->getMaxHP());
		mMyRole->act(CPElement::State::attack, DIR_RIGHT);
		mOtherRole->act(CPElement::State::idle, DIR_LEFT);
	}
	else if (id == 2)
	{
		damageLabel->setPosition(ccp(mMyRole->getPositionX(), y));
		mMyHead->setHP(mMyHead->getCurrentHP() - damage, mMyHead->getMaxHP());
		mMyRole->act(CPElement::State::idle, DIR_RIGHT);
		mOtherRole->act(CPElement::State::attack, DIR_LEFT);
	}
}

void ArenaFightPanel::playBegin()
{
	int hp = ArenaHelper::getMyMaxHP();
	mMyHead->setHP(hp, hp);
	hp = ArenaHelper::getOtherMaxHP();
	mOtherHead->setHP(hp, hp);

#define COUNT_DOWN_DELAY 1.0f
	const int cnt = 3;
	for (int i = 0; i < cnt; i++)
	{
		const std::string &path = LayoutData::getString(CPModuleName::MAIN_UI, "lvlUpNum");
		const CCSize &size = LayoutData::getSize(CPModuleName::MAIN_UI, "lvlUpNum");
		CCLabelAtlas *label = CCLabelAtlas::create(StringUtils::toString(cnt - i).c_str(), path.c_str(), size.width, size.height, '0');
		label->setScale(4.0f);
		label->setVisible(false);
		label->setAnchorPoint(ccp(0.5f, 0.5f));
		label->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY, "arenaFightCountDown"));
		addChild(label);

		CCAction *action = CCSequence::create(
			CCDelayTime::create(COUNT_DOWN_DELAY * i),
			CCShow::create(),
			CCEaseSineIn::create(CCScaleTo::create(COUNT_DOWN_DELAY, 1.0f)),
			CCFadeOut::create(0.1f),
			CCActionInstantRemoveFromParent::create(),
			NULL);
		label->runAction(action);
	}
	
	this->runAction(CCSequence::create(
		CCDelayTime::create(COUNT_DOWN_DELAY * cnt),
		CCCallFunc::create(this, callfunc_selector(ArenaFightPanel::playMove)),
		NULL));
}

void ArenaFightPanel::playMove()
{
#define MOVE_TIME 2.0f
	const CCPoint &myPos = LayoutData::getPoint(CPModuleName::ACTIVITY, "arenaFightMyStop");
	const CCPoint &otherPos = LayoutData::getPoint(CPModuleName::ACTIVITY, "arenaFightOtherStop");
	mMyRole->act(CPElement::State::walk, DIR_RIGHT);
	mMyRole->runAction(CCMoveTo::create(MOVE_TIME, myPos));
	mOtherRole->act(CPElement::State::walk, DIR_LEFT);
	mOtherRole->runAction(CCMoveTo::create(MOVE_TIME, otherPos));
	this->runAction(CCSequence::create(
		CCDelayTime::create(MOVE_TIME),
		CCCallFunc::create(this, callfunc_selector(ArenaFightPanel::playFight)),
		NULL));
}

void ArenaFightPanel::playFight()
{
	mCurrentAction = 0;
	mMaxAction = ActivityData::getArenaFightDataSize();
	schedule(schedule_selector(ArenaFightPanel::showDamage), PLAY_RATE);
	showDamage(0);
}

void ArenaFightPanel::playEnd()
{
	const int winnerID = ActivityData::getArenaWinner();
	if (winnerID == 1)
	{
		mMyRole->act(CPElement::State::idle, DIR_RIGHT);
		mOtherRole->act(CPElement::State::die, DIR_LEFT);
		NotificationHelper::showNote(LayoutData::getString(CPModuleName::ACTIVITY, "arenaWin"));
	}
	else
	{
		mMyRole->act(CPElement::State::die, DIR_RIGHT);
		mOtherRole->act(CPElement::State::idle, DIR_LEFT);
		NotificationHelper::showNote(LayoutData::getString(CPModuleName::ACTIVITY, "arenaLose"));
	}
}

void ArenaFightPanel::onClose( CCObject *target )
{
	unschedule(schedule_selector(ArenaFightPanel::showDamage));
	removeFromParent();
}

void ArenaFightPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageArenaFightResponse")
		{
			mChecker->stop();
			if (!CPEventHelper::isRequestSuccess())
			{
				onClose(NULL);
			}
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageArenaFightNotify")
		{
			initAnimAndHead();
			playBegin();
		}
	}
}

/////////ArenaHelper//////////////////////////////////////////////////
std::string ArenaHelper::getReward()
{
	if (HeroData::getProp(Entity::attr_arena_rank) <= 0)
	{
		return "";
	}

	int exp = 0, honor = 0;
	getRankReward(HeroData::getLevel(), HeroData::getProp(Entity::attr_arena_rank), exp, honor);
	std::string ret = LayoutData::getString(CPModuleName::COMMON, "exp") + " " + StringUtils::toString(exp);
	ret += "  " + LayoutData::getString(CPModuleName::COMMON, "honor") + " " + StringUtils::toString(honor);
	return ret;
}

bool ArenaHelper::getRankReward( int level, int rank, int &exp, int &honor )
{
	CPLua->push(level);
	CPLua->push(rank);
	if (CPLua->call("gdGame", "arenaRankReward", 2, 2)
		&& CPLua->pop(honor)
		&& CPLua->pop(exp))
	{
		return true;
	}
	CCLog(">>>Error: ArenaHelper::getRankReward failed, rank = %d", rank);
	return false;
}

std::string ArenaHelper::getPlayCnt()
{
	int maxCnt = 0;
	StaticData::getActivityData(EvtData::evt_zljj, "datax", maxCnt);
	int cnt = 0, data2 = 0, data3 = 0;
	ActivityData::getExData(ActivityData::getActivityID("zljj"), cnt, data2, data3);
	cnt = maxCnt - cnt;
	if (cnt < 0)
	{
		cnt = 0;
	}
	return StringUtils::toString(cnt) + "/" + StringUtils::toString(maxCnt);
}

std::string ArenaHelper::getFightAdd()
{
	const int buff = HeroData::getProp(Entity::attr_arena_buff);
	if (buff < 0)
	{
		return "";
	}

	float factor = 1.0f;
	StaticData::getArenaBuffData(buff, factor);
	factor -= 1.0f;

	std::string ret;
	const int data = HeroData::getProp(Entity::attr_combat_data_num) * factor;
	if (data > 0)
	{
		ret = "+" + StringUtils::toString(data);
		const std::string &key = "arenaBuff" + StringUtils::toString(buff);
		ret += "(";
		ret += LayoutData::getString(CPModuleName::ACTIVITY, key);
		ret += ")";
	}
	return ret;
}

std::string ArenaHelper::getRecord( int index )
{
	std::string name;
	int challengerFlag = 0, winFlag = 0;
	ActivityData::getArenaRecord(index, name, challengerFlag, winFlag);

	std::string ret;
	const int isNew = ((index + 1) == ActivityData::getArenaRecordSize() ? 1 : 0);
	Lua::instance()->push(isNew);
	Lua::instance()->push_utf8(name);
	Lua::instance()->push(challengerFlag);
	Lua::instance()->push(winFlag);
	if (Lua::instance()->call("activity_get_arena_record", 4, 1) &&
		Lua::instance()->pop_utf8(ret))
	{
		return ret;
	}
	CCLog(">>>Error: ArenaHelper::getRecord, index = %d", index);
	return ret;
}

int ArenaHelper::getMyMaxHP()
{
	int level= 0, reborn = 0, job = 0, gender = 0, maxHP = 0;
	int cloth = 0, weapon = 0, wings = 0;
	std::string name;
	ActivityData::getArenaFightBegin(1, level, name, reborn, job, gender, cloth, weapon, wings, maxHP);
	return maxHP;
}

int ArenaHelper::getOtherMaxHP()
{
	int level= 0, reborn = 0, job = 0, gender = 0, maxHP = 0;
	int cloth = 0, weapon = 0, wings = 0;
	std::string name;
	ActivityData::getArenaFightBegin(2, level, name, reborn, job, gender, cloth, weapon, wings, maxHP);
	return maxHP;
}

void ArenaHelper::dataRequest()
{
	HandleMessage::sendMessage(new MsgOpenArenaRequest);
}

void ArenaHelper::challengeRequest( int rank )
{
	challengeRequest(rank, ActivityData::getArenaCompetitorPID(rank));
}

void ArenaHelper::challengeRequest( int rank, int pid )
{
	MsgArenaFightRequest *msg = new MsgArenaFightRequest;
	msg->rank = rank;
	msg->pid = pid;
	HandleMessage::sendMessage(msg);
}

void ArenaHelper::cleanCoolDownRequest()
{
	MsgCleanCoolDownRequest *msg = new MsgCleanCoolDownRequest;
	msg->cdtype = EvtData::cd_cdzljj;
	HandleMessage::sendMessage(msg);
}

void ArenaHelper::addCountRequest()
{
	HandleMessage::sendMessage(new MsgBuyArenaFightCntRequest);
}

void ArenaHelper::refreshBuffRequest( int refreshType )
{
	MsgRefreshArenaBuffRequest *msg = new MsgRefreshArenaBuffRequest;
	msg->refreshtype = refreshType;
	HandleMessage::sendMessage(msg);
}

void ArenaHelper::recordRequest()
{
	HandleMessage::sendMessage(new MsgGetPlayerArenaFightRecordRequest);
}

void ArenaHelper::rankRequest( int page )
{
	MsgGetArenaHeroRequest *msg = new MsgGetArenaHeroRequest;
	msg->page = page;
	HandleMessage::sendMessage(msg);
}

void ArenaHelper::heighThreeRequest()
{
	MsgSyncWorldDataRequest *msg = new MsgSyncWorldDataRequest;
	msg->wid = WorldDefination::prop_arena_first_lvl;
	msg->version = ActivityData::getWorldIntPropVersion(WorldDefination::prop_arena_first_lvl);
	HandleMessage::sendMessage(msg);
}
