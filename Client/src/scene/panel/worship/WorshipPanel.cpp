#include "WorshipPanel.h"
#include "MsgActivity.h"
#include "ActivityDefinition.h"
#include "EvtDataDefinition.h"
#include "ActivityModule.h"

#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/ActivityData.h"
#include "userdata/activitydata/WorshipData.h"

#include "ext/GeneralMenu.h"

#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"

#include "network/HandleMessage.h"

#include "utils/StringUtils.h"

#include "logic/ItemOperator.h"

#include "controls/CPComboBox.h"
#include "controls/CPCheckBox.h"

#include "scene/panel/FloatPanel.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"


const int MultipleTable[5] = {1,2,3,5,10};
enum TagWorship
{
	TAG_ADD_WORSHIP_TIMES,
	TAG_REFRESH_TARGET,
	TAG_WORSHIP_ONCE,
	TAG_CONTEMPT_ONCE,
	TAG_REFRESH_FLAG,
};

/////////WorshipPanel///////////////////////////////////////////////
WorshipPanel::WorshipPanel()
	: m_pGoldenBorder(NULL)
	,mCheckBox(NULL)
	,mComboBox(NULL)
	, m_pFinalMultiple(NULL)
	, m_pFinalExperience(NULL)
	, m_pRefreshTimes(NULL)
	, m_pDoubleWorship(NULL)
	, m_pWorshipTimes(NULL)
	, m_pAddTimes(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

WorshipPanel::~WorshipPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool WorshipPanel::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}

	initUI();
	dataRequest();
	
	return true;
}

void WorshipPanel::onEnter()
{
	FullScreenPanel::onEnter();
	EventDispatcher::sharedEventDispather()->addListener(this);
}

void WorshipPanel::onExit()
{
	EventDispatcher::sharedEventDispather()->removeListener(this);
	FullScreenPanel::onExit();
}

void WorshipPanel::initUI()
{
	// title
	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "worshipTitle");
	addChild(title);

	// board
	CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "worshipBoard");
	addChild(board);

	CCScale9Sprite *subBoard = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "worshipSubBoard");
	addChild(subBoard);

	//add the other sprites
	std::string keyList[2] = {"dividingline.up","dividingline.down"};
	for (int i=0; i<2; i++)
	{
		std::string key = "worship.sprite." + keyList[i];
		CCSprite* pSprite = SystemData::getSpriteByPlist(key);
		addChild(pSprite);
	}

	for (int i=0; i<5; i++)
	{
		addOneExpGrid(i);
	}

	//add the other static labels
	std::string staticLabels[5] = {"reward","rewardmultiple","worshipcontempttimes","worshipcontempttimesadd","freerefreshtimes"};
	for(int i=0; i<5; i++)
	{
		std::string key = "worship.lbl."+staticLabels[i];
		CCLabelTTF* label = SystemData::getLabelTTF(key);
		addChild(label);
	}

	//add the dynamic labels
	updateDoubleWorshipTips();
	updateWorshipTimes();
	updateMultipleLabels();

	//add the buttons
	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCMenuItemImage *refreshBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "worshipRefresh");
	refreshBtn->setTarget(this, menu_selector(WorshipPanel::callback));
	pMenu->addChild(refreshBtn, 0, TAG_REFRESH_TARGET);

	CCMenuItemImage *addBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "worshipAddTimes");
	addBtn->setTarget(this, menu_selector(WorshipPanel::callback));
	pMenu->addChild(addBtn, 0, TAG_ADD_WORSHIP_TIMES);

	CCMenuItemImage *goodBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "worshipGood");
	goodBtn->setTarget(this, menu_selector(WorshipPanel::callback));
	pMenu->addChild(goodBtn, 0, TAG_WORSHIP_ONCE);

	CCMenuItemImage *badBtn = LayoutData::getMenuItemLabelImage(CPModuleName::ACTIVITY, "worshipBad");
	badBtn->setTarget(this, menu_selector(WorshipPanel::callback));
	pMenu->addChild(badBtn, 0, TAG_CONTEMPT_ONCE);

	// check box
	mCheckBox = LayoutData::getCheckBox(CPModuleName::ACTIVITY, "worship");
	addChild(mCheckBox);

	//add the list menu to select multiples
	mComboBox = LayoutData::getComboBox(CPModuleName::COMMON, "normal");
	mComboBox->setPosition(SystemData::getLayoutPoint("worship.btn.select")); 
	mComboBox->setAnchorPoint(CCPointZero); 
	addChild(mComboBox);
	for (int j = 0; j < 5; j++) 
	{
		std::string strMultiple = SystemData::intToString(MultipleTable[j])+SystemData::getLayoutString("worship.label.times");
		mComboBox->addLabelItem(strMultiple);
	}
}

void WorshipPanel::dataRequest()
{
	MsgMobaiDataRequest *msg = new MsgMobaiDataRequest;
	HandleMessage::sendMessage(msg);
}

void WorshipPanel::callback( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		const int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_REFRESH_TARGET:
			{
				const int refreshTimes = Worshipdata::s_max_refresh_count - ActivityData::getExDataX(EvtData::evt_czmb);
				if (refreshTimes > 0)
				{
					onRefreshTarget(Button_QD);
					return;
				}

				int cost = 0;
				StaticData::getGlobalData("worshipRefreshCost", cost);
				if (!ItemOperator::testGoldEnough(cost, true))
				{
					return;
				}

				StrVector vect;
				vect.push_back(StringUtils::toString(cost));
				FloatPanel::show(FloatPanelType::Worship_refresh, vect, this, floatpanel_selector(WorshipPanel::onRefreshTarget));
			}
			break;
		case TAG_ADD_WORSHIP_TIMES:
			{
				const int addTimes = Worshipdata::s_max_add_count - ActivityData::getExDataZ(EvtData::evt_czmb);
				if (addTimes <= 0)
				{
					CPEventHelper::uiNotify("WorshipPanel", "", Error::Mobai_addcnt_max);
					return;
				}

				const int curTimes = Worshipdata::s_max_worship_count - ActivityData::getExDataY(EvtData::evt_czmb);
				if (curTimes >= Worshipdata::s_max_worship_count)
				{
					CPEventHelper::uiNotify("WorshipPanel", "", Error::Mobai_cnt_is_zero);
					return;
				}

				int cost = 0;
				StaticData::getGlobalData("worshipAddCost", cost);
				if (!ItemOperator::testGoldEnough(cost))
				{
					return;
				}

				StrVector vect;
				vect.push_back(StringUtils::toString(cost));
				FloatPanel::show(FloatPanelType::Worship_add_count, vect, this, floatpanel_selector(WorshipPanel::onAddCount));
			}
			break;
		case TAG_CONTEMPT_ONCE:
			{
				const int curTimes = Worshipdata::s_max_worship_count - ActivityData::getExDataY(EvtData::evt_czmb);
				if (curTimes <= 0)
				{
					CPEventHelper::uiNotify("WorshipPanel", "", Error::Mobai_is_over_max);
					return;
				}
				MsgMobaiBishiRequest* msg = new MsgMobaiBishiRequest;
				msg->MobaiBishi = Activity::Bishi;
				HandleMessage::sendMessage(msg);
			}
			break;
		case TAG_WORSHIP_ONCE:
			{
				const int curTimes = Worshipdata::s_max_worship_count - ActivityData::getExDataY(EvtData::evt_czmb);
				if (curTimes <= 0)
				{
					CPEventHelper::uiNotify("WorshipPanel", "", Error::Mobai_is_over_max);
					return;
				}
				MsgMobaiBishiRequest* msg = new MsgMobaiBishiRequest;
				msg->MobaiBishi = Activity::Mobai;
				HandleMessage::sendMessage(msg);
			}
			break;
		default:
			break;
		}
	}
}

void WorshipPanel::onRefreshTarget( int btnType )
{
	if (btnType == Button_QD)
	{
		MsgRefreshMobaiPerRequest* msg = new MsgRefreshMobaiPerRequest;
		msg->per = mComboBox->getCurrentIndex();
		if(mCheckBox->isChecked())
		{
			msg->type = Activity::Mobai_refresh_ending;
		}
		else
		{
			msg->type = Activity::Mobai_refresh_normal;
		}
		HandleMessage::sendMessage(msg);
	}
}

void WorshipPanel::onAddCount( int btnType )
{
	if (btnType == Button_QD)
	{
		MsgAddMobaiCntRequest *msg = new MsgAddMobaiCntRequest;
		HandleMessage::sendMessage(msg);
	}
}

void WorshipPanel::addOneExpGrid( int id )
{
	CCNode* pGrid = CCNode::create();
	pGrid->setAnchorPoint(CCPointZero);
	static CCPoint beginPos = SystemData::getLayoutPoint("worship.point.experience_grid_begin");
	static float spanW = SystemData::getLayoutValue("worship.value.experience.spanw");
	pGrid->setPosition(ccpAdd(beginPos,ccp(id*spanW,0)));
	addChild(pGrid);

	//add the border
	CCScale9Sprite* pGoldenBorder = SystemData::getScale9SpriteByPlist("worship.sprite.experienceborder");
	pGrid->addChild(pGoldenBorder);

	//add the icon
	const std::string &iconKey = "worshipIcon" + StringUtils::toString(id);
	CCSprite* expIcon = LayoutData::getSprite(CPModuleName::ACTIVITY, iconKey);
	expIcon->setPosition(ccp(pGoldenBorder->getContentSize().width/2,pGoldenBorder->getContentSize().height/2));
	pGoldenBorder->addChild(expIcon);

	//add the multiple label
	std::string strMultiple = SystemData::intToString(MultipleTable[id])+SystemData::getLayoutString("worship.label.times");
	CCLabelTTF* pMultiLabel = SystemData::getLabelTTF("worship.lbl.multiple");
	pMultiLabel->setString(strMultiple.c_str());
	pGrid->addChild(pMultiLabel);

	//add the experience label
	CCLabelTTF* pExperience = SystemData::getLabelTTF("worship.lbl.experience");
	std::string strExperience = pExperience->getString();
	strExperience += SystemData::intToString(MultipleTable[id]*Worshipdata::s_experience);
	pExperience->setString(strExperience.c_str());
	pGrid->addChild(pExperience);
}

void WorshipPanel::randomMultiple()
{
	if(!m_pGoldenBorder)
	{
		m_pGoldenBorder = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY, "worshipSelBorder");
		addChild(m_pGoldenBorder);
	}

	const int t = HeroData::getProp(Entity::attr_mobai_multiple);
	const CCPoint &beginPos = LayoutData::getPoint(CPModuleName::ACTIVITY, "worshipFirst");
	const float &spanW = LayoutData::getInt(CPModuleName::ACTIVITY, "worshipOx");
	m_pGoldenBorder->setPosition(ccpAdd(beginPos, ccp(t * spanW, 0))),
	updateMultipleLabels();
}

void WorshipPanel::updateMultipleLabels()
{
	//add the dynamic labels
	if(!m_pFinalExperience)
	{
		m_pFinalExperience = SystemData::getLabelTTF("worship.lbl.rewardexperience");
		addChild(m_pFinalExperience);
	}

	if(!m_pFinalMultiple)
	{
		m_pFinalMultiple = SystemData::getLabelTTF("worship.lbl.rewardtimesvalue");
		addChild(m_pFinalMultiple);
	}

	if(!m_pRefreshTimes)
	{
		m_pRefreshTimes = SystemData::getLabelTTF("worship.lbl.freetimesvalues");
		addChild(m_pRefreshTimes);
	}

	m_pFinalExperience->setString((SystemData::getLayoutString("worship.lbl.rewardexperience")+SystemData::intToString(Worshipdata::s_experience*MultipleTable[HeroData::getProp(Entity::attr_mobai_multiple)])).c_str());
	m_pFinalMultiple->setString((SystemData::intToString(MultipleTable[HeroData::getProp(Entity::attr_mobai_multiple)])+SystemData::getLayoutString("worship.label.times")).c_str());
	m_pRefreshTimes->setString((SystemData::intToString(Worshipdata::s_max_refresh_count-ActivityData::getExDataX(EvtData::evt_czmb))+"/"+SystemData::intToString(Worshipdata::s_max_refresh_count)).c_str());
}

void WorshipPanel::updateDoubleWorshipTips()
{
	if(!m_pDoubleWorship)
	{
		m_pDoubleWorship = SystemData::getLabelTTF("worship.lbl.doubleworship");
	}
	else
	{
		m_pDoubleWorship = SystemData::getLabelTTF("worship.lbl.nonedoubleworship");
	}

	if(Worshipdata::s_is_double)
	{
		m_pDoubleWorship->setString(SystemData::getLayoutString("worship.lbl.doubleworship").c_str());
	}
	else
	{
		m_pDoubleWorship->setString(SystemData::getLayoutString("worship.lbl.nonedoubleworship").c_str());
	}
}

void WorshipPanel::updateWorshipTimes()
{
	if(!m_pWorshipTimes)
	{
		m_pWorshipTimes = SystemData::getLabelTTF("worship.lbl.worshiptimesvalue");
		addChild(m_pWorshipTimes);
	}

	if(!m_pAddTimes)
	{
		m_pAddTimes = SystemData::getLabelTTF("worship.lbl.addtimesvalues");
		addChild(m_pAddTimes);
	}

	const int curTimes = Worshipdata::s_max_worship_count - ActivityData::getExDataY(EvtData::evt_czmb);
	m_pWorshipTimes->setString((SystemData::intToString(curTimes)+"/"+SystemData::intToString(Worshipdata::s_max_worship_count)).c_str());
	m_pAddTimes->setString(SystemData::intToString(Worshipdata::s_max_add_count - ActivityData::getExDataZ(EvtData::evt_czmb)).c_str());
}

void WorshipPanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_UPDATE_WOSHIP_DATA)
	{
		updateMultipleLabels();
		updateDoubleWorshipTips();
		updateWorshipTimes();
	}
}

void WorshipPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageSyncPlayerEventDataNotify")
		{
			const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (type == EvtData::evt_czmb)
			{
				updateMultipleLabels();
				updateDoubleWorshipTips();
				updateWorshipTimes();
			}
		}
		else if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (type == Entity::attr_mobai_multiple)
			{
				randomMultiple();
			}
		}
	}
}

